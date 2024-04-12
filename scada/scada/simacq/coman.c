/**********************************************************************
*
*       C Source:               coman.c
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:04:14 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: coman.c-3 %  (%full_filespec: coman.c-3:csrc:2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   COMAN.C
		routine per l'invio dei comandi digitali a simulatore.
		In ingresso viene fornito il puntatore in dbs.
   

   (Simulatore ENEL-Piacenza)

   12.01.93  -  Rev. 1.00  -  GM.Furlan

   25 Marzo 1995 Fc Porting a 32Bit
*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "comunic.inc"
#include "mesqueue.h"
#include "g2comdb.inc"
#include "simdia.inc"      // indirizzi in DB dei digitali di diagnostica per simulatore
#include "simmsg.inc"      // strutture messaggi da simulatore
#include "dconf.inc"

extern short c_comani, c_comano;

coman(puntdb)
unsigned puntdb ;
{

short ier;
QUEUE_PACKET packo;     // pacchetto in trasmissione
QUEUE_PACKET packi;     // pacchetto in ricezione

SM_COM msgdo;           // messaggio comando verso simulatore
SM_DIAGNO msgrc;        // messaggio di diagnostica ricevimento comando 
FILE *fpfdcom;          // puntatore file descrittore comandi 
char fnome[FILENAME_MAX+1];         // nome file 
S_FDCOM_SIM rec;        // record file descrittore comandi 

// se supervisore non in RUN, comandi disabilitati
if (bitvalue(&dbdd[sscrun],g2di_sl))  return(0);
   
// inizializzazione coda di ricezione (per ACK)
packi.que=c_comani;

packi.flg=MSG_WAIT;
packi.wto=80;             // time out di 4 sec
packi.amsg=(char *)&msgrc;

/*
	lettura descrittore comando
*/
// open file descrittore comando (file FDCOM.RTF)
strcpy(fnome,conf[RTF]);
strcat(fnome,FDCOM);
fpfdcom=fopen(fnome,"rb+");
// posizionamento e lettura record file
rbyte(fileno(fpfdcom),&rec,(long)(puntdb)*(long)rec_fdcom_sim,rec_fdcom_sim);
// close file descrittore comando
fclose(fpfdcom);

/*
   messaggio invio comando 
*/
msgdo.hea.nodo=0;
msgdo.hea.mess=COMDO;
msgdo.pcom=rec.puntda;
msgdo.val=(float)rec.onoff;

// accodamento in trasmissione
packo.que=c_comano;

packo.wto=0;
packo.flg=MSG_WAIT;
packo.lmsg=sizeof(SM_COM);
packo.amsg=(char*)&msgdo;
enqueue(&packo);

// gestione organi
if((rec.organo != -1)||(rec.abili))             // se organo associato
                                                // o in caso di stampa
{
        simsetcom(&rec);
}

// scodamento ACK o NACK
ier=dequeue(&packi);
/*
   se nessun messaggio di ritorno o ricezione comando fallita,
   setting digitale di "comando fallito"
*/
if (ier || msgrc.tipo==NOCOM)
{
   bitset(&dbdd[sscnocom],g2di_sl,1);
   simvardd(sscnocom,1);          // allarme variazione stato digitale 
}
return(0);   
}



