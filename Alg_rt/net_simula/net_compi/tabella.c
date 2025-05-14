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
static char SccsID[] = "@(#)tabella.c	5.1\t11/7/95";
/*
   modulo tabella.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)tabella.c	5.1
*/

/*    SUBROUTINE TABELLA(MODEL,TABEL,NMOD,NRIP)
  Conversione f-c:	1991-05-22	autore: C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include "sim_param.h"
#include "sim_types.h"

void tabella(
 MODEL model[],
 TABEL tabel[],
 int nmod,
 int nrip)
{
int i, j, dt_millisec;
for (i=0; i<nmod; i++) {
  dt_millisec=model[i].dt*1000.;
  for (j=0; j<nrip; j++)
    if (j*100%dt_millisec == 0)
	{
      tabel[i].inst[j]=1;
	}
  }
} /* FINE "co_tabella.c" */
