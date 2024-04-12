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
	Modulo: PORTATA1.C
  
        PORTATA  a norme AGA.
  
        Prima di applicare la formula per il calcolo della
        portata occorre convertire :
        .  Temperatura da gradi centigradi a gradi Kelvin
        La portata non viene calcolata e viene quindi settato
        il bit di fuori attendibilita' se :
        .  Almeno una delle contribuenti si trova F.A o F.S
        .  La temperatura (in gradi Kelvin) e' uguale a zero
           oppure il polinomio calcolato e' zero.
        .  Il valore del rapporto (Dp*press)/(temper*polin)<0
        Il secondo punto evita una divisione per zero e il terzo
        il calcolo di una radice quadrata di un valore negativo.
  
        Non vengono passati parametri alla routine.
  
        La definizione delle costanti per il calcolo del polinimio
        e' nel file di include CALAS.INC , presente nello stesso
        direttorio di questa routine.
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <math.h>
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

portata1()
{
PUNTATORE temp[3];
int i;
double val[3], polin, radice, portata;
short *flag[3];

temp[0]=tab->corrente->p.Dp;
temp[1]=tab->corrente->p.press;
temp[2]=tab->corrente->p.temper;

for(i=0;i<3;i++)
  {
   switch(temp[i].ext)
    {
        case g1tipaa:
                flag[i]=&dbaaf[temp[i].punt];
                val[i]=dbaav[temp[i].punt];
                break;
        case g1tipac:
                flag[i]=&dbacf[temp[i].punt];
                val[i]=dbacv[temp[i].punt];
                break;
        case g1tipas:
                flag[i]=&dbasf[temp[i].punt];
                val[i]=dbasv[temp[i].punt];
                break;
        case g1tipad:
                flag[i]=&dbadf[temp[i].punt];
                val[i]=dbadv[temp[i].punt];
                break;
    }   /*end switch */

   if(bitvalue(flag[i],g2an_fa) || bitvalue(flag[i],g2an_fs))
        tab->corrente->p.cont_err++;
  }  /* end for */

if( tab->corrente->p.cont_err)
        bitset(&dbasf[tab->addr_corrente],g2an_fa,1);
else
 {
  val[2]=val[2] + 273.14 ;      /*temper.in gradi Kelvin */
  polin= x0 + x1*val[2] + x2*val[1] + x3*val[2]*val[2] +
         x4*val[1]*val[1] + x5*val[2]*val[1];
  if( (val[2]*polin) !=(double)0 )
    if( (radice=(val[0]*val[1])/(val[2]*polin)) >= (double)0 )
      {
        portata=(double)tab->corrente->p.cost1 * sqrt(radice);
        if(portata < (double)0) portata=(double)0.0;
        dbasv[tab->addr_corrente]=(float)portata;
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
      }  /* end if */
  }

tab->corrente->p.cont_err=0;
/*
printf("\ngenerata =%f",dbasv[tab->addr_corrente]);
printf("\nval[0] =%f",val[0]);
printf("\nval[1] =%f",val[1]);
printf("\nval[2] =%f\n",val[2]);
*/
}

