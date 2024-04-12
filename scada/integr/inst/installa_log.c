/*
   modulo installa_log.c
   tipo 
   release 1.2
   data 5/15/96
   reserved @(#)installa_log.c	1.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>

#include "db.h"
#include "installa.h"
#include "outascii.h"
#include "editlog.h"

extern char *path_input;
extern char *path_output;
#define errore_log(stringa) { \
			    fprintf(stderr,"installa_log: [%s]\n",stringa); \
			    return(0); \
			    }
int crea_log()
{
return(scrivi_header(path_output,"editlog",tabulati,NUM_RECORD_TABULATI));
}

int installa_log()
{
int i,num_rec;
ID_TABLE *tabella;
VAL_RET valore;
RECORD record;

if(!crea_log())
	return 0;

// Legge la tabella iniziale dei tabulati
// e compone la tabella di editing.
tabella=OpenTablePath(path_input,LOG_TABLE);
if(!tabella)
{
	fprintf(stderr,"installa_log: apertura tabella [%s]\n",LOG_TABLE);
	return(0);
}
num_rec=NumRecord(tabella);
for(i=0;i<num_rec;i++)
{
	if(!init_record(&record,tabulati,NUM_RECORD_TABULATI))
		errore_log("init_record");

	if(GetVal(tabella,"LOG_NAME",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_NAME\n");
		return 0;
	}
	if(!ins_campo_char("Nome",valore.char_val,&record))
		errore_log("ins_campo_char \"Nome\"");
	
	if(GetVal(tabella,"LOG_PERIOD",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_PERIOD\n");
		return 0;
	}
	if(!ins_campo_int("Periodo",valore.int_val,&record))
		errore_log("ins_campo_int \"Periodo\"");
	
	if(GetVal(tabella,"LOG_PERIODIC",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_PERIODIC\n");
		return 0;
	}
	if(!ins_campo_int("Periodico",valore.int_val,&record))
		errore_log("ins_campo_int \"Periodico\"");
	
	if(GetVal(tabella,"LOG_CYCLES",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_CYCLES\n");
		return 0;
	}
	if(!ins_campo_int("Cicli",valore.int_val,&record))
		errore_log("ins_campo_int \"Cicli\"");
	
	if(GetVal(tabella,"LOG_WAIT",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_WAIT\n");
		return 0;
	}
	if(!ins_campo_int("Attesa",valore.int_val,&record))
		errore_log("ins_campo_int \"Attesa\"");
	
	if(GetVal(tabella,"LOG_TYPE",i,&valore)!=1)
	{
		fprintf(stderr,"installa_arc: Errore GetVal LOG_TYPE\n");
		return 0;
	}
	if(!ins_campo_int("Tipo",valore.int_val,&record))
		errore_log("ins_campo_int \"Tipo\"");

	if(!scrivi_record(path_output,"editlog",&record))
		errore_log("scrivi_record");
}
CloseTable(tabella);

return 1;
}
