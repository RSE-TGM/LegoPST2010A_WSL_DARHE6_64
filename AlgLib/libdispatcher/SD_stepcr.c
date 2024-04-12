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
static char SccsID[] = "@(#)SD_stepcr.c	5.1\t11/7/95";
/*
   modulo SD_stepcr.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_stepcr.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"


int     SD_stepcr (processo, valore)
int     processo;
int     *valore;
{
int     app_int;
int     ret = -1;

    memcpy(&app_int, valore, sizeof(int));
    ret = to_dispatcher (processo, COMANDO_STEPCR, &app_int, sizeof (int));
    return (ret);
}
