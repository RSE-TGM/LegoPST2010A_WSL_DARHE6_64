/**********************************************************************
*
*       C Header:               calcstaz.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:08 1996 %
*
**********************************************************************/
/*** FILE: CALCSTAZ.H */
/* Buffo Massimo, Calleri Nicola 2/07/1992 */

/* include file che contiene le costanti/macro utilizzate nel programma di */
/* calcolo dello stazionario e diagnostica relativa */
#define APPLICATION_NAME "CALCSTAZ"
/* titolo della window */
#define ICON_NAME    "STEADY STATE"
#define WINDOW_TITLE "STEADY STATE COMPUTATION"

/* Macro per la creazioni di compound stringhe */
#define CS  			XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

#define	K_MODEL_SELECTION		 1
#define	K_EXIT_PROGRAM			 2
#define	K_TOLERANCE			 3
#define	K_DIRECT_MODE			 4
#define	K_INTERACTIVE_MODE		 5
#define	K_FREE_DIAGNOSTICS		 6
#define	K_GUIDED_DIAGNOSTICS		 7
#define K_SAVE_CURRENT_SETTING		 8
#define K_SET_DEFAULT_SETTING		 9
#define	K_UNKNOWN_VAR_SELECTION		10
#define	K_SYSTEM_DATA_MODIFY		11
#define	K_LOAD_PREVIOUS_DATA		12
#define	K_LOAD_LAST_DATA		13
#define K_RESULTS			14
#define K_EQUATION_DIAGNOSTICS			115
#define K_ITERATION_DIAGNOSTICS			116
#define K_JACOBIAN_DIAGNOSTICS			117
#define	K_SYSTEM_RESULTS		16
/*
#define	K_BLOCKS_RESULTS		17
*/
#define	K_COMPUTING_REPORTS		18

/*	Costanti per la memorizzazione dei push button per 
	attivare/disabilitare i buttons 
 */
#define	K_START				19
#define	K_STEP				20

/*	Costanti per la memorizzazione degli WidgetID relativi alle 
	labels il cui contenuto viene modificato 
 */

#define	K_MODEL_NAME			21 
#define	K_COMPUTING_MODE		22
#define	K_DIAGNOSTICS_CHOICE		23
#define	K_TOLERANCE_VALUE		24

/*
 	Costante per memorizzazione WdigetID della finestra di stato 
 */

#define	K_STATUS_WINDOW			25

/* 
	Costanti utilizzate per i BulletinBoardDialog 
 */
#define K_TOLERANCE_DIALOG              26 
#define K_TOLERANCE_DIALOG_TEXT         27 /* ID del Text widget */


#define K_STEADY_STATE_RESULTS_DIALOG	28

#define K_BLOCK_LIST_RESULTS		30
#define K_RESULTS_LIST			31

/*     Costante per la memorizzazione dello WidgetID relativo alla
       label della Results List, il cui contenuto viene modificato  */

#define K_DISPLAY_RESULTS_LABEL         33

/* Costanti che definiscono lo stato della ricerca di stringhe  */
#define K_FIND_BLOCK                    34  /*  ID degli Widget  */
#define K_FIND_DATA                     133 /*     X m T e x t   */
#define K_FIND_NEXT_BLOCK                       134
#define K_FIND_PREVIOUS_BLOCK                   135
#define K_FIND_NEXT_DATA                        136
#define K_FIND_PREVIOUS_DATA                    137
#define K_BLOCK_FOUND                           138
#define K_DATA_FOUND                            139

/* Costanti che definiscono la modalita' di ricerca */
#define FIND_NEXT       0
#define FIND_PREVIOUS   1

/* Costanti che definiscono lo stato del calcolo */
#define STAZIONARIO_NON_ATTIVATO	0
#define STAZIONARIO_IN_CORSO		1
#define STAZIONARIO_SODDISFATTO		2
#define STAZIONARIO_NON_SODDISFATTO	3

