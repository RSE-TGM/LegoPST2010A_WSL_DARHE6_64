/**********************************************************************
*
*       C Header:               autodoc.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 11:50:34 1996 %
*
**********************************************************************/
/*** file autodoc.h : header file documentazione automatica ***/

/****
#define F_OK 	0  * per porting Alpha *
****/


/* Macro per la creazioni di compound stringhe */
#ifndef AUTODOC_INCLUDE
#define AUTODOC_INCLUDE


#define CH_SET                   XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR(string,CH_SET))

#define TITOLO_DATI_GEOMETRICI	"GEOMETRICAL DATA OF THE BLOCK"
#define TITOLO_VARIABILI	"IN / OUT VARIABLES OF THE BLOCK"
#define TITOLO_STEADY_STATE_VER	"STEADY STATE VERSION COMPARISON"

#define ALTEZZA_TEXT 35

/* valore campo flag struttura InfoBlock */
#define DATI_GEOMETRICI		0
#define VARIABILI  	        1  /* var. con i valori del f14 del modello */
#define VARIABILI_N_F14	        2  /* var. con i valori di piu' f14 */
#define COMMENTO		3

/* numero massimo colonne foglio orizzontale e verticale */
#define MAX_COL_HOR	132
#define MAX_COL_VER	79

/* Tipo stampante */
#define	PRINTER_ASCII		0
#define PRINTER_POSTSCRIPT	1

/* Percorso dei file utilizzati */
#define FILE_F01		"f01.dat"
#define FILE_F14		"f14.dat"

/* tipo documentazione */
#define DOC_DATI		0
#define DOC_VARIABILI		1
#define DOC_STAZIONARI		2

#define DOC_DATI_MODELLO       	"dati_geometrici.doc"
#define IND_DATI_MODELLO	"ind_dati.doc"
#define FILE_INFO_DATI		"dati_geometrici.info"

#define DOC_VAR_MODELLO       	"variabili.doc"
#define IND_VAR_MODELLO		"ind_vari.doc"
#define FILE_INFO_VAR		"variabili.info"

#define DOC_SSTATE_MODELLO     	"steady_states.doc"

#define FILE_NOTE_MODELLO	"models_note.dat"

#define FILE_PRINT_CONFIG	"print.cfg"

#define MAX_LINEE_NOTE	100
#define MAX_NUM_BLOCCHI 1000
#define MAX_NUM_VAR     250
#define N_UNITA_MISURA	14
#define APPENDICE_1	"Appendice 1: Significato dei simboli"
#define APPENDICE_2A	"Appendice 2: Note di calcolo"
#define APPENDICE_2B	"Appendice 2: Note generali"

/* nomi dei settaggi per stampante */
#define NERETTO_ON	0
#define NERETTO_OFF	1
#define LANDSCAPE	2
#define PORTRAIT	3
#define SOFT_RESET	4
/*#define SHS_12		5*/
#define MARG_8_79	5
#define MARG_1_132	6
#define FORM_FEED	7

/* definizione delle strutture dati utilizzate */
typedef char byte;

/****************************************************************************/
/* struttura che contiene i dati relativi ai blocchi nel file f14.dat e */
/* f01.dat. Tale struttura viene creata e compilata all'inizio del programma. */
typedef struct {
		   char nome[9], descr[51]; /* nome del blocco e descrizione */
                   char nome_mod[5]; /* nome del modulo */
		   long offs_f01, offs_f14; /* posizione del record relativo */
					    /* al blocco nei file f01 e f14 */
               } ModelBlockStruct;

/* struttura per gestire una lista. */
/* La lista contiene gli swidget delle window delle informazioni aggiuntive */
/* (dati o variabili) aperte per consentire l'aggiornamento immediato delle */
/* unita' di misura e dei valori delle variabili ogni qual volta vengono */
/* modificate */
struct window_info_struct {
			     byte flag;
			     swidget swindow;
                             struct window_info_struct *next;
                          };

typedef struct window_info_struct WindowInfoStruct;

/****************************************************************************/

/* struttura che contiene le informazioni (nomi di variabili o dati, label e */
/* text, ecc.) degli oggetti contenuti nella scrolled window della */
/* window delle informazioni aggiuntive */
typedef struct {
                  char nome[9];
                  Widget wnome, source, rel, pag, data;
                  Widget unita, valore[5];
                  char tipo_e_descr[60];
                  double val_mks[5];
                  byte num_valori;
               } WBVar;

