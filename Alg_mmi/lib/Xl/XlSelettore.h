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
   modulo XlSelettore.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSelettore.h	5.1
*/
/*
 * XlSelettore.h - file di include pubblico per l'utilizzo del widget
 *             xlSelettore
 */
#ifndef _XlSelettore_h
#define _XlSelettore_h
/*
 nomi di risorse utilizzate internamente al xlSelettore
	XlN....   nome della risorsa
	XlC....   nome della classe
	XlD....   descrizione per la configurazione ( inserita nella
                  struttura confinfo).
	XlO....   descrizioni delle opzioni disponibili (nel caso 
		  di risorsa del tipo enumerated option
 */
#define XlNtipoSel "tipoSel"
#define XlCTipoSel "TipoSel"
#define XlDtipoSel "Selector type"
#define XlOtipoSel "Simple selector,Selector with key"
#define XlNselettoreFg "selettoreFg"
#define XlCSelettoreFg "SelettoreFg"
#define XlDselettoreFg "Selector color"

/* costanti utilizzabili per settare il tipo di xlSelettore */

#define SELETTORE  0
#define SELETTORE_CON_CHIAVE  1

/* declare the class constant */
extern WidgetClass xlSelettoreWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di XlSelettore */
typedef struct _XlSelettoreClassRec *XlSelettoreWidgetClass;
typedef struct _XlSelettoreRec *XlSelettoreWidget;

#endif /* _XlSelettore_h */

