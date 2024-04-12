/**********************************************************************
*
*       C Header:               OlDatabaseTopologiaP.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Mar 18 14:57:28 1998 %
*
**********************************************************************/
/*
   modulo OlDatabaseTopologiaP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlDatabaseTopologiaP.h	5.1
*/
/*
 * OlDatabaseTopologiaP.h - definizioni private per l'oggetto OlDatabaseTopologia
 */
#ifndef _OlDatabaseTopologiaP_h
#define _OlDatabaseTopologiaP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/


#include <Xm/XmP.h>
#include <Xl/XlP.h>
	
/*
 Inclusione dell'header file pubblico
*/
#include <Ol/OlDatabaseTopologia.h>



typedef Boolean (*OlInitializeProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlTagToIndProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumVariabiliProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumModelliProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumBlocchiProc) (
#if NeedFunctionPrototypes
#endif
);

typedef VARIABILI* (*OlProgToVarProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlIndToModProc) (
#if NeedFunctionPrototypes
#endif
);



/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        OlInitializeProc initialize;    /* metodo di inizializzazione DB  */
	OlTagToIndProc  tagtoind;       /* metodo di estrazione di indirizzo 
					   dal database a partire dal database 
					   e da una stringa terminata contenete
					   il nome della variabile           */
	OlTagToIndProc  tagtoinds;       /* metodo di estrazione di indirizzo 
					   dal database a partire dal database 
					   e da una stringa terminata contenete
					   il nome della variabile per SCADA */
	OlNumModelliProc nummodelli;    /* il metodo ritorna il numero dei
					   modelli		*/
	OlNumBlocchiProc numblocchi;    /* il metodo ritorna il numero dei
					   blocchi di un modello specificato
					   1 .. num modelli		*/
	OlNumVariabiliProc numvariabili;/* il metodo ritorna il numero delle
				           variabili definite nel database  */
	OlProgToVarProc progtovar;      /* il metodo ritorna il puntatore
				           alla struttura variabili a partire
					   dal progressivo                  */
	OlIndToModProc indtomod;        /* il metodo ritorna il numero
				           del modello a partire
					   dall'indirizzo                  */
        } OlDatabaseTopologiaClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _OlDatabaseTopologiaClassRec {
         OlDatabaseTopologiaClassPart    oldatabaseTopologia_class;
        } OlDatabaseTopologiaClassRec;

extern OlDatabaseTopologiaClassRec olDatabaseTopologiaClassRec;

/*
 Nuovi campi per il record del widget OlDatabaseTopologia
 */
typedef struct {
        /* risorse  */
        char *nome_database;      /* nome del database             */
	char *nome_file;          /* nome del file di database     */
	int shr_key;              /* chiave di accesso al database */
	char *file_subs;	  /* nome file dei SubSystem       */
	char *file_comp;	  /* nome file dei Component	   */
	char *file_varcc;	  /* nome file variabili default CC */
        /* file fnomi.rtf per calcolate SCADA*/
        FILE *fnomip;
	/* risorse private */
	int tipo_db;
	/* risorse per database tipo DB_XLRTF */
	int shmvar;               /* id shared                  */
	int size;		  /* size della shared memory   */
	char *id;                 /* puntatore all'inizio della shared memory */
	VARIABILI *variabili;     /* puntatore all'inizio dell'area delle
				     variabili  */
        } OlDatabaseTopologiaPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _OlDatabaseTopologiaRec {
        OlDatabaseTopologiaPart oldatabaseTopologia;
        } OlDatabaseTopologiaRec;

#endif /* _OlDatabaseTopologiaP_h */
