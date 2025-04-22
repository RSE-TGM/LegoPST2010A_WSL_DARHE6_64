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
static char SccsID[] = "@(#)statistics.c	5.1\t11/10/95";
/*
   modulo statistics.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)statistics.c	5.1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#if defined UNIX
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/time.h>
#if defined SCO_UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#endif
#else
#include <ssdef.h>
#include <stsdef.h>
#include <jpidef.h>
#include <descrip.h>
#include <starlet.h>
#endif
#include <statistics.h>

static double get_tempo();
static int get_system_statistics(double *,double *,double *);

int get_statistics(STATISTICS * in_statistics)
{
static STATISTICS loc_statistics;
STATISTICS *statistics = &loc_statistics;
double delta_time;
double tempo_attuale;
double user_time,system_time,io_oper;

memcpy(&loc_statistics,in_statistics,sizeof(STATISTICS));


get_system_statistics(&user_time,&system_time,&io_oper);

user_time -= statistics->first_user_time;
system_time -= statistics->first_system_time;
io_oper -= statistics->first_io_oper;

/*
	calcolo tempo attuale
*/
tempo_attuale= get_tempo();

/*
	calcolo intervallo di tempo in micro-secondi
*/
delta_time=(tempo_attuale- statistics->last_call)*1000;




/*
	registra il tempo della chiamata
*/
statistics->last_call=get_tempo();


if(delta_time!=0)
{
/*
	calcolo utilizzo percentuale durante l'ultima chiamata
*/

statistics->user_time=((user_time - statistics->tot_user_time*1000)/
			delta_time)*100;
statistics->system_time=((system_time - statistics->tot_system_time*1000)/
			delta_time)*100;
statistics->io_oper=((io_oper - statistics->tot_io_oper)/delta_time)*100;


/*
	calcolo utilizzo percentuale massimo
*/
if(statistics->user_time>statistics->max_user_time)
	statistics->max_user_time=statistics->user_time;
if(statistics->system_time>statistics->max_system_time)
	statistics->max_system_time=statistics->system_time;
if(statistics->io_oper>statistics->max_io_oper)
	statistics->max_io_oper=statistics->io_oper;
}

/*
	calcolo utilizzo totale
*/
statistics->tot_user_time=(user_time)/1000;
statistics->tot_system_time=(system_time)/1000;
statistics->tot_io_oper=(io_oper);


if(delta_time!=0)
{
/*
	calcolo utilizzo medio
*/
statistics->ave_user_time=statistics->tot_user_time/
		((tempo_attuale-statistics->start_process))*100;
statistics->ave_system_time=statistics->tot_system_time/
		((tempo_attuale-statistics->start_process))*100;
statistics->ave_io_oper=statistics->tot_io_oper/
		((tempo_attuale-statistics->start_process))*100;
}	
memcpy(in_statistics,&loc_statistics,sizeof(STATISTICS));

}

int print_statistics(STATISTICS *in_statistics)
{

static STATISTICS loc_statistics;
STATISTICS *statistics = &loc_statistics;

memcpy(&loc_statistics,in_statistics,sizeof(STATISTICS));

printf("user_time:   %f   max=%f  tot=%f  media=%f \n",
	statistics->user_time,statistics->max_user_time,
	statistics->tot_user_time,statistics->ave_user_time);
printf("system_time: %f   max=%f  tot=%f  media=%f \n",
	statistics->system_time,statistics->max_system_time,
	statistics->tot_system_time,statistics->ave_system_time);
printf("io_oper:     %f   max=%f  tot=%f  media=%f \n",
	statistics->io_oper, statistics->max_io_oper,
	statistics->tot_io_oper,statistics->ave_io_oper);
}

int init_statistics(STATISTICS * in_statistics)
{
STATISTICS statistics_loc;
STATISTICS *statistics;


memcpy(&statistics_loc,in_statistics,sizeof(STATISTICS));

statistics= &statistics_loc;

statistics->user_time=0;
statistics->tot_user_time=0;
statistics->max_user_time=0;
statistics->ave_user_time=0;

statistics->system_time=0;
statistics->tot_system_time=0;
statistics->max_system_time=0;
statistics->ave_system_time=0;

statistics->io_oper=0;
statistics->tot_io_oper=0;
statistics->max_io_oper=0;
statistics->ave_io_oper=0;

statistics->start_process=get_tempo();
statistics->last_call=statistics->start_process;
get_system_statistics(&(statistics->first_user_time),
		      &(statistics->first_system_time),
		      &(statistics->first_io_oper));
get_statistics(statistics);
memcpy(in_statistics,&statistics_loc,sizeof(STATISTICS));
memcpy(in_statistics,&statistics_loc,sizeof(STATISTICS));
}


static double get_tempo()

       {
	double gettim();
	double tempo=0;
	


	tempo=gettim();
	return(tempo);
       }

static int get_system_statistics(double *user_time,double *system_time,
		double *io_oper)
{
#if defined UNIX
/*
	ricavo le statistiche dal sistema
*/
#if defined SCO_UNIX
struct tms buffer;

if(times(&buffer)== -1)
	fprintf(stderr,"Errore [times]\n");
*user_time=(double)((float)(buffer.tms_utime*sysconf(_SC_CLK_TCK)));
*system_time=(double)((float)(buffer.tms_stime*sysconf(_SC_CLK_TCK)));
*io_oper=(double)(0);
#else
struct rusage r_usage;

if(getrusage(RUSAGE_SELF,&r_usage)!=0)
	fprintf(stderr,"Errore [getrusage]\n");
*user_time=(double)((float)(r_usage.ru_utime.tv_sec)*1000000+
		r_usage.ru_utime.tv_usec);
*system_time=(double)((float)(r_usage.ru_stime.tv_sec)*1000000+
		r_usage.ru_stime.tv_usec);
*io_oper=(double)(r_usage.ru_inblock+r_usage.ru_oublock);
#endif

#else
int status;                         /* Status of system calls */
int miopid;
int retcputim;
int buf_io,dir_io;

/* Initialize $GETJPI item list... */
ITMLST   item_list[6] = {
                  { 4, JPI$_DIRIO,         &dir_io,    0},
                  { 4, JPI$_BUFIO,         &buf_io,    0},
                  { 4, JPI$_CPUTIM,   &retcputim,    0},
                  { 0, 0,            0,             0} };

miopid=getpid();

status = sys$getjpiw(0, &miopid, 0, item_list, 0, 0, 0);
if (status & STS$M_SUCCESS)
   {
   retcputim = retcputim *10000;
   *user_time=(double)(retcputim);
   *system_time=(double)0;
   *io_oper=(double)(buf_io+dir_io);
   }
else
   {
   fprintf(stderr,"Errore [sys$getjpiw]\n");
   *user_time=(double)0.;
   *system_time=(double)0.;
   *io_oper=(double)0.;
   }
#endif
}
