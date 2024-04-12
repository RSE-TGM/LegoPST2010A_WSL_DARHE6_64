/*******************************************************************************
       OperatingWindow.c
       (Generated from interface file OperatingWindow.i)
       Associated Resource file: OperatingWindow.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/DrawingA.h>
#include <Xm/ScrolledW.h>
#include <Xm/SeparatoG.h>
#include <Xm/Label.h>
#include <Xm/ArrowB.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include <stdlib.h>
#include <Xm/Protocols.h>
#include <time.h>
#include <Xm/MwmUtil.h>
#include <Cs/Cs.h>
#include <Xm/RowColumn.h>

#ifndef DESIGN_TIME
#include <Xl/XlP.h>
#endif


#include <Ol/OlPert.h>



#include <Xl/XlIndicTelep.h>
#include <Xl/XlPictograph.h>
#include <Xl/XlOperableKeys.h>
#include <Xl/XlChangePage.h>

#include "other.h"

#include <Ol/OlTree.h>	         /* per gestione OlTree teleperm */
#include <Ol/OlDatabasePunti.h>  /* per gestione DatabasePunti */
#include <Cs/Cs.h>
#include <Xl/XlCaiAll.h>
/* offset aggiunti alla x,y dello widget
   che crea la OW
*/
#define OWXOFFSET 30      
#define OWYOFFSET 100     

/* altezza di default window extension2
   utilizzata se non specificata da risorsa
   height_ext2
*/
#define DEFAULT_HEXT2 100

#define TIMEOUTMINIASD  40  /* secondi per timeOut */
extern OlDatabasePuntiObject database_simulatore;

#define HEIGHTASDSTEP	32 /* altezza di ogni cella rowColumn allarmi miniASD */ 
#define HEIGHTASDLABEL	29 /* altezza di ogni label allarmi miniASD */
#define ALLARMI          0
#define MANUAL           1 
/* */
extern Boolean EsistePagina();
static void OperatingWindow_refreshPag();
static void no_closeMWM();
static Widget CreoOggettiOW();
static Boolean CreaPaginaOW();

extern AN_PAG *pagine;
extern PAGINE_APERTE *el_pagine;
extern int num_el_pagine;


static	int _UxIfClassId;
int	UxOperatingWindow_reqAlarms_Id = -1;
char*	UxOperatingWindow_reqAlarms_Name = "reqAlarms";
int	UxOperatingWindow_CreateExt1_Id = -1;
char*	UxOperatingWindow_CreateExt1_Name = "CreateExt1";
int	UxOperatingWindow_OpenExt1_Id = -1;
char*	UxOperatingWindow_OpenExt1_Name = "OpenExt1";
int	UxOperatingWindow_OpenExt2_Id = -1;
char*	UxOperatingWindow_OpenExt2_Name = "OpenExt2";
int	UxOperatingWindow_configBottoni_Id = -1;
char*	UxOperatingWindow_configBottoni_Name = "configBottoni";
int	UxOperatingWindow_chPage_Id = -1;
char*	UxOperatingWindow_chPage_Name = "chPage";
int	UxOperatingWindow_SetDescr_Id = -1;
char*	UxOperatingWindow_SetDescr_Name = "SetDescr";
int	UxOperatingWindow_decorationToggle_Id = -1;
char*	UxOperatingWindow_decorationToggle_Name = "decorationToggle";
int	UxOperatingWindow_DestroyExt1_Id = -1;
char*	UxOperatingWindow_DestroyExt1_Name = "DestroyExt1";
int	UxOperatingWindow_closeOW_Id = -1;
char*	UxOperatingWindow_closeOW_Name = "closeOW";
int	UxOperatingWindow_debug_Id = -1;
char*	UxOperatingWindow_debug_Name = "debug";
int	UxOperatingWindow_abilitaOpKeys_Id = -1;
char*	UxOperatingWindow_abilitaOpKeys_Name = "abilitaOpKeys";
int	UxOperatingWindow_ricMiniASD_Id = -1;
char*	UxOperatingWindow_ricMiniASD_Name = "ricMiniASD";

#ifndef OperatingWindow_reqAlarms
#define OperatingWindow_reqAlarms( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_reqAlarms_Id,\
			UxOperatingWindow_reqAlarms_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_CreateExt1
#define OperatingWindow_CreateExt1( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_CreateExt1_Id,\
			UxOperatingWindow_CreateExt1_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_OpenExt1
#define OperatingWindow_OpenExt1( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_OpenExt1_Id,\
			UxOperatingWindow_OpenExt1_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_OpenExt2
#define OperatingWindow_OpenExt2( UxThis, pEnv, drawing_area ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_OpenExt2_Id,\
			UxOperatingWindow_OpenExt2_Name)) \
		( UxThis, pEnv, drawing_area )
#endif

#ifndef OperatingWindow_configBottoni
#define OperatingWindow_configBottoni( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_configBottoni_Id,\
			UxOperatingWindow_configBottoni_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_chPage
#define OperatingWindow_chPage( UxThis, pEnv, w, nomePg, tipoApertura ) \
	((void(*)())UxMethodLookup(UxThis, UxOperatingWindow_chPage_Id,\
			UxOperatingWindow_chPage_Name)) \
		( UxThis, pEnv, w, nomePg, tipoApertura )
#endif

#ifndef OperatingWindow_SetDescr
#define OperatingWindow_SetDescr( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_SetDescr_Id,\
			UxOperatingWindow_SetDescr_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_decorationToggle
#define OperatingWindow_decorationToggle( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_decorationToggle_Id,\
			UxOperatingWindow_decorationToggle_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_DestroyExt1
#define OperatingWindow_DestroyExt1( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_DestroyExt1_Id,\
			UxOperatingWindow_DestroyExt1_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_closeOW
#define OperatingWindow_closeOW( UxThis, pEnv ) \
	((Boolean(*)())UxMethodLookup(UxThis, UxOperatingWindow_closeOW_Id,\
			UxOperatingWindow_closeOW_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_debug
#define OperatingWindow_debug( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_debug_Id,\
			UxOperatingWindow_debug_Name)) \
		( UxThis, pEnv )
#endif

#ifndef OperatingWindow_abilitaOpKeys
#define OperatingWindow_abilitaOpKeys( UxThis, pEnv, tipo_opkey, stato ) \
	((Boolean(*)())UxMethodLookup(UxThis, UxOperatingWindow_abilitaOpKeys_Id,\
			UxOperatingWindow_abilitaOpKeys_Name)) \
		( UxThis, pEnv, tipo_opkey, stato )
#endif

#ifndef OperatingWindow_ricMiniASD
#define OperatingWindow_ricMiniASD( UxThis, pEnv, tipo_allarmi ) \
	((int(*)())UxMethodLookup(UxThis, UxOperatingWindow_ricMiniASD_Id,\
			UxOperatingWindow_ricMiniASD_Name)) \
		( UxThis, pEnv, tipo_allarmi )
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
	Widget	UxOperatingWindow;
	Widget	UxmainForm;
	Widget	UxfooterForm;
	Widget	UxfEjecutar;
	Widget	UxEjecutar;
	Widget	UxfIMP;
	Widget	UxIMP;
	Widget	UxfCerrar;
	Widget	UxCerrar;
	Widget	UxheaderForm;
	Widget	UxbOpenExt1;
	Widget	UxidcodeLabel;
	Widget	UxfuncodeLabel;
	Widget	UxseparatorGadget2;
	Widget	UxseparatorGadget3;
	Widget	Uxextension1;
	Widget	Uxdummy_ric_all;
	Widget	UxscrolledAlarmMiniASD;
	Widget	UxscrolledManualMiniASD;
	Widget	Uxdummy_ric_manual;
	Widget	UxdrawingAreaOW;
	Position	UxowX;
	Position	UxowY;
	Position	UxowH;
	int	Uxext1Aperta;
	int	Uxext2Aperta;
	XrmDatabase	UxOwDb;
	XtIntervalId	UxOWtimer_refresh;
	int	UxOWkey_refresh;
	WidgetList	UxOWlista_wid;
	int	UxOWnum_wid;
	int	UxOWtime_ref;
	int	UxOWtop_x;
	int	UxOWtop_y;
	int	UxOWtop_width;
	int	UxOWtop_height;
	int	UxOWtop_tipo;
	unsigned char	*UxOWtop_descrizione;
	int	Uxdrawing_width;
	int	Uxdrawing_height;
	Pixel	*Uxdrawing_background;
	int	Uximp_premuto;
	Widget	UxlastWexec;
	BCK_OBJ	*Uxbkg_ow;
	Region	Uxregion_ow;
	int	UxHEXT2;
	Pixmap	Uxdrawing_pixmap;
	int	UxnumDetail;
	Widget	*UxDetail;
	Boolean	Uxflag_aperture;
	unsigned char	*Uxallarm_data;
	unsigned char	*Uxmanual_data;
	short	Uxindice;
	unsigned char	*Uxgerarchie;
	Widget	UxformAllarm;
	Widget	UxformManual;
	Widget	UxrowColumnAllarmCai;
	Widget	UxrowColumnManualCai;
	Widget	UxrowColumnAllarm;
	Widget	UxrowColumnManual;
	Widget	*Uxall_caiAll_form;
	Widget	*Uxall_caiMan_form;
	Widget	*Uxall_caiAll;
	Widget	*Uxall_caiMan;
	Widget	*Uxall_label;
	Widget	*Uxman_label;
	int	Uxnum_allarm;
	int	Uxnum_manual;
	unsigned char	*Uxpath_icone;
	unsigned char	Uxicon[255];
	swidget	UxUxParent;
	Widget	Uxopw;
	AN_PAG	*UxOWpag;
	XrmDatabase	UxParentDb;
} _UxCOperatingWindow;

