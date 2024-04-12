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
static char SccsID[] = "@(#)SD_lbtload.c	5.1\t11/7/95";
/*
   modulo SD_lbtload.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_lbtload.c	5.1
*/
#include <stdio.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#endif
#if defined VMS
#include "vmsipc.h"
#endif
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"


int     SD_lbtload (processo)
int     processo;
{
int     ret = -1;
int     i, comando, size, tipo;

    ret = to_dispatcher (processo, COMANDO_LBTLOAD, NULL, 0);
    comando=DATI_DISPATCHER;
    if(ret>0)
	from_dispatcher (processo, &comando, 
			&tipo, &ret, &size, !IPC_NOWAIT);
    if(size!=sizeof(int))
	ret= -1;

    return (ret);
}
