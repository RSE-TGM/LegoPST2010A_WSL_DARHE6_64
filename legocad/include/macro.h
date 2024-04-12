/**********************************************************************
*
*       C Header:               macro.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Jul 20 11:24:15 2001 %
*
**********************************************************************/
/* MACRO.H   header file per l'applicativo MACRO.C
   Versione: 0.1         5.11.92            Buffo & Calleri  */

/* Macro per la creazioni di compound stringhe */
#define CH_SET                   XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR(string,CH_SET))

#define ABS(val)        (((val)>0.0)?(val):-(val))

/* Titoli delle window */
#define MACRO_WINDOW_TITLE   "DIAGRAM EDITOR"
#define BLOCKS_WINDOW_TITLE  "DIAGRAM PAGE EDITOR"

#define APPLICATION_NAME	"MACRO"

/* Massimo numero di righe delle varie scrolled list */
#define VISIBLE_ITEMS 	10

#define MAX_SYMB_X_ROW	5

/* delta-pixel di selezione */
#define DELTA_SELECT_LINE 4

/***********************************************************************/
/* Strutture per la gestione degli widgets da tracciare ecc.           */
/***********************************************************************/

typedef struct { int posx, posy; } PosXY;

typedef struct { int    num_icona, width, height;
                 Pixmap pixmap;         } PixmapInfo;

typedef struct {
                  short int thickness, color, length_arrow, width_arrow;
                  Boolean with_arrow;
                  XPoint *points;
                  int num_points;
               } GLine;

typedef struct { short int ind_macro;
		 PixmapInfo    *pixmap_info;
                 Widget    wblock, wlabel, wpixmap;
		 char      nome_modulo[5], nome_blocco[9],
			   descr_blocco[51];
                 short int tipo,flag;
		 Boolean   selezionato, cancellato;
		 PosXY     pos_icona;
		 short int num_icona; } BlockType;

typedef struct { Widget    wmacro;
		 Widget	   wwinblock;
		 Widget	   wtavblock, wpopup;
                 char      nome_macro[15], descr_macro[51];
                 short int cancellato;
                 Boolean   selezionato;
                 PosXY     pos_icona;
                 int       num_blocchi, num_blocchi_selez, num_blocchi_alloc;
                 int       num_line, num_line_selez, num_line_alloc;
		 Widget    menu_edit_blocchi[12];
		 Widget    pop_edit_blocchi[12];
                 GLine     *line;
                 BlockType *blocks;       } MacroBlockType;

typedef struct { unsigned char tipo_info;
		 void	       *ptr;      } UserDataStruct;

typedef struct { int indice;
		 short int x, y, width, height; } DimWidgets;

typedef struct { char       nome_modulo[5], descr_modulo[51];
		 int        num_icone;
                 PixmapInfo pixmap_info[10];  } PixmapModuleStruct;

typedef struct { int  num_icone;
		 PixmapInfo pixmap_info[100]; } PixmapSymbolStruct;

/* tipi di informazioni utilizzate nelle userData */
#define UD_MACROBLOCKS	0
#define UD_BLOCKS	1
#define UD_BITMAPREC	2

/* tipo del blocco  */
#define	TP_BLOCK	0
#define TP_REMARK	1
#define TP_SYMBOL	2
#define TP_LINE		3
#define	TP_BLOCK_REG	4

/* provenienza dell'icona */
#define	FROM_ADD_BLOCK		0
#define	FROM_MODIFY_BLOCK	1
#define	FROM_WINDOW_BLOCK	2

/* DEFINIZIONE DEI DIMENSIONAMENTI DI TALUNI WIDGETS */
#define BORDER_WIDTH	2	/* cornice delle label dei macroblocchi */
#define PAGE_WIDTH	800
#define PAGE_HEIGHT	560
#define BB_WIDTH	(PAGE_WIDTH*5)/* larghezza dell'area di disegno */
#define BB_HEIGHT	(PAGE_HEIGHT*5)	/* ampiezza dell'area di disegno */
#define MACROBLOCKS_HEIGHT	45   /* altezza delle label dei mblocchi */
#define MACROBLOCKS_WIDTH	180  /* larghezza delle label dei mblocchi */
#define ICON_LABEL_HEIGHT       20

/* Dimensionamento degli array di widgets */
#define MAX_FINESTRE_BLOCCHI	10

/* stringhe di definizione delle translations */
#define STR_DESELECT_ALL_MACRO \
	"#override <Btn1Down> : deselect_all_macro()"
#define STR_SELECT_MACRO1 \
	"#override <Btn1Down> : select_macro(1 %d)"
#define STR_SELECT_MACRO2 \
	"#override Ctrl<Btn1Down> : select_macro(2 %d)"
#ifdef DATI
#define STR_DESELECT_ALL_BLOCK \
	"#override <Btn1Down> : desel_all_page_lista(%d) deselect_all_block(%d)"
#else
#define STR_DESELECT_ALL_BLOCK \
	"#override <Btn1Down> : deselect_all_block(%d)"
#endif
#define STR_SELECT_BLOCK1 \
        "#override <Btn1Down> : manage_select_block(1 %d %d)"
#define STR_SELECT_BLOCK2 \
        "#override Ctrl<Btn1Down> : manage_select_block(2 %d %d)"

/***************************************/
/* Costanti di definizione dei colori  */
/***************************************/
#define WHITE           0
#define MACRO_DEFAULT_BG	0
#define BLACK           1
#define YELLOW          2
#define GREEN           3
#define RED             4
#define BLUE            5

#define GREY		6

#define MACRO_MOVE_BG	7
#define MACRO_SELEZ_BG	8
#define BLOCKS_TABLE_BG	9
#define BORDER_MOVE_FG	10

