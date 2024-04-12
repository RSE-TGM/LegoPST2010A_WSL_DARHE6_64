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
	Questo modulo contiene le chiamata all'abilitazione
	dei seguenti moduli periodici:

		arcwai
*/
#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "pscserr.inc"
#include "arc.inc"
#include "taskwd.inc"      // tabella di watch-dog e stato dei task
#include "simula.inc"      // definizioni e variabili generali per simulatore
#include "simmsg.inc"      // strutture messaggi da simulatore
#include "simdia.inc"      // indirizzi in DB dei digitali di diagnostica per simulatore
#include "simana.inc"      // indirizzi in DB degli analogici di diagnostica per simulatore
#include "netmsg.h"

/*

	L'archiviazione e' attiva solo nello stato di RUN del simulatore

	ritorno:
		0: archiviazione ferma
		1: archiviazione abilitata
*/
int SimArcwai()
{
        if (!bitvalue(&dbdd[sscrun],g2di_sl))
		return(1);
	else
		return(0);
}

/*

	L'attivita' periodica dei tabulati  e' attiva solo nello stato 
	di RUN del simulatore

	ritorno:
		0: tabper fermo
		1: tabper abilitato
*/
int SimTabper()
{
        if (!bitvalue(&dbdd[sscrun],g2di_sl))
		return(1);
	else
		return(0);
}
