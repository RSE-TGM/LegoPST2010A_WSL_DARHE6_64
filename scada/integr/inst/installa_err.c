/*
   modulo installa_err.c
   tipo 
   release 1.6
   data 6/14/96
   reserved @(#)installa_err.c	1.6
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)installa_err.c	1.6\t6/14/96";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <db.h>
#include <installa.h>
#include <installa_err.h>

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione PointInst.err [%s]\n",stringa); \
	exit(1); \
	}

extern char *path_input;
extern char *path_output;

int crea_installa_err()
{
return(scrivi_header(path_output,"PointInstErr",installa_err_table,
		NUM_CAMPI_INSTALLA_ERR));
}

int installa_err(
        char *Sigla, // Sigla sigla del punto in errore
	int tipo
        )
{
FILE *fp;
char stringa[255];
RECORD record;
static int err_id=0;

if(tipo == CREATE_FILE_ERR)
	{
	fp = fopen(NOME_FILE_ERR,"w");
	if(fp == NULL)
		errore("creazione file errori");
	fprintf(fp,"\n");
	fprintf(fp,"                            PointInst file error log\n");
	fprintf(fp,"\n");
	fprintf(fp,"\n");
	fclose(fp);
	crea_installa_err();
	return(1);
	}

// inizializza il record
if(init_record(&record,installa_err_table,NUM_CAMPI_INSTALLA_ERR)!=1)
        errore("init_record");

fp = fopen(NOME_FILE_ERR,"a");
if(fp == NULL)
        errore("aggiornamento file errori");
switch(tipo){
	case TAG_NOT_IN_SCADA:
		sprintf(stringa,"tag found in TAG but TAG_SCADA_USE = 0");
		break;
	case TAG_NOT_FOUND_IN_TAG:
		sprintf(stringa,"tag found in simulator but not in TAG table");
		break;
	case TAG_NOT_FOUND_IN_MEASURE_OR_ALARM:
		sprintf(stringa,
	          "tag found in TAG table but not in ALARM or in MEASURE table");
		break;
	case ARC_TAG_NOT_FOUND:
		sprintf(stringa,"historic not configured");
		break;
	case SIGNAL_NOT_FOUND:
		sprintf(stringa,"signal type not found");
		break;
	default:
		sprintf(stringa,"Unknown error on");
	}

fprintf(fp,"[%d] %s [%s]\n",tipo,stringa,Sigla);
fclose(fp);
// Error ID
if(ins_campo_int("ERR_ID",err_id,&record)!=1)
        errore("ID");
// Sigla
if(ins_campo_char("ERR_TAG",Sigla,&record)!=1)
        errore("TAG");
// Descrizione
if(ins_campo_char("ERR_DESCRIPTION",stringa,&record)!=1)
        errore("Descrizione");
// CodiceErr
if(ins_campo_int("ERR_CODE",tipo,&record)!=1)
        errore("CodiceErr");
// scrittura del record
if(scrivi_record(path_output,"PointInstErr",&record)!=1)
        errore("scrivi_record");
err_id++;
return(1);
}
