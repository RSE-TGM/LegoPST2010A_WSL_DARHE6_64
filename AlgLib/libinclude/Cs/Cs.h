/**********************************************************************
*
*       C Header:               Cs.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Nov  7 12:40:17 2005 %
*
**********************************************************************/
/*
   modulo Cs.h
   tipo 
   release 5.2
   data 11/14/95
   reserved @(#)Cs.h	5.2
*/

#ifndef _Cs_h
#define _Cs_h

#include <Rt/RtMemory.h>
#include <sim_ipc.h>  
#include <stdio.h>  



/*
 OFFSET SHM pagine di mmi
*/
#define OFFSETMMIPAGE   500


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
#define SERVER_COMMAND_DATA     4

/*
	timeout richiesta interfacciamento con processo server
*/
#define TIMEOUT_ACK_SERVER	15
#define TIMEOUT_MMI		20


/*
	strutture e define per la richiesta e l'aggiornamento delle
	pagine
*/
#define MAXCHAR_PAGNAME		60

#define MAX_OPERAZIONI		200
#if defined SCADA_MMI
#define MAX_LUN_NOME_FILE_TREND   200
#endif

#define NEW_PAGE_MMI		1
#define NEW_PAGE_MMI_RET	2
#define DEL_PAGE_MMI		3
#define REF_PAGE_MMI		4
#define F22_MMI		        5
#define CHANGE_POINT_MMI	6
#if defined SCADA_MMI
#define TREND_REQ		7
#endif
#define ALL_REQ				8
#define ALL_REQ_ARCHIVI			9
#define ALL_REQ_ALLARMI			10
#define ALL_REQ_RIC			11
#define ALL_REQ_AVANTI			12
#define ALL_REQ_INDIETRO		13
#define ALL_REQ_CHIUDI			14
#define ALL_REQ_COMMAND			15
#define ALL_REQ_MINIASD			16
#define ALL_DES_MINIASD			17
#define ALL_RIC_MINIASD			18
#define CHECK_SIM_ID				19
#define CHECK_SIM_ID_ACK			20

#define MPALMINIASD			9  /* per richiesta all     */
#define MRICSMINIASD			10 /* per riconosc. singolo */

/*
Identificatore per riconoscimento Singolo miniASD
*/
#define OPERAZIONERICALL             -2
/*
FILTRI per interrogazione SCADA allarmi con miniASD
*/
#define MINIASD_ALARM_REQ               0
#define MINIASD_MANUAL_REQ              1 
#define  ALL_A    0
#define  ALL_N    13
#define  ALL_W    22
#define  ALL_M    12
#define  ALL_T    19
#define  ALL_S    18
#define  ALL_F    5

/*
Stato degli allarmi (utilizzato da client_scada e teleperm pag_all)
*/
#define EMISSIONE       1
#define RIENTRO         0
#define RICONOSCIUTO    2
#define SPENTO          3
/*
	Tag per richiesta aggiornamento tempo
*/
#define REQ_TIME		-10
#define REQ_STATUS		-11

#define MAX_TOKEN		100

/*
definisco il Max num di zone 
Vedi file: teleperm.c sdi_messhost.h 
*/
#define MAXZONEALL 	32
/*
Definisco DB allarmi principale
*/
#define DBMASTER	1
/*
	MACRO PER LA CONVERSIONE DEI DATI
*/
#define CONVERTI_INT_T(dato)  memcpy(&(dato), \
                                 converti_int(&(dato),TRASMISSIONE),\
                                 sizeof(int));
#define CONVERTI_INT_R(dato)  memcpy(&(dato), \
                                 converti_int(&(dato),RICEZIONE),\
                                 sizeof(int));
#define CONVERTI_FLOAT_T(dato)  memcpy(&(dato), \
                                converti_float(&(dato),TRASMISSIONE),\
                                  sizeof(int));
#define CONVERTI_FLOAT_R(dato)  memcpy(&(dato), \
                                converti_float(&(dato),RICEZIONE),\
                                     sizeof(int));

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

typedef struct msg_del_page_mmi_st
        {
	long mtype;
	int id_shm;
        } MSG_DEL_PAGE_MMI;

typedef struct msg_sim_id_st
        {
	long mtype;
	char path_sim[FILENAME_MAX];  /* path simulatore */
        } MSG_SIM_ID;
typedef struct msg_sim_id_ack_st
        {
	long mtype;
        int ris;                      /* eventuale risposta */
        } MSG_SIM_ID_ACK;

typedef struct msg_change_point_mmi_st
        {
	long mtype;
	int id_shm;
	int posizione;
	int indirizzo;
	int tipo;
        } MSG_CHANGE_POINT_MMI;

typedef struct msg_all_req_mmi_st
        {
	long mtype;
	int zone[MAXZONEALL];
        int db;
        } MSG_ALL_REQ_MMI;

typedef struct msg_all_miniasd_req_mmi_st
        {
	long mtype;
        char gerarchia[6]; /* 6 cablato temporaneam. N_GERARCHIE */
        int  id_allarm_data;
        int  id_manual_data;
        short filtro;
        short tipo_allarme;
        } MSG_ALL_MINIASD_REQ_MMI;
typedef struct msg_all_miniasd_des_mmi_st
        {
	long mtype;
        int  id_allarm;
        int  id_manual;
        } MSG_ALL_MINIASD_DES_MMI;


typedef struct msg_all_miniasd_ric_mmi_st
        {
	long mtype;
        char gerarchia[6]; /* 6 cablato temporaneam. N_GERARCHIE */
        int  id_data_all;
        int n_all;         /* No allarmi da riconoscere */
        short tipo_allarme;
        short filtro;
        int indice_all;
        } MSG_ALL_MINIASD_RIC_MMI;

