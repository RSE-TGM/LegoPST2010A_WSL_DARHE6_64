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
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)msg_snd.c	5.1\t11/7/95";
/*
   modulo msg_snd.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)msg_snd.c	5.1
*/
#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int msg_snd (msqid, msgp, msgsz, msgflg)
int msqid;
void *msgp;
size_t msgsz;
int msgflg;
{
int ret = -1;
/* DEBUG
printf("msg_snd: 0 GUAG msqid=%d msgsz=%d getpid=%d\n",msqid,msgsz,getpid());
fflush(stdout);
*/
	ret = msgsnd (msqid, msgp, msgsz, msgflg);
/* DEBUG
printf("msg_snd: 1 GUAG dopo msgsnd -  msqid=%d\n",msqid);
fflush(stdout);
*/
	return(ret);
}
#endif

