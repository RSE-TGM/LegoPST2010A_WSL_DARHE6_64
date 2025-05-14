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
static char SccsID[] = "@(#)sked_errore.c	5.1\t11/7/95";
/*
   modulo sked_errore.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_errore.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
#include <Rt/RtDbPunti.h>
#include <Rt/RtMemory.h>
#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "sked.h"
#include "sked_fun.h"
#include "comandi.h"

extern int      stato_sked;

extern int      tipo_sked;

extern int      id_msg_sked;	/* identificatore coda di messaggi da read  */

extern int      numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */
extern int      fp_master;	/* puntatore al socket del MAIN solo per
				 * slave  */

extern int      fp_com[MAX_MODEL];

extern int      fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi, solo per sked master */

extern int      nmod;		/* numero modelli */

extern RtDbPuntiOggetto dbpunti;


void sked_errore()
{
   MSG_NET         messaggio;
   int             i;
   STAT_PROC       *stat_proc;

   printf("\n\n GESTIONE ERRORI \n\n");

   /* propagazione dell'errore alle macchine SLAVE */
   if (tipo_sked == MASTER)
   {
      /* propaga il messaggio di errore */
      messaggio.header_net.tipo = ERRORE;
      messaggio.header_net.codice = (-1);
      messaggio.header_net.lun = 0;
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] > 0)
	 {
	    printf("prima scrittura in rete\n");
	    if (writen(fp_ordini[i], (char*)&messaggio.header_net,
		       sizeof(HEADER_NET)) < 0)
	    {
	       printf("Impossibile comunicare con %d\n", i);
	    }
	    printf("dopo scrittura in rete\n");
	 }
   } else
   {
      /* attende ciclo di messaggio ERRORE */
      printf("ATTENDE RITORNO ERRORE");
      msg_rcv(id_msg_sked, &messaggio, sizeof(HEADER_NET),
	      (long)ERRORE, !IPC_NOWAIT, TIMEOUT_SKED * 2);
   }

   /* Codifica tipo di errore  */

   /* circolo statistiche */
   printf("GESTIONE STATISTICHE\n");
   sked_statistiche();
   scoda_buffer(0);

   /* Verifica lo stato delle task */
   if (tipo_sked == MASTER)
   {
      for (i = 0; i < nmod; i++)
      {
	stat_proc = RtDbPGetPuntTaskStat(dbpunti,i);
	 if (fp_com[i] == 0)
	 {
	    if (stato_processo(stat_proc->pid) == 0)
	       printf("ERRORE TASK %d\n", i);
	 } else
	 {
	    if (stat_proc->pid == 0)
	       printf("ERRORE TASK %d\n", i);
	 }
      }
      sked_stato(stato_sked);
   }
   sked_fine();
   exit(0);
}
