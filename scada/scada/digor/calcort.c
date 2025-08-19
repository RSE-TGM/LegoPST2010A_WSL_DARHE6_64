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
/*-> calcort

   La funzione calcort esamina la variazione di organi aventi
   come contribuenti digitali acquisiti da linee telefonica

   Parametri

   punt short      puntatore in data base dell'organo da calcolare
   time *MISTIME   ora posto periferico

   Ritorno

   nessuno

   3 Dicembre 1992      Fc.

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"
#include "organi.inc"
#include "dconf.inc"

extern	DB_HEADER h_db;

/* Function prototypes */
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

int calcort(punt,time)
short punt ;
MISTIME *time;
{
struct punto_inibito *inib ;
S_DESORG  *org ;	/* descrittore dell'organo */
short i, j ;
char val ;		/* valore contribuente	     */
char flagc;		/* flag contribuenti fa o fs */
char stato ;		/* stato organo attuale   */
char statop;		/* stato organo precedente*/
char flago ;		/* flag organo	fa         */
QUEUE_PACKET pack;
S_MALLAT mess;

if(punt<0 || punt>=h_db.dimor)
   {
   //_visch('O'); 
   return(0);
   }
/*
	l'organo non viene calcolato se e' forzato o
	fuori scansione
*/
if(bitvalue(&dbosc[punt],g2or_fz) || bitvalue(&dbosc[punt],
			      g2or_fs)) return(0) ;
org=&dbode[punt] ;
/*
	ciclo per il calcolo dello stato attuale
*/
stato=0 ;		/* inizializzazione */
for(i=0;i<or_cont;i++)
{
	switch(org->ext[i])
	{
	case g1tipda:
	     val=bitvalue(&dbda[org->punt[i]],g2di_sl) ;
	     flagc=bitvalue(&dbda[org->punt[i]],g2di_fa) ||
	           bitvalue(&dbda[org->punt[i]],g2di_fs)  ;
	     break ;
	case g1tipds:
	     val=bitvalue(&dbds[org->punt[i]],g2di_sl) ;
	     flagc=bitvalue(&dbds[org->punt[i]],g2di_fa) ||
	           bitvalue(&dbds[org->punt[i]],g2di_fs)  ;
	     break ;
	case g1tipdc:
	     val=bitvalue(&dbdc[org->punt[i]],g2di_sl) ;
	     flagc=bitvalue(&dbdc[org->punt[i]],g2di_fa) ||
	           bitvalue(&dbdc[org->punt[i]],g2di_fs)  ;
	     break ;
	case g1tipdd:
	     val=bitvalue(&dbdd[org->punt[i]],g2di_sl) ;
	     flagc=bitvalue(&dbdd[org->punt[i]],g2di_fa) ||
	           bitvalue(&dbdd[org->punt[i]],g2di_fs)  ;
	     break ;
	default:	goto FINE ;
	}
/*
	se uno dei contribuenti e' fuori scansione o fuori
	attendibilita' l'organo viene messo fuori attendibilita'
	e lo stato non viene calcolato
*/
	if(flagc) {bitset(&dbosc[punt],g2or_fa,1);
		   return(0) ; }
        stato=stato +(val<<i) ;
}
FINE :
/*
	l'organo e'attendibile setto il flag FA
	lo stato attuale dell'organo si determina dalla tabella
	torg che contiene gli stati per tipo di organo
*/
bitset(&dbosc[punt],g2or_fa,0) ;
stato=storg[org->tipo].vet_stati[stato] ;
dbosc[punt]=(dbosc[punt] & 0xFF00) + stato;
/*
	se e' settato il bit di timer su	comando e se lo stato nuovo 
   dell'organo coincide	con lo stato atteso pongo il timer a 1	
   per inviare	immediatamente l'allarme di comando eseguito (vedi Timeor)
*/
if( ((dboft[punt] & mask_tc) == mask_tc) && (stato==dbosa[punt]))
{
   dbto[punt]=1;
   return(0);
}
/*
   se lo stato e' incongruente o transizione carico timer
*/
if(stato==st_incon || stato==st_trans)  
{
   dboft[punt]=dboft[punt] | mask_it ;
	if(!dbto[punt]) dbto[punt]=org->time_out ;
}
else          
{
/*
   verifico se si e' avuta una variazione rispetto allo stato
   precedente, segnalo allarme variazione spontanea ed annullo
   timer eventualmente caricato
*/
   statop=dbosp[punt];
   if(stato != statop && statop)       // variato e non primo calcolo ?
   {
      pack.que = c_visall;
      pack.flg = MSG_WAIT;
      pack.wto = 0;
      pack.amsg = (char *)  &mess;
      pack.lmsg=sizeof(S_MALLAT);
      mess.m.ext=g1tipor;
      mess.m.punt=punt;
      mess.m.ertr=(org->trat | 0x80) ;
		mess.m.sogl1=stato; mess.m.sogl2=statop;
		mess.m.sprec=mis_norm; mess.m.satt=var_org;
      mess.t=*time;
   	dbto[punt]=0;
      dbosp[punt]=stato ;
      enqueue(&pack);
   }
}
return(0);
}
