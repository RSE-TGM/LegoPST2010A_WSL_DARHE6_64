/**********************************************************************
*
*       C Source:               sked_prolog.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 15:57:56 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_prolog.c-11 %  (%full_filespec: sked_prolog.c-11:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_prolog.c	5.1\t11/7/95";
/*
   modulo sked_prolog.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_prolog.c	5.1
*/
# include <stdio.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>
# include <Rt/RtMemory.h>
#include <statistics.h>


extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1 */

extern int      stato_sked;


SNTAB  *snapshot_hea;			/* area shm per tabella snapshot */
int size_area_dati;	/* size in byte dell'area dati di tutte le task */
float *area_dati;        /* puntatore all'inizio dell'area dati delle task */
float *area_dati_ext;    /* puntatore all'inizio dell'area dati delle task */

#if defined BACKTRACK
BKTAB  *backtrack_hea;			/* area shm per tabella backtrack   */
#endif


#if defined SAVEPERT
FILE           *fp_pert;	/* puntatore file perturbazioni */
#endif

int             id_sh;		/* identificatore sh_var */
VARIABILI      *variabili;	/* database variabili di tutti i modelli */
char           *ind_sh_top;	/* puntatore inizio shared memory sh_var */


int             shr_usr_key;	/* chiave utente per shared  */
extern int      shmvid;		/* identificativo shm  varabili */

extern          slot_snap[MAX_VAL_SNAP];	/* indirizzi delle variabili
						 * caratteristiche degli
						 * snapshot */

STATO_CR        stato_cr;	/* struttura contenete lo stato dei backtrack
				 * e degli snapshot */

#if defined BACKTRACK
extern          slot_bktk[MAX_VAL_SNAP];	/* indirizzi delle variabili
						 * caratteristiche dei
						 * backtrack */
#endif
extern double   tempo_sim;	/* tempo della simulazione */
extern double   tempo_reale;	/* tempo reale   */
double          tempo_iniziale;	/* tempo iniziale della simulazione */
extern double   tempo_freeze;	/* tempo per conteggio freeze  */
extern double   ritardo_sim;	/* ritardo accumulato */
extern float    velocita;
extern float    passo_grafica;	/* passo registrazione grafica */
extern float    passo_legograf;	/* passo aggiornamento legograf su macchina
				 * MASTER   */
float           fattore_step = 1;	/* fattore moltiplicativo del passo
					 * di tempo                           */
extern int    _MAX_SNAP_SHOT;
extern int    _MAX_BACK_TRACK;
extern int    _MAX_CAMPIONI;
extern int    _NUM_VAR;
extern int    _MAX_PERTUR;
extern int    _SPARE_SNAP;
extern int    _PERT_CLEAR;


RtDbPuntiOggetto dbpunti;
RtDbPuntiOggetto dbpunti_ext;
RtErroreOggetto errore;


sked_prolog()
{
int        k;
FILE      *fp;
int        num;
float      tempo;
SIMULATOR *simpar;

   simpar = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
   simpar->max_snap_shot  = _MAX_SNAP_SHOT;
   simpar->max_back_track = _MAX_BACK_TRACK;
   simpar->max_campioni   = _MAX_CAMPIONI;
   simpar->num_var        = _NUM_VAR;
   simpar->max_pertur     = _MAX_PERTUR;
   simpar->spare_snap     = _SPARE_SNAP;
   simpar->pert_clear     = _PERT_CLEAR;

   /* decodifica SHR_USR_KEY */
   shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));

   /* aggancio al database dei punti */
   errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_sked");
#if defined SCO_UNIX
   dbpunti = RtCreateDbPunti(errore,"S02_SCO",DB_PUNTI_INT,simpar);
   dbpunti_ext = RtCreateDbPunti(errore,"S02_SCO",DB_PUNTI_SHARED,simpar);
#endif
#if defined OSF1
   dbpunti = RtCreateDbPunti(errore,"S02_OSF1",DB_PUNTI_INT,simpar);
   dbpunti_ext = RtCreateDbPunti(errore,"S02_OSF1",DB_PUNTI_SHARED,simpar);
