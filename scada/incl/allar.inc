/**********************************************************************
*
*       C Header:               allar.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jul 25 17:43:36 1997 %
*
**********************************************************************/
/*   file di include ALLAR.INC che descrive i buffer degli allarmi
     i messaggi MALLA di comunicazione fra call e stampe
*/
#include "defpub.h"
#include <all_1.h>
struct buff_all   { S_MALLA m   ;
		    short mask   ;  /* maschera per archivi */
		    unsigned char  giorno ;
		    unsigned char  ore    ;
		    unsigned char  minuti ;
	            unsigned char  secondi;} ;

#include <all_16.h>
#include "mestampe.inc"
#include <all_1.h>
/*
	flag per segnalare l'arrivo di nuovi allarmi
	viene settato da call e resettato da dec all'inivio
	dei messaggi paal e vdeal 
	il suo valore viene inserito nei due messaggi per
	la gestione del cicalino
*/
pub short  flag_all;	  
				
pub union u_stampe {	
		S_STALL  stal ;			   /* messaggi per stampe	*/
		S_STALS  stas ;			   /* messaggi per stampe  stringhe	*/
	       } us;

#define first_cont_all 384  // indice logico del primo analogico di
                             // diagnostica da utilizzare per memorizzare
                              // i contatori allarmi da riconoscere e 
                               // riconosciuti
                                // per zona di impianto e data base allarmi

#include <all_16.h>
#include "g0gerdb.inc"
#include "allstr.inc"
