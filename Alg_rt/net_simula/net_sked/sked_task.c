/**********************************************************************
*
*       C Source:               sked_task.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Oct 27 14:01:03 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_task.c-6 %  (%full_filespec: sked_task.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_task.c	5.1\t11/7/95";
/*
   modulo sked_task.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_task.c	5.1
*/
# include <stdio.h>
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
# include "dispatcher.h"
# include "comandi.h"
# include "sked.h"
#if defined BANCO_MANOVRA
# include "libmanovra.h"
# include "agg_manovra.h"
#endif
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>


void            attende_task();
void            sveglia_task();

extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

extern int      shr_usr_key;
extern int      pid_bm_slave;	/* identificatore pid processo agg_manovra
				 * SLAVE   */

extern S02      s02_;
extern int      id_msg_task[MAX_MODEL];
extern int      id_msg_rettask;
extern int      id_msg_taskbm;
extern SCAMBIO  scambio[MAX_MODEL][MAX_DT_DEC];
extern int      fp_com[MAX_MODEL];
int             attesa_task[MAX_MODEL];
int             ricezione_dati[MAX_MODEL];
int             pacchetto_anticipo[MAX_MODEL][MAX_MODEL];
extern int      stato_sked;	/* stato dello sked */
extern int      tipo_sked;
extern float    passo_grafica;
extern float    passo_legograf;
extern int      nmod;		/* numero dei modelli  */
extern int      nrip;		/* numero di ripetizioni della tabella di
				 * ripetizione */
extern float	fattore_step;

extern int      caricata_ci;

extern int      update_sicre_status;

extern int      id_msg_to_mandb, id_msg_from_mandb;

extern int      mandb_agganciato;

extern int      id_msg_pert;

double          tempo_ciclo;

double          tempo_chk_license = 0.0;  /* Istante di tempo a cui viene
                                             fatto il controllo della
                                             licenza                       */

double          gettim();

extern int TimeoutTask;

extern int      ind_task_rest;
extern double   tempo_license;           /* Tempo limite di validita' della
                                            licenza                       */
extern double   tempo_sim;

extern char     _NO_PRIOLO[10];

