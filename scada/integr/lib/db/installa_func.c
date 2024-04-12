/**********************************************************************
*
*       C Source:               installa_func.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jul 31 15:30:00 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: installa_func.c-7 %  (%full_filespec: installa_func.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <db.h>
#include <installa.h>
#include <g0gerdb.inc>
#include <sim_param.h>
#include <sim_types.h>
#include <tag.h>
#include <installa_variabili.h>

int indice_fisico_aa = 1;
int indice_fisico_ao = 1;
int indice_fisico_da = 1;
int indice_fisico_do = 1;
int numero_gerarchie = 0;

S_DBGERA gerarchie[MAX_GERARCHIE];
int zone_gerarchie[MAX_GERARCHIE];

char *path_input;
char *path_output;
int usa_informix;
int start_informix;


int scrivi_header(char * path, char * nome,STRUCT_TABLE *tab, int num)
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;

sprintf(nome_file,"%s/%s%s",path,nome,ESTENSIONE_TABELLA);
printf("Creazione tabella [%s]\n",nome_file);
if((fp=fopen(nome_file,"w"))==NULL)
	return(0);
for(i=0;i<num-1;i++)
	fprintf(fp,"\"%s\";",tab[i].nome_campo);
fprintf(fp,"\"%s\"\n",tab[i].nome_campo);
fclose(fp);

return(1);
}

int init_record(RECORD *record,STRUCT_TABLE *tab, int num)
{
int i;

memset(record,0,sizeof(RECORD));

record->tab=tab;

for(i=0;i<MAX_CAMPI_TABELLA;i++)
	record->tipo[i]= -1;

for(i=0;i<num;i++)
	{
	record->tipo[i]=tab[i].tipo;
	switch (tab[i].tipo)
		{
		case TIPO_CHAR:
			strcpy(&record->valore_char[i][0],tab[i].char_default);
				break;
		case TIPO_INT:
			record->valore_int[i]=tab[i].int_default;
				break;
		case TIPO_BOOLEAN:
			record->valore_int[i]=tab[i].int_default;
				break;
		}
	}


return(1);
}

int scrivi_record(char * path,char *nome,RECORD *record)
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;

sprintf(nome_file,"%s/%s%s",path,nome,ESTENSIONE_TABELLA);

if((fp=fopen(nome_file,"a"))==NULL)
	return(0);

for(i=0;i<MAX_CAMPI_TABELLA;i++)
	if(record->tipo[i] != -1)
	{
	if(i!=0)
		fprintf(fp,";");
	switch (record->tipo[i])
		{
		case TIPO_CHAR:
			fprintf(fp,"\"%s\"",record->valore_char[i]);
				break;
		case TIPO_INT:
			if(record->valore_int[i]!=INT_NODEF)
				fprintf(fp,"%d",record->valore_int[i]);
			break;
		case TIPO_BOOLEAN:
			fprintf(fp,"%d",record->valore_int[i]);
				break;
		}
	}
	fprintf(fp,"\n");
fclose(fp);
return(1);
}

int ins_campo_char(char *nome_campo,char * valore,RECORD *record)
{
STRUCT_TABLE *tab = record->tab;
int i;

for(i=0;i<MAX_CAMPI_TABELLA;i++)
	{
	if(record->tipo[i] == -1)
		return(0);
	if(strcmp(tab[i].nome_campo,nome_campo)==0)
		break;
	}
if(i==MAX_CAMPI_TABELLA)
	return(0);
strcpy(&record->valore_char[i][0],valore);

return(1);


}

int ins_campo_int(char *nome_campo,int valore,RECORD *record)
{
STRUCT_TABLE *tab = record->tab;
int i;

for(i=0;i<MAX_CAMPI_TABELLA;i++)
	{
	if(record->tipo[i] == -1)
		return(0);
	if(strcmp(tab[i].nome_campo,nome_campo)==0)
		break;
	}
if(i==MAX_CAMPI_TABELLA)
	return(0);
record->valore_int[i]=valore;

return(1);
}

int gest_argv(int argc, char ** argv)
{
int i;
if(argc <2)
	return;
for(i=1;i<argc;i++)
	{
	if(strcmp(argv[i],"-indaa")==0)
		{
		i++;
		indice_fisico_aa = atoi(argv[i]);
		if(indice_fisico_aa <1)
			indice_fisico_aa = 1;
		}
	if(strcmp(argv[i],"-indao")==0)
		{
		i++;
		indice_fisico_ao = atoi(argv[i]);
		if(indice_fisico_ao <1)
			indice_fisico_ao = 1;
		}
	if(strcmp(argv[i],"-indda")==0)
		{
		i++;
		indice_fisico_da = atoi(argv[i]);
		if(indice_fisico_da <1)
			indice_fisico_aa = 1;
		}
	if(strcmp(argv[i],"-inddo")==0)
		{
		i++;
		indice_fisico_do = atoi(argv[i]);
		if(indice_fisico_do <1)
			indice_fisico_ao = 1;
		}
	if(strncmp(argv[i],"-noinformix",7)==0)
		{
		usa_informix = 0;
		}
	if(strncmp(argv[i],"-startinformix",9)==0)
		{
		start_informix = 1;
		}
	if(strcmp(argv[i],"-help")==0)
		{
		printf("\n");
		printf("-help         (questo menu')\n");
		printf("-indaa <num>  (indice fisico di partenza AA)\n");
		printf("-indao <num>  (indice fisico di partenza AO)\n");
		printf("-indda <num>  (indice fisico di partenza DA)\n");
		printf("-inddo <num>  (indice fisico di partenza DO)\n");
		printf("-noinfor      (non accede a Informix)\n");
		exit(0);
		}
	}
}

int CostruisciGer(char *cger,int g0,int g1,int g2,int g3,int g4,int g5)
{
int i;
sprintf(cger,"%3d%3d%3d%3d%3d%3d",g0,g1,g2,g3,g4,g5);
for(i=0;i<=strlen(cger);i++)
        if(cger[i]==' ')
                cger[i]='0';
//printf("cger = [%s]\n",cger);
return(1);
}

int CostruisciUniMis(char *nome,char *uni)
{
strcpy(uni,"Kg/s");
}

int IsDig(char *nome)
{
if(nome[0]=='J')
	return(1);

return(0);
}

int IsAna(char *nome)
{
return(!IsDig(nome));
}

int InitGerarchie()
{
int i,j;

//printf("InitGerarchie\n");
for(i=0;i<MAX_GERARCHIE;i++)
	for(j=0;j<n_gerarchie;j++)
		gerarchie[i].chLivello[j]= -1;
for(i=0;i<MAX_GERARCHIE;i++)
	zone_gerarchie[i] = -1;
}

int PrintGerarchie()
{
int i,j;

printf("Elenco gerarchie configurate\n");
for(i=0;i<numero_gerarchie;i++)
	{
	printf("gerarchia [%d] = ",i);
	for(j=0;j<n_gerarchie;j++)
	   printf(" %d",gerarchie[i].chLivello[j]);
	printf("\n");
	}
}
/*
Funzione per aggiungere una gerarchia (cioe' un nodo) nella lista
delle gerarchie.Per ogni gerarchia si verifica se esiste gia' o se occorre
aggiungerla.Per ogni gerarchia vengono aggiunte ricorsivamente le gerarchie
dei padri.
Parametri : zona impianto
	    unsigned char ger0...n gerarchie
Val restituito: 1 se Ok
*/
int AddGerarchia(int zona,unsigned char ger0,unsigned char ger1,unsigned char ger2,unsigned char ger3,unsigned char ger4,unsigned char ger5)
{
int i,j;
int uguale;
// verifica se la gerarchia e' presente
for(i=0;i<numero_gerarchie;i++)
	if( (gerarchie[i].chLivello[0] == ger0)&&
		(gerarchie[i].chLivello[1] == ger1)&&
		(gerarchie[i].chLivello[2] == ger2)&&
		(gerarchie[i].chLivello[3] == ger3)&&
		(gerarchie[i].chLivello[4] == ger4)&&
		(gerarchie[i].chLivello[5] == ger5)/* &&
		(zone_gerarchie[i] == zona)*/)
			return(1);
//printf("Gerarchia [%d] = %d %d %d %d %d %d zona = %d\n",i,
//		ger0,ger1,ger2,ger3,ger4,ger5,zona);
// inserisce la gerarchia
gerarchie[numero_gerarchie].chLivello[0] = ger0;
gerarchie[numero_gerarchie].chLivello[1] = ger1;
gerarchie[numero_gerarchie].chLivello[2] = ger2;
gerarchie[numero_gerarchie].chLivello[3] = ger3;
gerarchie[numero_gerarchie].chLivello[4] = ger4;
gerarchie[numero_gerarchie].chLivello[5] = ger5;
zone_gerarchie[numero_gerarchie] = zona;
numero_gerarchie ++;
if(ger5!= 255)
 AddGerarchia(zona,ger0,ger1,ger2,ger3,ger4,255);
else
  if(ger4!= 255)
    AddGerarchia(zona,ger0,ger1,ger2,ger3,255,255);
  else
  if(ger3!= 255)
    AddGerarchia(zona,ger0,ger1,ger2,255,255,255);
  else
     if(ger2!= 255)
       AddGerarchia(zona,ger0,ger1,255,255,255,255);
  else
     if(ger1!= 255)
       AddGerarchia(zona,ger0,255,255,255,255,255);

return(1);
}

