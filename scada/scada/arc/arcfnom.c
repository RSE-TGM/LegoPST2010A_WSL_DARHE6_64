/**********************************************************************
*
*       C Source:               arcfnom.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Aug  4 12:17:14 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcfnom.c-4.1.1 %  (%full_filespec: arcfnom.c-4.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcfnom.c

   La funzione arcfnom gestisce le operazione di I/O (read e write)
   della tabella con i nomi dei file che costituiscono un singolo
   archivio.
   In caso di lettura inserisce nella tabella arcdes la dimensione
   del file attualmente in uso
   In caso di cancellazione, viene letto il record relativo all'
   archivio indicato e vengono cancellati i nomi dei file inseriti.

   Parametri

   narc  short    numero dell'archivio
   flag  short    =0 leggere
                  =1 scrivere
                  =3 cancellare

   12 Marzo 1992  Rel. 1.0    Fc
   06 Aprile 1992 Rel. 1.1    Fc
   
   Inserita la funzione di cancellazione
*/
#include <osf1.h>
#include <io.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#ifndef O_BINARY
#define O_BINARY 0x10000
#endif

#include "arc.inc"
#include "dconf.inc"
#include "g2comdb.inc"

arcfnom(narc,flag)
short narc;
char flag;
{
char fnome[FILENAME_MAX+1];
short canale;
long offset;
short ier;
ARCNOME *bufnomi;
ARCNOME *OrBufnomi;              // indirizzo iniziale allocazione
short i, lung, n_file;
/*
   costruisco il nome del file e lo apro
*/
strcpy(fnome,arcpath);
#if defined OSF1 || defined LINUX
strcat(fnome,ARCFILE);
#else
strcat(fnome,"/ARCFILE.RTF");
#endif
canale=open(fnome,O_BINARY | O_CREAT | O_RDWR, 0666);
if(canale==-1) 
	{
	pscserr(ERR_IO,TASK_ARC,ROU_FNOM0,0,SYS_HALT);
	}
offset=(long)narc*(long)sizeof(ARCNOME)*(long)n_farc;

switch (flag)
{
case 1:        // scrittura
   ier=wbyte(canale,arcnome[narc].arc,offset,sizeof(ARCNOME)*arcdes[narc].hea.n_file);
   break;
case 0:        // lettura
   ier=rbyte(canale,arcnome[narc].arc,offset,sizeof(ARCNOME)*arcdes[narc].hea.n_file);
/*
   ricavo la dimensione del file e la inserisco nella tabella arcdes.offset
*/
    close(canale);
    strcpy(fnome,arcpath);
    strcat(fnome,"/");
    strcat(fnome,arcnome[narc].arc+arcnome[narc].use);
    canale=open(fnome,O_BINARY | O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
    if(canale==-1) pscserr(ERR_IO,TASK_ARC,ROU_FNOM1,0,SYS_CONT);
    else arcdes[narc].offset=filelength(canale);
    break;
case 3:     // cancellazione
   n_file=32;         // n. max. file da leggere
   bufnomi=calloc(n_file, l_arcnome);           // alloco memoria
   OrBufnomi=bufnomi;
   if(bufnomi==NULL) pscserr(ERR_MEM,TASK_ARC,ROU_FNOM,0,SYS_HALT);
   ier=rbyte(canale,bufnomi,offset,sizeof(ARCNOME)*n_file);
   strcpy(fnome,arcpath);
   strcat(fnome,"/");
   lung=strlen(fnome);
   for(i=0;i<n_file;i++,bufnomi++)
   {
      if(strlen(bufnomi) && (strlen(bufnomi)<sizeof(fnome)-lung))      // nome definito accettabile ?
      {
         strcpy(&fnome[lung],bufnomi);
         unlink(fnome);
#if defined (DEBUG)
   printf("canc: %s ",fnome);
#endif
      }
   }
   memset(OrBufnomi,0,n_file*l_arcnome);           // inizializzo o zero
   ier=wbyte(canale,OrBufnomi,offset,sizeof(ARCNOME)*n_file);
//   free(bufnomi);                               // libero memoria
   break;
}
close(canale);
}


