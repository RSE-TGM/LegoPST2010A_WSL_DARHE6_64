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
	Septestn.c

	Routine per la diagnostica dello stato di un nodo della rete
	bitbus.
	Se un armadio e' off line su ambedue le reti tutte le misure
	vengono poste fuori attendibilita'

	Parametri

	indice	short	n. del nodo
	stato		unsigned char	stato del nodo

	Ritorno

	nessuno

	19	Aprile 1993

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesprocv.inc"
#include	"mesqueue.h"
#include "diagnodi.inc"
#include "sepdati.inc"
#include "sepdiag.inc"

extern short debsamp;		// flag per emissione non attendibilita'

testnodi(indice,stato)
short indice;
unsigned char stato;
{
short prog, allarme;
S_MDIA mess;
S_MRDAG tdig;
QUEUE_PACKET pack;
unsigned char *pstnodo;					//	puntatore stato digitale diagnostica
unsigned char valore;
unsigned char mask;
short i;
char f_mrdag;
short nConn;								// n. connessioni del nodo

/*
	verifico correttezza indice nodo
	Determino l'indice del digitale di diagnostica associato
	(rete A, rete B e modalita' di funzionamento)
*/
if(indice > n_tot_nodi) return(0);
pstnodo=&snodi[indice].stato[0];
nConn=snodi[indice].stato[n_digretA] + snodi[indice].stato[n_digretB];

switch (indice)					// seleziono indice allarme diagnostica
{
  	case nodo_stop_1 :
   	allarme=stastopa;
		if(stato & mask_msa) bitset(&dbdd[allarme],g2di_au,1);
		else bitset(&dbdd[allarme],g2di_au,0);
		if(stato & mask_msb) bitset(&dbdd[allarme],g2di_st,1);
		else bitset(&dbdd[allarme],g2di_st,0);
	break;
  	case nodo_stop_2 :
   	allarme=stastopb;
		if(stato & mask_msa) bitset(&dbdd[allarme],g2di_au,1);
		else bitset(&dbdd[allarme],g2di_au,0);
		if(stato & mask_msb) bitset(&dbdd[allarme],g2di_st,1);
		else bitset(&dbdd[allarme],g2di_st,0);
	break;
  	default:
   	if(indice>=nodo_armadi)
			{
			 allarme=staper0a+(indice-nodo_armadi)*3;
			 snodi[indice].Rce=0;				// variato stato nodo fine sequenza Rce	
			}
	   else return(0);
  	break;
}
prog=0;					// indice inserimento allarme nel messaggio
mask=mask_sta;			// esame rete A
f_mrdag=0;				// flag richiesta digitali globali
/*
	ciclo esame bit relativi a rete A e rete B e modalita' di funzionamento
	mask_sta, mask_stb, mask_mod
*/
for(i=0;i<n_dignodi;i++,allarme++,pstnodo++)
{
/*
	verifico variazione comunicazione sulla rete,
	f_mrdag viene posto = 1 se il nodo e' andato line su
	una delle linee bitbus
*/
   valore=stato & mask;
  	if(valore) valore=1;					// 0 o 1 on line off line
	if(valore != (*pstnodo))
	{
		mess.a[prog].allarme=allarme;
	   mess.a[prog].condiz=valore;
		*pstnodo=valore;					// aggiorno valore
   	prog++;
/*
	Setto il flag di richiesta digitali quando divento master
	o on line su una delle reti (connessioni off line presenti = 2)
*/
		if(!valore && (mask!=mask_mod) && (nConn==2))
		{nConn=1;	f_mrdag=1;}							// on line con 0 connessioni
		if(valore && (mask==mask_mod)) f_mrdag=1;	// master
   }
	if(mask==mask_sta) mask=mask_stb;
	else mask=mask_mod;
}
if(prog)					//	almeno una variazione ?
{
	mess.indice=mdia;
	mess.nodo=0;
	pack.wto=200;
	pack.flg=MSG_WAIT;
	pack.que=c_mmii;
	pack.amsg=(char*)&mess;
	pack.lmsg=h_dia+prog*sizeof(S_ALDIA);
	enqueue(&pack);

	if(indice >= nodo_armadi)		// se si tratta di nodo armadio Sepa
	{
/*
   Se il nodo e' un nodo master di armadio e se e' andato off-line
	su ambedue le reti pongo fuori attendibilita' tutte le misure associate
   (l'allarme viene generato in base a debsamp)
*/
		if((stato & (mask_mod+mask_sta+mask_stb)) == (mask_mod+mask_sta+mask_stb))
			{
				armfa((indice-nodo_armadi)/2,debsamp);
			}
/*
   Testo se e' richiesto l'invio del messaggio aggiornamento
	globale digitali
*/
		else if (f_mrdag && sys_master)  
		{
			tdig.hea.addr_nodo=indice;
			tdig.hea.mess=mrdag;
			tdig.hea.prov=cl_scada;
			tdig.hea.dest=cl_dac;
			tdig.point=POINT_NULL;
			pack.que=c_ut_tx;
			pack.amsg=(char*)&tdig;
			pack.lmsg=sizeof(S_MRDAG);
			enqueue(&pack);
			tra(mbox_inet,1);
		}
	}		
}
}


															                            
