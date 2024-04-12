/*
   modulo istrnoar.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)istrnoar.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			File istrnoar.c 		                                       *
*          							                                       *
* istrnoar()						                                       *
*          							                                       *
*********************************************************************/

#include <osf1.h>
#include "chascii.inc"

extern char linea_cor[];

/*********************************************************************
*          							                                       *
*			Procedura istrnoar			                                 *
*                                                                    *
* La procedura effettua l'analisi sintattica delle istruzione del    *
* linguaggio POL che non prevedono la presenza di nessun argomento.  *
* La sinatssi generica di una istruzione di questo risulta essere    *
* la seguente :                                                      *
*                                                                    *
* < Parola chiave >                                                  *
*                                                                    *
*  Esempi:                                                           *
*                                                                    *
*  - NOP                                                             *
*  - SETA                                                            *
*  - CLRA                                                            *
*          							                                       *
*********************************************************************/

istrnoar()

{

int M,flgerr;

M = 0;

/* Ciclo di posizionamento al termine della parola chiave */

while ( (linea_cor[M]!=BLANK) && (linea_cor[M]!=0x00) ) {

	M++;

}

if ( linea_cor[M] != 0x00 ) {

	flgerr = 0;

	while(linea_cor[M]!=0x00) {

		if ( !(linea_cor[M]==BLANK || linea_cor[M]==TAB) ) {

			if ( flgerr == 0 ) {

				flgerr = 1;
				stampa_err(77,0,"0");

			}
		}
		M++;
	}

}

return;

}




