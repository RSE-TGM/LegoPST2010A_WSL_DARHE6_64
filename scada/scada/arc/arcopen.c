/**********************************************************************
*
*       C Source:               arcopen.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 14:19:22 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcopen.c-4 %  (%full_filespec: arcopen.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcopen.c

   La funzione arcopen apre il file operativo FDARC degli archivi, legge 
   i descrittori ed inizializza le strutture per la memorizzazione dei dati
   Il file alla fine delle operazioni viene chiuso

   Parametri

   nessuno

   9 Marzo 1992   Rel. 1.0    Fc
   20 Febbraio 1995 Fc
      Inserita modifica caso anomalo archivio con 0 misure
      (ne viene impedita la creazione)
   24 Febbraio 1995 Fc
      Inserito reset analogici di data base per gli archivi cancellati
      Annullato immediatamente record in ARCFILE per archivi nuovi
*/
#include <osf1.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"
#include "dconf.inc"
#include "diagnodi.inc"

// External function declarations
extern void bitset(short *, short, short);
extern void pscserr(int, int, int, int, int);
extern void arcfnom(int, int);
extern int tra(int, int);

// Forward declarations
int calc_timer(short, short *);

static long fzq[n_freq]= {5L, 15L, 30L, 60L, 300L, 900L, 1800L,
         		         3600L, 28800L, 86400L, 600L};

