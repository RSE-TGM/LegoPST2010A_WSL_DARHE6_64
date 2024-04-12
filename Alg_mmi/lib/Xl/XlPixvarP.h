/**********************************************************************
*
*       C Header:               XlPixvarP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Mon Nov  3 16:33:19 1997 %
*
**********************************************************************/
/*
   modulo XlPixvarP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPixvarP.h	5.1
*/
/*
 * PixvarP.h - definizioni private per l'oggetto Pixvar
 */ 
#ifndef _XlPixvarP_h
#define _XlPixvarP_h
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
#include "XlPixvar.h"


/* struttura per la gestione della animazione
   derivata da file .prg
*/
typedef struct {
        int idvar;               /* id zona di animazione 1,2,3,4 */
        XlAnimatedColor animaz;  /* colore animato relativo alla zona */
        GC gc_animaz;            /* graphic context */
        int nval;                /* numero valori float */
        int *val;                /* elenco valori float */
} XlPixvarAnimazRow;

typedef struct {
	char nome_program[100];  /* nome del programma di animazione */
        Screen *scr;		 /* screen relativo al caricamento del programma */
        int  nrow; 
        XlPixvarAnimazRow *row; /* vettore di righe di valori */
} XlPixvarAnimaz;

/*
 Strutture relative alla nuova Classe
*/

typedef struct {
         int num_pixvar;
         int num_program;
         XlPixvarAnimaz *programs;
	} XlPixvarClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlPixvarClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlPixvarClassPart    xlpixvar_class;
	} XlPixvarClassRec;

extern XlPixvarClassRec xlPixvarClassRec;

/*
 Nuovi campi per il record del widget XlPixvar
 */
typedef struct {
	/* risorse  
	*/
	char * component;    /* nome del componente    */
	char * subsystem;    /* nome del sottosistema  */
        char * normalfont;  /* nome del font utilizzato per le scritte */
	int  pixtype;       /* specifica il contenuto di nome_pix 0=Pixmap 1=Stringa */
        char *nome_pix1;     /* contiene una stringa o il nome del file pixmap */
        char *nome_pix2;
        char *nome_pix3;
        char *nome_pix4;
	char * nome_file_program; /* nome del file contenente il programma*/
        int top_border;       /* bordo libero in alto     */
        int bottom_border;    /* bordo libero in basso    */
        int left_border;      /* bordo libero a sinistra  */
        int right_border;     /* bordo libero a destra    */
	int rotate;	     /* rotazione angolare del pixvar */
	int ass_rotate;      /* rotazione assiale del pixvar */

	/* struttura per la gestione del cambio colore
	*/
	CAMBIO_COLORE_PICT cambio_colore[1];

        /* variabili di stato (privato)
        */
        GC clear_gc;
	int primo_refresh;
        Boolean blinking;
        float blink_freq;
	Region region;             /* regione di ridisegno */
        XlPixvarAnimaz *program;
	int index_program;         /* indice programma all' interno della cache */
        Pixmap pix1;
        Pixmap pix2;
        Pixmap pix3;
        Pixmap pix4;
        int prevIndPix;            /* indice di pixmap/stringa visualizzato nel ciclo precedente */
        int currIndPix;            /* indice di pixmap/stringa da visualizzare */
        XFontStruct *font_info;
        XmFontList font_list;
        Dimension curr_width;
        Dimension curr_height;
	} XlPixvarPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlPixvarRec {
	CorePart   core;
	XlCorePart xlcore;
	XlPixvarPart  pixvar;
	} XlPixvarRec;


#endif /* _XlPixvar */
