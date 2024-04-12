/**********************************************************************
*
*       C Header:               XlCompositeP.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Sep 22 16:09:08 1998 %
*
**********************************************************************/
/*
   modulo XlCompositeP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlCompositeP.h	5.1
*/
/*
 * CompositeP.h - definizioni private per l'oggetto Composite
 */ 
#ifndef _XlCompositeP_h
#define _XlCompositeP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
/*
 Inclusione dell'header file pubblico
*/
#include "XlComposite.h"

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;
	} XlCompositeClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlCompositeClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlCompositeClassPart   xlcomposite_class;
	} XlCompositeClassRec;

extern XlCompositeClassRec xlCompositeClassRec;

/*
 Nuovi campi per il record del widget XlComposite
 */
typedef struct {
	/* risorse  */
	char *composite_name;
        int rotate;     /* rotazione in senso orario di 90 gradi, 0,1,2,3  */
        int ass_rotate; /* rotazione rispetto all'asse delle Y posizionato
                           a width/2                                       */
	int num_figli;  /* numero dei figli da creare */
	int childrenLayout;  /* se == 1 gestisce il layout dei figli dopo
				un resize */
	char *list_children; /* lista di nomi e classi cui
				 appartengono i figli */
        /* privato */
	AN_OBJ *pfigli;
	XlNormRectangle *prect_figli; /* dimensioni e posizioni dei figli
                                         rispetto al padre */
        int fatt_zoom_last;           /* ultimo fattore di zoom */
	} XlCompositePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlCompositeRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlCompositePart  xlcomposite;
	} XlCompositeRec;

#endif /* _XlCompositeP_h */
