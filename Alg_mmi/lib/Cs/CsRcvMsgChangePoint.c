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
   modulo CsRcvMsgChangePoint.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsRcvMsgChangePoint.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgChangePoint.c	5.1\t11/13/95";
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
    Riceve da mmi un messaggio per la modifica di un punto
*/
int CsRcvMsgChangePoint(int coda,MSG_CHANGE_POINT_MMI *msg)
{
int ret;


    if ( (ret=msg_rcv(coda,msg,sizeof(MSG_CHANGE_POINT_MMI)-sizeof(long),
		(long)CHANGE_POINT_MMI,IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {
       return(1);
       }
}
