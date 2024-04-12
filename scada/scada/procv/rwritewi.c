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
   Rwritewi
      La funzione gestisce il messaggio di scrittura e lettura
      contemporanea nel data base di sistema. Il messaggio ha
      sempre la struttura MCSP ma con diverso indice di messaggio mcspext.
      (il messaggio corriponde all'istruzione RWRITE della config)
      Viene inviato di ritorno alla stop il messaggio con struttura
      VSTAT ma con indice vstatext.

   Parametri
      S_MCSP*  indirizzo messaggio

   Ritorno
        nessuno

   12 Dicembre 1994
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "tipal.inc"

float vsoglia();

Rwritewi (m)
S_MCSP * m ;
{
S_VSTAT v;
S_MALLA mess ;
S_TRATG mtra ;

short ier; 
short newstato ;
float *val, valatt ;
short *flag, flagatt;
short ext ,punt ;
QUEUE_PACKET accodall, accotrg, spack;
short n_soglia;
short trat;

accodall.que = c_visall;      // allarmi analogici
accodall.flg = MSG_WAIT;
accodall.wto = 0;
accodall.lmsg=sizeof(S_MALLA);
accodall.amsg=(char *) & mess;

accotrg.que = c_digor;        // allarmi digitali
accotrg.flg = MSG_WAIT;
accotrg.wto = 0;
accotrg.lmsg=sizeof(S_TRATG);
accotrg.amsg=(char *) & mtra;

/*
   se e` un nome e` sicuramente nella posizione 0 e posso effettuare
   la ricerca ;
   altrimenti e` un puntatore da cui ricavo: ext 1^ mezzo byte alto e
   punt parte rimanente
*/
v.tip_pun=m_nondef;
punt= m->point[2];
ext = m->point[1];
/*
	inizializzo pacchetto per segnalare allarme
*/
mess.ext=ext ;		mess.punt=punt ;		/* per accodall	   */
mess.sogl2= -1 ;
mtra.ext=ext;	mtra.indice=punt ;		/* per accotrg			*/
/*
	in base al tipo di punto eseguo le altre funzioni
*/
switch (m->tipo)
{
case m_analogico:			 		/*			analogici 						*/
	switch(ext)
	{
	case g1tipaa:
		val =&dbaav[punt] ;
		flag=&dbaaf[punt] ;
		break;
	case g1tipas :
		val =&dbasv[punt] ;
		flag=&dbasf[punt] ;
		break ;
	case g1tipac :
		val =&dbacv[punt] ;
		flag=&dbacf[punt] ;
		break ;
	case g1tipad :
		val =&dbadv[punt] ;
		flag=&dbadf[punt] ;
		break ;
	default :
		punt=errtip ;	ext=errtip;
		goto RISP ;
	}

   trat=((trat & M_LSEVA)>>6) + (trat>>12); /* swap tratt. e l_sever */
	v.val.f=*val;      // inserisco nel messaggio vecchi valori
   v.val.s[2]=*flag;
   *val=m->dat.f;        // aggiorno con nuovi valori
   *flag=m->dat.s[2];
	verifall(punt,ext) ;
	break ;

case m_digitale :       // digitali
	switch(ext)
	{
	case g1tipda:
		flag=&dbda[punt] ;
		trat=dbda[punt]&M_TRSED;
		break;
	case g1tipds :
		flag=&dbds[punt] ;
		trat=dbds[punt]&M_TRSED;
		break ;
	case g1tipdc :
		flag=&dbdc[punt] ;
		trat=dbdc[punt]&M_TRSED;
		break ;
	case g1tipdd :
		flag=&dbdd[punt] ;
		trat=dbdd[punt]&M_TRSED;
		break ;
	default :
		punt=errtip ;		ext=errtip;
		goto RISP ;
	}

	newstato= (m->dat.c[0] & 1);
   v.val.c[0]=*(((char*)flag)+1);	 
	if(bitvalue(flag,g2di_sl) != newstato )
	{											/* segnalare la varaz */
		  bitset(flag,g2di_sl,newstato ) ;
		  mtra.stato=newstato;
		  if(ext==g1tipdd) mtra.mess=macdd;
		  else		       mtra.mess=macdi; 
        *(((char*)flag)+1)=m->dat.c[0]   ;	 
   	  enqueue(&accotrg);
	 }
    else    *(((char*)flag)+1)=m->dat.c[0]   ;	 
	 break;

case m_organo :               // organo
	if(ext != g1tipor)
   {
		punt=errtip; ext=errtip; v.tip_pun=m_nondef; 
		goto RISP ;
   }
	flag=&dbosc[punt] ;
   v.val.s[0]=*flag;
	*flag=m->dat.s[0] ;
	break ;

case m_stringa :
	if(ext != g1tipst)
   {
		punt=errtip; ext=errtip; v.tip_pun=m_nondef; 
		goto RISP ;
   }
	memcpy(v.val.c,&dbstv[punt*g0lunst],g0lunst);
	memcpy(&dbstv[punt*g0lunst],m->dat.c,g0lunst);
	break;

case m_anhs:
	n_soglia=g1tiphs; goto GEST_AL;
case m_anls:
	n_soglia=g1tipls; goto GEST_AL;
case m_anhc:
	n_soglia=g1tiphc; goto GEST_AL;
case m_anlc:
	n_soglia=g1tiplc; 
GEST_AL:
	v.val.f=vsoglia(punt,ext,n_soglia);	
	ier=msoglia(m->dat.f,punt,ext,n_soglia,f_mval);
	if(ier)
   {
     	punt=ier ;	ext=ier;
      goto RISP;
   }
	verifall(punt,ext);
   mess.punt=-1;              /* la segnalazione va in stampe  */
	break ;                    /* direttamente                  */

default:
  	punt=errtip ;	ext=errtip;
   goto RISP;
}
wrdb(ext); 						
v.tip_pun=m->tipo;

RISP : 			         // invio messaggio di risposta

v.indice=vstatext ;
v.zona = m->zona; 
v.video=m->video;
v.nodo=v.video-1;
v.dbl=m->dbl;
memcpy(&v.pag[0],&m->pag[0],10);
v.punt=punt ;
v.ext=ext ;

spack.que = c_mmio;
spack.flg = MSG_WAIT;
spack.wto = 0;
spack.lmsg=sizeof(S_VSTAT);
spack.amsg=(char *) & v;
enqueue(&spack);
}
