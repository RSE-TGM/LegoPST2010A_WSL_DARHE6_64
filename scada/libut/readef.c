/**********************************************************************
*
*       C Source:               readef.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 11:59:35 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: readef.c-5 %  (%full_filespec: readef.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
 *    READCONF.C: legge il file di configurazione variabili di environment.
 *                Se il file non esiste lo crea settando al suo interno
 *                i valori di default standart per EEXE, ECOL, EEDT, ERTF
 */

#include <osf1.h>
#include <stdio.h>

#include "dconf.inc"

#if !defined OSF1 && !defined LINUX
readef()
 {
 FILE *fp;
 fp=fopen("conf.cfg","r+");
 if(fp==NULL)
   {
			printf("CFG NON ESIS.");
			exit(0);
   }
 else
   {
    	fread(conf,rec_conf,1,fp);
   }
fclose(fp);
}
#else
#include <string.h>
#define lcBuffer 256
readef()
{
FILE *fp;
char cBuffer[lcBuffer];
char *pc;

fp=fopen("conf.cfg","r+");

if(fp)
{
	/* Scandisce tutto il file di configurazione nei limiti delle 
	   capacita' del buffer                                       */
	for(;fgets(cBuffer,lcBuffer,fp);)
	{
		/* Se e' un commento considera la linea successiva */
		if(IsComment(cBuffer))
			continue;
		else
			break;
	}

	/* Toglie eventuale new line */
	pc=strchr(cBuffer,'\n');
	if(pc)
		*pc='\0';

	strcpy(conf[RTF],cBuffer);
	printf("[readef.c] [%s]\n",conf[RTF]);
}
else
{
	perror("conf.cfg");
	exit(0);
}

fclose(fp);
}
#endif
