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
	Modulo: MEDIA.C

        Media su un contribuente.
        
        La media  possiede una frequenza di reset, quando questa
        e' scaduta vengono resettati i contatori di errore e di
        campionamento.
        Se la contribuente e' fuori attendibilita' oppure e'
        fuori scansione non viene eseguito il calcolo: la media
        rimane la precedente e viene incrementato il contatore
        di errore.
        In caso contrario la media viene aggiornata e viene resetta-
        to il bit di fuori attendibilita'.

        Alla routine viene passato come parametro a quale
        classe di scansione appartiene il punto corrente.

	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione
                11 Luglio 1994 Fc
                Reset con frequenza definita da utente

*************************************************************/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

void media(periodo)
int periodo;
{
double val;
short *flag, contr, freq;
short cong;
short *destf;

contr=tab->corrente->a.indice.punt;
freq=(tab->corrente->a.freq)-1;
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

if( reset[periodo][freq] == 1 )
{
   tab->corrente->a.cont_camp=0;
   tab->corrente->a.cont_err=0;
	if(cong)
   {
  		bitset(&dbasf[tab->addr_corrente],g2an_fa,
				bitvalue(&tab->corrente->a.savef,g2an_fa));
		dbasv[tab->addr_corrente]=tab->corrente->a.savev;
   }
   else
   {
   	dbasv[tab->addr_corrente]=0.0;
   	bitset(destf,g2an_fa,0);
   }
	tab->corrente->a.savev=(double)0.0;
}

tab->corrente->a.cont_camp++;
switch(tab->corrente->a.indice.ext)
 	{
  	case g1tipaa:
        flag=&dbaaf[contr];
        val=  dbaav[contr];
        break;
  	case g1tipac:
        flag=&dbacf[contr];
        val=  dbacv[contr];
        break;
  	case g1tipas:
        flag=&dbasf[contr];
        val=  dbasv[contr];
        break;
  case g1tipad:
        flag=&dbadf[contr];
        val=  dbadv[contr];
        break;
 	}
if(bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs))
    tab->corrente->a.cont_err++;
else
    {
    if( tab->corrente->a.cont_err >=(tab->corrente->a.cont_camp * coef_media))
    	bitset(destf,g2an_fa,1);
    else
    	{
      val=((tab->corrente->a.savev*(tab->corrente->a.cont_camp-1))+val)/tab->corrente->a.cont_camp;
      tab->corrente->a.savev=val;
      if (!cong)
   	   dbasv[tab->addr_corrente]=val;
      bitset(destf,g2an_fa,0);
      }
    }
/*
printf("\ncampioni: %ld, calcolata: %f",tab->corrente->a.cont_camp,val);
printf(" descr=%f dbase=%f",tab->corrente->a.savev,dbasv[tab->addr_corrente]);
*/
}

