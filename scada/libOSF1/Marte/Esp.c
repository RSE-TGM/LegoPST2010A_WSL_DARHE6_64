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
/*
        Fine sezione per SCCS
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <Marte/MarteP.h>


int esp(int indice)
{
extern TCB *PuntTcb;
int stato;

stato = GetTaskState(indice);

if(!(stato&SUSPENDED_STATE))
	return(1);

pthread_mutex_lock(&(PuntTcb[indice].mutex_sus));
pthread_cond_signal(&(PuntTcb[indice].condition_sus));
pthread_mutex_unlock(&(PuntTcb[indice].mutex_sus));
return(0);
}
