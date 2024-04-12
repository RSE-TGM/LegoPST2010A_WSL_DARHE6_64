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
	isadia.c
		La routine verifica che per tutti i nodi isa collegati ci
		sia il transito di almeno un messaggio al minuto.
		In caso contrario viene settato a 1 il bit di FA relativo
		al digitale di connessione


	Parametri
		short		nodo isa da 0 a 3 oppure -1
		short	   =0	  reset contatore messaggi
			      =1   incremento contatore messaggi in transito
				   =-1  non esiste collegamento

	Ritorno
		nessuno

*/
#include <osf1.h>
#include "g2comdb.inc"
#include "isarc.inc"
#include "messcada.inc"
#include "dconf.inc"
#include "isa.h"
#include "diagnodi.inc"

extern char* isaAC;
extern char* isaDC;

short isafl[NCHAN_ISA];

isadia(short nodo, short flag)
{
	short i, inizio, fine;

	if(nodo==-1)			// per tutti i nodi isa
	{
		inizio=0;
		fine=NCHAN_ISA-1;
	}
	else inizio=fine=nodo;		// solo per il nodo indicato
	for(i=inizio;i<=fine;i++)
	{
		if(!flag && (isafl[i]==-1)) continue;			// nessun reset se off line
		if(!flag)
		{
			if(!isafl[i]) bitset(&dbdd[stnod01+i],g2di_fa,1); //  FA set
		}
		else
		{
			if(!isafl[i]) bitset(&dbdd[stnod01+i],g2di_fa,0); //  FA reset
		}
		isafl[i]=flag;
	}
   if((nodo!=-1) && (flag==-1))     // nodo off line
   {
//
//    nodo off line: FA tutte le misure analogiche o digitali calcolate
//    non standard aggiornate dalla connessione indicata da app
//
      for(i=0;i<h_db.dimac;i++)
      {
         if((*(isaAC+i)) & (char)(1 << nodo)) // aggiornato dal nodo
            bitset(&dbacf[i],g2an_fa,1);
      }
      for(i=0;i<h_db.dimdc;i++)
      {
         if((*(isaDC+i)) & (char)(1 << nodo)) // aggiornato dal nodo
            bitset(&dbdc[i],g2di_fa,1);
      }
   }
}
