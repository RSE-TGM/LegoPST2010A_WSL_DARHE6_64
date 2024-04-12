/*
   modulo getnovar.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)getnovar.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"


extern char linea_cor[];
extern int subrcorr;


/*********************************************************************
*								                                             *
*			Procedura getnovar                                          *
*                                                                    *
* Procedura di caricamento da linea_cor in nomevar del nome di una   *
* variabile in una lista di argomenti.                               *
*                                                                    *
*********************************************************************/

getnovar(nomevar,M)

char nomevar[];	  // nome variabile (di ritorno)
int *M;				  // puntatore da cui iniziare a leggere i nomi
						  // (punta all'interno di linea_corr sul primo
						  // carattere appartenente al nome della variabile).

{

int i,temp=0;

for( i=0 ; linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00 &&
           linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=APTONDA &&
((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR)); (*M)++)
		nomevar[i++]=linea_cor[*M];	  // copia il nome in nomevar

nomevar[i]='\0';

	if(linea_cor[*M]==APTONDA)  {
		temp=*M;
}

while(linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=0x00)
	(*M)++;

if(temp!=0)			 // se Š specificato un elemento di variabile
						 // vettoriale (..) esce con M puntato su (
	*M=temp;

if ( i == 0 ) {

	return (-1);

}

return(0);

}
