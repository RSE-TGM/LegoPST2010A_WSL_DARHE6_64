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

/*
        la chiamata waisim funziona coma la wai ma utilizzando non il tempo
        dell'orologio ma quello del simulatore; la risoluzione e' di 0.5
        secondi.
        Se questa funzione viene chiamata con un tempo inferiore a 0.5
        viene utilizzata la chiamata wai e viene emesso un warning
*/


static void sosp(int);
extern float GetTimeSim();

int waisim(int time)
{
struct timespec interval;
float t_fin;
int save_time = time;

if(time ==0)
	return(1);

time = time * REAL_TIME_CLOCK;
SetTaskState(-1,SUSPENDED_STATE);
t_fin = GetTimeSim()+(float)time/1000.0;


//printf("waisim ingresso [%d]: t_fin = %f  tempo = %f\n",save_time,t_fin,GetTimeSim());
while(t_fin>GetTimeSim())
	{
	sosp(100);
	}
//printf("waisim uscita: t_fin = %f  tempo = %f\n",t_fin,GetTimeSim());


SetTaskState(-1,RUNNING_STATE);
return(0);
}

static void sosp(int time)
{
struct timespec interval;

interval.tv_sec = time/1000;
interval.tv_nsec = (time * 1000 - interval.tv_sec*1000000)*1000;
pthread_delay_np(&interval);
return;
}
