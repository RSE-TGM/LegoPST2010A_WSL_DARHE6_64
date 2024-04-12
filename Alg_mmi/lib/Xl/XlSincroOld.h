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
   modulo XlSincroOld.h
   tipo 
   release 1.3
   data 1/9/96
   reserved @(#)XlSincroOld.h	1.3
*/
/*
 * XlSincroOld.h - file di include pubblico per l'utilizzo del widget
 *             sincroOld
 */
#ifndef _XlSicroOld_h
#define _XlSincroOld_h


/*
 nomi di risorse utilizzate internamente al sincroOld
 */
#define XlNagoFg   "agoFg"
#define XlCAgoFg   "AgoFg"
#define XlDagoFg   "Ago or bar color"
#define XlNsincroOldDeltaFase "sincroDeltaFase"
#define XlCSincroOldDeltaFase "SincroDeltaFase"
#define XlDsincroOldDeltaFase "Differenza fasi"

#define XlNsincroOldDeltaV   "sincroDeltaV"
#define XlCSincroOldDeltaV   "SincroDeltaV"
#define XlDsincroOldDeltaV   "Differenza tensioni"

#define XlNsincroOldDeltaF   "sincroDeltaF"
#define XlCSincroOldDeltaF   "SincroDeltaF"
#define XlDsincroOldDeltaF   "Differenza frequenze"

#define XlNsincroOldTimeAgg   "sincroTimeAgg"
#define XlCSincroOldTimeAgg   "SincroTimeAgg"
#define XlDsincroOldTimeAgg   "Tempo di aggiornamento (ms)"





/* costanti utilizzabili per settare il tipo di XlIndic */



#define NO_ROTABLE      0
#define ROTABLE         1

/*
 Valore di default per la risorsa extra_range
*/

#define SINCRO_DELTA_FASE       "5."
#define SINCRO_DELTA_V		"5."
#define SINCRO_DELTA_F		"0.1" 
#define SINCRO_TIME_AGG		"40."

/*dichiarazioni delle variabili*/

#define XlNvarInput_1	"varInput_1"
#define XlCVarInput_1	"VarInput_1"
#define XlDvarInput_1	"Frequenza di rete (Hz)"

#define XlNvarInput_2	"varInput_2"
#define XlCVarInput_2	"VarInput_2"
#define XlDvarInput_2	"Frequenza alternatore (Hz)"

#define XlNvarInput_3	"varInput_3"
#define XlCVarInput_3	"VarInput_3"
#define XlDvarInput_3	"Tensione di rete (V)"

#define XlNvarInput_4	"varInput_4"
#define XlCVarInput_4	"VarInput_4"
#define XlDvarInput_4	"Tensione alternatore (V)"

#define XlNvarInput_5	"varInput_5"
#define XlCVarInput_5	"VarInput_5"
#define XlDvarInput_5	"Sincronoscopio attivo"

#define XlNvarInput_6	"varInput_6"
#define XlCVarInput_6	"VarInput_6"
#define XlDvarInput_6	"Richiesta di parallelo"



#define XlNvarOut_1	"varOut_1"
#define XlCVarOut_1	"VarOut_1"
#define XlDvarOut_1	"Consenso parallelo"

#define XlNvarOut_2	"varOut_2"
#define XlCVarOut_2	"VarOut_2"
#define XlDvarOut_2	"Mancanza di consenso"

#define TREFRESH	400
#define DELTA_REF	15
#define TREFRESH_FAST	TREFRESH/DELTA_REF

/*
Procedura usata per estrarre il valore di una var di output
*/	


static void DisegnaAgo(Widget ,float ,int );

/* declare the class constant */
extern WidgetClass xlSincroOldWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Sincro */
typedef struct _XlSincroOldClassRec *XlSincroOldWidgetClass;
typedef struct _XlSincroOldRec *XlSincroOldWidget;

#endif /* _XlSincroOld_h */

