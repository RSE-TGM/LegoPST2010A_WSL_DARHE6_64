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
   modulo XdCircleP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdCircleP.h	5.1
*/
/* XdCircleP.h
 *         oggetto base per draw
 */
#ifndef XdCircleP_h
#define XdCircleP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdCircle.h>
/******************************************************
 * Circle Class Structure
 ******************************************************/

typedef struct  {
		int dummy;
		} XdCircleClassPart;

typedef struct _XdCircleClassRec {
		DragetClassPart xdcore_class;
		XdCircleClassPart xdcircle_class;
		} XdCircleClassRec;

extern XdCircleClassRec xdCircleClassRec;

/*****************************************************
 * Circle data structures
 *****************************************************/

typedef struct {
	Position xf,yf;   /* posizione del secondo punto della linea */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	int type;  /* utilizzato per specificare se circonferenza
		      o arco (XD_TY_CIRCLE o XD_TY_ARC) */
	int a1;  /* angolo di partenza */
	int a2;  /* angolo finale      */
	} XdCirclePart;

typedef struct _XdCircleRec {
		XdCorePart xdcore;
		XdCirclePart xdcircle;
		} XdCircleRec;

#endif /* XdCircleP_h */
