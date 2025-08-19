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
#include <sched.h>
#include <mesqueue.h>
#include <code.h>

/* Function declarations */
int acmea(int coda, char *buff, int lung);
int scmea(int coda, char *buff);
int GetAbsTime(int timeout, struct timespec *abstime);

short enqueue(sep)
QUEUE_PACKET *sep;
{
char *app;
short size, ret;

/*
	allocazione buffer di appoggio
*/
size = sizeof(short)+sep->lmsg;
app = (char*)malloc(size);

/*
	copio il buffer nel buffer di appogio
*/
memcpy(app,&size,sizeof(short));
memcpy(&app[sizeof(short)],sep->amsg,sep->lmsg);

/*
	accodo il messaggio
*/
if(sep->flg & MSG_WAIT)
	{
	while((ret = acmea(sep->que,app,size))!=0)
		{
		pthread_mutex_lock(&(cd[sep->que].mutex_condition_s));
		if(sep->wto>0)
		   {
		   struct timespec abstime;

		   GetAbsTime(sep->wto,&abstime);
		   ret = pthread_cond_timedwait
				(&(cd[sep->que].condition_s),
                        	&(cd[sep->que].mutex_condition_s),&abstime);
        	   if(ret != 0)
			{
		        pthread_mutex_unlock(&(cd[sep->que].mutex_condition_s));
			return(1);
		        }
		   }
		else
		   {
		   pthread_cond_wait(&(cd[sep->que].condition_s),
                        &(cd[sep->que].mutex_condition_s));
		   }
		pthread_mutex_unlock(&(cd[sep->que].mutex_condition_s));
		}
	}
else
	ret = acmea(sep->que,app,size);

if(ret == 0)
	{
	/*
		se il messaggio e' stato inviato sblocco la contition
	*/
	pthread_mutex_lock(&(cd[sep->que].mutex_condition_r));
	pthread_cond_signal(&(cd[sep->que].condition_r));
	pthread_mutex_unlock(&(cd[sep->que].mutex_condition_r));
	sched_yield();
	}

/*
	libero il buffer di appoggio
*/
free(app);

return(ret);
}

short dequeue(QUEUE_PACKET *rep)
{
char *app;
short size, ret;

/*
	allocazione buffer di appoggio
*/
size = sizeof(short)+cd[rep->que].dim;
app = (char*)malloc(size);


if(rep->flg & MSG_WAIT)
	{
	if((ret=scmea(rep->que,app))!=0)
		{
		pthread_mutex_lock(&(cd[rep->que].mutex_condition_r));
		if(rep->wto>0)
		   {
		   struct timespec abstime;

                   GetAbsTime(rep->wto,&abstime);
                   ret = pthread_cond_timedwait
                                (&(cd[rep->que].condition_r),
                                &(cd[rep->que].mutex_condition_r),&abstime);
                   if(ret != 0)
                        {
                        pthread_mutex_unlock(&(cd[rep->que].mutex_condition_r));
                        return(1);
                        }
	           }
		else
		   {
		   pthread_cond_wait(&(cd[rep->que].condition_r),
                        &(cd[rep->que].mutex_condition_r));
		   }
		pthread_mutex_unlock(&(cd[rep->que].mutex_condition_r));
		if((ret=scmea(rep->que,app))!=0)
                	{
                	free(app);
                	return(ret);
                	}
		}
	}
else
	{
	if((ret=scmea(rep->que,app))!=0)
		{
		free(app);
		return(ret);
		}
	}

/*
	setto la condition per segnalare che e' stata liberata 
	una parte della coda
*/
pthread_mutex_lock(&(cd[rep->que].mutex_condition_s));
pthread_cond_signal(&(cd[rep->que].condition_s));
pthread_mutex_unlock(&(cd[rep->que].mutex_condition_s));

/*
	copio i dati dal buffer di appoggio al messaggio
*/
memcpy(&(rep->lmsg),app,sizeof(short));
rep->lmsg -=sizeof(short);
memcpy(rep->amsg,&app[sizeof(short)],rep->lmsg);

/*
	libero il buffer di appoggio
*/
free(app);


return(0);
}
