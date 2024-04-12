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
	Invao

	routine per l'invio dei comandi analogici su inet con protocollo
	Sepa

	Parametri

	puntdb	short puntatore in data base sistema
	valore	float valore del set point

	20 Aprile 1993

*/
#include "pscs.cfg"
#include "comunic.inc"
#include "mesqueue.h"
#include "g2comdb.inc"
#include "sepdati.inc"
#include "switch.inc"

invao(puntdb,valore)
unsigned short puntdb ;
float valore;
{
S_FDEAO des_com;					/* struttura descrittore comandi */
QUEUE_PACKET pack;
S_MSCAO_SEP mess;
/*
	lettura descrittore comando
*/
if(rbyte(fileno(fpp[fdeao]),&des_com,(long)puntdb*(long)sizeof(S_FDEAO),
		sizeof(S_FDEAO))==-1)	
         return(0);		// se nessun record letto

mess.hea.addr_nodo=des_com.peri*2+nodo_armadi;
mess.indice=des_com.indfis.s;

mess.hea.mess=mscao;
mess.hea.prov=cl_scada;
mess.hea.dest=cl_dac;
mess.valore=(float) valore/ (float) tab_k[(short)des_com.molt];

pack.que=c_ut_tx;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.lmsg=sizeof(S_MSCAO);
pack.amsg=(char*) & mess;

if((!SYS_DUALE)||(SYS_DUALE && sys_master))
    enqueue(&pack);

tra(mbox_inet,1);
}