/* costanti che identificano le dialog-box */
#define DBOX_NEW_MACRO			0
#define DBOX_NEW_BLOCK			1
#define DBOX_MODIFY_MACRO		2
#define DBOX_DELETE_MACRO		3
#define DBOX_MODIFY_BLOCK		4
#define DBOX_ADD_REMARK			5
#define DBOX_MODIFY_REMARK		6
#define DBOX_SETUP_LINE			7
#define DBOX_SETUP_LINE_APPLY		8
#define DBOX_MODIFY_SNAP		9

/* voci della menubar della window dei macroblocchi (utilizzati come */
/* parametri delle callback) */
/* Edit ... */
#define K_OPEN_MACRO		0  /* i primi 5 sono anche indici del */
#define K_COPY_MACRO		1  /* vettore edit_menu_macro.        */
#define K_NEW_MACRO		2  /* fare attenzione prima di modificare */
#define K_MODIFY_MACRO		3  /* tali numeri. */
#define K_DELETE_MACRO		4

/* File ... */
#define K_LOAD_ICONS		5
#define K_SAVE			6
#define K_QUIT			7

/* Snap ... */
#define K_MODIFY_SNAP		8


#ifdef MAIN
#define K_COPY_BLOCK		0
#define K_PASTE_BLOCK		1
#define K_CONNECT_BLOCK		2
#define K_MODIFY_BLOCK		3
#define K_DELETE_BLOCK          4
#define K_MOVE_BLOCK            5
#define K_ADD_PBLOCK            6
#define K_ADD_SBLOCK            7
#define K_ADD_SYMBOL            8
#define K_ADD_REMARK            9
#endif
#ifdef TOPOLOGIA
#define K_VARIABLES_BLOCK       0
#define K_NEW_BLOCK             1
#define K_NEW_PROCESS_BLOCK	2
#define K_NEW_REGULATION_BLOCK	9
#define K_MODIFY_BLOCK	        3	
#define K_DELETE_BLOCK          4
#define K_MOVE_BLOCK            5
#define K_ADD_BLOCK             6
#define K_ADD_SYMBOL            7
#define K_ADD_REMARK            8
#endif
/********************************************
#define K_DELETE_BLOCK		4
#define K_MOVE_BLOCK		5
#define K_ADD_BLOCK		6
#define K_ADD_SYMBOL		7
#define K_ADD_REMARK		8
*********************************************/

/* definizioni indici di menu utilizzati solo nel
   programma DATI */
#ifdef DATI
#define K_VAR_BLOCK		0
#define K_DATA_BLOCK		1
#define K_KNOW_BLOCK		2
#define K_NORM_BLOCK		3
#endif

/* tipo di toggle */
#define K_SNAP_TOGGLE		0
#define K_ARROW_TOGGLE		1

/* step della griglia in pixels */
#define PIXEL_STEP		5

/**************************/
/* Prototipi di funzione: */
/**************************/

/* FUNZIONI GENERICHE */
void crea_pagina_indice();
void dealloca_pixmap();
void menu_pagina_indice();
void macro_bpress();
void macro_bcont();
void macro_brelease();
void block_bpress();
void block_bcont();
void block_brelease();
void start_rubberband();
void continue_rubberband();
void end_rubberband();
void start_select();
void continue_select();
void end_select();
void attiva_popup();
void icon_press();
void crea_gc();
void get_pixel();
void set_label();
void add_translations();
void deselect_all_macro();
void select_macro();
void deselect_all_block();
#ifdef DATI
void desel_all_page_lista();
#endif
void manage_select_block();
void crea_finestra_blocchi();
void apri_finestra_blocchi();
void menu_finestra_blocchi();
void dialog_box_gen();
void dialog_nuovo_blocco();
void carica_lista_moduli();
void carica_icone_modulo();
void widget_selected();
Widget crea_find();
void popup_macro();
void popup_block();
void macro_edit_items();
void block_edit_items();
void crea_remark();
int  *cerca_macro_selezionati();
int  *cerca_blocchi_selezionati();
void cambia_edit_blk_menu();
void cambia_edit_mcr_menu();
void dialog_simboli();
void carica_simboli();
void cambia_pixmap_icona();
void crea_pixmap_moduli();
void crea_pixmap_simboli();
PixmapModuleStruct *ricerca_modulo();
PixmapInfo *ricerca_icona();
PixmapInfo *recupera_pixmap();
Pixmap crea_pixmap();
void leggi_nome_modello();
void conferma_uscita_blocchi();
void chiudi_window_blocchi();
void conferma_delete_macro();
void def_handler_macro();
void def_handler_block();
void def_translations_block();
void seleziona_window();
void cancella_blocco();
int alloca_nuovo_blocco();

/* FUNZIONI DI CALLBACK */
void quit_block();
void quit_session();
void cancel_proc();
void menu_macro();
void new_block();
void move_selected_blocks();
void add_remark();
void add_symbol();
void modify_block();
void delete_selected_blocks();
void save_block();
void deselect_blocks();
void ok_proc();
void selez_modulo();
void seleziona_icona();
void chiama_input();
void setup_line();
void dialog_setup_line();
void scelta_colore();
void toggle_proc();
void funz_draw_line();
void funz_expose();
void start_draw_line();
void cont_draw_line();
void end_draw_line();
void delete_line();
#ifdef TOPOLOGIA
void variables_block();
void add_process_block();
void add_regolation_block();
extern void bl_del_cb();
extern int delete_selected_from_all_macro();
#endif
#ifdef DATI
void menu_dati_callb();
#endif
/* fine macro.h */
