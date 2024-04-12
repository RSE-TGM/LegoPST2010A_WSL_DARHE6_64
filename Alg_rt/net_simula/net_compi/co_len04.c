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
static char SccsID[] = "@(#)co_len04.c	5.1\t11/7/95";
/*
   modulo co_len04.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)co_len04.c	5.1
*/

/* copia di legge_riga, con adattamenti
  Conversione f-c:	1992-05-18	Autore: C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>

#define MAXRIGA 80

 extern FILE *fp_n04;
 extern int riga_n04;

legge_riga_n04(riga,lun)
 char *riga;
 int *lun;
{
 int c, k;

 riga_n04++;
 for (k=0; k<MAXRIGA; k++) 
   riga[k] = (char)NULL;

 for (k=0; (c = fgetc( fp_n04)) != '\n'; k++) {
  if (c == EOF) {
   fprintf(stderr, "ATTENZIONE end_of_file inatteso del file N04\n");
   exit( 1);
  }
  if (k == MAXRIGA-1) {
   fprintf(stderr, "ATTENZIONE (N04.dat) riga %d supera %d caratteri.\n", riga_n04, MAXRIGA);
   exit( 1);
  }
  riga[k]=c;
 }
 riga[k]=(char)NULL;

 if (k == 0) {
  fprintf(stderr, "ATTENZIONE nel file N04 la riga %d e' vuota\n", riga_n04);
  exit( 1);
 }
 if (riga[0] == ' ') {
  fprintf(stderr, "ATTENZIONE nel file N04 la riga %d inizia con blank\n", riga_n04);
  fprintf(stderr, "LA COMPILAZIONE CONTINUA COMUNQUE !!!!\n");
 }

 /*   CALL LUNGH(RIGA,LUN,NCHAR) superflua: */
 *lun = k;
} /* FINE legge_riga_n04 */
