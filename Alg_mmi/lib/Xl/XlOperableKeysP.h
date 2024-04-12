/**********************************************************************
*
*       C Header:               XlOperableKeysP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Wed Sep  3 15:29:18 1997 %
*
**********************************************************************/
/*
 * XlOperableKeysP.h.h - definizioni private per l'oggetto OperableKeys
 */ 
#ifndef _XlOperableKeysP_h
#define _XlOperableKeysP_h
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
#include <Xl/XlOperableKeys.h>

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;
	} XlOperableKeysClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlOperableKeysClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlOperableKeysClassPart   xloperableKeys_class;
	} XlOperableKeysClassRec;

extern XlOperableKeysClassRec xlOperableKeysClassRec;

/*
 Nuovi campi per il record del widget XlOperableKeys
 */
typedef struct {
        /* risorse  */
	Pixel norm_fg;  	/* foreground bitmap o label interna */
	Pixel hstate_bg;  	/* background bottone corrispondente a stato 1 var input */
	Pixel lstate_bg;  	/* background bottone corrispondente a stato 0 var input */
	char * normalfont;  	/* nome del font utilizzato per le scritte */
	int tipo;       	/* tipo DIRECT,IMP,EXEC (o OPENEXT2 se verra' implementato) */
	int draw;		/* modalita' bitmap o label */
	int drawPush;		/* effetto bottone premuto */
	int fill_button;	/* modalita' con o senza bordo */
	char *label;    	/* label da inserire SOTTO al bottone */
	char *button_label;	/* label da inserire SUL bottone */
	char *name_bmp;	        /* nome del bitmap da caricare */
	char *str_var_input;    /* str variabile di input del bottone (animazione bottone) */
	char *str_var_output;   /* str variabile di attivazione (perturbazione da inviare) */
	char *str_var_output2;  /* seconda str variabile di attivazione (seconda perturbazione) */

        /*
          variabili di stato (privato)
        */
        Boolean (*ExecuteCB)();
        int impAble;		/* abilitazione invio pert tipo IMPULSE */
	GC hstate_gc;           /* GC stato 1 variabile di input */
	GC lstate_gc;		/* GC stato 0 variabile input */
	GC clear_gc;           	/* GC per sbiancamento  */
        XFontStruct *font_info; /* font per le scritte */
        XmFontList font_list;
	Pixmap bitmap_lstate;	/* Bitmap da caricare con input var == 0*/
	Pixmap bitmap_hstate;	/* Bitmap da caricare con input var == 1*/
	Pixmap bitmap_norm;	/* Bitmap da caricare */
	int button_width;	/* ampiezza bottone */
	int button_height;	/* altezza bottone */
	Widget text;		/* testo del bottone */
	Widget bottone;         /* id del bottone motif associato */
	PUNT_VARINP var_input;  /* variabile di input del bottone */
	PUNT_VAROUT var_output; /* variabile di attivazione (perturbazione) */
	PUNT_VAROUT var_output2; /* seconda variabile di attivazione (perturbazione) */
	} XlOperableKeysPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlOperableKeysRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlOperableKeysPart  operableKeys;
	} XlOperableKeysRec;
#endif /* _XlOperableKeysP_h */
