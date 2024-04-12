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
/*-> stampe

        il task stampe legge dalla coda c_stp
        messaggi di :

        -       stampa allarmi
        -       stampa archivio allarmi
        -       stampa tabulati (lo rimanda al task tabul)
        -       stop tabulati
        -       variazione strategia di fail over ]

	Revisioni :  28.05.92  -  GM Furlan
                Routine gestisce anche lo skip della pagina
                del libro giornale al cambio di data

                20.10.94  - Fc
               Per Selta gestione libro giornale con formato diverso
               (inserita routine Printalt)

               10 Novembre 1994
               Inserita gestione messaggio masc (stampa stringa ASCII su
               libro giornale)

               15 Giugno 1995
               Inizializzazione campo szvir per stampa "allarmi persi in
               stampa" e stringa da utente

               19 Giugno 1995
               Inserita routine resetlbg per poter gestire le stampanti
               virtuali  

               11 Settembre 1995
               Chiusura settimanale libro giornale
*/

#include <stdio.h>
#include <dos.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "mesqueue.h"
#include "diagnodi.inc"
#include "diagnoan.inc"
#ifdef AC_SIMULATORE
   #include "simdia.inc"
#endif
#include "pscserr.inc"
#include "dconf.inc"

extern DB_HEADER h_db;				// header data base

stampe()	          
{
/*
        tipo di stampe che possono essere presenti nella coda
*/
union u_messaggi { S_STALL  al;
                   S_STALS  as;
                   S_STAR   ar;
                   S_STAB   ta;
						 S_INAR   in;
						 S_STELEN el;
                   S_STALLT  te;
						 S_STSTR  st;		// stampa stringa
					 } u ;
short i;

QUEUE_PACKET pack;
short tgiorno;
short tmese;
short tanno;
short anno;

S_FOSTR	fostr;

#define l_full_stampe		40
struct	{	HEA_STA hea;
				char    s[l_full_stampe]; } s_full_stampe;

pack.que = c_stamp;
pack.flg = MSG_WAIT;
pack.wto = 0;

pack.amsg = (char *)  &u;
s_full_stampe.hea.lung=sizeof(s_full_stampe);
s_full_stampe.hea.szvir=-1;
memset(s_full_stampe.s,0,l_full_stampe);
strncpy(s_full_stampe.s,"** PERSI ALLARMI IN STAMPA ** \r\n",l_full_stampe);

tgiorno=0;   tmese=0;  tanno=0;


n_allfile=0; 				  					// indice file da utilizzare
byte_allfile=0;							  	// n. byte scritti

INIZIO:
	
	if(full_stampe) pack.flg=MSG_NOWAIT;
	if(dequeue(&pack))                           // coda vuota
   {
			full_stampe=0;								// reset flag
			invia(tpr_allarme,&s_full_stampe);	// invio stringa segnalazione
			pack.flg=MSG_WAIT;						// ripristino attesa	infinita
   }

	/* test cambio data per segnalazione stampa intestaz per allarmi */
   if(tgiorno!=dbadv[db_giorno] || tmese!=dbadv[db_mese] || tanno!=dbadv[db_anno])
   {
      i_day=0;
      tgiorno=dbadv[db_giorno];
      tmese=dbadv[db_mese];
      tanno=dbadv[db_anno];
   }

   switch (u.al.mess)
		     {
			     case mstal :            /* stampa allarmi normali       */
#ifdef AC_SIMULATORE
// nel caso di simulatore, stop del libro giornale negli stati di BACKTRACK e REPLAY
               if (!bitvalue(&dbdd[sscbktk],g2di_sl) || 
                   !bitvalue(&dbdd[sscreplay],g2di_sl) )  break;
#endif

/*                
        se e` settato il flag di fine giorno resetto il
        numero di righe per il salto pagina
		  chiudo il file in corso per la scrittura del libro
		  giornale
*/
					if(!i_day)
					{
						i_day=1;
                  if(RESET_LBGSETT)
                  {
                     if(dbadv[db_gioset]==1) resetlbg();
                  }
                  else resetlbg();
					 }
if (!strcmp(h_db.nome,"SELTA"))
{
                if(pack.lmsg!=sizeof(S_STALLT)) u.te.t.dd=-1;
	             printalt(&u) ;
}
else
	             printal(&u) ;
	             break ;
		  	 case mstar:
				 	 switch (u.ar.flag)
					 {
					 	case	mstar_f:		  /* fine trasmissione		  */
							invia(tpr_reset,0);
  							break;
						case  mstar_a:			/* allarmi da riconoscere	*/
						case  mstar_r:			/* allarmi in archivio		*/
						  	printar(&u);
						 	break;
				    }
				 	 break;
			  case minar:					 
					 infotesta[0]=u.in.pagina;
					 infotesta[1]=u.in.archivio;
					 break;
			  case minel:
				 	 switch (u.el.flag)
					 {
					 	case	ELE_FINE:		  /* fine trasmissione		  */
							invia(tpr_reset,0);
  							break;
						default:					 /* salvo parametri per intestazione */
						   infotesta[0]=u.el.flag;
							infotesta[1]=u.el.ext;
						  	printele(&u);
					 }
				  	 break;
			 case mmasc :            /* stampa stringa da utente     */
					 memset(&fostr,' ',sizeof(S_FOSTR));
					 fostr.hea.lung=sizeof(S_FOSTR);
					 fostr.hea.szvir=0;
					 if(dbadv[db_anno]>=2000)	anno=dbadv[db_anno]-2000;
					 else 				 			anno=dbadv[db_anno]-1900;
					 decnum(fostr.gior,2,-1,(short)dbadv[db_giorno],0.) ;					
					 decnum(fostr.mese,2,-1,(short)dbadv[db_mese],0.) ;
					 decnum(fostr.anno,2,-1,anno,0.);
					 decnum(fostr.ora ,2,-1,(short)dbadv[db_ora],0. ) ;
					 decnum(fostr.min ,2,-1,(short)dbadv[db_minuti],0.);
					 decnum(fostr.sec ,2,-1,(short)dbadv[db_secondi],0. ) ;
					 fostr.sep_1='-';
					 fostr.sep_2='-' ;
					 fostr.sep_3=':' ;
					 fostr.sep_4=':' ;
					 strncpy(fostr.message, u.st.message, lfostr);
					 invia(tpr_stringa,&fostr);
                invia(tpr_reset,&fostr);
					 break;
				default:
		          pscserr(ERR_TASK,TASK_STAMPE,ROU_STAMPE,u.al.mess,SYS_CONT);
		          break;
		     }
	goto INIZIO;
}




							
