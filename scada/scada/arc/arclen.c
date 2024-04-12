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
   arclen

   Il modulo arclen provvede a verificare la frequenza lenta degli archivi.
   Se la frequenza e' scattata, per le misure analogiche verifica la FA
   confrontando i contatori di errore. Aggiorna la tabella dei time out
   per la memorizzazione su disco.

   Parametri

   freq  long     frequenza da verificare in secondi

   13 Marzo 1992  Rel. 1.0 Fc
*/
#include <osf1.h>
#include "arc.inc"
#include "g1tipdb.inc"

arclen(freq)
long freq;
{
short nmis, narc;
PUNTDBS *point;
ARC_DBS *dbs;
PARCDES *arc;

for(narc=0,arc=&arcdes[0];narc<n_arc;narc++,arc++)
{
   if(freq!=arc->hea.freqL) continue;             // frequenza diversa
#if defined (DEBUG)
      printf(" arch. lenta");
#endif
   point=arc->mis;
   dbs=arcdbsL[narc];
   for(nmis=0;nmis<arc->hea.n_mis;nmis++,point++)
   {
      switch(point->ext)
      {
      case g1tipaa:
      case g1tipas:
      case g1tipac:
      case g1tipad:
         if(dbs->dbs[nmis].a.ave.cfsfa > dbs->dbs[nmis].a.ave.ctot*coefm_fa)
            dbs->dbs[nmis].a.ave.ctot=0x50;     // 0x50 FA + 0x10 ST archivio lento
         else
            dbs->dbs[nmis].a.ave.ctot=0x10;     // 0x10 ST archivio lento
      break;
      }
   }
   t_L[narc].tco=t_L[narc].tin;                 // setto timer
}
return(0);
}
