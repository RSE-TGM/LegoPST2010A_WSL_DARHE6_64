/**********************************************************************
*
*       C Header:               OlDatabasePuntiP.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Jul 29 16:17:11 1998 %
*
**********************************************************************/

/*
 * OlDatabasePuntiP.h - definizioni private per l'oggetto OlDatabasePunti
 */
#ifndef _OlDatabasePuntiP_h
#define _OlDatabasePuntiP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/


#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Rt/RtDbPunti.h>

	
/*
 Inclusione dell'header file pubblico
*/
#include <Ol/OlDatabasePunti.h>


#include <client_scada.h>

typedef Boolean (*OlInitializeDbPProc) (
#if NeedFunctionPrototypes
#endif
);


typedef float (*OlValVarDbPProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlRefreshConfinfoDbPProc) (
#if NeedFunctionPrototypes
#endif
);

typedef float (*OlGetTimeDbPProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlAddPageDbPProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlDelPageDbPProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlGetDataAllarmiProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlCommandAllarmiProc) (
#if NeedFunctionPrototypes
#endif
);


/*
 			Strutture relative alla pagina 
Modificata da Fabio 14/1/97 (Merge fra scada e simula )
	
 */

struct pagine_in_refresh_st {
		int id_shm;
		int id_shmS;   /* id shared mem per dati scada */
		int stato;
		int num_punti;
		int num_puntiS; /* numero punti scada di una pag */
		Widget drawing;
		float *var;
		float *varS;   /* puntatore a variabile scada attiva */
		};

typedef struct pagine_in_refresh_st PAGINE_IN_REFRESH;

#define MAX_PAGINE_IN_REFRESH 200

typedef struct {
        OlInitializeDbPProc initialize;    /* metodo di inizializzazione DB  */
	OlValVarDbPProc valvar;            /* ritorna il valore di una variabile
					   in funzione dell'indirizzo.
				           il metodo e' relativo al database
					   DB_XLSIMUL                       */
	OlRefreshConfinfoDbPProc refreshconfinfo; /*
					   metodo di refresh delle confinfo  */
        OlGetTimeDbPProc getTime;          /* ritorna il tempo del simulatore */
	OlAddPageDbPProc addPage;          /* aggiunge una nuova pagina all'
					      elenco delle pagine in refresh */

        OlDelPageDbPProc delPage;          /* elimina una pagina dalla 
					      tabella */
	OlGetDataAllarmiProc getDataAllarmi;  /* raccoglie i dati degli
						Allarmi */
	OlCommandAllarmiProc commandAllarmi;  /* Funzione per i comandi
						di scrool e riconoscimento
						degli allarmi   */
        } OlDatabasePuntiClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _OlDatabasePuntiClassRec {
         OlDatabasePuntiClassPart    oldatabasePunti_class;
        } OlDatabasePuntiClassRec;

extern OlDatabasePuntiClassRec olDatabasePuntiClassRec;

/*
	Struttura fondamentale oggetto OlDatabasePunti
Modifica di fabio 14/1/97 (merge fra scada e simulatore)
N.B. il nome del database deve essere il primo campo della struttura

 */
typedef struct {
        /* risorse  */
        char *nome_database;      /* nome del database             */
        char *hostname;           /* nome dell'host simulatore     */
	char *hostnameS;          /* nome dell'host scada	   */
	int codice_host;	  /* codice dopo host_name simulat.*/
	int codice_hostS;	  /* codice dopo host_name scada   */
	int client_mmi_on;        /* situazione client attivi      */
	int client_scada_on;
	int id_msg_client;        /* coda per le richieste di aggiornamento */
	int id_msg_clientS;	  /* coda per richieste agg. da scada */
	pid_t pid_client;         /* pid processo client da simulatore */
	pid_t pid_clientS;        /* pid processo client da scada */
	int shr_key;              /* chiave di accesso al database simulatore*/
	int shr_keyS;		  /* chiave accesso shared mem per var scada */
        int port_daemon;          /* porta X demone_mmi */
	RtDbPuntiOggetto dbpunti;
	/* risorse private */
	int tipo_db;
	PAGINE_IN_REFRESH *pagine_db;
	int shared_set;
	/* risorse per il database tipo DB_XLSIMUL */
	float *var;
	float *varS;        /* puntatore a variabile attiva */
	float *varCai;      /* puntatore a PAGINA_CAI */
	/* puntatore all'area shared contenete i dati delgi allarmi */
	char *allarm_data;
	int allarm_data_id; /* id shr memory allarmi */
	int allarm_flag;  /* =1 pagina allarmi aperta  */
	OlTreeObject root_oltree;   /* elemento di root di OlTree */
        int sem_mmi;              /* semaforo per sincr. miniASD */
        int sem_scada;
        OW_SHM shmMiniASD[MAX_NUM_OW]; /* strutt. shm per miniASD */
        } OlDatabasePuntiPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _OlDatabasePuntiRec {
        OlDatabasePuntiPart oldatabasePunti;
        } OlDatabasePuntiRec;

#endif /* _OlDatabasePuntiP_h */
