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
   modulo CsRcvMsgSimID.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsRcvMsgSimID.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgSimID.c	5.1\t11/13/95";
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

#include "libipc.h"
#include <sim_param.h>
#include <Cs/Cs.h>


/*
    Riceve da mmi un messaggio con l'indice della SHM da cancellare
    Parametri:
              int coda : coda su cui attende msg
              int molt_timeout: fattore di moltiplicazione del timeout
    Ritorno :
	      -1 se fallita 
              1 se ok.
*/
int CsRcvMsgSimID(int coda,char *path_sim )
{
int ret;
MSG_SIM_ID msg;
int timeout;

timeout=TIMEOUT_BASE/2;

    if ( (ret=msg_rcv(coda,&msg,(sizeof(MSG_SIM_ID)-sizeof(long)),(long)CHECK_SIM_ID,
                      !IPC_NOWAIT,timeout))<0 )
       {
       return -1;
       }
    else
       {
       if(path_sim)
          strcpy(path_sim,msg.path_sim);
       else
          strcpy(path_sim,"");
       return 1;
       }
}
