/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   GdcAllS
      funzione per inviare un generare un allarme di tipo stringa

   Parametri
      short punt  indice in data base del punto
      char* valore della stringa

   Ritorno
      nessuno
*/
#include "comunic.inc"
#include "mesqueue.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "repgdc.h"
#include "mesprocv.inc"
#include "messcada.inc"
#include "allar.inc"
#include "diagnoan.inc"

void GdcAllS(short point, char* val)
{
S_MALLA mess;
QUEUE_PACKET queue;

queue.que = c_visall;
queue.flg = MSG_WAIT;			 
queue.wto = 0;					  
queue.amsg = (char *)  &mess;
queue.lmsg=sizeof(S_MALLA);
mess.ertr=dbsttr[point] | 0x80;  /* emissione trattamento        */
mess.sprec=mis_norm; mess.satt=mod_st ; 
mess.sogl1= -1;
mess.sogl2= -1 ;
mess.ext=g1tipst;                /* estensione                   */
mess.punt=point;                 /* puntatore                    */

enqueue(&queue);
return;
}

