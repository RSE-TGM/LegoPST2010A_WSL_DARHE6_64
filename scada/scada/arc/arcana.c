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
	Modulo   :  ARCANA()
	            Archiviazione "normale" o "veloce" per ANALOGICI: i valori dei 
               punti dell'archivio vengono memorizzati direttamnte nel data 
               base di archivio, compattando la parola di flag.
               La memorizzazione e' "filtrata" attraverso la tabella "tabmem":
               per archivi Normali e per archivi Lenti/Veloci con memorizzazione 
               Totale, nei quali sia scattato almeno un trigger, "tabmem" e' 
               completamente settata a 1; per archivi Lenti/Veloci con 
               memorizzazione Parziale "tabmem" e' settata a 1 in corrispondenza
               dei punti per i quali e' scattato il trigger.

	Parametri:  PUNTDBS *point: puntatore alla misura
	            DATDBS  *dbs:   puntatore progressivo al data base di archivio 

	Creazione:  GM.Furlan  -  10.03.92  -  Rel. 1.0   

*/

#include <osf1.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"

// External function declarations
extern void pscserr(int, int, int, int, int);

/*
   definizione maschere per raccolta flag analogici
*/
#define  mask_al (mask_ahs + mask_als + mask_ahc + mask_alc)			// maschera flag di allarme
#define mask_fl (mask_afs + mask_afz + mask_afa) 			            // maschera flag di FA, FS,FZ

void arcana(PUNTDBS *point, DATDBS *dbs)
{
float valore;
short flag;

switch(point->ext)
{
   case g1tipaa:
      dbs->a.camp.val=dbaav[point->punt];
      flag=dbaaf[point->punt];
   break;
   case g1tipas:
      dbs->a.camp.val=dbasv[point->punt];
      flag=dbasf[point->punt];
   break;
   case g1tipac:
      dbs->a.camp.val=dbacv[point->punt];
      flag=dbacf[point->punt];
   break;
   case g1tipad:
      dbs->a.camp.val=dbadv[point->punt];
      flag=dbadf[point->punt];
   break;
   default:
      pscserr(ERR_TASK,TASK_ARC,ROU_ANA,0,SYS_CONT);
   break;
}
//	Compattamento word dei flag a byte con scrittura di solo quelli di interesse
dbs->a.camp.flag=(flag & mask_al) + ( (flag & mask_fl) >> 8 );
#if defined (DEBUG)
//   printf(" v %f f %x ",dbs->a.camp.val, dbs->a.camp.flag);
#endif
}


