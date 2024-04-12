/**********************************************************************
*
*       C Header:               XlManagerP.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Thu Nov 27 17:59:30 1997 %
*
**********************************************************************/
/*
   modulo XlManagerP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlManagerP.h	5.1
*/
/*
 * ManagerP.h - definizioni private per l'oggetto Manager
 */ 
#ifndef _XlManagerP_h
#define _XlManagerP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlManager.h>


#include <Ol/OlPertP.h>

#define XtInheritCompile  ((XlCompileFunc) _XtInherit)
#define XtInheritRead     ((XlReadFunc) _XtInherit)
#define XtInheritWrite    ((XlWriteFunc) _XtInherit)
#define XtInheritRefresh  ((XlRefreshFunc) _XtInherit)
#define XtInheritSelect   ((XlSelectProc) _XtInherit)
#define XtInheritClassInitialize  ((XtProc) _XtInherit)
#define XtInheritDrawBorderIfSelected  ((XlDrawBorderIfSelectedFunc) _XtInherit)
#define XtInheritPert    ((OlPertObject) _XtInherit)
#define XtInheritPrint    ((XlPrintFunc) _XtInherit)

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	OlPertObject   pert;      /* Oggetto per la gestione delle 
				     perturbazioni*/
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
	int ulevel;	/* user level, rende l'oggetto invisibile all'user > di questo */
	} XlManagerClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlManagerClassRec {
	 CoreClassPart     core_class;
	 CompositeClassPart  composite_class;
	 XlManagerClassPart   xlmanager_class;
	} XlManagerClassRec;

extern XlManagerClassRec xlManagerClassRec;

/*
 Nuovi campi per il record del widget XlManager
 */
typedef struct {
	/* risorse  */
        char *nome;  /* nome associato all'oggetto; viene utilizzato in fase
                        di configurazione lego-mmi */
        Boolean selected;  /* indica se l'oggetto e' selezionato */
        Boolean selectable; /* indica se l'oggetto selezionabile */
        Boolean config; /* e' true se il funzionamento e' per configurazione */
        Boolean in_edit; /* e' true se l'oggetto e' sottoposto a editing */
        Widget w_edit; /* indice di widget dell'editor che lavora sull'oggetto*/
        int fatt_zoom;  /* fattore di zoom moltiplicato 100: 
                           Es: 200 zoom del doppio */
        Boolean errore; /* e' true se si e'riscontrato un errore in compilaz.*/
	int inheritBackground; /* e' true se l'oggetto eredita il
                                        background del padre */
        Pixel selected_pixel; /* colore con cui evidenziare la selezione */
	Dimension width0;
        Dimension height0;
	Position x0;
        Position y0;
	int trasparent; /* abilita la trasparenza dell'oggetto */
        char *object_tag;  /* descrizione object TAG p.es. KKS */
        char *pagina_staz;  /* pagina di stazioni eventualmente collegata
                                all'oggetto  */
	char *compiled_str;
	int user_level;	/* user level associato all'istanza */
	/*
		risorse private
	*/
	Boolean compiled_allocated; /* indica se il campo compiled_str
                                       e' stato allocato internamente
                                       all'oggetto */
	GC sfondo_gc;               /* GC per disegno dello sfondo   */
	GC select_gc;               /* GC per disegno selezione      */
	Boolean hidden;		/* =True rende effettua Unmap oggetto */
	} XlManagerPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlManagerRec {
	CorePart   core;
	CompositePart  composite;
	XlManagerPart  xlmanager;
	} XlManagerRec;

#endif /* _XlManagerP_h */
