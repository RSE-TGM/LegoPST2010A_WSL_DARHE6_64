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
/*************************************************************
	Modulo: MASSIMO.C
  
        Massimo fra il valore della contribuente e il
        valore attuale della generata.
  
        I contatori di campioni e di errori vengono resettati
        secondo il valore della frequenza e il punto viene
        messo fuori scansione.
        Se la contribuente e' fuori attendibilita' oppure
        fuori scansione il confronto non viene eseguito e il
        valore della generata non viene cambiato.
        Altrimenti si esegue il confronto tra generata e
        contribuente, e si associa il valore massimo  alla
        contribuente.
        Alla routine viene passata la classe di scansione del punto.
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione
                14 Luglio 1994
                Getione frequenza utente indici 7 e 8
**************************************************************/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

void massimo(periodo)
int periodo;
{
int i;
double val;
short *flag, contr;
short freq,cong;
short *destf;

contr=tab->corrente->a.indice.punt;
freq=tab->corrente->a.freq-1;

switch(freq)
{
case 0: case 1: case 2:	 case 6:			 /* scrittura in dbs	*/
  		destf=&dbasf[tab->addr_corrente];
		cong=0;
      if(freq==6) freq=f_ut;
		break;
default:									 /* scrittura nel descrittore */
  		destf=&tab->corrente->a.savef;
      if(freq==7) freq=f_ut;
		else freq=freq-3;
		cong=1;
		break;
}			

/*
		  se e' scaduta la frequenza resetto contatori    
        e resetto anche il valore della calcolata       
*/
if( reset[periodo][freq] == 1)
  {
   tab->corrente->a.cont_err=0;
   tab->corrente->a.cont_camp=0;
	if(cong)
   {
  		bitset(&dbasf[tab->addr_corrente],g2an_fa,
			bitvalue(&tab->corrente->a.savef,g2an_fa));
		dbasv[tab->addr_corrente]=tab->corrente->a.savev;
   }
   else
   {
   	dbasv[tab->addr_corrente]=-100000.0;						  /* reset valori e flag */
	   bitset(destf,g2an_fa,0);
   }
	tab->corrente->a.savev=(double)-100000.0;
  }

tab->corrente->a.cont_camp++;   /* aggiorno numero di campionamenti*/
switch(tab->corrente->a.indice.ext)
 {
 case g1tipaa:
 		  flag=&dbaaf[contr];
        val= dbaav[contr];
        break;
  case g1tipac:
        flag=&dbacf[contr];
        val= dbacv[contr];
        break;
  case g1tipas:
        flag=&dbasf[contr];
        val= dbasv[contr];
        break;
  case g1tipad:
        flag=&dbadf[contr];
        val= dbadv[contr];
        break;
 }

/*      se la contribuente e' F.A o F.S. la calcolata non e' aggior.*/

if(bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs))
        tab->corrente->a.cont_err++;
else
    {
    if(tab->corrente->a.savev<val)
    {
      tab->corrente->a.savev=val;
      if (!cong)
   	   dbasv[tab->addr_corrente]=(float)val;
    }
    bitset(destf,g2an_fa,0);
    }
/*
printf("\ngenerata =%f ",tab->corrente->i.savev);
*/
}

