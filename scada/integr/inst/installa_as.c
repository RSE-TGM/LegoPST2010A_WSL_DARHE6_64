/*
   modulo installa_as.c
   tipo 
   release 1.9
   data 6/14/96
   reserved @(#)installa_as.c	1.9
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
#include <editas.h>
#include <g1tipdb.inc>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione AS [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_as()
{
return(scrivi_header(path_output,"editas",editas,NUM_CAMPI_EDITAS));
}

int installa_as(
        char *Sigla, // Sigla sigla del punto sullo SCADA
        char *Descrizione, // Descrizione del punto
	char *Unitamisura, // Unita' di misura del punto
	int Periodo,    // Periodo della calcolata
	int TipoCalc,    // TipoCalc della calcolata
        float LalBS, // LalBS      bassa sicurezza, non definita = NO_SOGLIA
        float LalBC, // LalBC      bassa conduzione, non definita = NO_SOGLIA
        float LalAC, // LalAC      alta conduzione, non definita = NO_SOGLIA
        float LalAS, // LalAS      alta sicurezza, non definita = NO_SOGLIA
	int Zonaimpianto,    // Zona di impianto 
	int BandaMorta,    // BandaMorta % banda morta
	int Trattamento,    // Trattamento Trattamento del punto
        int Severita,    // Severita   livello di severita'
        int ger0,    // livello di gerarchia 0 non definita = NO_GER
        int ger1,    // livello di gerarchia 1 non definita = NO_GER
        int ger2,    // livello di gerarchia 2 non definita = NO_GER
        int ger3,    // livello di gerarchia 3 non definita = NO_GER
        int ger4,    // livello di gerarchia 4 non definita = NO_GER
        int ger5,   // livello di gerarchia 5 non definita = NO_GER
        int cger0,    // livello di gerarchia calc 0 non definita = NO_GER
        int cger1,    // livello di gerarchia calc 1 non definita = NO_GER
        int cger2,    // livello di gerarchia calc 2 non definita = NO_GER
        int cger3,    // livello di gerarchia calc 3 non definita = NO_GER
        int cger4,    // livello di gerarchia calc 4 non definita = NO_GER
        int cger5,   // livello di gerarchia calc 5 non definita = NO_GER
        int cdatabase,    // database allarmi per la calcolata
        int czona     // zona di impianto per la calcolata
        )
{
RECORD record;
char riga[50];
static int prog = 0;

// Aggiorna tabella editnomi.txt
installa_nomi(Sigla,"AS",prog++,g1tipas);

// inizializza il record
if(init_record(&record,editas,NUM_CAMPI_EDITAS)!=1)
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

// inserisce il Periodo
if(ins_campo_int("Periodo",Periodo,&record)!=1)
	errore("Periodo");

// inserisce il TipoCalc
if(ins_campo_int("TipoCalc",TipoCalc,&record)!=1)
	errore("TipoCalc");

// inserisce i contribuenti
sprintf(riga,"%d",cger0);
if(ins_campo_char("Contrib1",riga,&record)!=1)
	errore("Contrib1");
sprintf(riga,"%d",cger1);
if(ins_campo_char("Contrib2",riga,&record)!=1)
	errore("Contrib2");
sprintf(riga,"%d",cger2);
if(ins_campo_char("Contrib3",riga,&record)!=1)
	errore("Contrib3");
sprintf(riga,"%d",cger3);
if(ins_campo_char("Contrib4",riga,&record)!=1)
	errore("Contrib4");
sprintf(riga,"%d",cger4);
if(ins_campo_char("Contrib5",riga,&record)!=1)
	errore("Contrib5");
sprintf(riga,"%d",cger5);
if(ins_campo_char("Contrib6",riga,&record)!=1)
	errore("Contrib6");
sprintf(riga,"%d",cdatabase);
if(ins_campo_char("Contrib7",riga,&record)!=1)
	errore("Contrib7");
sprintf(riga,"%d",czona);
if(ins_campo_char("Contrib8",riga,&record)!=1)
	errore("Contrib8");

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
if(scrivi_record(path_output,"editas",&record)!=1)
        errore("scrivi_record");

return(1);

}
