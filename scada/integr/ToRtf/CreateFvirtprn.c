/*
   modulo CreateFvirtprn.c
   tipo 
   release 2.5
   data 6/13/96
   reserved @(#)CreateFvirtprn.c	2.5
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "osf1.h"
#include <stdio.h>
#include <string.h>

#include "ToRtf.h"
#include "db.h"
#include "dconf.inc"
#include "tipal.inc"
#include "print.inc"
#include "virtinv.h"

extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];

int CreateFvirtprn()
{
FILE *fp;
ID_TABLE *tabella;
VAL_RET valore;
int i,j,num_record;
char szBuffer[l_szBuffer];

printf("Creazione file fvirtprn.rtf\n");

fp=fopen("fvirtprn.rtf","w");

/* Configurazione stampanti fisiche */
tabella = OpenTablePath(path_txt,CONF_STAMP_FIS);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFvirtprn: apertura tabella CONF_STAMPANTI\n");
        return(0);
}

num_record=NumRecord(tabella);
fputs("BEGIN_FIS_PER\n",fp);

for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}
	fprintf(fp," %d",valore.int_val);

	if(GetVal(tabella,"Device",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Device\n");
        	return(0);
       	}
        fprintf(fp," %s",valore.char_val);

	if(GetVal(tabella,"baud",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal baud\n");
        	return(0);
       	}
        fprintf(fp," %s",valore.char_val);

	if(GetVal(tabella,"data",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal data\n");
        	return(0);
       	}
        fprintf(fp," %s",valore.char_val);

	if(GetVal(tabella,"stop",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal stop\n");
        	return(0);
       	}
        fprintf(fp," %s",valore.char_val);

	if(GetVal(tabella,"parita",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal parita\n");
        	return(0);
       	}
	fprintf(fp," %s\n",valore.char_val);
}
fputs("END_FIS_PER\n\n",fp);
CloseTable(tabella);

tabella = OpenTablePath(path_txt,CONF_STAMP_VIR);

if(tabella == NULL)
{
        fprintf(stderr,"CreateFvirtprn: apertura tabella CONF_STAMP_VIR\n");
        return(0);
}

num_record=NumRecord(tabella);

/* Associazione fra stampanti virtuali e zone di impianto */
fputs("BEGIN_GROUP_LBG\n",fp);
for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}
	if(valore.int_val>n_virt_lbg)
		break;
	fprintf(fp," VLBG%d",valore.int_val);

	for(j=0;j<conf_max_zone;j++)
	{
		sprintf(szBuffer,"zona%d",j);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
	       	{
       	 		fprintf(stderr,"CreateFvirtprn: Errore GetVal zona%d\n",j);
        		return(0);
       		}

		if(valore.int_val)
			fprintf(fp," %d",j);
	}

	fprintf(fp," -1\n");
}
fputs("END_GROUP_LBG\n\n",fp);

/* Associazione fra stampanti virtuali libro giornale e stampanti fisiche */
fputs("BEGIN_FIS_LBG\n",fp);
for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}
	if(valore.int_val>n_virt_lbg)
		break;
	fprintf(fp," VLBG%d",valore.int_val);

	for(j=0;j<n_DevFis;j++)
	{
		sprintf(szBuffer,"linea%d",j);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
	       	{
       	 		fprintf(stderr,"CreateFvirtprn: Errore GetVal linea%d\n",j);
        		return(0);
       		}

		fprintf(fp," %d",valore.int_val);
	}

	fprintf(fp,"\n");
}
fputs("END_FIS_LBG\n\n",fp);

/* Associazione fra stampanti virtuali dei tabulati e stampanti fisiche */
fputs("BEGIN_FIS_TAB\n",fp);
for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}
	if(valore.int_val<=n_virt_lbg)
		continue;
	fprintf(fp," VTAB%d",valore.int_val-n_virt_lbg);

	for(j=0;j<n_DevFis;j++)
	{
		sprintf(szBuffer,"linea%d",j);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
	       	{
       	 		fprintf(stderr,"CreateFvirtprn: Errore GetVal linea%d\n",j);
        		return(0);
       		}

		fprintf(fp," %d",valore.int_val);
	}

	fprintf(fp,"\n");
}
fputs("END_FIS_TAB\n\n",fp);

/* Stampante di default dei tabulati */
for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}
	if(valore.int_val<=n_virt_lbg)
		continue;

	if(GetVal(tabella,"zona0",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFvirtprn: Errore GetVal Indice\n");
        	return(0);
       	}

	if(valore.int_val)
	{
		fprintf(fp,"DEF_TAB_VIRT %d\n",valore.int_val);
		break;
	}
}

CloseTable(tabella);

fclose(fp);

return(1);
}