/* Costanti che definiscono la modalita' di calcolo */
#define DIRECT_MODE	     0
#define INTERACTIVE_MODE     1
#define DIRECT_STRING	     CREATE_CSTRING("     Direct computing mode")
#define INTERACTIVE_STRING   CREATE_CSTRING("Interactive computing mode")


/* Nome del file che contiene le Options di default */
#define FILE_USER_SETTING	".user_setting"

/* Nomi dei file di topologia e di dati geometrici */
#define FILE_F14		"f14.dat"
#define FILE_F14_TMP		"f14.tmp"
#define FILE_F24		"proc/f24.dat"
#define FILE_F01		"f01.dat"
#define FILE_LG3		"lg3.out"
#define FILE_LG3_TMP		"lg3.tmp"

#define COMM_PIPE		"to_calcstaz"

#define MAX_ITERATIONS  500
#define MAX_NUM_BLOCCHI 500
#define MAX_NUM_VAR     500
 
#define MAX_WIDGETS	200

#define HEADER_BLOCCO_F14	"*LG*DATI DEL BLOCCO "
#define EOF_F14			"*LG*EOF"

/* Settings di defaults */
#define DEFAULT_TOLERANCE_VALUE	0.00001
#define DEFAULT_MODE		DIRECT_MODE
#define DEFAULT_DIAGNOSTICS	FREE_DIAGNOSTICS

#define NON_UTILIZZATO		-1

/******************************************/
/* Costanti per la funzione msgbox_button */
/******************************************/
#define ESCI_E_SALVA		0
#define ESCI_SENZA_SALVARE	1
#define STAMPA_F24		2
#define STAMPA_LG3		3
#define SALVA_F14		4
#define CANCELLA		5
#define VIEW_LG3_OUT		6

/* Definizione font per tutte le label, messaggi ecc. chiamati da C  */
#define BOLD   font('ADOBE-Times-Bold-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define NORMAL font('ADOBE-Helvetica-Medium-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define FIXED  font('8x13')

/* Definizione label della ScrolledList dei Results  */
#define DISPLAY_VARIABLE  0
#define DISPLAY_DATA      1
#define DISPLAY_VARIABLE_STRING CREATE_CSTRING \
       (" VARIABLE   FINAL VALUE   INITIAL VALUE    DESCRIPTION")
#define DISPLAY_DATA_STRING     CREATE_CSTRING \
       ("GEOMETRICAL  AND  PHYSICAL  DATA")


/* Definizione tipo booleano (vero,falso) */
#define	TRUE	1
#define FALSE	0

/* Numero massimo di righe e item visibili nella finestra di stato */
#define MAX_ROW_STATUS_WINDOW	200
#define VISIBLE_ITEMS		11

/* Window UNSATISFIED EQUATION  */

#define K_EQUATION_WINDOW 		35
#define K_ITERATION_EQUATION_WINDOW	36
#define K_VARIABLE_EQUATION_WINDOW	37

#define K_EQUATION_LIST			38
#define K_ITERATION_EQUATION_LIST	39
#define K_VARIABLE_EQUATION_LIST	40

#define K_BLOCK_VALUE_ITER_EQ_LABEL	41
#define K_MODULE_VALUE_ITER_EQ_LABEL	42
#define K_DESCRIPT_VALUE_ITER_EQ_LABEL 	43
#define K_NUMEQ_VALUE_ITER_EQ_LABEL	44
#define K_MEANING_VALUE_ITER_EQ_LABEL	45
#define K_UNIT_VALUE_ITER_EQ_LABEL	46

#define K_BLOCK_VALUE_VAR_EQ_LABEL	47
#define K_MODULE_VALUE_VAR_EQ_LABEL	48
#define K_DESCRIPT_VALUE_VAR_EQ_LABEL 	49


/* Window ITERATIONS LIST  */

#define K_ITERATION_WINDOW		50
#define K_EQUATION_ITERATION_WINDOW	51

#define K_ITERATION_LIST		52
#define K_EQUATION_ITERATION_LIST	53

