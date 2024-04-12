/*
   modulo installa_or.c
   tipo 
   release 1.4
   data 6/14/96
   reserved @(#)installa_or.c	1.4
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
#include <editor.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione OR [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_or()
{
return(scrivi_header(path_output,"editor",editor,NUM_CAMPI_EDITOR));
}
