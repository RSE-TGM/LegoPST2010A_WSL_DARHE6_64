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
   modulo XlLedP.h
   tipo 
   release 5.2
   data 12/4/95
   reserved @(#)XlLedP.h	5.2
*/
/*
 * LedP.h - definizioni private per l'oggetto Led
 */ 
#ifndef _XlLedP_h
#define _XlLedP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlLed.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlLedClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlLedClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlLedClassPart    xlled_class;
	} XlLedClassRec;

extern XlLedClassRec xlLedClassRec;

/*
 Nuovi campi per il record del widget XlLed
 */
typedef struct {
	/* risorse  */
	int tipo_led;   /* tipo di led */
	int alterna;    /* per la gestione del blink */
	Pixel color_norm;
	Pixel color_blink;
	float frequenza1; /*frequenza1 di blink */	
	float frequenza2; /*frequenza2 di blink */
        
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

	char *str_input_blink2;    /* label della 2a variabile di blink
                                    seguita dal nome del modello
                                    cui di riferisce e tipo di
                                    elaboraz. sulla
                                    variabile di blink */                                 
        /*
          variabili di stato (privato)
        */
	XtIntervalId time_id; 
        GC norm_gc;           /* GC nuormal  */
        GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC blink_gc;          /* GC blink */
        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input_colore;
        PUNT_VARINP input_blink;
        PUNT_VARINP input_blink2; /*2a var di blink*/

	} XlLedPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlLedRec {
	CorePart   core;
	XlCorePart xlcore;
	XlLedPart  led;
	} XlLedRec;

#endif /* _XlLedP_h */
