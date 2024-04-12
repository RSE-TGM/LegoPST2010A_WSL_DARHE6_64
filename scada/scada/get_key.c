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
#include "stdio.h"
#include "bios.h"

/* versione modificata con gestione to per
non bloccare task eventualmente meno prioritari
*/

get_key(s)
short *s;
{
	short key;
	while(getkey_wait(60,&key,s));		// aspetto all' infinito un tasto
	return key;
}

/*
	Routine GETKEY_WAIT

	Gestisce l' input di caratteri da keyboard con gestione attesa
	ritorna un valore diverso da 0 se scattato timeout in input.
	Il valore e' contenuto nel messaggio.
	Il valore di timeout 0 comporta attesa infinita.

	*/
getkey_wait(to,mess,scan)

	short to;
	short *mess;
	short *scan;
	{
	unsigned short t_lav=to;			// inizializzo to
	union { short v;
			 unsigned char c[2];} bios_d;
   fflush(stdout);
 	while(! _bios_keybrd(_KEYBRD_READY))		// finche' non c'e' tasto premuto
		{
		if(t_lav--)	wai(2); 
		else if(to)							// scatto t.o. e to != 0
			return 1;
		}
 
	bios_d.v=_bios_keybrd(_KEYBRD_READ);
	*mess=bios_d.c[0];
	*scan=bios_d.c[1];
	return 0;
	}

