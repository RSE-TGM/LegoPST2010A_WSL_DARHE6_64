/*
   modulo CreateFstato.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFstato.c	2.4
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

#include "ToRtf.h"
#include "db.h"
#include "fileop.inc"
extern char path_txt[FILENAME_MAX+1];

int CreateFstato()
{

FILE *fp;
ID_TABLE *tabella;
VAL_RET valore;
S_FSTATO fstato;
int j,i,num_record;
char szBuffer[l_szBuffer];

printf("Creazione file fstato.rtf\n");

fp=fopen("fstato.rtf","w");

tabella = OpenTablePath(path_txt,TO);
if(tabella == NULL)
{
        fprintf(stderr,"CreateFstato: apertura tabella\n");
        return(0);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	memset(&fstato,-1,sizeof(fstato));

	if(GetVal(tabella,"TipoO",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFstato: Errore GetVal TipoO\n");
        	return(0);
       	}
	
	if(*valore.char_val=='\0')	break;

	if(GetVal(tabella,"NumSegC",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFstato: Errore GetVal NumSegC\n");
        	return(0);
       	}
	
	fstato.ncontr=valore.int_val;

	for(j=1;j<=conf_max_stati_organo;j++)
	{
		sprintf(szBuffer,"Stato%d",j);

		if(GetVal(tabella,szBuffer,i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateFstato: Errore GetVal Stato%d\n",j);
        		return(0);
       		}
		
		fstato.vet_stati[j-1]=GetStatoOrgano(valore.char_val);
	}

	fwrite(&fstato,1,sizeof(fstato),fp);
}

CloseTable(tabella);
fclose(fp);

return(1);
}

int GetTipoOrgano(char *organo)
{
ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;

if(*organo=='\0') return -1;

tabella = OpenTablePath(path_txt,TO);
if(tabella == NULL)
{
        fprintf(stderr,"GetTipoOrgano: apertura tabella\n");
        return(-1);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetVal(tabella,"TipoO",i,&valore)!=1)
        {
                fprintf(stderr,"GetTipoOrgano: Errore GetVal TipoO\n");
		CloseTable(tabella);
                return(-1);
        }
	
	if(strcmp(organo,valore.char_val))
		continue;

        if(GetVal(tabella,"codice",i,&valore)!=1)
        {
                fprintf(stderr,"GetTipoOrgano: Errore GetVal codice\n");
		CloseTable(tabella);
                return(-1);
        }
	CloseTable(tabella);
	return valore.int_val;
}

CloseTable(tabella);
return (-1);
}

int GetStatoOrgano(char *stato)
{
ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;

if(*stato=='\0') return -1;

tabella = OpenTablePath(path_txt,STATI_ORGANI);
if(tabella == NULL)
{
        fprintf(stderr,"GetStatoOrgano: apertura tabella\n");
        return(-1);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetVal(tabella,"Stato",i,&valore)!=1)
        {
                fprintf(stderr,"GetStatoOrgano: Errore GetVal Stato\n");
		CloseTable(tabella);
                return(-1);
        }

        if(strcasecmp(stato,valore.char_val))
                continue;

        if(GetVal(tabella,"codice",i,&valore)!=1)
        {
                fprintf(stderr,"GetStatoOrgano: Errore GetVal codice\n");
		CloseTable(tabella);
                return(-1);
        }
	CloseTable(tabella);
        return valore.int_val;
}

CloseTable(tabella);
return (-1);
}

int GetContribOrgano(char *organo)
{
ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;

if(*organo=='\0') return -1;

tabella = OpenTablePath(path_txt,TO);
if(tabella == NULL)
{
        fprintf(stderr,"GetTipoOrgano: apertura tabella\n");
        return(-1);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
        if(GetVal(tabella,"TipoO",i,&valore)!=1)
        {
                fprintf(stderr,"GetContribOrgano: Errore GetVal TipoO\n");
		CloseTable(tabella);
                return(-1);
        }
	
	if(strcmp(organo,valore.char_val))
		continue;

        if(GetVal(tabella,"NumSegC",i,&valore)!=1)
        {
                fprintf(stderr,"GetContribOrgano: Errore GetVal NumSegC\n");
		CloseTable(tabella);
                return(-1);
        }
	CloseTable(tabella);
	return valore.int_val;
}

CloseTable(tabella);
return (-1);
}
