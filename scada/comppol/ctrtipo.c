/*
   modulo ctrtipo.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctrtipo.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* -> CTRTIPO.C 
 *       Controlla che il tipo della variabile sia compatibile 
 *       com i tipi ammessi per l'istruzione.
 *       Riceve in input il tipo della variabile in esame e l'indirizzo
 *       di un vettore di short contenente i tipi ammissibili per
 *       l'istruzione (tale vettore deve contenere come tappo il valore -1).
 *       Restituisce 1 se il tipo Š ammissibile 0 se non ammissibile.
 */
#include "osf1.h"

ctrtipo(tipo,tipamm)
short tipo;
short *tipamm;
{
while(*tipamm!=-1)
	if(tipo==*tipamm++) return(1);   // trovato il tipo corrispondente
return(0);
}
