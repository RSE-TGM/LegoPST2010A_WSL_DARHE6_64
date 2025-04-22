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


#include <time.h> // Già incluso, ma assicurati che ci sia per struct timespec e nanosleep
#include <errno.h> // Per controllare l'errore di nanosleep
#include <stdio.h> // Per printf in caso di errore
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/time.h>
#include <locale.h>
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

// Vecchia sospendi sostituita 
// static void handler_attesa(signum,code,scp)
//    int signum, code;
//    struct sigcontext *scp;
//   {
//    if( signum == SIGALRM )
//      {
//       signal(SIGALRM,handler_attesa);  /*   installazione sig_handler */
//       return;
//      }
//   }
//
// void sospendi(millisec)
// unsigned int millisec;
// {
// struct itimerval value,ovalue;   /* variabili per setitimer       */
// long micro_secondi;
// long secondi;

// if(millisec>0)
//    {
//       micro_secondi=(long)(millisec*1000);
//       secondi=(long)(micro_secondi/1000000);
//       micro_secondi=(long)(micro_secondi-secondi*1000000);
//       value.it_interval.tv_sec  = (long)0.0;
//       value.it_interval.tv_usec = (long)0.0;
//       value.it_value.tv_sec  = secondi;
//       value.it_value.tv_usec = micro_secondi;
//       signal(SIGALRM,handler_attesa);   /*   installazione sig_handler */
//       sigblock(sigmask(SIGALRM));      /*  blocca il segnale  */
//       setitimer(ITIMER_REAL,&value,&ovalue);
//       sigpause(0);   /* sblocca il segnale e attende */
//       /* sblocca tutti i segnali  */
//       sigsetmask(0);
//   }
// }




// Rimuovi o commenta le dichiarazioni di handler_attesa e le direttive #if specifiche
/*
#if defined SCO_UNIX
static void handler_attesa(signum) int signum; { return; }
#else
static void handler_attesa(signum,code,scp) int signum, code; struct sigcontext *scp; { ... }
#endif
*/

void sospendi(unsigned int millisec)
{
    struct timespec req, rem;
    int ret;

    if (millisec > 0)
    {
        // Calcola i secondi e i nanosecondi
        req.tv_sec = millisec / 1000;
        req.tv_nsec = (millisec % 1000) * 1000000L; // Converti ms rimanenti in nanosecondi

        // Chiama nanosleep. Gestisce le interruzioni da segnali.
        // Il ciclo do-while con controllo EINTR assicura che l'attesa
        // venga completata anche se nanosleep viene interrotto da un segnale.
        do {
            ret = nanosleep(&req, &rem);
            // Se nanosleep viene interrotto (EINTR), copia il tempo rimanente (rem)
            // in req e riprova a dormire per il tempo residuo.
            if (ret == -1 && errno == EINTR) {
                req = rem;
            }
        } while (ret == -1 && errno == EINTR);

        // Puoi aggiungere un controllo per altri errori se necessario
        // if (ret == -1) {
        //     perror("nanosleep error");
        // }
    }
}

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
