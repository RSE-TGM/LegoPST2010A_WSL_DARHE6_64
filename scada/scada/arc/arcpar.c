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
   arcpar

   La routine dato un record ARC_DBS fornisce la posizione
   della misura di indice ind nel record fornito
   Se la misura non esiste ritorna -1.

   Parametri

   dbs   ARC_DBS*    puntatore al record da esaminare
   ind   short       indice nel descrittore dell'archivio
                     della misura da considerare

   Ritorna
   
   short posizione della misura nel data base
         oppure -1  se la misura non e' stata trovata


   26 Marzo 1992  Rel. 1.0    Fc
*/
#include <osf1.h>
#include "arc.inc"
arcpar(dbs,ind)
ARC_DBS *dbs;
short ind;
{
DATDBS *val;
short i;

val=&dbs->dbs[0];
for(i=0;i<dbs->hea.n_misvel;i++,val++)
{
   if(val->d.imis==ind) return(i);         // trovata
}
return(-1);                              // non trovata
}

