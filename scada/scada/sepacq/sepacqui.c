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
	SepAcqui

	Il task acqui gestisce l'acquisizone da armadi di tipo Sepa.
	I tipi di messaggi gestiti sono definiti nel file di include
	SepMess.inc.

	Parametri

	nessuno

	Errori
	Segnala eventuali messaggi sconosciuti

	19 Aprile 1993

   13 Febbraio 1995
      Inserimento gestione buffer suddivisi per gruppo di impianto

*/
#include <dos.h>
#include <time.h>

#include "pscs.cfg"
#include "comunic.inc"
#include "g2comdb.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "pscserr.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "sepdati.inc"     // qui extern, public in alldef.c
#include "switch.inc"

/*
		  Union possibili messaggi da acquisizione:
*/
typedef union messaggi_acqui {
						  	S_STRETE 	 m_rete ;
							S_DANA_SEPA  m_dana ;
							S_DDIG_SEPA  m_ddig ;
							S_MDTIME		 time;
							S_VARETE		 m_varete;
							S_MRCE		 m_rce;
                              } U_MESS;
/*
        Struct messaggi con header per invio al sistema
        slave
*/
struct s_mess {
				short  mess;
  				U_MESS u;
					} ac;

extern short coefmese[];

acqui() 
{

	short i, punti, armadio, point ;
	QUEUE_PACKET pack;

	QUEUE_PACKET  slpack;
   struct tm timepc;  //data PC
   struct tm timesepa; //data SEPA
	short anno, giorno, mese;
	char inc;
	S_VANODO *pvanodo;
	S_RCE *prce;
	S_SEPNODI *psnodi;
   char *arm;
   short nGroup;

	slpack.que = c_dua_tx;
	slpack.flg = MSG_NOWAIT;
	slpack.wto = 0;
	slpack.amsg=(char *) & ac;

	pack.que=c_ut_rx;
	pack.flg=MSG_WAIT;
	pack.wto=0;
	pack.amsg=(char *)&ac.u;

	sepabil();							// abilitazione nodi rete
	if(RceInit()==-1) pscserr(ERR_MEM,TASK_ACQUI,ROU_RCE,0,SYS_HALT);

	while(1)
	{
		inv_slave=0;
		dequeue(&pack);
		switch(ac.u.m_dana.hea.mess)
		{
       // richiesta aggiornamento slave
         case  SL_AGG_ACQ:
            if (SYS_DUALE)
               aggsl(&ac,sizeof(ac));
         break;
/*
	acquisizione analogici
*/
			case mdanas :
				armadio=((ac.u.m_dana.hea.addr_nodo & MaskNodo) -nodo_armadi)/2;
				if(!svinarp[armadio]) break;
				inv_slave=1;
				punti=(pack.lmsg-sizeof(HEASCA))/sizeof(S_DTAA_SEPA);
				if(ac.u.m_dana.hea.addr_nodo & MaskReteA) inc=cn_incra;
				else inc=cn_incrb;
            gesarm(inc,armadio,punti);
            setaac(punti,armadio,&ac.u.m_dana.dati[0]);
			break ;
/*
	acquisizione digitali
*/
			case mddig :
				armadio=((ac.u.m_dana.hea.addr_nodo & MaskNodo) -nodo_armadi)/2;
				if(!svinarp[armadio]) break;
				punti=(pack.lmsg-sizeof(HEASCA))/sizeof(short);
				if(ac.u.m_dana.hea.addr_nodo & MaskReteA) inc=cn_incra;
				else inc=cn_incrb;
            gesarm(inc,armadio,punti);
            setdic(punti,armadio,&ac.u.m_ddig.dig_val[0]);
		   break ;
/*
	stato rete
*/
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
/*
	data e ora da armadi Sepa, la data non viene considerata se invalida
*/
			case mdtime:
				if((snodi[ac.u.time.hea.addr_nodo].Fa=ac.u.time.valida))
						break;				// data non valida
				inv_slave=1;

            // inizializzo data e ora PC
            timepc.tm_mday=dbadv[db_giorno];
            timepc.tm_mon=dbadv[db_mese]-1;
            timepc.tm_year=dbadv[db_anno]-1900;
            timepc.tm_hour=dbadv[db_ora];
         	timepc.tm_min=dbadv[db_minuti];
         	timepc.tm_sec=dbadv[db_secondi];
         	timepc.tm_wday=0;
         	timepc.tm_yday=0;
         	timepc.tm_isdst=-1;
            // inizializzo data e ora SEPA
				anno=dbadv[db_anno];
				giorno=ac.u.time.giorno;
				decgio(&giorno,&mese,anno);
         	timesepa.tm_mday=giorno;
         	timesepa.tm_mon=mese-1;
         	timesepa.tm_year=anno-1900;
         	timesepa.tm_hour=ac.u.time.ora;
         	timesepa.tm_min=ac.u.time.minuti;
         	timesepa.tm_sec=ac.u.time.secondi;
         	timesepa.tm_wday=0;
         	timesepa.tm_yday=0;
         	timesepa.tm_isdst=-1;
            //setta la data del PC come quella della SEPA 
         	setdata (&timepc,&timesepa);
			break;
			case mdrce:					// gestione messaggio Rce
				inv_slave=1;
				armadio=((ac.u.m_dana.hea.addr_nodo & MaskNodo) -nodo_armadi)/2;
				punti=(pack.lmsg-sizeof(HEASCA))/sizeof(S_RCE);
//				printf("\n arm %d punti %d", armadio,punti);
				if(punti)
					{
						RceIns(&ac.u.m_rce.m,punti,armadio);
						snodi[ac.u.m_rce.hea.addr_nodo & MaskNodo].Rce=1;	// rce in corso
					}
				else				// chiusura Rce verifico per tutti i nodi
					{
						snodi[ac.u.m_rce.hea.addr_nodo & MaskNodo].Rce=0;
                  nGroup=snodi[ac.u.m_rce.hea.addr_nodo & MaskNodo].Group;  // gruppo appartenenza
//   printf("\n chius. gruppo %d \n",nGroup);
						arm=&bGroupAcq[nGroup].arm[0];
						for(i=0;i<max_zone;i++,arm++)
                  {
                     if((*arm)==-1) break;
//      printf("\n arm %d ",*arm);
      					if(snodi[nodo_armadi+(*arm)*2].Rce) break; // non conclusa
      					if(snodi[nodo_armadi+(*arm)*2+1].Rce) break;   // non conclusa
                  }
//     printf("\n");
						if(i==max_zone || ((*arm)==-1))
						{
						 	RceIns(&ac.u.m_rce.m,0,armadio); 	// conclusa richiedo stampa
                     bGroupAcq[nGroup].Rce_timeout=0;	   // fine RCE
						}
					}
			break;
			default:
            pscserr(ERR_TASK,TASK_ACQUI,ROU_ACQUI,ac.u.m_dana.hea.mess,SYS_CONT);
			break;
		}
if(SYS_DUALE)
   {
/*
	se il sistema e' duale e sono master e lo slave e'	aggiornato
	devo accodare allo slave tutti i messaggi che ricevo eccetto
	lo stato rete e la richiesta di aggiornamento
*/
		if(inv_slave && sys_master && bitvalue(&dbdd[slaveagg],g2di_sl))
		{
	   	ac.mess=MSG_ACQUI;	  						// medesimo messaggio
			slpack.lmsg=pack.lmsg+sizeof(ac.mess);
			enqueue(&slpack);
		}
   }
	}
}
/* 
   Creazione : Luglio 1993 - Rel. 1.0 - R.L.

	DecGio
	Traduce il giorno dell'anno in:
		-	giorno del mese
		-	mese

*/
decgio (giorno,mese,anno)
short *giorno,*mese,anno;
{
short inc;

inc=0;
*giorno=*giorno-1;
for(*mese=1;*mese<12;(*mese)++)
{
	if( (*mese) == 2 &&  // da Febbraio possibile incremento
		(!(anno % 4) && (anno % 100) || !(anno % 400))) inc=1;
	if((*giorno)<(coefmese[*mese]+inc)) break;
}
if (*mese<=2)
   *giorno=*giorno-(coefmese[(*mese)-1])+1;
else
   *giorno=*giorno-(coefmese[(*mese)-1]+inc)+1;

return(0);
}


