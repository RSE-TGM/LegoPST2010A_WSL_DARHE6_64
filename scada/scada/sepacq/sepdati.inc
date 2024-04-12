/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
	Sepdati.inc

	Definizione strutture per esame dati rete inet con armadi
	di tipo Sepa e stop
	I nodi di tipo Sepa mantengo comunque la numerazione dei
	nodi di tipo Sdi partendo da nodo_armadi

	20 Aprile 1993
*/
#ifndef MESEST_INCL
#include "mesest.inc"
#endif
#include "sepstruc.inc"
#include "sepmess.inc"
#include "defpub.h"
/*
	struttura diagnostica comunicazione
*/
pub S_SEPNODI snodi[n_tot_nodi];
/*
	struttura statistica punti associati
	a ciascun armadio
*/
pub HEA_FSVAR heafsvar[sp_armadi];
/*
	array puntatori agli svincoli
*/
pub short *svinarp[sp_armadi];
/*
	array contatori messaggi digitali non
	variati
*/
pub unsigned short vnodi[sp_armadi];

pub char inv_slave;		// flag per abilitazione messaggio di acquisizione verso sistema slave

pub short n_confar;		// n. armadi effettivamente configurati
pub short scan_time;	// timer richiesta globale digitali
pub short scan_arm;		// indice ultimo armadio a cui e' stata
		        // inviata la richiesta di tutti i digitali

pub char *Kaa;		// puntatore area memoria coefficienti K
#define	n_tab_k	128	// n. massimo coefficienti k definibili
pub float tab_k[n_tab_k];
