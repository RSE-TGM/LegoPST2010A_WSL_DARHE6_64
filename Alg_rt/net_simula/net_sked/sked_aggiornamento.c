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
static char SccsID[] = "@(#)sked_aggiornamento.c	5.1\t11/7/95";
/*
   modulo sked_aggiornamento.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_aggiornamento.c	5.1
*/
# include <stdio.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
# include <Rt/RtMemory.h>


int             tipo_sked;	/* tipo di sked */


void sked_aggiornamento()
{
   FILE           *fp;
   char           *getenv();	/* funzioni utilizzate           */
   char            appoggio[80];

   if (tipo_sked == MASTER)

   {
      sprintf(appoggio, "%s/net_compi", getenv("LEGORT_BIN"));

      /* verifica S01 se non esiste esce da monit */
      if (!(fp = fopen("S01", "r")))
	 exit(puts(
		   "ATTENZIONE non esiste il file S01"));
      fclose(fp);

      /* verifica S02 se non esiste lancia COMPI  */
      if (!(fp = fopen("S02", "r")))
	 system(appoggio);
      fclose(fp);

      /* verifica l'aggiornamento del S02  */
      if (tempo_file("S01", "S02"))
	 system(appoggio);

   }
}
