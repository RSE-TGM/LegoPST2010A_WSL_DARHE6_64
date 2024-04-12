/**********************************************************************
*
*       C Source:               CsPrepMsgMiniASDReq.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Feb 17 19:35:45 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsgMiniASDReq.c-5 %  (%full_filespec: CsPrepMsgMiniASDReq.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgMiniAsdReq.c	5.1\t11/13/95";
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
#include <sim_param.h>
#include <Cs/Cs.h>

/*
  Prepara e spedisce il messaggio di richiesta al client_scada per allarmi miniASD
*/
int CsPrepMsgMiniASDReq(int coda,unsigned char gerarchia[N_GERARCHIE],int id_allarm_data,int id_manual_data,int filtro,int tipo_allarme)
{
MSG_ALL_MINIASD_REQ_MMI msg;


    msg.mtype  = ALL_REQ_MINIASD;
    if(!memcpy(&msg.gerarchia[0],&gerarchia[0],
       sizeof(unsigned char)*N_GERARCHIE))
         return(-1);
/*
Nel messaggio passo al client_scada i puntatori delle shm  in 
cui inserire i dati ricevuti dallo SCADA
*/
    msg.id_allarm_data=id_allarm_data;
    msg.id_manual_data=id_manual_data;
    msg.filtro=filtro;
    msg.tipo_allarme=tipo_allarme;
/*
printf("CsPrepMsgMiniASDReq:Sto per mandare messaggio a client_scada\n");
printf("CsPrepMsgMiniASDReq:allarm_data=%ld manual_data=%ld\n",allarm_data,manual_data);
printf("CsPrepMsgMiniASDReq:msg.allarm_data=%ld msg.manual_data=%ld\n",msg.allarm_data,msg.manual_data);
*/
    msg_snd(coda,&msg,sizeof(MSG_ALL_MINIASD_REQ_MMI)-sizeof(long),!IPC_NOWAIT);
    	return(1);
}
