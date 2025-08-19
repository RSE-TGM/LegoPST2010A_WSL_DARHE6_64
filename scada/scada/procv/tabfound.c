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
   tabFound.c
      La routine gestisce i messaggi relativi ai tabulati. Se il
      tabulato indicato e' del tipo "*.*" invia l'elenco dei tabulati
      installati in caso contrario verifica se il tabulato esiste
      ed invia la diagnostica relativa all'MMI che la richiesto

      La routine accoda i messaggi di risposta solo se l'indice del
      video non e' -1 (messaggio da PAS e non da nodo MMI)

   Parametri

      char *   nome del tabulato
      S_MSEN*  indirizzo del messaggio MSEN che richiede l'informazione


   Ritorno
      0     accodare a tabul la richiesta di stampa del tabulato
      1     tabulato non esistente o richiesta la lista
            (non accodare la richiesta)

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "tabulati.inc"
#include	"mesqueue.h"
#include <string.h>

int tabFound(char * NomeTab, S_MSEN* sen)
{
   S_VSTAT risp;
   S_DIZTAB *pdiz;
   QUEUE_PACKET spack;
   S_TABINST   tmess;
   short itab;     
//
// se il video=-1 nessuna risposta
//
   if(sen->video==-1) return 0;
//
// verifico nome del tabulato richiesto
//
   spack.que = c_mmio;
   spack.flg = MSG_WAIT;
   spack.wto = 0;
   if(!strncmp("*.*",NomeTab,3))       // richiesto elenco tabulati presenti
   {
      tmess.zona = sen->zona; 
      tmess.video=sen->video;
      tmess.nodo=sen->video-1;
      tmess.indice = mtabinst; 
      memcpy(&tmess.pag[0],&sen->pag[0],10);
      memcpy(tmess.tabulato,diztab,sizeof(S_DIZTAB)*n_tabu);

      spack.lmsg=sizeof(S_TABINST);
      spack.amsg=(char *) & tmess;
   }
   else                                // verifico presenza tabulato
   {
      risp.zona = sen->zona; 
      risp.video=sen->video;
      risp.nodo=sen->video-1;
      risp.indice=vstat;
      memcpy(&risp.pag[0],&sen->pag[0],10);
      risp.punt=-1 ;
      risp.tip_pun=-1;
   	itab=0;
	   pdiz=diztab;
   	while(itab < n_tabu && memcmp(NomeTab,pdiz->nome,l_nomtab))
		{
	      itab++;
		   pdiz++;
		}
   	if(itab==n_tabu) risp.ext=errtab	;     // tabulato non esistente
      else  risp.ext=oktab;                  // tabulato esistente
      spack.lmsg=sizeof(S_VSTAT);
      spack.amsg=(char *) & risp;
   }
   enqueue(&spack);
   return 0;
}
