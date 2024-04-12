/*
   modulo ctreninc.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctreninc.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "osf1.h"
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

/*********************************************************************
*
* Procedura ctreninc
*
*********************************************************************/

ctreninc(strpath)

char strpath[];	/* stringa che contiene il path di ambiente */

{

short ret,indcha;
short lstrpath;
short numcha;
short flgerrsin;
short indcha0;

ret = 0;
indcha = 0;
flgerrsin = 0;

lstrpath = strlen(strpath);

/* la stringa path di ambiente deve avere lunghezza non nulla */

if ( lstrpath == 0 )
	return(1);

/* ricerca nella stringa strpath del carattere BAKSLASH */

while ( (strpath[indcha] != BAKSLASH) && (strpath[indcha] != 0x00) )
	indcha++;

/* la stringa path di ambiente deve contenere il carattere BAKSLASH */

if ( strpath[indcha] == 0x00 ) 
	return(1);

/* indcha puo' assumere solo i valori 0 oppure 2 (es. \dir1 , d:\dir1) */

if ( (indcha != 0) && (indcha != 2) )
	return(1);

if ( indcha == 2 ) {

	/* la stringa path di ambiente specifica anche il drive */

	if ( (strpath[indcha - 1] != DUE_PUNTI) ||
	     (strpath[indcha - 2] < 0x41 ) ||
	     (strpath[indcha - 2] > 0x7a ) ||
	     ( (strpath[indcha - 2] > 0x5a) && (strpath[indcha - 2] < 0x61) ) ) {

		return(1);

	}

}

indcha0 = indcha;

while ( strpath[indcha] != 0x00 ) {

	indcha++;

	numcha = 0;
	
	while ( (strpath[indcha] != 0x00) && (strpath[indcha] != BAKSLASH) ) {

		if ( (strpath[indcha] != BLANK) &&
			  (strpath[indcha] != APICE) &&
			  (strpath[indcha] != VIRGOLETTE) &&
			  (strpath[indcha] != PUNTO) &&
           (strpath[indcha] != DUE_PUNTI) &&
			  (strpath[indcha] != VIRGOLA) &&
			  (strpath[indcha] != CAR_COMM) &&
			  (strpath[indcha] != SLASH) &&
			  (strpath[indcha] != APQUADRA) &&
           (strpath[indcha] != CHQUADRA) &&
			  (strpath[indcha] != PIU)	&&
			  (strpath[indcha] != UGUALE)	&&
			  (strpath[indcha] != ASTERISCO)	&&
			  (strpath[indcha] != PUNTO_INT) ) {

			indcha++;
			numcha++;

		}

		else {

			flgerrsin = 1;
			break;

		}

	} /* fine ciclo interno di scansione */

	if ( ( (numcha == 0) && ((indcha-1) != indcha0) ) || (flgerrsin == 1) ) {

		ret = 1;
		break;

	}

}

return(ret);

}
