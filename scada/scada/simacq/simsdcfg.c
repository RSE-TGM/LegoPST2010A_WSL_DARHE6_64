/**********************************************************************
*
*       C Source:               simsdcfg.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 12:21:58 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simsdcfg.c-4 %  (%full_filespec: simsdcfg.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   SIMSDCFG.C
      Invia al simulatore lo svincolo tra punti del simulatore e punti 
      installati su SSC 

      30.09.92  -  Rev.1.00  -  GM.Furlan

      27 Marzo 1995 Fc Porting a 32 Bit
*/
#include <osf1.h>
#include <stdio.h>

#include <string.h>
#include "comunic.inc"
#include "mesqueue.h"
#include "simmsg.inc"      // strutture messaggi da simulatore
#include "simula.inc"      // definizioni generali per simulatore
#include "dconf.inc"

// External function declarations
extern int rbyte(int, void *, long, int);

#if defined OSF1 || defined LINUX
#undef long
#define  long int
#endif

int simsdcfg(tipo, rc)
char tipo;     // tipo di punti: ANA=0: Analogici; DIG=1: Digitali
SM_DIAGNO* rc;   /* dignostica ricezione configurazione */
{
short i,j;
FILE *fp;           // pointer file di svincolo
QUEUE_PACKET pout;  // pacchetto da inserire in coda di trasmissione
QUEUE_PACKET pin;   // pacchetto da inserire in coda di ricezione
SM_CONFIG mout;     // messaggio in trasmissione (verso simulat.)
SVINHEA   hea;      // header file FSVINANA.RTF, FSVINDIG.RTF
SVINREC   recsvin;  // record file di svincolo 
char file[FILENAME_MAX+1];
long offset;

if(tipo==ANA)
{
   strcpy(file,conf[RTF]); 
   strcat(file,FSVINANA);    // file punti analogici
   fp=fopen(file,"rb");
   if(!fp)  return(-1);
}
else
{
   strcpy(file,conf[RTF]); 
   strcat(file,FSVINDIG);    // file punti digitali
   fp=fopen(file,"rb");
   if(!fp)  return(-1);
}

// inizializzazione coda di trasmissione
pout.que=c_ut_tx;
pout.wto=0;
pout.flg=MSG_WAIT;
pout.lmsg=sizeof(SM_CONFIG);
pout.amsg=(char*)&mout;

// inizializzazione coda di ricezione
pin.que=c_ut_rx;
pin.flg=MSG_WAIT;
pin.wto=0;
pin.amsg=(char *)rc;

/*
   preparazione e invio messaggio punti
*/
mout.hea.nodo=0;
mout.hea.mess=CONFIG;
mout.tipopunti=(long)tipo;

DACAPO:
offset=0L;
rbyte(fileno(fp),&hea,(long)offset,SVINHEA_L);
offset=offset+SVINHEA_L;
if(hea.numpunti%NUMREC)
   mout.lastpack=(long)(hea.numpunti/NUMREC);
else
   mout.lastpack=(long)((hea.numpunti/NUMREC)-1);
//printf("\ntipo:%d, num:%d, packs:%ld",tipo,hea.numpunti,mout.lastpack);

for (j=0;j<hea.numpunti;)
{
   mout.indpack=(long)(j/NUMREC);
   for (i=0;i<NUMREC  && j<hea.numpunti;)
   {
   char *app;
      rbyte(fileno(fp),&recsvin,(long)offset,SVINREC_L);
      app = (char *)&(recsvin.punt);
      memset(&app[2],0,2);
      offset=offset+SVINREC_L;
      if (recsvin.punt!=(long)-1)   // punto installato
      {
         memcpy(&mout.rec[i],&recsvin,SVINREC_L);
         j++;
         i++;
      }
   }
   mout.numpunti=(long)i;
   // trasmissione 
   enqueue(&pout);
   // ricezione ACK o NACK
	dequeue(&pin);       // scodamento
   if(rc->tipo==NOCFG) goto DACAPO;
//   _visch('g');
}
fclose(fp);
return(0);
}




#if defined OSF1 || defined LINUX
#undef long
#define  long long
#endif
