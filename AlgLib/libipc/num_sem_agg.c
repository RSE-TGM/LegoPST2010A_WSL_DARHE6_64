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
static char SccsID[] = "@(#)num_sem_agg.c	5.1\t11/7/95";
/*
   modulo num_sem_agg.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)num_sem_agg.c	5.1
*/

# include "libipc.h"

int num_sem_agg(id)
int id;
{
# if defined UNIX
int semval;

if((semval=semctl(id,1,GETVAL,0))<0)
	perror("GETVAL impossibile");
return(BIGCOUNT-semval);
#endif
# if defined VMS
/* momentaneamente  */
return(1);
#endif
}

	
