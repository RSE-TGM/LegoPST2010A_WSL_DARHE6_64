/**********************************************************************
*
*       C Source:               arcread.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 16:23:46 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcread.c-4 %  (%full_filespec: arcread.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	arcread.c

	La funzione dato l'indice di un file di archivio e un offset
	all'interno del file restituisce un record.
	La lettura avviene a multipli di arcsort.dim utilizzando il buffer
	indirizzato da arcsort.indir.
	La dimensione del record e quindi l'incremento di offset viene 
   calcolata in base al numero di misure specificate nell'header 
   del record.
   La struttura arcsort deve essere inizializzata utilizzando la
   routine arcind.c. Se l'offset richiesto non e' all'interno del 
   file viene incrementato il n. di file da considerare.
   Se il numero del file == -1 si vuole forzare la close del canale 
   utilizzato
   La routine resetta la locazione arcdes[].canc quando il file
   in uso non coincide con l'indice memorizzato nella stessa loca-
   zione

	Parametri

	narc	short		n. dell'archivio
   ifile short *  n. del file all'interno dell'archivio
	bcamp	ARC_DBS**  buffer dati
	off	long *   offset in bytes nel file

	Ritorna

	0		se non ci sono errori
	1		si e' raggiunto il numero massimo di campioni disponibili

	17	Marzo 1992	Rel. 1.0 Fc
*/
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include <string.h>
#include "arc.inc"
#include "dconf.inc"


short arcan=-1;              // canale per open file
short arcnuma=-1;            // numero dell'archivio dell'ultima operazione
short arcfilea=-1;           // numero del file dell'ultima operazione
long  arcoff;                // offset da cui e' stata effettuata l'ultima
                             // lettura
short arcdim;                // numero byte letti nell'ultima read




arcread(narc, ifile, bcamp, off)
short narc;
short *ifile;
ARC_DBS ** bcamp;
long *off;
{
char fnome[FILENAME_MAX+1];
short max_occup;

if((*ifile)==-1)               // richiesta la close del canale
{
   if(arcan!=-1) close(arcan);
   arcan=-1;
   arcdes[narc].canc=-1;
   return(0);
}
for(;;)
{
/*
   il file non e' mai stato aperto oppure l'archivio o il
   file e' variato ?
*/
   if(arcnuma != narc || (*ifile) != arcfilea || arcan==-1)
   {
      if(arcan!=-1) close(arcan);
      arcnuma=narc;
      arcfilea=*ifile;
      strcpy(fnome,arcpath);
      strcat(fnome,"/");
      strcat(fnome,arcnome[arcnuma].arc+(*ifile));
      arcan=open(fnome,O_BINARY | O_RDONLY, 0);
      if(arcan==-1) {pscserr(ERR_IO,TASK_ARC,ROU_READ,0,SYS_CONT); return(1); }
      arcoff=-1;
   }
/*
   verifico se devo effettuare un accesso a disco per recuperare
   i dati o se sono gia' presenti nel buffer
*/
   max_occup=arcdes[narc].hea.n_mis*sizeof(DATDBS)+sizeof(HEAD_CAMP);
   if((arcoff+arcdim-max_occup) <  (*off) || (arcoff > (*off)) || arcoff == -1)
   {
      arcdim=rbyte(arcan,arcsort.indir,*off,arcsort.dim);
      if(arcdim <= 0)                    // end of file passo al successivo
      {                                  // file
/*
   se l'indice del file coincide con quello attualmente in uso
   ho raggiunti il numero massimo di campioni disponibili
*/
         if((*ifile)==arcnome[narc].use) return(1);
         *off=arcoff=0L;
         (*ifile)++;
         if((*ifile)>= arcdes[narc].hea.n_file) *ifile=0;
/*
   reset indice file in uso
*/
         if((*ifile) != arcdes[narc].canc) arcdes[narc].canc=-1;
         continue;
      }
      else 
      {
         arcoff=*off;
         break;         
      }
   }
   else break;
}
/*
   calcolo l'indirizzo e aggiorno il puntatore al prossimo
   campione
*/
*bcamp=((char*)arcsort.indir+(short)((long)(*off)-(long)arcoff));
*off=(*off)+sizeof(HEAD_CAMP)+
     (long)sizeof(DATDBS)*(long)((*bcamp)->hea.n_mis+(*bcamp)->hea.n_misvel);
return(0);
}  
