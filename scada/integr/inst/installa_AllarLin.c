/*
   modulo installa_AllarLin.c
   tipo 
   release 1.4
   data 5/15/96
   reserved @(#)installa_AllarLin.c	1.4
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
#include <editallarline.h>

extern char *path_input;
extern char *path_output;

#define errore(stringa) { \
        fprintf(stderr,"Attenzione !!!\nErrore gestione AllarLin [%s]\n",stringa); \
        exit(1); \
        }



int crea_AllarLin()
{
return(scrivi_header(path_output,"editAllarLin",editallarline,
                NUM_CAMPI_EDITALLARLINE));
}

int installa_AllarLin()
{
RECORD record;
ID_TABLE *tabella;
VAL_RET valore;
int i;
char campo[255];

if(crea_AllarLin()!=1)
        errore("Creazione tabella");

tabella = OpenTablePath(path_input,SCDCONF_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarAs: apertura tabella [%s]\n",SCDCONF_TABLE);
        return(0);
        }
for(i=0;i<8;i++)
        {
	// inizializza il record
        if(init_record(&record,editallarline,NUM_CAMPI_EDITALLARLINE)!=1)
                errore("init_record");

	sprintf(campo,"SCD_PRN_%d",i);
	// SCD_PRN_
        if(GetVal(tabella,campo,0,&valore)!=1)
                 {
                 fprintf(stderr,
                       "installa_AllarLin: Errore GetVal SCD_PRN_%d\n",i);
		 CloseTable(tabella);
                 return(0);
                 }
	if(ins_campo_char("Device",valore.char_val,&record)!=1)
                        errore("SCD_PRN_");
	if(ins_campo_int("Indice",i+1,&record)!=1)
                        errore("SCD_PRN_");

	// scrittura del record
        if(scrivi_record(path_output,"editAllarLin",&record)!=1)
                errore("scrivi_record");
        }
CloseTable(tabella);
return(1);
}
