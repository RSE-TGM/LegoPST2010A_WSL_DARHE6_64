/*
   modulo CtrPort.c
   tipo 
   release 2.4
   data 6/13/96
   reserved @(#)CtrPort.c	2.4
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/****************************************************************
**
        la function ctrport verifica che le costanti associate
        ai diametri siano accettabili e ne fornisce il valore
        finale
                
        ritorna 1 se i valori non sono accettabili
                0 se tutto ok
**
****************************************************************/

#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <DatiPortata.h>

extern char path_txt[FILENAME_MAX+1];

CtrPort(tipc,cost1,cost2,costA,costB)
int tipc ;
float cost1, cost2 ;
float *costA, *costB ;
{
int i ;

float start,g,rapp;
float apiccolo,agrande,apic1,apic2, aerre, aesse ;


if( tipc==6)                    /* AGA */
  {
        *costA=cost1 * 0.9981 * sqrt(228.4) * cost2 * 24. *
              (1./35.31) * 0.001 * sqrt(14.22) ;
  }
else
  {
/* rapporto fra(diametro condotta/diametro orifizio)**2  */

        rapp=pow((cost2/cost1),2.);     
        for(i=0,start=0.05;i < 14;i++)
          {
          if((rapp>=start) &&  (rapp < (start+0.05)) ) goto PROSEGUI;
          else   start+=0.05;
          }
        return(1) ;
        PROSEGUI:
        agrande=prange[i][1];
        if(i==13)       apiccolo=prange[13][0];
        else
          {
                apic1=prange[i][0];
                apic2=prange[i+1][0];
                apiccolo=(((rapp-start)*(apic2-apic1))/0.05)+apic1;
          }
        aerre=prange[14][0];
        aesse=prange[15][0];
        g=prange[14][1];
        *costA=0.209250 * apiccolo * aerre * aesse * (cost2*cost2) *
                24. * sqrt(1./g) * (1./1000.) ;
        *costB=agrande;
 }
return(0) ;

}
