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
/*->
      Invia

        La function invia provvede ad esaminare il tipo stringa passato
        come parametro (tab_al):

        -   se si tratta di allarme, esamina hea.szvir ed invia la
            stringa a tutti i device virtuali in cui e' abilitata

        -   se si tratta di tabulato e hea.szvir non e' definito, invia
            alla stampante virtuale assegnata di default ai tabulati

        -   se si tratta di elenco o archivio o altro invia alla
            stampante virtuale assegnata di default ai tabulati

        -   se si tratta di stringa si comporta come nel caso di allarme

   Parametri:

        tab_al int     per  allarme
                       per tabulato
							  per archivio
							  per stringa

        st  char *  vettore di cui fare l'output

        lung int n. caratteri

   Ritorno

         nessuno

   4 Settembre 1995
   Inserita gestione per stampanti su server remoto

*/
#include <osf1.h>
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "mesqueue.h"
#include "print.inc"
#define _PUBLIC 0
#include "defpub.h"
#include "virtinv.h"
#include "diagnodi.inc"

// External function declarations
extern int bitvalue(short *, short);
extern void wai(int);
extern void intesta(int, int, int, int);
extern void stdisk(void *, int, int);

extern short qperif_00;
extern short c_prnrem0;          // coda stampanti remote

/*
   StInvia

      Data la stampante virtuale da utilizzare, provvede ad inviare
      il messaggio sulla stampante fisica attualmente on line.

      Il form feed viene automaticamente inserito se:

            . la stampante era stata utilizzata per altri tipi di
              stampa
            . era andata off line
            . e' stato raggiunto il numero massimo di righe

      Parametri
         
         short    tipo di stampa (libro giornale,...,ecc)
         short    indice della stampante virtuale
         S_PVIRT*  indirizzo descrittore della stamante virtuale
         S_FORAL* stringa da stampare

      Ritorno

         nessuno

*/
void stinvia(short tab_al, short indvirt, S_PVIRT* stplog, S_FORAL* st)
{
short j, i, ind, linea;
S_PFIS *stpfis;
unsigned char *page, *righe;
QUEUE_PACKET packs;
short coda;

NLbgVirt=indvirt;
/*
        verifico a quale stampante fisica indirizzare l'I/O
*/
for(j=0;j<n_DevFis;j++)
{
   ind=stplog->indice[j];
	if(ind <0 ) break ;        // non definito

   stpfis=&fisdev[ind] ;
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
   linea=stpfis->linea;
   if(stpfis->remota)
      coda=c_prnrem0;			 
   else
      coda=qperif_00;			 
/*
	scelgo il contatore di riga e di pagina da utilizzare in caso di
	libro giornale o attivita' generiche (archivi o elenchi)
*/
   if(tab_al==tpr_allarme)
	{
      page=&stplog->page_a;
      righe=&stplog->righe_a;
   }
	else
	{
      page=&stplog->page_g;
      righe=&stplog->righe_g;
   }
/*
    se e` variato il device su cui scrivere oppure passo da un tipo di
    stampa ad un altro oppure e' variata la stampante virtuale ripeto
    l'intestazione 
*/
   if((stpfis->flag != tab_al) || (j!=stplog->prev) || (stpfis->nvirt!=indvirt))
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
   }
/*
    se e' stato superato il num. max di righe per pagina
    scrivo l'intestazione
*/
   else if(!(*righe) && (tab_al!=tpr_tabulato))
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
/*
   invio a drive stampante fisica per scrittura stampa
*/
	stpfis->flag=tab_al;
	stpfis->nvirt=indvirt;
	stplog->prev=j;
  	if(linea == fis_disk)
   {
      stdisk(&st->blank_1,st->hea.lung-sizeof(HEA_STA),si_fine);
   }
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
if(j>=n_DevFis) stplog->prev=-1;

return;
}

int invia(short tab_al, S_FORAL *st)
{
S_PVIRT *stplog ;	
short i;
/*
	reset stato stampanti utilizzate per attivita' non di libro
	giornale
*/
if(tab_al==tpr_reset)
{
	for(i=0;i<n_fis;i++) 
   {     
      fisdev[i].stato=0;  
      if(fisdev[i].flag!=tpr_allarme) fisdev[i].flag=tpr_null; 
   }
	return(0);
}
/*
    esame tipo di stringa
*/
if(tab_al==tpr_allarme_2) tab_al=tpr_allarme;
switch (tab_al)
{
   case tpr_allarme: case tpr_stringa:
      if(st->hea.szvir==-1) st->hea.szvir=0;
      stplog=&virtprn[0];
      for(i=0;i<n_virt_lbg;i++,stplog++)
      {
         if(stplog->abzon & (1 << st->hea.szvir)) stinvia(tab_al,i,stplog,st);
      }
   break;
   default:
      if(st->hea.szvir==-1) st->hea.szvir=gDefTabPrn-1;
      stinvia(tab_al,st->hea.szvir,&virtprn[st->hea.szvir+n_virt_lbg],st);
   break;
}
return(0);
}
