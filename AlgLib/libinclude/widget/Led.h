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
   modulo Led.h
   tipo 
   release 1.2
   data 3/23/95
   reserved @(#)Led.h	1.2
*/
/*
 * Led.h - file di include pubblico per l'utilizzo del widget
 *             led
 */
#ifndef _Led_h
#define _Led_h

/*
 nomi di risorse utilizzate internamente al led
 */
#define XtNledBlinkOn "ledBlinkOn"
#define XtCLedBlinkOn "LedBlinkOn"
#define XtNledColorBlink "ledColorBlink"
#define XtCLedColorBlink "LedColorBlink"

/* declare the class constant */
extern WidgetClass ledWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Led */
typedef struct _LedClassRec *LedWidgetClass;
typedef struct _LedRec *LedWidget;

#endif /* _Led_h */

