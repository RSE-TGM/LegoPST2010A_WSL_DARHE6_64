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
	Modulo : INTEGRAL.C
  
        INTEGRALE  relativo a una misura su minuto/ora/giorno.
        ACCUMULO   relativo ad una misura.
  
        Si differenziano per la presenza o meno del campo "time"
        nel descrittore.
        
        L' integrale/accumulo possiede una frequenza di reset, quando
        questa e' scaduta vengono resettati i contatori dei campiona-
        menti validi e di errore.
  		  Se la frequenza e' 1-3 viene aggiornato il valore in data
  		  base altrimenti (4-6) viene aggiornato il descrittore e solo
  		  in fase di reset il valore in dbs.
  		  Se la frequenza e' 7 o 8, il valore in data base viene azzerato
  		  quando la calcolata vale 999999 o 99999999 rispettivamente.
        Se la contribuente e' fuori attendibilita' oppure e'
        fuori scansione la calcolata viene aggiornata con la media
        del valore ottenuto sino a quel momento.
        Se il numero di campionamenti errati supera il numero totale
        di questi moltiplicato un certo coefficiente, il calcolo e'
        ritenuto corretto.
  
        Alla routine viene passato come parametro la classe di
        scansione della calcolata.
  
        Possiede un file di include locale "converti.inc" in cui 
        sono specificati i valori di conversione per il calcolo 
        dell'integrale.

	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <stdio.h>
#include <math.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

extern float convertempo[4][5] ;

void integrale(scansione)
int scansione;
{
double val;
short *flag, contr, freq;
short *destf;					/* destinazione fa		*/
short cong;						/* =0 scrittura in dbs =1 scrittura nel descrittore */

contr=tab->corrente->i.indice.punt;
freq=(tab->corrente->i.freq)-1;

switch(freq)
{
case 0: case 1: case 2: case 6: case 7:	 /* scrittura in dbs	*/
  		destf=&dbasf[tab->addr_corrente];
		cong=0;
		break;
default: 											 /* scrittura nel descrittore */
  		destf=&tab->corrente->i.savef;
		freq=freq-3;
		cong=1;
		break;
}			

if ( freq!=6 && freq!=7)
{
 if( reset[scansione][freq] == 1 )
  {
   tab->corrente->i.cont_camp=0;
   tab->corrente->i.cont_err=0;
	if(cong)
      {
   		bitset(&dbasf[tab->addr_corrente],g2an_fa,
				bitvalue(&tab->corrente->i.savef,g2an_fa));
			dbasv[tab->addr_corrente]=tab->corrente->i.savev;
      }
   else 
      {
   	   dbasv[tab->addr_corrente]=0.0;
   	   bitset(destf,g2an_fa,0);
      }
	tab->corrente->i.savev=(double)0.0;
  }
}
tab->corrente->i.cont_camp++;
switch(tab->corrente->i.indice.ext)
 {
  case g1tipaa:
        flag=&dbaaf[contr];
        val=(double)dbaav[contr];
        break;
  case g1tipac:
        flag=&dbacf[contr];
        val=(double)dbacv[contr];
        break;
  case g1tipas:
        flag=&dbasf[contr];
        val=(double)dbasv[contr];
        break;
  case g1tipad:
        flag=&dbadf[contr];
        val=(double)dbadv[contr];
        break;
 }
if( bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs))
        tab->corrente->i.cont_err++;
if(tab->corrente->i.tipoc == 5) /*caso accumulo*/
        val=tab->corrente->i.savev+val;
else                        /*caso integrale*/
        /* La sottrazione di 2 permette la congruenza con il
           riempimento delle tabella "convertempo" */
        val=tab->corrente->i.savev+(val*convertempo[tab->corrente->i.time-2]
                                  [scansione]);

if ( (freq==6 && val>(double)999999.0) || 
	  (freq==7 && val>(double)99999999.0) )
{
   tab->corrente->i.cont_camp=0;
   tab->corrente->i.cont_err=0;
	if (freq==6)	
   {
      dbasv[tab->addr_corrente]=fmod(val,(double)1000000.0);
      tab->corrente->i.savev=fmod(val,(double)1000000.0);
   }
	if (freq==7)
   {
      dbasv[tab->addr_corrente]=fmod(val,(double)100000000.0);
      tab->corrente->i.savev=fmod(val,(double)100000000.0);
   }
	bitset(destf,g2an_fa,0);
}
else
{   
	tab->corrente->i.savev=val;
   if (!cong)
      dbasv[tab->addr_corrente]=(float)val;
}

if(tab->corrente->i.cont_err <= tab->corrente->i.cont_camp*coef_integrale)
   bitset(destf,g2an_fa,0);
else
   bitset(destf,g2an_fa,1);
}


