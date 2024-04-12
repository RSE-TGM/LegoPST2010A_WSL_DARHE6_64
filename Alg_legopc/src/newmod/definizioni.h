/**********************************************************************
*
*       C Header:               definizioni.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Nov  6 15:35:25 1996 %
*
**********************************************************************/

#ifndef DEFINIZIONI_H
#define DEFINIZIONI_H


/* DEFINIZIONI.H header file dell'applicativo librarian
   Versione: 0.1         17.03.93            Buffo & Calleri  */

/* Macro per la creazioni di compound stringhe */
#define CH_SET                   XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR(string,CH_SET))

#define APPLICATION_NAME	"LIBRARIAN"
#define TEST_ENVIRONMENT      "cad_testenv"
#define CREA_ENVIRONMENT      "make -f $LEGO_BIN/cad_environment crea_dir"
#define COPIA_STD_ENVIRONMENT "make -f $LEGO_BIN/cad_environment copia_all"
#define CREA_LIBUT            "make -f $LEGO_BIN/cad_environment crea_libut"
#define CREA_LIBUT_REG        "make -f $LEGO_BIN/cad_environment crea_libut_reg"
#define CREA_LIBREG           "make -f $LEGO_BIN/cad_environment crea_libreg"
#define CREA_LG1              "make -f $LEGO_BIN/cad_maketask lg1"

#ifdef VMS

#define DIR_DOC			".sorgmodu.processo"
#define DIR_STDLIB		".sorgmodu.processo"
#define DIR_STDGRAF		".sorgmodu.lib_graf"

#else

#define DIR_DOC                 "/sorgmodu/processo/"
#define DIR_STDLIB              "/sorgmodu/processo/"
#define DIR_STDGRAF             "/sorgmodu/lib_graf/"

#endif

#define FILE_MODULI_LIBUT       "lista_moduli.dat"
#define FILE_ICONE_LIBGRAF      "icon_list.dat"
#define ICON_LIST_FILE          "icon_list.dat"
#define ICON_STD_FILE           "icon_std.dat"

#define SEZIONE_PREC	0
#define SEZIONE_NEXT	1

/************************************************************************/
/* Definizione costanti e strutture per subroutine NEWMOD               */
/************************************************************************/
#define K_OPT_VOID	-1
#define K_OPT_STATO	0
#define K_OPT_ALGEBRAIC	1
#define K_OPT_INGRESSO	2
#define K_OPT_DATI	3
#define K_OPT_ALL	4

#define MANAGE		0
#define UNMANAGE	1
#define DESTROY		2

#define CREATE_WDG 	0
#define UPDATE_NAMES 	1

#define WIDTH_JAC_TOGGLES 	50
#define HEIGHT_JAC_TOGGLES 	30
#define MARGIN   		10

/*   Definizione costanti di uso generale (genera.c e genmod.c)  */
#define L_NOME                    5
#define L_TITOLO                 30
#define L_NOME_VAR                5
#define L_DESCR_VAR              51
#define L_NORM_VAR               13
#define L_NOME_DATI               9
#define L_DATI                    7
#define MAX_DATI_FORMAT           9
#define MAX_SIMBOLI             120        /*   MAX_VARIABILI + MAX_DATI    */
#define MAX_DICHIAR              24        /*   MAX_SIMBOLI / 5             */
#define L_SIMBOLI                 7        /*   MAX (L_DATI, L_VARIABILI)   */
#define L_STRINGA_APPOGGIO       81

/************************************************************************/
/* Definizione costanti per politica lista moduli                       */
/************************************************************************/
#define USER_MODULES_SELECTION		0
#define STDLIB_MODULES_COPY		1
#define INSERT_MODULE_NEWNAME  		2
#define RETRIEVE_OFFSET_LISTAMOD 	3
#define STDLIB_MODULES_DOC		4

/************************************************************************/
/* Definizione costanti per composizione percorsi e filenames           */
/************************************************************************/
#define FILE_FTN	0
#define FILE_DOC	1
#define FILE_IFACE	2
#define FILE_DAT	3
#define FILE_01DAT	4

/************************************************************************/
/* Definizione costante per lunghezza minima stringa modulo ("VALV*!"\n)*/
/************************************************************************/
#define STRMODULE_MIN_LENGTH 	7

/************************************************************************/
/* Definizione costanti per callback di conferma ecc.                   */
/************************************************************************/
#define YES	0
#define NO	1
#define CANCEL	2

#define C_OK     0
#define C_APPLY  1
#define C_CANCEL 2

