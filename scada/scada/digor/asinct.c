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
/*->asinct

	il task tratg esamina i messaggi provenienti
	dall`acquisizione digitale

   20 Gennaio 1992   Rel. 1.01   Fc
      Corretta gestione messaggio mcadi: ricalcolo digitali
      anche se non varia lo stato o la FA devono essere ricalcolati
      gli organi e le calcolate associate al punto
   
   11 Gennaio 1993
      Gestione trattamento - severita'
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include	"mesqueue.h"

/* Function prototypes */
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);
extern void calcdi(short);
extern void calcor(short);
extern void inibiz(short, short, short, short);
extern void calcau(short);
extern void calcort(short, void *);
extern void calcdit(short, void *);

int asinct()
{

S_CALIN *dig ;		      /* puntatore alla tabella CALIN       */
short *dbtr, mbox ;		/* puntatore alla tabella trattamento */
char *p1 ;
short i, ier, xbuf, stato ;
S_DESORG *des ;
struct punto_inibito *inib ;
short *dbs;
short calcolare,inibire;
/*
	definizione messaggio da scodare
*/

S_TRATG  mtrat ;
S_MALLA  mess ;

S_MALLAT messt;
S_TRATGT mtratt;
QUEUE_PACKET spackt;
short tele=0;

QUEUE_PACKET spack;
QUEUE_PACKET queue,queues;

queue.que=c_digor;
queue.flg=MSG_WAIT;
queue.wto=0;


   queue.amsg=(char *)&mtratt;       // messaggio piu' grande
   spackt.que=c_visall;
   spackt.flg=MSG_WAIT;
   spackt.wto=0;
   spackt.amsg=(char *)&messt;
   spackt.lmsg=sizeof(S_MALLAT);

//   queue.amsg=(char *)&mtrat;

spack.que=c_visall;
spack.flg=MSG_WAIT;
spack.wto=0;
spack.amsg=(char *)&mess;
spack.lmsg=sizeof(S_MALLA);

queues.que=c_digor;
queues.flg=MSG_NOWAIT;
queues.wto=0;
queues.amsg=(char *)&mtrat;
queues.lmsg=sizeof(S_TRATG);


/*
	verifico se ci sono dei messaggi
	se non ce ne sono mi sospendo
*/
INIZIO :

dequeue(&queue);
tele=0;
mtrat=mtratt.m;                  // ricopio messaggio parte comune
/*
	scodo il messaggio
*/
mess.ext= mtrat.ext ;            /* preparo tipo punto */
mess.punt= mtrat.indice ;         /* preparo l'indice punto */
switch (mtrat.mess)
{
case mcadi : /* ricalcolare il valore del digitale       */
         	 /* puo' essere fatto solo in caso di 	    */
             /* digitali acquisiti calcolati standard o di diagnostica */
             /* se il nuovo stato e' diverso viene accodato un messaggio di */
             /* variazione per l'emissione dell'allarme  */

	switch (mtrat.ext)
	{
	case g1tipds :		/* calcolato standard		*/
		calcdi(mtrat.indice) ;
		break;
	case g1tipda :         /*	acquisito		*/
		mtrat.stato= bitvalue(&dbda[mtrat.indice],g2di_asl); 
		if(mtrat.stato != bitvalue(&dbda[mtrat.indice],g2di_sl))
		  { 
		   bitset(&dbda[mtrat.indice],g2di_sl,mtrat.stato);
	      mtrat.mess= macdi ;
   	   enqueue(&queues) ;
		  }
		mtrat.stato= bitvalue(&dbda[mtrat.indice],g2di_afa); 
		if(mtrat.stato != bitvalue(&dbda[mtrat.indice],g2di_fa))
		  { 
		   bitset(&dbda[mtrat.indice],g2di_fa,mtrat.stato);
	      mtrat.mess= mfadi ;
   	   enqueue(&queues) ;
		  }
		break;
	case g1tipdd :  	/* 	digitale di diagnostica  */
      mtrat.mess= macdd ;
		mtrat.stato= bitvalue(&dbdd[mtrat.indice],g2di_asl) ;
		if(mtrat.stato != bitvalue(&dbdd[mtrat.indice],g2di_sl))
	     {
        enqueue(&queues) ;  
		  bitset(&dbdd[mtrat.indice],g2di_sl,mtrat.stato) ;
		}
		break;
	}
/*
   anche se lo stato o la fuori attendibilita' non e' variata
   occorre richiedere il trattamento delle calcolate e degli
   organi perche' il punto puo' essere stato messo fouri scan-
   sione (deve rientrare la FA del calcolato e dell'organo)
*/
   mtrat.mess= mtrdi ;
   enqueue(&queues) ;

	goto INIZIO ;
case mcaor :		/* ricalcolare il valore dell`organo variato */
	calcor(mtrat.indice) ;
	goto INIZIO ;

case mtrdit:
   tele=1;        // flag messaggio telefonico

case mtrdi :		/* verificare inibizioni e calcolate a cui il */
			/* digitale contribuisce (variato flag o val. */
	switch(mtrat.ext)
	{
	case g1tipda :
		dbtr= &dbdatr[mtrat.indice] ;
		dig= &dbdaco[mtrat.indice] ;
		stato=bitvalue(&dbda[mtrat.indice],g2di_sl) ;
		break ;
	case g1tipds :
		dbtr= &dbdstr[mtrat.indice] ;
		dig= &dbdsco[mtrat.indice] ;
		stato=bitvalue(&dbds[mtrat.indice],g2di_sl) ;
		break ;
	case g1tipdc :
		dbtr= &dbdctr[mtrat.indice] ;
		dig= &dbdcco[mtrat.indice] ;
		stato=bitvalue(&dbdc[mtrat.indice],g2di_sl) ;
		break ;
	case g1tipdd :
		dbtr= &dbddtr[mtrat.indice] ;
		dig= &dbddco[mtrat.indice] ;
		stato=bitvalue(&dbdd[mtrat.indice],g2di_sl) ;
		break ;
	}
	inibire=0; calcolare=1;
	goto TRATT ;
case mtror:			 /* un organo e' stato forzato occorre verificare se */
						 /* inibisce													  */
	des=&dbode[mtrat.indice] ;
	if(des->stinib == -1) goto INIZIO ;	/*	non inibente					  */
	if(des->stinib==mtrat.stato) stato=1 ;
	else 								  stato=0 ;
	inib=&des->pinib[0] ;
	for(i=0;i<or_inib;i++,inib++)
	{
			if(inib->ext==-1) break;
			inibiz(inib->ext,inib->punt,inib->tipin,stato) ;
	}
	goto INIZIO ;	

case macdit:
   tele=1;        // flag messaggio telefonico

case macdi :		/* variazione digitale per acquisiti  */
			/* calcolati standard e non standard  */
/*
	accodo l`allarme al task call
	e verifico le inibizioni e le calcolate a cui il punto
	contribuisce
*/
	switch(mtrat.ext)
	{
	case g1tipda :
		mess.ertr=dbda[mtrat.indice] & M_TRSED ;
		dbs= &dbda[mtrat.indice];
		dbtr= &dbdatr[mtrat.indice] ;
		dig= &dbdaco[mtrat.indice] ;
		break;
	case g1tipds :
		mess.ertr=dbds[mtrat.indice] & M_TRSED ;
		dbs= &dbds[mtrat.indice];
		dbtr= &dbdstr[mtrat.indice] ;
		dig= &dbdsco[mtrat.indice] ;
		break;
	case g1tipdc :
		mess.ertr=dbdc[mtrat.indice] & M_TRSED ;
		dbs= &dbdc[mtrat.indice];
		dbtr= &dbdctr[mtrat.indice] ;
		dig= &dbdcco[mtrat.indice] ;
		break;
	}
/*
	se il digitale e' inibito non emetto nessun allarme
*/
	calcolare=1; 	inibire=1;
	if(bitvalue(dbs,g2di_in)) goto TRATT;	
	if(mtrat.stato) {mess.ertr=mess.ertr | 0x80 ;
		mess.sprec=mis_norm; mess.satt=var_dig ; }
	else  { mess.sprec=var_dig ; mess.satt=mis_norm; }
   mess.sogl1= mtrat.stato ;
   mess.sogl2= 0 ;

   if(tele)             // se da linea telefonica
   {
      messt.m=mess;     // ricopio messaggio in mallat
      messt.t=mtratt.t;  // inserisco tempo ricevuto
      enqueue(&spackt);

   }
   else
   	enqueue(&spack);

	stato=mtrat.stato ;
	goto TRATT ;

case mfadit:
   tele=1;        // flag messaggio telefonico

case mfadi :		/* variazione digitale flag fuori attendibilta' */
/*
	accodo l`allarme al task call
	e verifico le inibizioni e le calcolate a cui il punto
	contribuisce
*/
	switch(mtrat.ext)
	{
	case g1tipda :
		mess.ertr=dbda[mtrat.indice] & M_TRSED ;
		dbs= &dbda[mtrat.indice];
		dbtr= &dbdatr[mtrat.indice] ;
		dig= &dbdaco[mtrat.indice] ;
		break;
	case g1tipds :
		mess.ertr=dbds[mtrat.indice] & M_TRSED ;
		dbs= &dbds[mtrat.indice];
		dbtr= &dbdstr[mtrat.indice] ;
		dig= &dbdsco[mtrat.indice] ;
		break;
	case g1tipdc :
		mess.ertr=dbdc[mtrat.indice] & M_TRSED ;
		dbs= &dbdc[mtrat.indice];
		dbtr= &dbdctr[mtrat.indice] ;
		dig= &dbdcco[mtrat.indice] ;
		break;
	case g1tipdd :
		mess.ertr=dbdd[mtrat.indice] & M_TRSED ;
		dbs= &dbdd[mtrat.indice];
		dbtr= &dbddtr[mtrat.indice] ;
		dig= &dbddco[mtrat.indice] ;
		break;
	}
/*
	se il digitale e' inibito non emetto nessun allarme
*/
	calcolare=1; 	
	if(mtrat.stato) {mess.ertr=mess.ertr | 0x80 ;
		mess.sprec=mis_norm; mess.satt=non_att ; }
	else  { mess.sprec=non_att ; mess.satt=mis_norm; }
   mess.sogl1= -1;
   mess.sogl2=-1 ;
   if(tele)             // se da linea telefonica
   {
      messt.m=mess;     // ricopio messaggio in mallat
      messt.t=mtratt.t;  // inserisco tempo ricevuto
      enqueue(&spackt);
   }
   else
   	enqueue(&spack);
	stato=mtrat.stato ;
	goto TRATT ;

case macdd :		/* variazione digitale di diagnostica */
/*
	accodo l`allarme al task call
	e verifico inibizioni e calcolate a cui il punto
	contribuisce
*/
	dbtr= &dbddtr[mtrat.indice] ;
	dig= &dbddco[mtrat.indice] ;
	stato=mtrat.stato ;
	calcolare=1; 	inibire=1;
	if(bitvalue(&dbdd[mtrat.indice],g2di_in)) goto TRATT ;
	mess.ertr=dbdd[mtrat.indice] & M_TRSED ;
	if(mtrat.stato) {mess.ertr=mess.ertr | 0x80 ;
			 mess.sprec=mis_norm; mess.satt=dia_sys ; }
	else  { mess.sprec=dia_sys ; mess.satt=mis_norm; }
   mess.sogl1= mtrat.stato ;
   mess.sogl2= 0 ;
	enqueue(&spack);
	goto TRATT ;

case macst :		/* variazione valore stringa  */
/*
	accodo l`allarme al task call	in base al tipo di trattamento
*/
	mess.ertr=dbsttr[mtrat.indice] | 0x80 ;
	mess.sprec=mis_norm; mess.satt=mod_st ; 
   mess.sogl1= -1;
   mess.sogl2= -1 ;
	enqueue(&spack) ;
	goto INIZIO;

case maudi :            // gestione bit AU
   switch(mtrat.ext)
	{
	case g1tipda :
		dig= &dbdaco[mtrat.indice] ;
		break ;
	case g1tipds :
		dig= &dbdsco[mtrat.indice] ;
		break ;
	case g1tipdc :
		dig= &dbdcco[mtrat.indice] ;
		break ;
	case g1tipdd :
		dig= &dbddco[mtrat.indice] ;
		break ;
	}
	for(i=0;i<di_cont;i++)
		if(dig->tipo_cont[i]==g1tipds) calcau(dig->cont[i]);
   goto  INIZIO;

}
goto INIZIO ;

TRATT :		/* solo per digitali	*/
/*
	se e' settato il bit ic contribuisce a calcoli
	vado a calcolare organi e digitali a cui
	contribuisce
*/

if(bitvalue(dbtr,g2di_ic) && calcolare)
{
	for(i=0;i<di_cont;i++)
	{
		switch(dig->tipo_cont[i])
		{
		case g1tipor:
           if(tele) calcort(dig->cont[i],&mtratt.t);
           else
   		     calcor(dig->cont[i]) ;
		     break ;
		case g1tipds :
           if(tele) calcdit(dig->cont[i],&mtratt.t) ;
           else
	   	     calcdi(dig->cont[i]) ;
		     break ;
		default :
		     goto FINE ;
		}
	}
}
FINE :
/*
	verifico se e' stato settato il bit di inibizioni
*/
if(bitvalue(dbtr,g2di_io) && inibire)
{
	for(i=0;i<di_inib;i++)
	{
		switch(dig->tipo_inib[i])
		{
		case -1:
			break ;
		default :
		   inibiz(dig->tipo_inib[i],dig->inib[i],dig->tin_an,stato) ;
		}
	}
}
goto INIZIO ;
return 0;  /* Never reached */
}

