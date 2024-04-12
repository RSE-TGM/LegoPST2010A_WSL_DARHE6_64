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
   modulo XdLine.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdLine.h	5.1
*/
/*  XdLine.h
 *       oggetto XdLine - linea
 *                       
 */
#ifndef _XdLine_h
#define _XdLine_h
typedef struct _XdLineClassRec *XdLineDragetClass;
typedef struct _XdLineRec *XdLineDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreateLineDraget(Widget, GC, GC);

#endif /* _XdCore_h */

