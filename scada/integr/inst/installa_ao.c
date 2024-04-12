/*
   modulo installa_ao.c
   tipo 
   release 1.8
   data 6/14/96
   reserved @(#)installa_ao.c	1.8
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
#include <editao.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione AO [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_ao()
{
return(scrivi_header(path_output,"editao",editao,NUM_CAMPI_EDITAO));
}

int installa_ao(
        char *Sigla, // Sigla sigla del punto sullo SCADA
        char *Descrizione, // Descrizione del punto
	char *Unitamisura, // Unita' di misura del punto
        char *SiglaSim, // Sigla sigla del punto sul simulatore
	int Zonaimpianto,    // Zona di impianto 
	int InStampa,    // flag per stampa comando
        int ger0,    // livello di gerarchia 0 non definita = NO_GER
        int ger1,    // livello di gerarchia 1 non definita = NO_GER
        int ger2,    // livello di gerarchia 2 non definita = NO_GER
        int ger3,    // livello di gerarchia 3 non definita = NO_GER
        int ger4,    // livello di gerarchia 4 non definita = NO_GER
        int ger5   // livello di gerarchia 5 non definita = NO_GER
        )
{
RECORD record;
char riga[50];
extern int indice_fisico_ao;
static int prog = 0;

// Aggiorna tabella editnomi.txt
installa_nomi(Sigla,"AO",prog++,g1tipao);

// inizializza il record
if(init_record(&record,editao,NUM_CAMPI_EDITAO)!=1)
	errore("init_record");

// inserisce la sigla del punto sullo SCADA
if(ins_campo_char("Sigla",Sigla,&record)!=1)
	errore("Sigla");

// inserisce la sigla del punto sul simulatore
if(ins_campo_char("SiglaSim",SiglaSim,&record)!=1)
	errore("Sigla");

// inserisce la descrizione del punto sullo SCADA
if(ins_campo_char("Descrizione",Descrizione,&record)!=1)
	errore("Descrizione");

// inserisce l'unita' di misura del punto sullo SCADA
if(ins_campo_char("Unitamisura",Unitamisura,&record)!=1)
	errore("Unitamisura");

// inserisce la zona di impianto
if(ins_campo_int("Zonaimpianto",Zonaimpianto,&record)!=1)
        errore("Zonaimpianto");

// inserisce il flag InStampa
if(ins_campo_int("InStampa",InStampa,&record)!=1)
        errore("InStampa");

// gestione indice scheda e indice fisico
if(ins_campo_int("IDscheda",indice_fisico_ao,&record)!=1)
        errore("IDscheda");
if(ins_campo_int("IDpunto",1,&record)!=1)
        errore("IDpunto");
++indice_fisico_ao;


// gerarchie
if(CostruisciGer(riga,ger0,ger1,ger2,ger3,ger4,ger5)==1)
	{
	if(ins_campo_char("Gerarchia",riga,&record)!=1)
		errore("Gerarchia");
	}
else
	errore("CostruisciGer");

// scrittura del record
if(scrivi_record(path_output,"editao",&record)!=1)
        errore("scrivi_record");

return(1);

}
