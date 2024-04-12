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
   allcomp

   Routine per il compattamento degli allarmi. Elimina gli allarmi
   con il puntatore a -1. Viene chiamata al termine del riconoscimento 
   singolo.
   
   Durante il compattamento aggiorna i puntatori pout, pinv, pin del data
   base allarmi e i puntatori pvis0, pvis1 di tutti i video che hanno 
   il data base allarmi in visualizzazione.


   Parametri

   alv      S_DBS_ALV *    puntatore tabella video allarmi


   Ritorno 

   0        se non e' stato effettuato nessun compattamento
   1        e' stato eliminato almeno un allarme

   23 Novembre 1992

*/

#include "messcada.inc"
#include "allar.inc"

allcomp(alv)
S_DBS_ALV *alv;
{
S_DBS_ALL *ald;
S_DBS_ALV *alc;
struct buff_all *all_o, *all_n;
int data;
short i, j;
short save_pout, save_pinv;    
short pvis0_save[max_video], pvis1_save[max_video];
short flagpin;

ald=&bDbsAll[alv->pal];
/*
   setto lock data base allarmi in uso
*/
rew(ald->mbox,0,&data);
all_o=ald->pall;        // puntatore primo allarme
all_n=all_o;            // puntatore nuova struttura
/*
   salvo valori attuali puntatori per confronto posizione nel
   buffer
*/
save_pout=ald->pout;
save_pinv=ald->pinv;

alc=&bDbsAlv[0];
for(j=0;j<num_video;j++,alc++)
{
   pvis0_save[j]=alc->pvis0;
   pvis1_save[j]=alc->pvis1;
}
/*
   ciclo ricerca posizioni da cancellare e ricalcolo puntatore 
   pin
*/
ald->pin=0;
flagpin=0;
for(i=0;i<save_pout;i++,all_o++)
{
   if(all_o->m.punt==-1)                  // elemento da eliminare
   {
//   printf("\n el %d ",i);
      if(ald->pout) ald->pout--;
      if(ald->pinv && save_pinv>i) ald->pinv--;
      alc=&bDbsAlv[0];
      for(j=0;j<num_video;j++,alc++)
      {
         if(alc->pal!=alv->pal) continue;
         if(alc->pvis0 && pvis0_save[j]>i) alc->pvis0--;
         if(alc->pvis1 && pvis1_save[j]>i) alc->pvis1--;
      }
   }
   else
   {
      if(all_o != all_n) (*all_n)=(*all_o);
      if(all_n->mask >=0) flagpin=1;         // non ancora riconosciuto
      if(!flagpin) ald->pin++;
      all_n++;
   }
}
// printf("\n allcomp pout %d pin %d pinv %d ",ald->pout,ald->pin,ald->pinv);
tra(ald->mbox,1);                         // libero mail box
return(0);
}
