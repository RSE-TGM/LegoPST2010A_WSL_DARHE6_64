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
	Gesarm.c

	La funzione monitorizza il numero di messaggi ricevuti da
	scada sulla rete
	Utilizza i contatori di diagnostica contarm0 ...

	Parametri
   
   azione   short cn_incra  incrementa contatore rete A
						cn_incrb	 incrementa contatore rete B
                  cn_test  testa se arrivati messaggi,
                  cn_reset memorizza in data base vnodi e lo annulla
   nodo     n. armadio da 0 a n_tot_nodi/3  se cn_incr
            oppure -1 se cn_test o cn_reset
   num      valore inremento

   21 Aprile 1993 Fc

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "sepdati.inc"
#include "sepdiag.inc"

float contarm[max_cn];           // valori contatori per verificare 
                                 // se il nodo ha inviato almeno
                                 // un messaggio

gesarm(azione, nodo, num)
short azione, nodo, num;
{
S_TRATG  dig;
QUEUE_PACKET pack;
short i, stato, point, nd;
float delta;
S_DBADV *dbv;						// valore contatore in data base
S_DBDD  *dbd;						// puntatore digitali di diagnostica


switch(azione)
{
case cn_reset:					//	reset contatori
	for(i=0;i<max_cn*2;i++)
			dbadv[cnta01+i]=0.0;
//			dbadv[contarm01+i]=vnodi[i];
//	memset((char*)vnodi,0,sizeof(vnodi));
break;
case cn_incra:        		// incremento contatore 
//   vnodi[nodo]=vnodi[nodo]+num;
	dbadv[cnta01+nodo]=dbadv[cnta01+nodo]+num;
break;
case cn_incrb:        		// incremento contatore 
//   vnodi[nodo]=vnodi[nodo]+num;
	dbadv[cntb01+nodo]=dbadv[cntb01+nodo]+num;
break;
case cn_test:        	   // testo se incrementato 
   pack.flg=MSG_WAIT;      // parametri comuni
   pack.wto=0;
   pack.amsg=(char*)&dig;
   pack.que=c_digor;
   pack.lmsg=sizeof(S_TRATG);

   dig.mess= mfadi ;         
   dig.ext= g1tipdd ;
   for(nd=0;nd<max_cn;nd++)
   {
/*
   contatore minore o uguale al precedente piu' 0  emetto fuori attendibilita'
   altrimenti rientro fuori attendibilita'
*/
      delta=(*dbv)-contarm[nd];
      if(delta>=0 && delta<10) stato=1;
      else stato=0;   
/*
   ad ogni nodo sono associati n_dignodi digitali di diagnostica 
   3 per rete
   li pongo tutti fuori attendibilita' eccetto il modo di
   funzionamento (terzo punto)
*/
      point=staper0a+nd*n_dignodi;
		dbd=&dbdd[point];
      for(i=0;i<n_dignodi-1;i++,point++,dbd++)
      {
/*
   se il digitale e' off line non lo considero
*/
         if((*dbd) & mask_sl)  continue;
/*
   metto la fuori attendibilita' del punto nel nuovo stato
   verificando che non lo sia gia'
*/
         if(bitvalue(dbd,g2di_fa) != stato)
         {
            bitset(dbd,g2di_fa,stato);
            dig.indice=point;
            dig.stato=stato;
            enqueue(&pack);
         }
      }
      contarm[nd]=*dbv;
   }
break;
}
return(0);
}
 
