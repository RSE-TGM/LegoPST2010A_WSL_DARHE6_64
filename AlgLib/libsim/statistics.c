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

// --- Include Essenziali Mantenuti ---
#include <stdio.h>        // Per printf, perror, fprintf, stderr
#include <stdlib.h>       // Per NULL (usato da gettimeofday), potenzialmente per exit se usata altrove

#include <errno.h>        // Per la variabile errno usata con perror
#include <sys/time.h>     // Per gettimeofday, struct timeval
#include <sys/resource.h> // Per getrusage, struct rusage, RUSAGE_SELF
#include <sys/types.h>    // Per tipi base usati da altri header di sistema (es. time_t, pid_t se usate)
#include <unistd.h>       // Per _SC_CLK_TCK e sysconf (anche se SCO è stato rimosso, potenziale uso futuro)

// --- Include Specifici del Progetto (Presumibilmente Necessari) ---
#include <statistics.h> // Presumibilmente definisce la struct STATISTICS
#include <string.h>       // Per memcpy

// --- Include Rimossi (Non più necessari per la parte UNIX/getrusage rimasta) ---
// #include <signal.h>    // Non più necessario (era per la vecchia sospendi)
// #include <time.h>      // time_t è in sys/types.h, struct tm non è usata
// #include <locale.h>    // setlocale non è usato qui
// Se SCO_UNIX è definitivamente rimosso:
// #include <sys/times.h> // Era per times() specifico di SCO

// --- Dichiarazioni Forward ---
static double get_tempo();
static int get_system_statistics(double *,double *,double *);
static double gettim(); // Dichiarato static qui

// Definizione ADESSO spostata vicino al suo uso in gettim
#define  ADESSO    700000000     /* shift convenzionale della data   */

// --- Funzioni Principali (non condizionali) ---



int get_statistics(STATISTICS * in_statistics)
{
    static STATISTICS loc_statistics;
    STATISTICS *statistics = &loc_statistics;
    double delta_time;
    double tempo_attuale;
    double user_time, system_time, io_oper;

    // Copia stato iniziale locale
    memcpy(&loc_statistics, in_statistics, sizeof(STATISTICS));

    // Prendi le statistiche correnti
    if (get_system_statistics(&user_time, &system_time, &io_oper) != 0) {
        // Errore recupero statistiche, non continuare i calcoli
        return -1;
    }

    // Calcola i valori assoluti dall'inizio del processo
    user_time -= statistics->first_user_time;
    system_time -= statistics->first_system_time;
    io_oper -= statistics->first_io_oper;

    /*
	calcolo tempo attuale
    */
    tempo_attuale = get_tempo();

    /*
	calcolo intervallo di tempo in millisecondi dall'ultima chiamata
    */
    delta_time = (tempo_attuale - statistics->last_call);

    /*
	registra il tempo della chiamata attuale
    */
    statistics->last_call = tempo_attuale;

    if (delta_time != 0)
    {
        /*
	calcolo utilizzo percentuale durante l'ultima chiamata
        Tempi user/system in microsec, delta_time in millisec
        */
        statistics->user_time = ((user_time / 1000.0) - statistics->tot_user_time) /
                                  delta_time * 100.0;
        statistics->system_time = ((system_time / 1000.0) - statistics->tot_system_time) /
                                    delta_time * 100.0;
        statistics->io_oper = (io_oper - statistics->tot_io_oper) / delta_time * 100.0;


        /*
	calcolo utilizzo percentuale massimo
        */
        if (statistics->user_time > statistics->max_user_time)
            statistics->max_user_time = statistics->user_time;
        if (statistics->system_time > statistics->max_system_time)
            statistics->max_system_time = statistics->system_time;
        if (statistics->io_oper > statistics->max_io_oper)
            statistics->max_io_oper = statistics->io_oper;
    } else {
        // Evita divisione per zero se delta_time è 0
        statistics->user_time = 0.0;
        statistics->system_time = 0.0;
        statistics->io_oper = 0.0;
    }

    /*
	calcolo utilizzo totale (in secondi)
    */
    statistics->tot_user_time = user_time / 1000000.0; // us -> s
    statistics->tot_system_time = system_time / 1000000.0; // us -> s
    statistics->tot_io_oper = io_oper;

    // Calcolo media percentuale
    double delta_time_total = (tempo_attuale - statistics->start_process); // ms
    if (delta_time_total != 0)
    {
        statistics->ave_user_time = (statistics->tot_user_time * 1000.0) / // s -> ms
                                     delta_time_total * 100.0;
        statistics->ave_system_time = (statistics->tot_system_time * 1000.0) / // s -> ms
                                       delta_time_total * 100.0;
        statistics->ave_io_oper = statistics->tot_io_oper /
                                  delta_time_total * 100.0;
    } else {
        statistics->ave_user_time = 0.0;
        statistics->ave_system_time = 0.0;
        statistics->ave_io_oper = 0.0;
    }

    // Copia stato finale indietro
    memcpy(in_statistics, &loc_statistics, sizeof(STATISTICS));
    return 0;
}

