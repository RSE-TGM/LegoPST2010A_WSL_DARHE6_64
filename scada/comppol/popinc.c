/*
   modulo popinc.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)popinc.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
extern int nrigaco;  /* numero relativo di riga nel modulo corrente */
extern int numriga;  /* numero riga corrente file di input */

extern int stkinc[]; /* Pseudo stack di gestione annidamento INCLUDE */

extern int *stk;     /* Puntatore allo pseudo stack */

#include "all_1.h"
extern struct TBIND {

	int ptdzmod;  /* indice relativo al primo byte del nome modulo */
	int indass;   /* indice assoluto di riga nel file sorgente */
	int indrel;   /* indice relativo di riga nel file corrente */
	};
#include "all_16.h"

extern struct TBIND tabind[];  /* Tabella indici assoluti e relativi */

extern int itabind;  /* indice progressivo Tabella indici */


#include <osf1.h>

popinc()

{

/* Decremento di un livello il puntatore allo stack */

stk-=3;

if ( stk > stkinc ) {

/* Esiste un livello inferiore nello stack */

/* Aggiornamento indice relativo di riga livello inferiore stack */

nrigaco = ( *(stk-1) ) - 1;

/* Aggiornamento indice assoluto di riga livello inferiore stack */

*(stk-2) = numriga+1;

/* Inserisco la riga corrente nella tabella indici */

tabind[itabind].ptdzmod = *(stk-3);
tabind[itabind].indass = *(stk-2);
tabind[itabind].indrel = *(stk-1);

/* Aggiorno l'indice corrente della tabella indici */

itabind++;

}

else {

/* Pop con un solo livello contenuto nello stack */

/* Inserisco l'ultima riga nella tabella indici */

tabind[itabind].ptdzmod = *(stk);
tabind[itabind].indass = numriga+1;
tabind[itabind].indrel = 0;

/* Aggiorno l'indice corrente della tabella indici */

itabind++;

}

/* Ripulisco l'area di stack liberata dalla istruzione POP */

*(stk) = -1;
*(stk+1) = -1;
*(stk+2) = -1;

}
