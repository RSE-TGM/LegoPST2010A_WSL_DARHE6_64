/**********************************************************************
*
*       C Source:               CsRcvTokenS.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Sep  8 17:37:27 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsRcvTokenS.c-3 %  (%full_filespec: CsRcvTokenS.c-3:csrc:1 %)";
#endif
/*
   modulo CsRcvToken.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsRcvToken.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvToken.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#ifndef VMS
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#else
#include <vmsipc.h>
#endif

#include <sim_param.h>
#include <Cs/Cs.h>

#include "libipc.h"
#include "sim_types.h"

extern int sgancia_shrmem(char *);

/*
    Riceve il messaggio di richiesta di una nupova pagina,
    crea la SHM della nuova pagina,  restituisce un buffer
    contenente i TOKEN della pagina e spedisce ad MMI un
    messaggio di acknoledge con le informazioni sulla SHM creata.
*/
int CsRcvTokenS(int coda, char **buffer)
{
MSG_NEW_PAGE_MMI msg;
MSG_NEW_PAGE_MMI_RET msg_ret;
HEADER_NEW_PAGE_MMI header;
static int indice_pagina=0;
int offset=500;
int ret,i,j;
int nattese;
int size;
char *ind;
char *punt;
int shr_usr_key;
int shmvid;
int val;


/* Ricevo il primo messaggio */
   if ( (ret = msg_rcv(coda,&msg,sizeof(MSG_NEW_PAGE_MMI)-sizeof(long),
                      (long)NEW_PAGE_MMI,IPC_NOWAIT,TIMEOUT_MMI))<0 )
       return(-1);
/* Decodifica SHR_USR_KEYS */
if((getenv("SHR_USR_KEYS"))==NULL)
        {
        printf("CsRcvTokenS:Variabili di ambiente SHR_USR_KEYS non definita\n");
	return(-1);
        }
else
   shr_usr_key = atoi((char *)getenv("SHR_USR_KEYS"));
/* Creo la shared memory */
   indice_pagina++;
   errno = 0;


#ifdef FABIO
   ind = (char*) crea_shrmem(shr_usr_key+offset+indice_pagina,
                            (msg.num_punti*2+1)*sizeof(float),&shmvid);
if(ind ==NULL)
      {
      printf("CsRcvTokenS:ERRORE impossibile aprire la SHM con key=%d\n",
              shr_usr_key+offset+indice_pagina);
      return(-1);
      }
   else
     printf("Ho aperto la   SHMS   di  id=%d  e  shmvid=%d\n",
             shr_usr_key+offset+indice_pagina,shmvid);


if(sgancia_shrmem(ind)<0)
	{
	printf("CsRcvTokenS:ERRORE impossibile sgancia_shrmem con key=%d\n",
              shr_usr_key+offset+indice_pagina);
	return(-1);
	}
#endif


/* Allocazione buffer */
   nattese = msg.num_msg;
   size = sizeof(HEADER_NEW_PAGE_MMI) +  nattese*MAX_TOKEN*sizeof(TOKEN);
   (*buffer) = (char*)malloc(size);
   punt = (*buffer);
/* Header della trasmissione via rete */


#ifdef FABIO
   header.id_shm = shr_usr_key+offset+indice_pagina;
#endif


   header.id_shm = 100;
   header.t_agg = msg.t_agg;
   header.num_punti = msg.num_punti;
   header.size =  nattese*MAX_TOKEN*sizeof(TOKEN);
   header.richiesta_mmi = NEW_PAGE_MMI; 
/* Copio l'header e il primo messaggio */
   memcpy(punt,&header,sizeof(HEADER_NEW_PAGE_MMI));
   punt += sizeof(HEADER_NEW_PAGE_MMI);
   memcpy(punt,msg.token,MAX_TOKEN*sizeof(TOKEN));
   punt += MAX_TOKEN*sizeof(TOKEN);
/* Ricevo i restanti messaggi */
   for(i=1;i<nattese;i++)
     {
     msg_rcv(coda,&msg,sizeof(MSG_NEW_PAGE_MMI)-sizeof(long),
             (long)NEW_PAGE_MMI,!IPC_NOWAIT,TIMEOUT_INFINITO);
     memcpy(punt,msg.token,MAX_TOKEN*sizeof(TOKEN));
     punt += MAX_TOKEN*sizeof(TOKEN);
     }

/* Spedisco il messaggio di akwnoledge */
#ifdef FABIO
   msg_ret.mtype  = NEW_PAGE_MMI_RET; 
   msg_ret.id_shm = header.id_shm;
   msg_snd(coda,&msg_ret,sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
           !IPC_NOWAIT);
#endif

   return(header.id_shm);
}
