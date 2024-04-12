/**********************************************************************
*
*       C Header:               XlCoreP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Thu Nov 27 16:55:35 1997 %
*
**********************************************************************/
/*
   modulo XlCoreP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlCoreP.h	5.1
*/
/*
 * XlCoreP.h - definizioni private per l'oggetto XlCore
 */ 
#ifndef _XlCoreP_h
#define _XlCoreP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlDrawingUtil.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlCore.h>
/*
 Inclusione dell'header file privato dell'oggetto compilatore e pert
*/ 
#include <Ol/OlCompilerP.h>
#include <Ol/OlDatabaseTopologiaP.h>
#include <Ol/OlDatabasePuntiP.h>
#include <Ol/OlPertP.h>

#define XtInheritCompile  ((XlCompileFunc) _XtInherit)
#define XtInheritRead     ((XlReadFunc) _XtInherit)
#define XtInheritWrite    ((XlWriteFunc) _XtInherit)
#define XtInheritRefresh  ((XlRefreshFunc) _XtInherit)
#define XtInheritClassInitialize  ((XtProc) _XtInherit)
#define XtInheritDrawBorderIfSelected  ((XlDrawBorderIfSelectedFunc) _XtInherit)
#define XtInheritSelect    ((XlSelectProc) _XtInherit)
#define XtInheritPrint    ((XlPrintFunc) _XtInherit)
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	OlPertObject   pert;      /* oggetto per l'invio delle perturbazioni */
	OlDatabasePuntiObject database;  /* database dei punti   */
	OlDatabaseTopologiaObject database_topologia;  /* database della
				     topologia   */
	OlCompilerObject   compilatore;  /* compilatore delle risorse */
	XlConfInfoList confinfo;  /* record delle risorse settabili
                                        dall'utente tramite il configuratore
                                        delle risorse e informazioni per la
					compilazione */
	Cardinal num_confinfo;    /* numero delle confinfo */
	XlRefreshFunc refresh;     /* metodo richiamato per il refresh della
					pagina grafica */
	XlCompileFunc compile;    /* metodo per la compilazione */
	XlReadFunc    read;       /* metodo per la lettura file non ascii */
	XlWriteFunc   write;      /* metodo per la scrittura file non ascii */
	XlSelectProc select;      /* metodo di selezione */
	XlDrawBorderIfSelectedFunc drawBorderIfSelected;    
	XlSelectRunTimeProc selectRunTime;
#if defined XPRINTER_USED
	XlPrintFunc   print;      /* metodo per la stampa con xprinter */
#endif
        int ulevel; /* user level,rende l'oggetto visibile all'user > di questo */
	} XlCoreClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlCoreClassRec {
	 CoreClassPart      core_class;
	 XlCoreClassPart    xlcore_class;
	} XlCoreClassRec;

extern XlCoreClassRec xlCoreClassRec;

/*
 Nuovi campi per il record del widget XlCore
 */
typedef struct {
	/* risorse  */
	char *nome;  /* nome associato all'oggetto; viene utilizzato in fase
                        di configurazione lego-mmi */
	Boolean selected;  /* indica se l'oggetto e' selezionato */
	Boolean selectable; /* indica se l'oggetto selezionabile */
	Boolean config; /* e' true se il funzionamento e' per configurazione */
	Boolean in_edit; /* e' true se l'oggetto e' sottoposto a editing */
	Widget w_edit;   /* indice di widget dell'editor che 
				lavora sull'oggetto */
	int fatt_zoom; /* fattore moltiplicativo di zoom
				in % cioe': 100 = scala normale
					    200 = zoom di due volte */
	Boolean errore; /* e' true se si e' riscontrato un errore 
				in compilaz. */
	int inheritBackground; /* e' true se l'oggetto eredita il 
					background del padre */
	Pixel selected_pixel; /* colore con cui evidenziare la selezione */
	Dimension width0;
	Dimension height0;
	Position x0;
	Position y0;
	int rotate;	/* rotazione in senso orario di 90 gradi, 0,1,2,3  */
	int ass_rotate; /* rotazione rispetto all'asse delle Y posizionato
			   a width/2                                       */
	int pub_rotate;
	int pub_ass_rotate;
	int trasparent; /* abilita la trasparenza dell'oggetto */
	char *pagina_staz;  /* pagina di stazioni eventualmente collegata
				all'oggetto  */
        char *compiled_str;
        char *object_tag;    /* tag dell'oggetto p.es. KKS */
        int user_level;   /* user level associato all'istanza */

	/* privato */
	Boolean compiled_allocated; /* indica se il campo compiled_str
                                       e' stato allocato internamente 
                                       all'oggetto */
	GC select_gc;            /* GC per disegno selezione      */
        Boolean hidden;   /* =True rende l'oggetto invisibile */
	} XlCorePart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlCoreRec {
	CorePart core;
	XlCorePart xlcore;
	} XlCoreRec;

#endif /* _XlCoreP_h */
