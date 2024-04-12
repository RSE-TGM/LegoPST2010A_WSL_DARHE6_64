/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef _XdUndo_h
#define _XdUndo_h

#define NUM_MAX_UNDO 5 

typedef struct _XdListaUndoRec *XdListaUndo;

/*
 Funzioni di uso esterno
*/
XdListaUndo undoCreateLists();
void undoListAdd(XdListaUndo, XdLista);
void undoListDelete(XdListaUndo);

#endif /* _XdUndo_h */
