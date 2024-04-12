/*
   modulo CreateFnomi.c
   tipo 
   release 2.8
   data 6/13/96
   reserved @(#)CreateFnomi.c	2.8
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
#include <stdlib.h>

#include "ToRtf.h"
#include "db.h"
#include "tag.h"
#include "dconf.inc"
#include "db.h"
#include "installa.h"
#include "editnomi.h"
#include "g1tipdb.inc"

#define sizefnomi (BLK_OVER+BLK_NORM)*SCD_FATBLK  //557056
extern DB_HEADER header_ToRtf;
extern char path_txt[FILENAME_MAX+1];
extern char path_rtf[FILENAME_MAX+1];

int CreateFnomi()
{
FILE *fp;
char *zero;
int i;
char nome[SCD_SIGLA+1];
short point,ext,posiz;
long blocco;
ID_TABLE *tabella;
VAL_RET valore;
int num_record;
int ret;

printf("Creazione file fnomi.rtf\n");

if(!FillNomi())
{
	fprintf(stderr,"Creazione Nomi.txt fallita\n");
	return(0);
}


// inizializzazione del file fnomi

fp=fopen("fnomi.rtf","w");
/*
printf("CreateFnomi: sizefnomi = %d\n",sizefnomi);
*/
zero=(char *)calloc(sizefnomi, sizeof(char));

if(zero==NULL)
	{
	perror("createFnomi: errore malloc zero");
	printf("\n");
	return(0);
	}
/*
memset(zero,0,sizefnomi);
*/
fwrite(zero,1,sizefnomi,fp);
free(zero);
fclose(fp);

tabella = OpenTablePath(path_txt,NOMI);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateFnomi: apertura tabella\n");
        return(0);
        }
num_record = NumRecord(tabella);

fp=fopen("fnomi.rtf","r+");
for(i=0;i<num_record;i++)
        {
	//  Sigla
	if(GetVal(tabella,"Sigla",i,&valore)!=1)
        	{
        	fprintf(stderr,"CreateFnomi: Errore GetVal Sigla\n");
        	return(0);
        	}
	memset(nome,0,SCD_SIGLA+1);
	strncpy(nome,valore.char_val,SCD_SIGLA);
	//  PointDB
	if(GetVal(tabella,"PointDB",i,&valore)!=1)
        	{
        	fprintf(stderr,"CreateFnomi: Errore GetVal PointDB\n");
        	return(0);
        	}
	point = valore.int_val;
	//  ExtDB
	if(GetVal(tabella,"ExtDB",i,&valore)!=1)
        	{
        	fprintf(stderr,"CreateFnomi: Errore GetVal ExtDB\n");
        	return(0);
        	}
	ext = valore.int_val;
	//printf("[%d] sigla = %s point = %d ext = %d\n",i,nome,point,ext);
	ret=ricerca(nome,&point,&ext,&blocco,&posiz,fp);
	if(ret==0)
 		printf(stderr,"Punto esistente [%s]\n",nome);
	else if(ret==2)
		fprintf(stderr,"Nome da cambiare [%s]\n",nome);
	else
		wrfnomi(nome,point,ext,blocco,posiz,fp);
        }

CloseTable(tabella);
fclose(fp);

return(1);
}


#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore gestione NOMI [%s]\n",stringa); \
	exit(1); \
	}

int crea_fnomi()
{
return(scrivi_header(path_txt,"Nomi",editnomi,NUM_CAMPI_EDITNOMI));
}

int installa_fnomi(char *Sigla,char *Tipo,int PointDB,char ExtDB)
{
RECORD record;
char riga[50];

// inizializza il record
if(init_record(&record,editnomi,NUM_CAMPI_EDITNOMI)!=1)
	errore("init_record");

// inserisce la sigla del punto sullo SCADA
if(ins_campo_char("Sigla",Sigla,&record)!=1)
	errore("Sigla");

// inserisce il Tipo del Punto
if(ins_campo_char("Tipo",Tipo,&record)!=1)
	errore("Tipo");

// inserisce Indice del punto
if(ins_campo_int("PointDB",PointDB,&record)!=1)
        errore("PointDB");

// inserisce Indice del punto
if(ins_campo_int("ExtDB",ExtDB,&record)!=1)
        errore("ExtDB");

// scrittura del record
if(scrivi_record(path_txt,"Nomi",&record)!=1)
        errore("scrivi_record");

return(1);
}

