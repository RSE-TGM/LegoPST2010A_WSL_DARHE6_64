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
static char SccsID[] = "@(#)SD_loadbt.c	5.1\t11/7/95";
/*
   modulo SD_loadbt.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_loadbt.c	5.1
*/
#if defined BACKTRACK
#include <stdio.h>
#include <string.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#endif
#if defined VMS
#include "vmsipc.h"
#endif
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "libdispatcher.h"


int     SD_loadbt (processo, posizione
#if defined MFFR
,sommari
#endif
)
int     processo;
int     *posizione;
#if defined MFFR
char    *sommari;
#endif
{
int     app_int, comando, size, tipo, k;
int     ret = -1;
char 	*app;

    memcpy(&app_int,  posizione,sizeof(int));
    ret = to_dispatcher (processo, COMANDO_LOADBT, &app_int, sizeof (int));
#if defined MFFR
    if(ret<0)
		return(ret);
    /* riceve i sommari e malfunzioni remote */
    app=sommari;
     for(k=0;k<(sizeof(SNAP_SKED)/MAX_LUN_COMANDI_DISPATCHER);k++)
        {
	comando=DATI_DISPATCHER;
	from_dispatcher (processo, &comando, &tipo, app,
                &size, !IPC_NOWAIT);
	app+=MAX_LUN_COMANDI_DISPATCHER;
	}
     from_dispatcher (processo, &comando, &tipo, app,
                &size, !IPC_NOWAIT);
#endif
    return (ret);
}
#endif
