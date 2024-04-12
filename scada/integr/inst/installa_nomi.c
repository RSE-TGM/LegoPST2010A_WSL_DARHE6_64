/*
   modulo installa_nomi.c
   tipo 
   release 1.4
   data 5/14/96
   reserved @(#)installa_nomi.c	1.4
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
#include <editnomi.h>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione NOMI [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_nomi()
{
return(scrivi_header(path_output,"editNomi",editnomi,NUM_CAMPI_EDITNOMI));
}

int installa_nomi(
        char *Sigla, // Sigla sigla del punto sullo SCADA
        char *Tipo, // Tipo del Punto
        int PointDB, // Indice del punto
        char ExtDB // Estensione del Punto
        )
{
RECORD record;
char riga[50];


// inizializza il record
if(init_record(&record,editnomi,NUM_CAMPI_EDITNOMI)!=1)
	errore("init_record");

// inserisce la sigla del punto sullo SCADA
if(ins_campo_char("Sigla",Sigla,&record)!=1)
	errore("Sigla");

// inserisce il Tipo del Punto
if(ins_campo_char("Tipo",Tipo,&record)!=1)
	errore("Tipo");

// inserisce Indice del punto
if(ins_campo_int("PointDB",PointDB,&record)!=1)
        errore("PointDB");

// inserisce Indice del punto
if(ins_campo_int("ExtDB",ExtDB,&record)!=1)
        errore("ExtDB");

// scrittura del record
if(scrivi_record(path_output,"editNomi",&record)!=1)
        errore("scrivi_record");

return(1);
}
