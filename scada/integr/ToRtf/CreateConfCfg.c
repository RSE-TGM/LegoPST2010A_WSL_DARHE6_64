/*
   modulo CreateConfCfg.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateConfCfg.c	2.4
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

extern char path_txt[FILENAME_MAX+1];

int CreateConfCfg()
{
FILE *fp;
char *path;
printf("Creazione file conf.cfg\n");

if((path=getcwd(NULL,FILENAME_MAX))==NULL)
	return(0);

if((fp=fopen("conf.cfg","w"))==NULL)
	return(0);
fprintf(fp,"; pathname del direttorio in cui si trovano i file operativi\n");
fprintf(fp,"%s\n",path);
fclose(fp);
free(path);

return(1);
}
