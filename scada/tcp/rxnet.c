/*
   modulo rxnet.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)rxnet.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/****************************************************************************/
/*                                                                          */
/*  -> RxNet.C                                                              */
/*                                                                          */
/*  Task di gestione ricezione dati da rete EtherNet                        */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"
#include "mesqueue.h"


/* Parte comune del task */

extern SERCLIDEF _SerCliDef[];
extern DESCCON _Conn[];

extern unsigned short _iParent[];
extern unsigned long  parent_tcb;

_net_rxcom(long ind)
   {
   QUEUE_PACKET pack;    // packet per send
   SERCLIDEF *d;
   DESCCON   *c;
   long error;
   long ret;
   long len;
   short attesi,recived;
   long timeout;
   char stind[20];
   char blen[2];


   c = &_Conn[ind];
   d = &_SerCliDef[_iParent[ind]];

/* Inizializzazione packet per Send. */

   pack.que  = d->chrx;
	pack.flg  = MSG_WAIT;
	pack.wto  = 0;
   pack.amsg = c->buf;

   recived = attesi = 0;

/* ciclo continuo: finche` la sessione e` attiva */

   while(1)
      {
LOOP:
      if(!c->present) suw(100);
      if(c->stat)
         {
         c->present = 0;
         recived = attesi = 0;
         goto LOOP;
         }
      get_net();
      if(!recived)
         {
         len  = net_read(c->nd,&blen[attesi],2-attesi,(struct adr *)0,0);
         error= neterrno;
         rel_net();

         if(len == -1)
            {
            if(error == NET_ERR_WOULD_BLOCK)
               c->present = 0;
            else 
               {
               if(error ==NET_ERR_REENTRY)
                  {
                  c->present = 1;
                  wai(1);
                  }
               else
                  {
#ifdef DEBNET
                  cputs("\n\rerrore connessione  ");
                  cputs(itoa(error,stind,10));
                  cputs("\n\r");
#endif
                  recived=0;
                  attesi= 0;
                  chiudi_porta(ind);
                  evsp(parent_tcb);
                  }
               }
            }
         else
            {
            attesi = attesi + len;
#ifdef DEBNET
            itoa(recived,stind,10);
            cputs("\n\r r  ");
            cputs(stind);
#endif
            if(attesi == 2) 
               {
               recived = * ((short *) blen);

#if defined (SWAP_WORD)
   		   	SWAP(recived);
#endif
	   		   if(recived < 0 || recived > Bufsize)
                  {
                  printf("Errore lungezza");
                  recived = attesi = 0;
                  chiudi_porta(ind);
                  evsp(parent_tcb);
                  }
//			      printf("R%d \n",recived);
               }
            }
         }
      else
         {
//			printf("ra %d",recived-attesi);
         len  = net_read(c->nd,&c->buf[attesi],recived-attesi,(struct adr *)0,0);
         error= neterrno;
         rel_net();
         if(len == -1)
            {
            if(error == NET_ERR_WOULD_BLOCK)
               c->present = 0;
            else if(error == NET_ERR_REENTRY)
               {
               c->present = 1;
               wai(1);
               }
            else
               {
#ifdef DEBNET
               cputs("\n\rerrore connessione   ");
               cputs(itoa(error,stind,10));
               cputs("\n\r");
#endif
               recived = attesi = 0;
               chiudi_porta(ind);
               evsp(parent_tcb);
               }
            }
         else
            {
            attesi = attesi + len;
            if(attesi == recived)
               {
               *((short *) c->buf) = ind - d->base;
//					printf("ac %d %d ",ind - d->base,recived);
               pack.lmsg = recived;
               enqueue(&pack);
               recived = attesi = 0;
               timeout = 0;
               }
#ifdef DEBNET
            itoa(len,stind,10);
            cputs("  ");
            cputs(stind);
#endif
            }
         }
      }
   }





