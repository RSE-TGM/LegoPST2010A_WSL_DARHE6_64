/**********************************************************************
*
*       C Header:               iconvert.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:54 1996 %
*
**********************************************************************/
/* ICONVERT.H   header file per l'applicativo ICONVERT.C
   Versione: 0.1          13.01.93           Buffo & Calleri 
   Modificato il  ------> 11.11.93                           */

/* Macro per la creazioni di compound stringhe */
#define CS                      XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

/* MAcroblock di default */
#define MACRO_DEFAULT	"default"

/* Titolo della main window e dell'icona */
#define WINDOW_TITLE   "OBSOLETE LEGO MODELS CONVERTER FOR ADVANCED GRAPHICS"
#define ICON_NAME      "ICONVERT"

/* DEFINIZIONE DEI DIMENSIONAMENTI DI TALUNI WIDGETS */
#define BORDER_WIDTH    2       /* cornice delle label dei macroblocchi */
#define BB_WIDTH        1500    /* larghezza dell'area di disegno */
#define BB_HEIGHT       1500    /* ampiezza dell'area di disegno */
#define MACROBLOCKS_HEIGHT      45   /* altezza delle label dei mblocchi */
#define MACROBLOCKS_WIDTH       180  /* larghezza delle label dei mblocchi */

/* step della griglia in pixels */
#define PIXEL_STEP              5

/* Massimo numero di righe della scroll-list */
#define VISIBLE_ITEMS 	10

/* Codici per messaggi */
#define WNOMCRSELECT	0
#define WMCRNAMEBLANK	1
#define WMCRNAMEEXIST	2
#define WSEARCHMACRO	3
#define WNOBLKSELECT	4
#define WMCRNAMERES	5
#define WMACRONOTFOUND	6

#define EOPENMACROBLK	0

#define APPLICATION_NAME	"ICONVERT"

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

/* tipo del blocco  */
#define	TP_BLOCK	0
#define	TP_BLOCK_REG	1
#define TP_REMARK	2
#define TP_SYMBOL	3
#define TP_LINE		4

/* fine iconvert.h */
