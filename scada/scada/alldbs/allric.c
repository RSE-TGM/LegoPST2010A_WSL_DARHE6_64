/**********************************************************************
*
*       C Source:               allric.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Mar 19 17:56:05 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allric.c-6 %  (%full_filespec: allric.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   rical.c

   La subroutine rical gestisce il riconoscimento  degli allarmi in base
   al tipo di trattamento e alle zone di impianto selezionate nella
   pagina allarmi indicata.

   Emissioni      2, 3, 5
                  vengono inserite in archivio
   Rientri        2, 5
                  vengono eliminate le corrispondenti emissioni gia'
                  archiviate

   Per ogni allarme trattato vengono aggiornati i contatori degli
   allarmi in archivio e degli allarmi da riconoscere.

   Parametri

   alv   S_DBS_ALV*     puntatore alla tabella allarmi relativa al
                        video che ha richiesto il riconoscimento

   Ritorno

   nessuno

   26 Maggio 1992    Rel. 1.0    Fc.

	21 Gennaio 1993
   Inserita gestione contatori allarmi in emissione e rientro
   per zona
   Inserita gestione contatori allarmi in emissione e rientro
   per livello di severita'

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

// External function declarations
extern int abzon(short *, short *, short, char *);
extern int rew(int, int, void *);
extern void allpvis(short, short, short);
extern int allinger(void *, void *, void *);
extern void gestri(int, int, int);
extern void allsev(void *, int, short);
extern void tra(int, int);


void rical(alv)
S_DBS_ALV *alv;               // tabella video allarmi 
{
short limite;                 // n. massimo allarmi da riconoscere
S_DBS_ALL *all;               // puntatore dbs allarmi da considerare
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
#include "diagnodi.inc"
QUEUE_PACKET queue;
S_TRATG     mtra;

all=&bDbsAll[alv->pal];                   // data base allarmi associato al video
#if defined GERARC
abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);  // ricerco zone e gerarchie abilitate
#else
abzon(&alv->mask1,&alv->mask2,alv->pal);  // ricerco zone abilitate
#endif
if(!abilzo.n_al) return;


if (SEGNALA_RIC_ALLARMI)
   {
	queue.que=c_digor;
	queue.wto=4;								// time out non infinito per evitare
	queue.flg=MSG_WAIT;					// blocchi in caso di riconoscimento automatico
	queue.amsg=(char*)&mtra;
	queue.lmsg=sizeof(mtra);
	mtra.ext=g1tipdd;
	mtra.stato=1;
	mtra.mess=macdd;
	mtra.indice=ricall+alv->pal;
   if ((!SYS_DUALE) || sys_master)
	   enqueue(&queue);
#ifdef DEBUGYES
printf("allric:ho spedito messsaggio di segnalaz. ric con enqueue\n");
#endif
   }


   if (SYS_DUALE && (!sys_master)) 
      limite=all->pout;		 // slave riconoscere tutto  
	else 
      limite=alv->nallco;   // master solo 16 da riconoscere   

flagpin=0;                                 // nessun allarme non riconosciuto
ind=all->pin;                              // indice scorrimento buffer
save_pinv=all->pinv;                       // salvo indice all. archiviato piu' recente
all->pinv=all->pin;                        // indice inserimento in archivio
#ifdef DEBUGYES
printf("allric:all->pinv=%d\n",all->pinv);
#endif
all_pin=all->pall+ind;                     /* indir.inserimento archivio 		*/
all_ex=all_pin;                     		 /* indirizzo allarme da esaminare	*/

