/**********************************************************************
*
*       C Source:               wait_ef.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:51:39 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: wait_ef.c-2 %  (%full_filespec: wait_ef.c-2:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)wait_ef.c	5.2\t1/3/96";
/*
   modulo wait_ef.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)wait_ef.c	5.2
*/
/*
 * wait_ef(i,k)
 *  attende il settaggio dell'EF i-esimo del Common cluster EES$$CLUST (se K=1)
 *  attende il settaggio dell'EF i-esimo del Common cluster SKED$$.... (se K=2)
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
/*
 *  versione per sistema operativo VMS
 */
int wait_ef(i,k)
int i,k;
{
int status,j;
k--;
j=i+efbase[k];
status=SYS$WAITFR(j);
if(status!=SS$_NORMAL)
	{
	LIB$SIGNAL(status);
	return(-1);
	}
return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int wait_ef(i,k)
int i,k;
{
int status,j;
struct sembuf buf;
k--;
buf.sem_num=i;
buf.sem_op=(-1);
buf.sem_flg=SEM_UNDO; /* la wait non deve modificare lo stato
                         del semaforo */
status=semop(efbase[k],&buf,1);
if(status==-1)
	{ perror("wait_ef"); return(-1);}
else return(0);
}

#endif

