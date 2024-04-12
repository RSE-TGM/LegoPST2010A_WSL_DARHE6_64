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
        la function lantab esamina fra i tabulati periodici
        presenti nel dizionario quelli installati alla periodicita'
		  specificata in input .
		  Per ogni tabulato individuato accoda un messaggio sulla 
		  coda c_tabul.
*/
#include <osf1.h>
#include <stdio.h>


#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tabulati.inc"
#include "mesqueue.h"

lantab(per)
short per;
{
S_DIZTAB *pdiz;
register int i ;
short ier;
S_STAB mess;            /* messaggio per richiedere la stampa */
QUEUE_PACKET queue;

pdiz=&diztab[0];

queue.flg=MSG_WAIT;
queue.wto=0;
queue.amsg=(char*)&mess;
queue.lmsg=sizeof(mess);
queue.que=c_tabul;
/*
        inizializzazione del messaggio
*/
mess.mess=mstab ; 
mess.richiesta=-1;
/*
        ciclo di ricerca dei tabulati di periodicita' per
*/
for(i=0;i<n_tabu;i++,pdiz++)
	{
   if(pdiz->periodo==per)		 // se il periodo Š quello desiderato
		{
		mess.lung=sizeof(S_STAB);
      memcpy(mess.nome,pdiz->nome,l_tnome) ;	 // copia il nome nel messaggio
	   enqueue(&queue);		  // accoda il messaggio per tabul.
      }
	}
return ;
}


