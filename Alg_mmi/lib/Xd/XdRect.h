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
   modulo XdRect.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdRect.h	5.1
*/
/*  XdRect.h
 *       oggetto XdRect - linea
 *                       
 */
#ifndef _XdRect_h
#define _XdRect_h
typedef struct _XdRectClassRec *XdRectDragetClass;
typedef struct _XdRectRec *XdRectDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreateRectDraget(Widget, GC, GC);
#endif /* _XdRect_h */

