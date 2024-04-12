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
   hcwin
      modulo per la gestione delle richieste di hardcopy provenienti
      da mmi Win
      La funzione gestisce i seguenti tipi di operazioni:
         
         op_hc_new   richiesta di inizio di una nuova hardcopy
            Se non ci sono hard copy in corso invia il messaggio
            di inizio sequenza stampa, altrimenti inserisce nel
            buffer associato al video il flag di richiesta

         op_hc_cont  richiesta di continuazione di una hard copy
            gia' in corso. Invia immediatamente il messaggio di
            accettazione

         op_hc_off un video e' stato dichiarato off_line. Reset
            dei flag di hardcopy associati. Se il video ha una
            hardcopy in corso passa ad esaminare le richieste di
            hardcopy degli altri video

         op_hc_end e' terminata l'hardcopy in corso. Passa ad esaminare
            le richieste di hardcopy relative agli altri video


      Parametri:
         short    tipo di operazione
         short    n. del video a partire da 1
         short    n. dell'hardcopy da 1 a max_hcpy_video

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include	"mesqueue.h"

short vhcpy, ihcpy;     // n. video che sta eseguendo l'hardcopy ed indice
                        // dell'hardcopy in corso
char stvihc[max_video][max_hcpy_video];
                        // matrice video*n. hardcopy =1 hardcopy prenotata

hcwin (funz, video, nhcp)
short funz, video, nhcp;
{
QUEUE_PACKET  queue;         
S_RHCPY hcp;                 // messaggio ack per MMI Win
short i, j;

switch (funz)
{
   case op_hc_new:         // nuova hardcopy
      if(vhcpy)            // gia' in corso
      {
         stvihc[video-1][nhcp-1]=1;    // prenotata - nessun messaggio di ritorno
         return;
      }
      vhcpy=video; ihcpy=nhcp;          // in corso
      hcp.bFirst=1;                    // primo messaggio
   break;

   case op_hc_off:         // video off line
      for(j=0;j<max_hcpy_video;j++) stvihc[video-1][j]=0;   // reset hardcopy
      if(video!=vhcpy) return;    // video off line non era in hardcopy
                                  // se era in hardcopy la termino  
   case op_hc_end:         // fine hardcopy
      stvihc[vhcpy-1][ihcpy-1]=0;    // libera
      vhcpy=0; ihcpy=0;              // reset in corso
      for(i=0;i<max_video;i++)      // ricerco eventuale hardcopy prenotata
      {
         for(j=0;j<max_hcpy_video;j++)
            if(stvihc[i][j])
            {
               vhcpy=i+1;
               ihcpy=j+1;
               break;
            }
         if(vhcpy) break;     // trovata hardcopy prenotata
      }
      if(!vhcpy) return;            // fine attivita'
      hcp.bFirst=1;                 // primo messaggio
   break;
   case op_hc_cont:
      hcp.bFirst=0;                 // primo messaggio
   break;
}
queue.que = c_mmio;           // invio messaggio
queue.flg = MSG_WAIT;
queue.wto = 0;
queue.amsg=(char*)&hcp;
queue.lmsg=sizeof(hcp);

hcp.nhcpy=ihcpy;
hcp.indice=mhcp;
hcp.classe=0;
hcp.nodo=vhcpy-1;
enqueue(&queue);
return;
}
