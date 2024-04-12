/**********************************************************************
*
*       C Source:               shrmem.c
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Feb 28 18:07:58 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: shrmem.c-9 %  (%full_filespec: shrmem.c-9:csrc:3 %)";
#endif
/*
   modulo shrmem.c
   tipo 
   release 5.2
   data 3/13/96
   reserved @(#)shrmem.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)shrmem.c	5.2\t3/13/96";
/*
        Fine sezione per SCCS
*/
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
#include <unistd.h>
#include <Rt/RtMemory.h>
#include <string.h>

/* ****** Funzione modificata da Fabio 6/2/97  ***** *
Funzione che crea una shrm (se non esiste) di dimensioni size + sizeof(int).
Nella word iniziale della shm, viene inserito il valore di size.
Se la shm con chiave key esiste gia', controlla che le dimensioni (scritte nella prima word della shm) siano = al valore size. 

Se si verifica un errore viene restituito NULL

 ***************************************************************** */

char *crea_shrmem();
void distruggi_shrmem(); /* per comaptibilita' col vecchio codice */
void elimina_shrmem();   /* nuova chiamata per l'eliminazione della shared
				memory */
int sgancia_shrmem();


char *crea_shrmem(key,size,shmid)
int key;
int size;
int *shmid;            /* identificativo shm solo per ULTRIX e AIX */
{
  char *ind;                            /* variabile spare           */
  int *appo;
  /* ** Creazione della memoria condivisa ************************** */
/*
Controllo se la shmem esiste gia'
*/

  *shmid   = shmget(key, size+sizeof(int), 0777 | IPC_CREAT | IPC_EXCL);
  if((*shmid) < 0) /* shm  esiste gia'*/
        {
        *shmid   = shmget(key, size+sizeof(int), 0777 | IPC_CREAT );
        if((*shmid) <0)
                {
		switch(errno)
			{
			case EINVAL:
			printf("ERRORE:shmget-EINVAL\n");
			break;
			case EACCES:
			printf("ERRORE:shmget-EACCES\n");
			break;
			case ENOENT:
			printf("ERRORE:shmget-ENOENT\n");
			break;
			case ENOSPC:
			printf("ERRORE:shmget-ENOSPC\n");
			break;
			case ENOMEM:
			printf("ERRORE:shmget-ENOMEM\n");
			break;
			case EEXIST:
			printf("ERRORE:shmget-EEXIST\n");
			break;

			}

                printf("ERRORE:impossibile agganciarsi a shm gia' es. che ha dim inf\n");
                return(NULL); 
		}
        else
                {
                ind = shmat(*shmid, 0, ! ( SHM_RND & SHM_RDONLY ));
                        if(((int)ind) == -1)
                                {
				printf("ERRORE:shmat fallita\n");
                                return(NULL);
                                }
/*
Modifica dovuta alla parte di integrazione Scada 
*/
		appo=(int *)ind;
                if(!(*appo==size))
                        {
                        printf("ERRORE: SHM %d esiste ed ha dim %d superiori a %d !!!\n",*shmid, appo, size);
                        return(NULL);
                        }
                else
                        {
                        return(ind+sizeof(int));
                        }
                }

        } /* end shm esiste gia' */
else
        {
        ind = shmat(*shmid, 0, ! ( SHM_RND & SHM_RDONLY ));
        if(((int)ind) == -1)
                {
		switch(errno)
			{
			case EACCES:
			printf("ERRORE:shmatEACCESS\n");
			break;
			case ENOMEM:
			printf("ERRORE:shmat ENOMEM\n");
			break;
			case EINVAL:
			printf("ERRORE:shmat EINVAL\n");
			break;
			case EMFILE:
			printf("ERRORE:shmat EMFILE\n");
			break;
			case ENOSYS:
			printf("ERRORE:shmat ENOSYS\n");
			break;
			}
                printf("ERRORE: Non si attacca alla shm per errore: |ind=%x| |errno=%d| !! \n", ind, errno);
                return (NULL);
                }
/*
Inserisci nella prima parte della shm le dimensioni della shm stessa (cioe' size
)
*/
        memcpy(ind,&size,sizeof(int));
        return(ind+sizeof(int));
        }
}

void distruggi_shrmem(shmid)
int shmid;   
{
struct shmid_ds buf;

    if(shmctl(shmid,IPC_STAT,&buf)<0)
        printf("shmctl: impossibile cancellare %d\n",shmid);
    else if(buf.shm_nattch<=1)
	{
        if(shmctl(shmid,IPC_RMID,&buf)<0)
          printf("shmctl: impossibile cancellare %d\n",shmid);
	}
    else
	printf("shmctl: impossibile cancellare  %d n_attac=%d\n",shmid,buf.shm_nattch);
}

int sgancia_shrmem(char *addr)
{
if(shmdt(addr-(sizeof(int)))!=0)
	{
        perror("shmdt");
	return( -1);
	}
return(0);
}


void elimina_shrmem(shmid,inizio,size)
int shmid;   
char *inizio;
int size;
{
struct shmid_ds buf;

    if(shmctl(shmid,IPC_STAT,&buf)<0)
        printf("shmctl: impossibile cancellare %d\n",shmid);
    else if(buf.shm_nattch<=1)
	{
        if(shmctl(shmid,IPC_RMID,&buf)<0)
          printf("shmctl: impossibile cancellare %d\n",shmid);
	}
   else 
	printf("shmctl: impossibile cancellare  %d n_attac=%d\n",shmid,buf.shm_nattch);
}
