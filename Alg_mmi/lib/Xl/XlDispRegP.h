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
   modulo XlDispRegP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlDispRegP.h	5.1
*/
/*
 * DispRegP.h - definizioni private per l'oggetto DispReg
 */ 
#ifndef _XlDispRegP_h
#define _XlDispRegP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlDispReg.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	XlCheckDispRegFunc checkDispReg;    /* metodo per il controllo
                                       della consistenza di un dispReg */
	} XlDispRegClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlDispRegClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlDispRegClassPart    xldispReg_class;
	} XlDispRegClassRec;

extern XlDispRegClassRec xlDispRegClassRec;

/*
 Nuovi campi per il record del widget XlDispReg
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground  */
	char * normalfont;  /* nome del font utilizzato per le scritte */
        int dispReg_mode;
        int dispReg_behavior;
        int numero_int; /* numero di interi nei numeri rappresentati */
        int numero_dec; /* numero di decimali nei numeri rappresentati */
        float scalamento; /* scalamento della variabile di ingresso */
        float valore_minimo; /* valore minimo della variabile di ingresso */
        float valore_massimo; /* valore massimo della variabile di ingresso */
        float offset;     /* offset della variabile di ingresso */
	char *tagSave;   /* tag salvata per funzionamento in run-time */


	/*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
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
	XFontStruct *font_info;
	XmFontList font_list;
	FLAG_MMI OldFlag;
        Pixel OldPixel;
    
        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input;


	} XlDispRegPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlDispRegRec {
	CorePart   core;
	XlCorePart xlcore;
	XlDispRegPart  dispReg;
	} XlDispRegRec;

#endif /* _XlDispRegP_h */
