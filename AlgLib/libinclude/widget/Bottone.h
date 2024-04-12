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
   modulo Bottone.h
   tipo 
   release 1.2
   data 3/23/95
   reserved @(#)Bottone.h	1.2
*/
/*
 * Bottone.h - file di include pubblico per l'utilizzo del widget
 *             bottone
 */
#ifndef _Bottone_h
#define _Bottone_h

/*
 nomi di risorse utilizzate internamente al bottone
 */
#define XtNactFg "actFg"
#define XtCActFg "ActFg"
#define XtNtipoBt "tipoBt"
#define XtCTipoBt "TipoBt"
#define XtNcolorLamp "colorLamp"
#define XtCColorLamp "ColorLamp"
#define XtNcolorBlink "colorBlink"
#define XtCColorBlink "ColorBlink"
#define XtNblinkOn "blinkOn"
#define XtCBlinkOn "BlinkOn"
#define XtNnormFg "normFg"
#define XtCNormFg "NormFg"
#define XtNnormBg "normBg"
#define XtCNormBg "NormBg"

#define XtNpressBtCallback "pressBtCallback"
#define XtCPressBtCallback "PressBtCallback"
#define XtNreleaseBtCallback "releaseBtCallback"
#define XtCReleaseBtCallback "ReleaseBtCallback"

/* costanti utilizzabili per settare il tipo di bottone */
#define BOTTONE  0
#define BOTTONE_CON_LUCE  1
#define BOTTONE_LUCE      2

/* declare the class constant */
extern WidgetClass bottoneWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Bottone */
typedef struct _BottoneClassRec *BottoneWidgetClass;
typedef struct _BottoneRec *BottoneWidget;

#endif /* _Bottone_h */