int FillNomi(void)
{
	ID_TABLE *tabella;
	char Sigla[SCD_SIGLA+1];
	char Tipo[3];
	int PointDB;
	char ExtDB;
	int i,num_record;
	VAL_RET valore;

	if(!crea_fnomi())
	{
		perror("");
		return(0);
	}
fprintf(stderr,"dopo di if !crea_fnomi\n");

	/* Aggiunge gli analogici acquisiti */
	tabella=OpenTablePath(path_txt,"PuntAA");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella AA\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
/*
printf("FillNomi: num_record = %d\n",num_record);
*/
	strcpy(Tipo,"AA");
	ExtDB=g1tipaa;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli analogici calcolati standard */
	tabella=OpenTablePath(path_txt,"PuntAS");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella AS\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"AS");
	ExtDB=g1tipas;
fprintf(stderr,"prima di for(i=0;i<num_record;i++): num_recordr=[%d]\n",num_record);
	for(i=0;i<num_record;i++)
	{
//fprintf(stderr,"prima di GetVal: i=[%d]\n",i);
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli analogici calcolati non standard */
	tabella=OpenTablePath(path_txt,"PuntAC");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella AC\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"AC");
	ExtDB=g1tipac;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli analogici di uscita */
	tabella=OpenTablePath(path_txt,"PuntAO");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella AO\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"AO");
	ExtDB=g1tipao;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli analogici di diagnostica */
	tabella=OpenTablePath(path_txt,"PuntAD");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella AD\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"AD");
	ExtDB=g1tipad;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s] (1)\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);

		if(GetVal(tabella,"IndDB",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s] (2)\n",Tipo);
        		return(0);
		}
		PointDB=valore.int_val;

		installa_fnomi(Sigla,Tipo,PointDB,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli digitali acquisiti */
	tabella=OpenTablePath(path_txt,"PuntDA");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella DA\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"DA");
	ExtDB=g1tipda;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge i digitali calcolati standard */
	tabella=OpenTablePath(path_txt,"PuntDS");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella DS\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"DS");
	ExtDB=g1tipds;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge i digitali calcolati non standard */
	tabella=OpenTablePath(path_txt,"PuntDC");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella DC\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"DC");
	ExtDB=g1tipdc;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge i digitali di uscita */
	tabella=OpenTablePath(path_txt,"PuntDO");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella DO\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"DO");
	ExtDB=g1tipdo;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge i digitali di diagnostica */
	tabella=OpenTablePath(path_txt,"PuntDD");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella DD\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"DD");
	ExtDB=g1tipdd;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s] (1)\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);

		if(GetVal(tabella,"IndDB",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s] (2)\n",Tipo);
        		return(0);
		}
		PointDB=valore.int_val;

		installa_fnomi(Sigla,Tipo,PointDB,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge le stringhe */
	tabella=OpenTablePath(path_txt,"PuntST");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella ST\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"ST");
	ExtDB=g1tipst;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);

	/* Aggiunge gli organi */
	tabella=OpenTablePath(path_txt,"PuntOR");
	if(!tabella)
	{
        	fprintf(stderr,"CreateNomi: apertura tabella OR\n");
        	return(0);
	}

	num_record=NumRecord(tabella);
	strcpy(Tipo,"OR");
	ExtDB=g1tipor;
	for(i=0;i<num_record;i++)
	{
		if(GetVal(tabella,"Sigla",i,&valore)!=1)
		{
        		fprintf(stderr,"CreateNomi: Errore GetVal: Tipo [%s]\n",Tipo);
        		return(0);
		}
		strcpy(Sigla,valore.char_val);
		installa_fnomi(Sigla,Tipo,i,ExtDB);
	}
	
	CloseTable(tabella);
fprintf(stderr,"dopo CloseTable Tipo [%s]\n",Tipo);
	return(1);
}

