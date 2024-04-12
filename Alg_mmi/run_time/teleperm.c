
/*******************************************************************************
       teleperm.c
       (Generated from interface file teleperm.i)
       Associated Resource file: teleperm.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/param.h>
#include <Xm/MwmUtil.h>
#include <X11/Xlib.h>
#include <time.h>
#include <Ol/OlTree.h>	         /* per gestione OlTree teleperm */
#include <Ol/OlDatabasePunti.h>  /* per gestione DatabasePunti */
#include <Xl/XlChangePage.h>     /* per gestione oggetto XlChangePage */
#include <Xl/XlPictograph.h>    
#include "other.h"
#include <Xl/XlCai.h>
#include <Xl/XlCaiAll.h>
#ifndef DESIGN_TIME
#include <Xl/Xl.h>
#endif
#include <other.h>
#include <Cs/Cs.h>	/* per comunocazioni per AlarmPage */

extern XrmDatabase ApplDb;    /* db delle risorse della applicazione */

extern OlTreeObject root_oltree;  /* OlTree root */

extern AN_PAG *pagine;     /* lista delle pagine */
extern int totale_pagine;
extern OlDatabasePuntiObject database_simulatore;
extern int database_type;
extern Boolean allPageFlag;
extern Boolean scada_on;
extern Boolean topologia_on;
extern PAGINE_APERTE *el_pagine;
extern int num_el_pagine;

/* dichiaro la routine di refresh  definita nella aux function
*/
static void teleperm_refreshPag();
static void conver_time(float tempoSim,char *ora);

extern swidget create_topLevelShell1();
extern swidget popup_topLevelShellStaz();
extern Boolean PrintAllarmi();
extern ClosePageStaz();

extern ScriviTestoInfo();
 
extern Boolean EsistePagina();

int  getSubLevel();
void set_titleLabel();

static void teleperm_refreshTime();
static void teleperm_refreshCai();
/*
static void build_cai();
*/
extern AN_DISPLAY *elenco_display;

/***************
definizioni
***************/
#define TIPOSTAZIONE   1
#define TIPOOW		2

#define ROOT_LEVEL 100
#define VERTMENUON 1
#define ORIZMENUON 2
#define PLANTMENUON 3

/* definizioni nomi bitmap utilizzati per i bottoni del footer
*/
#define previousBMP "previous.bmp"
#define swscreenBMP "cscreen.bmp"
#define leftBMP "left.bmp"
#define upBMP "up.bmp"
#define rightBMP "right.bmp"
#define swscreenBMP "cscreen.bmp"
#define ackaudBMP "ackaud.bmp"
#define ackalBMP "ackal.bmp"
#define hardcopyBMP "hardcopy.bmp"
#define helpBMP "help.bmp"
#define precessDisplayBMP "overview.bmp"
#define logoffBMP "logon.bmp"
#define plantOverviewBMP "overview.bmp"





/*
Defaults per Info plot e aing
*/
#define TMPINFOFILE	"/WidResources_"
#define DEFEDITOR       "vi"
#define DEFTMPDIR       "/tmp"
#define SISTEMLABEL     "Sist."

#define ALLMAXLUNNOMEWID 256
#define NUMMAXZONE	32
#define MAXNUMALLVIS	16
#define SEPARATORALARM  "|"
#define KKSTAGLEN	4
#define MAXLUNTOKEN	150
#define NUMTOKEN	4
#define MODO_ALLARMI	0
#define MODO_ARCHIVIO	1


#define HEIGHTSMALLFORMHEADER 55
#define HEADERTRERIGHE 19
#define HEADERQUATTRORIGHE 25
#define HEADERCINQUERIGHE 31
#define INDALLPAG	-15
#define INDALLPAGFROMPLANT -30
#define SINCROCLOSEALLPAG	-10
#define TOLERANCE_N_TIME        180     /* sec per time-out pag all tasto [n] */
#define DEF_TIME_OUT_N		50000   /* sec per usleep tasto [n]   */
/* 
Dichiarazione di variabili per pagina allarmi che devono essere globali perche'
e' possibile avere una sola pagina allarmi attiva per volta.
In particolore  la situazione zone deve essere unica (anche per miniASD)
*/
/* 
Variabili per pagina allarmi
*/
int last_indice_fa=0;
int num_zone;

int last_zone_pressed;   /* ultima zona selezionata (per 2 utenti allPage o  dati all non validi */
int zone_ko;
int allPageOnScreen=-1;
int zone_status[NUMMAXZONE];   /* tipo int per compatibilita' con msg per client_scada */
int zone_status_old[NUMMAXZONE];/*vecchia situazione impostazione zone */
int selectable_zone[NUMMAXZONE];  /* tabella fa attive */
Boolean prima_apertura_all=True; /* tiene conto se non ho ancora richiesto gli allarmi */
Boolean prima_apertura_teleperm=True;
XtIntervalId  timer_timerefreshAll; /* per Refresh Pagina Allarmi */


static	int _UxIfClassId;
int	Uxteleperm_orizHier_Id = -1;
char*	Uxteleperm_orizHier_Name = "orizHier";
int	Uxteleperm_drawPush_Id = -1;
char*	Uxteleperm_drawPush_Name = "drawPush";
int	Uxteleperm_openStaz_Id = -1;
char*	Uxteleperm_openStaz_Name = "openStaz";
int	Uxteleperm_aggHeaderArea_Id = -1;
char*	Uxteleperm_aggHeaderArea_Name = "aggHeaderArea";
int	Uxteleperm_switchScreen_Id = -1;
char*	Uxteleperm_switchScreen_Name = "switchScreen";
int	Uxteleperm_moveleft_Id = -1;
char*	Uxteleperm_moveleft_Name = "moveleft";
int	Uxteleperm_moveup_Id = -1;
char*	Uxteleperm_moveup_Name = "moveup";
int	Uxteleperm_openTopProcDisplay_Id = -1;
char*	Uxteleperm_openTopProcDisplay_Name = "openTopProcDisplay";
int	Uxteleperm_navigation_Id = -1;
char*	Uxteleperm_navigation_Name = "navigation";
int	Uxteleperm_decorationToggle_Id = -1;
char*	Uxteleperm_decorationToggle_Name = "decorationToggle";
int	Uxteleperm_createCaiHeader_Id = -1;
char*	Uxteleperm_createCaiHeader_Name = "createCaiHeader";
int	Uxteleperm_createButtonPixmap_Id = -1;
char*	Uxteleperm_createButtonPixmap_Name = "createButtonPixmap";
int	Uxteleperm_moveroot_Id = -1;
char*	Uxteleperm_moveroot_Name = "moveroot";
int	Uxteleperm_closeOW_Id = -1;
char*	Uxteleperm_closeOW_Name = "closeOW";
int	Uxteleperm_close_allPage_Id = -1;
char*	Uxteleperm_close_allPage_Name = "close_allPage";
int	Uxteleperm_xaing_Id = -1;
char*	Uxteleperm_xaing_Name = "xaing";
int	Uxteleperm_refreshAllPageWidgets_Id = -1;
char*	Uxteleperm_refreshAllPageWidgets_Name = "refreshAllPageWidgets";
int	Uxteleperm_popupPage_Id = -1;
char*	Uxteleperm_popupPage_Name = "popupPage";
int	Uxteleperm_ridisegna_Id = -1;
char*	Uxteleperm_ridisegna_Name = "ridisegna";
int	Uxteleperm_gotopag_Id = -1;
char*	Uxteleperm_gotopag_Name = "gotopag";
int	Uxteleperm_xplot_Id = -1;
char*	Uxteleperm_xplot_Name = "xplot";
int	Uxteleperm_application_Id = -1;
char*	Uxteleperm_application_Name = "application";
int	Uxteleperm_previousPag_Id = -1;
char*	Uxteleperm_previousPag_Name = "previousPag";
int	Uxteleperm_isOldAlarmPage_Id = -1;
char*	Uxteleperm_isOldAlarmPage_Name = "isOldAlarmPage";
int	Uxteleperm_moveright_Id = -1;
char*	Uxteleperm_moveright_Name = "moveright";
int	Uxteleperm_chPage_Id = -1;
char*	Uxteleperm_chPage_Name = "chPage";
int	Uxteleperm_aggTitleArea_Id = -1;
char*	Uxteleperm_aggTitleArea_Name = "aggTitleArea";
int	Uxteleperm_aggListChild_Id = -1;
char*	Uxteleperm_aggListChild_Name = "aggListChild";
int	Uxteleperm_dispData_Id = -1;
char*	Uxteleperm_dispData_Name = "dispData";
int	Uxteleperm_closePag_Id = -1;
char*	Uxteleperm_closePag_Name = "closePag";
int	Uxteleperm_create_allPage_Id = -1;
char*	Uxteleperm_create_allPage_Name = "create_allPage";
int	Uxteleperm_WidgetSelect_Id = -1;
char*	Uxteleperm_WidgetSelect_Name = "WidgetSelect";
int	Uxteleperm_info_Id = -1;
char*	Uxteleperm_info_Name = "info";
int	Uxteleperm_dispTime_Id = -1;
char*	Uxteleperm_dispTime_Name = "dispTime";
int	Uxteleperm_vertHier_Id = -1;
char*	Uxteleperm_vertHier_Name = "vertHier";

#ifndef teleperm_orizHier
#define teleperm_orizHier( UxThis, pEnv, lista_ind, npag ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_orizHier_Id,\
			Uxteleperm_orizHier_Name)) \
		( UxThis, pEnv, lista_ind, npag )
#endif

#ifndef teleperm_drawPush
#define teleperm_drawPush( UxThis, pEnv, w, bmpName ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_drawPush_Id,\
			Uxteleperm_drawPush_Name)) \
		( UxThis, pEnv, w, bmpName )
#endif

#ifndef teleperm_openStaz
#define teleperm_openStaz( UxThis, pEnv, pagina, Padre, nome_disp, sfondo_staz ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_openStaz_Id,\
			Uxteleperm_openStaz_Name)) \
		( UxThis, pEnv, pagina, Padre, nome_disp, sfondo_staz )
#endif

#ifndef teleperm_aggHeaderArea
#define teleperm_aggHeaderArea( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_aggHeaderArea_Id,\
			Uxteleperm_aggHeaderArea_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_switchScreen
#define teleperm_switchScreen( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_switchScreen_Id,\
			Uxteleperm_switchScreen_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_moveleft
#define teleperm_moveleft( UxThis, pEnv, pcurr, pnew ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_moveleft_Id,\
			Uxteleperm_moveleft_Name)) \
		( UxThis, pEnv, pcurr, pnew )
#endif

#ifndef teleperm_moveup
#define teleperm_moveup( UxThis, pEnv, pcurr, pnew ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_moveup_Id,\
			Uxteleperm_moveup_Name)) \
		( UxThis, pEnv, pcurr, pnew )
#endif

#ifndef teleperm_openTopProcDisplay
#define teleperm_openTopProcDisplay( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_openTopProcDisplay_Id,\
			Uxteleperm_openTopProcDisplay_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_navigation
#define teleperm_navigation( UxThis, pEnv, direction, pag_ind, screen_selected, calling ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_navigation_Id,\
			Uxteleperm_navigation_Name)) \
		( UxThis, pEnv, direction, pag_ind, screen_selected, calling )
#endif

#ifndef teleperm_decorationToggle
#define teleperm_decorationToggle( UxThis, pEnv ) \
	((void(*)())UxMethodLookup(UxThis, Uxteleperm_decorationToggle_Id,\
			Uxteleperm_decorationToggle_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_createCaiHeader
#define teleperm_createCaiHeader( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_createCaiHeader_Id,\
			Uxteleperm_createCaiHeader_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_createButtonPixmap
#define teleperm_createButtonPixmap( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_createButtonPixmap_Id,\
			Uxteleperm_createButtonPixmap_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_moveroot
#define teleperm_moveroot( UxThis, pEnv, pcurr, pnew ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_moveroot_Id,\
			Uxteleperm_moveroot_Name)) \
		( UxThis, pEnv, pcurr, pnew )
#endif

#ifndef teleperm_closeOW
#define teleperm_closeOW( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_closeOW_Id,\
			Uxteleperm_closeOW_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_close_allPage
#define teleperm_close_allPage( UxThis, pEnv ) \
	((Boolean(*)())UxMethodLookup(UxThis, Uxteleperm_close_allPage_Id,\
			Uxteleperm_close_allPage_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_xaing
#define teleperm_xaing( UxThis, pEnv, w ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_xaing_Id,\
			Uxteleperm_xaing_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_refreshAllPageWidgets
#define teleperm_refreshAllPageWidgets( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_refreshAllPageWidgets_Id,\
			Uxteleperm_refreshAllPageWidgets_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_popupPage
#define teleperm_popupPage( UxThis, pEnv, nomePag, tipo ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_popupPage_Id,\
			Uxteleperm_popupPage_Name)) \
		( UxThis, pEnv, nomePag, tipo )
#endif

#ifndef teleperm_ridisegna
#define teleperm_ridisegna( UxThis, pEnv, ind_pag ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_ridisegna_Id,\
			Uxteleperm_ridisegna_Name)) \
		( UxThis, pEnv, ind_pag )
#endif

#ifndef teleperm_gotopag
#define teleperm_gotopag( UxThis, pEnv, pcur, pnew, indice ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_gotopag_Id,\
			Uxteleperm_gotopag_Name)) \
		( UxThis, pEnv, pcur, pnew, indice )
#endif

#ifndef teleperm_xplot
#define teleperm_xplot( UxThis, pEnv, w ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_xplot_Id,\
			Uxteleperm_xplot_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_application
#define teleperm_application( UxThis, pEnv, w ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_application_Id,\
			Uxteleperm_application_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_previousPag
#define teleperm_previousPag( UxThis, pEnv, pcur, pnew ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_previousPag_Id,\
			Uxteleperm_previousPag_Name)) \
		( UxThis, pEnv, pcur, pnew )
#endif

#ifndef teleperm_isOldAlarmPage
#define teleperm_isOldAlarmPage( UxThis, pEnv, pag_candidata ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_isOldAlarmPage_Id,\
			Uxteleperm_isOldAlarmPage_Name)) \
		( UxThis, pEnv, pag_candidata )
#endif

#ifndef teleperm_moveright
#define teleperm_moveright( UxThis, pEnv, pcurr, pnew ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_moveright_Id,\
			Uxteleperm_moveright_Name)) \
		( UxThis, pEnv, pcurr, pnew )
#endif

#ifndef teleperm_chPage
#define teleperm_chPage( UxThis, pEnv, w, nomePg, tipoApertura ) \
	((void(*)())UxMethodLookup(UxThis, Uxteleperm_chPage_Id,\
			Uxteleperm_chPage_Name)) \
		( UxThis, pEnv, w, nomePg, tipoApertura )
#endif

#ifndef teleperm_aggTitleArea
#define teleperm_aggTitleArea( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_aggTitleArea_Id,\
			Uxteleperm_aggTitleArea_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_aggListChild
#define teleperm_aggListChild( UxThis, pEnv, childW ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_aggListChild_Id,\
			Uxteleperm_aggListChild_Name)) \
		( UxThis, pEnv, childW )
#endif

#ifndef teleperm_dispData
#define teleperm_dispData( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_dispData_Id,\
			Uxteleperm_dispData_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_closePag
#define teleperm_closePag( UxThis, pEnv, w ) \
	((void(*)())UxMethodLookup(UxThis, Uxteleperm_closePag_Id,\
			Uxteleperm_closePag_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_create_allPage
#define teleperm_create_allPage( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_create_allPage_Id,\
			Uxteleperm_create_allPage_Name)) \
		( UxThis, pEnv )
#endif

#ifndef teleperm_WidgetSelect
#define teleperm_WidgetSelect( UxThis, pEnv, w ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_WidgetSelect_Id,\
			Uxteleperm_WidgetSelect_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_info
#define teleperm_info( UxThis, pEnv, w ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_info_Id,\
			Uxteleperm_info_Name)) \
		( UxThis, pEnv, w )
#endif

#ifndef teleperm_dispTime
#define teleperm_dispTime( UxThis, pEnv, tempoSim ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_dispTime_Id,\
			Uxteleperm_dispTime_Name)) \
		( UxThis, pEnv, tempoSim )
#endif

#ifndef teleperm_vertHier
#define teleperm_vertHier( UxThis, pEnv, lista_ind, npag ) \
	((int(*)())UxMethodLookup(UxThis, Uxteleperm_vertHier_Id,\
			Uxteleperm_vertHier_Name)) \
		( UxThis, pEnv, lista_ind, npag )
#endif


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	Uxteleperm;
	Widget	UxformTop;
	Widget	UxscreenFooterForm;
	Widget	UxrcFooter;
	Widget	Uxprevious;
	Widget	Uxleft;
	Widget	Uxup;
	Widget	Uxright;
	Widget	Uxswscreen;
	Widget	Uxackaud;
	Widget	Uxackal;
	Widget	Uxhardcopy;
	Widget	Uxhelp;
	Widget	UxscreenHeaderForm;
	Widget	UxrcProcess;
	Widget	Uxproceso;
	Widget	UxprocessDisplay;
	Widget	UxformSystem;
	Widget	UxmenuSystem;
	Widget	UxmenuSystem_rc1;
	Widget	UxmenuSystem_rc1_b7;
	Widget	Uxlogoff;
	Widget	UxmenuSystem_rc1_b8;
	Widget	UxcommonAck;
	Widget	UxmenuSystem_rc1_b9;
	Widget	UxlogSelection;
	Widget	UxmenuSystem_rc1_b10;
	Widget	UxIncidentRew;
	Widget	UxmenuSystem_rc1_b11;
	Widget	UxlongTermArc;
	Widget	UxmenuSystem_rc1_b12;
	Widget	Uxaing;
	Widget	UxmenuSystem_rc1_b13;
	Widget	Uxplot;
	Widget	UxmenuSystem_csbutt;
	Widget	UxrcData;
	Widget	UxData;
	Widget	UxOra;
	Widget	UxformCaiPlant;
	Widget	Uxisa;
	Widget	UxplantOverview;
	Widget	UxplantButton;
	Widget	UxseparatorGadget1;
	Widget	Uxproceso1;
	Widget	UxdrawingArea;
	Widget	UxtitleAreaform;
	Widget	UxtitleLabel;
	Widget	UxvertHierButton;
	Widget	UxorizHierButton;
	unsigned char	*Uxpath_icone;
	unsigned char	Uxicon[255];
	unsigned char	UxiconOnScreen[255];
	XtIntervalId	Uxtimer_refresh;
	int	Uxkey_refresh;
	Region	Uxregion_sin;
	WidgetList	Uxlista_wid;
	int	Uxnum_wid;
	int	Uxtime_ref;
	int	Uxtop_x;
	int	Uxtop_y;
	int	Uxtop_width;
	int	Uxtop_height;
	int	Uxtop_tipo;
	unsigned char	*Uxtop_descrizione;
	int	Uxprogress;
	int	Uxpos_pag_curr;
	int	Uxpos_pag_new;
	int	UxnumChildPagList;
	Widget	*UxChildPagList;
	int	*UxlistaPushButton;
	int	*Uxlista_fa;
	int	Uxnum_fa;
	int	Uxnum_telepag;
	Widget	UxOrizMenu;
	Widget	UxOrizPopup;
	Widget	UxOrizPane;
	Widget	*UxlistaPushButtonOr;
	Widget	UxPlantMenu;
	Widget	UxPlantPane;
	Widget	*UxlistaPushButtonPlant;
	Widget	*UxlistaLabelPlant;
	int	UxOrizMenuIsActive;
	Widget	UxVertMenu;
	Widget	UxVertPopup;
	Widget	UxVertPane;
	Widget	UxVertTop;
	Widget	UxRowPull;
	Widget	*UxlistaPushButtonVr;
	Widget	*UxlistaCaiVr;
	Widget	UxlistaCaiHeader[5];
	Widget	*UxlistaCaiFormVr;
	Widget	*UxlistaPlantAsd;
	int	UxnpagPulldown;
	int	UxVertMenuIsActive;
	OlTreeObject	Uxcurr_level;
	XtIntervalId	Uxtimer_timerefresh;
	XtIntervalId	Uxtimer_timerefreshCai;
	XtIntervalId	Uxtimer_timerefreshCaiHeader;
	unsigned char	UxgerarchiaHeader[30];
	unsigned char	UxlabelCaiHeader[100];
	int	Uxscreen_selezionato;
	int	Uxscreen_switched;
	XrmDatabase	UxPagDb;
	int	UxpullMenuOn;
	Widget	*UxpullDownActive;
	Pixel	Uxdef_background_butt;
	Pixel	Uxdef_armColor_butt;
	Pixel	Uxdef_topShadowColor_butt;
	Pixel	Uxdef_bottomShadowColor_butt;
	unsigned char	Uxdef_background_emission[256];
	unsigned char	Uxdef_background_acknowledge[256];
	Widget	Uxall_topLevelShell;
	Widget	Uxall_form_topLevelShell;
	Widget	Uxall_form_title;
	Widget	Uxall_old;
	Widget	Uxall_new;
	Widget	Uxall_old_button;
	Widget	Uxall_new_label;
	Widget	Uxall_old_label;
	Widget	Uxall_new_button;
	Widget	Uxall_title_label;
	Widget	Uxall_header_mainForm;
	Widget	Uxheader_rowColumn;
	Widget	*Uxlista_header_label;
	Widget	*Uxlista_header_rowColumn;
	Widget	*Uxlista_header_copri;
	Widget	*Uxlista_header_form;
	Widget	*Uxlista_header_button;
	Widget	Uxall_formAll;
	Widget	Uxall_rowColumn_caiAll;
	Widget	Uxall_rowColumn_nameAll;
	Widget	Uxall_rowColumn_descrAll;
	Widget	Uxall_rowColumn_dataAll;
	Widget	*Uxall_caiAll_form;
	Widget	*Uxall_name_label;
	Widget	*Uxall_descr_label;
	Widget	*Uxall_data_label;
	Widget	*Uxall_caiAll;
	Widget	Uxall_button_minus;
	Widget	Uxall_button_plus;
	Widget	Uxall_button_n;
	int	UxmodoPageAll;
	unsigned char	UxgerarchiaValoreAll[16][60];
	DATI_ALLARMI_SHM	Uxold_allarmi;
	Pixmap	Uxdrawing_pixmap;
	XrmDatabase	UxOldTeleDb;
	int	Uxoperazione_attiva;
	Boolean	UxInfoUsed;
	Widget	UxListaWidVar[7];
	Pixel	Uxdef_col_menuSystem;
	swidget	UxUxParent;
	AN_PAG	*UxPag;
	unsigned char	*Uxnome_display;
} _UxCteleperm;

static _UxCteleperm            *UxTelepermContext;
#define teleperm                UxTelepermContext->Uxteleperm
#define formTop                 UxTelepermContext->UxformTop
#define screenFooterForm        UxTelepermContext->UxscreenFooterForm
#define rcFooter                UxTelepermContext->UxrcFooter
#define previous                UxTelepermContext->Uxprevious
#define left                    UxTelepermContext->Uxleft
#define up                      UxTelepermContext->Uxup
#define right                   UxTelepermContext->Uxright
#define swscreen                UxTelepermContext->Uxswscreen
#define ackaud                  UxTelepermContext->Uxackaud
#define ackal                   UxTelepermContext->Uxackal
#define hardcopy                UxTelepermContext->Uxhardcopy
#define help                    UxTelepermContext->Uxhelp
#define screenHeaderForm        UxTelepermContext->UxscreenHeaderForm
#define rcProcess               UxTelepermContext->UxrcProcess
#define proceso                 UxTelepermContext->Uxproceso
#define processDisplay          UxTelepermContext->UxprocessDisplay
#define formSystem              UxTelepermContext->UxformSystem
#define menuSystem              UxTelepermContext->UxmenuSystem
#define menuSystem_rc1          UxTelepermContext->UxmenuSystem_rc1
#define menuSystem_rc1_b7       UxTelepermContext->UxmenuSystem_rc1_b7
#define logoff                  UxTelepermContext->Uxlogoff
#define menuSystem_rc1_b8       UxTelepermContext->UxmenuSystem_rc1_b8
#define commonAck               UxTelepermContext->UxcommonAck
#define menuSystem_rc1_b9       UxTelepermContext->UxmenuSystem_rc1_b9
#define logSelection            UxTelepermContext->UxlogSelection
#define menuSystem_rc1_b10      UxTelepermContext->UxmenuSystem_rc1_b10
#define IncidentRew             UxTelepermContext->UxIncidentRew
#define menuSystem_rc1_b11      UxTelepermContext->UxmenuSystem_rc1_b11
#define longTermArc             UxTelepermContext->UxlongTermArc
#define menuSystem_rc1_b12      UxTelepermContext->UxmenuSystem_rc1_b12
#define aing                    UxTelepermContext->Uxaing
#define menuSystem_rc1_b13      UxTelepermContext->UxmenuSystem_rc1_b13
#define plot                    UxTelepermContext->Uxplot
#define menuSystem_csbutt       UxTelepermContext->UxmenuSystem_csbutt
#define rcData                  UxTelepermContext->UxrcData
#define Data                    UxTelepermContext->UxData
#define Ora                     UxTelepermContext->UxOra
#define formCaiPlant            UxTelepermContext->UxformCaiPlant
#define isa                     UxTelepermContext->Uxisa
#define plantOverview           UxTelepermContext->UxplantOverview
#define plantButton             UxTelepermContext->UxplantButton
#define separatorGadget1        UxTelepermContext->UxseparatorGadget1
#define proceso1                UxTelepermContext->Uxproceso1
#define drawingArea             UxTelepermContext->UxdrawingArea
#define titleAreaform           UxTelepermContext->UxtitleAreaform
#define titleLabel              UxTelepermContext->UxtitleLabel
#define vertHierButton          UxTelepermContext->UxvertHierButton
#define orizHierButton          UxTelepermContext->UxorizHierButton
#define path_icone              UxTelepermContext->Uxpath_icone
#define icon                    UxTelepermContext->Uxicon
#define iconOnScreen            UxTelepermContext->UxiconOnScreen
#define timer_refresh           UxTelepermContext->Uxtimer_refresh
#define key_refresh             UxTelepermContext->Uxkey_refresh
#define region_sin              UxTelepermContext->Uxregion_sin
#define lista_wid               UxTelepermContext->Uxlista_wid
#define num_wid                 UxTelepermContext->Uxnum_wid
#define time_ref                UxTelepermContext->Uxtime_ref
#define top_x                   UxTelepermContext->Uxtop_x
#define top_y                   UxTelepermContext->Uxtop_y
#define top_width               UxTelepermContext->Uxtop_width
#define top_height              UxTelepermContext->Uxtop_height
#define top_tipo                UxTelepermContext->Uxtop_tipo
#define top_descrizione         UxTelepermContext->Uxtop_descrizione
#define progress                UxTelepermContext->Uxprogress
#define pos_pag_curr            UxTelepermContext->Uxpos_pag_curr
#define pos_pag_new             UxTelepermContext->Uxpos_pag_new
#define numChildPagList         UxTelepermContext->UxnumChildPagList
#define ChildPagList            UxTelepermContext->UxChildPagList
#define listaPushButton         UxTelepermContext->UxlistaPushButton
#define lista_fa                UxTelepermContext->Uxlista_fa
#define num_fa                  UxTelepermContext->Uxnum_fa
#define num_telepag             UxTelepermContext->Uxnum_telepag
#define OrizMenu                UxTelepermContext->UxOrizMenu
#define OrizPopup               UxTelepermContext->UxOrizPopup
#define OrizPane                UxTelepermContext->UxOrizPane
#define listaPushButtonOr       UxTelepermContext->UxlistaPushButtonOr
#define PlantMenu               UxTelepermContext->UxPlantMenu
#define PlantPane               UxTelepermContext->UxPlantPane
#define listaPushButtonPlant    UxTelepermContext->UxlistaPushButtonPlant
#define listaLabelPlant         UxTelepermContext->UxlistaLabelPlant
#define OrizMenuIsActive        UxTelepermContext->UxOrizMenuIsActive
#define VertMenu                UxTelepermContext->UxVertMenu
#define VertPopup               UxTelepermContext->UxVertPopup
#define VertPane                UxTelepermContext->UxVertPane
#define VertTop                 UxTelepermContext->UxVertTop
#define RowPull                 UxTelepermContext->UxRowPull
#define listaPushButtonVr       UxTelepermContext->UxlistaPushButtonVr
#define listaCaiVr              UxTelepermContext->UxlistaCaiVr
#define listaCaiHeader          UxTelepermContext->UxlistaCaiHeader
#define listaCaiFormVr          UxTelepermContext->UxlistaCaiFormVr
#define listaPlantAsd           UxTelepermContext->UxlistaPlantAsd
#define npagPulldown            UxTelepermContext->UxnpagPulldown
#define VertMenuIsActive        UxTelepermContext->UxVertMenuIsActive
#define curr_level              UxTelepermContext->Uxcurr_level
#define timer_timerefresh       UxTelepermContext->Uxtimer_timerefresh
#define timer_timerefreshCai    UxTelepermContext->Uxtimer_timerefreshCai
#define timer_timerefreshCaiHeader UxTelepermContext->Uxtimer_timerefreshCaiHeader
#define gerarchiaHeader         UxTelepermContext->UxgerarchiaHeader
#define labelCaiHeader          UxTelepermContext->UxlabelCaiHeader
#define screen_selezionato      UxTelepermContext->Uxscreen_selezionato
#define screen_switched         UxTelepermContext->Uxscreen_switched
#define PagDb                   UxTelepermContext->UxPagDb
#define pullMenuOn              UxTelepermContext->UxpullMenuOn
#define pullDownActive          UxTelepermContext->UxpullDownActive
#define def_background_butt     UxTelepermContext->Uxdef_background_butt
#define def_armColor_butt       UxTelepermContext->Uxdef_armColor_butt
#define def_topShadowColor_butt UxTelepermContext->Uxdef_topShadowColor_butt
#define def_bottomShadowColor_butt UxTelepermContext->Uxdef_bottomShadowColor_butt
#define def_background_emission UxTelepermContext->Uxdef_background_emission
#define def_background_acknowledge UxTelepermContext->Uxdef_background_acknowledge
#define all_topLevelShell       UxTelepermContext->Uxall_topLevelShell
#define all_form_topLevelShell  UxTelepermContext->Uxall_form_topLevelShell
#define all_form_title          UxTelepermContext->Uxall_form_title
#define all_old                 UxTelepermContext->Uxall_old
#define all_new                 UxTelepermContext->Uxall_new
#define all_old_button          UxTelepermContext->Uxall_old_button
#define all_new_label           UxTelepermContext->Uxall_new_label
#define all_old_label           UxTelepermContext->Uxall_old_label
#define all_new_button          UxTelepermContext->Uxall_new_button
#define all_title_label         UxTelepermContext->Uxall_title_label
#define all_header_mainForm     UxTelepermContext->Uxall_header_mainForm
#define header_rowColumn        UxTelepermContext->Uxheader_rowColumn
#define lista_header_label      UxTelepermContext->Uxlista_header_label
#define lista_header_rowColumn  UxTelepermContext->Uxlista_header_rowColumn
#define lista_header_copri      UxTelepermContext->Uxlista_header_copri
#define lista_header_form       UxTelepermContext->Uxlista_header_form
#define lista_header_button     UxTelepermContext->Uxlista_header_button
#define all_formAll             UxTelepermContext->Uxall_formAll
#define all_rowColumn_caiAll    UxTelepermContext->Uxall_rowColumn_caiAll
#define all_rowColumn_nameAll   UxTelepermContext->Uxall_rowColumn_nameAll
#define all_rowColumn_descrAll  UxTelepermContext->Uxall_rowColumn_descrAll
#define all_rowColumn_dataAll   UxTelepermContext->Uxall_rowColumn_dataAll
#define all_caiAll_form         UxTelepermContext->Uxall_caiAll_form
#define all_name_label          UxTelepermContext->Uxall_name_label
#define all_descr_label         UxTelepermContext->Uxall_descr_label
#define all_data_label          UxTelepermContext->Uxall_data_label
#define all_caiAll              UxTelepermContext->Uxall_caiAll
#define all_button_minus        UxTelepermContext->Uxall_button_minus
#define all_button_plus         UxTelepermContext->Uxall_button_plus
#define all_button_n            UxTelepermContext->Uxall_button_n
#define modoPageAll             UxTelepermContext->UxmodoPageAll
#define gerarchiaValoreAll      UxTelepermContext->UxgerarchiaValoreAll
#define old_allarmi             UxTelepermContext->Uxold_allarmi
#define drawing_pixmap          UxTelepermContext->Uxdrawing_pixmap
#define OldTeleDb               UxTelepermContext->UxOldTeleDb
#define operazione_attiva       UxTelepermContext->Uxoperazione_attiva
#define InfoUsed                UxTelepermContext->UxInfoUsed
#define ListaWidVar             UxTelepermContext->UxListaWidVar
#define def_col_menuSystem      UxTelepermContext->Uxdef_col_menuSystem
#define UxParent                UxTelepermContext->UxUxParent
#define Pag                     UxTelepermContext->UxPag
#define nome_display            UxTelepermContext->Uxnome_display



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_teleperm();

