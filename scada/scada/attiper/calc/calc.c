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
/********************************************************************
	Modulo:  CALC.C

        Main del processo calcolate.

        Chiama la ruotine di inizializzazione delle variabili.
        Gestisce ciclicamente il calcolo delle cinque classi di
        scansione.
        Ogni secondo calcola:
          -  Tutte le calcolate a 1 secondo
          -  1/5 delle calcolate a 5 secondi
          -  1/15 delle calcolate a 15 secondi
          -  1/30 delle calcolate a 30 secondi
          -  1/60 delle calcolate a 60 secondi

	Creazione :  Antecedente 01.05.92
  
*******************************************************************/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"
#include "maxpar.inc"

// External function declarations
extern int rew(int, int, int*);
extern int tra(int, int);
extern int gettime(int);
extern int bitvalue(short *, short);
extern void media(int);
extern void massimo(int);
extern void minimo(int);
extern void integrale(int);
extern void portata1(void);
extern void portata2(void);
extern void filtro(void);
extern void mediaist(void);
extern void operaz(void);
extern void sommaist(void);
extern void scartoqm(int);
extern void oreorgani(int);
extern void oremisure(int);
extern void gerarch(void);
extern void verifall(short, short);

#ifdef GERARC
extern char g_cAbilCalcGer[];
extern short mbox_abilger;
#endif

void calc()
{
int i,j;

#ifdef GERARC
char cAbilCalcGer[max_dbsall];
int iRew;
rew(mbox_abilger,0,&iRew);
for(i=0;i<max_dbsall;i++)
{
	cAbilCalcGer[i]=g_cAbilCalcGer[i];
	g_cAbilCalcGer[i]=0;
}
tra(mbox_abilger,1);
#endif

tab=&tab_cal[n_periodi-1];
for(i=n_periodi-1;i>-1; i--,tab--)
	{
  	if(!tab->count_periodo)		  
   	{
      tab->addr_corrente=tab->indice;
      tab->corrente=tab->inizio;
      tab->count=tab->ncalt;
      tab->count_periodo=tab->period;
      gettime(i);	  
    	}
	if(!tab->count) goto NESSUNA_CALC;
   j=0;
   do
   	{
      if(bitvalue(&dbasf[tab->addr_corrente],g2an_fs) ||
         bitvalue(&dbasf[tab->addr_corrente],g2an_fz))
      		goto CONT;
      switch(tab->corrente->a.tipoc)
        {
        case 1:/*media*/
	        media(i);		 
           break;
        case 2:/*massimo*/
           massimo(i);
           break;
        case 3:/*minimo*/
           minimo(i);	 
           break;
        case 4:/*integrale*/
	        integrale(i);		
           break;
        case 5:/*accumulo*/
           integrale(i);		
           break;
        case 6:/*portata aga*/
	        portata1();			
			  break;
        case 7:/*portata uni*/
           portata2();			
           break;
        case 8:/*filtro*/
           filtro();				
           break;
        case 9:/*media nel tempo*/
           mediaist();			
           break;
        case 10:/*operazioni*/
           operaz();		
           break;
        case 11:/*somma*/
	        sommaist();			
           break;
        case 12:/*scarto*/
           scartoqm(i);			
           break;
        case 13:/*organi*/
           oreorgani(i);			  
           break;
        case 14:/*ore misura*/
           oremisure(i);		
           break;
#ifdef GERARC
	/* gerachia allarmi pendenti o in archivio*/
	case AS_GERARCHIA_ALLPENDENTI:
	case AS_GERARCHIA_ALLARCHIVIATI:
		if(cAbilCalcGer[tab->corrente->g.sDbAll-1] || 
		  (tab->corrente->a.periodo & ~0X80)>1)
			gerarch();
		break;
#endif
		  }       /* end switch */
		verifall(tab->addr_corrente,g1tipas) ;
      CONT:
      tab->count--;
      if(tab->corrente->a.link==-1) break ;
      tab->addr_corrente=tab->corrente->a.link;
      tab->corrente=&dbasde[tab->corrente->a.link];
    }
	while(++j<tab->ncals ) ;

   NESSUNA_CALC:

    tab->count_periodo--;
	}

}

