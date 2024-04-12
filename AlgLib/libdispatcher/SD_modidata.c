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
   modulo SD_modidata.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_modidata.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)SD_modidata.c	5.1\t11/7/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "libdispatcher.h"
#include "mod_data.h"


int     SD_modidata (processo, dati, nrighe)
int     processo;
char   *dati;
int nrighe;
{
int k;
char *app_char;
int     ret = -1;
int app_int=nrighe;
int size=nrighe*LUN_RIGA_F14;


    ret = to_dispatcher (processo, COMANDO_MODIDATA, &app_int, sizeof(int));
    app_char=dati;
    
    for(k=0;k<(size/MAX_LUN_COMANDI_DISPATCHER);k++)
	{
    	ret = to_dispatcher (processo, COMANDO_MODIDATA, app_char,
		MAX_LUN_COMANDI_DISPATCHER);
	app_char+=MAX_LUN_COMANDI_DISPATCHER;
	}
	
    k=size-k*MAX_LUN_COMANDI_DISPATCHER;
    ret = to_dispatcher (processo, COMANDO_SAVEIC, app_char,k);
    return (ret);
}