static _UxCOperatingWindow     *UxOperatingWindowContext;
#define OperatingWindow         UxOperatingWindowContext->UxOperatingWindow
#define mainForm                UxOperatingWindowContext->UxmainForm
#define footerForm              UxOperatingWindowContext->UxfooterForm
#define fEjecutar               UxOperatingWindowContext->UxfEjecutar
#define Ejecutar                UxOperatingWindowContext->UxEjecutar
#define fIMP                    UxOperatingWindowContext->UxfIMP
#define IMP                     UxOperatingWindowContext->UxIMP
#define fCerrar                 UxOperatingWindowContext->UxfCerrar
#define Cerrar                  UxOperatingWindowContext->UxCerrar
#define headerForm              UxOperatingWindowContext->UxheaderForm
#define bOpenExt1               UxOperatingWindowContext->UxbOpenExt1
#define idcodeLabel             UxOperatingWindowContext->UxidcodeLabel
#define funcodeLabel            UxOperatingWindowContext->UxfuncodeLabel
#define separatorGadget2        UxOperatingWindowContext->UxseparatorGadget2
#define separatorGadget3        UxOperatingWindowContext->UxseparatorGadget3
#define extension1              UxOperatingWindowContext->Uxextension1
#define dummy_ric_all           UxOperatingWindowContext->Uxdummy_ric_all
#define scrolledAlarmMiniASD    UxOperatingWindowContext->UxscrolledAlarmMiniASD
#define scrolledManualMiniASD   UxOperatingWindowContext->UxscrolledManualMiniASD
#define dummy_ric_manual        UxOperatingWindowContext->Uxdummy_ric_manual
#define drawingAreaOW           UxOperatingWindowContext->UxdrawingAreaOW
#define owX                     UxOperatingWindowContext->UxowX
#define owY                     UxOperatingWindowContext->UxowY
#define owH                     UxOperatingWindowContext->UxowH
#define ext1Aperta              UxOperatingWindowContext->Uxext1Aperta
#define ext2Aperta              UxOperatingWindowContext->Uxext2Aperta
#define OwDb                    UxOperatingWindowContext->UxOwDb
#define OWtimer_refresh         UxOperatingWindowContext->UxOWtimer_refresh
#define OWkey_refresh           UxOperatingWindowContext->UxOWkey_refresh
#define OWlista_wid             UxOperatingWindowContext->UxOWlista_wid
#define OWnum_wid               UxOperatingWindowContext->UxOWnum_wid
#define OWtime_ref              UxOperatingWindowContext->UxOWtime_ref
#define OWtop_x                 UxOperatingWindowContext->UxOWtop_x
#define OWtop_y                 UxOperatingWindowContext->UxOWtop_y
#define OWtop_width             UxOperatingWindowContext->UxOWtop_width
#define OWtop_height            UxOperatingWindowContext->UxOWtop_height
#define OWtop_tipo              UxOperatingWindowContext->UxOWtop_tipo
#define OWtop_descrizione       UxOperatingWindowContext->UxOWtop_descrizione
#define drawing_width           UxOperatingWindowContext->Uxdrawing_width
#define drawing_height          UxOperatingWindowContext->Uxdrawing_height
#define drawing_background      UxOperatingWindowContext->Uxdrawing_background
#define imp_premuto             UxOperatingWindowContext->Uximp_premuto
#define lastWexec               UxOperatingWindowContext->UxlastWexec
#define bkg_ow                  UxOperatingWindowContext->Uxbkg_ow
#define region_ow               UxOperatingWindowContext->Uxregion_ow
#define HEXT2                   UxOperatingWindowContext->UxHEXT2
#define drawing_pixmap          UxOperatingWindowContext->Uxdrawing_pixmap
#define numDetail               UxOperatingWindowContext->UxnumDetail
#define Detail                  UxOperatingWindowContext->UxDetail
#define flag_aperture           UxOperatingWindowContext->Uxflag_aperture
#define allarm_data             UxOperatingWindowContext->Uxallarm_data
#define manual_data             UxOperatingWindowContext->Uxmanual_data
#define indice                  UxOperatingWindowContext->Uxindice
#define gerarchie               UxOperatingWindowContext->Uxgerarchie
#define formAllarm              UxOperatingWindowContext->UxformAllarm
#define formManual              UxOperatingWindowContext->UxformManual
#define rowColumnAllarmCai      UxOperatingWindowContext->UxrowColumnAllarmCai
#define rowColumnManualCai      UxOperatingWindowContext->UxrowColumnManualCai
#define rowColumnAllarm         UxOperatingWindowContext->UxrowColumnAllarm
#define rowColumnManual         UxOperatingWindowContext->UxrowColumnManual
#define all_caiAll_form         UxOperatingWindowContext->Uxall_caiAll_form
#define all_caiMan_form         UxOperatingWindowContext->Uxall_caiMan_form
#define all_caiAll              UxOperatingWindowContext->Uxall_caiAll
#define all_caiMan              UxOperatingWindowContext->Uxall_caiMan
#define all_label               UxOperatingWindowContext->Uxall_label
#define man_label               UxOperatingWindowContext->Uxman_label
#define num_allarm              UxOperatingWindowContext->Uxnum_allarm
#define num_manual              UxOperatingWindowContext->Uxnum_manual
#define path_icone              UxOperatingWindowContext->Uxpath_icone
#define icon                    UxOperatingWindowContext->Uxicon
#define UxParent                UxOperatingWindowContext->UxUxParent
#define opw                     UxOperatingWindowContext->Uxopw
#define OWpag                   UxOperatingWindowContext->UxOWpag
#define ParentDb                UxOperatingWindowContext->UxParentDb



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_OperatingWindow();

/*******************************************************************************
Declarations of methods
*******************************************************************************/

static int	_OperatingWindow_reqAlarms();
static int	_OperatingWindow_CreateExt1();
static int	_OperatingWindow_OpenExt1();
static int	_OperatingWindow_OpenExt2();
static int	_OperatingWindow_configBottoni();
static void	_OperatingWindow_chPage();
static int	_OperatingWindow_SetDescr();
static int	_OperatingWindow_decorationToggle();
static int	_OperatingWindow_DestroyExt1();
static Boolean	_OperatingWindow_closeOW();
static int	_OperatingWindow_debug();
static Boolean	_OperatingWindow_abilitaOpKeys();
static int	_OperatingWindow_ricMiniASD();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* 
routine per aprire una pagina da oggetto cambio pagina interno alla OW
*/
void OperatingWindow_OpenPage(drawing,nomePag,tipoOpen)
Widget drawing;
char *nomePag;
int tipoOpen;
{
   /* salvo il context
   */
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;

   /* recupero il context
   */
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( drawing );

   OperatingWindow_chPage(OperatingWindow,&UxEnv,drawing,nomePag,tipoOpen);

   /* rispristino il context salvato
   */ 
   UxOperatingWindowContext = UxSaveCtx;
}


/* interfaccia per apertura extension2
   w = indice di widget tipo ChangePage posto
      sulla OperatingWindow di tipo OPEN_EXT2
*/
void apriExt2( Widget wid )
{   
   /* salvo il context
   */
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;

   /* recupero il context
   */
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( wid );

   /* chiamo la funzione di apertura della Extension2
   */ 
   OperatingWindow_OpenExt2(OperatingWindow,&UxEnv, drawingAreaOW );

   /* rispristino il context salvato
   */ 
   UxOperatingWindowContext = UxSaveCtx;
}

/* interfaccia esterna per chiusura della OW
*/
Boolean OW_close( Widget OW)
{
   OperatingWindow_closeOW(OW,&UxEnv);
   return(True);
}

/*******************************************************
 * store pert
 *
 * CB associata agli operable Keys di tipo OPKEY_EXEC
 *
 * stabilisce quale perturbazione deve essere inviata 
 * dalla activate callback del tasto ejecutar
 * 
 *******************************************************/
void store_pert(Widget w)
{
   Pixel bg_butt;
   /* salvo il context
   */
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;

   /* recupero il context
   */
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( XtParent(w) );
 
   if( w != NULL )
   {   
      /* memorizzo l'indice di Widget relativo all'OperableKeys 
      di tipo EXEC che e' stato premuto e rendo sensitive il
      bottone Ejecutar
      */
      lastWexec = w;

      XtVaGetValues( lastWexec,XlNhstateBg,&bg_butt,NULL);

      XtVaSetValues(Ejecutar,
                 XmNsensitive,True,
                 XmNbackground,bg_butt,
                 NULL);
   }

   /* rispristino il context salvato
   */ 
   UxOperatingWindowContext = UxSaveCtx;
  
}

/*******************
 *
 ********************/
static void no_closeMWM(UxWidget,UxClientData,UxCallbackArg)
Widget UxWidget;
XtPointer UxClientData,UxCallbackArg;
{
   return;
}

/*************************************************
 * refresh della pagina tipo Operating Window
 *************************************************/

static void OperatingWindow_refreshPag(wid)
swidget wid;
{
   int i;
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;
   float simTime;

/* recupero il context 
*/
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( wid );

  if(!OlSetDataPage(database_simulatore,OWkey_refresh))
  {
        printf("Error in refresh\n");
        return;
  }

  if(OlGetDataStatus(database_simulatore,OWkey_refresh))  
        {
        XlRefreshWidget(OWlista_wid,OWnum_wid);
        if(num_allarm>0 && num_allarm <17)
           XlRefreshWidget(all_caiAll,num_allarm);
        if(num_manual>0 && num_manual <17)
           XlRefreshWidget(all_caiMan,num_manual);
        }
   if(!OlUnsetDataPage(database_simulatore,OWkey_refresh))
   {
      printf("Error in refresh\n");
      return;
   }

/*
        carica il timer per il refresh
*/
      OWtimer_refresh = XtAppAddTimeOut (
            XtWidgetToApplicationContext (OperatingWindow),
            (unsigned long) (OWtime_ref*100) ,OperatingWindow_refreshPag, OperatingWindow);

/* switch del context
*/
   UxOperatingWindowContext = UxSaveCtx;


}

/*******************************************************************************
       The following are method functions.
*******************************************************************************/

static int	Ux_reqAlarms( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	char appo_gerarchia[LUN_GERAR];
	
	int i;
	
	/*
	Metodo per preparare la gerarchia secondo 
	modalita' tabelle SCADA (XtCalloc imposta da AIC che non sembra digerire array di 
	unsigned char come var specifiche)
	*/
	if((gerarchie=(unsigned char *)XtCalloc(N_GERARCHIE,sizeof(unsigned char)))==NULL)
	   {
	    printf("ERROR: impossible to allocate memory for gerarchia miniASD\n");
	    return(-1);
	   }
	strcpy(appo_gerarchia,OWpag->gerarchia);
	printf("gerarchia=%s \n",appo_gerarchia);
	gerarchie[0]=(unsigned char)atoi((strtok(appo_gerarchia,",")));
	
	for(i=1;i<N_GERARCHIE;i++)
	   {
	   gerarchie[i]=(char unsigned) atoi((strtok((char *) NULL,",")));   
	
	   }
	printf("gerarchia=\n");
	
	for(i=0;i<N_GERARCHIE;i++)
	   {
	   printf(" %d ",gerarchie[i]);
	   }
	printf("\n");
	
	/* 
	Chiamo metodo per creazione shm associate miniASD
	Viene associato un indice alla O.W.
	Tale indice e' l' indice nell' array delle shm associate al miniASD.
	Viene anche utilizzato per la distruzione della shm associata
	*/
	
	if (OlInserisci_shmMiniASD(database_simulatore,&allarm_data,&manual_data,&indice)<0)
	   {
	   printf("richiediAllarmiMiniASD:FALLITA creazione shm per ASD\n");
	   return(-1);
	   }
	
	
	/*
	Chiamo metodo Ol per richiesta allarmi a client_scada
	*/
	
	if(!OlRichiediAllarmiMiniASD(database_simulatore,gerarchie,indice,MINIASD_ALARM_REQ,ALL_M))
	   {
	   printf("ERROR: Impossible to send request alarms ASD to client_scada\n");
	   return(-1);
	   }
	/*
	Chiamo metodo Ol per richiesta manual a client_scada
	*/
	
	if(!OlRichiediAllarmiMiniASD(database_simulatore,gerarchie,indice,MINIASD_MANUAL_REQ,ALL_M))
	   {
	   printf("ERROR: Impossible to send request alarms ASD to client_scada\n");
	   return(-1);
	   }
	
	return(1);
}

