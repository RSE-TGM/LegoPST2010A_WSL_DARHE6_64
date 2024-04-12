/**********************************************************************
*
*       C Source:               taskscc.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:44:41 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: taskscc.c-3 %  (%full_filespec: taskscc.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/********************************************************************
 *
 * Scope:
 *    Task gestione comunicazione sulla porta destinata alla
 * 	CPU di SCC.
 *
 * History:
 * ********
 * Date       Author   Description    											
 * ---------- -------- ----------------------------------------------
 * 10/07/1993 TD	     Created
 *
 ********************************************************************/

// Messaggi SCC
// ------------
#define	msgRCE 	0x6016 		// SCC RCE Request
#define	msgACK	0x0616		// SCC ACK Message
#define	msgNCK	0x1516		// SCC NACK Message
#define	traRCE 	0x61	 		// SCC RCE Trasmission
#define	traSYN 	0x16	 		// SCC RCE Trasmission

#include <stdlib.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "sepdati.inc"
#include "sepdiag.inc"
#include "mesprocv.inc"
#include "dconf.inc"
#include "print.inc"

extern	unsigned short 	MsgSCC ;

lnkscc()
{
	#define max_retry	3				// n. massimo tentativi invio messaggio
	#define l_rcestr	132
	#define LRce	2					// linea Rce a partire da 0
	#define TRce	100				// Timeout Rce

	#define  hea_trasm	5			// byte header messaggio syn cod e lun 
											// + 2 byte crc
	struct {
			char	syn;					// syncronizzazione
			char	cod;					// codice
unsigned	char	lun;					// lunghezza pacchetto
			char 	st[l_rcestr+2]; 	// stringa caratteri da inviare + 2 crc16
		} trasm;							// messaggio da inviare

	char RceFname[FILENAME_MAX+1];				// nome file Rce
	short nFRce;						// numero file rce
	long offset;						// posizione attuale lettura file
	short canale;						// canale per open file
	short retry;						// n. tentativi invio messaggio
	short lung;
	short numbyte;						// n. byte letti
	short ier;							// codice errore ModSend
	short TSuw;							// timeout Suw

	QUEUE_PACKET pack;
	S_MDIA_R		 mmdia;
	S_FIS  stlin;
	
	stlin.linea=LRce;						// terza linea seriale
	stlin.baud=9600;
	stlin.data=8;
	stlin.stbit=1;
	stlin.parity='N';

	pack.wto=0;
	pack.flg=MSG_WAIT;
	pack.amsg=(char*)&mmdia;
	pack.lmsg=sizeof(mmdia);
	pack.que=c_mmii;

	mmdia.indice=mdia;					// messaggio segnalazione on line off line
	mmdia.a.allarme=stscc;
	
	IniLine(&stlin);						// inizializzazione linea
	SetInt();								// abilito interrupt
	canale=-1;
	bitset(&dbdd[stscc],g2di_sl,1);
	trasm.syn=traSYN;
	trasm.cod=traRCE;

	TSuw=0;
	while (1)
		{
		if(suw(TSuw))							// Attendo sblocco dal task di ricezione
			{
				TSuw=FineTrasm(&canale,&mmdia,&pack);
				continue;
			}
		switch (MsgSCC)
			{
			case	msgRCE:				// richiesta ultimo file Rce
				strcpy(RceFname,conf[RTF]);
				strcat(RceFname,"\\FRCE");
				lung=strlen(RceFname);
				nFRce=n_rcefp-1;
				if(nFRce<0) 
               nFRce=max_rcefp-1;
		   	decnum(&RceFname[lung],2,-2,nFRce,0.) ;
				RceFname[lung+2]=0;
				strcat(RceFname,RTFEXT);
				if(canale!=-1) 
               close(canale);
	  			if((canale=open(RceFname,O_RDONLY|O_BINARY))!=-1)
					{
						offset=0l;
						retry=0;
					}
				TSuw=400;					// time out attesa Ack di riposta
				mmdia.a.condiz=0;
				enqueue(&pack);			// sistema collegato
		 	case	msgACK:
				if(canale!=-1) 			// esiste un file Rce ?
					numbyte=rbyte(canale,trasm.st,offset,l_rcestr);
				else numbyte=0;
				trasm.lun=numbyte;
				*((short*)&trasm.st[numbyte])=CRC16(&trasm.cod,trasm.lun+2);
		      ier=ModSend(LRce,TRce,numbyte+hea_trasm,&trasm) ;
				if(!numbyte || ier) 
               TSuw=FineTrasm(&canale,&mmdia,&pack);
				else 
               offset+=numbyte;
				break;
			case	msgNCK:
				if(++retry > max_retry) 
               TSuw=FineTrasm(&canale,&mmdia,&pack);
				else
					{
						if(ModSend(LRce,TRce,numbyte+hea_trasm,&trasm))
							FineTrasm(&canale,&mmdia,&pack);
					}
				break;
			}
		}
}
/*
	FineTrasm

	Routine che effettua le operazione di chiusura canale e invio
	diagnostica per segnalare la fine del collegamento con scc

	Parametri

	canale	short	*				canale file
	mmdia	   S_MDIA_R*			puntatore al messaggio di diagnostica
	pack		QUEUE_PACKET * 	puntatore al pacchetto invio messaggio

	Ritorno

	Valore timeout per attesa prossima richiesta
*/
FineTrasm (short * canale, S_MDIA_R * mmdia, QUEUE_PACKET * pack)
{
	if((*canale)!=-1) 
      close(*canale);  			// chiusura file
	*canale=-1;
	mmdia->a.condiz=1;								// comunicazione off line
	enqueue(pack);
	return(0);
}
