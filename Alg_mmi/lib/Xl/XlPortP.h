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
   modulo XlPortP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPortP.h	5.1
*/
/*
 * PortP.h - definizioni private per l'oggetto Port
 */ 
#ifndef _XlPortP_h
#define _XlPortP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlPort.h>
/*
 Strutture relative alla nuova Classe
 */

typedef Boolean (*XlSelectPortProc) (
#if NeedFunctionPrototypes
    Widget ,     /* widget prima porta*/
    Widget ,     /* widget seconda porta (se fine connessione) o NULL */
    int,         /* connessione attiva/non attiva */
    GC           /* GC per il disegno della connessione */
#endif
);


typedef struct {
	int stato_porte;
	Widget wport;
	XlSelectPortProc selectPort;
        XlCheckPortFunc checkPort;    /* metodo per il controllo
                                           della consistenza di una porta */
	} XlPortClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlPortClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlPortClassPart    xlport_class;
	} XlPortClassRec;

extern XlPortClassRec xlPortClassRec;

/*
 Nuovi campi per il record del widget XlPort
 */
typedef struct {
        /* risorse  */
        int tipo_port;   /* tipo di porta (input, output) */
        int interface_port;   /* porta di interfaccia o meno */
	int layout_port;   /* tipo di layout della porta, arrow/circle */
	char *nome_port;  /* nome della porta              */
	char *nome_port_connect;  /* nome della porta connessa  */
	char *nome_page_connect;  /* nome della porta connessa  */
	Pixel color_digital_port;
	Pixel color_analog_port;
	Pixel color_port_start_connection;
	Pixel color_port_connected;
	Pixel color_foreground_label;
	Pixel color_background_label;
	Widget wLabel;
	char * normalfont;  /* nome del font utilizzato per le scritte */
	int connectMode;
	int visibleMode;    /* modalita' di visualizzazione delle porte */
	int position_tag;    /* posizione della tag; bottom, center, top */
        /*
          variabili di stato (privato)
        */
        GC digital_gc;           /* GC della porta digitale  */
        GC analog_gc;            /* GC della porta analogica  */
        GC start_connection_gc;  /* GC della porta di inizio connessione */
        GC connected_gc;         /* GC della porta connessa */
	XFontStruct *font_info;
        XmFontList font_list;
	} XlPortPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlPortRec {
	CorePart   core;
	XlCorePart xlcore;
	XlPortPart  port;
	} XlPortRec;

#endif /* _XlPortP_h */
