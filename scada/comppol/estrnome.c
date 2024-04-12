/*
   modulo estrnome.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)estrnome.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*   -> ESTRNOME.C
 *          Routine utilizzata per estrarre il nome di una variabile
 *          note che siano :
 *                .lunghezza massima ammessa per il nome
 *                .numero di terminatori su cui fare il confronto
 *                .indirizzo del vettore contenente tali terminatori
 */

#include <osf1.h>
#include <ctype.h>

#include "chascii.inc"

estrnome(buffin,nomevar,lungvar,vet_term,num_term,flag)
char *buffin;    // puntatore al buffer da cui estrarre il nome della 
					  // variabile (il puntatore deve puntare al primo
					  // carattere da considerarsi come appartenente alla
					  // variabile.
char *nomevar;	  // puntatore al buffer in cui verr… inserito il nome della
					  // variabile estratta
short lungvar;	  // lunghezza massima ammissibile per la variabile.
char *vet_term;  // vettore contenente i terminatori 
short num_term;  // numero dei terminatori
short flag;      /* flag = 0 estrazione senza controllo singolo carattere */
                 /* flag = 1 estrazione con controllo singolo carattere   */
{
register short i,j;
char *pbuffin=buffin;
i=0;
while(i<=lungvar)			// esamina fino ad un carattere in pi— della lunghezza
								// massima ammessa per verificare se c'Š il terminatore
	{
	for(j=0;j<num_term;j++)	  // confronta il carattere con tutti i terminatori
		{
		if(*pbuffin==vet_term[j])
			{
			nomevar[i]=0;              // termina la stringa 
			return((i==0)?	(1):(0));		// ritorna 1 se non ha trovato il nome
												//         0 se tutto O.K.
			}
		}
	if ( flag ) {

	/* Controllo carattere alfanumerico */

	if( ( !isalnum((int)(*pbuffin)) ) && ( *pbuffin!=UNDSCORE ) && ( *pbuffin!='#')
			&& (*pbuffin!='-'))

		return(1);  // errore carattere non alfanumerico

	}
	nomevar[i++]=*pbuffin++;	  // copia il carattere in nome var
	}
return(1);   // errore: manca il terminatore
}
