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
   modulo XlComposite.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlComposite.h	5.1
*/
/*
 * XlComposite.h - file di include pubblico per l'utilizzo del widget
 *             led
 */
#ifndef _XlComposite_h
#define _XlComposite_h

/*
 nomi di risorse utilizzate internamente al led
 */
#define XlNlistChildren "listChildren"
#define XlCListChildren "ListChildren"
#define XlNnumFigli "numFigli"  /* numero figli nella lista */
#define XlCNumFigli "NumFigli"

/* declare the class constant */
extern WidgetClass xlCompositeWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Composite */
typedef struct _XlCompositeClassRec *XlCompositeWidgetClass;
typedef struct _XlCompositeRec *XlCompositeWidget;
 
/* tipi ad uso della classe XlComposite */
/* Rettangolo normalizzato : viene usato per memorizzare posizioni e
   dimensioni dei figli di composite rispetto al contenitore composite
   stesso
*/
typedef struct {
    float nx, ny;
    float nwidth, nheight;
} XlNormRectangle;

#endif /* _XlLed_h */

