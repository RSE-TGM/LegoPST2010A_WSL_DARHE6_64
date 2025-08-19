/**********************************************************************
*
*       C Source:               scartoqm.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 12:26:47 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: scartoqm.c-3 %  (%full_filespec: scartoqm.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*************************************************************
	Modulo: SCARTOQM.C
  
        SCARTO QUADRATICO MEDIO relativo a una misura.

        La formula di calcolo e':
           s.q.m.=(1/n) * (somma_q - (1/n)*(somma_i*somma_i));
        con:
           s.q.m. = scarto quadratico medio;
           n      = numero di campioni acquisiti nell'intervallo di calcolo;
           somma_q= somma dei quadrati dei campioni;
           somma_i= somma dei campioni.

        Lo scarto  possiede una frequenza di reset, quando questa
        e' scaduta vengono resettati i contatori dei campionamenti
        validi, totale,somme parziali e quadratiche.
        Se la contribuente e' fuori attandibilita' oppure e'
        fuori scansione non viene eseguito il calcolo.
        Se il numero di campionamenti validi supera il numero totale
        di questi moltiplicato un certo coefficiente, il calcolo e'
        ritenuto corretto.
  
        Non vengono passati parametri alla routine.
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

void scartoqm(periodo)
int periodo;
{
int i;
double somma_q,somma_i,val;
short *flag, contr, freq;
short cong;
float *destv;
short *destf;
#if defined OSF1 || defined LINUX
float app_float_osf1;
#endif

contr=tab->corrente->q.misura.punt;
freq=(tab->corrente->q.freq)-1;

switch(freq)
{
case 0: case 1: case 2:				 /* scrittura in dbs	*/
  		destf=&dbasf[tab->addr_corrente];
		destv=&dbasv[tab->addr_corrente];
		cong=0;
		break;
default:									 /* scrittura nel descrittore */
  		destf=&tab->corrente->q.savef;
		destv=&tab->corrente->q.savev;
		freq=freq-3;
		cong=1;
		break;
}			

if( reset[periodo][freq] == 1)
   {
   tab->corrente->q.cont_cv=0;
   tab->corrente->q.cont_ctot=0;
   tab->corrente->q.somma_q=0;
   tab->corrente->q.somma_i=0;
	if(cong)
   {
  		bitset(&dbasf[tab->addr_corrente],g2an_fa,
			bitvalue(&tab->corrente->q.savef,g2an_fa));
		dbasv[tab->addr_corrente]=tab->corrente->q.savev;
   }
#if defined OSF1 || defined LINUX
    	app_float_osf1 = (float)0.0;
    	memcpy(destv,&app_float_osf1,sizeof(float));
#else
	*destv=0.0;
#endif
	bitset(destf,g2an_fa,0);
   }
tab->corrente->q.cont_ctot++;
switch(tab->corrente->q.misura.ext)
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
//printf("\nval_db=%f; n=%d;", val, tab->corrente->q.cont_cv);
if( bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs))
     { }
else
    {
    tab->corrente->q.cont_cv++;
    somma_q=(double)tab->corrente->q.somma_q+(val*val);
    tab->corrente->q.somma_q=somma_q;
    somma_i=(double)tab->corrente->q.somma_i+val;
    tab->corrente->q.somma_i=somma_i;
    val=((double)1.0 / (double)tab->corrente->q.cont_cv) *
    (somma_q-((double)1.0/(double)tab->corrente->q.cont_cv)*(somma_i*somma_i));
	 if(val <0) val=-val;
        
#if defined OSF1 || defined LINUX
    app_float_osf1 = (float)val;
    memcpy(destv,&app_float_osf1,sizeof(float));
#else
    *destv=val;
#endif

    if(tab->corrente->q.cont_cv > (tab->corrente->q.cont_ctot * coef_scarto))
	    {
       bitset(destf,g2an_fa,0);
       }
    else
       bitset(destf,g2an_fa,1);
    }

//printf("\nsomma_q=%f; somma_i=%f; scartoqm=%f",somma_q,somma_i,val);
//printf("\n");
}

