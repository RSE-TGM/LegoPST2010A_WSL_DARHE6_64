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
static char SccsID[] = "@(#)sem_create.c	5.1\t11/7/95";
/*
   modulo sem_create.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_create.c	5.1
*/

# include "libipc.h"

int sem_create(key,initval)
int key;
int initval;
{
int id,semval;

#if defined UNIX
union semun{
	int	val;
	struct semid_ds *buf;
	ushort	*array;
} semctl_arg;

if(key==IPC_PRIVATE)
	return(-1);
else if (key==(int)-1)
	return(-1);

again:
	{
	if((id=semget(key,3,0666|IPC_CREAT))<0)
		return(-1);
	}

if (semop(id, &op_lock[0],2)<0){
	if(errno ==EINVAL)
		goto again;

	perror("locking impossibile");
	}

if ((semval = semctl(id,1,GETVAL,0))<0)
	perror("GETVAL impossibile");

if(semval==0)
	{
	semctl_arg.val=initval;
	if(semctl(id,0,SETVAL,semctl_arg)<0)
		perror("SETVAL[0] impossibile");
	semctl_arg.val=BIGCOUNT;
	if(semctl(id,1,SETVAL,semctl_arg)<0)
		perror("SETVAL[1] impossibile");
	}
if(semop(id,&op_endcreate[0],2)<0)
	perror("Impossibile terminare la creazione");
return(id);
#endif

#if defined VMS
return(1);
#endif
}
	

