/**********************************************************************
*
*       C Header:               f03.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:14:55 1996 %
*
**********************************************************************/
/*
   modulo f03.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)f03.h	5.1
*/
/* file f03_data.h
 Contiene le definizioni delle variabili e degli array utilizzati
 nella lettura dei file fortran F03.DAT */

#define   FILE_F03	"proc/f03.dat"

/* Variabili relative al file f03.dat */
long int  nbl, neqal, nbl1, nvart, neqsis, neqs1, npvrt;
long int  nu, nu1, nvri, isiss, nbtri, nst;

char     sigla[8];
char     *nosl;

char     **nosub, **noblc, **nom_bloc;
long int *nusta, *nusci, *ningr, *islb;

long int *ip;   /* IP(1,NBL1)   puntatore alle variabili */
char     **var;
long int *ipvrs;

long int *ips; /* IPS(1,NEQS1) puntatore variabili di uscita e di stato */
char     **sivar, **nom_sivar;
long int *iout_sivar;

long int *ipvrt; /* IPVRT(1,NPVRT) puntatore alle incognite(+) o noti(-) */

long int *ipi;  /* IPI(1,NPVRT) puntatore alle variabili di ingresso */
char     **vari, **nom_vari;
long int *iout_vari;

long int *ipvri; /* IPVRI(1,NVRI)  puntatore alla roulette */

