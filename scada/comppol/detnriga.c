/*
   modulo detnriga.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)detnriga.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include "all_1.h"
extern struct TBIND {

	int ptdzmod;  /* indice relativo al primo byte del nome modulo */
	int indass;   /* indice assoluto di riga nel file sorgente */
	int indrel;   /* indice relativo di riga nel file corrente */
	};
#include "all_16.h"

extern struct TBIND tabind[];  /* Tabella indici assoluti e relativi */

extern int itabind;  /* indice progressivo Tabella indici */


detnriga(nrass,nrrel)

int nrass;  /* indice assoluto di riga */
int *nrrel;  /* indice relativo di riga */

{

int i;

i = 0;

while ( tabind[i].indass <= nrass )
i++;

*nrrel = nrass - tabind[i-1].indass + tabind[i-1].indrel;

/* Ritorno il puntatore di stringa nel dizionario nomi moduli */

return( tabind[i-1].ptdzmod );

}

