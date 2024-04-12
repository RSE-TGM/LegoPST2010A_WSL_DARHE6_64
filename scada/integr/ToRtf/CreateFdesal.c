/*
   modulo CreateFdesal.c
   tipo 
   release 2.5
   data 6/13/96
   reserved @(#)CreateFdesal.c	2.5
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
#include "dconf.inc"
#include "tipal.inc"
#include "VociAlla.h"

extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];

int CreateFdesal()
{
FILE *fp;
ID_TABLE *tabella;
VAL_RET valore;
int i,j,k,num_record;
char szBuffer[l_szBuffer];

printf("Creazione file fdesal.rtf\n");

fp=fopen("fdesal.rtf","w");

/* Struttura dei database allarmi */
tabella = OpenTablePath(path_txt,CONF_DB_ALLARMI);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFdesal: apertura tabella CONF_DB_ALLARMI\n");
        return(0);
}

num_record=NumRecord(tabella);
fputs("BEGIN_DBS_ALL\n",fp);

for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Indice\n");
        	return(0);
       	}
	fprintf(fp," %d",valore.int_val);

	if(GetVal(tabella,"NumAll",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal NumAll\n");
        	return(0);
       	}
	fprintf(fp," %d",valore.int_val);

        printf ("Zone=[%d]\n",conf_max_zone);
	for(j=0;j<conf_max_zone;j++)
	{
		sprintf(szBuffer,"zona%d",j);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
       		{
       	 		fprintf(stderr,"CreateFdesal: Errore GetVal zona%d\n",j);
       	 		return(0);
       		}
		if(valore.int_val)
			fprintf(fp," %d",j);
	}
	fputs(" -1\n",fp);
}
fputs("END_DBS_ALL\n\n",fp);
CloseTable(tabella);

/* Database allarmi: tipi  e livelli */
tabella = OpenTablePath(path_txt,CONF_LIV_ALLARMI);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFdesal: apertura tabella CONF_DB_ALLARMI\n");
        return(0);
}

num_record=NumRecord(tabella);
fputs("BEGIN_ALLAR_LIV\n",fp);

for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Indice\n");
        	return(0);
       	}
	for(k=0;k<NUMERO_VOCI_ALLARME;k++)
		if(valore.int_val==voci_allarme[k].Indice)
			break;
	if(k==NUMERO_VOCI_ALLARME)
		fprintf(fp,"all_%02d",valore.int_val);
	else
		fprintf(fp,"%-40s",voci_allarme[k].CodiceFile);

	for(j=1;j<=max_liv;j++)
	{
		sprintf(szBuffer,"ColSev%d",j);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
	       	{
       	 		fprintf(stderr,"CreateFdesal: Errore GetVal ColSev%d\n",j);
        		return(0);
       		}
		fprintf(fp," %s",valore.char_val);
	}

	if(GetVal(tabella,"Emissione",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Emissione\n");
        	return(0);
       	}
	fprintf(fp," %s",valore.char_val);

	if(GetVal(tabella,"Rientro",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Rientro\n");
        	return(0);
       	}
	fprintf(fp," %s\n",valore.char_val);
}

fputs("END_ALLAR_LIV\n\n",fp);
CloseTable(tabella);

/* Configurazioni varie */
tabella = OpenTablePath(path_txt,CONF_SER_ALLARMI);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFdesal: apertura tabella CONF_DB_ALLARMI\n");
        return(0);
}

if(GetVal(tabella,"TipoCicalino",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal TipoCicalino\n");
        return(0);
}
fprintf(fp,"TIPO_CICALINO %d\n",valore.int_val);

for(j=1;j<=max_liv;j++)
{
	sprintf(szBuffer,"Sev%dCica",j);
	if(GetVal(tabella,szBuffer,0,&valore)!=1)
	{
       		fprintf(stderr,"CreateFdesal: Errore GetVal Sev%dCica\n",j);
        	return(0);
	}
	if(valore.int_val == -1)
		fprintf(fp,"SEV%d_CICALINO 1\n",j);
	else
		fprintf(fp,"SEV%d_CICALINO 0\n",j);
}

if(GetVal(tabella,"FaMediaT",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaMediaT\n");
        return(0);
}
fprintf(fp,"COEF_FA_MEDIAT 0.%d\n",valore.int_val);

if(GetVal(tabella,"FaFiltro",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaFiltro\n");
        return(0);
}
fprintf(fp,"COEF_FA_FILTRO 0.%d\n",valore.int_val);

if(GetVal(tabella,"FaScarto",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaScarto\n");
        return(0);
}
fprintf(fp,"COEF_FA_SCARTO 0.%d\n",valore.int_val);

if(GetVal(tabella,"FaMediaI",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaMediaI\n");
        return(0);
}
fprintf(fp,"COEF_FA_MEDIAI 0.%d\n",valore.int_val);

if(GetVal(tabella,"FaSomma",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaSomma\n");
        return(0);
}
fprintf(fp,"COEF_FA_SOMMA 0.%d\n",valore.int_val);

if(GetVal(tabella,"FaIntegrale",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal FaIntegrale\n");
        return(0);
}
fprintf(fp,"COEF_FA_INTEGRALE 0.%d\n\n",valore.int_val);

if(GetVal(tabella,"freq_ut",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal freq_ut\n");
        return(0);
}
fprintf(fp,"FREQ_UT %d\n\n",valore.int_val);

if(GetVal(tabella,"REP_MESS",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal REP_MESS\n");
        return(0);
}
fprintf(fp,"REP_MESS %d\n\n",valore.int_val);

if(GetVal(tabella,"REP_RETRY",0,&valore)!=1)
{
        fprintf(stderr,"CreateFdesal: Errore GetVal REP_RETRY\n");
        return(0);
}
fprintf(fp,"REP_RETRY %d\n\n",valore.int_val);

CloseTable(tabella);

/* Coefficienti K */
tabella = OpenTablePath(path_txt,CONF_TABK);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFdesal: apertura tabella CONF_TABK\n");
        return(0);
}

num_record=NumRecord(tabella);
fputs("BEGIN_TAB_K\n",fp);

for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Indice\n");
        	return(0);
	}
	fprintf(fp," %d",valore.int_val);

	if(GetVal(tabella,"Coeff",i,&valore)!=1)
	{
        	fprintf(stderr,"CreateFdesal: Errore GetVal Coeff\n");
        	return(0);
	}
	fprintf(fp," %d\n",valore.int_val);
}

fputs("END_TAB_K\n\n",fp);
CloseTable(tabella);

fclose(fp);

return(1);
}
