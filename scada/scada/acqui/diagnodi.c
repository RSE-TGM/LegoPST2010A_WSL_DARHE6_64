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
		la routine diagnodi invia la richiesta di stato rete	
		la risposta viene gestita dal task acqui
*/
#include "g2comdb.inc"
#include "fileop.inc"
#include "mesest.inc"
#include "mesqueue.h"
#include "diagnoan.inc"

extern short mbox_inet;
extern short c_ut_tx;

diagnodi()
{
QUEUE_PACKET 	pack;

HEASCA hea;

pack.wto=-1;
pack.flg=MSG_NOWAIT;
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
