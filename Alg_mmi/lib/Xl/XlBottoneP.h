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
   modulo XlBottoneP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlBottoneP.h	5.1
*/
/*
   modulo XlBottoneP.h
   tipo 
   release 1.1
   data 6/16/93
   reserved @(#)XlBottoneP.h	1.1
*/
/*
 * XlBottoneP.h - definizioni private per l'oggetto XlBottone
 */ 
#ifndef _XlBottoneP_h
#define _XlBottoneP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlCoreP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlBottone.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;    /* dummy field */
	} XlBottoneClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlBottoneClassRec {
	 CoreClassPart         core_class;
	 XlCoreClassPart       xlcore_class;
	 XlBottoneClassPart    xlbottone_class;
	} XlBottoneClassRec;

extern XlBottoneClassRec xlBottoneClassRec;

/*
 Nuovi campi per il record del widget XlBottone
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground nello stato normale */
        Pixel act_fg;   /* foreground nello stato attivato */
        Pixel norm_bg;  /* background nello stato normale */
        int tipo_bt;  /* tipo di bottone */
        Pixel color_lamp; /* colore della lampada */
	Pixel color_blink; /* colore stato blinkante */
	int blink_on;      /* 1 se lampada in stato blinkante */

        /* 
          risorse connesse con sistema di simulazione 
          da usarsi per la compilazione
        */
	char *str_input_colore;  /* label della variabile di
                                    illuminazione : la stringa e'
				    seguita dal tipo di
 				    elaborazione richiesta
                                    Es: NEG per negazione */
	char *str_input_blink;   /* label della variabile di blink
        			    seguita dal nome del modello
				    cui di riferisce e tipo di
                                    elaboraz. sulla
                                    variabile di blink */
	char *str_output;        /* label della variabile di output
                                    seguita da modello di
                                    appartenenza e tipo di
                                    perturbazione richiesta */
	/* 
	  variabili di stato (privato) 
        */
        GC norm_gc;           /* GC stato normale  */
	GC norm_bg_gc;        /* GC background bottone
                                    stato normale */
	GC act_gc;            /* GC stato attivato */
        GC clear_gc;  	      /* GC sbiancamento iniziale pixmap */
	GC lamp_gc;	      /* GC colorazione lampada */
	GC blink_gc;          /* GC lampada in stato di blinking */
	int alterna; /* per realizzazione blinking */
	Boolean  premuto;     /* registra la pressione del bottone*/

        /* 
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata 
        */
	PUNT_VAROUT out;
        PUNT_VARINP input_colore;
        PUNT_VARINP input_blink;

	} XlBottonePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlBottoneRec {
	CorePart core;
	XlCorePart xlcore;
	XlBottonePart bottone;
	} XlBottoneRec;

#endif /* _XlBottoneP_h */
