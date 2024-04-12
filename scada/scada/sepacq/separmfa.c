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
   la routine armfa pone fuori attendibilta' tutti i punti
   associati ad un armadio sepa

   la routine viene chiamata quando un armadio va off line
	L'allarme di fuori attendibilita' viene generato in base
	al valore del parametro flag.
 	La fuori attendibilita' non viene segnalata se il punto e'
	forzato o fuori scansione.

 	Parametri

   armadio  short n. dell'armadio off line a partire da 0
   flag     short =0 non generare l'allarme
                  =1 generare l'allarme


	Ritorno
	
	nessuno

	19	Aprile 1993
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "mesqueue.h"
#include "sepdati.inc"

armfa(armadio,flag)
short armadio;
short flag;
{
short i;
short point;			// indice logico in data base
short *psvin;			// puntatore allo svincolo
short vflag;    		// flag del data base
short *pflag;    		// puntatore ai flag del data base
short trat;
S_MALLA  ana;
S_TRATG  dig;
QUEUE_PACKET packana, packdig;
short dimsvin;			// dimensione svincolo armadio

psvin=svinarp[armadio];
if(!psvin) return(0);    // armadio non configurato
dimsvin=heafsvar[armadio].l_punto;		// n. massimo punti associati all'armadio

packana.flg=MSG_WAIT;      // parametri accodamento allarmi analogici
packana.wto=0;
packana.lmsg=sizeof(S_MALLA);
packana.amsg=(char*)&ana;
packana.que=c_visall;

packdig.flg=MSG_WAIT;      // parametri accodamento allarmi analogici
packdig.wto=0;
packdig.lmsg=sizeof(S_TRATG);
packdig.amsg=(char*)&dig;
packdig.que=c_digor;

/*
	ciclo scansione tabelle punti, possono essere sia analogici
	che digitali
*/

ana.ext= g1tipaa ;                                   
ana.satt=non_att;         
ana.sprec=mis_norm ;

dig.stato= 1;
dig.mess= mfadi ;         
dig.ext= g1tipda ;
/*
	ciclo scansione punti dell'armadio
*/
for(i=0;i<dimsvin;i++,psvin++)
{
   if((*psvin) == -1) continue;        // punto non configurato
	point=(*psvin) & (~mask_tpun);
	if((*psvin) & mask_tpun)			// test analogico o digitale ?
	{
		vflag=dbda[point];
		pflag=&dbda[point];
	   if(vflag & mask_dfa) continue;   // gia' FA
	   bitset(pflag,g2di_afa,1);                  // FA fisica
      if((vflag & mask_dfz) || (vflag & mask_dfs)) continue;
      bitset(pflag,g2di_fa,1);
	  	if (!flag)	continue;
   	dig.indice=point ;
	   enqueue(&packdig) ;
	}
	else											// analogico
	{
		vflag=dbaaf[point];
   	if((vflag & mask_afa) || (vflag & mask_afz) || (vflag & mask_afs)) continue;     // gia' FA o FS o FZ     
	   bitset(&dbaaf[point],g2an_fa,1);
  		if (!flag)	continue;				// abilitazione allarme ?
	   ana.punt=point ;
   	trat=dbaaal[point].tr_bdm;
   	ana.ertr=((trat & M_LSEVA)>>6) + (trat>>12) + 0x80;  
      enqueue(&packana) ;
	}
}
return(0);
}
