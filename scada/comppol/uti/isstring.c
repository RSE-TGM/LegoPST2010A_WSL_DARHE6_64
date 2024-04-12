/*
   modulo isstring.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)isstring.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "defpath.inc"

#include "chascii.inc"
#include "define.inc"

/*********************************************************************
*          							                                       *
*			Procedura isstringa                                         *
*          							                                       *
* 	La procedura rende 1 se la stringa passata contiene effetti=      *
*  vamente una stringa con apici sia nel primo che nell' utlimo 	   *
*  carattere.							                                    *
*          							                                       *
*********************************************************************/

isstringa(valore,nomevar,i)

char valore[];
char nomevar[];
short *i;

{

short vir;

if(valore[0]!=VIRGOLETTE) {
	stampa_err(6,1,nomevar); /* mancano le prime virg. */
	return(-1);
}
vir=0;
for(*i=1;*i<DIM_RIGA;(*i)++)
	if(valore[*i]==VIRGOLETTE) {
		vir=1;
		break;
	}
if(vir==0) {
	stampa_err(6,1,nomevar); /* mancano le seconde virgolette */
	return(-1);
}
return(1);
}

