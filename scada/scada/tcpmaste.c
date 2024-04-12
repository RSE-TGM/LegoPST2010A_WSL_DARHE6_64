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
	tcpmaster

	Routine utilizzata dalla rete TCP/IP per testare se il sistema
	e' master o slave	e filtrare alcuni messaggi

	Parametri

	short	*	indice messaggio

	Ritorno

	1	se master
	0	se slave

*/
#include <stdio.h>

#include "comunic.inc"
#include "messcada.inc"

tcpmaster(mess)
short *mess;
{
	if(*(mess+1)==NO_STATOSIS) return(1);
	return((short) sys_master);
}
