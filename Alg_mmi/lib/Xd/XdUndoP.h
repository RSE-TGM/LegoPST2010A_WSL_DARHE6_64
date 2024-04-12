/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef XdUndoP_h
#define XdUndoP_h
#include <Xd/XdLista.h>
#include <Xd/XdUndo.h>

/*****************************************************
 * ListaUndo data structures
 *****************************************************/
typedef struct _XdListaUndoRec {
        XdLista ListeUndo;
        int num_liste;
        } XdListaUndoRec;

#endif /* XdUndoP_h */
