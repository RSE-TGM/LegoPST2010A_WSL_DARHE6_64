/*
   modulo scrvar_c.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)scrvar_c.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "chascii.inc"

#include "tipi.h"

#include "define.inc"

/***********************************************************************
*								                                               *
*			Procedura scrvar_cost			                                *
*								                                               *
* La procedura cerca nell' albero delle variabili quelle che           *
* corrispondono al tipo specificato, e ne scrive i campi significativi *
* sul file di listing.						                                *
*								                                               *
***********************************************************************/

extern int fdlst;
extern int righelst;
extern char *t_var[];

scrvar_cost(albero,ind,s)

struct variabili *albero;
int ind;
int s;

{

static char scritta[81];
static char ausscritta[81];
int j;

if(albero!=NULL)  {

	if(ind==(albero->tipo & 15) &&
	(int)(albero->codicevar) == ( s + 1 ) ) {

		sbianca(scritta,80);
		if(s==0) {
			j=1+1;
			j+=sprintf(&scritta[1+1],"%s",albero->valcost);
			scritta[j]=BLANK;
		}
		if(s==0 || s==1) {
			j=15+1;
			j+=sprintf(&scritta[j],"%s",albero->nome);
			scritta[j]=BLANK;
			j=30+4;
			j+=sprintf(&scritta[j],"%s",t_var[albero->tipo & 15]);
			scritta[j]=BLANK;
			j=47+4;
			j+=sprintf(&scritta[j],"%04d",albero->indirizzo);
		}
		else {
			j=1+1;
			j+=sprintf(&scritta[j],"%s",albero->nome);
			scritta[j]=BLANK;
			j=15+3;
			if(albero->flag==1)
				j+=sprintf(&scritta[j],"%s",t_var[8]);
			else
				j+=sprintf(&scritta[j],"%s",t_var[albero->tipo & 15]);
 			scritta[j]=BLANK;
 			j=33+6;
			j+=sprintf(&scritta[j],"%04d",albero->indirizzo);
			scritta[j]=BLANK;
			j=53+1;
			j+=sprintf(&scritta[j],"%s",albero->valcost);
		}
		scrivisufile(fdlst,scritta,j+1,&righelst);
	}
	scrvar_cost(albero->left,ind,s);
	scrvar_cost(albero->right,ind,s);
}
}


