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
#include <stdio.h>
#include <string.h>

void XAddScadaLog(char * testo)
{
#if defined XSCADA_INTERFACE
	AddLog(testo);
#else
	printf("%s",testo);
#endif
}

void XSetLineDebug(char *testo, int line)
{
#if defined XSCADA_INTERFACE
	SetDebug(testo,line);
#endif
}
