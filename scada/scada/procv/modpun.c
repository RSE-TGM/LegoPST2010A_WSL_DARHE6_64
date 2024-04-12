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
		la function modpun esegue il forzamento la fuori scansione e
		la messa in scansione di tutti i tipi di punto

      20 Gennaio 1993
      Inserimento trattamento severita'

      02 Marzo 1995 Fc
      Inserimento generazione allarmi in base alla variazione dei flag
      di allarme (solo per analogici) e di fuori attendibilita' (per analo-
      gici e digitali) mediante i messaggi con funzione mvaf o mfla
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

extern get_aa_val(short);

float vsoglia();
/*	
	la subroutine modpun gestisce la modifica
	di un qualsiasi punto in data base
	Viene passata la struttura S_MCPS in cui sono specificate:
	char indice
	char zona
	char video
	char point puntatore in db
	funz   short funzione da eseguire
	tipo   short tipo di data base a cui deve appartenere
	       il punto
	dat    puntatore al vettore che contiene i dati da
	       trasferire ( i dati digitali sono nel 2 byte per swap)

Viene preparato il messaggio di risposta VSTAT in cui compaiono i campi
	lun 	lunghezza del messaggio
	indice  indice del messaggio
	video   video interessato
	zona video	zona
	punt    puntatore in d.b. swappato ;
	valori e flag  valori e flags aggiornati con le modifiche

      03 Marzo 1995
         Modificata la gestione di scrittura dei flag analogici
         in caso di messaggio di modifica flag o valore e flag
         Vengono esaminati i flag HC HS LC LS DH DL e vengono
         generati gli opportuni allarmi in base al tipo di trattamento
         del punto (routine exall e exfa)

*/
modpun(m,bWild)
S_MCSP m ;
short bWild;   // e' a 1 se si stanno modificando punti con wildcharacters
	     		   // 	a 2 se si vuole inviare un messaggio di fine scansione
			      //    a 0 per modifica punti senza wild characters
{
S_VSTAT v;
S_MALLA mess ;
S_TRATG mtra ;

short i,ier,*flag ;  /* ier= punt. db o codice errore */
char *cflag ;
long blocco; 
short  posiz, newstato ;
float *val ;
short ext ,punt ;
short rientro_fa ;
char *p1 ;
short trat;
QUEUE_PACKET accodall, accotrg, spack;
float val_prec;
short n_soglia;
S_DBALL* all;
short bytef;

/*
	vede se deve inviare per punti con wildch. il messaggio di fine
	scansione.
*/
if(bWild==2) {v.tip_pun=m_analogico; goto RISP;}

accodall.que = c_visall;		  /* accodamento per call	*/
accodall.flg = MSG_WAIT;
accodall.wto = 0;
accodall.lmsg=sizeof(S_MALLA);
accodall.amsg=(char *) & mess;

accotrg.que = c_digor;	  		/*	accodamento per asinct */
accotrg.flg = MSG_WAIT;
accotrg.wto = 0;
accotrg.lmsg=sizeof(S_TRATG);
accotrg.amsg=(char *) & mtra;

/* se e` un nome e` sicuramente nella posizione 0 e posso effettuare
   la ricerca ;
   altrimenti e` un puntatore da cui ricavo: ext 1^ mezzo byte alto e
   punt parte rimanente
*/
v.tip_pun=m_nondef;
if(m.point[0])
    {
			 p1= (char *) & m.point[0] ;
		    for(i=0;i<SCD_SIGLA;i++,p1++) if( (*p1) == ' ') (*p1) = 0 ;
          if(ricerca(m.point,&punt,&ext,&blocco,&posiz,fpp[fnomi]))
	  		 {   ext=erres; 			/*		  misura non esistente 				*/
	      	  goto RISP ; 
			  }
   }
    else
	 { 	punt= m.point[2];
     		ext = m.point[1];
	 }

rientro_fa=0 ;							/* non emettere allarme rientro fa	*/
/*
	inizializzo pacchetto per segnalare allarme
*/
mess.ext=ext ;		mess.punt=punt ;		/* per accodall	   */
mess.sogl2= -1 ;
mtra.ext=ext;	mtra.indice=punt ;		/* per accotrg			*/
/*
	in base al tipo di punto eseguo le altre funzioni
*/
switch (m.tipo)
{
case m_analogico:			 		/*			analogici 						*/
	switch(ext)
	{
	case g1tipaa:
		val =&dbaav[punt] ;
		flag=&dbaaf[punt] ;
		all=&dbaaal[punt]; 
		break;
	case g1tipas :
		val =&dbasv[punt] ;
		flag=&dbasf[punt] ;
		all=&dbasal[punt];
		break ;
	case g1tipac :
		val =&dbacv[punt] ;
		flag=&dbacf[punt] ;
		all=&dbacal[punt];
		break ;
	case g1tipad :
		val =&dbadv[punt] ;
		flag=&dbadf[punt] ;
		all=&dbadal[punt];
		break ;
	case g1tipao:			 				/* invio del set point */
		invao(punt,m.dat.f);
		return;
	default :
		punt=errtip ;	ext=errtip;
		goto RISP ;
	}

   trat=all->tr_bdm;
   trat=((trat & M_LSEVA)>>6) + (trat>>12); /* swappo tratt. e l_sever */  

	switch(m.funz)
	{
	case f_none :						/* nessuna modifica 					*/
		v.val.f=*val ;	  v.val.s[2]=*flag ;
		break ;
	case f_mvaf :                 /* modif.valori e flag 				*/
	case f_mval :                 /* modif. solo valori 				*/
		*val=m.dat.f ;
		if(m.funz!=f_mval)
      {
         exfa(punt,ext,all,flag,m.dat.s[2]);
         if(exall(punt,ext,all,flag,m.dat.s[2]))
            verifall(punt,ext) ;          // soglie definite
      }
		else verifall(punt,ext) ;
		break ;
	case f_mfla :						/* modif. solo flag   				*/
      exfa(punt,ext,all,flag,m.dat.s[2]);
      exall(punt,ext,all,flag,m.dat.s[2]);
		break ;
	case f_forz :						/* forzamento punto   				*/
		bitset(flag,g2an_fz,1) ;
		bitset(flag,g2an_fs,0) ;
		if(bitvalue(flag,g2an_fa))	/* emettere rientro fa				*/
                     rientro_fa =1 ;
		bitset(flag,g2an_fa,0) ;
		*val=m.dat.f ;
		verifall(punt,ext) ;
		v.val.f=m.dat.f ;
		mess.ertr= 0x80 ;
		mess.sprec=mis_norm ;
		mess.satt=pun_forz ;
		mess.sogl1=-1 ;
		break ;
	case f_fsca :						/* fuori scansione pto				*/
		if(bitvalue(flag,g2an_fs))
			{ punt= errfs; ext=errfs; v.tip_pun=m_nondef ;goto RISP ;}
		bitset(flag,g2an_fs,1) ;
		bitset(flag,g2an_fz,0) ;
		if(bitvalue(flag,g2an_fa))  /* emettere rientro fa 			*/
		   rientro_fa=1 ;
		bitset(flag,g2an_fa,0) ;
		mess.ertr= 0x80 ;
		mess.satt=fuori_scan ;
		mess.sprec=mis_norm ;
		mess.sogl1=-1 ;
		break ;
	case f_isca :						/* in scansione punto 				*/
		if(!bitvalue(flag,g2an_fs) & (!bitvalue(flag,g2an_fz)))
			{ punt= errin ;  ext=errin; v.tip_pun=m_nondef; goto RISP ;}
		bitset(flag,g2an_fs,0) ;
		bitset(flag,g2an_fz,0) ;
		mess.ertr= 0x00 ;
		mess.sprec=fuori_scan ;
		mess.satt=mis_norm ;
		mess.sogl1=-1 ;
#if defined (AC_SAMP)
		get_aa_val(punt);
#endif
		break ;
	} /* end switch(m.funz) */
	break ;
case m_digitale :
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
	switch(m.funz)
	{
	case f_none :						/* nessuna modifica 				*/
		v.val.s[0]=*flag ;
		break ;
	case f_mvaf :                 /* modif.valori e flag 			*/
	case f_mval :                 /* modif. solo valori   		*/
		newstato= (m.dat.c[0] & 1);
  	   cflag=(char *) flag ;
      bytef=m.dat.c[0] << 8;
      if(m.funz!= f_mval)
         exfa(punt,ext,all,flag,bytef);
		if(bitvalue(flag,g2di_sl) != newstato )
		{											/* segnalare la varaz */
		  bitset(flag,g2di_sl,newstato ) ;
		  mtra.stato=newstato;
		  if(ext==g1tipdd) mtra.mess=macdd;
		  else		       mtra.mess=macdi; 
	     if(m.funz!= f_mval) *(cflag+1)=m.dat.c[0]   ;	 
   	  enqueue(&accotrg);
		}
      else if(m.funz!= f_mval) *(cflag+1)=m.dat.c[0]   ;	 
//		printf("\n %x %x",m.dat.c[0], m.dat.c[1]);
		break ;
	case f_mfla :						/* modif. solo flag   				*/
      bytef=m.dat.c[0] << 8;
      exfa(punt,ext,all,flag,bytef);
		cflag=(char *) flag ;
		*cflag=(m.dat.c[0] & 0xFE) ;
		break ;
	case f_forz :						/* forzamento punto   				*/
		bitset(flag,g2di_fz,1) ;
		bitset(flag,g2di_fs,0) ;
		if(bitvalue(flag,g2di_fa)) rientro_fa=1;
		bitset(flag,g2di_fa,0) ;

/* se il valore forzato e` diverso dal valore precedente si inviano
   i messaggi "macdd" oppure "macdi" ; altrimenti "mtrdi"	*/

		mtra.stato=m.dat.c[0];
		if(m.dat.c[0] != bitvalue(flag,g2di_sl))
		  {
		  if(ext==g1tipdd) mtra.mess=macdd; 
		  else		       mtra.mess=macdi; 
		  }
		else 	mtra.mess=mtrdi; 
		bitset(flag,g2di_sl,m.dat.c[0]) ;
	   enqueue(&accotrg);
		mess.ertr=0x80 ;
		mess.satt=pun_forz ;
		mess.sprec=mis_norm ;
		mess.sogl1=m.dat.c[0] ;
		break ;
	case f_fsca :			/* fuori scansione pto*/
		if(bitvalue(flag,g2di_fs))
			{ punt= errfs ; ext=errfs; v.tip_pun=m_nondef;goto RISP ;}
		bitset(flag,g2di_fs,1) ;
		bitset(flag,g2di_fz,0) ;
		if(bitvalue(flag,g2di_fa)) rientro_fa=1;
		bitset(flag,g2di_fa,0) ;
		mtra.mess=mtrdi; 
	   enqueue(&accotrg);
		mess.ertr=0x80 ;
		mess.satt=fuori_scan ;
		mess.sprec=mis_norm ;
		mess.sogl1=-1 ;
		break ;
	case f_isca :			/* in scansione punto */
		if(!bitvalue(flag,g2di_fs) & (!bitvalue(flag,g2di_fz)))
			{ punt= errin ; ext=errin; v.tip_pun=m_nondef;goto RISP ;}
		bitset(flag,g2di_fs,0) ;
		bitset(flag,g2di_fz,0) ;
		mtra.mess=mcadi; 
	   enqueue(&accotrg);
		mess.ertr=0x00 ;
		mess.sprec=fuori_scan ;
		mess.satt=mis_norm ;
		mess.sogl1=-1 ;
		break ;
	} /* end switch(m.funz) */
	break;
case m_organo :
/*
	verifico che il tipo di data base coincida con il
	tipo di punto

*/
	if(ext != g1tipor) {
				punt=errtip; ext=errtip; v.tip_pun=m_nondef; 
				goto RISP ;}
	flag=&dbosc[punt] ;
	switch(m.funz)
	{
	case f_none :							/* nessuna modifica 				*/
		v.val.s[0]=*flag ;
		break ;
	case f_mvaf :                   /* modif.valori e flag 			*/
		*flag=m.dat.s[0] ;
		break ;
	case f_mval :                   /* modif. solo valori 			*/
		cflag=(char *) flag ;		/* a byte	      */
		*(cflag+1)=m.dat.c[1] ;
		break ;
	case f_mfla :							/* modif. solo flag   			*/
		cflag=(char *) flag ;            /* a byte	      */
		*cflag=m.dat.c[0];
		break ;
	case f_forz :							/* forzamento punto   			*/
	   if(m.dat.c[0]) v.val.s[0]=ctrlstato(m.dat.c,&storg[dbode[punt].tipo],stat_diz) ;
		else v.val.s[0]=m.dat.c[1];
		if(v.val.s[0] < 0){ punt=errst; ext=errst; v.tip_pun=m_nondef; goto RISP;}
		bitset(flag,g2or_fz,1) ;
		bitset(flag,g2or_fs,0) ;
		bitset(flag,g2or_fa,0) ;
		if(v.val.s[0] != (*flag & 0x00FF) )
	   {
			*flag =(*flag & 0xFF00) + v.val.s[0] ;
			mtra.mess=mtror; 
			mtra.stato=v.val.s[0];
			dbosp[punt]=v.val.s[0];
	   	enqueue(&accotrg);
		}
		mess.ertr=0x80 ;
		mess.satt=pun_forz ;
		mess.sprec=mis_norm ;
		mess.sogl1=v.val.s[0] ;
		break ;
	case f_fsca :						/* fuori scansione pto			*/
		if(bitvalue(flag,g2or_fs))
			{ punt= errfs ; ext=errfs ; v.tip_pun=m_nondef;goto RISP ;}
		bitset(flag,g2or_fs,1) ;
		bitset(flag,g2or_fz,0) ;
		if(bitvalue(flag,g2di_fa)) rientro_fa=1;
		bitset(flag,g2or_fa,0) ;
		v.val.s[1]=*flag ;
		mess.ertr=0x80 ;
		mess.satt=fuori_scan ;
		mess.sprec=mis_norm ;
		mess.sogl1=-1 ;
		break ;
	case f_isca :					/* in scansione punto 				*/
		if(!bitvalue(flag,g2or_fs) & (!bitvalue(flag,g2or_fz)))
			{ punt= errin ; ext=errin; v.tip_pun=m_nondef;goto RISP ;}
		bitset(flag,g2or_fs,0) ;
		bitset(flag,g2or_fz,0) ;
		v.val.s[1]=*flag ;
		mtra.mess=mcaor; 
	   enqueue(&accotrg);
		mess.ertr=0x00 ;
		mess.sprec=fuori_scan ;
		mess.satt=mis_norm ;
		mess.sogl1=-1 ;
		break ;
	} /* end switch(m.funz) */
	v.val.s[0]=*flag;
	break ;
case m_dout    :			  
	coman(punt) ;					/*	 invio comando	*/	 
	return ;
	break;
case m_stringa :
	switch(m.funz)
	{
	case f_none :							/* nessuna modifica 				*/
		memcpy(v.val.c,&dbstv[punt*g0lunst],g0lunst);
		break ;
	case f_mvaf :                   /* modif.valori  			*/
	case f_mval :              
	case f_mfla :							/* modif. solo flag   			*/
		memcpy(&dbstv[punt*g0lunst],m.dat.c,g0lunst);
		mtra.mess=macst;
		enqueue(&accotrg);
		break;
	case f_forz :							/* forzamento punto   			*/
		memcpy(&dbstv[punt*g0lunst],m.dat.c,g0lunst);
		mess.ertr= 0x80 ;
		mess.sprec=mis_norm ;
		mess.satt=pun_forz ;
		mess.sogl1=-1 ;
		mess.sogl2=-1;
		break;
	}
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
// printf(" arrivato messaggio %d val %f funz %d",n_soglia,m.dat.f,m.funz);
   switch(m.funz)
	{
	case f_none :						/* nessuna modifica 					*/
		v.val.f=vsoglia(punt,ext,n_soglia);	
		break ;
	case f_forz :						/* forzamento soglia   				*/
	case f_mvaf :                 /* modif.valori e flag 				*/
	case f_mval :                 /* modif. solo valori 				*/
		ier=msoglia(m.dat.f,punt,ext,n_soglia,m.funz);
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
  break;
}  /*end switch(m.tipo) */
/*
	segnalazione della modifica del punto in caso
	di forzamento, fuori scansione o in scansione
*/
switch(m.funz)
{
case f_forz:
case f_isca:
case f_fsca:
	wrdb(ext);										/* salvo in dbs le variazioni						 */
	mess.ertr= mess.ertr + trat_op ;
	if(mess.punt!=-1) enqueue(&accodall) ;	  
	if(rientro_fa && m.tipo==m_analogico)   /* se il punto e' fa deve rientrare l'allarme */
	{	mess.ertr=trat ;  mess.sprec=non_att; 	mess.satt=mis_norm ;
		mess.sogl1=-1;		mess.sogl2=0 ;  
		enqueue(&accodall) ;
	}
	if(rientro_fa && m.tipo==m_digitale)   /* se il punto e' fa deve rientrare l'allarme */
	{	mess.ertr=trat ;  mess.sprec=non_att; 	mess.satt=mis_norm ;
		mess.sogl1=-1;		mess.sogl2=-1 ;  
		enqueue(& accodall) ;
	}
	break ;
case f_mvaf :                 /* modif.valori e flag 				*/
case f_mval :                 /* modif. solo valori 				*/
//	wrdb(ext); 						// problematico in caso di collegamento isa in continuo aggiornamento   
	return;							/* in caso di scrittura in dbs   */
}										/* non devo inviare il mess. di  */
										/* risposta								*/

v.tip_pun=m.tipo;

RISP : 						/* invio messaggio di risposta al task della stop */
/*
  in caso di wildch e scansione fnomi in atto non manda il messaggio di errore
*/
if(bWild==1) return;

// /* Modifica per permettere l' accesso anche da pag */
if (m.video == 0) return;
v.indice=vstat ;
/*
   il messaggio deve essere sempre riferito alla zona window utilizzata
   per la scrittura del codice di errore
*/
v.zona = m.zona; 
v.video=m.video;
v.nodo=v.video-1;
memcpy(&v.pag[0],&m.pag[0],10);
v.punt=punt ;
v.ext=ext ;

spack.que = c_mmio;
spack.flg = MSG_WAIT;
spack.wto = 0;
spack.lmsg=sizeof(S_VSTAT);
spack.amsg=(char *) & v;
enqueue(&spack);
}
