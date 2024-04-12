/*
   modulo installa_dd.c
   tipo 
   release 1.10
   data 6/14/96
   reserved @(#)installa_dd.c	1.10
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
#include <editdd.h>
#include <g1tipdb.inc>

extern char *path_input;
extern char *path_output;

int installa_dd()
{
char nome_file[FILENAME_MAX+1];
int i;
FILE *fp;
static int prog = 0;
char Sigla[SCD_SIGLA+1];
int pos;
char *app;
char app1[40];


sprintf(nome_file,"%s/%s%s",path_output,"editdd",ESTENSIONE_TABELLA);
printf("Creazione tabella [%s]\n",nome_file);

if((fp=fopen(nome_file,"w"))==NULL)
        return(0);

for(i=0;i<NUM_RECORD_EDITDD;i++)
        {
	fprintf(fp,"%s\n",editdd[i].riga);
        if(i!=0)
                {
                // aggiunge il record alla tabella editnomi
                memcpy(Sigla,&editdd[i].riga[1],SCD_SIGLA);
                app=strstr(Sigla,"\"");
                *app = 0;
                app=strstr(editdd[i].riga,";");
                ++app;
                app=strstr(app,";");
                ++app;
                memcpy(app1,app,20);
                app=strstr(app,";");
                *app=0;

		// Aggiorna tabella editnomi.txt
		installa_nomi(Sigla,"DD",atoi(app1),g1tipdd);
                }
        }
fclose(fp);
return(1);
}