/*******************************************************************************
Declarations of methods
*******************************************************************************/

static int	_teleperm_orizHier();
static int	_teleperm_drawPush();
static int	_teleperm_openStaz();
static int	_teleperm_aggHeaderArea();
static int	_teleperm_switchScreen();
static int	_teleperm_moveleft();
static int	_teleperm_moveup();
static int	_teleperm_openTopProcDisplay();
static int	_teleperm_navigation();
static void	_teleperm_decorationToggle();
static int	_teleperm_createCaiHeader();
static int	_teleperm_createButtonPixmap();
static int	_teleperm_moveroot();
static int	_teleperm_closeOW();
static Boolean	_teleperm_close_allPage();
static int	_teleperm_xaing();
static int	_teleperm_refreshAllPageWidgets();
static int	_teleperm_popupPage();
static int	_teleperm_ridisegna();
static int	_teleperm_gotopag();
static int	_teleperm_xplot();
static int	_teleperm_application();
static int	_teleperm_previousPag();
static int	_teleperm_isOldAlarmPage();
static int	_teleperm_moveright();
static void	_teleperm_chPage();
static int	_teleperm_aggTitleArea();
static int	_teleperm_aggListChild();
static int	_teleperm_dispData();
static void	_teleperm_closePag();
static int	_teleperm_create_allPage();
static int	_teleperm_WidgetSelect();
static int	_teleperm_info();
static int	_teleperm_dispTime();
static int	_teleperm_vertHier();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

/********************************  
 * interfaccia per uso esterno del 
 * metodo aggListChild
 ********************************/
int aggiornaListChild( Widget ow )
{
   Widget parent;
 
   parent = XtParent(ow);
   teleperm_aggListChild( parent,&UxEnv, ow );
}

/***********************
* costruzione dei CAI
************************/
static void build_cai(listaCai,nomeLista,parent,leftWidget,gerarchia,i)
Widget *listaCai;
char *nomeLista;
Widget parent;
Widget leftWidget;
char *gerarchia;
int i;
{
char nomeCai[100];
Dimension alt,larg;
XmFontList caiFont;
Pixel background_parent;


/*
Lettera e bordo Cai in base a parent background
*/
get_something(parent,XmNbackground,&background_parent);
/*
Posizione Cai in base a widget di sx
*/
get_something(leftWidget,XmNheight,&alt);
get_something(leftWidget,XmNwidth,&larg);
/*printf("builCai: gerarchia=%s\n",gerarchia);*/

        strcpy(nomeCai,nomeLista);
        strcat(nomeCai,"A");
if(parent==leftWidget) /* Cai appaiono da soli */
	{
	listaCai[i*MAXNUMCAIXLINE]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,leftWidget,
			XmNtopWidget,leftWidget,*/
			XmNtopAttachment,XmATTACH_FORM,
			XmNleftAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_A,
			XmNleftOffset,LEFTOFFSET,
			XlNcolorBord,background_parent,
			XmNtopOffset,TOPOFFSET,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif
			XlNvarGerarchia,gerarchia,
			NULL);
	}
else
	{
	listaCai[i*MAXNUMCAIXLINE]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,leftWidget,
			XmNtopAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_A,
			XmNleftOffset,LEFTOFFSET,
			XlNcolorBord,background_parent,
			XmNtopOffset,TOPOFFSET,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif
			XlNvarGerarchia,gerarchia,
			NULL);
	}		
	UxPutContext( listaCai[i*MAXNUMCAIXLINE],(char *) UxTelepermContext );

        strcpy(nomeCai,nomeLista);
        strcat(nomeCai,"W");

	listaCai[i*MAXNUMCAIXLINE+1]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE],
			/*XmNtopWidget,leftWidget,*/
			XmNtopAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_W,
			XmNleftOffset,LEFTOFFSET,
			XmNtopOffset,TOPOFFSET,
			XlNcolorBord,background_parent,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif
			XlNvarGerarchia,gerarchia,
			NULL);

	UxPutContext( listaCai[i*MAXNUMCAIXLINE+1],(char *) UxTelepermContext );

        strcpy(nomeCai,nomeLista);
        strcat(nomeCai,"T");

	listaCai[i*MAXNUMCAIXLINE+2]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+1],
			/*XmNtopWidget,leftWidget,*/
			XmNtopAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_T,
			XmNleftOffset,LEFTOFFSET,
			XmNtopOffset,TOPOFFSET,
			XlNcolorBord,background_parent,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif

			XlNvarGerarchia,gerarchia,
			NULL);

	UxPutContext( listaCai[i*MAXNUMCAIXLINE+2],(char *) UxTelepermContext );

        strcpy(nomeCai,nomeLista);
        strcat(nomeCai,"M");
	listaCai[i*MAXNUMCAIXLINE+3]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+2],
			/*XmNtopWidget,leftWidget,*/
			XmNtopAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_M,
			XmNleftOffset,LEFTOFFSET,
			XmNtopOffset,TOPOFFSET,
			XlNcolorBord,background_parent,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif

			XlNvarGerarchia,gerarchia,
			NULL);

	UxPutContext( listaCai[i*MAXNUMCAIXLINE+3],(char *) UxTelepermContext );

        strcpy(nomeCai,nomeLista);
        strcat(nomeCai,"F");
	listaCai[i*MAXNUMCAIXLINE+4]= XtVaCreateManagedWidget(nomeCai,
			xlCaiWidgetClass,
			parent,
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/
			XmNleftAttachment,XmATTACH_WIDGET,
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+3],
			/*XmNtopWidget,leftWidget,*/
			XmNtopAttachment,XmATTACH_FORM,
			XlNtipoCai, CAI_F,
			XmNleftOffset,LEFTOFFSET,
			XmNtopOffset,TOPOFFSET,
			XlNcolorBord,background_parent,
#ifndef DESIGN_TIME
			XlNconfig, False,
#endif

			XlNvarGerarchia,gerarchia,
			NULL);

	UxPutContext( listaCai[i*MAXNUMCAIXLINE+4],(char *) UxTelepermContext );




}

static void teleperm_refreshTime(wid)
swidget wid;
{
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;
   float simTime;

   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );

/* refresh del tempo di simulazione
*/
  simTime = OlGetTime(database_simulatore);
  teleperm_dispTime(teleperm,&UxEnv,simTime);

/* 
        carica il timer per il refresh
*/
   timer_timerefresh = XtAppAddTimeOut (
         XtWidgetToApplicationContext (wid),
         (unsigned long) (1000) ,teleperm_refreshTime, wid);

   UxTelepermContext = UxSaveCtx;
 
}
static void teleperm_refreshCai(wid)
swidget wid;
{
int i;
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;


   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );
/*
Faccio la refresh dei soli Cai del pullDownMenu 
attivo in quel momento
*/


   XlRefreshWidget(listaCaiVr,npagPulldown);

   timer_timerefreshCai = XtAppAddTimeOut (
         XtWidgetToApplicationContext (wid),
         (unsigned long) (1000) ,teleperm_refreshCai, wid);


   UxTelepermContext = UxSaveCtx;
 
}
static void teleperm_refreshCaiHeader(wid)
swidget wid;
{
int i;
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;


   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );

   XlRefreshWidget(listaCaiHeader,MAXNUMCAIXLINE);


   timer_timerefreshCaiHeader = XtAppAddTimeOut (
         XtWidgetToApplicationContext (wid),
         (unsigned long) (1000) ,teleperm_refreshCaiHeader, wid);


   UxTelepermContext = UxSaveCtx;
 
}
static void teleperm_refreshAllPage(wid)
swidget wid;
{
  _UxCteleperm            *UxSaveCtx = UxTelepermContext;


   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );
/*
chiamo metodo di Refresh per pagina allarmi 
*/
teleperm_refreshAllPageWidgets(teleperm,&UxEnv);
	timer_timerefreshAll = XtAppAddTimeOut (XtWidgetToApplicationContext (wid),
		(unsigned long) (1000) ,teleperm_refreshAllPage,wid);



   UxTelepermContext = UxSaveCtx;
 
}

static void teleperm_refreshPag(wid)
swidget wid;
{
   int i;
   Boolean found = False;
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;
   float simTime;

/* recupero il context 
*/
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );

  if(!OlSetDataPage(database_simulatore,key_refresh))
  {
        printf("Error in refresh\n");
        return;
  }

  if(OlGetDataStatus(database_simulatore,key_refresh)) {   
        XlRefreshWidget(lista_wid,num_wid);
  }
  else {
/*
	MAURIC. Gestione del refresh dell'oggetto XlCurve. L'oggetto XlCurve deve essere
	rinfrescato anche se non fa riferimento al database del simulatore (deve visualizzare
	i valori presenti nel file f22circ.dat per un certo numero di variabili configurate).
        05/11/1997
*/ 
     i=0;
     while((found==False)&&(i<num_wid)) {
        found=XlIsCurve(lista_wid[i]);
        i++;
     }
     if(found==True)
        XlRefreshWidget(lista_wid,num_wid);
  }

   if(!OlUnsetDataPage(database_simulatore,key_refresh))
        {
        printf("Error in refresh\n");
        return;
        }

/*
        carica il timer per il refresh
*/
      timer_refresh = XtAppAddTimeOut (
            XtWidgetToApplicationContext (teleperm),
            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm);

/* switch del context
*/
   UxTelepermContext = UxSaveCtx;


}



/* routine interfaccia verso moduli esterni per chiusura pagina
*/
void telep_chiudi_pag( w )
Widget w;
{
   /* chiamo il metodo closePag
   */
   teleperm_closePag( w,&UxEnv,w);
}
/*
Funzione per aprire pagine di Stazione da PlantDisplay di 
tipo Teleperm
*/
void teleperm_apriStaz(pagina,Padre, nome_disp,sfondo_staz)
char *pagina;
Widget Padre;
char *nome_disp;
BCK_OBJ *sfondo_staz;
{
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;


   UxTelepermContext = (_UxCteleperm *) UxGetContext( Padre );
   
   teleperm_openStaz(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,pagina,Padre, nome_disp,(char *)sfondo_staz);

   UxTelepermContext = UxSaveCtx;
}
/*
routine interfaccia verso moduli esterni per navigazione teleperm
*/
void teleperm_naviga(wid,direction, indice)
Widget wid;
int direction;
int indice;
{
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;


   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );

/*
Invoco la teleperm navigation passandogli come parametro il wteleperm del giusto screen 
per permettere elaborazione del  Context corretto
N.B.
Lo screen_selezionato deve essere quello Della interfaccia chiamante
Passo anche come parametro il widget chiamante
*/


if( elenco_display[0].scr[screen_selezionato].wteleperm != NULL )
        teleperm_navigation(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,direction,indice,screen_selezionato,wid);
else
	{
        if(pos_pag_new==INDALLPAG) /* creo teleperm con pag corrente */
		{
		if(pos_pag_curr<0)
			{
			fprintf(stderr,"Error: invalid index of selected pag\n");
                        UxTelepermContext = UxSaveCtx;
			return;
			}

		elenco_display[0].scr[screen_selezionato].wteleperm = create_teleperm(elenco_display[0].scr[screen_selezionato].topLevel,
                                                           &pagine[pos_pag_curr],"nome_display");

                if( elenco_display[0].scr[screen_selezionato].wteleperm > 0 )
        	   UxPopupInterface(elenco_display[0].scr[screen_selezionato].wteleperm,no_grab);
		}
     	else
        	{

	        elenco_display[0].scr[screen_selezionato].wteleperm = create_teleperm(elenco_display[0].scr[screen_selezionato].topLevel,
                                                           &pagine[pos_pag_new],"nome_display");

                if( elenco_display[0].scr[screen_selezionato].wteleperm  > 0)
         	   UxPopupInterface(elenco_display[0].scr[screen_selezionato].wteleperm,no_grab); 
       		}
         
           if( elenco_display[0].scr[screen_selezionato].wteleperm  > 0)
	      teleperm_navigation(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,direction,indice,screen_selezionato,wid);

	}

   UxTelepermContext = UxSaveCtx;
}


/* routine per aprire una pagina da oggetto cambio pagina
*/
void teleperm_changePage(drawing,nomePag,tipoOpen)
Widget drawing;
char *nomePag;
int tipoOpen;
{
   teleperm_chPage(teleperm,&UxEnv,drawing,nomePag,tipoOpen);
}

/* get della lista degli indici delle pagine figlie 
   della pagina di un livello dato
*/
int getSubLevel(OlTreeObject level,int **lista_ind,int *npag)
{
   int i;
  
   /* alloco la lista delle pagine (superdimensionata)
      puo' contenere la lista di tutte le pagine
   */
   if( ((*lista_ind) = (int *)XtCalloc(totale_pagine,sizeof(int))) == NULL)
   {
       printf("getSubLevel ERROR in malloc: lista_ind\n");
       return(False);;
   }

   /* get della lista della pagine figlie del livello dato
   */ 
   if( OlTreeGetSubInfo( level,(*lista_ind) ) == True ) 
   {
      (*npag)  = 0 ;
      while( (*lista_ind)[ *npag ] != -1)      
         (*npag) ++; 
   }       
   else
   {
      XtFree(*lista_ind);
      *lista_ind = NULL;
      *npag = 0;     
      return(False);
   }

   return(True);

}



/* callback per i bottoni del plantMenu (creato dinamicamente)
   che chiama il metodo navigation passandogli l'indice di pagina da visualizzare
*/
static void view_fa(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)
{
   int indice;
   OlTreeObject app_oltree,curr_oltree;
   _UxCteleperm            *UxSaveCtx, *UxContext;

   UxSaveCtx = UxTelepermContext;
   UxTelepermContext = UxContext =
                        (_UxCteleperm *) UxGetContext( UxWidget );

   indice = (int)UxClientData;
/*
Sostituita teleperm_navigation con teleperm naviga 
*/
   teleperm_naviga(UxWidget,GOTOPAG,indice);

   UxTelepermContext = UxSaveCtx;
}
/*
Callback per pulsanti di navigazione pagAllarmi
*/
static void command_alarm(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)
{
int comando;
   _UxCteleperm            *UxSaveCtx, *UxContext;

   UxSaveCtx = UxTelepermContext;
   UxTelepermContext = UxContext =
                        (_UxCteleperm *) UxGetContext( UxWidget );

comando=(int)UxClientData;
/*
Spedisco comando allo Scada
*/
if(comando==OL_MODO_ALLARMI)
	{
	modoPageAll=MODO_ALLARMI;
	}
else if(comando==OL_MODO_ARCHIVIO)
	{
	modoPageAll=MODO_ARCHIVIO;
	}


OlCommandAllarmi(database_simulatore,comando);

}
/*
callback per aperura pagina Allarmi da plant Menu'
*/
static void open_allPag_fa(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)
{
int indice_fa,i;
   _UxCteleperm            *UxSaveCtx, *UxContext;

   UxSaveCtx = UxTelepermContext;
   UxTelepermContext = UxContext =
                        (_UxCteleperm *) UxGetContext( UxWidget );


   indice_fa = (int)UxClientData;


/*
Seleziono la zona di impianto solamente se posso aprire la pagina allarmi
cioe' se la pagAll e' sullo screen selezionato o
se la pagAll non e' ancora stata aperta
*/
if((allPageOnScreen==-1) || (allPageOnScreen==screen_selezionato))
        {
	printf("\n\n VALORE di indice_fa=%d\n\n",indice_fa);
	for(i=0;i<NUMMAXZONE;i++)
		{
		if(i==indice_fa)
			zone_status[i]=1;
		else
			zone_status[i]=0;
		}
	}
/*
Parte per creazione Pag Allarmi
*/

teleperm_naviga(UxWidget,GOTOPAG,INDALLPAGFROMPLANT);
 
}


/*
callback per bottone newest per pagAllarmi [n]
*/
static void go_newest(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)
{
DATI_ALLARMI_SHM allarmi,vecchi_allarmi;
int num_tot_allarmi,old_allarmi_a;
long n_sleep;
time_t time_end,time_start;  /* Var per timeout */

 _UxCteleperm            *UxSaveCtx, *UxContext;

   UxSaveCtx = UxTelepermContext;
   UxTelepermContext = UxContext =
                        (_UxCteleperm *) UxGetContext( UxWidget );

/*acquisisco allarmi */
OlGetDataAllarmi(database_simulatore,&allarmi);

if(modoPageAll==MODO_ALLARMI)
	num_tot_allarmi=allarmi.num_all_da_ric;
else num_tot_allarmi=allarmi.num_all_arc;

memset(&vecchi_allarmi,0,sizeof(DATI_ALLARMI_SHM));
old_allarmi_a=0;

printf("go_newest:allarmi.num_all_da_ric=%d allarmi.num_all_arc=%d\n",allarmi.num_all_da_ric,allarmi.num_all_arc);
/*
Variabile ambiente per taratura tempo di sleep su lettura shm
*/
if( XlGetenv("N_SLEEP") != NULL )
   n_sleep=atol(XlGetenv("N_SLEEP"));
else
   n_sleep=DEF_TIME_OUT_N; 

printf("go_newest:num_tot_allarmi=%d n_sleep=%ld\n",num_tot_allarmi,n_sleep);

/*
Finche' non sono arrivato agli allarmi piu' nuovi...
invia comando ALLARMI_AVANTI
*/
time(&time_start);
while(allarmi.allarmi_a<num_tot_allarmi)
	{
        time(&time_end);
        if((time_end-time_start) > TOLERANCE_N_TIME)
           {
           printf("\nWARNING : Time-out elapsed \n");
           printf("WARNING : Impossible retrieving newest Alarms\n\n");
           break;
           }
/*
printf("\ngo_newest:allarmi.allarmi_a=%d num_tot_allarmi=%d\n\n",allarmi.allarmi_a,num_tot_allarmi);
*/
	if((OlGetDataAllarmi(database_simulatore,&allarmi)) &&
           (old_allarmi_a!=allarmi.allarmi_a) &&
           (allarmi.allarmi_a<num_tot_allarmi))
		{
                printf("gonewest: lancio comando AVANTI\n");
                time(&time_start);
		if(OlCommandAllarmi(database_simulatore,OL_AVANTI_ALLARMI))
/*
			memcpy(&vecchi_allarmi,&allarmi,sizeof(DATI_ALLARMI_SHM));
*/
                        old_allarmi_a=allarmi.allarmi_a;
		else 
			{
			printf("WARNING : Impossible retrieving newest Alarms\n");
			break;
			}
		}
        usleep(n_sleep);
	}

printf("go_newest:exit !!!\n");
}
/*
Callback per pulsanti di header per pagAllarmi
*/

static void select_zone(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)
{
 int zona; /* zona selezionata passata come argomanto della callback*/  
Boolean zone_attive; /* verifico che esistano zone attive */
int kk;
 Pixel background_color,arm_color,top_shadow,bottom_shadow;/* Pixels per effetto "schiacciamento bottone*/
   _UxCteleperm            *UxSaveCtx, *UxContext;


   UxSaveCtx = UxTelepermContext;
   UxTelepermContext = UxContext =
                        (_UxCteleperm *) UxGetContext( UxWidget );

   zona = (int)UxClientData;
   zone_attive=False;

/* 
Cambia visualizzazione bottone 
*/

/* Acquisisco valori dei colori del bottone */

XtVaGetValues(UxWidget,XmNarmColor,&arm_color,NULL);
XtVaGetValues(UxWidget,XmNbackground,&background_color,NULL);
XtVaGetValues(UxWidget,XmNtopShadowColor,&top_shadow,NULL);
XtVaGetValues(UxWidget,XmNbottomShadowColor,&bottom_shadow,NULL);

/* Setto nuovi valori del bottone (scambio bordini e sfondi)*/

XtVaSetValues(UxWidget,XmNbackground,arm_color,NULL);
XtVaSetValues(UxWidget,XmNarmColor,background_color,NULL);
XtVaSetValues(UxWidget,XmNtopShadowColor,bottom_shadow,NULL);
XtVaSetValues(UxWidget,XmNbottomShadowColor,top_shadow,NULL);

/*Cambia lo stato della zona*/
if(zone_status[zona]==1)
	zone_status[zona]=0;
else
       {
	zone_status[zona]=1;
        last_zone_pressed=zona;    /* tiene conto della ultima zona premuta X due
                                    utenti che selezionano la stessa zona */
       }
printf("zona premuta=%d\n",zona);

/*
Verifico se esistono zone attive
*/
for(kk=1;kk<NUMMAXZONE;kk++)
          {
          if(zone_status[kk]==1)
               {
              zone_attive=True; /* almeno una zona e' attiva */
              break;
              }
          }
/* Se la zona non e' stata selezionata da altro utente */
if(zone_ko==-1)
	{
	if((modoPageAll== MODO_ALLARMI) && zone_attive)
 		{
		OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
		}
	else if((modoPageAll== MODO_ARCHIVIO) && zone_attive)
		{
		/* Sospendo refresh per evitare visualizzazione dopo OlTeleperm_richiediAllarmi */
		XtRemoveTimeOut(timer_timerefreshAll);
		
		OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
		OlCommandAllarmi(database_simulatore,OL_MODO_ARCHIVIO);	
		/* Rimetto il Refresh */
		teleperm_refreshAllPage(all_form_topLevelShell);
		}
       } /* end if(zone_ko==-1) */

   UxTelepermContext = UxSaveCtx;
}

/* setta il titolo della pagina nella titleAreaForm
   Il titolo impostato equivale alla risorsa della pagina top_descrizione
   che e' presente come stringa nella struttura della pagina
*/
void set_titleLabel(char *descr)
{
   XmString xstr;
  
   xstr = XmStringCreateSimple(descr);   
   set_something(titleLabel,XmNlabelString,xstr);
   XmStringFree(xstr);
}

