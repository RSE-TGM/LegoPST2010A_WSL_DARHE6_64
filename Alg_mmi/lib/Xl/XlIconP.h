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
   modulo XlIconP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIconP.h	5.1
*/
/*
 * IconP.h - definizioni private per l'oggetto Icon
 */ 
#ifndef _XlIconP_h
#define _XlIconP_h
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
#include "XlIcon.h"



/*
 Strutture relative alla nuova Classe
 */

typedef struct {
	BCK_OBJ *sfondo;     /*  sfondo dell'icona */
	int rotate;	     /* rotazione angolare dell'icona */
	int ass_rotate;      /* rotazione assiale dell'icona */
	Display *display;    /* display su cui e' visualizzata l'icona */
	int num_obj;
	char nome_icona[100];  /* nome dell'icona */
	int dim[4];      /* x min y min x max x max */
	int contatore;  /* per il momento non viene utilizzato */
	} XlIconSfondo;

typedef struct {
        int num_icone;
	XlIconSfondo *sfondi;
	} XlIconClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlIconClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlIconClassPart    xlicon_class;
	} XlIconClassRec;

extern XlIconClassRec xlIconClassRec;

/*
 Nuovi campi per il record del widget XlIcon
 */
typedef struct {
	/* risorse  */
	char * nome_file_icon; /* nome del file contenete il icon*/
	char * component;      /* nome del componente    */
	char * subsystem;       /* nome del sottosistema  */
	int primo_refresh;
	
	/*
		struttura per la gestione del cambio colore
	*/
	CAMBIO_COLORE cambio_colore[4];

        /*
          variabili di stato (privato)
        */
	Pixel OldPixel1;
	Pixel OldPixel2;
	Pixel OldPixel3;
	Pixel OldPixel4;
	Region region;      /* regione di ridisegno */
	BCK_OBJ *sfondo;
	} XlIconPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlIconRec {
	CorePart   core;
	XlCorePart xlcore;
	XlIconPart  icon;
	} XlIconRec;


#endif /* _XlIcon */
