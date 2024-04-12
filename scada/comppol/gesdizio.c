/*
   modulo gesdizio.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)gesdizio.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <string.h>
#include <memory.h>

/*

	gesdizio - gestione dizionari di stringhe

	- dizio   : dizionario di stringhe

	- lmaxdiz : numero massimo di stringhe del dizionario

	- lstring : lunghezza di una stringa del dizionario

	- stringa : stringa da inserire nel dizioanrio

	- occupaz : numero di stringhe presenti nel dizionario

	- indstr  : indice della stringa trovata o inserita

*/

gesdizio(dizio,lmaxdiz,lstring,stringa,occupaz,indstr)

char dizio[],stringa[];

int lmaxdiz,lstring;

int *occupaz,*indstr;

{

int ier,i;

int nstrpre,pstrdiz,uguali;

	nstrpre = (*occupaz);

	/* Ricerca della stringa nel dizionario */

	for ( i = 0; i < nstrpre; i++ ) {

	pstrdiz = ( i * lstring );

	/* Comparazione delle due stringhe */

	uguali = strncmp(&stringa[0],&dizio[pstrdiz],lstring);

	if ( uguali == 0 ) {

	  /* Stringa presente nel dizionario */

	  (*indstr) = i;

	  ier = 0;

	  return (ier);

	  }

	}

	/* Stringa non presente nel dizionario o dizionario vuoto */

	/* Verifica spazio esistente nel dizionario */

	if ( ( nstrpre + 1 ) > lmaxdiz ) {

	  /* Dizionario completo */

	  ier = -1;

	  return (ier);

	  }

	/* Spazio nel dizionario OK */

	/* Procedura di inserimento stringa */

	/* Puntatore primo byte stringa nel dizionario */

	pstrdiz = ( nstrpre * lstring );

	memcpy(&dizio[pstrdiz],&stringa[0],lstring);

	(*indstr) = (*occupaz);

	(*occupaz) = ( (*occupaz) + 1 );

	ier = 1;

	return(ier);

}
