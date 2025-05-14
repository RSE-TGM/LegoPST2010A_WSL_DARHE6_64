/**********************************************************************
*
*       C Source:               sked_stato.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Jul 10 16:28:44 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_stato.c-4 %  (%full_filespec: sked_stato.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_stato.c	5.4\t2/20/96";
/*
   modulo sked_stato.c
   tipo 
   release 5.4
   data 2/20/96
   reserved @(#)sked_stato.c	5.4
*/
# include <stdio.h>
# include <string.h>
# include <errno.h>
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
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "libnet.h"
# include "sked.h"
# include "sked_fun.h"
# include "dispatcher.h"

#include "libipc.h"

#include <curses.h>

extern int      stato_sked;	/* definisce lo stato dello sked */
extern int      nmod;

extern int      nrip;

extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1          */

extern int      id_msg_banco;	/* id coda messaggi banco    */
extern int      id_msg_monit;	/* id coda messaggi monit    */

extern RtDbPuntiOggetto  dbpunti;
extern RtDbPuntiOggetto  dbpunti_ext;


extern int      fp_com[MAX_MODEL];

extern int      numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */


extern int      nrip;

extern double   tempo_sim;	/* tempo della simulazione */
extern double   tempo_reale;	/* tempo reale   */
extern double   tempo_iniziale;	/* tempo iniziale della simulazione */
extern double   tempo_freeze;	/* tempo per conteggio freeze  */
extern double   ritardo_sim;	/* ritardo accumulato */
extern float    velocita;

extern int      id_msg_to_sked, id_msg_from_sked;

extern int      id_sem_disp;

extern int      fp_to_dispatcher;

extern double   tempo_ciclo;

extern int      TimeAggStat;

extern int      ind_task_rest;          /* indice della task che e' caduta
                                           e fatta ripartire               */ 

extern int      rest_banco_err;

STATISTICA_SKED statistica_sked;

double          gettim();

double          tempo_agg_stat = 0.0;
double          tempo_agg_stat_int = 0.0;

