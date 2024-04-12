/**********************************************************************
*
*       C Header:               f11.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:15:02 1996 %
*
**********************************************************************/
/*
   modulo f11.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)f11.h	5.1
*/
/* file f11_data.h
 Contiene le definizioni delle variabili e degli array utilizzati
 nella lettura dei file fortran F11.DAT */

#define   FILE_F11	"proc/f11.dat"

/* Variabili relative al file f11.dat */
long int irc11, npvrt_f11;
long int *ipvrs_f11, *ips_f11, *ipvrt_f11;
char     **varsi, **varno;
long int *iresbl, *ibleqz;
_REAL    *cnxyu, *uu, *xy0, *xy;
char     **signeq, **uniteq;
_REAL    *cosnor;
long int **itopva;
long int *irj, *icj;
_REAL    *rn, *tn, *fj, norma;
long int *iconv, iconve, itert, iflag, kbeta, ibeta;
long int icef, irx, jac, nzter;
_REAL    residuo, tolle;

