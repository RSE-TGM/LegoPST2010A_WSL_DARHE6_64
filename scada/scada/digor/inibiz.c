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
/*
        la function inibiz.c esegue le inibizioni
        sui vari tipi di punti
        per gli organi
        -       inserisce lo stato protetto nello
                stato atteso e setta il flag di
                variazione su protezione

        ext char input tipo di punto su cui eseguire
                       l'inibizione
        punt short input puntatore in db del punto
        tipo char input tipo di inibizione da applicare
                        ( ha senso solo per gli analogici )
        stato input short o int tipo di inibizione da eseguire

        11 Gennaio 1993
        Inserimento trattamento - severita'

        01 Marzo 1995
        Inserito test per emissione allarmi analogici senza soglia
        definita
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"

inibiz(ext,punt,tipo,stato)
short stato ;
char ext ;
short punt ;
char tipo ;
{
QUEUE_PACKET pack;
S_DESORG *des ;
short  trat ;
short *dbs ;
short flag ;
S_MALLA mess ;
S_DBALL *all;

pack.que = c_visall;
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &mess;
pack.lmsg=sizeof(S_MALLA);
/*
	inizializzo il pacchetto malla
*/
mess.ext=ext ;
mess.punt=punt;
/*
        esamino il tipo di punto da inibire
*/
switch(ext)
{
/*
        protezione di un organo
        setto lo stato atteso il time out e il flag ta
*/
case g1tipor :
        if(!stato) return ;
        des=&dbode[punt] ;
        dbosa[punt]=des->stprot ;
        dbto[punt]=des->time_out ;
	  	  dboft[punt]=dboft[punt] | mask_ta ;
        return;
case g1tipda :          /* digitali acquisiti   */
        dbs=&dbda[punt] ;
        goto DIGITALI ;
case g1tipds :          /* digitali calcolati standard */
        dbs=&dbds[punt] ;
        goto DIGITALI ;
case g1tipdc :          /* digitali calcolati  non standard */
        dbs=&dbdc[punt] ;
        goto DIGITALI ;
case g1tipdd :          /* digitali di diagnostica      */
        dbs=&dbdd[punt] ;
        goto DIGITALI  ;
case g1tipaa:           /* analogici acquisiti          */
        dbs=&dbaaf[punt] ;
        all=&dbaaal[punt];
        goto ANALOGICI ;
case g1tipas:           /* analogici calcolati stan.    */
        dbs=&dbasf[punt] ;
        all=&dbasal[punt];
        goto ANALOGICI ;
case g1tipac:           /* analogici calc. non stan.    */
        dbs=&dbacf[punt] ;
        all=&dbacal[punt];
        goto ANALOGICI ;
case g1tipad:           /* analogici diagnostica        */
        dbs=&dbadf[punt] ;
        all=&dbadal[punt];
        goto ANALOGICI ;
default :
        return ;
}
DIGITALI :
/*
        se lo stato dell'inibente e' uno
        - setto il bit in nel dbda
        - rientro digitali in allarme
*/
trat= (*dbs) & M_TRSED ;         /* trattamento + liv sev */
if(stato==1 || stato==5)
{
        bitset(dbs,g2di_in,1) ;
        if(bitvalue(dbs,g2di_sl))
        {
        if(ext==g1tipdd)
	{      
		mess.ertr=trat;	mess.sprec=dia_sys; mess.satt=mis_norm;
		mess.sogl1=0; mess.sogl2=0 ;
		enqueue(&pack);
	}			
        else       
	{      
		mess.ertr=trat;	mess.sprec=var_dig; mess.satt=mis_norm;
		mess.sogl1=0; mess.sogl2=0 ;
		enqueue(&pack);
	}			
        }
}       
/*
        stato inibente = 0
        - reset del bit
        - emissione allarmi
*/
if(! stato || stato == 4)
{
        bitset(dbs,g2di_in,0) ;
        if(bitvalue(dbs,g2di_sl))
        {
        if(ext==g1tipdd)
	{      
		mess.ertr=trat+0x80;	mess.satt=dia_sys; mess.sprec=mis_norm;
		mess.sogl1=1; mess.sogl2=0 ;
		enqueue(&pack);
	}			
        else 
	{      
		mess.ertr=trat+0x80;	mess.satt=var_dig; mess.sprec=mis_norm;
		mess.sogl1=1; mess.sogl2=0 ;
		enqueue(&pack);
	}			
        }
}
return ;

ANALOGICI :

