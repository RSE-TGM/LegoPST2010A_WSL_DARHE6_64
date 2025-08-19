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
	Modulo   :  ARCAVE() 
	            Archiviazione "lenta" per ANALOGICI: nel data base di archivio 
	            viene memorizzata la media dei punti.
               
	Parametri:  PUNTDBS *point: puntatore alla struttura dei puntatori delle 
	                            misure in archivio
				   DATDBS  *dbs:   puntatore al data base archivio da aggiornare

	Ritorno  :  short flag:      parola di flag della misura

	Creazione:  GM.Furlan  -  16.03.92

*/
#include <osf1.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"

// External function declarations
extern void pscserr(int, int, int, int, int);

short arcave(PUNTDBS *point, DATDBS *dbs)
{
float valore;
short flag;

switch(point->ext)
{
   case g1tipaa:
      valore=dbaav[point->punt];
      flag=dbaaf[point->punt];
   break;
   case g1tipas:
      valore=dbasv[point->punt];
      flag=dbasf[point->punt];
   break;
   case g1tipac:
      valore=dbacv[point->punt];
      flag=dbacf[point->punt];
   break;
   case g1tipad:
      valore=dbadv[point->punt];
      flag=dbadf[point->punt];
   break;
   default:
      pscserr(ERR_TASK,TASK_ARC,ROU_AVE,0,SYS_CONT);
   break;
}
dbs->a.ave.med=(dbs->a.ave.med*dbs->a.ave.ctot+valore)/(dbs->a.ave.ctot+1);
dbs->a.ave.ctot++;
if(flag & (mask_afa + mask_afs)) dbs->a.ave.cfsfa++;

#if defined (DEBUG)
//   printf(" media %f ctot %d  cerr %d ",dbs->a.ave.med, dbs->a.ave.ctot,
//                                        dbs->a.ave.cfsfa);
#endif
return(flag);
}
