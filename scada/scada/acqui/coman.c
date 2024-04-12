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
	routine per l'invio dei comandi digitali su inet
	in ingresso viene fornito solo il puntatore in dbs
*/
#include <stdio.h>

#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"

extern short mbox_inet;
extern short c_ut_tx;

coman(puntdb)
unsigned short puntdb;
   {
   QUEUE_PACKET pack;

   S_MSCDO mess;
   
   pack.lmsg=sizeof(S_MSCDO);

   pack.que=c_ut_tx;
   pack.wto=0;
   pack.flg=MSG_WAIT;
   pack.amsg=(char*) & mess;

   mess.hea.mess=mscdo;
   mess.hea.prov=cl_scada;
   mess.hea.dest=cl_dac;

   mess.hea.addr_nodo=dbdom[puntdb]*2+nodo_armadi;
   mess.indice=puntdb;

   if ((!SYS_DUALE) || sys_master)
      enqueue(&pack);
#if defined (AC_INETDUALE)
   tra(mbox_inet,1);
#endif

   }



