/*
   modulo sbianca.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)sbianca.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "defpath.inc"

#include "chascii.inc"


/*********************************************************************
*								                                             *
*			Procedura sbianca      			                              *
* La procedura serve per sbiancare il vettore passato ed inserisce   *
* alla fine dello stesso (la dimensione la indica termine) il fine   *
* stringa ( codice 0x00 ).                                           *
*								                                             *
*********************************************************************/

sbianca(vettore,termine)

char vettore[];
short termine;

{

short i;

/* Assegno a <termine> elementi di vettore il carattere BLANK */

for(i=0;i<termine;i++)
	vettore[i]=BLANK;

/* Inserisco il terminatore di stringa */

vettore[i]=0x00;

}

