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
   isalloc.c

   Routine per l'allocazione del buffer associato ai valori
   analogici e digitali calcolati non standard

   Parametri 
      
   nessuno

   Ritorno

   nessuno

*/
#include <osf1.h>
#include <malloc.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "isarc.inc"
#include "dconf.inc"
#include "isa.h"
#include "pscserr.inc"

extern DB_HEADER h_db;

/*
   puntatori aree per memorizzazione per dati aggiornati da isa
*/
/*
   puntatori aree per memorizzazione per dati aggiornati da isa
*/
extern char * isaAC;
extern char * isaDC;   

isalloc()
{
   isaAC= (char*)calloc(h_db.dimac,sizeof(char));
   isaDC= (char*)calloc(h_db.dimdc,sizeof(char));

   if(isaAC==NULL || (isaDC==NULL)) 
                  pscserr(ERR_MEM,TASK_ISA,ROU_ALLOC,0,SYS_HALT);
   return(0);
}
