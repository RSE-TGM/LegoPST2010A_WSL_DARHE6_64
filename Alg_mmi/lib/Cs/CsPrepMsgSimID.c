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
   modulo CsPrepMsgSimID.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgSimID.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgSimID.c	5.1\t11/13/95";
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
    Prepara e spedisce il messaggio di verifica ID Simulatore.
*/
int CsPrepMsgSimID(int coda,char *path_sim)
{
MSG_SIM_ID msg;


    msg.mtype  = CHECK_SIM_ID;
    if(path_sim)
       strcpy(msg.path_sim,path_sim);
    else 
       strcpy(msg.path_sim,"");
    msg_snd(coda,&msg,(sizeof(MSG_SIM_ID)-sizeof(long)),!IPC_NOWAIT);

    return 1;
}
