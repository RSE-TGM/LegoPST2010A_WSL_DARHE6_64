/**********************************************************************
*
*       C Header:               xaing.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Tue Jun 18 14:39:00 1996 %
*
**********************************************************************/
/*
   modulo xaing.h
   tipo 
   release 1.11
   data 6/3/96
   reserved @(#)xaing.h	1.11
*/
/*
 *  XAING.H
 *     header per l'applicativo xstaz: contiene i dimensionamenti e
 *     le strutture dati utilizzate
 */

#define LUN_NOME_VAR 8
#define LUN_DES_VAR  80
#define LUN_NOME_MOD 8
#define LUN_UMIS     6
#define LUN_SIMB69   69

#define NUM_WIDGET_AING 71 /* numero dei widget figli della
                              stazione il cui indice deve essere
                              memorizzato per permettere operazioni
                              successive */

#define MAX_VALORE 999999999999999999.0 /* massimo valore inseribile */

#define TIPO_PERT_NORMAL	1
#define TIPO_PERT_PERIODIC	2
#define TIPO_PERT_WHITENOISE	3
#define TIPO_PERT_MALFUNCTION	4

#define MAX_AING 10    /* massimo numero di stazioni AING visualizzate */

typedef void (*xaingcallbackproc)(void *);

typedef struct XaingCallback_st{
	xaingcallbackproc  callback;
	void * closure;
	}XaingCallback;

typedef struct s_aing{
	int attiva;      /* indica se la stazione AING e' visualizzata */
	Widget wtopLevel;
	Widget w;	 /* indice di widget della stazione */
	Widget sw[NUM_WIDGET_AING]; /* indici dei widget figli della
                                       stazione */
	int ind_var;   /* indice variabile nella lista var.per attuaz. */
	char nome_display[100];  /* nome del display dove e' vis. la finestra */
	char nome_var[LUN_NOME_VAR+1];
	char descrizione_v[LUN_DES_VAR+1];
	char umis[LUN_UMIS+1];
	char nome_mod[LUN_NOME_MOD+1];
	int select;
	int modello;
	int x;
	int y;
	float a;  /* coefficiente per conversione unita' di misura */
	float b;  /* costante per conv. unita' di misura */
	int flag_rampa;  /* indica se e' definita una rampa */
	int flag_impulso;  /* indica se e' definito un impulso */
	float valore;  /* valore corrente */
	float val_imp; /* valore finale dell'impulso */
	float tempo_imp; /* durata dell'impulso */
	float valfin;  /* valore finale rampa */
	float rateo;   /* incremento della rampa */
	float valt;    /* tempo della perturbazione */
	int ists;      /* stato della rampa (se in START o in STOP) */
	int isegn;     /* segno della rampa */
        int grad_dt_time;
        int delta_time;
	int legocad;	/* verifica interfaccia legocad */
	int tipo_pert;
	} S_AING;


#define k_val_corr 0  /* indice nell'array dei widget figli
                         del widget in cui e' visualizzato
                         il valore corrente */
#define k_delay    1
#define k_val_step 2  /* indice del widget di testo per
                         introduzione valore di step */

#define k_val_finale 3
#define k_val_grad   4
#define k_but_invia  5
#define k_but_start  6
#define k_but_stop   7
#define k_but_imp    8
#define k_but_impstop    9
#define k_val_imp    10
#define k_tempo_imp 11
#define k_not       12
#define k_updown    13
#define k_rampa_option    14
#define k_rampa_grad      15
#define k_rampa_time      16
#define k_rampa_delta     17
#define k_rampa_pull      18
#define k_time_option    19
#define k_time_time      10
#define k_time_delta     21
#define k_time_tinc     22
#define k_time_pull      23
#define k_tipo_option	 24
#define k_tipo_pull	 25
#define k_tipo_normal	 26
#define k_tipo_periodic	 27
#define k_string_step 		29
#define k_string_pulse 		30
#define k_string_ramp 		31
#define k_string_targetstep	32
#define k_string_targetimp	33
#define k_string_targetramp	34
#define k_string_wide_s		35
#define k_string_min		36
#define k_string_general	37
#define k_string_sinusoidal	38
#define k_string_trapezoidal	39
#define k_sin_start 		40
#define k_sin_stop		41
#define k_trap_start 		42
#define k_trap_stop		43
#define k_string_period		44
#define k_string_phase		45
#define k_string_meanvalue	46
#define k_string_wide		47
#define k_text_period		48
#define k_text_phase		49
#define k_text_meanvalue	50
#define k_text_wide		51
#define k_string_t1		52
#define k_string_t2		53
#define k_string_t3		54
#define k_text_t1		55
#define k_text_t2		56
#define k_text_t3		57
#define k_tipo_noise		58
#define k_string_variance	59
#define k_text_variance		60
#define k_whitenoise_start 	61
#define k_whitenoise_stop	62
#define k_string_whitenoise	63
#define k_quit      	 	70

