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
   modulo client_server_mmi.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)client_server_mmi.h	5.1
*/
/*
	tipi di client_mmi previsti
*/
#define CLIENT_MMI_FIRST	0

#define CLIENT_MMI_COMMAND	1
#define CLIENT_MMI_DATA		2
#define CLIENT_MMI_PERT		3

#define SERVER_MMI_COMMAND	1
#define SERVER_MMI_DATA		2
#define SERVER_MMI_PERT		3

/*
	timeout richiesta interfacciamento con processo server
*/
#define TIMEOUT_ACK_SERVER	15

/*
	indice della coda per il ricevimento
	dei messaggi dall'MMI
*/
#define FROM_MMI_MSG			88889

/*
	strutture e define per la richiesta e l'aggiornamento delle
	pagine
*/
#define MAXCHAR_PAGNAME		50

#define MAX_OPERAZIONI		200

#define NEW_PAGE_MMI		1
#define NEW_PAGE_MMI_RET	2

#define MAX_TOKEN		100

typedef struct token_st
        {
	int tipo;
	int puntdb;
        } TOKEN;

typedef struct msg_new_page_mmi_st
        {
	long mtype;
	char nome_pagina[MAXCHAR_PAGNAME];
	int t_agg;
	int num_punti;
	int num_punti_msg;
	int prog_msg;
	int num_msg;
	TOKEN token[MAX_TOKEN];
        } MSG_NEW_PAGE_MMI;

typedef struct elenco_pagine_st
	{
	int id_shm;
	char nome_pagina[MAXCHAR_PAGNAME];
	} ELENCO_PAGINE;

typedef struct msg_new_page_mmi_ret_st 
	{
	long mtype;
	int id_shm;
      	} MSG_NEW_PAGE_MMI_RET;

typedef struct header_new_page_mmi_st 
	{
    	int id_shm;
	int t_agg;
	int num_punti;
	int size;
      	} HEADER_NEW_PAGE_MMI;

/*
	tipo costituente la tabella delle operazioni eseguite
	dal server-data
*/
typedef struct elenco_operazioni_st 
	{
	int stato;
	int id_shm;
	int t_agg;
	int cont;
	int num_punti;
	TOKEN *token;
	} ELENCO_OPERAZIONI;
