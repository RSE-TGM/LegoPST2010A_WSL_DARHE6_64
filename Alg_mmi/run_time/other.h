/**********************************************************************
*
*       C Header:               other.h
*       Subsystem:              3
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Jul 29 16:08:32 1998 %
*
**********************************************************************/
/*
   modulo other.h
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)other.h	5.2
*/
#ifndef _OTHER_INCLUDED
#define _OTHER_INCLUDED

#include <Xl/XlUtilBkg.h>

#include <Rt/RtMemory.h>

#include "libutilx.h"


/*
	definizioni per i parametri sulla linea di comando
*/
#define ARGV_CONTEXT "-Context"
#define ARGV_TOPOLOGIA "-Topologia"
#define ARGV_DEMONE_PORT "-DemonePort"
#define ARGV_PAG "-pag"
#define ARGV_BACKGROUND "-pagback"
#define ARGV_NOCLOSE    "-noclose"
#define ARGV_ALLDISP    "-alldisp"

#define MAX_STARTUP_PAGES	10
#define MAX_BACKGROUND_PAGES	10
#define MAX_NOCLOSE_PAGES	10

/* dichiarazione del nome della srawing area della pagina
   tipo Stazioni,sinottico,aing,teleperm
*/
#define DRAWING_STAZ "drawingAreaStaz"
#define DRAWING_SIN  "drawingSinottico"
#define DRAWING_AING "drawingAing"
#define DRAWING_TELE "drawingArea"
#define DRAWING_OW "drawingAreaOW"
#define DRAWING_PLOT "drawingPlot"
#define DRAWING_AING "drawingAing"

/*
	definizione della password
*/
#define PASSWORD "SysOk"

/*
	definizioni per la finestra Aing
        spostate in aing_def.h
*/

/***
typedef struct menu_aing_st {
			char *descrizione;
			Boolean _campo_1;
		        char *descr_1;
			Boolean _campo_2;
		        char *descr_2;
			Boolean _campo_3;
		        char *descr_3;
			Boolean _campo_4;
		        char *descr_4;
			Boolean _campo_5;
		        char *descr_5;
			Boolean _campo_6;
		        char *descr_6;
			Boolean _campo_7;
		        char *descr_7;
			Boolean _Start;
			Boolean _Stop;
                        } S_MENU_AING;

static S_MENU_AING menu_aing[]={
{"Not: ",False,"",False,"",False,"",False,"",False,"",False,"",
	False,"",True,False},
{"Step: ",True,"Target: ",False,"",False,"",False,"",False,"",False,"",
	False,"",True,False},
{"Pulse: ",True,"Target: ",True,"Wide: ",False,"",False,"",
	False,"",False,"",False,"",True,True},
{"Ramp/Grad: ",True,"Target: ",True,"Grad.: ",False,"",False,"",
		False,"",False,"",False,"",True,True},
{"Ramp/Delta: ",True,"Target: ",True,"Delta: ",False,"",False,"",
	False,"",False,"",False,"",True,True},
{"Ramp/At: ",True,"Target: ",True,"At: ",False,"",False,"",False,"",False,"",
	False,"",True,True},
{"Sinusoidal: ",True,"Period: ",True,"Mean Value: ",True,"Wide: ",
	True,"Phase: ",False,"",False,"",False,"",True,True},
{"Periodic: ",True,"Period: ",True,"Mean Value: ",True,"Wide: ",True,"Phase: ",
	True,"T1: ",True,"T2: ",True,"T3: ",True,True},
{"White Noise: ",True,"Variance : ",True,"Mean Value: ",False,"",False,"",
	False,"",False,"",False,"",True,True},
{"Malfunction: ",True,"Target : ",True,"Type: ",False,"",False,"",
	False,"",False,"",False,"",True,True}
		};

#define NUM_MENU_AING 	10
***/

/*
	definizione di strutture
*/
#define MODO_ELENCO_ALL  0
#define MODO_ELENCO_SINOTTICI 1
#define MODO_ELENCO_STAZIONI    2  
#define L_NOME_PAGINE    200
#define L_DESCR_PAGINE   200
#define L_DESCR_TIPO     200
#define LUN_PATH	400
#define LUN_GERAR	50


