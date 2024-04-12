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
   armadio  short n. dell'armadio
	dig	   S_DIG_VAL * primo elemento del messaggio

   24 Feb. 1992   Rel 0.01    Fc

   Trattamento inversione di polarita'
	10 Gennaio 1994	Rel. 0.02	Fc
*/
#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "tipal.inc"
#include "pscserr.inc"
#include "sepdati.inc"
#include "dconf.inc"

extern short debsamp;		// flag per emissione non attendibilita'
extern DB_HEADER h_db;

setdic(n_punti,armadio,dig)
short n_punti, armadio;
union DIG_VAL *dig;
{

S_TRATG mess ;  /* struttura accodamento allarmi al task asinct */ 
short point, k ;
short st_logico; 		/* nuovo stato logico digitale	*/
short st_attendi;		/* nuovo stato attendibilita'	   */
short *p3;			   /* puntatore al data base logico */
QUEUE_PACKET pack;

pack.que=c_digor;
pack.flg=MSG_WAIT;
pack.wto=0;
pack.amsg=(char*)&mess;
pack.lmsg=sizeof(S_TRATG);

mess.ext= g1tipda ;

//printf("\n n_punti %d armadio %d ",n_punti,armadio);

for(k=0;k<n_punti;k++,dig++)
{
/*
	ricavo indice logico e i due bit di stato
*/
   point = dig->digital & 0x3FFF;
	if(point < 1 || point > heafsvar[armadio].l_punto)
	{
//      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETDI,armadio,SYS_CONT);
//      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETDI,point,SYS_CONT);
      continue;
	}
   point=(*(svinarp[armadio]+point-1));
   if(point==-1) continue;
	
	point=point & (~mask_tpun);		  	// elimino flag di riconoscimento
   if(point<0 || point >=h_db.dimda)
   { 
//      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETDI,point,SYS_CONT);
      continue;
   }
   if(dbdau[point]==-1) continue;			/* non installato	*/

   p3= & dbda[point];

   if(dig->digital & 0x8000) st_logico=1;
   else					   st_logico=0;
	st_logico=st_logico ^ bitvalue(&dbdatr[point],g2di_ip);	// inversione di polarita'
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
      enqueue(&pack); 
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
      enqueue(&pack); 
   }
}
}



