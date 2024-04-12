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
   Setdic.c

   La funzione tratta il messaggio mddig esaminando tutti
   i punti inseriti

   Parametri

   n_punti  short n. punti inseriti

   24 Feb. 1992   Rel 0.01    Fc
*/

#include <stdio.h>
#include "dconf.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "acqui.inc"
#include "pscserr.inc"

	extern short debsamp;		// flag per emissione non attendibilita'
extern short inv_slave;

extern DB_HEADER h_db;

setdic(n_punti)
short n_punti;
{

S_TRATG mess ;  /* struttura accodamento allarmi al task asinct */ 
short point, k ;
short st_logico; 		/* nuovo stato logico digitale	*/
short st_attendi;		/* nuovo stato attendibilita'	   */
short *p3;			   /* puntatore al data base logico */
QUEUE_PACKET queue;
union DIG_VAL *dig;

queue.que=c_digor;
queue.flg=MSG_WAIT;
queue.wto=0;
queue.amsg=(char*)&mess;
queue.lmsg=sizeof(S_TRATG);

mess.ext= g1tipda ;

dig=&ac.u.m_ddig.dig_val[0];

for(k=0;k<n_punti;k++,dig++)
{
/*
	ricavo indice logico e i due bit di stato
*/
   point = dig->digital & 0x3FFF;

   if(point<0 || point >=h_db.dimda) 
   { 
      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETDI,point,SYS_CONT);
      continue;
   }
   if(dbdau[point]==-1) continue;			/* non installato	*/

   p3= & dbda[point];

   if(dig->digital & 0x8000) st_logico=1;
   else					   st_logico=0;
   if(dig->digital & 0x4000) st_attendi=1;
   else					   st_attendi=0;
/*
	aggiorno comunque flag fisici
*/
   bitset(p3,g2di_afa,st_attendi);
   bitset(p3,g2di_asl,st_logico) ;
   if(bitvalue(p3,g2di_fs) || bitvalue(p3,g2di_fz)) continue;

/*
	verifico se si e' avuta una variazione di stato
	se il punto non e` forzato o fuori scansione aggiorno
	il data base di sistema tenendo  
	ed accodo il punto al task tratg per le
	inibizioni le calcolate e l`emissione dell`eventuale
	allarme
*/

   mess.indice= point ;

   if(st_logico != bitvalue(p3,g2di_sl))
   {
      inv_slave=1;
		mess.stato= st_logico;
  		bitset(p3,g2di_sl,st_logico) ;
      mess.mess= macdi ;                     /* preparo messfer da accodare */
      enqueue(&queue); 
   }
   if(st_attendi != bitvalue(p3,g2di_fa))
   {
      inv_slave=1;
  		bitset(p3,g2di_fa,st_attendi);
      mess.mess= mfadi ;                     /* preparo messaggio da accodare */
/* 
   se flag debsamp = 0 non  viene generato l' allarme  
*/
		if (!debsamp)	mess.mess=mtrdi;
  		mess.stato= st_attendi;
      enqueue(&queue); 
   }
}
}