sked_task()
{
   int             i, k;
   int             itab;	/* indice variabile tabella sincronizzazione */
   static int      passo_g = 0;
   static int      passo_l = 0;
   float	   tempo_f22;
   double          tempo_lic_corr;
   int             ret;
   int             agg_dbpunti = 0;

   /*
    * legge il tempo di inizio ciclo 
    */
   tempo_ciclo = gettim();



   /*
    * incremento passi grafica, se passo_grafica=0  la registrazione e'
    * disabilitata      
    */
   if (passo_grafica != 0)
   {
      passo_g++;
      if (passo_g > passo_grafica)
	 passo_g = 1;
   }
   passo_l++;
   if (passo_l > passo_legograf)
      passo_l = 1;



   /* azzeramento campi attesa_task e ricezione_dati */
   for (i = 0; i < nmod; i++)
   {
      attesa_task[i] = 0;
      ricezione_dati[i] = 0;
      for (k = 0; k < nmod; k++)
	 pacchetto_anticipo[i][k] = 0;
   }
#if defined BANCO_MANOVRA
   invia_messaggio_bm(-1);
#endif

#if defined REPLAY
   /* se lo stato e' REPLAY legge da file le eventuali perturbazioni */
   if (stato_sked == STATO_REPLAY)
      if (sked_replay(1) < 0)
	 printf("Errore lettura file perturbazioni.dat\n");
#endif


   /* blocca la shared memory */
   blocca_shr();

   itab = 0;
   sveglia_task(0);
   if ((itab == 0) && (caricata_ci == 1))
   {
      printf("CARICATO SNAPSHOT\n");
      caricata_ci = 0;
   }
   if((itab == 0) && (update_sicre_status == 1))
   {
      printf("STO PER SALVARE SNAPSHOT\n");
      update_sicre_status =0;
   }


   for (itab = 1; itab < nrip; itab++)
   {
      /* attende le task previste */
      attende_task(itab);
#if defined BANCO_MANOVRA
      invia_messaggio_bm(MAX_MODEL);
#endif
      /* svuota gli eventuali buffer di rete */
      scoda_buffer(itab);
      /* scambia gli ingressi fra le task */
      sked_ingressi(itab);
      /* libera per un istante la shared memory */
      libera_shr();
      blocca_shr();

      /* si sincronizza con il tempo reale */
      sked_timer(agg_dbpunti);
      /* attiva le task */
      sveglia_task(itab);
      /*
       * invia il messaggio intermedio allo scada 
       */

#if defined SCADA 
      if(strcmp(_NO_PRIOLO, "") == 0) {
         if (itab == (int)(nrip/2)) {
/*
printf("sked_task DEBUG: AGGIORNAMENTO INTERMEDIO!!!!!\n");
*/
	    sked_stato_intermedio();
         }
      }
#endif
   }
   /* ultima iterazione */
   attende_task(0);
#if defined BANCO_MANOVRA
   invia_messaggio_bm(MAX_MODEL);
#endif

   scoda_buffer(0);

   sked_ingressi(0);

   /* gestione delle statistiche */
   if (tipo_sked != MASTER)
   {
      sked_statistiche();
      scoda_buffer(0);
   }
   if (tipo_sked == MASTER)
   {
      sked_statistiche();
   }
   if (passo_l == 1)
      sked_legograf(0.1);

   /* libera la shared memory */
   libera_shr();

   /* attivazione processo net_prepf22  */
   if ((passo_g == 1) && (passo_grafica != 0) && (stato_sked != STATO_REPLAY))
   {
/*
   Si anticipa il calcolo del tempo finale del passo di simulazione per
   caricarlo in dbpunti_ext e metterlo a disposizione del processo
   net_prepf22_circ. Viene settato il flag agg_dbpunti che segnala alla
   sked_timer che il tempo di simulazione e' gia' stato aggiornato.
*/
      tempo_f22=tempo_sim + 100.0*fattore_step;
      RtDbPPutTime(dbpunti,(float)(tempo_f22/1000));
      RtDbPPutTime(dbpunti_ext,(float)(tempo_f22/1000));
      agg_dbpunti = 1;
/*
printf("sked_task DEBUG dopo: tempo_f22_sec = %f\n", (float)(tempo_f22/1000));
*/
      sked_pf22(1);
   }
   sked_timer(agg_dbpunti);
   /*
    * calcola il tempo del ciclo 
    */

   tempo_ciclo = gettim() - tempo_ciclo;

/*
 * Invia ai processi di monitoraggio lo stato dello sked, imponendo
 * lo stato di freeze nel caso di ripartenza di una task dopo un crash.
 * Verifica se la licenza e' ancora attiva. 
 */
   if(ind_task_rest==-1) {
/*
   Il controllo dello stato della licenza si fa ogni TIME_CHK_LIC
*/
      if((gettim() - tempo_chk_license) > TIME_CHK_LIC) {
         tempo_chk_license = gettim();
         ret = getTimeLicense(&tempo_lic_corr);
/*
printf("sked_task DEBUG: tempo_license = %lf\ttempo_lic_corr = %lf\n",
       tempo_license, tempo_lic_corr);
*/
         if(ret == 0) {
            if(tempo_lic_corr > tempo_license) {
/*
 *   Scaduta disponibilita' licenza. killsim
 */
                printf("###################################################\n");
                printf("###################################################\n");
                printf("#                                                 #\n");
                printf("#        SIMULATOR LICENSE IS EXPIRED!!!          #\n");
                printf("#                                                 #\n");
                printf("###############%d#############################\n",tempo_lic_corr);
                printf("##############%d##############################\n",tempo_license);
                system("killsim");
		exit(123);
            }
         }
      }
      sked_stato(stato_sked);
   }
   else {
/*
printf("SKED_TASK DEBUG: prima della chiamata alla sked_stato!!!\n");
*/
      if(stato_sked == STATO_REPLAY)
         sked_stato(stato_sked);
      else
         sked_stato(STATO_FREEZE);
   }


}
/*
Funzione che permette di svegliare tutte le task 
dopo aver settato un certo tipo di messaggio (parametro int)
per la task. Tale msg viene ricevuto nella task in reg000
*/
int sked_task_info(int *tipo_messaggio)
{

int             i, k;

/* blocca la shared memory */
   blocca_shr();
/*
Invio messaggio alla task
*/
   sveglia_task(0);

   attende_task(0);




   /* gestione delle statistiche */
   if (tipo_sked != MASTER)
   {
      sked_statistiche();
      scoda_buffer(0);
   }
   if (tipo_sked == MASTER)
   {
      sked_statistiche();
   }
   /* libera la shared memory */
   libera_shr();

   /*
    * calcola il tempo del ciclo 
    */


   /* invia ai processi di monitoraggio lo stato dello sked */
   sked_stato(stato_sked);

   if( *tipo_messaggio == 1)
   {
      *tipo_messaggio =0; /* don't send  TASK_SAVE_SNAP during next sveglia_task */
   }

}

