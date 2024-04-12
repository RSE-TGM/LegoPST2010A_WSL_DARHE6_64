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
/*-> invia

        la function invia provvede a scrivere fisicamente
        sul devices indicati dalla strategia di fail over

        tab_al int     per  allarme
                       per tabulato
							  per archivio
							  per stringa
        st  char *  vettore di cui fare l'output
        lung int n. caratteri

*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "mesqueue.h"

extern short qperif_00;

invia(tab_al,st)
S_FORAL *st ;
short tab_al ;
{
short ier ;
S_FIS *stpfis ;			 	/* stampante fisica selezionata 	*/	
S_LOG *stplog ;				/* stampante logica selezionata 	*/	
short i,j,k ;
short ind ;
short n_logica;
QUEUE_PACKET packs;
unsigned char *righe;
unsigned char *page;
short remote;					/* flag utilizzo linea remota		*/
short coda;
short linea;
/*
	reset stato stampanti utilizzate per attivita' non di libro
	giornale
*/
if(tab_al==tpr_reset)
{
	for(i=0;i<n_fis;i++) 
   {     
      stfis[i].stato=0;  
      if(stfis[i].flag!=tpr_allarme) stfis[i].flag=tpr_null; 
   }
	return(0);
}
remote=(tab_al & 0xFF00) >> 8 ;     // sposto su byte basso
tab_al=tab_al & 0x00FF;
if(remote)           // inviare sulla seconda board
   return(0);
else  coda=qperif_00;				// primo canale periferiche
/*
	in caso di utilizzo di linee remote utilizzo la tabella
	stremote
*/
if(remote)
   return(0);
else
{
/*
	inserisce in stplog[] il descrittore della stampante logica relativa agli
	allarmi o ai tabulati a seconda del valore di tab_all.
*/
	if(tab_al==tpr_allarme || tab_al==tpr_stringa) {
            stplog=&stloga[0];
            n_logica=n_loga;
           }
	else    { 
            stplog=&stlogt[0];
            n_logica=n_logt;
           }
	if(tab_al==tpr_allarme_2) tab_al=tpr_allarme;
}

for (i=0;i<n_logica;i++,stplog++)
{
/*
        verifico a quale stampante fisica indirizzare l'I/O
*/
   for(j=0;j<n_device;j++)
	{
  	   ind=stplog->indice[j];
/*
        se il device non e' definito non eseguo nessuna operazione
*/
	   if(ind <0 ) break ;
     	stpfis=&stfis[ind] ;
/*
        se il device e` stato messo fuori servizio non eseguo
        nessuna operazione
*/
      if(bitvalue(stpfis->dig,g2di_sl)) continue;
/*
   se il device e' occupato da una tabulato o altro e devo
   stampare il libro giornale attendo fino al 
   massimo 2 minuti
*/
//     	if(stpfis->stato && (tab_al==tpr_allarme))
     	if(stpfis->stato && (tab_al!=stpfis->flag))
      {
/*
   ciclo attesa stampante libera per allarmi
   attendo al massimo 2 minuti con wai di due secondi
*/
         for(i=0;i<60;i++)  
         {
            wai(40);
            if(!stpfis->stato) break;    
         }
         if(i==60) continue;                 // non si e' liberata
       }    
		if(tab_al != tpr_allarme) stpfis->stato=1;
      if(remote) linea=stpfis->linea | 0x10;
      else  linea=stpfis->linea;
/*
	scelgo il contatore di riga e di pagina da utilizzare in caso di
	libro giornale o attivita' generiche (archivi o elenchi)
*/
		  if(tab_al==tpr_allarme)
		  {	page=&stplog->page_a;	righe=&stplog->righe_a; }
		  else
		  {	page=&stplog->page_g;	righe=&stplog->righe_g; }
/*
        se e` variato il device su cui scrivere oppure passo
		  da un tipo di stampa ad un altro ripeto l'intestazione 
*/
		  if((stpfis->flag != tab_al) || (j!=stplog->prev))
		  {
		  		switch(tab_al)
				{
				case tpr_allarme:
   				(*page)++;
	      		(*righe)=max_righe ;
					intesta(coda,mstal,linea,*page);
					break;
				case tpr_stringa:
					break;
				case tpr_archivio:
			  		*page=1; 					/* reset n. pagina	*/
			  		intesta(coda,mstar,linea,*page);
					*righe=max_righe;
					break;
				case tpr_elenco:
			  		*page=1; 					/* reset n. pagina	*/
			  		intesta(coda,minel,linea,*page);
					*righe=max_righe;
					break;
				}
				goto SCRIVI;
		  }
/*
        se e' stato superato il num. max di righe per pagina
        scrivo l'intestazione
*/
      if(!(*righe) && (tab_al!=tpr_tabulato))
			{
   		*righe=max_righe ;
   		(*page)++;
			switch(tab_al)
			{
				case tpr_archivio:
					intesta(coda,mstar,linea,*page);
					break;
			   case tpr_allarme:
	  		   	intesta(coda,mstal,linea,*page);
					break;
				case tpr_elenco:
			  		intesta(coda,minel,linea,*page);
					break;
		   }
		 }
SCRIVI:
		stpfis->flag=tab_al;
		stplog->prev=j;
     	if(linea == fis_disk) stdisk(&st->blank_1,st->hea.lung-sizeof(HEA_STA),si_fine);
     	else
		{
			packs.flg=MSG_WAIT;
		   packs.wto=0;
		   packs.amsg=(char*) st;
	   	packs.lmsg=st->hea.lung;
			st->hea.linea=linea;
			packs.que=coda+linea;
	   	enqueue(&packs);
		}
	 	if(tab_al!=tpr_tabulato) (*righe)--;
		break;
	  }
/*
	se non e' stato trovato neppure un device non off line forzo
	l'eventuale prossima intestazione
*/
  	  if(j>=n_device) stplog->prev=-1;
}
}
