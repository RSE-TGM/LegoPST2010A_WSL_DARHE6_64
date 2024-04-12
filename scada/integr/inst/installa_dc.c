/*
   modulo installa_dc.c
   tipo 
   release 1.5
   data 6/14/96
   reserved @(#)installa_dc.c	1.5
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <db.h>
#include <installa.h>
#include <editdc.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione DC [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_dc()
{
return(scrivi_header(path_output,"editdc",editdc,NUM_CAMPI_EDITDC));
}
