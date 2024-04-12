/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Rceinit

	Routine per inizializzazione paramteri e tabelle gestione Rce

	Parametri

	nessuno

	Ritorno

	nessuno

	21 giugno 1993

   13 Febbraio 1995
      Modifiche per gestioni rce a gruppi

*/
#include <stdlib.h>
#include <malloc.h>
#include "comunic.inc"
#include "sepdati.inc"
#include "pscserr.inc"
#include "mesqueue.h"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnodi.inc"

extern DB_HEADER h_db;
extern short c_rce;
short RceComp(S_RCE *, S_RCE *);

RceInit()
{
	S_BRCE *pBrce;
   S_GROUP_ACQ *pGroup;
   short nGroup, j;
   char *arm;

	pBrce=&BuffRce[0];
   pGroup=&bGroupAcq[0];
   for(nGroup=0;nGroup<nBRCE;nGroup++,pBrce++,pGroup++)
   {
      if(!pGroup->def) break;
      arm=&pGroup->arm[0];
      for(j=0;j<max_zone;j++,arm++)
      {
         if(*arm==-1) break;
         snodi[nodo_armadi+(*arm)*2].Group=nGroup;
         snodi[nodo_armadi+(*arm)*2+1].Group=nGroup;
      }
   	pBrce->f=NON_ALLOCATO;
	   pBrce->n=0;
   	pBrce->max=(n_rceante+n_rcesucc)*2;
	   pBrce->ord=(n_rceante+n_rcesucc);

   	if((pBrce->p=malloc((pBrce->max*sizeof(S_RCE))))==NULL) return(-1);

   }
   n_rcefp=dbadv[PCRCE];									// valore rce corrente
   return (0);
}
/*
	RceIns

	Routine per l'inserimento di un elemento Rce nel buffer allocato
	proviente da un dato nodo

	pRce	puntatore al buffer da inserire
	punti	n. massimo punti da trattare
	nodo	short indice nodo armadio provenienza da 0 a 12

	Ritorno

	nessuno

   13 Febbraio 1995
   Definizione di piu' buffer di RCE - dato l'indice del nodo
   ricavo l'indice del gruppo di acquisizione a cui appartiene
   l'armadio
*/
RceIns(S_RCE *pRce,short punti, short nodo)
{
	short i;
	QUEUE_PACKET pack;
	S_BRCE *pBrce;
	S_STRCE mess;
	S_RCE	  mrce;
   short nGroup;

	pack.wto=0;
	pack.flg=MSG_WAIT;
	pack.que=c_rce;
	pack.lmsg=sizeof(S_STRCE);
	pack.amsg=(char *)&mess;

	nGroup=snodi[nodo_armadi+nodo*2].Group;
   mess.gruppo=nGroup;

	if(!punti)								// ordinamento e richiesta stampa perturbografica
	{											// invio messaggio
		pBrce=&BuffRce[nGroup];
		pBrce->f=IN_ORDINAMENTO;
		mess.mess=rceprnp;
		enqueue(&pack);
	}
	else
	{
		for(i=0;i<punti;i++,pRce++)
		{
			memcpy(&mrce,pRce,sizeof(S_RCE));		// copio singolo pacchetto
   		pBrce=&BuffRce[nGroup];
			if(pBrce->f==IN_ORDINAMENTO)			// non ancora concluso ordinamento
			{
	   	   pscserr(ERR_TASK,TASK_ACQUI,ROU_RCEORD,0,SYS_CONT);
				return(0);				
			}
			mrce.tipo=nodo;
/*
	verifico che l'identificativo sia ammissibile e lo sostituisco con
	indice logico in dbs
*/
			if(mrce.id < 1 || mrce.id > heafsvar[nodo].l_punto)
			{
//	   	   pscserr(ERR_TASK,TASK_ACQUI,ROU_RCE,pRce->id,SYS_CONT);
				continue;
			}
/*
	recupero puntatore in data base eliminando il bit che segnala
	il tipo di punto digitale o analogico
*/
	   	mrce.id=(*(svinarp[nodo]+mrce.id-1));
		   if(mrce.id==-1) return(0);
	   	mrce.id=mrce.id & (~mask_tpun);
			if(mrce.id<0 || mrce.id >= h_db.dimda) 
	   	{ 
//   	   	pscserr(ERR_TASK,TASK_ACQUI,ROU_RCE,pRce->id,SYS_CONT);
	      	return(0);
		   }
/*
	se ho raggiunto la massima dimensione possibile procedo
	ad un ordinamento
*/
			if(pBrce->n>=pBrce->max) RceSort(pBrce,1);	// con annullamento dati piu' vecchi
/*
	Inserimento nuovo dato
*/
			memcpy(pBrce->p+pBrce->n,&mrce,sizeof(S_RCE));
			pBrce->n++;
/*
	verifico il tipo di categoria ed accodo al task di stampa se
	necessario (se stampa continua non abilitata non accodo eventi di
	tipo A)
	Se l'evento e' di categoria C inizializzo il time out per
	la fine dei messaggi
*/
			if((dbdatr[mrce.id] & mask_cC) && !bGroupAcq[nGroup].Rce_timeout)
      			bGroupAcq[nGroup].Rce_timeout=RCETIME;
			if(!(dbdd[rcestampa] & mask_sl) || !(dbdatr[mrce.id] & mask_cA))
				{
					mess.mess=rceprnc;
					memcpy(&mess.rce,&mrce,sizeof(S_RCE));
					enqueue(&pack);
				}
		}
	}
   return(0);
}
/*
	RceSort

	Routine per l'ordinamento dei dati Rce
	Se flag assume il valore 1 dopo l'ordinamento gli	ultimi ord valori
	vengono spostati all'inizio del buffer

	Parametri

	S_DBRCE	*pBrce	puntatore buffer in uso
	short		flag     =1 compattamento e annullamento dati piu' vecchi
							=0 solo compattamento

	Ritorno

	nessuno

*/
RceSort(S_BRCE *pBrce, short flag)
{
	qsort((void*)pBrce->p,(size_t)pBrce->n,sizeof(S_RCE),RceComp);
	if(!flag) return;
	if(pBrce->n > pBrce->ord)
		{
			memcpy(pBrce->p,pBrce->p+(pBrce->n-pBrce->ord),
				pBrce->ord*sizeof(S_RCE));
		}
	pBrce->n=min(pBrce->n,pBrce->ord);
	return;
}
short RceComp(S_RCE *p1, S_RCE *p2)
{
/*
	se la differenza fra i giorni e' > 300, e' variato
	l'anno
*/
	if(p1->giorno > p2->giorno)
		{
		if(((p1->giorno-p2->giorno)<300)) 
           return(1);
		else 
           return(-1);
		}
	if(p1->giorno < p2->giorno)
		{
		if(((p2->giorno-p1->giorno)<300)) 
         return(-1);
		else 
         return(1);
		}
	if(p1->ora > p2->ora) 
      return(1);
	if(p1->ora < p2->ora) 
      return(-1);
	if(p1->minuti > p2->minuti) 
      return(1);
	if(p1->minuti < p2->minuti) 
      return(-1);
	if(p1->secondi > p2->secondi) 
      return(1);
	if(p1->secondi < p2->secondi) 
      return(-1);
	if(p1->millisecondi > p2->millisecondi) 
      return(1);
	if(p1->millisecondi < p2->millisecondi) 
      return(-1);
	return(0);
}
