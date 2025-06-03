/**********************************************************************
*
*       C Source:               SD_dummy.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:32:14 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: SD_dummy.c-4 %  (%full_filespec: SD_dummy.c-4:csrc:1 %)";
#endif

#include <stdio.h>
#include <X11/Xlib.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/Xm.h>

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

#include "option.h"
#include "archivi.h"
#include "bistrutt.h"

int write_options(char*,Boolean *);

/*
 * dummy function
 */
/****************************************************************/
int SD_archive (processo, dati)
int processo;
ARCHIVE_REQ *dati;
{
	printf ("SD_archive tinit = %f\n",dati->t_init);
	printf ("SD_archive tinit = %f\n",dati->t_end);
	printf ("SD_archive comm = %s\n",dati->commento);
	return(1);
}
/****************************************************************/
int SD_stato (processo, dati)
int processo;
RICHIESTA_STAT *dati;
{
	printf ("DUMMY function SD_stato\n");
	return (1);
}
/****************************************************************/
int SD_sessione (processo, dati)
int processo;
char *dati;
{
   printf ("DUMMY function SD_sessione:%s:\n",dati);
   return (1);
}

int SD_optsave (processo, dati)
int processo;
char *dati;
{
	Boolean res;
	if (write_options(dati,&res) == 0)
		return(1);
	return(0);
}
/****************************************************************/
