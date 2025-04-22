/**********************************************************************
*
*       C Source:               CsRcvToken.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep  3 09:20:30 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsRcvToken.c-5 %  (%full_filespec: CsRcvToken.c-5:csrc:1 %)";
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

/*
    Riceve il messaggio di richiesta di una nupova pagina,
    crea la SHM della nuova pagina,  restituisce un buffer
    contenente i TOKEN della pagina. 
*/
int CsRcvToken(int coda, char **buffer)
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



/* Allocazione buffer */
   nattese = msg.num_msg;
   size = sizeof(HEADER_NEW_PAGE_MMI) +  nattese*MAX_TOKEN*sizeof(TOKEN);
   (*buffer) = (char*)malloc(size);
   punt = (*buffer);
/* Header della trasmissione via rete */

   header.id_shm = 100; /* dummy value; no longer used */

   printf("CsRcvToken: header.id_shm=%d\n",header.id_shm);
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

   return(header.id_shm);
}
