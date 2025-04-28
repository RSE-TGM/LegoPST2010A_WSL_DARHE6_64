/**********************************************************************
*
*       C Source:               XdLista.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu May  7 09:47:04 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdLista.c-2 %  (%full_filespec: XdLista.c-2:csrc:1 %)";
#endif
/*
   modulo XdLista.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdLista.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdLista.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 listdraget.c
    contiene le routine per la manipolazione della lista dei draget
*/
#include <stdio.h>
#include <X11/Intrinsic.h>
#include <Xd/Xd.h>
#include <Xd/XdCore.h>
#include <Xd/XdListaP.h>

/*
 Dichiarazione dei metodi
*/
void XdDestroyDraget(Draget);
static int inc_ind(XdLista);


XdListaClassRec xdListaClassRec = {
	0
	};

ListaClass xdListaClass = (ListaClass) &xdListaClassRec;
/*
	static Draget *ListaDraget=NULL;
	static int num_draget=0;
	static int ind_draget=0;
*/
XdLista XdCreateLista()
{
XdLista l;
l=(XdLista)XtCalloc(1, sizeof(XdListaRec));
l->ListaDraget=NULL;
l->num_draget=0;
l->ind_draget=0;
l->start_pos=0;
l->stop_pos=0;
l->in_use=False;  /* indica se la lista e' in scorrimento */
if(l== NULL)
	printf("\n impossibile creare Lista Draget");
return(l);
}

/*
 Distruzione oggetto lista undo
*/
Boolean XdDestroyListaUndo(l)
XdLista l;
{
int i;

printf("XdDestroyListaUndo: ENTRATO\n");
   if(l->ListaDraget) {
      if(l->num_draget>0) {
         for(i=0;i<l->num_draget;i++)
            XdDestroyDraget(l->ListaDraget[i]);
      }
      XtFree((char*)l->ListaDraget);
   }
   XtFree((char*)l);
printf("XdDestroyListaUndo: USCITO\n");
return(True);
}


/*
 Distruzione oggetto lista undo ultimo elemento
*/
Boolean XdDestroyListaUndoLast(l)
XdLista l;
{
int i;

printf("XdDestroyListaUndoLast: ENTRATO\n");
   if(l->ListaDraget) {
      if(l->num_draget>0) {
         for(i=0;i<l->num_draget;i++)
            XdDestroyDraget(l->ListaDraget[i]);
      }
      XtFree((char*)l->ListaDraget);
   }
printf("XdDestroyListaUndoLast: USCITO\n");
return(True);
}


/*
 Distruzione oggetto lista 
*/
Boolean XdDestroyLista(l)
XdLista l;
{

printf("XdDestroyLista: ENTRATO\n");
   if(l->ListaDraget) {
      XtFree((char*)l->ListaDraget);
   }
   XtFree((char*)l);
printf("XdDestroyLista: USCITO\n");

return(True);
}

void ListDragetAdd(l,dr)
XdLista l;
Draget dr;
{
/*
 la lista viene ingrandita di un
 elemento ed il draget viene inserito in coda
*/
ListDragetAddTop(l,dr);
}

void ListDragetAddTop(l,dr)
XdLista l;
Draget dr;
{
l->num_draget++;
if(l->ListaDraget==NULL)
        l->ListaDraget=(Draget *)XtMalloc(sizeof(Draget));
else
        l->ListaDraget=(Draget *)XtRealloc((char*)l->ListaDraget,sizeof(Draget)*l->num_draget);
l->ListaDraget[l->num_draget-1]=dr;
}

/*
 Si posiziona all'inizio della lista
*/
void ListDragetRew(l)
XdLista l;
{
l->ind_draget=0;
l->start_pos=0;
l->stop_pos=l->num_draget-1;
l->in_use=True;
}

void ListSetPosByDraget(l,dr)
XdLista l;
Draget dr;
{
int i;
ListDragetRew(l);
/*
 Ricerca nella lista la posizione del draget
 richiesto
*/
if(dr!= NULL)
	{
	for(i=0;i<l->num_draget; i++)
		{
		if(l->ListaDraget[i] == dr)
			{
			l->ind_draget= i;
			inc_ind(l);
			l->start_pos=l->ind_draget;
			l->stop_pos= 
				(l->start_pos+l->num_draget-1)%l->num_draget;
/*
printf("\n----------\n parte posiz = %d\n",l->start_pos);
printf(" stop posiz = %d\n",l->stop_pos);
printf(" numero draget = %d\n",l->num_draget);
*/
			break;
			}
		}
	}
l->in_use=True;
l->ind_draget=l->start_pos;
}

Draget ListDragetNext(l)
XdLista l;
{
Draget retDraget;
/*
 skip di eventuali locazioni libere in lista
*/
if(l->ListaDraget==NULL) return(NULL);
while (l->ListaDraget[l->ind_draget] == NULL &&
		 (l->ind_draget != l->stop_pos))
	inc_ind(l);
/*
 Se non si e' scorsa tutta la lista restituisce il draget
 e incrementa l'indice di scorrimento
*/
if(l->ind_draget != l->stop_pos)
	{
	retDraget=l->ListaDraget[l->ind_draget];
	inc_ind(l);
	}
/*
 Si e' arrivati a fondo lista; restituisce l'ultimo draget
 e segnala che si e' concluso lo scorrimento della lista
*/
else if (l->ind_draget == l->stop_pos && l->in_use == True)
	{
	retDraget=l->ListaDraget[l->ind_draget];
	l->in_use=False;
	}
/*
 Segnala la fine della lista (anche l'ultimo draget e' stato
 restituito
*/
else
	{
	retDraget=NULL;
	}

return(retDraget);
}

