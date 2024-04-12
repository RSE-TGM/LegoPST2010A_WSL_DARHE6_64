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
   modulo XdCore.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdCore.h	5.1
*/
/*  XdCore.h
 *       oggetto XdCore - costituisce la superclass comune a tutti gli
 *                        oggetti per il disegno (draw)
 */
#ifndef _XdCore_h
#define _XdCore_h

#define PICK_NORMAL 0
#define PICK_EXTENDED 1

typedef struct _DragetClassRec *DragetClass;
typedef struct _DragetRec *Draget;
/*
 Definizione tipo per descrizione contesto di disegno
*/
typedef struct _XdGC {
			Widget wid;
			int width_contorno;
			int style_contorno;
			Pixel fg_contorno;
			Pixel bg_contorno;
			Pixel fg_fill;
			Boolean filled; /* se True filled */
			} XdGC;
			
/*
 Funzioni di uso esterno
*/
Draget XdCreateCoreDraget(Widget ,GC);

#endif /* _XdCore_h */

