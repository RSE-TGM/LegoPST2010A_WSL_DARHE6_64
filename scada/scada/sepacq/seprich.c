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
	Seprich.c

	La routine ad ogni chiamata richiede la data ad uno dei nodi
	Sepa on line e i digitali variati.
	Per la scansione ciclica dei nodi utilizza la variabile in
	common scan_arm per scorrere i nodi e scan_time per decrementare
	il timer tra una richiesta e la successiva.
	Per interrompere la richiesta dei digitali globali e' sufficiente
	porre scan_time=-1

	Parametri
	
	nessuno

	Ritorno

	nessuno

	22 Aprile 1993
*/
#include "mesqueue.h"
#include "comunic.inc"
#include "sepdati.inc"
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"

seprich()
{
QUEUE_PACKET pack, packora;
S_MRTIME mtime;					// richiesta data
S_MRDAG  rdig;						// richiesta digitali globali
S_SEPNODI *psnodiA, *psnodiB;
short nodo, nodoS;
short i;
S_MALLA malla;

if(!sys_master) return(0);
/*
	ricerco il primo nodo collegato verificando che sia in linea su una
	delle due reti.
	Se il nodo ha ricevuto una data invalida non viene considerato a meno
	che non sia l'unico a disposizione. In questo caso se tutti gli armadi
	sono o off line o con Fa settato viene cancellata la Fa
*/
nodoS=0;
psnodiA=&snodi[nodo_armadi];
for(nodo=nodo_armadi;nodo<n_tot_nodi;nodo++,psnodiA++)
{
	if(psnodiA->stato[n_digmodF])			// master
	{
		if(!psnodiA->stato[n_digretA] || !psnodiA->stato[n_digretB])
		{
			if(!psnodiA->Fa) goto INVIO;		// nodo Ok
			else nodoS=nodo;						// data precedente fuori attendibilita'
		}
	}
}
if(!nodoS) return(0);				// nessun nodo collegato
else nodo=nodoS;						// unico a disposizione nodo con Fa 

psnodiA=&snodi[nodo_armadi];		// reset di tutte le FA
for(nodoS=nodo_armadi;nodoS<n_tot_nodi;psnodiA->Fa=0,nodoS++,psnodiA++);

INVIO:

if (dbadv[PRICORA] != nodo)				// segnalo nodo a cui inviato richiesta ora
{
	dbadv[PRICORA]=nodo;
   malla.ertr=0x80+1;			// solo stampa 
	malla.ext=g1tipad;
	malla.punt=PRICORA;
	malla.sprec=mis_norm;
	malla.satt=al_blank;
	malla.sogl1=-1;
	malla.sogl2=-1;
	packora.wto=0;
	packora.que=c_visall;
	packora.flg=MSG_WAIT;
	packora.amsg=(char*)&malla;
	packora.lmsg=sizeof(S_MALLA);
	enqueue(&packora);
}
_RicOra(nodo);

if(scan_time==-1) return(0);			// interrotta la scansione
if(!scan_time--)							// invio messaggio richiesta digitali globali
{
	for(i=0;i<sp_armadi;i++)
	{
 		if((++scan_arm) == sp_armadi) scan_arm=0;
		if(svinarp[scan_arm])							// nodo definito ?
		{
			nodo=scan_arm*2+nodo_armadi;
			psnodiA=&snodi[nodo];						// da armadio a nodo fisico
			psnodiB=psnodiA+1;							// master e slave
																// nodo in linea ?									
			if(!psnodiA->stato[n_digretA] || !psnodiA->stato[n_digretB] ||
	   	!psnodiB->stato[n_digretA] || !psnodiB->stato[n_digretB])
			{
				rdig.hea.mess=mrdag;
				rdig.hea.prov=cl_scada;
				rdig.hea.dest=cl_dac;
				rdig.hea.addr_nodo=nodo;
				rdig.point=POINT_NULL;
				pack.que=c_ut_tx;
				pack.flg=MSG_WAIT;
				pack.wto=40;
				pack.lmsg=sizeof(S_MRDAG);
				pack.amsg=(char*) &rdig;
				enqueue(&pack);
			}
			break;											// interrompo ciclo ricerca
		}
	}
   scan_time=10/n_confar;								// ogni 10 minuti tutti gli armadi
}
tra(mbox_inet,1);
}
