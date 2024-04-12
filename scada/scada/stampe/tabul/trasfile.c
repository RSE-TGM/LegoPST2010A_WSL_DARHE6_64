/**********************************************************************
*
*       C Source:               trasfile.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 16:18:26 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: trasfile.c-3.1.1 %  (%full_filespec: trasfile.c-3.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* ->TRASFILE.C
 *      Trasferisce un file generico su dischetto
 */
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif

#include "switch.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "diagnodi.inc"
#include "dconf.inc"

#if !defined  OSF1 && !defined LINUX
trasfile(filename,buf)
char *filename ;
char *buf;
{
#define l_buf 512
long offset;
int fh1,fh2;
short numbyte;
char nomecopia[FILENAME_MAX+1];      // A:nome_del file 
char fnome[FILENAME_MAX+1];

if (SYS_DUALE && (!sys_master)) 
      return(0);			  // se duale e slave ritorno

strcpy(nomecopia,"A:/");
strcat(nomecopia,filename);

strcpy(fnome,conf[RTF]);
strcat(fnome,"/");
strcat(fnome,filename);

/*
	RESETTA il digitale di errore su disco
*/

bitset(&dbdd[diskerr],g2di_sl,0);

fh1=open(fnome,O_BINARY|O_RDWR);
if(fh1==-1)   return(1); 
fh2=open(nomecopia,O_RDWR|O_BINARY|O_CREAT,S_IREAD|S_IWRITE);
if(fh2==-1)   { close(fh1); return(1);} 
/*
	ciclo di lettura / scrittura 
*/
offset=0L;
while(numbyte=rbyte(fh1,buf,offset,l_buf))
	{
	if(wbyte(fh2,buf,offset,numbyte)!=numbyte)
		{
		close(fh1); close(fh2);	 // se errore in scrittura
		bitset(&dbdd[diskerr],g2di_sl,1);
		return(1);
		}																									  
	offset+=numbyte;
	wai(2);
	}
close(fh1);
close(fh2);
return(0);
}
#else
trasfile(filename,buf)
char *filename ;
char *buf;
{
int i;
char nomedir[FILENAME_MAX+1];
char fnome[FILENAME_MAX+1];
char command[(FILENAME_MAX+1)*2+10];

/* Se duale e slave ritorno */
if (SYS_DUALE && (!sys_master)) 
      return(0);	

/* Converte il nome in minuscolo */
for(i=0;filename[i];i++)
	filename[i]=tolower(filename[i]);

/* Compone il nome del file da copiare */
strcpy(fnome,conf[RTF]);
strcat(fnome,"/");
strcat(fnome,filename);
if(!strcmp(filename,""))
{
	printf("[trasfile.c] nome file nullo\n");
	return 1;
}

if(access(fnome,F_OK))
{
	printf("[trasfile.c] impossibile trovare il file [%s]\n",fnome);
	return 1;
}

/* Pone a zero il digitale di errore su disco */
bitset(&dbdd[diskerr],g2di_sl,0);

/* Crea il sottodir. TAR */
strcpy(nomedir,conf[RTF]);
strcat(nomedir,"/TAR");
mkdir(nomedir,S_IRWXU|S_IRGRP|S_IROTH);

/* Compone la riga di comando e la esegue */
sprintf(command,"tar cf %s/%s %s",nomedir,filename,fnome);
system(command);
return(0);
}
#endif
