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
   GdcDia
      La funzione gestisce la diagnostica del reperibile
      interpretando il byte STAT_A1 del protocollo

      In particolare segnala:
            -  funzionamento del Gdc bit IDL
            -  funzionamento delle linee bit L1, L2, L3, L4

   Parametri
      
      short Status del reperibile

   Ritorno

      nessuno

*/
#include "comunic.inc"
#include "mesqueue.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "repgdc.h"
#include "mesprocv.inc"

short GdcOldStatus;           // stato precedente Gdc

void GdcDia(short GdcNewStatus)
{
short status;
S_MDIA mess;
QUEUE_PACKET pack;
short prog;

status=GdcNewStatus ^ GdcOldStatus;
if(!status) return;                      // nessuna variazione

mess.indice=mdia;
mess.nodo=0;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.que=c_mmii;
pack.amsg=(char*)&mess;

prog=0;
if(status & gdc_mStatus)                 // stato complessivo
{
   mess.a[prog].allarme=gdc_dStatus;
   if(GdcNewStatus & gdc_mStatus) mess.a[prog].condiz=1;
   else mess.a[prog].condiz=0;
  	prog++;
}
if(status & gdc_mL1)                        // stato linea 1
{
   mess.a[prog].allarme=gdc_dL1;
   if(GdcNewStatus & gdc_mL1) mess.a[prog].condiz=1;
   else mess.a[prog].condiz=0;
  	prog++;
}
if(status & gdc_mL2)                        // stato linea 2
{
   mess.a[prog].allarme=gdc_dL2;
   if(GdcNewStatus & gdc_mL2) mess.a[prog].condiz=1;
   else mess.a[prog].condiz=0;
  	prog++;
}
if(status & gdc_mL3)                         // stato linea 3
{
   mess.a[prog].allarme=gdc_dL3;
   if(GdcNewStatus & gdc_mL3) mess.a[prog].condiz=1;
   else mess.a[prog].condiz=0;
  	prog++;
}
if(status & gdc_mL4)                         // stato linea 4
{
   mess.a[prog].allarme=gdc_dL4;
   if(GdcNewStatus & gdc_mL4) mess.a[prog].condiz=1;
   else mess.a[prog].condiz=0;
  	prog++;
}
GdcOldStatus=GdcNewStatus;             // memorizzo nuovo stato
pack.lmsg=h_dia+prog*sizeof(S_ALDIA);
enqueue(&pack);
}


