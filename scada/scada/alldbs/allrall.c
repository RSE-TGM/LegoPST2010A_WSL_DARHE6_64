/**********************************************************************
*
*       C Source:               allrall.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 15:35:46 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allrall.c-3 %  (%full_filespec: allrall.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   rall.c

   La funzione esegue la gestione del messaggio $RALL
   viene attivato da scgev 
   Parametri

   codice             codice della funzione da eseguire
                      0 = modalita' di riconoscimento
                      1 = riconoscimento allarmi
                      0 = modalita' di congelamento

   operazione         operazione da svolgere in funzione di codice
                      se codice == 0
                             operazione == 0 ==>riconoscimento  a 16 
                             operazione == 1 ==>riconoscimento  singolo 
                      se codice == 1
                             operazione == 0 ==>riconoscimento 16 allarmi
                             operazione >1 <16 ==>ricon. singolo 
                      se codice == 2
                             operazione == 0 ==>pagina allarmi congelata
                             operazione == 1 ==>pagina allarmi aggiornabile

   numvideo           numero del video che ha inviato la send

   
   Ritorno

   nessuno

   18 Novembre 1992         M.Z.


*/
#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "allar.inc"

#if defined OSF1 || defined LINUX
extern short mbox_scgev;
#endif

// External function declarations
extern int abzon(short *, short *, short, char *);
extern int ricsi(short, void *);
extern int rew(int, int, int*);
extern int tra(int, int);

int rall (codice,operazione,numvideo)
short codice,operazione,numvideo;
{
S_DBS_ALV *alv;
S_DBS_ALL *all;        /* puntatore al data allarmi                    */

S_MCVAL mcval; 
QUEUE_PACKET queue;
short ind;
int i; 

alv=&bDbsAlv[numvideo];                     // tabella dbs all. per video
all=&bDbsAll[alv->pal];                     // data base allarmi

switch (codice)
   {

/*
   tipo di riconoscimento
   se riconoscimento singolo inizializza la tabella per gli svincoli
   allrmi pagina e buffer
   se riconoscimento a 16 procedo al compattamento degli allarmi fino
   ad ora riconosciuti singolarmente ed alla rivisualizzazione della pagina
*/
   case 0:     
      if (RIC_SI)
         {
         if(operazione) 
            for(i=0;i<nall_vi;i++) 
               alv->svi[i]=i+1;
         else  
            {
            queue.que = c_cval;
            queue.flg = MSG_WAIT;
            queue.wto = 0;
            queue.amsg=(char*)&mcval;
            queue.lmsg=sizeof(S_MCVAL);
            mcval.video=numvideo;
            mcval.direz=0;
            mcval.zona=zonai;
            if(alv->ricsi==RICSI_EF) 
               {
           	   mcval.indice=mriv;            // rivisualizzazione pagina d'archivio
           	   enqueue( &queue);               // dopo riconoscimento
               }
            }
         alv->ricsi=operazione;   
         }
      break;
/*
   operazione di riconoscimento
*/
   case 1:
      if (RIC_SI)
         {
         if (operazione>nall_vi || operazione<0) 
            break;     // num. allarme non corretto 
         if (!operazione  && (alv->ricsi) 
               || (operazione  && (!alv->ricsi))) 
            break;     // incongruenza
         if (alv->ricsi)                               // ricon. singolo   
            {                         
#ifndef GERARC
            abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
            abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
            alv->ricsi=RICSI_EF;
            ricsi (operazione,alv);
            }
         queue.que = c_cval;
         queue.flg = MSG_WAIT;
         queue.wto = 0;
         queue.amsg=(char*)&mcval;
         queue.lmsg=sizeof(S_MCVAL);
 	      mcval.video=numvideo;
  	      mcval.direz=0;
  	      mcval.zona=zonai;
  	      mcval.indice=mria;                              // richiedo riconoscimento
  	      enqueue( &queue);
#if defined OSF1 || defined LINUX
	      rew(mbox_scgev,0,&i); // attende che cval termini le operazioni
#endif
         }
      break;
/*
   congelamento on off    alv->full=0 pagina allarmi congelata
*/
   case 2:
      if(operazione==1)                 // congelamento off
         {                                 // se non sono in riconoscimento singolo
         alv->nallco=nall_vi;        // ripristino n. allarmi da riconoscere
         if(tstv[numvideo].tsv[zonai].v_tipo != p_al || alv->ricsi==RICSI_EF) break;
         alv->ricsi=0;
         alv->pvis0=all->pin ;
         all->video=numvideo;
         alv->full=operazione;
         queue.que = c_cval;
         queue.flg = MSG_WAIT;
         queue.wto = 0;
         queue.amsg=(char*)&mcval;
         queue.lmsg=sizeof(S_MCVAL);
       	mcval.video=numvideo;
        	mcval.direz=0;
        	mcval.zona=zonai;
        	mcval.indice=mall;               // richiedo rivisualizzazione
         rew(all->mbox,0,&i) ;
         all->fchanga=1;
         tra(all->mbox,1);
        	enqueue( &queue);
         }
      else                             // congelamento on
         {
         alv->full=operazione;             // setto flag pagina completa
#ifndef GERARC
         abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
         abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
         alv->nallco=min(abilzo.n_al,nall_vi);   // salvo quanti allarmi congelati
         }
      break;
   }

}

