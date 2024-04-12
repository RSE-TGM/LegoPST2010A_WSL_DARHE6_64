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
   Stamar.c

	La funzione stamar dato l'indice del data base allarmi ed una o
   piu' zone di impianto prepara i pacchetti per la stampa degli 
   allarmi del data base. E' possibile richiedere la stampa di tutti
   gli allarmi o solo di quelli riconosciuti.

	i messaggi MSTAR sono preceduti da un primo messaggio
	MINTAR con i dati per l'intestazione del tabulato
   
   L'elenco puo' essere inviato o sulle periferiche standard
   peri=0 oppure sulle periferiche remote peri != 0 (in tal caso
   indica la periferica su cui inviarlo)

   Il messaggio e' cosi' composto:

      word 1      = -2  argomento intero
      word 2      n. data base
      word 3      = -2  argomento intero
      word 4      = 0   stampa solo allarmi in archivio
                  = 1   stampa allarmi in archivio e da riconoscere
      word 5      = -2 argomento intero
      word 6      = 0 zona 0 non selezionata
                  = 1 zona 0 selezionata
      ---
      --
      word n      = -2  argomento intero
      word n+1    = 0 zona 31 non selezionata
                  = 1 zona 31 selezionata

   Parametri

     mess      short *     puntatore al messaggio

   Ritorno

      1        se i parametri del messaggio non sono corretti
               ( n. del data base non accettabile)
      0        se tutto ok

      5 Giugno 1992     Rel 1.0     Fc.
*/
#include <stdio.h>

#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "mesqueue.h"

struct stam_zone  {
                     short arg;
                     short zona;
                  };

struct stam_mess {
         short arg1;
         short dbs;
         short arg2;
         short flag;
struct stam_zone z[max_zone];
                  };

stamar(mess, peri)
struct stam_mess *mess;
short peri;                   /* n. gruppo periferiche su cui      */
                              /* indirizzare l'elenco              */
{
struct buff_all *all;
S_DBS_ALL *alp;
QUEUE_PACKET pack;
union	u_arc		{	S_STAR mess;
						S_INAR iniz;
					} u;
int ier;
short i;

pack.que = c_stamp;
pack.flg = MSG_WAIT;				/* messaggio per processo stampe */
pack.wto = 0;						/* wait infinita						*/
pack.amsg = (char *)  &u;
pack.lmsg=sizeof(S_STAR);

u.iniz.mess=minar;				 	/* messaggio inizializzazione    */
u.iniz.pagina=mess->dbs-1;			/* dati di pagina allarmi			*/
u.iniz.archivio=0;
enqueue(&pack);
/*
	preparo la maschera per estrarre gli allarmi associati
	alle zone abilitate
*/
u.mess.mess=mstar;
u.mess.al.m.punt=-1;
u.mess.al.m.ext=-1;
u.mess.flag=mstar_r;					
u.mess.peri=peri;


if(mess->dbs <1 || mess->dbs > max_dbsall) return(1);  //  n. data base non accettabile

alp=&bDbsAll[mess->dbs-1];
if(!alp->def) return(1);               // data base non definito

all=alp->pall;                         // inizio buffer allarmi
/*
	prendo in carico la pagina allarmi
*/
rew(alp->mbox,0,&ier) ;
for(i=0;i<alp->pout;i++,all++)
{
/*
	se flag=0 stampo solo allarmi in archivio
*/
 	   if(i>=alp->pinv && !mess->flag) break;
      if(!mess->flag && all->mask >= 0) continue;     // non in archivio
      if(all->m.punt==-1){ continue; } 					// annullato
/*
	invio il pacchetto con l'allarme selezionato
*/
		if(mess->z[all->mask & 0x7FFF].zona)
		{
			if(all->mask>=0) u.mess.flag=mstar_a;		   // all. da riconosc. 			*/
         else u.mess.flag=mstar_r;                    // gia' riconosciuto
		   u.mess.al=*all;
			enqueue(&pack);
		}
}
/*
	rilascio la pagina
*/
tra(alp->mbox,1);
/*
	se non e' stato trovato nessun allarme forzo
	l'intestazione con un messaggio fittizio
*/
if(u.mess.al.m.punt==-1) enqueue(&pack);
/*
	fine invio pacchetti
*/
u.mess.flag=mstar_f;	       /*	messaggio fine							*/
enqueue(&pack);
}
