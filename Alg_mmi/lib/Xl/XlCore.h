/**********************************************************************
*
*       C Header:               XlCore.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Aug 28 11:31:54 2003 %
*
**********************************************************************/
/*
   modulo XlCore.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlCore.h	5.1
*/
/*
 * XlCore.h - file di include pubblico per l'utilizzo del widget
 *             legocore
 */
#ifndef _XlCore_h
#define _XlCore_h

#define DEFAULT_ULEVEL	0   /* user level default value */

/*
 nomi di risorse utilizzate internamente a XlCore
 */
#define XlNrotate "rotate"
#define XlCRotate "Rotate"
#define XlDrotate "Rotate (clockwise)"
#define XlOrotate "0,90,180,270"
#define XlNassRotate "assRotate"
#define XlCAssRotate "AssRotate"
#define XlDassRotate "Rotate on Y axis"
#define XlOassRotate "No,Yes"
#define XlNtrasparent "trasparent"
#define XlCTrasparent "Trasparent"
#define XlDtrasparent "Trasparent attribute"
#define XlOtrasparent "No,Yes"

#define XlNobjectTag "objectTag"
#define XlCObjectTag "ObjectTag"
#define XlDobjectTag "Object TAG"


#define XlNuserLevel       "userLevel"
#define XlCUserLevel       "UserLevel"
#define XlDuserLevel       "User Level"

/*
	define per la gestione della trasparenza, il default e' NO_TRASPARENT
*/
#define NO_TRASPARENT	False
#define TRASPARENT	True

/*
	dimensione del quadrato per la selezione
*/
#define DIM_Q_SEL	6

/* declare the class constant */
extern WidgetClass xlCoreWidgetClass;


/* dichiarazione tipi per Classe e Instanziazione di XlCore */
typedef struct _XlCoreClassRec *XlCoreWidgetClass;
typedef struct _XlCoreRec *XlCoreWidget;

// Prototyping della funzione XlAddBlink ( nel file XlWidgetUtil.c)
Boolean XlAddBlink(Widget, int , float , void * );

#endif /* _XlCore_h */

