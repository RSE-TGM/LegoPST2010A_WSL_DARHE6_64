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
   modulo OlConn.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlConn.h	5.1
*/
/*
 * OlConn.h - file di include pubblico per l'utilizzo delle connessioni
	      fra i diversi schemi di regolazione
 */
#ifndef _OlConn_h
#define _OlConn_h

#include <Rt/RtMemory.h>
/*
 nomi di risorse utilizzate internamente a OlConn
 */


/* dichiarazione tipi per Classe e Instanziazione di OlConn */
typedef struct _OlConnClassRec *OlConnObjectClass;
typedef struct _OlConnRec *OlConnObject;

/*
 Definizioni di uso generale riguardanti le connessioni
*/


#define MAX_LUN_NOME_PAG        60
#define MAX_LUN_NOME_WIDGET     30
#define MAX_LUN_NOME_REGOVAR    10
#define MAX_LUN_NOME_MOD        10
#define MAX_LUN_NOME_TAG        10
#define MAX_LUN_DESCR           100
#define MAX_LUN_RIGA_CONN       700
#define MAX_LUN_NOME_V		9


typedef struct _connessione {
		int spare;
		/*
			USCITA
		*/
		char u_nome_pagina[MAX_LUN_NOME_PAG];
		char u_nome_porta_int[MAX_LUN_NOME_WIDGET];
		char u_nome_icona_int[MAX_LUN_NOME_WIDGET];
		char u_nome_porta[MAX_LUN_NOME_WIDGET];
		char u_nome_icona[MAX_LUN_NOME_WIDGET];
		char u_nome_var[MAX_LUN_NOME_V];
		char u_nome_modulo[MAX_LUN_NOME_MOD];
		char u_nome_tag[MAX_LUN_NOME_TAG];
		char u_descrizione[MAX_LUN_DESCR];
		/*
			INGRESSO
		*/
		char i_nome_pagina[MAX_LUN_NOME_PAG];
		char i_nome_porta_int[MAX_LUN_NOME_WIDGET];
		char i_nome_icona_int[MAX_LUN_NOME_WIDGET];
		char i_nome_porta[MAX_LUN_NOME_WIDGET];
		char i_nome_icona[MAX_LUN_NOME_WIDGET];
		char i_nome_var[MAX_LUN_NOME_V];
		char i_nome_modulo[MAX_LUN_NOME_MOD];
		char i_nome_tag[MAX_LUN_NOME_TAG];
		char i_descrizione[MAX_LUN_DESCR];

		float valore_variabile;
                } CONNESSIONE;


/*
	procedure utilizzabili per la creazione  la distruzione
	e in generale per la gestione dell'oggetto OlConn
*/
OlConnObject OlCreateConn();
void OlDestroyConn();
Boolean OlSaveConn();
Boolean OlInsNewConn();
Boolean OlDelConn();
int OlGetNumConn();
int OlFindConn();
int OlFindConnByPort();
Boolean OlPagIsConnected();
char * OlFindConnectedTag();
void OlPrintConn();
void OlPrintSingleConn();
void OlCreateStructConn(CONNESSIONE*,
                char*, char*, char*, char*, char*, char*, char*, char*, char*,
                char*, char*, char*, char*, char*, char*, char*, char*, char*,
                float
                );
CONNESSIONE *OlGetConn();


#endif /* _OlConn_h */

