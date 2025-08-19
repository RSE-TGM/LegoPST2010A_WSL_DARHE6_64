/**********************************************************************
*
*       C Source:               simlddbs.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu May 13 09:47:11 1999 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simlddbs.c-5 %  (%full_filespec: simlddbs.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   SIMLDDBS.C
      Carica DBS e genera allarmi corrispondenti

      07.08.92  -  Rev.1.00  -  GM.Furlan

      27 Marzo 1995 Fc Porting 32Bit
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "dconf.inc"
#include "messcada.inc"
#include "mesqueue.h"
#include "comunic.inc"
#include "pscserr.inc"      
#include "simdia.inc"      
#include "simmsg.inc"      
#include "simula.inc"

// External function declarations
extern void verifall(short, short);
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);
extern void pscserr(int, int, int, int, int);      

extern DB_HEADER h_db;

/*
 riconosci_all manages the automatic ackowledge after a LOADCI phase.
 riconosci_all is disabled when the proper LOADCIRICALL not set = YES.
 Otherwise, riconosci_all is set =1 during LOADCI.
 Then, if at least an alarm is found, riconosci_all is set to OFF state within   simlddbs.
 If no alarm  is found, riconosci_all remains set to on so that the next
 DBUPD operation may trigger the automatic alarms' archiving.
*/

extern char riconosci_all;


short anapack;        // indice dell'ultimo pacchetto di analogici ricevuto
short digpack;        // indice dell'ultimo pacchetto di digitali ricevuto

int simlddbs(ud)
SM_DBUPD *ud;
{
short i;
short st_logico; 		/* stato logico digitale	*/
short *pdbaaf;       /* puntatore flag analogici */
short *pdig;  		   /* puntatore al data base logico */
S_TRATG mess;  /* struttura accodamento allarmi al task asinct */ 
QUEUE_PACKET queue;

// controllo corretta successione trasmissione blocchi

if (ud->tipopunti==ANA)     // analogici
{
   if (ud->indpack==0)
      anapack=0;
   else
   {
      if (ud->indpack==anapack+1)  
         anapack++;
      else
         goto errore;
   }
}
else                              // digitali
{
   if (ud->indpack==0)
      digpack=0;
   else
   {
      if (ud->indpack==digpack+1)  
         digpack++;
      else
         goto errore;
   }

   // coda allarmi digitali
   queue.que=c_digor;
   queue.flg=MSG_WAIT;
   queue.wto=0;
   queue.amsg=(char*)&mess;
   queue.lmsg=sizeof(S_TRATG);
}

// per tutti i punti del messaggio
for (i=0;i<ud->numpunti;i++)
   {
   if (ud->tipopunti==ANA)
   {
      // controllo flag di FS o FZ
      pdbaaf=&dbaaf[ud->db[i].punt];
      if(((*pdbaaf) & mask_afs) || ((*pdbaaf) & mask_afz)) continue ;
      dbaav[ud->db[i].punt]=ud->db[i].val;
      // generazione allarmi analogici
      verifall((short)ud->db[i].punt,g1tipaa);
   }

   if (ud->tipopunti==DIG)
   { 

      if(dbdatr[ud->db[i].punt] & 0x8000)
	{
	if(ud->db[i].val)
		ud->db[i].val=0;
	else
		ud->db[i].val=1;
	}
      pdig=&dbda[ud->db[i].punt];   // puntatore in data base digitale
      bitset(pdig,g2di_asl,(short)ud->db[i].val);	// aggiornamento flag fisico
      st_logico=dbda[ud->db[i].punt] & mask_sl;    // precedente stato logico
      // controllo flag di FS o FZ
      if(bitvalue(pdig,g2di_fs) || bitvalue(pdig,g2di_fz)) continue;

      // se e' cambiato lo stato logico

      if( st_logico != (short)ud->db[i].val )
         {

         /*
         Block for the communication and alarms' acknowledge  during the
         startup phase.
         I set dbdatr flag 13 of the point to insert the alarm directly
         in the archive.
         This flag is tested in _call() when the alarm must be inserted.
         modifica by Fabio
         */

         if((riconosci_all==LOADCIRICALLON) || (riconosci_all==LOADCIRICALLDONE))
            {
            /*
            Setto bit per inserimento in archivio immediato
            */
            riconosci_all=LOADCIRICALLDONE; // al prossimo DBUPD non riconosce piu'
            bitset(&(dbdatr[ud->db[i].punt]),ric13start,1); 
            }
         else
            bitset(&(dbdatr[ud->db[i].punt]),ric13start,0);


            // valore pari, digitale=0; se dispari, digitale=1
            bitset(pdig,g2di_sl,((short)ud->db[i].val%2));
            mess.mess=macdi;                 // messaggio di allarme da accodare 
            mess.stato=(short)ud->db[i].val;
            mess.ext=g1tipda;
            mess.indice=ud->db[i].punt;
            enqueue(&queue); 

         }  /* end if stato changed */

      }     /* end if pto == DIG */

   }        /* end ciclo for sui pti */


if(riconosci_all==LOADCIRICALLDONE)    /* Prossimo DBUPD emissioni normali */
   riconosci_all=LOADCIRICALLOFF;


return(0);

errore:
//   errore successione blocchi
   pscserr(ERR_TASK,TASK_SIMACQUI,ROU_LOAD,0,SYS_CONT);
   return(-1);

}

