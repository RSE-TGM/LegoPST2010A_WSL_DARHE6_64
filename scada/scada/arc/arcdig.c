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
/*/
	Modulo   :  ARCDIG() 
	            Archiviazione per DIGITALI: i valori dei punti dell'archivio 
	            vengono memorizzati direttamnte nel data base. 

	Parametri:  PUNTDBS *point: puntatore alla struttura dei puntatori delle 
	                            misure in archivio

	Ritorno  :	Parola di flag e stato del digitale

	Creazione:  GM.Furlan  -  13.03.92  - Rel. 1.0
*/

#include <osf1.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"


arcdig(point)
PUNTDBS *point;
{

switch(point->ext)
{
   case g1tipda:
      return(dbda[point->punt]);
   break;
   case g1tipds:
      return(dbds[point->punt]);
   break;
   case g1tipdc:
      return(dbdc[point->punt]);
   break;
   case g1tipdd:
      return(dbdd[point->punt]);
   break;
   default:
      pscserr(ERR_TASK,TASK_ARC,ROU_DIG,0,SYS_CONT);
   break;
}
}
