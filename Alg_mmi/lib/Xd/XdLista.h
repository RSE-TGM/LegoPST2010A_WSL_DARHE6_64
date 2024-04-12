/**********************************************************************
*
*       C Header:               XdLista.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Oct 17 10:36:09 1996 %
*
**********************************************************************/
/*
   modulo XdLista.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdLista.h	5.1
*/
/*  XdLista.h
 *       oggetto XdLista - costituisce la superclass comune a tutti gli
 *                        oggetti per il disegno (lista)
 */
#ifndef _XdLista_h
#define _XdLista_h

#include <Xd/XdCore.h>

#define PICK_NORMAL 0
#define PICK_EXTENDED 1

typedef struct _ListaClassRec *ListaClass;
typedef struct _XdListaRec *XdLista;

/*
 Funzioni di uso esterno
*/
XdLista XdCreateLista();
Boolean XdDestroyLista(XdLista);
XdLista XdCreateLista();
void ListDragetAdd(XdLista, Draget);
void ListDragetAddTop(XdLista, Draget);
void ListDragetRew(XdLista);
Draget ListDragetNext(XdLista);
void ListDeleteDraget(XdLista, Draget);
int ListGetSelected(XdLista, Draget **);
void ListPutTop(XdLista, Draget);
void ListPutBottom(XdLista, Draget);

#endif /* _XdLista_h */

