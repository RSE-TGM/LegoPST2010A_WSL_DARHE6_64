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
   modulo XlIndicP.h
   tipo 
   release 5.3
   data 1/5/96
   reserved @(#)XlIndicP.h	5.3
*/
/*
 * IndicP.h - definizioni private per l'oggetto Indic
 */ 
#ifndef _XlIndicP_h
#define _XlIndicP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlIndic.h>
/*
 Strutture relative alla nuova Classe
 */




typedef struct {
	int empty;
	} XlIndicClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlIndicClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlIndicClassPart    xlindic_class;
	} XlIndicClassRec;

extern XlIndicClassRec xlIndicClassRec;

/*
 Nuovi campi per il record del widget XlIndic
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground  */
        Pixel ago_fg;   /* ago  */
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

        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
        char *str_input;         /* label della variabile di
                                    ingresso monitorata dall'in-
				    dicatore
				  */
	/*
                struttura per la gestione del cambio colore
        */
        CAMBIO_COLORE cambio_colore[1];

        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC ago_gc;            /* GC ago indicatore */
	XFontStruct *font_info;
	XmFontList font_list;
	float old_posizione;
	FLAG_MMI OldFlag;
	Pixel OldPixel;
	Position starting_x;  /* posizione x iniziale indicatore istogr. */
	Position starting_y;  /* posizione y iniziale indicatore istogr. */

        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input;

	} XlIndicPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlIndicRec {
	CorePart   core;
	XlCorePart xlcore;
	XlIndicPart  indic;
	} XlIndicRec;

#endif /* _XlIndicP_h */
