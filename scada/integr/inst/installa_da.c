/*
   modulo installa_da.c
   tipo 
   release 1.8
   data 6/14/96
   reserved @(#)installa_da.c	1.8
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
#include <editda.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione DA [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_da()
{
return(scrivi_header(path_output,"editda",editda,NUM_CAMPI_EDITDA));
}

int installa_da(
        char *Sigla, // Sigla sigla del punto sullo SCADA
        char *Descrizione, // Descrizione del punto
        char *SiglaSim, // Sigla sigla del punto sul simulatore
	char *Stato0, // descrizione stato 0
	char *Stato1, // descrizione stato 0
	char *TagPP1, // Sigla punto protezione 1
	char *TagPP2, // Sigla punto protezione 2
	char *TInib, // Sigla punto inibizione
        int Contatto,  // 0 normale 1 negato
	int Zonaimpianto,    // Zona di impianto 
        int Trattamento,    // Trattamento Trattamento del punto
        int Severita,    // Severita   livello di severita'
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
extern int indice_fisico_da;
static int prog = 0;

// Aggiorna tabella editnomi.txt
installa_nomi(Sigla,"DA",prog++,g1tipda);

// Aggiunge la gerarchia se non esiste
AddGerarchia(Zonaimpianto,ger0,ger1,ger2,ger3,ger4,ger5);

// inizializza il record
if(init_record(&record,editda,NUM_CAMPI_EDITDA)!=1)
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

// inserisce lo Stato0
if(ins_campo_char("Stato0",Stato0,&record)!=1)
	errore("Stato0");

// inserisce lo Stato1
if(ins_campo_char("Stato1",Stato1,&record)!=1)
	errore("Stato1");

// inserisce TagPP1
if(ins_campo_char("TagPP1",TagPP1,&record)!=1)
	errore("TagPP1");

// inserisce TagPP2
if(ins_campo_char("TagPP2",TagPP2,&record)!=1)
	errore("TagPP2");

// inserisce TInib
if(ins_campo_char("TInib",TInib,&record)!=1)
	errore("TInib");

// inserisce il Contatto 
if(ins_campo_int("Contatto",Contatto,&record)!=1)
        errore("Contatto");

// inserisce la zona di impianto
if(ins_campo_int("Zonaimpianto",Zonaimpianto,&record)!=1)
        errore("Zonaimpianto");

// inserisce il Trattamento
if(ins_campo_int("Trattamento",Trattamento,&record)!=1)
        errore("Trattamento");

// inserisce il Severita'
if(ins_campo_int("Severita",Severita,&record)!=1)
        errore("Severita");

// gestione indice scheda e indice fisico
if(ins_campo_int("IDscheda",indice_fisico_da,&record)!=1)
        errore("IDscheda");
if(ins_campo_int("IDpunto",1,&record)!=1)
        errore("IDpunto");
++indice_fisico_da;


// gerarchie
if(CostruisciGer(riga,ger0,ger1,ger2,ger3,ger4,ger5)==1)
	{
	if(ins_campo_char("Gerarchia",riga,&record)!=1)
		errore("Gerarchia");
	}
else
	errore("CostruisciGer");

// scrittura del record
if(scrivi_record(path_output,"editda",&record)!=1)
        errore("scrivi_record");

return(1);

}
