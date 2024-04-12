/**********************************************************************
*
*       C Header:               edicole.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:41 1996 %
*
**********************************************************************/
/*** FILE: EDICOLE.H */
/* Buffo Massimo, Calleri Nicola 18/9/1992 */

/* include file che contiene le costanti/macro utilizzate nel programma di */
/* editing delle edicole lego */

/* titolo della window */
#define APPLICATION_NAME    "EDICOLE"
#define WINDOW_TITLE "LEGO ICON EDITOR"

/* Macro per la creazioni di compound stringhe */
#define CS  			XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

/*************************************************/
/**** D I M E N S I O N A M E N T I   V A R I ****/
/*************************************************/

/* PARAMETRO PER L'INCREMENTO DEGLI SCALE WIDGET */
#define STEPPING        5

/* Dimensioni di default */
/* La LARGHEZZA dipende dal font adoperato. E' settata da programma. */
#define DEFAULT_ICON_HEIGHT     10   /* N.B. da moltiplicare per STEPPING */
#define SYMBOL_MIN_DIMENSION	2    /* N.B. da moltiplicare per STEPPING */ 
#define MAX_DIMENSION           300
#define ICON_LABEL_HEIGHT       20


/****************************************************/
/* Costanti per corrispondenza widget con file .UIL */
/****************************************************/

/* Voci della Menubar */
#define	K_QUIT_PROGRAM			1
#define	K_MODULE_P			2
#define	K_MODULE_NP			3
#define	K_MODIFY			4
#define	K_CLEAR				5
#define	K_NEW				6
#define	K_DELETE			7
#define K_SAVE				8
#define K_STD_MODULE_P			9
#define K_STD_MODULE_NP			10
#define K_COPY				11
#define K_SYMBOL				90

/*  Costanti per la memorizzazione degli WidgetID relativi alle
    labels il cui contenuto viene modificato			*/
#define K_MODULE_NAME			12
#define K_ICON_MODULE			13
#define K_MODULE_DESCRIPTION		14

/*  Altre costanti di widget della main window  */
#define K_ICON_WIDTH			15
#define K_ICON_HEIGHT			16
#define K_VIEW_WINDOW			17
#define K_BBOARD_WINDOW			18
#define K_BBOARD_ICON			19
#define K_ICON_PIXMAP			20
#define K_ICON_LABEL			21
#define K_ORDER_OF_ICONS		22
#define K_ICONS_OF_MODULE		23
#define K_NEXT_ICON			24
#define K_PREVIOUS_ICON			25
#define K_FILE_BITMAP			26

/*  Costanti utilizzate per i Bulletin Board Dialog  */
#define K_MODULE_P_DIALOG		30
#define K_MODULE_NP_DIALOG		31
#define K_MODIFY_DIALOG			32
#define K_MODULE_P_LIST			35
#define K_MODULE_NP_LIST		36
#define K_MODULE_P_FORM			37   /* gli ID di queste form   */
#define K_MODULE_NP_FORM		38   /* servono per il find_kit */

#define K_COPY_DIALOG			40
#define K_COPY_TEXT			42

/*   #define K_ICON_FILES_LIST		41    */

/* Costanti dei vari Option Menu */
#define K_WHITE_FG			50
#define K_BLACK_FG			51
#define K_YELLOW_FG			52
#define K_GREEN_FG			53
#define K_RED_FG			54
#define K_BLUE_FG			55
#define K_FG_MENU			80

/* Costanti di definizione dei colori  */
#define	WHITE		0
#define	BLACK		1
#define	YELLOW		2
#define	GREEN		3
#define	RED		4
#define	BLUE		5


/* SETTAGGIO DEI COLORI DI BACKGROUND -- DISABILITATO */
/*
  #define K_WHITE_BG			60
  #define K_BLACK_BG			61
  #define K_YELLOW_BG			62
  #define K_GREEN_BG			63
  #define K_RED_BG			64
  #define K_BLUE_BG			65
  #define K_BG_MENU			81
   void color_bg_proc();
*/

/* Altre costanti */
#define MAX_WIDGETS	100
#define VISIBLE_ITEM_COUNT	12

/* tipo di icone */
#define TP_MODULE_PROCESS	0
#define TP_MODULE_SCHEME	1
#define TP_STD_PROCESS		2
#define TP_STD_SCHEME		3
#define TP_SYMBOL		4

/* verso ricerca per la funzione next_icon_available() */
#define S_NEXT		0
#define S_PREVIOUS	1

/* Definizione font per tutte le label, messaggi ecc. chiamati da C  */
#define BOLD   font('ADOBE-Times-Bold-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define NORMAL font('ADOBE-Helvetica-Medium-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define FIXED  font('8x13')
/* Definizione tipo booleano (vero,falso) */
#define	TRUE	1
#define FALSE	0

/* Definizioni per il ridimensionamento  */
#define WIDTH	0
#define HEIGHT  1

/* eseguibile bitmap editor */
#define BITMAP_EXE "bitmap"

/* prefisso delle variabili nei files bitmap */
#define NOME_VAR_BITMAP	"bmap"

/* stringhe di formato utilizzate nelle scroll-list */

/* Prototipi di funzione */
void s_error();
void s_warning();
void centra_icona();
void centra_icona_dinamica();
void load_icon(); 
void get_pixel();
void crea_find();
void copy_n_car();
void cambia_stato_menu();
void icon_defaults();
void symbol_defaults();

/* Prototipi delle funzioni di callback */
void create_proc();
void cancel_proc();
void ok_proc();
void activate_proc();
void dialog_proc();
void drag_proc();
void step_proc();
void color_fg_proc();
void cambio_dim();
void select_icon();
void select_modulo();
void end_bmap_edit();

/* Definizione delle strutture */
/* Struttura delle voci di menu & push button */
typedef struct {
		int indice;  /* indice in widget_array[] */
		int stato;   /* True=attivo, False=disattivo */
	       } Voci_menu;

/*** Fine file edicole.h ***/
