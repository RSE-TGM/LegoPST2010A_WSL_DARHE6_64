/**********************************************************************
*
*       C Header:               XlManager.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Thu Nov 27 17:59:27 1997 %
*
**********************************************************************/
/*
   modulo XlManager.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlManager.h	5.1
*/
/*
 * XlManager.h - file di include pubblico per l'utilizzo del widget
 *             led
 */
#ifndef _XlManager_h
#define _XlManager_h

#define DEFAULT_ULEVEL  0   /* user level default value */

/*
 nomi di risorse utilizzate internamente al led
 */
#define XlNlistChildren "listChildren"
#define XlCListChildren "ListChildren"
#define XlNnumFigli "numFigli"  /* numero figli nella lista */
#define XlCNumFigli "NumFigli"

#define XlNobjectTag "objectTag"
#define XlCObjectTag "ObjectTag"
#define XlDObjectTag "Object Tag"

#define XlNuserLevel       "userLevel"
#define XlCUserLevel       "UserLevel"
#define XlDuserLevel       "User Level"


/* declare the class constant */
extern WidgetClass xlManagerWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Manager */
typedef struct _XlManagerClassRec *XlManagerWidgetClass;
typedef struct _XlManagerRec *XlManagerWidget;
 
#endif /* _XlManager_h */

