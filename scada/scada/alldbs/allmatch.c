/**********************************************************************
*
*	C Source:		allmatch.c
*	Instance:		1
*	Description:	
*	%created_by:	famgr %
*	%date_created:	Wed Feb 11 11:52:55 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allmatch.c-1 %  (%full_filespec: allmatch.c-1:csrc:1 %)";
#endif

/*

   allmatch.c
   
   Routine che verifica se l' allarme passato come primo parametro 
   e' quello cercato. Le informazioni che identificano l' allarme cercato
   sono nella struttura alv   S_DBS_ALV* che e' il secondo parametro.
   
   Parametri:
           alv   S_DBS_ALV*     puntatore alla tabella allarmi relativa al
                                video che ha richiesto il riconoscimento
                                Contiene informazioni dell' allarme cercato.

           all_ex buff_all*     puntatore all' allarme da esaminare. 
*/

#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"
#include "diagnoan.inc"


int allmatch(all_ex,alv)
struct buff_all *all_ex;      /* allarme da esaminare */
S_DBS_ALV *alv;               // tabella video allarmi
{
/*
Verifico indice allarme
*/
if(all_ex->m.punt!=alv->par_miniASD.punt)
   return(1);
/*
Verifico tipo
*/
if(all_ex->m.ext!=alv->par_miniASD.ext)
   return(2);
/*
Verifico emissione rientro
*/
if(all_ex->m.ertr!=alv->par_miniASD.ertr)
   return(3);
/*
Verifico ore
*/
if(all_ex->ore!=alv->par_miniASD.ore)
   return(4);
/*
Verifico minuti
*/
if(all_ex->minuti!=alv->par_miniASD.minuti)
   return(5);
/*
Verifico secondi
*/
if(all_ex->secondi!=alv->par_miniASD.secondi)
   return(6);

/*
Ho trovato l' allarme
*/

return(0);
}
