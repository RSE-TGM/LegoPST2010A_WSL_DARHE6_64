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
static char SccsID[] = "@(#)check_o.c	5.1\t11/7/95";
/*
   modulo check_o.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)check_o.c	5.1
*/

/*    SUBROUTINE CHECK_OUTPUT(STRINGA,IMU,IU,VARLEGO,MODEL)
  conversione f-c       1991-05-23      autore C.Lusso (CISE)
*/
        /* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"
#include "net_compi_fun.h"


void check_output(
 char *stringa,
 int imu,
 int *iu,
 VARLEGO *varlego,
 MODEL model[])
{
int i;
for (i=0; i<varlego->neqsis; i++)
  if (! strcmp( stringa, varlego->nom_sivar[i]))
    break;
if (i==varlego->neqsis) exit( fprintf(stderr,
 "ATTENZIONE la variabile %s non e` uscita del modello %s\n",
	stringa, model[imu].name));
*iu=i + model[imu].punt_ivus;
} /* FINE "co_check_output.c" */
