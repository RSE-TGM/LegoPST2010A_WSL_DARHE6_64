/**********************************************************************
*
*       C Source:               stato_processo.c
*       Subsystem:              2
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 09:59:57 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: stato_processo.c-2 %  (%full_filespec: stato_processo.c-2:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)stato_processo.c	5.1\t11/10/95";
/*
   modulo stato_processo.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)stato_processo.c	5.1
*/
# include <stdio.h>
# include <errno.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
#if defined VMS
#include <unixlib.h>
#include <ssdef.h>
#include <jpidef.h>
#include <descrip.h>

typedef struct itmlst{
 short buflen;
 short code;
 char *bufadr;
 char *retlenadr;
 int end_list;} ITMLIST;
#endif

#if defined VMS
#define pid_t int
#endif



int stato_processo();

int stato_processo(pid)
pid_t pid;
{
int ritorno;
#if defined OSF1 || defined SCO_UNIX || defined LINUX
int status;
#endif
#if defined VMS
ITMLIST item_list;
int iosb[2];
unsigned int app_pid;
struct dsc$descriptor_s name_desc;
int status;
int state,state_len;
#endif

if(pid<=0)
	return(0);

if(pid==1)
	return(1);

#if defined AIX 
        ritorno = getpri(pid);
#endif
#if defined ULTRIX 
        ritorno = getpgrp(pid);
#endif
#if defined OSF1 || defined SCO_UNIX || defined LINUX
	ritorno=waitpid(pid,&status,WNOHANG);
	ritorno=waitpid(pid,&status,WNOHANG);
#endif
#if defined HELIOS
/* momentaneamente */
	ritorno = 1;
#endif
#if defined VMS
item_list.buflen=sizeof(int);
item_list.code=JPI$_STATE;
item_list.bufadr=(&state);
item_list.retlenadr=(&state_len);
item_list.end_list=0;
app_pid=pid;
status=sys$getjpi(0,&app_pid,&name_desc,&item_list,&iosb,0,0);
if (status%2)
        return(1);
else return(0);
#endif

if(ritorno<0)
	return(0);
else
	return(1);
}
