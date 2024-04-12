/*
   modulo tstnomva.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)tstnomva.c	1.1
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

#include "tipi.h"


/*********************************************************************
*                                                                    *
*                        Procedura tstnomvar                         *
*                                                                    *
* La procedura verifica che il nome di una variabile non sia uguale  *
* ad una parola chiave definita nel linguaggio POL                   *
* In caso di errore la procedura restituisce il valore -1            *
*                                                                    *
*********************************************************************/

tstnomvar(nomvar)

char nomvar[];

{

/* Indice parola chiave da esaminare */

int iparchi;

/* Cerco nel primo set di parole chiavi */

for ( iparchi=1; iparchi<NUM_ISTR; iparchi++ ) {

	if((strcmp(nomvar,par_chiav[iparchi]))==0) {

		stampa_err(74,1,nomvar);
		return(-1);

	}

}

/* Cerco nel secondo set di parole chiavi */

for ( iparchi=1; iparchi<NU_ISTRS; iparchi++ ) {

	if((strcmp(nomvar,altre_istr[iparchi]))==0) {

		stampa_err(74,1,nomvar);
		return(-1);

	}

}

return(1);

}
