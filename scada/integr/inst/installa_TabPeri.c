/*
   modulo installa_TabPeri.c
   tipo 
   release 1.5
   data 6/13/96
   reserved @(#)installa_TabPeri.c	1.5
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
#include <tag.h>
#include <installa.h>
#include <editTabPeri.h>

extern char *path_input;
extern char *path_output;

int installa_TabPeri()
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;
static int prog = 0;
char Sigla[SCD_SIGLA+1];
int pos;
char *app;
char app1[40];


sprintf(nome_file,"%s/%s%s",path_output,"editTabPeri",ESTENSIONE_TABELLA);
printf("Creazione tabella [%s]\n",nome_file);

if((fp=fopen(nome_file,"w"))==NULL)
        return(0);

for(i=0;i<NUM_RECORD_EDITTABPERI;i++)
        {
	fprintf(fp,"%s\n",editTabPeri[i].riga);
        }
fclose(fp);
return(1);
}
