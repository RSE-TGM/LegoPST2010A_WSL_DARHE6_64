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
   modulo XlDispReg.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlDispReg.h	5.1
*/
/*
 * XlDispReg.h - file di include pubblico per l'utilizzo del widget
 *             dispReg
 */
#ifndef _XlDispReg_h
#define _XlDispReg_h

/*
 nomi di risorse utilizzate internamente al dispReg
 */
#define XlNnormalFont "normalFont"
#define XlCNormalFont "NormalFont"
#define XlDnormalFont "Font"

#define XlNdispRegTagSave "dispRegTagSave"
#define XlCDispRegTagSave "DispRegTagSave"

#define XlNdispRegMode "dispRegMode"
#define XlCDispRegMode "DispRegMode"
#define XlDdispRegMode "DispReg Mode"
#define XlOdispRegMode "Tag mode,Value mode,Unmanaged"

#define XlNdispRegBehavior "dispRegBehavior"
#define XlCDispRegBehavior "DispRegBehavior"
#define XlDdispRegBehavior "Run-time behavior"
#define XlOdispRegBehavior "Value,Vertical bar,Horizontal bar"

/* costanti utilizzabili per settare il tipo di XlDispReg */
#define DISPREG_UNMANAGED	0
#define DISPREG_TAG		1
#define DISPREG_MODUL		2
#define DISPREG_VALUE		3

#define VALUE_BEHAVIOR			0
#define VERTICAL_BAR_BEHAVIOR		1
#define HORIZONTAL_BAR_BEHAVIOR		2
#define DEFAULT_BEHAVIOR	VALUE_BEHAVIOR


/*
	momentaneamente
*/
#define DISP_TAG_MODE       DISPREG_TAG
#define DISP_VALUE_MODE       DISPREG_VALUE
#define DISP_UNMANAGED_MODE       DISPREG_UNMANAGED

#define DISP_TAG_DEFAULT_MODE		DISPREG_TAG

/* declare the class constant */
extern WidgetClass xlDispRegWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di DispReg */
typedef struct _XlDispRegClassRec *XlDispRegWidgetClass;
typedef struct _XlDispRegRec *XlDispRegWidget;

/*
	funzioni richiamabili dall'esterno
*/
Boolean XlIsDispReg();
Boolean XlCheckDispReg(Widget );

#endif /* _XlDispReg_h */

