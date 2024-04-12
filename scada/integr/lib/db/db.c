/**********************************************************************
*
*       C Source:               db.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon May 31 15:09:19 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: db.c-9 %  (%full_filespec: db.c-9:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <db.h>

/*
ID_TABLE * OpenTable(char *);
ID_TABLE * OpenTablePath(char *,char *);
int CloseTable(ID_TABLE *);
int ConnectDb();
int DisconnectDb();
int GetNumRecord(ID_TABLE *);
char * GetCampi(ID_TABLE *);
int GetVal(ID_TABLE *, char *, int, VAL_RET*);
*/

static int legge_riga(ID_TABLE *, char *);
static int legge_riga_num(ID_TABLE *, char *,int);
static int Rewind(ID_TABLE *);

#if defined TEST_QQ
main()
{
ID_TABLE *tabella;
int i;
VAL_RET valore;

printf("TEST DB\n");
if(!ConnectDb())
	printf("Errore connessione database\n");
tabella = OpenTable("TDPUNaa");
if(tabella == NULL)
	printf("Errore apertura tabella\n");
printf("Numero di campi tabella %d\n",NumCampi(tabella));
printf("Numero di record tabella %d\n",NumRecord(tabella));
//for(i=0;i<NumCampi(tabella);i++)
	//printf("Campo [%d] = [%s]\n",i,NomeCampo(tabella,i));
if(GetVal(tabella,"Trattamento",2,&valore)!=1)
	printf("Errore GetVal\n");
printf("valore int = [%d]\n",valore.int_val);
for(i=0;i<NumRecord(tabella);i++)
	{
	GetVal(tabella,"Sigla",i,&valore);
	printf("Sigla[%d]=[%s]\n",i,valore.char_val);
	}
// chiusura tabella
if(!CloseTable(tabella))
	printf("Errore chiusura tabella\n");
if(!DisconnectDb())
	printf("Errore sconnessione database\n");
}
#endif
ID_TABLE * OpenTablePath(char *path, char *nome_tabella)
{
char nome[255];

if((path == NULL) || (nome_tabella == NULL))
	return(NULL);

sprintf(nome,"%s/%s",path,nome_tabella);
return(OpenTable(nome));
}

ID_TABLE * OpenTable(char *nome_tabella)
{
char nome[FILENAME_MAX+1];
ID_TABLE *ret;
struct stat *buf_var;
int i;
size_t size_p_rec;

if(nome_tabella==NULL)
	return(NULL);
#if defined ASCII_DB

sprintf(nome,"%s%s",nome_tabella,ESTENSIONE_TABELLA);

ret = (ID_TABLE *)calloc(1, sizeof(ID_TABLE));
if(ret==NULL)
	{
	perror("OpenTable: errore calloc di ID_TABLE");
	printf("\n");
	return(NULL);
	}
	
ret->fp = fopen(nome,"r");

if(ret->fp==NULL)
	{
	free(ret);
	return(NULL);
	}
/*
	leggo le dimensioni del file
*/

buf_var = (struct stat *)malloc(sizeof (struct stat));
if(buf_var==NULL)
	{
	fprintf(stderr,"OpenTable: errore malloc di buf_var!!!\n");
	free(ret);
	return(NULL);
	}
stat (nome, buf_var);
ret->size = (int) (buf_var -> st_size);
/*
 printf("DEBUG:ret->size=%d per tabella =%s \n",ret->size,nome);
*/
free (buf_var);

//printf("dimensioni del file = %d\n",ret->size);

/*
	leggo il file
*/
if(ret->size<MAX_SIZE_MEM)
	{
/*
printf("DEBUG: tabella =%s come MEM_TABLE !!! \n",nome);
*/
	ret->table_start=malloc(ret->size+1);
        if(ret->table_start==NULL)
		{
		fprintf(stderr,"OpenTable: errore malloc di table_start!!!\n");
		free(ret);
		return(NULL);
		}
	fread(ret->table_start,1,ret->size,ret->fp);
	ret->table=ret->table_start;
	ret->tipo_table = MEM_TABLE;
	}
else
	ret->tipo_table = FILE_TABLE;

ret->num_campi = -1;
ret->num_record = GetNumRecord(ret);
ret->record_save = -1;

// Alloca i campi point_record
size_p_rec = ret->num_record*sizeof(char *);
if(ret->num_record > 0) 
	{
ret->point_record=(char **)malloc(size_p_rec);
if(ret->point_record==NULL)
	{
        fprintf(stderr,"OpenTable: errore malloc di point_record!!!\n");
	free(ret);
	return(NULL);
	}
for(i=0;i<ret->num_record;i++)
	ret->point_record[i] = NULL;
GetCampi(ret);
}
return(ret);
#endif
return(NULL);
}

int CloseTable(ID_TABLE *table)
{

if(table==NULL)
	return(0);

#if defined ASCII_DB
if(table->fp ==NULL)
	return(0);
fclose(table->fp);
if(table->tipo_table == MEM_TABLE)
	{
        if(table->table_start!=NULL)
	   free(table->table_start);
	}

        if(table->point_record!=NULL)
	   free(table->point_record);

        if(table!=NULL)
           free(table);

return(1);
#endif
return(0);
}

int ConnectDb()
{
#if defined ASCII_DB
return(1);
#endif
return(0);
}

int DisconnectDb()
{
#if defined ASCII_DB
return(1);
#endif
return(0);
}

int GetNumRecord(ID_TABLE *tabella)
{
char riga[MAXRIGA];
int ret = 0;
if(tabella == NULL)
	return(-1);
#if defined ASCII_DB
Rewind(tabella);
while(legge_riga(tabella,riga)>0)
{
	++ret;
}
return(ret-1);  // -1 per eliminare l'header
#endif

return(-1);
}