static int	_OperatingWindow_reqAlarms( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_reqAlarms( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_CreateExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int i;
	DATI_ALLARMI_SHM dati_allarm;
	DATI_ALLARMI_SHM dati_manual;
	DATI_ALLARMI_SHM *p_allarm_data;
	Widget sb;
	int increment,maximum,minimum,page_incr,slider_size,value;
	
	/* Var di appoggio per stringhe per widge*/
	char nomeWidget[256],appo_descr[256]; 
	char descr_token[3][256];
	char *str;
	char *tipo_cai; /* punt. tipo di Cai */
	
	XrmSetDatabase(XtDisplay((Widget)UxThis),OwDb);
	/* 
	Verfica su num_allarm e num_manual
	*/
	
	num_allarm =0;  /* provvisorio per DEBUG */
	num_manual=0;
	
	if(num_allarm || num_manual)
	   {
	   fprintf(stderr,"WARNING: num_allarm=%d e num_manual=%d not zero\n",
	           num_allarm,num_manual);
	   return(-1);
	   }
	
	
	
	/*
	Attendo che il client_scada abbia messo i dati nelle shm e li copi poi 
	nelle variabili dati_allarm dati_manual
	La gestione e' affidata ad un semaforo.
	*/
	if(!OlGetDatiMiniASD(database_simulatore,&dati_allarm,&dati_manual,indice))
	   {
	   fprintf(stderr,"WARNING: Impossible to retrieve valid data for miniASD\n");
	   num_allarm=0;
	   num_manual=0;
	   }
	else
	   {
	   num_allarm=dati_allarm.n_all;
	   num_manual=dati_manual.n_all;
	   }
	
	printf("num_allarm=%d\n",num_allarm);
	printf("num_manual=%d\n",num_manual);
	
	/*
	Abilito bottoni di riconoscimento solo se il No di all>0
	*/
	if (num_allarm > 0)
	    set_something(dummy_ric_all,XmNsensitive,True);
	else 
	    set_something(dummy_ric_all,XmNsensitive,False);
	    
	if (num_manual > 0)
	    set_something(dummy_ric_manual,XmNsensitive,True);
	else 
	    set_something(dummy_ric_manual,XmNsensitive,False);
	/*
	Spazio per allocazione dinamica oggetti per miniASD
	*/
	if ( (all_caiAll_form = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: all_caiAll_form");
	       return(-1);
	       }
	if ( (all_label = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: all_label");
	       return(-1);
	       }
	if ( (all_caiAll = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: all_caiAll");
	       return(-1);
	       }
	
	
	if ( (all_caiMan_form = (Widget *) XtCalloc(1, num_manual* sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: all_caiMan_form");
	       return(-1);
	       }
	if ( (man_label = (Widget *) XtCalloc(1, num_manual * sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: man_label");
	       return(-1);
	       }
	if ( (all_caiMan = (Widget *) XtCalloc(1, num_manual * sizeof(Widget)) )
	                       == NULL)
	       {
	       fprintf(stderr," OW:Error in malloc: all_caiMan");
	       return(-1);
	       }
	
	/*
	Vado a costruire gli oggetti contenuti nelle scrolled Window
	*/
	
	/*
	Form entro scrolled window
	*/
	       formAllarm = XtVaCreateManagedWidget( "formAllarm",
	                        xmFormWidgetClass,
	                        scrolledAlarmMiniASD,
	                        /*XmNwidth, 700,*/
	                        XmNheight, HEIGHTASDSTEP*num_allarm,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 0,
	                        XmNy, 0,
	                       /* RES_CONVERT( XmNbackground, "midnight blue" ),*/
	                        NULL );
	        UxPutContext( formAllarm, (char *) UxOperatingWindowContext );
	/*
	RowColumn per contenitori CAi
	*/
	
	       rowColumnAllarmCai = XtVaCreateManagedWidget( "rowColumnAllarmCai",
	                        xmRowColumnWidgetClass,
	                        formAllarm,
	                        /*XmNwidth, 30, */
	                        XmNx, 0,
	                        XmNy, 0,
	                       /* RES_CONVERT( XmNbackground, "cyan" ), */
	                        XmNadjustLast, FALSE,
	                        XmNadjustMargin, FALSE,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNleftOffset, 0,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 0,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        NULL );
	        UxPutContext( rowColumnAllarmCai, (char *) UxOperatingWindowContext );
	/*
	rowColumn per contenere stringhe allarmi
	*/
	rowColumnAllarm=XtVaCreateManagedWidget( "rowColumnAllarm",
	                        xmRowColumnWidgetClass,
	                        formAllarm,
	                       /* XmNwidth, 600,*/
	                        XmNheight, HEIGHTASDSTEP*num_allarm,
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 0,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftWidget, rowColumnAllarmCai,
	                        /*RES_CONVERT( XmNbackground, "forest green"),*/
	                        NULL );
	        UxPutContext( rowColumnAllarm, (char *) UxOperatingWindowContext );
	/*
	Parte per costruzione oggetti allocati dinamicamente
	*/
	for(i=0;i<num_allarm;i++)
	   {
	
	/*
	Vado a ricavare la stringa che scrivero' nella label
	*/
	strcpy(appo_descr,dati_allarm.descr[i]);
	str=strtok(appo_descr,"$");
	if(str)
	   {
	   str=strtok((char *)NULL,"|");
	   str++;             /* salto il tipo di allarme */
	   while(*str==' ')   /* salto spazi vuoti che SCADA spedisce */
	      str++;
	   if(str)
	      strcpy(descr_token[0],str);
	   else 
	      strcpy(descr_token[0],"");
	   
	   str=strtok((char *)NULL,"|");
	   if(str)
	      strcpy(descr_token[1],str);
	   else
	      strcpy(descr_token[1],"");
	   }
	   strcpy(descr_token[2],dati_allarm.data[i]);
	  
	   sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s",41,41,descr_token[0],10,10,
	             descr_token[1],10,10,descr_token[2]);
	
	/*printf("label=%s\n",appo_descr);*/
	
	   strcpy(nomeWidget,"");
	   sprintf(nomeWidget,"%d",i);
	   strcat(nomeWidget,"_allLabelASD");
	
	       all_label[i] = XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        rowColumnAllarm,
	                        XmNx, 100,
	                        XmNy, 40,
	                        XmNrecomputeSize, FALSE,
	                        /*XmNwidth, 600,*/
	                        XmNheight, 29,
	                        /*XmNfontList, UxConvertFontList( "courier_bold10" ),*/
	                        RES_CONVERT( XmNlabelString, appo_descr ),
	                        NULL );
	        UxPutContext( all_label[i], (char *) UxOperatingWindowContext  );
	/*
	Parte per inserimento form per cai
	*/ 
	   strcpy(nomeWidget,"");
	   sprintf(nomeWidget,"%d",i);
	   strcat(nomeWidget,"_formCaiAllASD");
	
	   all_caiAll_form[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmFormWidgetClass,
	                        rowColumnAllarmCai,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNheight, 29,
	                        XmNwidth, 29,
	                        /*RES_CONVERT( XmNbackground, "white"),*/
	                        NULL );
	        UxPutContext( all_caiAll_form[i], (char *) UxOperatingWindowContext  );
	/*
	Parte per inserimento CAI
	*/
	       strcpy(nomeWidget,"");
	       sprintf(nomeWidget,"%d",i);
	       strcat(nomeWidget,"_CaiAll");
	/*
	Determino il tipo di Cai che e' la  lettera dopo $ del name_all 
	*/
	       tipo_cai=strchr(dati_allarm.descr[i],'$');
	       if(!tipo_cai)
	           {
	           fprintf(stderr,"WARNING:Impossble to determine CAI[%d] type\n",i);
	           }
	
	       all_caiAll[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xlCaiAllWidgetClass,
	                        all_caiAll_form[i],
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNheight, 20,
	                        XmNwidth, 20,
	                        XmNtopAttachment,XmATTACH_FORM,
	                        XmNleftAttachment,XmATTACH_FORM,
#ifndef DESIGN_TIME
	                        XlNconfig, False,
#endif
	                        XlNtipoCaiAll,(int)( *(tipo_cai+1) ),
	                        
	                        XlNstatus, (int)dati_allarm.emission[i],
	                        NULL );
	
	        UxPutContext( all_caiAll[i], (char *) UxOperatingWindowContext );
	                                                                      
	                                               
	   }/* end for num_allarm */
	
	/*
	Setto database dei punti per CaiAll
	*/
	OlSetDatabasePunti(all_caiAll,num_allarm,database_simulatore);
	
	/*
	Parte per gestione (parziale) scrollbar 
	*/
	XtVaGetValues(scrolledAlarmMiniASD,XmNverticalScrollBar,&sb,NULL);
	
	XtVaGetValues( sb,
	              XmNincrement, &increment,
	              XmNmaximum, &maximum,
	              XmNminimum,   &minimum,
	              XmNpageIncrement, &page_incr,
	              XmNsliderSize, &slider_size,
	              XmNvalue, &value,
	              NULL);
	
	/*
	printf("DEBUG:increment=%d maximum=%d minimum=%d page_incr=%d slider_size=%d value=%d\n",increment,maximum,minimum,page_incr,slider_size,value);
	*/
	XtVaSetValues(sb,
	             XmNincrement,HEIGHTASDSTEP,
	             XmNpageIncrement,HEIGHTASDSTEP*3,
	             NULL);
	
	
	/************************
	Parte per Manual
	*************************/
	/*
	Vado a costruire gli oggetti contenuti nelle scrolled Window
	*/
	
	/*
	Form entro scrolled window
	*/
	       formManual = XtVaCreateManagedWidget( "formManual",
	                        xmFormWidgetClass,
	                        scrolledManualMiniASD,
	                        XmNheight, HEIGHTASDSTEP*num_manual,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNx, 0,
	                        XmNy, 0,
	                        NULL );
	        UxPutContext( formManual, (char *) UxOperatingWindowContext );
	
	/*
	RowColumn per contenitori CAi
	*/
	
	       rowColumnManualCai = XtVaCreateManagedWidget( "rowColumnManualCai",
	                        xmRowColumnWidgetClass,
	                        formManual,
	                        /*XmNwidth, 30, */
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNadjustLast, FALSE,
	                        XmNadjustMargin, FALSE,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNleftOffset, 0,
	                        XmNleftAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 0,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        NULL );
	        UxPutContext( rowColumnManualCai, (char *) UxOperatingWindowContext );
	/*
	rowColumn per contenere stringhe manual
	*/
	rowColumnManual=XtVaCreateManagedWidget( "rowColumnManual",
	                        xmRowColumnWidgetClass,
	                        formManual,
	                        XmNheight, HEIGHTASDSTEP*num_manual,
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNtopOffset, 0,
	                        XmNtopAttachment, XmATTACH_FORM,
	                        XmNbottomOffset, 0,
	                        XmNbottomAttachment, XmATTACH_FORM,
	                        XmNleftAttachment, XmATTACH_WIDGET,
	                        XmNleftWidget, rowColumnManualCai,
	                        NULL );
	        UxPutContext( rowColumnManual, (char *) UxOperatingWindowContext );
	
	/*
	Parte per costruzione oggetti allocati dinamicamente
	*/
	for(i=0;i<num_manual;i++)
	   {
	/*
	Vado a ricavare la stringa che scrivero' nella label
	*/
	strcpy(appo_descr,dati_manual.descr[i]);
	str=strtok(appo_descr,"$");
	if(str)
	   {
	   str=strtok((char *)NULL,"|");
	   str++;             /* salto il tipo di manual */
	   while(*str==' ')   /* salto spazi vuoti che SCADA spedisce */
	      str++;
	   if(str)
	      strcpy(descr_token[0],str);
	   else 
	      strcpy(descr_token[0],"");
	   
	   str=strtok((char *)NULL,"|");
	   if(str)
	      strcpy(descr_token[1],str);
	   else
	      strcpy(descr_token[1],"");
	   }
	   strcpy(descr_token[2],dati_manual.data[i]);
	  
	   sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s",41,41,descr_token[0],10,10,
	             descr_token[1],10,10,descr_token[2]);
	
	/*printf("label=%s\n",appo_descr);*/
	
	   strcpy(nomeWidget,"");
	   sprintf(nomeWidget,"%d",i);
	   strcat(nomeWidget,"_manLabelASD");
	
	       man_label[i] = XtVaCreateManagedWidget( nomeWidget,
	                        xmLabelWidgetClass,
	                        rowColumnManual,
	                        XmNx, 100,
	                        XmNy, 40,
	                        XmNrecomputeSize, FALSE,
	                        /*XmNwidth, 600,*/
	                        XmNheight, 29,
	                        /*XmNfontList, UxConvertFontList( "courier_bold10" ),*/
	                        RES_CONVERT( XmNlabelString, appo_descr ),
	                        NULL );
	        UxPutContext( man_label[i], (char *) UxOperatingWindowContext  );
	/*
	Parte per inserimento form per cai
	*/ 
	   strcpy(nomeWidget,"");
	   sprintf(nomeWidget,"%d",i);
	   strcat(nomeWidget,"_formCaiManASD");
	
	   all_caiMan_form[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xmFormWidgetClass,
	                        rowColumnManualCai,
	                        XmNresizePolicy, XmRESIZE_NONE,
	                        XmNheight, 29,
	                        XmNwidth, 29,
	                        /*RES_CONVERT( XmNbackground, "white"),*/
	                        NULL );
	        UxPutContext( all_caiMan_form[i], (char *) UxOperatingWindowContext  );
	/*
	Parte per inserimento CAI
	*/
	       strcpy(nomeWidget,"");
	       sprintf(nomeWidget,"%d",i);
	       strcat(nomeWidget,"_CaiMan");
	/*
	Determino il tipo di Cai che e' la  lettera dopo $ del name_man 
	*/
	       tipo_cai=strchr(dati_manual.descr[i],'$');
	       if(!tipo_cai)
	           {
	           fprintf(stderr,"WARNING:Impossble to determine CAI[%d] type\n",i);
	           }
	
	       all_caiMan[i]= XtVaCreateManagedWidget( nomeWidget,
	                        xlCaiAllWidgetClass,
	                        all_caiMan_form[i],
	                        XmNx, 0,
	                        XmNy, 0,
	                        XmNheight, 20,
	                        XmNwidth, 20,
	                        XmNtopAttachment,XmATTACH_FORM,
	                        XmNleftAttachment,XmATTACH_FORM,
#ifndef DESIGN_TIME
	                        XlNconfig, False,
#endif
	                        XlNtipoCaiAll,(int)( *(tipo_cai+1) ),
	                        
	                        XlNstatus, (int)dati_manual.emission[i],
	                        NULL );
	
	        UxPutContext( all_caiMan[i], (char *) UxOperatingWindowContext );
	                                                                      
	                                               
	   }/* end for num_manual */
	
	/*
	Setto database dei punti per CaiMan
	*/
	OlSetDatabasePunti(all_caiMan,num_manual,database_simulatore);
	
	/*
	Parte per gestione scrollbar
	*/
	XtVaGetValues(scrolledManualMiniASD,XmNverticalScrollBar,&sb,NULL);
	
	XtVaGetValues( sb,
	              XmNincrement, &increment,
	              XmNmaximum, &maximum,
	              XmNminimum,   &minimum,
	              XmNpageIncrement, &page_incr,
	              XmNsliderSize, &slider_size,
	              XmNvalue, &value,
	              NULL);
	/*
	printf("DEBUGmanual:increment=%d maximum=%d minimum=%d page_incr=%d slider_size=%d value=%d\n",increment,maximum,minimum,page_incr,slider_size,value);
	*/
	XtVaSetValues(sb,
	             XmNincrement,HEIGHTASDSTEP,
	             XmNpageIncrement,HEIGHTASDSTEP*3,
	             NULL);
}

static int	_OperatingWindow_CreateExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_CreateExt1( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_OpenExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	Dimension wh,ww,ext1h;
	Position x,y;
	int      off_dwa;
	
	/* apertura della Ext1 
	*/
	if( !ext1Aperta )
	{
	 
	   /* recupero le attuali dimensioni della OW e della 
	      extension1
	      calcolo le nuove dimesioni della OW sommandogli 
	      quelle della extension1 e le impongo      
	   */
	   XtVaGetValues(OperatingWindow,XmNwidth,&ww,XmNheight,&wh,NULL);
	   XtVaGetValues(extension1,XmNheight,&ext1h,NULL);
	
	   wh += ext1h;
	   XtVaSetValues(OperatingWindow,XmNheight,wh,NULL);      
	
	   /* riposiziono la drawing area che deve essere 
	      sotto la extension1 (la ext1 non deve coprirla)
	      modifico il topOffset della drawing area
	   */
	
	   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);
	
	printf("OPENEXT1: APRIRE PRIMA off_dwa = %d\n",off_dwa);
	
	/*
	   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);
	   y += (ext1h);
	   XtMoveWidget(drawingAreaOW,x,y);
	   if( ext2Aperta )
	   {
	      y += HEXT2;
	   }
	*/
	
	   off_dwa += (ext1h);
	
	printf("OPENEXT1: APRIRE DOPO off_dwa = %d\n",off_dwa); 
	
	   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);
	
	   /* setto la width della extension1 come quella del parent
	   */   
	   XtVaSetValues(extension1,XmNwidth,ww,NULL);
	
	   /* mappo la extension 1 con i suoi children
	   */ 
	   XtMapWidget(extension1);
	   
	   /* inverto la direzione dello
	      arrowButton per indicare
	      che attiva la chiusura della extension
	   */
	   XtVaSetValues(bOpenExt1,XmNarrowDirection,XmARROW_DOWN,NULL);
	
	   /* set variabile di controllo
	   */
	   ext1Aperta = 1;
	   
	}
	else /* chisura extension1 */
	{
	
	   /* recupero le attuali dimensioni della OW e della 
	      extension1 e la posizione della drawing area
	      calcolo le nuove dimesioni della OW sottraendogli 
	      quelle della extension1 e le impongo  
	      calcolo le nuove coordinate della drawing area
	      e le impongo    
	   */
	   XtVaGetValues(OperatingWindow,XmNheight,&wh,NULL);
	   XtVaGetValues(extension1,XmNheight,&ext1h,NULL);
	
	   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);
	
	printf("OPENEXT1: CHIUDERE off_dwa = %d\n",off_dwa);
	
	   wh -= ext1h;
	   XtVaSetValues(OperatingWindow,XmNheight,wh,NULL);
	
	/*
	   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);
	   y -= (ext1h);
	   XtMoveWidget(drawingAreaOW,x,y);
	*/
	
	   off_dwa -= (ext1h);
	   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);
	 
	   /* smappo la extension 1 con i suoi children
	   */ 
	   XtUnmapWidget(extension1);
	
	   /* inverto la direzione dello
	       arrowButton per indicare
	       che attiva la chiusura della extension
	   */
	    XtVaSetValues(bOpenExt1,XmNarrowDirection,XmARROW_UP,NULL);
	  
	    /* reset variabile controllo
	    */
	    ext1Aperta=0;
	}
}

static int	_OperatingWindow_OpenExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_OpenExt1( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_OpenExt2( UxThis, pEnv, drawing_area )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	drawing_area;
{
	Position x,y;
	int      h,hext1;
	int      off_dwa;
	
	/* apro la extension2 
	*/
	if( !ext2Aperta )
	{
	   /* recupero la dimensione della OW e
	      le coordinate della drawing area
	      calcolo la nuova altezza della OW sommandogli la 
	      HEXT2
	      muovo la drawing area  
	   */
	
	   XtVaGetValues(OperatingWindow,XmNheight,&h,NULL);
	   h += HEXT2;
	   XtVaSetValues(OperatingWindow,XmNheight,h,NULL);
	
	/*
	   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);
	   y += HEXT2;
	   if( ext1Aperta )
	   { 
	      XtVaGetValues(extension1,XmNheight,&hext1,NULL);
	      printf("extension1 h=%d\n",hext1);
	      y += hext1;
	   }
	   XtMoveWidget(drawingAreaOW,x,y);
	*/
	
	   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);
	
	printf("OPENEXT2: APRIRE PRIMA off_dwa = %d\n",off_dwa);
	
	   off_dwa += HEXT2;
	
	printf("OPENEXT2: APRIRE DOPO off_dwa = %d\n",off_dwa);
	
	   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);
	
	   ext2Aperta = 1; 
	
	}
	else
	{
	   /* recupero la dimensione della OW e
	      le coordinate della drawing area
	      calcolo la nuova altezza della OW sottraendogli la 
	      HEXT2
	      muovo la drawing area  
	   */
	
	   XtVaGetValues(OperatingWindow,XmNheight,&h,NULL);
	   h -= HEXT2;
	   XtVaSetValues(OperatingWindow,XmNheight,h,NULL);
	
	/*
	   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);
	   y -= HEXT2;
	   XtMoveWidget(drawingAreaOW,x,y);
	*/
	
	   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);
	
	printf("OPENEXT2: CHIUDERE off_dwa = %d\n",off_dwa);
	
	   off_dwa -= HEXT2;
	   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);
	
	   ext2Aperta = 0;
	}
}

