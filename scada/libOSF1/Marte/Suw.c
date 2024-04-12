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


int suw(int timeout)
{
pthread_t self;
int i,ret;
struct timespec delta;
struct timespec abstime;
extern TCB *PuntTcb;


self = pthread_self();

for (i=0;i<MAX_THREAD; i++)
        if( pthread_equal(self, PuntTcb[i].id)== 1)
                break;

SetTaskState(i,SUSPENDED_STATE);

pthread_mutex_lock(&(PuntTcb[i].mutex_sus));

if(timeout!=0)
	{
	timeout = timeout * REAL_TIME_CLOCK;
        delta.tv_sec = timeout/1000;
        delta.tv_nsec = (timeout*1000 - delta.tv_sec*1000000)*1000;
        pthread_get_expiration_np(&delta,&abstime);
	ret = pthread_cond_timedwait(&(PuntTcb[i].condition_sus),
			&(PuntTcb[i].mutex_sus),&abstime);
	pthread_mutex_unlock(&(PuntTcb[i].mutex_sus));
	SetTaskState(i,RUNNING_STATE);
	if(ret != 0)
		return(1);
	else
		return(0);
	}
else
	{
	pthread_cond_wait(&(PuntTcb[i].condition_sus),&(PuntTcb[i].mutex_sus));
	pthread_mutex_unlock(&(PuntTcb[i].mutex_sus));
	SetTaskState(i,RUNNING_STATE);
	return(0);
	}
}
