/**********************************************************************
*
*       C Source:               SD_loadic.c
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Tue Nov 26 16:58:28 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: SD_loadic.c-3 %  (%full_filespec: SD_loadic.c-3:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)SD_loadic.c	5.2\t2/21/96";
/*
   modulo SD_loadic.c
   tipo 
   release 5.2
   data 2/21/96
   reserved @(#)SD_loadic.c	5.2
*/
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


int     SD_loadic (processo, posizione , sommari)
int     processo;
int     *posizione;
char    *sommari;
{
int     app_int, comando, size, tipo, k;
int     ret = -1;
char 	*app;

    memcpy(&app_int,  posizione,sizeof(int));
    ret = to_dispatcher (processo, COMANDO_LOADIC, &app_int, sizeof (int));
#if defined MFFR
    if(ret<0)
       return(ret);
    /* riceve i sommari e malfunzioni remote */
    /* printf("\n SD_loadic riceve i sommari e malfunzioni remote\n"); */

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
     /* printf(" Fine SD_loadic (dopo ciclo from_dispatcher)\n"); */
#endif
    return (ret);
}
