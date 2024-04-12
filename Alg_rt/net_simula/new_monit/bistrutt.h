/**********************************************************************
*
*       C Header:               bistrutt.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Fri Jun  6 13:07:32 1997 %
*
**********************************************************************/
/*
 * include con le definizioni e strutture dati relative alla realizzazione 
 * delle nuove funzionalita' banco istruttore
 */
#ifndef BISTRUTT_H
#define BISTRUTT_H
/*********************************************************************************/
#define MAX_LUN_COMMENTO	40
/**
char commento_sessione[MAX_LUN_COMMENTO];
**/

/*********************************************************************************/
struct malfact_st
   {
   int address;        /* in database, per identificare la variabile    */
   float attuale;      /* valore attuale                                */
	float target;       /* valore target impostato                       */
   float delay;        /* delay allo start                              */
   float durata;       /* durata impostata                              */
   float rampa;        /* gradiente impostato                           */
   };
typedef struct malfact_st MALFACT;

struct fract_st
   {
   int address;        /* in database, per identificare la variabile    */
   float delay;        /* delay allo start                              */
   float durata;       /* durata impostata                              */
   float attuale;      /* valore attuale                                */
   float target;       /* valore target impostato                       */
   float rampa;        /* gradiente impostato                           */
   };
typedef struct fract_st FRACT;


/*********************************************************************************/
#define MAX_VIEW_ENTRY    10
#define CI_VIEW            1     /* preview di snapshot       */
#define BT_VIEW            2     /* preview di backtrack      */

struct var_val_st
	{
	int puntatore;      /* puntatore in database                         */
	float valore;       /* valore della variabile                        */
	};
typedef struct var_val_st VAR_VAL;


struct snap_view_st
	{
	int which;          /* snap o bt                                     */
	int record;         /* n. del record nel file richiesto              */
	int nvar;           /* n. di variabili richieste                     */
	VAR_VAL var_val[MAX_VIEW_ENTRY]; /* strutture puntatore/valore       */
	};
typedef struct snap_view_st SNAP_VIEW;
/*********************************************************************************/
struct archive_req_st
	{
	float t_init;       /* tempo di inizio del set                       */
	float t_end;        /* tempo finale del set                          */
	char  commento[MAX_LUN_COMMENTO]; /* commento impostato              */
	};
typedef struct archive_req_st ARCHIVE_REQ;


#define MAX_LUN_NOME_ARCH  40
struct archive_header_st
	{
	char nome_arch[MAX_LUN_NOME_ARCH]; /* nome del file archivio         */
	float t_init;       /* tempo di inizio del set                       */
   float t_end;        /* tempo finale del set                          */
	char data[8];       /* data di registrazione ggmmmaa                 */
   char  commento[MAX_LUN_COMMENTO]; /* commento impostato              */
	char  sessione[MAX_LUN_COMMENTO]; /* titolo di sessione              */
	int nrec_cr;        /* numero di record cr registrati                */
	int nrec_bt;        /* numero record bt registrati                   */
	int neventi;        /* numero eventi I&T A.L. registrati             */
	int nrec_perf;      /* numero record performance analisys registrati */
	};
typedef struct archive_header_st ARCHIVE_HEADER;

struct archive_list_st
	{
	int n_archivi;      /* numerodegli archivi registrati                */
	ARCHIVE_HEADER *header; /* puntatore agli header degli archivi       */
	};
typedef struct archive_list_st ARCHIVE_LIST;

/*********************************************************************************/
#define MAX_STRINGA_COMANDO 100 
/*char comando[MAX_STRINGA_COMANDO];*/ /* comando da eseguire               */

/*********************************************************************************/
struct crlistvar_st
	{
	int numero;         /* numero di variabili registrate                */
	int *punt;          /* puntatore alla lista degli indirizzi          */
	};
typedef struct crlistvar_st CRLISTVAR;


/*********************************************************************************/
struct stato_tempo_st
	{
	int   stato_sim;    /* stato simulatore                              */
	float tempo_sim;    /* tempo di simulazione                          */
	float tempo_ritardo;/* tempo di ritardo                              */
	};
typedef struct stato_tempo_st STATO_TEMPO;

struct stato_parametri_st
	{
	float timescaling_sim; /* fattore di velocita'                       */
	float maxtime;			  /* max simulation time                        */
	float stepscaling_sim; /* fattore di velocita'                       */
	int   grandezze_mem;   /* numero variabili registrate                */
	int   passo_reg_cr;    /* passo registrazione cont. recording        */
	float passo_reg_bt;    /* passo registrazione backtrack              */
	int   passo_pres_bt;   /* passo presentazione backtrack automatico   */
	};
typedef struct stato_parametri_st STATO_PARAMETRI;

struct stato_esec_st
	{
	float tempo[MAX_MODEL]; /* tempo di cpu dei modelli nell' ultimo passo */
	float t_cpu[MAX_SLAVE]; /* totale cpu impegnata nell' ultimo passo   */
	};
typedef struct stato_esec_st TEMPI_TASK;

struct stato_task_st
	{
	int stato_task[MAX_MODEL]; /* stato attivo-non attivo dei modelli   */
	int stato_sked[MAX_SLAVE]; /* stato attivo-non attivo degli sked    */
	int stato_proc1;           /* stato processo 1 .... etc             */
	};
typedef struct stato_task_st STATO_TASK;

struct stato_operazione_st
	{
   int operazione_eseguita;
   int num_operazione;
	};
