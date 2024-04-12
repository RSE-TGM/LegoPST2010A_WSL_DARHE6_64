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
   modulo XlLed.h
   tipo 
   release 5.2
   data 12/4/95
   reserved @(#)XlLed.h	5.2
*/
/*
 * XlLed.h - file di include pubblico per l'utilizzo del widget
 *             led
 */
#ifndef _XlLed_h
#define _XlLed_h

#include <stdlib.h>
/*
 nomi di risorse utilizzate internamente al led
 */
#define XlNtipoLed "tipoLed"
#define XlCTipoLed "TipoLed"
#define XlDtipoLed "Led type"
#define XlOtipoLed "Rectangular,Circular"

/* costanti utilizzabili per settare il tipo di XlIndic */

#define LED_RETTANGOLARE  0
#define LED_ROTONDO  1
#define LED_DEFAULT  LED_RETTANGOLARE
#define _LED_MAX     1
#define BLINK_ON_FQZ1     2
#define BLINK_ON_FQZ2     3
#define FREQUENZA1	"0.5"
#define FREQUENZA2	"2.0"
/* definizioni delle variabili risorse */

#define XlNfrequenza1   "frequenza1"
#define XlCFrequenza1   "Frequenza1"
#define XlDfrequenza1   "Variabile 1a frequenza(Hz) [max.4Hz]"
#define XlNfrequenza2   "frequenza2"
#define XlCFrequenza2   "Frequenza2"
#define XlDfrequenza2   "Variabile 2a frequenza(Hz) [max.4Hz]"
#define XlNvarInputBlink2   "varInputBlink2"
#define XlCVarInputBlink2   "VarInputBlink2"
#define XlDvarInputBlink2   "Variabile di Blink 2"
float frequenza_letta;
/* declare the class constant */
extern WidgetClass xlLedWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Led */
typedef struct _XlLedClassRec *XlLedWidgetClass;
typedef struct _XlLedRec *XlLedWidget;

#endif /* _XlLed_h */

