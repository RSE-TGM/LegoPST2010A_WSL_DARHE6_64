/**********************************************************************
*
*       C Source:               set_ef.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:55:00 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: set_ef.c-2 %  (%full_filespec: set_ef.c-2:csrc:3 %)";
#endif

#include <stdio.h>
#include <errno.h>

/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)set_ef.c	5.2\t1/3/96";
/*
   modulo set_ef.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)set_ef.c	5.2
*/
/*
 * set_ef(i,k)
 *    setta l'EF i-esimo del Common cluster EES$$CLUST (se K=1)
 *    setta l'EF i-esimo del Common cluster SKED$$.... (se K=2)
 */
#ifdef VMS
#include ssdef
#include stdio
#include "libcom.h"
extern int efbase[2];

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
extern int efbase[2];

#endif

#ifdef VMS
int set_ef(i,k)
int i,k;
{
int status,j;
k--;
j=i+efbase[k];
status=SYS$SETEF(j);
if(status!=SS$_WASCLR && status!=SS$_WASSET)
	{
	LIB$SIGNAL(status);
	return(-1);
	}
return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int set_ef(i,k)
int i,k;
{
int status,j;
int ret_status;
int arg;
k--;
arg=1;
status=semctl(efbase[k],i,SETVAL,arg);
if(status==-1)
        { perror("set_ef"); return(-1); }
else
/*printf("\n da set_cl ef_base %d i %d ",efbase[k],i); */
        return(0);
}

#endif