typedef struct an_pag{
                char nome[L_NOME_PAGINE];
                char descrizione[L_DESCR_PAGINE];
  		char tipo[L_DESCR_TIPO];
		int t_refresh;
                char gerarchia[LUN_GERAR];
  		BCK_OBJ *sfondo;
    } AN_PAG;


/* definizione dello screen */
typedef struct an_screen {
                char nome[100];
                Widget topLevel;      /* widget topLevel parent del teleperm */
                Widget wteleperm;     /* widget topLevel tipo teleperm */
   } AN_SCREEN;

/* la struttura AN_DISPLAY permette nel caso teleperm
di gestire attualmente due screen
*/

typedef struct an_display {
                char nome[100];
  		Widget topLevel;  
  		Widget wb;
                int num_screens;      /* gestione di piu' screen */
#ifndef DESIGN_TIME
                AN_SCREEN *scr;  /* punta altri screen */
#else
                int *scr;    
#endif
    } AN_DISPLAY;


typedef struct pagine_aperte_st{
                char nome[100];
  		Widget w; /*drawing Area */ 
    } PAGINE_APERTE;


/*
	font utilizzati
*/
#define FONT_TASTI "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define FONT_LISTA "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define FONT_LABEL "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define OPERAZIONE_NOP			0
#define OPERAZIONE_XAING		1
#define OPERAZIONE_XPLOT		2
#define OPERAZIONE_XSTAZ		3
#define OPERAZIONE_INFO			4
#define OPERAZIONE_REG			5

#define REFRESH_AING			1000
#define REFRESH_PLOT			1000
#define DELTA_PLOT			120
#define COLOR_PLOT			"yellow"

/*
	numero massimo di pagine visualizzabili
*/
#if defined SCADA_MMI
#define MAX_PAGE		9
#else
#define MAX_PAGE		100
#endif


#define XtNtop_x "top_x"
#define XtCTop_x "Top_x"
#define XtNtop_y "top_y"
#define XtCTop_y "Top_y"
#define XtNtop_width "top_width"
#define XtCTop_width "Top_width"
#define XtNtop_height "top_height"
#define XtCTop_height "Top_height"
#define XtNtop_tipo "top_tipo"
#define XtCTop_tipo "Top_tipo"
#define XtNtop_descrizione "top_descrizione"
#define XtCTop_descrizione "Top_descrizione"
#define XtNdrawing_width "drawing_width"
#define XtCDrawing_width "Drawing_width"
#define XtNdrawing_height "drawing_height"
#define XtCDrawing_height "Drawing_height"
#define XtNdrawing_background "drawing_background"
#define XtCDrawing_background "Drawing_background"

#define PAGINA_SINOTTICO	1
#define PAGINA_STAZIONI		2

/**************Fabio 29/4/97*******************/
/*****         Costanti per movimento su pag teleperm *****/
#define LEFT      1
#define RIGTH     2 
#define UP        3
#define PREVIOUS  4
#define PLANT_OVW 5
#define GOTOPAG      6


