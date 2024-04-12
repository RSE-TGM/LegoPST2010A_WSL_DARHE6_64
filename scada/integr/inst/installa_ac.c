/*
   modulo installa_ac.c
   tipo 
   release 1.5
   data 6/14/96
   reserved @(#)installa_ac.c	1.5
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
#include <editac.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione AC [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_ac()
{
return(scrivi_header(path_output,"editac",editac,NUM_CAMPI_EDITAC));
}
