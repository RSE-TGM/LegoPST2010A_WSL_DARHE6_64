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
   modulo XdLineP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdLineP.h	5.1
*/
/* XdLineP.h
 *         oggetto base per draw
 */
#ifndef XdLineP_h
#define XdLineP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdLine.h>
/******************************************************
 * Line Class Structure
 ******************************************************/

typedef struct  {
		int dummy;
		} XdLineClassPart;

typedef struct _XdLineClassRec {
		DragetClassPart xdcore_class;
		XdLineClassPart xdline_class;
		} XdLineClassRec;

extern XdLineClassRec xdLineClassRec;

/*****************************************************
 * Line data structures
 *****************************************************/

typedef struct {
	Position xf,yf;   /* posizione del secondo punto della linea */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	} XdLinePart;

typedef struct _XdLineRec {
		XdCorePart xdcore;
		XdLinePart xdline;
		} XdLineRec;

#endif /* XdLineP_h */
