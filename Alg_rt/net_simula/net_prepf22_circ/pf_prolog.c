/**********************************************************************
*
*       C Source:               pf_prolog.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:28:54 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pf_prolog.c-3 %  (%full_filespec: pf_prolog.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pf_prolog.c	5.2\t11/30/95";
/*
   modulo pf_prolog.c
   tipo 
   release 5.2
   data 11/30/95
   reserved @(#)pf_prolog.c	5.2
*/
# include <errno.h>
# include <stdio.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
#endif
#if defined VMS
#include "vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtErrore.h>
# include "comandi.h"
# include "pf_macro.h"          /* macro per switch VMS-UNIX    */

RtDbPuntiOggetto dbpunti;
RtErroreOggetto errore;

void pf_address();


void pf_prolog()
{
SIMULATOR *sim;

  int             shr_usr_key;	/* chiave utente per shared         */

  shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));


   errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_prepf22");
   sim = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
   dbpunti = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
   free(sim);


  /* lettura della selezione delle variabili */
  pf_address();


  /* aggancio code messaggi */
  msg_create_fam(shr_usr_key, 0);

}