void sked_stato(stato)
   int             stato;
{
   char            app[MAX_LUN_COMANDI_SKDIS];
   int             i;
   MSG_DISPATCHER  comando_dispatcher;
   int             tipo_comando;
   static int      prima_volta = 1;
   int             messaggi_code = 0;
   int             stato_modificato = 0;
   int app_stato,app_passo_reg;
   float app_tempo;
   STATISTICS *punt_stat;
   STATISTICS statistics;
   STAT_PROC *stat_proc;

#if defined MAURIC
/* Ripristino stampe id_sem_disp */
   int sem_val;
#endif

#if defined UNIX
   struct msqid_ds buf;
#endif

   if ((prima_volta) && (stato_sked != STATO_ERRORE) && (tipo_sked == MASTER))
   {
      prima_volta = 0;
   }
   RtDbPGetStato(dbpunti,&app_stato);
   if (app_stato != stato)
      stato_modificato = 1;

   stato_sked = stato;
   RtDbPPutStato(dbpunti,stato);

   /*
    * verifica il numero di messaggi presenti nella coda se e' scarica (2
    * messaggi) invia la statistica 
    */

#if defined UNIX 
   msgctl(id_msg_from_sked, IPC_STAT, &buf);
   messaggi_code = buf.msg_qnum;
#endif



   if (((messaggi_code < 2)&&((gettim() - tempo_agg_stat) > TimeAggStat)) || (stato_modificato))
      { 
      tempo_agg_stat = gettim();
      /* notifica al banco e a monit */
      if (tipo_sked == MASTER)
      {
	 RtDbPGetStato(dbpunti,&app_stato);
	 RtDbPPutStato(dbpunti_ext,app_stato);
	 RtDbPGetTime(dbpunti,&app_tempo);
	 RtDbPPutTime(dbpunti_ext,app_tempo);
	 /* costruisce il messaggio */
	 statistica_sked.stato_sked = stato_sked;
	 RtDbPGetTime(dbpunti,&(statistica_sked.tempo_sim));
	 RtDbPGetDelay(dbpunti,&(statistica_sked.tempo_ritardo));
	 RtDbPGetTimeScaling(dbpunti,&(statistica_sked.timescaling_sim));
	 RtDbPGetStepScaling(dbpunti,&(statistica_sked.stepscaling_sim));
	 RtDbPGetStepCr(dbpunti,&app_passo_reg);
	 statistica_sked.passo_reg = app_passo_reg;
	 RtDbPGetNumCr(dbpunti_ext,&(statistica_sked.grandezze_mem));
	 RtDbPPutNumCr(dbpunti,statistica_sked.grandezze_mem);
         stat_proc = RtDbPGetPuntAusStat(dbpunti,PREP_F22 - 1);
	 if (stato_processo(stat_proc->pid))
	 {
	    statistica_sked.stato_prepf22 = 1;
	 } else
	 {
	    statistica_sked.stato_prepf22 = 0;
	 }
         stat_proc = RtDbPGetPuntAusStat(dbpunti,SNAPSHOT - 1);
	 if (stato_processo(stat_proc->pid))
	 {
	    statistica_sked.stato_snapshot = 1;
	 } else
	 {
	    statistica_sked.stato_snapshot = 0;
	 }
#if defined BANCO_MANOVRA
	 /* registra lo stato dei processi agg_manovra e agg_scada */
	 for (i = 0; i < MAX_SLAVE + 2; i++)
            {
            stat_proc = RtDbPGetPuntAusStat(dbpunti,AGG_MANOVRA - 1);
	    if (stato_processo(stat_proc->pid))
	       {
	       statistica_sked.stato_agg_manovra[i] = 1;
	       } else
	       {
	       statistica_sked.stato_agg_manovra[i] = 0;
	       }
	    }

	 for (i = 0; i < MAX_SLAVE + 1; i++)
            {
            stat_proc = RtDbPGetPuntAusStat(dbpunti,
				AGG_MANOVRA + i + MAX_SLAVE + 2);
	    if (stato_processo(stat_proc->pid))
	    {
	       statistica_sked.stato_agg_manovra_pert[i] = 1;
	    } else
	    {
	       statistica_sked.stato_agg_manovra_pert[i] = 0;
	    }
	    }

         stat_proc = RtDbPGetPuntAusStat(dbpunti,
				AGG_MANOVRA + 2 * MAX_SLAVE + 3);
	 if (stato_processo(stat_proc->pid))
	    statistica_sked.stato_agg_manovra_stato = 1;
	 else
	    statistica_sked.stato_agg_manovra_stato = 0;

#endif
	 statistica_sked.tempo_cpu = 0;;
	 for (i = 0; i < nmod; i++)
	 {
/*
printf("sked_stato DEBUG: i=%d  ind_task_rest=%d\n",
       i,ind_task_rest); 
*/
            stat_proc = RtDbPGetPuntTaskStat(dbpunti,i);
	    if ((stato_processo(stat_proc->pid) > 0) && (stat_proc->pid > 0))
	    {
/*
   Se una task e' stata fatta ripartire dopo un crash (ind_task_rest!=-1)
   il valore di 'stato_task' e' posto uguale a 2 
*/  
             if(rest_banco_err == 0) {
               if(ind_task_rest==i) {
/*
printf("sked_stato DEBUG: settaggio stato_task = 2!!!!\n");
*/
                  statistica_sked.stato_task[i] = 2; 
                  ind_task_rest = -1;
               }
               else {
	          statistica_sked.stato_task[i] = 1;
               }
             }
	    } else
	    {
	       printf("SKED_STATO abortita task %d\n", i);
	       statistica_sked.stato_task[i] = 0;
	       stato_sked = STATO_ERRORE;
	       RtDbPPutStato(dbpunti,stato_sked);
	       statistica_sked.stato_sked = stato_sked;
	    }
         /* 
		preleva la statistica
	  */
	   statistica_sked.tempi_task[i] = stat_proc->cpu_use;
	   statistica_sked.tempo_cpu += statistica_sked.tempi_task[i];
	 }
         if(rest_banco_err == 1)
            rest_banco_err = 0;
/* Scrive su un file le statistiche */
/*
         ScriviStatistiche(&statistica_sked);
*/
	 memcpy(comando_dispatcher.comando_dispatcher.dati,
		&statistica_sked, sizeof(STATISTICA_SKED));
	 comando_dispatcher.comando_dispatcher.sorgente = SKED;
	 comando_dispatcher.comando_dispatcher.tipo = SKDIS_STATO;
	 comando_dispatcher.comando_dispatcher.num = 0;
	 comando_dispatcher.comando_dispatcher.num_tot = 0;
	 comando_dispatcher.comando_dispatcher.size = sizeof(STATISTICA_SKED);
	 comando_dispatcher.mtype = SKDIS_STATO + 1;
	 /* spedisce il messaggio sulla coda ID_MSG_FROM_SKED */
	 if(msg_snd(id_msg_from_sked, &comando_dispatcher,
		 5 * sizeof(int) + sizeof(STATISTICA_SKED), !IPC_NOWAIT) == (-1)) {
            perror("sked_stato");
         }
         sem_signal_disp(id_sem_disp);
#if defined MAURIC
/* Ripristino stampe id_sem_disp */
   msgctl(id_msg_from_sked, IPC_STAT, &buf);
   messaggi_code = buf.msg_qnum;
printf("sked_stato: id_msg_from_sked  num_msg = %d\ttipo_msg = %d\n",
        messaggi_code, comando_dispatcher.comando_dispatcher.tipo);
   sem_val = semctl(id_sem_disp,0,GETVAL,0);
printf("sked_stato: sem_val = %d\n",sem_val);
   if(sem_val>=5)
      beep();
#endif
	 /* resetta l'operazione eseguita */
	 statistica_sked.operazione_eseguita = ESEGUITO_DEFAULT;
	 statistica_sked.num_operazione = 0;
      }
   }
}



