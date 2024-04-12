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
   modulo CsPrepMsgF22.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgF22.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgF22.c	5.1\t11/13/95";
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
/********
int CsPrepMsgDel(int coda, char *nome_client, char *nome_server)
{
MSG_F22_MMI msg;


    msg.mtype  = F22_MMI;
    strcpy(msg.path_client,nome_client);
    strcpy(msg.path_server,nome_server);
    msg_snd(coda,&msg,sizeof(MSG_F22_MMI)-sizeof(long),!IPC_NOWAIT);

    return(1);
}
********/
