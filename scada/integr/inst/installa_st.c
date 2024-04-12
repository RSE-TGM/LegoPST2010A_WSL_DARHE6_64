/*
   modulo installa_st.c
   tipo 
   release 1.4
   data 6/14/96
   reserved @(#)installa_st.c	1.4
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
#include <editst.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione ST [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_st()
{
return(scrivi_header(path_output,"editst",editst,NUM_CAMPI_EDITST));
}
