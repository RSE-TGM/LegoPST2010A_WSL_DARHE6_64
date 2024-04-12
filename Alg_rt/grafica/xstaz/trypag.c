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
   modulo trypag.c
   tipo 
   release 1.3
   data 3/23/95
   reserved @(#)trypag.c	1.3
*/
 /*   programma di invio messaggi a xstaa
 */


#include <stdio.h>
#include <string.h>
#include <math.h>

main(argc,argv)
int argc;
char *argv[];
{
int ix,iy;
char nome[10],app[50];
char file[50];
int shr_usr_key;


/*
  inizializza cluster event flags
*/

ef_cluster();
file[0]='.';
file[1]=0;
set_nom_log_s(file,strlen(file),"S04_PATH","EASE$LNM");
set_ef(7,1);
printf("\n premi un tasto per nvio dati  ");
getchar();

INIZIO:

printf ("\n X: ");
gets(app);
if (strlen(app) == 0) goto fine;
set_nom_log_s(app,strlen(app),"X_STAZ","EASE$LNM");

printf ("\n Y: ");
gets(app);
if (strlen(app) == 0) goto fine;
set_nom_log_s(app,strlen(app),"Y_STAZ","EASE$LNM");


printf ("\n NOME:    ");
gets(app);
if (strlen(app) == 0) goto fine;
set_nom_log_s(app,strlen(app),"VAR_STAZ","EASE$LNM");


set_ef(7,1);
set_ef(5,1);

goto INIZIO;

fine:
clr_ef(7,1);
clr_ef(5,1);
/*end_nom_log_s();*/
}
