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
   modulo XlSelettoreP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSelettoreP.h	5.1
*/
/*
 * XlSelettoreP.h - definizioni private per l'oggetto XlSelettore
 */ 
#ifndef _XlSelettoreP_h
#define _XlSelettoreP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlCoreP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlSelettore.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;    /* dummy field */
	} XlSelettoreClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlSelettoreClassRec {
	 CoreClassPart         core_class;
	 XlCoreClassPart       xlcore_class;
	 XlSelettoreClassPart    xlselettore_class;
	} XlSelettoreClassRec;

extern XlSelettoreClassRec xlSelettoreClassRec;

/*
 Nuovi campi per il record del widget XlSelettore
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground */
        Pixel norm_bg;  /* background */
        Pixel selettore_fg;  /* foreground del selettore */
        int tipo_sel;   /* tipo di selettore */
        /* 
          risorse connesse con sistema di simulazione 
          da usarsi per la compilazione
        */
	char *str_output;        /* label della variabile di output
                                    seguita da modello di
                                    appartenenza e tipo di
                                    perturbazione richiesta */
	char *str_input;        /* label della variabile di input
                                    seguita da modello di
                                    appartenenza            */
	/* 
	  variabili di stato (privato) 
        */
        GC norm_gc;           /* GC stato normale  */
	GC norm_bg_gc;        /* GC background selettore
                                    stato normale */
	GC selettore_gc;      /* GC del selettore   */
        GC clear_gc;  	      /* GC sbiancamento iniziale pixmap */
	Boolean  premuto;     /* registra la pressione del selettore*/
	Boolean  old_premuto; /* registra la vecchia condizione*/

        /* 
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata 
        */
	PUNT_VAROUT out;
	PUNT_VARINP input;
	} XlSelettorePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlSelettoreRec {
	CorePart core;
	XlCorePart xlcore;
	XlSelettorePart selettore;
	} XlSelettoreRec;

#endif /* _XlSelettoreP_h */