/************* Carlo 14-11-96

Boolean EsistePagina(char*);
   int NumeroPagina(char*);
   Boolean CreaPagina(Widget, WidgetList *, int *);
   Boolean DistruggiPagina(WidgetList , int );
   XrmDatabase CaricaDB(Display *,char*);
   Boolean GetResTopLevel(Widget ,int *, int *, int *, int *, int*, char **, char **);
   Boolean GetResDrawing(Widget, int *,int *, Pixel *);
Boolean GetDescrPag(Widget, char* , char **, char **);
    Boolean LoadBitmap(Widget, Pixmap * ,char *, int, int);
    int InsElencoPagine(char *, WidgetList , int, int);
    Boolean DelElencoPagine(int,Widget);
    Boolean PreparaTestoInfo(Widget, char *);
Boolean ScriviTestoInfo(Widget,FILE  *);
   Boolean LoadFont(char *, XmFontList *, Display *);
   Boolean FreeFont(XmFontList, Display *);
   Boolean SettaSelect();
   Boolean PrintScreen(Widget, char *, char*, Boolean, BCK_OBJ *);
   Widget PrintSetup(Widget);
void show_warning(char*);
   void SalvaContextBin();
   Boolean CaricaContextBin();
   void AllocaColoriSfondo(Widget ,BCK_OBJ *);
Boolean ActivatePlot(Widget,Widget , char *,Widget *);
   Boolean ActivateAing(Widget ,Widget , char *,Widget *);
   Boolean ActivateChangeVar(Widget ,Widget ,Widget *);
void ActivateVarAing(Widget *);
void ActivateVarPlot(Widget *);
int SettaIndicAing(Widget, char*,float,float);
   void StopAing();
Boolean PosMouse(Widget , int *, int *);
   Boolean CloseAllPages(AN_DISPLAY *, int);
Boolean PaginaAperta(Widget , char* );
int NumPagineAperte();
   Boolean CanOpenPage();
void CheckMmiStatus();
void ripulisci_files();
Boolean AcceptAing(Widget );
   Boolean AcceptPlot(Widget );
int SettaGrafPlot(Widget, char*,float,float);
void WriteDbPlot();
void WriteDbAing();
Widget ToTopLevel(Widget);
   Boolean RaisePlotAing();
   Boolean CanClosePage(char *);

**********************/


Boolean ActivateChangeVar(Widget ,Widget ,Widget *);
Widget popup_errorDialog(char *, Widget );
Widget	popup_formInfo();
Boolean AcceptAing(Widget w);
Boolean ActivateAing(Widget ,Widget , char *,Widget *);
Boolean AcceptPlot(Widget );
Boolean ActivatePlot(Widget  ,Widget ,char *, Widget *);
Boolean PaginaAperta(Widget ,char* );
Boolean CanOpenPage();
Widget	popup_Attesa( Widget );
void SettaAttesa(Widget ,int );
void show_warning(char*);
int XlRefreshWidget(WidgetList ,Cardinal );
XrmDatabase CaricaDB(Display *,char*);
Boolean DistruggiPagina(WidgetList , int );
Boolean CreaPagina(Widget, WidgetList *, int *);
int NumeroPagina(char*);
Boolean DelElencoPagine(int,Widget);
void ClosePageSin(Widget );
Boolean CanClosePage(char *);
Widget	popup_CloseQuestion();
Boolean PrintScreen(Widget, char *, char*, Boolean, BCK_OBJ *);
Widget PrintSetup(Widget);
Boolean GetResTopLevel(Widget ,int *, int *, int *, int *, int*, char **, char **);
//Boolean GetResDrawing(Widget, int *,int *, Pixel *);
Boolean GetResDrawing(Widget , int *, int *, Pixel *,Pixmap *);
void AllocaColoriSfondo(Widget ,BCK_OBJ *);
Boolean LoadFont(char *, XmFontList *, Display *);
int InsElencoPagine(char *, WidgetList , int, int);
Boolean RaisePlotAing();
Boolean PreparaTestoInfo(Widget, char *);
Boolean FreeFont(XmFontList, Display *);
Boolean XlIsXlCore(Widget );
Boolean XlIsXlComposite(Widget );
void CursorErrFree(Widget ,Cursor );
void XlUnsetCursor(Widget );
Boolean XlFreeCursor(Widget , Cursor );
Boolean PutPagBackground();

extern  void *		UxNewContext();
void StopAing();
Widget ToTopLevel(Widget );
Cursor XlCreateErrCursor(Widget wid);
void XlSetCursor(Widget , Cursor );
int creaOlDbPunti(char *,Widget);
Widget popup_Warning_sim(char *, Widget );
Boolean CloseAllPages(AN_DISPLAY *, int);

Boolean OlDestroyPert( );
int OlDatabasePuntiType( );
OlPertObject OlCreatePert( );

Boolean CaricaContextBin();
void SalvaContextBin();
Boolean SettaSelect();
Boolean Build_OlTree( );
Widget	create_topLevelShell1();
void ClosePageStaz(Widget );

int pert_malfunction_stop(int ,int ,float );
void WriteDbPlot();
int SettaGrafPlot(Widget , char *,float , float );
Boolean LoadBitmap(Widget, Pixmap * ,char *, int, int);






#endif
