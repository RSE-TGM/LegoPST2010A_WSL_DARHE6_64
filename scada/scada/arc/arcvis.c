/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcvis.c

   Modulo che interpreta il messggio S_MAGGR ed prepara ed invia al
   task tabul il messaggio S_VISARC

   Parametri

   mric  S_MAGGR *   indirizzo messaggio da trattare
   msen  S_VISARC*   indirizzo messaggio da inviare

   Ritorno

   nessuno   

   27 Marzo 1992  Rel. 1.0    Fc
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include "switch.inc"
#include "gpunt.inc"
#include "comunic.inc"
#include "arc.inc"
#include "arcvis.inc"
#include "video.inc"

// External function declarations
extern int ricerca(char*, short*, short*, long*, short*, FILE*);
/*
   codtrend e' una variabile utilizzata come lock fra il task
   scgev che che riceve il messaggio di richiesta visualizzazione 
   trend e tabul che invia effettivamente i dati.
   Ad ogni trend per il solo primo quadrante viene associato un
   codice inserito poi nel messaggio verso tabul e nella tabella stato
   video. Quando tabul scoda il messaggio  verifica che il codice 
   nel messaggio sia ancora equivalente a quello inserito nella
   tabella video, in caso contrario non gestisce il messaggio e abortisce
   le operazioni
*/
short codtrend[max_video];

int arcvis(S_MAGGR *mric, S_VISARC *msen)
{
short i, j;
long blocco; 	// per routine ricerca 
short  posiz;	// per routine ricerca
char *sig;     // puntatore inizio sigle quadrante
PARCDES *arc;  // puntatore all'archivio richiesto
short point, ext;
PUNTDBS *pnt;  // puntatore ai punti nel descrittore 
               // dell'archivio

//printf(" qua %d arc %d\n",msen->hea.indqua,mric->archivio);
/*
   verifico esistenza archivio
*/
arc=&arcdes[mric->archivio-1];
if(arc->hea.iarc==-1) return(0);    
/*
   inizializzo header e puntatori alle sigle delle curve
*/
memcpy(msen,mric,sizeof(H_MTREND));
msen->archivio=mric->archivio;
memset(msen->point,-1,max_sigqua);
msen->hea.indice=mvisarc;			
msen->hea.spare=0;
/*
   solo nel caso di primo quadrante incremento codtrend
   e inserisco nella tabella video
*/
if(msen->hea.indqua==1)
{
   if((codtrend[msen->hea.video-1]++)>100) codtrend[msen->hea.video-1]=1;
   tstv[msen->hea.video-1].tsv[msen->hea.zona-1].v_tipo=codtrend[msen->hea.video-1];
}
msen->hea.codtrend=codtrend[msen->hea.video-1];   
/*
       ricerca in fnomi per ricavare dalle sigle dei punti richiesti 
       i puntatori in DBS e verifico la loro presenza nell'archivio.
*/
sig=&mric->sigla[0];
for(i=0;i<mric->hea.n_mis;i++,sig=sig+SCD_SIGLA)
{
   for(j=0;j<SCD_SIGLA;j++) if(*(sig+j)==' ') *(sig+j)=0; 
   if(ricerca(sig,&point,&ext,&blocco,&posiz,fpp[fnomi])) continue;
/*
   se il punto esiste verifico la sua posizione nel descrittore dell'
   archivio
*/
   pnt=arc->mis;
  	for(j=0;j<arc->hea.n_mis;j++,pnt++)
	{
      if(pnt->ext==ext && pnt->punt==point)
      {
         msen->point[i]=j;
			break; 
		}
      if(pnt->ext==g1tipst) j=j+2;           // in caso di stringhe incremento
                                             // di due posizioni
	}
}
return(sizeof(S_VISARC));
}

