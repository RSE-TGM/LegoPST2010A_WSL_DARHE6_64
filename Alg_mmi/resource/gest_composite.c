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
        Inizio sezione per SCCS
*/
/*
   modulo gest_composite.c
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)gest_composite.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)gest_composite.c	5.2\t2/13/96";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Rt/RtMemory.h>

/*
 Ridimensione x e width di tutti i figli di un composite
 a seguito del ridimensionamento del composite stesso.
 La routine agisce sulle risorse dei figli in modo
 che la modifica delle dimensioni dia correttamente 
 riportata nel database delle risorse della pagina.
 Infatti una modifica di width e height di un composite effettuata 
 con le SetValues modifica anche le dimensioni dei figli 
 (gestione interna all'oggetto Composite) ma non viene
 riportata la modifica a livello di risorse.
*/
XlSetResCompositeWidth(wid,new_width,Pdb)
Widget wid;
Dimension new_width;
XrmDatabase Pdb;
{
int num_children,i;
float nx,nwidth;
char str[5];
Dimension child_width,new_child_width;
Position child_x,new_child_x;
Dimension old_width;
Widget *children;

get_something(wid,XmNwidth,&old_width);
if (old_width != new_width)
{
	/*
	 Ricava numero e indici di widget dei figli
	*/
	get_something(wid,XmNnumChildren,&num_children);
	get_something(wid,XmNchildren,&children);
	for(i=0;i<num_children;i++)
	{
	/*
	 Ricava x e width del figlio
	*/
		get_something(children[i],XmNx,&child_x);
		get_something(children[i],XmNwidth,&child_width);
	
	/*
	 Normalizza rispetto alle dimensione di composite le dimensioni
	 dei figli e le loro coordinate
	*/
		nx= (float) child_x / (float) old_width;
       		nwidth= (float) child_width / (float) old_width;
	/*
 	Calcola la nuova posizione e dimensione dei figli utilizzando
 	le dimensioni normalizzate
	*/
       		new_child_x=(float)(nx * (float) new_width);
        	new_child_width=(float)(nwidth * (float) new_width);
	/*
	 Setta le risorse corrispondenti
	*/
		sprintf(str,"%d",new_child_x);
		XlSetResourceByName(&Pdb,XtName(children[i]),XmNx,str);
		sprintf(str,"%d",new_child_width);
		XlSetResourceByName(&Pdb,XtName(children[i]),XmNwidth,str);
        	}
	}
}

/*
 Ridimensiona y e height di tutti i figli di un composite
 a seguito del ridimensionamento del composite stesso
*/

XlSetResCompositeHeight(wid,new_height,Pdb)
Widget wid;
Dimension new_height;
XrmDatabase Pdb;
{
int num_children,i;
float ny,nheight;
char str[5];
Dimension child_height,new_child_height;
Position child_y,new_child_y;
Dimension old_height;
Widget *children;

get_something(wid,XmNheight,&old_height);
if (old_height != new_height)
{
/*
 Ricava numero e indici di widget dei figli
*/
get_something(wid,XmNnumChildren,&num_children);
get_something(wid,XmNchildren,&children);
for(i=0;i<num_children;i++)
	{
/*
 Ricava y e height del figlio
*/
	get_something(children[i],XmNy,&child_y);
	get_something(children[i],XmNheight,&child_height);
	
/*
 Normalizza rispetto alle dimensione di composite le dimensioni
 dei figli e le loro coordinate
*/
	ny= (float) child_y / (float) old_height;
        nheight= (float) child_height / (float) old_height;
/*
 Calcola la nuova posizione e dimensione dei figli utilizzando
 le dimensioni normalizzate
*/
        new_child_y=(float)(ny * (float) new_height);
        new_child_height=(float)(nheight * (float) new_height);
/*
 Setta le risorse corrispondenti
*/
	sprintf(str,"%d",new_child_y);
	XlSetResourceByName(&Pdb,XtName(children[i]),XmNy,str);
	sprintf(str,"%d",new_child_height);
	XlSetResourceByName(&Pdb,XtName(children[i]),XmNheight,str);
        }
}
}
