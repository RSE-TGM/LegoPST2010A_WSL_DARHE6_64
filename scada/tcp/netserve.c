/*
   modulo netserve.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)netserve.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
Task di gestione dei server. Esiste un solo task che gestisce le attivita'
di tutti i server. Queste attivita' sono eseguite in base agli stati delle
porte:

	0 - porta on line
	1 - porta inizializzata ma non connessa
	2 - porta da inizializzare
	3 - porta da chiudere e reinizializzare

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

#define ATTESASERVER  20*10

extern SERCLIDEF _SerCliDef[];
extern DESCCON _Conn[];
extern short _nServer;
extern short _nClient;
extern short _nConn;
extern short _nParent;

extern int parent_tcb;
extern unsigned mbNet;

extern unsigned long _acknoledge[];
extern unsigned long _byteinviati[];
extern unsigned long _difference[];

extern unsigned short _iParent[];


extern REALPTR RP;

long const timeout=5000L;
int __exec;



netparent()
	{
	int i,j,porta;
	int timeout=ATTESASERVER;


	while(1)
		{
		do
			{
			__exec=0;
			for(i=0;i<_nParent;i++)
				{
				for(j=0;j< _SerCliDef[i].ncon;j++)
					{
					porta=j+ _SerCliDef[i].base;
					switch( _Conn[porta].stat )
						{
						case 0:
							break;
						case 1:
							break;
						case 2:
							if(!attiva_porta(i,porta))
   							__exec=1;
							break;
						case 3:
							chiudi_porta(porta);
							if(!attiva_porta(i,porta))
   							__exec=1;
							break;
                  case 4:
                     get_net();
                  	set_option(_Conn[porta].nd,STREAM,
                                 NET_OPT_KEEPALIVE,(long) 1,4);
                     rel_net();
                     _Conn[porta].stat=0;
							inviastato(porta,ONLINE);
                     break;
                  case 5:
                     _Conn[porta].stat=3;
                     if(_SerCliDef[i].tipo ==SERVER)
   							__exec=1;
                     break;
						case 6:
						// connessione disabilitata
							break;
                  default:
                     _Conn[porta].stat=3;
                     break;
						}
					}
				}
			} while(__exec);
		suw(timeout);
		}
	}

/*
	Routine Attiva_porta

	Preleva un descrittore e ne attiva opzioni.

	*/

attiva_porta(parent,ind)
	int parent;
	int ind;
	{
	int ret;
	DESCCON *c;
   int nd;
   char stind[8];

	c = &_Conn[ind];


	nd=net_getglobdesc();

	if(nd <0)
		{
		printf("\n impossibile allocare network descriptor %d ",neterrno);
      return 2;
		}
   c->nd=nd;
#ifdef DEBNET
   itoa(ind,stind,10);
   strcat(stind,"\n\r");
   cputs("\naggancio porta  ");
   cputs(stind);
#endif
   get_net();
//	set_option(nd,STREAM,NET_OPT_TIMEOUT,(char far *) timeout,4);
	set_option(nd,STREAM,NET_OPT_NONBLOCKING,(long) 1,0);
	set_option(nd,STREAM,NET_OPT_WAITFLUSH,(long) 1,0);
#if 0			// passaggio per indice (definire HINTINDEX)
	net_asynch(nd,NET_AS_OPEN,RP,ind);
	net_asynch(nd,NET_AS_ERROR,RP,ind);
	net_asynch(nd,NET_AS_CLOSE,RP,ind);
	net_asynch(nd,NET_AS_FCLOSE,RP,ind);
	net_asynch(nd,NET_AS_RCV,RP,ind);
	net_asynch(nd,NET_AS_XMT,RP,ind);
#else
	net_asynch(nd,NET_AS_OPEN,RP,(int) c);
	net_asynch(nd,NET_AS_ERROR,RP,(int) c);
	net_asynch(nd,NET_AS_CLOSE,RP,(int) c);
	net_asynch(nd,NET_AS_FCLOSE,RP,(int) c);
	net_asynch(nd,NET_AS_RCV,RP,(int) c);
	net_asynch(nd,NET_AS_XMT,RP,(int) c);
#endif
   c->stat=1;

   if(_SerCliDef[parent].tipo ==CLIENT)
      {
   	c->a.lsocket=0;	// unspecified port
		if(c->a.fhost)
	      ret=net_connect(nd,STREAM,&c->a);
		else
			ret=1;
      rel_net();
      if(ret > 0 ) return 1;
      }
   else
      {
   	c->a.fsocket=0;	// unspecified port
   	ret=net_listen(nd,STREAM,&c->a) ;
      rel_net();
      }

  	if(ret < 0)
   	{
	   printf("impossibile eseguire connessione. errore %i",neterrno);
  		c->stat=3;
   	ret = 1;
	   }
  	else
   	{
	   ret=0;
   	}
	return ret;
	}
	

chiudi_porta(ind)
	int ind;
	{
	DESCCON *c;

	c = &_Conn[ind];
	if(c->stat != 2 && c->stat!=6)
		{
	   get_net();
		net_abort(c->nd);
		net_release(c->nd);
	   rel_net();
		c->stat=2;
	   _difference[ind]=_byteinviati[ind]=_acknoledge[ind]=0;
		inviastato(ind,OFFLINE);
		}
	return 0;
	}

disabilita_porta(ind)
	int ind;
	{
	DESCCON *c;

	c = &_Conn[ind];

	if (c->stat ==2)
		c->stat = 6;
	else if (c->stat != 6)
		{
	   get_net();
		net_abort(c->nd);
		net_release(c->nd);
		res(c->t_rx);
	   rel_net();
		c->stat=6;
	   _difference[ind]=_byteinviati[ind]=_acknoledge[ind]=0;
		inviastato(ind,OFFLINE);
		}
	return 0;
	}

abilita_porta(ind)
	int ind;
	{
	DESCCON *c;

	c = &_Conn[ind];

	if (c->stat == 6)
		{
		c->stat=2;
	   evsp(parent_tcb);
		}
	return 0;
	}



get_net()
   {
   int d;
   rew(mbNet,0,&d);
   }

rel_net()
   {
   tra(mbNet,1);
   }

inviastato(porta,modo)
	int porta,modo;
	{
   QUEUE_PACKET pack;    // packe per send
   SERCLIDEF  *d;
	short buf[8];

   d=&_SerCliDef[_iParent[porta]];
   pack.que = d->chrx;
	pack.flg = MSG_NOWAIT;
	pack.wto = 0;
   pack.amsg = (char *) buf;
   pack.lmsg = 8;
	buf[0]=-1;
	buf[1]=STATOPORTA;
	buf[2]=porta- d->base;
	buf[3]=modo;
   enqueue(&pack);
	}

