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
        la function modfst permetta la modifica
        del valore di una stringa

        punto input short puntatore in db della misura da
                          modificare
*/
#include <stdio.h>
#include <string.h>

#include "ansiscr.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"			 
#include "comunic.inc"
#include "tabelle.inc"
#include "deflag.inc"
#include "ansiscr.h"
#include "ctasti.inc"

extern char * nuovo_valore;

modfst(punto)
short punto ;
{
char risp[g0lunst];
short letti ;

/*
        chiedo il nuovo valore
*/
risp[0]=0;
letti=0 ;
scrxy(23,0);
deleol() ;
scrxy(23,1);
printf(nuovo_valore);
letti=rdpb(21,23,risp,g0lunst-1,0);
if(letti==0) return(0);
risp[letti]=0;
memcpy(&dbstv[punto*g0lunst],risp,g0lunst);
}


