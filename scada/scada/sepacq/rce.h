/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
	Rce.h

	File di include per la definizione dei parametri riguardanti
	la gestione rce Sepa

   13 Febbraio 1995
   Modifiche al buffer Rce per la gestione di Rce separati in base
   ai gruppi di acquisizione definiti nel file FDESAL.RTF

*/
#include "defpub.h"
#include "maxpar.inc"

#define	EVENTO_ANTE	1
#define	EVENTO_SUCC	2
	typedef struct s_rce {
						short	giorno;
						short	ora;
						char	minuti;
						char	secondi;
						short millisecondi;
						short id;
						char	valore;
						char  stato;
						short tipo;
		} S_RCE;

#define NON_ALLOCATO		0
#define ALLOCATO			1
#define IN_ORDINAMENTO	2

	typedef struct s_dbrce {	 	// struttura descrittore buffer RCE
				char	f;				// stato buffer
				S_RCE	*p;			// puntatore buffer in dos
//				_vmhnd_t h;			// handle buffer in XMS
				short	n;				// numero dati Rce inseriti
				short max;			// n. massimo elementi
				short ord;			// n. elementi validi dopo ordinamento
				} S_BRCE;

#define nBRCE	max_group   // un buffer per ogni gruppo

	pub S_BRCE BuffRce[nBRCE];
	
#define	n_rceante	 128
#define	n_rcesucc	 256

#define RCETIME		 (10*6) 		// massima attesa chiusura rce 10 minuti
	pub short rce_timeout;

#include <stdio.h>

	pub short rcecan;							// canale file scrittura
	pub short	n_rcefp;	   					// n. file in uso
#define max_rcefp		8				// n. massimo file rce disponibili
	pub long	rceoffset;						// posizione scrittura
/*
	elenco punti analogici di diagnostica per memorizzazione dati
	riguardanti rce avvenuti
*/
#define  PRICORA	  118				// nodo richiesta ora
#define  PCRCE		  119 			// indice Prossimo file rce
#define	PFRCE 	  120				// file 0
