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
	Modulo: ACSIMU.C
   Simula l'acquisizione con anche l'invio dei comandi digitali su inet;
	in ingresso viene fornito solo il puntatore in dbs
*/
#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"

coman(unsigned short puntdb)
{

S_FDCOM des_com;					/* struttura descrittore comandi */
S_MDCOM com;						/* per attivare messaggio ad acqui */
   
/*
	lettura descrittore comando
*/
   if(rbyte(fileno(fpp[fdcom]),&des_com,(long)puntdb*(long)sizeof(S_FDCOM),
		sizeof(S_FDCOM)))	return;		// se nessun record letto

/*
	Se messaggio relativo ad un organo invio messaggio ad ACQUI
*/

if((des_com.organo != -1)||(des_com.abili))		// se organo associato
{																// o in caso di stampa

	memcpy(&com.comando,&des_com,sizeof(com)-sizeof(HEASCA));
	com.hea.mess=mdcom;
	setcom((char*)&com);
}

return(0);
}
invao(punt,value)
short punt;
float value;
{

return;
}






