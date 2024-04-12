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
	-> _dos_findnext()

	Trova il successivo file presente nel direttorio corrente, prima
	deve essere stata chiamata _dos_findfirst().
*/

#include <osf1.h>
#include <stdio.h>
#include <dos.h>

unsigned _dos_findnext(struct find_t *filinfo)
{
	printf("_dos_findnext() funzione ancora da implementare\n");
}
