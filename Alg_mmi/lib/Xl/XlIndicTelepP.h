/**********************************************************************
*
*       C Header:               XlIndicTelepP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Wed Jun  4 15:45:50 1997 %
*
**********************************************************************/
/*
   modulo XlIndicTelepP.h
   tipo 
   release 1.0
   data 21/5/96
   reserved @(#)XlIndicTelepP.h	1.0
*/
/*
 * IndicTelepP.h - definizioni private per l'oggetto IndicTelep
 */ 
#ifndef _XlIndicTelepP_h
#define _XlIndicTelepP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlIndicTelep.h>

/*
 Strutture relative alla nuova Classe
*/
typedef struct {
	int empty;
	} XlIndicTelepClassPart;
/*
 Dichiarazione del record completo di classe
*/
typedef struct _XlIndicTelepClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlIndicTelepClassPart    xlindicTelep_class;
	} XlIndicTelepClassRec;

extern XlIndicTelepClassRec xlIndicTelepClassRec;

/*
 Nuovi campi per il record del widget XlIndicTelep
 */
typedef struct {
	/* risorse  */
        Pixel ago_fg;   /* ago  */
        Pixel bordino_fg;   /* bordino per led e indicatore stringa  */
        int bordino_width;  /* spessore del bordino */
	int tipo_ind;   /* tipo di indicatore */
	int numero_int; /* numero di interi nei numeri rappresentati */
	int numero_dec; /* numero di decimali nei numeri rappresentati */
	float scalamento; /* scalamento della variabile di ingresso */
	float valore_minimo; /* valore minimo della variabile di ingresso */
	float valore_massimo; /* valore massimo della variabile di ingresso */
	float extra_range_sup; /*extra range superiore */
	float offset;     /* offset della variabile di ingresso */
	char * normalfont;  /* nome del font utilizzato per le scritte */
	int primo_refresh;

	char * indicText;  /* testo stringa interno indicatore */

        /* struttura per la gestione del colore del frame
        */
        CAMBIO_COLORE_FRAME frame;

        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
        char *str_input;         /* label della variabile di
                                    ingresso monitorata dall'in-
				    dicatore
				  */
	/* struttura per la gestione del cambio colore
           della variabile da visualizzare e della variabile di fault
        */
        CAMBIO_COLORE_VAR cambio_colore[1];
        CAMBIO_COLORE_VAR colore_fault[2];

        /*
          variabili di stato (privato)
        */
        Boolean operable;     /* True se viene configurato il frame */
        Boolean owOpen;       /* gestione del frame */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC  */
        GC ago_gc;            /* GC Fg stato normale */
        GC bordino_gc;            /* GC per bordino indicatori (led e stringa) */
	XFontStruct *font_info;
	XmFontList font_list;
	float old_posizione;
	float old_frameval;
	FLAG_MMI OldFlag;
	Pixel OldPixel;
	Position starting_x;  /* posizione x iniziale indicatore istogr. */
	Position starting_y;  /* posizione y iniziale indicatore istogr. */
	Boolean  blinking;    /* stato di blink */

        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input;

	} XlIndicTelepPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlIndicTelepRec {
	CorePart   core;
	XlCorePart xlcore;
	XlIndicTelepPart  indic;
	} XlIndicTelepRec;

#endif /* _XlIndicTelepP_h */
