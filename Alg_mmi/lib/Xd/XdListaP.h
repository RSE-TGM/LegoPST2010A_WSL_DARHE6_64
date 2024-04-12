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
   modulo XdListaP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdListaP.h	5.1
*/
/* XdListaP.h
 *         oggetto base per draw
 */
#ifndef XdListaP_h
#define XdListaP_h
#include <Xd/XdP.h>
#include <Xd/XdLista.h>
/******************************************************
 * Lista Class Structure
 ******************************************************/

typedef struct _ListaClassRec {
		int dummy;
		} ListaClassRec, XdListaClassRec;

extern XdListaClassRec xdListaClassRec;
/*****************************************************
 * Lista data structures
 *****************************************************/

typedef struct _XdListaRec {
	Draget *ListaDraget;
	int num_draget;  /* lunghezza della lista (compresi record
                             cancellati eventuali) */
	int ind_draget;  /* indice di scorrimento della lista */
	int start_pos;   /* posizione di partenza nello scorrimento 
			    della lista */
	int stop_pos;    /* posizione di fine scorrimento nella lista */
	Boolean in_use;  /* se True la lista e' stata riavvolta ed e'
				in scorrimento */
	} XdListaRec,ListaRec;

#endif /* XdListaP_h */
