/*
   modulo CreateFdcom.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFdcom.c	2.4
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>

#include "ToRtf.h"
#include "db.h"
#include "g0gerdb.inc"
#include "g3calcdb.inc"
#include "fileop.inc"
#include "simfile.inc"
#include <string.h>

extern char path_txt[FILENAME_MAX+1];
int CreateFdcom()
{

FILE *fp;
ID_TABLE *tabella;
VAL_RET valore;
PUNTATORE punt;
int j,i,num_record;
S_FDCOM_SIM fdcom;
char szBuffer[l_szBuffer];

printf("Creazione file fdcom.rtf\n");

fp=fopen("fdcom.rtf","w");

tabella = OpenTablePath(path_txt,DO);
if(tabella == NULL)
{
        fprintf(stderr,"CreateFdcom: apertura tabella\n");
        return(0);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	fdcom.comando=i;

	if(GetVal(tabella,"TipoCom",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal TipoCom\n");
        	return(0);
       	}
	fdcom.tipo=valore.int_val;

	if(GetVal(tabella,"SiglaOrg",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal SiglaOrg\n");
        	return(0);
       	}
	if(SetPunt(valore.char_val,&punt))
		fdcom.organo=punt.punt;
	else
		fdcom.organo=-1;

	if(GetVal(tabella,"TimeOut",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal TimeOut\n");
        	return(0);
       	}
	fdcom.time=valore.int_val;

	for(j=0;j<st_com;j++)
	{
		sprintf(szBuffer,"StAttuale%d",j+1);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateFdcom: Errore GetVal StAttuale%d\n",j+1);
        		return(0);
       		}
		fdcom.stat[j].st_att=GetStatoOrgano(valore.char_val);

		sprintf(szBuffer,"StAtteso%d",j+1);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateFdcom: Errore GetVal StAtteso%d\n",j+1);
        		return(0);
       		}
		fdcom.stat[j].st_fut=GetStatoOrgano(valore.char_val);
	}

	if(GetVal(tabella,"InStampa",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal  InStampa\n");
        	return(0);
       	}
	fdcom.abili=valore.int_val;

	if(GetVal(tabella,"Azione",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal  Azione\n");
        	return(0);
       	}
	if(fdcom.organo>=0)
		fdcom.onoff= -1;
	else
		fdcom.onoff=valore.int_val;

	if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdcom: Errore GetVal  SiglaSim\n");
        	return(0);
       	}
	if(SetPunt(valore.char_val,&punt))
		fdcom.puntda=punt.punt;
	else
		fdcom.puntda=-1;

	fwrite(&fdcom,1,sizeof(fdcom),fp);
}

CloseTable(tabella);
fclose(fp);

return(1);
}
