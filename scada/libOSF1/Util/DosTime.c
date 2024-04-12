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
	-> _dos_settime()
	-> _dos_setdate()

*/

#include <osf1.h>
#include <stdio.h>
#include <dos.h>

unsigned _dos_settime(struct dostime_t *time)
{
	printf("_dos_settime() funzione ancora da implementare\n");
}

unsigned _dos_setdate(struct dosdate_t *date)
{
	printf("_dos_settime() funzione ancora da implementare\n");
}
