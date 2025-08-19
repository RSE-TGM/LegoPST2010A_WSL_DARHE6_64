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
   thcwin.c
      task per la gestione dei messaggio di hardcopy.
      Utilizza la funzione hcwin.c

      E' in attesa sulla coda c_hcwin

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include	"mesqueue.h"

/* Function prototypes */
extern void hcwin(int, int, int);

extern short coda_hc_mi;
extern short c_hcwin;

void thcwin()
{
   QUEUE_PACKET  queue, hcqueue;         
   S_IHCPY hcp;                 // messaggio richiesta hardcopy da MMI Win

   queue.que = c_hcwin;
   queue.flg = MSG_WAIT;
   queue.wto = 0;
   queue.amsg=(char*)&hcp;
   queue.lmsg=sizeof(hcp);

   hcqueue.que = coda_hc_mi;     // hardcopy
   hcqueue.flg = MSG_WAIT;
   hcqueue.wto = 0;
   hcqueue.amsg=(char *)&hcp.nbyte; // 4 byte di spare vedi schc

   while(1)
   {
      dequeue(&queue);
      if(!hcp.nbyte)  // controllare se possibile hardcopy
         hcwin (op_hc_new, hcp.video, hcp.nhcpy);
      else              // invio messaggio a driver parallela
      {
         hcqueue.lmsg=hcp.nbyte+4;
         enqueue(&hcqueue);
         if(!hcp.bLast)     // richiesta prossimo buffer da stampare
            hcwin (op_hc_cont, hcp.video, hcp.nhcpy);
         else                    // fine stampa libero lock
            hcwin (op_hc_end, hcp.video, hcp.nhcpy);
      }
   }
}