/************************************************************************/
/* Definizione costanti per impostazione tipo di jacobiano              */
/************************************************************************/
#define ANALYTICAL 	0
#define NUMERICAL 	1

/************************************************************************/
/* Definizione costanti per optionMenu copia dalla standard lib         */
/************************************************************************/
#define ONLY_FORTRAN 	0
#define ONLY_ICONS 	1
#define COPY_BOTH 	2

/************************************************************************/
/* Definizione costanti tipo libreria (indice array path_librerie)      */
/************************************************************************/
#define LIBUT 		0
#define LIBUTREG 	1
#define LIBREG 		2
#define LIBGRAF		3

/************************************************************************/
/* Definizione costanti per inserimento in lista moduli                 */
/************************************************************************/
#define INSERT		0
#define CONTINUE	1

/************************************************************************/
/* Definizione costanti per spaziatura sezioni di text (EQUAZIONI)      */
/************************************************************************/
#define SPAZIO_FRA_SEZIONI 	25
#define ALTEZZA_TEXT  		35
#define ALTEZZA_LABEL  		15
#define TEXT_FORTRAN_LINES	5

/************************************************************************/
/* Definizione costanti per dipendenze matrice jacobiana	        */
/* WHITE = nessuna dipendenza = False					*/
/* BLACK = tutte dipendenze = True (default)				*/
/************************************************************************/
#define WHITE 	0
#define BLACK	1

/* Limiti del programma fissati dal Magico Silvan */
#define MAX_VARIABILI_USCITA	100
#define MAX_VARIABILI_INGRESSO	200
#define MAX_EQUAZIONI	MAX_VARIABILI_USCITA
#define MAX_VARIABILI_IN_OUT MAX_VARIABILI_USCITA+MAX_VARIABILI_INGRESSO
#define MAX_DATI_GEOMETRICI	100


typedef char byte;

/************************************************************************/
/* Definizione struttura e macro per identificazione 8 sezioni file doc */
/************************************************************************/
typedef struct {
  		char pattern[9];
  		char descrizione[60];
  	       } Sezioni;

/* variabili del modulo (stato, algebriche e ingresso) */
typedef struct {
                  char nome[L_NOME_VAR];
                  char descr[L_DESCR_VAR];
                  char norm[L_NORM_VAR];
               } StructVars;

/* dati geoemtrici del modulo */
typedef struct {
                  char nome[L_NOME_DATI];
                  char sigla[L_DATI];
               } StructDati;

/*********************************************************/
/* Struttura per il widget di conferma COPIA (overwrite) */
/*********************************************************/

/* Struttura per la topologia della matrice jacobiana, rappresentata */
/* da un array bidimensionale di ToggleButtons */
/* N.B. Ora DrawnButton per volonta' del Divo Silvano */
typedef struct {
		 enum {False, True} jac_yes;
                 char var_name[5];
                 char *stringa;
               } JacToggStruct;

/* Struttura dati del modulo per l'editing del FORTRAN */
typedef struct {
                  char nome_mod[5], descr_mod[51];
                  byte tipo_lib;
               } EditFtnStruct;

/*** PROTOTYPING FUNZIONI ***/
char *componi_filename();
char *componi_stdlib_filename();
char *file_dati_lib();
char *percorso_libreria();
char *componi_file_modulo();
char *sottodir_utente();
void edit_code_callback();
void overwrite_yes();
void overwrite_no();
void setta_label_modsel();
void delete_module();
void cambia_tipo_modulo();
void cambia_tipo_copia();
void setup_again();
void jac_toggle_premuto();
void increment();
void prepara_file_doc();
void get_pixel();
void editor_done();  /* Callback del push-button 'Done' */
void end_process();
void end_edicole();
void confirm_save();
void confirm_quit();
int riempi_lista_moduli();
int controlla_lista_moduli();
int apponi_tag_listamod();
int controlla_lista_moduli();
int aggiungi_modulo_lista();
int aggiungi_record_icona();
int copia_nella_libut();
int copia_nella_libgraf();

/* prototipi di funzione utilizzate nella generazione del FORTRAN */
void genmod(void);
void genmodI2();
void genmodC1();
void genmodJC();
void genmodMOD();
void genmodI3();
void genmodI4();
void genmodD1();
void dichiara_common();
void dichiaraI2_common();
void dich_variabili_e_dati();
void topologia();
void titoli_topologia();
void init_topol();
void input_topologia();
void genera_topologia();
void strnleftindent();
void intesta_subroutine();
void text_maius_callback();
void conf_test_env();

/* FINE FILE definizioni.h  (librarian)  */

#endif

