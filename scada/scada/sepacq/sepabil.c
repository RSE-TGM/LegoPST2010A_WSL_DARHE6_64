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
	Sepabil

	La routine sepabil abilita i nodi della rete inet con
	armadi Sepa
	
	Parametri

	nessuno

	Ritorno

	nessuno

	20 Aprile 1993
*/
#include "g2comdb.inc"
#include "mesqueue.h"
#include "comunic.inc"
#include "sepdati.inc"

sepabil()
{
QUEUE_PACKET 	pack;
S_INET_ABIL	mess;
S_INET_SYS	  mess_sys;
HEA_FSVAR *pheafsvar;
short i;

pack.wto=0;
pack.flg=MSG_WAIT;
pack.amsg=(char*)&mess;
pack.que=c_ut_tx;
pack.lmsg=sizeof(HEASCA)+sizeof(mess.n_nodi)+sizeof(S_NAB);

mess.hea.addr_nodo=nodo_test_rete;
mess.hea.prov=cl_scada;
mess.hea.dest=cl_scada;
mess.hea.mess=inet_abil;
mess.n[0].abil=nodo_abilitato ;
mess.n_nodi=1;
//mess.n[0].addr=nodo_stop_1;
//enqueue(&pack);
//mess.n[0].addr=nodo_stop_2;
//enqueue(&pack);
//tra(mbox_inet,1);
/*
	ciclo per abilitazione armadi
*/
for(i=0, pheafsvar=&heafsvar[0];i<sp_armadi;i++,pheafsvar++)
{
	if(pheafsvar->n_punti)
	{
		mess.n[0].addr=nodo_armadi+i*2;
		enqueue(&pack);
		if(!pheafsvar->duale)				// singolo o duale
		{
			mess.n[0].addr=nodo_armadi+i*2+1;
			enqueue(&pack);
		}
		tra(mbox_inet,1);
	}
}
/*
	attendo che Inet abbia eseguito le operazioni preliminari
*/
if(sys_master)			// in caso di sistema singolo master di default
{
	wai(60);
	printf("Master abilitazione Rete e Modo Operativo");
	_modorete(reteA,MASTER);
	_modorete(reteB,MASTER);

	_modoappli(MASTER);
}

return(0);
}
