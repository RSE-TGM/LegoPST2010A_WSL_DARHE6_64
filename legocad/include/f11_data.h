/**********************************************************************
*
*       C Header:               f11_data.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:57 1996 %
*
**********************************************************************/
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

