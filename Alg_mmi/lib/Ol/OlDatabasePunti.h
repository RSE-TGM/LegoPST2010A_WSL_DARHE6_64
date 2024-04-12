/**********************************************************************
*
*       C Header:               OlDatabasePunti.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Nov  4 12:21:30 1998 %
*
**********************************************************************/
/*
   modulo OlDatabasePunti.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlDatabasePunti.h	5.1
*/
/*
 * OlDatabasePunti.h - file di include pubblico per l'utilizzo del database
 */
#ifndef _OlDatabasePunti_h
#define _OlDatabasePunti_h

#include <Rt/RtMemory.h>
#include <Ol/OlTree.h>
#include <Cs/Cs.h>

/* dichiarazione tipi per Classe e Instanziazione di OlDatabasePunti */
typedef struct _OlDatabasePuntiClassRec *OlDatabasePuntiObjectClass;
typedef struct _OlDatabasePuntiRec *OlDatabasePuntiObject;

#define DB_XLSIMUL             0          /* database simulatore */ 

#define DB_XLSCADA_CLIENT      1	/* database solo scada 
					     residente             */ 
#define DB_XLSIMUL_CLIENT      2          /* database simulatore                   					     non residente          */
#define DB_XLCLIENTS           3  /* database con client scada e client mmi */



/*
Tempo di refresh pagina fittizia situazione allarmi
*/
#define T_REFRESH_CAI   10      /* tempo di refresh pagina fittizia per Cai */
                                /* espresso in decimi di secondo            */
#define PAGINA_CAI   MAX_PAGINE_IN_REFRESH    /* indice pagina per pagina per Cai         */
/* 
Costante per timeout eliminazione pag tempo all' atto
della distruzione di OldatabasePunti
*/
#define TIME_DEL_PAG 9
/*
	nome del processo client per l'aggiornamento 
*/
#if defined SCADA_MMI
#define PROCESSO_CLIENT		"client_scada"
#else
#define PROCESSO_CLIENT		"client_mmi"
#define PROCESSO_CLIENTS	"client_scada"
#endif

#define ELENCO_PUNTI_ANALOGICI		0
#define ELENCO_PUNTI_DIGITALI		1
/*
definizione massima lunghezza codice di hostname
*/
#define MAXCODE	5
/*
	define per la gestione degli allarmi
*/
#define OL_MODO_ARCHIVIO	1
#define OL_MODO_ALLARMI		2
#define OL_RICONOSCI_ALLARMI	3
#define OL_AVANTI_ALLARMI	4
#define OL_INDIETRO_ALLARMI	5
#define OL_CHIUDI_ALLARMI	6

/*
Definisci valori per oggetti delle O.W
*/
#define MAX_NUM_OW              20
typedef struct {
	char *allarm_data;      /* puntatore shm allarmi per miniASD */
	char *manual_data;      /* puntatore shm segnali manual per miniASD */
        int id_allarm_data;     /* id shm allarmi per miniASD */
        int id_manual_data;     /* id shm allarmi per miniASD */
        int shmvid_allarm;     /* id shmvm allarmi per miniASD */
        int shmvid_manual;    /* id shmvm allarmi per miniASD */
        short indice;           /* indice della struttura nello array */
        } OW_SHM;
/*
	procedure utilizzabili per la creazione e la distruzione
	dell'oggetto OlDatabasePunti
*/
OlDatabasePuntiObject OlCreateDatabasePunti();
Boolean OlDestroyDatabasePunti();
Boolean OlSetDataPage();
Boolean OlUnsetDataPage();
Boolean OlGetDataStatus();
Boolean OlChangePointInPage();
int OlAddSinglePoint();
Boolean OlIsDigital();
Boolean OlCheckDatabasePuntiStatus();
Boolean OlCanOpenAllarmPage();
int OlDataBasePuntiType();
float OlGetTime();
Boolean OlGetDataAllarmi();
Boolean OlGetDataAllarmiMiniASD();
Boolean OlCommandAllarmi(OlDatabasePuntiObject , int);
Boolean OlTeleperm_richiediAllarmi();
Boolean OlRichiediAllarmiMiniASD(OlDatabasePuntiObject,unsigned char *,int,short,short);

Boolean OlSetOpeningAllarmPage(OlDatabasePuntiObject , int );

Boolean OlRiconosciAllarmiMiniASD(OlDatabasePuntiObject database,
                                        unsigned char *gerarchia,
                                        int indiceOW,short filtro,
                                        short tipo_allarme,
                                        int n_all, int indice_all);
Boolean OlRiconosciManualiMiniASD(OlDatabasePuntiObject database,
                                        unsigned char *gerarchia,
                                        int indiceOW,short filtro,
                                        short tipo_allarme,
                                        int n_all,int indice_all);
/*
Boolean OlGetDatiMiniASD(OlDatabasePuntiObject database,DATI_ALLARMI_SHM *dati_allarm, DATI_ALLARMI_SHM *dati_manual,int indice);
*/
/*Boolean OlGetDatiMiniASD();*/
int OlAddPage();
int  OlInserisci_shmMiniASD();
int  OlEliminai_shmMiniASD();
int OlInizia_shmMiniASD();
Boolean OlDelPage();
#endif /* _OlDatabasePunti_h */