int num_codici_allaras;
STRUCT_ALLARAS *allaras;

int CreateAllarAs()
{
ID_TABLE *tabella;
VAL_RET valore;
int num_record;
int i;

printf("CreateAllarAs\n");

tabella = OpenTablePath(path_input,ALARMTYPE_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"CreateAllarAs: apertura tabella [%s]\n",ALARMTYPE_TABLE
);
        return(0);
        }
num_record = NumRecord(tabella);
num_codici_allaras = num_record *2;
if(num_codici_allaras==0)
	return(1);
allaras=(STRUCT_ALLARAS *)malloc(num_codici_allaras*sizeof(STRUCT_ALLARAS));
for(i=0;i<num_record;i++)
{
//  ALTYPE_SIGNAL
        if(GetVal(tabella,"ALTYPE_SIGNAL",i,&valore)!=1)
                {
                fprintf(stderr,"CreateAllarAs: Errore GetVal ALTYPE_SIGNAL\n");
                return(0);
                }
// CodiceAll
allaras[i*2].CodiceAll=malloc(SCD_SIGLA+1);
allaras[i*2+1].CodiceAll=malloc(SCD_SIGLA+1);
sprintf(allaras[i*2].CodiceAll,"PEN%s%s",TAG_SIGNAL,valore.char_val);
sprintf(allaras[i*2+1].CodiceAll,"ARC%s%s",TAG_SIGNAL,valore.char_val);

// DescrAll
allaras[i*2].DescrAll=malloc(SCD_DESCRIZIONE+1);
allaras[i*2+1].DescrAll=malloc(SCD_DESCRIZIONE+1);
sprintf(allaras[i*2].DescrAll,"N. of pending type %s alarm under",
			valore.char_val);
sprintf(allaras[i*2+1].DescrAll,"N. of arch. type %s alarm under",
			valore.char_val);
// TipoCalc
allaras[i*2].TipoCalc=15;
allaras[i*2+1].TipoCalc=16;
// PeriodoCalc
allaras[i*2].PeriodoCalc=1;
allaras[i*2+1].PeriodoCalc=1;
}

return(1);
}
