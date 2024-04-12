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


int pri(int pos, int prio)
{
extern TCB *PuntTcb;

if((prio > PRI_FIFO_MAX) || (prio < PRI_FIFO_MIN))
	{
	printf("Pri: valore di prio [%d] non accettabile\n",prio);
	return(1);
	}

if(PuntTcb[pos].stato == INACTIVE_STATE)
	return(1);

if(!SetRootPriv())
	{
	UnSetRootPriv();
	return(1);
	}

PuntTcb[pos].prio = prio;

if(pthread_setprio(PuntTcb[pos].id,PuntTcb[pos].prio) != -1)
	{
	UnSetRootPriv();
	return(0);
	}
else
	{
	UnSetRootPriv();
	return(1);
	}
}