/* interfaccia per l'esterno del metodo
*/
int teleperm_IcoSelect( Widget UxThis, Environment *penv, Widget w)
{
   teleperm_WidgetSelect(UxThis,penv,w);
}
/* 
Interfaccia per l'esterno del metodo
*/
int teleperm_ApplSelect( Widget UxThis, Environment *penv, Widget w)
{
   teleperm_application(UxThis,penv,w);
}
int recognize_fa()
{
int indice_fa,i;
char *str,appo[200];
/*******************************************************
Ricavo la lista delle functional Area
Vado a vedere quali nodi del primo livello sono attivi
-> abilito le corrispondenti fa
********************************************************/
memset(selectable_zone,0,NUMMAXZONE*sizeof(int));
num_telepag=0;
if( getSubLevel(root_oltree,&lista_fa,&num_fa) != True )
    return;
printf("numero di fa=%d\n",num_fa);
/*
Vado a determinare le zone attive
*/
if(num_fa)
        for(i=0;i<num_fa;i++)
                {
		if( !PagIsTeleperm(pagine[lista_fa[i]]) )
                        {
                         printf("###############################################################\n");
                         printf("SEVERE ERROR: functional area associated with a notteleperm page\n");
                         printf(" ERROR: functional area=%d -- notteleperm page=%s\n",i,pagine[lista_fa[i]].nome);
                         printf("###############################################################\n");
                        return;
                        }
                strcpy(appo,pagine[lista_fa[i]].gerarchia);
                strtok(appo,",");
                str=strtok((char *)NULL,",");
                if(!str)
                        {
                        printf("ERROR: hierarchy function Area page not correct!\n");
                        return(-1);
                        }
                indice_fa=atoi(str);
                /*
                Associo l' indice del nodo nell' elenco pagine, alla zona
                abilitata
                */
                if(indice_fa)  /* Escludo la zona 0 */
			{
                        selectable_zone[indice_fa]=lista_fa[i];
			num_telepag++;
			if(indice_fa>last_indice_fa)
				last_indice_fa=indice_fa;
			/*printf("num_telepag=%d lista_fa[%d]=%d indice_fa=%d\n",num_telepag,i,lista_fa[i],indice_fa);*/
			}
                }
                  
printf("num_telepag=%d \n",num_telepag);
printf("last_indice_fa=%d \n",last_indice_fa);
/* 
Parte che decide quante righe nella parte header AllPag devo utilizzare 
*/ 
if((last_indice_fa>0) && (last_indice_fa<=18))
      {
      num_zone=HEADERTRERIGHE;   /* tre righe */
      }
else if((last_indice_fa>18) && (last_indice_fa<25))
      {
      num_zone=HEADERQUATTRORIGHE;     /* 4 righe */
      }
else if(( last_indice_fa>25) && (last_indice_fa<31))
      {
      num_zone=HEADERCINQUERIGHE;    /* 5 righe di bottoni */
      }                 
XtFree(lista_fa);
return(1);                                
}

/*******************************************************************************
       The following are method functions.
*******************************************************************************/

static int	Ux_orizHier( UxThis, pEnv, lista_ind, npag )
	swidget	UxThis;
	Environment *	pEnv;
	int	**lista_ind;
	int	*npag;
{
	OlTreeObject curr_oltree;
	int i;
	int pcur,parente,progr;
	
	 
	/* recupero il parent della pagina attuale
	   e la lista dei figli, ottengo cosi la lista orizzontale della gerarchia
	   NOTA Pag e' il puntatore alla pagina correntemente visualizzata e la
	   sua definizione sta nel Context.
	*/
	
	/* recupero le informazioni sulla pagina corrente
	*/
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,Pag->gerarchia) == False )
	{
	      printf("Error retrieving hierarchy information for this page\n");
	      (*lista_ind) = NULL;
	      (*npag) = 0;
	      return(False);
	}
	
	if( curr_oltree == root_oltree )
	{
	      (*lista_ind) = NULL;
	      (*npag) = 0; 
	      return(True);
	}    
	
	/* recupero l'indice del padre 
	*/
	OlTreeGetTop( curr_oltree, &parente);
	
	 
	/* recupero le informazioni sul padre
	*/ 
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,pagine[parente].gerarchia) == False )
	{
	      printf("Error retrieving hierarchy information for this page\n");      
	      return(False);
	}
	
	/* recupero lista indici pagine figlie, cioe' la lista orizzontale
	*/
	if( getSubLevel( curr_oltree, lista_ind, npag) != True)
	{
	   printf("DEBUG orizHier metod no SubLevel\n");
	   return(False);
	}
	
	return(True);
}

static int	_teleperm_orizHier( UxThis, pEnv, lista_ind, npag )
	swidget	UxThis;
	Environment *	pEnv;
	int	**lista_ind;
	int	*npag;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_orizHier( UxThis, pEnv, lista_ind, npag );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_drawPush( UxThis, pEnv, w, bmpName )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*bmpName;
{
	char pathBmp[255];
	        int ret;
	        Pixmap bmp,pix;
	        int xh,yh,width,height;
	        Pixel bkg_col,arm_col,bot_col,top_col,dummy_col,fg_col;
	        GC gcapp;
	        XGCValues values;
	        unsigned long valuemask =  GCForeground | GCBackground ;
	
	        /* costruisco il file name completo
	        */
	        sprintf(pathBmp,"%s/%s",getenv("LEGOCAD_ICO"),bmpName);
	         
	        /* recupero colori e dimensioni dello widget chiamante
	        */
	        XtVaGetValues(w,
	                            XmNforeground,&fg_col,
	                            XmNbackground,&bkg_col,
	                            XmNarmColor,&arm_col,
	                            XmNbottomShadowColor,&bot_col,
	                            XmNtopShadowColor,&top_col,
	                            XmNx,&xh,
	                            XmNy,&yh,
	                            XmNwidth,&width,
	                            XmNheight,&height,
	                            NULL);
	
	        /* leggo il file bitmap
	        */
	        ret=XReadBitmapFile(XtDisplay(w),
	                        RootWindow(XtDisplay(w),DefaultScreen(XtDisplay(w))),
	                        pathBmp,&width,
	                        &height,
	                        &bmp,&xh,&yh);
	
	          if(ret==BitmapSuccess)
	                printf("Bitmap caricato correttamente\n");
	           else if(ret==BitmapOpenFailed)
	                printf("Apertura fallita\n");
	           else if(ret==BitmapFileInvalid)
	                printf("File bitmap non valido \n");
	           else if(ret==BitmapNoMemory)
	                printf("No memory\n");
	           if(ret!=BitmapSuccess)
	           {
	                printf("Impossibile leggere il file con XReadBitmap\n");
	                return(False);
	           }
	
	
	           /* Creo un pixmap delle dimensioni del bottone
	           */
	           pix=XCreatePixmap(XtDisplay(w),
	                             RootWindow(XtDisplay(w),
	                             DefaultScreen(XtDisplay(w))),
	                             width,
	                             height,
	                             DefaultDepth(XtDisplay(w),
	                             DefaultScreen(XtDisplay(w))));
	
	
	           /* inverto i colori del bottone
	              bkg, arm, top shadow e bottom shadow
	           */
	           dummy_col = bkg_col;
	           bkg_col = arm_col;
	           arm_col = dummy_col;
	           dummy_col = top_col;
	           top_col = bot_col;
	           bot_col = dummy_col;
	
	        /* setto il GC di appoggio
	           per impostare i colori di backg e foreg al pixmap
	        */
	           values.foreground = fg_col;
	           values.background = bkg_col;
	
	           gcapp = XtGetGC(w,valuemask,&values);
	
	           /* tramite la copyPlane ottengo che il pixmap
	              venga costruito in base al bitmap letto
	             con i colori impostati dal GC
	           */
	           XCopyPlane(XtDisplay(w),bmp,pix,
	                gcapp,0,0,
	                width,height,
	                0, 0, 1);
	
	           /* assegno allo widget chiamante il pixmap e i colori
	              nuovi.
	           */
	           XtVaSetValues(w,
	                            XmNforeground,fg_col,
	                            XmNbackground,bkg_col,
	                            XmNarmColor,arm_col,
	                            XmNbottomShadowColor,bot_col,
	                            XmNtopShadowColor,top_col,
	                            XmNlabelPixmap,pix,
	                            NULL);
	        
	/* libero il pixmap
	        XFreePixmap(XtDisplay(w),pix);
	*/
}

static int	_teleperm_drawPush( UxThis, pEnv, w, bmpName )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*bmpName;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_drawPush( UxThis, pEnv, w, bmpName );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_openStaz( UxThis, pEnv, pagina, Padre, nome_disp, sfondo_staz )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*pagina;
	Widget	Padre;
	unsigned char	*nome_disp;
	unsigned char	*sfondo_staz;
{
	Widget w;
	
	
	w=popup_topLevelShellStaz(pagina,Padre,elenco_display[screen_selezionato].nome,
	                          (BCK_OBJ *)sfondo_staz);
	
	
	XrmSetDatabase(XtDisplay((Widget)Padre),PagDb);
}

static int	_teleperm_openStaz( UxThis, pEnv, pagina, Padre, nome_disp, sfondo_staz )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*pagina;
	Widget	Padre;
	unsigned char	*nome_disp;
	unsigned char	*sfondo_staz;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_openStaz( UxThis, pEnv, pagina, Padre, nome_disp, sfondo_staz );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_aggHeaderArea( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	teleperm_dispData(teleperm,&UxEnv);
	/*
	teleperm_plantMenu(teleperm,&UxEnv);
	*/
}

