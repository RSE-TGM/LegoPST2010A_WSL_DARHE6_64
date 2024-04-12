/*
   modulo installa_AllarSer.c
   tipo 
   release 1.2
   data 5/15/96
   reserved @(#)installa_AllarSer.c	1.2
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
#include <editallarser.h>

extern char *path_input;
extern char *path_output;

#define errore(stringa) { \
        fprintf(stderr,"Attenzione !!!\nErrore gestione AllarServ [%s]\n",stringa); \
        exit(1); \
        }

int crea_AllarServ()
{
return(scrivi_header(path_output,"editAllarServ",editallarser,
                NUM_CAMPI_EDITALLARSER));
}

int installa_AllarSer()
{
RECORD record;
ID_TABLE *tabella;
VAL_RET valore;
int i;
char campo[255];

if(crea_AllarServ()!=1)
        errore("Creazione tabella");

tabella = OpenTablePath(path_input,SCDCONF_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarAs: apertura tabella [%s]\n",SCDCONF_TABLE);
        return(0);
        }

// inizializza il record
        if(init_record(&record,editallarser,NUM_CAMPI_EDITALLARSER)!=1)
                errore("init_record");
for(i=1;i<4;i++)
        {
	sprintf(campo,"SCD_SEVCIC%d",i);
        // SCD_SEVCIC
        if(GetVal(tabella,campo,0,&valore)!=1)
                 {
                 fprintf(stderr,
                       "installa_AllarServ: Errore GetVal SEVCIC%d\n",i);
                 CloseTable(tabella);
                 return(0);
                 }
	if(valore.int_val == 1)
                 {
		 sprintf(campo,"Sev%dCica",i);
		 if(ins_campo_int(campo,-1,&record)!=1)
                        errore("SEVCIC");
                 }
	else
                 {
		 sprintf(campo,"Sev%dCica",i);
		 if(ins_campo_int(campo,0,&record)!=1)
                        errore("SEVCIC");
                 }
		
	}

// scrittura del record
if(scrivi_record(path_output,"editAllarServ",&record)!=1)
                errore("scrivi_record");

CloseTable(tabella);
return(1);
}
