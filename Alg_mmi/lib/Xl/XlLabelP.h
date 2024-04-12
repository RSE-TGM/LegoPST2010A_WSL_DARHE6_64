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
   modulo XlLabelP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlLabelP.h	5.1
*/
/*
 * LabelP.h - definizioni private per l'oggetto Label
 */ 
#ifndef _XlLabelP_h
#define _XlLabelP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlLabel.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlLabelClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlLabelClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlLabelClassPart    xllabel_class;
	} XlLabelClassRec;

extern XlLabelClassRec xlLabelClassRec;

/*
 Nuovi campi per il record del widget XlLabel
 */
typedef struct {
	/* risorse  */
	Pixel norm_fg;  /* foreground  */
	int tipo_label;   /* tipo di label */
	char * labeltext;  /* testo della label */
	char * normalfont;  /* nome del font utilizzato per le scritte */

        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
	XFontStruct *font_info;
	XmFontList font_list;

	} XlLabelPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlLabelRec {
	CorePart   core;
	XlCorePart xlcore;
	XlLabelPart  label;
	} XlLabelRec;

#endif /* _XlLabelP_h */
