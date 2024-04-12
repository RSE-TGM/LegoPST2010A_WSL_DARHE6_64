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
	-> _dos_findfirst()

	Trova il primo file del presente nel direttorio corrente.
*/

#include <osf1.h>
#include <stdio.h>
#include <dos.h>

unsigned _dos_findfirst(const char *filename,unsigned attrib,struct find_t *filinfo)
{
        printf("_dos_findfirst() funzione ancora da implementare\n");
}
