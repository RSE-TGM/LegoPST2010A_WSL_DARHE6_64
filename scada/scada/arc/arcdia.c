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
   arcdia.c

   Modulo per la generazione degli allarmi dei punti di diagnostica
   relativi agli archivi.

   Parametri

   point    short    indice punto in data base
   ext      short    tipo di punto
   tipall   short    tipo di allarme 

   Ritorno

   nessuno
   
   31 Marzo 1992  Rel. 1.0 Fc

   11 Gennaio 1993
   Inserimento trattamento severita'
*/
#include <osf1.h>
#include <stdio.h>
#include "comunic.inc"
#include "messcada.inc"
#include "mesqueue.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "tipal.inc"

arcdia(point,ext,tipall)
short point, ext, tipall;
{
QUEUE_PACKET pack;
S_MALLA mess;

pack.wto=0;
pack.que=c_visall;
pack.flg=MSG_WAIT;
pack.amsg=(char*)&mess;
pack.lmsg=sizeof(S_MALLA);

switch(ext)       // tipo di trattamento piu' bit di emissione
{
case g1tipdd:
   mess.ertr=(dbdd[point] & M_TRSED) + 0x80 ;
	mess.sogl1=1;
break;
case g1tipad:
    mess.ertr=((dbadal[point].tr_bdm & M_LSEVA)>>6) + 
    (dbadal[point].tr_bdm>>12)+0x80;  
	mess.sogl1=-1;
break;
default:
return(0);
}
/*
   costruzione pacchetto
*/
mess.ext=ext;
mess.punt=point;
mess.sprec=mis_norm;
mess.satt=tipall;
mess.sogl2=-1;
   
enqueue(&pack);
return(0);
}
