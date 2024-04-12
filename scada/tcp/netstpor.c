/*
   modulo netstpor.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)netstpor.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   Netstpor

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

   -1                   punto inesistente/nessuna variazione di stato
    0                   stato 0
    1                   stato 1    


   7 Ottobre 1992  Rel. 1.0  Fc

*/
#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/asynch.h>
#include <pctcp/options.h>

#include "netstr.h"
#include "mesqueue.h"
#include "g2comdb.inc"
#include "g1tipdb.inc"
#include "messcada.inc"

netstpor(pdb,mess,porta)
short pdb;
SPO_STATO *mess;
short *porta;
{
QUEUE_PACKET pack;
short point;
S_TRATG mtra;

point=pdb+mess->porta;
*porta=mess->porta;
printf("\n %d %d",point,mess->stato);

if(dbddu[point]==-1) return(-1);     // punto non esistente ?

if(bitvalue(&dbdd[point],g2di_sl) != mess->stato)
{
   bitset(&dbdd[point],g2di_sl,mess->stato) ;
   pack.wto=0;                         // segnalo variazione
   pack.flg=MSG_WAIT;
   pack.amsg=&mtra;
   pack.lmsg=sizeof(S_TRATG);
  	mtra.mess=macdd;  mtra.ext=g1tipdd;
   mtra.indice=point; mtra.stato=mess->stato;
  	enqueue(&pack);
   return(mess->stato);
}   
return(-1);
}

