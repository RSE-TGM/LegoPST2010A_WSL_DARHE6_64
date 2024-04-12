/**********************************************************************
*
*	C Source:		CsPrepMsgMiniASDDes.c
*	Instance:		1
*	Description:	
*	%created_by:	famgr %
*	%date_created:	Thu Feb 26 18:06:10 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsgMiniASDDes.c-2 %  (%full_filespec: CsPrepMsgMiniASDDes.c-2:csrc:1 %)";
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
  Prepara e spedisce il messaggio di richiesta al client_scada per allarmi miniA
SD
*/
int CsPrepMsgMiniASDDes(int coda,int id_allarm ,int id_manual)
{
MSG_ALL_MINIASD_DES_MMI msg;


    msg.mtype  = ALL_DES_MINIASD;
/*
Nel messaggio passo al client_scada i puntatori delle shm  in
cui inserire i dati ricevuti dallo SCADA
*/
    msg.id_allarm=id_allarm;
    msg.id_manual=id_manual;
printf("CsPrepMsgMiniASDDes:Sto per mandare messaggio a client_scada\n");
/*
printf("CsPrepMsgMiniASDDes:allarm_data=%ld manual_data=%ld\n",allarm_data,manua
l_data);
printf("CsPrepMsgMiniASDDes:msg.allarm_data=%ld msg.manual_data=%ld\n",msg.allar
m_data,msg.manual_data);
*/
    msg_snd(coda,&msg,sizeof(MSG_ALL_MINIASD_DES_MMI)-sizeof(long),!IPC_NOWAIT);
        return(1);
}

