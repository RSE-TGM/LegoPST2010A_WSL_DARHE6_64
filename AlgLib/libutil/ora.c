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
static char SccsID[] = "@(#)ora.c	5.1\t11/10/95";
/*
   modulo ora.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)ora.c	5.1
*/
#include <stdio.h>
#include <time.h>

/*

	restituisce l'ora corrente nel in tre interi nel formato
	
		hh mm ss

*/

int     ora (ora, minuti, secondi)
int    *ora;
int    *minuti;
int    *secondi;
{
struct tm  *strutt_tempo;
int     tempo_time;

    time (&tempo_time);

    strutt_tempo = localtime (&tempo_time);
    if (strutt_tempo == NULL)
	return (-1);

    *ora = strutt_tempo -> tm_hour;
    *minuti = strutt_tempo -> tm_min;
    *secondi = strutt_tempo -> tm_sec;
    return (1);
}
