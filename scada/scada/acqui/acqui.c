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
/*  acqui

	il task acqui gestisce l'acquisizone da front end
	dei punti analogici e digitali distingue
   tra messaggi spontanei e su richiesta 

*/

#include <stdio.h>

#include "pscs.cfg"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesest.inc"
#include "messcada.inc"
#include "mesqueue.h"
#include "diagnodi.inc"
#include "aggsis.inc"
#include "dconf.inc"
#include "diagnoan.inc"

extern DB_HEADER h_db;

#define _PUBLIC 0

#include "acqui.inc"
#include "pscserr.inc"


#if defined (STAR_SDI)              // comunicazione con star tipo sdi
   extern S_DESINET st_nodi_inet[];
#endif
/*
   flag di abilitazione invio messaggio allo slave
*/
extern short inv_slave;    // extern perchä definito in sepdati.inc
                            // incluso _PUBLIC in alldef.c 
acqui()
	{

	short i, punti, point ;
   QUEUE_PACKET pack;
	S_VANODO *pvanodo;

   short armadio, inc;

	QUEUE_PACKET  slpack;
#if defined (AC_INETDUALE)
	struct agg_mess { short  addr_nodo;
		 			 RX_STATO386 mess; }	agg;
	QUEUE_PACKET packagg;
#endif

if (SYS_DUALE)
   {
	slpack.que = c_dua_tx;
	slpack.flg = MSG_NOWAIT;
	slpack.wto = 0;
	slpack.amsg=(char *) & ac;
   }

	pack.que=c_ut_rx;     
	pack.flg=MSG_WAIT;
	pack.wto=0;
	pack.amsg=(char *)&ac.u;

#if defined (AC_INETDUALE)
/*
	in caso di acquisizione inet invio mediante la routine
	invnodi la configurazione della rete e metto off line
	la locazione corrispondente allo stato della config
*/
 	invnodi();
#endif

	while(1)
		{
 		dequeue(&pack);
      
      inv_slave=0;            // flag invio allo slave

#if defined (AC_SIMU)
#else
		switch(ac.u.m_dana.hea.mess)
			{
         case  SL_AGG_ACQ:
            if (SYS_DUALE)       // richiesta aggiornamento slave
               aggsl(&ac,sizeof(ac));
            break;
			case mdana :
            if (SYS_DUALE)       // richiesta aggiornamento slave
               inv_slave=1;
/*
	acquisizione analogici
*/
				punti=(pack.lmsg-sizeof(HEASCA))/sizeof(S_DTAA);
   #if defined (AC_INETDUALE)
				armadio=((ac.u.m_dana.hea.addr_nodo & MaskNodo) -nodo_armadi)/2;
				if(ac.u.m_dana.hea.addr_nodo & MaskReteA) inc=cn_incra;
				else inc=cn_incrb;
            gesarm(inc,armadio,punti);
   #endif
            setaac(punti);
			break ;

			case mddig :
/*
	acquisizione digitali
*/
				punti=(pack.lmsg-sizeof(HEASCA)-sizeof(ac.u.m_ddig.secondo))/sizeof(short);
   #if defined (AC_INETDUALE)
				armadio=((ac.u.m_dana.hea.addr_nodo & MaskNodo) -nodo_armadi)/2;
				if(ac.u.m_dana.hea.addr_nodo & MaskReteA) inc=cn_incra;
				else inc=cn_incrb;
            gesarm(inc,armadio,punti);
   #endif
            setdic(punti);
		   break ;

			case mdcom:
				setcom(&ac.u);
				break;

   #if defined (AC_INETDUALE)
			case mstrete:
				punti=pack.lmsg-sizeof(HEASCA);
				for(i=0;i<punti;i++)
               testnodi(i,ac.u.m_rete.st_nodo[i]);
			break;
/*
	variazione stato nodo
*/
			case varete:
				punti=(pack.lmsg-sizeof(HEASCA))/sizeof(S_VANODO);
				pvanodo=&ac.u.m_varete.nodo[0];
				for(i=0;i<punti;i++,pvanodo++)
				{
					testnodi(pvanodo->ind,pvanodo->stat);
					}
			break;

   #endif
   #if defined (STAR_SDI)              // comunicazione con star tipo sdi
         case rgtcfg:
           ac.u.rev.hea.addr_nodo=ac.u.rev.hea.addr_nodo & MaskNodo; // filtro indice rete
			  if(!strncmp(ac.u.rev.release,h_db.release,6)) 
               st_nodi_inet[ac.u.rev.hea.addr_nodo].iniz=nd_con;   // gia' configurato
           else
               st_nodi_inet[ac.u.rev.hea.addr_nodo].iniz=nd_cfg;   // da configurare
         break;
   #endif

         case mclock:
            setdata(&ac.u);
         break;

			default:
            pscserr(ERR_TASK,TASK_ACQUI,ROU_ACQUI,ac.u.m_dana.hea.mess,SYS_CONT);
				break;
			}
#endif

/*
	se il sistema e' duale e sono master e lo slave e'	aggiornato
	devo accodare allo slave tutti i messaggi che ricevo eccetto
	quelli provenienti da config che esplicitamente non dichiarano
	di essere inviati allo slave
   e lo stato delle connessioni di rete
*/
      if (SYS_DUALE)
         {
	      if(inv_slave && sys_master && bitvalue(&dbdd[slaveagg],g2di_sl))
	         {
   	      ac.mess=MSG_ACQUI;
			   slpack.lmsg=pack.lmsg+sizeof(ac.mess);
		      enqueue(&slpack);
//          _visch('L');
	         }
         }

		}
	}

