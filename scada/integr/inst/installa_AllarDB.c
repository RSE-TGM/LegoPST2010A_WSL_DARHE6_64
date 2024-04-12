/*
   modulo installa_AllarDB.c
   tipo 
   release 1.4
   data 5/15/96
   reserved @(#)installa_AllarDB.c	1.4
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
#include <editallardb.h>

extern char *path_input;
extern char *path_output;

#define errore(stringa) { \
        fprintf(stderr,"Attenzione !!!\nErrore gestione AllarDb [%s]\n",stringa); \
        exit(1); \
        }



int crea_AllarDB()
{
return(scrivi_header(path_output,"editAllarDB",editallardb,
		NUM_CAMPI_EDITALLARDB));
}

int installa_AllarDB()
{
RECORD record;
ID_TABLE *tabella;
VAL_RET valore;
int num_record;
int i,j;
char campo[255];

if(crea_AllarDB()!=1)
	errore("Creazione tabella");

tabella = OpenTablePath(path_input,SCDDBA_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarAs: apertura tabella [%s]\n",SCDDBA_TABLE
);
        return(0);
        }
num_record = NumRecord(tabella);


for(i=0;i<num_record;i++)
        {
	// inizializza il record
	if(init_record(&record,editallardb,NUM_CAMPI_EDITALLARDB)!=1)
        	errore("init_record");
	// SCDDBA_ID
        if(GetVal(tabella,"SCDDBA_ID",i,&valore)!=1)
                {
                fprintf(stderr,"installa_AllarDB: Errore GetVal SCDDBA_ID\n");
		CloseTable(tabella);
                return(0);
                }
	if(ins_campo_int("Indice",valore.int_val,&record)!=1)
        	errore("SCDDBA_ID");
	// SCDDBA_NUMALL
        if(GetVal(tabella,"SCDDBA_NUMALL",i,&valore)!=1)
                {
                fprintf(stderr,"installa_AllarDB: Errore GetVal SCDDBA_NUMALL\n");
		CloseTable(tabella);
                return(0);
                }
	if(valore.int_val<=0)
		continue;
	if(ins_campo_int("NumAll",valore.int_val,&record)!=1)
        	errore("SCDDBA_NUMALL");

	for(j=0;j<32;j++)
                {
		sprintf(campo,"SCDDBA_ZONE_%d",j);
		// SCDDBA_ID
        	if(GetVal(tabella,campo,i,&valore)!=1)
                	{
                	fprintf(stderr,
			"installa_AllarDB: Errore GetVal SCDDBA_ZONE_%d\n",j);
			CloseTable(tabella);
                	return(0);
                	}
		sprintf(campo,"zona%d",j);
		if(ins_campo_int(campo,valore.int_val,&record)!=1)
        		errore("SCDDBA_ZONE_");
                }

	// scrittura del record
	if(scrivi_record(path_output,"editAllarDB",&record)!=1)
        	errore("scrivi_record");
        }
CloseTable(tabella);

return(1);
}
