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
   resetlbg
      La routine esegue il reset delle variabili legate alla gestione del
      libro giornale. Viene chiamata alla mezzanotte per la chiusura
      dei file del libro giornale.

   Parametri
      nessuno

   Ritorno
      nessuno

*/
#include <osf1.h>
#include <stdio.h>

#include "defpub.h"
#include "print.inc"
#include "virtinv.h"

void resetlbg(void)
{
   short i;
   S_PVIRT * pVirt;

   if(LbgFp!=NULL) fclose(LbgFp);      // no! chiudo il file attualmente in uso�

   pVirt=&virtprn[0];
   for(i=0;i<n_virt_lbg+n_virt_tab;i++,pVirt++)
   {
      pVirt->page_a=0;     // reset n. di pagine
      pVirt->righe_a=0;    // reset n. di righe
      pVirt->ByteOcc=0;    // inizializzazione offset file
   }

}
