/**********************************************************************
*
*       C Source:               to_dispatcher.c
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 14:23:10 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: to_dispatcher.c-10 %  (%full_filespec: to_dispatcher.c-10:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)to_dispatcher.c	5.2\t2/14/96";
/*
   modulo to_dispatcher.c
   tipo 
   release 5.2
   data 2/14/96
   reserved @(#)to_dispatcher.c	5.2
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
#include "vmsipc.h"
#endif
#include "sim_param.h"
#include "sim_ipc.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "libdispatcher.h"

#include "libipc.h"

int to_dispatcher (processo, comando, dati, size)
int     processo;
int     comando;
char   *dati;
int     size;
{
static int  id = -1;
static int  id_ret = -1;

static int  id_sem = -1;

int     shr_usr_key;
    MSG_DISPATCHER messaggio_dispatcher;
    MSG_ACK msg_ack;
#if defined UNIX
struct msqid_ds  buf;
#endif
printf("to_dispatcher: 0 GUAG id_sem = %d getpid=%d\n",id_sem,getpid());

/* aggancio coda messaggi e semaforo per il dispatcher */
    if(id_sem == -1)
    {
        shr_usr_key = atoi (getenv ("SHR_USR_KEY"));
        id_sem = sem_create(shr_usr_key + ID_SEM_DISP, 0); 
printf("to_dispatcher: 1 GUAG id_sem = %d\n",id_sem);
    }

    if (id == -1)
    {
	shr_usr_key = atoi (getenv ("SHR_USR_KEY"));
	if (processo == MONIT)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_MONIT, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_MONIT, 0);
	}
	if (processo == BI)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_BI, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_BI, 0);
	}
	if (processo == SUPERVISIONE)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_SUPER, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_SUPER, 0);
	}
	if (processo == BM)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_BM, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_BM, 0);
	}
	if (processo == TASTIERA)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_TAST, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_TAST, 0);
	}
	if (processo == SKED)
	{
	    id = msg_create (shr_usr_key + ID_MSG_FROM_SKED, 0);
	    id_ret = msg_create (shr_usr_key + ID_MSG_TO_SKED, 0);
	}
    }
/* invia il messaggio */
    if (size > 0)
    {
	memcpy (messaggio_dispatcher.comando_dispatcher.dati,
		dati, size);
    }
    messaggio_dispatcher.mtype = comando;
    messaggio_dispatcher.comando_dispatcher.sorgente = processo;
    messaggio_dispatcher.comando_dispatcher.tipo = comando;
    messaggio_dispatcher.comando_dispatcher.num = 0;
    messaggio_dispatcher.comando_dispatcher.num_tot = 1;
    messaggio_dispatcher.comando_dispatcher.size = size;
#if defined UNIX
    /* verifica che a livello di sistema sia possibile inserire il
       messaggio nella coda
    */
                msgctl(id,IPC_STAT,&buf);
                while(buf.msg_qnum>30)
                        {
                        sospendi(50);
                        msgctl(id,IPC_STAT,&buf);
                        }
#endif

    if(msg_snd (id, &messaggio_dispatcher, 
		size + 5 * sizeof (float), !IPC_NOWAIT)<0)
	{
	printf("TO_DISPATCHER : fallita msgsnd (COMANDO)\n");
	return(-1);
	}

/* incremento del valore del semaforo */
    sem_signal_disp(id_sem);

printf("to_dispatcher: 2 GUAG id_sem = %d id=%d\n",id_sem,id);

/* attende ack */
    if(msg_rcv (id_ret, &msg_ack, sizeof(MSG_ACK)-sizeof(long), 
		(long)1000, !IPC_NOWAIT, TIMEOUT_DISP)<0)
	{
	printf("TO_DISPATCHER : fallita msgrcv (ACK)\n");
	return(-1);
	}
printf("to_dispatcher: 3 GUAG id_ret = %d msg_ack.ret=%d\n",id_ret,msg_ack.ret);
   if(msg_ack.ret > 0)
	{
/*******
        if ( msg_ack.ret==NUOVA_CI )
           return(NUOVA_CI);
   	return(1);
*********/
        return(msg_ack.ret);
	}
   else
	{
	if ( msg_ack.ret == NO_ALLINEA ) 
           return(NO_ALLINEA);
        else
	   return(-1);
	}
}
