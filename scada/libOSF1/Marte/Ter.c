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
#include <setjmp.h>

#include <Marte/MarteP.h>


void ter()
{
pthread_t self;
int i;
struct timespec delta;
struct timespec abstime;
extern TCB *PuntTcb;


self = pthread_self();

for (i=0;i<MAX_THREAD; i++)
        if( pthread_equal(self, PuntTcb[i].id)== 1)
                break;

if(i == MAX_THREAD)
	{
	fprintf(stderr,"ter: thread non trovato\n");
	return;
	}

if(PuntTcb[i].stato&BOOK_STATE)
	{
	SetBookState(i,0);
	SetTaskState(i,RUNNING_STATE);
	return;
	}

SetTaskState(i,DORMANT_STATE);
if(PuntTcb[i].periodo == 0)
	{
	pthread_mutex_lock(&(PuntTcb[i].mutex));
	pthread_cond_wait(&(PuntTcb[i].condition),&(PuntTcb[i].mutex));
	pthread_mutex_unlock(&(PuntTcb[i].mutex));
	SetTaskState(i,RUNNING_STATE);
	}
else
	{
	/*
		rida' il controllo all routine app_syn (modulo Syn.c)
		con in ingresso RETURN_JMP
	*/
	longjmp(PuntTcb[i].jmp_syn,RETURN_JMP);
	}
}
