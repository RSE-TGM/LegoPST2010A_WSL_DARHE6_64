/**********************************************************************
*
*       C Header:               RtDbPuntiP.h
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:35:39 1997 %
*
**********************************************************************/
/*
   modulo RtDbPuntiP.h
   tipo 
   release 5.2
   data 11/15/95
   reserved @(#)RtDbPuntiP.h	5.2
*/
/*
 * RtDbPuntiP.h - definizioni private per l'oggetto RtDbPunti
 */
#ifndef _RtDbPuntiP_h
#define _RtDbPuntiP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/
#include <Rt/RtP.h>
#include <Rt/RtErroreP.h>

/*
 Inclusione dell'header file pubblico
*/
#include <Rt/RtDbPunti.h>

typedef Boolean (*RtInitializeDbPuntiProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*RtCloseDbPuntiProc) (
#if NeedFunctionPrototypes
#endif
);

/*
 *   definizioni di strutture utilizzate
 */

#define KEY_HEAD	19283746

#define ID_SH_HEAD_SIM	6
#define ID_SH_SIM	7


/*
SOSTITUITA DALLA NUMERI_MODELLI
typedef struct {
	int stati;
	int ingressi;
	int derivate;
	int dati;
	} HEAD_DBPUNTI_MODEL;
*/

typedef struct {
	int key_head;
	int n_task;
	int par_N000;
	int par_N001;
	int par_N002;
	int par_N003;
	int par_N004;
	int par_N005;
	int par_N007;
	int par_M000;
	int par_M001;
	int par_M002;
	int par_M003;
	int par_M004;
	int par_M005;
	int par_MAX_PROC_AUS;
	int par_MAX_SLAVE;
	int par_MAX_MODEL;
	char spare_head_1[100];
	HEADER_REGISTRAZIONI hdrg;
	char spare_head_2[100];
	} HEAD_DBPUNTI;

typedef struct {
	float tempo;
	float ritardo;
	float timescaling;
	float stepscaling;
	int stato;
	int stepcr;
	int numcr;
	int stepdb;
	float dt[MAX_MODEL];
	float tempo_task[MAX_MODEL];
	STAT_PROC  task_statistics[MAX_MODEL];
	STAT_PROC  aus_statistics[MAX_PROC_AUS];
	} STAT_DBPUNTI;

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        RtInitializeDbPuntiProc initialize; /* metodo di inizializzazione DB  */
	RtCloseDbPuntiProc close;	/* metodo di chiusura dell'oggetto */
        } RtDbPuntiClassPart;

/*
 Dichiarazione del record completo di classe
 */
typedef struct _RtDbPuntiClassRec {
         RtDbPuntiClassPart    rtDbPunti_class;
        } RtDbPuntiClassRec;

extern RtDbPuntiClassRec rtDbPuntiClassRec;

/*
 Nuovi campi per il record del widget RtDbPunti
 */

typedef struct {
        /* risorse  */
	RtErroreOggetto errore; /* oggetto per la gestione degli errori */
	Boolean errore_privato; /* True l'oggetto e' privato all'oggetto */
	HEAD_DBPUNTI *punt_head;
	int id_head;
	int size;
	float *punt_data;
	STAT_DBPUNTI *punt_statistics;
	TIPO_PERT    *perturbazioni;
	TIPO_PERT    *perturbazioni_att;
	SNTAB        *snapshot;
#if defined BACKTRACK
	BKTAB        *backtrack;
#endif
	int id_data;
	
        } RtDbPuntiPart;

/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _RtDbPuntiRec {
        RtDbPuntiPart rtDbPunti;
        } RtDbPuntiRec;

#endif /* _RtDbPuntiP_h */