void
attende_task(tab)
   int             tab;
{
   int             i, j, r_mod;
   MESSAGGI_TASK   messaggi_task;
   int             attendere = 0;
   int             ret = 1;


   /* settaggio task da attendere */
   for (i = 0; i < nmod; i++)
      if ((s02_.tabel[i].inst[tab] == 1) && (attesa_task[i] == 1) &&
	  (fp_com[i] == 0))
      {
	 ++attendere;
      }
   while (attendere > 0)
   {
      if (attendere > 0)
	 ret = msg_rcv(id_msg_rettask, &messaggi_task,
		       sizeof(messaggi_task.mtext), (long)(-MAX_MODEL), !IPC_NOWAIT, 
                       TimeoutTask);
      else
	 ret = msg_rcv(id_msg_rettask, &messaggi_task,
		       sizeof(messaggi_task.mtext), (long)(-MAX_MODEL), IPC_NOWAIT, 
                       TimeoutTask);

      if (ret == TIMEOUT_SCADUTO)
      {
	 printf("\n\n\nSKED_TASK: ATTENZIONE ERRORE TASK itab=%d\n\n\n", tab);
	 sked_stato_task();
	 sked_stato(STATO_ERRORE);
	 sked_errore();
      }
      if (ret > 0)
      {
#if defined BANCO_MANOVRA
	 invia_messaggio_bm(messaggi_task.mtype - 1);
#endif
	 attesa_task[messaggi_task.mtype - 1] = 0;
	 if (s02_.tabel[messaggi_task.mtype - 1].inst[tab] == 1)
	    --attendere;
	 /* trasmette i dati */
	 for (j = tab; j < nrip; ++j)
	    if (s02_.tabel[messaggi_task.mtype - 1].inst[j] == 1)
	    {
	       sked_trasmette(messaggi_task.mtype - 1, j);
	       /*
	        * printf ("trasmette dati mod. %d per frame %d\n",
	        * messaggi_task.mtype-1,j);   
	        */
	       break;
	    }
	 if (s02_.tabel[messaggi_task.mtype - 1].inst[j] == 0)
	 {
	    sked_trasmette(messaggi_task.mtype - 1, 0);
	    /*
	     * printf ("trasmette dati mod. %d per frame %d\n",
	     * messaggi_task.mtype-1,j);             
	     */
	 }
      }
   }
}


