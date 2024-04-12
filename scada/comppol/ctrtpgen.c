/*
   modulo ctrtpgen.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctrtpgen.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			Procedura ctrtpgen			                                 *
* La procedura legge da linea_cor un codice di tipo generico di 2    *
* caratteri a parire dall'indice specificato dal parametro di        *
* passaggio (s), lo ricerca in un vettore di codici ammessi e se     *
* lo trova ritorna un valore numerico associato al codice altrimenti *
* ritorna -1.                                                        *
*          							                                       *
*********************************************************************/

#include "osf1.h"
#include <string.h>

#include "chascii.inc"


extern char linea_cor[];


ctrtpgen (nchload,prov,s,ntipamm,vtipamm)

short nchload;	/* numero di caratteri da caricare da linea_cor */
char prov[];	/* vettore caricato con i caratteri del codice  */
short s;			/* indice in linea_cor di inizio dei caratteri del codice */
short ntipamm;	/* numero dei codici ammissibili */
char *vtipamm[];	/* vettore contenente i codici ammissibili */

{

int j,valret;

for( j=0; j < nchload; j++ ) {

prov[j]=linea_cor[s++];		/* Carico il carattere */

}

prov[nchload]=0x00;			/* termino la stringa prov */

if(!(linea_cor[s]==BLANK || linea_cor[s]==APTONDA))
	prov[1]='\0';

valret = -1;

/* Ciclo di ricerca nel vettore dei codici ammessi */

for ( j=0; j < ntipamm; j++ ) {

	if((strcmp(prov,vtipamm[j]))==0) {

		/* Trovato il codice tra quelli ammessi */

		valret = j;   /* tipo trovato */

		break;

	}

}

return(valret);

}


