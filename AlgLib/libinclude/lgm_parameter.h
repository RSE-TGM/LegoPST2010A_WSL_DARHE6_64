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
   modulo lgm_parameter.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)lgm_parameter.h	5.1
*/
/*
C**    NICON           = N. MAX DI TIPI ICONA
C**    NMODU           = N. MAX DI MODULI LEGO
C**    NMOD2           =    NICON * NMODU
C**    NBLOC           = N. MAX DI BLOCCHI LEGO
C**    NVARI           = N. MAX DI VARIABILI LEGO (CON RIPETIZIONI)
C**    NBLMO           = N. MAX DI BLOCCHI LEGO MODIFICATI
C**    NVAMO           = N. MAX DI VARIABILI LEGO MODIFICATE
C**    NTIPREG         = N. MAX DI TIPI DI ICONE DI REGOLAZIONE
*/

#define NICON	200
#define NMODU	100
#define NMOD2	2000
#define NBLOC	5000
#if defined PIACENZA
#define NVARI	32000
#else
#define NVARI	20000
#endif
#define NBLMO	500
#define NVAMO	2000
#define NTIPREG	200

/* INCLUDE 'LEGOGRAF$ROOT:[SHARE]PARAMETER.INC' */
#include "sim_param.h"
#include "sim_types.h"
