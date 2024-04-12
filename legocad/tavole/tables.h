/**********************************************************************
*
*       C Header:               tables.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:32 1996 %
*
**********************************************************************/

/* TABLES.H   header file per l'applicativo TABLES.C
   Versione: 0.1          9.7.92            Buffo & Calleri  */

/* Macro per la creazioni di compound stringhe */
#define CS                      XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

/* Titolo della main window e dell'icona, titolo della dialog box */
#define WINDOW_TITLE   "CALCULATION TABLES"
#define ICON_NAME      "TABLES"
#define DIALOG_TITLE   "FUNCTIONS HISTORY"

/* Massimo numero di righe della scroll-list di history */
#define VISIBLE_ITEMS 	14
#define MAX_ROW_HISTORY	300

/* numero massimo di input ed output */
#define MAX_INPUT_VALUE         10
#define MAX_OUTPUT_VALUE        10

/* Numero massimo di funzioni (toggle button) per ogni tipologia */
/* (vapore, fumi, droghe...) */
#define MAX_TOGGLEB             30

/* Colonne dei widget di testo relativi all'input */
#define MAX_COL_TESTO           15

/* Label dei push button relativi all'input */
#define PB_CLEAR        "Clear"
#define PB_EQUAL        "y=f(x)"

/* costanti relative alle tavole */
#define K_VAPORE	0
#define K_GAS		1


/* Prototipi di funzione: */
/* FUNZIONI */
void crea_main_window();
void componi_menu();
void crea_dialog();
void update_history();
void riempi_form();
void display_toggle_function();
void occulta_bambini();
void chiama_tavH2O();
char *mesg_errore();
extern double calcola( int*, double[], double[], double[],
		       int*, double[], double[] );


/* FUNZIONI DI CALLBACK */
void quit_tables();
void apri_dialog();
void svuota_lista();
void next_text();
void text_verify();
void toggle_on();
void display_results();
void clear_input();
void selez_tavola();

/* Definizione della struttura che deve contenere le informazioni
   necessarie ad identificare ogni funzione di calcolo : 
   nome e descrizione della funzione, numero di input e di output (max.10),
   nomi delle grandezze di input e di output, sigle di tali grandezze,
   puntatore alla funzione che effettua il calcolo termodinamico
   (attualmente CALCOLA.F), parametro da passare a tale funzione 
   (=equivalente ad un case all'interno di un ciclo switch).		    */

typedef struct {
		char    *nome_funzione,
			*descr_funzione;
		int     num_input,
			num_output;
		char    *nomi_input[MAX_INPUT_VALUE],
			*nomi_output[MAX_OUTPUT_VALUE];
		char    *sigle_input[MAX_INPUT_VALUE],
			*sigle_output[MAX_OUTPUT_VALUE];
                void    (*attiva_calcolo)();
                int     param;
	       } Struct_toggle;


