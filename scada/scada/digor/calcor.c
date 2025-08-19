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
#include <osf1.h>
#include <stdio.h>
/*-> calcor

	la function calcor permette di determinare
	lo stato di un organo dato i valori dei
	contribuenti digitali

	punt short puntatore in data base dell'
		   organo da calcolare

*/
#include "dconf.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"

/* Function prototypes */
extern int bitvalue(short *, short);
extern void bitset(short *, short, short);
extern void inibiz(short, short, short, short);

extern DB_HEADER h_db;

void calcor(punt)
short punt ;
{
struct punto_inibito *inib ;
S_DESORG  *org ;	/* descrittore dell'organo */
short i, j ;
char val ;		/* valore contribuente	     */
char flagc;		/* flag contribuenti fa o fs */
char stato ;		/* stato organo		     */
char flago ;		/* flag organo	fa           */

if(punt<0 || punt>=h_db.dimor) {visch('O'); return;}
/*
	l'organo non viene calcolato se e' forzato o
	fuori scansione
*/
if(bitvalue(&dbosc[punt],g2or_fz) || bitvalue(&dbosc[punt],
			      g2or_fs)) return ;

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
		   return ; }
        stato=stato +(val<<i) ;
}
FINE :
/*
	l'organo e'attendibile setto il flag FA ed inserisco
	il timer
	lo stato attuale dell'organo si determina dalla tabella
	torg che contiene gli stati per tipo di organo
*/
bitset(&dbosc[punt],g2or_fa,0) ;
dbosc[punt]=(dbosc[punt] & 0xFF00) +
		  storg[org->tipo].vet_stati[stato] ;
/*
	verifico se l'organo e' inibente ed e' la sua prima transizione
*/
if(org->stinib != -1 && !(dboft[punt] & mask_it))
{
/*
	se lo stato attuale e' non inibente rientro
	di tutti gli allarmi altrimenti rientro dei non inibiti
*/
	if(dbosp[punt] == org->stinib ) stato=3 ;
	else stato=5 ;

	inib= &org->pinib[0] ;
	for(i=0;i<or_inib;i++,inib++)
	{
		if(inib->ext == -1) break;
		inibiz(inib->ext,inib->punt,inib->tipin,stato) ;
	}
}
		
/*
	setto il bit di variazione spontanea
	ed inserisco il time-out
*/
dboft[punt]=dboft[punt] | mask_it ;
if(!dbto[punt]) dbto[punt]=org->time_out ;
return ;
}
