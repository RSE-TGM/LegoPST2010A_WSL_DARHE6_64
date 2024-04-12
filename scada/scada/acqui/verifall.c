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
/*-> verifall

	la function verifall  verifica i limiti di
	allarme dei punti
	vengono considerati per primi i limiti di sicurezza
	(alto e basso) e successivamente i limiti di conduzione
	(alto e basso)
	i limiti bassi di conduzione e sicurezza possono venire
	inibiti settando i flag DC e DS

	punt	short in puntatore in data base del punto
	tipo    short in tipo del punto

   20 Gennaio 1993
   Inserita gestione livelli di severita'

*/
#include <math.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "mesqueue.h"

extern short c_visall;

verifall(punt,tipo)
short punt;
short tipo;
{
QUEUE_PACKET pack;
S_MALLA mess ;
double limite ;
short fuorat[4] ;		/* flag di misura soglia fuori att. */
union valin soglia[4];
float valore;
short *flag;
short banda ;
short valflag ;		/* save flag misura */
short statoall();
short basso ;  /* flag che indica la soglia che si esamina */
static short verin[4]={g2an_dh,g2an_dl,g2an_dh,g2an_dl} ;   /* inibizioni */
static short verfl[4]={g2an_hs,g2an_ls,g2an_hc,g2an_lc} ; /* allarmi */
short i ;
char trat;

pack.que = c_visall;
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &mess;
pack.lmsg=sizeof(S_MALLA);
/*
	in base al tipo di punto memorizzo il suo valore
	i flag, le soglie di allarme e la banda morta
*/

   mess.ext=tipo & 0x7FFF;

mess.punt=punt;
   switch(tipo & 0x7FFF)
{
case g1tipaa :
	valore=dbaav[punt]; flag=&dbaaf[punt] ;
	soglia[0]=dbaaal[punt].alto_sic ;
	soglia[1]=dbaaal[punt].bass_sic ;
	soglia[2]=dbaaal[punt].alto_con ;
	soglia[3]=dbaaal[punt].bass_con ;
	banda=dbaaal[punt].tr_bdm ;
	break;
case g1tipas :
	valore=dbasv[punt]; flag=&dbasf[punt] ;
	soglia[0]=dbasal[punt].alto_sic ;
	soglia[1]=dbasal[punt].bass_sic ;
	soglia[2]=dbasal[punt].alto_con ;
	soglia[3]=dbasal[punt].bass_con ;
	banda=dbasal[punt].tr_bdm ;
	break;
case g1tipac :
	valore=dbacv[punt]; flag=&dbacf[punt] ;
	soglia[0]=dbacal[punt].alto_sic ;
	soglia[1]=dbacal[punt].bass_sic ;
	soglia[2]=dbacal[punt].alto_con ;
	soglia[3]=dbacal[punt].bass_con ;
	banda=dbacal[punt].tr_bdm ;
	break;
case g1tipad :
	valore=dbadv[punt]; flag=&dbadf[punt] ;
	soglia[0]=dbadal[punt].alto_sic ;
	soglia[1]=dbadal[punt].bass_sic ;
	soglia[2]=dbadal[punt].alto_con ;
	soglia[3]=dbadal[punt].bass_con ;
	banda=dbadal[punt].tr_bdm ;
	break;
}
/*
	se il punto e` fuori attendibilita` o fuori scansione
	gli allarmi non vengono controllati
*/
if(bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs)) return ;
/*
	ciclo per esaminare le diverse soglie
*/
trat=((banda & M_LSEVA)>>6) + (banda>>12);  
banda= banda & M_BMORA;		/* banda       */
valflag= *flag ;	/* salvo il valore dei flag */
basso=0 ;	/* la prima soglia e` alta sicurezza */
for(i=0;i<4;i++)
{
	fuorat[i]=0 ;
	switch(soglia[i].cval[0])
	{
	case -1 :	             /* limite variabile */
		switch(soglia[i].cval[1])
		{
		case g1tipaa :
			fuorat[i]=bitvalue
			  (&dbaaf[soglia[i].sval[1]],g2an_fa) ||
		bitvalue  (&dbaaf[soglia[i].sval[1]],g2an_fs) ;
			soglia[i].fval=dbaav[soglia[i].sval[1]] ;
			break ;
		case g1tipac :
			fuorat[i]=bitvalue
			  (&dbacf[soglia[i].sval[1]],g2an_fa) ||
		bitvalue  (&dbacf[soglia[i].sval[1]],g2an_fs) ;
			soglia[i].fval=dbacv[soglia[i].sval[1]] ;
			break ;
		case g1tipas :
			fuorat[i]=bitvalue
			  (&dbasf[soglia[i].sval[1]],g2an_fa) ||
		bitvalue  (&dbasf[soglia[i].sval[1]],g2an_fs);
			soglia[i].fval=dbasv[soglia[i].sval[1]] ;
			break ;
		case g1tipad :
			fuorat[i]=bitvalue
			  (&dbadf[soglia[i].sval[1]],g2an_fa) ||
		bitvalue  (&dbadf[soglia[i].sval[1]],g2an_fs) ;
			soglia[i].fval=dbadv[soglia[i].sval[1]] ;
			break ;
		}
		break;
	case -2 : goto PROSSIMA ;     /* nessun limite */
	        break ;
	}

/*
	ho il valore floating della soglia
*/
	 limite=soglia[i].fval * banda /100 ;
	 if(basso)		/* controllo limiti bassi */
	 { if(bitvalue(flag,verfl[i]) && (valore >= (soglia[i].fval +
	   fabs(limite)) || fuorat[i] ))
/*
	la misura e` in allarme devo verificare se e` rientrato
	tenendo presente l`intervallo della banda morta
	il rientro viene effettuato comunque se la misura limite
	e` fuori attendibilita
*/
		{
         bitset(flag,verfl[i],0) ;
   		if(!bitvalue(flag,verin[i]))
         {
      		mess.ertr=trat;
      		mess.sprec=all_an[i];
		      mess.satt=statoall(flag);
      		mess.sogl1=i;
		      mess.sogl2=0;
            if(tipo & 0x8000) verifalt(&pack,&mess);
            else
         		enqueue(&pack);
         }
		goto PROSSIMA ;
		}
/*
	la misura non e` in allarme verifico che non lo
	sia
*/
	 if(!bitvalue(flag,verfl[i]) && (valore < soglia[i].fval)
	    && ! fuorat[i] )
		{
			bitset(flag,verfl[i],1) ;
			if(!bitvalue(flag,verin[i]))
			{
				mess.ertr=trat | 0x80;
 				mess.sprec=statoall(&valflag);
	  			mess.satt=all_an[i];
				mess.sogl1=i;
				mess.sogl2=0;
		      if(tipo & 0x8000) verifalt(&pack,&mess);
      		else
	        			enqueue(&pack); 
			}
		}
	}
	else    		/* controllo limiti alti */
	{if(bitvalue(flag,verfl[i]) && (valore<=(soglia[i].fval -
	 	fabs(limite)) || fuorat[i] ))
/*
	la misura e` in allarme devo verificare se e` rientrato
        tenendo presente l`intervallo della banda morta
	il rientro viene effettuato comunque se la misura soglia
	e` fuori attendibilita`
*/
		{
         bitset(flag,verfl[i],0) ;
   		if(!bitvalue(flag,verin[i]))
         {
      		mess.ertr=trat ;
		      mess.sprec=all_an[i];
      		mess.satt=statoall(flag);
		      mess.sogl1=i;
      		mess.sogl2=0;
            if(tipo & 0x8000) verifalt(&pack,&mess);
            else
   		      enqueue(&pack);
         }
		goto PROSSIMA ;
		}
/*
	la misura non e` in allarme verifico che non lo
	sia ora
*/
	 if(!bitvalue(flag,verfl[i]) && (valore > soglia[i].fval )
	     && ! fuorat[i] )
		{
			bitset(flag,verfl[i],1) ;
			if(!bitvalue(flag,verin[i]))
			{
					mess.ertr=trat | 0x80;
 					mess.sprec=statoall(&valflag);
					mess.satt=all_an[i];
					mess.sogl1=i;
					mess.sogl2=0;
   		      if(tipo & 0x8000) verifalt(&pack,&mess);
         		else
	   				enqueue(&pack); 
			}
		}
	}
PROSSIMA : basso= ! basso ;
}
return ;

}
/*
	la function statoall fornisce lo stato di una misura
	analogica dato il puntatore short ai respettivi flag
*/
short statoall(ind)
short *ind;
{
if(bitvalue(ind,g2an_hs))return(sic_al);
if(bitvalue(ind,g2an_ls))return(sic_ba);
if(bitvalue(ind,g2an_hc))return(con_al);
if(bitvalue(ind,g2an_lc))return(con_ba);
return(mis_norm) ;
}