int inc_ind(l)
XdLista l;
{
if(l->ind_draget < (l->num_draget-1))
	l->ind_draget ++;
else
	l->ind_draget=0;
}
/*
 ListDeleteDraget
	cancella un draget dalla lista
*/
void ListDeleteDraget(l,dr)
XdLista l;
Draget dr;
{
int i;
if(l->ListaDraget==NULL) return;
/*
 ricerca il draget nella lista
*/
for(i=0; i< l->num_draget; i++)
	if(l->ListaDraget[i] == dr)
		{
		l->ListaDraget[i] = NULL;
		break;
		}
}
/*
 ListGetNumDraget
 	restituisce il numero di draget effettivamente presenti in lista
*/
int ListGetNumDraget(l)
XdLista l;
{
int num_draget;
Draget dr;
if(l->ListaDraget==NULL) return(0);
ListDragetRew(l);
num_draget=0;
while (dr=ListDragetNext(l))
	{
	if(dr) num_draget++;
	}
return(num_draget);
}

/*
 ListGetNumAllDraget
	restituisce il numero di oggetti totale compresi
	gli oggetti che compongono eventuali gruppi.
	I gruppi medesimi non vengono conteggiati.
*/
int ListGetNumAllDraget(l)
XdLista l;
{
extern XdLista XdGroupGetList();
extern Boolean XdIsGroup();
int num_draget;
Draget dr;
if(l->ListaDraget==NULL) return(0);
ListDragetRew(l);
num_draget=0;
while (dr=ListDragetNext(l))
        {
        if(XdIsGroup(dr)) 
		num_draget+= ListGetNumAllDraget(XdGroupGetList(dr));
	else
		num_draget++;
        }
return(num_draget);
}
/*
 ListGetAll
	restituisce come parametro una lista contenente gli oggetti selezionati
	- la lista viene allocata internamente alla funzione
	- il chiamante deve eseguire la XtFree della lista dopo
	  l'uso.
	- Il valore di ritorno e' il numero di draget 
*/
int ListGetAll(l,drlist)
XdLista l;
Draget **drlist;  /* lista per contenere i draget */
{
int num_selected;
Draget dr;
*drlist=NULL;
if(l->ListaDraget==NULL) return(0);
/*
 memorizza i draget 
*/
ListDragetRew(l);
num_selected=0;
while (dr=ListDragetNext(l))
	{
	num_selected++;
	*drlist=(Draget *)XtRealloc((char*)*drlist,num_selected*sizeof(Draget));
	(*drlist)[num_selected-1]=dr;
	}
return(num_selected);
}
/*
 ListGetSelected
	restituisce come parametro una lista contenente gli oggetti selezionati
	- la lista viene allocata internamente alla funzione
	- il chiamante deve eseguire la XtFree della lista dopo
	  l'uso.
	- Il valore di ritorno e' il numero di draget selezionati.
*/
int ListGetSelected(l,drlist)
XdLista l;
Draget **drlist;  /* lista per contenere i draget selezionati */
{
int num_selected;
Draget dr;
*drlist=NULL;
if(l->ListaDraget==NULL) return(0);
/*
 memorizza i draget selezionati
*/
ListDragetRew(l);
num_selected=0;
while (dr=ListDragetNext(l))
	{
	if(XdIsSelected(dr))
		{
		num_selected++;
		*drlist=(Draget *)XtRealloc((char*)*drlist,num_selected*sizeof(Draget));
		(*drlist)[num_selected-1]=dr;
		}
	}
return(num_selected);
}

/*
 Rende l'oggetto come visualizzato al di sopra degli altri
 lo pone quindi come ultimo della lista
*/
void ListPutTop(l,dr)
XdLista l;
Draget dr;
{
if(l->ListaDraget==NULL) return;
/*
 aggiunge l'oggetto in fondo alla lista
*/
ListDragetAddTop(l,dr);
/*
 cancella l'oggetto duplicato
*/
ListDeleteDraget(l,dr);
}

void ListPutBottom(l,dr)
XdLista l;
Draget dr;
{
int pos;
int i;
pos= -1;
if(l->ListaDraget==NULL) return;
/*
 individua la posizione in lista del draget da spostare
*/
for(i=0; i< l->num_draget; i++)
	if(l->ListaDraget[i] == dr)
		{
		pos=i;
		break;
		}
if(pos==-1) return;   /* oggetto non trovato */
/*
 shifta tutta la lista di una posizione a partire dalla
 posizione occupata dal draget andando all'indietro
*/
pos--;
while(pos >= 0)
	{
	l->ListaDraget[pos+1] = l->ListaDraget[pos];
	pos--;
	}
/*
 inserisce il draget in prima posizione
*/
l->ListaDraget[0]=dr;
}

