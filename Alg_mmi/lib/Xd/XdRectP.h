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
   modulo XdRectP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdRectP.h	5.1
*/
/* XdRectP.h
 *         oggetto base per draw
 */
#ifndef XdRectP_h
#define XdRectP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdRect.h>
/******************************************************
 * Rect Class Structure
 ******************************************************/

typedef struct  {
		int dummy;
		} XdRectClassPart;

typedef struct _XdRectClassRec {
		DragetClassPart xdcore_class;
		XdRectClassPart xdrect_class;
		} XdRectClassRec;

extern XdRectClassRec xdRectClassRec;

/*****************************************************
 * Rect data structures
 *****************************************************/

typedef struct {
	Position xf,yf;   /* posizione del secondo punto della linea */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	} XdRectPart;

typedef struct _XdRectRec {
		XdCorePart xdcore;
		XdRectPart xdrect;
		} XdRectRec;

#endif /* XdRectP_h */
