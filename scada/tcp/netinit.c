/*
   modulo netinit.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)netinit.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*

	Modulo di startup

	Le routine contenute sono:
		NetDosStartup	 - chiamata a livello DOS
		NetMarteStartup - chiamata a livello MARTE

*/

#include <stdio.h>
#include <pharlap.h>


#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"


extern short _nServer,_nClient,_nConn;
extern short _nParent;
extern short _nUdp;

extern unsigned parent_tcb;

extern DESCCON _Conn[];
extern SERCLIDEF  _SerCliDef[];
extern UDPDEF  _UdpDef[];
extern BROADCON  _UdpConn[];
extern unsigned int _T_Rx[];
char *fileserver="PORTS.ADR";

REALPTR RP;

extern int _hand1();


NetDosStartup()
	{
	FILE *f;
	char buf[80];
   int i,ad,u;
   char *p;
   char *nome;
   in_name fhost;
   int ind,j;
	int statoinit;

	if(Tcp32Init(_nConn,2048))
		{
		printf("Errore  attivazione interfaccia Real mode\n");
		exit(1);
		}
	RP = InstRMCall(0xc0,_hand1);


	if((f=fopen(fileserver,"r")) == NULL)
		{
		printf("\nerrore in apertura file %s",fileserver);
		terminit();
		}
	i=0;
	u=0;
	while(fgets(buf,79,f)!= NULL)
		{
		if(!strncmp(buf,"PORT_DEF",8))
			{
			if(i ==_nParent)
				{
				printf("\nDefinizioni sovrambbondanti in def. server");
				break;
				}
			nome=buf;
			while(*nome !=' ' && *nome!='\0') nome++;
			while(*nome ==' ' && *nome!='\0') nome++;
			p=nome;
	   	while(*p != ':' && *p)
				{
				if (*p==' ') *p=0;
				p++;
				}
			*p++=0;
			if((ad=atoi(p)) == 0)
				{
				printf("\nerrore in decodifica address");
				terminit();
				}
			statoinit=2;	// stato attivo: default
	      if(_SerCliDef[i].tipo==CLIENT)
   	      {
				if(*nome == '@')	// nodo parte come disabilitato
					{
					nome++;
					statoinit=6;	// stato disabilitato
					}
      	   fhost = nm_res_name(nome, (char *) 0, 0);
         	if(fhost ==0)
	   			{
		   		printf("\nerrore in decodifica host. Porta non abilitata");
				   }
	         }
   	   else
      	   fhost=0;

			for(j=0,ind=_SerCliDef[i].base;j<_SerCliDef[i].ncon;j++,ind++)
   			{
				_Conn[ind].a.fsocket=ad;
				_Conn[ind].a.lsocket=ad++;
				_Conn[ind].a.fhost=fhost;
   		   _Conn[ind].stat=statoinit;		// setto lo stato iniziale
         	}
			i++;
			}
		else if(!strncmp(buf,"UDP_DEF",7))
			{
			if(u ==_nUdp)
				{
				printf("\nDefinizioni sovrabbondanti in def. server");
				break;
				}
			nome=buf;
			while(*nome !=' ' && *nome!='\0') nome++;
			while(*nome ==' ' && *nome!='\0') nome++;
			p=nome;
	   	while(*p != ':' && *p)
				{
				if (*p==' ') *p=0;
				p++;
				}
			*p++=0;
			if((ad=atoi(p)) == 0)
				{
				printf("\nerrore in decodifica address");
				terminit();
				}
     	   fhost = nm_res_name(nome, (char *) 0, 0);
        	if(fhost ==0)
   			{
	   		printf("\nassegnazione canale broadcast");
				_UdpConn[u].flag=NET_FLG_BROADCAST;
			   }
			else
				_UdpConn[u].flag=0;

			_UdpConn[u].a.fsocket=ad;
			_UdpConn[u].a.lsocket=ad;
			_UdpConn[u].a.fhost=fhost;
			u++;
			}
		}
	if(i < _nParent || u < _nUdp)
		{
		printf("\nInformazioni insufficenti in PORTS.ADR");
		terminit();
		}
	fclose(f);
	}	

terminit()
	{
	RemoveRMCall(RP);
	Tcp32Close();
	exit(0);
	}


NetMarteStartup()
   {
   int i;

   rel_net();

   tas(parent_tcb);
   for(i=0;i<_nConn;i++)
      {
      _Conn[i].t_rx=_T_Rx[i];   // inizializzo in ram tcb ricezione
      tas(_T_Rx[i]);
      }
   for(i=0;i<_nParent;i++)
      tas(_SerCliDef[i].t_tx);
	for(i=0;i<_nUdp;i++)
		{
	 	_UdpConn[i].t_rx=_UdpDef[i].t_rx;
      tas(_UdpDef[i].t_rx);
      tas(_UdpDef[i].t_tx);
		}
   }   

NetMarteEnd()
   {
	int i;

	sce();
	get_net();		
	scd();
   for(i=0;i<_nConn;i++)
      {
		if(_Conn[i].stat != 2 && _Conn[i].stat != 6)
			{
	   	net_abort(_Conn[i].nd);
	   	net_release(_Conn[i].nd);
			}
		}
	RemoveRMCall(RP);
	Tcp32Close();
   }
