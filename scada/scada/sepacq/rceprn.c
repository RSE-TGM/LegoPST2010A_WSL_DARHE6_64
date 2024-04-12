/**********************************************************************
*
*       C Source:               rceprn.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:50:59 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: rceprn.c-3 %  (%full_filespec: rceprn.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Rceprn

	Task che stampa le registrazioni Rce e le memorizza su file
	E' in attesa di messaggi sulla coda c_rce

	Ritorno

	nessuno

      13 Febbraio 1995
         Stampa rce suddivisa per gruppo di acquisizione

*/
#include <stdlib.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>

#include "mesqueue.h"
#include "comunic.inc"
#include "sepdati.inc"
#include "print.inc"
#include "g2comdb.inc"
#include "messcada.inc"
#include "rceintesta.h"
#include "allar.inc"
#include "dconf.inc"
#include "pscserr.inc"
#include "diagnoan.inc"


extern long  off_f[] ;     /* definiti nel main mpscs */
extern short nbyte[] ;     /* come sopra */
extern short c_rce;			// coda
/*
		struttura per stampa segnalazioni Rce
*/
#define c_rcedata	2
#define c_rcemilli	3
#define c_armadio		6
#define c_nome		  10
#define c_desc		  24

typedef struct s_frce  {
			 HEA_STA hea;
			 char blank_0 ;
			 char blank_1 ;
			 long blank_2 ;
			 char blank_3 ;
			 char sep_0;
          char ora[c_rcedata];
          char sep_1 ;
          char min[c_rcedata];
          char sep_2;
          char sec[c_rcedata];
			 char	sep_3;
			 char milli[c_rcemilli];
			 char sep_4;
          char armadio[c_armadio];
			 char	sep_5;
			 char nome[c_nome];
			 char sep_6;
			 char	cat;
			 char sep_7;
          char desc[c_desc];
			 char sep_8;
			 char valore;
			 char sep_9;
			 char stato;
          short  crlf1;
          short  crlf2 ;
            } S_FRCE ;

typedef struct s_irce  {
			 char    stringa[max_rcest];
          short  crlf1;
          short  crlf2;
            } S_IRCE ;
