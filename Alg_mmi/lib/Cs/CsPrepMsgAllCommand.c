/**********************************************************************
*
*       C Source:               CsPrepMsgAllCommand.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Nov  4 09:17:25 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsgAllCommand.c-2_deb1 %  (%full_filespec: CsPrepMsgAllCommand.c-2_deb1:csrc:1 %)";
#endif
/*
   modulo CsPrepMsgAllCommand.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgAllCommand.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgAllCommand.c	5.1\t11/13/95";
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
  Prepara e spedisce il messaggio per la gestione della pgina allarmi
*/
int CsPrepMsgAllCommand(int coda, int comando,int db)
{
MSG_ALL_COMMAND_MMI msg;


    msg.mtype  = ALL_REQ_COMMAND;
    msg.comando=comando;
    msg.db=db;
    if(msg_snd(coda,&msg,sizeof(MSG_ALL_COMMAND_MMI)-sizeof(long),
               !IPC_NOWAIT)<0)
      {
      perror("---mmi-CsPrepMsgAllCommand---");
      fprintf(stderr,"WARNING: Impossible to send command to client_scada\n");
      return(-1);
      }
    else
      return(1);
}
