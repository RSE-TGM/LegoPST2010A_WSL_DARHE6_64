/*
   modulo netstr.h
   tipo 
   release 1.2
   data 12/4/95
   reserved @(#)netstr.h	1.2
*/
#include "netmsg.h"
#include <all_1.h>

#define SERVER    1
#define CLIENT    2
#define UDP		   3
#define BROAD	   4

#define Bufsize 2500
#define Udpsize 1528

typedef struct _svd { short tipo;
                      short base;
                      short ncon;
                      unsigned short chtx;
                      unsigned short chrx;
                      unsigned int t_tx; } SERCLIDEF;



typedef struct _netp { long server;
                       short port; } NETPORT;


typedef struct _dcon { short nd;
#if !defined OSF1 && !defined LINUX
                       struct addr a;
#endif
                       unsigned char spcon; 
                       unsigned char stat;
                       unsigned char present;
							  unsigned int t_rx;
                       char buf[Bufsize]; } DESCCON;

// definizioni strutture per UDP

typedef struct _udd { short tipo;
                      unsigned short chtx;
                      unsigned short chrx;
                      unsigned int t_tx;
                      unsigned int t_rx; } UDPDEF;


typedef struct _dudp { short nd;
#if !defined OSF1 && !defined LINUX
                       struct addr a;
#endif
                       int 	flag; 
                       unsigned char present;
							  unsigned int t_rx;
                       char buf_r[Udpsize];
                       char buf_t[Udpsize]; } BROADCON;



typedef struct _ric_stato  {  short nodo;
                              short mess;
                           } RIC_STATO;

typedef struct _ris_porta  {  char stato;
                              char null;
                           } RIS_PORTA;

typedef struct _ris_stato  {  short nodo;
                              short mess;
                              RIS_PORTA porta;  
                           } RIS_STATO;

typedef struct _spo_stato  {  short nodo;
                              short mess;
                              char  porta;
                              char  null0;
                              char  stato;
                              char  null1;
                           } SPO_STATO;

/*-------------------------------------------------------------------------
| macro per swap byte 
|-------------------------------------------------------------------------*/
#define SWAP(x)  _asm { _asm mov ax,x _asm xchg al,ah _asm mov x,ax }
#include <all_16.h>
