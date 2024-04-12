/**********************************************************************
*
*       C Source:               stdisk.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:54:11 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: stdisk.c-3 %  (%full_filespec: stdisk.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	la routine stdisk scrive su disco le stringhe allarmi
	i  file sono chiamati ALLAR1 fino ad ALLAR8, ogni file
	contine fino a n_fial stringhe di allarme, riempito 
   l'ultimo file si ricicla sul primo
*/
#include <dos.h>
#include <stdio.h>

#include "print.inc"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "fileop_names.h"

stdisk(stringa,lung,flag)
char *stringa;
short flag, lung;
{
char fnome[FILENAME_MAX+1];
short ier;

if(byte_allfile == 0L)
   {
	n_allfile=dbadv[db_fileal];
	n_allfile++;
	if(n_allfile>max_n_allfile) n_allfile=1;
/*
	aggiorno nel data base di diagnostica il n. del file in uso
	e l'ora e il giorno in cui e' stato aperto
	poiche' il file e' in uso resetto il bit FZ di copiato
*/
	dbadv[db_fileal]=n_allfile;
	dbadv[db_falco1+n_allfile-1]=dbadv[db_giorno]+dbadv[db_ora]*100;
	bitset(&dbadf[db_falco1+n_allfile-1],g2an_fz,0);
	
	strcpy(fnome,conf[RTF]);
	strcat(fnome,FILBG0);
	fnome[strlen(fnome)-1]=fnome[strlen(fnome)-1]+n_allfile;
	strcat(fnome,RTFEXT);
	fpstall=fopen(fnome,"wb");
	if(fpstall==NULL) 
      { perror("errore stdisk "); 
      return; 
      }
/*
	verifico che il file successivo sia gia' stato copiato su dischetto
*/
	testlbg(n_allfile);
   }
if(wbyte(fileno(fpstall),(short*)stringa,byte_allfile,lung)==-1) 
   printf(" err wbyte %d",ier);
byte_allfile=byte_allfile+lung;
if(byte_allfile > max_byte_allfile && (flag==si_fine))   
   {
   byte_allfile=0L;  
   fclose(fpstall); 
   }
}



