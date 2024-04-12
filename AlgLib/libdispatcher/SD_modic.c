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
static char SccsID[] = "@(#)SD_modic.c	5.1\t11/7/95";
/*
   modulo SD_modic.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)SD_modic.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "libdispatcher.h"


int     SD_modic (processo, posizione, descrizione)
int     processo;
int    *posizione;
char   *descrizione;
{
#if defined MFFR
char    app[SNAP_DESC + 4 + sizeof(SNAP_SKED)];
int k;
char *app_char;
#else
char    app[SNAP_DESC + 4];
#endif
int     ret = -1;

    memcpy (&app[0], posizione, sizeof (int));
    if (descrizione != NULL)
	memcpy (&app[4], descrizione, SNAP_DESC);
    ret = to_dispatcher (processo, COMANDO_MODIC, app, 
					SNAP_DESC + sizeof (int));
    return (ret);
}
