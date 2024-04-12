/**********************************************************************
*
*       C Header:               XlIndicTelep.h
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Wed Oct 23 15:58:31 2002 %
*
**********************************************************************/
/*
   modulo XlIndicTelep.h
   tipo 
   release 1.0
   data 21/5/96
   reserved @(#)XlIndicTelep.h	1.0
*/
/*
 * XlIndicTelep.h - file di include pubblico per l'utilizzo del widget
 *             indic
 */
#ifndef _XlIndicTelep_h
#define _XlIndicTelep_h

#define XlNindicTelep "indicTelep"
#define XlCIndicTelep "IndicTelep"

/*
 nomi di risorse utilizzate internamente al indic
 */
#define XlNagoFg_tel   "agoFg"
#define XlCAgoFg_tel   "AgoFg"
#define XlDagoFg_tel   "Indicator foreground"

#define XlNbordinoFg   "bordinoFg"
#define XlCBordinoFg   "BordinoFg"
#define XlDbordinoFg   "Indicator border foreground"

#define XlNbordinoWidth   "bordinoWidth"
#define XlCBordinoWidth   "BordinoWidth"
#define XlDbordinoWidth   "Indicator border width"

#define XlNindicatorText "indicText"
#define XlCIndicatorText "IndicText"
#define XlDindicatorText "Indicator Text"

#define XlNextraRangeSup "extraRangeSup"
#define XlCExtraRangeSup "ExtraRangeSup"
#define XlDextraRangeSup "Superior extra range"
#define XlNtipoInd "tipoInd"
#define XlCTipoInd "TipoInd"
#define XlDtipoInd "Indicator type"

/* ATTE.NE commento per rilascio versione senza istogramma
#define XlOtipoInd "Indicator led rectang,Indicator led circle,Indicator text (on/off animation),Indicator text (bkg animation),Indicator display,Indicator a istogramma crescente,Indicator a istogramma decrescente"
*/
#define XlOtipoInd "Indicator led rectang,Indicator led circle,Indicator text (on/off animation),Indicator text (bkg animation),Indicator display,Indicator Bar (Increase),Indicator Bar (Decrease)"

/* costanti utilizzabili per settare il tipo di XlIndicTelep */

#define INDICATORE_LED_RECT  0           /* led rettangolare */
#define INDICATORE_LED_CIRCLE  1         /* led circolare */
#define INDICATORE_TEXT_FG_AN  2         /* label che appare o scompare */
#define INDICATORE_TEXT_BG_AN  3         /* label fissa con bkg variabile */
#define INDICATORE_DISPLAY  4            /* indicatore display */
#define INDICATORE_ISTOGRAMMA_CRES  5    /* Indicatore bar crescente */
#define INDICATORE_ISTOGRAMMA_DEC  6     /* Indicatore Bar decrescente */
#define INDICATORE_DEFAULT  INDICATORE_LED_RECT
#define _INDIC_MAX_tel     7
#define NO_ROTABLE         0
#define ROTABLE            1


/*
Valore della max lung. stringa testo
*/
#define MAXLUNTESTO	256

/*
 Valore di default per la risorsa extra_range
*/
#define EXTRA_RANGE_SUP  "0."
/* declare the class constant */
extern WidgetClass xlIndicTelepWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di IndicTelep */
typedef struct _XlIndicTelepClassRec *XlIndicTelepWidgetClass;
typedef struct _XlIndicTelepRec *XlIndicTelepWidget;

#endif /* _XlIndicTelep_h */

