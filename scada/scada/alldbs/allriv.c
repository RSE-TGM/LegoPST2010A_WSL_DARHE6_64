/**********************************************************************
*
*       C Source:               allriv.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jul 25 17:44:11 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allriv.c-4 %  (%full_filespec: allriv.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*

   allriv

   Routine per la rivisualizzazione di una pagina allarmi dopo
   uno o piu' riconoscimenti singoli.
   Data la tabella video alv in uso vengono decrementati pvis0
   e pvis1 di 16 allarmi. Se gli allarmi sono < 16 viene richiesta
   la rivisualizzazione della pagina allarmi.
   La routine deve essere chiamata solo se effettivamente e' stato
   effettuato almeno un riconoscimento singolo.

   Parametri

   alv   S_DBS_ALV*     puntatore alla tabella video
   nvideo   short       n. del video

   Ritorno

   nessuno

   24 Novembre 1992    Fc

*/
#include <stdio.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "comunic.inc"
#include "g1tipdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "mesqueue.h"

allriv(alv,nvideo)
S_DBS_ALV *alv;
{
S_DBS_ALL *ald;
struct buff_all *all, *alp;
short iall;
#include "diagnodi.inc"
QUEUE_PACKET queue;
S_TRATG     mtra;

ald=&bDbsAll[alv->pal];

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
	if((*ald->db_al)==0)
	   {
		mtra.indice=noall+alv->pal;
      if ((!SYS_DUALE) || sys_master)	
         enqueue(&queue);
	   }
   }

all=ald->pall+alv->pvis0-1;
alp=ald->pall+ald->pin;
#if defined GERARC
abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#else
abzon(&alv->mask1,&alv->mask2,alv->pal);
#endif
/*
   Verifico che ci siano almeno 16 allarmi meno recenti da visualizzare
   sono considerati validi gli allarmi in emissione, della zona voluta
   e definiti (punt!=-1)
*/
//printf("\n riv pvis0 %d pvis1 %d ind_all %d ",alv->pvis0,alv->pvis1,alv->ind_all);

for(iall=16;iall>0;all--)        // posiziono primo limite della finestra
{
    if(all <= alp) break;
    if(all->mask >=0 && abilzo.abil_zone[all->mask] && all->m.punt!=-1) 
#ifdef GERARC
    if(allinger(&all->m,alv,NULL))
#endif
      iall--;
   alv->pvis0--;
}
//printf("\n dopo riv pvis0 %d pvis1 %d ind_all %d ",alv->pvis0,alv->pvis1,alv->ind_all);
/*
   se il numero di allarmi e' < 16 richiedo la visualizzazione della pagina allarmi
   altrimenti la ripresento 
*/
if(iall)             // meno di 16 allarmi disponibili
{
    alv->pvis0=ald->pin ;
    ald->video=nvideo;                        // video associato alla pagina
    dec (1,16,ald,alv) ;      // rivisualizzo pagina allarmi
}
else                 // aggiorno pagina inserendo allarmi meno recenti (dall'alto)
{
   alv->ind_sav=0;
   if(alv->movi==-1) alv->ind_all=alv->ind_all+8;
   alv->movi=1;
   ald->video=nvideo;                        // video associato alla pagina
   alv->pvis1=alv->pvis0;                    // valore provvisorio
   dec (4,16,ald,alv) ;
   alv->ind_sav=8;
/*
   riposiziono il secondo limite della finestra 16 allarmi prima pvis0
*/
   all=ald->pall+alv->pvis0-1;
   alv->pvis1=alv->pvis0;
   for(iall=17;iall>0;all--)
   {
       if(all->mask >=0 && abilzo.abil_zone[all->mask] && all->m.punt!=-1)
#ifdef GERARC
       if(allinger(&all->m,alv,NULL))
#endif
         iall--;
       alv->pvis1--;
   }
   //printf("\n dec pvis0 %d pvis1 %d ind_all %d ",alv->pvis0,alv->pvis1,alv->ind_all);
}
return(0);
}





