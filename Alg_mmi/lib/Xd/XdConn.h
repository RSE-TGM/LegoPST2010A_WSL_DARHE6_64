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
   modulo XdConn.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdConn.h	5.1
*/
/*  XdConn.h
 *       oggetto XdConn - connessione
 *                       
 */
#ifndef _XdConn_h
#define _XdConn_h
typedef struct _XdConnClassRec *XdConnDragetClass;
typedef struct _XdConnRec *XdConnDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreateConnDraget(Widget, GC, GC);

#endif /* _XdConn_h */

