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
   modulo SD_allinea.c
   tipo 
   release 5.2
   data 2/20/96
   reserved @(#)SD_allinea.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)SD_allinea.c	5.2\t2/20/96";
/*
        Fine sezione per SCCS
*/
#if defined BANCO_MANOVRA
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
#include "agg_manovra.h"


int     SD_allinea (processo, punti_check)
int     processo;
char    *punti_check;
{
int     app_int, comando, size, tipo, k;
int     ret = -1;
char 	*app;

    ret = to_dispatcher (processo, COMANDO_ALLINEA, NULL, 0);
    if(ret<0)
      return(ret);
    /* riceve l'elenco degli elementi disallineati */
    printf("    Riceve l'elenco degli elementi disallineati \n");
    app=punti_check;
    for(k=0;k<(sizeof(ALLINEAMENTO)/MAX_LUN_COMANDI_DISPATCHER);k++)
        {
	comando=DATI_DISPATCHER;
	from_dispatcher (processo, &comando, &tipo, app,
                &size, !IPC_NOWAIT);
	app+=size;
	}
    comando=DATI_DISPATCHER;
    from_dispatcher (processo, &comando, &tipo, app,
              &size, !IPC_NOWAIT);
    app+=size;
    ret=1;
    return (ret);
}
#endif
