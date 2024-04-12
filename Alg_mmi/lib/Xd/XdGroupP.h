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
   modulo XdGroupP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdGroupP.h	5.1
*/
/* XdGroupP.h
 *         oggetto raggruppamento di draget
 */
#ifndef XdGroupP_h
#define XdGroupP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
#include <Xd/XdGroup.h>
#include <Xd/XdLista.h>
/******************************************************
 * Group Class Structure
 ******************************************************/

typedef struct  {
		int dummy;
		} XdGroupClassPart;

typedef struct _XdGroupClassRec {
		DragetClassPart xdcore_class;
		XdGroupClassPart xdgroup_class;
		} XdGroupClassRec;

extern XdGroupClassRec xdGroupClassRec;

/*****************************************************
 * Rect data structures
 *****************************************************/

typedef struct {
	Position xf,yf;   /* posizione del secondo punto della linea */
	Boolean is_first; /* indica il primo disegno */
	Position xprev,yprev; /* posizione precedente (per gestione
				disegno con il mouse) */
	int num_draget; /* numero dei draget componenti il gruppo */
	XdLista dr_list; /* Lista dei draget componenti */
	} XdGroupPart;

typedef struct _XdGroupRec {
		XdCorePart xdcore;
		XdGroupPart xdgroup;
		} XdGroupRec;

#endif /* XdGroupP_h */
