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
   repTask:
      Task gestione reperibili
      Inizializzazione aree dati per comunicazione con driver
      Ciclo di interrogazione GDC con scodamento eventuali messaggi.

*/
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesprocv.inc"
#include <string.h>
#include "dconf.inc"
#include "print.inc"
#include "repgdc.h"
#include "gesrep.h"

// External function declarations
extern void SetInt(void);
extern void _Vuota(void);
extern void IniGdc(void);
extern void GdcAllD(int, int);
extern void IniLine(void *);
extern int InvioGdc(char *);
extern void wai(int);
extern int InterpGdc(char **);
extern void GdcAllS(int);
extern void ter(void);

extern short c_rep;

void reptask()
{
	S_FIS  stlin;
   short i;
   short statoL;
   int ier;

   char* sReset="$R\r\n";        // stringa di reset
   char* sAbort="$A\r\n";        // stringa di abort generico
   char* sQuery="$Q\r\n";        // stringa richiesta stato

   char* pCampi[n_campi];
   QUEUE_PACKET queue;
   S_MGESREP m;

   stlin.linea=linea_Gdc;						// terza linea seriale
	stlin.baud=9600;
	stlin.data=8;
	stlin.stbit=1;
	stlin.parity='E';

	SetInt();								// abilito interrupt
   _Vuota();
//
// se non e' stato definito nel file fdesal.rtf il valore massimo
// degli accodamenti, lo assegno al valore di default
//
   if(!max_repall || (max_repall>def_max_repall))
         max_repall=def_max_repall;    

   queue.que=c_rep;
   queue.amsg=(char*) &m;
   queue.flg=MSG_WAIT;
   queue.wto=timer_que;
   queue.lmsg=max_BRx;

//
// Inizializzazione Gdc (gestore di chiamate)
//
   IniGdc();
//
// Ciclo iniziale con reset GDC
//
   do
   {
      GdcAllD(gdc_dConn,1);                   // off line
   	IniLine(&stlin);						// inizializzazione linea
      if(InvioGdc(sReset))                    
      {
         wai(tquery_Gdc);  // non ha risposto correttamente al reset
         continue;
      }
      statoL=InterpGdc(pCampi);
      GdcAllD(gdc_dConn,0);                   // on line

//
// ciclo attesa messaggi su coda
//
      do
      {
         ier=dequeue(&queue);
         if(!ier) cont_repall--;       // decremento n. messaggi in coda
         else cont_repall=0;
      //printf(" n. mess. %d \n",cont_repall);
      	if((!ier) && (dbdd[gdc_dAbil] & mask_sl)) 	// messaggio in coda e gestione abilitata
      	{
            m.mess[queue.lmsg]=0;
            //printf("\n %s",m.mess);
		      if(InvioGdc(m.mess)) break;	// errore comunicazione
      		statoL=InterpGdc(pCampi);
		      do
      		{
               wai(tquery_Gdc);              // periodo interrogazione
		      	if(InvioGdc(sQuery)) break;	// errore comunicazione
      			statoL=InterpGdc(pCampi);
               if(pCampi[gdc_cTag])          // memorizzo Tag in esame
                  strncpy(&dbstv[svDia[nTag]*g0lunst],pCampi[gdc_cTag],g0lunst-1);
               if(pCampi[gdc_cTel])          // memorizzo n. di telefono in uso
               {
                  strncpy(&dbstv[svDia[nPref]*g0lunst],pCampi[gdc_cTel],g0lunst-1);
                  strncpy(&dbstv[svDia[nTel]*g0lunst],pCampi[gdc_cTel]+g0lunst-1,g0lunst-1);
               }
               dbadv[gdc_aStatoL]= statoL & gdc_mST;  // stato sequenza
		       }
         	 while ((!(statoL & gdc_mS)) && (!(statoL & gdc_mRI)));  // o riconosciuto o terminata la sequenza
             if(statoL & gdc_mRI)     // allarme riconosciuto ?
             {
               strncpy(&dbstv[svRic[nRicTag]*g0lunst],pCampi[gdc_cTag],g0lunst-1);
               GdcAllS(svRic[nRicTag]);
               GdcAllS(svDia[nPref]);
             }
             else                     // non riconosciuto riaccodo
             {
               strncpy(&dbstv[svRic[nNonRicTag]*g0lunst],pCampi[gdc_cTag],g0lunst-1);
               GdcAllS(svRic[nNonRicTag]);
               if(!max_repretry || ((++m.count)<=max_repretry))    // permesso il riaccodamento ?
               {
                  queue.flg=MSG_NOWAIT;
                  if(cont_repall < max_repall)
                  {
                     cont_repall++;
                     enqueue(&queue);  // spazio in coda ?
                  }
                  queue.flg=MSG_WAIT;
               }
             }
       		 if(InvioGdc(sAbort)) break;	// errore comunicazione
      	}
      	else		// time out o gestione reperibili non abilitata
      	{
            strcpy(&dbstv[svDia[nTag]*g0lunst],"");
            strcpy(&dbstv[svDia[nPref]*g0lunst],"");
            strcpy(&dbstv[svDia[nTel]*g0lunst],"");
            dbadv[gdc_aStatoL]= -1;  // sequenza in stop
		      if(InvioGdc(sQuery)) break;	// errore comunicazione
      	}
      }
      while(1);
   }
   while (1);
   ter();
}
