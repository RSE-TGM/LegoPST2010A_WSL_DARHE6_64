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
   modulo XlSetValoreP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSetValoreP.h	5.1
*/
/*
 * XlSetValoreP.h.h - definizioni private per l'oggetto SetValore
 */ 
#ifndef _XlSetValoreP_h
#define _XlSetValoreP_h
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
#include <Xl/XlSetValore.h>

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;
	} XlSetValoreClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlSetValoreClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlSetValoreClassPart   xlsetValore_class;
	} XlSetValoreClassRec;

extern XlSetValoreClassRec xlSetValoreClassRec;

/*
 Nuovi campi per il record del widget XlSetValore
 */
typedef struct {
        /* risorse  */
	Pixel norm_fg;  /* foreground nello stato normale */
	char * normalfont;  /* nome del font utilizzato per le scritte */
	int numero_int; /* numero di interi nei numeri rappresentati */
        int numero_dec; /* numero di decimali nei numeri rappresentati */
        float scalamento; /* scalamento della variabile di ingresso */
        float offset;     /* offset della variabile di ingresso */
	/*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
        char *str_inibit;
	char *str_input;
	char *str_rltarget;
	char *str_output;

        /*
          variabili di stato (privato)
        */
	Boolean premuto;
	GC norm_gc;            /* GC normale  */
	GC clear_gc;           /* GC per sbiancamento  */
        XFontStruct *font_info;
        XmFontList font_list;
	Widget text;
	Widget bottone;
	/*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP inibit;
        PUNT_VARINP input;
	PUNT_VAROUT rltarget;
	PUNT_VAROUT output;
	float old_valore;
	int old_inibit;
	} XlSetValorePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlSetValoreRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlSetValorePart  setValore;
	} XlSetValoreRec;

#endif /* _XlSetValoreP_h */
