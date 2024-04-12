/**********************************************************************
*
*       C Header:               XlPictographP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Thu Jul 17 17:22:33 1997 %
*
**********************************************************************/
/*
   modulo XlPictographP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPictographP.h	5.1
*/
/*
 * PictographP.h - definizioni private per l'oggetto Pictograph
 */ 
#ifndef _XlPictographP_h
#define _XlPictographP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlUtilBkg.h>
/*
 Inclusione dell'header file pubblico
*/
#include "XlPictograph.h"


/* struttura per la gestione della animazione
   derivata da file .prg
*/
typedef struct {
        int idvar;               /* id zona di animazione 1,2,3,4 */
        XlAnimatedColor animaz;  /* colore animato relativo alla zona */
        GC gc_animaz;            /* graphic context */
        int nval;                /* numero valori float */
        int *val;                /* elenco valori float */
} XlPictographAnimazRow;

typedef struct {
	char nome_program[100];  /* nome del programma di animazione */
        Screen *scr;		 /* screen relativo al caricamento del programma */
        int  nrow; 
        XlPictographAnimazRow *row; /* vettore di righe di valori */
} XlPictographAnimaz;

/*
 Strutture relative alla nuova Classe
 */

typedef struct {
	BCK_OBJ *sfondo;     /*  sfondo dell'pictograph */
	int rotate;	     /* rotazione angolare del pictograph */
	int ass_rotate;      /* rotazione assiale del pictograph */
        int top_border;       /* bordo libero in alto     */
        int bottom_border;    /* bordo libero in basso    */
        int left_border;      /* bordo libero a sinistra  */
        int right_border;     /* bordo libero a destra    */
	Display *display;    /* display su cui e' visualizzata la pictograph */
	int num_obj;
	char nome_pictograph[100];  /* nome dell'pictograph */
	int dim[4];      /* x min y min x max x max */
	int contatore;  /* per il momento non viene utilizzato */
	} XlPictographSfondo;

typedef struct {
        int num_pictograph;
	XlPictographSfondo *sfondi;
        int num_program;
        XlPictographAnimaz *programs;
	} XlPictographClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlPictographClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlPictographClassPart    xlpictograph_class;
	} XlPictographClassRec;

extern XlPictographClassRec xlPictographClassRec;

/*
 Nuovi campi per il record del widget XlPictograph
 */
typedef struct {
	/* risorse  
	*/
	char * nome_file_pictograph; /* nome del file contenete il pictograph*/
	char * nome_file_program; /* nome del file contenente il programma*/
	char * component;      /* nome del componente    */
	char * subsystem;       /* nome del sottosistema  */
        int top_border;       /* bordo libero in alto     */
        int bottom_border;    /* bordo libero in basso    */
        int left_border;      /* bordo libero a sinistra  */
        int right_border;     /* bordo libero a destra    */
	
	/* struttura per la gestione del colore del frame
	*/
        CAMBIO_COLORE_FRAME frame;

	/* struttura per la gestione del cambio colore
	*/
	CAMBIO_COLORE_PICT cambio_colore[4];


        /* variabili di stato (privato)
        */
        GC clear_gc;
        Boolean owOpen;	             /* gestione del frame */
	int primo_refresh;
	float old_frameval;
	Pixel OldPixel1;
	Pixel OldPixel2;
	Pixel OldPixel3;
	Pixel OldPixel4;
        Boolean blinking[4];
        float blink_freq[4];
	Region region;      /* regione di ridisegno */
        XlPictographAnimaz *program;
	int index_program;    /* indice programma all' interno della cache */
	BCK_OBJ *sfondo;
	} XlPictographPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlPictographRec {
	CorePart   core;
	XlCorePart xlcore;
	XlPictographPart  pictograph;
	} XlPictographRec;


#endif /* _XlPictograph */
