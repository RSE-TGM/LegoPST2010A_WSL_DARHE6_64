/*
   modulo CreateFgerarch.c
   tipo 
   release 2.6
   data 6/13/96
   reserved @(#)CreateFgerarch.c	2.6
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
#include <malloc.h>

#include "ToRtf.h"
#include "db.h"
#include "dconf.inc"
#include "g0gerdb.inc"

extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];

int CreateFgerarch()
{
FILE *fp;
char *pc;
ID_TABLE *tabella;
S_DBGERA gerarchia;
int i,num_record,num_punti;

printf("Creazione file fgerarch.rtf\n");

num_punti=header_ToRtf.dimaa+header_ToRtf.dimas+header_ToRtf.dimac+header_ToRtf.dimad+header_ToRtf.dimao+
	  header_ToRtf.dimda+header_ToRtf.dimds+header_ToRtf.dimdc+header_ToRtf.dimdd+header_ToRtf.dimdo+
	  header_ToRtf.dimor+header_ToRtf.dimst;
fp=fopen("fgerarch.rtf","w+");
pc=(char *)malloc(num_punti*n_gerarchie);
memset(pc,-1,num_punti*n_gerarchie);
fwrite(pc,1,num_punti*n_gerarchie,fp);
free(pc);

/* Riposiziona il puntatore all'inizio del file */
fseek(fp,0,SEEK_SET);
num_punti=0;

/* Analogici Acquisiti */
tabella=OpenTablePath(path_txt,AA);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella AA\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimaa;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Analogici Calcolati Standard */
tabella=OpenTablePath(path_txt,AS);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella AS\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimas;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Analogici Calcolati Non Standard */
tabella=OpenTablePath(path_txt,AC);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella AC\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimac;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Analogici Di Diagnostica */
tabella=OpenTablePath(path_txt,AD);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella AD\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimad;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Analogici Di Uscita */
tabella=OpenTablePath(path_txt,AO);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella AO\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimao;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Digitali Acquisiti */
tabella=OpenTablePath(path_txt,DA);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella DA\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimda;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Digitali Calcolati Standard */
tabella=OpenTablePath(path_txt,DS);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella DS\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimds;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Digitali Calcolati Non Standard */
tabella=OpenTablePath(path_txt,DC);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella DC\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimdc;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Digitali Di Diagnostica */
tabella=OpenTablePath(path_txt,DD);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella DD\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimdd;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Digitali Di Uscita */
tabella=OpenTablePath(path_txt,DO);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella DO\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimdo;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Organi */
tabella=OpenTablePath(path_txt,OR);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella OR\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimor;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);

/* Stringhe */
tabella=OpenTablePath(path_txt,ST);
if(!tabella)
{
	fprintf(stderr,"CreateFgerarch: apertura tabella ST\n");
	return(0);
}
num_record=NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	if(!GetGerarchia(tabella,i,&gerarchia))
		return 0;
	fwrite(&gerarchia,1,sizeof(gerarchia),fp);
}
CloseTable(tabella);
num_punti+=header_ToRtf.dimst;
fseek(fp,num_punti*n_gerarchie,SEEK_SET);
fclose(fp);
return(1);
}

#define l_szValore	3

int GetGerarchia(ID_TABLE *tabella,int i,S_DBGERA *gerarchia)
{
int j;
VAL_RET valore;
char tok_val[n_gerarchie][l_szValore]; 
char szVal[l_szValore+1];
int iVal;


if(GetVal(tabella,"Gerarchia",i,&valore)!=1)
{
/*
        fprintf(stderr,"GetGerarchia: Errore GetVal\n");
*/
        return(0);
}

if(!*valore.char_val)
{
	memset(gerarchia,-1,sizeof(*gerarchia));
}
else
{
	memcpy(tok_val,valore.char_val,n_gerarchie*l_szValore);
	for(j=0;j<n_gerarchie;j++)
	{
		memcpy(szVal,tok_val[j],l_szValore);
		szVal[l_szValore]='\0';
/*********************************************************************
	Eliminato codice con sscanf che non converte la stringa 
        0-1 come decimale -1	
**********************************************************************/
                if(szVal[l_szValore-2]=='-') /* Se c'e' '-' allora c'e' -1 */
                        iVal=-1;
                else
                        sscanf(szVal,"%d",&iVal); /* converti val da %s a %d */
                *((char *)gerarchia+j)=(char )iVal;

	}
}
return(1);
}
