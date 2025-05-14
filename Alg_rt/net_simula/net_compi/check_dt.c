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
static char SccsID[] = "@(#)check_dt.c	5.1\t11/7/95";
/*
   modulo check_dt.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)check_dt.c	5.1
*/

/*    SUBROUTINE CHECK_DT(MODEL,NMOD,NRIP)
  Conversione f-c:	1991-05-22	autore: C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>
#include "sim_param.h"
#include "sim_types.h"

void check_dt(
 MODEL model[],
 int nmod,
 int *nrip)
{
 float dt[MAX_MODEL], temp;
 int dt_millisec, dt_millisecp, i, j; 

 for (i=0; i<nmod; i++)
   dt[i]=model[i].dt;
 for (i=0; i<nmod; i++) {
   for (j=i+1; j<nmod; j++) {
     if (dt[j]>dt[i]) {
       temp=dt[i]; dt[i]=dt[j]; dt[j]=temp;
 } } }
 if (dt[0] > MAX_DT_DEC/10.) exit( fprintf(stderr,
   "ATTENZIONE il massimo passo di tempo ammesso e' di %5.3f s\n",
	(float)MAX_DT_DEC/10.) );
 dt_millisec = dt[nmod-1]*1000.;
 if (dt[nmod-1] == 0 || dt_millisec%100 != 0) exit( fprintf(stderr,
   "ATTENZIONE i passi di tempo ammessi debbono essere multipli di 0.1 s") );
 for (i=1; i<nmod; i++) {
   dt_millisecp=dt[i-1]*1000.;
   dt_millisec=dt[i]*1000.;
   if (dt_millisecp%dt_millisec != 0) exit( fprintf(stderr,
     "ATTENZIONE i passi di tempo ammessi debbono essere tra loro multipli") );
 }
 *nrip=10.*dt[0];
}
