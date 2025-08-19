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
/* -> INITLINE.C
 *			inizializza le linee seriali ed eventualmente parallele
 			utilizzate dalla stop
 */
#include <stdio.h>	 
#include <bios.h>

#include "print.inc"
#include "pscs.cfg"

/* Function prototypes */
extern void IniLine(void *);
extern void inprser(void *);

void initline()
{
short j;

for(j=0;j<n_fis-1;j++)
	{
		if(stfis[j].linea==-1) continue;
		if(stfis[j].baud)
		{
#if defined (iSDx507)			// scheda seriali
			IniLine(&stfis[j]);
#else
			inprser(&stfis[j]);
#endif
		}
	}
}
