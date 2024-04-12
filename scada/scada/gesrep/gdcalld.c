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
   GdcAllD
      funzione per inviare un generare un allarme di tipo digitale
      di diagnostica

   Parametri
      short punt  indice in data base del punto
      short stato stato del digitale

   Ritorno
      nessuno
*/
#include "comunic.inc"
#include "mesqueue.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "repgdc.h"
#include "mesprocv.inc"

GdcAllD(short point, short stato)
{
S_MDIA mess;
QUEUE_PACKET pack;

mess.indice=mdia;
mess.nodo=0;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.que=c_mmii;
pack.amsg=(char*)&mess;
pack.lmsg=h_dia+sizeof(S_ALDIA);

mess.a[0].allarme=point;
mess.a[0].condiz=stato;

enqueue(&pack);
return;
}
