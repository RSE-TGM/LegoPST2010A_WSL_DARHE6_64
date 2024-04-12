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

   La funzione esamina il pacchetto mdanas ed inserisce tutti
   i valori nel data base
   
   Parametri:

   n_punti     short    n. punti da esaminare
   armadio     short    n. dell'armadio 
	an				S_DTAA_SEPA * primo elemento del messaggio
   
   24 Feb. 1992      Rel. 0.01   Fc
   24 Ott. 1994      Rel. 0.02
      Correzione gestione FA
*/
#include "pscs.cfg"
#include "g1tipdb.inc" 
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "tipal.inc"				
#include "pscserr.inc"
#include "sepdati.inc"
#include "dconf.inc"

extern short debsamp;		// flag per emissione non attendibilita'
extern DB_HEADER h_db;

#define MASKFLAGMESS		0xE000		// maschera per messaggio

setaac (n_punti,armadio,an)
short n_punti;
short armadio;
S_DTAA_SEPA *an;
{
short i,k,j;
S_MALLA mess ;
QUEUE_PACKET pack;
short trat;
short *pdbaaf;				// flag logici
char *pdbaafa;				// flag fisici
short point;
char  coef_k;				// indice tabella coefficienti K
char flagaa, flagaaold;	// flag acquisizione fisici
char all_acaa[3]={range_al,range_ba,ch_fser};

//printf("\n n_punti %d armadio %d ",n_punti,armadio);

for(j=0;j<n_punti;j++,an++ )
{
   flagaa= (an->point & MASKFLAGMESS) >> 13 ;
	point=an->point & (~MASKFLAGMESS);
	if(point < 1 || point > heafsvar[armadio].l_punto)
	{
//	      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETAA1,point,SYS_CONT);
			continue;
	}
   point=*(svinarp[armadio]+point-1);
   if(point==-1) continue;

	if(point<0 || point >= h_db.dimaa) 
   { 
//      pscserr(ERR_TASK,TASK_ACQUI,ROU_SETAA,point,SYS_CONT);
      continue;
   }
   if(dbaau[point]==-1) continue;			// punto non installato
/*
	il valore viene inserito in data base solo se il
	punto non e` fuori scansione o forzato
*/
   pdbaaf=&dbaaf[point];

   if(((*pdbaaf) & mask_afs) || ((*pdbaaf) & mask_afz)) continue ;
/*
   preparo pacchetto per generazione allarmi
*/
	pack.que=c_visall;
	pack.amsg=(char*)&mess;
	pack.lmsg=sizeof(S_MALLA);
	pack.flg=MSG_WAIT;
	pack.wto=0;

	mess.ext=g1tipaa;

	pdbaafa=&dbaafa[point];
	coef_k=*(Kaa+point);	   									// recupero coefficiente K
   flagaaold=(*pdbaafa);					 					// memorizzo vecchi valori
   *pdbaafa=flagaa;												// aggiorno nuovi
	dbaav[point]=an->val * tab_k[coef_k];
/*
	controllo la variazione dei flag di acquisizione
*/
   flagaaold=(flagaa ^ flagaaold) ;     /* ricavo flag variati */
   if(flagaaold)		                   /* ci sono state variazioni nei */
   {				  		                   /* bit di acquisizione	  */
      mess.sogl1=-1 ;
      mess.sogl2=0 ;
      mess.punt=point ;
	   for(i=5,k=0;i<8;i++,k++)
   	{
			if(flagaaold & (1<<k)) 				// bit variato ?
		   {
				if(flagaa & (1<<k))
		      {
					mess.ertr=(trat_ac | 0x80); mess.satt=all_acaa[k]; mess.sprec=0 ;
				}
		      else
				{
					mess.ertr=trat_ac; mess.satt=0; mess.sprec=all_acaa[k];
				}
   		 	enqueue(&pack) ;
	   	}
   	}
   }
   if(flagaa) flagaa=1 ;
   if ( flagaa !=  bitvalue(pdbaaf,g2an_fa))
   {
/*
	variata la fuori attendibilita`
*/
	   bitset(pdbaaf,g2an_fa,flagaa);
/* 
   se flag debsamp = 0 non viene generato l' allarme   
*/
		if (!debsamp)	goto csetaa;
      mess.sogl1=-1 ;
      mess.sogl2=0 ;
      mess.punt=point ;
   	trat=((dbaaal[point].tr_bdm & M_LSEVA)>>6) + (dbaaal[point].tr_bdm>>12);  
	   if(flagaa){ mess.ertr=(trat | 0x80); mess.satt=non_att; mess.sprec=mis_norm ; }
   	else    { mess.ertr=trat ; mess.satt=mis_norm ; mess.sprec=non_att; }
      enqueue(&pack) ;
csetaa:
	;
   }
   verifall(point,g1tipaa) ;
}
}

