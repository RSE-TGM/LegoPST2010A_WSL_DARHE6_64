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
   modulo CsPrepMsgTrendReq.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsgTrendReq.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsgTrendReq.c	5.1\t11/13/95";
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
  Prepara e spedisce il messaggio di richiesta allo scada dei dati di un trend
*/
#if defined SCADA_MMI
int CsPrepMsgTrendReq(int coda, int id_shm,char *nome_pagina,
		int codice_trend,char *nome_file_trend,int num_mis,
		char *sigla_1,char *sigla_2,char *sigla_3,char *sigla_4)
{
static MSG_TREND_REQ_MMI msg;


    msg.mtype  = TREND_REQ;
    msg.id_shm=id_shm;
    strcpy(msg.nome_pagina,nome_pagina);
    msg.codice_trend=codice_trend;
    strcpy(msg.nome_file_trend,nome_file_trend);
    msg.num_mis=num_mis;
    if(sigla_1!=NULL) 
	strcpy(msg.sigla_1,sigla_1);
    else 
	msg.sigla_1[0]=NULL;
    if(sigla_2!=NULL) 
	strcpy(msg.sigla_2,sigla_2);
    else 
	msg.sigla_2[0]=NULL;
    if(sigla_3!=NULL) 
	strcpy(msg.sigla_3,sigla_3);
    else 
	msg.sigla_3[0]=NULL;
    if(sigla_4!=NULL) 
	strcpy(msg.sigla_4,sigla_4);
    else 
	msg.sigla_4[0]=NULL;
    if(msg_snd(coda,&msg,sizeof(MSG_TREND_REQ_MMI)-sizeof(long),!IPC_NOWAIT)<0)
	return(-1);
    else
    	return(1);
}
#endif
