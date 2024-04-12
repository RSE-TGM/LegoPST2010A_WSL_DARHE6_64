/**********************************************************************
*
*       C Source:               GetTime.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 14:31:35 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: GetTime.c-4 %  (%full_filespec: GetTime.c-4:csrc:1 %)";
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
#ifndef LINUX
#include <sys/timers.h>
#endif

/*

	restituisce la data corrente nel in tre interi nel formato
	
		gg mm aa

*/

#if defined ENEL_SIM
int ora_simulatore = 0;
int minuti_simulatore = 0;
int secondi_simulatore = 0;
int milli_simulatore = 0;
int giorno_simulatore = 0;
int giornowk_simulatore = 0;
int mese_simulatore = 0;
int anno_simulatore = 1996;
float tempo_simulatore = 0.;
#endif

int    GetData (giorno, mese, anno, gio_set, gio_anno)
int    *giorno;
int    *mese;
int    *anno;
int    *gio_set;
int    *gio_anno;
{
#if defined ENEL_SIM
memcpy(giorno,&giorno_simulatore,sizeof(int));
memcpy(mese,&mese_simulatore,sizeof(int));
memcpy(anno,&anno_simulatore,sizeof(int));
memcpy(gio_set,&giornowk_simulatore,sizeof(int));
#else
struct tm  strutt_tempo;
int     tempo_time;
int ret;

    time (&tempo_time);

    ret = localtime_r (&tempo_time,&strutt_tempo);
    if (ret != 0)
	return (-1);

    *giorno = strutt_tempo.tm_mday;
    *mese = strutt_tempo.tm_mon + 1;
    *anno = strutt_tempo.tm_year + 1900;
    *gio_set = strutt_tempo.tm_wday;
    *gio_anno = strutt_tempo.tm_year;
#endif
    return (1);
}

/*

	restituisce l'ora corrente nel in tre interi nel formato
	
		hh mm ss millisec

*/

int    GetOra (ora, minuti, secondi,millisec)
int    *ora;
int    *minuti;
int    *secondi;
int    *millisec;
{
#if defined ENEL_SIM
memcpy(ora,&ora_simulatore,sizeof(int));
memcpy(minuti,&minuti_simulatore,sizeof(int));
memcpy(secondi,&secondi_simulatore,sizeof(int));
memcpy(millisec,&milli_simulatore,sizeof(int));
#else
struct tm  strutt_tempo;
int     tempo_time;
struct timespec tp;
int ret;



    time (&tempo_time);

    ret = localtime_r (&tempo_time,&strutt_tempo);
    if (ret != 0)
	return (-1);
    getclock(TIMEOFDAY,&tp);

    *ora = strutt_tempo.tm_hour;
    *minuti = strutt_tempo.tm_min;
    *secondi = strutt_tempo.tm_sec;
    *millisec = tp.tv_nsec/1000000;
#endif
    return (1);
}

#if defined ENEL_SIM
float    GetTimeSim ()
{
return(tempo_simulatore);
}
#endif

