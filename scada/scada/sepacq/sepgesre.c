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
	Gesrete.c

	Verifica lo stato di comunicazione del sistema con i nodi
	Sepa.
	L'attivita' ha sisgnificato solo se il sistema e' master.
	Le reti vengono dichiarate off line solo se neanche il nodo
	slave e' collegato, in questo caso, se non era avvenuta una
	precedente commutazione (vedi digitale congrete flag FZ),
	il sistema si ferma.

	Parametri
	
	nessuno

	Ritorno
	
	nessuno

	21 Aprile 1993
*/
#include "g2comdb.inc"
#include "comunic.inc"
#include "sepdati.inc"
#include "pscserr.inc"
#include "sepdiag.inc"
#include "pscserr.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"

float gio_save;
short retry_rete=0;						// n. cicli verifica stato comunicazioni
#define max_retry_rete	3

gesrete()
{
S_SEPNODI *psnodi;
short i, j;
short ncoll;
S_RCE brce;
S_GROUP_ACQ *pGroup;
char *arm;

if(!sys_master) return(0);				// sono master ?
if(gio_save != dbadv[db_giorno])		// variato il giorno ?
{
	gio_save=dbadv[db_giorno];
	gesarm(cn_reset,0,0);				// reset contatori
}
/*
	verifico time out su rce per ogni gruppo di acquisizione
*/
pGroup=&bGroupAcq[0];
for(i=0;i<max_group;i++,pGroup++)
{
   if(pGroup->Rce_timeout)
   {
//   printf("\n time out gruppo %d \n",pGroup->Rce_timeout);
   	if(!(--pGroup->Rce_timeout))					// forzo chiusura rce
		{                                         // per scatto time out
//   printf("\n scattato \n",i);
         arm=&pGroup->arm[0];
         for(j=0;j<max_zone;j++,arm++)
         {
            if((*arm)==-1) break;
//   printf("\n time out arm %d \n ",*arm);
            snodi[nodo_armadi+(*arm)*2].Rce=0;
            snodi[nodo_armadi+(*arm)*2+1].Rce=0;
         }
			RceIns(&brce,0,pGroup->arm[0]); 	// conclusa richiedo stampa
		}
   }
}
/*
	verifico il numero di nodi on line
*/
ncoll=0;
psnodi=&snodi[0];
for (i=0,ncoll=0;i<n_tot_nodi;i++,psnodi++)
{
	if(!psnodi->stato[n_digretA] || !psnodi->stato[n_digretB]) ncoll++;
}
if(ncoll>=2) 			// rete ok almeno due nodi collegati
{
   bitset(&dbdd[congrete],g2di_fz,0);
	retry_rete=0;
	return(0);
}
/*
	nessun nodo collegato neppure lo scada slave:
  	se sono in doppio (ambedue i watch dog attivi) e non
	ho gia' eseguito un reset stop del sistema
*/
if(bitvalue(&dbdd[stwda],g2di_sl) && bitvalue(&dbdd[stwdb],g2di_sl)
  && !bitvalue(&dbdd[congrete],g2di_fz) && ((retry_rete++)>=max_retry_rete))
{
	   bitset(&dbdd[congrete],g2di_fz,1);
		pscserr(ERR_TASK,TASK_RETE,TASK_RETE,0,SYS_HALT_FLUSH);
}
}