static int	_OperatingWindow_OpenExt2( UxThis, pEnv, drawing_area )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	drawing_area;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_OpenExt2( UxThis, pEnv, drawing_area );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_configBottoni( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/* recupero la lista dei children 
	    e controllo se sono presenti OperableKeys
	    di tipo OPKEY_IMP e OPKEY_EXEC
	    se non ce ne sono elimino i tasti 
	    EJECUTAR E IMP
	*/
	
	Cardinal numChildren;
	WidgetList listChildren;
	int i;
	Boolean ExecYes,ImpYes;
	
	ExecYes=False;
	ImpYes=False;
	
	/* recupero la lista dei children
	   della drawing area
	*/
	XtVaGetValues(drawingAreaOW,XmNchildren,&listChildren,
	                            XmNnumChildren,&numChildren,
	                            NULL);
	
	for(i=0;i<numChildren;i++)
	{
	   if( XlIsOperableKeysImp( listChildren[i]) )
	      ImpYes=True;
	   if( XlIsOperableKeysExec( listChildren[i]) )
	      ExecYes=True;
	}
	
	if( !ImpYes )
	  XtDestroyWidget( IMP );
	if(!ExecYes )
	  XtDestroyWidget( Ejecutar );
}

static int	_OperatingWindow_configBottoni( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_configBottoni( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static void	Ux_chPage( UxThis, pEnv, w, nomePg, tipoApertura )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*nomePg;
	int	tipoApertura;
{
	/*********
	 effettua il popup o la navigazione
	  di una pagina, che viene richiamata da un change page
	  posto sulla OperatingWindow
	**********************************************************/
	extern swidget create_topLevelShell1();
	extern swidget popup_topLevelShellStaz();
	extern void teleperm_naviga();
	extern int NumeroPagina();
	
	int ind_pag;  /* indice della pagina nel vettore delle pagine */
	Widget newPag; /* top widget nuova pagina */
	
	if( !strlen(nomePg) ) 
	   return;
	
	
	/* apertura di una pagina
	*/
	if( (tipoApertura != CLOSE_PAGE) )
	{
	   /* la pagina non e' gia' aperta
	   */
	   if( !PaginaAperta(w,nomePg) )
	   {
	      if( !CanOpenPage(w) )
	         return;
	
	
	      ind_pag=NumeroPagina(nomePg);
	    
	      if( (Detail = (Widget *)XtRealloc( Detail, sizeof(Widget) * (numDetail+1))) == NULL)
	      {
	          fprintf(stderr,"OW: Error in allocation of Detail list\n");
	          return;
	      }
	
	      /* verifico il tipo di pagina e la apro. 
	         Nota, la pagina corrente e la nuova pagina hanno lo stesso parent.
	         Att.ne la gestione del tipo Sinottico,Stazioni o teleperm
	         determina il tipo e il modo di apertura della pagina
	         se il tipo e' teleperm viene effettuata una navigazione
	         altrimenti viene fatto il popup della pagina con layout
	         e funzionalita' basate sul tipo
	         La attivazione con CHANGE_PAGE o NEW_PAGE e' 
	         ininfluente.
	      */
	      if( strcmp(pagine[ind_pag].tipo,"Sinottico") == 0)
	      {
	         /* Pagine di tipo sinottico non dovrebbero essere mai chiamate
	         */
	         Detail[numDetail] = newPag = create_topLevelShell1(nomePg,UxThis,"nome_display",pagine[ind_pag].sfondo);
	         numDetail++;
	      if( newPag == NULL )
	         { 
	         popup_errorDialog("SBAGLIO pagina",w);
	         return;
	         }
	      }
	      if( strcmp(pagine[ind_pag].tipo,"Stazioni") == 0)
	      {
	/*         printf("chiamo la stazione con parent = %s\n",XtName(UxThis)); */
	         Detail[numDetail] = newPag = popup_topLevelShellStaz(nomePg,UxThis,"nome_display",pagine[ind_pag].sfondo);
	         numDetail++;
	       if( newPag == NULL )
	         { 
	         popup_errorDialog("SBAGLIO pagina",w);
	         return;
	         }
	      }
	      if( (strcmp(pagine[ind_pag].tipo,"Teleperm") == 0) ||
	          (strcmp(pagine[ind_pag].tipo,"Regolazione") == 0) ) {
	/*
	printf("OperatingWindow: aprire pagina regolazione --> nomepg = %s\n", nomePg);
	*/
	         teleperm_naviga(XtParent(UxThis),GOTOPAG,NumeroPagina(nomePg));
	/*
	printf("OperatingWindow: dopo chiamata a teleperm_naviga!!!\n");
	*/
	
	      }
	
	
	   }
	}
	/***
	else if( (tipoApertura == CHANGE_PAGE) )
	{
	   printf("chiamo la teleperm_naviga da CHANGE_PAGE\n");
	   teleperm_naviga(UxThis,GOTOPAG,NumeroPagina(nomePg));     
	}
	***/
}

static void	_OperatingWindow_chPage( UxThis, pEnv, w, nomePg, tipoApertura )
	swidget	UxThis;
	Environment *	pEnv;
	Widget	w;
	unsigned char	*nomePg;
	int	tipoApertura;
{
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	Ux_chPage( UxThis, pEnv, w, nomePg, tipoApertura );
	UxOperatingWindowContext = UxSaveCtx;
}

static int	Ux_SetDescr( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/* recupero le risorse top_descrizione_2,_3
	   che contengono le label da settare nelle
	   IdcodeLabel e funcodeLabel
	   ( le due descrizioni accanto all'arroe button )
	*/
	
	char *tipo;
	XrmValue value;
	char risorsa[100];
	char descr2[100];
	char descr3[100];
	XmString appo;
	Display *disp;
	
	disp = XtDisplay( UxThis );
	
	sprintf(risorsa,"top_descrizione_2");
	XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);
	strncpy(descr2,value.addr,(int)value.size);
	
	sprintf(risorsa,"top_descrizione_3");
	XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);
	strncpy(descr3,value.addr,(int)value.size);
	
	appo = XmStringCreateSimple( descr2 );
	XtVaSetValues( idcodeLabel,XmNlabelString,appo,NULL);
	XmStringFree( appo );
	
	appo = XmStringCreateSimple( descr3 );
	XtVaSetValues( funcodeLabel,XmNlabelString,appo,NULL);
	XmStringFree( appo );
}