typedef struct msg_all_command_mmi_st
        {
	long mtype;
	int comando;
        int db;
        } MSG_ALL_COMMAND_MMI;

#if defined SCADA_MMI
typedef struct msg_trend_req_mmi_st
        {
	long mtype;
	int id_shm;
	char nome_pagina[MAXCHAR_PAGNAME];
	int codice_trend;
	char nome_file_trend[MAX_LUN_NOME_FILE_TREND];
        int num_mis;
	char sigla_1[MAX_LUN_NOME_VAR];
	char sigla_2[MAX_LUN_NOME_VAR];
	char sigla_3[MAX_LUN_NOME_VAR];
	char sigla_4[MAX_LUN_NOME_VAR];
        } MSG_TREND_REQ_MMI;
#endif

#define OFFSET_SHM_ALLARMI	480
#define OFFSET_SHM_MINIASD	(OFFSET_SHM_ALLARMI + 1)
#define OFFSET_SEM_SCADA		80
#define OFFSET_SEM_MMI		        81
#define ALL_DATA	12
/*
Valore precedente; modifica 16/09/96 by Fabio
#define ALL_DESC	64
*/
/*
Modificato ancora per compatibilita' Teleperm
*/
#define ALL_DESC 120
#define N_ALL_STR	16

#define ERRORE_DATI_ALLARMI	       -1
#define DATI_ALLARMI_NON_VALIDI		0
#define DATI_ALLARMI_VALIDI		1
#define N_GERARCHIE		6
/*
N.B.
Nei miniASD si utilizzata la stessa struttura di shm per avere 
la possibilita' di una eventuale lettura con una pagallarmi qualsiasi
col_ast  col_str sono utilizzati per contenere ext e punt tipici
di un allarme 
*/
typedef struct dati_allarmi_shm_st
	{
	int dati_validi;
	int allarmi_da;
	int allarmi_a;
	int num_all_arc;
	int num_all_da_ric;
	int n_all;
	int col_ast[N_ALL_STR];  
	int col_str[N_ALL_STR]; 
	char data[N_ALL_STR][ALL_DATA];
	char descr[N_ALL_STR][ALL_DESC];
	char hierarchy[N_ALL_STR][N_GERARCHIE];
	char emission[N_ALL_STR];        /* stato allarme */
	short n_all_pen[MAXZONEALL];
	short n_all_arc[MAXZONEALL];
	int esiste_val[N_ALL_STR];
	float val[N_ALL_STR];
        char tipo[N_ALL_STR];
        char ext[N_ALL_STR];
        short indice[N_ALL_STR];
	} DATI_ALLARMI_SHM;


#define SIZE_PATH_MMI 200

typedef struct msg_f22_mmi_st
        {
	long mtype;
	char path_client[SIZE_PATH_MMI];
	char path_server[SIZE_PATH_MMI];
        } MSG_F22_MMI;
/*
#define SERVER_CMD_NEWPG
#define SERVER_CMDT_DELPG
*/

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
	int richiesta_mmi;
      	} HEADER_NEW_PAGE_MMI;

typedef struct header_data_data_st 
	{
    	int tipo_operazione;
	int id_shm;
	int num_punti;
      	} HEADER_DATA_DATA;

#define CLT_CMDT_NEWPAGE 10
#define CLT_CMDT_DELPAGE 11
#define CLT_CMDT_REFPAGE 12
#define CLT_CMDT_F22PAGE 13
#define CLT_CMDT_WATCHDOG 14



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




typedef struct msg_tok_st
     {
     long mtype;
     TOKEN token[MAX_TOKEN];
     } MSG_TOK;

typedef struct msg_hdr_st
     {
     long mtype;
     int operazione;
     HEADER_NEW_PAGE_MMI header;
     } MSG_HDR;

typedef struct tab_shared_st
     {
     char *ind;
     int id_shm;
     int shmvid;
     int num_punti;
     } TAB_SHARED;
/*
	funzioni di libreria
*/

int CsPrepMsg(char *, int, int, int, int, int, int);
int CsRcvToken(int, char **);
int CsRcvTokenS(int, char **);
int CsChangePoint(int ,int ,int , int, int);
/*
Utilita'
*/
int cerca_shm(TAB_SHARED *, int );
int send_mmi_ret_ack(int ,int );
int tab_piena(TAB_SHARED *);


#if defined SCADA_MMI
int CsPrepMsgTrendReq(int, int,char *, int ,char *,int ,
		 char *,char *,char *,char *);


int CsRcvMsgSimID(int ,char *);
int CsPrepMsgSimID(int ,char * );
int CsRcvMsgSimIDAck(int ,int *);
int CsPrepMsgSimIDAck(int ,int  );


#endif
int CsPrepMsgAllCommand(int , int ,int );
int CsPrepMsgAllReq(int , int *zone,int );
int CsRcvMsgAllReq(int ,MSG_ALL_REQ_MMI *);
int CsRcvMsgMiniASDReq(int ,MSG_ALL_MINIASD_REQ_MMI *);
int CsPrepMsgMiniASDReq(int ,unsigned char *,int ,int ,int ,int );
int CsPrepMsgMiniASDRic(int ,unsigned char *,int ,int ,int ,int ,int );
int CsRcvMsgMiniASDRic(int ,MSG_ALL_MINIASD_RIC_MMI *);
int CsPrepMsgMiniASDDes(int , int ,int);
int CsRcvMsgMiniASDDes(int, MSG_ALL_MINIASD_DES_MMI *);
#endif

