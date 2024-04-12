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
   modulo XlGraficoP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlGraficoP.h	5.1
*/
/*
 * XlGraficoP.h.h - definizioni private per l'oggetto Grafico
 */ 
#ifndef _XlGraficoP_h
#define _XlGraficoP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlGrafico.h>

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int dummy;
	} XlGraficoClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlGraficoClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlGraficoClassPart   xlgrafico_class;
	} XlGraficoClassRec;

extern XlGraficoClassRec xlGraficoClassRec;

/*
 Nuovi campi per il record del widget XlGrafico
 */
typedef struct {
        /* risorse */
	int tipo;
	/* colori delle misure visualizzate */
	Pixel col_trend[4];
        /* Colore griglia  */
	Pixel col_grid;
	/* Path e nome del file grafici */
	char *nome_file_f22;
	/* Nome variabili da visualizzare */	
	char *nome_var[4];
	/* Descrizione delle variabili da visualizzare */
	char *descr_var[4];
	/*
	puntatore alla struttura delle variabili di stato
        del grafico (la struttura e' definita in XlGrafico.h)
	( corrispondono a variabili originariamente in common
            nella grafics)
	*/
	S_XLGRAFICO *p;
	/*  Flag per l'identificazione del primo refresh */
	Boolean primo_refresh;
	/*  Ampiezza in secondi dello spazio di memorizzazione dei dati
	    per il grafico RUNTIME  */
	int delta_tempo;
	/* numero massimo di campioni registrati per archivio run_time */
	int max_samples;
	/*  Etichetta del grafico runtime  */
	char *titolo_graf;
	/*  Variabili per settaggio scale delle quattro misure  */
	int autoscaling[4];
	float max_val[4];
	float min_val[4];
	/*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */
        PUNT_VARINP input[4];

	} XlGraficoPart;
	
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlGraficoRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlGraficoPart  grafico;
	} XlGraficoRec;

#endif /* _XlGraficoP_h */