u=rew(all->mbox,0, &data );
npout=all->pout;
#ifdef DEBUGYES
printf("allric:all->pout=%d\n",all->pout);
#endif
allpvis(alv->pal,0,0);				// inizializzazione puntatori
for (u=0;u<limite  && ind < npout; all_ex++,ind++)
{
#ifdef DEBUGYES
printf("all_ex->m.punt=%d all_ex->m.ext=%d all_ex->m.ertr=%x\n",all_ex->m.punt,all_ex->m.ext,all_ex->m.ertr);
#endif
/*
   verifico che l'allarme abbia la zona di impianto corrispondente
   a quella selezionata e che sia ancora da riconoscere  (mask>0)
   in tal caso li ricopio senza trattarli
*/
#ifndef GERARC
   if(all_ex->mask <0 || !abilzo.abil_zone[all_ex->mask])
#else
   if(all_ex->mask <0 || !abilzo.abil_zone[all_ex->mask] || !allinger(&all_ex->m,alv,NULL))
#endif
   {
      (*all_pin)=(*all_ex);
      if(all_ex->mask >=0) flagpin=1;     // allarme ancora da riconoscere
                                          // non incrementare il contatore
                                          // punti archiviati
      else if(!flagpin) all->pin++;       // incremento punt. allarmi in archivio
      all_pin++;
      all->pinv++;
      continue;
   }
   u++;                                   // punto archiviabile
/*
   allarme da riconoscere: 	reset bit RI
*/
#ifdef DEBUGYES
printf("allric: OK to ri ext=%d punt=%d\n",all_ex->m.ext,all_ex->m.punt);
#endif
   gestri(all_ex->m.ext,all_ex->m.punt,0);
   zona=all_ex->mask;                     // zona associata
/*
   verifico il tipo di trattamento e se si tratta di emissione o rientro
   emissioni 2 3 5 8 inserimento in archivio
*/
   if(all_ex->m.ertr & 0x80 )
   {
#ifdef DEBUGYES
printf("allric: allarme e' in emissione\n");
#endif
      dbadv[allemdb1+alv->pal*2]--;      // elimino emissione
      trat= (all_ex->m.ertr & M_TRALL) ;
      if(trat  == 2  || trat == 3 || trat == 5 || trat == 8)
          {
          (*all_pin)=(*all_ex); /* tecnica per cancellare eventuale rientro */
          all_pin->mask=all_pin->mask+0x8000;  // allarme riconosciuto
          if(!flagpin) all->pin++;
          all->pinv++;
          all_pin++;
#ifdef DEBUGYES
printf("allric: allarme e' in emissione all_pin=%d all->pinv=%d\n",all->pin,all->pinv);
#endif
          *(all->db_ar)=*(all->db_ar)+1;     // incremento cont. globale
          bDbsAlu[zona].n_ar[alv->pal]++;    // incremento cont. zona
#ifdef DEBUGYES
/*
Debug
*/
printf("*******************DEBUG dopo if  ***********************\n");
         for(all_conf=all->pall,j=0;j< all->pout;j++, all_conf++)
		{
printf("j=%d\n",j);
printf("all_conf->m.punt=%d all_conf->m.ext=%d all_conf->m.ertr=%x all_conf->secondi=%d\n",all_conf->m.punt,all_conf->m.ext,all_conf->m.ertr,all_conf->secondi);
		}
printf("*******************DEBUG***********************\n");
printf("allric: allarme e' in emissione incrementati contatori\n");
#endif
          if (CONT_ALL_ZONE)
            {
#ifdef DEBUGYES
printf("allric:CONT_ALL_ZONE\n");
#endif
            punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
            dbadv[punt]++;
  	         lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
            nallsev = ++bDbsAlu[zona].n_arsev[lsev][alv->pal];// incr. all. del livello
            allsev (&dbadf[punt],nallsev,lsev);
            }
         }
   }
/*
        rientro  2 5 ricerca emissione
*/
   else
   {
#ifdef DEBUGYES
printf("allric:allarme in rientro\n");
#endif
      allpvis(alv->pal,ind,1);
      dbadv[allridb1+alv->pal*2]--;      // elimino rientro
      if((all_ex->m.ertr & M_TRALL)== 5 || (all_ex->m.ertr & M_TRALL)== 2)
      {
         for(all_conf=all->pall,j=0;j< all->pinv;j++, all_conf++)
         {
            if(all_conf->m.punt  == all_ex->m.punt &&
              ((all_conf->m.satt & 0x7F)  ==  all_ex->m.sprec ) &&
              (all_conf->m.ext  == all_ex->m.ext ))
               {
#ifdef DEBUGYES
printf("creco emiss: all->pinv=%d\n",all->pinv);
#endif
/*                      
        trovata emissione cancello l'elemento dagli
        archivi
*/
                all_conf->m.punt = -1 ;
                *(all->db_ar)=*(all->db_ar)-1;               // decremento cont. globale
                bDbsAlu[zona].n_ar[alv->pal]--;    // decremento cont. zona   
#ifdef DEBUGYES
printf("allric:decremento contatori zone\n");
#endif
                if (CONT_ALL_ZONE)
                  {
#ifdef DEBUGYES
printf("allric:CONT_ALL_ZONE\n");
#endif
                  punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
                  dbadv[punt]--;
  	               lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
                  nallsev = --bDbsAlu[zona].n_arsev[lsev][alv->pal];// dec. all. del livello
                  allsev (&dbadf[punt],nallsev,lsev);
                  }
                break;
               }
         }   /* end for */
     }
   }    /* end else all in rientro */


   *(all->db_al)=*(all->db_al)-1;                              // decremento cont. globale
   bDbsAlu[zona].n_al[alv->pal]--;                             // decremento cont. zona
   if (CONT_ALL_ZONE)
      {
#ifdef DEBUGYES
printf("allric:CONT_ALL_ZONE FINALE !!!\n");
#endif
      punt=first_cont_all+(max_zone*alv->pal+zona)*2;
      dbadv[punt]--;
      lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
      nallsev = --bDbsAlu[zona].n_alsev[lsev][alv->pal];  // dec. all. del livello
      allsev (&dbadf[punt],nallsev,lsev);
      }
}  /* end for */
/*
        compatto buffer archivio se il buffer allarmi e'
        quasi completo
*/
if(all->pout >= (all->dim)*80/100)
{
#ifdef DEBUGYES
printf("COMPATTO BUFFER ARCHIVIO\n");
#endif
   allpvis(alv->pal,0,0);
   all_ex= all->pall;
   data=all->pin;
   datav=all->pinv;
   for(j=0,all_conf=all->pall;j<all->pinv;j++,all_conf++)
   {
      if(all_conf->m.punt != -1 )
      {
			if(all_ex != all_conf) (*all_ex)=(*all_conf);
         all_ex++;
      }
      else 
      {
         if(j<all->pin) data -- ;        /* posto vuoto */
         datav--;
         allpvis(alv->pal,j,1);
      }
   }
   all->pin=data ;   /* nuovo puntatore */
   all->pinv=datav;
}
/*
        compatto buffer allarmi riconosciuti
*/
#ifdef DEBUGYES
printf("allric: ind=%d prima compatto buffer allarmi ri all->pinv=%d\n",ind,all->pinv);
#endif
all_ex= all->pall + all->pinv;
for (j=ind,all_conf= all->pall+j; j < all->pout;j++, all_conf++)
{
#ifdef DEBUGYES
printf("Compatto buffer\n");
#endif
    (*all_ex)=(*all_conf);
    all_ex++ ;
}
#ifdef DEBUGYES
printf("allric:all->pout prima =%d ind=%d\n",all->pout,ind);
#endif
all->pout=all->pinv+(all->pout-ind);
#ifdef DEBUGYES
printf("allric:all->pout dopo =%d",all->pout);
#endif
alv->pvis0=all->pin;
#ifdef DEBUGYES
printf("allric: all->pout=%d alv->pvis0=%d =all->pin\n",all->pout,all->pin);
#endif
if(save_pinv > all->pinv) save_pinv=all->pinv+(save_pinv-ind);
all->pinv=max(all->pinv,save_pinv);
#ifdef DEBUGYES
printf("allric: all->pinv=%d\n",all->pinv);
#endif
tra(all->mbox,1);
#ifdef DEBUGYES
/*
Debug
*/
printf("*******************DEBUG***********************\n");
         for(all_conf=all->pall,j=0;j< all->pout;j++, all_conf++)
		{
printf("j=%d\n",j);
printf("all_conf->m.punt=%d all_conf->m.ext=%d all_conf->m.ertr=%x all_conf->secondi=%d\n",all_conf->m.punt,all_conf->m.ext,all_conf->m.ertr,all_conf->secondi);
		}
printf("*******************DEBUG***********************\n");
#endif
if (SEGNALA_RIC_ALLARMI)
   {
#ifdef DEBUGYES
printf("allric:SEGNALA_RIC_ALLARMI !!!\n");
#endif
	if((*all->db_al)==0)
	   {
		mtra.indice=noall+alv->pal;
      if ((!SYS_DUALE) || sys_master)
		   enqueue(&queue);
	   }
   }

return;
}
