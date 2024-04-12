/**********************************************************************
*
*       C Source:               arcflop.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 16:22:22 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcflop.c-4 %  (%full_filespec: arcflop.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcflop.c

   La funzione gestisce il messaggio S_FLOPPY per la copia di un
   file su floppy.
   Se il valore di dim e di blocco sono = -1 si vuole sapere la di-
   mensione del file. Il valore deve essere scritto nell'analogico
   arc-copy.
   Se il valore del campo dim == -1 si vuol trasferire il file in
   modo completo sul dischetto.
   Se il valore di dim e' diverso da -1 va trasferito solo il blocco
   indicato dal campo blocco dimensionato dim kbytes.
   Al termine della copia nell'analogico arccorr va inserito il n. di
   blocco copiato.
   
   Parametri

   mess  S_FLOPPY*   puntatore al messaggio
   bufio char*       indirizzo buffer di appoggio per l'I/O

   Ritorno

   nessuno

   2 Aprile 1992  Rel. 1.0 Fc
*/

#include <osf1.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include <string.h>

#include "switch.inc"      // contiene i parametri di attivazione

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "arc.inc"
#include "dconf.inc"
#include "arcvis.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"

#define  bytes_IO    2048      // n. bytes trasferiti per ciclo

arcflop(mess,bufio)
S_FLOPPY *mess;
char *bufio;
{
short caninp, canout;
char fsorg[FILENAME_MAX+1], fdest[FILENAME_MAX+1];
char *str;
long offsetr, offsetw;
long numbyte;          // numero bytes trasferiti
long numrich;          // numero bytes richiesti
short lung;
short lungpath;
short nbytes;

if (SYS_DUALE && (!sys_master)) 
      return(0);			  // se duale e slave ritorno

if(mess->archivio!=-1) strcpy(fsorg,arcpath);
else strcpy(fsorg,conf[RTF]);
lungpath=strlen(fsorg);

strcat(fsorg,"\\");
strcpy(fdest,"A:");
/*
   copio il nome del file da trasferire fino all'estensione
   punto compreso
*/
str=memccpy(&fsorg[strlen(fsorg)],mess->nome,'.',l_filext);
*str=0;
strcat(fdest,&fsorg[lungpath]);
/*
   aggiungo l'estensione se il blocco ha valore -1
   altrimenti il numero del blocco su tre cifre forma l'estensione
*/
strncat(fsorg,&mess->nome[strlen(fsorg)-lungpath-1],3);
lung=strlen(fdest);
if(mess->blocco == -1)
   strncat(fdest,&mess->nome[lung-lungpath-1],3);
else
{
   decnum(&fdest[lung],3,-2,mess->blocco,0.);
   fdest[lung+3]=0;                          // fine stringa
}

/*
   apro i canali per il trasferimento e resetto il digitale 
   per errore su disco
*/
bitset(&dbdd[diskerr],g2di_sl,0);
/* 
   se si tratta di file di archivio ed il file in uso coincide con
   quello da copiare impedisco la copia
*/
if(mess->archivio != -1) 
{
   if(arcnome[mess->archivio-1].use==mess->n_file)
   {
      dbadv[arccopy]=-999999;
      goto FINE_COPIA;
   }
}
/*
   lock file in uso
*/
if(mess->archivio != -1) arcdes[mess->archivio-1].canc=mess->n_file;

caninp=open(fsorg,O_BINARY|O_RDONLY);
if(mess->dim == -1)                       // richiesta solo la dimensione
{
   if(caninp==-1) dbadv[arccopy]=-999999;
   else  dbadv[arccopy]=lseek(caninp,0L,SEEK_END);
   if(dbadv[arccopy]==0.0) dbadv[arccopy]=-999999;
   if(caninp!=-1) close(caninp);
   goto FINE_COPIA;
}
if(caninp==-1)   goto FINE_COPIA; 
canout=open(fdest,O_RDWR|O_BINARY|O_CREAT,S_IREAD|S_IWRITE);
if(canout==-1)   { close(caninp); goto FINE_COPIA;} 
/*
	ciclo di lettura / scrittura  calcolo offset partenza e n. bytes
   da trasferire
*/
if(mess->blocco==-1)
{
    offsetr=0L;                           // inizio file
    numrich=lseek(caninp,0L,SEEK_END);    // dimensione massima
}
else 
{  
   numrich=(long)mess->dim*1024L;
   offsetr=(long)(mess->blocco-1)*numrich;
}
numbyte=0L;
nbytes=0;
offsetw=0;
while(numbyte < numrich)
{
   nbytes=rbyte(caninp,bufio,offsetr,bytes_IO);
   if(!nbytes) break;                           // fine file
	if(wbyte(canout,bufio,offsetw,nbytes)!=nbytes)
	{
		bitset(&dbdd[diskerr],g2di_sl,1);
		break;
	}							  
	offsetr=offsetr+bytes_IO;
	offsetw=offsetw+bytes_IO;
   numbyte=numbyte+nbytes;
	wai(2);
}
close(caninp);
close(canout);
bitset(&dbadf[arccorr],g2an_au,0);         // fine copia su floppy
dbadv[arccorr]=mess->blocco;
/*
   se il file e' di un archivio ed e' l'ultimo blocco segnalo
   fine copia
*/
if(mess->archivio != -1 && mess->flag)
   bitset(&dbadf[arcdes[mess->archivio-1].hea.p_1f+mess->n_file],g2an_fs,1);

FINE_COPIA:

if(mess->archivio != -1) arcdes[mess->archivio-1].canc=-1;

return(0);
}