void sked_stato_intermedio()
{
   char            app[MAX_LUN_COMANDI_SKDIS];
   int             i;
   MSG_DISPATCHER  comando_dispatcher;
   int             tipo_comando;
   static int      prima_volta = 1;
   int             messaggi_code = 0;
   int             stato_modificato = 0;
   int app_stato;
   float app_tempo;
   int app_passo_reg;

#if defined MAURIC
   int sem_val;
   struct msqid_ds buf;
#endif

#if defined AIX || ULTRIX
   struct msqid_ds buf;
#endif




   /* notifica al banco e a monit */
   if ((tipo_sked == MASTER) && ((gettim()-tempo_agg_stat_int) > TimeAggStat))
   {
      tempo_agg_stat_int = gettim();
      RtDbPGetStato(dbpunti,&app_stato);
      RtDbPPutStato(dbpunti_ext,app_stato);
      RtDbPGetTime(dbpunti,&app_tempo);
      RtDbPPutTime(dbpunti_ext,app_tempo);
      /* costruisce il messaggio */
      statistica_sked.stato_sked = stato_sked;
      RtDbPGetTime(dbpunti,&(statistica_sked.tempo_sim));
      RtDbPGetDelay(dbpunti,&(statistica_sked.tempo_ritardo));
      RtDbPGetTimeScaling(dbpunti,&(statistica_sked.timescaling_sim));
      RtDbPGetStepScaling(dbpunti,&(statistica_sked.stepscaling_sim));
      RtDbPGetStepCr(dbpunti,&app_passo_reg);
      statistica_sked.passo_reg = app_passo_reg;
      RtDbPGetNumCr(dbpunti,&(statistica_sked.grandezze_mem));
      memcpy(comando_dispatcher.comando_dispatcher.dati,
	     &statistica_sked, sizeof(STATISTICA_SKED));
      comando_dispatcher.comando_dispatcher.sorgente = SKED;
      comando_dispatcher.comando_dispatcher.tipo = SKDIS_STATO_INT;
      comando_dispatcher.comando_dispatcher.num = 0;
      comando_dispatcher.comando_dispatcher.num_tot = 0;
      comando_dispatcher.comando_dispatcher.size = sizeof(STATISTICA_SKED);
      comando_dispatcher.mtype = SKDIS_STATO_INT + 1;
      /* spedisce il messaggio sulla coda ID_MSG_FROM_SKED */
      if(msg_snd(id_msg_from_sked, &comando_dispatcher,
	      5 * sizeof(int) + sizeof(STATISTICA_SKED), !IPC_NOWAIT) == (-1)) {
         perror("sked_stato_intermedio");
      }
      sem_signal_disp(id_sem_disp);

#if defined MAURIC
   msgctl(id_msg_from_sked, IPC_STAT, &buf);
   messaggi_code = buf.msg_qnum;
printf("sked_stato_intermedio: id_msg_from_sked  num_msg=%d\ttipo_msg=%d\n",
        messaggi_code,comando_dispatcher.comando_dispatcher.tipo);
   sem_val = semctl(id_sem_disp,0,GETVAL,0);
printf("sked_stato_intermedio: sem_val = %d\n",sem_val);
#endif
      /* resetta l'operazione eseguita */
      statistica_sked.operazione_eseguita = ESEGUITO_DEFAULT;
      statistica_sked.num_operazione = 0;
   }
}



