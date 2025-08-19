/**********************************************************************
*
*       C Header:               g0gerdb.inc
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 15:05:39 2002 %
*
**********************************************************************/
/*
	Definizione delle strutture delle tabelle
	di data base per la gestione delle gerarchie
	degli allarmi.
*/

#include "all_1.h"
#ifdef GERARC
#ifndef _g0gerdb_inc

#define n_gerarchie       6
#define n_liv_gerarchie 128
#define ger_default      -1

typedef struct s_gerarc {
                unsigned char chLivello[n_gerarchie];
                        } S_DBGERA;

#define _g0gerdb_inc
#endif
#endif
#include "all_16.h"
