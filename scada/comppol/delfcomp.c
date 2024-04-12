/*
   modulo delfcomp.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)delfcomp.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <string.h>
#include <stdio.h>

delfcomp(ctfile)

int ctfile;  /* contatore numero file da temporanei creati */

{

int i;
char nome[10];

/***********************************************************/
/* NB Tutti i file da cancellare devono essere chiusi      */
/***********************************************************/

/* Cancello i file temporanei 0.tmp 1.tmp ... (ctfile-1).tmp */

for (i=0; i<ctfile; i++) {

sprintf(nome,"%d",i);

strcat(nome,".TMP");

unlink(nome);

}

}

