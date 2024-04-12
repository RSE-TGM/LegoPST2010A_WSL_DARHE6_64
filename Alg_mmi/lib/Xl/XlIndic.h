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
   modulo XlIndic.h
   tipo 
   release 5.3
   data 1/5/96
   reserved @(#)XlIndic.h	5.3
*/
/*
 * XlIndic.h - file di include pubblico per l'utilizzo del widget
 *             indic
 */
#ifndef _XlIndic_h
#define _XlIndic_h


/*
 nomi di risorse utilizzate internamente al indic
 */
#define XlNagoFg   "agoFg"
#define XlCAgoFg   "AgoFg"
#define XlDagoFg   "Ago or bar color"
#define XlNextraRangeSup "extraRangeSup"
#define XlCExtraRangeSup "ExtraRangeSup"
#define XlDextraRangeSup "Superior extra range"
#define XlNtipoInd "tipoInd"
#define XlCTipoInd "TipoInd"
#define XlDtipoInd "Indicator type"
#define XlOtipoInd "Indicatore ago,Indicatore barra,Indicatore display,Indicatore a istogramma crescente,Indicatore a istogramma decrescente"


/* costanti utilizzabili per settare il tipo di XlIndic */

#define INDICATORE_AGO  0
#define INDICATORE_BARRA  1
#define INDICATORE_DISPLAY  2
#define INDICATORE_ISTOGRAMMA_CRES  3
#define INDICATORE_ISTOGRAMMA_DEC  4
#define INDICATORE_DEFAULT  INDICATORE_AGO
#define _INDIC_MAX     4
#define NO_ROTABLE      0
#define ROTABLE         1

/*
 Valore di default per la risorsa extra_range
*/
#define EXTRA_RANGE_SUP  "0."
/* declare the class constant */
extern WidgetClass xlIndicWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Indic */
typedef struct _XlIndicClassRec *XlIndicWidgetClass;
typedef struct _XlIndicRec *XlIndicWidget;

#endif /* _XlIndic_h */

