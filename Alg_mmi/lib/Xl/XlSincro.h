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
   modulo XlSincro.h
   tipo 
   release 1.4
   data 1/9/96
   reserved @(#)XlSincro.h	1.4
*/
/*
 * XlSincro.h - file di include pubblico per l'utilizzo del widget
 *             sincro
 */
#ifndef _XlSicro_h
#define _XlSincro_h


/*
 nomi di risorse utilizzate internamente al sincro
 */
#define XlNagoFg   "agoFg"
#define XlCAgoFg   "AgoFg"
#define XlDagoFg   "Ago or bar color"







/* costanti utilizzabili per settare il tipo di XlIndic */



#define NO_ROTABLE      0
#define ROTABLE         1

/*
 Valore di default per la risorsa extra_range
*/


#define SINCRO_TIME_AGG		"40."

/*dichiarazioni delle variabili*/

#define XlNvarInput_1	"varInput_1"
#define XlCVarInput_1	"VarInput_1"
#define XlDvarInput_1	"Valore della fase"

#define XlNvarInput_5	"varInput_5"
#define XlCVarInput_5	"VarInput_5"
#define XlDvarInput_5	"Sincronoscopio attivo"

#define XlNvarInput_6	"varInput_6"
#define XlCVarInput_6	"VarInput_6"
#define XlDvarInput_6	"Richiesta di parallelo"

static void DisegnaAgo(Widget ,float ,int );

/* declare the class constant */
extern WidgetClass xlSincroWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Sincro */
typedef struct _XlSincroClassRec *XlSincroWidgetClass;
typedef struct _XlSincroRec *XlSincroWidget;

#endif /* _XlSincro_h */