static int	_OperatingWindow_SetDescr( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_SetDescr( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_decorationToggle( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	Arg args[2];
	int nargs;
	int decorOn;
	char *tipo;
	XrmValue value;
	char risorsa[50];
	char appo[50];
	Display *disp;
	
	disp = XtDisplay(UxThis);
	
	sprintf(risorsa,"teleperm.decorazioni");
	XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);
	strncpy(appo,value.addr,(int)value.size);
	decorOn = atoi(appo);
	
	if( decorOn == 0) 
	{
	nargs=0;
	/* decorazioni con titolo e bordino*/
	XtSetArg(args[0],XmNmwmDecorations,MWM_DECOR_TITLE|MWM_DECOR_BORDER);
	nargs++;
	XtSetValues(UxThis,args,nargs);
	}
	else /* decorazioni complete */
	{
	nargs=0;
	XtSetArg(args[0],XmNmwmDecorations,MWM_DECOR_ALL);
	nargs++;
	XtSetValues(UxThis,args,nargs);
	}
}

static int	_OperatingWindow_decorationToggle( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_decorationToggle( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_DestroyExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	/********************
	Parte per allarmi
	********************/
	/*
	Distruggo oggetti creati e le memorie allocate
	*/
	if(num_allarm)
	   {  
	    XtDestroyWidget(formAllarm);
	    XtFree(all_caiAll_form);
	    XtFree(all_label);
	    XtFree(all_caiAll);
	   /*
	   Metto a 0 num_allarm per bloccare XlRefresh
	   */
	   num_allarm=0;
	   }
	
	/********************
	Parte per manual
	********************/
	/*
	Distruggo oggetti creati e le memorie allocate
	*/
	if(num_manual)
	   {  
	    XtDestroyWidget(formManual);
	    XtFree(all_caiMan_form);
	    XtFree(man_label);
	    XtFree(all_caiMan);
	   /*
	   Metto a 0 num_manual per bloccare XlRefresh
	   */
	   num_manual=0;
	   }
}

static int	_OperatingWindow_DestroyExt1( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_DestroyExt1( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static Boolean	Ux_closeOW( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	extern int aggiornaListChild();
	extern int ClosePageStazFromOW();
	int i,j;
	Widget ref=NULL;
	
	if( numDetail )
	{
	    printf("numDetail  =%d\n",numDetail );
	
	   for(i=0;i<num_el_pagine;i++)
	   {
	
	      if( el_pagine[i].w )
	         ref = XtParent(XtParent(XtParent(XtParent(el_pagine[i].w))));
	      else
	        continue;
	
	printf("ref = %d\n",ref);
	
	      for(j=0;j<numDetail;j++)
	         if( ref == Detail[j] )
	         {  
	              printf("Deve essere eliminata la DetailWindow\n");
	/*
	              ClosePageStazFromOW( Detail[j] );
	*/
	              ClosePageStaz( Detail[j] );
	              break;
	         } 
	   }
	}
	
	/* resetto la risorsa del pictograph o indicatore
	   che ha attivato la OW
	   opw (parametro) e' l'indice del w che ha creato la OW
	*/
	XtVaSetValues(opw,XlNowOpen,False,NULL);
	
	DelElencoPagine(OWkey_refresh, drawingAreaOW );
	
	XSync(XtDisplay(UxThis),False);
	
	/* rimuovo il timer del refresh
	*/
	XtRemoveTimeOut(OWtimer_refresh);
	
	/* distruggo il db corrente
	   e rispristino quello del parent
	*/
	XrmDestroyDatabase(OwDb);
	XrmSetDatabase(XtDisplay((Widget)UxParent),ParentDb);
	
	/* elimino dalla lista delle OW aperte mantenuta
	   dalla interfaccia teleperm chiamante
	*/ 
	aggiornaListChild( OperatingWindow );
	/*
	 Elimina il pixmap di sfondo se esiste
	*/
	if(drawing_pixmap)
		XFreePixmap(XtDisplay((Widget)UxParent),drawing_pixmap);
	
	/*
	Elimino shm associate alle  window Extension se attive
	*/
	if(flag_aperture && (indice>=0))
	      {
	       if((OlElimina_shmMiniASD(database_simulatore,indice)<0))
	          printf(stderr,"ERROR: impossible to destroy shm for this O.W indice=%d\n",indice);
	      }
	/* 
	chiudo la finestra 
	*/
	
	UxDestroyInterface(OperatingWindow);
}

static Boolean	_OperatingWindow_closeOW( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	Boolean			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_closeOW( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_debug( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	printf("Stampa di debug\n");
}

static int	_OperatingWindow_debug( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_debug( UxThis, pEnv );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static Boolean	Ux_abilitaOpKeys( UxThis, pEnv, tipo_opkey, stato )
	swidget	UxThis;
	Environment *	pEnv;
	int	tipo_opkey;
	Boolean	stato;
{
	/* recupero la lista dei children 
	   e per quelli del tipo_opkey
	   faccio le opportune abilitazioni;
	*/
	extern Boolean XlOperableKeysAbleImp();
	extern Boolean XlIsOperableKeyImp();
	WidgetList listChildren;
	Cardinal numChildren;
	int i,numAbilitati;
	
	XtVaGetValues(drawingAreaOW,XmNchildren,&listChildren,
	                            XmNnumChildren,&numChildren,NULL);
	
	printf("numChildren = %d\n",numChildren);
	
	numAbilitati=0;
	for(i=0;i<numChildren;i++)
	{
	
	   if( XlIsOperableKeysImp( listChildren[i]) )
	   { 
	
	      if( XlOperableKeysAbleImp(listChildren[i],stato) )
	
	          numAbilitati++;
	
	      else
	
	         return(False);
	
	   } 
	
	}
	
	if( numAbilitati > 0 )
	   return(True);
	
	return(False);
}

static Boolean	_OperatingWindow_abilitaOpKeys( UxThis, pEnv, tipo_opkey, stato )
	swidget	UxThis;
	Environment *	pEnv;
	int	tipo_opkey;
	Boolean	stato;
{
	Boolean			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_abilitaOpKeys( UxThis, pEnv, tipo_opkey, stato );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static int	Ux_ricMiniASD( UxThis, pEnv, tipo_allarmi )
	swidget	UxThis;
	Environment *	pEnv;
	int	tipo_allarmi;
{
	/*
	
	Metodo che permette di attivare la richiesta di riconoscimento di un singolo 
	allarme per miniASD
	Oppure di piu' allarmi contemporaneamente
	*/
	int i;
	
	/*
	Disabilito bottoni chiusura O.W.
	*/
	
	
	if(tipo_allarmi==ALLARMI)
	   {
	   /*
	   Riconosco tutti gli allarmi
	   */
	 /*  for(i=0;i<num_allarm;i++)
	      {
	       if(!OlRiconosciAllarmiMiniASD(database_simulatore,gerarchie,indice,
	           0,ALL_M,num_allarm,i))
	         {
	         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");
	         return(-1);
	         }
	      } */
	    if(!OlRiconosciAllarmiMiniASD(database_simulatore,gerarchie,indice,
	           0,ALL_M,num_allarm,OPERAZIONERICALL))
	         {
	         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");
	         return(-1);
	         }
	   }
	
	else if(tipo_allarmi==MANUAL)
	   {
	   /*
	   Riconosco tutti gli allarmi
	   */
	  /* for(i=0;i<num_manual;i++)
	      {
	       if(!OlRiconosciManualiMiniASD(database_simulatore,gerarchie,indice,
	           0,ALL_M,num_manual,i))
	         {
	         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");
	         return(-1);
	         }
	      }
	   */
	    if(!OlRiconosciManualiMiniASD(database_simulatore,gerarchie,indice,
	           0,ALL_M,num_manual,OPERAZIONERICALL))
	         {
	         printf("ERROR: Impossible to send request manuals ASD to client_scada\n");
	         return(-1);
	         }
	   }
	/*
	Riattivo pulsanti di chiusura
	*/
	
	return(1);
}

static int	_OperatingWindow_ricMiniASD( UxThis, pEnv, tipo_allarmi )
	swidget	UxThis;
	Environment *	pEnv;
	int	tipo_allarmi;
{
	int			_Uxrtrn;
	_UxCOperatingWindow     *UxSaveCtx = UxOperatingWindowContext;

	UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_ricMiniASD( UxThis, pEnv, tipo_allarmi );
	UxOperatingWindowContext = UxSaveCtx;

	return ( _Uxrtrn );
}


/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_Ejecutar( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	extern void XlOperableKeysSendPert();
	Pixel bg_butt;
	
	/* invio la perturbazione associata all'ultimo OPKEY_EXEC
	   che e' stato premuto
	*/
	
	if( lastWexec != NULL )
	{
	   XlOperableKeysSendPert( lastWexec );
	
	   XtVaGetValues( lastWexec,XlNlstateBg,&bg_butt,NULL);
	
	   /* reset dell'indice di widget 
	   */
	   lastWexec = NULL;
	
	   /* rendo insensitive il bottone di ejecutar
	      (che deve risultare sensitive solo quando c'e' una perturbazione da inviare)
	   */
	   XtVaSetValues(Ejecutar,
	                  XmNsensitive,False,
	                  XmNbackground,bg_butt,
	                  NULL);
	
	}
	
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	activateCB_IMP( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	extern void EffettoPushButton();
	Pixel bkg_col,arm_col,top_col,bot_col,dummy_col;
	
	
	/* inverto i colori di arm e background ad ogni pressione
	   del bottone cosi da dare la impressione dello stato
	   premuto o rilasciato del tasto
	*/ 
	
	/* recupero i colori correnti
	
	XtVaGetValues(UxWidget,XmNwidth,&w,XmNheight,&h,
	                         XmNbackground,&bkg_col,
	                         XmNarmColor,&arm_col,
	                         XmNbottomShadowColor,&bot_col,
	                         XmNtopShadowColor,&top_col,
	                         NULL);
	*/
	
	
	/* se il bottone e' premuto
	    disabilito tutto
	*/                      
	if( imp_premuto )
	{
	              
	/* disabilitazione degli OperableKeys di tipo IMPULSE
	   abilitaOpkeys();        
	*/
	   if( OperatingWindow_abilitaOpKeys(OperatingWindow,&UxEnv,OPKEY_IMPULSE,False) )
	   {
	      /* inverto i colori
	     
	      dummy_col = bkg_col;
	      bkg_col = arm_col;
	      arm_col = dummy_col; 
	      dummy_col = top_col;
	      top_col = bot_col;
	      bot_col = dummy_col;
	   
	      XtVaSetValues(UxWidget,
	                    XmNbackground,bkg_col,
	                    XmNarmColor,arm_col,
	                    XmNbottomShadowColor,bot_col,
	                    XmNtopShadowColor,top_col,
	                    NULL);          
	      */
	
	      EffettoPushButton(UxWidget);
	      imp_premuto = False;
	   }
	}
	else
	{
	
	/* se e' disabilitato il bottone IMPULSE lo abilito
	   abilitazione degli OperableKeys di tipo IMPULSE
	   disabilitaOpKeys();        
	*/
	   if( OperatingWindow_abilitaOpKeys(OperatingWindow,&UxEnv,OPKEY_IMPULSE,True) )
	   {
	      /* inverto i colori
	      
	      dummy_col = bkg_col;
	      bkg_col = arm_col;
	      arm_col = dummy_col; 
	
	      dummy_col = top_col;
	      top_col = bot_col;
	      bot_col = dummy_col;
	
	      XtVaSetValues(UxWidget,
	                    XmNbackground,bkg_col,
	                    XmNarmColor,arm_col,
	                    XmNbottomShadowColor,bot_col,
	                    XmNtopShadowColor,top_col,
	                    NULL);          
	*/
	      EffettoPushButton( UxWidget );
	
	      imp_premuto = True;
	   }
	}
	
	
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	activateCB_Cerrar( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	/*
	  chiudo la OW
	*/
	OperatingWindow_closeOW(OperatingWindow,&UxEnv);
	
	
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	activateCB_bOpenExt1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	
	/*unsigned char *gerarchie;*/
	
	if(!flag_aperture)
	   {
	/*
	Chiamo metodo che richiede allarmi allo scada in base alla gerarchia
	della O.W..Restituisce se tutto OK, l' indice della shm nell' array
	dell ' oggetto OLDatabasePunti. 
	*/
	
	   if((OperatingWindow_reqAlarms(OperatingWindow,&UxEnv))<0)
	      {
	      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");
	      return;
	      } 
	   flag_aperture=1;
	   OperatingWindow_CreateExt1(OperatingWindow,&UxEnv);
	   }
	else     /* Chiusura Window Extension1 */
	   { 
	/*
	Elimino shm associate alla shm se esistono
	*/
	   if(indice>=0)
	      {
	       if((OlElimina_shmMiniASD(database_simulatore,indice)<0))
	          printf(stderr,"ERROR: impossible to destroy shm for this O.W indice=%d\n",indice);
	      indice=-1;
	      }
	
	   flag_aperture=0; 
	   XtFree(gerarchie);
	/*
	Chiamo il metodo con cui  distruggo widget contenuti nella EW1
	*/
	
	OperatingWindow_DestroyExt1(OperatingWindow,&UxEnv);
	
	   }
	
	/*
	chiamo il metodo di apri/chiudi window extension1
	*/
	OperatingWindow_OpenExt1(OperatingWindow,&UxEnv);
	
	
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	activateCB_dummy_ric_all( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	
	int increment,maximum,minimum,page_incr,slider_size,value;
	if(flag_aperture)
	   {
	
	/*
	Invio richiesta riconoscimento allarmi (parametro ALLARMI)
	*/
	 
	
	  if((OperatingWindow_ricMiniASD(OperatingWindow,&UxEnv,ALLARMI))<0)
	      {
	      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");
	      return;
	      }
	   /* Disabilito bottone  e ne setto le dimensioni*/
	   set_something(dummy_ric_all,XmNsensitive,False);
	
	   }
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	activateCB_dummy_ric_manual( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
	
	
	if(flag_aperture)
	   {
	
	   if((OperatingWindow_ricMiniASD(OperatingWindow,&UxEnv,MANUAL))<0)
	      {
	      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");
	      return;
	      }
	
	   set_something(dummy_ric_manual,XmNsensitive,False);
	   }
	}
	UxOperatingWindowContext = UxSaveCtx;
}

static	void	exposeCB_drawingAreaOW( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOperatingWindow     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOperatingWindowContext;
	UxOperatingWindowContext = UxContext =
			(_UxCOperatingWindow *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	disegna_bck(UxWidget,OWpag->sfondo,UxCallbackArg,&(region_ow),False);
#endif
	}
	UxOperatingWindowContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_OperatingWindow()
{
	Widget		_UxParent;


	/* Creation of OperatingWindow */
	_UxParent = UxParent;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	OperatingWindow = XtVaCreatePopupShell( "OperatingWindow",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 440,
			XmNy, 231,
			XmNwidth, 325,
			XmNheight, 400,
			XmNmwmDecorations, -1,
			XmNallowShellResize, TRUE,
			XmNmwmFunctions, -1,
			NULL );
	UxPutContext( OperatingWindow, (char *) UxOperatingWindowContext );


	/* Creation of mainForm */
	mainForm = XtVaCreateManagedWidget( "mainForm",
			xmFormWidgetClass,
			OperatingWindow,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 360,
			XmNheight, 380,
			XmNnavigationType, XmNONE,
			NULL );
	UxPutContext( mainForm, (char *) UxOperatingWindowContext );


	/* Creation of footerForm */
	footerForm = XtVaCreateManagedWidget( "footerForm",
			xmFormWidgetClass,
			mainForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 10,
			XmNy, 370,
			XmNwidth, 370,
			XmNheight, 40,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopPosition, 0,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( footerForm, (char *) UxOperatingWindowContext );


	/* Creation of fEjecutar */
	fEjecutar = XtVaCreateManagedWidget( "fEjecutar",
			xmFormWidgetClass,
			footerForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 33,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( fEjecutar, (char *) UxOperatingWindowContext );


	/* Creation of Ejecutar */
	Ejecutar = XtVaCreateManagedWidget( "Ejecutar",
			xmPushButtonWidgetClass,
			fEjecutar,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 1,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 1,
			NULL );
	XtAddCallback( Ejecutar, XmNactivateCallback,
		(XtCallbackProc) activateCB_Ejecutar,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( Ejecutar, (char *) UxOperatingWindowContext );


	/* Creation of fIMP */
	fIMP = XtVaCreateManagedWidget( "fIMP",
			xmFormWidgetClass,
			footerForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 66,
			XmNleftPosition, 33,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( fIMP, (char *) UxOperatingWindowContext );


	/* Creation of IMP */
	IMP = XtVaCreateManagedWidget( "IMP",
			xmPushButtonWidgetClass,
			fIMP,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 1,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 1,
			XmNlabelType, XmSTRING,
/*	                RES_CONVERT( XmNforeground, "red"),*/
			NULL );
	XtAddCallback( IMP, XmNactivateCallback,
		(XtCallbackProc) activateCB_IMP,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( IMP, (char *) UxOperatingWindowContext );


	/* Creation of fCerrar */
	fCerrar = XtVaCreateManagedWidget( "fCerrar",
			xmFormWidgetClass,
			footerForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 139,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 66,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( fCerrar, (char *) UxOperatingWindowContext );


	/* Creation of Cerrar */
	Cerrar = XtVaCreateManagedWidget( "Cerrar",
			xmPushButtonWidgetClass,
			fCerrar,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 1,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 1,
			NULL );
	XtAddCallback( Cerrar, XmNactivateCallback,
		(XtCallbackProc) activateCB_Cerrar,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( Cerrar, (char *) UxOperatingWindowContext );


	/* Creation of headerForm */
	headerForm = XtVaCreateManagedWidget( "headerForm",
			xmFormWidgetClass,
			mainForm,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 330,
			XmNheight, 70,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNbottomPosition, 13,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNbottomOffset, 345,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( headerForm, (char *) UxOperatingWindowContext );


	/* Creation of bOpenExt1 */
	bOpenExt1 = XtVaCreateManagedWidget( "bOpenExt1",
			xmArrowButtonWidgetClass,
			headerForm,
			XmNx, 289,
			XmNy, 0,
			XmNwidth, 36,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_SELF,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNbottomOffset, 0,
			XmNbottomPosition, 0,
			XmNsensitive, TRUE,
			NULL );
	XtAddCallback( bOpenExt1, XmNactivateCallback,
		(XtCallbackProc) activateCB_bOpenExt1,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( bOpenExt1, (char *) UxOperatingWindowContext );


	/* Creation of idcodeLabel */
	idcodeLabel = XtVaCreateManagedWidget( "idcodeLabel",
			xmLabelWidgetClass,
			headerForm,
			XmNx, 10,
			XmNy, 7,
			XmNwidth, 340,
			XmNheight, 20,
			RES_CONVERT( XmNlabelString, "IDENTIFICATIONCODE" ),
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 5,
			XmNrightWidget, bOpenExt1,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( idcodeLabel, (char *) UxOperatingWindowContext );


	/* Creation of funcodeLabel */
	funcodeLabel = XtVaCreateManagedWidget( "funcodeLabel",
			xmLabelWidgetClass,
			headerForm,
			XmNx, 0,
			XmNy, 38,
			XmNwidth, 338,
			XmNheight, 20,
			RES_CONVERT( XmNlabelString, "FUNCTION NAME" ),
			XmNalignment, XmALIGNMENT_CENTER,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, bOpenExt1,
			XmNtopAttachment, XmATTACH_NONE,
			NULL );
	UxPutContext( funcodeLabel, (char *) UxOperatingWindowContext );


	/* Creation of separatorGadget2 */
	separatorGadget2 = XtVaCreateManagedWidget( "separatorGadget2",
			xmSeparatorGadgetClass,
			headerForm,
			XmNx, 10,
			XmNy, 31,
			XmNwidth, 250,
			XmNheight, 3,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 3,
			XmNtopWidget, idcodeLabel,
			NULL );
	UxPutContext( separatorGadget2, (char *) UxOperatingWindowContext );


	/* Creation of separatorGadget3 */
	separatorGadget3 = XtVaCreateManagedWidget( "separatorGadget3",
			xmSeparatorGadgetClass,
			headerForm,
			XmNx, 10,
			XmNy, 61,
			XmNwidth, 250,
			XmNheight, 3,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 2,
			XmNtopWidget, funcodeLabel,
			NULL );
	UxPutContext( separatorGadget3, (char *) UxOperatingWindowContext );


	/* Creation of extension1 */
	extension1 = XtVaCreateWidget( "extension1",
			xmFormWidgetClass,
			mainForm,
			XmNresizePolicy, XmRESIZE_ANY,
			XmNx, 0,
			XmNy, 70,
			XmNwidth, 295,
			XmNheight, 260,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNancestorSensitive, TRUE,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( extension1, (char *) UxOperatingWindowContext );


	/* Creation of dummy_ric_all */
	dummy_ric_all = XtVaCreateManagedWidget( "dummy_ric_all",
			xmPushButtonWidgetClass,
			extension1,
			XmNx, 250,
			XmNy, 30,
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( dummy_ric_all, XmNactivateCallback,
		(XtCallbackProc) activateCB_dummy_ric_all,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( dummy_ric_all, (char *) UxOperatingWindowContext );


	/* Creation of scrolledAlarmMiniASD */
	scrolledAlarmMiniASD = XtVaCreateManagedWidget( "scrolledAlarmMiniASD",
			xmScrolledWindowWidgetClass,
			extension1,
			XmNscrollingPolicy, XmAUTOMATIC,
			XmNwidth, 250,
			XmNheight, 130,
			XmNx, 0,
			XmNy, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			NULL );
	UxPutContext( scrolledAlarmMiniASD, (char *) UxOperatingWindowContext );


	/* Creation of scrolledManualMiniASD */
	scrolledManualMiniASD = XtVaCreateManagedWidget( "scrolledManualMiniASD",
			xmScrolledWindowWidgetClass,
			extension1,
			XmNscrollingPolicy, XmAUTOMATIC,
			XmNwidth, 270,
			XmNheight, 120,
			XmNx, 0,
			XmNy, 130,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 0,
			XmNtopWidget, scrolledAlarmMiniASD,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNrightWidget, scrolledAlarmMiniASD,
			XmNleftAttachment, XmATTACH_FORM,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			NULL );
	UxPutContext( scrolledManualMiniASD, (char *) UxOperatingWindowContext );


	/* Creation of dummy_ric_manual */
	dummy_ric_manual = XtVaCreateManagedWidget( "dummy_ric_manual",
			xmPushButtonWidgetClass,
			extension1,
			XmNx, 250,
			XmNy, 160,
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( dummy_ric_manual, XmNactivateCallback,
		(XtCallbackProc) activateCB_dummy_ric_manual,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( dummy_ric_manual, (char *) UxOperatingWindowContext );


	/* Creation of drawingAreaOW */
	drawingAreaOW = XtVaCreateManagedWidget( "drawingAreaOW",
			xmDrawingAreaWidgetClass,
			mainForm,
			XmNx, 0,
			XmNy, 70,
			XmNwidth, 325,
			XmNheight, 290,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNtopOffset, 71,
			XmNnavigationType, XmNONE,
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			NULL );
	XtAddCallback( drawingAreaOW, XmNexposeCallback,
		(XtCallbackProc) exposeCB_drawingAreaOW,
		(XtPointer) UxOperatingWindowContext );

	UxPutContext( drawingAreaOW, (char *) UxOperatingWindowContext );

	XtVaSetValues(IMP,
			RES_CONVERT( XmNarmPixmap, "/usr/include/X11/bitmaps/mailfull" ),
			NULL );

	XtVaSetValues(dummy_ric_all,
			RES_CONVERT( XmNlabelPixmap, "ackalMiniASD.bmp" ),
			RES_CONVERT( XmNlabelInsensitivePixmap, "nullMiniASD.bmp" ),
			NULL );

	XtVaSetValues(dummy_ric_manual,
			RES_CONVERT( XmNlabelPixmap, "ackmaMiniASD.bmp" ),
			RES_CONVERT( XmNlabelInsensitivePixmap, "nullMiniASD.bmp" ),
			NULL );


	XtAddCallback( OperatingWindow, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxOperatingWindowContext);


	return ( OperatingWindow );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_OperatingWindow( _UxUxParent, _Uxopw, _UxOWpag, _UxParentDb )
	swidget	_UxUxParent;
	Widget	_Uxopw;
	AN_PAG	*_UxOWpag;
	XrmDatabase	_UxParentDb;
{
	Widget                  rtrn;
	_UxCOperatingWindow     *UxContext;
	static int		_Uxinit = 0;

	UxOperatingWindowContext = UxContext =
		(_UxCOperatingWindow *) UxNewContext( sizeof(_UxCOperatingWindow), False );

	UxParent = _UxUxParent;
	opw = _Uxopw;
	OWpag = _UxOWpag;
	ParentDb = _UxParentDb;

	if ( ! _Uxinit )
	{
		_UxIfClassId = UxNewClassId();
		UxOperatingWindow_reqAlarms_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_reqAlarms_Name,
					_OperatingWindow_reqAlarms );
		UxOperatingWindow_CreateExt1_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_CreateExt1_Name,
					_OperatingWindow_CreateExt1 );
		UxOperatingWindow_OpenExt1_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_OpenExt1_Name,
					_OperatingWindow_OpenExt1 );
		UxOperatingWindow_OpenExt2_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_OpenExt2_Name,
					_OperatingWindow_OpenExt2 );
		UxOperatingWindow_configBottoni_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_configBottoni_Name,
					_OperatingWindow_configBottoni );
		UxOperatingWindow_chPage_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_chPage_Name,
					_OperatingWindow_chPage );
		UxOperatingWindow_SetDescr_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_SetDescr_Name,
					_OperatingWindow_SetDescr );
		UxOperatingWindow_decorationToggle_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_decorationToggle_Name,
					_OperatingWindow_decorationToggle );
		UxOperatingWindow_DestroyExt1_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_DestroyExt1_Name,
					_OperatingWindow_DestroyExt1 );
		UxOperatingWindow_closeOW_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_closeOW_Name,
					_OperatingWindow_closeOW );
		UxOperatingWindow_debug_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_debug_Name,
					_OperatingWindow_debug );
		UxOperatingWindow_abilitaOpKeys_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_abilitaOpKeys_Name,
					_OperatingWindow_abilitaOpKeys );
		UxOperatingWindow_ricMiniASD_Id = UxMethodRegister( _UxIfClassId,
					UxOperatingWindow_ricMiniASD_Name,
					_OperatingWindow_ricMiniASD );
		UxLoadResources( "OperatingWindow.rf" );
		_Uxinit = 1;
	}

	{
		char nome_pag[255];
		Atom WM_DELETE_WINDOW; /* per close con MWM*/
		
		/* per gestione backgroundsinottico
		*/
		int dim[4];
		int num_b;
		extern Boolean leggi_file_bck();
		
		Pixmap pix;
		char *tipo;            /* usati nella put resource per set del background della OW */
		XrmValue value;
		XrmValue valueImp;
		XrmValue valueStr1;
		XrmValue valueStr2;
		XrmValue valueStr3;
		int retval;
/* carlo
*/
		char appo[100];
		
		/* inizializzo lista Detail window figlie della OW
		*/
		numDetail=0;
		Detail=NULL;
		
		drawing_pixmap=0;
		
		ext1Aperta =0;
		
		/* inizializzo lo stato del IMP button
		*/
		imp_premuto = 0;
		
		if( !EsistePagina(OWpag->nome) )
		{
		    printf("Error. File Page %s not exist.\n",OWpag->nome);
		    return( NULL );
		}
		
		                
		/* file delle risorse della pagina da caricare
		*/
		sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),OWpag->nome);
		
		                
		/* carico il db della pagina
		*/
		if( (OwDb = XrmGetFileDatabase(nome_pag)) == NULL)
		{
		   printf("Error. Cannot open page %s\n",nome_pag);
		   return(NULL);
		}
		
		/* recupero il background della drawing area della pagina
		   che uso poi nella PutResource per forzare il bkg
		   di tutti gli oggetti figli 
		*/
		XrmGetResource(OwDb,"drawing_background",(char*)NULL,&tipo,&value);

		
		/* merge db della pagina e della applicazione (quello salvato su file)
		*/
		XrmCombineFileDatabase( "ApplDb.res", &OwDb ,True);

/* carlo
*/
		XrmGetResource(OwDb,"*OperatingWindow.mainForm.footerForm.fIMP.IMP.foreground",(char*)NULL,&tipo,&valueImp);
		XrmGetResource(OwDb,"*OperatingWindow.mainForm.footerForm.fIMP.IMP.labelString",(char*)NULL,&tipo,&valueStr1);
		XrmGetResource(OwDb,"*OperatingWindow.mainForm.footerForm.fCerrar.Cerrar.labelString",(char*)NULL,&tipo,&valueStr2);
		XrmGetResource(OwDb,"*OperatingWindow.mainForm.footerForm.fEjecutar.Ejecutar.labelString",(char*)NULL,&tipo,&valueStr3);
		
		/* setto il bkg di tutti gli oggetti figli della OW
		   al colore della drawing area della pagina
		   La Ow risulta cosi di un colore tutta uniforme
		*/
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm*background",tipo,&value);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.headerForm*background",tipo,&value);
		/*
		Modifica by Fabio
		*/
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmLabel.background",tipo,&value);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmForm.background",tipo,&value);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.formAllarm.*XmRowColumn.background",tipo,&value);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.background",tipo,&value);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmScrolledWindow.background",tipo,&value);
		/*XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmPushButton.background",tipo,&value);*/
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmScrollBar.background",tipo,&value);
		
/* carlo
	qui setto i valori scritti nel file delle risorse
*/
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm.fIMP.IMP.foreground",tipo,&valueImp);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm.fIMP.IMP.labelString",tipo,&valueStr1);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm.fCerrar.Cerrar.labelString",tipo,&valueStr2);
		XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm.fEjecutar.Ejecutar.labelString",tipo,&valueStr3);


		/* 
		setto il display su PagDb
		*/
		XrmSetDatabase(XtDisplay((Widget)UxParent),OwDb);
		
		/* mi serve solo per caricare il time_ref
		*/
		if(!GetResTopLevel(opw,&OWtop_x,&OWtop_y,&OWtop_width,&OWtop_height,&OWtime_ref,
				&OWtop_tipo,&OWtop_descrizione))
			return(False);
		
		/* recupero le risorse della drawing area
		*/
		if(!GetResDrawing(opw,&drawing_width,&drawing_height,&drawing_background,&drawing_pixmap))
				return(False);
		
		/* recupero la dimensione della extension2 dalla risorsa
		   height_ext2   e la imposto alla variabile HEXT2
		   che viene utilizzata per calcolare le dimensioni della
		   extension2 e quindi della drawing area della OW
		*/
		retval = XrmGetResource(OwDb,"height_ext2",(char*)NULL,&tipo,&value);
		
		if( retval && (value.size > 1))
		   HEXT2 = atoi(value.addr);
		else
		   HEXT2 = DEFAULT_HEXT2;
		
		flag_aperture=0;
		/*
		Setto a zero No allarmi per OperatingWindow
		*/
		num_manual=0;
		num_allarm=0;
		rtrn = _Uxbuild_OperatingWindow();
		UxPutClassCode( OperatingWindow, _UxIfClassId );

		{
		long  decor;
		Widget child;  /* a perdere */
		Position x,y;
		
		/* set frame sul pictograph/indic
		*/
		XtVaSetValues(opw,XlNowOpen,True,NULL);
		
		/* carlo
		   qui posso impostare i valori letti dal db delle risorse
		   sugli widget MA:   i dati sono tutti in formato string
				      e occorre convertirlo nel formato opportuno.
		   PER I COLORI e' un po piu' complicato
		*/
		printf("VALORE = %s\n",valueStr1.addr);
		strncpy(appo,valueStr1.addr,valueStr1.size);
		printf("APPO = %s\n",appo);
		XtVaSetValues(IMP,
			RES_CONVERT(XmNlabelString,appo),
			NULL );
		XtVaSetValues(Cerrar,
			RES_CONVERT(XmNlabelString,valueStr2.addr),
			NULL );
		XtVaSetValues(Ejecutar,
			RES_CONVERT(XmNlabelString,valueStr3.addr),
			NULL );

		
		/* richiedo la x e la y del parent
		   per poter riposizionare la ow vicino al parent
		   (se il parent diretto non e' la drawing area
		    richiedo il parent)
		*/
		
		if( XlIsXlComposite(XtParent(opw)) )
		   XtVaGetValues(XtParent(opw),XmNx,&owX,XmNy,&owY,XmNheight,&owH,NULL);
		else
		   XtVaGetValues(opw,XmNx,&owX,XmNy,&owY,XmNheight,&owH,NULL);
		
		x = owX;
		y = owY;
		
		/* sposto le coordinate di visualizzazione della OW
		   rispetto a quelle dello widget chiamante in base ad un offset prefissato
		   attualmente fissato come define (potrebbe diventare una risorsa della applicazione)
		*/
		x += OWXOFFSET;
		y += OWYOFFSET;
		
		
		/* set della posizione della operating Window 
		   ( rispetto al parent widget )
		   e della sua dimensione esterna 
		*/
		XtVaSetValues(OperatingWindow,XmNx,x,XmNy,y,
		              XmNwidth,OWtop_width,XmNheight,OWtop_height,NULL);
		
		
		/* setto la posizione  dimensioni della drawing area
		   e della OW in base alle risorse 
		*/
		XtVaSetValues(drawingAreaOW,
		              XmNwidth,drawing_width,XmNheight,drawing_height,NULL);
		
		/* decorazioni mwm per OW
		*/
		
		OperatingWindow_decorationToggle(OperatingWindow,&UxEnv);
		
		}
		
		/* set titolo blank*/
		set_something(OperatingWindow,XmNtitle," ");
		/*
		set_something(OperatingWindow,XmNtitle,OWpag->nome);
		*/
		
		/* setto il background della drawingArea
		*/
		if(drawing_pixmap)
			set_something(drawingAreaOW,XmNbackgroundPixmap,drawing_pixmap);
		else
			set_something(drawingAreaOW,XmNbackground,drawing_background);
		
		if(!CreaPagina(drawingAreaOW,&OWlista_wid, &OWnum_wid))
			return(NULL);
		
		
		if((OWkey_refresh=InsElencoPagine(OWpag->nome,OWlista_wid,OWnum_wid,OWtime_ref)) == -1)
			return(NULL);
		
		/* set del timer di refresh e della routine di refresh (teleperm_refreshPag)
		*/
		OWtimer_refresh = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (OperatingWindow),
		            (unsigned long) (OWtime_ref*100) ,OperatingWindow_refreshPag, OperatingWindow );
		
		/* disabilito la chiusura della finestra da MWM
		*/
		 WM_DELETE_WINDOW=XmInternAtom(XtDisplay(OperatingWindow),"WM_DELETE_WINDOW",False);
		XmAddWMProtocolCallback(OperatingWindow,WM_DELETE_WINDOW,no_closeMWM,NULL);
		
		
		/* faccio sparire la extension2
		   chiudendola
		*/
		ext2Aperta = 1;
		OperatingWindow_OpenExt2(rtrn,&UxEnv,drawingAreaOW);
		
		/* inizializzo come insensitive il bottone di Ejecutar
		   che viene reso sensitive solo se c'e' una perturbazione disponibile a essere
		   da lui inviata
		*/
		XtVaSetValues(Ejecutar,
		              XmNsensitive,False,
		              NULL);
		
		/*
		  inizializza la regione di ridisegno dello sfondo
		*/
		   if(OWpag->sfondo==NULL)
			leggi_file_bck(UxParent,OWpag->nome,"bkg",&(OWpag->sfondo),dim);
		   else	 
		      AllocaColoriSfondo(UxParent,OWpag->sfondo);
		
		
		
		region_ow=NULL;
		
		/* setto le descrizione idcode e funcode
		*/
		OperatingWindow_SetDescr(OperatingWindow,&UxEnv);
		
		/* distruggo i bottoni Ejecutar e IMP
		   verificando se ci sono bottoni tipo OPKEY_IMP
		   e OPKEY_EXEC
		*/
		OperatingWindow_configBottoni(OperatingWindow,&UxEnv);/*
		Setto bottoni per miniASD
		*/
		/* setto i pixmap sui bottoni dlla pagina teleperm 
		   i .bmp so trovano in $LEGOCAD_ICO 
		*/
		
		path_icone=(char *)getenv("LEGOCAD_ICO");
		
		if(path_icone==NULL)
		{
		   printf("\nERROR Environment variable LEGOCAD_ICO is not defined. Exit.\n");
		   
		}
		
		sprintf(icon,"%s/ackmaMiniASD.bmp",path_icone);
		UxPutStrRes(dummy_ric_manual,XmNlabelPixmap,icon);
		sprintf(icon,"%s/nullMiniASD.bmp",path_icone);
		UxPutStrRes(dummy_ric_manual,XmNlabelInsensitivePixmap,icon);
		UxPutStrRes(dummy_ric_all,XmNlabelInsensitivePixmap,icon);
		
		sprintf(icon,"%s/ackalMiniASD.bmp",path_icone);
		UxPutStrRes(dummy_ric_all,XmNlabelPixmap,icon);
		
		
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