void
sveglia_task(tab)
   int             tab;
{
   int             i, r_mod;
   MESSAGGI_TASK   messaggi_task;
   MSG_DISPATCHER  messaggio_mandb;
   int             imp = 1;
   STAT_PROC       *stat_proc;

   /* riceve le perturbazioni */
   pert_rcv(id_msg_pert);


   for (i = 0; i < nmod; i++)
      if ((s02_.tabel[i].inst[tab] == 1) &&
	  (fp_com[i] == 0))
      {
	stat_proc = RtDbPGetPuntTaskStat(dbpunti,i);
	 if (stato_processo(stat_proc->pid) != 0)
	 {
	    gest_area_pert(i, s02_.model[i].dt);
	    if (imp == 1)
	    {
	       imp = 0;
	       /* manda l'impulso MDB     */
	       if (mandb_agganciato)
	       {
		  messaggio_mandb.mtype = SKDIS_MANDB_SIGNAL;
		  msg_snd(id_msg_to_mandb, &messaggio_mandb, sizeof(MSG_DISPATCHER) -
			  sizeof(long), !IPC_NOWAIT);
		  if (msg_rcv(id_msg_from_mandb, &messaggio_mandb, sizeof(MSG_DISPATCHER) -
		  sizeof(long), (long)SKDIS_MANDB_SIGNAL_ACK, !IPC_NOWAIT, 2) < 0)
		     mandb_agganciato = 0;
	       }
	       /*
	        * imp_mdb(); 
	        */
	    }
	    messaggi_task.mtype = i + 1 + MAX_MODEL;
	    messaggi_task.mtext = TASK_NEXT;
	    if (stato_sked == STATO_FREEZE)
	       messaggi_task.mtext = TASK_STEP;
	    if ((tab == 0) && (caricata_ci == 1))
	       messaggi_task.mtext = TASK_SNAP;
	    if ((tab == 0) && (update_sicre_status == 1))
	       messaggi_task.mtext = TASK_SAVE_SNAP;
	    /* manda il messaggio di attivazione alla task  */
	    msg_snd(id_msg_task[i], &messaggi_task,
		    sizeof(messaggi_task.mtext), !IPC_NOWAIT);
	    attesa_task[i] = 1;
	 } else
	 {
	    printf("\n\n\nERRORE TASK(sveglia)\n\n\n");
	    stato_sked = STATO_ERRORE;
	    sked_stato(stato_sked);
	    sked_errore();
	 }
      }
}


#if defined BANCO_MANOVRA
invia_messaggio_bm(modo)
   int             modo;
{
   static MESSAGGI_TASKBM messaggi_taskbm;
#if defined UNIX
   static struct msqid_ds buf;
#endif
   int             count = 0;

   if (pid_bm_slave > 0)
   {
      if (modo == -1)
	 memset(&messaggi_taskbm.task[0], 0, MAX_MODEL * sizeof(int));
      else
      if (modo == MAX_MODEL)
      {
	 /*
	  * Invia messaggio a bm 
	  */
#if defined UNIX
	 if (msgctl(id_msg_taskbm, IPC_STAT, &buf) == -1)
	    fprintf(stderr, "net_sked: errore msgctl\n");
	 while (buf.msg_qnum > 50)
	 {
	    fprintf(stderr, "MANOVRA: > 50\n");
	    sospendi(100);
	    if (msgctl(id_msg_taskbm, IPC_STAT, &buf) == -1)
	       fprintf(stderr, "net_sked: errore msgctl\n");
	    count++;
	    if (count > 10)
	    {
	       fprintf(stderr,
		       "\nnet_sked: aggiornamento task agg_manovra SLAVE messaggi non scodati\n");
	       /*
	        * pid_bm_slave=0; return(1); 
	        */
	       count = 0;
	    }
	 }
#endif
	 messaggi_taskbm.mtype = 1;
	 msg_snd(id_msg_taskbm, &messaggi_taskbm,
		 sizeof(MESSAGGI_TASKBM) - sizeof(long), !IPC_NOWAIT);
	 memset(&messaggi_taskbm.task[0], 0, MAX_MODEL * sizeof(int));
      } else
	 messaggi_taskbm.task[modo] = 1;
   }
}
#endif
