/**********************************************************************
*
*       C Source:               CsPrepMsgAllReq.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Nov  3 16:01:22 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsgAllReq.c-2 %  (%full_filespec: CsPrepMsgAllReq.c-2:csrc:1 %)";
#endif
/*
   modulo CsPrepMsgAllReq.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgAllReq.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgAllReq.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#ifndef VMS
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#else
#include <vmsipc.h>
#endif
#include <sim_param.h>
#include <Cs/Cs.h>

/*
  Prepara e spedisce il messaggio di richiesta allo scada dei dati di un trend
*/
int CsPrepMsgAllReq(int coda, int zone[32],int db)
{
MSG_ALL_REQ_MMI msg;


    msg.mtype  = ALL_REQ;
    msg.db     = db;
    memcpy(&msg.zone[0],&zone[0],sizeof(int)*32);
    msg_snd(coda,&msg,sizeof(MSG_ALL_REQ_MMI)-sizeof(long),!IPC_NOWAIT);
    	return(1);
}
