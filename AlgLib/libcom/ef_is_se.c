/**********************************************************************
*
*       C Source:               ef_is_se.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:56:30 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ef_is_se.c-2 %  (%full_filespec: ef_is_se.c-2:csrc:3 %)";
#endif

#include <stdio.h>
#include <errno.h>

/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ef_is_se.c	5.2\t1/3/96";
/*
   modulo ef_is_se.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)ef_is_se.c	5.2
*/
/*
 * ef_is_set(i,k)
 *    legge l'EF i-esimo del Common cluster EES$$CLUST (se K=1)
 *    legge l'EF i-esimo del Common cluster SKED$$.... (se K=2)
 *    ritorna 1 se il flag e' settato,0 se il flag non e' settato.
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
int ef_is_set(i,k)
int i,k;
{
int status,j;
int ret_status;
k--;
j=i+efbase[k];
status=SYS$READEF(j,&ret_status);
if(status!=SS$_WASCLR && status!=SS$_WASSET)
	{
	LIB$SIGNAL(status);
	return(-1);
	}
if(status==SS$_WASSET)
	return(1);
else
	return(0);
}


#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int ef_is_set(i,k)
int i,k;
{
int status,j;
int ret_status;
int arg;
k--;
status=semctl(efbase[k],i,GETVAL,arg);
if(status==-1)
	{ perror("ef_is_set"); return(-1); }
else
	return( status ? 1 : 0);
}

#endif
