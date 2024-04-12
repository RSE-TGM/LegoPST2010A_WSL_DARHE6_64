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
   modulo XdGroup.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdGroup.h	5.1
*/
/*  XdGroup.h
 *       oggetto XdGroup - raggruppamento di draget
 *                       
 */
#ifndef _XdGroup_h
#define _XdGroup_h
#include <Xd/XdLista.h>
typedef struct _XdGroupClassRec *XdRectGroupClass;
typedef struct _XdGroupRec *XdGroupDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreateGroupDraget(Widget, GC, GC);
Draget XdFirstGroupDraget(Widget,XdLista);
Boolean XdUngroupDraget(XdGroupDraget,XdLista);
XdLista XdGroupGetList(Draget);
#endif /* _XdGroup_h */