int Rewind(ID_TABLE *tabella)
{
FILE *fp = tabella->fp;


if(tabella->tipo_table == MEM_TABLE)
	tabella->table=tabella->table_start;
else
	rewind(fp);
}


int legge_riga(ID_TABLE *tabella,char *riga)
{
char *ret_fg;
int  ret;
FILE *fp = tabella->fp;

memset(riga,0,MAXRIGA);
if(tabella->tipo_table == FILE_TABLE)
	{
	if(fgets(riga,MAXRIGA,fp)==NULL)
		return(0);
        ret=1; 
	if(strlen(riga))
		riga[strlen(riga)-1]=0;
	}
else
	{
	ret = 0;
	tabella->table_old = tabella->table;
	while(1)	
		{
		if(*tabella->table=='\n' || tabella->table-tabella->table_start>=tabella->size)
			{
			++tabella->table;
			break;
			}

		riga[ret]= *tabella->table;
		++ret;
		++tabella->table;
		}
	riga[ret]=0;
/*
printf("LEGGE_RIGA uscito: table-table_start = %d\n",(tabella->table-tabella->table_start));
printf("LEGGE_RIGA uscito: table->size = %d\n",tabella->size);
*/
	}
return(ret);

/*
int k;
char c;

for (k=0; k<MAXRIGA; k++)
   riga[k] = (char)NULL;

for (k=0; (c = fgetc( fp)) != '\n'; k++) {
  if (c == EOF) {
   return( -1);
  }
  if (k == MAXRIGA-1) {
   fprintf(stderr, "ATTENZIONE riga %d supera %d caratteri.\n", riga, 
	MAXRIGA);
   return( -1);
  }
  riga[k]=c;
 }
 riga[k]=(char)NULL;
return(k);
*/
}

char * GetCampi(ID_TABLE *tabella)
{
char riga[MAXRIGA];
char *inizio;
char *app, *app1;
int campo = 0;

if(tabella == NULL)
	return(NULL);
#if defined ASCII_DB
Rewind(tabella);
if(legge_riga(tabella,riga)<0)
	return(NULL);

inizio = riga;
while(inizio!=NULL)
	{
	app = strstr(inizio,"\"");
	if(app ==NULL)
		break;
	inizio = app +1;
	app = strstr(inizio,"\"");
        if(app ==NULL)
                break;
	*app = 0;
	strcpy(tabella->campi[campo],inizio);
	//printf("campo = %s\n",tabella->campi[campo]);
	++campo;
	inizio = app +1;
	}
tabella->num_campi = campo;
return(riga);
#endif
return(NULL);
}

int GetVal(ID_TABLE * tabella, char *nome_campo, int record, VAL_RET * valore)
{
int ret = 0;
int pos_campo;
int i;
char riga[MAXRIGA];
char *app, *campo;

/*
	azzara il valore di ritorno
*/
memset(valore,0,sizeof(VAL_RET));

#if defined ASCII_DB
/*
	verifico il numero del record
*/
if((record<0) || (record >=NumRecord(tabella)))
	return(ret);
/*
	verifico il nome del campo
*/
for(pos_campo=0;pos_campo<NumCampi(tabella);pos_campo++)
	if(strcasecmp(nome_campo,NomeCampo(tabella,pos_campo))==0)
		break;

if(pos_campo == NumCampi(tabella))
{
printf("campo [%s]\n",nome_campo);
	return(ret);
}
if(record == tabella->record_save)
	{
	strcpy(riga,tabella->riga_save);
	}
else
	{
	legge_riga_num(tabella, riga, record);
/*
	Rewind(tabella);
	legge_riga(tabella,riga);
	for(i=0;i<=record;i++)
		legge_riga(tabella,riga);
*/
	tabella->record_save = record;
	strcpy(tabella->riga_save,riga);
	}
app = riga;
for(i=0;i<pos_campo;i++)
	{
	app=strstr(app,";");
	app++;
	}

campo = app;

if(pos_campo!=(NumCampi(tabella)-1))
	{
	app=strstr(app,";");
	*app = 0;
	}
if(strlen(campo))
	{

		valore->float_val=atof(campo);
		valore->int_val=atoi(campo);
	if(campo[0]=='\"')  // stringa
		{
		++campo;
		app=strstr(campo,"\"");
		*app=0;
		strcpy(valore->char_val,campo);
		}
#if defined OLD
	if(campo[0]=='\"')  // stringa
		{
		++campo;
		app=strstr(campo,"\"");
		*app=0;
		strcpy(valore->char_val,campo);
		}
	else if(strstr(campo,".")!=NULL)  // float
		{
		valore->float_val=atof(campo);
		}
	else  // int
		{
		valore->int_val=atoi(campo);
		}
#endif
	}

ret = 1;
#endif
return(ret);
}

static int legge_riga_num(ID_TABLE *tabella, char *riga,int record)
{
int i;

	if((tabella->tipo_table != FILE_TABLE)&&
		(tabella->point_record[record]!=NULL))
	{
	tabella->table = tabella->point_record[record];
	legge_riga(tabella,riga);
	return(1);
	}
        if((tabella->tipo_table != FILE_TABLE))
        {
	Rewind(tabella);
	legge_riga(tabella,riga);
           for(i=0;i<tabella->num_record;i++)
           {
              legge_riga(tabella,riga);
              tabella->point_record[i]=tabella->table_old;
           }
	   tabella->table = tabella->point_record[record];
        }
	Rewind(tabella);
	legge_riga(tabella,riga);
	for(i=0;i<=record;i++)
 	   legge_riga(tabella,riga);
        if(tabella->tipo_table != FILE_TABLE)
        {
          tabella->point_record[record]=tabella->table_old;
        }
        return(1);
}