#define K_ITERATION_LABEL		54
#define K_NEQSIS_LABEL			55
/*      #define K_NUMITER_VALUE_LABEL		56    COMPRESA NEL TITOLO  */
/* Label (=stringhe concatenate) della scrolled list delle iterazioni */
#define ITERATION_LIST_LABEL_TEXT_1 \
"Iteration    Jacobian    Convergence    Maximum        Norma           Unsatisfied" 
#define ITERATION_LIST_LABEL_TEXT_2 \
"                computed       problem          residual                               equations of"

/* Window JACOBIAN ANALYSIS */

#define K_JACOBIAN_WINDOW		60

#define K_JACOBIAN_LIST			61
#define K_DISPLAY_VARIABLES    			161
#define K_DISPLAY_BLOCKS      			162
#define K_INFO_BUTTON				164
#define K_ROW_BUTTON				165
#define K_COLUMN_BUTTON				166

#define K_JACOBIAN_BLOCKS_WINDOW	62
#define K_JACOBIAN_BLOCKS_LIST		63

#define K_JACOBIAN_ROWS_LIST		64
#define K_JACOBIAN_COLS_LIST		65

#define K_JACOBIAN_VALUES_LIST		66

/*  creata da C   */
#define K_JAC_SING_INFO_WINDOW		70
  
#define K_JAC_SING_ROW_WINDOW		71
#define K_JAC_SING_ROW_LIST		72
#define K_JAC_SING_ROW_VAR_LIST		73
#define K_JAC_SING_ROW_REASON		74

#define K_JAC_SING_COL_WINDOW		75
#define K_JAC_SING_COL_LIST		76
#define K_JAC_SING_COL_REASON_1		77
#define K_JAC_SING_COL_REASON_2		78

#define K_JACOBIAN_VARIABLES_WINDOW	80
#define K_JACOBIAN_VARIABLES_VAR_LIST	81
#define K_JACOBIAN_VARIABLES_EQ_LIST	82

/* stringhe di formato utilizzate nelle scroll-list */
#define SF_EQUATION_LIST 	"%4d        %.8s        %3d"
#define SF_ITERATION_LIST 	"%4d        %c          %c      %s %s      %3d"
#define SF_JACOBIAN_LIST 	"%4d             %c            %c"
#define SF_ITERATION_EQUATION_LIST 	"%4d           %s       %s"
#define SF_EQUATION_ITERATION_LIST 	"%4d      %.8s    %s     %s    %.10s"
#define SF_VARIABLE_EQUATION_LIST 	"%c %.8s %s    %s     %.48s"
#define SF_RESULTS_LIST 		"%c %.8s %s   %s   %.50s"
#define SF_JACOBIAN_VARIABLES_EQ_LIST 	"%3d             %.8s        %s"
#define SF_JAC_SING_ROW_LIST 		"%4d        %.60s"
#define SF_JAC_SING_COL_LIST 		"%.70s"
#define SF_JAC_SING_ROW_VAR_LIST	"%.70s"
#define SF_JACOBIAN_VARIABLES_VAR_LIST 	"%.70s"
#define SF_JACOBIAN_BLOCKS_LIST 	"%.80s"

/* Prototipi di funzione */
void read_user_setting();
char *extract_string();

/* funzioni definite in utilx.c ... */
Widget information (), attention(), editor(); 

/* Prototipi delle funzioni di callback */
void mesg_from_lg3();
void create_proc();
void cancel_proc();
void ok_proc();
void dialog_proc();
void activate_proc();
void show_results();
void selez_proc();
void selez_jac_proc();
void start_proc();
void find_proc();
void msgbox_button();
void show_jacobian();
double valore_jacobiano();
void show_jacobian();
void increment();
void sig_child();

/* Definizione delle strutture */
typedef struct voce_menu {
			    int ind; /* indice in widget_array */
			    int stato; /* Stato della voce:
					  attiva -> True
				          non attiva -> False */
		 	 } VOCE_MENU;

/*** Fine file calcstaz.h ***/
