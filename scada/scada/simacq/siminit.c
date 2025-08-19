/**********************************************************************
*
*       C Source:               siminit.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Oct 15 15:16:50 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: siminit.c-3 %  (%full_filespec: siminit.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* 
      SIMINIT.C
      Inizializzazione dei task nel caso di supervisione di un 
      simulatore    (ENEL PC)

      10.09.92  -  Rev.1.00  -  GM.Furlan

      27 Marzo 1995 Fc Porting a 32bit
*/

#include "taskwd.inc"
#include "simdia.inc"
#include "simana.inc"
#include "g2comdb.inc"

// External function declarations
extern void bitset(short *, short, short);

int siminit()
{

short i;

#if defined (AC_SIM_ENEL)
   for (i=0;i<n_task;i++)
   {
      wd[i].task_per=TNONPERIODICO;   // tutti i task non periodici 
      wd[i].task_st=TSTOP;            // tutti i task in stop
   }
#endif

   // inizializzazione digitali diagnostica legati a supervisione simulatore
   bitset(&dbdd[sscsimon],g2di_sl,1);
   bitset(&dbdd[sscstop],g2di_sl,0);
   bitset(&dbdd[sscwait],g2di_sl,1);
   bitset(&dbdd[sscready],g2di_sl,1);
   bitset(&dbdd[sscrun],g2di_sl,1);
   bitset(&dbdd[sscfreeze],g2di_sl,1);
   bitset(&dbdd[sscbktk],g2di_sl,1);
   bitset(&dbdd[sscreplay],g2di_sl,1);
   dbadv[db_ora_sim]=0;
   dbadv[db_minuti_sim]=0;
   dbadv[db_secondi_sim]=0;
}
