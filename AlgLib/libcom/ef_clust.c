/**********************************************************************
*
*       C Source:               ef_clust.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:57:05 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ef_clust.c-2 %  (%full_filespec: ef_clust.c-2:csrc:3 %)";
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ef_clust.c	5.2\t1/3/96";
/*
   modulo ef_clust.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)ef_clust.c	5.2
*/
/*
 * ef_cluster.c
 *    definisce i cluster per EF ( 2 cluster: - per EASE+ - per 
 *    schedulatore)
 */
#ifdef VMS
#include unixlib
#include stdio
#include ssdef
#include descrip
#include jpidef
#include "libcom.h"
char* ease_cluster="EES$$CLUST";  /* nome cluster per EASE+ */
char* sked_cluster="SKED$$";
int efbase[2];

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "libcom.h"
S_NOME_LOGICO *ease_lnm; /* puntatore all'area shared utilizzata come
                            tabella dei nomi logici per EASE */
char* ease_cluster="EES$$CLUST";  /* nome cluster per EASE+ */
char* sked_cluster="SKED$$";
int efbase[2];

#endif

/*
 *  versione per sistema operativo VMS
 */
#ifdef VMS


int ef_cluster()
{
int i,j;
struct dsc$descriptor_s name_desc;
int uid;
int status;
char *puic;
int val;
short lun;
int item;
char cluster_name[20];
efbase[0]=EASE_EF;
efbase[1]=SKED_EF;

strcpy(cluster_name,ease_cluster);
name_desc.dsc$b_class=DSC$K_CLASS_S;
name_desc.dsc$b_dtype=DSC$K_DTYPE_T;
name_desc.dsc$a_pointer=cluster_name;
name_desc.dsc$w_length=strlen(cluster_name);

status=sys$ascefc(EASE_EF,&name_desc,0,0);

if(status!=SS$_NORMAL)
	{
	LIB$SIGNAL(status);
	return(-1);
	}


puic =(char *) getenv("SHR_USR_KEY");
strcpy(cluster_name,sked_cluster);
strcat(cluster_name,puic);
printf("cluster_name %s \n",cluster_name);
name_desc.dsc$w_length=strlen(cluster_name);

status=sys$ascefc(SKED_EF,&name_desc,0,0);

if(status!=SS$_NORMAL)
        {
        LIB$SIGNAL(status);
        return(-1);
        }
return(0);
}

#elif AIX      || defined OSF1 || defined SCO_UNIX || defined LINUX
/*
 *   Versione per sistema operativo ULTRIX o AIX
 */
/*
 Il numero di semafori disponibili per ogni gruppo viene settato
 pari al numero di EF che in VMS sono presenti nel singolo cluster
*/
#define NUM_SEM_EASE 20
#define NUM_SEM_SKED 20
#define NUM_SEM_AUX 22 /* numero semafori ausiliari (per compatibi_
                          lita' con sked ansaldo */
key_t getkey();
static int isnumber(register char *);
int ef_cluster()
{
int i,j;
int mid;
int shmflg;
key_t shr_usr_key; /* chiave utente per compatibilita' con ansaldo */
/*
  crea i due gruppi di semafori (per skedulatore e per EASE ) se non 
  esistono. Altrimenti ne ricava solamente l'ID.
*/
efbase[0]=semget(getkey(ease_cluster),NUM_SEM_EASE,0644|IPC_CREAT);
if(efbase[0]==-1) 
             {perror("a)ef_cluster"); return(-1);}
/*
 *  Creazione del gruppo di semafori per lo skedulatore:
 *    La creazione commentata e' quella proposta per le future
 *    implementazioni (la key del gruppo viene ricavata dal cor_
 *    rispondente nome del cluster VMS ). Per il cluster relativo
 *    ai singoli modelli (SEM_MOD nello skedulatore di ansaldo)
 *    bisognerebbe utilizzare una key che contiene il riferimento
 *    ad uno dei files simulatore (s04 per esempio). Esaminare
 *    anche la possibilita' di legare a tale file il gruppo di
 *    semafori relativi allo skedulatore in generale (SEM_AUX)
 *    per lo sked ansaldo)
 */
/*
efbase[1]=semget(getkey(sked_cluster),NUM_SEM_SKED,0644|IPC_CREAT);
if(efbase[1]==-1) 
	{perror("b)ef_cluster"); return(-1);}
*/
/*
 * Segue la creazione del gruppo di semafori conforme a quanto fatto
 * da ansaldo per lo skedulatore: tale impostazione e' momentaneamente
 * mantenuta per poter utilizzare lo sked di ansaldo.
 */
shr_usr_key = atoi((char *)getenv("SHR_USR_KEY"));
efbase[1] = semget(shr_usr_key+1, NUM_SEM_AUX, 0777 | IPC_CREAT);
if(efbase[1]==-1)
        {perror("c)ef_cluster"); return(-1);}
/*
 * Creazione della area shared utilizzata come area dei nomi
 * logici per ease; 
 */
mid=shmget(getkey("EASE$LNM"),sizeof(S_NOME_LOGICO)*NUM_NOM_LOG,
           IPC_CREAT|0666);
if(mid==-1)
	{
	perror("d)ef_cluster - creazione nomi logici");
	return(-1);
	}
shmflg = ! ( SHM_RND & SHM_RDONLY );
ease_lnm=(S_NOME_LOGICO *)shmat(mid,(char *)0,shmflg);
if(ease_lnm==(S_NOME_LOGICO *)-1)
	{
	perror("e)ef_cluster - installazione nomi logici");
	return(-1);
	}
return(0);
}

/* 
 * getkey  : ricava da una stringa passata come argomento una key per
 *           identificare una risorsa ( area shared, semafori o code)
 */

key_t getkey(p)
register char *p;
{
key_t key;
register int i;
if(isnumber(p))
	{
	key=(key_t) atoi(p);
	}
else
	{
	key=(key_t)0;
	for(i=0;i<(sizeof(key_t))&&p[i];i++)
		{
		key=(key<<8)| p[i];
		}
	}
return(key);
}

/*
 * isnumber(p)
 *    controlla che una stringa sia un numero
 */
int isnumber(p)
register char *p;
{
for(;*p&& isdigit(*p);p++);
return(*p ? 0 : 1);
}

#endif



