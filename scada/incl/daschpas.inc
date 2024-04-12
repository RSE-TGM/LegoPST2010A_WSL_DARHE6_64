/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* File contenente le dichiarazioni aree dati scheduler PAS */
#include "defpub.h"

/* Vettore di puntatori alle strutture di tipo SCHEDULER */

pub struct SCHEDULER *pntschpas[NMAX_PAS] ;

/* Vettore di puntatori alle strutture di tipo PCB */

pub struct PCB *pcb[NMAX_PAS] ;

// Vettori contenenti TCb e Indici di code utilizzati dai PAS

pub unsigned int   TAB_TCBPAS[NMAX_PAS] ;
pub unsigned short TAB_INDCD[NMAX_PAS] ;

/* Tabella indici fisici digitali acquisiti di comando Scheduler */

pub short tbischpas [NMAX_PAS][2] ;

/* Tabella timer per attivazione dei pas		 */

pub short v_timepas [NMAX_PAS] ;    	// valore timer
pub short v_contpas [NMAX_PAS] ;	// contatore
