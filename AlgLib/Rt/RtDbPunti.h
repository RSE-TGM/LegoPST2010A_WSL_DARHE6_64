/**********************************************************************
*
*       C Header:               RtDbPunti.h
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:35:36 1997 %
*
**********************************************************************/
/*
   modulo RtDbPunti.h
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)RtDbPunti.h	5.1
*/
/*
 * RtDbPunti.h - file di include pubblico 
 */
#ifndef _RtDbPunti_h
#define _RtDbPunti_h

#include <sys/types.h>
#include <Rt/Rt.h>
#include <Rt/RtErrore.h>
#include <Rt/RtMemory.h>

#include <statistics.h>
#include <comandi.h>

/*
 nomi di risorse utilizzate internamente a RtDbPunti
 */


/* dichiarazione tipi per Classe e Instanziazione di RtDbPunti */
typedef struct _RtDbPuntiClassRec *RtDbPuntiOggettoClass;
typedef struct _RtDbPuntiRec *RtDbPuntiOggetto;

/*
 Definizioni di uso generale riguardanti l'oggetto 
*/
#define DB_PUNTI_INT    0  /* database interno al simulatore */
#define DB_PUNTI_SHARED 1  /* database ufficiale del simulatore */

typedef struct {
        pid_t pid;
        float cpu_use;
        } STAT_PROC;

/*
	procedure utilizzabili per la creazione  la distruzione
	e in generale per la gestione dell'oggetto RtDbPunti
*/
RtDbPuntiOggetto RtCreateDbPunti(RtErroreOggetto, char *, int, SIMULATOR*);
Boolean RtDestroyDbPunti(RtDbPuntiOggetto );
int RtDbPNumeroModelli(RtDbPuntiOggetto );
int RtDbPInizioModelli(RtDbPuntiOggetto ,int);

int RtDbPGetHeaderReg(RtDbPuntiOggetto dbpunti, HEADER_REGISTRAZIONI *hdreg);
int RtDbPNumStatiModelli(RtDbPuntiOggetto dbpunti,int mod);
int RtDbPNumIngModelli(RtDbPuntiOggetto dbpunti,int mod);
int RtDbPNumDerivModelli(RtDbPuntiOggetto dbpunti,int mod);
int RtDbPNumDatiModelli(RtDbPuntiOggetto dbpunti,int mod);

int RtDbPSizeModelli(RtDbPuntiOggetto ,int);

int RtDbPSizeHeader(RtDbPuntiOggetto dbpunti);

int RtDbPSizeData(RtDbPuntiOggetto );
Boolean RtDbPClearData(RtDbPuntiOggetto);
Boolean RtDbPGetValue(RtDbPuntiOggetto ,int, float *);
float   RtDbPGetValueD(RtDbPuntiOggetto ,int);
Boolean RtDbPPutValue(RtDbPuntiOggetto ,int, float);
Boolean RtDbPCopyValue(RtDbPuntiOggetto ,int, int);
Boolean RtDbPGetTime(RtDbPuntiOggetto , float *);
Boolean RtDbPPutTime(RtDbPuntiOggetto , float);
Boolean RtDbPGetDelay(RtDbPuntiOggetto , float *);
Boolean RtDbPPutDelay(RtDbPuntiOggetto , float);
Boolean RtDbPGetTimeScaling(RtDbPuntiOggetto , float *);
Boolean RtDbPPutTimeScaling(RtDbPuntiOggetto , float);
Boolean RtDbPGetStepScaling(RtDbPuntiOggetto , float *);
Boolean RtDbPPutStepScaling(RtDbPuntiOggetto , float);
Boolean RtDbPCopyDb(RtDbPuntiOggetto ,RtDbPuntiOggetto );

NUMERI_MODELLI *RtDbPGetPuntHeadmodelli(RtDbPuntiOggetto dbpunti);

TIPO_PERT *RtDbPGetPuntPert(RtDbPuntiOggetto);
TIPO_PERT *RtDbPGetPuntPertAtt(RtDbPuntiOggetto);
Boolean RtDbPGetStepCr(RtDbPuntiOggetto , int *);
Boolean RtDbPPutStepCr(RtDbPuntiOggetto , int);
Boolean RtDbPGetNumCr(RtDbPuntiOggetto , int *);
Boolean RtDbPPutNumCr(RtDbPuntiOggetto , int);
Boolean RtDbPGetStepDb(RtDbPuntiOggetto , int *);
Boolean RtDbPPutStepDb(RtDbPuntiOggetto , int);
Boolean RtDbPGetStato(RtDbPuntiOggetto , int *);
Boolean RtDbPPutStato(RtDbPuntiOggetto , int);
Boolean RtDbPGetDt(RtDbPuntiOggetto , int, float *);
Boolean RtDbPPutDt(RtDbPuntiOggetto , int, float);
STAT_PROC *RtDbPGetPuntTaskStat(RtDbPuntiOggetto, int);
STAT_PROC *RtDbPGetPuntAusStat(RtDbPuntiOggetto, int);
Boolean RtDbPGetTimeTask(RtDbPuntiOggetto , int, float *);
Boolean RtDbPPutTimeTask(RtDbPuntiOggetto , int, float);
float * RtDbPPuntData(RtDbPuntiOggetto);
SNTAB * RtDbPGetPuntSnapshot(RtDbPuntiOggetto);
#if defined BACKTRACK
BKTAB * RtDbPGetPuntBacktrack(RtDbPuntiOggetto);
#endif
int     RtDbPGetModelFromInd(RtDbPuntiOggetto,int);
#endif /* _RtDbPunti_h */
