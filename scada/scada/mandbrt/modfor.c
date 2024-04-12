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
        la function modfor permetta la modifica
        dello stato e dei flag degli organi

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

modfor(punto)
short punto ;
{
#include "modfor.inc"
char risp[lun_stato+1];
short letti ;
short i,ii;
short stato ;
S_FSTATO  *tabtipo ;


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
  	printf("%s",status_flag) ;
   rdpb(50,23,risp,0,0);
	}
while(risp[0] !='S' && risp[0] != 'F' && risp[0] != ESC && risp[0] != CR);
if(risp[0] == ESC || risp[0] == CR) return(0) ;        /* newline o cr o escape */
switch(risp[0])
	{
	case 'F' :                     /* modifica flag */
        NON_ACCET:
		  scrxy(23,1);
		  deleol() ;
        printf("FLAG : ");
		  ii=9;
        for(i=0;i<8;i++)if(strcmp(sigfor[i],"  "))
        	{printf("%s ",sigfor[i]);ii+=3;}
        letti=rdpb(46,23,risp,2,0);
        if(letti==0) return(0);
        for(i=0;i<8 ;i++)     /* verifico quale  */
        	{ 
		  	if(!strncmp(risp,sigfor[i],2))
        		{       
         	bitset(&dbosc[punto],i,!bitvalue(&dbosc[punto],i));
         	goto INIZIO ;
         	}
        }
        goto NON_ACCET ;
        break ;
	case 'S' :              /* modifica stato  */
        DECOD :
		  scrxy(23,1);
		  deleol() ;
        printf("%s",nuovo_stato);
        letti=rdpb(21,23,risp,lun_stato,0);
        if(letti==0) return(0);
		  while(letti < lun_stato)
		  	risp[letti++]=' ';
        tabtipo=&storg[dbode[punto].tipo] ;	  
		  if((stato=ctrlstato(risp,tabtipo,stat_diz))>=0)
        		dbosc[punto]=(dbosc[punto] & 0xFF00)+stato ;
        else  goto DECOD ;
        goto INIZIO ;
}
}

