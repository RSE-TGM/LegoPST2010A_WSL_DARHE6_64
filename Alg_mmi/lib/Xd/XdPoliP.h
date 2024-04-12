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
   modulo XdPoliP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdPoliP.h	5.1
*/
/* XdPoliP.h
 *         oggetto base per draw
 */
#ifndef XdPoliP_h
#define XdPoliP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdPoli.h>
/******************************************************
 * Poli Class Structure
 ******************************************************/

typedef struct  {
		int dummy;
		} XdPoliClassPart;

typedef struct _XdPoliClassRec {
		DragetClassPart xdcore_class;
		XdPoliClassPart xdpoli_class;
		} XdPoliClassRec;

extern XdPoliClassRec xdPoliClassRec;

/*****************************************************
 * Poli data structures
 *****************************************************/

typedef struct {
	XPoint *points;   /* punti costituenti il poligono */
	int npoints;      /* numero di punti */
	Position xf,yf;   /* posizione del secondo punto della polilinea */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	} XdPoliPart;

typedef struct _XdPoliRec {
		XdCorePart xdcore;
		XdPoliPart xdpoli;
		} XdPoliRec;

#endif /* XdPoliP_h */
