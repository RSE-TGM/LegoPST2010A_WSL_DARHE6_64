/*
   modulo CreateFtab.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CreateFtab.c	2.4
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
int CreateFtab()
{
FILE *fp;
char record[l_datab+l_codtab+l_htab];
int i;

if((fp=fopen("ftab.rtf","w"))==NULL)
	return(0);
memset(record,0,l_datab+l_codtab+l_htab);
for(i=0;i<n_tabu;i++)
	fwrite(record,1,l_datab+l_codtab+l_htab,fp);
fclose(fp);

return(1);
}
