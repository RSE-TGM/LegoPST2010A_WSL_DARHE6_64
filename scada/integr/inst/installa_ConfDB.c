/*
   modulo installa_ConfDB.c
   tipo 
   release 1.3
   data 5/15/96
   reserved @(#)installa_ConfDB.c	1.3
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
#include <editconfigurazionedb.h>

extern char *path_input;
extern char *path_output;

#define errore(stringa) { \
        fprintf(stderr,"Attenzione !!!\nErrore gestione ConfDB [%s]\n",stringa); \
        exit(1); \
        }

static int sistema_dim(int);

int crea_ConfDB()
{
return(scrivi_header(path_output,"editConfDB",editconfigurazionedb,
                NUM_CAMPI_EDITCONFIGURAZIONEDB));
}

static int sistema_dim(int dim)
{
int ret = dim;

ret = ret + 256 - ret%256;

return(ret);
}

int installa_ConfDB()
{
RECORD record;
ID_TABLE *tabella;
int dim_aa = 0;
int dim_ac = 0;
int dim_as = 0;
int dim_ad = 0;
int dim_ao = 0;
int dim_da = 0;
int dim_dc = 0;
int dim_ds = 0;
int dim_dd = 0;
int dim_do = 0;
int dim_or = 0;
int dim_st = 0;

if(crea_ConfDB()!=1)
        errore("Creazione tabella");

// inizializza il record
if(init_record(&record,editconfigurazionedb,NUM_CAMPI_EDITCONFIGURAZIONEDB)!=1)
                errore("init_record");

// AA
tabella = OpenTablePath(path_output,"editaa");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editaa");
        return(0);
        }
dim_aa = NumRecord(tabella);
if(ins_campo_int("DimAA",sistema_dim(dim_aa),&record)!=1)
                errore("DimAA");
CloseTable(tabella);

// AC
tabella = OpenTablePath(path_output,"editac");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editac");
        return(0);
        }
dim_ac = NumRecord(tabella);
if(ins_campo_int("DimAC",sistema_dim(dim_ac),&record)!=1)
                errore("DimAC");
CloseTable(tabella);

// AS
tabella = OpenTablePath(path_output,"editas");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editas");
        return(0);
        }
dim_as = NumRecord(tabella);
if(ins_campo_int("DimAS",sistema_dim(dim_as),&record)!=1)
                errore("DimAS");
CloseTable(tabella);

// AD
tabella = OpenTablePath(path_output,"editad");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editad");
        return(0);
        }
dim_ad = NumRecord(tabella);
if(ins_campo_int("DimAD",sistema_dim(dim_ad),&record)!=1)
                errore("DimAD");
CloseTable(tabella);

// AO
tabella = OpenTablePath(path_output,"editao");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editao");
        return(0);
        }
dim_ao = NumRecord(tabella);
if(ins_campo_int("DimAO",sistema_dim(dim_ao),&record)!=1)
                errore("DimAO");
CloseTable(tabella);

// DA
tabella = OpenTablePath(path_output,"editda");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editda");
        return(0);
        }
dim_da = NumRecord(tabella);
if(ins_campo_int("DimDA",sistema_dim(dim_da),&record)!=1)
                errore("DimDA");
CloseTable(tabella);

// DC
tabella = OpenTablePath(path_output,"editdc");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editdc");
        return(0);
        }
dim_dc = NumRecord(tabella);
if(ins_campo_int("DimDC",sistema_dim(dim_dc),&record)!=1)
                errore("DimDC");
CloseTable(tabella);

// DS
tabella = OpenTablePath(path_output,"editds");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editds");
        return(0);
        }
dim_ds = NumRecord(tabella);
if(ins_campo_int("DimDS",sistema_dim(dim_ds),&record)!=1)
                errore("DimDS");
CloseTable(tabella);

// DD
tabella = OpenTablePath(path_output,"editdd");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editdd");
        return(0);
        }
dim_do = NumRecord(tabella);
if(ins_campo_int("DimDD",sistema_dim(dim_dd),&record)!=1)
                errore("DimDD");
CloseTable(tabella);

// DO
tabella = OpenTablePath(path_output,"editdo");
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarStr: apertura tabella [%s]\n","editdo");
        return(0);
        }
dim_do = NumRecord(tabella);
if(ins_campo_int("DimDO",sistema_dim(dim_do),&record)!=1)
                errore("DimDO");
CloseTable(tabella);

// OR
if(ins_campo_int("Organi",sistema_dim(dim_or),&record)!=1)
                errore("Organi");
// ST
if(ins_campo_int("Stringhe",sistema_dim(dim_st),&record)!=1)
                errore("Stringhe");

// scrittura del record
if(scrivi_record(path_output,"editConfDB",&record)!=1)
                errore("scrivi_record");
return(1);
}

