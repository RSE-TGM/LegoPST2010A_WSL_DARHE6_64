/**********************************************************************
*
*       C Source:               XdUndo.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue May 12 11:03:46 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdUndo.c-1.1.1 %  (%full_filespec: XdUndo.c-1.1.1:csrc:1 %)";
#endif

#include <stdio.h>
#include <X11/Intrinsic.h>
#include <Xd/Xd.h>
#include <Xd/XdCore.h>
#include <Xd/XdListaP.h>
#include <Xd/XdUndoP.h>

/*********************************************************************/
/*                                                                   */
/*   Crea la struttura contenente le liste di draget richiamabili    */
/*   dall'operazione di 'undo'.                                     */
/*                                                                   */
/*********************************************************************/
XdListaUndo undoCreateLists()
{
XdListaUndo l_undo;

   l_undo=(XdListaUndo)XtCalloc(1, sizeof(XdListaUndoRec));
   l_undo->ListeUndo = NULL;
   l_undo->num_liste = 0;

return(l_undo);

}

extern Boolean XdDestroyListaUndoLast(XdLista);


/*********************************************************************/
/*                                                                   */
/*   Aggiunge una lista alla struttura contenente le liste di        */
/*   draget richiamabili dall'operazione di 'undo'.                  */
/*                                                                   */
/*********************************************************************/
void undoListAdd(l_undo, lista)
XdListaUndo l_undo;
XdLista lista;
{
int i;

   if(l_undo->num_liste == (NUM_MAX_UNDO + 1)) {
      XdDestroyListaUndoLast(&l_undo->ListeUndo[0]);
      for(i=1; i<(NUM_MAX_UNDO + 1); i++)
          l_undo->ListeUndo[i-1] = l_undo->ListeUndo[i];
   }
   else {
      l_undo->num_liste++;
      if(l_undo->ListeUndo==NULL)
         l_undo->ListeUndo=(XdLista)XtMalloc(sizeof(XdListaRec));
      else
         l_undo->ListeUndo=(XdLista)XtRealloc((char*)l_undo->ListeUndo,sizeof(XdListaRec)*l_undo->num_liste);
   }

/*
l_undo->ListeUndo[l_undo->num_liste-1] = *lista;
*/
(l_undo->ListeUndo[l_undo->num_liste-1]).ListaDraget = lista->ListaDraget;
(l_undo->ListeUndo[l_undo->num_liste-1]).num_draget = lista->num_draget;
(l_undo->ListeUndo[l_undo->num_liste-1]).ind_draget = lista->ind_draget;
(l_undo->ListeUndo[l_undo->num_liste-1]).start_pos = lista->start_pos;
(l_undo->ListeUndo[l_undo->num_liste-1]).stop_pos = lista->stop_pos;
(l_undo->ListeUndo[l_undo->num_liste-1]).in_use = lista->in_use;

}


/*********************************************************************/
/*                                                                   */
/*   Elimina una lista alla struttura contenente le liste di         */
/*   draget richiamabili dall'operazione di 'undo'.                  */
/*                                                                   */
/*********************************************************************/
void undoListDelete(l_undo)
XdListaUndo l_undo;
{

   if(l_undo->num_liste > 1) {
#ifdef MAURIC
      XtFree(l_undo->ListeUndo[l_undo->num_liste -1]);
#endif
      XdDestroyListaUndoLast(&l_undo->ListeUndo[l_undo->num_liste -1]);
/*
      XtFree(l_undo->ListeUndo[l_undo->num_liste -1]);
*/
      l_undo->num_liste--;
   }

}


/*********************************************************************/
/*                                                                   */
/*   Libera la struttura contenente le liste di draget richiamabili  */
/*   dall'operazione di 'undo'.                                      */
/*                                                                   */
/*********************************************************************/
void undoListDeleteAll(l_undo)
XdListaUndo l_undo;
{
int i;

   if(l_undo->num_liste > 0) {
#ifdef MAURIC
        XtFree(l_undo->ListeUndo[l_undo->num_liste -1]);
#endif
      for(i=0; i<l_undo->num_liste; i++)
         XdDestroyListaUndoLast(&l_undo->ListeUndo[(l_undo->num_liste-i-1)]);
/*
         XtFree(l_undo->ListeUndo[(l_undo->num_liste-i-1)]);
*/
   }
   XtFree((char*)l_undo->ListeUndo);
   XtFree((char*)l_undo);

}
