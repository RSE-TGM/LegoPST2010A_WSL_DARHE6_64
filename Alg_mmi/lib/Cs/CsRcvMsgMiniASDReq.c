/**********************************************************************
*
*       C Source:               CsRcvMsgMiniASDReq.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Feb  4 12:00:39 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsRcvMsgMiniASDReq.c-2 %  (%full_filespec: CsRcvMsgMiniASDReq.c-2:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgAllReq.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <sim_param.h>
#include <Cs/Cs.h>


/*
    Riceve da mmi un messaggio per la richiesta di allarmi per miniASD
*/
int CsRcvMsgMiniASDReq(int coda,MSG_ALL_MINIASD_REQ_MMI *msg)
{
int ret;


    if ( (ret=msg_rcv(coda,msg,sizeof(MSG_ALL_MINIASD_REQ_MMI)-sizeof(long),
		(long)ALL_REQ_MINIASD,IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {
/*
printf("CsRcvMsgMiniASDReq:RICEVUTO MESSAGGIO miniASD\n");
*/
       return(1);
       }
}
