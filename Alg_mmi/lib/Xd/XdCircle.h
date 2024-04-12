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
   modulo XdCircle.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdCircle.h	5.1
*/
/*  XdCircle.h
 *       oggetto XdCircle - linea
 *                       
 */
#ifndef _XdCircle_h
#define _XdCircle_h
typedef struct _XdCircleClassRec *XdCircleDragetClass;
typedef struct _XdCircleRec *XdCircleDraget;
/*
 Funzioni di uso esterno
*/
Draget XdCreateCircleDraget(Widget, GC, GC);
Draget XdCreateArcDraget(Widget, GC, GC);
#define XD_TY_CIRCLE   0
#define XD_TY_ARC      1
#endif /* _XdCircle_h */

