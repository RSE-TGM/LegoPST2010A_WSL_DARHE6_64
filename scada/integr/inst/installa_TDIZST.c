/*
   modulo installa_TDIZST.c
   tipo 
   release 1.4
   data 6/13/96
   reserved @(#)installa_TDIZST.c	1.4
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
#include <editTDIZST.h>

extern char *path_input;
extern char *path_output;

int installa_TDIZST()
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;
static int prog = 0;
char Sigla[SCD_SIGLA+1];
int pos;
char *app;
char app1[40];


sprintf(nome_file,"%s/%s%s",path_output,"editTDIZST",ESTENSIONE_TABELLA);
printf("Creazione tabella [%s]\n",nome_file);

if((fp=fopen(nome_file,"w"))==NULL)
        return(0);

for(i=0;i<NUM_RECORD_EDITTDIZST;i++)
        {
	fprintf(fp,"%s\n",editTDIZST[i].riga);
        }
fclose(fp);
return(1);
}