#define k_tipo_option_malf      71
#define k_tipo_malfunction      72  /* Forse dovrebbe essere 28 */  

#define k_string_malfunction    73
#define k_string_targetmalf     74
#define k_string_typemalf       75
#define k_text_targetmalf       76
#define k_text_typemalf         77
#define k_malfunction_start     78
#define k_malfunction_stop      79


typedef struct voce_pert {
                    int ind;  /* indice in widget_array
                                 della voce pert */
                    int stato;  /* stato della voce: True, False
                                 */
                        } VOCE_PERT;


#define NUMERO_VOCI	57


static VOCE_PERT voce_normal[]={
			{k_val_step,True},
			{k_val_finale,True},
			{k_val_grad,True},
			{k_but_invia,True},
			{k_but_start,True},
			{k_but_stop,True},
			{k_but_imp,True},
			{k_but_impstop,True},
			{k_val_imp,True},
			{k_tempo_imp,True},
			{k_not,True},
			{k_updown,True},
			{k_rampa_option,True},
			{k_rampa_grad,True},
			{k_rampa_time,True},
			{k_rampa_delta,True},
			{k_string_step,True},
			{k_string_pulse,True},
			{k_string_ramp,True},
			{k_string_targetstep,True},
			{k_string_targetimp,True},
			{k_string_targetramp,True},
			{k_string_wide_s,True},
			{k_string_min,True},
			{k_string_general,False},
			{k_string_sinusoidal,False},
			{k_string_trapezoidal,False},
			{k_sin_start,False},
			{k_sin_stop,False},
			{k_trap_start,False},
			{k_trap_stop,False},
			{k_string_period,False},
			{k_string_phase,False},
			{k_string_meanvalue,False},
			{k_string_wide,False},
			{k_text_period,False},
			{k_text_phase,False},
			{k_text_meanvalue,False},
			{k_text_wide,False},
			{k_string_t1,False},
			{k_string_t2,False},
			{k_string_t3,False},
			{k_text_t1,False},
			{k_text_t2,False},
			{k_text_t3,False},
			{k_string_variance,False},
			{k_text_variance,False},
			{k_whitenoise_start ,False},
			{k_whitenoise_stop,False},
			{k_string_whitenoise,False},
		{k_string_malfunction,False},
		{k_string_targetmalf,False},
		{k_string_typemalf,False},
		{k_text_targetmalf,False},
		{k_text_typemalf,False},
		{k_malfunction_start ,False},
		{k_malfunction_stop,False},
			};

static VOCE_PERT voce_periodic[]={
			{k_val_step,False},
			{k_val_finale,False},
			{k_val_grad,False},
			{k_but_invia,False},
			{k_but_start,False},
			{k_but_stop,False},
			{k_but_imp,False},
			{k_but_impstop,False},
			{k_val_imp,False},
			{k_tempo_imp,False},
			{k_not,False},
			{k_updown,False},
			{k_rampa_option,False},
			{k_rampa_grad,False},
			{k_rampa_time,False},
			{k_rampa_delta,False},
			{k_string_step,False},
			{k_string_pulse,False},
			{k_string_ramp,False},
			{k_string_targetstep,False},
			{k_string_targetimp,False},
			{k_string_targetramp,False},
			{k_string_wide_s,False},
			{k_string_min,False},
			{k_string_general,True},
			{k_string_sinusoidal,True},
			{k_string_trapezoidal,True},
			{k_sin_start,True},
			{k_sin_stop,True},
			{k_trap_start,True},
			{k_trap_stop,True},
			{k_string_period,True},
			{k_string_phase,True},
			{k_string_meanvalue,True},
			{k_string_wide,True},
			{k_text_period,True},
			{k_text_phase,True},
			{k_text_meanvalue,True},
			{k_text_wide,True},
			{k_string_t1,True},
			{k_string_t2,True},
			{k_string_t3,True},
			{k_text_t1,True},
			{k_text_t2,True},
			{k_text_t3,True},
			{k_string_variance,False},
			{k_text_variance,False},
			{k_whitenoise_start ,False},
			{k_whitenoise_stop,False},
			{k_string_whitenoise,False},
		{k_string_malfunction,False},
		{k_string_targetmalf,False},
		{k_string_typemalf,False},
		{k_text_targetmalf,False},
		{k_text_typemalf,False},
		{k_malfunction_start ,False},
		{k_malfunction_stop,False},
			};

