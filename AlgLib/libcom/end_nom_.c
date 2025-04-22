/**********************************************************************
*
*       C Source:               end_nom_.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:55:37 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: end_nom_.c-2 %  (%full_filespec: end_nom_.c-2:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)end_nom_.c	5.2\t1/3/96";
/*
   modulo end_nom_.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)end_nom_.c	5.2
*/
#include <stdio.h>

#ifdef VMS

end_nom_log_s()
{
	return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int end_nom_log_s()
{
        return(0);
}

#endif