#endif
#if defined AIX
   dbpunti = RtCreateDbPunti(errore,"S02_AIX",DB_PUNTI_INT,simpar);
   dbpunti_ext = RtCreateDbPunti(errore,"S02_AIX",DB_PUNTI_SHARED,simpar);
#endif
#if defined VMS
   dbpunti = RtCreateDbPunti(errore,"S02_VMS",DB_PUNTI_INT,simpar);
   dbpunti_ext = RtCreateDbPunti(errore,"S02_VMS",DB_PUNTI_SHARED,simpar);
#endif
#if defined LINUX
   dbpunti = RtCreateDbPunti(errore,"S02_LINUX",DB_PUNTI_INT,simpar);
   dbpunti_ext = RtCreateDbPunti(errore,"S02_LINUX",DB_PUNTI_SHARED,simpar);
#endif

   free(simpar);

   /* azzeramento shared memory */
   RtDbPClearData(dbpunti);
   RtDbPClearData(dbpunti_ext);

   /*  recupero il puntatore all'area degli header degli snapshot */
   snapshot_hea = RtDbPGetPuntSnapshot(dbpunti);
   size_area_dati = RtDbPSizeData(dbpunti);
   area_dati = RtDbPPuntData(dbpunti);
   area_dati_ext = RtDbPPuntData(dbpunti_ext);
   /*printf("\nsize_area_dati=%d SNTAB=%d HD=%d SNAP_SKED=%d\n",
        size_area_dati,sizeof(SNTAB),sizeof(HEADER_REGISTRAZIONI),
        sizeof(SNAP_SKED));*/

   /*  recupero il puntatore all'area degli header dei backtrack */
#if defined BACKTRACK
   backtrack_hea = RtDbPGetPuntBacktrack(dbpunti);
#endif

   /* inizializza l'area delle perturbazioni */
   init_area_pert();

   if (tipo_sked == MASTER)
   {
      /* Legge il file Simulator */
      /* si aggancia alla shared memory sh_var */
      costruisci_var(&ind_sh_top, &variabili, &id_sh);
      /* legge la tabella degli snapshot */
#if defined SNAP_PIAC
      snap_tab_read_piac();
#else
      snap_tab_read();
#endif

      /* legge la tabella dei backtrack */
#if defined BACKTRACK
#if defined SNAP_PIAC
      bktk_tab_read_piac();
#else
      bktk_tab_read();
#endif
#endif
   }

   /* inizializzazione degli slot degli snapshot */
   for (k = 0; k < MAX_VAL_SNAP; k++)
      slot_snap[k] = -1;

#if defined BACKTRACK
   /* inizializzazione degli slot dei backtrack */
   for (k = 0; k < MAX_VAL_SNAP; k++)
      slot_bktk[k] = -1;
#endif

   /* lettura stato backtrack e snapshot (se definito BACKTRACK) */
   if (load_stato_cr(&stato_cr) < 0)
      {
      printf("\t\t STATO_CR= %d %d   %d %d \n\n",
             stato_cr.last_snap_save,stato_cr.last_snap_load,
             stato_cr.last_bktk_save,stato_cr.last_bktk_load);
      save_stato_cr(&stato_cr);
      }
#if defined BACKTRACK
   /* inserisce la tacca nell'ultimo backtrack registrato */
   if (tipo_sked == MASTER)
	{
#if defined SNAP_PIAC
   	ins_tacca_bktk_piac(2);
#else
   	ins_tacca_bktk(2);
#endif
	}
#endif
   if (tipo_sked == MASTER)
   {
      sked_tempo_iniziale();
   }
#if defined SAVEPERT
#if defined LEGOCAD
   sked_replay(5);
#else
   sked_replay(3);
#endif
#endif

   /* registra il fattore moltiplicativo del passo di tempo */
   RtDbPPutStepScaling(dbpunti,fattore_step);

}

sked_prolog_code()
{
   /* decodifica SHR_USR_KEY */
   shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));

   /* aggancio semaforo shared memory */
   aggancia_sem_shr();
// printf("prima di msg_create_fam \n");
   msg_create_fam(shr_usr_key, 1);
// printf("dopo di msg_create_fam \n");
}
/* Fine file */
