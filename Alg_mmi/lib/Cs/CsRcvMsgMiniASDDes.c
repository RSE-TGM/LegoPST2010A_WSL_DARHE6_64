/**********************************************************************
*
*	C Source:		CsRcvMsgMiniASDDes.c
*	Instance:		1
*	Description:	
*	%created_by:	famgr %
*	%date_created:	Mon Feb 23 15:15:52 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsRcvMsgMiniASDDes.c-1 %  (%full_filespec: CsRcvMsgMiniASDDes.c-1:csrc:1 %)";
#endif


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
int CsRcvMsgMiniASDDes(int coda,MSG_ALL_MINIASD_DES_MMI *msg)
{
int ret;


    if ( (ret=msg_rcv(coda,msg,sizeof(MSG_ALL_MINIASD_DES_MMI)-sizeof(long),
                (long)ALL_DES_MINIASD,IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {
/*
printf("CsRcvMsgMiniASDDes:RICEVUTO MESSAGGIO miniASD\n");
*/
       return(1);
       }
}

