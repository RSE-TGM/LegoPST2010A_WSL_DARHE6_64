/**********************************************************************
*
*       C Source:               fpp.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:46:53 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: fpp.c,2 %  (%full_filespec: 1,csrc,fpp.c,2 %)";
#endif
/*
   modulo fpp.c
   tipo 
   release 1.15
   data 11/13/95
   reserved @(#)fpp.c	1.15
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)fpp.c	1.15\t11/13/95";
/*
        Fine sezione per SCCS
*/


/* file fpp.c
 scopo:
   fornire le routines di lettura/scrittura di paia
   (o-var Known, i-var Unknown)
 NOTA: per gli arg di chiamata, consultare il file "fpp.h"
 Autore: C.Lusso(CISE) 1994/05/03
 */

#include <stdio.h>
#include <string.h>

#include "fpp.h"

#define FPP_NAME	"fpp.dat"
/* tracciato del file FPP_NAME: */
#define FPP_REC_1	"*LG*NOME IMPIANTO= %.8s\n"
#define FPP_REC_2	"*LG*PAIA\n"
#define FPP_REC_3_R	"%3d %8c %8c\n"
#define FPP_REC_3_W	"%3d %s %s\n"
#define FPP_REC_EOF	"*LG*EOF\n"

int read_file_fpp( char **azPout, char **azPinp )
{
 char zPout[8+1], zPinp[8+1];
 FILE *p_file;
 int cPair, c, i;
   zPout[8] = zPinp[8] = '\0';
   p_file = fopen( FPP_NAME, "r");
   if (! p_file)
      return 0;
   /* 1' record: nome impianto */
   while(fgetc(p_file) != '\n')
      ;
   /* 2' record: n. paia */
   fscanf( p_file, FPP_REC_2);
   /* 3' record(s): paia */
   cPair = 0;
   while (fscanf( p_file, FPP_REC_3_R, &c, zPout, zPinp)) {
      azPout[cPair] = strdup( zPout);
      azPinp[cPair] = strdup( zPinp);
      cPair++;
   }
   /* 4' record: EOF */
   fclose( p_file);
   return cPair;
}

void write_file_fpp( char *zModel, int cPair, char **azPout, char **azPinp)
{
 FILE *p_file;
 int i;
   p_file = fopen( FPP_NAME, "w");
   /* 1' record: nome impianto */
   fprintf( p_file, FPP_REC_1, zModel);
   /* 2' record: n. paia */
   fprintf( p_file, FPP_REC_2);
   /* 3' record(s): paia */
   for (i=0; i<cPair; i++) {
      fprintf( p_file, FPP_REC_3_W, i+1, azPout[i], azPinp[i]);
   }
   /* 4' record: EOF */
   fprintf( p_file, FPP_REC_EOF);
   fclose( p_file);
}
