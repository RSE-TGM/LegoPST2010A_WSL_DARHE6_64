/*
   modulo CreateFdeao.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFdeao.c	2.4
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <ToRtf.h>
#include <db.h>
#include <dconf.inc>
#include <fileop.inc>
#include <g1tipdb.inc>
#include <g2comdb.inc>
#include <simmsg.inc>


extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];

int CreateFdeao()
{
ID_TABLE *tabella;
VAL_RET valore;
FILE *fp;
int i;
S_FDEAO_SIM ao;
PUNTATORE punt;
int num_record;

printf("Creazione file fdeao.rtf\n");

tabella = OpenTablePath(path_txt,AO);
if(tabella == NULL)
	{
	fprintf(stderr,"CreateFdeao: apertura tabella\n");
	return(0);
	}

if((fp=fopen("fdeao.rtf","w"))==NULL)
	return(0);
num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
        {
	ao.puntdb=i;
	// InStampa
        if(GetVal(tabella,"InStampa",i,&valore)!=1)
                {
                fprintf(stderr,"CreateFdeao: Errore GetVal InStampa\n");
		fclose(fp);
                return(0);
                }
        ao.flabst=valore.int_val;
        // SiglaSim
        if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
                {
                fprintf(stderr,
                   "CreateFdeao: Errore GetVal SiglaSim\n");
		fclose(fp);
                return(0);
                }
	ao.puntaa = -1;
        if(SetPunt(valore.char_val,&punt)==1)
                ao.puntaa=punt.punt;
	fwrite(&ao,sizeof(S_FDEAO_SIM),1,fp);
	}
fclose(fp);


if(!CloseTable(tabella))
	{
	fprintf(stderr,"CreateFdeao: Errore chiusura tabella\n");
	return(0);
	}
return(1);
}