typedef struct stato_operazione_st STATO_OPERAZIONE;
                    

struct statistiche_st
	{
	STATO_TEMPO stato_tempo;
	STATO_PARAMETRI stato_parametri;
	TEMPI_TASK tempi_task;
	STATO_TASK stato_task;
	STATO_OPERAZIONE stato_operazione;
	};
typedef struct statistiche_st STATISTICHE;

struct richiesta_stat_st
	{
	int tempo;				  /* se = 1 richiede STATO_TEMPO                */
	int parametri;         /* se = 1 richiede STATO_PARAMETRI            */
	int tempi;             /* se = 1 richiede TEMPI_TASK                 */
	int stato;             /* se = 1 richiede STATO_TASK                 */
	int operazione;        /* se = 1 richiede STATO_OPERAZIONE           */
	int statistiche;       /* se = 1 richiede STATISTICHE                */
	};
typedef struct richiesta_stat_st RICHIESTA_STAT;
/*********************************************************************************/
#define MAX_LUN_NOME_SCEN 	100
#define MAX_SCENARI 	      50

struct scen_header_st
	{
	char nome_file[MAX_LUN_NOME_SCEN];  /* nome del file                 */
	int numvar;         /* numero delle variabili nello scenario         */
	char data[8];       /* data di registrazione ggmmmaa                 */
	float t_sim;         /* tempo di simulazione della registrazione      */
	char commento[MAX_LUN_COMMENTO]; /* commento associato allo scenario */
	char  sessione[MAX_LUN_COMMENTO]; /* titolo di sessione              */
	};
typedef struct scen_header_st SCEN_HEADER;

#define MAX_VAR_SCENARIO	30

#define ACTIVATION		0			/* richiesta di attivazione				*/
#define DEACTIVATION		1			/* richiesta la disattivazione			*/

#define SELECTED			0			/* variabile solo in elenco				*/
#define INSERTED			1			/* e' stata richiesta l' attivazione   */
#define ACTIVE				2			/* ha raggiunto il valore target			*/
#define REMOVED			3			/* e' stata richiesta la disattivazione*/

struct record_scenario_st
	{
	int valido;         /* se = 1 il record e' occupato                  */
	int non_configurata;/* se != 0 la var. in sommario non e' configurata*/
	char label[MAX_LUN_NOME_VAR]; /* variabile principale						*/

	int stato;			  /* stato attuale 0=select 1=lanciata 2=attiva		*/
	int stato_prec;	  /* stato precedente										*/
	int punt_comp;      /* puntatore in m_component                      */

	int p_main_var;	  /* puntatore in memoria main var						*/
	int p_sec1_var;	  /* puntatore in memoria var sec 1						*/
	int p_sec2_var;	  /* puntatore in memoria var sec 2                */
	int p_sec3_var;	  /* puntatore in memoria var sec 3                */
	int p_sec4_var;	  /* puntatore in memoria var sec 4                */

	float delay;        /* ritardo alla attivazione                      */
	float durata;       /* durata in secondi dell' attivazione           */
	int durataInf;		  /* se = 0 durata infinita								*/
	float time_to;      /* tempo entro il quale fare variazione (rampa)  */

	float target;       /* valore finale variabile principale            */
	float valSec1;			/* valore target della variabile secondaria 1   */
	float valSec2;			/* valore target della variabile secondaria 2   */
	float valSec3;			/* valore target della variabile secondaria 3   */
	float valSec4;			/* valore target della variabile secondaria 4   */

	int tipoPert1;			/* tipo perturbazione variabile secondaria 1    */
	int tipoPert2;			/* tipo perturbazione variabile secondaria 2    */
	int tipoPert3;			/* tipo perturbazione variabile secondaria 3    */
	int tipoPert4;			/* tipo perturbazione variabile secondaria 4    */
	};
typedef struct record_scenario_st REC_SCENARIO;


struct scenario_st
	{
	SCEN_HEADER scen_header;  /* header dello scenario                   */
	REC_SCENARIO rec[MAX_VAR_SCENARIO];  /* records registrati           */
	};
typedef struct scenario_st SCENARIO;

struct file_scen_malf_st
   {
   int n;         /* numero degli scenari registrati        */
	int valido[MAX_SCENARI];   /* se = 1 = occupato       */
   SCENARIO s[MAX_SCENARI];   /* struttura scenari       */
   };
typedef struct file_scen_malf_st SCENARI;

struct genpert_st
	{
	int tipo_pert;            /* tipo della perturbazione                */
	REC_SCENARIO rec_scenario;
	};
typedef struct genpert_st GENPERT;
/*********************************************************************************/
/*
 * da definire in modo particolareggiato durante lo sviluppo della grafica
 */
struct options_st
	{
	short step_button;          /* se = 1 presente                         */
	short archivio_button;      /* se = 1 presente                         */
	short registrazioni_button; /* se = 1 presente                         */
	short malffrem_button;      /* se = 1 presente                         */
	short view_button;          /* se = 1 presente                         */
	short init_da_ci;           /* se = 1 abilitato                        */
	short init_da_bt;           /* se = 1 abilitato                        */
	short init_clear;           /* se = 1 presente                         */
	short archivi_edit;         /* se = 1 abilitato                        */
	short snapshot_edit;        /* se = 1 abilitato                        */
	};
typedef struct options_st OPTIONS;
/*******************************************************************************
**/
#endif
