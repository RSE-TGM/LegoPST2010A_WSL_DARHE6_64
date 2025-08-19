/**********************************************************************
*
*       C Source:               diagnet.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 14:29:52 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: diagnet.c-3 %  (%full_filespec: diagnet.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   diagnet.c

   Routine che gestisce il messaggio di variazione spontanea 
   delle connessioni della rete ethernet. In input viene fornito
   l'indice del digitale corrispondente alla prima porta della
   connessione del server. Fornisce in output lo stato del digitale
   per eventuali trattamenti.
   
   Parametri in input

   pdb short          puntatore digitale corrispondente alla prima
                      porta
   mess SPO_STATO*    puntatore al messaggio  da trattare
   porta short *      puntatore porta che ha variato di stato

   Ritorno  short

    0                   variazione stato: -> stato 0
    1                   variazione stato: -> stato 1    
   -1                   nessuna variazione di stato: stato 0
   -2                   nessuna variazione di stato: stato 1
   -3                   punto inesistente


   7 Ottobre 1992  Rel. 1.0  Fc

*/
#if defined OSF1 || defined LINUX
#include <stdio.h>
#else
#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>
#endif

#include "netmsg.h"
#include "netstr.h"
#include "mesqueue.h"
#include "g2comdb.inc"
#include "g1tipdb.inc"
#include "messcada.inc"

extern short c_digor;

// Function declarations for bit manipulation
int bitvalue(short *buffer, short indice);
void bitset(short *buffer, short indice, short bit);

int diagnet(pdb,mess,porta)
short pdb;
SPO_STATO *mess;
short *porta;
{
QUEUE_PACKET pack;
short point;
S_TRATG mtra;

point=pdb+mess->porta;
*porta=mess->porta;
// printf("\n %d %d",point,mess->stato);

if(dbddu[point]==-1) return(-3);     // punto non esistente

if(bitvalue(&dbdd[point],g2di_sl) != mess->stato)     // variazione di stato
{
   bitset(&dbdd[point],g2di_sl,mess->stato);

   // segnalazione variazione in pagina allarmi
   pack.que=c_digor;               
   pack.wto=0;                     
   pack.flg=MSG_WAIT;
   pack.amsg=(char *)&mtra;
   pack.lmsg=sizeof(S_TRATG);
  	mtra.mess=macdd;  mtra.ext=g1tipdd;
   mtra.indice=point; mtra.stato=mess->stato;
  	enqueue(&pack);

   return(mess->stato);
}   
else
{
   if( mess->stato==0 )       // nessuna variazione: stato 0
      return(-1);
   else                       // nessuna variazione: stato 1
      return(-2);
}   
}

