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
   Setaac.c

   La funzione esamina il pacchetto mdana ed inserisce tutti
   i valori nel data base
   
   Parametri:

   n_punti     short    n. punti da esaminare
   
   24 Feb. 1992      Rel. 0.01   Fc

   20 Gennaio 1993
   Inserimento livelli di severita'

*/
#include <stdio.h>

#include "dconf.inc"
#include "g1tipdb.inc" 
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"
#include "messcada.inc"
#include "tipal.inc"				
#include "acqui.inc"
#include "pscserr.inc"

	extern short debsamp;		// flag per emissione non attendibilita'
	#define MASKFLAG		0x0000001F
	#define MASKVAL		0xFFFFFFE0

extern DB_HEADER h_db;

setaac (n_punti)
short n_punti;
{
union f_i valore ;
short i, k, flagold, flag ;
S_MALLA mess ;
QUEUE_PACKET pack;
short trat;
short *pdbaaf;
S_DTAA *an;
short point;

/*
   preparo pacchetto per generazione allarmi
*/
pack.que=c_visall;
pack.amsg=(char*)&mess;
pack.lmsg=sizeof(S_MALLA);
pack.flg=MSG_WAIT;
pack.wto=0;

mess.ext=g1tipaa;

an=&ac.u.m_dana.dati[0];      // primo elemento del messaggio

for(k=0;k<n_punti;k++,an++ )
{
   point=an->point;
   if(point<0 || point >=h_db.dimaa) 
   { 
      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETAA,point,SYS_CONT);
      continue;
   }
   if(dbaau[point]==-1) continue;			// punto non installato
/*
	il valore viene inserito in data base solo se il
	punto non e` fuori scansione o forzato
*/
   pdbaaf=&dbaaf[point];

   if(((*pdbaaf) & mask_afs) || ((*pdbaaf) & mask_afz)) continue ;

   flag= an->val.l & MASKFLAG ;

   valore.l= an->val.l & MASKVAL ;
   dbaav[point]=valore.f ;
   flagold=dbaafa[point];
   dbaafa[point]=flag ;
   
   if (debsamp) 
   {
/*
	controllo la variazione dei flag di acquisizione
*/
   flagold=(flag ^ flagold) ;           /* ricavo flag variati */
   if(flagold)			                   /* ci sono state variazioni nei */
   {				  		                   /* bit di acquisizione	  */
      mess.sogl1=-1 ;
      mess.sogl2=0 ;
      mess.punt=point ;

	   for(i=0;i<5;i++)
   	{	if(bitvalue(&flagold,(15-i)))
		   { if(bitvalue(&flag,(15-i)) )
		      {mess.ertr=(trat_ac | 0x80); mess.satt=all_ac[i]; mess.sprec=0 ;}
		      else { mess.ertr=trat_ac; mess.satt=0; mess.sprec=all_ac[i]; }
   		  enqueue(&pack) ;
	   	}
   	}
   }
   }
   if(flag) flag=1 ;
   if ( flag != bitvalue(pdbaaf,g2an_fa))
   {
/*
	variata la fuori attendibilita`
*/
	   bitset(pdbaaf,g2an_fa,flag);
/* 
   se flag debsamp = 0 non viene generato l' allarme   
*/

		if (!debsamp)	goto csetaa;

      mess.sogl1=-1 ;
      mess.sogl2=0 ;
      mess.punt=point ;
   	trat=((dbaaal[point].tr_bdm & M_LSEVA)>>6) + (dbaaal[point].tr_bdm>>12);  
	   if(flag){ mess.ertr=(trat | 0x80); mess.satt=non_att; mess.sprec=mis_norm ; }
   	else    { mess.ertr=trat ; mess.satt=mis_norm ; mess.sprec=non_att; }
      enqueue(&pack) ;
csetaa:
	;
   }
   verifall(point,g1tipaa) ;
}
}

