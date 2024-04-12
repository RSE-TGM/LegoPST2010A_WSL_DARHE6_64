/**********************************************************************
*
*       C Header:               mandb.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:16:28 1996 %
*
**********************************************************************/
/*
   modulo mandb.h
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)mandb.h	5.1
*/

/*
	definizione parametri e strutture per mandb
*/

#define MAX_VAR		20
#define MAX_PAGINE	10
#define MAX_TOTVAR      MAX_VAR*MAX_PAGINE
#define MAX_CAMPIONI	50
#define MAX_LUN_DESCRPAGE 40
#define MAX_PAGE_SETVAL 10


typedef struct campione  { float valore[MAX_CAMPIONI];
			   float tempo[MAX_CAMPIONI];
		 } CAMP;

typedef struct dbase_mandb {
		int  indice_var[MAX_TOTVAR];
		int  pointin[MAX_TOTVAR];
		CAMP valori [MAX_TOTVAR];
		} DBASE_MANDB;

typedef struct page_vis { Widget w;
			  Widget *pogg;
			  int modifica_var;
			  int modifica_valsp;
			  int indice_pagina_save;
			  char sigle_vis[MAX_VAR][MAX_LUN_NOME_VAR];
			  int toggle_attivo;
                         } PAGE_VIS;
			

/*  indici messaggi per la coda di mandb */

#define  CODA_MANDB     1
#define  LUN_MSG_MAX   100
#define	MSG_START	1
#define	MSG_STOP	2
#define	MSG_RESET_HISTORY	3
#define	MSG_MOD_VALORI	4

typedef struct messaggio{
       long mtype;
       char mtext[LUN_MSG_MAX];} MSG;

typedef struct mess_mod_valori 
	{ int indice_var; /* campo addr struttura variabili */
          float valore;} MOD_VALORI;

typedef struct mess_reset 
	{ int indice_var; /* da 0 - 200 */
     } RESET_HISTORY;
