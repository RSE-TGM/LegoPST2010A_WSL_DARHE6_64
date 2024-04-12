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
static char SccsID[] = "@(#)sem_open.c	5.1\t11/7/95";
/*
   modulo sem_open.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_open.c	5.1
*/

# include "libipc.h"

int sem_open(key)
int key;
{
int id;

#if defined UNIX
if(key==IPC_PRIVATE)
	return(-1);
else if(key==(int)-1)
	return(-1);

if((id=semget(key,3,0))<0)
	return(-1);

if (semop(id, &op_open[0],1)<0)
	perror("impossibile aprire il semaforo");
return(id);
#endif

#if defined VMS
return(1);
#endif
}
