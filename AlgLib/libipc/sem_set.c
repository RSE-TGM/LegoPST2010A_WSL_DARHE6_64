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
static char SccsID[] = "@(#)sem_set.c	5.1\t11/7/95";
/*
   modulo sem_set.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_set.c	5.1
*/

# include "libipc.h"

int sem_set(id,initval)
int id;
int initval;
{
int semval;

#if defined UNIX
union semun{
	int	val;
	struct semid_ds *buf;
	ushort	*array;
} semctl_arg;

semctl_arg.val=initval;
if(semctl(id,0,SETVAL,semctl_arg)<0)
	perror("SETVAL[0] impossibile");
return(initval);
#endif

#if defined VMS
return(1);
#endif
}
	

