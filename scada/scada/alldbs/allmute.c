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
	allmute.c

	La funzione verifica che siano stati riconosciuti tutti
	gli allarmi presenti nei data base per effettuare la
	tacitazione del cicalino.

	Parametri

	nessuno

	Ritorno

	nessuno

	18 Maggio 1993
*/

#include "messcada.inc"
#include "allar.inc"

allmute()
{
S_DBS_ALL *paldbs;
short i;

paldbs=&bDbsAll[0];
for(i=0;i<max_dbsall;i++,paldbs++)
{
	if(!paldbs->def) break;						// data base configurato ?
	if(*(paldbs->db_al) != 0.0) return(0);	// ancora allarmi da riconoscere ?
}
CmdBell(0);
}
