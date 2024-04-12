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
   modulo CsPrepMsgDel.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgDel.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgDel.c	5.1\t11/13/95";
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
    Prepara e spedisce il messaggio della cancellazione di una pagina.
*/
int CsPrepMsgDel(int coda, int id_shm)
{
MSG_DEL_PAGE_MMI msg;


    msg.mtype  = DEL_PAGE_MMI;
    msg.id_shm = id_shm;
    msg_snd(coda,&msg,sizeof(int),!IPC_NOWAIT);

    return(1);
}
