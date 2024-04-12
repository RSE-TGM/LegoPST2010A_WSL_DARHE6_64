/**********************************************************************
*
*       C Source:               Private.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jun  1 16:06:37 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: Private.c-10 %  (%full_filespec: Private.c-10:csrc:1 %)";
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <Marte/MarteP.h>

#include <mesqueue.h>

extern pthread_mutex_t RootPrivMutex;

int RegTask(int pos, pthread_t id, char *task_name)
{
extern TCB *PuntTcb;

if(pos >= MAX_THREAD)
	return(-1);

memcpy(&(PuntTcb[pos].id), &id, sizeof(pthread_t));
strncpy(PuntTcb[pos].nome_task,task_name,MAX_LUN_NOME_TASK-1);
PuntTcb[pos].stato = RUNNING_STATE;
PuntTcb[pos].prio = pthread_getprio(id);
return(0);
}

int SetTaskState(int pos, int stato)
{
int i;
pthread_t self;

self = pthread_self();

if(pos == -1)
	{
	for (i=0;i<MAX_THREAD; i++)
		if( pthread_equal(self, PuntTcb[i].id)== 1)
			break;
	if(i == MAX_THREAD)
		return(-1);
	}
else
	i = pos;

if(PuntTcb[i].stato&BOOK_STATE)
	{
	PuntTcb[i].stato = stato;
	PuntTcb[i].stato = BOOK_STATE|PuntTcb[i].stato;
	}
else
	{
	PuntTcb[i].stato = stato;
	}
return(0);
}

int GetTaskState(int pos)
{
int i;
pthread_t self;

self = pthread_self();

if(pos == -1)
	{
	for (i=0;i<MAX_THREAD; i++)
		if( pthread_equal(self, PuntTcb[i].id)== 1)
			break;
	if(i == MAX_THREAD)
		return(-1);
	}
else
	i = pos;
return(PuntTcb[i].stato);
}

int PrintThreadState()
{
int i;
char testo[200];
char stato[50];

dprint(2,"Statistics: PrintThreadState");

for (i=0;i<MAX_THREAD; i++)
	if(PuntTcb[i].stato!=INACTIVE_STATE)
		{
		memset(testo,0,200);
                memset(stato,0,50);

                if(PuntTcb[i].stato& RUNNING_STATE) strcpy(stato,"running");
                if(PuntTcb[i].stato& READY_STATE) strcpy(stato,"ready");
                if(PuntTcb[i].stato& SUSPENDED_STATE) strcpy(stato,"suspended");
                if(PuntTcb[i].stato& DORMANT_STATE) strcpy(stato,"dormant");
                if(PuntTcb[i].stato& RESUMED_STATE) strcpy(stato,"resumend");
                if(PuntTcb[i].stato& BOOK_STATE) strcat(stato," book");

		sprintf(testo,"thread [%d] [%s] stato %s prio %d\n",
		  i,PuntTcb[i].nome_task,stato,PuntTcb[i].prio);
		XSetLineDebug(testo,i+1);
		}
}

int ActivateThread(void *(*routine)(void*), char *name, 
		int prio, int pos)
{
int status;
pthread_attr_t threads_attr;
int set_prio;
char testo[200];
extern TCB *PuntTcb;

if(pos >= MAX_THREAD)
	{
	fprintf(stderr,"ActivateThread: raggiunto il massimo numero di thread");
        return(-1);
	}

/*
	setto lo stato il nome e la priorita' nella TCB
*/
PuntTcb[pos].stato = RUNNING_STATE;
PuntTcb[pos].prio = prio;
strncpy(PuntTcb[pos].nome_task,name,MAX_LUN_NOME_TASK-1);

set_prio=SetRootPriv();
printf("ActivateThread  pos = %d  name = %s prio = %d\n",pos,name,prio);
pthread_attr_create(&threads_attr);
/*
	se e' stato possibile settare i privilegi di root
	viene gestita la priorita'
*/
if(set_prio)
	{
/*
	pthread_attr_setinheritsched(&threads_attr,PTHREAD_DEFAULT_SCHED);
*/
	pthread_attr_setsched(&threads_attr,SCHED_FIFO);
	pthread_attr_setprio(&threads_attr,prio);
	}
pthread_attr_setstacksize(&threads_attr,1000000);
status= pthread_create (&(PuntTcb[pos].id),threads_attr,
                        routine,(pthread_addr_t) pos);
UnSetRootPriv();
if(status == -1) 
	{
	perror("ActivateThread");
	return(status);
	}
// verifico la priorita' effettiva

PuntTcb[pos].prio = -123456789;
PuntTcb[pos].prio = pthread_getprio(PuntTcb[pos].id);

