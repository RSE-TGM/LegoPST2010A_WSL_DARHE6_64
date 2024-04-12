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
        la function aggiornor visualizza lo stato dell'organo
        e flag degli organi

        indice input posizione nella tabella
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

aggiornor(indice)
short indice;
{
short punt;
short tot,i ;
short flag;     /* flag generali */
short flat;     /* flag time out     */
short stato ;
char  sigla[lun_stato+1] ;
/*
        leggo dal data base i valori da visualizzare
*/
punt=vispun.punt[indice] ;
stato=(dbosc[punt] &  0x00FF) ;	 
memcpy(sigla,&stat_diz[stato *lun_stato],lun_stato);
sigla[lun_stato]=0 ;

flag = dbosc[punt] ;
flat= dboft[punt] << 8 ;    /* nel primo byte */
/*
        scrittura dei valori e dei flag
*/
tot=indice*num_righe+1+off_val;
scrxy(tot,val_pos);
printf("%s",sigla);

tot=indice*num_righe+1+off_flag ;
for(i=0;i<8;i++)             /* flag generici */
	{
	scrxy(tot,flag_pos+3*i);
	if(bitvalue(&flag,i))
		printf("%s",sigfor[i]);	
	else printf("  ");
	}
tot=indice*num_righe+1+off_flag ;
for(i=0;i<8;i++)
	{	
	scrxy(tot,flat_pos+3*i);
	if(bitvalue(& flat,i))
		printf("%s",sigfat[i]);	
	else printf("  ");
   }
}