int print_statistics(STATISTICS * in_statistics)
{
    printf("user_time:   %f %% (last), max=%f %%, tot=%f s, media=%f %%\n",
           in_statistics->user_time, in_statistics->max_user_time,
           in_statistics->tot_user_time, in_statistics->ave_user_time);
    printf("system_time: %f %% (last), max=%f %%, tot=%f s, media=%f %%\n",
           in_statistics->system_time, in_statistics->max_system_time,
           in_statistics->tot_system_time, in_statistics->ave_system_time);
    printf("io_oper:     %f %% (last), max=%f %%, tot=%f, media=%f %%\n",
           in_statistics->io_oper, in_statistics->max_io_oper,
           in_statistics->tot_io_oper, in_statistics->ave_io_oper);
    return 0;
}

int init_statistics(STATISTICS * in_statistics)
{
    in_statistics->user_time = 0;
    in_statistics->tot_user_time = 0;
    in_statistics->max_user_time = 0;
    in_statistics->ave_user_time = 0;

    in_statistics->system_time = 0;
    in_statistics->tot_system_time = 0;
    in_statistics->max_system_time = 0;
    in_statistics->ave_system_time = 0;

    in_statistics->io_oper = 0;
    in_statistics->tot_io_oper = 0;
    in_statistics->max_io_oper = 0;
    in_statistics->ave_io_oper = 0;

    in_statistics->start_process = get_tempo();
    in_statistics->last_call = in_statistics->start_process;

    if (get_system_statistics(&(in_statistics->first_user_time),
                          &(in_statistics->first_system_time),
                          &(in_statistics->first_io_oper)) != 0) {
         // Errore nell'ottenere i valori iniziali, forse uscire o segnalare
         return -1;
    }

    return 0;
}


// --- Funzioni Ausiliarie (statiche) ---

/* GETTIM - restituisce il tempo di orologio in millisecondi         */
static double gettim()
{
    int ret ;
    double tempo;
    struct timeval tp;

    ret = gettimeofday(&tp, NULL);
    if (ret == -1) {
        perror("gettim - errore gettimeofday");
        return 0.0; // o gestisci errore
    }
    // Calcolo millisecondi dall'epoch + ADESSO shift
    tempo = (1000.0 * (tp.tv_sec - ADESSO) + tp.tv_usec / 1000.0);
    return (tempo);
}


static double get_tempo()
{
    return gettim();
}


// --- Parte Specifica UNIX (solo get_system_statistics) ---

static int get_system_statistics(double *user_time, double *system_time,
                                 double *io_oper)
{
    struct rusage r_usage;

    if (getrusage(RUSAGE_SELF, &r_usage) != 0) {
        perror("get_system_statistics - errore getrusage");
        *user_time = 0.0;
        *system_time = 0.0;
        *io_oper = 0.0;
        return -1;
    }
    // Converti tutto in microsecondi (come double)
    *user_time = (double)(r_usage.ru_utime.tv_sec) * 1000000.0 +
                 (double)r_usage.ru_utime.tv_usec;
    *system_time = (double)(r_usage.ru_stime.tv_sec) * 1000000.0 +
                   (double)r_usage.ru_stime.tv_usec;
    *io_oper = (double)(r_usage.ru_inblock + r_usage.ru_oublock);

    return 0; // Successo
}
