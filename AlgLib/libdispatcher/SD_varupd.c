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
   modulo SD_varupd.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_varupd.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)SD_varupd.c	5.1\t11/7/95";
/*
        Fine sezione per SCCS
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


int     SD_varupd (processo, dati, lungh)
int     processo;
char    *dati;     /* buffer per label e dati          */
int     lungh;        
{
int     comando, size, tipo, k,n;
int     ret = -1;
char 	*app;

/*
 * manda a sked la lista delle variabili 
 */
	app = dati;                 
	for(k=0;k<(lungh/MAX_LUN_COMANDI_DISPATCHER);k++)
        	{
			printf ("VARUPD: mando %d bytes interni al loop\n",
						MAX_LUN_COMANDI_DISPATCHER);
    		if ((ret = to_dispatcher (processo, 
								COMANDO_VARUPD, 
								app, 
								MAX_LUN_COMANDI_DISPATCHER)) <0)
				return(ret);
			app += MAX_LUN_COMANDI_DISPATCHER;
			}

	n = lungh - k*MAX_LUN_COMANDI_DISPATCHER;
	if ((ret = to_dispatcher (processo, COMANDO_VARUPD, app, n)) <0)
            return(ret);
/*	printf ("SD_varupd: mandati %d bytes in %d cicli\n",lungh,k+1);  */
/* 
 * riceve la struttura con i valori delle variabili 
 */
    app=dati;
	comando=DATI_DISPATCHER;
     for(k=0;k<(lungh/MAX_LUN_COMANDI_DISPATCHER);k++)
        {
			from_dispatcher (processo, &comando, &tipo, app,
                &size, !IPC_NOWAIT);
			app+=MAX_LUN_COMANDI_DISPATCHER;
/*	printf ("SD_varupd: ricevuto ciclo %d\n",k+1); */
			}
     from_dispatcher (processo, &comando, &tipo, app,
                &size, !IPC_NOWAIT);
/*	printf ("SD_varupd: ricevuto ciclo %d\n",k+1);  */
    return (ret);
}
