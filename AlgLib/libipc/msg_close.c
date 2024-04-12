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
static char SccsID[] = "@(#)msg_close.c	5.1\t11/7/95";
/*
   modulo msg_close.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)msg_close.c	5.1
*/
# include "libipc.h"



#define MAX_NUM_CODE 20

int id_code[MAX_NUM_CODE];
int id_sem[MAX_NUM_CODE];


int msg_close();

int msg_close(key)
int key;
{
int id_msg;
int id;
int i;
int cont;
int ret;
#if defined UNIX
struct msqid_ds buf_msg;

ret = msgctl(key, IPC_RMID, &buf_msg);
if(ret==(-1))
   	{
    	perror("chiusura coda messaggi:");
	return(-1);
	}
#endif
return(1);
}
