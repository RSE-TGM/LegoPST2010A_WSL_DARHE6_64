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

#include <pthread.h>
#include <stdio.h>
#if defined UNIX
# include <errno.h>
# include <stdio.h>
# include <setjmp.h>
# include <sys/signal.h>
# include <unistd.h>
#include <sys/time.h>
#endif
#if defined VMS
#include <ssdef.h>
#include <psldef.h>
#include <iodef.h>
#include <descrip.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#endif
#include "sim_param.h"
#include "agg_scada.h"

#define MAX_ALLOC_MODEL 100000000
#define TIMEOUT_SCAD -100

extern int id_msg_pert;

int ricevo_pert();

static jmp_buf Jmp;               /* struttura per il timer  */

/* ************************************************************* */

int timeout_ricevi()
{
        longjmp(Jmp,TIMEOUT_SCAD);
}

/* ************************************************************* */

int ricevo_pert(fp)
int fp;
{
int mod;
int millisec=300;
char app[12];
int ind;
float val;
short tipo_pert;
int tipo;
int ind_sked;
#if defined UNIX
struct itimerval value,ovalue;   /* variabili per setitimer       */
long micro_secondi;
long secondi;
#endif

/*
if(setjmp(Jmp)==TIMEOUT_SCAD)
       {
       return(-1);
       }
signal(SIGALRM,timeout_ricevi);
#if defined UNIX
micro_secondi=(long)(millisec*1000);
secondi=(long)(0);
value.it_interval.tv_sec  = (long)0.0;
value.it_interval.tv_usec = (long)0.0;
value.it_value.tv_sec  = secondi;
value.it_value.tv_usec = micro_secondi;
setitimer(ITIMER_REAL,&value,&ovalue);
#endif
#if defined VMS
alarm(1);
#endif
*/


while(1)
       {
if(readn(fp,&app[0],sizeof(char)*12)<0)
	{
	errore("caduta connessione con scada su porta ricevimento comandi");
	}
//alarm(0);
memcpy(&tipo_pert,&app[2],sizeof(short));
memcpy(&ind,&app[4],sizeof(int));
memcpy(&val,&app[8],sizeof(float));
if (tipo_pert==259)
	tipo=0;
else
	tipo=1;
ind_sked=scada_to_sked(ind,tipo);
printf(" tipo =%d ind_scada=%d ind_sked=%d val=%f\n\n\n",
		tipo,ind,ind_sked,val);
mod=ind_sked/MAX_ALLOC_MODEL;
if(ind_sked != (-1))
	{
	/* trovato indirizzo della variabile*/
	/* verifico che il messaggio non sia un impulso*/
	if((tipo_pert==260)&&(val == -1.))
		{
		pert_impulso(id_msg_pert,ind_sked,1.,0.,0.);
printf("pert_impulso ind_sked = %d\n",ind_sked);
		}
	else	
		{
		pert_scalino(id_msg_pert,ind_sked,val,0.);
printf("pert_scalino ind_sked = %d valore %f\n",ind_sked,val);
		}
	ack_send(fp);
	}
       }
}
