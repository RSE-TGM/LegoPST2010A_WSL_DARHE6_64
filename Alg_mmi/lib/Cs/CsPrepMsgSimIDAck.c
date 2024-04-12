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
   modulo CsPrepMsgSimIDAck.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgSimIDAck.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgSimIDAck.c	5.1\t11/13/95";
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
int CsPrepMsgSimIDAck(int coda,int ris)
{
MSG_SIM_ID_ACK msg;


    msg.mtype  = CHECK_SIM_ID_ACK;
    msg.ris=ris;
    msg_snd(coda,&msg,(sizeof(MSG_SIM_ID_ACK)-sizeof(long)),!IPC_NOWAIT);

    return 1;
}