int arcopen(void)
{
FILE *fp;
char fnome[FILENAME_MAX+1];
short i, j;
char arcfreq[n_freq];
short to;
short num_stringhe;           // n. variabili stringa
char *env;
/*
   inizializzo arcpath[] variabile contenente il direttorio
   per la creazione dei file di archivio
*/
if((env=getenv("ARCPATH")) != NULL) strcpy(arcpath,env);
else  strcpy(arcpath,conf[RTF]);
/*
   inizializzazione tabella archivi associati a ciascuna frequenza
*/
memset(arcfreq,0,n_freq);
/*
   definisco tutti gli archivi non installati
*/
for(i=0;i<n_arc;i++) bitset(&dbdd[arc_st01+i],g2di_sl,0);

strcpy(fnome,conf[RTF]);
#if defined OSF1 || defined LINUX
strcat(fnome,FDARC);
#else
strcat(fnome,"/FDARC.RTF");
#endif
fp=fopen(fnome,"rb+");
if(!fp)
{
   pscserr(ERR_IO,TASK_ARC,ROU_OPEN,0,SYS_HALT);
}
/*
   lettura dei record del file Fdarc e allocazione buffer necessari
   per la gestione degli archivi installati
*/
for(i=0;i<n_arc;i++)
{
   fseek(fp,(long)i*(long)rec_fdarc,SEEK_SET);
   fread(&arcdes[i],sizeof(HEAD_ARC),1,fp); 
   if(!arcdes[i].hea.n_mis) arcdes[i].hea.iarc=-1; // archivio vuoto impossibile
   if(arcdes[i].hea.iarc == -1) 
   {
      arcfnom(i,3);   // archivio non installato, verifico se occorre cancellare vecchi file
      continue;
   }
/*
   l'archivio e' presente: alloco la memoria per i puntatori delle
   misure associate e le leggo dal file
*/
   arcdes[i].mis=calloc(arcdes[i].hea.n_mis,sizeof(PUNTDBS));
   if(arcdes[i].mis==NULL) pscserr(ERR_MEM,TASK_ARC,ROU_OPEN1,i,SYS_HALT);
   fread(arcdes[i].mis,arcdes[i].hea.n_mis * sizeof(PUNTDBS),1,fp); 
/*
   alloco le strutture per i data base utilizzati per archiviazione
   normale e veloce tenendo presente che le stringhe occupano 3
   posizioni
*/
   for(j=0,num_stringhe=0;j<arcdes[i].hea.n_mis;j++)
      if(arcdes[i].mis[j].ext==g1tipst) num_stringhe++;
   arcdbsN[i]=malloc((arcdes[i].hea.n_mis+num_stringhe*2)*sizeof(DATDBS)+sizeof(HEAD_CAMP));    
   if(arcdbsN[i]==NULL) pscserr(ERR_MEM,TASK_ARC,ROU_OPEN1,i,SYS_HALT);
/*
   incremento il n. di archivi associati alla frequenza normale
   o veloce
*/
   arcfreq[arcdes[i].hea.c_freqN]++;   
   bitset(&dbadf[arcdes[i].hea.p_pd],g2di_fs,0);      // normale
/*
   inserisco codice frequenza e codice durata
*/
   dbadv[arcdes[i].hea.p_pd]=arcdes[i].hea.c_freqN*100+arcdes[i].hea.c_dur;
/*
   se l'archivio e' di tipo lento-veloce alloco anche il dbs
   per il calcolo degli accumuli e lo inizializzo a zero
*/
   if(arcdes[i].hea.tipo == arc_Len)
   {
      arcdbsL[i]=malloc((arcdes[i].hea.n_mis+num_stringhe*2)*sizeof(DATDBS)+sizeof(HEAD_CAMP));    
      if(arcdbsL[i]==NULL) pscserr(ERR_MEM,TASK_ARC,ROU_OPEN2,i,SYS_HALT);
      memset(arcdbsL[i],0,arcdes[i].hea.n_mis*sizeof(DATDBS)+sizeof(HEAD_CAMP));    
/*
   incremento il n. di archivi associati alla frequenza lenta
*/
      arcfreq[arcdes[i].hea.c_freqL]++;   
      bitset(&dbadf[arcdes[i].hea.p_pd],g2di_fs,1);   // lenta
   }
/*
   alloco la memoria per le tabelle contenenti i nomi dei file
   associati all'archivio
*/
   arcnome[i].arc=calloc(arcdes[i].hea.n_file, l_arcnome);
   if(arcnome[i].arc==NULL) pscserr(ERR_MEM,TASK_ARC,ROU_OPEN3,i,SYS_HALT);
/*
   setto a -1 la locazione relativa all'indice dell'ultimo file
   cancellato (vedi arcfile, arcfind e arcread)
*/
   arcdes[i].canc=-1;   
/*
   se l'archivio e' di nuova installazione inizializzo i digitali
   e gli analogici in data base di sistema
*/
   bitset(&dbdd[arcdes[i].hea.p_st],g2di_sl,1);        // archivio esist.
   bitset(&dbdd[arcdes[i].hea.p_st],g2di_fa,0);        // archiviazione sospesa  attiva
   if(!arcdes[i].hea.flag)
   {
      arcnome[i].use=0;                                    // n. file in uso
      dbadv[arcdes[i].hea.p_fc]=0;
      dbadv[arcdes[i].hea.p_nc]=0;                        // n. campioni
/*
   se l'archivio e' stato modificato devo cancellare i file precedentemente
   memorizzati, il numero di file e' memorizzato nell'analogico p_nfmax
   i nomi nel file ARCFILE.RTF. L'operazione viene effettuata da arcfnom
*/
      if(dbadv[arcdes[i].hea.p_nfmax]!=0.0) arcfnom(i,3); // cancellazione vecchi files
      dbadv[arcdes[i].hea.p_nfmax]=arcdes[i].hea.n_file;  // n. max. file attuali
      for(j=0;j<arcdes[i].hea.n_file;j++)
         dbadv[arcdes[i].hea.p_1f+j]=0.0;                  // ggoommaa
      arcdes[i].hea.flag=1;                                 // archivio in uso
      fseek(fp,(long)i*(long)rec_fdarc,SEEK_SET);
      fwrite(&arcdes[i],sizeof(HEAD_ARC),1,fp);
      arcfnom(i,1);
   }
   else            // archivio gia' in uso leggo la tabella file in uso
   {               // se almeno un file e' stato utilizzato
      dbadv[arcdes[i].hea.p_nfmax]=arcdes[i].hea.n_file;  // n. max. file attuali
      if(dbadv[arcdes[i].hea.p_fc] != 0.0)
      {
         arcnome[i].use=dbadv[arcdes[i].hea.p_fc]-1;
         arcfnom(i,0);
      }
   }
}
fclose(fp);
/*
   preparazione tabelle time out per distribuzione salvataggio
   archivi su disco
   inizializzo la tabella dei time out a -1 (corrisponde ad archivio
   non installato o ad scrittura su disco avvenuta)
   Il time out viene caricato dopo la raccolta dei dati, decrementato
   ciclicamente ad ogni attivazione del task  e resettato dopo la 
   memorizzazione su disco
*/
memset((char*)t_N,-1,sizeof(t_N));
memset((char*)t_L,-1,sizeof(t_L));

to=0;
for(i=0;i<n_freq;i++)
{
   if(arcfreq[i]) calc_timer(i,&to);       // calcolo timer per frequenza
}
/*
   inizializzo la mail box
*/
tra(mbox_archiv,1);
return(0); 
}
/*
   calc_timer

   Funzione per il calcolo della distribuzione dei tempi di scrittura su disco
   dei dati di archivio
   
   Parametri

   freq  short       codice frequenza in esame
   to    short *     tempo di memorizzazione (viene aggiornato dalla
                     routine stessa)

   10 Marzo 1992     Rel. 1.0 Fc
*/
int calc_timer(short freq, short *to)
{
short i;
short to_max;

/*
   frequenza inferiore al ritardo massimo
*/
if(fzq[freq] < ArcRit) to_max=fzq[freq]-2;
else  to_max=ArcRit-2;

for(i=0;i<n_arc;i++)
{
/*
   archivio esistente ? 
*/   
   if(arcdes[i].hea.iarc == -1 ) continue;
/*
   frequenza corretta ?
   anche la tempificazione della frequenza lenta deve essere posta
   uguale a quella veloce (l'accumulo viene infatti eseguito alla
   frequenza veloce)
*/
   if(arcdes[i].hea.c_freqN == freq )
   {
      t_N[i].tin=*to;
      if(arcdes[i].hea.tipo==arc_Len) t_L[i].tin=*to;
   }
   else continue;

   *to=*to+ArcMin;                    // incremento per prossimo archivio
   if((*to)>to_max) *to=0;     

}
return(0);
}
