/*
   modulo installa_ad.c
   tipo 
   release 1.9
   data 6/14/96
   reserved @(#)installa_ad.c	1.9
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <db.h>
#include <installa.h>
#include <tag.h>
#include <editad.h>
#include <g1tipdb.inc>

extern char *path_input;
extern char *path_output;

int installa_ad()
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;
static int prog = 0;
char Sigla[SCD_SIGLA+1];
int pos;
char *app;
char app1[40];



sprintf(nome_file,"%s/%s%s",path_output,"editad",ESTENSIONE_TABELLA);
printf("Creazione tabella [%s]\n",nome_file);

if((fp=fopen(nome_file,"w"))==NULL)
	return(0);
for(i=0;i<NUM_RECORD_EDITAD;i++)
	{
	fprintf(fp,"%s\n",editad[i].riga);
	if(i!=0)
		{
		// aggiunge il record alla tabella editnomi
		memcpy(Sigla,&editad[i].riga[1],SCD_SIGLA);
		app=strstr(Sigla,"\"");
		*app = 0;
		app=strstr(editad[i].riga,";");
		++app;
		app=strstr(app,";");
		++app;
		memcpy(app1,app,20);
		app=strstr(app,";");
		*app=0;
		// Aggiorna tabella editnomi.txt
		installa_nomi(Sigla,"AD",atoi(app1),g1tipaa);
		}
	}
fclose(fp);
return(1);
}
