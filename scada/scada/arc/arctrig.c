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
	Modulo   :  ARCTRIG()
	            confrontando la parola di flag del punto in archivio con la 
	            maschera di trigger, stabilisce se per il punto corrente e' 
	            scattato il trigger
               Il trigger non viene considerato se il punto e' fuori atten-
               dibilita' o fuori scansione

	Parametri:	short w_flag: word di flag
					short trig    codice trigger

	Ritorno  :	1: punto in allarme: scatto del trigger
	          	0: nessun allarme: trigger non scattato

	Creazione:  GM.Furlan  -  16.03.92  - Rel. 1.0

*/
#include <osf1.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"


arctrig(w_flag,trig)
short w_flag;				// word di flag
short trig;	            // codice trigger
{
/*
   se il punto e' fuori attendibilita' o fuori scansione, il
   trigger non viene generato 
*/   
if ( w_flag & (mask_afa + mask_afs)) return(0);

switch(trig)
{
case trig_s:               // sicurezza
	if ( w_flag & (mask_als + mask_ahs)) return(1);
   else return(0);
break;
case trig_c:               // conduzione
	if ( w_flag & (mask_ahc + mask_alc)) return(1);
   else return(0);
break;
case trig_sc:              // sicurezza + conduzione
	if ( w_flag & (mask_ahs + mask_als + mask_ahc + mask_alc)) return(1);
	return(0);
break;
case trig_sl:               // stato digitale
	if ( w_flag & mask_sl) return(1);
   else return(0);
break;
default:
return(0); 
break;
}
}


