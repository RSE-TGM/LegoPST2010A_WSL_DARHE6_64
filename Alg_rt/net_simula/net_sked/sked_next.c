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
static char SccsID[] = "@(#)sked_next.c	5.1\t11/7/95";
/*
   modulo sked_next.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_next.c	5.1
*/
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <time.h>
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
# include "dispatcher.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1          */
extern int      nmod;

extern int      id_msg_sked;	/* id coda messaggi sked    */

extern int      fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi, solo per sked master */

extern MSG_NET  messaggio_master;	/* messaggio da master */

extern int      iterazione_successiva;


extern RtDbPuntiOggetto dbpunti;

sked_next()
{
   int             i;
   float app_tempo;

   /* messaggio di esecuzione passo successivo */
   if (tipo_sked == MASTER)
   {
      messaggio_master.header_net.tipo = COMSIM;
      messaggio_master.header_net.codice = NEXT;
      messaggio_master.header_net.lun = sizeof(float);
      /* printf("------------ INVIA NEXT ------------\n"); */
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] > 0)
	 {
	    if (writen(fp_ordini[i], &messaggio_master.header_net,
		       sizeof(HEADER_NET)) < 0)
	    {
	       sked_stato(STATO_ERRORE);
	       printf("Impossibile com %d\n", i);
	       sked_errore();
	    }
	    RtDbPGetTime(dbpunti,&app_tempo);
	    if (writen(fp_ordini[i], &app_tempo, sizeof(float)) < 0)
	    {
	       sked_stato(STATO_ERRORE);
	       printf("Impossibile com %d\n", i);
	       sked_errore();
	    }
	 }
   } else
   {
      /* printf("------------ ATTENDE NEXT ------------\n"); */
      messaggio_master.header_net.codice = -1;
      while (messaggio_master.header_net.codice != NEXT)
      {
	 msg_rcv(id_msg_sked, &messaggio_master,
		 sizeof(HEADER_NET) + sizeof(float),
		 (long)COMSIM, !IPC_NOWAIT, TIMEOUT_INF);
	 if (messaggio_master.header_net.codice != NEXT)
	    printf("sked_next: ricevuto messaggio errato\n");
      }
      RtDbPPutTime(dbpunti,messaggio_master.dato[0]);
      printf("tempo_slave=%f\n", messaggio_master.dato[0]);
      if (messaggio_master.header_net.codice != STOP)
	 iterazione_successiva = 1;
      else
	 iterazione_successiva = 0;

      /* printf("------------ RICEVUTO NEXT ------------\n"); */
   }
}
