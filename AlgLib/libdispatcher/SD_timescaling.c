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
static char SccsID[] = "@(#)SD_timescaling.c	5.1\t11/7/95";
/*
   modulo SD_timescaling.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_timescaling.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"



int     SD_timescaling (processo, valore)
int     processo;
float   *valore;
{
float   app_float;
int     ret = -1;

    memcpy(&app_float, valore, sizeof(float));
    ret = to_dispatcher (processo, COMANDO_TIMESCALING,&app_float, sizeof (float));
    return (ret);
}
