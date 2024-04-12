/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)utlistascroll.c	5.1\t11/10/95";
/*
   modulo utlistascroll.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)utlistascroll.c	5.1
*/
/*   Seleziona un elemento all'interno di una lista effettuando
     uno scroll che porta l'elemento selezionato in prima posizione
     tra gli elementi visualizzati 

     w          widget lista
     dim_lista  dimensione in elementi della lista 
     num_vis    numero di elementi visualizzati nella lista
     pos        posizione dell'elemento da evidenziare (primo
                elemento --> posizione 0 .
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <Xm/MessageB.h>
# include <Xm/List.h>

#include "libutilx.h"

void UtListaScroll(w,dim_lista,num_vis,pos)
Widget w;
int dim_lista;
int num_vis;
int pos;
{
XmListSelectPos(w,pos+1,True);
if(dim_lista>num_vis)
if(pos<=dim_lista-num_vis)
     XmListSetPos(w,pos+1);
else
     XmListSetPos(w,dim_lista-num_vis+1);
}
