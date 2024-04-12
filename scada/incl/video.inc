/**********************************************************************
*
*       C Header:               video.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Oct  9 11:50:18 1998 %
*
**********************************************************************/
/*
	include VIDEO.inc 
	definisce le tabelle video e i puntatori associati alle pagine

	Strutture definite per il max numero di video fisso

	7 Settembre 1994 Fc.
	Modifica per gestione fine a 10 zone per compatibilita' com MMI-WIN

        9 Giugno 1995 Fc.
        Ampliato il n. di punti per zona video da 256 a 384
*/
#include "maxpar.inc"
#include "switch.inc"

#include "defpub.h"

#define n_zone     10   /* n. zone  */
#define n_zone_matrox   3       /* n. zone per MMI Matrox       */

#define zonai      1   /* zona intera (mmi old) riservata pagina allarmi (mmi new)   */
#define zonaw      2   /* zona window (mmi old)  */
#define zonas      0   /* zona short (mmi old) pagina first (mmi new)   */
/*
	definizioni tipi di pagina allarmi
*/
#define p_al 256		/* allarmi non riconosciuti	*/
#define p_ar 257		/* allarmi in archivio		*/
/*
	definizioni tipi di pagina trend
*/
#define trendv  2               /* trend verticali   */
#define trendo  3               /* trend orizzontali */
/*
	definizione video
*/
typedef struct gztv   { char v_video;       /* spare                 */
			char v_input;  	    /* tipo input 	     */
			char v_pagina[10];  /* nome pagina           */
			char v_address[10] ;/* elenco                */
			short v_tipo ;	    /* tipo pagina           */
			short v_periodo ;   /* periodo aggiornamento */
			short v_cont ;}     /* contatore            */
			S_ZONE ;
typedef struct gstv { char ind_un;   /* indice unita' allarmi    */
		      char micro ;   /* indice micro assegnato al */
				     /*	al video		  */
        struct  gztv tsv [n_zone]; } S_VIDEO ;
pub S_VIDEO tstv[max_video] ;
/*
	definizione buffer aggiornamento valori pagina
*/

#define max_mis_zone	640				// n. massimo punti per zona video
pub S_PUNT  gdav[max_video][max_mis_zone*n_zone] ;   	// puntatori associati alla pagina 