{

int gattino;
gattino=1234;
gattino=pthread_getprio(PuntTcb[pos].id);
printf("gattino=%d\n",gattino);

}

printf("Fine attivazione thread [%s] ", name);
printf("prio = %d\n",PuntTcb[pos].prio);
printf("Fine attivazione thread [%s] prio = %d\n", name,PuntTcb[pos].prio);

printf("Fine attivazione thread [%s] prio = %d\n", name,PuntTcb[pos].prio);
/*
sprintf(testo,"Fine attivazione thread [%s] prio = %d\n",
	name,pthread_getprio(thread));
XAddScadaLog(testo);
*/
return(pos);
}

int SetBookState(int pos,int val)
{
int i;
pthread_t self;

self = pthread_self();

if(pos == -1)
	{
	for (i=0;i<MAX_THREAD; i++)
		if( pthread_equal(self, PuntTcb[i].id)== 1)
			break;
	if(i == MAX_THREAD)
		return(-1);
	}
else
	i = pos;

if(val==0)
	{
	PuntTcb[i].stato = (!BOOK_STATE)&PuntTcb[i].stato;
	}
else
	{
	PuntTcb[i].stato = BOOK_STATE|PuntTcb[i].stato;
	}
}

void GetAbsTime(int timeout_in, struct timespec *abstime)
{
struct timespec delta;
long timeout;

        timeout = timeout_in * REAL_TIME_CLOCK;
        delta.tv_sec = timeout/1000;
        delta.tv_nsec = (timeout*1000 - delta.tv_sec*1000000)*1000;
        pthread_get_expiration_np(&delta,abstime);
}


fcloseall()
{
return(0);
}

RestIDT()
{
return(0);
}

proc_prova(pthread_addr_t arg)
{
while(1)
	{
	printf("attiper\n");
	attiper();
	wai(20);
	}
}

int SetRootPriv()
{
// blocco il Mutex
pthread_mutex_lock(&RootPrivMutex);

if(getuid()==0)
	return(1); // il processo e' stato attivato da root


if(setreuid(getuid(),0)!= 0)
	{
        fprintf(stderr,"impossibile settare i diritti di super-utente\n");
	return(0);
	}
return(1);
}

int UnSetRootPriv()
{
if(getuid()==0)
	{
	pthread_mutex_unlock(&RootPrivMutex); // sblocco il Mutex
	return(1); // il processo e' stato attivato da root
	}

if(geteuid()!=0)
	{
	pthread_mutex_unlock(&RootPrivMutex); // sblocco il Mutex
	return(0); // il processo non possiede i diritti di root
	}

if(setreuid(getuid(),getuid())!= 0)
	{
	pthread_mutex_unlock(&RootPrivMutex); // sblocco il Mutex
        fprintf(stderr,"impossibile resettare i diritti di utente\n");
	return(0);
	}

pthread_mutex_unlock(&RootPrivMutex); // sblocco il Mutex
return(1);
}

test_p1()
{
QUEUE_PACKET  mess;
char messaggio[40];
struct rusage r_usage;

return(0);
mess.que = 35; 
mess.flg = MSG_WAIT;
mess.wto = 0;
mess.amsg=(char *)messaggio;

wai(90);
while(1)
	{
	//printf("programma test_p1: sospensione\n");
	wai(10);
	wai(10);
	wai(10);
	wai(10);
	wai(10);
	wai(10);
	//printf("programma test_p1: inviato messaggio\n");
	//enqueue(&mess);
	tra(35,1);
	//printf("programma test_p1: dopo invia messaggio\n");
	if(getrusage(RUSAGE_SELF,&r_usage)!=0)
		printf("Errore getrusage\n");
	printf("p1: user %d %d  system %d %d\n",
		r_usage.ru_utime.tv_sec,r_usage.ru_utime.tv_usec,
		r_usage.ru_stime.tv_sec,r_usage.ru_stime.tv_usec);
	}
return(0);
}

test_p2()
{
QUEUE_PACKET  mess;
char messaggio[40];
struct rusage r_usage;
int i;

return(0);
mess.que = 35; 
mess.flg = MSG_WAIT;
mess.wto = 0;
mess.amsg=(char *)messaggio;
while(1)
	{
	//printf("programma test_p2: attesa messaggio\n");
	//dequeue(&mess);
	rew(35,0,&i);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	for(i=0;i<90000;i++);
	//printf("programma test_p2: ricevuto messaggio\n");
	if(getrusage(RUSAGE_SELF,&r_usage)!=0)
		printf("Errore getrusage\n");
	printf("p2: user %d %d  system %d %d\n",
		r_usage.ru_utime.tv_sec,r_usage.ru_utime.tv_usec,
		r_usage.ru_stime.tv_sec,r_usage.ru_stime.tv_usec);
	}
}
