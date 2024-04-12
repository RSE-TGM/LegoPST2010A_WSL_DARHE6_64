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
        la function modfan permette la modifica
        di valori e flag di punti analogici di
        qualsiasi tipo

        tipo input indica il tipo di analogici
                   che si sta esaminando
        punto input short puntatore in db della misura da
                          modificare
*/
#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "ctasti.inc"
#include "tabelle.inc"
#include "deflag.inc"
#include "ansiscr.h"
#include "ctasti.inc"


modfan(tipo,punto)
short tipo ;
short punto ;
{

#include "modfan.inc"
char risp[10];
short letti ;
short i,ii;
float value ;

INIZIO :
/*
        chiedo se si vuole modificare il valore o i flag
*/
risp[0]=0;
letti=0 ;
do
	{	
   scrxy(23,1);
	deleol() ;
	printf("%s",valori_flag);
   rdpb(50,23,risp,0,0);
	}
while(risp[0] !='V' && risp[0] != 'F' && risp[0] != ESC && risp[0] != CR);
if(risp[0] == ESC || risp[0] == CR) return(0) ;        /* newline o cr o escape */
switch(risp[0])
	{
	case 'F' :                     /* modifica flag */
        NON_ACCET:
		  scrxy(23,1);
		  deleol() ;
		  scrxy(23,1);
        printf("FLAG : ");
		  ii=9;
        for(i=0;i<16;i++)if(strcmp(sigfan[i],"  "))
        	{printf("%s ",sigfan[i]);ii+=3;}
        letti=rdpb(66,23,risp,2,0);
        if(letti==0) return(0);
        for(i=0;i<16;i++)     /* verifico quale  */
        	{
			if(!strncmp(risp,sigfan[i],2))
         	{
				switch(tipo)      /* modifica del flag*/
            	{       
               case g1tipaa :   /*  an. acquisiti */
               	bitset(&dbaaf[punto],i,!bitvalue(&dbaaf[punto],i));
                  break ;
               case g1tipas :  /* an. calcolati st.*/
                  bitset(&dbasf[punto],i,!bitvalue(&dbasf[punto],i));
                  break ;
               case g1tipac :  /* an. calc. non st.*/
                  bitset(&dbacf[punto],i,!bitvalue(&dbacf[punto],i));
                  break ;
               case g1tipad :  /* an. diagnostica */
                  bitset(&dbadf[punto],i,!bitvalue(&dbadf[punto],i));
                  break ;
               case g1tipao :  /* analogici uscita */
                  bitset(&dbaof[punto],i,!bitvalue(&dbaof[punto],i));
                  break ;
               }
				goto INIZIO ;
            }
         }
        goto NON_ACCET ;
        break ;
	case 'V' :              /* modifica valori */
        DECOD :
		  scrxy(23,1);
		  deleol() ;
		  printf("%s",nuovo_valore);
        letti=rdpb(21,23,risp,10,0);
        if(letti==0) return(0);
        if(sscanf(risp,"%f",& value) != 1) goto DECOD ;
        switch(tipo)
        	{
        	case g1tipaa:           /* an. acquisiti */
         	dbaav[punto]=value ;
            break;
        	case g1tipas:           /* an. calcolati standard */
            dbasv[punto]=value ;
            break;
        	case g1tipac:           /* an. calcolati non stan. */
            dbacv[punto]=value ;
            break;
        	case g1tipad:           /* an. diagnostica */
            dbadv[punto]=value ;
            break;
		   case g1tipao :
				invao(punto,value);
				break;
        	}

        goto INIZIO ;
	}
}

