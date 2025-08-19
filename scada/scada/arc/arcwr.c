/**********************************************************************
*
*       C Source:               arcwr.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 16:28:53 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcwr.c-3.1.1 %  (%full_filespec: arcwr.c-3.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcwr.c

   La funzione gestisce la memorizzazione di un record di un archivio
   su disco

   Parametri

   nessuno

   10 Marzo 1992  Rel. 1.0    Fc

   30 Giugno 1995
      Inserimento gestione flag fa per digitale di stato archivio
      Se il flag =1 l'archivio sospende l'archiviazione
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

#include "arc.inc"
#include "dconf.inc"  
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "diagnodi.inc"
#include "tipal.inc"

// External function declarations
extern int bitvalue(short *, short);
extern void pscserr(int, int, int, int, int);
extern int wbyte(int, char *, long, int);
extern int rew(int, int, int *);
extern int tra(int, int);
extern void wai(int);
extern void arcfnom(int, int);
extern void bitset(short *, short, short);
extern void arcdia(short, short, short);

int arcwr(void)
{
char j;
short  canale;
char fnome[FILENAME_MAX+1];
short narc;
ARTIME *timer;
ARC_DBS **dbs;
PARCDES *arc;     // puntatore al descrittore dell'archivio
short dim;        // n. bytes trasferiti
short use;
ARCNOME *posname;	// puntatore nome file da cancellare
char fdel[FILENAME_MAX+1];		// path file da cancellare
int ier;
/*
   ciclo di gestione dei time-out normale e lento con i rispettivi
   data base
*/
for(j=0,timer=t_N,dbs=&arcdbsN[0];j<2;j++,timer=t_L,dbs=&arcdbsL[0])
{
   for(arc=&arcdes[0],narc=0;narc<n_arc;narc++,timer++,dbs++,arc++)
   {
      if(timer->tco==-1L) continue;
      if(bitvalue(&dbdd[arc->hea.p_st],g2di_fa)) continue;  // archiviazione sospesa
      if(timer->tco >= ArcMin) 
      {
         timer->tco=timer->tco - ArcMin;
         continue;
      }
/*
   memorizzo il record su disco, resetto il timer e incremento
   il numero di campioni
*/
      timer->tco=-1L;
      dbadv[arc->hea.p_nc]=dbadv[arc->hea.p_nc]+1;
/*
   apro il file recuperando il nome dalla tabella arcnome
*/
      strcpy(fnome,arcpath);
      strcat(fnome,"/");
      strcat(fnome,(char*)(arcnome[narc].arc+arcnome[narc].use));
#if defined (DEBUG)
   printf("\n wr %d %s %ld \n",narc,fnome,arc->offset);
#endif
      canale=open(fnome,O_BINARY | O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
      if(canale==-1) {pscserr(ERR_IO,TASK_ARC,ROU_WR,0,SYS_CONT); return(0); }
      if((*dbs)->hea.n_misvel)            // archiviazione veloce
          dim=sizeof(HEAD_CAMP)+(*dbs)->hea.n_misvel*sizeof(DATDBS);
      else                             // archiviazione lenta
          dim=sizeof(HEAD_CAMP)+(*dbs)->hea.n_mis*sizeof(DATDBS);
      if(wbyte(canale,(char*)(*dbs),arc->offset,dim)!=dim)
      {
/*
	problemi scrittura su disco probabile disco pieno
	cancello il file piu' vecchio
*/
			use=arcnome[narc].use;
         if((++use) >= arc->hea.n_file) use=0;
         posname=arcnome[narc].arc+use;
			if(!posname->nome[0])
			{
				posname=arcnome[narc].arc; 	// primo file
				use=0;
			}
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
            while(use==arc->canc) wai(20);
            unlink(fdel);                     // cancello precedente file
				posname->nome[0]=0;					 // annullo descrittori
		      dbadv[arc->hea.p_1f+use]=0.0;
		      arcfnom(narc,1);
			}
         if(!bitvalue(&dbdd[sthdisk],g2di_sl))     // disco gia' pieno 
         {
            bitset(&dbdd[sthdisk],g2di_sl,1);      // disco pieno
            arcdia(sthdisk,g1tipdd,al_blank);
         }
      }
      else arc->offset=arc->offset+dim;
      close(canale);
/*
   se sto trattando il data base ad archiviazione lenta 
   (accumuli) lo resetto dopo la copia
*/
      if(j==1) memset((*dbs),0,dim);         
   }
}   
}
