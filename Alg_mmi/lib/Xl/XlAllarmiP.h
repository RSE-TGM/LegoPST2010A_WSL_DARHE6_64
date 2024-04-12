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
   modulo XlAllarmiP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlAllarmiP.h	5.1
*/
/*
 * AllarmiP.h - definizioni private per l'oggetto Allarmi
 */ 
#ifndef _XlAllarmiP_h
#define _XlAllarmiP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
#include <Cs/Cs.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlAllarmi.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlAllarmiClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlAllarmiClassRec {
	 CoreClassPart     core_class;
         CompositeClassPart  composite_class;
         XlManagerClassPart   xlmanager_class;
	 XlAllarmiClassPart    xlallarmi_class;
	} XlAllarmiClassRec;

extern XlAllarmiClassRec xlAllarmiClassRec;

/*
 Nuovi campi per il record del widget XlAllarmi
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground  */
	Pixel troughScrollBar;  /* trough color scrollBar  */
	char * normalfont;  /* nome del font utilizzato per le scritte */
	char * titolofont;  /* nome del font utilizzato per le scritte 
				dei titoli */
	int zone[NUMERO_ZONE];
	int database_allarmi;

        /*
        puntatore alla struttura delle variabili di stato
        del grafico (la struttura e' definita in XlAllarmi.h)
        */
        S_XLALLARMI *p;
        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
	XFontStruct *font_info;
	XmFontList font_list;
	XFontStruct *font_info_titolo;
	XmFontList font_list_titolo;
	int codice_ret;
	DATI_ALLARMI_SHM old_allarmi;
	} XlAllarmiPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlAllarmiRec {
        CorePart   core;
        CompositePart  composite;
        XlManagerPart  xlmanager;
	XlAllarmiPart  allarmi;
	} XlAllarmiRec;

#endif /* _XlAllarmiP_h */
