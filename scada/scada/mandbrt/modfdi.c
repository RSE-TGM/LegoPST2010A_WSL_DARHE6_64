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
        la function modfdi per mette la modifica
        di valori e flag di punti digitali  di
        qualsiasi tipo

        tipo input indica il tipo di digitali
                   che si sta esaminando
        punto input short puntatore in db della misura da
                          modificare
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "ctasti.inc"
#include "tabelle.inc"
#include "deflag.inc"
#include "ansiscr.h"
#include "ctasti.inc"

modfdi(tipo,punto)
short tipo ;
short punto ;
{
#include "modfdi.inc"
char risp[10];
short letti ;
short i,ii,app,ier ;
short value ;

INIZIO :
/*
        chiedo se si vuole modificare il valore o i flag
*/
risp[0]=0;
letti=0 ;

if(tipo==g1tipdo)  /* solo per comandi digital output */
	{
	do
		{
	   scrxy(23,1);
		deleol() ;
		printf("%s",inv_com) ;
      rdpb(50,23,risp,0,0);
		}
    while(risp[0] !='I' &&  risp[0] !=ESC && risp[0] !=CR)	;
	 if(risp[0] == ESC || risp[0] == CR) return(0) ;       
	 coman(punto);
    return  0 ;
}
else
	{
		do
			{
		   scrxy(23,1);
			deleol() ;
			printf("%s",status_flag) ;
         rdpb(50,23,risp,0,0); 
			}
      while(risp[0] !='S' && risp[0] != 'F' && risp[0] !=ESC && risp[0] !=CR);
	}
if(risp[0] == ESC || risp[0] == CR) return(0) ;        /* newline o cr o escape */
switch(risp[0])
	{
	case 'F' :                     /* modifica flag */
    NON_ACCET:
    scrxy(23,1);
  	 deleol() ;
    printf("FLAG : ");
	 ii=9;
    for(i=0;i<10;i++)if(strcmp(sigfdi[i],"  "))	/* scrivo solo i flag modificabili */
    	{printf("%s ",sigfdi[i]);ii+=3;}
    letti=rdpb(48,23,risp,2,0);
    if(letti==0) return(0);
    for(i=0;i<10;i++)     /* verifico quale  */
    	{
		if(!strncmp(risp,sigfdi[i],2))
      	{
			switch(tipo)      /* modifica del flag*/
         	{       
            case g1tipda :   /*  di. acquisiti */
             bitset(&dbda[punto],i,!bitvalue(&dbda[punto],i));
				 break ;
            case g1tipds :  /* di. calcolati st.*/
             bitset(&dbds[punto],i,!bitvalue(&dbds[punto],i));
             break ;
            case g1tipdc :  /* di. calc. non st.*/
             bitset(&dbdc[punto],i,!bitvalue(&dbdc[punto],i));
             break ;
            case g1tipdd :  /* di. diagnostica */
             bitset(&dbdd[punto],i,!bitvalue(&dbdd[punto],i));
             break ;
            }
         goto INIZIO ;
         }
      }
    goto NON_ACCET ;
    break ;
	case 'S' :              /* modifica valori */
	 scrxy(23,1);
	 deleol() ;
    switch(tipo)
    	{
      case g1tipda :   /*  di. acquisiti */
        bitset(&dbda[punto],g2di_sl,
                !bitvalue(&dbda[punto],g2di_sl));
        break ;
      case g1tipds :  /* di. calcolati st.*/
        bitset(&dbds[punto],g2di_sl,
                !bitvalue(&dbds[punto],g2di_sl));
        break ;
      case g1tipdc :  /* di. calc. non st.*/
        bitset(&dbdc[punto],g2di_sl,
                !bitvalue(&dbdc[punto],g2di_sl));
        break ;
      case g1tipdd :  /* di. diagnostica */
        bitset(&dbdd[punto],g2di_sl,
                !bitvalue(&dbdd[punto],g2di_sl));
        break ;
      }
	goto INIZIO ;
	}
}

