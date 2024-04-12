/*
   modulo txnet.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)txnet.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
      Task di gestione trasmissione.

      Il task e' cosituito da una entry relativa a ciascun server/client
      e di un corpo comune a tutti

		6 Aprile 1995
		Recupero valore di retry da impostanzione opzioni di lancio /Tnn
		(default 12)
      */

#include <stdio.h>
#include <stdlib.h>

#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"

#include "mesqueue.h"

/*
   parte comune del task 
   Il task si sospende in attesa di richieste di trasmissione
   e li invia sulla rete. 
   riceve in attivazione il puntatore al descrittore
   */

extern SERCLIDEF _SerCliDef[];
extern DESCCON _Conn[];
extern char _buftx[][2048];
extern short _nConn;
extern unsigned parent_tcb;

extern unsigned long _byteinviati[];
extern unsigned long _difference[];
extern short tcp_retry;
//
// per compattare la trasmissione 
// #define NONPUSH

_net_txcom(ind)
   int ind;
   {
   QUEUE_PACKET pack;    // packe per send
   SERCLIDEF  *d;
   DESCCON *c;
   int ret;
   short channel,port;
   short inviati;
   short len;
   short retry;
   char *b;
   int   error;
   short k,chan;
   unsigned long diff;
   char stind[8];

   b=_buftx[ind];
   d=&_SerCliDef[ind];

/*  inizializzo packet  */

   pack.que = d->chtx;
	pack.flg = MSG_WAIT;
	pack.wto = 0;
   pack.amsg = b;

/* ciclo continuo: finche' la sessione e' attiva */
   while(1)
      {
      pack.lmsg=Bufsize;
      if(!dequeue(&pack))
         {
#ifdef NONPUSH
// la prossima scodata senza timeout per impacchettare le trasmissioni
         pack.flg = MSG_NOWAIT;
#endif
         if(!tcpmaster(b)) continue;
         channel=*((short *) b);
         if(channel == -1) 
            service_message(b,d);
         else
            {
            port=channel + d->base;
            c=&_Conn[port];
            if( channel < d->ncon && c->stat == 0)
               {
#if defined (SWAP_WORD)
					short lm;
			   		lm=pack.lmsg;
						SWAP(lm);
	               *((short *) b) = lm;
#else
               *((short *) b) = pack.lmsg;
#endif
               inviati=0;
               retry=tcp_retry;
#ifdef DEBNET
               cputs("\n\rt ");
#endif
              	while (inviati != pack.lmsg)
                  {
//						_visch('0'+ind);
                  get_net();
//						_visch('a'+channel);
#ifdef NONPUSH
// continuo a riempire buffer
                  len=net_write(c->nd, &b[inviati],pack.lmsg-inviati, 0);
#else
                  len=net_write(c->nd, &b[inviati],pack.lmsg-inviati, NET_FLG_PUSH);
#endif
                  error=neterrno;
  		            rel_net();
                  if (len == -1)
                     {
                     if(error == NET_ERR_REENTRY)
                        {  wai(1); }
                     else if(error == NET_ERR_WOULD_BLOCK)
                        {
                        if(--retry)  wai(3);
//                           {visch('A'); wai(3); retry=3;}
                        else
                           {
#ifdef DEBNET
                           cputs("\nscatto timeout");
#endif
                           for(k=chan=diff=0;k<_nConn;k++)
                              {
                              if(_difference[k] > diff)
                                 {
                                 chan=k;
                                 diff=_difference[k];
                                 }
                              }
#ifdef DEBNET
                           cputs("\n\r chiudo connessione ");
                           itoa(chan,stind,10);
                           cputs(itoa(chan,stind,10));
                           cputs("\n\r");
#endif
								  cprintf("\n task %i chiudo connessione %i",ind,chan);
                           chiudi_porta(chan);
                           evsp(parent_tcb);
                           if(chan != port)
                              retry=tcp_retry;
                           else
                              break;
                           }
                        }
                     else
                        {
#ifdef DEBNET
               	   	cputs("net_write error  ");
                        cputs(itoa(neterrno,stind,10));
                        cputs("\n\r");
#endif
                        chiudi_porta(port);
                        evsp(parent_tcb);
                        break;
                     	}
                     }
                  else
                     {
                     inviati += len;
                     _byteinviati[port]+=len;
                     _difference[port]+=len;
#ifdef DEBNET
                     itoa(len,stind,10);
                     cputs(stind);
                     cputs("  ");
#endif
                     }
                  }
      
//               if(!c->stat)
//                  {
//                  net_flush(c->nd);
//                 }
               } /* channel ok */
            } /* tipo messaggio */
         } /* dequeue */
      else  // errore in scodamento
         {
         pack.flg = MSG_WAIT;
         // forzo l'invio di quello che ho in coda
         len=net_write(c->nd, &b[0],0, NET_FLG_PUSH);
         }
      } /* while */
   }


service_message(b,d)
   char * b;
   SERCLIDEF  *d;
   {
   short * comm;
   short porta,i;
   QUEUE_PACKET pack;    // packe per send

   comm = (short *) b;
	comm++;
   switch( *comm)
      {
      case STATUS:
			*comm = STATUS_R;
			comm++;
			for(i=0,porta=d->base;i< d->ncon;i++,porta++)
				*comm++=_Conn[porta].stat;
		   pack.que = d->chrx;
			pack.flg = MSG_WAIT;
			pack.wto = 0;
		   pack.amsg = b;
         pack.lmsg= 4 + d->ncon * 2;
         enqueue(&pack);

         break;

      case MODOFF:
         porta= *(comm+1);
         if(porta < d->ncon)
            {
            chiudi_porta(porta+d->base);
            }
         break;
      case MODABIL:
         porta= *(comm+1);
         if(porta < d->ncon)
            {
            abilita_porta(porta+d->base);
            }
         break;
      case MODDISAB:
         porta= *(comm+1);
         if(porta < d->ncon)
            {
            disabilita_porta(porta+d->base);
            }
         break;
      }
   }
