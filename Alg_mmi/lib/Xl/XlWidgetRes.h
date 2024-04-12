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
   modulo XlWidgetRes.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlWidgetRes.h	5.1
*/
/*
 XlWidgetRes.h
*/
#ifndef _XlWidgetRes_h
#define _XlWidgetRes_h

#define XLWIDGETRES_NAME	80
#define XLWIDGETRES_CLASSE	20
#define XLWIDGETRES_VALORE	80
#define XLWIDGETRES_WID		20

typedef struct _XlWidgetRes {
	char   name[XLWIDGETRES_NAME];         
			     /* descrizione per esteso della risorsa */
	char   valore[XLWIDGETRES_VALORE];       
			     /* valore per esteso della risorsa */
	char nome_wid[XLWIDGETRES_WID];
	char nome_classe[XLWIDGETRES_CLASSE];
	char nome_wid_padre[XLWIDGETRES_WID];
	int    type;         /* tipo usato nella rappresentazione da
			        parte del configuratore delle risorse */
	int    db_type;      /* indica il tipo di risorsa XlTipoVarXX
			        dal punto di vista del database dei punti:
			        ex: XlRVarDO, ecc...			*/
	int    group;        /* tipo di gruppo cui la risorsa appartiene
                                viene utilizzato per la visualizzazione
                                nel configuratore delle risorse attuata
                                per gruppi separati */
	} XlWidgetRes, *XlWidgetResList; 

Boolean XlGetResWidget(Widget, XlWidgetResList *, int *);
Boolean XlPrintResWidget(XlWidgetResList , int ,char *);

#endif 
