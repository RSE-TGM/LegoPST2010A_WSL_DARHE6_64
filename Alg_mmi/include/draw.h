/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo draw.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)draw.h	5.1
*/




#ifndef _DRAW_H
#define _DRAW_H
#define LOCAL_GC_SET 0
#define DEFAULT_GC_SET 1
/*
 Definizione della struttura che contiene tutte le caratteristiche
 personalizzabili (opzioni ed altro) del draw_wid.
 N.B.: con il termine 'corrente' si intende che l'attributo si
       applica agli oggetti in selezione. 
       Con il termine 'default' si intende un attributo che si applica
       ai nuovi oggetti in creazione. 
*/
typedef struct {
Region region;          /* region utilizzata per la compressione del ridisegno */
int line_style; 	/* stile di linea per i contorni */
int line_width; 	/* spessore di linea per i contorni */
int def_line_style; 	/* stile di linea per i contorni (default) */
int def_line_width; 	/* spessore di linea per i contorni (default) */
GC gc; 		/* gc usato per i contorni dei draget (corrente) */
GC gc_bg;  	/* gc usato per il filling dei draget (corrente) */
GC def_gc; 	/* gc di default per i contorni */
GC def_gc_bg; 	/* gc di default per il filling */
int step;  	/* ampiezza in pixel dello snap */
int grid_on; 	/* presenza della griglia di sfondo */
int def_filled; /* indica se il draget va fillato */
float def_zoom;   /* fattore di zoom di default  */
/*
 indici di widget di bottone presenti nell'interfaccia di comando
*/
Widget bott_fill; 	/* bottone selezionato per il fill (corrente) */
Widget bott_border; 	/* bottone selezionato per il bordo (corrente) */
Widget def_bott_fill;
Widget def_bott_border;
Widget bott_arrow;      /* bottone freccia (default) */
} ST_DRAW_WID; 
/*
 enumerazione dei tipi consentiti per chiamate di get e set sulla
 widget di drawing
*/
enum ris_draw_wid {DR_REGION,
		   DR_LINE_STYLE,
		   DR_LINE_WIDTH,
		   DR_DEF_LINE_STYLE,
		   DR_DEF_LINE_WIDTH,
		   DR_GC,
		   DR_GC_BG,
		   DR_DEF_GC,
		   DR_DEF_GC_BG,
		   DR_STEP,
		   DR_GRID_ON,
		   DR_DEF_FILLED,
		   DR_DEF_ZOOM,
		   DR_BOTT_FILL,
		   DR_BOTT_BORDER,
		   DR_DEF_BOTT_FILL,
		   DR_DEF_BOTT_BORDER,
		   DR_BOTT_ARROW};	
/*
 Prototiping delle funzioni utilizzate per il settaggio delle
 risorse di draw_wid
*/
extern Region get_region(Widget );
extern void set_region(Widget , Region );
extern int get_line_style(Widget );
extern void set_line_style(Widget  , int );
extern int get_line_width(Widget );
extern int set_line_width(Widget  , int );
extern int get_def_line_style(Widget );
extern int set_def_line_style(Widget  , int );
extern int get_def_line_width(Widget );
extern int set_def_line_width(Widget  , int );
extern int get_step(Widget );
extern int set_step(Widget  , int );
extern int get_grid_on(Widget );
extern int set_grid_on(Widget  , int );
extern int get_def_filled(Widget );
extern int set_def_filled(Widget  , int );
extern float get_def_zoom(Widget );
extern int set_def_zoom(Widget  , float );
extern GC get_gc(Widget );
extern int set_gc(Widget  , GC );
extern GC get_gc_bg(Widget );
extern int set_gc_bg(Widget  , GC );
extern GC get_def_gc(Widget );
extern int set_def_gc(Widget  , GC );
extern GC get_def_gc_bg(Widget );
extern int set_def_gc_bg(Widget  , GC );
extern Widget get_bott_fill(Widget );
extern int set_bott_fill(Widget  , Widget );
extern Widget get_bott_border(Widget );
extern int set_bott_border(Widget  , Widget );
extern Widget get_def_bott_fill(Widget );
extern int set_def_bott_fill(Widget  , Widget );
extern Widget get_def_bott_border(Widget );
extern int set_def_bott_border(Widget  , Widget );
extern Widget get_bott_arrow(Widget );
extern int set_bott_arrow(Widget  , Widget );

extern int init_st_draw(ST_DRAW_WID * );
int set_current_gcs(Widget);

extern  void *		UxNewContext();
void LoadDrawPixmap(Pixmap *,Widget);
void wselez_bott_fill(Widget);
void add_def_translation(Widget ,char *);

void wselez_bott_border(Widget);
void aggiungi_pagedit_translation(Widget );
void DeselectAllDraget(Widget, Boolean);
void draget_duplicate(Widget,int,int);
void draget_cut();
void draget_cutS();
//void draget_copy(Widget);
void draget_paste(Widget);
void DrawDelete(Widget,XEvent *);
void DrawPutTop(Widget);
void DrawPutBottom(Widget);
void DrawGroup(Widget);
void DrawUngroup(Widget);
void DrawSetZoom(Widget,float);
void DrawSetGrid(Widget);
void set_current_filled(Widget,Boolean);
void DrawSetSnap(Widget,int);
void DrawSetSnap(Widget,int);
//Widget	create_ColorViewer( int, unsigned char	*, XmString, XrmDatabase, Widget	*, Widget );
Widget	create_ColorViewer();
void undo_draget_copy(Widget,Widget);
//void get_child(Widget ,WidgetList *,Cardinal *);
void get_geometry(Widget ,Position *,Position *,Dimension  *,Dimension *);
void XlRedisplay(Widget );
void print_callback(Widget );
void XdSetSnap();
void append_redraw(Widget);
void reset_bott_def(Widget );
void XdSetFilled();
void XdSetZoom();
void set_arrow_mode(Widget);
 void set_draw_translations();
 void ListSetPosByDraget();
 void SelectDragetRect();
 void WriteBackground(Widget,char *);
 int ListGetNumAllDraget();
 void ReadBackground(Widget,char *);
 void DrawSetZoom(Widget,float);
 void XdChangeZoom();
 int ListGetAll();
 void XdDestroyDragetNoClear();
 void XdRedrawDraget();
 void XdRedrawDraget();
 void XdClearDraget();
 Boolean XdUngroupDraget();
 Boolean XdMoveDraget();
 Boolean XdEndMoveDraget();
 void XdSetGC();
 void draget_copy();
 void draget_copyS();
 int gs_draw_ris(Widget ,enum ris_draw_wid , void *,Boolean );
 








#endif   /* _DRAW_H */
