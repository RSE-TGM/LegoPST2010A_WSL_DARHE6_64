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
   modulo XdConnP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdConnP.h	5.1
*/
/* XdConnP.h
 *         oggetto connessione per draw
 */
#ifndef XdConnP_h
#define XdConnP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdConn.h>
/******************************************************
 * Conn Class Structure
 ******************************************************/
typedef void (*XdDeleteConnProc) (
#if NeedFunctionPrototypes
		Widget, /* Widget drawing area contenente il Draget */
		int,    /* Coordinate primo estremo connessione */
		int,
		int,    /* Coordinate secondo estremo connessione */
		int
#endif
);

typedef struct  {
		XdDeleteConnProc deleteConn;
		int dummy;
		} XdConnClassPart;

typedef struct _XdConnClassRec {
		DragetClassPart xdcore_class;
		XdConnClassPart xdconn_class;
		} XdConnClassRec;

extern XdConnClassRec xdConnClassRec;

/*****************************************************
 * Conn data structures
 *****************************************************/

typedef struct {
	XPoint *points;   /* punti costituenti il connessione */
	int npoints;      /* numero di punti */
	Position xf,yf;   /* posizione del secondo punto della connessione */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	} XdConnPart;

typedef struct _XdConnRec {
		XdCorePart xdcore;
		XdConnPart xdconn;
		} XdConnRec;

#endif /* XdConnP_h */
