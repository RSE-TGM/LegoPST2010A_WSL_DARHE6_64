/**********************************************************************
*
*       C Source:               simclarc.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 12:21:19 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simclarc.c-3 %  (%full_filespec: simclarc.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   SIMCLARC.C

      24.11.92  -  Rev.1.00  -  GM.Furlan

      27 Marzo 1995 Fc
      Porting a 32 Bit.
      Integrato nella routine il restart del task di archiviazione
      Viene eseguita solo per (AC_SIM_ENEL)
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "g2comdb.inc"
#include "arc.inc"
#include "simana.inc"
#include "simula.inc"

// External function declarations
extern void arcfnom(short, short);
extern void bitset(short *, short, short);
extern void res(int);

extern int arcwai_tcb;

void simclarc()
{
short i, narc, nfil, nmaxfile;
short ora;
char hour[3];
char fdel[FILENAME_MAX+1];
ARCNOME *posname;

memset(hour,0,3);
for(narc=0;narc<n_arc;narc++)
{
   if(arcdes[narc].hea.iarc==-1) continue;
   nmaxfile=arcdes[narc].hea.n_file;                  // n. max. file da leggere
   nfil=arcnome[narc].use;
   for(i=0;i<nmaxfile;i++)
   {
      posname=arcnome[narc].arc+nfil;
      if(!posname->nome[0]) continue;      // nessun file d'archivio aperto
      // cancellazione file da disco
      strcpy(fdel,arcpath);  
#if defined OSF1 || defined LINUX
      strcat(fdel,"/");
#else
      strcat(fdel,"\\");
#endif
      strcat(fdel,posname->nome);
printf("unlink file : %s\n",fdel);
      unlink(fdel);                     
      posname->nome[0]=0;               // cancellazione nome file da tabella
printf("prima di arcfnom [%d]\n",narc);
      arcfnom(narc,1);                  // aggiornamento file ARCFILE.RTF
      dbadv[arcdes[narc].hea.p_1f+nfil]=0.;  // reset ana. diag. durata file
      bitset(&dbadf[arcdes[narc].hea.p_1f+nfil],g2di_fa,0);
      bitset(&dbadf[arcdes[narc].hea.p_1f+nfil],g2di_fs,0);
      dbadv[arcdes[narc].hea.p_nc]=0;   // reset num. camp.
      arcdes[narc].offset=0L;           // reset offset
      arcnome[narc].use=nfil;           // nuovo file in use 
      dbadv[arcdes[narc].hea.p_fc]=nfil;
      nfil--;
      if (nfil<0) nfil=nmaxfile-1;
   }
}

// ripartenza task archiviazione
res(arcwai_tcb);
}







