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
	-> GesRep.c
	
	Rountine di gestione dei reperibili.
	Prepara ed accoda il messaggio per il TASKREP.
	
	Parametri:				short tipo		il tipo del punto da gestire (aa, ad, etc.)
							short indDB		l'indice nel data base
	
	Codici di errore:		1	OK
                        	0  	KO
	
	Data di creazione:		12.5.1995
	Autore:					E.L.

   27 Luglio 1995
      Corretta gestione voce variabile non definita
*/

#include <string.h>
#include <stdio.h>

#include "defpub.h"
#include "gesrep.h"
#include "dconf.inc"
#include "g1tipdb.inc"
#include "g0strdb.inc"
#include "g2ptrdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "tipal.inc"

extern DB_HEADER h_db;
extern short c_rep;

// Tabella per le associazioni
				         // rientro, emissione
char svVoci[max_st][2]={
				{  ST0,	ST1},	// var_dig 		 0
				{	ST0, 	ST1},	// dia_sys 		 1
				{	 -1,	 -1},	// mod_st  		 2
				{	 -1,	 -1},	// com_ok  		 3
				{RFLHH, FLHH},	// sic_al  		 4	
				{RFLLL, FLLL},	// sic_ba  		 5
				{  RFLH,	FLH},	// con_al  		 6
				{  RFLL,	FLL},	// con_ba  		 7
				{	 -1,	 -1},	// pun_forz 	 8
				{	RFA,	 FA},	// non_att 		 9
				{	 -1,	 -1},	// fuori_scan 	10
				{	 -1,	 -1},	// gr_var   	11
				{	 -1,	 -1},	// range_al 	12
				{	 -1,	 -1},	// range_ba 	13
				{	 -1,	 -1},	// ch_fser  	14
				{	 -1,	 -1},	// giun_fred 	15
				{	 -1,	 -1},	// mis_norm 	16
				{	 -1,	 -1},	// emi_com   	17
				{	 -1,	 -1},	// non_esi   	18
				{	 -1,	 -1},	// al_blank  	19
				{	 VS,	 VS},	// var_org  	20
				{	 CF,	 CF},	// com_fall 	21
				{	 -1,	 -1},	// prot_fall 	22
				{	 -1,	 -1},	// com_stop  	23
				{	 -1,	 -1},	// com_pas  	24
				{	 -1,	 -1},	// mod_hs   	25
				{	 -1,	 -1},	// mod_hc   	26
				{	 -1,	 -1},	// mod_ls   	27
				{	 -1,	 -1},	// mod_lc   	28
				};

short GestRep(short tipo, short indDB, short rientro, short call)
{
	// Variabili locali
	short indREP; 			// indice del reperibile
	short i;
   long lDTMF;
	S_MGESREP m;
	char chBuffer[lBuffer];
   char szDBS1[g0lunst];
   char szDBS2[g0lunst];
   QUEUE_PACKET pack;

   if(!sys_master) return 0;       // solo sistema master

   // Inizializzazioni
   pack.que=c_rep;
   pack.wto=-1;
   pack.flg=MSG_NOWAIT;
   pack.amsg=(char*) &m;

	memset(m.mess,0,lBuffer);
	
	// Calcola l'indice del reperibile
	switch(tipo)
	{
		// analogici acquisiti
		case g1tipaa:
			indREP=*(repaa+indDB);
		break;

		// analogici calcolati standard
		case g1tipas:
			indREP=*(repas+indDB);
		break;
			
		// analogici calcolati non standard
		case g1tipac:
			indREP=*(repac+indDB);
		break;
			
		// analogici di diagnostica
		case g1tipad:
			indREP=*(repad+indDB);
		break;
			
		// digitali acquisiti
		case g1tipda:
			indREP=*(repda+indDB);
		break;
			
		// digitali  calcolati standard
		case g1tipds:
			indREP=*(repds+indDB);
		break;
			
		// digitali  calcolati non standard
		case g1tipdc:
			indREP=*(repdc+indDB);
		break;
			
		// digitali  di diagnostica
		case g1tipdd:
			indREP=*(repdd+indDB);
		break;
			
		// organi
		case g1tipor:
			indREP=*(repor+indDB);
		break;
			
		default:
			return 0;
	}
	
	// Il punto non ha trattamento "reperibile"
	if(indREP==FILPATT)
		return 0;
		
	// Altrimenti compone il messaggio
	
	// Intestazione
	sprintf(m.mess,"$C;%s",punrep[indREP].tag);

	// Voci fisse
	for(i=0;i<max_vfisse;i++)
	{
		if(punrep[indREP].vfisse[i]==FILPATT)
			continue;
		
		memset(chBuffer,0,lBuffer);
		sprintf(chBuffer,";%hd",punrep[indREP].vfisse[i]);
		strcat(m.mess,chBuffer);
	}
	
	// Voci variabili
	i=svVoci[call][rientro];

   // Tipo di allarme non gestito
   if(i==-1)
      return 0;

	if(punrep[indREP].vvaria[i]!=FILPATT)
	{
		memset(chBuffer,0,lBuffer);
		sprintf(chBuffer,";%hd",punrep[indREP].vvaria[i]);
		strcat(m.mess,chBuffer);
	}
   else
      return 0;

	// Severita'
	memset(chBuffer,0,lBuffer);
	sprintf(chBuffer,";S%c",punrep[indREP].severita);
	strcat(m.mess,chBuffer);
	
   indREP=punrep[indREP].specrep-1;

	// N. di chiamate
	memset(chBuffer,0,lBuffer);
   sscanf(dbstv+(svrep[indREP].nchiam*g0lunst),"%hd%s",&i,chBuffer);
   if(chBuffer[0])
   	strcat(m.mess,";NR0");
   else
   {
	   sprintf(chBuffer,";NR%hd",i);
   	strcat(m.mess,chBuffer);
   }

	// Intervallo di chiamata
	memset(chBuffer,0,lBuffer);
   sscanf(dbstv+(svrep[indREP].interv*g0lunst),"%hd%s",&i,chBuffer);
   if(chBuffer[0])
   	strcat(m.mess,";IR000");
   else
   {
   	sprintf(chBuffer,";IR%03d",i);
	   strcat(m.mess,chBuffer);
   }
	
	// Codice di risposta
	memset(chBuffer,0,lBuffer);
   sscanf(dbstv+(svrep[indREP].cod*g0lunst),"%ld,%s",&lDTMF,chBuffer);
   if(chBuffer[0] || !strlen(dbstv+(svrep[indREP].cod*g0lunst)))
	   strcat(m.mess,";");
   else
   {
	   sprintf(chBuffer,";%ld",lDTMF);
	   strcat(m.mess,chBuffer);
	}

   // Numeri telefonici
	for(i=0;i<max_elesqu;i++)
	{
   	memset(chBuffer,0,lBuffer);
		sscanf(dbstv+(svrep[indREP].npref[i]*g0lunst),"%s",szDBS1);
      sscanf(dbstv+(svrep[indREP].ntel[i]*g0lunst),"%s",szDBS2);
		sprintf(chBuffer,";%s%s",szDBS1,szDBS2);
      if(strlen(chBuffer)>1)
		   strcat(m.mess,chBuffer);
	}
	
   // 0D0A
	strcat(m.mess,"\r\n");

   // Invia, ed incremento n. messaggi inviati
   pack.lmsg=strlen(m.mess)+sizeof(m.count);
   m.count=0;
   if(cont_repall < max_repall)
   {
      enqueue(&pack);
      cont_repall++;
   }   
	return 1;
}

