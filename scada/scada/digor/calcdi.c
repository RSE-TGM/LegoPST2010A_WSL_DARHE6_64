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
/*-> calcdi

	la function calcdi  calcola il valore del
	digitale calcolato standard di cui viene
	passato il puntatore

	punt short input puntatore in db della calolata
				da eseguire
	i calcoli previsti sono :
	1.	and
	2.	or
	3.	xor

   16 Marzo 1995
   Se la coda c_digor e' piena abilito il flag di ricalcolo
   di tutti i digitali ed organi

*/
#include <osf1.h>
#include <stdio.h>

#include "pscserr.inc"
#include "dconf.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"

extern DB_HEADER h_db;

calcdi(punt)
short punt ;
{
QUEUE_PACKET queue;
S_TRATG mtra ;
S_DCALC *des ;
short i,stato,val,flag  ;

if(punt<0 || punt>=h_db.dimds) {visch('C'); return(0);}

queue.que = c_digor;
queue.flg = MSG_NOWAIT;
queue.wto = 0;
queue.amsg = (char *)  &mtra;
queue.lmsg=sizeof(S_TRATG);
/*
	il digitale viene calcolato solo se non e' o
	fuori scansione o forzato
*/
if(bitvalue(&dbds[punt],g2or_fs) || bitvalue(&dbds[punt],
			     g2or_fz)) return(0) ;

des=& dbdsde[punt] ;

stato=0 ;
for(i=0;i<ds_cont;i++)
{
	switch(des->ext[i])
	{
	case g1tipda :
		val=bitvalue(&dbda[des->punt[i]],g2di_sl) ;
		flag=bitvalue(&dbda[des->punt[i]],g2di_fa) ||
		     bitvalue(&dbda[des->punt[i]],g2di_fs) ;
		  break ;
	case g1tipds :
		val=bitvalue(&dbds[des->punt[i]],g2di_sl) ;
		flag=bitvalue(&dbds[des->punt[i]],g2di_fa) ||
		     bitvalue(&dbds[des->punt[i]],g2di_fs) ;
		break ;
	case g1tipdc :
		val=bitvalue(&dbdc[des->punt[i]],g2di_sl) ;
		flag=bitvalue(&dbdc[des->punt[i]],g2di_fa) ||
		     bitvalue(&dbdc[des->punt[i]],g2di_fs) ;
		break ;
	case g1tipdd :
		val=bitvalue(&dbdd[des->punt[i]],g2di_sl) ;
		flag=bitvalue(&dbdd[des->punt[i]],g2di_fa) ||
		     bitvalue(&dbdd[des->punt[i]],g2di_fs) ;
		break ;
   default:
      goto FINE;
	}
	if(flag)  goto FINE ;
/*
	la calcolata risulta fuori attendibilita'
	non continuo con i calcoli
*/
	if(! i) stato=val ;	/* primo valore	*/
	else
	{
		switch(des->tipc)
		{
		case 1:			/* and	*/
			stato=stato & val ;
			break;
		case 2:			/* or	*/
			stato=stato | val ;
			break;
		case 3:			/* xor 	*/
			stato=stato + val ;
			break;
		default :
         pscserr(ERR_TASK,TASK_ASINCT,ROU_CALCDIT,des->tipc,SYS_CONT);
			break ;
		}
	}
}
FINE :
/*
   nel caso di xor se stato=0 o stato=n. contribuenti risultato=0
   altrimenti =1
*/
if(des->tipc==3)
{
   if(!stato || stato==i) stato=0;
   else stato=1;
}
/*
	se e' variato o il flag o il valore deve essere
	accodato ad asinct il puntatore del punto per
	emissione dell'allarme
	se il punto e' FA devo esguire solo il trattamento del
	digitale e non emettere l'allarme (messaggio mridi)
	se variato lo stato devo emettere l'allarme (messaggio macdi)
*/
mtra.indice=punt;
mtra.ext=g1tipds;
mtra.stato=stato ;

if(stato  != bitvalue(&dbds[punt],g2di_sl) && !flag)
{
	mtra.mess=macdi ;
	if(enqueue(&queue))     // verra' calcolato da attiper
   {
      flag_ordi=1;
      return (0);
   }
}
else		/* se e` variato solo il flag di FA richiedo solo il */
{		/* trattamento e non emetto allarmi		     */
	if(flag != bitvalue(&dbds[punt],g2di_fa))
	{	
		mtra.mess=mtrdi ;		
		if(enqueue(&queue)) flag_ordi=1;    // coda piena abilitato il ricalcolo di tutti i digitali
	}
}
/*
	inserisco il valore nella calcolata	solo se attendibile
*/
if(!flag) bitset(&dbds[punt],g2di_sl,stato) ;
bitset(&dbds[punt],g2di_fa,flag) ;
return(0) ;
}