int ScriviStatistiche(STATISTICA_SKED *ss)
{
FILE *ff;
int ii;

ff=fopen("statistiche_sked.edf","w");
fprintf(ff,"DATI STATISTICHE processo net_sked stati=%d\n",
       ss->stato_sked);
fprintf(ff,"tempo_sim=%f tempo_ritardo=%f timescaling_sim=%f stepscaling=%f\n",
       ss->tempo_sim,
       ss->tempo_ritardo,
       ss->timescaling_sim,
       ss->stepscaling_sim);
fprintf(ff,"grandezze_mem=%d passo_reg=%f tempo_cpu=%f\n",
       ss->grandezze_mem,
       ss->passo_reg,
       ss->tempo_cpu);
fprintf(ff,"MAX_SLAVE+1=%d MAX_MODEL=%d\n",MAX_SLAVE+1,MAX_MODEL);
for(ii=0;ii<MAX_SLAVE+1;ii++)
    fprintf(ff,"  tempi_sked[%d]=%f\n",
             ii,ss->tempi_sked[ii]);
for(ii=0;ii<MAX_MODEL;ii++)
    fprintf(ff,"  tempi_task[%d]=%f  stato_task[%d]=%f\n",
             ii,ss->tempi_task[ii],
             ii,ss->stato_task);
#if defined BANCO_MANOVRA
for(ii=0;ii<MAX_SLAVE+1;ii++)
    fprintf(ff,"  s_agg_manovra[%d]=%d  s_agg_manovra_pert[%d]=%d\n",
                ii,ss->stato_agg_manovra[ii],
                ii,ss->stato_agg_manovra_pert[ii]);
fprintf(ff,"  s_agg_man[MAX_SLAVE+2]=%d  s_agg_man_stato=%d, s_a_scada=%d\n",
        ss->stato_agg_manovra[MAX_SLAVE+2],
        ss->stato_agg_manovra_stato,
        ss->stato_agg_scada);
#endif
fprintf(ff,"  s_snapshot=%d  s_prepf22=%d op_eseguita=%d n_op=%d\n",
        ss->stato_snapshot,
        ss->stato_prepf22,
        ss->operazione_eseguita,
        ss->num_operazione);
fprintf(ff,"****Fine file****\n");
fclose(ff);
}
