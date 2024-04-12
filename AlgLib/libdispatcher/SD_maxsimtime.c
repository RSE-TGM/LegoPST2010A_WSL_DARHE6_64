/**********************************************************************
*
*	C %name:		SD_maxsimtime.c %
*	Instance:		1
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Thu Oct 13 17:44:13 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: SD_maxsimtime.c-1 %  (%full_filespec: SD_maxsimtime.c-1:csrc:1 %)";
#endif

#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "dispatcher.h"
#include "libdispatcher.h"

int     SD_maxsimtime (processo, valore)
int     processo;
float   *valore;
{
float   app_float;
int     ret = -1;

    memcpy(&app_float, valore, sizeof(float));
printf("SD_maxsimtime app_float = |%f| valore = |%f|\n", app_float, *valore);
printf("SD_maxsimtime comando = |%d|\n", COMANDO_MAXSIMTIME);
    ret = to_dispatcher (processo, COMANDO_MAXSIMTIME, &app_float, sizeof (float));
    return (ret);
}

