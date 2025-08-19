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
   exfa
      Confronta il data base di sistema attuale con la word
      di flag passata come parametro. Se il flag FA e' variato
      genera il messaggio malla per analogici e mtrdi o mfadi
      per punti digitali

   Parametri
      short    ext   tipo di punto
      short    punt  indice in data base di sistema
      S_DBALL* all   puntatore data base allarme
                     (e' significativo solo per gli analogici)
      short*   flag  puntatore ai flag attuali
      short    exfl  word di flag

   Ritorno
      nessuno

      03 Marzo 1995 Fc

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "mesqueue.h"

/* Function prototypes */
extern void bitset(short *, short, short);

extern short c_visall;
extern short debsamp;		// flag per emissione non attendibilita'

void exfa(punt,tipo, all, flag, exfl)
short punt, tipo, exfl;
short *flag;
S_DBALL* all;
{
   QUEUE_PACKET pack;
   S_TRATG mess;
   S_MALLA malla;
   short trat;
   short stato;
   stato=exfl & mask_afa;

   if(stato != (*flag & mask_afa))
   {
      if(!stato) bitset(flag,g2an_fa,0);     // aggiorno data base
      else bitset(flag,g2an_fa,1);
      if(tipo<g1tipda && (!debsamp)) return;    // analogico non abilitata la generazione FA

      pack.flg=MSG_WAIT;
      pack.wto=0;
      if(tipo <g1tipda)    // analogico
      {
         pack.que=c_visall;
         pack.amsg=(char*)&malla;
         pack.lmsg=sizeof(S_MALLA);
         malla.ext=tipo;
         malla.sogl1=-1 ;
         malla.sogl2=0 ;
         malla.punt=punt ;
      	trat=((all->tr_bdm & M_LSEVA)>>6) + (all->tr_bdm>>12);  
   	   if(stato){ malla.ertr=(trat | 0x80); malla.satt=non_att; malla.sprec=mis_norm ; }
      	else    { malla.ertr=trat ; malla.satt=mis_norm ; malla.sprec=non_att; }
      }
      else              // digitale
      {
         pack.que=c_digor;
         pack.amsg=(char*)&mess;
         pack.lmsg=sizeof(S_TRATG);
         mess.ext= tipo;
         mess.indice= punt ;
		   if (!debsamp)	mess.mess=mtrdi;  // generazione allarme
         else mess.mess= mfadi ;               // solo trattamento
         if(stato) mess.stato= 1;
         else	mess.stato= 0;
      }
      enqueue(&pack);
   }
}

