/**********************************************************************
*
*       C Source:               arcfile.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 14:17:24 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcfile.c-3 %  (%full_filespec: arcfile.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcfile.c

   La funzione crea i nomi dei file associati agli archivi che hanno
   durata pari a quella fornita in input.

   Parametri:

   dur  short    codice durata dell'archivio

   
   12 Marzo 1992  Rel. 1.0    Fc

   29 Giugno 1995
   In caso di archivio di tipo vettoriale non deve essere creato
   il file (crea incongruenze per durate superiori al giorno)
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"
#include "dconf.inc"
#include "diagnoan.inc"
#include "tipal.inc"

// External function declarations
extern void decnum(char *, int, int, int, float);
extern void bitset(short *, short, short);
extern void arcdia(short, short, short);
extern int rew(int, int, int *);
extern int tra(int, int);
extern void wai(int);
extern void arcfnom(int, int);

void arcfile(short dur)
{
short narc;
char fnome[FILENAME_MAX+1], fdel[FILENAME_MAX+1];
short lung;
ARCNOME *posname;
float dfile;
short anno;
int   ier;
short point;

strcpy(fnome,arcpath);
strcat(fnome,"/");
lung=strlen(fnome);

for(narc=0;narc<n_arc;narc++)
{
   if(arcdes[narc].hea.iarc==-1 || arcdes[narc].hea.c_dur!=dur) continue;
   if(arcdes[narc].hea.tipo==arc_Vet) continue;
/*
   crea il nome dell'archivio e lo apro 
   il nome viene costruito dato:
      - num. archivio  (2 caratteri) a partire da 1
      - ora (se freq 5 sec.) o giorno (2 caratteri) 
      - giorno (se freq 5 sec.) o mese (2 caratteri) 
      - mese (se freq 5 sec.) o anno (2 caratteri) 
*/
   decnum(&fnome[lung],2,-2,narc+1,0.) ;
   if(!arcdes[narc].hea.c_dur)
   {
      decnum(&fnome[lung+2],2,-2,(short)dbadv[db_mese],0.) ;
      dfile=dbadv[db_giorno]*100+dbadv[db_ora];
      decnum(&fnome[lung+4],4,-2,(short)dfile,0.) ;
      dfile=dfile+dbadv[db_mese]*10000.;
      fnome[lung+8]=0;
#if defined OSF1 || defined LINUX
      strcat(fnome,".ars");
#else
      strcat(fnome,".ARS");
#endif
   }
   else
   {
      anno=dbadv[db_anno];
      dfile=dbadv[db_giorno]+dbadv[db_mese]*100;
      if(anno >= 2000) anno=anno-2000;
      else anno=anno-1900;
      decnum(&fnome[lung+2],2,-2,anno,0.) ;
      decnum(&fnome[lung+4],4,-2,(short) dfile,0.) ;
      dfile=dfile+anno*10000.;
      fnome[lung+8]=0;
#if defined OSF1 || defined LINUX
      strcat(fnome,".arc");
#else
      strcat(fnome,".ARC");
#endif
   }
/*
   verifico se il nome del file e' uguale a quello inserito nella tabella
   se e' diverso aggiorno la tabella e la salvo su disco
*/
   posname=arcnome[narc].arc+arcnome[narc].use;
   if(strcmp((char*)posname,&fnome[lung]))
   {
/*
   Dichiaro il file in uso da copiare (bit FA)
   incremento il n. del file in uso, aggiorno la tabella dei nomi,
   Cancello il precedente file e  se ho superato il numero massimo 
   di file riparto da zero
*/
      if(posname->nome[0])               // occupato o a 0 ?
      {
         point=arcdes[narc].hea.p_1f+arcnome[narc].use;
         bitset(&dbadf[point],g2di_fa,1);
         arcdia(point,g1tipad,al_blank);
         if((++arcnome[narc].use) >= arcdes[narc].hea.n_file) arcnome[narc].use=0;
         posname=arcnome[narc].arc+arcnome[narc].use;
         if(posname->nome[0])
         {
            strcpy(fdel,arcpath);
            strcat(fdel,"/");
            strcat(fdel,posname->nome);
/*
   prima di cancellare il file verifico che non sia in uso
   ad un tabulato altrimenti attendo 1 secondo la fine delle
   operazioni di ricerca dati
*/
            rew(mbox_archiv,0,&ier);         // lock con task di ricerca meno prioritario
            tra(mbox_archiv,1);              // e quindi interrompibile
            while(arcnome[narc].use==arcdes[narc].canc) wai(20);
            unlink(fdel);                     // cancello precedente file
         }
      }
      strcpy(posname->nome,&fnome[lung]);
      arcfnom(narc,1);
      dbadv[arcdes[narc].hea.p_1f+arcnome[narc].use]=dfile;
      bitset(&dbadf[arcdes[narc].hea.p_1f+arcnome[narc].use],g2di_fa,0);
      bitset(&dbadf[arcdes[narc].hea.p_1f+arcnome[narc].use],g2di_fs,0);
      dbadv[arcdes[narc].hea.p_fc]=arcnome[narc].use+1;
      dbadv[arcdes[narc].hea.p_nc]=0;
      arcdes[narc].offset=0L;
   }
}
}
