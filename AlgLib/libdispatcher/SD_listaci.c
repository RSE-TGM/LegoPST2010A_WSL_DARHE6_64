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
static char SccsID[] = "@(#)SD_listaci.c	5.1\t11/7/95";
/*
   modulo SD_listaci.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_listaci.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"



int     SD_listaci (processo, variabile, posizione)
int     processo;
char    *variabile;
int	posizione;
{
char    app[sizeof(int)+MAX_LUN_NOME_VAR];
int     ret = -1;

    if((posizione>MAX_VAL_SNAP)||(posizione<1))
	return(-1);
    memcpy(&app[0], &posizione, sizeof(int));
    memcpy(&app[4], variabile, MAX_LUN_NOME_VAR);
    ret = to_dispatcher (processo, COMANDO_LISTACI,
		&app[0], sizeof (int) + MAX_LUN_NOME_VAR);
    return (ret);
}
