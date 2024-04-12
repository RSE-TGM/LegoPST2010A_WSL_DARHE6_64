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
   modulo RtErroreP.h
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)RtErroreP.h	5.1
*/
/*
 * RtErroreP.h - definizioni private per l'oggetto RtErrore
 */
#ifndef _RtErroreP_h
#define _RtErroreP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/
#include <Rt/RtP.h>

/*
 Inclusione dell'header file pubblico
*/
#include <Rt/RtErrore.h>

typedef Boolean (*RtInitializeErroreProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*RtCloseErroreProc) (

#if NeedFunctionPrototypes
#endif
);

typedef void (*RtVisualizzaErroreProc) (
#if NeedFunctionPrototypes
#endif
);

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        RtInitializeErroreProc initialize; /* metodo di inizializzazione DB  */
	RtCloseErroreProc close;	/* metodo di chiusura dell'oggetto */
	RtVisualizzaErroreProc visualizza; /* metodo di visualizzazione dell'errore */ 
        } RtErroreClassPart;

/*
 Dichiarazione del record completo di classe
 */
typedef struct _RtErroreClassRec {
         RtErroreClassPart    rtErrore_class;
        } RtErroreClassRec;

extern RtErroreClassRec rtErroreClassRec;

/*
 Nuovi campi per il record del widget RtErrore
 */

typedef struct {
        /* risorse  */
	int tipo_output;
	char *applicazione;
	RtErroreInfoList info_err;
	int num_info_err;
        } RtErrorePart;

/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _RtErroreRec {
        RtErrorePart rtErrore;
        } RtErroreRec;

#endif /* _RtErroreP_h */
