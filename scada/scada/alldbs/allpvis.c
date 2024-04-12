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
   allpvis

   Routine per allineamento indicatori pvis0 e pvis1 per scroll archivio
	o paginba allrmi. Viene chiamata in caso di riconoscimento a pagine e
	lo stesso data base e' visualizzato su altri video.
   
   Parametri

	dbsal		short		n. data base allarmi
	ind		short		posizione dell'ultimo allarme riconosciuto
	flag		short		=0 inizializzazione puntatori
							=1	test

   Ritorno 

	nessuno

   1 Ottobre 1993

*/

#include "messcada.inc"
#include "allar.inc"

short pvis0_save[max_video], pvis1_save[max_video];

allpvis(short dbsal, short ind, short flag)
{
short j;
S_DBS_ALV *alc;
/*
	salvo indici attuali posizionamento visualizzazione
*/
alc=&bDbsAlv[0];

switch(flag)
{
	case 0:						// inizializzazione
		for(j=0;j<num_video;j++,alc++)
		{
		   pvis0_save[j]=alc->pvis0;
		   pvis1_save[j]=alc->pvis1;
		}
	break;
	case 1:						// correzione valori
		for(j=0;j<num_video;j++,alc++)
		{
		    if(alc->pal!=dbsal) continue;
		    if(pvis0_save[j]>ind) alc->pvis0--; 
		    if(pvis1_save[j]>ind) alc->pvis1--;
		}
	break;
}
return(0);
}
