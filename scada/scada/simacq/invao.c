/**********************************************************************
*
*       C Source:               invao.c
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:05:06 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: invao.c-3 %  (%full_filespec: invao.c-3:csrc:2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   INVAO.C
		Routine per l'invio dei comandi analogici a simulatore.
		In ingresso viene fornito il puntatore in dbs  e il valore
		float da inviare.
   
   (Simulatore ENEL-Piacenza)

   12.01.93  -  Rev. 1.00  -  GM.Furlan

   27 Marzo 1995 Fc Porting a 32 Bit
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

// External function declarations
extern int bitvalue(short *, short);
extern int rbyte(int, void *, long, int);
extern void bitset(short *, short, short);
extern void simvardd(short, short);

extern short c_comani, c_comano;

int invao(puntdb,valore)
unsigned puntdb ;
float valore;
{

short ier;
QUEUE_PACKET packo;     // pacchetto in trasmissione
QUEUE_PACKET packi;     // pacchetto in ricezione

SM_COM msgao;           // messaggio comando analogico verso simulatore
SM_DIAGNO msgrc;        // messaggio di diagnostica ricevimento comando 
FILE *fpfdeao;          // puntatore file descrittore comandi analogici
char fnome[FILENAME_MAX+1];         // nome file 
S_FDEAO_SIM rec;        // record file descrittore comandi analogici

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
// open file descrittore comando (file FDEAO.RTF)
strcpy(fnome,conf[RTF]);
strcat(fnome,FDEAO);
fpfdeao=fopen(fnome,"rb+");
// posizionamento e lettura record file
rbyte(fileno(fpfdeao),&rec,(long)(puntdb)*(long)rec_fdeao_sim,rec_fdeao_sim);
// close file descrittore comando
fclose(fpfdeao);

/*
   messaggio invio comando analogico
*/
msgao.hea.nodo=0;
msgao.hea.mess=COMAO;
msgao.pcom=rec.puntaa;
msgao.val=valore;

// accodamento in trasmissione
packo.que=c_comano;

packo.wto=0;
packo.flg=MSG_WAIT;
packo.lmsg=sizeof(SM_COM);
packo.amsg=(char*)&msgao;
enqueue(&packo);

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




