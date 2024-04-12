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
static char SccsID[] = "@(#)sked_statistiche.c	5.1\t11/7/95";
/*
   modulo sked_statistiche.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_statistiche.c	5.1
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
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern int      nmod;		/* numero_modelli */

extern int      nrip;

extern float    velocita;	/* velocita' di simulazione */


extern int      fp_master;	/* puntatore al socket del MAIN solo per
				 * slave  */

extern int      fp_com[MAX_MODEL];	/* 0 -> task sulla stessa macchina 1
					 * -> task su macchine diverse fp ->
					 * socket scrittura */

extern char    *fp_app_master;

extern int     *fp_size_master;

extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1          */
extern int      stato_sked;

extern int      numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */

extern RtDbPuntiOggetto dbpunti;

extern int      id_msg_sked;	/* id coda messaggi  da processi read */

extern int      id_msg_task[MAX_MODEL];

extern int      id_msg_rettask;


sked_statistiche()
{
   int             i, k;
   MSG_NET         messaggio;
   PACCHETTO_NET   pacchetto_net;
   float           cpu_tot = 0;
   int             sorg;
   STAT_PROC       *stat_proc;


   if (tipo_sked == MASTER)
   {
      for (i = 0; i < numero_slave; i++)
      {
	 if (msg_rcv(id_msg_sked, &messaggio, sizeof(HEADER_NET) +
		     sizeof(float) * MAX_DATI_NET, (long)DATISTAT,
		     !IPC_NOWAIT, TIMEOUT_SKED) == TIMEOUT_SCADUTO)
	 {
	    printf("Sked_statistiche: timeout scaduto\n");
	    if (stato_sked < STATO_ERRORE)
	    {
	       sked_stato(STATO_ERRORE);
	       sked_errore();
	    }
	 }
	 for (k = 0; k < (messaggio.header_net.lun / sizeof(float)); k = k + 3)
	 {
	    if ((int) messaggio.dato[k] < MAX_MODEL)
	    {
	       stat_proc=RtDbPGetPuntTaskStat(dbpunti,(int) messaggio.dato[k]);
	       stat_proc->cpu_use = messaggio.dato[k+1];
	       stat_proc->pid = (int) messaggio.dato[k+2];
	    }
#if defined BANCO_MANOVRA
	    else
	    {
	       sorg = messaggio.header_net.sorg;
	       stat_proc=RtDbPGetPuntAusStat(dbpunti,
			AGG_MANOVRA + 1 + sorg + 1);
	       stat_proc->pid = (int) messaggio.dato[k+1];
	       k = k + 3;
	       stat_proc=RtDbPGetPuntAusStat(dbpunti,
			AGG_MANOVRA + MAX_SLAVE + sorg + 3);
	       stat_proc->pid = (int) messaggio.dato[k+1];
	    }
#endif
	 }
      }
   } else
   {
      k = 0;
      pacchetto_net.header_net.sorg = (-1);	/* momentaneamente a -1 */
      pacchetto_net.header_net.dest = (-1);	/* momentaneamente a -1 */
      pacchetto_net.header_net.tasksorg = (-1);
      pacchetto_net.header_net.taskdest = (-1);
      pacchetto_net.header_net.tipo = DATISTAT;
      pacchetto_net.header_net.flag = (-1);
      pacchetto_net.header_net.lun = k;
      pacchetto_net.header_net.codice = (-1);
      for (i = 0; i < nmod; i++)
	 if (fp_com[i] == 0)
	 {
	    stat_proc=RtDbPGetPuntTaskStat(dbpunti,i);
	    pacchetto_net.dato[k] = i;
	    k++;
	    pacchetto_net.dato[k] = stat_proc->cpu_use;
	    k++;
	    pacchetto_net.dato[k] =
	       (float) stato_processo(stat_proc->pid);
	    k++;
	 }
#if defined BANCO_MANOVRA
      stat_proc=RtDbPGetPuntAusStat(dbpunti,AGG_MANOVRA + 1);
      if (stat_proc->pid > 0)
      {
	 pacchetto_net.dato[k] = MAX_MODEL;
	 k++;
	 stat_proc=RtDbPGetPuntAusStat(dbpunti,AGG_MANOVRA + 1);
	 pacchetto_net.dato[k] =
	    (float) stato_processo(stat_proc->pid);
	 k++;
	 k++;
	 pacchetto_net.dato[k] = MAX_MODEL;
	 k++;
	 stat_proc=RtDbPGetPuntAusStat(dbpunti,AGG_MANOVRA + MAX_SLAVE + 2);
	 pacchetto_net.dato[k] =
	    (float) stato_processo(stat_proc->pid);
	 k++;
	 k++;
      }
#endif
      pacchetto_net.header_net.lun = k * sizeof(float);
      /* spedisce il pacchetto */
      memcpy(&fp_app_master[(*(fp_size_master))], &pacchetto_net,
	     sizeof(HEADER_NET) + pacchetto_net.header_net.lun);

      *fp_size_master = *fp_size_master + sizeof(HEADER_NET) +
	 pacchetto_net.header_net.lun;

   }
}


int
sked_stato_task()
{
   int             i, ret;
   MESSAGGI_TASK   messaggi_task;
   STAT_PROC       *stat_proc;

   printf("testo lo stato delle task\n");
   for (i = 0; i < nmod; i++)
   {
      if (fp_com[i] == 0)
      {
	 messaggi_task.mtype = i + 1 + MAX_MODEL;
	 messaggi_task.mtext = TASK_TEST;
	 msg_snd(id_msg_task[i], &messaggi_task,
		 sizeof(messaggi_task.mtext), !IPC_NOWAIT);
	 ret = msg_rcv(id_msg_rettask, &messaggi_task,
		       sizeof(messaggi_task.mtext),
		       (long)(i + 1), !IPC_NOWAIT, 1);
	 if (ret < 0)
	 {
	    stat_proc=RtDbPGetPuntTaskStat(dbpunti,i);
	    stat_proc->pid = -1;
	    printf("Abortita task %d\n", i);
	 }
      }
   }

}
