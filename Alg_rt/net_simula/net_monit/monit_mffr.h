/**********************************************************************
*
*       C Header:               monit_mffr.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:16:47 1996 %
*
**********************************************************************/
/*
   modulo monit_mffr.h
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)monit_mffr.h	5.1
*/
#if defined MFFR
/* ***************** definizione variabili globali ***************** */
#define NUM_COLORI 12
extern Pixel pix_val[NUM_COLORI];
Pixel colore_sfondo;
Pixel colore_sfondo_fr;
Pixel colore_tabelle;
Pixel colore_tabelle_fr;
Pixel colore_scrollbar;
Pixel colore_scrollbar_fr;
Pixel colore_tasti;
Pixel colore_tasti_fr;
Pixel colore_selezionato;
Pixel colore_selezionato_fr;
Pixel colore_inserito;
Pixel colore_attivato;

/********************************************************************/
#define tasto_att      "ATTIVAZIONE"
#define tasto_dis      "DISATTIVAZIONE"
#define tasto_del      "CANCELLAZIONE"
#define tasto_add      "SELEZIONE"
#define tasto_exit      "USCITA"

/********************************************************************/
#define file_elenco_sistemi  "ELENCO_SIST.DAT"
#define nome_modello_mffr    "PRIMF000"
#define nome_blocco_malf     "MALFMALF"
#define nome_blocco_frem     "FREMFREM"
#define malf_analog          "MA"
#define malf_digital         "MD"
#define frem_analog          "FA"
#define frem_digital         "FD"
#define analog_inp           "YI"
#define analog_out           "YU"
#define digital_inp          "JI"
#define digital_out          "JU"
/************************************************************************/
#define MAX_LUNGH_SIGLA     3  /* 2 char per la sigla di sistema      */
#define MAX_MALF_SIST     200  /* 200 malfunzioni per sistema         */
#define MAX_FREM_SIST     200  /* 200 funz. remote per sistema         */
#define MAX_MF_SOMM      40
#define MAX_FR_SOMM      40
/************************************************************************/
#define direzione_up       "UP"
#define direzione_down     "DOWN"
/************************************************************************/
void label_new();
void label_act();
void delay_new();
void durata_new();
void target_new();
void rampa_new();
void delay_act();
void durata_act();
void target_act();
void rampa_act();
void rampa_fr_new();
void target_fr_new();
void rampa_fr_act();
void target_fr_act();
void label_focus();
void label_losing_focus();
void toggled();
void toggled_fr();
void tasto_mf();
void tasto_fr();
/************************************************************************/
/*
 * definizioni per la grafica
 */
#define y_init_top_label     25
#define y_init_scrolledwin   50
#define y_height_scrolledwin 350
#define y_init_tasti        y_height_scrolledwin + y_init_scrolledwin
/************************************************************************/
/*
 * struttura sommari visualizzati
 */
struct sommario_mf_st
	{
	char label[MAX_MF_SOMM][9];
	char descrizione[MAX_MF_SOMM][MAX_LUN_DESCR_VAR];
	int address[MAX_MF_SOMM];
	float val_def[MAX_MF_SOMM];
	float delay[MAX_MF_SOMM];
	float durata[MAX_MF_SOMM];
	int durata_non_inf[MAX_MF_SOMM];  /* 0 = durata infinita    */
	float rampa[MAX_MF_SOMM];
	float target[MAX_MF_SOMM];
	float attuale[MAX_MF_SOMM];
	char stato[MAX_MF_SOMM][4];
	int marcato[MAX_MF_SOMM];
	int occupato[MAX_MF_SOMM];
	int da_riattivare[MAX_MF_SOMM];
	int delay_in_modifica[MAX_MF_SOMM];
	int durata_in_modifica[MAX_MF_SOMM];
	int numero;
	};
typedef struct sommario_mf_st SOMMARIO_MF;

struct sommario_fr_st
   {
   char label[MAX_FR_SOMM][9];
   char descrizione[MAX_FR_SOMM][MAX_LUN_DESCR_VAR];
	int address[MAX_FR_SOMM]; 
   float val_def[MAX_FR_SOMM];
   float rampa[MAX_FR_SOMM];
   float target[MAX_FR_SOMM];
   float attuale[MAX_FR_SOMM];
   char stato[MAX_FR_SOMM][4];
   int marcato[MAX_FR_SOMM];
	int occupato[MAX_FR_SOMM];
	int da_riattivare[MAX_FR_SOMM];
	int numero;
   };
typedef struct sommario_fr_st SOMMARIO_FR;
/************************************************************************/
#define DELAY_DEFAULT    0.0
#define DURATA_DEFAULT   0.0
#define RAMPA_DEFAULT    0.0
#define TARGET_DEFAULT   0.0
#define SELEZIONATO      "SEL"
#define INSERITO         "INS"
#define ATTIVATO         "ATT"
#define DISATTIVATO      "DIS"
#define MARCATO          1
#define NON_MARCATO      0
#define OCCUPATO         1
#define NON_OCCUPATO     0
#define DELAY_ALLA_RIATTIVAZIONE   5
/************************************************************************/
#define MAX_VARIABILI 	MAX_MF_SOMM+MAX_FR_SOMM
struct updvar_st
	{
	int indirizzo;
	float valore;
	};
typedef struct updvar_st UPDVAR;

struct aggiorna_valori_sommario_st
	{
	int n;             /* numero di variabili richieste       */
	UPDVAR updvar[MAX_VARIABILI];
	};
typedef struct aggiorna_valori_sommario_st AGGIORNA_VALORI;
/************************************************************************/
/*
 * messaggi di errore
 */
#define NON_IN_STOP "OPERAZIONE NON PERMESSA NELLO STATO STOP"
#define GIA_IN_SOMMARIO "VARIABILE GIA' INSERITA IN SOMMARIO"
#define VALORE_NON_CORRETTO "VALORE IN DATABASE NON CORRETTO"
#define FILE_NOT_FOUND "FILE NON ESISTENTE"
#define NIENTE_SISTEMI "NON E' POSSIBILE GENERARE LA LISTA DEI SISTEMI"
/************************************************************************/
#endif
