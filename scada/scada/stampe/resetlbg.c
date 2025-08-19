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
   resetlbg
      La routine esegue il reset delle variabili legate alla gestione del
      libro giornale. Viene chiamata alla mezzanotte per la chiusura
      dei file del libro giornale.

   Parametri
      nessuno

   Ritorno
      nessuno

*/
#include <stdio.h>

#include "defpub.h"
#include "print.inc"
void resetlbg()
{
   short i;

   if(byte_allfile)
	{
		fclose(fpstall);     // chiusura file libro giornale 
		byte_allfile=0L;
	}
	for(i=0;i<n_loga;i++) stloga[i].page_a=0;   // reset n. pagine e righe libro giornale
	for(i=0;i<n_loga;i++) stloga[i].righe_a=0;
}
