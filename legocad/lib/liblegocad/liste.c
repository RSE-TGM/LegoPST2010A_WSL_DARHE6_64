/**********************************************************************
*
*       C Source:               liste.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 14:10:56 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: liste.c,2 %  (%full_filespec: 1,csrc,liste.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)liste.c	2.3\t7/13/95";
/*
        Fine sezione per SCCS
*/
/*
 Liste.c 
 contiene routines di utilita' per gestione delle liste in uimx
*/
#include <stdio.h>
#include <malloc.h>
#include <Xm/Xm.h>
#include <Xm/List.h>
/*
aggiungi_item_n
aggiunge alla lista un elemento che viene passato come buffer di caratteri
SENZA TERMINATORE. La routine provvede ad aggiungere il terminatore servendosi
di un buffer di appoggio allocato dinamicamente all'interno della routine stessa
*/
aggiungi_item_n(lista,buf,dim)
Widget lista;
char *buf;
int dim;
{
XmString item;
char *str;
/* alloca il buffer di appoggio */
str=malloc(dim+1);
memcpy(str,buf,dim);
str[dim]=0;
/*
 Crea la XmString; la aggiunge alla lista; libera la XmString
*/
/*
item= (XmString)XmStringCreateLtoR (str,XmSTRING_DEFAULT_CHARSET);
*/
item= (XmString)XmStringCreateSimple (str);
XmListAddItem(lista,item,0);
XmStringFree(item);
free(str);
}

update_lista()
{
extern Display *UxDisplay;
XSync(UxDisplay,False);
}

