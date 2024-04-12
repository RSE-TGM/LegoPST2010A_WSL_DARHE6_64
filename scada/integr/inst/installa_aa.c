/*
   modulo installa_aa.c
   tipo 
   release 1.11
   data 6/14/96
   reserved @(#)installa_aa.c	1.11
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
#include <editaa.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione AA [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_aa()
{
return(scrivi_header(path_output,"editaa",editaa,NUM_CAMPI_EDITAA));
}

int installa_aa(
        char *Sigla, // Sigla sigla del punto sullo SCADA
        char *Descrizione, // Descrizione del punto
	char *Unitamisura, // Unita' di misura del punto
        char *SiglaSim, // SiglaSim del punto nel simulatore
        float LalBS, // LalBS      bassa sicurezza, non definita = NO_SOGLIA
        float LalBC, // LalBC      bassa conduzione, non definita = NO_SOGLIA
        float LalAC, // LalAC      alta conduzione, non definita = NO_SOGLIA
        float LalAS, // LalAS      alta sicurezza, non definita = NO_SOGLIA
	int Zonaimpianto,    // Zona impianto
	int BandaMorta,    // BandaMorta % banda morta
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
extern int indice_fisico_aa;
static int prog = 0;

// Aggiorna tabella editnomi.txt
installa_nomi(Sigla,"AA",prog++,g1tipaa);

// Aggiunge la gerarchia se non esiste
AddGerarchia(Zonaimpianto,ger0,ger1,ger2,ger3,ger4,ger5);

// inizializza il record
if(init_record(&record,editaa,NUM_CAMPI_EDITAA)!=1)
	errore("init_record");

// inserisce la sigla del punto sullo SCADA
if(ins_campo_char("Sigla",Sigla,&record)!=1)
	errore("Sigla");

// inserisce la sigla del punto sullo SCADA
if(ins_campo_char("Descrizione",Descrizione,&record)!=1)
	errore("Descrizione");

// inserisce l'unita' di misura del punto sullo SCADA
if(ins_campo_char("Unitamisura",Unitamisura,&record)!=1)
	errore("Unitamisura");

// inserisce la sigla del punto del simulatore
if(ins_campo_char("SiglaSim",SiglaSim,&record)!=1)
	errore("SiglaSim");

// inserisce la zona di impianto
if(ins_campo_int("Zonaimpianto",Zonaimpianto,&record)!=1)
	errore("Zonaimpianto");

// inserisce il BandaMorta
if(ins_campo_int("BandaMorta",BandaMorta,&record)!=1)
	errore("BandaMorta");

// inserisce il Trattamento
if(ins_campo_int("Trattamento",Trattamento,&record)!=1)
	errore("Trattamento");

// inserisce il Severita'
if(ins_campo_int("Severita",Severita,&record)!=1)
	errore("Severita");

// gestione indice scheda e indice fisico
if(ins_campo_int("IDscheda",indice_fisico_aa,&record)!=1)
	errore("IDscheda");
if(ins_campo_int("IDpunto",1,&record)!=1)
        errore("IDpunto");
++indice_fisico_aa;

// allarme basso sicurezza
if(LalBS != NO_SOGLIA)
	{
	sprintf(riga,"%.2f",LalBS);
	if(ins_campo_char("LalBS",riga,&record)!=1)
		errore("LalBS");
	}

// allarme basso conduzione
if(LalBC != NO_SOGLIA)
	{
	sprintf(riga,"%.2f",LalBC);
	if(ins_campo_char("LalBC",riga,&record)!=1)
		errore("LalBC");
	}

// allarme alto sicurezza
if(LalAS != NO_SOGLIA)
	{
	sprintf(riga,"%.2f",LalAS);
	if(ins_campo_char("LalAS",riga,&record)!=1)
		errore("LalBS");
	}

// allarme alto conduzione
if(LalAC != NO_SOGLIA)
	{
	sprintf(riga,"%.2f",LalAC);
	if(ins_campo_char("LalAC",riga,&record)!=1)
		errore("LalAC");
	}

// gerarchie
if(CostruisciGer(riga,ger0,ger1,ger2,ger3,ger4,ger5)==1)
	{
	if(ins_campo_char("Gerarchia",riga,&record)!=1)
		errore("Gerarchia");
	}
else
	errore("CostruisciGer");

// scrittura del record
if(scrivi_record(path_output,"editaa",&record)!=1)
        errore("scrivi_record");

return(1);

/**
       init_record(&record,editaa,NUM_CAMPI_EDITAA);
        sprintf(nome,"PIPPO_%d",i);
        ins_campo_char("Sigla",nome,&record);
        sprintf(nome,"S_PIPPO_%d",i);
        ins_campo_char("SiglaSim",nome,&record);
        ins_campo_int("IDscheda",indice_fisico_aa,&record);
        ins_campo_int("IDpunto",1,&record);
        ++indice_fisico_aa;
        scrivi_record(path_output,"editaa",&record);
**/
}
