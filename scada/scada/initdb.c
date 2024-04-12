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
/*  1
        la routine initdb inizializza il data base

        11 Gennaio 1993

        Modifica inizializzazione data base digitale per salvataggio
        trattamento e severita'
*/

#include <stdio.h>

#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "g2ptrdb.inc" 
#include "comunic.inc"
#include "dconf.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "switch.inc"


#if defined (STAR_SDI)
   #include "diaginet.inc"
#endif
#if defined (STAR_SEPA)
   #include "sepdiag.inc"
#endif

extern DB_HEADER h_db;

initdb()
{
short i, ier;
short mask, maskal,bit,j ;

/*
        inizializzazione del data base :
        - salvare i flag di FZ e FS
        - per gli analogici se il punto e` FZ occorre salvare anche
          i flag di allarme
        - i valori degli analogici non vengono variati
        - inizializzazione del data base logico digitale a 0
        - stato organi =0 timer=0
*/

mask=0 ;
bitset(&mask,g2an_fs,1) ;
bitset(&mask,g2an_fz,1) ;
maskal=mask ;
bitset(&maskal,g2an_ls,1) ;
bitset(&maskal,g2an_lc,1) ;
bitset(&maskal,g2an_hs,1) ;
bitset(&maskal,g2an_hc,1) ;
for(i=0;i<h_db.dimaa;i++){
								dbaafa[i]=0;           /* an. acq.   */
                        if(dbaaf[i] & mask)
                                dbaaf[i]=dbaaf[i] & maskal ;
                        else dbaaf[i] = 0 ;
                       }
for(i=0;i<h_db.dimas;i++){                             /* an. calc.  */
                  if(dbasf[i] & mask)
                          dbasf[i]=dbasf[i] & maskal ;
                  else dbasf[i] = 0 ;
                 }
for(i=0;i<h_db.dimac;i++){                            /* an. calc.nst */
                  if(dbacf[i] & mask)
                          dbacf[i]=dbacf[i] & maskal ;
                  else dbacf[i] = 0 ;
                 }
if(dbadv[db_anno]==0.0) dbadv[db_anno]=1980;			   //	impostazione anno
dbadv[db_secondi]=0.0;	  	                        //	reset secondi

dbadv[num_vdummi]=num_video;

if(getenv("RESETLBG") != NULL)
{
   dbadv[db_fileal]=0.0;			//	reset n. file allarmi in uso
   for(i=db_falco1;i<=db_falco8;i++)
   {
		dbadv[i]=0.0;	dbadf[i]=0;
   }
}

/* salvo tipo di trattamento  e livello di severita' */

mask=M_TRSED;
bitset(&mask,g2di_fs,1) ;
bitset(&mask,g2di_fz,1) ;
maskal=mask ;
bitset(&maskal,g2di_sl,1) ;      /* salvo lo stato */
for(i=0;i<h_db.dimda;i++){                 /* dig. acquisiti */
                        if((dbda[i] & mask) !=
                           (dbda[i] & M_TRSED))
                                dbda[i]=dbda[i] & maskal ;
                        else    dbda[i]=dbda[i] & M_TRSED ;
                      }
for(i=0;i<h_db.dimds;i++){                 /* dig. calcolati */
                        if((dbds[i] & mask) !=
                           (dbds[i] & M_TRSED))
                                dbds[i]=dbds[i] & maskal ;
                        else    dbds[i]=dbds[i] & M_TRSED ;
                      }
for(i=0;i<h_db.dimdc;i++){                 /* dig. calcolati non stand. */
                        if((dbdc[i] & mask) !=
                           (dbdc[i] & M_TRSED))
                                dbdc[i]=dbdc[i] & maskal ;
                        else    dbdc[i]=dbdc[i] & M_TRSED ;
                      }
/*
	devo salvare lo stato dei digitali di archivio
*/
for(i=0;i<h_db.dimdd;i++)
{ 
   switch(i)
   {
	case arc_st01:				// salvo lo stato dei digitali di archivio
	case arc_st02:
	case arc_st03:
	case arc_st04:
	case arc_st05:
	case arc_st06:
	case arc_st07:
	case arc_st08:
	break;

   case stosta1:				// gestione start stop pas
   case stosta2:
   case runfre1:
   case runfre2:
/*
   reset bit FA e RI
*/
       bitset(&dbdd[i],g2di_fa,0);
       bitset(&dbdd[i],g2di_ri,0);
       if(bitvalue(&dbdd[i],g2di_fz)) break;
       dbdd[i]=(dbdd[i] & M_TRSED) ;
   break;
#if defined (AC_INETDUALE)
/*
   il punto congrete viene utilizzato nel suo flag FZ per
   indicare se il sistema si e' precedentemente fermato (non avendo
   la possibilita' di comunicare su nessuna rete) per consentire allo
   slave di verificare il funzionamento delle reti 
*/
   case congrete:
      bitset(&dbdd[i],g2di_sl,0);
   break;
#endif
   default:
       dbdd[i]=(dbdd[i] & M_TRSED) ;
   break;
   }
}		 

/*
	setto off_line i digitali di diagnostica associati alla comunicazione
	con nodi tcp/ip
*/
bitset(&dbdd[config],g2di_sl,1);

#if defined (MMI_PC)
for(i=stvide2;i<=stvide9;i++) bitset(&dbdd[i],g2di_sl,1);
#else
for(i=stvide1;i<=stvide9;i++) bitset(&dbdd[i],g2di_sl,1);
#endif
bitset(&dbdd[sthard],g2di_sl,1);

if(!HCPY)
   bitset(&dbdd[sthard],g2di_fs,1);

if(SYS_DUALE)
   bitset(&dbdd[sys_d],g2di_sl,1);

bitset(&dbdd[stnod01],g2di_sl,1);
bitset(&dbdd[stnod02],g2di_sl,1);
bitset(&dbdd[stnod03],g2di_sl,1);
bitset(&dbdd[stnod04],g2di_sl,1);

mask=0 ;
bitset(&mask,g2or_fs,1) ;
bitset(&mask,g2or_fz,1) ;

   for(i=0;i<h_db.dimor;i++)
   {
	   dbto[i]=0 ;
	   dboft[i]=0 ;
      dbosp[i]=0 ;
      if(dbosc[i] & mask)
             dbosc[i]=dbosc[i] &
                           (mask | 0x00FF) ;
      else dbosc[i]=0 ;
   }
}
