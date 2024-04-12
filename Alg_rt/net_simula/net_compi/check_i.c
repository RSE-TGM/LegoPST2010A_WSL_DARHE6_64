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
static char SccsID[] = "@(#)check_i.c	5.1\t11/7/95";
/*
   modulo check_i.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)check_i.c	5.1
*/

/*    SUBROUTINE CHECK_INPUT(STRINGA,IMI,II,VARLEGO,MODEL)
  conversione f-c	1991-05-23	autore C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"

check_input(
 char *stringa,
 int imi,
 int *ii,
 VARLEGO *varlego,
 MODEL model[])
{
int i;
for (i=0; i<varlego->nu; i++)
  if (! strcmp( stringa, varlego->nom_vari[i]))
    break;
if (i==varlego->nu) exit( fprintf(stderr,
 "ATTENZIONE la variabile %s non e` ingresso del modello %s\n",
	stringa, model[imi].name));
*ii=i + model[imi].punt_ivin;
} /* FINE "co_check_input.c" */
