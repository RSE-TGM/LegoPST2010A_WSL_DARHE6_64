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
   modulo XlBottone.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlBottone.h	5.1
*/
/*
   modulo XlBottone.h
   tipo 
   release 1.1
   data 6/16/93
   reserved @(#)XlBottone.h	1.1
*/
/*
 * XlBottone.h - file di include pubblico per l'utilizzo del widget
 *             xlBottone
 */
#ifndef _XlBottone_h
#define _XlBottone_h
/*
 nomi di risorse utilizzate internamente al xlBottone
	XlN....   nome della risorsa
	XlC....   nome della classe
	XlD....   descrizione per la configurazione ( inserita nella
                  struttura confinfo).
	XlO....   descrizioni delle opzioni disponibili (nel caso 
		  di risorsa del tipo enumerated option
 */
#define XlNtipoBt "tipoBt"
#define XlCTipoBt "TipoBt"
#define XlDtipoBt "Button type"
#define XlOtipoBt "Simple button,Button with lamp,Rectangle button,Rectangle button whith lamp"
#define XlNactFg "actFg"
#define XlCActFg "ActFg"
#define XlDactFg "Activaton color"
#define XlNcolorLamp "colorLamp"
#define XlCColorLamp "ColorLamp"
#define XlDcolorLamp "Color of internal lamp"
#define XlNblinkOn "blinkOn"
#define XlCBlinkOn "BlinkOn"
/*
 Funzioni di Callback
*/
#define XlNpressBtCallback "pressBtCallback"
#define XlCPressBtCallback "PressBtCallback"
#define XlNreleaseBtCallback "releaseBtCallback"
#define XlCReleaseBtCallback "ReleaseBtCallback"

/* costanti utilizzabili per settare il tipo di xlBottone */

#define BOTTONE  0
#define BOTTONE_CON_LUCE  1
#define BOTTONE_RETTANGOLARE  2
#define BOTTONE_RETTANGOLARE_CON_LUCE  3

/* declare the class constant */
extern WidgetClass xlBottoneWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di XlBottone */
typedef struct _XlBottoneClassRec *XlBottoneWidgetClass;
typedef struct _XlBottoneRec *XlBottoneWidget;

#endif /* _XlBottone_h */

