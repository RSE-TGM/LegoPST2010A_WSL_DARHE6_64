/**********************************************************************
*
*       C Header:               OlPertP.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Jun 17 15:15:54 1997 %
*
**********************************************************************/
/*
   modulo OlPertP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlPertP.h	5.1
*/
/*
 * OlPertP.h - definizioni private per l'oggetto OlPert
 */
#ifndef _OlPertP_h
#define _OlPertP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/


#include <Xm/XmP.h>
#include <Xl/XlP.h>
	
/*
 Inclusione dell'header file pubblico
*/
#include <Ol/OlPert.h>

typedef Boolean (*OlInitializePertProc) (
#if NeedFunctionPrototypes
#endif
);


typedef Boolean (*OlPertSendProc) (
#if NeedFunctionPrototypes
#endif
);


/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        OlInitializePertProc initialize_pert;     /* metodo 
						di inizializzazione */
	OlPertSendProc pertsend;          /* metodo di invio di una
					     perturbazione          */
        } OlPertClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _OlPertClassRec {
         OlPertClassPart    olpert_class;
        } OlPertClassRec;

extern OlPertClassRec olPertClassRec;

/*
 Nuovi campi per il record del widget OlPert
 */
typedef struct {
	char *nome_database;
	int shr_key;              /* chiave di accesso alla coda */
        /* risorse  private*/
	int   id_msg;		/* coda di messaggi */
        } OlPertPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _OlPertRec {
        OlPertPart olpert;
        } OlPertRec;

#endif /* _OlPertP_h */