rceprn()
{
	QUEUE_PACKET pack;

	S_STRCE mess;							// messaggio in coda
	short i;
	short lung;

	S_FRCE stam;					  // stampa messaggio
	S_IRCE stai;					  // stampa intestazione
	S_BRCE *pBrce;
	S_RCE   *pRce;
	char	  RceFname[FILENAME_MAX+1];
	S_SFILE mstampa;				  // messaggio richiesta stampa	 
	QUEUE_PACKET packs;			  // packet per invio messaggio

	char	  hstr[5];
	short	  n_ante, n_succ, n_inizio;

	pack.que=c_rce;
	pack.wto=0;
	pack.amsg=(char *) &mess;
	pack.flg=MSG_WAIT;

	packs.que=c_tabul;
	packs.wto=0;
	packs.amsg=(char *) &mstampa;
	packs.lmsg=sizeof(mstampa);
	packs.flg=MSG_WAIT;

	mstampa.lung=sizeof(S_SFILE);
   mstampa.richiesta=-1;            // stampante di default
	mstampa.mess=msfile;
/*
	Inizializzazione header messaggio
*/
	stai.crlf1=0x0D0A ;
	stai.crlf2=0x0D0A ;

	stam.hea.lung=sizeof(S_FRCE);
	stam.blank_0=0x20;
	stam.blank_1=0x20;
	stam.blank_3=0x20;
	stam.sep_0=' ';
	stam.sep_1=':';
	stam.sep_2=':';
	stam.sep_3=',';
	stam.sep_4=' ';
	stam.sep_5=' ';
	stam.sep_6=' ';
	stam.sep_7=' ';
	stam.sep_8=' ';
	stam.sep_9=' ';
	stam.crlf1=0x0D0A ;
	stam.crlf2=0x0D0A ;
	rcecan=0;

	while(1)
	{
		dequeue(&pack);
		switch (mess.mess)
		{
		case rceprnc:				// stampa continuata
         stam.hea.szvir=cunita(mess.rce.id,g1tipda);
			RceId(&mess.rce, &stam, "-RCE");
		break;
		case rceprnp:				// ordinamento e stampa perturbografica
			pBrce=&BuffRce[mess.gruppo];		// buffer precedente
			if(!pBrce->n)
			{
			 	BuffRce[mess.gruppo].f=ALLOCATO;					// libero risorsa
				break;
			}
			RceSort(pBrce,0);						// con compattamento
			strcpy(RceFname,conf[RTF]);
			strcat(RceFname,"\\FRCE");
			lung=strlen(RceFname);
		   decnum(&RceFname[lung],2,-2,n_rcefp,0.) ;
			RceFname[lung+2]=0;
			strcat(RceFname,RTFEXT);
			strcpy(mstampa.nome,RceFname);
	  		if((rcecan=open(RceFname,O_CREAT|O_WRONLY|O_BINARY|O_TRUNC,
				S_IREAD|S_IWRITE))==-1)
			{
					BuffRce[mess.gruppo].f=ALLOCATO;					// libero risorsa
				   pscserr(ERR_IO,TASK_RCE,ROU_PRN,0,SYS_CONT);
					break;
			}
			rceoffset=0;
/*
	ricerco evento sganciatore: e' il primo evento di categoria C
*/
			for(n_ante=0,pRce=pBrce->p;n_ante<pBrce->n;n_ante++,pRce++)
			{
				if(dbdatr[pRce->id] & mask_cC) break;
			}
			pRce=pBrce->p+n_ante;				// evento sganciatore
			dbadv[PFRCE+n_rcefp]=(float)pRce->giorno*10000.0+(float)pRce->ora*100.0+
				(float)pRce->minuti;
			bitset(&dbadf[PFRCE+n_rcefp],g2an_fz,0);
			RceIntesta(&stai, rce_testa, pRce, bGroupAcq[mess.gruppo].nome);
			n_inizio=max(0,n_ante-n_rceante);
			pRce=pBrce->p+n_inizio;
			for(i=n_inizio;i<n_ante;i++,pRce++)
				{
					decnum(hstr,4,-1,i+1-n_inizio,0. ) ;
					RceId(pRce, &stam, hstr);
				}
			RceIntesta(&stai, rce_sgancio, pRce, bGroupAcq[mess.gruppo].nome);
			n_succ=min(pBrce->n,i+n_rcesucc);
			for(;i<n_succ;i++,pRce++)
				{
					decnum(hstr,4,-1,i+1,0. ) ;
					RceId(pRce, &stam, hstr);
				}
			pBrce->n=0;
			pBrce->f=ALLOCATO;					// libero risora
			RceIntesta(&stai, rce_fine, pRce, bGroupAcq[mess.gruppo].nome);
			close(rcecan);
			rcecan=0;
/*
	incremento n. file Rce e richiedo la stampa del file preparato
	(messaggio al task tabul)
*/
			if((++n_rcefp)>=max_rcefp) n_rcefp=0;
			dbadv[PCRCE]=n_rcefp;
			enqueue(&packs);
			wrdb(g1tipad);
		break;
		}
	}
}
/*
	RceId

	Routine per la costruzione della stringa per la stampa
	di un singolo evento in formato rce

	Parametri

	S_RCE	* indirizzo pacchetto rce
	S_FRCE * indirizzo stringa stampa
  	char	*  stringa di al massimo 4 caratteri da inserire come primo
				elemento nella stringa di stampa

	Ritorno

	nessuno

*/
RceId(S_RCE *pRce, S_FRCE *stam, char *shea)
{
	long fileoff, tot;
	short filebyte;
	char	desc[rec_fdda];				// buffer descrittore punto
	short *pdbdatr;

	fileoff=off_f[g1tipda];
	filebyte=nbyte[g1tipda];

   memcpy(&stam->blank_2,shea,4);
/*
        inserisco ora giorno mese anno minuti e secondi
        sono i medesimi per tutti gli allarmi arrivati
*/
	decnum(stam->ora ,c_rcedata,-1,pRce->ora,0. ) ;
	decnum(stam->min ,c_rcedata,-1,pRce->minuti,0. ) ;
	decnum(stam->sec ,c_rcedata,-1,pRce->secondi,0. ) ;
	decnum(stam->milli ,c_rcemilli,-1,pRce->millisecondi,0. ) ;
	stam->sep_1=':';
	stam->sep_2=':';
	stam->sep_3=',';
	stam->sep_4=' ';
/*
        leggo il record dal file descrittore
*/
	tot=fileoff+(long)filebyte*(long)pRce->id;
	rbyte(fileno(fpp[fdde]),(short *)desc,tot,filebyte);
/*
        copio nome punto descrizione nel buffer per la stampa
*/
	strncpy(stam->nome,desc,c_nome) ;
	strncpy(stam->desc,&desc[c_nome],c_desc);
/*
		inserisco categoria, armadio e valore del punto
*/
	strncpy(stam->armadio,heafsvar[pRce->tipo].nome,c_armadio);
	if(pRce->valore) stam->valore='1';
	else stam->valore='0';
	if(pRce->stato) stam->stato='1';
	else stam->stato='0';
	pdbdatr=&dbdatr[pRce->id];
	if(*pdbdatr & mask_cA) stam->cat='A';
	else if(*pdbdatr & mask_cB) stam->cat='B';
	else stam->cat='C';

	if(rcecan)								// disco o stampa diretta ?
	{
		wbyte(rcecan,&stam->blank_0,rceoffset,stam->hea.lung-sizeof(HEA_STA));
		rceoffset=rceoffset+stam->hea.lung-sizeof(HEA_STA);
	}
	else
	{
//		invia(tpr_stringa,stam);
//		invia(tpr_reset,(char *) 0);
		invia(tpr_allarme,stam);
	}
	return(0);
}
/*
	RceIntesta

	Routine per la stampa dell' intestazione Rce

	Parametri

	S_IRCE * stringa per codifica intestazione
	flag	short	tipo di intestazione richiesta
	S_RCE  *	puntatore record evento sganciatore
   char *   stringa nome gruppo

	Ritorno

	nessuno

	25 Giugno 1993

   13 Febbraio 1995
      Inserimento parametro aggiuntivo stringa nome gruppo
      a cui si riferisce RCE
*/
RceIntesta(S_IRCE *stai, short flag, S_RCE *pRce, char * stGruppo)
{
	short lung;
	char  formfeed;
	short giorno, mese, anno;

	switch(flag)
		{
		case rce_testa:
			formfeed=0x0c;
			wbyte(rcecan,&formfeed,rceoffset,1);
			rceoffset++;
			memset(stai->stringa,'-',max_rcest);
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			memset(stai->stringa,' ',max_rcest);
			lung=strlen(rcest1)+strlen(stGruppo);
 			memcpy(&stai->stringa[(max_rcest-lung)/2],rcest1,strlen(rcest1));
 			memcpy(&stai->stringa[(max_rcest-lung)/2+strlen(rcest1)],stGruppo,
            strlen(stGruppo));
			
         wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			memset(stai->stringa,' ',max_rcest);
			anno=dbadv[db_anno];
			giorno=pRce->giorno;
			decgio(&giorno,&mese,anno);
			memcpy(&stai->stringa[10],rcedate,6) ;
			decnum(&stai->stringa[20],2,-1,giorno,0.) ;
			stai->stringa[22]='-';
			decnum(&stai->stringa[23],2,-1,mese,0.) ;
			memcpy(&stai->stringa[30],rcetime,5) ;
			decnum(&stai->stringa[40],2,-1,pRce->ora,0.) ;
			stai->stringa[42]=':';
			decnum(&stai->stringa[43],2,-1,pRce->minuti,0.) ;
			stai->stringa[45]=':';
			decnum(&stai->stringa[46],2,-1,pRce->secondi,0.) ;
			stai->stringa[48]=',';
			decnum(&stai->stringa[49],3,-1,pRce->millisecondi,0.) ;
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			memset(stai->stringa,' ',max_rcest);
			lung=strlen(rcest3);
 			memcpy(&stai->stringa[0],rcest3,lung);
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			memset(stai->stringa,'-',max_rcest);
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			break;
		case rce_sgancio:
			lung=strlen(rcest4);
			memset(stai->stringa,' ',max_rcest);
 			memcpy(&stai->stringa[(max_rcest-lung)/2],rcest4,lung);
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			break;
		case rce_fine:
			lung=strlen(rcest5);
			memset(stai->stringa,' ',max_rcest);
 			memcpy(&stai->stringa[(max_rcest-lung)/2],rcest5,lung);
			wbyte(rcecan,stai,rceoffset,sizeof(S_IRCE));
			rceoffset+=sizeof(S_IRCE);
			break;
		}
}	
