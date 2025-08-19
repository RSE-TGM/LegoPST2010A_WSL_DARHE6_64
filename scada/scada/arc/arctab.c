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
   arctab

   La funzione gestisce la stampa di un tabulato da archivio.
   Per la ricerca dei dati chiama la funzione arcfind, mentre
   per la stampa delle intestazioni dell'archivio chiama la 
   funzione arctabini.
   Il tabulato viene stampato a blocchi di n_misst misure alla volta.
   Alla fine delle operazioni viene chiamata la funzione arcread
   per forzare la chiusura del canale utilizzato per la ricerca
   dei dati.

   Parametri

   mess     S_TAB *     messaggio di richiesta tabulato

   Ritorno
   
   nessuno

   23 Marzo 1992     Rel 1.0  Fc
*/
   
#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messcada.inc"
#include "allar.inc"
#include "arc.inc"
#include "print.inc"
#include "arctab.inc"
#include "g1tipdb.inc"
#include "switch.inc"

extern char *arc_errore;
extern char stat_diz[];

// External function declarations
extern int arctabin(PARCDES*, short, short, short, short, void*);
extern int arcfind(S_STAB*, short*, long*, ARC_DBS**);
extern void decnum(char*, int, int, short, float);
extern short arcpar(ARC_DBS*, short);
extern void invia(int, void*);
extern int arcread(short, short*, ARC_DBS**, long*);

int arctab(S_STAB *mess)	 
{
PARCDES *arc;
long arpos;
short arfile;
short nSez, nMaxSez, posmis;
short pagina, ier;
ARC_DBS *archr;               
short ncamp;
short arj, stk, pd, pdsave;

arc=&arcdes[mess->archivio-1];  
if(arc->hea.iarc==-1)	return(0);  // archivio non installato  
/*
	caso di archivio esistente
   preparo l'header del tabulato
*/
pagina=0;
arctabin(arc,minit,pagina,0,0,(char*)0);		
/*
   trovato inizio dati da stampare procedo al ciclo di stampa
   calcolando quante sezione di stampa devo effettuare
*/
pd=0;
nMaxSez=(arc->hea.n_mis-1)/n_misst+1;
for(nSez=0;nSez<nMaxSez;nSez++)
{
/*
   ricerco il campione e memorizzo il file e l'offset iniziale
   per la stampa dei valori
*/                                                
   ier=arcfind(mess,&arfile,&arpos,&archr); 
   if(ier)                      // non esistono dati disponibili
   {
      arcerr.hea.lung=sizeof(arcerr);
      arcerr.hea.szvir=-1;
      strcpy(arcerr.errore, arc_errore);
      arctabin(arc,msigle,pagina,0,0,(char*)&arcerr);		
   	goto FINE_TAB;
   }
   pagina++;
   arctabin(arc,msigle,pagina,nSez*n_misst,n_misst,(char*)0);		
   pagina++;
   arctabin(arc,msigle,pagina,0,0,&rtag);		
/*
   inizio il ciclo di stampa per tanti campioni quanti sono quelli
   richiesti
   arj indice scorrimento descrittore archivio
   stk indice inserimento nel stringa di stampa
   pd indice di scorrimento nel record archiviato
*/
   ncamp=0;
   pdsave=pd;
	while(ncamp < mess->ncamp)
   {
   	memset(rval.date,' ',sizeof(RIGVAL)-sizeof(HEA_STA));
      rval.new=0x0D0A;
if  (INGLESE)
{
   	decnum(&rval.date[0],2,-1,archr->hea.mese,0.);
	   rval.date[2]='/';
   	decnum(&rval.date[3],2,-1,archr->hea.giorno,0.);
}
else
{
   	decnum(&rval.date[0],2,-1,archr->hea.giorno,0.);
	   rval.date[2]='/';
   	decnum(&rval.date[3],2,-1,archr->hea.mese,0.);
}
	   decnum(&rval.ore[0],2,-1,archr->hea.ore,0.);
   	rval.ore[2]=':';
	   decnum(&rval.ore[3],2,-1,archr->hea.minuti,0.);
   	rval.ore[5]=':';
	   decnum(&rval.ore[6],2,-1,archr->hea.secondi,0.);

   	for(arj=nSez*n_misst,stk=0,pd=pdsave;arj<(nSez+1)*n_misst;arj++,stk++)
		{
	   	if(arj == arc->hea.n_mis) break;        // fine scansione
/*
   se l'archivio e' normale, lento o veloce ad archiviazione totale
   la posizione nel descrittore  coincide con quella nel data base 
   altrimenti se l'archiviazione e' veloce e a memorizzazione
   parziale occorre ricercala
*/
         if(archr->hea.n_misvel && arc->hea.t_mem==M_Par) 
         {
            posmis=arcpar(archr,arj);
            if(posmis==-1) goto PROSS;             // non esiste
         }
         else posmis=pd;        

         if(archr->dbs[posmis].d.imis==-1) goto PROSS;

         switch(archr->dbs[posmis].d.dtipo)
         {
         case -1:                               // digitale
				decnum(&rval.valori[stk][1],5,-1,(archr->dbs[posmis].d.f_s & 0x0100)>>8,0.);
         break;
         case -2:                               // organo
				memcpy(&rval.valori[stk][3],&stat_diz[(archr->dbs[posmis].d.f_s & 0x00ff)*SCD_STATO],SCD_STATO);
         break;
         case -3:                               // stringa
				memcpy(&rval.valori[stk][1],(char *)& archr->dbs[posmis].d.f_s,
				min(strlen((char *)&archr->dbs[posmis].d.f_s),10));
         break;
         default:                               // analogico
				decnum(&rval.valori[stk][2],9,3,0,archr->dbs[posmis].a.camp.val);
         break;
			}
PROSS:
         if((arc->mis+arj)->ext==g1tipst) pd=pd+3;    // posizione in dbs arch.
         else pd=pd+1;
	  }
     ncamp++;			// decrementa il numero di campioni da leggere
	  invia(tpr_tabulato,&rval);
/*
   se esauriti i campioni disponibili interrompo ciclo
*/
     if(arcread(mess->archivio-1, &arfile, &archr, &arpos)) break;
/*
   verifico se fine pagina
*/
     if(!(ncamp % 60))      // salto pagina
     {
         pagina++;
         arctabin(arc,msigle,pagina,0,0,&rtag);		
     }
	}
}
FINE_TAB:
/*
   chiusura canale file utilizzato per la ricerca
   e form feed al tabulato
*/
arfile=-1;
arcread(mess->archivio-1, &arfile, &archr, &arpos);
arcontrol.val=0x0D0A;
invia(tpr_tabulato,&arcontrol);
arcontrol.val=0x0C00;
invia(tpr_tabulato,&arcontrol);
return(0);
}



 
