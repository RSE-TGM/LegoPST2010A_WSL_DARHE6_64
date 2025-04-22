/**********************************************************************
*
*       C Source:               clr_ef.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:57:52 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: clr_ef.c-2 %  (%full_filespec: clr_ef.c-2:csrc:3 %)";
#endif

#include <stdio.h>
#include <errno.h>

/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)clr_ef.c	5.2\t1/3/96";
/*
   modulo clr_ef.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)clr_ef.c	5.2
*/
/*
 * clr_ef(i,k)
 *    resetta l'EF i-esimo del Common cluster EES$$CLUST (se K=1)
 *    resetta l'EF i-esimo del Common cluster SKED$$.... (se K=2)
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
#include <errno.h>
extern int efbase[2];

#endif

#ifdef VMS
int clr_ef(i,k)
int i,k;
{
int status,j;
k--;
j=i+efbase[k];
status=SYS$CLREF(j);
if(status!=SS$_WASCLR && status!=SS$_WASSET)
	{
	LIB$SIGNAL(status);
	return(-1);
	}
return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
#include <errno.h>
int clr_ef(i,k)
int i,k;
{
int status,j;
int arg;
k--;
arg=0;
status=semctl(efbase[k],i,SETVAL,arg);
if(status==-1)
        { perror("clr_ef"); return(-1); }
else
        return(0);
}

#endif

