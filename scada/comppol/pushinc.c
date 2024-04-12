/*
   modulo pushinc.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)pushinc.c	1.1
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


pushinc(istr)

int istr;  /* Indice di stringa inserita nel dizionario dzmod */

{

/* Aggiornamento indice relativo di riga livello inferiore stack */

*(stk-1) = nrigaco+1;

/* Push di un livello nello pseudo stack */

*(stk) = istr;
*(stk+1) = numriga;
*(stk+2) = 1;

/* Aggiorno il puntatore allo stack */

stk+=3;

/* Inserisco la riga corrente nella tabella indici */

tabind[itabind].ptdzmod = istr;
tabind[itabind].indass = numriga;
tabind[itabind].indrel = 1;

/* Aggiorno l'indice corrente della tabella indici */

itabind++;

/* Decremento il contatore assoluto di riga */
/* NB la linea contenente l'istruzione INCLUDE non deve essere contata */
/* nel file sorgente espanso */

numriga--;

}
