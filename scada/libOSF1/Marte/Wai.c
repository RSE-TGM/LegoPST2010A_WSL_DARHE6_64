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


int wai(int time)
{
struct timespec interval;

if(time ==0)
	return(1);

time = time * REAL_TIME_CLOCK;

SetTaskState(-1,SUSPENDED_STATE);
interval.tv_sec = time/1000;
interval.tv_nsec = (time * 1000 - interval.tv_sec*1000000)*1000;
if(interval.tv_nsec > 8000)
	interval.tv_nsec -=8000;
/**
printf("wai sec = %d nsec = %d\n",interval.tv_sec,interval.tv_nsec);
**/
if(pthread_delay_np(&interval) == 0)
	{
	SetTaskState(-1,RUNNING_STATE);
	return(0);
	}
else
	{
	SetTaskState(-1,RUNNING_STATE);
	return(1);
	}
}

int fwai(float ftime)
{
struct timespec interval;
int time;

if(ftime ==0)
	return(1);

time = ftime * REAL_TIME_CLOCK;

SetTaskState(-1,SUSPENDED_STATE);
interval.tv_sec = time/1000;
interval.tv_nsec = (time * 1000 - interval.tv_sec*1000000)*1000;
/**
printf("wai sec = %d nsec = %d\n",interval.tv_sec,interval.tv_nsec);
**/
if(pthread_delay_np(&interval) == 0)
	{
	SetTaskState(-1,RUNNING_STATE);
	return(0);
	}
else
	{
	SetTaskState(-1,RUNNING_STATE);
	return(1);
	}
}
