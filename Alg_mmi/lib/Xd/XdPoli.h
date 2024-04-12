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
   modulo XdPoli.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdPoli.h	5.1
*/
/*  XdPoli.h
 *       oggetto XdPoli - poligono
 *                       
 */
#ifndef _XdPoli_h
#define _XdPoli_h
typedef struct _XdPoliClassRec *XdPoliDragetClass;
typedef struct _XdPoliRec *XdPoliDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreatePoliDraget(Widget, GC, GC);

#endif /* _XdPoli_h */

