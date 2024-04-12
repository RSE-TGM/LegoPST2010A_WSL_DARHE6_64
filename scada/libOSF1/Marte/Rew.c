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


int rew(int indice,int timeout, int *valore)
{
extern MarteMailbox *PuntMarteMailbox;
struct timespec delta;
struct timespec abstime;
int ret;

SetTaskState(-1,SUSPENDED_STATE);
pthread_mutex_lock(&(PuntMarteMailbox[indice].mutex));
if(PuntMarteMailbox[indice].valore!=0)
        {
        *valore = PuntMarteMailbox[indice].valore;
        PuntMarteMailbox[indice].valore = 0;
        ret = pthread_mutex_unlock(&(PuntMarteMailbox[indice].mutex));
	SetTaskState(-1,RUNNING_STATE);
        return(0);
        }

if(timeout!= 0)
	{
	timeout = timeout * REAL_TIME_CLOCK;
	delta.tv_sec = timeout/1000;
	delta.tv_nsec = (timeout*1000 - delta.tv_sec*1000000)*1000;
	pthread_get_expiration_np(&delta,&abstime);
	ret = pthread_cond_timedwait(&(PuntMarteMailbox[indice].condition),
			&(PuntMarteMailbox[indice].mutex),&abstime);
	if(ret != 0)
		{
		*valore = 0;
		pthread_mutex_unlock(&(PuntMarteMailbox[indice].mutex));
		SetTaskState(-1,RUNNING_STATE);
		return(1);
		}
	}
else
	ret = pthread_cond_wait(&(PuntMarteMailbox[indice].condition),
			&(PuntMarteMailbox[indice].mutex));
*valore = PuntMarteMailbox[indice].valore;
PuntMarteMailbox[indice].valore = 0;
pthread_mutex_unlock(&(PuntMarteMailbox[indice].mutex));
SetTaskState(-1,RUNNING_STATE);
return(0);
}