trat=all->tr_bdm ;
trat=( (trat & M_LSEVA) >> 6 ) + (trat >> 12);  
switch(stato)
{
case 4 :                /* emissione di tutti gli allarmi */
        if(bitvalue(dbs,g2an_hs))
			{      
			mess.ertr=trat+0x80; 
			mess.sprec=mis_norm; mess.satt=sic_al;
         if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
         else	mess.sogl1=0;
         mess.sogl2=0 ;
			enqueue(&pack);
			}			
        if(bitvalue(dbs,g2an_ls)) 
			{      
				mess.ertr=trat+0x80;
				mess.sprec=mis_norm; mess.satt=sic_ba;
            if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
				else mess.sogl1=1;
            mess.sogl2=0 ;
				enqueue(&pack);
			}			
        if(bitvalue(dbs,g2an_hc)) 
			{      
				mess.ertr=trat+0x80;
				mess.sprec=mis_norm; mess.satt=con_al;
            if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
            else	mess.sogl1=2;
            mess.sogl2=0 ;
				enqueue(&pack);
			}			
        if(bitvalue(dbs,g2an_lc)) 
			{      
				mess.ertr=trat+0x80;
				mess.sprec=mis_norm; mess.satt=con_ba;
            if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
            else	mess.sogl1=3;
            mess.sogl2=0 ;
				enqueue(&pack);
			}			
        flag=0 ;                /* rientro inibizioni   */
        break;
case 5 :                /* rientro   di tutti gli allarmi */
        if(bitvalue(dbs,g2an_hs)) 
	{      
		mess.ertr=trat;
		mess.satt=mis_norm; mess.sprec=sic_al;
      if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
		else mess.sogl1=0;
      mess.sogl2=0 ;
		enqueue(&pack);
	}			
        if(bitvalue(dbs,g2an_ls))
	{      
		mess.ertr=trat;
		mess.satt=mis_norm; mess.sprec=sic_ba;
      if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
		else mess.sogl1=1;
      mess.sogl2=0 ;
		enqueue(&pack);
	}			
        if(bitvalue(dbs,g2an_hc)) 
	{      
		mess.ertr=trat;
		mess.satt=mis_norm; mess.sprec=con_al;
      if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
		else mess.sogl1=2;
      mess.sogl2=0 ;
		enqueue(&pack);
	}			
        if(bitvalue(dbs,g2an_lc)) 
	{      
		mess.ertr=trat;
		mess.satt=mis_norm; mess.sprec=con_ba;
      if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
		else mess.sogl1=3;
      mess.sogl2=0 ;
		enqueue(&pack);
	}			
        flag=1 ;                /* inserimento inibizioni */
        break;
case 2 :                /* emissione di allarmi non inibiti */
        if(!bitvalue(dbs,g2an_dh))
        {
                if(bitvalue(dbs,g2an_hs)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=sic_al;
         if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=0;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_hc))
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=con_al;
         if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=2;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        if(!bitvalue(dbs,g2an_dl))      /* all. bassi non inibiti */
        {
                if(bitvalue(dbs,g2an_ls)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=sic_ba;
         if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=1;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_lc)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=con_ba;
         if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=3;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        flag=1 ;                /* rientro inibizione   */
        break;
case 3 :                /* rientro allarmi non inibiti    */
        if(!bitvalue(dbs,g2an_dh))
        {
                if(bitvalue(dbs,g2an_hs)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=sic_al;
         if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=0;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_hc)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=con_al;
         if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=2;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        if(!bitvalue(dbs,g2an_dl))      /* all. bassi non inibiti */
        {
                if(bitvalue(dbs,g2an_ls)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=sic_ba;
         if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=1;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_lc))
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=con_ba;
         if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=3;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        flag=1 ;                /* attivo inibizioni    */
        break ;
case 0 :                /* emissione di allarmi     inibiti */
        if( !tipo || tipo == g2in_al)
        {
                if(bitvalue(dbs,g2an_hs))
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=sic_al;
         if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=0;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_hc)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=con_al;
         if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=2;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        if( !tipo || tipo == g2in_ba)  /* all. bassi inibiti */
        {
                if(bitvalue(dbs,g2an_ls)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=sic_ba;
         if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=1;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_lc)) 
		{      
			mess.ertr=trat+0x80;
			mess.sprec=mis_norm; mess.satt=con_ba;
         if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=3;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        flag=0 ;                /* rientro inibizione   */
        break;
case 1 :                /* rientro allarmi inibiti    */
        if( !tipo || tipo == g2in_al)
        {
                if(bitvalue(dbs,g2an_hs))
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=sic_al;
         if(all->alto_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=0;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_hc)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=con_al;
         if(all->alto_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=2;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        if( !tipo || tipo == g2in_ba)           /* all. bassi inibiti */
        {
                if(bitvalue(dbs,g2an_ls)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=sic_ba;
         if(all->bass_sic.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=1;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
                if(bitvalue(dbs,g2an_lc)) 
		{      
			mess.ertr=trat;
			mess.satt=mis_norm; mess.sprec=con_ba;
         if(all->bass_con.cval[0]==-2) mess.sogl1=-1;
			else mess.sogl1=3;
         mess.sogl2=0 ;
			enqueue(&pack);
		}			
        }
        flag=1 ;                /* attivo inibizioni    */
        break ;
}
if(!tipo || tipo == g2in_al) bitset(dbs,g2an_dh,flag) ;
if(!tipo || tipo == g2in_ba) bitset(dbs,g2an_dl,flag) ;
return ;
}

