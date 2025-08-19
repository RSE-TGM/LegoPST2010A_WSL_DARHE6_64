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
#include <stdio.h>
/*
	la routine initor inizializza le tabelle per la suddivisione del
	calcolo degli organi
*/

#include "dconf.inc"

#define _PUBLIC 0

#include "organi.inc"

extern DB_HEADER h_db;

void initor()
{
short or_part ;

/*
	divido i timer degli organi in 5 parti per il decremento
	dei contatori (si considerano poi 4 organi alla volta) 
*/
if(! or_tab[4].num)				 /* non e' ancora stato inizializz. ? */
{
	or_part=(h_db.dimor/20);
	or_tab[0].iniz=0 ;			or_tab[0].num=or_part ;
	or_tab[1].iniz=or_part;		or_tab[1].num=or_part*2 ;
	or_tab[2].iniz=or_part*2;	or_tab[2].num=or_part*3 ;
	or_tab[3].iniz=or_part*3;	or_tab[3].num=or_part*4;
	or_tab[4].iniz=or_part*4 ;	or_tab[4].num=h_db.dimor/4 ;
	inizio_or=0 ;
}
return ;
}

