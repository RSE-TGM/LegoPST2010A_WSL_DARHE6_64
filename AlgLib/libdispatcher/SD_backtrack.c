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
static char SccsID[] = "@(#)SD_backtrack.c	5.1\t11/7/95";
/*
   modulo SD_backtrack.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_backtrack.c	5.1
*/
#include <stdio.h>
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"


int     SD_backtrack (processo)
int     processo;
{
int     ret = -1;

    ret = to_dispatcher (processo, COMANDO_BACKTRACK, NULL, 0);
    return (ret);
}
