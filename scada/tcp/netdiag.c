/*
   modulo netdiag.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)netdiag.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   Netdiag

   Routine che richiede la diagnostica sullo stato della rete
   Ethernet, accodando il messaggio STATUS alle code di mmi e
   di acquisizione
   La routine viene chiamata da attiper circa ogni minuto.
   
   Parametri

   nessuno

   Ritorno

   nessuno

   7 Ottobre 1992  Rel. 1.0

*/
#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"
#include "mesqueue.h"

extern short c_mmio, c_acquio;
netdiag()
{
QUEUE_PACKET pack;
RIC_STATO mess;

mess.nodo=NODO_DIAG;
mess.mess=STATUS;

pack.que=c_mmio;
pack.flg=MSG_WAIT;
pack.wto=0;
pack.amsg=(char *) &mess;
pack.lmsg=sizeof(mess);

enqueue(&pack);

pack.que=c_acquio;
enqueue(&pack);
}