typedef struct {
                  char nome[9];
                  Widget wnome, source, rel, pag, data;
                  Widget nota, pb_nota;
                  swidget win_note;
                  Boolean open_win;
               } WBData;
		   

typedef union {
                WBData data;
                WBVar  vars;
              }  WidgetBlock;

/****************************************************************************/

/* strutture che contengono le informazioni recuperate dai file di dati */
/* f01.dat e/o f14.dat */
typedef struct {
                  byte flag;
                  char nome[9], valore[12], sorgente[28], release[5],
                       pagina[4], data[9], note[6];
               } BlockData;

typedef struct {
                  byte flag;
                  byte noto;
                  char nome[9], tipovar[3], descrizione[51], valore[12],
                       sorgente[28], release[5], pagina[4], data[9];
                  double fval_mks;
		  char blocco_co[9]; /* nome del blocco a cui e' collegato */
		  char old_name[9]; /* nome prima della connessione */
               } BlockVar; /* valori recuperati dal file f14 del modello */

typedef struct {
                  byte flag;
                  byte noto;
                  char nome[9], nome_blk[9], tipovar[3], descrizione[51],
                       valori[5][12];
                  double fval_mks[5];
                  byte num_valori;
               } BlockVarNmod;  /* valori recuperati da + file f14.dat */

typedef struct {
                  byte flag;
                  char commento[81];
               } Comment;

typedef union {
                 byte flag;
                 Comment comment;
                 BlockData dati;
                 BlockVar var;
                 BlockVarNmod varN;
              } InfoBlock;

/****************************************************************************/

/* Posizionamento e settaggi degli oggetti contenuti nella scrolled-window */
/* delle informazioni aggiuntive */
typedef struct {
		   char intestazione[21];
		   int leftpos, rightpos, num_col;
                   Boolean editable;
               } TextWidgetPos;

/****************************************************************************/

/* struttura che contiene i titoli ed i percorsi delle versioni del calcolo */
/* dello stazionario */
typedef struct {
		    char titolo[16];
		    char percorso[256];
                    byte abilitato;
	       } StructVarianti;

/****************************************************************************/

/* prototipi di funzioni */
char *taglia();
char *dim_unita_misura();

int update_blocks_list();
int leggi_record_f14();
int leggi_var_f01();
int copia_valori();
int setta_nome_modello();
int crea_label();
int copia_testo_nota();
int get_blocchi_modello();

long cerca_var_co();
long cerca_blocco_info();

Widget crea_text();
Widget crea_labelG();
Widget crea_pb_note();
Widget crea_toggle();
Widget crea_opt_menu_unita();

#ifndef DESIGN_TIME
WindowInfoStruct *new_struct_info();
#endif

Pixmap crea_pixmap();

Pixel get_colore();

swidget create_autodoc_shell();
swidget create_info_ashell();
swidget create_window_notes();
swidget create_window_models();
swidget create_window_unita();
swidget create_form_modi_unita();
swidget create_dialog_print_config();
swidget create_ashell_print();
swidget create_bb_conferma_print();
swidget crea_errorDialog();
swidget create_bb_cambia_pag();

double converti_val();
double ascii_to_float();

void cerca_descr_f01();
void esamina_rec_f14();
void copia_descr_var();
void cambio_dim_window();
void blocco_selezionato();
void info_aggiuntive();
void copia_str(char *, char *, char , int );
void conferma_note_inserite();
void recupera_nota_blocco();
void callback_note();
void callback_toggle();
void callback_ins_nota();
void cambia_dim_unita();
void setta_toggle();
void setta_label_int();
void set_label();
void chiudi_info_ashell();
void aggiorna_unita_misura();
void cambia_dim_unita();
void find_var_name();
void *realloc_mem();
void *calloc_mem();

void StampaIntestDati();
void FinePagina();
void StampaStrInTabella();
void StampaTrattoOrizzontale();
void StampaRiga();
void StampaIntestVar();
void StampaIntestConnect();
void dealloca_note();

char *StampaNota();
char *cerca_descr_blocco();

char *leggi_pagina();

long vai_alla_pagina();
long pagina_prec();
long pagina_succ();


void lcDestroySwidget(Widget);
void free(void *);
int confronta_date(char*, char*);
int crea_docdati(int*, int*);

int conta_pagine_doc(char*, int);
int crea_docvar(int*, int*);
int crea_sstate_doc(int*);
 

#include "note.h"

#endif

/* fine autodoc.h */
