/**********************************************************************
*
*       C Source:               sked_slave.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:29:46 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_slave.c-6 %  (%full_filespec: sked_slave.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_slave.c	5.2\t3/7/96";
/*
   modulo sked_slave.c
   tipo 
   release 5.2
   data 3/7/96
   reserved @(#)sked_slave.c	5.2
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

extern int      id_msg_sked;

extern int      tipo_sked;

extern int      stato_sked;	/* definisce lo stato dello sked */

extern MSG_NET  messaggio_master;	/* messaggio da master */

extern int      iterazione_successiva;

extern float    passo_grafica;

extern float    fattore_step;	/* fattore moltiplicativo del passo di tempo                           */

extern int      caricata_ci;

extern RtDbPuntiOggetto dbpunti;


/*
 * per gestione MANDB sulla macchina slave 
 */
extern int      id_msg_to_mandb, id_msg_from_mandb;

extern int      mandb_agganciato;

extern int      shr_usr_key;

int             modo_backtrack;

extern int    _MAX_SNAP_SHOT;
extern int    _MAX_BACK_TRACK;
extern int    _MAX_CAMPIONI;
extern int    _NUM_VAR;
extern int    _MAX_PERTUR;
extern int    _SPARE_SNAP;
extern int    _PERT_CLEAR;

