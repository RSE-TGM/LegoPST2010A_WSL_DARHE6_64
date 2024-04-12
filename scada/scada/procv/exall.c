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
/*-> exall

   Aggiorna la word di flag per i punti analogici.
	Il modulo exall verifica se la misura ha soglie.
   In caso contrario esamina la word di flag generando
   gli allarmi opportuni.
   Utilizza la funzione statoall per determinare lo stato della
   misura prima dell'emissione della segnalazione di allarme
   (Statoall e' definita nel modulo verifall)

   Parametri
   	punt	short in puntatore in data base del punto
      tipo  short tipo del punto
      all   S_DBALL* data base allarmi
      flag  short* flag attuale data base
      exfl  short nuovi flag

   Ritorno
      0     generate le soglie
      1     verificare le soglie degli allarmi su SCADA

   28 Febbraio 1995

*/
#include <math.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "mesqueue.h"

extern short c_visall;

exall(punt,tipo,all,pflag, exfl)
short punt, tipo, exfl;
short *pflag;
S_DBALL* all;
{
short flag;
QUEUE_PACKET pack;
S_MALLA mess ;
static short verin[4]={mask_adh,mask_adl,mask_adh,mask_adl} ;   /* inibizioni */
static short verfl[4]={mask_ahs,mask_als,mask_ahc,mask_alc} ; /* allarmi */
char trat;
short i ;
short mask, maskRI;
short stato;

mask=mask_ahc+mask_ahs+mask_als+mask_alc+mask_adh+mask_adl;
maskRI=mask_ahc+mask_ahs+mask_als+mask_alc+mask_adh+mask_adl+mask_ari;
/*
   verifico che il punto abbia associato soglie di allarme
   in tal caso memorizzo tutti i flag eccetto i bit di
   allarme e di inibizione
*/
if((all->alto_sic.cval[0]!=-2) || (all->alto_con.cval[0]!=-2) &&
   (all->bass_sic.cval[0]!=-2) || (all->bass_con.cval[0]!=-2))
{
   *pflag=((*pflag) & maskRI) | (exfl & (~maskRI));     
   return(1);
}
/*
   nessuna soglia associata: verifico le variazioni sui flag
   HC, HS, LS, LC se non sono inibiti
*/
if(((*pflag) & mask) == (exfl & mask))
{
   *pflag=((*pflag) & mask_ari) | (exfl & (~mask_ari));      // copio i flag salvando il bit di RI
   return(0);    // nessuna variazione sulle soglie
}

pack.que = c_visall;                // preparo pacchetto per allarme
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &mess;
pack.lmsg=sizeof(S_MALLA);
mess.ext=tipo;
mess.punt=punt;
trat=((all->tr_bdm & M_LSEVA)>>6) + (all->tr_bdm>>12);  // trattamento
flag=*pflag;
/*
   verifico variazione inibizione
*/
stato=exfl & mask_adh;
if((flag & mask_adh) != stato)
{
   if(stato) stato=1;
   inibiz(tipo,punt,g2in_al,stato);
}
stato=exfl & mask_adl;
if((flag & mask_adh) != stato)
{
   if(stato) stato=1;
   inibiz(tipo,punt,g2in_ba,stato);
}
/*
      l'allarme di emissione o di rientro deve essere emesso se
      l'inibizione=0 ed il flag e' variato
*/
for(i=0;i<4;i++)
{
   stato=exfl & verfl[i];
   if((flag & verfl[i]) != stato)
   {
      if(stato) stato=1;
   	if(!(exfl & verin[i]))      // allarmi inibiti ?
      {
         if(stato)                // emissione
         {
            mess.ertr=trat | 0x80;
        		mess.satt=all_an[i];
	         mess.sprec=statoall(&flag);
     		   mess.sogl1=-1;
   	      mess.sogl2=0;
         }
         else                      // rientro
         {
            mess.ertr=trat;
        		mess.sprec=all_an[i];
	         mess.satt=statoall(&exfl);
     	   	mess.sogl1=-1;
	         mess.sogl2=0;
         }
     		enqueue(&pack);
      }
	}
}
*pflag=((*pflag) & mask_ari) | (exfl & (~mask_ari));      // copio i flag salvando il bit di RI
   
return(0);
}
