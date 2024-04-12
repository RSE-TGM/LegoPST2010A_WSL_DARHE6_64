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
   modulo XlIconRegP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIconRegP.h	5.1
*/
/*
 * IconRegP.h - definizioni private per l'oggetto IconReg
 */ 
#ifndef _XlIconRegP_h
#define _XlIconRegP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
#include <Xl/XlCompositeP.h>
#include <Xl/XlUtilBkg.h>

/*
 Inclusione dell'header file pubblico
*/
#include "XlIconReg.h"

/*
        File di  include per la gestione delle form
*/
#include <Ol/OlForm.h>


/*
 Strutture relative alla nuova Classe
 */

typedef struct {
        BCK_OBJ *sfondo;     /*  sfondo dell'icona */
        int rotate;          /* rotazione angolare dell'icona */
        int ass_rotate;      /* rotazione assiale dell'icona */
	int top_border;       /* bordo libero in alto     */
	int bottom_border;    /* bordo libero in basso    */
	int left_border;      /* bordo libero a sinistra  */
	int right_border;     /* bordo libero a destra    */
        Display *display;    /* display su cui e' visualizzata l'icona */
        int num_obj;
        char nome_icona[100];  /* nome dell'icona */
        int dim[4];      /* x min y min x max x max */
        int contatore;  /* per il momento non viene utilizzato */
        } XlIconRegSfondo;

/*
        Struttura per la gestione, nella classe dell'oggetto
        dell'elenco delle form
*/
typedef struct {
       OlFormObject elencoForm;
       char nome_form[MAX_LUN_NOME_MODULO+1];
       } XlPortElencoForm;


typedef struct {
	int num_icone;
        XlIconRegSfondo *sfondi;
        int num_form;   /* numero delle form caricate nella classe */
        XlPortElencoForm *elencoForm; /* puntatore all'elenco delle form */
	XlCheckIconRegFunc checkIconReg;    /* metodo per il controllo
						della consistenza di una
					    icona diregolazione  */
	} XlIconRegClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlIconRegClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	 XlCompositeClassPart   xlcomposite_class;
	 XlIconRegClassPart   xliconReg_class;
	} XlIconRegClassRec;

extern XlIconRegClassRec xlIconRegClassRec;

/*
 Nuovi campi per il record del widget XlIconReg
 */
typedef struct {
        /* risorse  */
        char * nome_file_icon; /* nome del file contenete il icon*/
	char * nome_modulo;   /* nome del modulo di regolazione  
				e del file delle form*/
	char * nome_sigla;    /* nome dell'istanza */
	OlFormObject form;  /* puntatore all'oggetto form associato alla
                               all'icona di regolazione    */
	char *inputValue;   /* riga contenete i valori dei dati relativi alla
			       form             */
	char *descrizione;  /* descrizione dell'icona */
        int iconRegType;   /* normale, interfaccia input, interfaccia output */
	int top_border;       /* bordo libero in alto     */
	int bottom_border;    /* bordo libero in basso    */
	int left_border;      /* bordo libero a sinistra  */
	int right_border;     /* bordo libero a destra    */
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
	} XlIconRegPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlIconRegRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	XlCompositePart  xlcomposite;
	XlIconRegPart  iconReg;
	} XlIconRegRec;

#endif /* _XlIconRegP_h */
