/*
   modulo installa_AllarStr.c
   tipo 
   release 1.3
   data 5/15/96
   reserved @(#)installa_AllarStr.c	1.3
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
#include <editallarstrat.h>

extern char *path_input;
extern char *path_output;

#define errore(stringa) { \
        fprintf(stderr,"Attenzione !!!\nErrore gestione AllarDb [%s]\n",stringa); \
        exit(1); \
        }

int crea_AllarStr()
{
return(scrivi_header(path_output,"editAllarStr",editallarstrat,
                NUM_CAMPI_EDITALLARSTRAT));
}

int installa_AllarStr()
{
RECORD record;
ID_TABLE *tabella;
VAL_RET valore;
int num_record;
int i,j;
char campo[255];
int def_tab;

if(crea_AllarStr()!=1)
        errore("Creazione tabella");

tabella = OpenTablePath(path_input,SCDLBG_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n",SCDLBG_TABLE);
        return(0);
        }
num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
        {
        // inizializza il record
        if(init_record(&record,editallarstrat,NUM_CAMPI_EDITALLARSTRAT)!=1)
                errore("init_record");
        // SCDLBG_ID
        if(GetVal(tabella,"SCDLBG_ID",i,&valore)!=1)
                {
                fprintf(stderr,"installa_AllarStr: Errore GetVal SCDLBG_ID\n");
                CloseTable(tabella);
                return(0);
                }
        if(ins_campo_int("Indice",valore.int_val,&record)!=1)
                errore("SCDLBG_ID");
        for(j=0;j<4;j++)
                {
                sprintf(campo,"SCDLBG_LINE_%d",j);
                // SCDLBG_ID
                if(GetVal(tabella,campo,i,&valore)!=1)
                        {
                        fprintf(stderr,
                        "installa_AllarStr: Errore GetVal SCDLBG_LINE_%d\n",j);
                        CloseTable(tabella);
                        return(0);
                        }
                sprintf(campo,"linea%d",j);
                if(ins_campo_int(campo,valore.int_val,&record)!=1)
                        errore("SCDLBG_LINE_");
                }
        for(j=0;j<32;j++)
                {
                sprintf(campo,"SCDLBG_ZONE_%d",j);
                // SCDLBG_ID
                if(GetVal(tabella,campo,i,&valore)!=1)
                        {
                        fprintf(stderr,
                        "installa_AllarStr: Errore GetVal SCDLBG_ZONE_%d\n",j);
                        CloseTable(tabella);
                        return(0);
                        }
                sprintf(campo,"zona%d",j);
                if(ins_campo_int(campo,valore.int_val,&record)!=1)

                        errore("SCDLBG_ZONE_");
                }

        // scrittura del record
        if(scrivi_record(path_output,"editAllarStr",&record)!=1)
                errore("scrivi_record");
        }
CloseTable(tabella);

// preleva la stampante di default dei tabulati
tabella = OpenTablePath(path_input,SCDCONF_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n",SCDCONF_TABLE);
        return(0);
        }
// SCD_TABDEF
if(GetVal(tabella,"SCD_TABDEF",0,&valore)!=1)
       {
       fprintf(stderr,"installa_AllarStr: Errore GetVal SCD_TABDEF\n");
       CloseTable(tabella);
       return(0);
       }
def_tab = valore.int_val;
CloseTable(tabella);

tabella = OpenTablePath(path_input,SCDTAB_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n",SCDTAB_TABLE);
        return(0);
        }
num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
        {
        // inizializza il record
        if(init_record(&record,editallarstrat,NUM_CAMPI_EDITALLARSTRAT)!=1)
                errore("init_record");
        // SCDTAB_ID
        if(GetVal(tabella,"SCDTAB_ID",i,&valore)!=1)
                {
                fprintf(stderr,"installa_AllarStr: Errore GetVal SCDTAB_ID\n");
                CloseTable(tabella);
                return(0);
                }
        if(ins_campo_int("Indice",valore.int_val+8,&record)!=1) // 8 line * LBG
                errore("SCDTAB_ID");
	// stampante di default
	if(i== def_tab -1)
                {
        	if(ins_campo_int("zona0",def_tab,&record)!=1) 
                	errore("SCD_TABDEF");
                }
        for(j=0;j<4;j++)
                {
                sprintf(campo,"SCDTAB_LINE_%d",j);
                // SCDTAB_ID
                if(GetVal(tabella,campo,i,&valore)!=1)
                        {
                        fprintf(stderr,
                        "installa_AllarStr: Errore GetVal SCDTAB_LINE_%d\n",j);
                        CloseTable(tabella);
                        return(0);
                        }
                sprintf(campo,"linea%d",j);
                if(ins_campo_int(campo,valore.int_val,&record)!=1)
                        errore("SCDTAB_LINE_");
                }
        // scrittura del record
        if(scrivi_record(path_output,"editAllarStr",&record)!=1)
                errore("scrivi_record");
        }
CloseTable(tabella);


return(1);
}
