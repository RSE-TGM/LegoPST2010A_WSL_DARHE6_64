/**********************************************************************
*
*       C Header:               XlChangePageP.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Mon Jun 16 10:28:48 1997 %
*
**********************************************************************/
/*
 * XlChangePageP.h.h - definizioni private per l'oggetto ChangePage
 */ 
#ifndef _XlChangePageP_h
#define _XlChangePageP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlChangePage.h>

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;
	} XlChangePageClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlChangePageClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlChangePageClassPart   xlchangePage_class;
	} XlChangePageClassRec;

extern XlChangePageClassRec xlChangePageClassRec;

/*
 Nuovi campi per il record del widget XlChangePage
 */
typedef struct {
        /* risorse  */
	Pixel norm_fg;  /* foreground nello stato normale */
	Pixel norm_bg;  /* background nello stato normale */
	char * normalfont;  /* nome del font utilizzato per le scritte */
	int tipo;       /* modalita' cambio o nuova pagina  */
	int draw;	/*modalita' bitmap o label */
	int fill_button;	/*modalita' con o senza bordo */
	char *pagina;    /* nome della pagina */
	char *label;    /* label da inserire SOTTO al bottone */
	char *name_button;	/*label da inserire SUL bottone */
	char *name_bmp;	/*nome del bitmap da caricare*/
	char *command;	/*comando da eseguire con la System */
        /*
          variabili di stato (privato)
        */
	GC norm_gc;            /* GC normale  */
	GC clear_gc;           /* GC per sbiancamento  */
        XFontStruct *font_info;
        XmFontList font_list;
	Pixmap bitmap_norm;	/*Bitmap da caricare*/
	int button_width;	/*ampiezza bottone*/
	int button_height;	/*altezza bottone*/
	Widget text;
	Widget bottone;
	} XlChangePagePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlChangePageRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlChangePagePart  changePage;
	} XlChangePageRec;
#endif /* _XlChangePageP_h */
