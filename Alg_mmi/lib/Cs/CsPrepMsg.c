/**********************************************************************
*
*       C Source:               CsPrepMsg.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Jan 29 13:13:14 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsPrepMsg.c-2_deb %  (%full_filespec: CsPrepMsg.c-2_deb:csrc:1 %)";
#endif
/*
   modulo CsPrepMsg.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsPrepMsg.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsPrepMsg.c	5.1\t11/13/95";
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
    Prepara e spedisce il messaggio della nuova pagina una
    volta arrivati i tot_punti attesi
*/
int CsPrepMsg(char *nome_pagina, int coda, int t_agg, int indice, int tipo,
                int prog_punti, int tot_punti)
{
static MSG_NEW_PAGE_MMI *msg;
static int conta_punti=0;
static int totale_punti=0;
static int nummsg=0;
static int nmsg;
int pt_mancanti;
int ntoken;
int i,j;

/* Parte comune */
   if(prog_punti==0)
     {
     conta_punti=0;
     totale_punti=0;
     nummsg=0;
     ntoken = MAX_TOKEN;
     nmsg = (int)(tot_punti/MAX_TOKEN);
     if( (tot_punti%MAX_TOKEN)>0 )
        nmsg++;
     msg = (MSG_NEW_PAGE_MMI*)calloc(nmsg,sizeof(MSG_NEW_PAGE_MMI));
     for(i=0;i<nmsg;i++)
        {
        if(i==nmsg-1)
           ntoken = tot_punti - i*MAX_TOKEN;
        strcpy(msg[i].nome_pagina,nome_pagina);
        msg[i].mtype = NEW_PAGE_MMI;
        msg[i].t_agg = t_agg;
        msg[i].num_punti = tot_punti;
        msg[i].num_msg   = nmsg;
        msg[i].prog_msg  = i;
        msg[i].num_punti_msg = ntoken;
        }
     }
/* Parte specifica dell' iesimo messaggio */
   msg[nummsg].token[conta_punti].tipo = tipo;
   msg[nummsg].token[conta_punti].puntdb = indice;
/* Aggiornamento indici */
   totale_punti++;
/*  Termine dei punti attesi */
    if ( totale_punti == tot_punti )
       {
       pt_mancanti = MAX_TOKEN - conta_punti -1;
       for(j=0;j<pt_mancanti;j++)
          {
          msg[nummsg].token[MAX_TOKEN-1-j].tipo = -1;
          msg[nummsg].token[MAX_TOKEN-1-j].puntdb = -1;
          }
       for(i=0;i<nmsg;i++)
          msg_snd(coda,&msg[i],sizeof(MSG_NEW_PAGE_MMI)-sizeof(long),
                  !IPC_NOWAIT);
       /*
        libera l'elenco dei messaggi
       */
       free(msg);
       }
   conta_punti++;   
   if(conta_punti==MAX_TOKEN)
      {
      conta_punti = 0;
      nummsg++;
      }
 return(1);
}
