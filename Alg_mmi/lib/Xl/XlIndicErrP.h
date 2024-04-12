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
   modulo XlIndicErrP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIndicErrP.h	5.1
*/
/*
 * IndicErrP.h - definizioni private per l'oggetto IndicErr
 */ 
#ifndef _XlIndicErrP_h
#define _XlIndicErrP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlIndicErr.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlIndicErrClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlIndicErrClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlIndicErrClassPart    xlindicErr_class;
	} XlIndicErrClassRec;

extern XlIndicErrClassRec xlIndicErrClassRec;

/*
 Nuovi campi per il record del widget XlIndicErr
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground  */
        Pixel ago_fg;   /* ago  */
	int numero_int; /* numero di interi nei numeri rappresentati */
	int numero_dec; /* numero di decimali nei numeri rappresentati */
	float scalamento; /* scalamento della variabile di ingresso */
	float valore_minimo; /* valore minimo della variabile di ingresso */
	float valore_massimo; /* valore massimo della variabile di ingresso */
	float offset;     /* offset della variabile di ingresso */
	float scalamento_err; /* scalamento della variabile di ingresso */
	float valore_minimo_err; /* valore minimo della variabile di ingresso */
	float valore_massimo_err; /* valore massimo della variabile 
				     di ingresso */
	float offset_err;     /* offset della variabile di ingresso */
	char * normalfont;  /* nome del font utilizzato per le scritte */

        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
        char *str_input;         /* label della variabile di
                                    ingresso monitorata dall'in-
				    dicatore
				  */
        char *str_input_err;         /* label della variabile di
                                    ingresso monitorata dall'in-
				    dicatore
				  */

        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC ago_gc;            /* GC ago indicErratore */
	XFontStruct *font_info;
	XmFontList font_list;
	float old_posizione;
	float old_posizione_err;

        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input;
        PUNT_VARINP input_err;

	} XlIndicErrPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlIndicErrRec {
	CorePart   core;
	XlCorePart xlcore;
	XlIndicErrPart  indicErr;
	} XlIndicErrRec;

#endif /* _XlIndicErrP_h */
