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


int kil(int pos)
{
extern TCB *PuntTcb;

if(PuntTcb[pos].stato==INACTIVE_STATE)
	return(1);

if( pthread_equal(pthread_self(), PuntTcb[pos].id)== 1)
	return(1);

PuntTcb[pos].stato=INACTIVE_STATE;

if(pthread_cancel(PuntTcb[pos].id) == 0)
	return(0);
else
	return(1);
}
