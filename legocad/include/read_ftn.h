/**********************************************************************
*
*       C Header:               read_ftn.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:33 1996 %
*
**********************************************************************/
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

int leggi_record_ftn( int , int , int , char , int , ...);

void crea_array_bidim( char*, char*, int, int );

/*** Fine file read_ftn.h ***/
