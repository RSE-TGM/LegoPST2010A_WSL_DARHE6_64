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
   alllast.c
      routine che gestisce l'invio della stringa contenente l'ultimo
      allarme
      Mantiene in memoria l'ultimo pacchetto allarmi esaminato e la
      stringa relativa. Solo se il pacchetto e' variato procede alla
      decodifica del nuovo allarme

      La routine viene chiamata da gdac con periodicita' pari ad ogni
      invio dell'ora

      Parametri
         char*  buffer di caratteri in cui inserire le stringhe degli
                allarmi

      Ritorno
         short n. di byte che compongono il buffer

*/
#include <stdio.h>
#include <stdlib.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include <string.h>
#include "tipal.inc"
#include "mesqueue.h"
#include "diagnoan.inc"
#include "mesprocv.inc"

// External function declarations
extern int allcod(short, void *, void *);

S_STRALL  LStrAll[max_dbsall];         // stringa ultimi allarmi
struct buff_all LDatAll[max_dbsall];   // dati ultimi allarmi

int alllast (char* mess)
{
   short i,j;
   S_DBS_ALL *all;
   struct buff_all plast;
   char *p1, *p2;
   S_STRALL *str;
   short ptipo, pdata;        // tipo e puntatore misura associata all'allarme
   long tot;

   all=&bDbsAll[0];
   for(i=0;i<max_dbsall;i++,all++)
   {
      str= &LStrAll[i] ;
      if(all->def && (all->pin < all->pout))         // data base definito o nessun allarme da riconoscere
      {
//
//    ricerca ultimo allarme non ancora riconosciuto
//
         j=0;
         do
         {
            j++;
            plast=*(all->pall+all->pout-j);
         }
         while(plast.mask<0);
//
//    verifico eventuale variazione dell'allarme confrontando i due
//    pacchetti byte a byte
//
         p1=(char*) &plast;
         p2=(char*) &LDatAll[i];
         for(j=0;j<sizeof(struct buff_all);j++,p1++,p2++) if(*p1!=*p2) break;
         if(j<sizeof(struct buff_all))      // variato allarme
         {
//
//    il pacchetto risulta differente: procedo all' aggiornamento e alla
//    decodifica
//
            LDatAll[i]=plast;
            allcod(1, str, &LDatAll[i]);
         }
      }
      else           // data base non definito (buffer a 0)
      {
         memset(str,0,sizeof(S_STRALL));
         memset(str->data,' ',sizeof(str->data));
         memset(str->desc,' ',sizeof(str->desc));
      }
      memcpy(mess+i*sizeof(S_STRALL),str,sizeof(S_STRALL));
   }
   return (sizeof(S_STRALL)*max_dbsall);
}
