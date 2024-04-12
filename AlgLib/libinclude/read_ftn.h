/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo read_ftn.h
   tipo 
   release 2.3
   data 3/21/95
   reserved @(#)read_ftn.h	2.3
*/
/* file read_ftn.h */

/* Calleri Nicola, Buffo Massimo 2/07/1992 */
#define _READ_FTN_H /* per evitare doppie definizioni */
#ifdef DOUBLE_PREC
typedef double _REAL;
#else
typedef float _REAL;
#endif

typedef int _INTEGER;

#define BUFSIZE 512

#define DIMTIPO(tipo,n) ((n)*(sizeof(tipo)))

/*** Fine file read_ftn.h ***/
