/**********************************************************************
*
*       C Header:               XlIndicErr.h
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Wed Oct 23 15:53:44 2002 %
*
**********************************************************************/
/*
   modulo XlIndicErr.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIndicErr.h	5.1
*/
/*
 * XlIndicErr.h - file di include pubblico per l'utilizzo del widget
 *             indicErr
 */
#ifndef _XlIndicErr_h
#define _XlIndicErr_h


/*
 nomi di risorse utilizzate internamente al indicErr
 */
#define XlNagoFg_err   "agoFg"
#define XlCAgoFg_err   "AgoFg"
#define XlDagoFg_err   "Ago color"


#define _INDIC_MAX_err     3
#define NO_ROTABLE         0
#define ROTABLE            1


/* declare the class constant */
extern WidgetClass xlIndicErrWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di IndicErr */
typedef struct _XlIndicErrClassRec *XlIndicErrWidgetClass;
typedef struct _XlIndicErrRec *XlIndicErrWidget;

#endif /* _XlIndicErr_h */

