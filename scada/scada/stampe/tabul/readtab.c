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
/* ->READTAB.C
 *    legge il dizionario dei tabulati e lo rende disponibile nel
 *		buffer diztab.
 */
#include <osf1.h>
#include <stdio.h>

#include "fileop.inc"
#define _PUBLIC 0          // definisco le strutture per i tabulati
#include "tabulati.inc"

int readtab(FILE *fp)
{
return(fread(diztab,rec_fdiztab*n_tabu,1,fp));
}
