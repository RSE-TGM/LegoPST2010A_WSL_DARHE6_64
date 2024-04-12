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
#include "mesest.inc"
#include "diaginet.inc"

float contarm[max_cn];           // valori contatori per verificare 
                                 // se il nodo ha inviato almeno
                                 // un messaggio

gesarm(azione, nodo, num)
short azione, nodo, num;
{
short i;
switch(azione)
{
case cn_reset:					//	reset contatori
	for(i=0;i<max_cn*2;i++)
			dbadv[cnta01+i]=0.0;
break;
case cn_incra:        		// incremento contatore 
	dbadv[cnta01+nodo]=dbadv[cnta01+nodo]+num;
break;
case cn_incrb:        		// incremento contatore 
	dbadv[cntb01+nodo]=dbadv[cntb01+nodo]+num;
break;
}
return(0);
}
 
