/*
   modulo broadf.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)broadf.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <pharlap.h>

#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"

#include "mesqueue.h"

extern REALPTR RP;
extern UDPDEF _UdpDef[];
extern BROADCON _UdpConn[];

_broad_rx(ind)
	int ind;
	{
	UDPDEF *d;
	BROADCON *c;
	QUEUE_PACKET pack;
	int nd,len,locerr;

	d=&_UdpDef[ind];
	c=&_UdpConn[ind];

	nd=net_getdesc();
	if(nd <0)
		{
		cputs("impossibile allocare network descriptor\n\r");
      ter();
		}
	c->nd=nd;
	pack.que=d->chrx;
	pack.amsg=c->buf_r;
	pack.flg = MSG_WAIT;
	pack.wto = 0;


   get_net();
	set_option(nd,DGRAM,NET_OPT_NONBLOCKING,(long) 1,0);
	net_asynch(nd,NET_AS_RCV,RP,(int) c);
   if(net_connect(nd,DGRAM,&c->a) <0)
		{
		rel_net();
		net_release(nd);
		ter();
		}
	rel_net();
	while(1)
		{
      if(!c->present)   suw(100);
		get_net();
  	   len = net_read(c->nd, c->buf_r, Udpsize,NULL, c->flag);  
		locerr=neterrno;
		rel_net();
		if(len==-1)
			{
			if(locerr!=NET_ERR_WOULD_BLOCK)
				{
				}
			else
				c->present=0;
			}
		else
			{
			pack.lmsg=len;
			enqueue(&pack);
			}
		}
	}

_broad_tx(ind)
	int ind;
	{
	UDPDEF  *d;
	BROADCON *c;
	QUEUE_PACKET pack;
	int error;
	d=&_UdpDef[ind];
	c=&_UdpConn[ind];

	pack.que=d->chtx;
	pack.amsg=c->buf_t;
	pack.flg = MSG_WAIT;
	pack.wto = 0;

	while(1)
		{
      if(!dequeue(&pack))
			{
         if(*((int *) c->buf_t) ==-1) continue;

         *((int *) c->buf_t) = pack.lmsg;
			get_net();
		  	if(net_write(c->nd, c->buf_t,pack.lmsg,c->flag) <0) 
				error=neterrno;
			else
				error=0;
			rel_net();
			}
		if(error)
			{
			printf("errore tx broadcast %i\n",error);
			error=0;
			}
		}
	}
		
