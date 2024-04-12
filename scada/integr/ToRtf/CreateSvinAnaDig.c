/*
   modulo CreateSvinAnaDig.c
   tipo 
   release 2.5
   data 6/13/96
   reserved @(#)CreateSvinAnaDig.c	2.5
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
#include "fileop.inc"
#include "simmsg.inc"

extern char path_txt[FILENAME_MAX+1];

extern DB_HEADER header_ToRtf;

int CreateSvinAnaDig()
{
ID_TABLE *tabella;
VAL_RET valore;
FILE *fp;
SVINHEA header;
SVINREC record;
int num_record,i;

printf("Creazione file fsvinana.rtf\n");

tabella = OpenTablePath(path_txt,AA);
if(tabella == NULL)
	{
	fprintf(stderr,"CreateSvinAnaDig: apertura tabella\n");
	return(0);
	}
num_record = NumRecord(tabella);
header.tipopunti=ANA;
header.numpunti=0;
for(i=0;i<num_record;i++)
        {
	if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
                        {
                        fprintf(stderr,
                           "CreateFdbdp: Errore CreateSvinAnaDig SiglaSim\n");
                        return(0);
                        }
	if(strlen(valore.char_val))
		++header.numpunti;
	}
if((fp=fopen("fsvinana.rtf","w"))==NULL)
      {
      fprintf(stderr,"CreateFdbdp: Errore CreateSvinAnaDig fopen\n");
      return(0);
      }
fwrite(&header,sizeof(SVINHEA),1,fp);
header.numpunti=0;
for(i=0;i<num_record;i++)
        {
	if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
                        {
                        fprintf(stderr,
                           "CreateFdbdp: Errore CreateSvinAnaDig SiglaSim\n");
                        return(0);
                        }
	if(!strlen(valore.char_val))
		continue;
	memset(record.sigla,' ',LUN);
	memcpy(record.sigla,valore.char_val,min(strlen(valore.char_val),LUN));
	record.punt=i;
	fwrite(&record,sizeof(SVINREC),1,fp);
	++header.numpunti;
	}
fclose(fp);
		

if(!CloseTable(tabella))
	{
	fprintf(stderr,"CreateSvinAnaDig: Errore chiusura tabella\n");
	return(0);
	}

printf("Creazione file fsvindig.rtf\n");

tabella = OpenTablePath(path_txt,DA);
if(tabella == NULL)
	{
	fprintf(stderr,"CreateSvinAnaDig: apertura tabella\n");
	return(0);
	}
num_record = NumRecord(tabella);
header.tipopunti=DIG;
header.numpunti=0;
for(i=0;i<num_record;i++)
        {
	if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
                        {
                        fprintf(stderr,
                           "CreateFdbdp: Errore CreateSvinAnaDig SiglaSim\n");
                        return(0);
                        }
	if(strlen(valore.char_val))
		++header.numpunti;
	}
if((fp=fopen("fsvindig.rtf","w"))==NULL)
      {
      fprintf(stderr,"CreateFdbdp: Errore CreateSvinAnaDig fopen\n");
      return(0);
      }
fwrite(&header,sizeof(SVINHEA),1,fp);
header.numpunti=0;
for(i=0;i<num_record;i++)
        {
	if(GetVal(tabella,"SiglaSim",i,&valore)!=1)
                        {
                        fprintf(stderr,
                           "CreateFdbdp: Errore CreateSvinAnaDig SiglaSim\n");
                        return(0);
                        }
	if(!strlen(valore.char_val))
		continue;
	memset(record.sigla,' ',LUN);
	memcpy(record.sigla,valore.char_val,min(strlen(valore.char_val),LUN));
	record.punt=i;
	fwrite(&record,sizeof(SVINREC),1,fp);
	++header.numpunti;
	}
fclose(fp);
		

if(!CloseTable(tabella))
	{
	fprintf(stderr,"CreateSvinAnaDig: Errore chiusura tabella\n");
	return(0);
	}

return(1);
}
