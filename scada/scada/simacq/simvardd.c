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
   SIMVARDD.C

      Genera allarmi di variazione stato di punti digitali di diagnostica
   
   
   10.09.92  -  Rel. 1.00  -  GM.Furlan

   27 Marzo 1995 Fc Porting a 32Bit
*/
#include "messcada.inc"
#include "mesqueue.h"
#include "comunic.inc"
#include "g1tipdb.inc"

simvardd(p_index,st_log)
short p_index;    /* indice in DBS del punto */
short st_log;     /* stato logico digitale */
{
S_TRATG mess ;    /* struttura accodamento allarmi al task asinct */ 
QUEUE_PACKET queue;

   mess.mess=macdd;                 /* messaggio da accodare */
   mess.stato=st_log;
   mess.ext=g1tipdd;
   mess.indice=p_index;

   queue.que=c_digor;               /* accodamento */
   queue.flg=MSG_WAIT;
   queue.wto=0;
   queue.amsg=(char*)&mess;
   queue.lmsg=sizeof(S_TRATG);
   enqueue(&queue); 
}
