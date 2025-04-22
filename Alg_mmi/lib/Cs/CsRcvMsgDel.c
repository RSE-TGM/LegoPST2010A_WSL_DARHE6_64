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
   modulo CsRcvMsgDel.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsRcvMsgDel.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgDel.c	5.1\t11/13/95";
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
#include "sim_types.h"

/*
    Riceve da mmi un messaggio con l'indice della SHM da cancellare
*/
int CsRcvMsgDel(int coda)
{
int ret;
MSG_DEL_PAGE_MMI msg;


    if ( (ret=msg_rcv(coda,&msg,sizeof(int),(long)DEL_PAGE_MMI,
                      IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {
       return(msg.id_shm);
       }
}
