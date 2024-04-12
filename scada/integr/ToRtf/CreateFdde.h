/*
   modulo CreateFdde.h
   tipo 
   release 2.5
   data 6/7/96
   reserved @(#)CreateFdde.h	2.5
*/

#include "all_1.h"
#include "tag.h"

#define h_db header_ToRtf

typedef struct _REC_FDDE_AN {
    char Sigla[SCD_SIGLA];
    char Descrizione[SCD_DESCRIZIONE];
    char Altro[SCD_UNIMIS];
} REC_FDDE_AN;

typedef struct _REC_FDDE_DIG {
    char Sigla[SCD_SIGLA];
    char Descrizione[SCD_DESCRIZIONE];
    char Stato0[SCD_STATO];
    char Stato1[SCD_STATO];
} REC_FDDE_DIG;

typedef struct _REC_FDDE_DO {
    char Sigla[SCD_SIGLA];
    char Descrizione[SCD_DESCRIZIONE];
} REC_FDDE_DO;

typedef struct _REC_FDDE_OR {
    char Sigla[SCD_SIGLA];
    char Descrizione[SCD_DESCRIZIONE];
    char Tipo[SCD_TIPOR];
} REC_FDDE_OR;

typedef struct _REC_FDDE_ST {
    char Sigla[SCD_SIGLA];
    char Descrizione[SCD_DESCRIZIONE];
} REC_FDDE_ST;
     
typedef union _REC_FDDE {
	REC_FDDE_AN	_an;
	REC_FDDE_DIG	_di;
	REC_FDDE_DO	_do;
	REC_FDDE_OR	_or;
	REC_FDDE_ST	_st;
} REC_FDDE;

#include "all_16.h"
