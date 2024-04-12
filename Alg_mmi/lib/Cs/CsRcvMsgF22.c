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
   modulo CsRcvMsgF22.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsRcvMsgF22.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsRcvMsgF22.c	5.1\t11/13/95";
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


/*
    Riceve da mmi un messaggio con l'indice della SHM da cancellare
*/
int CsRcvMsgF22(int coda, char **buf)
{
int ret;
int size;
char *punt;
MSG_F22_MMI msg;
HEADER_NEW_PAGE_MMI hd;

    if ( (ret=msg_rcv(coda,&msg,sizeof(MSG_F22_MMI)-sizeof(long),(long)F22_MMI,
                      IPC_NOWAIT,TIMEOUT_MMI))<0 )
       {
       return(-1);
       }
    else
       {
/*     Copia dell'header del messaggio da inviare in rete sul buffer */
       size = sizeof(HEADER_NEW_PAGE_MMI) + sizeof(MSG_F22_MMI)-sizeof(long);
       (*buf) = (char *)malloc(size);
       hd.id_shm    = 0;
       hd.t_agg     = 0;
       hd.num_punti = 0;
       hd.size      = 0;
       hd.richiesta_mmi = F22_MMI;
       punt = (*buf);
       memcpy(punt,&hd,sizeof(HEADER_NEW_PAGE_MMI));
       punt += sizeof(HEADER_NEW_PAGE_MMI);
       memcpy(punt,&msg,sizeof(MSG_F22_MMI));

       return(size);
       }
}
