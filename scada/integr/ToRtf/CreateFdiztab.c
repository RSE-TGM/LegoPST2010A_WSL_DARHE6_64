/*
   modulo CreateFdiztab.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFdiztab.c	2.4
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
#include "g0gerdb.inc"
#include "g3calcdb.inc"
#include "fileop.inc"

extern char path_txt[FILENAME_MAX+1];
int CreateFdiztab()
{
FILE *fp;
S_DIZTAB record;
int i;

if((fp=fopen("fdiztab.rtf","w"))==NULL)
	return(0);
memset(&record,-1,sizeof(S_DIZTAB));
for(i=0;i<n_tabu;i++)
	fwrite(&record,sizeof(S_DIZTAB),1,fp);
fclose(fp);

return(1);
}
