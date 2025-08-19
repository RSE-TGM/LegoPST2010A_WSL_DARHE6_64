/**********************************************************************
*
*	C Source:		ricPreviousAll.c
*	Instance:		1
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Fri May 28 15:52:40 1999 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ricPreviousAll.c-4 %  (%full_filespec: ricPreviousAll.c-4:csrc:1 %)";
#endif

/* 
 The routine ricPreviousAll performs the acknowledgment of the 
 previous alarm of a specified point. 
 
 Parameters: 
           S_DBS_ALV *alv;  info alarms x video
           S_MALLA point ; new emission
 Return :
           1 if OK
           0 if KO

*/


#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"
#include "diagnoan.inc"
#include "diagnodi.inc"

// External function declarations
extern int rew(int, int, int*);
extern int tra(int, int);
extern int allpvis(short, short, short);
extern int gestri(short, short, short);
extern int allsev(short*, short, short);


int ricPreviousAll(S_DBS_ALV *alv,S_MALLA point)
{
S_DBS_ALL *all;               // puntatore dbs allarmi da considerare
                              // dal meno recente
QUEUE_PACKET queue;
S_TRATG     mtra;
short punt;                   // punt. dbs diagno contatori
short ind;                    // indice allarme in esame a partire
                              // dal meno recente
int data;
short datav;            // per appoggio
short trat;                   // tipo di trattamento
short npout;                  // n. massimo allarmi in data base
struct buff_all *all_ex, *all_conf, *all_pin;
short u, j, lsev, nallsev;
short flagpin;
short save_pinv;              // salvo indice allarme archiviato piu' recente
                              // memorizzato in all->pinv
short zona;
short compact_over=0;           /* Mi segnala se ho trovato allarme */
short ack_set=0;             /* Indica se il riconoscimento e' avvenuto */




all=&bDbsAll[alv->pal];         // alarms db related to the video

if (SEGNALA_RIC_ALLARMI)
   {
        queue.que=c_digor;
        queue.wto=4;
// time out non infinito per evitare
        queue.flg=MSG_WAIT;      // blocchi in caso di riconoscimento automatico
        queue.amsg=(char*)&mtra;
        queue.lmsg=sizeof(mtra);
        mtra.ext=g1tipdd;
        mtra.stato=1;
        mtra.mess=macdd;
        mtra.indice=ricall+alv->pal;
   if ((!SYS_DUALE) || sys_master)
           enqueue(&queue);
   }

 flagpin=0;                                 // nessun allarme non riconosciuto




/*
N.B. all->pin e' un puntatore ad un elemento della tabella allarmi.
Prima di questo elemento ho solo allarmi riconosciuti
*/

ind=all->pin;               // indice scorrimento buffer
save_pinv=all->pinv;        // salvo indice all. archiviato piu' recente
all->pinv=all->pin;         // indice inserimento in archivio

/*
all_pin e all_ex sono puntatori per lo
scorrimento della tabella
*/

all_pin=all->pall+ind;                     /* indir.inserimento archivio */
all_ex=all_pin;                            /* indirizzo allarme da esaminare */

u=rew(all->mbox,0, &data );
npout=all->pout;


/*
        Routine per allineamento indicatori pvis0 e pvis1 per scroll archivio
        o pagina allrmi. Viene chiamata in caso di riconoscimento a pagine e
        lo stesso data base e' visualizzato su altri video.
*/
allpvis(alv->pal,0,0);                          // inizializzazione puntatori

#ifdef DEBUGYES
        for(all_conf=all->pall,j=0;(j< all->pout) ;j++, all_conf++)
           {

           printf("##################PRIMA###########################\n");
           printf("[%d]all_conf..punt=%d all_conf..ext=%d all_conf..satt=%d\n",
                  j,all_conf->m.punt,all_conf->m.ext,(all_conf->m.satt & 0x7F));
           printf("##################################################\n");
           }
#endif

for ( ; ind < npout && !compact_over ; all_ex++,ind++)
{

   /*
     Find the allarm related to the same point
   */
  if( (all_ex->m.punt != point.punt) )  
     {
     (*all_pin)=(*all_ex);               // clear the possible reentry
     if(all_ex->mask >=0) flagpin=1;     // allarme ancora da riconoscere
                                         // non incrementare il contatore
                                         // punti archiviati
     else if(!flagpin) all->pin++;       // incremento punt. allarmi in arc.
     all_pin++;
     all->pinv++;
     continue;

     }  /* end if alarm doesn't match */

/*
NB.
   In caso di rientro settare compact_ver=1;
*/
   gestri(all_ex->m.ext,all_ex->m.punt,0);
   zona=all_ex->mask;                     // zona associata


/*
   verifico il tipo di trattamento e se si tratta di emissione o rientro
   emissioni 2 3 5 8 inserimento in archivio
*/
   if(all_ex->m.ertr & 0x80  && !(all_ex->mask & 0x8000))
      {
      dbadv[allemdb1+alv->pal*2]--;      // elimino emissione
      trat= (all_ex->m.ertr & M_TRALL) ;
      if(trat  == 2  || trat == 3 || trat == 5 || trat == 8 || trat == 6)
         {
         (*all_pin)=(*all_ex); /* tecnica per cancellare eventuale rientro */
         all_pin->mask=all_pin->mask+0x8000;  // allarme riconosciuto
         if(!flagpin) all->pin++;
         all->pinv++;
         all_pin++;
         ack_set=1;               /* alarm in emission state found */
         *(all->db_ar)=*(all->db_ar)+1;     // incremento cont. globale
         bDbsAlu[zona].n_ar[alv->pal]++;    // incremento cont. zona


         if (CONT_ALL_ZONE)
            {
            punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
            dbadv[punt]++;
            lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
            nallsev = ++bDbsAlu[zona].n_arsev[lsev][alv->pal];
            allsev (&dbadf[punt],nallsev,lsev);
            }

         }  /* end if trat */
 
      }  /* end if emission */
   /*
      Allarme gia' archiviato: incremento pinv
   */
   else if(all_ex->m.ertr & 0x80  && (all_ex->mask & 0x8000))
      {
      (*all_pin)=(*all_ex); /* way to cancel the possible reentry */
      if(!flagpin) all->pin++;
      all_pin++;
      all->pinv++;  // increase the last archived alarm pointer value 
      }

/*
        rientro  2 5 ricerca emissione
Quando ho un rientro devo andare a ritrovare il corrispondente
all in emissione. Pertanto devo rianalizzare la tabella allarmi
all' indietro partendo dall' allarme in rientro da riconoscere
*/

   else  // if it's a reentry
     {
     allpvis(alv->pal,ind,1);
     if((all_ex->m.ertr & M_TRALL)== 5 || (all_ex->m.ertr & M_TRALL)== 2)
        {

        /*
        Looking for related archived alarm.
        (Same punt but flag archived set)
        */

        for(all_conf=all->pall,j=0;(j< all->pout) && 
              ( !compact_over);j++, all_conf++)
           {
#ifdef PROVA
           printf("--------------------------------------------------\n");
           printf("[%d]all_conf..punt=%d all_conf..ext=%d all_conf..satt=%d\n",
                  j,all_conf->m.punt,all_conf->m.ext,(all_conf->m.satt & 0x7F));
           printf("[%d] all_ex..punt=%d all_ex..ex=%d all_ex..sprec=%d\n",
                   j,all_ex->m.punt,all_ex->m.ext,all_ex->m.sprec );
           printf("--------------------------------------------------\n");
#endif
           if(all_conf->m.punt  == all_ex->m.punt &&
              ((all_conf->m.satt & 0x7F)  ==  all_ex->m.sprec ) &&
              (all_conf->m.ext  == all_ex->m.ext ))
               {
               all_conf->m.punt = -1 ;
               *(all->db_ar)=*(all->db_ar)-1; // decremento cont. globale
               bDbsAlu[zona].n_ar[alv->pal]--;    // decremento cont. zona
               if (CONT_ALL_ZONE)
                  {
                  punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
                  dbadv[punt]--;
                       lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
                  nallsev = --bDbsAlu[zona].n_arsev[lsev][alv->pal];
                  allsev (&dbadf[punt],nallsev,lsev);
                  }

#ifdef DEBUGYES                       
                printf("\n\nATTENZIONE emissione found posiz.=%d\n\n",j);
#endif

               compact_over=1; /* reentry alarm found */
               break;
               }
            }   /* end for */

        }  /* end trattam. */
   /*
   Check if the reentry alarm was found together with the related emission
   */
   if( compact_over )       // if reentry  found
      dbadv[allridb1+alv->pal*2]--;      // cancel reentry
   else
      {
      printf("WARNING: Reentry without related emission x  punt=%d n db=%d\n",
             point.punt,alv->pal);
      printf("WARNING: Type pint ext =%d \n",(short)point.ext);
      }

   }    /* end else all in rientro */

   if ( compact_over || ack_set)
      {
      *(all->db_al)=*(all->db_al)-1;  // decremento cont. globale

#ifdef DEBUGYES
      printf("DEBUG: zona =%d \n",zona);
#endif

      bDbsAlu[zona].n_al[alv->pal]--; // decremento cont. zona
  
      if (CONT_ALL_ZONE)
         {
         punt=first_cont_all+(max_zone*alv->pal+zona)*2;
         dbadv[punt]--;
         lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
         nallsev = --bDbsAlu[zona].n_alsev[lsev][alv->pal];  
         allsev (&dbadf[punt],nallsev,lsev);
         }
       }    /* end if compact_over */

}  /* end for */


#ifdef DEBUGYES
        for(all_conf=all->pall,j=0;(j< all->pout) ;j++, all_conf++)
           {
           printf("--------------------------------------------------\n");
           printf("[%d]all_conf..punt=%d all_conf..ext=%d all_conf..satt=%d\n",
                  j,all_conf->m.punt,all_conf->m.ext,(all_conf->m.satt & 0x7F));
           printf("--------------------------------------------------\n");
           }
#endif


/*
        compatto buffer allarmi riconosciuti
*/
all_ex= all->pall + all->pinv;

for (j=ind,all_conf= all->pall+j; j < all->pout;j++, all_conf++)
   {
   (*all_ex)=(*all_conf);
   all_ex++ ;
   }
all->pout=all->pinv+(all->pout-ind);

alv->pvis0=all->pin;
if(save_pinv > all->pinv) save_pinv=all->pinv+(save_pinv-ind);
all->pinv=max(all->pinv,save_pinv);


tra(all->mbox,1);
if (SEGNALA_RIC_ALLARMI)
   {
        if((*all->db_al)==0)
           {
                mtra.indice=noall+alv->pal;
      if ((!SYS_DUALE) || sys_master)
                   enqueue(&queue);
           }
   }

      
 return 1;
}
