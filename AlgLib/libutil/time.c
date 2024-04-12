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
static char SccsID[] = "@(#)time.c	5.3\t1/18/96";
/*
   modulo time.c
   tipo 
   release 5.3
   data 1/18/96
   reserved @(#)time.c	5.3
*/
#if defined UNIX
#include <stdio.h>
#include <sys/time.h>
#include <locale.h>
#include <errno.h>
#include <signal.h>

#define  ADESSO    700000000     /* shift convenzionale della data   */

/* GETTIM - restituisce il tempo di orologio in millisecondi         */

double gettim()

       {
        int ret ;
        double tempo;
        struct timeval tp;
        struct timezone tzp;
        /* gettimeofday(); */
        ret = gettimeofday(&tp,&tzp);
        if(ret == -1)
        	printf("gettim - errore lettura tempo n. %d\n",errno);
	tempo=(1000.0*(tp.tv_sec-ADESSO) + tp.tv_usec/1000.0);
        return(tempo);
       }

#if defined SCO_UNIX

static void handler_attesa(signum)
   int signum;
   
  {
   
      return;
  }

#else 
static void handler_attesa(signum,code,scp)
   int signum, code;
   struct sigcontext *scp;
  {
   if( signum == SIGALRM )
     {
      signal(SIGALRM,handler_attesa);  /*   installazione sig_handler */
      return;
     }
  }

#endif
sospendi(millisec)
unsigned int millisec;
{
struct itimerval value,ovalue;   /* variabili per setitimer       */
long micro_secondi;
long secondi;

if(millisec>0)
   {
      micro_secondi=(long)(millisec*1000);
      secondi=(long)(micro_secondi/1000000);
      micro_secondi=(long)(micro_secondi-secondi*1000000);
      value.it_interval.tv_sec  = (long)0.0;
      value.it_interval.tv_usec = (long)0.0;
      value.it_value.tv_sec  = secondi;
      value.it_value.tv_usec = micro_secondi;


#if defined SCO_UNIX

      signal(SIGALRM,handler_attesa);   /*   installazione sig_handler */
      sighold(SIGALRM);			/* blocca il segnale */
      setitimer(ITIMER_REAL,&value,&ovalue);
      sigpause(SIGALRM);

#else
      signal(SIGALRM,handler_attesa);   /*   installazione sig_handler */
      sigblock(sigmask(SIGALRM));      /*  blocca il segnale  */
      setitimer(ITIMER_REAL,&value,&ovalue);
      sigpause(0);   /* sblocca il segnale e attende */

      /* sblocca tutti i segnali  */
      sigsetmask(0);

#endif
  }
}

#endif

#if defined VMS
#include <stdio.h>
#include <math.h>
#include <iodef.h>
#include <psldef.h>
#include <ssdef.h>
#include <secdef.h>
#include <signal.h>

/* ritorna il tempo dell'orologio di sistema in millisecondi */

double gettim()
{
unsigned int stato;
double tempo;
unsigned long ret;
char app_ret[8];
float app_t;
unsigned long base=4294967295;
static unsigned long inizio=(-1);

        /* legge il tempo di sistema e lo inserisce in un quad-word */
        stato=SYS$GETTIM(&app_ret[0]);
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }

        /* ricopia il byte 1-2-3-4 in un unsigned int */
        memcpy(&ret,&app_ret[1],sizeof(long));

        /* normalizza a zero il valore ottenuto */
        if(inizio==(-1))
                inizio=ret;
        if(ret<inizio)
                ret=ret+(base-inizio);
        else
                ret=ret-inizio;
        tempo=ret;

        /* normalizza a millisecondi il valore ottenuto */
        tempo=tempo*256/10000;

        return(tempo);
}



/* iberna il processo per un certo numero di millisecondi
   il valore minimo di tale tempo e' 10 millisecondi      */

sospendi(millisec)
unsigned int millisec;
{
float app;
char app_0[8];
char app_1[8];
char app_2[8];
char app_ch=0;
unsigned int stato;

        /* normalizza il tempo per essere inserito in un quad-word */
        app=millisec;
        app=app*10000/256;
        millisec=app;
        /* inserisce il valore ottenuto in un quad-word */
        memcpy(&app_0[0],&app_ch,sizeof(char));
        memcpy(&app_0[1],&millisec,sizeof(long));
        memcpy(&app_0[5],&app_ch,sizeof(char));
        memcpy(&app_0[6],&app_ch,sizeof(char));
        memcpy(&app_0[7],&app_ch,sizeof(char));
        /* legge il tempo di sistema */
        stato=SYS$GETTIM(&app_1[0]);
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }
        /* somma il tempo di sistema con il tempo di attesa */
        stato=LIB$ADDX(&app_0[0],&app_1[0],&app_2[0]);
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }
        /* setta la wake */
        stato=SYS$SCHDWK(0,0,&app_2[0],0);
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }
        /* ibernazione del processo */
        stato=SYS$HIBER();
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }
}

#endif

#if defined HELIOS
#include <stdio.h>
#include <syslib.h>
#include <sys/time.h>
#include <errno.h>

#define  ADESSO    700000000     /* shift convenzionale della data   */

/* GETTIM - restituisce il tempo di orologio in millisecondi         */

double gettim()

       {
        int ret ;
        double tempo;
        struct timeval tp;
        struct timezone tzp;
        /* gettimeofday(); */
        ret = gettimeofday(&tp,&tzp);
        if(ret == -1)
        	printf("gettim - errore lettura tempo n. %d\n",errno);
	tempo=(1000.0*(tp.tv_sec-ADESSO) + tp.tv_usec/1000.0);
        return(tempo);
       }

sospendi(millisec)
unsigned int millisec;
{
	Delay(millisec*1000);
}
#endif


char *GetStrTime()
{
char *ret;
time_t nowbin;
struct tm *nowstruct;

    (void)setlocale(LC_ALL, "");

    if (time(&nowbin) == (time_t) - 1)
	{
        fprintf(stderr,"Could not get time of day from time()\n");
	return(ret);
	}

    nowstruct = localtime(&nowbin);

    ret=(char*)malloc(50);
    if (strftime(ret, 50, "%T %x", nowstruct) == (size_t) 0)
	{
        fprintf(stderr,"Could not get string from strftime()\n");
	return(ret);
	}

return(ret);
}
