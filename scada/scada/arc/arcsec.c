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
   arcsec

   la funzione data la struttura HEAD_CAMP trasforma il tempo
   in essa inserito in secondi.
   Utilizza la funzione mktime.

   Paramteri

   bcamp    *HEAD_CAMP     header campione d'archivio
   secondi  *long          secondi a partire dal 1900

   Ritorno  

   nessuno

   
   11 Maggio 1992    Rel. 1.0 Fc

*/
#include <osf1.h>
#include <time.h>
#include "arc.inc"

int arcsec(HEAD_CAMP *bcamp, long *secondi)
{
struct tm stimep;

stimep.tm_sec=bcamp->secondi;	         /* seconds after the minute - [0,59] */
stimep.tm_min=bcamp->minuti;	         /* minutes after the hour - [0,59] */
stimep.tm_hour=bcamp->ore;  	         /* hours since midnight - [0,23] */
stimep.tm_mday=bcamp->giorno;	         /* day of the month - [1,31] */
stimep.tm_mon=bcamp->mese-1;	         /* months since January - [0,11] */
stimep.tm_year=bcamp->anno-1900;	      /* years since 1900 */
stimep.tm_isdst=0;                     /* daylight savings time flag */

*secondi=mktime(&stimep);
return(0);
}
   
