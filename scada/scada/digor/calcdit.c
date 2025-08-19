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
#include <stdio.h>
/*-> calcdit

   La funzione calcdit esegue le calcolate digitali per valori
   generati da posto periferico
	i calcoli previsti sono :
	1.	and
	2.	or
	3.	xor

   Parametri

   punt     short    puntatore digitale calcolo da eseguire
   time     *MISTIME tempo posto periferico associato all'allarme

   4 Dicembre 1992 Fc.

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"
#include "pscserr.inc"
#include "dconf.inc"

extern DB_HEADER h_db;

/* Function prototypes */
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);
extern void pscserr(int, int, int, int, int);

int calcdit(punt,time)
short punt ;
MISTIME *time;
{
QUEUE_PACKET pack;
S_TRATGT mtra ;
S_DCALC *des ;
int i,stato,val,flag  ;

if(punt<0 || punt>=h_db.dimds)
   {
   //_visch('C');
   return(0);
   }

pack.que = c_digor;
pack.flg = MSG_NOWAIT;
pack.wto = 0;
pack.amsg = (char *)  &mtra;
pack.lmsg=sizeof(S_TRATGT);
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
mtra.m.indice=punt;
mtra.m.ext=g1tipds;
mtra.m.stato=stato ;
mtra.t=*time;

if(stato  != bitvalue(&dbds[punt],g2di_sl) && !flag)
{
	mtra.m.mess=macdit ;
	enqueue(&pack);
}
else		/* se e` variato solo il flag di FA richiedo solo il */
{		/* trattamento e non emetto allarmi		     */
	if(flag != bitvalue(&dbds[punt],g2di_fa))
	{	
		mtra.m.mess=mtrdit ;		
		enqueue(&pack) ;
	}
}
/*
	inserisco il valore nella calcolata	solo se attendibile
*/
if(!flag) bitset(&dbds[punt],g2di_sl,stato) ;
bitset(&dbds[punt],g2di_fa,flag) ;
return(0) ;
}