sked_slave()
{
   int             operazione;

   /*
    * per gestione MANDB sulla macchina slave 
    */
   MSG_DISPATCHER  messaggio_mandb;
   MSG_ACK         msg_ack;
   static int      prima_volta = 1;

   if (prima_volta == 1)
   {
      prima_volta = 0;
      /* decodifica SHR_USR_KEY */
      shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));
      /* creazione code messaggio da mandb */
      id_msg_to_mandb = msg_create(shr_usr_key + ID_MSG_TO_MANDB, 1);
      id_msg_from_mandb = msg_create(shr_usr_key + ID_MSG_FROM_MANDB, 1);
   }
   /* verifica che non ci siano messaggi da MANDB */
   if (msg_rcv(id_msg_from_mandb, &messaggio_mandb, sizeof(MSG_DISPATCHER) -
	       sizeof(long), (long)-999, IPC_NOWAIT, TIMEOUT_INF) > 0)
   {
      printf("\n\n\n RICEVUTO MESSAGGIO MANDB\n\n\n");
      if (messaggio_mandb.mtype == SKDIS_AGGANCIO_MANDB)
	 mandb_agganciato = 1;
      if (messaggio_mandb.mtype == SKDIS_SGANCIO_MANDB)
	 mandb_agganciato = 0;
      /* comunica al mandb il ricevimento del messaggio */
      msg_ack.mtype = 1000;
      msg_snd(id_msg_to_mandb, &msg_ack, 0, !IPC_NOWAIT);
      printf("mandb_agganciato = %d\n", mandb_agganciato);
   }
   /* scodamento messaggi sked non master */
   msg_rcv(id_msg_sked, &messaggio_master, sizeof(HEADER_NET) + sizeof(float),
	   (long)COMSIM, !IPC_NOWAIT, TIMEOUT_INF);

   iterazione_successiva = 0;
   /*
    * if(messaggio_master.header_net.codice!=STOP) iterazione_successiva=1;
    * else iterazione_successiva=0; 
    */

   operazione = messaggio_master.header_net.codice;

   /* scodamento eventuali messaggi */
   switch (operazione)
   {
   case NEXT:
      {
	 RtDbPPutTime(dbpunti,messaggio_master.dato[0]);
	 /*
	  * MODIFICA PER MANDB 
	  */
	 RtDbPPutStato(dbpunti,STATO_RUN);
/*
         Dal momento che non si usa la funzione sked_stato si setta la
         stato_sekd=STATO_RUN     22 FEBB
         Comunque da questo lo stato dello slave restera' RUN
         anche se il master va in freeze.
*/
         stato_sked = STATO_RUN;
	 iterazione_successiva = 1;
	 break;
      }
   case STOP:
      {
	 iterazione_successiva = 0;
	 sked_fine();
	 break;
      }
   case SAVESNAP:
      {
	 iterazione_successiva = 0;
	 /* sked_snapshot(SAVESNAP);         */
	 /* per rimozione up_down su slave                          */
	 modo_backtrack = 0;
	 sked_snapshot_piac(SAVESNAP);
	 break;
      }
   case LOADSNAP:
      {
	 iterazione_successiva = 0;
	 /* sked_snapshot(LOADSNAP); 29-8-96 */
	 sked_snapshot_piac(LOADSNAP);
	 /*init_area_pert();*/
/*       In modalita' _PERT_CLEAR si azzerano le perturbazioni */
         if ( _PERT_CLEAR==1 )
            {
            init_area_pert();
            }
	 caricata_ci = 1;
	 break;
      }
   case SAVEBKTK:
      {
	 iterazione_successiva = 0;
	 /* sked_snapshot(SAVESNAP);    */
	 /* per rimozione up_down su slave                          */
	 modo_backtrack = 1;
	 sked_snapshot_piac(SAVESNAP);
	 break;
      }
   case LOADBKTK:
      {
	 iterazione_successiva = 0;
	 /* sked_snapshot(LOADSNAP);  29-8-96 */
	 sked_snapshot_piac(LOADSNAP);
/*       In modalita' _PERT_CLEAR si azzerano le perturbazioni */
         if ( _PERT_CLEAR==1 )
            {
            init_area_pert();
            }
	 caricata_ci = 1;
	 break;
      }
   case STEPCR:
      {
      int app_passo_grafica;

	 passo_grafica = messaggio_master.header_net.flag;
	 app_passo_grafica = passo_grafica;
	 RtDbPPutStepCr(dbpunti,app_passo_grafica);
	 printf("Passo grafica=%f\n", passo_grafica);
	 iterazione_successiva = 0;
	 break;
      }
   case STEPSCALING:
      {
	 fattore_step = (float) messaggio_master.header_net.flag;
	 fattore_step = fattore_step / 10;
	 RtDbPPutStepScaling(dbpunti,fattore_step);
	 printf("Nuovo step integr.=%f\n", fattore_step);
	 iterazione_successiva = 0;
	 break;
      }
#if defined SAVEPERT
   case INVIO_PERT:
      {
/*       Quando si proviene da stato RUN del master  */
	 iterazione_successiva = 0;
	 printf("sked_slave: Ricevuto comando INVIO_PERT\n");
	 sked_raccogli_pert();
	 break;
      }
#endif
#if defined SAVEPERT
   case CLEAR_PERT:
      {
/*
         Quando si proveniva da stato BACKTRACK del master. Ora tale messaggio
         non viene piu' inviato in quanto dopo il load di un backtrack ho gia'
         la mia nuova area pert!!!
*/
	 iterazione_successiva = 0;
	 printf("sked_slave: Ricevuto comando CLEAR_PERT\n");
	 sked_replay(4);
	 break;
      }
   case CLEAR_PERT_FILE:
      {
/*       Riscrive il file perturbazioni.dat */
	 iterazione_successiva = 0;
	 printf("\n\nsked_slave: Ricevuto comando CLEAR_PERT_FILE\n");
	 sked_replay(6);
	 break;
      }
#endif
   case CLEAR:
      {
      fprintf(stderr,"sked_slave: ricevuto comando CLEAR\n");
      iterazione_successiva = 0;
      sked_replay(4);
      break;
      }
   case CLEAR_AREA_PERT:
      {
/*
         Inviato dal master quando fa loadbt con lo stato backtrack allo
         scopo di far fare allo slave la init_area_pert.
*/
	 iterazione_successiva = 0;
	 printf("sked_slave: Ricevuto comando CLEAR_AREA_PERT\n");
	 init_area_pert();
	 break;
      }
   case CLEAR_UPDOWN:
      {
	 printf("Ricevuto comando clear updown pert\n");
	 iterazione_successiva = 0;
	 cut_updown();
/*
         Il master dopo cut_updown non fa piu' init_area_pert perche'
         prosegue con il database che ha al momento e con le sue pert.
         Lo stesso (sempre a parte gli updown) lo fa lo slave.
*/
         /*init_area_pert();*/ /* 29-8-96 */
	 break;
      }
   default:
      {
	 iterazione_successiva = 0;
	 sleep(1);
	 printf("Comando non corretto o non implementato [%d]\n",
                 operazione);
	 break;
      }
   }				/* switch */
}
