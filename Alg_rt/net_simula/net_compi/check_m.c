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
static char SccsID[] = "@(#)check_m.c	5.1\t11/7/95";
/*
   modulo check_m.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)check_m.c	5.1
*/

/*    SUBROUTINE CHECK_MODEL(STRINGA,IMI,IMU,MODEL,NMOD)
  conversione f-c	1991-05-23	autore C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"

void check_model(
 char *stringa,
 int imi,
 int *imu,
 MODEL model[],
 int nmod)
{
int i;
for (i=0; i<nmod; i++)
  if (! strcmp( stringa, model[i].name))
    break;
if (i==nmod) exit( fprintf(stderr,
 "ATTENZIONE il modello %s non esiste", stringa));
if (i==imi) exit( fprintf(stderr,
 "ATTENZIONE il modello %s non puo` essere connesso con se stesso"));
*imu=i;
} /* FINE "co_check_model.c" */
