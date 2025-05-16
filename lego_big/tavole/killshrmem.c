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

/********************************************************************
C*
C*    File killtav.c  Programma killtav:
C*
C*    Gruppo Informatica, ENEL D.C.O., via Cardano 10, Milano.
C*
C*    Versione : xx.x   23-maggio-1990   Autore: Giovanni W. Villa
C*
C*    Rilascia la shared memory legata al valore di "SHR_USR_KEY"
C*    relativa alla memoria condivisa tra tasks e sked.
C*
C*******************************************************************/

# include <sys/types.h>
# include <sys/shm.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main()
   {
    int shmtid, shmflg, shmerr;
    char *stringa;
    struct shmid_ds *buff;
    
    stringa = getenv("SHR_USR_KEY");
    shmtid = shmget(atoi(stringa), 10, 0);
    shmflg = ! (SHM_RND & SHM_RDONLY );
    shmerr = shmctl(shmtid, IPC_RMID, buff);
   }

