/**********************************************************************
*
*       C Source:               CsPrepMsgMiniASDReq.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Feb 26 13:29:28 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsgMiniASDRic.c-3 %  (%full_filespec: CsPrepMsgMiniASDRic.c-3:csrc:1 %)";
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
Costruisce un messaggio MSG_ALL_MINIASD_RIC_MMI contenente le informaz.
relative all' allarme da riconoscere di indice indice_all contenuto nella shm data_all e lo spedisce all' MMI.

Parametri:
     int coda: coda messaggi fra mmi e client_scada
     int  id_data_all: id shm dove c'e l' allarme da riconoscere
     filtro: valore del filtro su operazione di ric.
     tipo_allarme: tipo di allarme da riconoscere
     indice_all: indice allarme da riconoscere

Return:
      1 se tutto OK.    
*/
int CsPrepMsgMiniASDRic(int coda,unsigned char gerarchia[N_GERARCHIE],int id_data_all,int filtro,int tipo_allarme,int n_all,int indice_all)
{
MSG_ALL_MINIASD_RIC_MMI msg;

    msg.mtype  = ALL_RIC_MINIASD;

    if(!memcpy(&msg.gerarchia[0],&gerarchia[0],
           sizeof(unsigned char)*N_GERARCHIE))
           return(-1);

/*
Inserisco i dati dell' allarme nel messaggio
*/
    msg.id_data_all=id_data_all;
    msg.filtro=filtro;
    msg.tipo_allarme=tipo_allarme;
    msg.n_all=n_all;
    msg.indice_all=indice_all;
printf("CsPrepMsgMiniASDRic:Sto per mandare messaggio a client_scada\n");
printf("CsPrepMsgMiniASDRiq:data_all n_all=%d=%d \n",id_data_all,n_all);
    msg_snd(coda,&msg,sizeof(MSG_ALL_MINIASD_RIC_MMI)-sizeof(long),!IPC_NOWAIT);
    	return(1);
}
