/**********************************************************************
*
*       C Source:               sked_legograf.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:29:31 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_legograf.c-4 %  (%full_filespec: sked_legograf.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_legograf.c	5.1\t11/7/95";
/*
   modulo sked_legograf.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_legograf.c	5.1
*/
# include <stdio.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "sked.h"
# include "comandi.h"
# include "libnet.h"
#include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern S02      s02_;
extern int      tipo_sked;
extern int      nmod;		/* numero dei modelli */
extern int      id_msg_leg;	/* id coda messaggi  da processi ausiliari */
extern int      fp_com[MAX_MODEL];	/* 0 -> task sulla stessa macchina 1
					 * -> task su macchine diverse fp ->
					 * socket scrittura */
extern int      numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */

extern int      fp_to_dispatcher;

extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

extern float *area_dati;
extern float *area_dati_ext;

sked_legograf(float off_time)
{
   MSG_LEGOGRAF    messaggio_legograf;
   int             i, j, app_int;
   float app_tempo;
   int app_stato;

   if (tipo_sked == MASTER)
   {
      /*
       * esegue la copia della sezione della banca dati residente sulla
       * macchina master sul database di legograf  
       */

/**
      RtDbPCopyDb(dbpunti_ext,dbpunti);
**/

      for (i = 0; i < nmod; i++)
               if (fp_com[i] == 0)
               {
		int size_task;
		int ini_task;

		ini_task = RtDbPInizioModelli(dbpunti,i);
		size_task = RtDbPSizeModelli(dbpunti,i);
                /*
                printf("\tSKED_LEGOGRAF i=%d ini_task=%d  size_task=%d [%f]\n",
                       i,ini_task,size_task,area_dati[ini_task]);
                */
		memcpy(&area_dati_ext[ini_task],&area_dati[ini_task],size_task);
		}
		



      /* assegna la variabile tempo */
      RtDbPGetTime(dbpunti,&app_tempo);
      RtDbPPutTime(dbpunti_ext,app_tempo);
      RtDbPGetStato(dbpunti,&app_stato);
      RtDbPPutStato(dbpunti_ext,app_stato);
   } else
   {
      /* invia il messaggio di start al processo net_upd_legograf */
      messaggio_legograf.mtype = LEGOGRAF;
      msg_snd(id_msg_leg, &messaggio_legograf, sizeof(TIPO_LEGOGRAF),
	      !IPC_NOWAIT);
   }
}
