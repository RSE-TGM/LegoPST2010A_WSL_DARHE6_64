/*
   modulo CreateFdizst.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFdizst.c	2.4
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
int CreateFdizst()
{

FILE *fp;
ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;

printf("Creazione file fdizst.rtf\n");

fp=fopen("fdizst.rtf","w");

tabella = OpenTablePath(path_txt,STATI_ORGANI);
if(tabella == NULL)
{
        fprintf(stderr,"CreateFdizst: apertura tabella\n");
        return(0);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(GetVal(tabella,"Stato",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdizst: Errore GetVal Stato\n");
        	return(0);
       	}
	fprintf(fp,"%-*s  ;",lun_stato,valore.char_val);

	if(GetVal(tabella,"codice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateFdizst: Errore GetVal codice\n");
        	return(0);
       	}
	fprintf(fp,"  %d\n",valore.int_val);
}

CloseTable(tabella);
fclose(fp);

return(1);
}
