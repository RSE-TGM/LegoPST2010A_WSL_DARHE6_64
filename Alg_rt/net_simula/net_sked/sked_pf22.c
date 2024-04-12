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
static char SccsID[] = "@(#)sked_pf22.c	5.1\t11/7/95";
/*
   modulo sked_pf22.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_pf22.c	5.1
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
# include "comandi.h"
# include "sked.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern RtDbPuntiOggetto dbpunti;

extern int      id_msg_prep;

extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1          */




sked_pf22(modo)
   int             modo;
{
   MSG_AUS         messaggio_aus;
   STAT_PROC       *stat_proc;

   if (tipo_sked == MASTER)
   {
      stat_proc = RtDbPGetPuntAusStat(dbpunti,PREP_F22 - 1);
      if (stato_processo(stat_proc->pid))
      {
	 if (modo == 1)
	    messaggio_aus.ausiliario.comando = START_AUS;
	 if (modo == 0)
	    messaggio_aus.ausiliario.comando = RESET_AUS;
	 if (modo == 2)
	    messaggio_aus.ausiliario.comando = RELOAD_AUS;
	 messaggio_aus.mtype = PREP_F22;
	 msg_snd(id_msg_prep, &messaggio_aus, sizeof(TIPO_AUS),
		 !IPC_NOWAIT);
	 if (modo == 2)
	    msg_rcv(id_msg_prep, &messaggio_aus, sizeof(TIPO_AUS),
		    (long)(PREP_F22 + OFFSET_AUS), !IPC_NOWAIT, TIMEOUT_AUS * 2);
	 else
	    msg_rcv(id_msg_prep, &messaggio_aus, sizeof(TIPO_AUS),
		    (long)(PREP_F22 + OFFSET_AUS), !IPC_NOWAIT, TIMEOUT_AUS);
      }
   }
}
