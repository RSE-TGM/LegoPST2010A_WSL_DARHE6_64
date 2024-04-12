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
static char SccsID[] = "@(#)sem_rm.c	5.1\t11/7/95";
/*
   modulo sem_rm.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_rm.c	5.1
*/

# include "libipc.h"

void sem_rm(id)
int id;
{
#if defined UNIX
if(semctl(id,0,IPC_RMID,0)<0)
	perror("Impossibile eliminare il semaforo");
#endif
}
