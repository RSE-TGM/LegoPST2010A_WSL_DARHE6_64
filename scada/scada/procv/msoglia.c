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
        la function msoglia modifica il valore di una soglia
		  di allarme verificando la congruenza con le altre
		  soglie fisse

        punt   short puntatore della misura
        ext    char  estensione della misura
        soglia char  n. della soglia limite di allarme
        funz   short tipo di funzione (forzamento, modifica valori)

		  la funzione ritorna 0 se il nuovo limite e' accettabile
		  altrimenti -1
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
//#include "diagnodi.inc"
#include "diagnoan.inc"
#include "tipal.inc"
#include "allar.inc"

msoglia(valore,punt,ext,soglia,funz)
short punt;
char ext,soglia;
float valore;
short funz;
{
struct allarmi *all, new_all ;   // puntatore tabella allarme 		 
short *flag;                     // flag misura di cui modificare l'allarme
union valin *val;
QUEUE_PACKET  packs;              // pacchetto per stampe
S_STALL mess;
short ind_all;							// indice soglia modificata

/*
        seleziono il puntatore alla soglia
        di allarme
*/
switch (ext)
{
case g1tipaa :
        all= & dbaaal[punt] ;
        flag= &dbaaf[punt];
        break;
case g1tipas :
        all= & dbasal[punt] ;
        flag= &dbasf[punt];
        break;
case g1tipac :
        all= & dbacal[punt] ;
        flag= &dbacf[punt];
        break;
case g1tipad :
        all= & dbadal[punt] ;
        flag= &dbadf[punt];
        break;
default: return(errtip);
}
memcpy(&new_all,all,sizeof(new_all));
/*
        in base alla soglia individuo
        il valore dell`allarme
*/
switch (soglia)
{
case g1tiphs :
        val=&new_all.alto_sic;
	  	  ind_all=mod_hs;
        break;
case g1tipls :
        val=&new_all.bass_sic;
	  	  ind_all=mod_ls;
        break;
case g1tiphc :
        val=&new_all.alto_con;
	  	  ind_all=mod_hc;
        break;
case g1tiplc :
        val=&new_all.bass_con;
	  	  ind_all=mod_lc;
        break;
default :
        return(errso);
}
/*
		  la modifica e' permessa solo per soglie a cui e' associato
		  un valore floating o se la soglia non esiste
*/
switch (val->cval[0])
{
	case -1:
/*
        se la soglia e` una misura la modifica non e' possibile
*/
	 return(errso);
	 break;
	 case -2:
/*
	caso di soglia non esistente la inserisco
*/
      mess.al.vrif.c[0]=-1;
		val->fval=valore;
		break;
	default:
/*
	caso di soglia gia' presente in formato floating
*/
      mess.al.vrif.f=val->fval;
		val->fval=valore;
		break;
}
/*
	eseguo il controllo sulle soglie di allarme 
*/
if(contr_all(&new_all)) return(errso);
/*
   eseguo le operazioni in base al tipo di funzione
*/
switch (funz)
{
	case f_mvaf :                 /* modif.valori e flag 				*/
	case f_mval :                 /* modif. solo valori 				*/
      memcpy(all,&new_all,sizeof(new_all));
      break;
   case f_forz :						/* forzamento soglia   				*/
/*
	preparo pacchetto per stampa e accodo
*/	
		packs.que = c_stamp;
		packs.flg = MSG_WAIT;			 
		packs.wto = 0;					  
		packs.amsg = (char *)  &mess;
		packs.lmsg=sizeof(S_STALL);

		mess.mess=mstal;                     /* codice messaggio             */
		mess.al.ertr=0x80;                   /* emissione trattamento        */
		mess.al.ext=ext ;                    /* estensione                   */
		mess.al.punt=punt ;                  /* puntatore                    */
		mess.al.sprec=mis_norm;              /* stato precedente             */

		if(dbadv[db_anno]>=2000)
				mess.anno=dbadv[db_anno]-2000;
		else	mess.anno=dbadv[db_anno]-1900;

		mess.mese= dbadv[db_mese];
		mess.gior= dbadv[db_giorno];
		mess.ora = dbadv[db_ora];
		mess.min = dbadv[db_minuti];
		mess.sec = dbadv[db_secondi];

      bitset(flag,g2an_al,1);    	/* flag allarmi variati          */
      mess.al.satt = ind_all;
      memcpy(all,&new_all,sizeof(new_all));
      mess.al.vatt.f=valore;
      enqueue(&packs);
      break;
}   
return(0) ;
}
/*
	controllo che i nuovi limiti di allarme siano accettabili
	in riferimento a quelli gia' presenti
*/
contr_all(all)
S_DBALL *all;
{
short num, i;
float val[4];

num=0;
if(all->bass_sic.cval[0]!=-1 && all->bass_sic.cval[0]!=-2)
{  val[num]=all->bass_sic.fval; num++; }
if(all->bass_con.cval[0]!=-1 && all->bass_con.cval[0]!=-2)
{  val[num]=all->bass_con.fval; num++; }
if(all->alto_con.cval[0]!=-1 && all->alto_con.cval[0]!=-2)
{  val[num]=all->alto_con.fval; num++; }
if(all->alto_sic.cval[0]!=-1 && all->alto_sic.cval[0]!=-2)
{  val[num]=all->alto_sic.fval; num++; }
/*
   ciclo di controllo
*/
for(i=0;i<num-1;i++)
{
     if(val[i]>=val[i+1]) return(1);
}
return(0);
}
