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
        la function tabper attiva i tabulati periodici
        leggendone le caratteristiche dal file fdiztab

        ha una periodicita` di 30 minuti
*/
#include <osf1.h>
#include <dos.h>

#include "fileop.inc"
#include "tabulati.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "taskwd.inc"

// External function declarations
extern int SimTabper(void);
extern void wai(int);
extern void waisim(int);
extern void lantab(int);

void tabper()
{
short itime ;
unsigned short attesa;
int mese_prec ;                  /* salvo il mese            */
int minuti, ora,	mese_att;
S_DIZTAB *pdiz;					  /* punta a record file dizionario */
int  bis ;                      /* flag per tabulato bisett. */
short gsett;      	           /* giorno della settimana    */

bis=0 ;                         /* inizializzo flag bisettimanale */

for(;;)
	{
#if defined ENEL_SIM
	/*
		attende che la simulazione sia in RUN
	*/
	while(!SimTabper())
		wai(10);
#endif
	mese_prec=dbadv[db_mese];
/*
        calcolo il tempo di attesa per la mezz'ora
*/
	itime=1800-(short) dbadv[db_secondi]-((short)dbadv[db_minuti]*60); /* sec. manc. */
	if(itime<=0) itime=itime+1800 ;	

	attesa=itime*18+itime/5+19;

#if defined ENEL_SIM
	waisim(attesa);	  // attende la mezz'ora
#else
	wai(attesa);	  // attende la mezz'ora
#endif
						  // verifico
   wd[wd_tabul].cont=wd_max_tabul;
/*
        lancio tabulati a 30 min
                        a 60 min se min e' inferiore a 30
*/
   lantab(1) ;
/*
        chiedo il nuovo tempo
*/
	gsett=dbadv[db_gioset];
	if(dbadv[db_minuti] >= 30.0) continue ;	// se � alla mezzora torna all'inizio
															// del ciclo
	lantab(2) ;		  // lancia i tabulati relativi all'ora
/*
        verifico il lancio dei tabulati a 4 e 8 ore
*/
	ora=(short) dbadv[db_ora];
	if(ora % 4) continue ;
	lantab(3) ;
	if(ora % 8) continue ;
	lantab(4) ;
/*
        se l`ora e` 0 lancio tabulato a 1 giorno
        se il giono della settimana e' 1 lancio il tabulato
        settimanale ed eventualmente quello bisettimanale
*/
	if(ora) continue ;
	lantab(5) ;
	if(gsett == 1)                     /* se e' il primo giorno    */
		{                               /* della settimana           */
      lantab(6) ;
      bis=!bis ;
      if(bis) lantab(7) ;
  		}
/*
        se e' variato anche il mese lancio i tabulati mensili
        e verifico quelli a 3 mesi 6 mesi 1 anno
*/
	mese_att=dbadv[db_mese];
	if(mese_att == mese_prec) continue ;
		lantab(8) ;

	switch (mese_att-1)
		{
		case 0:                 /*      tabulato annuale         */
        lantab(11) ;
		case 6:                 /*       tabulato semestrale    */
        lantab(10) ;
		case 3:
		case 9 :                /*      tabulato trimestrale    */
        lantab(9) ;
		}
	}
}


