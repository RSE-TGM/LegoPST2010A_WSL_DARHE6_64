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
#include <stdio.h>
/* 
		la routine Inetmast deve essere chiamata in caso di commutazione
		slave->master. Resetta diagnostica nodi (tutti off line) e richiede
		il nuovo stato delle connessioni
		
		Parametri  nessuno

		Ritorno	  nessuno

		14 Marzo 1994
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "diagnodi.inc"
#include "sepdati.inc"
#include "sepdiag.inc"

inetmast()
{
QUEUE_PACKET 	pack;
HEASCA hea;
short i;

scd();										// riinizializzazione diagnostica
for(i=0;i<n_tot_nodi;i++)				// con blocco aggiornamento
{
     snodi[i].stato[n_digretA]=1;
     snodi[i].stato[n_digretB]=1;
     snodi[i].stato[n_digmodF]=0;
}
sce();
/*
	richiesta stato della rete
*/
pack.wto=0;
pack.flg=MSG_WAIT;
pack.amsg=(char*)&hea;
pack.que=c_ut_tx;
pack.lmsg=sizeof(hea);
/*
	invio la richiesta per conoscere lo stato della rete
*/
hea.addr_nodo=nodo_test_rete;
hea.prov=cl_scada;
hea.dest=cl_scada;
hea.mess=inet_stato;
enqueue(&pack);

tra(mbox_inet,1);

}
