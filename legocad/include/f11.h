/**********************************************************************
*
*       C Header:               f11.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon May 12 12:00:06 2003 %
*
**********************************************************************/
/* file f11.h */

/* Calleri Nicola, Buffo Massimo 2/07/1992 */

/* Contiene le definizioni delle variabili e degli array utilizzati */
/* nella lettura dei file fortran F11.DAT */

/*
 se non incluso si include il file contente le definizioni di tipi
 di variabili relative ai files fortran
*/
#ifndef _READ_FTN_H
#include "read_ftn.h"
#endif

#define   FILE_F11      "proc/f11.dat"

/* valori di irc11 (f11.dat) */
/* N.B. La 'C' significa 'CALCOLO' */
#define   C_RESIDUI             1
#define   C_SOLUZIONI           2
#define   C_JACOBIANO           3
#define   C_PROBLEMI            4
#define   C_MAX_JACOBIANI       5
#define   C_NON_OK              6
#define   C_OK                  7

/* Variabili relative al file f11.dat */
_INTEGER irc11;
_INTEGER npvrt_f11, neqsis_f11, nu_f11,nvart_f11; /* Queste variabili sono */
						 /* comunque uguali a quelle */
						 /* lette dal file f03.dat */
_INTEGER spare1[1000];
_INTEGER *ipvrs_f11, *ips_f11, *ipvrt_f11;
_INTEGER spare2[1000];
char     **varsi, **varno;
_INTEGER *iresbl, *ibleqz;
_REAL    *cnxyu, *uu, *xy0, *xy;
char     **signeq, **uniteq;
_REAL    *cosnor;
_INTEGER **itopva;
_INTEGER *irj, *icj;
_REAL    *rn, *tn, *fj, norma;
_INTEGER *iconv, iconve, itert, iflag, kbeta, ibeta;
_INTEGER icef, irx, jac, nzter;
_REAL    residuo, tolle;
_INTEGER *ipvrs_f11_bis, *ips_f11_bis, *ipvrt_f11_bis;

/*** Fine file f11.h ***/
