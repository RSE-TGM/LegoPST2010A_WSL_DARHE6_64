/**********************************************************************
*
*       C Source:               CsRcvMsgMiniASDRic.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Feb 26 16:03:49 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsRcvMsgMiniASDRic.c-2 %  (%full_filespec: CsRcvMsgMiniASDRic.c-2:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgAllRic.c	5.1\t11/13/95";
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
    Riceve da mmi un messaggio per la richiesta riconoscimento singolo 
    allarme per miniASD
*/
int CsRcvMsgMiniASDRic(int coda,MSG_ALL_MINIASD_RIC_MMI *msg)
{
int ret;


    if ( (ret=msg_rcv(coda,msg,sizeof(MSG_ALL_MINIASD_RIC_MMI)-sizeof(long),
		(long)ALL_RIC_MINIASD,IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {

printf("CsRcvMsgMiniASDReq:RICEVUTO MESSAGGIO ric miniASD\n");
       return(1);
       }
}
