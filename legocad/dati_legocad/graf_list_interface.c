/**********************************************************************
*
*       C Source:               graf_list_interface.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:47:34 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: graf_list_interface.c,2 %  (%full_filespec: 1,csrc,graf_list_interface.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)graf_list_interface.c	2.15\t4/26/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Xm.h>
#include <Xm/List.h>


#include "libutilx.h"
#include "macro.h"
#include "utile.h"
#include "files.h"

extern MacroBlockType *macroblocks;  /* vettore puntatore a descrittori macroblo
cchi */
extern int num_macro,macro_allocate; /* num macro istanziate, num macro allocate
 */

/*
 deselez_all_graf()
  deseleziona tutti i blocchi presenti nelle pagina 
 grafiche
*/
deselez_all_graf()
{
int i,j;
MacroBlockType *ind;
char modname[20],blname[20];

for(i=0 ;i<num_macro; i++)
   {
   ind = &macroblocks[i];
      if(!ind->cancellato)
         for(j=0;j< ind->num_blocchi;j++)
            if(!ind->blocks[j].cancellato)
            {
	    if(ind->blocks[j].selezionato)
		seleziona_blocco(ind,&ind->blocks[j],False);
	    }
   }
}

/*
 desel_all_page_lista
  deseleziona dalla lista tutti i blocchi presenti su di una pagina
*/
void desel_all_page_lista(w, ev, params, num_params)
Widget w;
XEvent *ev;
String *params;
Cardinal *num_params;
{
int pagina;
int j;
MacroBlockType *ind;
sscanf(params[0],"%d",&pagina);
ind = &macroblocks[pagina];
if(!ind->cancellato)
    for(j=0;j< ind->num_blocchi;j++)
        if(!ind->blocks[j].cancellato)
            {
	    if(ind->blocks[j].selezionato && ind->blocks[j].tipo==TP_BLOCK)
		seleziona_blocco_lista(ind,&ind->blocks[j],False);
	    }
}

/*
 seleziona_blocco_lista
  in base alla selezione effettuata sullo schema grafico aggiorna la
  selezione in lista
*/
void seleziona_blocco_lista(macro,blocco,flag)
MacroBlockType *macro;
BlockType *blocco;
Boolean flag;
{
int pos;
extern Widget widget_list_blocchi;
int nblocchi,narg; /* numero blocchi da selezionare */
if(blocco->tipo!=TP_BLOCK) return;
if(!flag) /* deselezione */
	{
	pos=posiz_in_lista_blocchi(blocco->nome_blocco);  
	if(pos==-1)
		{
		printf("\n DISALLINEAMENTO tra grafica e lista");
		exit(1);
		}
	else 
		pos++; /* le liste sono indicizzate a partire da 1 */
	XmListDeselectPos(widget_list_blocchi,pos);
	}
else   /* aggiunta alla lista del blocco selezionato */
	{
        pos=posiz_in_lista_blocchi(blocco->nome_blocco);
        if(pos==-1)
                {
                printf("\n DISALLINEAMENTO tra grafica e lista");
                exit(1);
                }
/*
 viene effettuata una selezione in lista che si aggiunge alle altre
*/
printf("\n aggiunta selez");
        aggiungi_sel_lista(widget_list_blocchi,pos);
	}
}

aggiungi_sel_lista(wlista,pos)
Widget wlista;
int pos;
{
Arg arg[2];
int narg;
int i;
extern char **nom_bloc;
XmStringTable blocchi_selez;
XmString *lista;  /* lista che conterra' selezionati
                     compreso quello da aggiungere */
char nome_blocco[81];  /* contiene la riga di lista che specifica
                         nome del blocco piu' descrizione: viene ottenuto
                         dall'elemento del vettore nom_bloc inserendo 
                         il terminatore di fine stringa */
int num_selez;
int *item_positions;
Boolean retval;
/***********************
get_something(wlista, XmNselectedItemCount, (void*) &num_selez);
get_something(wlista, XmNselectedItems, (void*) &blocchi_selez);

lista = ( XmString *) malloc( (num_selez+1) * sizeof(XmString) );
for(i=0;i<num_selez;i++)
	lista[i]=XmStringCopy(blocchi_selez[i]);
lista[num_selez]=XmStringCreateSimple(nom_bloc[pos]);
num_selez++;
*************************/

   retval=XmListGetSelectedPos(wlista,&item_positions,&num_selez);

   if(retval==False)
       num_selez=0;
  

lista = ( XmString *) malloc( (num_selez+1) * sizeof(XmString) );

for(i=0;i<num_selez;i++)
   {
   memcpy(nome_blocco,nom_bloc[item_positions[i]-1],80);
   nome_blocco[80]='\0';
   lista[i]=XmStringCreateSimple(nome_blocco);
   }

memcpy(nome_blocco,nom_bloc[pos],80);
nome_blocco[80]='\0';
lista[num_selez]=XmStringCreateSimple(nome_blocco);
num_selez++;

/*
 setta nella lista le selezioni attuali
*/
narg = 0;
XtSetArg(arg[narg], XmNselectedItems, lista );narg++;
XtSetArg(arg[narg], XmNselectedItemCount, num_selez);narg++;
XtSetValues(wlista, arg, narg);
for(i=0;i<num_selez;i++)
	XmStringFree(lista[i]);
free(lista);

retval=XmListGetSelectedPos(wlista,&item_positions,&num_selez);

}




posiz_in_lista_blocchi(nome)
char *nome;
{
extern char **nom_bloc;
extern int nbl;
int i;
for(i=0;i<nbl;i++)
	{
	if(strncmp(nome,nom_bloc[i],8)==0)
		return(i);
	}
return(-1);
}

/* 21-4-95 (Micheletti) */
int macro_is_open()
{
Boolean aperta=False;
int i,j;
MacroBlockType *ind;

for(i=0 ;i<num_macro; i++)
   {
   ind = &macroblocks[i];
      if(ind->wwinblock != NULL)
         aperta=True;
      else
         aperta=False;
   }

return(aperta);
}