static int	_teleperm_aggHeaderArea( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_aggHeaderArea( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_switchScreen( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/* switch dello screen 
	 */
	if( elenco_display[0].num_screens > 1 )
	{    
	   if(  screen_selezionato == 0   )
	      screen_selezionato = 1;
	   else 
	      screen_selezionato--;
	}
}

static int	_teleperm_switchScreen( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_switchScreen( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_moveleft( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	OlTreeObject curr_oltree;
	int progr;
	/* recupero le informazioni sulla pagina corrente
	*/
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )
	{
	   printf("Error retrieving hierarchy information for this page\n");
	   return(False);
	}
	
	
	/* recupero le informazioni sulla pagina a destra
	*/
	OlTreeGetLeft(curr_oltree,pnew);
	
	
	return(True);
}

static int	_teleperm_moveleft( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_moveleft( UxThis, pEnv, pcurr, pnew );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_moveup( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	OlTreeObject curr_oltree;
	int progr;
	
	
	/* recupero le informiazioni sulla pagina corrente
	*/
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )
	{
	   printf("Error retrieving hierarchy information for this page\n");
	   return(False);
	}
	
	/* 
	recupero le informazioni sulla pagina parent
	*/
	OlTreeGetTop(curr_oltree,pnew);
	
	
	return(True);
}

static int	_teleperm_moveup( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_moveup( UxThis, pEnv, pcurr, pnew );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_openTopProcDisplay( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	char pagName[255];
	char *tipo;
	XrmValue value;
	char risorsa[50];
	Display *disp;
	int i,indice_pagina;
	
	disp = XtDisplay(UxThis);
	
	sprintf(risorsa,"teleperm.topProcDisplay");
	        
	XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);
	        
	if( (value.addr == NULL) || (value.size == 0) )
	{
	   fprintf(stderr,"Warning: cannnot open NULL process display\n");
	   return(False);;
	}
	
	strncpy(pagName,value.addr,(int)value.size);
	
	indice_pagina = 0;       
	for( i=0;i < totale_pagine; i++ )
	   if( !strcmp(pagine[i].nome,pagName) )
	   {
	      indice_pagina = i;
	      break;
	   }
	
	if( i >= totale_pagine )
	{
	   fprintf(stderr,"Warning: topProcessDisplay not found in list\n");
	   return(False);;
	}
	
	teleperm_naviga(UxThis , GOTOPAG,indice_pagina);
	
	return(True);
}

static int	_teleperm_openTopProcDisplay( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_openTopProcDisplay( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_navigation( UxThis, pEnv, direction, pag_ind, screen_selected, calling )
	swidget	UxThis;
	Environment *	pEnv;
	int	direction;
	int	pag_ind;
	int	screen_selected;
	Widget	calling;
{
	/*
	Come primo parametro viene passata l' interfaccia su cui
	aprire una pagina.
	Come 4o parametro (screen_selected) lo screen su cui verra' visualizzata la pag
	Come 5o parametro (calling) un widget appartenente alla interfaccia chiamante
	*/
	
	
	/*
	N.B.
	 poslocal contiene la pagina attualmente visualizzata su UxThis 
	*/
	int retval,poscurr,posnew,poslocal,i;
	extern int num_el_pagine;
	extern PAGINE_APERTE *el_pagine;
	
	
	poslocal= pos_pag_new;
	poscurr = pos_pag_curr;
	posnew = pos_pag_new;
	
	/*
	printf("\n\nNAVIGATION numero_screen=%d allPageOn=%d prevAll=%d\n\n",numero_screen,allPageOnScreen,prevAll);  
	printf("\n\nNAVIGATION pos_pag_new=%d pos_pag_curr=%d \n\n",pos_pag_new,pos_pag_curr);
	*/
	/*
	Acquisisco informazioni dalla interfaccia chiamante
	*/
	switch( direction )
	{
	   case LEFT:
	      retval = teleperm_moveleft(calling,&UxEnv,&poscurr,&posnew);
	   break;
	   case RIGTH:
	      retval = teleperm_moveright(calling,&UxEnv,&poscurr,&posnew);
	   break;
	   case UP:
	      retval = teleperm_moveup(calling,&UxEnv,&poscurr,&posnew);
	   break;
	   case PREVIOUS:
	      retval = teleperm_previousPag(calling,&UxEnv,&poscurr,&posnew);
	   break; 
	   case PLANT_OVW:
	      retval = teleperm_moveroot(calling,&UxEnv,&poscurr,&posnew);
	   break;
	   case GOTOPAG:
	      retval = teleperm_gotopag(calling,&UxEnv,&poscurr,&posnew,pag_ind);
	   break;
	}
	
	if( retval == False )
	{
	   printf("telperm_navigation: direction = %d nothing on this direction\n",direction);
	   return(False);
	}
	
	
	
	
	/*
	printf("\n\n NAVIGATION: valori di posnew=%d e poscurr=%d screen_selected=%d allPageOnScreen=%d\n\n",pos_pag_new,pos_pag_curr,screen_selected,allPageOnScreen);
	*/
	/* 
	Devo fare una distinzione :
	INDALLPAG e' un indice fitttizio per pag allarmi chiamata da isa
	INDALLPAGFROMPLANT e' un indice fitttizio per pag allarmi chiamata da plant Menu'
	Segue una serie di controlli per gestire eccezioni su apertura da pagAll
	*/ 
	
	if((posnew==INDALLPAG) && (allPageOnScreen!=-1)  ) /* tentativo di riaprire pag allarmi da isa */
	 	return(False);
	if(posnew==INDALLPAGFROMPLANT)  /* tentativo di aprire pag allarmi da plantMenu */
		{
		posnew=INDALLPAG;			        /* Controlli su apertura pagAll da plantMenu end -> */
							        /* segnalo che devo aprire una pagAllarmi */
		if(allPageOnScreen!=-1) 			/* pagAll gia aperta */
		   if(screen_selected!=allPageOnScreen)         /* tentativo di aprira allPag da planMenu su uno screen */
			   return(False);                       /* con pag allarmi gia' aperta su un altro -> VIETATO !*/ 
		}
	
	
	         /*
	         Blocco per la gestione della apertura della pagina allarmi di 
	         tipo non-Teleperm. Viene aperta se la pagAll-teleperm non e' gia' aperta
	         Se la pagAll-Teleperm e' gia' aperta, viene impedito di aprire una pagina
	         di tipo Teleperm con l' oggetto XlAllarmi
	         */ 
	
	         if( (allPageOnScreen!=-1) && (posnew!=INDALLPAG))       
	           {
	            printf("DEBUG: Effettuo confronto con =%s \n",pagine[posnew].nome);
	            if( teleperm_isOldAlarmPage(UxThis,pEnv,pagine[posnew].nome ))
	              {
	              return(False);
	              }
	            }
	/*
	Controlli su aperture pagine normali 
	*/
	
	if(posnew!=INDALLPAG)
	  if( el_pagine != NULL)
	   	for(i=0;i<num_el_pagine;i++)
	   	  { 
	      	    if( !strcmp(el_pagine[i].nome,pagine[posnew].nome) )
	      	     {
	             printf("DEBUG:posnew=%s  el_pagine=%s\n",pagine[posnew].nome,el_pagine[i].nome);
	             return(False);
	      	     }       
	   	  }
	
	/* GESTIONE DUE SCREEN
	   chiamo il METODO ridisegna per il refresh della sola drawing area
	   oppure creo la interfaccia su l'altro screen
	
	printf("navigation screen selezionato - %d\n",screen_selected);
	printf("wteleperm[0] - %d\n",elenco_display[0].scr[0].wteleperm);
	printf("wteleperm[1] - %d\n",elenco_display[0].scr[1].wteleperm);
	*/
	/*	printf("\n\nNAVIGATION MIDL posnew=%d poscurr=%d \n\n",posnew,poscurr); */
	
	if( elenco_display[0].scr[screen_selected].wteleperm != NULL )
	{
	/*printf("\n\n elenco_display!= NULL%d\n\n",posnew);*/
	  /* chiudo le operating window
	  */ 
	  teleperm_closeOW(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv);
	  
	  if(allPageOnScreen!=-1 && screen_selected==allPageOnScreen)
		{
	/*printf("\n\nCHIUDO ALLPAG\n\n");*/
		teleperm_close_allPage(elenco_display[0].scr[allPageOnScreen].wteleperm,&UxEnv);
		allPageOnScreen=SINCROCLOSEALLPAG;
		}
		
	  
	  if(posnew==INDALLPAG)
		{
	
	/*printf("\n\nCREO ALLPAG con ridisegna\n\n");*/
	
		if(teleperm_create_allPage(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv)<0)
	           {
	           posnew=poscurr;
	           fprintf(stderr,"\n Impossible to open All page \n");
	           }
	        else
		   allPageOnScreen=screen_selected;
		}
	  else
		{
		/*printf("\n\nRIDISEGNO %d\n\n",posnew);*/
	        teleperm_ridisegna(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv,posnew);
		if(allPageOnScreen==SINCROCLOSEALLPAG)  /* vedo se e' stata appena chiusa la pagALL */
			   allPageOnScreen=-1;
	
	        /*
	        Se contiene XlAllarmi, alla prossima riapertura della pagina Allarmi 
	        si dovra' richiedere gli allarmi per rinfrescare i valori sull' header della 
	        pagina allarmi di tipo Teleperm
	        */
	        if( teleperm_isOldAlarmPage(UxThis,pEnv,pagine[posnew].nome) )
	           prima_apertura_all=True;
	
		}
	}
	else
	{
	printf("\n\n FORBIDDEN OPERATION \n\n ");
	}
	/*printf("\n\nNAVIGATION FINAL pos_pag_new=%d pos_pag_curr=%d \n\n",posnew,poscurr);*/
	
	
	if( poscurr != posnew )
	  {
	/* Aggiornamento indici */
	      pos_pag_curr = poslocal;
	      pos_pag_new = posnew;
	  }
	/*
	Destroy previous page pullDown menu
	*/
	
	if(pullDownActive)
		{
		if(scada_on)
	           XtRemoveTimeOut(timer_timerefreshCai);
	           
	           
		UxDestroyInterface(*pullDownActive);
	        if(scada_on)
	           {
	            XtFree(listaCaiVr);
	            XtFree(listaCaiFormVr);
	            XtFree(listaPushButton);
	           }
		pullDownActive=NULL;
		}
	
	return(True);
}

static int	_teleperm_navigation( UxThis, pEnv, direction, pag_ind, screen_selected, calling )
	swidget	UxThis;
	Environment *	pEnv;
	int	direction;
	int	pag_ind;
	int	screen_selected;
	Widget	calling;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_navigation( UxThis, pEnv, direction, pag_ind, screen_selected, calling );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static void	Ux_decorationToggle( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int decorOn;
	char *tipo;
	XrmValue value;
	char risorsa[50];
	char appo[50];
	
	sprintf(risorsa,"teleperm.decorazioni");
	XrmGetResource(UxDisplay->db,risorsa,(char*)NULL,&tipo,&value);
	strncpy(appo,value.addr,(int)value.size);
	decorOn = atoi(appo);
	
	if( decorOn == 0) 
	{
	   /* questo mette solo un sottile bordino 
	   XtVaSetValues(UxThis,XmNmwmDecorations,MWM_DECOR_BORDER,NULL);
	   */
	   /* elimina tutte le decorazioni
	   */
	   XtVaSetValues(UxThis,XmNmwmDecorations,0,NULL);
	}
	else
	{
	   printf("\n\nWARNING you have application resource 'decoration' set to 1\n");
	   printf("in this mode you can resize this shell\n");
	   printf("change $XAPPLRESDIR/run_time resource file for change\n\n\n");
	
	
	   XtVaSetValues( UxThis,
	                  XmNmwmDecorations,MWM_DECOR_ALL,
	                  XmNallowShellResize, True,
	                  XmNminWidth, 400,
	                  XmNminHeight, 400,
	                  NULL);
	                     
	}
}

static void	_teleperm_decorationToggle( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	Ux_decorationToggle( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;
}

static int	Ux_createCaiHeader( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/*
	Funzione che permette di disegnare i Cai sull' header della pagina teleperm.
	La funzione e' invocata alla fine del final code dell' interfaccia teleperm
	*/
	char nomeCai[100];      /* MAXCHAR_PAGNAME */
	Pixel background_parent;
	
	
	
	/* gerarchia relativa a root cablata */
	strcpy(gerarchiaHeader,"[0][-1][-1][-1][-1][-1]");
	
	/* Valore sfondo per Cai in transparent  */
	get_something(formCaiPlant,XmNbackground,&background_parent);
	
		strcpy(labelCaiHeader,"HeaderCai");
	        strcpy(nomeCai,labelCaiHeader);
	        strcat(nomeCai,"A");
	
		listaCaiHeader[0]= XtVaCreateManagedWidget(nomeCai,
				xlCaiWidgetClass,
				formCaiPlant,
				XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget,isa,
				XmNtopWidget,isa,
				XlNtipoCai, CAI_A,
				XlNcolorBord,background_parent,
				XmNleftOffset,LEFTOFFSET,
#ifndef DESIGN_TIME
				XlNconfig, False,
#endif
				XlNvarGerarchia,gerarchiaHeader,
				NULL);
	
		UxPutContext( listaCaiHeader[0],(char *) UxTelepermContext );
	
	        strcpy(nomeCai,labelCaiHeader);
	        strcat(nomeCai,"W");
	
		listaCaiHeader[1]= XtVaCreateManagedWidget(nomeCai,
				xlCaiWidgetClass,
				formCaiPlant,
				XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget,isa,
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget,listaCaiHeader[0],
				XlNtipoCai, CAI_W,
				XlNcolorBord,background_parent,
				XmNleftOffset,LEFTOFFSET,
#ifndef DESIGN_TIME
				XlNconfig, False,
#endif
				XlNvarGerarchia,gerarchiaHeader,
				NULL);
	
		UxPutContext( listaCaiHeader[1],(char *) UxTelepermContext );
	        strcpy(nomeCai,labelCaiHeader);
	        strcat(nomeCai,"T");
	
		listaCaiHeader[2]= XtVaCreateManagedWidget(nomeCai,
				xlCaiWidgetClass,
				formCaiPlant,
				XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget,isa,
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget,listaCaiHeader[1],
				XlNcolorBord,background_parent,
				XlNtipoCai, CAI_T,
				XmNleftOffset,LEFTOFFSET,
#ifndef DESIGN_TIME
				XlNconfig, False,
#endif
				XlNvarGerarchia,gerarchiaHeader,
				NULL);
	
		UxPutContext( listaCaiHeader[2],(char *) UxTelepermContext );	
	
	        strcpy(nomeCai,labelCaiHeader);
	        strcat(nomeCai,"M");
	
		listaCaiHeader[3]= XtVaCreateManagedWidget(nomeCai,
				xlCaiWidgetClass,
				formCaiPlant,
				XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget,isa,
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget,listaCaiHeader[2],
				XlNcolorBord,background_parent,
				XlNtipoCai, CAI_M,
				XmNleftOffset,LEFTOFFSET,
#ifndef DESIGN_TIME
				XlNconfig, False,
#endif
				XlNvarGerarchia,gerarchiaHeader,
				NULL);
	
		UxPutContext( listaCaiHeader[3],(char *) UxTelepermContext );	
	
	        strcpy(nomeCai,labelCaiHeader);
	        strcat(nomeCai,"F");
	
		listaCaiHeader[4]= XtVaCreateManagedWidget(nomeCai,
				xlCaiWidgetClass,
				formCaiPlant,
				XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget,isa,
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget,listaCaiHeader[3],
				XlNtipoCai, CAI_F,
				XlNcolorBord,background_parent,
				XmNleftOffset,LEFTOFFSET,
#ifndef DESIGN_TIME
				XlNconfig, False,
#endif
				XlNvarGerarchia,gerarchiaHeader,
				NULL);
	
		UxPutContext( listaCaiHeader[4],(char *) UxTelepermContext );	
	
	/*
	Setto il database dei punti per ogni oggetto Cai
	*/
	OlSetDatabasePunti(listaCaiHeader,MAXNUMCAIXLINE,database_simulatore);
	/*
	Innesco Refresh del Cai
	*/
	teleperm_refreshCaiHeader(formCaiPlant);
}

static int	_teleperm_createCaiHeader( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_createCaiHeader( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_createButtonPixmap( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	Pixmap pix;
	Pixel bg,fg;
	char pathBMP[255];
	int numero_screen;
#ifdef GESTIONE_SU_SCREEN_DIVERSI
	numero_screen=XScreenNumberOfScreen(XtScreen(previous));
	
	XtVaGetValues(previous,
	              XmNforeground,&fg,
	              XmNbackground,&bg,
	              NULL);
	
	sprintf(pathBMP,"%s/previous%d.bmp",getenv("LEGOCAD_ICO"),numero_screen);
	
	pix = XmGetPixmap( XtScreen(UxThis),
	                   pathBMP,
	                   fg,bg);
	
	if( pix == XmUNSPECIFIED_PIXMAP )
	{
	   printf("invalid pixmap %s\n",pathBMP);
	   return(False);
	}
	
	XtVaSetValues(previous,
	              XmNlabelType,XmPIXMAP,
	              XmNlabelPixmap,pix,
	              NULL);
#endif
	return(True);
}

static int	_teleperm_createButtonPixmap( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_createButtonPixmap( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_moveroot( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	OlTreeObject curr_oltree;
	int progr,i;
	
	/* recupero l'indice relativo all root
	   e se non ci sono errori aggiorno il puntatore
	   pcur per la gestione del previous
	*/
	
	if( OlTreeGetPosInfo(root_oltree,pnew) == False )
	   return(False);
	
	*pcurr = pos_pag_new;
	
#ifdef PROVO_A_NON_FARLO
	/* recupero le informazioni sulla pagina corrente
	*/
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )
	{
	
	   /* 20-6-97 carlo gestione pagine fuori gerarchia
	   printf("Error retrieving hierarchy information for this page\n");
	   return(False);
	   */
	
	   for(i=0;i<totale_pagine;i++)
	      if( strcmp(pagine[i].gerarchia,"0,-1,-1,-1,-1,-1") == NULL)
	      {
	         *pnew = i;
	          break;
	      }
	
	      if( i == totale_pagine)
	      {
	          printf("Root page not found\n");
	          return(False);
	      }
	
	      curr_oltree = root_oltree;
	      return(True);
	}
	
	/*
	recupero le informazioni sulla pagina parent
	*/
	while ( curr_oltree != root_oltree )
	   curr_oltree = OlTreeGetTop(curr_oltree,pnew);
	
#endif
	
	return(True);
}

static int	_teleperm_moveroot( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_moveroot( UxThis, pEnv, pcurr, pnew );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_closeOW( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	extern Boolean OW_close();
	Widget drawing;
	int i;
	XrmDatabase StazDb;
	
	/* elimino tutte le OW eventualmente aperte
	*/
	for(i=0;i<numChildPagList;i++)
	{
	   if( (ChildPagList[i] != NULL) )
	   {
	       if( !XtIsRealized( ChildPagList[i] ) )
	          continue;
	
	      /* chiudo solo se lo screen selezionato e' quello dove risiede la OW
	      
	      if( XScreenNumberOfScreen(XtScreen(ChildPagList[i])) == screen_selezionato )
	      Questo test potrebbe essere errato perche' lo screen potrebbe essere stato switchato 
	      */
	if( XScreenNumberOfScreen(XtScreen(ChildPagList[i])) == 
	    XScreenNumberOfScreen(XtScreen( UxThis )) )
	         {
	         
	         OW_close(ChildPagList[i]);
	         }
	   }
	
	}
	
	
	for(i=0;i<num_el_pagine;i++)
	   {
	   if(el_pagine[i].w!=NULL)
	      {
	      /* Ricavo la drawing Area del padre
	         per capire il tipo di pagina */
	      drawing=el_pagine[i].w;
	      if( !strcmp(XtName(drawing),DRAWING_STAZ))
	         {
	         if( XScreenNumberOfScreen(XtScreen(drawing)) ==
	              XScreenNumberOfScreen(XtScreen( UxThis )) )
	              {
	              printf("Sto per chiudere la pagina di Staz.\n");
	              ClosePageStaz(drawing);
	              /* 
	              La stazione elimina il database delle risorse 
	              devo ripristinarlo
	              */
	              
	              XrmSetDatabase(XtDisplay(UxThis),PagDb); 
	              }
	         }
	      }
	
	   }
}

static int	_teleperm_closeOW( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_closeOW( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static Boolean	Ux_close_allPage( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	if((allPageOnScreen==-1) || (OlCanOpenAllarmPage(database_simulatore)))
		return(False);
	XtRemoveTimeOut(timer_timerefreshAll); /*elimino timeoutRefresh */ 
	XtDestroyWidget(all_form_topLevelShell); /*Distruggo l' interfaccia */
	/***********
	Parte destinata a liberazione memoria oggetti multipli
	***********/
	
	XtFree(lista_header_form);
	XtFree(lista_header_button);
	XtFree(lista_header_rowColumn); 
	XtFree(lista_header_label); 
	XtFree(all_caiAll_form); 
	
	XtFree(all_caiAll);
	XtFree(all_name_label); 
	XtFree(all_descr_label); 
	
	XtFree(all_data_label); 
	memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM)); /*vecchi allarmi azzerati */
		
				
	/*
	Riattiva pulsanti navigazione
	*/
	XtSetSensitive(left,True);
	XtSetSensitive(right,True);
	XtSetSensitive(up,True);
	/*
	Ripristina modalita' allarmi pendenti
	*/
	modoPageAll=MODO_ALLARMI;
	allPageFlag=False;
	OlSetOpeningAllarmPage(database_simulatore,0); /* Posso settare a 1 ? */
}

static Boolean	_teleperm_close_allPage( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	Boolean			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_close_allPage( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_xaing( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	/*
	Verify if the widget accepts the Aing procedure
	*/
	if(AcceptAing(w))
	   {
	   if(!ActivateAing(w,drawingArea,
	                   elenco_display[0].nome,
	                   &(ListaWidVar[0])))
	                            popup_errorDialog("Variable not defined",
	                                drawingArea);
	   }
	else
	   printf("WARNIG: widget doesn't fit Aing\n");
}

static int	_teleperm_xaing( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_xaing( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_refreshAllPageWidgets( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int i,tot_all_da_ric,tot_all_arc;
	        int kk;
	        Boolean zone_attive; /* almeno una zona attiva */
	        char appo[MAXLUNTOKEN],appo_descr[MAXLUNTOKEN],*str,*str1,*str2,descr_token[NUMTOKEN][MAXLUNTOKEN];
	        XmString stringa;
	        char *tipo_cai;
	        char gerarchiaNome[10* N_GERARCHIE];
	        DATI_ALLARMI_SHM app_allarmi;
	        int primo_set_zone_ko=0;
	        tot_all_da_ric=0;
	        tot_all_arc=0;
	        zone_attive=False;
	            for(kk=1;kk<NUMMAXZONE;kk++)
	                        {
	                        if(zone_status[kk]==1)
	                                {
	                                zone_attive=True; /* almeno una zona e' attiva */
	                                break;
	                                }
	                        }
	        /***************************************************************************
	        Parte riservata alla gestione di allarmi non validi
	        Gli allarmi non validi possono essere dovuti a diversi tipi di situazione:
	                1) selezione di una zona gia' selezionata da altro mmi
	                2) situazione di attesa temporanea
	                3) messaggio da Scada che non arrivera' piu'
	        ***************************************************************************/
	
	        if(!OlGetDataAllarmi(database_simulatore,&app_allarmi)) /* acquisisco all SHM */
	                {
	                printf("WARNING:Waiting for valid alarm data\n");
	                 for(kk=0;kk<MAXNUMALLVIS;kk++)
	                        {
	                        /*
	                        Se non vi sono dati validi, cancella visualizzazione allarmi
	                        */
	
	                        if((app_allarmi.descr[kk][0]==NULL) || !zone_attive )
	                                {
	                                stringa=XmStringCreateSimple("");
	                                set_something(all_name_label[kk],XmNlabelString,stringa);
	                                set_something(all_name_label[kk],XmNlabelString,stringa);
	                                set_something(all_descr_label[kk],XmNlabelString,stringa);
	                                XmStringFree(stringa);
	                                XtVaSetValues(all_name_label[kk],XmNbackground,def_background_butt,NULL);
	                                XtVaSetValues(all_descr_label[kk],XmNbackground,def_background_butt,NULL);
	                                XtVaSetValues(all_caiAll_form[kk],XmNbackground,def_background_butt,NULL);
	                                XtVaSetValues(all_data_label[kk],XmNbackground,def_background_butt,NULL);
	
	                                set_something(all_caiAll[kk],XlNstatus,(int)SPENTO);
	                                set_something(all_caiAll[kk],XlNvarGerarchia,"[-1][-1][-1][-1][-1][-1]");
	                                }
	                        /*
	                        setto a zero la vecchia SHM per innescare l' eventuale refresh
	                        */
	                        memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM));
	                        }
	                /* Chiamo refresh per spegnere i Cai */
	                XlRefreshWidget(all_caiAll,MAXNUMALLVIS);
	        /*
	        Se e' stato premuto un bottone, verifica che non sia gia' segnalato (zone_ko==-1) e
	        setta il colore di segnalazione zona ko.
	        */
	                if((last_zone_pressed!=-1) && (zone_ko==-1) && zone_attive)
	                        {
	                        /* Cambio colore a bottone con zona ko */
	
	                        XtVaSetValues(lista_header_button[last_zone_pressed],RES_CONVERT(XmNbackground,"yellow"
	),NULL);
	                        zone_ko=last_zone_pressed;
	                        primo_set_zone_ko=zone_ko;
	                        /* Premuta zona ko -> disabilito altri pulsanti */
	                        for(kk=1;kk<num_zone;kk++)
	                                {
	                                if(kk!=zone_ko && selectable_zone[kk])
	                                        XtVaSetValues(lista_header_button[kk],XmNsensitive,False,NULL);
	                                }
	
	                        }
	        /*
	        Quando il tasto relativo a zona selezionata gia' da altro utente,
	        viene disabilitato; riabilita gli altri tasti e ripristina il colore originario
	        Tutti i tasti (cioe' le zone) saranno disabilitati.
	        */
	                if((zone_ko!=-1) && (zone_status[zone_ko]==0) &&
	                         (!primo_set_zone_ko)  &&  (zone_ko==last_zone_pressed))
	                        {
	                        for(kk=1;kk<num_zone;kk++)
	                                {
	                                if(selectable_zone[kk])  /* zona con pag esistente a livello 0 */
	                                        {
	                                        XtVaSetValues(lista_header_button[kk],XmNsensitive,True,NULL);
	                                        XtVaSetValues(lista_header_button[kk],XmNbackground,def_background_butt,NULL);
	                                        XtVaSetValues(lista_header_button[kk],XmNarmColor,def_armColor_butt,NULL);
	                                        XtVaSetValues(lista_header_button[kk],XmNtopShadowColor,def_topShadowColor_butt,NULL);
	                                        XtVaSetValues(lista_header_button[kk],XmNbottomShadowColor,def_bottomShadowColor_butt,NULL);
	                                        zone_status[kk]=0;
	                                        }
	                                }
	                        zone_ko=-1;  /* situazione di nuovo ok */
	                        }
	                primo_set_zone_ko=0;
	                return(0); /* esci da routine */
	                }
	        /*
	        Ripristino colore di eventuale zona_ko .
	        Questa parte viene eseguita quando sono stati trovati in una refresh precedente
	        dei dati non validi (caso 2) :situazione pero' non dovuta alla selezione di una pagina allarme
	        gia' selezionata da altro utente
	        */
	        if(zone_ko!=-1)
	                {
	                if(zone_status[zone_ko])
	                        {
	                        XtVaSetValues(lista_header_button[zone_ko],XmNarmColor,def_background_butt,NULL);
	                        XtVaSetValues(lista_header_button[zone_ko],XmNbackground,def_armColor_butt,NULL);
	                        }
	                else
	                        {
	                        XtVaSetValues(lista_header_button[zone_ko],XmNbackground,def_background_butt,NULL);
	                        XtVaSetValues(lista_header_button[zone_ko],XmNarmColor,def_armColor_butt,NULL);
	
	                        }
	                 for(kk=1;kk<num_zone;kk++)
	                      {
	                      if((kk!=zone_ko) && (selectable_zone[kk]))
	                      XtVaSetValues(lista_header_button[kk],XmNsensitive,True,NULL);
	                      }
	                zone_ko=-1;
	                last_zone_pressed=-1;
	                if(modoPageAll== MODO_ARCHIVIO)
	                        {
	                        OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
	                        OlCommandAllarmi(database_simulatore,OL_MODO_ARCHIVIO);
	                        }
	                else
	                        OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
	                }
	/*****************************************************************
		Fine parte riservata a gestione dati non validi
	*****************************************************************/
	/*
	Innesco Refresh dei CaiAll
	*/
	XlRefreshWidget(all_caiAll,MAXNUMALLVIS);
	
	/*
	Verifico che ci sia stato qualche cambiamento nella situazione allarmi
	o che sia stato premuto o rilasciato qualche bottone per attivaz. zone
	*/
	if( (memcmp(&app_allarmi,&old_allarmi,sizeof(DATI_ALLARMI_SHM))!=0) || (memcmp(zone_status,zone_status_old,NUMMAXZONE*sizeof(int))) )
		{
		memcpy(&(old_allarmi),&app_allarmi,
	                sizeof(DATI_ALLARMI_SHM));
		memcpy(zone_status_old,zone_status,
	                sizeof(int)*NUMMAXZONE);
	/*
	Debug prova
	*/
	printf("allarmi_da=%d allarmi_a=%d\n",app_allarmi.allarmi_da,app_allarmi.allarmi_a);
	/*
	Se cerco di visualizzare allarmi in archivio che non ci sono
	esco da modo ARCHIVIO e visualizzo allarmi da ric se ve ne sono
	*//*	
		if(modoPageAll==MODO_ARCHIVIO)
			{
			if(app_allarmi.num_all_arc==0)
				modoPageAll=MODO_ALLARMI;
			}
	*/
	/*
	Se non esistono allarmi da riconoscere -> deseleziona il pulsante di acknowledge
	Se
	 il numero di allarmi e' < 16 deseleziona il tasto +
	*/
		if(modoPageAll==MODO_ALLARMI)
			{
	/* 
	Setto pulsante acknowledge per riconoscere prim gli allarmi piu' vecchi
	*/
			if((app_allarmi.num_all_da_ric >0) && (app_allarmi.allarmi_da == 1))
				XtSetSensitive(ackal,True);
			else 
				XtSetSensitive(ackal,False);
	/* 
	Setto pulsante minus  disabilitato se n allarmi =0 o se inizio pag
	*/
	
			if(app_allarmi.allarmi_da>1) /* non e' la pag + vecchia */
				XtSetSensitive(all_button_minus,True);
			else 
				XtSetSensitive(all_button_minus,False);
	/*
	Se non sono arrivato alla pagina piu' nuova button + e n attivi
	*/
				
			if(app_allarmi.num_all_da_ric<MAXNUMALLVIS)
				{
	                        XtSetSensitive(all_button_plus,False);
	                        XtSetSensitive(all_button_n,False);
				}
			else
				{
				if((app_allarmi.allarmi_a<app_allarmi.num_all_da_ric)) 
					{
					XtSetSensitive(all_button_plus,True);
					XtSetSensitive(all_button_n,True);
					}
				else 
					{
					XtSetSensitive(all_button_plus,False);
					XtSetSensitive(all_button_n,False);
					}
				}
			} 
		else if(modoPageAll==MODO_ARCHIVIO)
			{
			XtSetSensitive(ackal,False);
			if(app_allarmi.allarmi_da!=1)
	                        XtSetSensitive(all_button_minus,True);
	                else XtSetSensitive(all_button_minus,False);
	
			if(app_allarmi.num_all_arc<MAXNUMALLVIS)
				{
	                        XtSetSensitive(all_button_plus,False);
	                        XtSetSensitive(all_button_n,False);
				}
			else
				{
	               		 if((app_allarmi.allarmi_a<app_allarmi.num_all_arc))
					{
	                        	XtSetSensitive(all_button_plus,True);
					XtSetSensitive(all_button_n,True);
					}
	       		         else 
					{
					XtSetSensitive(all_button_plus,False);
					XtSetSensitive(all_button_n,False);
					}
				}
			}
		
	/*
	Parte riguardante il totale degli allarmi da riconoscere e archiviati 
	visualizzati in alto a dx nella pagina Allarmi.Il totale deve essere calcolato
	(in num_all_da_ric e num_all_arc vi sono solo gli allarmi delle zone selezionabili)
	*/
		for(kk=1;kk<NUMMAXZONE;kk++)
	                {
	                if(selectable_zone[kk])
	                   {
			   tot_all_da_ric+=app_allarmi.n_all_pen[kk];
			   tot_all_arc+=app_allarmi.n_all_arc[kk];
	                   }
	      		if(zone_status[kk]==1)
	             		zone_attive=True; /* almeno una zona e' attiva */
			}
	/*
	Setto i tasti per switch modo
	*/
		if(modoPageAll==MODO_ALLARMI)
	                {
			if(tot_all_arc>0 && zone_attive)
				XtSetSensitive(all_old_button,True);
			else XtSetSensitive(all_old_button,False);
			XtSetSensitive(all_new_button,False);
			}
		else if(modoPageAll==MODO_ARCHIVIO)
			{
			XtSetSensitive(all_old_button,False);
			XtSetSensitive(all_new_button,True);
			}
	        sprintf(appo,"%d",tot_all_da_ric);
	        stringa=XmStringCreateSimple(appo);
	        set_something(all_new,XmNlabelString,stringa);
	        XmStringFree(stringa);
	        sprintf(appo,"%d",tot_all_arc);
	        stringa=XmStringCreateSimple(appo);
	        set_something(all_old,XmNlabelString,stringa);
	        XmStringFree(stringa);
	/*
	Parte riguardante la visualizzazione del numero di allarmi archiviati e pendenti per ogni
	Zona
	*/
	
	        for(kk=1;kk<num_zone;kk++)
	                {
			if(selectable_zone[kk])
				{
	       		        sprintf(appo,"%d",app_allarmi.n_all_pen[kk]);
	                 	stringa=XmStringCreateSimple(appo);
	                	set_something(lista_header_label[kk*4+1],XmNlabelString,stringa);
	
	 	                sprintf(appo,"%d",app_allarmi.n_all_arc[kk]);
	                        XmStringFree(stringa);
	        	        stringa=XmStringCreateSimple(appo);
	                	set_something(lista_header_label[kk*4+3],XmNlabelString,stringa);
	                        XmStringFree(stringa);
				}
	                }
		/* Se nessuna zona e' attiva invia richiesta cancellazione pagAll */
		if (!zone_attive)
			{
			OlCommandAllarmi(database_simulatore,OL_CHIUDI_ALLARMI);
			}
	/*
	Parte riguardante la visualizzazione degli allarmi e delle date per ogni allarme
	*/ 
	        for(kk=0;kk<MAXNUMALLVIS;kk++)
	                {
			
			/* 
			Stringa con il NOME dell' allarme solo se allarme esiste
			(tecnica di Marcello) . Se la descriz. non esiste o
			non vi sono zone attive -> pagAllarmi e' vuota
			*/
			
			if((app_allarmi.descr[kk][0]==NULL) || !zone_attive )
				{
				stringa=XmStringCreateSimple("");
				set_something(all_name_label[kk],XmNlabelString,stringa);
				set_something(all_descr_label[kk],XmNlabelString,stringa);
				set_something(all_data_label[kk],XmNlabelString,stringa);	
	                        XmStringFree(stringa);
	
				set_something(all_caiAll[kk],XlNstatus,(int)SPENTO);	
				set_something(all_caiAll[kk],XlNvarGerarchia,"[-1][-1][-1][-1][-1][-1]");
				XtVaSetValues(all_name_label[kk],XmNbackground,def_background_butt,NULL);
	                        XtVaSetValues(all_descr_label[kk],XmNbackground,def_background_butt,NULL);
	                        XtVaSetValues(all_caiAll_form[kk],XmNbackground,def_background_butt,NULL);
	                        XtVaSetValues(all_data_label[kk],XmNbackground,def_background_butt,NULL);
				
				}
			else
				{
				/*
				Imposto la gerarchia per ogni caiAll
				Devo prima trasformare la sequenza di int in una stringa separata da []
				*/
				strcpy(gerarchiaValoreAll[kk],"");
				for(i=0;i<N_GERARCHIE;i++)
	                        	{
					strcpy(gerarchiaNome,"");
				/*
				Se livello !=-1 lo trasformo come unsigned per valori super. a 127
				Devo scrivere -1 con strcpy.
				*/
	                        	if(app_allarmi.hierarchy[kk][i]!=-1)
	                                                sprintf(gerarchiaNome,"\[%d\]",(unsigned char)(app_allarmi.hierarchy[kk][i]));
	                                        else
	                                                strcpy(gerarchiaNome,"[-1]");
					strcat(gerarchiaValoreAll[kk],gerarchiaNome);
	                        	}
				/*printf("gerarchiaValore=%s\n",gerarchiaValoreAll[kk]);*/
	
				set_something(all_caiAll[kk],XlNvarGerarchia,gerarchiaValoreAll[kk]);
	
				/*
				Analisi descrizione
				*/
	
				strcpy(appo_descr,"");
				
				strcpy(appo,app_allarmi.descr[kk]);

				str=strtok(appo,"_");
				if(str)
					strcpy(appo_descr,appo);
					

				stringa=XmStringCreateSimple(appo_descr);
				if(app_allarmi.emission[kk]==EMISSIONE)
					XtVaSetValues(all_name_label[kk],RES_CONVERT(XmNbackground,def_background_emission), NULL);
				else if(app_allarmi.emission[kk]==RIENTRO)
	                		XtVaSetValues(all_name_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
				set_something(all_name_label[kk],XmNlabelString,stringa);
	                        XmStringFree(stringa);
	
				strcpy(appo_descr,"");
			/*
			Verifico tipo di CaiAll
			*/
				tipo_cai=strchr(app_allarmi.descr[kk],'$');
				if(tipo_cai)
					set_something(all_caiAll[kk],XlNtipoCaiAll,(int)( *(tipo_cai+1) ));
			
			/*
			Filtro il KKS prima e dopo la DESCRIZIONE
	                Ho 3 campi separati da '|' :
	                      1) Descrizione principale
	                      2) Descrizione secondaria 1a parte
	                      3) Descrizione secondaria 2a parte
	
	Es:
	
	TAG| KKS  | |   Descrizione principale                | 1a sec| 2a secondaria
	
	  S_JR0400$A                       Turbo ALTERNATORE  |1o all | °k/cm. 
			
	*/
				str=strtok((char *)NULL,"$");	
				if(str)
				{
	                                /* In descr_token[0] es: JR0400 */
	
					strcpy(descr_token[0],str);
	 						/*printf("descr_token[0]=%s\n",descr_token[0]);*/
					str=strtok((char *)NULL,SEPARATORALARM);
	                                /* In descr_token[1] descriz. principale */
	                                /* Salto tipo allarme e caratteri inutili */
	                                str++;
	                                while(*str==' ')
	                                   str++;
					if(str)
						strcpy(descr_token[1],str);
					else strcpy(descr_token[1],"");
	 						/*printf("descr_token[1]=%s\n",descr_token[1]);*/
	
					str=strtok((char *)NULL,SEPARATORALARM);
	                                /* In descr_token[2] 1a descriz. secondaria  */
					if(str)
						{
						 strcpy(descr_token[2],str);
	 						/*printf("descr_token[2]=%s\n",descr_token[2]);*/
						}
					else strcpy(descr_token[2],"");
	
					/*printf("appo_descr prima di strtok=%s\n",appo_descr);*/
					str=strtok((char *)NULL,SEPARATORALARM);
	                                /* In descr_token[3] 2a descriz. secondaria  */
						if(str)
							{
							strcpy(descr_token[3],str);
	 						/*printf("descr_token[3]=%s\n",descr_token[3]);*/
	
							}
						else strcpy(descr_token[3],"");
					sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s %-*.*s",5,6,descr_token[0],41,41,descr_token[1],10,10,descr_token[2],10,10,descr_token[3]);
					/*printf("descrfinal=%s\n",appo_descr);*/
					stringa=XmStringCreateSimple(appo_descr);
					
					/*
					Setto lo stato del CaiAll associato
					*/
					if(tipo_cai)
						set_something(all_caiAll[kk],XlNstatus,(int)(app_allarmi.emission[kk]));
						
	        		        if(app_allarmi.emission[kk]==EMISSIONE)
						{
						XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);
						XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);
						}
					else if(app_allarmi.emission[kk]==RIENTRO)
						{
	                			XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
	                			XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
						}
					set_something(all_descr_label[kk],XmNlabelString,stringa);
	                        XmStringFree(stringa);
				}/* end if(str) per 2a parte descr */
			else
				{
				
			   	   strcpy(appo,app_allarmi.descr[kk]);
                               
                                   printf("\n\n\n***** DEBUG CARLO appor=%s\n",appo);
                                   if( strlen(appo) )
                                   {
                                      // skip della sigla
                                      str=appo; 
	                              str++;
	                              while(*str!=' ')
	                                 str++;

                                      // skip dei blank dopo la sigla
	                              while(*str==' ')
	                                 str++;
                                      
                                      printf("\n\n\n***** DEBUG CARLO STR=%s\n",str);

				      strcpy(appo_descr,str);
				      stringa=XmStringCreateSimple(appo_descr);
				      set_something(all_descr_label[kk],XmNlabelString,stringa);
	                              XmStringFree(stringa);
	        		        if(app_allarmi.emission[kk]==EMISSIONE)
						{
						XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);
						XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);
						}
					else if(app_allarmi.emission[kk]==RIENTRO)
						{
	                			XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
	                			XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
						}
                                   }
                                   else
                                   {
				      strcpy(appo_descr," ");
				      stringa=XmStringCreateSimple(appo_descr);
				      set_something(all_descr_label[kk],XmNlabelString,stringa);
	                              XmStringFree(stringa);
				   }
				}
	
	/*
	Parte per DATA
	*/
			
				strcpy(appo,app_allarmi.data[kk]);
				stringa=XmStringCreateSimple(appo);
	
				if(app_allarmi.emission[kk]==EMISSIONE)
						XtVaSetValues(all_data_label[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);
					else if(app_allarmi.emission[kk]==RIENTRO)
	                			XtVaSetValues(all_data_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);
				set_something(all_data_label[kk],XmNalignment,XmALIGNMENT_END);
				set_something(all_data_label[kk],XmNlabelString,stringa);
	                        XmStringFree(stringa);
				}  /* end else sulla descr e zone_attive*/
			} /*end for*/
	
		} /* end if(memcmp) */
}

static int	_teleperm_refreshAllPageWidgets( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_refreshAllPageWidgets( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_popupPage( UxThis, pEnv, nomePag, tipo )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*nomePag;
	int	tipo;
{
	/* questo metodo effettua il popup di una pagina 
	   sopra una pagina di tipo teleperm
	*/
	
	return(True);
}

static int	_teleperm_popupPage( UxThis, pEnv, nomePag, tipo )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*nomePag;
	int	tipo;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_popupPage( UxThis, pEnv, nomePag, tipo );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_ridisegna( UxThis, pEnv, ind_pag )
	swidget	UxThis;
	Environment *	pEnv;
	int	ind_pag;
{
	/* metodo che distrugge la drawing area e la ricrea
	   la pagina da ricreare e' individuata dal puntatore Pag 
	   che e' definito nel context e che viene svicciato
	   dalle funzioni di navigazione 
	*/
	
	XtCallbackProc exposeCB_drawingArea();
	char nome_pag[255];
	
	  
	/* variabili per risorse della drawing area
	*/
	int drawing_width,drawing_height;
	Pixel *drawing_background;
	Pixmap pix;
	
	
	/* per gestione sinottico
	*/
	int dim[4];
	int num_b;
	extern Boolean leggi_file_bck();
	
	
	 
	Pag = (AN_PAG *)&pagine[ind_pag]; 
	
	 
	/* nome del file delle risorse della pagina da caricare
	*/
	sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),Pag->nome);
	
	
	/* carico il db della pagina
	*/
	
	if( (PagDb = XrmGetFileDatabase(nome_pag)) == NULL )
	{
	   printf("Error. Cannot open page %s\n",nome_pag);
	   return(1);
	}
	
	/* prima di switchare il db delle risorse su quello della
	   pagina in apertura devo ditruggere il precedente.
	   Per fare cio' devo distruggere anche i cai posti nell'header
	   che fanno riferimento alle risorse del vecchio db.
	   Ricreo quindi i cai header dopo avere ripristinato il nuovo
	   db delle risorse
	*/
	
	/* rimuovo il timeout dei cai header prima della destroy del database
	   delle risorse
	   (se sono stati creati, vale a dire se scada_on)
	*/
	if( scada_on)
	{
	   XtRemoveTimeOut(timer_timerefreshCaiHeader);
	
	/* distruggo i cai nell'header
	*/
	   XtDestroyWidget(listaCaiHeader[0]);
	   XtDestroyWidget(listaCaiHeader[1]);
	   XtDestroyWidget(listaCaiHeader[2]);
	   XtDestroyWidget(listaCaiHeader[3]);
	   XtDestroyWidget(listaCaiHeader[4]);
	}
	
	/* distruggo il db delle risorse precedente
	*/
	XrmDestroyDatabase( (Display *)(XtDisplay(UxThis))->db);
	
	
	/*
	Combino database della applicazione con quello della pagina 
	*/
	XrmCombineFileDatabase("ApplDb.res",&PagDb,True);
	/* setto il display su PagDb
	*/
	XrmSetDatabase(XtDisplay(teleperm),PagDb);
	
	/* ricreo i caiHeader
	*/
	if( scada_on )
	   teleperm_createCaiHeader(UxThis,&UxEnv);
	
	/* mi serve solo per caricare il time_ref
	*/
	if(!GetResTopLevel(UxParent,&top_x,&top_y,&top_width,&top_height,&time_ref,
			&top_tipo,&top_descrizione))
		return(False);
	/*
	 Se nella pagina visualizzata era presente un pixmap di sfondo
	 lo libera
	*/
	if(drawing_pixmap)
		{
		XFreePixmap(XtDisplay(teleperm),drawing_pixmap);
		drawing_pixmap=0;
		}
	/* recupero le risorse della drawing area
	*/
	if(!GetResDrawing(UxParent,&drawing_width,&drawing_height,&drawing_background, &drawing_pixmap))
	   return(1);
	
	/* aggiornamento elenchi pagine per refresh
	*/
	if(allPageOnScreen!=SINCROCLOSEALLPAG)  /* Se pagina allarmi era attiva non distruggere drawing area inesistenti*/
		{
		DelElencoPagine(key_refresh, drawingArea);
		XSync(XtDisplay(drawingArea),False);
		XtRemoveTimeOut(timer_refresh);
	        XtFree(lista_wid);
		}
	/* inizializza la regione di ridisegno
	*/
	
	/*
	Devo discriminare fra pagina allarmi e altri tipi di pagina
	*/
	
	
	
	if( Pag->sfondo == NULL)
	   leggi_file_bck(UxParent,Pag->nome,"bkg",&(Pag->sfondo),dim);
	else  
	   AllocaColoriSfondo(UxParent,Pag->sfondo);
	
	
	region_sin=NULL;
	
	/* distuggo la drawing area
	*/
	if(allPageOnScreen!=SINCROCLOSEALLPAG)
		XtDestroyWidget( drawingArea);
	
	/* creo la nuova drawing area ignorando le dimensioni
	   presenti nel file delle risorse
	   ma gestendo gli attachment 
	   le dimensioni della drawing area sono quindi 
	   width = width del form genitore
	   height = heigth del form genitore - TopOffset  - BottomOffset
	   y = y del genitore + TopOffset
	    
	*/
	drawingArea = XtVaCreateManagedWidget( "drawingArea",
	                        xmDrawingAreaWidgetClass,
	                        formTop,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNtopOffset, 60,
	                        XmNbottomOffset, 35,
	                        XmNmarginHeight, 0,
	                        XmNmarginWidth, 0,
	                        NULL );
	/* 
	   setto il background della drawingArea
	*/
	if(drawing_pixmap)
	       set_something(drawingArea,XmNbackgroundPixmap,drawing_pixmap);
	else
		set_something(drawingArea,XmNbackground,drawing_background);
	/*
	   set callback per ridisegno background
	*/
/*	XtAddCallback( drawingArea, XmNexposeCallback,
	                (XtCallbackProc) exposeCB_drawingArea(),
	                (XtPointer) UxTelepermContext );
*/

/* 18 aprile 2016 corretto errore sul cambio pagina di mmi  */
        XtAddCallback( drawingArea, XmNexposeCallback,
                        (XtCallbackProc) exposeCB_drawingArea,
                        (XtPointer) UxTelepermContext );
/* 18  aprile 2016 fine modifica */
	
	
	UxPutContext( drawingArea, (char *) UxTelepermContext );
	
	/* creazione di tutti gli widget della drawing area
	*/
	if(!CreaPagina(drawingArea,&lista_wid, &num_wid))
	  return(1);
	
	/* aggiorno la title area
	*/
	if( teleperm_aggTitleArea(teleperm,&UxEnv) == False ) 
	   printf("Aggiornamento title Area non riuscito correttamente\n");
	
	
	if((key_refresh=InsElencoPagine(Pag->nome,lista_wid,num_wid,time_ref)) == -1)
	return(1);
	/*
	Aggiorno vecchio indice della pagina 
	*/
	
	timer_refresh = XtAppAddTimeOut (
	            XtWidgetToApplicationContext (teleperm),
	            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm );
	
	
	return(0);
}

static int	_teleperm_ridisegna( UxThis, pEnv, ind_pag )
	swidget	UxThis;
	Environment *	pEnv;
	int	ind_pag;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_ridisegna( UxThis, pEnv, ind_pag );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_gotopag( UxThis, pEnv, pcur, pnew, indice )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcur;
	int	*pnew;
	int	indice;
{
	OlTreeObject curr_oltree;
	int progr;
	
	/* recupero le informazioni sulla pagina corrente
	   nota: 
	   pos_pag_curr e' indice della pagina corrente
	   e' importante mantenerlo aggiornato per la gestione del previous 
	
	PROVO COMMENTANDO QUESTA PARTE a 
	   gestire il salto da pagine fuori gerarchia
	   if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcur,Pag->gerarchia) == False )
	   {
	      printf("Error retrieving hierarchy information for this page\n");
	      return;
	   }
	*/
	
	/* aggiorno l'indice della pagina pcur per
	   mantenere le funzionalita' di previous
	   Non aggiorno nulla se riapro una pagina allarmi
	*/
	
	  (*pcur) = pos_pag_new;
	
	/* setto la variabile globale (nel context)
	   pos_pag_new indice della pagina da visualizzare
	   e' importante mantenerlo aggiornato per la gestione del previous 
	*/
	   (*pnew) = indice;
}

static int	_teleperm_gotopag( UxThis, pEnv, pcur, pnew, indice )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcur;
	int	*pnew;
	int	indice;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_gotopag( UxThis, pEnv, pcur, pnew, indice );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_xplot( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	if(AcceptPlot(w))
	   {
	   if(!ActivatePlot(w,
	                   drawingArea,
	                    elenco_display[0].nome,
	                   &(ListaWidVar[0])))
	                            popup_errorDialog("Variable not defined",
	                                drawingArea);
	   }
	else
	    printf("WARNIG: widget doesn't fit Plot or Topology not loaded \n");
}

static int	_teleperm_xplot( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_xplot( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_application( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	printf("DEBUG: entrato nel metodo application operazione_attiva=%d\n",operazione_attiva);
	
	/*
	Verifica tipo di operazione 
	*/
	switch(operazione_attiva)
	   {
	   case OPERAZIONE_NOP:
	      {
	      break; 0; /* No operation set */
	      }
	   case OPERAZIONE_INFO:
	      {
	      teleperm_info(UxThis,pEnv,w);
	      break ;
	      }
	    case OPERAZIONE_XAING:
	      {
	      teleperm_xaing(UxThis,pEnv,w);
	      break ;
	      }
	    case OPERAZIONE_XPLOT:
	      {
	      teleperm_xplot(UxThis,pEnv,w);
	      break ;
	      }
	   }
	
	return operazione_attiva;
}

static int	_teleperm_application( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_application( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_previousPag( UxThis, pEnv, pcur, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcur;
	int	*pnew;
{
	/* questo metodo permette di rivisualizzare la penultima pagina visualizzata
	   Attivando due volte consecutove questo metodo devo ritornare sulla prima pagina 
	   cha ha attivato il metodo (circolare su due pagine)
	*/
	
	int prev;
	
	printf("METODO PREVIOUS\n");
	
	
	if( pos_pag_curr == pos_pag_new )
	   return(True);
	
	(*pcur) = pos_pag_new;
	(*pnew) = pos_pag_curr;
	
	return(True);
}

static int	_teleperm_previousPag( UxThis, pEnv, pcur, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcur;
	int	*pnew;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_previousPag( UxThis, pEnv, pcur, pnew );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_isOldAlarmPage( UxThis, pEnv, pag_candidata )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*pag_candidata;
{
	/*
	Metodo per determinare se su una pagina di tipo teleperm di nome "nome_pag", e' presente
	l' oggetto di libreria pagina Allarmi( XlAllarmi).
	Per ottenere questo, verifico se nel database risorse della pagina da esaminare
	e' presente nella risorsa elenco widget il nome del widget XlAllarmi
	*/
	XrmDatabase db;
	char nome_pag[FILENAME_MAX];
	char *tipo;
	XrmValue value;
	int ret;
	char *appo=NULL;
	/*
	Path full della pagina
	*/
	sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),pag_candidata);
	
	/*
	Carico DB risorse associato alla pagina
	*/
	if( (db = XrmGetFileDatabase(nome_pag)) == NULL )
	        {
	           fprintf(stderr,"Error. Cannot open page %s\n",nome_pag);
	           return(-1);
	        }
	/*
	Verifico se la risorsa esiste
	*/
	if(XrmGetResource(db,"elenco_wid0",(char *)NULL,&tipo,&value))
	   {
	             
	   if(!(appo=(char *)XtCalloc(1,(int)(value.size+1))))
	      {
	      fprintf(stderr,"ERROR: Impossible to allocate memory\n");
	      return -1;
	      }
	             
	      strncpy(appo,value.addr,(int)value.size);
	      if(strstr(appo,"Allarmi") )
	         ret=1;
	      else ret=0;
	             
	    }
	else
	    return -1;
	
	
	/*
	Destroy del db
	*/
	XrmDestroyDatabase(db);
	if(appo)
	   XtFree(appo);
	printf("DEBUG: pagina=%s ret=%d\n",pag_candidata,ret);
	
	
	return  ret;
}

static int	_teleperm_isOldAlarmPage( UxThis, pEnv, pag_candidata )
	swidget	UxThis;
	Environment *	pEnv;
	unsigned char	*pag_candidata;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_isOldAlarmPage( UxThis, pEnv, pag_candidata );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_moveright( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	int progr;
	OlTreeObject curr_oltree;
	
	
	/* recupero le informiazioni sulla pagina corrente
	*/
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )
	{
	   printf("Error retrieving hierarchy information for this page\n");
	   return(False);
	}
	
	
	/* recupero le informazioni sulla pagina a destra
	*/
	OlTreeGetRight(curr_oltree,pnew);
	
	
	return(True);
}

static int	_teleperm_moveright( UxThis, pEnv, pcurr, pnew )
	swidget	UxThis;
	Environment *	pEnv;
	int	*pcurr;
	int	*pnew;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_moveright( UxThis, pEnv, pcurr, pnew );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static void	Ux_chPage( UxThis, pEnv, w, nomePg, tipoApertura )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*nomePg;
	int	tipoApertura;
{
	int ind_pag;  /* indice della pagina nel vettore delle pagine */
	Widget newPag; /* top widget nuova pagina */
	
	if( !strlen(nomePg) ) 
	   return;
	
	/* apertura di una pagina
	*/
	if( (tipoApertura != CLOSE_PAGE) || (tipoApertura != CHANGE_PAGE) )
	{
	   /* la pagina non e' gia' aperta
	   */
	   if( !PaginaAperta(w,nomePg) )
	   {
	      if( !CanOpenPage(w) )
	         return;
	
	      printf("Abilitato ad aprire la pagina\n");
	
	      ind_pag=NumeroPagina(nomePg);
	    
	      printf("nella lista la pagina e' %s\n",pagine[ind_pag].nome);
	
	      /* verifico il tipo di pagina e la apro. 
	         Nota, la pagina corrente e la nuova pagina hanno lo stesso parent.
	      */
	      if( strcmp(pagine[ind_pag].tipo,"Sinottico") == 0)
	         newPag = create_topLevelShell1(nomePg,XtParent(UxThis),nome_display,pagine[ind_pag].sfondo);
	      if( strcmp(pagine[ind_pag].tipo,"Stazioni") == 0)
	         newPag = popup_topLevelShellStaz(nomePg,XtParent(UxThis),nome_display,pagine[ind_pag].sfondo);
	
	      if( newPag == NULL )
	      {
	         popup_errorDialog("Errore Creazione pagina",w);
	         return;
	      }
	   }
	   else
	      printf("La pagina sembra gia aperta\n");
	}
	else
	   printf("tipoApertura non e' diverso da ClosePage\n");
}

static void	_teleperm_chPage( UxThis, pEnv, w, nomePg, tipoApertura )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*nomePg;
	int	tipoApertura;
{
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	Ux_chPage( UxThis, pEnv, w, nomePg, tipoApertura );
	UxTelepermContext = UxSaveCtx;
}

static int	Ux_aggTitleArea( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/* set title area
	*/
	int npag,*lista_ind;
	
	set_titleLabel(Pag->descrizione);
	
	/* set menu jerarqia horizontal
	*/
	teleperm_orizHier(teleperm,&UxEnv,&lista_ind,&npag);
	if(  npag> 0 )
	   {
	   set_something(orizHierButton,XmNsensitive,True); 
	   
	   }
	else
	   set_something(orizHierButton,XmNsensitive,False); 
	
	if(lista_ind)
	   XtFree(lista_ind);
	
	/* set menu jerarqia vertical
	*/
	teleperm_vertHier(teleperm,&UxEnv,&lista_ind,&npag);
	if(  npag> 0 )
	   { 
	   set_something(vertHierButton,XmNsensitive,True);   
	   
	   }
	else
	   set_something(vertHierButton,XmNsensitive,False);   
	if(lista_ind)
	   XtFree(lista_ind);
	
	return(True);
}

static int	_teleperm_aggTitleArea( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_aggTitleArea( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_aggListChild( UxThis, pEnv, childW )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	childW;
{
	/****************************************************
	 * aggiorno la lista delle pagine figlie durante
	 * la chiusura di una di esse
	 ***************************************************/
	int i;
	
	for( i=0;i<numChildPagList;i++)
	   if( childW == ChildPagList[i] )
	   {
	      ChildPagList[i] = NULL;
	      
	      /* non decremento il contatore delle pagine 
	         perche' mii basero' sul NULL in ChildPagList
	         per descriminare se la OW e' aperta o chiusa
	      */
	   }
	
	return(True);
}

static int	_teleperm_aggListChild( UxThis, pEnv, childW )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	childW;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_aggListChild( UxThis, pEnv, childW );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_dispData( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int dd,mm,yy;
	char data_oggi[20];
	XmString xstr;
	
        /* introdotto l'uso di data2 anziche data
        */
	if( data2(&dd,&mm,&yy) == 1)
	{
              
	   sprintf(data_oggi,"%d-%d-%2.2d",dd,mm,yy);
	
	   xstr = XmStringCreateSimple(data_oggi);
	
	   set_something(Data,XmNlabelString,xstr);
	   
	   XmStringFree(xstr); 
	
	   return(True);
	}
	else
	   return(False);
}

static int	_teleperm_dispData( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_dispData( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static void	Ux_closePag( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	extern Boolean OW_close();
	int i;
	char *envvar;
	char comando[FILENAME_MAX*2];
	char appo[100];
	int localScreen=0;
	
	        /* elimino le OW aperte
	        */
	        teleperm_closeOW(teleperm,&UxEnv);
	        /*
	        Se ho aperto la pagina allarmi sullo Screen da chiudere -> la chiudo
	        */
	        localScreen=XScreenNumberOfScreen(XtScreen(UxThis));
	
	        if( localScreen == allPageOnScreen )
	                {
	                teleperm_close_allPage(elenco_display[0].scr[allPageOnScreen].wteleperm,&UxEnv);
	                allPageOnScreen=SINCROCLOSEALLPAG;
	                }
	        /* libero la pagina teleperm
	        */
	        /*
	        elenco_display[0].scr[screen_selezionato].wteleperm = NULL;
	        */
	        /* reset dell'indice di pagina
	           Tengo conto dell'effettico screen sul quale e' visualizzata
	        */
	
	        /* chiudendo la pagina devo aggiornare
	            la variabile screen_selezionato sull'altro screen
	        */
	        if( screen_selezionato == 1)
	           screen_selezionato = 0;
	        else
	           screen_selezionato = 1;
	
	                XtRemoveTimeOut(timer_timerefresh);
	        if((allPageOnScreen!=SINCROCLOSEALLPAG )|| (allPageOnScreen==-1))
	                {
	
	                DelElencoPagine(key_refresh, drawingArea);
	
	                XSync(XtDisplay(w),False);
	                XtRemoveTimeOut(timer_refresh);
	                XtFree(lista_wid);
	                }
	        else if(allPageOnScreen==SINCROCLOSEALLPAG)
	           allPageOnScreen=-1;
	
	        /*
	        Rimuovi timeout dei Cai sul 'costolone' pag teleperm solo se lo scada e' agganciato
	        */
	        if(scada_on)
	                XtRemoveTimeOut(timer_timerefreshCaiHeader);
	
	        if(pullDownActive)
	                {
	                if(scada_on)
	                        XtRemoveTimeOut(timer_timerefreshCai);
	                UxDestroyInterface(*pullDownActive);
	                if(scada_on)
	                   {
	                    XtFree(listaCaiVr);
	                    XtFree(listaCaiFormVr);
	                    XtFree(listaPushButton);
	                   }
	                pullDownActive=NULL;
	                }
	        elenco_display[0].scr[DefaultScreen(XtDisplay(teleperm))].wteleperm = NULL;
	
	        prima_apertura_all=True;
	
	        if(drawing_pixmap)
	                {
	                XFreePixmap(XtDisplay(teleperm),drawing_pixmap);
	                drawing_pixmap=0;
	                }
	
	        UxDestroyInterface( teleperm );
	
	/*
	Eliminazione eventuali file tmp per info da teleperm
	*/
	if(InfoUsed)
	   {  
	   strcpy(comando,"rm ");
	   if((envvar=(char *) getenv("TMPDIR"))==NULL)
	      {
	      strcat(comando,"/tmp");
	      }
	   else
	      strcat(comando,envvar);
	
	   strcat(comando,TMPINFOFILE);
	   sprintf(appo,"%d",getpid());
	   strcat(comando,appo);
	   strcat(comando,"_");
	   strcat(comando,"*");
	   system(comando);
	   
	} /* end if InfoUsed */
	/*
	   system(comando);
	*/
}

static void	_teleperm_closePag( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	Ux_closePag( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;
}

static int	Ux_create_allPage( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/*
	Funzione per la creazione della pagina allarmi
	*/
	Position xShell,yShell;
	int i,j;
	int last_zone;   /* indice ultima zona attivabile */
	Pixel background_color,arm_color,top_shadow,bottom_shadow; /* Pixel per bottoni header */
	char *nome_header,*nomeWidget;
	Pixel background_parent;  /* background del parent dei Cai */
	Boolean readButtColor=False;
	char *tipo;
	XrmValue value;
	/* 
	In base al num_telepag possono essere visualizzati allarmi fino a 30 
	zone di impianto.
	Ne vengono influenzati la altezza della header_form , e i bordi ed i margini
	dei rowColumn contenenti  le informazioni sugli allarmi.La dimensione 
	delle form contenute nell' header e' fissa.
	*/
	
	int height_header_form,dim_entryBorder,dim_marginHeight;
	
	/* 
	Acquisisco valore risorsa per background per emissioni e rientri label
	*/
	XrmGetResource(UxDisplay->db,"teleperm.emission",(char*)NULL,&tipo,&value);
	strncpy(def_background_emission,value.addr,(int)value.size);
	/*printf("\n\n def_background_emission=%s\n\n",def_background_emission);*/
	
	XrmGetResource(UxDisplay->db,"teleperm.ack",(char*)NULL,&tipo,&value);
	strncpy(def_background_acknowledge,value.addr,(int)value.size);
	/*printf("\n\n def_background_acknowledge=%s\n\n",def_background_acknowledge);*/
	
	/*
	Controllo che pagina allarmi vecchi tipo non sia gia' stata aperta
	Se non e' stata aperta nessuna pagAll set a 1 il flag di sync.
	*/
	if(!OlCanOpenAllarmPage(database_simulatore))
	   return -1;
	else
	   if(!OlSetOpeningAllarmPage(database_simulatore,1)) /* Posso settare a 1 ? */
	      return -1;
	   
	/* Setto a true flag per apertura pagina allarmi cosicche' non possa aprirla 
	un altro screen
	*/
	if(!allPageFlag)
	      allPageFlag=True;
	else
	      return -1;
	/*
	Setto le caratteristiche della interfaccia: No righe per dimensioni di
	ogni lista_header_form
	*/
	if(num_zone==HEADERTRERIGHE)
	      {
	      height_header_form=3*HEIGHTSMALLFORMHEADER+7;
	      dim_entryBorder=4;
	      dim_marginHeight=3;
	      }
	else if(num_zone==HEADERQUATTRORIGHE)
	      {
	      height_header_form=4*HEIGHTSMALLFORMHEADER+7;
	      dim_entryBorder=2;
	      dim_marginHeight=1;
	      }
	else if(num_zone==HEADERCINQUERIGHE)
	      {
	      height_header_form=5*HEIGHTSMALLFORMHEADER+10;
	      dim_entryBorder=0;
	      dim_marginHeight=0;
	      }
	else
	      {
	      printf("ERROR: num_telepag=%d Zone number not correct\n");
	      return(-1);
	      }
	
	/*
	Setto il database delle risorse
	*/
	XrmSetDatabase(XtDisplay(UxThis),PagDb); 
	/* Se un pullDown e' active eliminalo */
	 if(pullDownActive)
	                {
	                XtRemoveTimeOut(timer_timerefreshCai);
	                UxDestroyInterface(*pullDownActive);
	                XtFree(listaCaiVr);
	                XtFree(listaCaiFormVr);
	                XtFree(listaPushButton);
	                pullDownActive=NULL;
	                }
	
	/*
	Uguaglio gli indici della vecchia e della nuova pagina  
	per funzionamaento pushButton Previous
	*/
	
	
	
	/*
	Deseleziono i bottoni per navigazione
	*/
	XtSetSensitive(left,False);
	XtSetSensitive(right,False);
	XtSetSensitive(up,False);
	/* acquisisco la posizione della main di teleperm */
	get_something(	teleperm,XmNx,&xShell);		
	get_something(	teleperm,XmNy,&yShell);	
	
	
	/*****************************************************
	Parte riservata ad allocazione per oggetti multipli
	*******************************************************/
	
	if ( (lista_header_form = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)
	{
	   printf("Allarm Page: Error in malloc: lista_header_form\n");
	   return(-1);
	}
	if ( (lista_header_button = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)
	{
	   printf("Allarm Page: Error in malloc: lista_header_button\n");
	   return(-1);
	}
	if ( (lista_header_rowColumn = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)
	{
	   printf("Allarm Page: Error in malloc: lista_header_rowColumn\n");
	   return(-1);
	}
	if((nome_header=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)
		{ 
		printf("nome_headerFont Error in malloc: createAllPage\n");
	        return(-1);
		}
	
	if ( (lista_header_label = (Widget *) XtCalloc(1, num_zone * 4* sizeof(Widget)) ) == NULL)
		{
		printf("nome_headerFont Error in malloc: lista_header_label\n");
	        return(-1);
		}
	/*
	Allocazioni per label per allarmi
	*/
	if ( (all_caiAll_form = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)
		{
		printf("creaAllPage Error in malloc: all_caiAll_form\n");
	        return(-1);
		}
	if ( (all_caiAll = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)
		{
		printf("creaAllPage Error in malloc: all_caiAll\n");
	        return(-1);
		}
	if ( (all_name_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)
		{
		printf("creaAllPage Error in malloc: all_name_label\n");
	        return(-1);
		}
	if ( (all_descr_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)
		{
		printf("creaAllPage Error in malloc: all_descr_label\n");
	        return(-1);
		}
	if ( (all_data_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)
		{
		printf("creaAllPage Error in malloc: all_data_label\n");
	        return(-1);
		}
	
	/*******************************************************
	Fine parte riservata ad allocazione per oggetti multipli
	********************************************************/
	
	/*
	Inizializzazioni
	*/
	strcpy(nome_header,"header");
	for(i=0;i<MAXNUMALLVIS;i++)
		strcpy(gerarchiaValoreAll[i],"");
	/*
	Inizio costruzione oggetti
	Distruggo la pagina precedente
	*/
	if(allPageOnScreen!=SINCROCLOSEALLPAG)
		{
		DelElencoPagine(key_refresh, drawingArea);
		XSync(XtDisplay(drawingArea),False);
		XtRemoveTimeOut(timer_refresh);
		XtDestroyWidget( drawingArea);
	        XtFree(lista_wid);
		}
	/*Eliminazione della pagina precedente */
	all_form_topLevelShell=XtVaCreateManagedWidget( "all_form_topLevelShell",
	                        xmFormWidgetClass,
	                        formTop,
	                        XmNwidth, 200,
	                        XmNheight, 960,
	                        XmNresizePolicy, XmRESIZE_NONE,
				XmNbottomAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNtopOffset, 30,
	                        XmNbottomOffset, 35,
	                        XmNunitType, XmPIXELS,
				/*RES_CONVERT( XmNbackground, "#000000" ),*/
	                        NULL );
	        UxPutContext( all_form_topLevelShell, (char *) UxTelepermContext );
	
	all_form_title = XtVaCreateManagedWidget( "all_form_title",
	                        xmFormWidgetClass,
	                        all_form_topLevelShell,
	                        XmNwidth, 1275,
	                        XmNheight, 40,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 0,
	                        XmNy, 0,
	                       /* RES_CONVERT( XmNbackground, "cyan" ),*/
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        NULL );
	        UxPutContext( all_form_title, (char *) UxTelepermContext );
	
	all_new_button = XtVaCreateManagedWidget( "all_new_button",
	                        xmPushButtonWidgetClass,
	                        all_form_title,
	                        XmNx, 10,
	                        XmNy, 10,
				XmNleftOffset, 3,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 3,
	                        NULL );
	        UxPutContext( all_new_button, (char *) UxTelepermContext  );
	
		XtAddCallback(all_new_button, XmNactivateCallback,
	                    (XtCallbackProc)command_alarm,OL_MODO_ALLARMI);
	
	        /* Creation of label all new */
	all_new = XtVaCreateManagedWidget( "all_new",
	                        xmLabelWidgetClass,
	                        all_form_title,
	                        XmNx, 90,
	                        XmNy, 10,
				XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 5,
				XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
				XmNbottomWidget, all_new_button,
				XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget, all_new_button,
				XmNleftWidget, all_new_button,
	                        NULL );
	        UxPutContext( all_new, (char *) UxTelepermContext  );
	
	
	        /* Creation of label12 */
	all_old_button = XtVaCreateManagedWidget( "all_old_button",
	                        xmPushButtonWidgetClass,
	                        all_form_title,
	                        XmNx, 170,
	                        XmNy, 10,
				XmNleftWidget, all_new,
				XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 10,
				XmNbottomAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 3,
	                        NULL );
	 UxPutContext( all_old_button, (char *) UxTelepermContext  );
	
		XtAddCallback(all_old_button, XmNactivateCallback,
	                    (XtCallbackProc)command_alarm,OL_MODO_ARCHIVIO);
	all_old = XtVaCreateManagedWidget( "all_old",
	                        xmLabelWidgetClass,
	                        all_form_title,
	                        XmNx, 240,
	                        XmNy, 10,
				XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
				XmNbottomWidget, all_old_button,
				XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
				XmNtopWidget, all_old_button,
				XmNleftWidget, all_old_button,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 5,
	                        NULL );
	        UxPutContext( all_old, (char *) UxTelepermContext );
	
	
	        /* Creation of label  title*/
	all_title_label = XtVaCreateManagedWidget( "all_title_label",
	                        xmLabelWidgetClass,
	                        all_form_title,
	                        XmNx, 460,
	                        XmNy, 0,
	                        XmNwidth, 300,
	                        NULL );
	        UxPutContext( all_old, (char *) UxTelepermContext );
	
	all_header_mainForm = XtVaCreateManagedWidget( "all_header_mainForm",
	                        xmFormWidgetClass,
	                        all_form_topLevelShell,
	                        XmNwidth, 1258,
	                        XmNheight,  height_header_form,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 0,
				XmNtopAttachment,XmATTACH_WIDGET,
				XmNtopWidget,all_form_title,
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        /*RES_CONVERT( XmNbackground, "gray" ),*/
	                        NULL );
	        UxPutContext( all_header_mainForm, (char *) UxTelepermContext );
	
	header_rowColumn = XtVaCreateManagedWidget( "header_rowColumn",
	                        xmRowColumnWidgetClass,
	                        all_header_mainForm,
	                        XmNwidth, 1654,
	                        XmNheight, 162,
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNnumColumns, 3,
	                        XmNpacking, XmPACK_TIGHT,
	                        XmNorientation, XmHORIZONTAL,
	                        XmNadjustLast, FALSE,
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
				XmNbottomAttachment, XmATTACH_FORM,
	                        XmNtopAttachment, XmATTACH_FORM,
				XmNresizeHeight, TRUE,
	                        XmNresizeWidth, FALSE,
				XmNisAligned, FALSE,
	                        XmNresizable, FALSE,
				XmNmarginHeight, 1,
	                        XmNmarginWidth, 1,
	                        NULL );
	        UxPutContext( header_rowColumn, (char *) UxTelepermContext );
	/*
	Costruisco num_zone pulsanti di selezione delle zone:
	la zona 0 e' utilizzata per gli allarmi di diagnostica (parto con i=1)
	*/
	
	for(i=1;i<num_zone;i++)
		{
		if((nomeWidget=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)
	   		{
	      		printf("create_allPage Error in malloc: nomeWidget\n");
	      		return(-1);;
	   		}
		sprintf(nomeWidget,"%d",i);
		strcat(nomeWidget,nome_header);	/* inserisco "header" nel nome */
		strcat(nomeWidget,"_form");
	
	lista_header_form[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmFormWidgetClass,
	                        header_rowColumn,
	                        XmNwidth, 207,
	                        XmNheight, 55,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 3,
	                        XmNy, 3,
	                        NULL );
	        UxPutContext( lista_header_form[i], (char *) UxTelepermContext );	
	/*
	Creo gli altri oggetti solo se la zona e' abilitabile
	Le zone (function Area) abilitabili sono state  settate nella creazione 
	della pagina teleperm
	*/
		if(selectable_zone[i])
		  {
	/*
	Inserisco il bottone per ogni Zona
	*/
		  strcpy(nomeWidget,"");
		  sprintf(nomeWidget,"%d",i);
	          strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */
		  strcat(nomeWidget,"_button");
	
	          lista_header_button[i]=XtVaCreateManagedWidget( nomeWidget,
	                        xmPushButtonWidgetClass,
	                        lista_header_form[i],
	                        XmNx, 0,
	                        XmNy, 30,
	                        XmNwidth, 207,
	                        XmNheight, 30,
				RES_CONVERT( XmNlabelString,pagine[selectable_zone[i]].descrizione),
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        NULL );
	           UxPutContext( lista_header_button[i], (char *) UxTelepermContext );
	/*
	Acquisisco valori variabili back e arm per gestione piu' utenti con la stessa
	pagina allarmi-> vedi codice inizion metodo refresh pagina allarmi
	readButtColor e' usata per non acquisire colori bottoni + di una volta.
	*/
	      if(!readButtColor)
	              {
	              get_something(lista_header_button[i],XmNbackground,&def_background_butt);
	              get_something(lista_header_button[i],XmNarmColor,&def_armColor_butt);
	              get_something(lista_header_button[i],XmNtopShadowColor,&def_topShadowColor_butt);
	              get_something(lista_header_button[i],XmNbottomShadowColor,&def_bottomShadowColor_butt);
	              readButtColor=True;
	              }
	/*
	Setto subito colori dei bottoni in base alle zone attivate
	N.B.
	All' iesimo bottone e' associata la zona i+1 poiche' nella zona 0
	vi sono gli allarmi di diagnostica generale.
	*/
		  if(zone_status[i])
		  	{
			/* Acquisisco valori dei colori del bottone */
	
			XtVaGetValues(lista_header_button[i],XmNarmColor,&arm_color,NULL);
			XtVaGetValues(lista_header_button[i],XmNbackground,&background_color,NULL);
			XtVaGetValues(lista_header_button[i],XmNtopShadowColor,&top_shadow,NULL);
			XtVaGetValues(lista_header_button[i],XmNbottomShadowColor,&bottom_shadow,NULL);
	
	/* Setto nuovi valori del bottone (scambio bordini e sfondi)*/
	
			XtVaSetValues(lista_header_button[i],XmNbackground,arm_color,NULL);
			XtVaSetValues(lista_header_button[i],XmNarmColor,background_color,NULL);
			XtVaSetValues(lista_header_button[i],XmNtopShadowColor,bottom_shadow,NULL);
			XtVaSetValues(lista_header_button[i],XmNbottomShadowColor,top_shadow,NULL);
			}
			
	/*
	Acquisisco valori dei colori dei bottoni
	*/
	    	  XtAddCallback(lista_header_button[i], XmNactivateCallback,
	                    (XtCallbackProc)select_zone,i);
	
	/* rowColumn per indicatori per ogni zona */
	          strcpy(nomeWidget,"");
	          sprintf(nomeWidget,"%d",i);
	          strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */
	          strcat(nomeWidget,"_rowColumn");
	
	          lista_header_rowColumn[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmRowColumnWidgetClass,
	                        lista_header_form[i],
	                        XmNwidth, 210,
	                        XmNheight, 30,
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNbottomAttachment, XmATTACH_WIDGET,
	                        XmNbottomWidget, lista_header_button[i],
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNnumColumns, 4,
	                        XmNpacking, XmPACK_COLUMN,
	                        XmNadjustLast, FALSE,
	                        XmNtopAttachment, XmATTACH_FORM,
				RES_CONVERT( XmNbackground, "ivory"),
				XmNisAligned, FALSE,
	                        NULL );
	           UxPutContext( lista_header_rowColumn[i], (char *) UxTelepermContext );
	
		  	  strcpy(nomeWidget,"");
	        	  sprintf(nomeWidget,"%d",i);
	        	  strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */
	        	  strcat(nomeWidget,"_labelNew");
	
	           lista_header_label[i*4]=XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        lista_header_rowColumn[i],
	                        XmNx, 3,
	                        XmNy, 3,
	                        XmNwidth, 49,
	                        XmNrecomputeSize, FALSE,
	                        XmNheight, 20,
	                        NULL );
	
	        	UxPutContext( lista_header_label[i*4], (char *) UxTelepermContext );
	
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */
	        	strcat(nomeWidget,"_labelNewDisplay");
	
		        lista_header_label[i*4+1]=XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        lista_header_rowColumn[i],
				XmNx, 13,
	                        XmNy, 13,
	                        XmNwidth, 49,
	                        XmNrecomputeSize, FALSE,
	                        XmNheight, 20,
				XmNalignment, XmALIGNMENT_END,
	                        RES_CONVERT( XmNlabelString, "-" ),
	                        NULL );
	
	                UxPutContext( lista_header_label[i*4+1], (char *) UxTelepermContext);
			
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */
	        	strcat(nomeWidget,"_labelOld");
	lista_header_label[i*4+2]= XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        lista_header_rowColumn[i],
	                        XmNx, 85,
	                        XmNy, 13,
	                        XmNwidth, 49,
	                        XmNrecomputeSize, FALSE,
	                        XmNheight, 20,
	                        NULL );
	        UxPutContext( lista_header_label[i*4+2], (char *) UxTelepermContext );
	
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,nome_header); /*inserisco "header" nel nome */
	        	strcat(nomeWidget,"_labelOldDisplay");
	
		        lista_header_label[i*4+3]=XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        lista_header_rowColumn[i],
				XmNx, 157,
	                        XmNy, 13,
	                        XmNwidth, 49,
	                        XmNrecomputeSize, FALSE,
	                        XmNheight, 20,
				XmNalignment, XmALIGNMENT_END,
	                        RES_CONVERT( XmNlabelString, "-" ),
	                        NULL );
	
	                UxPutContext( lista_header_label[i*4+3], (char *) UxTelepermContext);
			
	          last_zone=i; /* ultima zona selezionabile */
		  } /* end if selectable_zone */
		else
		  {
		  lista_header_button[i]=NULL;
		  lista_header_rowColumn[i]=NULL;
		  lista_header_label[i*4]=NULL;
		  lista_header_label[i*4+1]=NULL;
		  lista_header_label[i*4+2]=NULL;
		  lista_header_label[i*4+3]=NULL;
		  }
	
		XtFree(nomeWidget);	
	
		} /* end for X header */                                                              
	/*
	Istanzio form che conterra' i rowColumn per le label
	*/                                                                   
	
	        all_formAll = XtVaCreateManagedWidget( "all_formAll",
	                        xmFormWidgetClass,
	                        all_form_topLevelShell,
	                        XmNwidth, 1270,
	                        XmNheight, 1050,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 0,
	                        /*RES_CONVERT( XmNbackground, "midnight blue" ),*/
	                        XmNrightAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNtopAttachment, XmATTACH_WIDGET,
	                        XmNtopWidget, all_header_mainForm ,
				XmNtopOffset, 5,
	                        NULL );
	
	        UxPutContext( all_formAll, (char *) UxTelepermContext );
	/*
	Istanzio le rowColumn che conterranno le label per gli allarmi
	*/
	
	all_rowColumn_caiAll=XtVaCreateManagedWidget( "all_rowColumn_CaiAll",
	                        xmRowColumnWidgetClass,
	                        all_formAll,
	                        XmNwidth, 35,
	                        XmNheight, 692,
	                        XmNx, 1,
	                        XmNy, 0,
	                        XmNresizeWidth, TRUE,
	                        XmNresizeHeight, TRUE,
	                        XmNentryBorder, dim_entryBorder,
	                        XmNmarginHeight, dim_marginHeight,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        /*RES_CONVERT( XmNbackground, "white"),*/
	                        NULL );
	        UxPutContext( all_rowColumn_caiAll, (char *) UxTelepermContext );
	
	all_rowColumn_nameAll=XtVaCreateManagedWidget( "all_rowColumn_nameAll",
	                        xmRowColumnWidgetClass,
	                        all_formAll,
	                        /*XmNwidth, 347,*/
	                        /*XmNheight, 692,*/
	                        XmNx, 40,
	                        XmNy, 0,
	                        XmNresizeWidth, TRUE,
	                        XmNresizeHeight, TRUE,
	                        XmNentryBorder, dim_entryBorder,
	                        XmNmarginHeight, dim_marginHeight,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftWidget, all_rowColumn_caiAll,
				/*RES_CONVERT( XmNbackground, "aquamarine"),*/
	                        NULL );
	        UxPutContext( all_rowColumn_nameAll, (char *) UxTelepermContext );
	
	all_rowColumn_descrAll = XtVaCreateManagedWidget( "all_rowColumn_descrAll",
	                        xmRowColumnWidgetClass,
	                        all_formAll,
	                        /*XmNwidth, 614,*/
	                        XmNx, 374,
	                        XmNy, 0,
	                        XmNresizeWidth, TRUE,
	                        XmNresizeHeight, TRUE,
	                        XmNentryBorder, dim_entryBorder,
	                        XmNmarginHeight, dim_marginHeight,
	                        XmNtopOffset, 0,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 0,
	                        XmNleftWidget, all_rowColumn_nameAll,
	                        XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
	                        XmNtopWidget, all_rowColumn_nameAll,
	                        XmNnumColumns, 1,
	                        XmNpacking, XmPACK_TIGHT,
				/*RES_CONVERT( XmNbackground, "forest green"),*/
	                        NULL );
	        UxPutContext( all_rowColumn_descrAll, (char *) UxTelepermContext );
	
	all_rowColumn_dataAll = XtVaCreateManagedWidget( "all_rowColumn_data",
	                        xmRowColumnWidgetClass,
	                        all_formAll,
	                        /*XmNwidth, 213,*/
	                        /*XmNheight, 695,*/
	                        XmNx, 276,
	                        XmNy, 11,
	                        XmNresizeWidth, TRUE,
	                        XmNresizeHeight, TRUE,
	                        XmNentryBorder, dim_entryBorder,
	                        XmNmarginHeight, dim_marginHeight,
	                        XmNnumColumns, 1,
	                        XmNpacking, XmPACK_TIGHT,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftWidget, all_rowColumn_descrAll,
	                        XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
	                        XmNtopOffset, 0,
	                        XmNtopWidget, all_rowColumn_descrAll,
				/*RES_CONVERT( XmNbackground, "cornsilk"),*/
	                        NULL );
	        UxPutContext( all_rowColumn_dataAll, (char *) UxTelepermContext );
	
	for(i=0;i<MAXNUMALLVIS;i++)
		{
		if((nomeWidget=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)
	   		{
	      		printf("create_allPage Error in malloc: nomeWidget\n");
	      		return(-1);;
	   		}
	/*
	Creazione delle form contenenti i caiAll
	*/
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,"_formCaiAll");
	all_caiAll_form[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmFormWidgetClass,
	                        all_rowColumn_caiAll,
	                        XmNx, 3,
	                        XmNy, 4,
				XmNresizePolicy, XmRESIZE_NONE,
	                        XmNheight, 32,
	                        XmNwidth, 32,
	                        NULL );
	        UxPutContext( all_caiAll_form[i], (char *) UxTelepermContext );
	
	/*
	Creazione dei caiAll
	Devo acquisire il background del parent per disegnarlo in transparent quando
	disattivato
	*/
			get_something(all_caiAll_form[i],XmNbackground,&background_parent);
	
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,"_CaiAll");
	
	all_caiAll[i]= XtVaCreateManagedWidget( nomeWidget,
				xlCaiAllWidgetClass,
	                        all_caiAll_form[i],
	                        XmNx, 3,
	                        XmNy, 4,
	                        XmNheight, 25,
	                        XmNwidth, 25,
	/*			XmNtopOffset,TOPOFFSET,
				XmNleftOffset,LEFTOFFSET,*/
				XlNcolorBord,background_parent,
				XmNtopAttachment,XmATTACH_FORM,
				XmNleftAttachment,XmATTACH_FORM,
				XlNtipoCai, CAI_A,
#ifndef DESIGN_TIME
	                        XlNconfig, False,
#endif
				XlNstatus, SPENTO,
	                        NULL );
	        UxPutContext( all_caiAll[i], (char *) UxTelepermContext );
	
	
			strcpy(nomeWidget,"");
	        	sprintf(nomeWidget,"%d",i);
	        	strcat(nomeWidget,"_labelNameAlarm");
	all_name_label[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        all_rowColumn_nameAll,
	                        XmNx, 3,
	                        XmNy, 218,
	                        XmNheight, 32,
	                        XmNrecomputeSize, FALSE,
	                        /*XmNwidth, 250,*/
				RES_CONVERT(XmNlabelString," "),
	                        NULL );
	
	        UxPutContext( all_name_label[i], (char *) UxTelepermContext );
	/*
	Istanzio label per descrizione allarmi
	*/
		        strcpy(nomeWidget,"");
	                sprintf(nomeWidget,"%d",i);
	                strcat(nomeWidget,"_labelDescrAlarm");
	
	all_descr_label[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        all_rowColumn_descrAll,
	                        XmNx, 3,
	                        XmNy, 4,
	                        XmNheight, 32,
	                        XmNrecomputeSize, FALSE,
	                        /*XmNwidth, 670,*/
				RES_CONVERT(XmNlabelString," "),
	                        XmNalignment, XmALIGNMENT_CENTER,
	                        NULL );
	
	        UxPutContext( all_descr_label[i], (char *) UxTelepermContext );
	
	/*
	Istanzio label per data allarmi
	*/
	                strcpy(nomeWidget,"");
	                sprintf(nomeWidget,"%d",i);
	                strcat(nomeWidget,"_labelDataAlarm");
	
	all_data_label[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        all_rowColumn_dataAll,
	                        XmNx, 3,
	                        XmNy, 4,
	                        XmNheight, 32,
	                        XmNrecomputeSize, FALSE,
	                        /*XmNwidth, 200,*/
				RES_CONVERT(XmNlabelString," "),
	                        XmNalignment, XmALIGNMENT_END,
	                        NULL );
	
	        UxPutContext( all_data_label[i], (char *) UxTelepermContext );
		
		XtFree(nomeWidget);
		}
	/*
	Creazione bottoni per scorrimento pagina allarmi
	*/
		all_button_minus=XtVaCreateManagedWidget( "all_button_minus",
	                        xmPushButtonWidgetClass,
	                        all_formAll,
	                        XmNx, 1210,
	                        XmNy, 10,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 3,
	                        XmNleftWidget, all_rowColumn_dataAll,
	                        XmNtopOffset, 0,
	                        RES_CONVERT( XmNlabelString, "[-]" ),
	                        NULL );
	        UxPutContext( all_button_minus, (char *) UxTelepermContext );
	/*
	Callaback per comandi allarmi
	*/
		XtAddCallback(all_button_minus, XmNactivateCallback,
	                    (XtCallbackProc)command_alarm,OL_INDIETRO_ALLARMI);
	
	        all_button_plus = XtVaCreateManagedWidget( "all_button_plus",
	                        xmPushButtonWidgetClass,
	                        all_formAll,
	                        XmNx, 1210,
	                        XmNy, 635,
	                        RES_CONVERT( XmNlabelString, "[+]" ),
	                        XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
	                        XmNbottomOffset, 10,
	                        XmNbottomWidget, all_rowColumn_dataAll,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 4,
	                        XmNleftWidget, all_rowColumn_dataAll,
	                        NULL );
	        UxPutContext( all_button_plus, (char *) UxTelepermContext );
		
	        XtAddCallback(all_button_plus, XmNactivateCallback,
	                    (XtCallbackProc)command_alarm,OL_AVANTI_ALLARMI);
	
		all_button_n = XtVaCreateManagedWidget( "all_button_n",
	                        xmPushButtonWidgetClass,
	                        all_formAll,
	                        XmNx, 1210,
	                        XmNy, 690,
	                        RES_CONVERT( XmNlabelString, "[n]" ),
	                        XmNtopAttachment, XmATTACH_WIDGET,
	                        XmNtopOffset, 5,
	                        XmNtopWidget, all_button_plus,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftOffset, 4,
	                        XmNleftWidget, all_rowColumn_dataAll,
	                        NULL );
	        UxPutContext( all_button_n, (char *) UxTelepermContext );
		XtAddCallback(all_button_n, XmNactivateCallback,
	                    (XtCallbackProc)go_newest,NULL);
	
	
	for(i=0;i<NUMMAXZONE;i++)
		{
		
		if(zone_status[i])   /* Se trovo una zona attiva richiedo Allarmi */
			{
			OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
			break;
			}
		}
	printf("MAINALLPAGE Ho richiesto gli allarmi\n");
	OlSetDatabasePunti(all_caiAll,MAXNUMALLVIS,database_simulatore);
	teleperm_refreshAllPage(all_form_topLevelShell);
	/*
	Parte per visualizzare immediatamente la situazione allarmi
	nella parte di header della pagina Allarmi.
	Viene settata la richiesta allarmi per la zona  0 (destinata ad essere
	la zona di servizio ) dopodiche ' viene risettata a
	zero la zona in zone_status e rinviata la richiesta allarmi per 
	avere la situazione pulita.
	*/ 
	
	if(prima_apertura_all)
	      {
	      /*zone_status[last_zone]=1;*/
	      zone_status[0]=1;
	      OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
	      /*zone_status[last_zone]=0;*/
	      zone_status[0]=0;
	      OlTeleperm_richiediAllarmi(database_simulatore,zone_status);
	      prima_apertura_all=False;
	      }
	XtFree(nome_header);
        

return 1;
}

static int	_teleperm_create_allPage( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_create_allPage( UxThis, pEnv );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_WidgetSelect( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	/* recupero il nome della OW da aprire
	   e faccio blinkare il frame dello widget 
	   chiamante
	*/
	
	extern swidget create_OperatingWindow();
	swidget Ow=NULL;
	char *nome_pag;
	char nome_ow[255];
	FILE *fp;
	struct stat StatBuff;
	int i,posnew;
	Widget padre; /* padre del pictogrraph/indic */
	char class_name[100];
	
#ifndef DESIGN_TIME
	/* recupero il nome della OW da aprire
	*/
	XtVaGetValues(w,XlNpaginaStazioni,&nome_pag,NULL);
#endif
	
	strcpy(class_name, XlGetClassName(XtClass(w)) );
	
	printf("classe oggetto selezionato %s\n",class_name);
	
	if( strcmp( class_name , "IndicTelep" ) &&
	    strcmp( class_name , "Pictograph") )
	{
	   printf("Class parent not valid\n");
	   return(False);
	}
	
	/* verifica sul nome
	*/
	if( strlen(nome_pag) == 0 )
	{
	    printf("Not OW associated\n");
	    return(False);
	}
	
	/* individuo il file per verificare che esista il compilato
	*/
	sprintf(nome_ow,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),nome_pag);
	
	if( stat(nome_ow,&StatBuff) != 0 )
	{
	    printf("Cannot open associated OW\n");
	    return(False);
	}
	
	/* recupero l'indice nella lista delle pagine
	*/
	posnew = -1;
	for(i=0;i<totale_pagine;i++)
	    if( strcmp(pagine[i].nome,nome_pag) == NULL)
	    {
	       posnew = i;
	       break;
	    }
	
	if( posnew == -1 )
	{
	   printf("Page not faound in context\n");
	   return(False);
	}
	
	if( PaginaAperta(w,nome_pag) )
	{
	   printf("Page already open\n");
	   return(False);
	}
	
	if( !CanOpenPage(w) )
	{
	   printf("Cannot open page %s\n",nome_pag);
	   return(False);
	}
	
	printf("Open the associated OW\n");
	
	/* cerco la drawing area parent del pictograph/Indic
	*/
	padre = w;
	while( (xmDrawingAreaWidgetClass != XtClass(padre)) )
	   padre = XtParent(padre); 
	
	/* creo la interfaccia e aggiorno la lista
	   delle OW aperte
	*/
	
	Ow = create_OperatingWindow(padre,w,&pagine[posnew],PagDb);
	
	if( Ow != NULL )
	{
	
	   /* alloco spazio per la lista delle pagine figlie
	   */
	   if( (ChildPagList = (Widget *) XtRealloc( ChildPagList,
	           sizeof( Widget ) * (numChildPagList+1) )) == NULL )
	   {
	      fprintf(stderr,"Teleperm: Error in allocation of childPag list\n");
	      return(False);
	   }
	
	   ChildPagList[ numChildPagList ] = Ow;
	   numChildPagList++;
	
	printf("Aperta OW = %d \n",ChildPagList[ numChildPagList-1 ]);
	printf("numChildPagList = %d\n",numChildPagList);
	
	   UxPopupInterface(Ow,no_grab);
	}
	
	return(True);
}

static int	_teleperm_WidgetSelect( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_WidgetSelect( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_info( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	FILE *fp;
	
	char *envvar;
	char nomefile[FILENAME_MAX];
	char editor[FILENAME_MAX];
	char comando[FILENAME_MAX*2];
	char filtro[FILENAME_MAX];
	char appo[200];
	char num_widget[100];
	char *tipo;
	XrmValue value;
	char risorsa[50];
	Display *disp;
	
	
	static int nwidget=1;
	
	
	if((envvar=(char *) getenv("TMPDIR"))==NULL)
	   {
	   strcpy(nomefile,DEFTMPDIR);
	   }
	else
	   strcpy(nomefile,envvar);
	
	
	
	/*
	Ricavo nome file
	*/
	sprintf(num_widget,"%d",nwidget);  /* No file di Info*/
	sprintf(appo,"%d",getpid());
	
	strcat(nomefile,TMPINFOFILE);
	strcat(nomefile,appo);
	strcat(nomefile,"_");
	strcat(nomefile,num_widget);
	strcat(nomefile,".tmp");
	
	
	
	
	if((fp=fopen(nomefile,"w"))==0)
	   {
	   printf("ERROR: Impossible to open the temporay file =%s \n",nomefile);
	   return -1;
	   }
	
	
	if(ScriviTestoInfo(w,fp))
	   fclose(fp);
	else
	   return -1;
	
	
	InfoUsed=True;
	/*
	Filtraggio file
	*/
	disp = XtDisplay(UxThis);
	
	sprintf(risorsa,"teleperm.InfoFilter"); 
	XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);
	
	
	
	if( ((value.addr != NULL) && (value.size != 0)) )
	   {
	   /*
	   Esegue filtraggio
	   */
	   strncpy(filtro,value.addr,(int)value.size);
	
	   /*
	   Verifico che non ci siano solo spazi
	   */
	   strcpy(appo,"");
	   sscanf(filtro,"%s",appo);
	
	   if(strlen(appo))
	      {
	      strcpy(comando,"cat ");
	      strcat(comando,nomefile);
	      strcat(comando," | ");
	      strcat(comando,filtro);
	      strcat(comando," >> appo ");
	      system(comando);
	
	      /*
	      Copia file filtrato su originale
	      */
	      strcpy(comando,"cp ");
	      strcat(comando," appo ");
	      strcat(comando,nomefile);
	      system(comando);
	      system("rm appo");
	      }
	
	   }
	
	
	/*
	Vado ad editare il file 
	*/
	
	if((envvar=(char *) getenv("TPEDITOR"))==NULL) /* Verifico editor teleperm */
	   {
	   strcpy(editor,DEFEDITOR);
	   }
	else
	   strcpy(editor,envvar);
	/*
	Preparazione comando
	*/
	if(strcmp(editor,"asedit"))  /* Se e' asedit inutile lanciare xterm */
	   strcpy(comando,"xterm -e ");
	else
	   strcpy(comando," ");
	strcat(comando,editor);
	strcat(comando," ");
	strcat(comando,nomefile);
	strcat(comando,"&");
	
	/* 
	Esecuzione comando
	*/
	system(comando);
	
	nwidget++;
	return 1;
}

static int	_teleperm_info( UxThis, pEnv, w )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_info( UxThis, pEnv, w );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_dispTime( UxThis, pEnv, tempoSim )
	swidget	UxThis;
	Environment *	pEnv;
	float	tempoSim;
{
	char ora[20];
	XmString xstr;
	
/*        prova(&tempoSim, "Stringa di prova"); */
	conver_time(tempoSim,ora);
	
	xstr = XmStringCreateSimple(ora);
	set_something(Ora,XmNlabelString,xstr);
	XmStringFree(xstr);
	return(True);
}

static void conver_time(float tempoSim,char *ora)
{
int hh;
int mm;
int ss;
int resto;
int k1=3600;
int k2=60;

/* converto in hh.mm.ss
*/
hh = tempoSim/k1;
resto = (int)tempoSim % k1;

if( resto )
{
  mm = resto / k2;
  resto %= k2;
}
else
  mm = 0;

ss = resto;

/* emetto la stringa
*/
sprintf(ora,"%2d:%2d:%2d",hh,mm,ss);

}
static int	_teleperm_dispTime( UxThis, pEnv, tempoSim )
	swidget	UxThis;
	Environment *	pEnv;
	float	tempoSim;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_dispTime( UxThis, pEnv, tempoSim );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_vertHier( UxThis, pEnv, lista_ind, npag )
	swidget	UxThis;
	Environment *	pEnv;
	int	**lista_ind;
	int	*npag;
{
	OlTreeObject curr_oltree;
	int pcur,i,progr;
	
	 
	if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,Pag->gerarchia) == False )
	{
	      printf("Error retrieving hierarchy information for this page\n");
	      (*lista_ind) = NULL;
	      (*npag) = 0;
	      return(False);
	}
	
	
	
	   /* recupero il parent del livello attuale 
	      e la lista dei figli, ottengo cosi la lista verticale della gerarchia
	   */
	
	   getSubLevel( curr_oltree, lista_ind, npag);
}

static int	_teleperm_vertHier( UxThis, pEnv, lista_ind, npag )
	swidget	UxThis;
	Environment *	pEnv;
	int	**lista_ind;
	int	*npag;
{
	int			_Uxrtrn;
	_UxCteleperm            *UxSaveCtx = UxTelepermContext;

	UxTelepermContext = (_UxCteleperm *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_vertHier( UxThis, pEnv, lista_ind, npag );
	UxTelepermContext = UxSaveCtx;

	return ( _Uxrtrn );
}


/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_previous( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int numero_screen; /* numero screen di questa interfaccia */
	
	numero_screen=XScreenNumberOfScreen(XtScreen(UxWidget));
	/*
	Se il numero di screen e' quello dell' interfaccia cui appartiene qusto bottone,
	usa il previous altrimenti deve usare un gotopag.
	Se non facessi cosi' userei il previous della interfaccia remota.
	*/
	if(numero_screen==screen_selezionato)
		teleperm_naviga(UxWidget,PREVIOUS,NULL);
	else
		teleperm_naviga(UxWidget,GOTOPAG,pos_pag_curr);
	/*
	Es.:
	Se sono sullo screen 0	con l' ultima chiamata attivo la pagina di indice pos_pag_curr (screen 0)0
	sullo screen 1. Verranno aggiornate le var pos_pag_curr e pos_pag_new sullo screen 1 dalla
	procedura teleperm_navigation.
	*/
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_left( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	
	  teleperm_naviga(UxWidget,LEFT,NULL);
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_up( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	  teleperm_naviga(UxWidget,UP,NULL);
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_right( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	  teleperm_naviga(UxWidget,RIGTH,NULL);
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_swscreen( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int numero_screen; /* per determinare quale pixmap usare */
	int stato;
	char nome_bitmap[256];
	 
	teleperm_switchScreen(teleperm,&UxEnv);
	
	teleperm_drawPush(teleperm,&UxEnv, UxWidget,swscreenBMP);
	
	if( screen_switched != True )
	
	   screen_switched = True;
	else
	   screen_switched = False;
	  
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_ackal( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	if(allPageOnScreen==-1)
		return;
	else
	 OlCommandAllarmi(database_simulatore,OL_RICONOSCI_ALLARMI);
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_hardcopy( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	if(allPageOnScreen!=-1)
	{
		if(!PrintAllarmi(all_form_topLevelShell))
			fprintf(stderr,"Hardcopy error on Alarm Page\n");	
	}
	else	
	{
	
	
	if(!PrintScreen(drawingArea,"nome_disp","Pagina","False",Pag->sfondo))
	   fprintf(stderr,"Hardcopy error\n");
	}
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_help( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	/*
	Setta operazione attiva come INFO.
	
	Passaggi leciti:
	NOP-> INFO
	INFO->NOP
	*/
	if(operazione_attiva==OPERAZIONE_NOP)
	   {
	   operazione_attiva=OPERAZIONE_INFO;
	   XtVaSetValues(aing,XmNsensitive,False,NULL);
	   XtVaSetValues(plot,XmNsensitive,False,NULL);
	   }
	else if(operazione_attiva==OPERAZIONE_INFO)
	   {
	   operazione_attiva=OPERAZIONE_NOP;
	   XtVaSetValues(aing,XmNsensitive,True,NULL);
	   XtVaSetValues(plot,XmNsensitive,True,NULL);
	   }
	else return;
	
	teleperm_drawPush(teleperm,&UxEnv, UxWidget,helpBMP);
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_processDisplay( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int retval;
	
	retval = teleperm_openTopProcDisplay(teleperm,&UxEnv); 
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_logoff( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	extern int password_ok;
	extern void quit_proc();
	extern swidget popup_password();
	
	/* chiamo il metodo di close
	*/
	popup_password( teleperm );
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_aing( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	char aingColor[256];
	char *tipo;
	XrmValue value;
	
	if(operazione_attiva==OPERAZIONE_NOP)
	   {
	    
	   operazione_attiva=OPERAZIONE_XAING;
	
	   /*
	   Cerco il colore come risorsa da run_time
	   */
	   XrmGetResource((XtDisplay(aing))->db,"teleperm.aingColor",(char *)NULL,&tipo,&value);
	   if(value.size)
	      strncpy(aingColor,value.addr,(int)value.size);
	   else 
	      strcpy(aingColor,"blue");
	
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNbackground, aingColor),NULL);
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,"Aing"),NULL);
	   XtVaSetValues(help,XmNsensitive,False,NULL);
	   XtVaSetValues(plot,XmNsensitive,False,NULL);
	   }
	else if(operazione_attiva==OPERAZIONE_XAING)
	   {
	   operazione_attiva=OPERAZIONE_NOP;
	   XtVaSetValues(menuSystem_csbutt,XmNbackground,def_col_menuSystem,NULL);
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,SISTEMLABEL),NULL);
	   XtVaSetValues(help,XmNsensitive,True,NULL);
	   XtVaSetValues(plot,XmNsensitive,True,NULL);
	   }
	else return;
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_plot( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	char plotColor[256];
	char *tipo;
	XrmValue value;
	
	
	if(operazione_attiva==OPERAZIONE_NOP)
	   {
	
	   operazione_attiva=OPERAZIONE_XPLOT;
	
	           /*
	           Cerco il colore come risorsa da run_time
	           */
	           XrmGetResource((XtDisplay(aing))->db,"teleperm.plotColor",(char *)NULL,&tipo,&value);
	           if(value.size)
	              strncpy(plotColor,value.addr,(int)value.size);
	           else
	              strcpy(plotColor,"green");
	
	
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNbackground, plotColor),NULL);
	   XtVaSetValues(help,XmNsensitive,False,NULL);
	   XtVaSetValues(aing,XmNsensitive,False,NULL);
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,"Plot"),NULL);
	   }
	else if(operazione_attiva==OPERAZIONE_XPLOT)
	   {
	   operazione_attiva=OPERAZIONE_NOP;
	   XtVaSetValues(menuSystem_csbutt,XmNbackground,def_col_menuSystem,NULL);
	   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,SISTEMLABEL),NULL);
	   XtVaSetValues(help,XmNsensitive,True,NULL);
	   XtVaSetValues(aing,XmNsensitive,True,NULL);
	   }
	else return;
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_isa( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int numero_screen;
	if(allPageOnScreen!=-1)
		return;
	teleperm_naviga(UxWidget,GOTOPAG,INDALLPAG);
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_plantOverview( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	teleperm_naviga(UxWidget,PLANT_OVW,NULL);
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_plantButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int i,kk;
	char *nomePushButton;
	int *lista_ind,npag;
	char *gerarchiaValore;
	char nomeCai[100];
	char *nomeLabel;
	char *gerarchiaNome;
	Position xShell,yShell,xButton;
	Dimension heightButton;
	extern int PagIsTeleperm();
	extern OlTreeObject root_oltree;
	int indice_fa;
	char appo[100],*str;
	
	gerarchiaNome=NULL;
	gerarchiaValore=NULL;
	/*
	Se esiste qualche altro pullDownMenu eliminalo
	*/
	if (pullDownActive)
		{				/* Verifico se e' questo stesso Menu */
		if(pullMenuOn==PLANTMENUON)   /* Second click -> close VertMenu */
			{
			XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive);
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);		
	                XtFree(listaPushButtonPlant);
	                XtFree(listaPlantAsd);
			pullDownActive=NULL;
		        pullMenuOn=0;
			return;
			}
		else
			{
					/* elimino altro pullDownMenu */
			XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);
	                XtFree(listaPushButton);
			pullDownActive=NULL;
			}
		
		}
	
	if(!num_telepag)
		return;     /* no pages under Vertical hierarchy */if( (listaPushButtonPlant = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)
	{
	   printf("plantMenu. Error in malloc: listaPushButton\n");
	   return;
	}
	/*
	Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr
	cosi' da poterlo poi eliminare da qualunque interfaccia
	*/
	listaPushButton=listaPushButtonPlant;
	if( (listaCaiVr = (Widget *) XtCalloc(1, num_telepag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)
	{
	   printf("plantMenu. Error in malloc: listaCai\n");
	   return;
	}
	
	if ( (listaCaiFormVr = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)
	{
	   printf("vertHierMenu. Error in malloc: listaCaiForm\n");
	   return;
	}
	if ( (listaPlantAsd = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)
	{
	   printf("vertHierMenu. Error in malloc: listaPlantAsd\n");
	   return;
	}
	get_something(	teleperm,XmNx,&xShell);		
	get_something(	teleperm,XmNy,&yShell);		
	get_something(	formCaiPlant,XmNx,&xButton);
	
	
	PlantMenu = XtVaCreatePopupShell("PlantMenu",
/*
				topLevelShellWidgetClass,
*/
                                transientShellWidgetClass,
				plantButton,
				XmNallowShellResize, True,
	                        XmNx, (xShell+xButton),
	                        XmNy, (yShell+30),
				XmNmwmDecorations, 0 ,
				NULL );
	UxPutContext( PlantMenu, (char *) UxTelepermContext );
	
	/*
	Point to pullDownMenu
	*/
	
	pullDownActive=&PlantMenu;
	pullMenuOn=PLANTMENUON; /* menu attivo Plantmenu */
	
	
	PlantPane=XtVaCreateManagedWidget( "plantPane",
	                        xmFormWidgetClass,
	                        PlantMenu,
	                        NULL );
	
	UxPutContext( PlantPane, (char *) UxTelepermContext );
	
	RowPull=XtVaCreateManagedWidget( "rowColumnPull",
					xmRowColumnWidgetClass,
					PlantPane,
					XmNpacking,XmPACK_COLUMN,
					XmNorientation,XmHORIZONTAL,
					XmNnumColumns, num_telepag,
					XmNtopAttachment,XmATTACH_FORM,
					XmNleftAttachment,XmATTACH_FORM,
					NULL);
	UxPutContext( RowPull, (char *) UxTelepermContext );
	
	i=0;
	for(kk=0; kk < num_zone ; kk++)
	{
	 if(selectable_zone[kk])
	  {
	    		/*      Ricavo nome del Bottone 	*/
	   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].descrizione) +20) )) == NULL)
	   {
	      printf("plantMenu Error in malloc: nomePushButton\n");
	      return;
	   }
	   strcpy(nomePushButton, pagine[selectable_zone[kk] ].descrizione);
	 
	  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].descrizione) +20) )) == NULL)
	   {
	      printf("plantMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	
	  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].gerarchia) +20) )) == NULL)
	   {
	      printf("plantMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	  if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].gerarchia) +20) )) == NULL)
	   {
	      printf("plantMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	strcpy(gerarchiaNome,pagine[selectable_zone[kk]].gerarchia);
	hierarchy_format_new(gerarchiaValore,gerarchiaNome);
	
	/*printf("gerarchiaValore=%s\n",gerarchiaValore);*/
	
	 strcpy(nomeLabel,"CAI of ");
	 strcat(nomeLabel,pagine[selectable_zone[kk]].descrizione);
	
	   /* push button */
	if(i==0)
	  listaPushButtonPlant[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_FORM,
				XmNleftAttachment,XmATTACH_FORM,
	*/  
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );
	else
	  listaPushButtonPlant[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_WIDGET,
				XmNleftAttachment,XmATTACH_FORM,
				XmNtopWidget,listaPushButtonPlant[i-1],
	*/
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );	
	
	   UxPutContext( listaPushButtonPlant[i], (char *) UxTelepermContext );
	
	   XtAddCallback(listaPushButtonPlant[i], XmNactivateCallback,
	                    (XtCallbackProc)view_fa,selectable_zone[kk] ); 
	
	
	/*
	Costruisco Nome form dei Cai
	*/
	strcat(nomePushButton,"FORM");
	/*printf("nomeformCai=%s\n",nomePushButton);*/
	
	listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmFormWidgetClass,
	                        RowPull,
	                        XmNwidth, 250,
	                       	RES_CONVERT( XmNbackground, "#000000"),
				NULL );
	
	UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );
	
	/*
	Creo lista di bottoni ASD per Plant Menu' 
	*/
	strcpy(nomePushButton,"");
	sprintf(nomePushButton,"%d",i);
	strcat(nomePushButton,"ASD");
	
	listaPlantAsd[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        listaCaiFormVr[i],
	                        XmNwidth, 45,
				XmNheight, 25,
				XmNtopAttachment,XmATTACH_FORM,
				XmNleftAttachment,XmATTACH_FORM,
				XmNleftOffset,LEFTOFFSET,
				XmNtopOffset,TOPOFFSET,
				NULL );
	
	UxPutContext( listaPlantAsd[i], (char *) UxTelepermContext );
	
	XtAddCallback(listaPlantAsd[i], XmNactivateCallback,
	                    (XtCallbackProc)open_allPag_fa,kk ); 
	
	build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaPlantAsd[i],gerarchiaValore,i);
	
	
	
	   XtFree(nomePushButton);  
	   XtFree(nomeLabel);
	if(gerarchiaNome)
	   XtFree(gerarchiaNome);
	if(gerarchiaValore)
	   XtFree(gerarchiaValore);
	  i++; /*incremento contatore lista oggetti */
	   /*printf("i=%d selectable_zone[%d]=%d\n",i,kk,selectable_zone[kk]);*/
	  }/* end if selectable_zone */
	}/* end for */
	printf("NUM_TELEPAG=%d i=%d\n",num_telepag,i);
	npagPulldown=i*MAXNUMCAIXLINE;
	UxPopupInterface(PlantMenu,no_grab);
	
	/*
	Cai refresh routine with a XtAppAddTimeOut inside 
	*/
	
	OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);
	teleperm_refreshCai(PlantMenu);
	
	
	
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

XtCallbackProc	exposeCB_drawingArea( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	/*
	disegna_bck(UxWidget,bkg_sin,UxCallbackArg,&(region_sin),False);
	*/
	disegna_bck(UxWidget,Pag->sfondo,UxCallbackArg,&(region_sin),False);
	
#endif
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_vertHierButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int i;
	char *nomePushButton;
	int *lista_ind,npag;
	char *gerarchiaValore;
	char nomeCai[100];
	char *nomeLabel;
	char *gerarchiaNome;
	Position xShell,yShell,xButton;
	Dimension heightButton;
	
	
	/*
	Risettaggio database risorse
	*/
	gerarchiaNome=NULL;
	gerarchiaValore=NULL;
	XrmSetDatabase(XtDisplay(UxWidget),PagDb); 
	
	/*
	Se esiste qualche altro pullDownMenu eliminalo
	*/
	
	if (pullDownActive)
		{				/* Verifico se e' questo stesso Menu */
		if(pullMenuOn==VERTMENUON)   /* Second click -> close VertMenu */
			{
			if(scada_on)
				XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive);
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);
			XtFree(listaPushButton);
			pullDownActive=NULL;
		        pullMenuOn=0;
			return;
			}
		else
			{
					/* elimino altro pullDownMenu */
			if(scada_on)
				XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);
			XtFree(listaPushButton);
			pullDownActive=NULL;
			}
		
		}
	/*
	Acquisisco gerarchia Verticale 
	*/
	teleperm_vertHier(teleperm,&UxEnv,&lista_ind,&npag);
	
	if(!npag)
		return;     /* no pages under Vertical hierarchy */
	if( (listaPushButtonVr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)
	{
	   printf("vertHierMenu. Error in malloc: listaPushButton\n");
	   return;
	}
	/*
	Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr
	cosi' da poterlo poi eliminare da qualunque interfaccia
	*/
	listaPushButton=listaPushButtonVr;
	if( (listaCaiVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)
	{
	   printf("vertHierMenu. Error in malloc: listaCai\n");
	   return;
	}
	if ( (listaCaiFormVr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)
	{
	   printf("vertHierMenu. Error in malloc: listaCaiForm\n");
	   return;
	}
	get_something(	teleperm,XmNx,&xShell);		
	get_something(	teleperm,XmNy,&yShell);		
	get_something(	vertHierButton,XmNx,&xButton);
	
	
	VertMenu = XtVaCreatePopupShell("VertMenu",
/*
				topLevelShellWidgetClass,
*/
                                transientShellWidgetClass,
				vertHierButton,
				XmNallowShellResize, True,
	                        XmNx, (xShell+xButton),
	                        XmNy, (yShell+60),
				XmNmwmDecorations, 0 ,
				NULL );
	UxPutContext( VertMenu, (char *) UxTelepermContext );
	
	/*
	Point to pullDownMenu
	*/
	pullDownActive=&VertMenu;
	pullMenuOn=VERTMENUON; /* menu attivo Vertmenu */
	
	
	VertPane=XtVaCreateManagedWidget( "formCaiPull",
	                        xmFormWidgetClass,
	                        VertMenu,
	                        NULL );
	
	UxPutContext( VertPane, (char *) UxTelepermContext );
	
	RowPull=XtVaCreateManagedWidget( "rowColumnPull",
					xmRowColumnWidgetClass,
					VertPane,
					XmNpacking,XmPACK_COLUMN,
					XmNorientation,XmHORIZONTAL,
					XmNnumColumns, npag,
					XmNtopAttachment,XmATTACH_FORM,
					XmNleftAttachment,XmATTACH_FORM,
					NULL);
	UxPutContext( RowPull, (char *) UxTelepermContext );
	
	for(i=0; i < npag; i++)
	{
	    		/*      Ricavo nome del Bottone 	*/
	   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomePushButton\n");
	      return;
	   }
	   strcpy(nomePushButton, pagine[ lista_ind[i] ].descrizione);
	 
	  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	/*
	Alloco gerarchiaNome per gerarchia con ',' e gerarchiaValore per gerarchia con '['
	*/
	
	  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	 if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	strcpy(gerarchiaNome,pagine[lista_ind[i]].gerarchia);
	
	hierarchy_format_new(gerarchiaValore,gerarchiaNome);
	
	/*
	printf("gerarchiaNome=%s\n",gerarchiaNome);
	printf("gerarchiaValore=%s\n",gerarchiaValore);
	*/
	
	 strcpy(nomeLabel,"CAI of ");
	 strcat(nomeLabel,pagine[lista_ind[i]].descrizione);
	
	   /* push button */
	if(i==0)
	  listaPushButtonVr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_FORM,
				XmNleftAttachment,XmATTACH_FORM,
	*/
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );
	else
	  listaPushButtonVr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_WIDGET,
				XmNleftAttachment,XmATTACH_FORM,
				XmNtopWidget,listaPushButtonVr[i-1],
	*/
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );	
	
	   UxPutContext( listaPushButtonVr[i], (char *) UxTelepermContext );
	
	   XtAddCallback(listaPushButtonVr[i], XmNactivateCallback,
	                    (XtCallbackProc)view_fa,lista_ind[i] ); 
	
	/*
	Costruisco Nome form dei Cai
	*/
	strcat(nomePushButton,"FORM");
	  
	listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmFormWidgetClass,
	                        RowPull,
	                        XmNwidth, 200,
	                       	RES_CONVERT( XmNbackground, "#000000" ),
				NULL );
	
	 UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );
	
	/* Costruisci lista di cai solo se mmi agganciato con scada */
	if(scada_on)
	      build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaCaiFormVr[i],gerarchiaValore,i);
	  
	   XtFree(nomePushButton);
	   XtFree(nomeLabel);
	
	if(gerarchiaNome)
	   XtFree(gerarchiaNome);
	if(gerarchiaValore)
	   XtFree(gerarchiaValore);
	}/* end for */
	/* Innesco refresh dei cai solo se esistono */
	if(scada_on)
	      {
	      npagPulldown=npag*MAXNUMCAIXLINE;
	
		OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);
	
		/*
		Cai refresh routine with a XtAppAddTimeOut inside 
		*/
	
		teleperm_refreshCai(VertMenu);
		}  
	UxPopupInterface(VertMenu,no_grab);
	
	XtFree(lista_ind);
	
	
	}
	UxTelepermContext = UxSaveCtx;
}

static	void	activateCB_orizHierButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCteleperm            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTelepermContext;
	UxTelepermContext = UxContext =
			(_UxCteleperm *) UxGetContext( UxWidget );
	{
	int i;
	char *nomePushButton;
	int *lista_ind,npag;
	char *gerarchiaValore;
	char *nomeLabel;
	char *gerarchiaNome;
	Position xShell,yShell,xButton;
	Dimension heightButton;
	
	npag=0;
	gerarchiaNome=NULL;
	gerarchiaValore=NULL;
	/*
	Se esiste qualche altro pullDownMenu eliminalo
	*/
	if (pullDownActive)
		{				/* Verifico se e' questo stesso Menu */
		if(pullMenuOn==ORIZMENUON)   /* Second click -> close VertMenu */
			{
			if(scada_on)
				XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive);
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);
			XtFree(listaPushButton);
			pullDownActive=NULL;
			return;
			}
		else
			{
					/* elimino altro pullDownMenu */
			if(scada_on)
				XtRemoveTimeOut(timer_timerefreshCai);
			UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */
			XtFree(listaCaiVr);
			XtFree(listaCaiFormVr);
			XtFree(listaPushButton);
			pullDownActive=NULL;
			}
		
		}
	/*
	Acquisisco gerarchia Verticale 
	*/
	teleperm_orizHier(teleperm,&UxEnv,&lista_ind,&npag);
	
	if(!npag)
		{
		return;
		}     /* no pages under Horizontal hierarchy */
	if( (listaPushButtonOr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)
	{
	   printf("orizHierMenu. Error in malloc: listaPushButton\n");
	   return;
	}
	/*
	Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr
	cosi' da poterlo poi eliminare da qualunque interfaccia
	*/
	listaPushButton=listaPushButtonOr;
	if( (listaCaiVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)
	{
	   printf("orizHierMenu. Error in malloc: listaCaiVr\n");
	   return;
	}
	
	if( (listaCaiFormVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)
	{
	   printf("orizHierMenu. Error in malloc: listaCaiFormVr\n");
	   return;
	}
	
	get_something(	teleperm,XmNx,&xShell);		
	get_something(	teleperm,XmNy,&yShell);		
	get_something(	orizHierButton,XmNx,&xButton);
	
	printf("OrizMenu is about to be created\n");
	OrizMenu = XtVaCreatePopupShell("OrizMenu",
/*
				topLevelShellWidgetClass,
*/
                                transientShellWidgetClass,
				orizHierButton,
				XmNallowShellResize, True,
	                        XmNx, (xShell+xButton),
	                        XmNy, (yShell+60),
				XmNmwmDecorations, 0 ,
				NULL );
	UxPutContext( OrizMenu, (char *) UxTelepermContext );
	/*
	Point to pullDownMenu
	*/
	pullDownActive=&OrizMenu;
	pullMenuOn=ORIZMENUON;    /* Menu attivo  orizzontale */
	printf("npag=%d\n",npag);
	
	OrizPane=XtVaCreateManagedWidget( "rowColumn1",
	                        xmFormWidgetClass,
	                        OrizMenu,
	                       	NULL );
	
	UxPutContext( OrizPane, (char *) UxTelepermContext );
	
	RowPull=XtVaCreateManagedWidget( "rowColumnPull",
					xmRowColumnWidgetClass,
					OrizPane,
					XmNpacking,XmPACK_COLUMN,
					XmNorientation,XmHORIZONTAL,
					XmNnumColumns, npag,
					XmNtopAttachment,XmATTACH_FORM,
					XmNleftAttachment,XmATTACH_FORM,
					NULL);
	UxPutContext( RowPull, (char *) UxTelepermContext );
	
	for(i=0; i < npag; i++)
	{
	    		/*      Ricavo nome del Bottone 	*/
	   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomePushButton\n");
	      return;
	   }
	   strcpy(nomePushButton, pagine[ lista_ind[i] ].descrizione);
	 
	  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	
	  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	  if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)
	   {
	      printf("vertMenu Error in malloc: nomeLabel\n");
	      return;
	   }
	
	strcpy(gerarchiaNome,pagine[lista_ind[i]].gerarchia);
	hierarchy_format_new(gerarchiaValore,gerarchiaNome);
	
	
	 strcpy(nomeLabel,"CAI of ");
	 strcat(nomeLabel,pagine[lista_ind[i]].descrizione);
	
	   /* push button */
	if(i==0)
	  listaPushButtonOr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_FORM,
				XmNleftAttachment,XmATTACH_FORM,
	*/
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );
	else
	  listaPushButtonOr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmPushButtonWidgetClass,
	                        RowPull,
	/*
				XmNtopAttachment,XmATTACH_WIDGET,
				XmNleftAttachment,XmATTACH_FORM,
	*/
				XmNtopWidget,listaPushButtonOr[i-1],
	                        RES_CONVERT( XmNlabelString, nomePushButton ),
	                        NULL );	
	
	   UxPutContext( listaPushButtonOr[i], (char *) UxTelepermContext );
	
	   XtAddCallback(listaPushButtonOr[i], XmNactivateCallback,
	                    (XtCallbackProc)view_fa,lista_ind[i] ); 
	/*
	Costruisco Nome form dei Cai
	*/
	strcat(nomePushButton,"FORM");
	  
	listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,
	                        xmFormWidgetClass,
	                        RowPull,
	                        XmNwidth, 200,
	                       	RES_CONVERT( XmNbackground, "#000000" ),
				NULL );
	
	UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );
	/* Costruisci lista di cai solo se mmi agganciato con scada */
	if(scada_on)
	      build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaCaiFormVr[i],gerarchiaValore,i);
	
	   XtFree(nomePushButton);
	
	   XtFree(nomeLabel);
	
	   if(gerarchiaNome)
	      XtFree(gerarchiaNome);
	   if(gerarchiaValore)
	      XtFree(gerarchiaValore);
	}/* end for */
	
	/* Innesco refresh dei cai solo se esistono */
	if(scada_on)
	      {
	      npagPulldown=npag*MAXNUMCAIXLINE;
	      
	      /*
	      Cai refresh routine with a XtAppAddTimeOut inside 
	      */
	      OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);
	
	      teleperm_refreshCai(OrizMenu);
	      }
	
	UxPopupInterface(OrizMenu,no_grab);
	XtFree(lista_ind);
	
	}
	UxTelepermContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_teleperm()
{
	Widget		_UxParent;
	Widget		menuSystem_rc1_shell;


	/* Creation of teleperm */
	_UxParent = UxParent;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	teleperm = XtVaCreatePopupShell( "teleperm",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 150,
			XmNy, 190,
			XmNheight, 660,
			XmNmwmDecorations, MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE,
			XmNminHeight, 1024,
			XmNminWidth, 1280,
			NULL );
	UxPutContext( teleperm, (char *) UxTelepermContext );


	/* Creation of formTop */
	formTop = XtVaCreateManagedWidget( "formTop",
			xmFormWidgetClass,
			teleperm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 240,
			XmNy, 230,
			XmNwidth, 340,
			XmNheight, 140,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( formTop, (char *) UxTelepermContext );


	/* Creation of screenFooterForm */
	screenFooterForm = XtVaCreateManagedWidget( "screenFooterForm",
			xmFormWidgetClass,
			formTop,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 610,
			XmNwidth, 1110,
			XmNheight, 35,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( screenFooterForm, (char *) UxTelepermContext );


	/* Creation of rcFooter */
	rcFooter = XtVaCreateManagedWidget( "rcFooter",
			xmRowColumnWidgetClass,
			screenFooterForm,
			XmNx, 10,
			XmNy, 0,
			XmNwidth, 1210,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 50,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNspacing, 30,
			XmNorientation, XmHORIZONTAL,
			NULL );
	UxPutContext( rcFooter, (char *) UxTelepermContext );


	/* Creation of previous */
	previous = XtVaCreateManagedWidget( "previous",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Previous" ),
			XmNlabelType, XmPIXMAP,
			XmNy, 0,
			NULL );
	XtAddCallback( previous, XmNactivateCallback,
		(XtCallbackProc) activateCB_previous,
		(XtPointer) UxTelepermContext );

	UxPutContext( previous, (char *) UxTelepermContext );


	/* Creation of left */
	left = XtVaCreateManagedWidget( "left",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Left" ),
			XmNlabelType, XmPIXMAP,
			XmNx, 590,
			XmNy, -1,
			NULL );
	XtAddCallback( left, XmNactivateCallback,
		(XtCallbackProc) activateCB_left,
		(XtPointer) UxTelepermContext );

	UxPutContext( left, (char *) UxTelepermContext );


	/* Creation of up */
	up = XtVaCreateManagedWidget( "up",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Up" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( up, XmNactivateCallback,
		(XtCallbackProc) activateCB_up,
		(XtPointer) UxTelepermContext );

	UxPutContext( up, (char *) UxTelepermContext );


	/* Creation of right */
	right = XtVaCreateManagedWidget( "right",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Right" ),
			XmNlabelType, XmPIXMAP,
			RES_CONVERT( XmNbottomShadowColor, "#feeed4" ),
			XmNx, 590,
			XmNy, -1,
			NULL );
	XtAddCallback( right, XmNactivateCallback,
		(XtCallbackProc) activateCB_right,
		(XtPointer) UxTelepermContext );

	UxPutContext( right, (char *) UxTelepermContext );


	/* Creation of swscreen */
	swscreen = XtVaCreateManagedWidget( "swscreen",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "switch scr" ),
			XmNlabelType, XmPIXMAP,
			XmNx, 403,
			XmNy, 13,
			NULL );
	XtAddCallback( swscreen, XmNactivateCallback,
		(XtCallbackProc) activateCB_swscreen,
		(XtPointer) UxTelepermContext );

	UxPutContext( swscreen, (char *) UxTelepermContext );


	/* Creation of ackaud */
	ackaud = XtVaCreateManagedWidget( "ackaud",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Alarm Off" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	UxPutContext( ackaud, (char *) UxTelepermContext );


	/* Creation of ackal */
	ackal = XtVaCreateManagedWidget( "ackal",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Ack Alarm" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( ackal, XmNactivateCallback,
		(XtCallbackProc) activateCB_ackal,
		(XtPointer) UxTelepermContext );

	UxPutContext( ackal, (char *) UxTelepermContext );


	/* Creation of hardcopy */
	hardcopy = XtVaCreateManagedWidget( "hardcopy",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Hardcopy" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( hardcopy, XmNactivateCallback,
		(XtCallbackProc) activateCB_hardcopy,
		(XtPointer) UxTelepermContext );

	UxPutContext( hardcopy, (char *) UxTelepermContext );


	/* Creation of help */
	help = XtVaCreateManagedWidget( "help",
			xmPushButtonWidgetClass,
			rcFooter,
			RES_CONVERT( XmNlabelString, "Help" ),
			XmNlabelType, XmPIXMAP,
			XmNx, 590,
			XmNy, -1,
			NULL );
	XtAddCallback( help, XmNactivateCallback,
		(XtCallbackProc) activateCB_help,
		(XtPointer) UxTelepermContext );

	UxPutContext( help, (char *) UxTelepermContext );


	/* Creation of screenHeaderForm */
	screenHeaderForm = XtVaCreateManagedWidget( "screenHeaderForm",
			xmFormWidgetClass,
			formTop,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 290,
			XmNy, 50,
			XmNwidth, 990,
			XmNheight, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( screenHeaderForm, (char *) UxTelepermContext );


	/* Creation of rcProcess */
	rcProcess = XtVaCreateManagedWidget( "rcProcess",
			xmRowColumnWidgetClass,
			screenHeaderForm,
			XmNx, 600,
			XmNy, 0,
			XmNwidth, 140,
			XmNheight, 40,
			XmNorientation, XmHORIZONTAL,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 2,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			NULL );
	UxPutContext( rcProcess, (char *) UxTelepermContext );


	/* Creation of proceso */
	proceso = XtVaCreateManagedWidget( "proceso",
			xmPushButtonWidgetClass,
			rcProcess,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 90,
			NULL );
	UxPutContext( proceso, (char *) UxTelepermContext );


	/* Creation of processDisplay */
	processDisplay = XtVaCreateManagedWidget( "processDisplay",
			xmPushButtonWidgetClass,
			rcProcess,
			RES_CONVERT( XmNlabelString, "Up" ),
			XmNlabelType, XmPIXMAP,
			XmNwidth, 30,
			XmNx, 30,
			XmNy, 0,
			NULL );
	XtAddCallback( processDisplay, XmNactivateCallback,
		(XtCallbackProc) activateCB_processDisplay,
		(XtPointer) UxTelepermContext );

	UxPutContext( processDisplay, (char *) UxTelepermContext );


	/* Creation of formSystem */
	formSystem = XtVaCreateManagedWidget( "formSystem",
			xmFormWidgetClass,
			screenHeaderForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 880,
			XmNy, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 30,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			NULL );
	UxPutContext( formSystem, (char *) UxTelepermContext );


	/* Creation of menuSystem */
	menuSystem = XtVaCreateManagedWidget( "menuSystem",
			xmRowColumnWidgetClass,
			formSystem,
			XmNrowColumnType, XmMENU_BAR,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNx, 10,
			XmNy, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#ffefd5" ),
			NULL );
	UxPutContext( menuSystem, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1 */
	menuSystem_rc1_shell = XtVaCreatePopupShell ("menuSystem_rc1_shell",
			xmMenuShellWidgetClass, menuSystem,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menuSystem_rc1 = XtVaCreateWidget( "menuSystem_rc1",
			xmRowColumnWidgetClass,
			menuSystem_rc1_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( menuSystem_rc1, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b7 */
	menuSystem_rc1_b7 = XtVaCreateManagedWidget( "menuSystem_rc1_b7",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b7, (char *) UxTelepermContext );


	/* Creation of logoff */
	logoff = XtVaCreateManagedWidget( "logoff",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "logoff " ),
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( logoff, XmNactivateCallback,
		(XtCallbackProc) activateCB_logoff,
		(XtPointer) UxTelepermContext );

	UxPutContext( logoff, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b8 */
	menuSystem_rc1_b8 = XtVaCreateManagedWidget( "menuSystem_rc1_b8",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b8, (char *) UxTelepermContext );


	/* Creation of commonAck */
	commonAck = XtVaCreateManagedWidget( "commonAck",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "Common Ack" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	UxPutContext( commonAck, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b9 */
	menuSystem_rc1_b9 = XtVaCreateManagedWidget( "menuSystem_rc1_b9",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b9, (char *) UxTelepermContext );


	/* Creation of logSelection */
	logSelection = XtVaCreateManagedWidget( "logSelection",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "LogSelection" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	UxPutContext( logSelection, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b10 */
	menuSystem_rc1_b10 = XtVaCreateManagedWidget( "menuSystem_rc1_b10",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b10, (char *) UxTelepermContext );


	/* Creation of IncidentRew */
	IncidentRew = XtVaCreateManagedWidget( "IncidentRew",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "IncidentReview" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	UxPutContext( IncidentRew, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b11 */
	menuSystem_rc1_b11 = XtVaCreateManagedWidget( "menuSystem_rc1_b11",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b11, (char *) UxTelepermContext );


	/* Creation of longTermArc */
	longTermArc = XtVaCreateManagedWidget( "longTermArc",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "Long Term Arc" ),
			XmNlabelType, XmPIXMAP,
			NULL );
	UxPutContext( longTermArc, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b12 */
	menuSystem_rc1_b12 = XtVaCreateManagedWidget( "menuSystem_rc1_b12",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b12, (char *) UxTelepermContext );


	/* Creation of aing */
	aing = XtVaCreateManagedWidget( "aing",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "Aing" ),
			XmNlabelType, XmSTRING,
			RES_CONVERT( XmNmnemonic, "A" ),
			NULL );
	XtAddCallback( aing, XmNactivateCallback,
		(XtCallbackProc) activateCB_aing,
		(XtPointer) UxTelepermContext );

	UxPutContext( aing, (char *) UxTelepermContext );


	/* Creation of menuSystem_rc1_b13 */
	menuSystem_rc1_b13 = XtVaCreateManagedWidget( "menuSystem_rc1_b13",
			xmSeparatorGadgetClass,
			menuSystem_rc1,
			NULL );
	UxPutContext( menuSystem_rc1_b13, (char *) UxTelepermContext );


	/* Creation of plot */
	plot = XtVaCreateManagedWidget( "plot",
			xmPushButtonWidgetClass,
			menuSystem_rc1,
			RES_CONVERT( XmNlabelString, "Plot" ),
			RES_CONVERT( XmNmnemonic, "P" ),
			NULL );
	XtAddCallback( plot, XmNactivateCallback,
		(XtCallbackProc) activateCB_plot,
		(XtPointer) UxTelepermContext );

	UxPutContext( plot, (char *) UxTelepermContext );


	/* Creation of menuSystem_csbutt */
	menuSystem_csbutt = XtVaCreateManagedWidget( "menuSystem_csbutt",
			xmCascadeButtonWidgetClass,
			menuSystem,
			RES_CONVERT( XmNlabelString, SISTEMLABEL ),
			XmNsubMenuId, menuSystem_rc1,
			XmNx, 0,
			XmNy, 0,
			NULL );
	UxPutContext( menuSystem_csbutt, (char *) UxTelepermContext );


	/* Creation of rcData */
	rcData = XtVaCreateManagedWidget( "rcData",
			xmRowColumnWidgetClass,
			screenHeaderForm,
			XmNx, 5,
			XmNy, 2,
			XmNheight, 26,
			XmNorientation, XmHORIZONTAL,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 2,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNspacing, 10,
			XmNmarginWidth, 2,
			XmNwidth, 175,
			NULL );
	UxPutContext( rcData, (char *) UxTelepermContext );


	/* Creation of Data */
	Data = XtVaCreateManagedWidget( "Data",
			xmLabelWidgetClass,
			rcData,
			RES_CONVERT( XmNlabelString, "27-11-96" ),
			XmNwidth, 78,
			NULL );
	UxPutContext( Data, (char *) UxTelepermContext );


	/* Creation of Ora */
	Ora = XtVaCreateManagedWidget( "Ora",
			xmLabelWidgetClass,
			rcData,
			RES_CONVERT( XmNlabelString, "09:32:54" ),
			XmNwidth, 88,
			/* XmNfontList, UxConvertFontList( "helvetica10" ), */
			XmNheight, 20,
			NULL );
	UxPutContext( Ora, (char *) UxTelepermContext );


	/* Creation of formCaiPlant */
	formCaiPlant = XtVaCreateManagedWidget( "formCaiPlant",
			xmFormWidgetClass,
			screenHeaderForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 190,
			XmNy, 2,
			XmNwidth, 380,
			XmNheight, 26,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 2,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 190,
			NULL );
	UxPutContext( formCaiPlant, (char *) UxTelepermContext );


	/* Creation of isa */
	isa = XtVaCreateManagedWidget( "isa",
			xmPushButtonWidgetClass,
			formCaiPlant,
			XmNwidth, 45,
			XmNx, 150,
			XmNy, 0,
			XmNmarginHeight, 1,
			XmNmarginWidth, 1,
			XmNheight, 25,
			NULL );
	XtAddCallback( isa, XmNactivateCallback,
		(XtCallbackProc) activateCB_isa,
		(XtPointer) UxTelepermContext );

	UxPutContext( isa, (char *) UxTelepermContext );


	/* Creation of plantOverview */
	plantOverview = XtVaCreateManagedWidget( "plantOverview",
			xmPushButtonWidgetClass,
			formCaiPlant,
			RES_CONVERT( XmNlabelString, "Up" ),
			XmNlabelType, XmPIXMAP,
			XmNwidth, 38,
			XmNx, 120,
			XmNy, 0,
			XmNmarginHeight, 1,
			XmNmarginWidth, 1,
			XmNheight, 25,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			NULL );
	XtAddCallback( plantOverview, XmNactivateCallback,
		(XtCallbackProc) activateCB_plantOverview,
		(XtPointer) UxTelepermContext );

	UxPutContext( plantOverview, (char *) UxTelepermContext );


	/* Creation of plantButton */
	plantButton = XtVaCreateManagedWidget( "plantButton",
			xmPushButtonWidgetClass,
			formCaiPlant,
			XmNx, 10,
			XmNy, 0,
			XmNwidth, 90,
			XmNheight, 27,
			RES_CONVERT( XmNlabelString, "PLANT" ),
			XmNleftAttachment, XmATTACH_FORM,
			NULL );
	XtAddCallback( plantButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_plantButton,
		(XtPointer) UxTelepermContext );

	UxPutContext( plantButton, (char *) UxTelepermContext );


	/* Creation of separatorGadget1 */
	separatorGadget1 = XtVaCreateManagedWidget( "separatorGadget1",
			xmSeparatorGadgetClass,
			screenHeaderForm,
			XmNx, 0,
			XmNy, 30,
			XmNwidth, 1260,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 29,
			NULL );
	UxPutContext( separatorGadget1, (char *) UxTelepermContext );


	/* Creation of proceso1 */
	proceso1 = XtVaCreateManagedWidget( "proceso1",
			xmPushButtonWidgetClass,
			screenHeaderForm,
			XmNx, 890,
			XmNy, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 750,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			XmNbottomOffset, 2,
			NULL );
	UxPutContext( proceso1, (char *) UxTelepermContext );


	/* Creation of drawingArea */
	drawingArea = XtVaCreateManagedWidget( "drawingArea",
			xmDrawingAreaWidgetClass,
			formTop,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 240,
			XmNy, 100,
			XmNwidth, 1040,
			XmNheight, 877,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 60,
			XmNbottomOffset, 35,
			RES_CONVERT( XmNbackground, "black" ),
			XmNtraversalOn, FALSE,
			XmNnavigationType, XmNONE,
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			NULL );
	XtAddCallback( drawingArea, XmNexposeCallback,
		(XtCallbackProc) exposeCB_drawingArea,
		(XtPointer) UxTelepermContext );

	UxPutContext( drawingArea, (char *) UxTelepermContext );


	/* Creation of titleAreaform */
	titleAreaform = XtVaCreateManagedWidget( "titleAreaform",
			xmFormWidgetClass,
			formTop,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 40,
			XmNwidth, 1250,
			XmNheight, 30,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( titleAreaform, (char *) UxTelepermContext );


	/* Creation of titleLabel */
	titleLabel = XtVaCreateManagedWidget( "titleLabel",
			xmLabelWidgetClass,
			titleAreaform,
			XmNx, 580,
			XmNy, 0,
			XmNwidth, 450,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 00,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 510,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 250,
			NULL );
	UxPutContext( titleLabel, (char *) UxTelepermContext );


	/* Creation of vertHierButton */
	vertHierButton = XtVaCreateManagedWidget( "vertHierButton",
			xmPushButtonWidgetClass,
			titleAreaform,
			XmNx, 230,
			XmNy, 0,
			XmNwidth, 170,
			XmNheight, 27,
			RES_CONVERT( XmNlabelString, "Vert. Hierarchy" ),
			RES_CONVERT( XmNhighlightColor, "yellow" ),
			NULL );
	XtAddCallback( vertHierButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_vertHierButton,
		(XtPointer) UxTelepermContext );

	UxPutContext( vertHierButton, (char *) UxTelepermContext );


	/* Creation of orizHierButton */
	orizHierButton = XtVaCreateManagedWidget( "orizHierButton",
			xmPushButtonWidgetClass,
			titleAreaform,
			XmNx, 20,
			XmNy, 0,
			XmNwidth, 170,
			XmNheight, 27,
			RES_CONVERT( XmNlabelString, "Horiz. Hierarchy" ),
			NULL );
	XtAddCallback( orizHierButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_orizHierButton,
		(XtPointer) UxTelepermContext );

	UxPutContext( orizHierButton, (char *) UxTelepermContext );

	XtVaSetValues(previous,
			RES_CONVERT( XmNlabelPixmap, previousBMP ),
			NULL );

	XtVaSetValues(left,
			RES_CONVERT( XmNlabelPixmap, leftBMP ),
			NULL );

	XtVaSetValues(up,
			RES_CONVERT( XmNlabelPixmap, upBMP ),
			NULL );

	XtVaSetValues(right,
			RES_CONVERT( XmNlabelPixmap, rightBMP ),
			NULL );

	XtVaSetValues(swscreen,
			RES_CONVERT( XmNlabelPixmap, swscreenBMP ),
			NULL );

	XtVaSetValues(ackaud,
			RES_CONVERT( XmNlabelPixmap, ackaudBMP ),
			NULL );

	XtVaSetValues(ackal,
			RES_CONVERT( XmNlabelPixmap, ackalBMP ),
			NULL );

	XtVaSetValues(hardcopy,
			RES_CONVERT( XmNlabelPixmap, hardcopyBMP ),
			NULL );

	XtVaSetValues(help,
			RES_CONVERT( XmNlabelPixmap, helpBMP ),
			NULL );

	XtVaSetValues(processDisplay,
			RES_CONVERT( XmNlabelPixmap, "overview.bmp" ),
			NULL );

	XtVaSetValues(plantOverview,
			RES_CONVERT( XmNlabelPixmap, "overview.bmp" ),
			NULL );


	XtAddCallback( teleperm, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTelepermContext);


	return ( teleperm );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_teleperm( _UxUxParent, _UxPag, _Uxnome_display )
	swidget	_UxUxParent;
	AN_PAG	*_UxPag;
	unsigned char	*_Uxnome_display;
{
	Widget                  rtrn;
	_UxCteleperm            *UxContext;
	static int		_Uxinit = 0;

	UxTelepermContext = UxContext =
		(_UxCteleperm *) UxNewContext( sizeof(_UxCteleperm), False );

	UxParent = _UxUxParent;
	Pag = _UxPag;
	nome_display = _Uxnome_display;

	if ( ! _Uxinit )
	{
		_UxIfClassId = UxNewClassId();
		Uxteleperm_orizHier_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_orizHier_Name,
					_teleperm_orizHier );
		Uxteleperm_drawPush_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_drawPush_Name,
					_teleperm_drawPush );
		Uxteleperm_openStaz_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_openStaz_Name,
					_teleperm_openStaz );
		Uxteleperm_aggHeaderArea_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_aggHeaderArea_Name,
					_teleperm_aggHeaderArea );
		Uxteleperm_switchScreen_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_switchScreen_Name,
					_teleperm_switchScreen );
		Uxteleperm_moveleft_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_moveleft_Name,
					_teleperm_moveleft );
		Uxteleperm_moveup_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_moveup_Name,
					_teleperm_moveup );
		Uxteleperm_openTopProcDisplay_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_openTopProcDisplay_Name,
					_teleperm_openTopProcDisplay );
		Uxteleperm_navigation_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_navigation_Name,
					_teleperm_navigation );
		Uxteleperm_decorationToggle_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_decorationToggle_Name,
					_teleperm_decorationToggle );
		Uxteleperm_createCaiHeader_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_createCaiHeader_Name,
					_teleperm_createCaiHeader );
		Uxteleperm_createButtonPixmap_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_createButtonPixmap_Name,
					_teleperm_createButtonPixmap );
		Uxteleperm_moveroot_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_moveroot_Name,
					_teleperm_moveroot );
		Uxteleperm_closeOW_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_closeOW_Name,
					_teleperm_closeOW );
		Uxteleperm_close_allPage_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_close_allPage_Name,
					_teleperm_close_allPage );
		Uxteleperm_xaing_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_xaing_Name,
					_teleperm_xaing );
		Uxteleperm_refreshAllPageWidgets_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_refreshAllPageWidgets_Name,
					_teleperm_refreshAllPageWidgets );
		Uxteleperm_popupPage_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_popupPage_Name,
					_teleperm_popupPage );
		Uxteleperm_ridisegna_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_ridisegna_Name,
					_teleperm_ridisegna );
		Uxteleperm_gotopag_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_gotopag_Name,
					_teleperm_gotopag );
		Uxteleperm_xplot_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_xplot_Name,
					_teleperm_xplot );
		Uxteleperm_application_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_application_Name,
					_teleperm_application );
		Uxteleperm_previousPag_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_previousPag_Name,
					_teleperm_previousPag );
		Uxteleperm_isOldAlarmPage_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_isOldAlarmPage_Name,
					_teleperm_isOldAlarmPage );
		Uxteleperm_moveright_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_moveright_Name,
					_teleperm_moveright );
		Uxteleperm_chPage_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_chPage_Name,
					_teleperm_chPage );
		Uxteleperm_aggTitleArea_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_aggTitleArea_Name,
					_teleperm_aggTitleArea );
		Uxteleperm_aggListChild_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_aggListChild_Name,
					_teleperm_aggListChild );
		Uxteleperm_dispData_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_dispData_Name,
					_teleperm_dispData );
		Uxteleperm_closePag_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_closePag_Name,
					_teleperm_closePag );
		Uxteleperm_create_allPage_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_create_allPage_Name,
					_teleperm_create_allPage );
		Uxteleperm_WidgetSelect_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_WidgetSelect_Name,
					_teleperm_WidgetSelect );
		Uxteleperm_info_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_info_Name,
					_teleperm_info );
		Uxteleperm_dispTime_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_dispTime_Name,
					_teleperm_dispTime );
		Uxteleperm_vertHier_Id = UxMethodRegister( _UxIfClassId,
					Uxteleperm_vertHier_Name,
					_teleperm_vertHier );
		UxLoadResources( "teleperm.rf" );
		_Uxinit = 1;
	}

	{
		/* Per scelta pixmap a seconda dello screen */
		int numero_screen;
		
		/*XrmDatabase PagDb;*/
		char nome_pag[255];
		OlTreeObject curr_oltree;
		
		
		/* per gestione sinottico
		*/
		int dim[4];
		int num_b;
		extern Boolean leggi_file_bck();
		int *ind_list,nlist,i;
		
		
		/* variabili per risorse della drawing area
		*/
		int drawing_width,drawing_height;
		Pixel *drawing_background;
		Pixmap pix;
		
		
		
		/* inizializzazione 
		*/
		drawing_pixmap=0;
		numChildPagList=0;
		ChildPagList=NULL;
		screen_switched = False;
		
		pullMenuOn=False; 
		
		OrizMenuIsActive = False;
		VertMenuIsActive = False;
		
		modoPageAll=MODO_ALLARMI;
		
		pullDownActive=NULL;	/* Inizialize pointer to pullDownMenu */ 
		npagPulldown=0;
		if( !EsistePagina(Pag->nome) )
		{
		      printf("Error. File Page %s not exist.\n",Pag->nome);
		      return( NULL );
		}
		/********************************************
		Inizio inizializzazione var glob pagAll
		Questa parte viene eseguita solo alla prima
		apertura di una pag teleperm
		*********************************************/
		if(prima_apertura_teleperm)
		   {
		   /*
		   Setto a 0 la situazione vecchi allarmi
		   */
		   memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM));
		   /*
		   Inizializzo stato delle zone
		   */
		
		   for(i=0;i<NUMMAXZONE;i++)
			   {
			   zone_status[i]=0;
			   zone_status_old[i]=0;
		           }
		   num_zone=16; /* num_zone su layout grafico */
		
		   
		
		   last_zone_pressed=-1;      /* ultimo bottone-zona premuto */
		   zone_ko=-1;             /* zona gia' selezionata */
		   prima_apertura_teleperm=False;   
		   /*************************************************
		   Fine settaggio var globali per pagina ALLARMI
		   *************************************************/
		   }
		
		/*
		Calcolo la situazione delle fa con le selectable_zone
		*/
		num_telepag=0;
		recognize_fa();
		/*************************************************
		Fine settaggio var locali  per pagina ALLARMI
		*************************************************/
		
		/* file delle risorse della pagina da caricare
		*/
		   sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),Pag->nome);
		
		/* carico il db della pagina
		*/
		  if( (PagDb = XrmGetFileDatabase(nome_pag)) == NULL)
		  {
		      printf("Error. Cannot open page %s\n",nome_pag);
		      return(NULL);
		  }
		
		/* merge db della pagina e della applicazione (quello salvato su file)
		*/
		   XrmCombineFileDatabase( "ApplDb.res", &PagDb ,True);
		
		/* setto il display su PagDb 
		   NOTA come parametro display devo utilizzare quello del parent
		   perche la applicazioni e' multidisplay o mulriscreen.
		*/
		   XrmSetDatabase(XtDisplay(UxParent),PagDb);
		
		/* mi serve solo per caricare il time_ref
		*/
		if(!GetResTopLevel(UxParent,&top_x,&top_y,&top_width,&top_height,&time_ref,
				&top_tipo,&top_descrizione))
			return(False);
		
		/* recupero le risorse della drawing area
		*/
		   if(!GetResDrawing(UxParent,&drawing_width,&drawing_height,&drawing_background,&drawing_pixmap))
				return(False);
		
		operazione_attiva=OPERAZIONE_NOP;
		rtrn = _Uxbuild_teleperm();
		UxPutClassCode( teleperm, _UxIfClassId );

		screen_selezionato = XDefaultScreen(XtDisplay(rtrn));
		elenco_display[0].scr[screen_selezionato].wteleperm = rtrn;
		
		
		printf("screen default = %d\n",screen_selezionato);
		printf("wteleperm[0] - %d\n",elenco_display[0].scr[0].wteleperm);
		printf("wteleperm[1] - %d\n",elenco_display[0].scr[1].wteleperm);
		
		/* provo a impostare le heigth e la width in base alle dimensioni dello screen
		*/
		{
		   int h,w;
		  
		  h = HeightOfScreen( XtScreen(rtrn) );
		  w = WidthOfScreen( XtScreen(rtrn) );
		  
		  printf("Set dimensioni dello screen w=%d h=%d\n",w,h);
		 
		  XtVaSetValues( rtrn, 
		                 XmNheight,h,
		                 XmNwidth, w,
		                 NULL);
		
		  XtVaGetValues( rtrn, 
		                 XmNheight,&h,
		                 XmNwidth, &w,
		                 NULL);
		
		  printf("Get dimensioni della pagina w=%d h=%d\n",w,h);
		
		}
		
		teleperm_refreshTime(Ora);
		
		/* setto i pixmap sui bottoni dlla pagina teleperm 
		   i .bmp so trovano in $LEGOCAD_ICO 
		*/
		
		path_icone=(char *)getenv("LEGOCAD_ICO");
		
		if(path_icone==NULL)
		{
		   printf("\nERROR Environment variable LEGOCAD_ICO is not defined. Exit.\n");
		   exit(1);
		}
		
		sprintf(icon,"%s/overview.bmp",path_icone);
		UxPutStrRes(plantOverview,XmNlabelPixmap,icon);
		UxPutStrRes(processDisplay,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/previous.bmp",path_icone);
		UxPutStrRes(previous,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/left.bmp",path_icone);
		UxPutStrRes(left,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/up.bmp",path_icone);
		UxPutStrRes(up,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/right.bmp",path_icone);
		UxPutStrRes(right,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/cscreen.bmp",path_icone);
		UxPutStrRes(swscreen,XmNlabelPixmap,icon);
		UxPutStrRes(swscreen,XmNlabelInsensitivePixmap,icon);
		
		sprintf(icon,"%s/ackal.bmp",path_icone);
		UxPutStrRes(ackal,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/ackaud.bmp",path_icone);
		UxPutStrRes(ackaud,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/hardcopy.bmp",path_icone);
		UxPutStrRes(hardcopy,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/help.bmp",path_icone);
		UxPutStrRes(help,XmNlabelPixmap,icon);
		
		sprintf(icon,"%s/logon.bmp",path_icone);
		UxPutStrRes(logoff,XmNlabelPixmap,icon);
		
		
		
		/* setto il background della drawingArea
		*/
		if(drawing_pixmap)
			{
			set_something(drawingArea,XmNbackgroundPixmap,drawing_pixmap);
			}
		else
			set_something(drawingArea,XmNbackground,drawing_background);
		
		/* inizia la gestione della pagina come sinottico
		*/
		
		/*
		  inizializza la regione di ridisegno
		*/
		if(Pag->sfondo==NULL)	
		   leggi_file_bck(UxParent,Pag->nome,"bkg",&(Pag->sfondo),dim);
		else
		   AllocaColoriSfondo(UxParent,Pag->sfondo);
		
		
		region_sin=NULL;
		
		if(!CreaPagina(drawingArea,&lista_wid, &num_wid))
			return(NULL);
		
		if((key_refresh=InsElencoPagine(Pag->nome,lista_wid,num_wid,time_ref)) == -1)
			return(NULL);
		
		/* set del timer di refresh e della routine di refresh (teleperm_refreshPag)
		*/
		timer_refresh = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (teleperm),
		            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm );
		
		
		
		/* elimino le decorazioni di window manager
		*/
		teleperm_decorationToggle(rtrn,&UxEnv);
		
		/* aggiorno la header area
		*/
		teleperm_aggHeaderArea(rtrn,&UxEnv);
		
		/* aggiorno la title area
		*/
		teleperm_aggTitleArea(teleperm,&UxEnv);
		
		/* recupero le informazioni sulla pagina corrente
		*/
		/* Carlo. provo la gestione di pagine senza gerarchia
		if( OlTreeGetPage(root_oltree,&curr_oltree,&progress,&pos_pag_curr,Pag->gerarchia) == False )
		{
		   printf("Error retrieving hierarchy information for this page\n");
		   return(False);
		}
		*/
		
		if( strcmp(Pag->gerarchia,"-1,-1,-1,-1,-1,-1") != NULL)
		{
		   if( OlTreeGetPage(root_oltree,&curr_oltree,&progress,&pos_pag_curr,Pag->gerarchia) == False )
		   {
		      printf("Error retrieving hierarchy information for this page\n");
		      return(False);
		   }
		}
		else
		{
		   printf("Pagina fuori gerarchia %s\n",Pag->nome);
		   for(i=0;i<totale_pagine;i++)
		      if( strcmp(Pag->nome,pagine[i].nome)==NULL)
		      {
		          pos_pag_curr=i;
		          break;
		      }
		}
		                
		
		if( elenco_display[0].num_screens < 2 )
		   set_something(swscreen,XmNsensitive,False);
		
		pos_pag_new = pos_pag_curr;
		
		/* Creo caiHeader per configurazione con scada */
		if(scada_on)
			{
			teleperm_createCaiHeader(teleperm,&UxEnv);
		
			teleperm_createButtonPixmap(teleperm,&UxEnv);
		
			}
		
		else
			{	
			set_something(plantButton,XmNsensitive,False);
			/*set_something(orizHierButton,XmNsensitive,False);
			set_something(vertHierButton,XmNsensitive,False);*/
			set_something(isa,XmNsensitive,False);
			}
		/*
		Se mmi senza -Topologia, disattiva bottoni Plot ed Aing
		*/ 
		if(!topologia_on)
		  {
		  set_something(plot,XmNsensitive,False);
		  set_something(aing,XmNsensitive,False);
		  }
		else
		  {
		  /*
		  Per plot Aing Info
		  */
		  get_something(menuSystem_csbutt,XmNbackground,&def_col_menuSystem);
		  }
		InfoUsed=False;
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

