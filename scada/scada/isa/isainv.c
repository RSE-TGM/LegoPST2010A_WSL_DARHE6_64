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
   isainv.c

   La routine esegue l' accodamento di un messaggio creato attraverso
   l'istruzione POL SEND "$ISA" 
		  
	word 0		= 4	lunghezza stringa $ISA
	word 1		$I
   word 2      SA
   word 3      = -2 argomento intero
	word 4      n. connessione
	word 5		= 
	......        word con messaggi
	......
	word n		= 


   Parametri

   mess  short *     messaggio di selezione zone
	lung	short			dimensione del messaggio 

   Ritorno

   nessuno

   22 Settembre 1995

*/
struct  sel_zon {
								short arg1;
							   short isa1;
                        short isa2;
                        short arg2;
								short conn;
								short arg3;
								short dati;
							} ;

#include <osf1.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "isarc.inc"
#include "messcada.inc"
#include "dconf.inc"
#include "isa.h"

extern unsigned short cisa_samp1;

isainv(mess,lung)
struct sel_zon* mess;
short lung;
{
QUEUE_PACKET queue;

if(mess->conn <=0 || mess->conn >NCHAN_ISA)
{
   return;
}
queue.que  = cisa_samp1+mess->conn-1;        // accodo per isa alla coda indicata
queue.lmsg = lung-sizeof(mess->arg1)-sizeof(mess->isa1)-sizeof(mess->isa2)-
             sizeof(mess->arg2)-sizeof(mess->conn);

queue.amsg = &mess->arg3;
queue.flg  = MSG_NOWAIT;
queue.wto  = -1;
enqueue(&queue);
}