static VOCE_PERT voce_noise[]={
			{k_val_step,False},
			{k_val_finale,False},
			{k_val_grad,False},
			{k_but_invia,False},
			{k_but_start,False},
			{k_but_stop,False},
			{k_but_imp,False},
			{k_but_impstop,False},
			{k_val_imp,False},
			{k_tempo_imp,False},
			{k_not,False},
			{k_updown,False},
			{k_rampa_option,False},
			{k_rampa_grad,False},
			{k_rampa_time,False},
			{k_rampa_delta,False},
			{k_string_step,False},
			{k_string_pulse,False},
			{k_string_ramp,False},
			{k_string_targetstep,False},
			{k_string_targetimp,False},
			{k_string_targetramp,False},
			{k_string_wide_s,False},
			{k_string_min,False},
			{k_string_general,False},
			{k_string_sinusoidal,False},
			{k_string_trapezoidal,False},
			{k_sin_start,False},
			{k_sin_stop,False},
			{k_trap_start,False},
			{k_trap_stop,False},
			{k_string_period,False},
			{k_string_phase,False},
			{k_string_meanvalue,True},
			{k_string_wide,False},
			{k_text_period,False},
			{k_text_phase,False},
			{k_text_meanvalue,True},
			{k_text_wide,False},
			{k_string_t1,False},
			{k_string_t2,False},
			{k_string_t3,False},
			{k_text_t1,False},
			{k_text_t2,False},
			{k_text_t3,False},
			{k_string_variance,True},
			{k_text_variance,True},
			{k_whitenoise_start ,True},
			{k_whitenoise_stop,True},
			{k_string_whitenoise,True},
		{k_string_malfunction,False},
		{k_string_targetmalf,False},
		{k_string_typemalf,False},
		{k_text_targetmalf,False},
		{k_text_typemalf,False},
		{k_malfunction_start ,False},
		{k_malfunction_stop,False},
			};

static VOCE_PERT voce_malf[]={
			{k_val_step,False},
			{k_val_finale,False},
			{k_val_grad,False},
			{k_but_invia,False},
			{k_but_start,False},
			{k_but_stop,False},
			{k_but_imp,False},
			{k_but_impstop,False},
			{k_val_imp,False},
			{k_tempo_imp,False},
			{k_not,False},
			{k_updown,False},
			{k_rampa_option,False},
			{k_rampa_grad,False},
			{k_rampa_time,False},
			{k_rampa_delta,False},
			{k_string_step,False},
			{k_string_pulse,False},
			{k_string_ramp,False},
			{k_string_targetstep,False},
			{k_string_targetimp,False},
			{k_string_targetramp,False},
			{k_string_wide_s,False},
			{k_string_min,False},
			{k_string_general,False},
			{k_string_sinusoidal,False},
			{k_string_trapezoidal,False},
			{k_sin_start,False},
			{k_sin_stop,False},
			{k_trap_start,False},
			{k_trap_stop,False},
			{k_string_period,False},
			{k_string_phase,False},
			{k_string_meanvalue,False},
			{k_string_wide,False},
			{k_text_period,False},
			{k_text_phase,False},
			{k_text_meanvalue,False},
			{k_text_wide,False},
			{k_string_t1,False},
			{k_string_t2,False},
			{k_string_t3,False},
			{k_text_t1,False},
			{k_text_t2,False},
			{k_text_t3,False},
			{k_string_variance,False},
			{k_text_variance,False},
			{k_whitenoise_start ,False},
			{k_whitenoise_stop,False},
			{k_string_whitenoise,False},
		{k_string_malfunction,True},
		{k_string_targetmalf,True},
		{k_string_typemalf,True},
		{k_text_targetmalf,True},
		{k_text_typemalf,True},
		{k_malfunction_start ,True},
		{k_malfunction_stop,True},
			};

/*
        define per l'utilizzo multi-display
*/
typedef struct an_display{
                char nome[100];
                Widget topLevel;
                Widget wb;
                        } AN_DISPLAY;

#define MAX_DISPLAY 30


#define XlNnumDisplay              "numDisplay"
#define XlCNumDisplay              "NumDisplay"
#define XlNdisplayList             "displayList"
#define XlCDisplayList             "DisplayList"

