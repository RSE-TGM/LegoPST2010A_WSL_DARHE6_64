/**********************************************************************
*
*       C Source:               shresist.c
*       Subsystem:              3
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Feb 27 12:09:14 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: shresist.c-3 %  (%full_filespec: shresist.c-3:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)shresist.c	5.1\t11/7/95";
/*
   modulo shresist.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)shresist.c	5.1
*/
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
#include <unistd.h>
#include <Rt/RtMemory.h>

/* ****** Definizione variabili globali per ULTRIX e AIX  ***** */


int     shresist (id)
int     id;
{
int size,i;
char *ind;
struct shmid_ds buf;

    size = 777;			/* valore casuale */
    if ((i = shmget (id, size+sizeof(int), 0777 | IPC_CREAT | IPC_EXCL)) > 0)
    {
	/* la shared memory non esiste */
	ind = shmat (i, 0, !(SHM_RND & SHM_RDONLY));
        /*
        Detach della shm
        */
        if(shmdt(ind)!=0)
           {
           perror("shmdt\n");
           }
	if (shmctl (i, IPC_RMID, &buf) < 0)
	{
            fprintf (stderr,"shresist: codice errore %d\n", errno);
	    perror ("shmctl");
	}
	return (0);
    }
    else
	return (1);
}
