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
	routine per l'invio dei comandi analogici su inet
	in ingresso viene fornito il puntatore in dbs  e il valore
	float da inviare
*/

#include <stdio.h>

#include "pscs.cfg"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"
#include "g2comdb.inc"

extern short mbox_inet;
extern short c_ut_tx;

invao(puntdb, valore)
unsigned short puntdb;
float valore;
   {

   QUEUE_PACKET pack;
   S_MSCAO mess;
/*
	lettura descrittore comando
*/
   mess.hea.addr_nodo=dbaom[puntdb]*2+nodo_armadi;
   mess.indice=puntdb;

   mess.hea.mess=mscao;
   mess.hea.prov=cl_scada;
   mess.hea.dest=cl_dac;
   mess.valore=valore;

#if defined AC_SERIALE
   pack.que = c_out_inet1;
#else
   pack.que = c_ut_tx;
#endif

   pack.wto = 0;
   pack.flg = MSG_WAIT;
   pack.lmsg= sizeof(S_MSCAO);
   pack.amsg= (char *) & mess;
   if((!SYS_DUALE) || sys_master) enqueue(&pack);

#if defined (AC_INETDUALE)
	tra(mbox_inet,1);
#endif

   }




