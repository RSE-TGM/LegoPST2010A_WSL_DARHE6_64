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
   SIMLGINI.C
      Segnala su Libro Giornale l'avvenuta inizializzazione del simulatore

      30.09.92  -  Rev.1.00  -  GM.Furlan

      27 Marzo 1995 Fc Porting a 32Bit
*/
#include	"comunic.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "tipal.inc"
#include "simula.inc"      // definizioni e variabili generali per simulatore
#include "simana.inc"      // analogici di diagnostica per simulatore

simlgini(ptr_db)
short ptr_db;    // indice in DB dell'AD contenente il numero di CI o BT
{

   QUEUE_PACKET packs;
	S_MALLA	alla;
   
packs.que= c_visall ;
packs.flg= MSG_WAIT;
packs.wto= 0;
packs.amsg=(char *) &alla ;
packs.lmsg= sizeof(S_MALLA) ;

alla.punt=ptr_db;
alla.ext= g1tipad;  
alla.ertr=trat_ne | 0x80;
alla.sprec=al_blank;
alla.satt=al_blank;
alla.sogl1=-1;
alla.sogl2=-1;
enqueue(&packs);


}



