/*
   modulo installa_AllarLiv.c
   tipo 
   release 1.7
   data 6/3/96
   reserved @(#)installa_AllarLiv.c	1.7
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
#include <tag.h>
#include <installa.h>
#include <editallarliv.h>
#include <tipal.inc>

extern char *path_input;
extern char *path_output;

int crea_AllarLiv()
{
return(scrivi_header(path_output,"editAllarLiv",editallarliv,
                NUM_CAMPI_EDITALLARLIV));
}

int installa_AllarLiv()
{
RECORD record;
ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;

if(crea_AllarLiv()!=1)
        errore("Creazione tabella");

// modifica la tabella dei default
tabella = OpenTablePath(path_input,ALARMTYPE_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarAs: apertura tabella [%s]\n",ALARMTYPE_TABLE
);
        return(0);
        }
num_record = NumRecord(tabella);

for(i=0;i<num_record;i++)
{
int rec;
	//  ALTYPE_SIGNAL
	if(GetVal(tabella,"ALTYPE_SIGNAL",i,&valore)!=1)
                {
                fprintf(stderr,
			"installa_AllarLiv: Errore GetVal ALTYPE_SIGNAL\n");
                return(0);
                }
	rec = valore.char_val[0]+max_st_no_sig-'A';
	//  ALTYPE_COLOR_SEV1
        if(GetVal(tabella,"ALTYPE_COLOR_SEV1",i,&valore)!=1)
                {
                fprintf(stderr,
			"installa_AllarLiv: Errore GetVal ALTYPE_COLOR_SEV1\n");
                return(0);
                }
	strcpy(default_allarliv[rec].ColSev1,valore.char_val);
	//  ALTYPE_COLOR_SEV2
        if(GetVal(tabella,"ALTYPE_COLOR_SEV2",i,&valore)!=1)
                {
                fprintf(stderr,
			"installa_AllarLiv: Errore GetVal ALTYPE_COLOR_SEV2\n");
                return(0);
                }
	strcpy(default_allarliv[rec].ColSev2,valore.char_val);
	//  ALTYPE_COLOR_SEV3
        if(GetVal(tabella,"ALTYPE_COLOR_SEV3",i,&valore)!=1)
                {
                fprintf(stderr,
			"installa_AllarLiv: Errore GetVal ALTYPE_COLOR_SEV3\n");
                return(0);
                }
	strcpy(default_allarliv[rec].ColSev3,valore.char_val);
}

for(i=0;i<NUM_CAMPI_DEFAULTALLARLIV;i++)
{
// inizializza il record
        if(init_record(&record,editallarliv,NUM_CAMPI_EDITALLARLIV)!=1)
                errore("init_record");
// Indice
if(ins_campo_int("Indice",default_allarliv[i].Indice,&record)!=1)
                        errore("SEVCIC");

// ColSev1
if(ins_campo_char("ColSev1",default_allarliv[i].ColSev1,&record)!=1)
                        errore("ColSev1");
// ColSev2
if(ins_campo_char("ColSev2",default_allarliv[i].ColSev2,&record)!=1)
                        errore("ColSev2");
// ColSev3
if(ins_campo_char("ColSev3",default_allarliv[i].ColSev3,&record)!=1)
                        errore("ColSev3");
// Emissione
if(ins_campo_char("Emissione",default_allarliv[i].Emissione,&record)!=1)
                        errore("Emissione");
// Rientro
if(ins_campo_char("Rientro",default_allarliv[i].Rientro,&record)!=1)
                        errore("Rientro");
// scrittura del record
if(scrivi_record(path_output,"editAllarLiv",&record)!=1)
                errore("scrivi_record");
}

return(1);
}
