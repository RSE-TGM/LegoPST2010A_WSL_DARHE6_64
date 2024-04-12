/**********************************************************************
*
*       C Header:               f03.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jun  5 11:48:30 1997 %
*
**********************************************************************/
/* file f03.h */
/* Calleri Nicola, Buffo Massimo 2/07/1992 */

/* Contiene le definizioni delle variabili e degli array utilizzati */
/* nella lettura dei file fortran F03.DAT */

/*
 se non incluso si include il file contente le definizioni di tipi
 di variabili relative ai files fortran
*/
#ifndef _F03_H_
#define _F03_H_

#ifndef _READ_FTN_H
#include "read_ftn.h"
#endif

#define   FILE_F03      "proc/f03.dat"

_INTEGER  nbl, neqal, nbl1, nvart, neqsis, neqs1, npvrt;
_INTEGER  nu, nu1, nvri, isiss, nbtri, nst;

char     sigla[8];
char     *nosl;

char     **nosub, **noblc, **nom_bloc;
_INTEGER *nusta, *nusci, *ningr, *islb;

_INTEGER *ip;   /* IP(1,NBL1)   puntatore alle variabili */
char     **var;
_INTEGER *ipvrs;

_INTEGER *ips; /* IPS(1,NEQS1) puntatore variabili di uscita e di stato */
char     **sivar, **nom_sivar;
_INTEGER *iout_sivar;

_INTEGER *ipvrt; /* IPVRT(1,NPVRT) puntatore alle incognite(+) o noti(-) */

_INTEGER *ipi;  /* IPI(1,NPVRT) puntatore alle variabili di ingresso */
char     **vari, **nom_vari;
_INTEGER *iout_vari;

_INTEGER *ipvri; /* IPVRI(1,NVRI)  puntatore alla roulette */

/* funzioni definite in f03.c */
int rd_file_f03();

#endif/*_F03_H_*/
/* fine file f03.h */
