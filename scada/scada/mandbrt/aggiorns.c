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
/*-> AGGIORst.C
        la function aggiornst visualizza valori
        delle stringhe
        scorrendo la tabella vispun

        tipo input int tipo di analogico
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

aggiornst(indice)
short indice;
{
short punt;
short tot,i ;
char valore[g0lunst+1];

memset(valore,0,g0lunst+1);
/*
        scrittura dei valori e dei flag
*/
tot=indice*num_righe+1+off_val;
memcpy(valore,&dbstv[vispun.punt[indice]*g0lunst],g0lunst);
scrxy(tot,val_pos);
printf("%s",valore);

}


