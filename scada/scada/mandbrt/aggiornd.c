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
		  la function aggiorndi visualizza valori
        e flag dei punti digitali
        scorrendo la tabella vispun

        tipo input int tipo di digitale
*/
#include <stdlib.h>
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "tabelle.inc"
#include "deflag.inc"
#include "ansiscr.h"
#include "ctasti.inc"

aggiorndi(indice)
short indice;
{
short punt;
short tot,i,ii ;
short flag;     /* flag */
short trat;     /* flag di trattamento */
short vatt;     /* valore attuale */
char chvatt[2];
/*
        leggo dal data base i valori da visualizzare in
        base al tipo di digitale
*/
punt=vispun.punt[indice] ;
switch (vispun.ext[indice])
	{
   case g1tipda :
    flag=dbda[punt];
    trat=dbdatr[punt] ;
    vatt=bitvalue(&dbda[punt],g2di_sl) ;
    break ;
   case g1tipds :
    flag=dbds[punt];
    trat=dbdstr[punt] ;
    vatt=bitvalue(&dbds[punt],g2di_sl) ;
    break ;
   case g1tipdc :
    flag=dbdc[punt];
    trat=dbdctr[punt] ;
    vatt=bitvalue(&dbdc[punt],g2di_sl) ;
    break ;
   case g1tipdd :
    flag=dbdd[punt];
    trat=dbddtr[punt] ;
    vatt=bitvalue(&dbdd[punt],g2di_sl) ;
	   break ;
   case g1tipdo:
    return ;
   }
/*
        scrittura dei valori e dei flag
*/
tot=indice*num_righe+1+off_val;
scrxy(tot,val_pos);
printf("%1d",vatt);

tot=indice*num_righe+1+off_flag ;
for(i=0;i<10;i++)             /* flag generici */
	{
   if(bitvalue(&flag,i))
   	{
			 	scrxy(tot,flag_pos+3*i);
				printf("%s",sigfdi[i]);
     }
   else 
   	{
			 	scrxy(tot,flag_pos+3*i);
				printf("  ");
      
     }
   }
		  
for(i=0,ii=10;i<16;i++,ii++)           /* flag trattamento */
	{
   if(bitvalue(&trat,i))
   	{
			 	scrxy(tot,flag_pos+3*ii);
				printf("%s",sigftr[i]);
      
     }
	else 
   	{
			 	scrxy(tot,flag_pos+3*ii);
				printf("  ");
      
     }
	}	
}

