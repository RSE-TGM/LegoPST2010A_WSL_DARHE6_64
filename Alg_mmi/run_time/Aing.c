
/*******************************************************************************
       Aing.c
       (Generated from interface file Aing.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/DrawingA.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo Aing.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)Aing.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Ol/OlDatabasePunti.h>
#include <Xm/Protocols.h>
#include "aing_def.h"

#ifndef DESIGN_TIME
#include "other.h"
#endif

#ifdef SCO_UNIX
#include <Xm/MwmUtil.h>
#else
#include <Xm/MwmUtil.h>
#endif

#include "sim_param.h"
#include "sim_ipc.h"
#include "page_aing_icon.bmp"


extern OlDatabasePuntiObject database_simulatore;
int msg_pert;

static void CreaIndicatore( );
void DestroyAing( );
static void refresh_aing( );
void ConfigureAing( );
static void activateCB_QuitAing();
int AingStartEnable(Widget, int);


static	int _UxIfClassId;
int	UxAing_start_enable_Id = -1;
char*	UxAing_start_enable_Name = "start_enable";

#ifndef Aing_start_enable
#define Aing_start_enable( UxThis, pEnv, sensitive ) \
	((int(*)())UxMethodLookup(UxThis, UxAing_start_enable_Id,\
			UxAing_start_enable_Name)) \
		( UxThis, pEnv, sensitive )
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
	Widget	UxAing;
	Widget	Uxsfondo;
	Widget	Uxtestata;
	Widget	Uxtag;
	Widget	Uxunimis;
	Widget	Uxseparator1;
	Widget	UxdrawingAing;
	Widget	Uxtasti_label;
	Widget	UxStop;
	Widget	UxStart;
	Widget	UxSceltaPert;
	Widget	Uxpert_1;
	Widget	Uxpert_2;
	Widget	Uxpert_3;
	Widget	Uxpert_4;
	Widget	Uxpert_5;
	Widget	Uxpert_6;
	Widget	UxSceltaPert_b10;
	Widget	Uxpert_7;
	Widget	Uxpert_8;
	Widget	UxSceltaPert_b11;
	Widget	Uxpert_9;
	Widget	Uxpert_10;
	Widget	Uxtipo_pert;
	Widget	UxConfigure;
	Widget	UxQuitAing;
	Widget	Uxcampo_1;
	Widget	Uxtext_1;
	Widget	Uxcampo_2;
	Widget	Uxcampo_3;
	Widget	Uxcampo_4;
	Widget	Uxcampo_5;
	Widget	Uxcampo_6;
	Widget	Uxcampo_7;
	Widget	Uxtext_3;
	Widget	Uxtext_4;
	Widget	Uxtext_5;
	Widget	Uxtext_6;
	Widget	Uxtext_7;
	Widget	Uxtext_2;
	Widget	Uxmenu3_p1;
	Widget	UxdelayAing;
	Widget	UxstartAtAing;
	Widget	UxtimeAing;
	Widget	UxTextFieldTempo;
	Widget	UxtopLevel_selezionataAing;
	XtIntervalId	Uxtimer_refresh_aing;
	XmFontList	UxFontLabelAing;
	int	Uxkey_refresh_aing;
	WidgetList	Uxlista_wid_aing;
	int	Uxnum_wid_aing;
	Widget	UxOptionPert[10];
	int	UxPertSelezionata;
	int	UxTempoSelezionato;
	unsigned char	UxtagSelect[20];
	unsigned char	UxunimisSelect[20];
	float	UxaSelect;
	float	UxbSelect;
	int	UxindSelect;
	XrmDatabase	UxRisDb;
	unsigned char	*UxrigaAing;
	Widget	UxPadreAing;
} _UxCAing;

static _UxCAing                *UxAingContext;
#define Aing                    UxAingContext->UxAing
#define sfondo                  UxAingContext->Uxsfondo
#define testata                 UxAingContext->Uxtestata
#define tag                     UxAingContext->Uxtag
#define unimis                  UxAingContext->Uxunimis
#define separator1              UxAingContext->Uxseparator1
#define drawingAing             UxAingContext->UxdrawingAing
#define tasti_label             UxAingContext->Uxtasti_label
#define Stop                    UxAingContext->UxStop
#define Start                   UxAingContext->UxStart
#define SceltaPert              UxAingContext->UxSceltaPert
#define pert_1                  UxAingContext->Uxpert_1
#define pert_2                  UxAingContext->Uxpert_2
#define pert_3                  UxAingContext->Uxpert_3
#define pert_4                  UxAingContext->Uxpert_4
#define pert_5                  UxAingContext->Uxpert_5
#define pert_6                  UxAingContext->Uxpert_6
#define SceltaPert_b10          UxAingContext->UxSceltaPert_b10
#define pert_7                  UxAingContext->Uxpert_7
#define pert_8                  UxAingContext->Uxpert_8
#define SceltaPert_b11          UxAingContext->UxSceltaPert_b11
#define pert_9                  UxAingContext->Uxpert_9
#define pert_10                 UxAingContext->Uxpert_10
#define tipo_pert               UxAingContext->Uxtipo_pert
#define Configure               UxAingContext->UxConfigure
#define QuitAing                UxAingContext->UxQuitAing
#define campo_1                 UxAingContext->Uxcampo_1
#define text_1                  UxAingContext->Uxtext_1
#define campo_2                 UxAingContext->Uxcampo_2
#define campo_3                 UxAingContext->Uxcampo_3
#define campo_4                 UxAingContext->Uxcampo_4
#define campo_5                 UxAingContext->Uxcampo_5
#define campo_6                 UxAingContext->Uxcampo_6
#define campo_7                 UxAingContext->Uxcampo_7
#define text_3                  UxAingContext->Uxtext_3
#define text_4                  UxAingContext->Uxtext_4
#define text_5                  UxAingContext->Uxtext_5
#define text_6                  UxAingContext->Uxtext_6
#define text_7                  UxAingContext->Uxtext_7
#define text_2                  UxAingContext->Uxtext_2
#define menu3_p1                UxAingContext->Uxmenu3_p1
#define delayAing               UxAingContext->UxdelayAing
#define startAtAing             UxAingContext->UxstartAtAing
#define timeAing                UxAingContext->UxtimeAing
#define TextFieldTempo          UxAingContext->UxTextFieldTempo
#define topLevel_selezionataAing UxAingContext->UxtopLevel_selezionataAing
#define timer_refresh_aing      UxAingContext->Uxtimer_refresh_aing
#define FontLabelAing           UxAingContext->UxFontLabelAing
#define key_refresh_aing        UxAingContext->Uxkey_refresh_aing
#define lista_wid_aing          UxAingContext->Uxlista_wid_aing
#define num_wid_aing            UxAingContext->Uxnum_wid_aing
#define OptionPert              UxAingContext->UxOptionPert
#define PertSelezionata         UxAingContext->UxPertSelezionata
#define TempoSelezionato        UxAingContext->UxTempoSelezionato
#define tagSelect               UxAingContext->UxtagSelect
#define unimisSelect            UxAingContext->UxunimisSelect
#define aSelect                 UxAingContext->UxaSelect
#define bSelect                 UxAingContext->UxbSelect
#define indSelect               UxAingContext->UxindSelect
#define RisDb                   UxAingContext->UxRisDb
#define rigaAing                UxAingContext->UxrigaAing
#define PadreAing               UxAingContext->UxPadreAing


/*******************************************************************************
       The following function is an event-handler for posting menus.
*******************************************************************************/

static void	_UxAingMenuPost( wgt, client_data, event, ctd )
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;

{
	Widget	menu = (Widget) client_data;
	int 	which_button;

	XtVaGetValues( menu, XmNwhichButton, &which_button, NULL );

	if ( event->xbutton.button == which_button )
	{
		XmMenuPosition( menu, (XButtonPressedEvent *) event );
		XtManageChild( menu );
	}
}


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_Aing();

/*******************************************************************************
Declarations of methods
*******************************************************************************/

static int	_Aing_start_enable();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void DestroyAing(Widget w)
{
#ifndef DESIGN_TIME
_UxCAing *Context;

        Context =(_UxCAing *) UxGetContext(w);	
	DelElencoPagine(Context->Uxkey_refresh_aing, 
		Context->UxdrawingAing);
	XSync(XtDisplay(w),False);
	XtRemoveTimeOut(Context->Uxtimer_refresh_aing);
	XtDestroyWidget(Context->UxAing);
	XrmDestroyDatabase(Context->UxRisDb);
#endif
}


#ifndef DESIGN_TIME
static void refresh_aing(_UxCAing *Context)
#else
static void refresh_aing()
#endif
{
#ifndef DESIGN_TIME
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_aing))
        {
        show_warning("Error in refresh");
        return;
        }
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_aing))
     XlRefreshWidget(Context->Uxlista_wid_aing,Context->Uxnum_wid_aing);

if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_aing))
        {
        show_warning("Error in refresh");
        return;
        }
/*
        carica il timer per il refresh
*/
Context->Uxtimer_refresh_aing = XtAppAddTimeOut (
            XtWidgetToApplicationContext (Context->UxAing),
            (unsigned long) REFRESH_AING ,refresh_aing, Context);
#endif	
}



static void CreaIndicatore(Widget Drawing)
{
#ifndef DESIGN_TIME
_UxCAing *Context;
XrmDatabase SaveDb;
Display *display;

	WriteDbAing();	
        Context =(_UxCAing *) UxGetContext(Drawing);
	RisDb=XrmGetFileDatabase("TemplateIndicAing.rtf");
	display=XtDisplay(Drawing);
	SaveDb=display->db;
	display->db=RisDb;
	CreaPagina(Context->UxdrawingAing,&(Context->Uxlista_wid_aing),
		 &(Context->Uxnum_wid_aing));
	Context->UxindSelect = SettaIndicAing(Context->Uxlista_wid_aing[0],Context->UxtagSelect,
		Context->UxaSelect,Context->UxbSelect);
	display->db=SaveDb;
	
#endif

}



void ConfigureAing(Widget w, int sel)
{
#ifndef DESIGN_TIME
 _UxCAing                *UxSaveCtx, *UxContext;

        UxSaveCtx = UxAingContext;
        UxAingContext = UxContext =
                        (_UxCAing *) UxGetContext( w );
#endif
PertSelezionata=sel;
printf("Perturbazione selezionata = %d\n",PertSelezionata);
XtUnmanageChild(campo_1);
XtUnmanageChild(text_1);
XtUnmanageChild(campo_2);
XtUnmanageChild(text_2);
XtUnmanageChild(campo_3);
XtUnmanageChild(text_3);
XtUnmanageChild(campo_4);
XtUnmanageChild(text_4);
XtUnmanageChild(campo_5);
XtUnmanageChild(text_5);
XtUnmanageChild(campo_6);
XtUnmanageChild(text_6);
XtUnmanageChild(campo_7);
XtUnmanageChild(text_7);
#ifndef DESIGN_TIME
if(menu_aing[sel]._campo_1)
	{
	set_something(campo_1,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_1,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_1);
	XtManageChild(text_1);
	}
if(menu_aing[sel]._campo_2)
	{
	set_something(campo_2,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_2,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_2);
	XtManageChild(text_2);
	}
if(menu_aing[sel]._campo_3)
	{
	set_something(campo_3,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_3,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_3);
	XtManageChild(text_3);
	}
if(menu_aing[sel]._campo_4)
	{
	set_something(campo_4,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_4,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_4);
	XtManageChild(text_4);
	}
if(menu_aing[sel]._campo_5)
	{
	set_something(campo_5,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_5,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_5);
	XtManageChild(text_5);
	}
if(menu_aing[sel]._campo_6)
	{
	set_something(campo_6,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_6,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_6);
	XtManageChild(text_6);
	}
if(menu_aing[sel]._campo_7)
	{
	set_something(campo_7,XmNlabelString,
                 (void*) XmStringCreateLtoR(menu_aing[sel].descr_7,XmSTRING_DEFAULT_CHARSET));
	XtManageChild(campo_7);
	XtManageChild(text_7);
	}
if(menu_aing[sel]._Start)
	set_something(Start,XmNsensitive,(void*) True);
else
	set_something(Start,XmNsensitive,(void*) False);
if(menu_aing[sel]._Stop)
	set_something(Stop,XmNsensitive,(void*) True);
else
	set_something(Stop,XmNsensitive,(void*) False);

UxAingContext = UxSaveCtx;
#endif
}


AingStartEnable(w,enable)
Widget w;
int enable;
{

 _UxCAing                *UxSaveCtx, *UxContext;

        UxSaveCtx = UxAingContext;
        UxAingContext = UxContext =
                        (_UxCAing *) UxGetContext( w );

Aing_start_enable(w,&UxEnv,enable);

UxAingContext = UxSaveCtx;

}

/*******************************************************************************
       The following are method functions.
*******************************************************************************/

static int	Ux_start_enable( UxThis, pEnv, sensitive )
	swidget	UxThis;
	Environment *	pEnv;
	int	sensitive;
{
	if(!sensitive)
	   {
	   XtVaSetValues(tipo_pert,XmNsensitive,False,NULL);
	   XtVaSetValues(timeAing,XmNsensitive,False,NULL);
	   XtVaSetValues(Start,XmNsensitive,False,NULL);
	   }
	else
	   XtVaSetValues(Start,XmNsensitive,True,NULL);
}

static int	_Aing_start_enable( UxThis, pEnv, sensitive )
	swidget	UxThis;
	Environment *	pEnv;
	int	sensitive;
{
	int			_Uxrtrn;
	_UxCAing                *UxSaveCtx = UxAingContext;

	UxAingContext = (_UxCAing *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_start_enable( UxThis, pEnv, sensitive );
	UxAingContext = UxSaveCtx;

	return ( _Uxrtrn );
}


/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_Stop( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	{
	float t;
	int shr_usr_key;
	
	if(msg_pert==0)
		{
		shr_usr_key=atoi(XlGetenv("SHR_USR_KEY"));
	/*
	Inserisco controllo sul tipo di database in maniera da inviare perturbazioni sulla
	giusta coda di messaggi.
	*/	if((OlDatabasePuntiType(database_simulatore))==DB_XLSIMUL)
			msg_pert=msg_create(shr_usr_key+ID_MSG_PERT,0);
		else
			msg_pert=msg_create(shr_usr_key+ID_MSG_PERT_MMI,0);
		}
	
	
	
	t=atof(XmTextFieldGetString(TextFieldTempo));
	if(TempoSelezionato == 0)
	 t = -t;
	
	if(PertSelezionata == 2)
		pert_impulso_stop(msg_pert,indSelect,t);	
	
	if(PertSelezionata == 3)
		pert_rampa_stop(msg_pert,indSelect,t);	
		
	if((PertSelezionata == 4) || (PertSelezionata == 5))
		pert_to_stop(msg_pert,indSelect,t);
	
	if((PertSelezionata == 6) || (PertSelezionata == 7))
		pert_period_stop(msg_pert,indSelect,t);
	
	if(PertSelezionata == 8)
		pert_whitenoise_stop(msg_pert,indSelect,t);
	
	if(PertSelezionata == 9)
	        pert_malfunction_stop(msg_pert,indSelect,t);	
	
	}
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_Start( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	{
	float v1,v2,v3,v4,v5,v6,v7,t;
	int shr_usr_key;
	
	if(msg_pert==0)
		{
		shr_usr_key=atoi(XlGetenv("SHR_USR_KEY"));
	/*
	Inserisco controllo sul tipo di database in maniera da inviare perturbazioni sulla
	giusta coda di messaggi.
	*/	if((OlDatabasePuntiType(database_simulatore))==DB_XLSIMUL)
			msg_pert=msg_create(shr_usr_key+ID_MSG_PERT,0);
		else
			msg_pert=msg_create(shr_usr_key+ID_MSG_PERT_MMI,0);
		}
	
	
	
	v1=atof(XmTextFieldGetString(text_1));
	v2=atof(XmTextFieldGetString(text_2));
	v3=atof(XmTextFieldGetString(text_3));
	v4=atof(XmTextFieldGetString(text_4));
	v5=atof(XmTextFieldGetString(text_5));
	v6=atof(XmTextFieldGetString(text_6));
	v7=atof(XmTextFieldGetString(text_7));
	t=atof(XmTextFieldGetString(TextFieldTempo));
	if(TempoSelezionato == 0)
		t = -t;
	
	
	if(PertSelezionata == 0)
		pert_nega(msg_pert,indSelect,t);
	
	if(PertSelezionata == 1)
		{
		v1=(v1-bSelect)/aSelect;
		pert_scalino(msg_pert,indSelect,v1,t);	
		}
	if(PertSelezionata == 2)
		{
		v1=(v1-bSelect)/aSelect;
		pert_impulso(msg_pert,indSelect,v1,v2,t);	
		}
	if(PertSelezionata == 3)
		{
		v1=(v1-bSelect)/aSelect;
		v2=(v2/60.-bSelect)/aSelect;
		pert_rampa(msg_pert,indSelect,v1,v2,t);	
		}
	
	if(PertSelezionata == 4)
		{
		v1=(v1-bSelect)/aSelect;
		v2= -v2;
		pert_to(msg_pert,indSelect,v1,v2,t);	
		}
	
	if(PertSelezionata == 5)
		{
		v1=(v1-bSelect)/aSelect;
		pert_to(msg_pert,indSelect,v1,v2,t);	
		}
	
	if(PertSelezionata == 6)
		{
		v2=(v2-bSelect)/aSelect;
		v3=(v3-bSelect)/aSelect;
		pert_period(msg_pert,indSelect,-1.,-1.,v1,v4,v2,v3,0.,t);
		}
	
	if(PertSelezionata == 7)
		{
		v2=(v2-bSelect)/aSelect;
		v3=(v3-bSelect)/aSelect;
		pert_period(msg_pert,indSelect,v5,v6,v1,v4,v2,v3,v7,t);
		}
	if(PertSelezionata == 8)
		{
		v1=(v1-bSelect)/aSelect;
		pert_whitenoise(msg_pert,indSelect,v1,v2,t);	
		}
	if(PertSelezionata == 9)
	        {
	        v1=(v1-bSelect)/aSelect;
	        pert_malfunction(msg_pert,indSelect,v1,v2,t);
	        }
	}
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_1,0);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_2,1);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_3,2);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_4,3);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_5,4);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_6( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_6,5);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_7,6);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_8( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_8,7);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_9,8);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_pert_10( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	ConfigureAing(pert_10,9);
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_QuitAing( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	{
	DestroyAing(Aing);
	}
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_delayAing( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	{
	TempoSelezionato = 0;
	}
	UxAingContext = UxSaveCtx;
}

static	void	activateCB_startAtAing( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAing                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAingContext;
	UxAingContext = UxContext =
			(_UxCAing *) UxGetContext( UxWidget );
	{
	TempoSelezionato = 1;
	}
	UxAingContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Aing()
{
	Widget		SceltaPert_shell;
	Widget		Configure_shell;
	Widget		menu3_p1_shell;
	char		*UxTmp0;


	/* Creation of Aing */
	Aing = XtVaCreatePopupShell( "Aing",
			topLevelShellWidgetClass,
			UxTopLevel,
			XmNx, 240,
			XmNy, 190,
			XmNwidth, 400,
			XmNheight, 240,
			XmNmwmDecorations, MWM_DECOR_BORDER | MWM_DECOR_MINIMIZE,
			XmNiconName, tagSelect,
			XmNtitle, tagSelect,
			XmNdeleteResponse, XmDO_NOTHING,
			NULL );
	UxPutContext( Aing, (char *) UxAingContext );


	/* Creation of sfondo */
	sfondo = XtVaCreateManagedWidget( "sfondo",
			xmFormWidgetClass,
			Aing,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 520,
			XmNheight, 300,
			NULL );
	UxPutContext( sfondo, (char *) UxAingContext );


	/* Creation of testata */
	testata = XtVaCreateManagedWidget( "testata",
			xmFormWidgetClass,
			sfondo,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 560,
			XmNheight, 60,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( testata, (char *) UxAingContext );


	/* Creation of tag */
	tag = XtVaCreateManagedWidget( "tag",
			xmLabelWidgetClass,
			testata,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 100,
			XmNheight, 40,
			XmNtopOffset, 8,
			XmNleftOffset, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( tag, (char *) UxAingContext );


	/* Creation of unimis */
	unimis = XtVaCreateManagedWidget( "unimis",
			xmLabelWidgetClass,
			testata,
			XmNx, 350,
			XmNy, 10,
			XmNwidth, 100,
			XmNheight, 40,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNleftAttachment, XmATTACH_NONE,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 8,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( unimis, (char *) UxAingContext );


	/* Creation of separator1 */
	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass,
			testata,
			XmNx, 0,
			XmNy, 50,
			XmNwidth, 560,
			XmNheight, 10,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( separator1, (char *) UxAingContext );


	/* Creation of drawingAing */
	drawingAing = XtVaCreateManagedWidget( "drawingAing",
			xmDrawingAreaWidgetClass,
			testata,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 120,
			XmNy, 10,
			XmNwidth, 190,
			XmNheight, 40,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, unimis,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 2,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, tag,
			XmNrightOffset, 10,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( drawingAing, (char *) UxAingContext );


	/* Creation of tasti_label */
	tasti_label = XtVaCreateManagedWidget( "tasti_label",
			xmFormWidgetClass,
			sfondo,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 160,
			XmNy, 70,
			XmNwidth, 380,
			XmNheight, 230,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, testata,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNborderWidth, 0,
			RES_CONVERT( XmNborderColor, "#507050" ),
			NULL );
	UxPutContext( tasti_label, (char *) UxAingContext );


	/* Creation of Stop */
	Stop = XtVaCreateManagedWidget( "Stop",
			xmPushButtonWidgetClass,
			tasti_label,
			XmNx, 220,
			XmNy, 150,
			XmNwidth, 80,
			XmNheight, 40,
			RES_CONVERT( XmNbackground, "#ff0000" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			XmNbottomOffset, 10,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( Stop, XmNactivateCallback,
		(XtCallbackProc) activateCB_Stop,
		(XtPointer) UxAingContext );

	UxPutContext( Stop, (char *) UxAingContext );


	/* Creation of Start */
	Start = XtVaCreateManagedWidget( "Start",
			xmPushButtonWidgetClass,
			tasti_label,
			XmNx, 120,
			XmNy, 150,
			XmNwidth, 80,
			XmNheight, 40,
			RES_CONVERT( XmNbackground, "#00ff00" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_NONE,
			XmNleftOffset, 30,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 5,
			XmNrightWidget, Stop,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( Start, XmNactivateCallback,
		(XtCallbackProc) activateCB_Start,
		(XtPointer) UxAingContext );

	UxPutContext( Start, (char *) UxAingContext );


	/* Creation of SceltaPert */
	SceltaPert_shell = XtVaCreatePopupShell ("SceltaPert_shell",
			xmMenuShellWidgetClass, tasti_label,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	SceltaPert = XtVaCreateWidget( "SceltaPert",
			xmRowColumnWidgetClass,
			SceltaPert_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( SceltaPert, (char *) UxAingContext );

	UxTmp0 = menu_aing[0].descrizione;

	/* Creation of pert_1 */
	pert_1 = XtVaCreateManagedWidget( "pert_1",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_1, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_1,
		(XtPointer) UxAingContext );

	UxPutContext( pert_1, (char *) UxAingContext );

	UxTmp0 = menu_aing[1].descrizione;

	/* Creation of pert_2 */
	pert_2 = XtVaCreateManagedWidget( "pert_2",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_2, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_2,
		(XtPointer) UxAingContext );

	UxPutContext( pert_2, (char *) UxAingContext );

	UxTmp0 = menu_aing[2].descrizione;

	/* Creation of pert_3 */
	pert_3 = XtVaCreateManagedWidget( "pert_3",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_3, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_3,
		(XtPointer) UxAingContext );

	UxPutContext( pert_3, (char *) UxAingContext );

	UxTmp0 = menu_aing[3].descrizione;

	/* Creation of pert_4 */
	pert_4 = XtVaCreateManagedWidget( "pert_4",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_4, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_4,
		(XtPointer) UxAingContext );

	UxPutContext( pert_4, (char *) UxAingContext );

	UxTmp0 = menu_aing[4].descrizione;

	/* Creation of pert_5 */
	pert_5 = XtVaCreateManagedWidget( "pert_5",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_5, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_5,
		(XtPointer) UxAingContext );

	UxPutContext( pert_5, (char *) UxAingContext );

	UxTmp0 = menu_aing[5].descrizione;

	/* Creation of pert_6 */
	pert_6 = XtVaCreateManagedWidget( "pert_6",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_6, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_6,
		(XtPointer) UxAingContext );

	UxPutContext( pert_6, (char *) UxAingContext );


	/* Creation of SceltaPert_b10 */
	SceltaPert_b10 = XtVaCreateManagedWidget( "SceltaPert_b10",
			xmSeparatorWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( SceltaPert_b10, (char *) UxAingContext );

	UxTmp0 = menu_aing[6].descrizione;

	/* Creation of pert_7 */
	pert_7 = XtVaCreateManagedWidget( "pert_7",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_7, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_7,
		(XtPointer) UxAingContext );

	UxPutContext( pert_7, (char *) UxAingContext );

	UxTmp0 = menu_aing[7].descrizione;

	/* Creation of pert_8 */
	pert_8 = XtVaCreateManagedWidget( "pert_8",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_8, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_8,
		(XtPointer) UxAingContext );

	UxPutContext( pert_8, (char *) UxAingContext );


	/* Creation of SceltaPert_b11 */
	SceltaPert_b11 = XtVaCreateManagedWidget( "SceltaPert_b11",
			xmSeparatorWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( SceltaPert_b11, (char *) UxAingContext );

	UxTmp0 = menu_aing[8].descrizione;

	/* Creation of pert_9 */
	pert_9 = XtVaCreateManagedWidget( "pert_9",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_9, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_9,
		(XtPointer) UxAingContext );

	UxPutContext( pert_9, (char *) UxAingContext );

	UxTmp0 = menu_aing[9].descrizione;

	/* Creation of pert_10 */
	pert_10 = XtVaCreateManagedWidget( "pert_10",
			xmPushButtonWidgetClass,
			SceltaPert,
			RES_CONVERT( XmNlabelString, UxTmp0 ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( pert_10, XmNactivateCallback,
		(XtCallbackProc) activateCB_pert_10,
		(XtPointer) UxAingContext );

	UxPutContext( pert_10, (char *) UxAingContext );


	/* Creation of tipo_pert */
	tipo_pert = XtVaCreateManagedWidget( "tipo_pert",
			xmRowColumnWidgetClass,
			tasti_label,
			XmNrowColumnType, XmMENU_OPTION,
			XmNsubMenuId, SceltaPert,
			XmNx, 0,
			XmNy, 190,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftOffset, 0,
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( tipo_pert, (char *) UxAingContext );


	/* Creation of Configure */
	Configure_shell = XtVaCreatePopupShell ("Configure_shell",
			xmMenuShellWidgetClass, tasti_label,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	Configure = XtVaCreateWidget( "Configure",
			xmRowColumnWidgetClass,
			Configure_shell,
			XmNrowColumnType, XmMENU_POPUP,
			XmNmenuAccelerator, "<KeyUp>F4",
			NULL );
	UxPutContext( Configure, (char *) UxAingContext );


	/* Creation of QuitAing */
	QuitAing = XtVaCreateManagedWidget( "QuitAing",
			xmPushButtonWidgetClass,
			Configure,
			RES_CONVERT( XmNlabelString, "Quit" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( QuitAing, XmNactivateCallback,
		(XtCallbackProc) activateCB_QuitAing,
		(XtPointer) UxAingContext );

	UxPutContext( QuitAing, (char *) UxAingContext );


	/* Creation of campo_1 */
	campo_1 = XtVaCreateManagedWidget( "campo_1",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_1, (char *) UxAingContext );


	/* Creation of text_1 */
	text_1 = XtVaCreateManagedWidget( "text_1",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 90,
			XmNy, 0,
			XmNwidth, 80,
			XmNheight, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 100,
			XmNleftWidget, campo_1,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_1, (char *) UxAingContext );


	/* Creation of campo_2 */
	campo_2 = XtVaCreateManagedWidget( "campo_2",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 0,
			XmNy, 30,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_2, (char *) UxAingContext );


	/* Creation of campo_3 */
	campo_3 = XtVaCreateManagedWidget( "campo_3",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 0,
			XmNy, 60,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_3, (char *) UxAingContext );


	/* Creation of campo_4 */
	campo_4 = XtVaCreateManagedWidget( "campo_4",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 0,
			XmNy, 90,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNancestorSensitive, TRUE,
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_4, (char *) UxAingContext );


	/* Creation of campo_5 */
	campo_5 = XtVaCreateManagedWidget( "campo_5",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 200,
			XmNy, 30,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_5, (char *) UxAingContext );


	/* Creation of campo_6 */
	campo_6 = XtVaCreateManagedWidget( "campo_6",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 200,
			XmNy, 0,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_6, (char *) UxAingContext );


	/* Creation of campo_7 */
	campo_7 = XtVaCreateManagedWidget( "campo_7",
			xmLabelWidgetClass,
			tasti_label,
			XmNx, 200,
			XmNy, 60,
			XmNwidth, 90,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNalignment, XmALIGNMENT_END,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( campo_7, (char *) UxAingContext );


	/* Creation of text_3 */
	text_3 = XtVaCreateManagedWidget( "text_3",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 100,
			XmNy, 60,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_3, (char *) UxAingContext );


	/* Creation of text_4 */
	text_4 = XtVaCreateManagedWidget( "text_4",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 100,
			XmNy, 90,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_4, (char *) UxAingContext );


	/* Creation of text_5 */
	text_5 = XtVaCreateManagedWidget( "text_5",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 300,
			XmNy, 0,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_5, (char *) UxAingContext );


	/* Creation of text_6 */
	text_6 = XtVaCreateManagedWidget( "text_6",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 300,
			XmNy, 30,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_6, (char *) UxAingContext );


	/* Creation of text_7 */
	text_7 = XtVaCreateManagedWidget( "text_7",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 300,
			XmNy, 60,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_7, (char *) UxAingContext );


	/* Creation of text_2 */
	text_2 = XtVaCreateManagedWidget( "text_2",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 100,
			XmNy, 30,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( text_2, (char *) UxAingContext );


	/* Creation of menu3_p1 */
	menu3_p1_shell = XtVaCreatePopupShell ("menu3_p1_shell",
			xmMenuShellWidgetClass, tasti_label,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu3_p1 = XtVaCreateWidget( "menu3_p1",
			xmRowColumnWidgetClass,
			menu3_p1_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu3_p1, (char *) UxAingContext );


	/* Creation of delayAing */
	delayAing = XtVaCreateManagedWidget( "delayAing",
			xmPushButtonWidgetClass,
			menu3_p1,
			RES_CONVERT( XmNlabelString, "Delay" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( delayAing, XmNactivateCallback,
		(XtCallbackProc) activateCB_delayAing,
		(XtPointer) UxAingContext );

	UxPutContext( delayAing, (char *) UxAingContext );


	/* Creation of startAtAing */
	startAtAing = XtVaCreateManagedWidget( "startAtAing",
			xmPushButtonWidgetClass,
			menu3_p1,
			RES_CONVERT( XmNlabelString, "Start at" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( startAtAing, XmNactivateCallback,
		(XtCallbackProc) activateCB_startAtAing,
		(XtPointer) UxAingContext );

	UxPutContext( startAtAing, (char *) UxAingContext );


	/* Creation of timeAing */
	timeAing = XtVaCreateManagedWidget( "timeAing",
			xmRowColumnWidgetClass,
			tasti_label,
			XmNrowColumnType, XmMENU_OPTION,
			XmNsubMenuId, menu3_p1,
			XmNy, 90,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNbottomAttachment, XmATTACH_NONE,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 200,
			XmNleftWidget, tipo_pert,
			NULL );
	UxPutContext( timeAing, (char *) UxAingContext );


	/* Creation of TextFieldTempo */
	TextFieldTempo = XtVaCreateManagedWidget( "TextFieldTempo",
			xmTextFieldWidgetClass,
			tasti_label,
			XmNx, 300,
			XmNy, 90,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNmarginHeight, 5,
			XmNmarginWidth, 5,
			NULL );
	UxPutContext( TextFieldTempo, (char *) UxAingContext );


	XtAddCallback( Aing, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxAingContext);

	XtAddEventHandler(tasti_label, ButtonPressMask,
			False, (XtEventHandler) _UxAingMenuPost, (XtPointer) Configure );

	return ( Aing );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_Aing( _UxrigaAing, _UxPadreAing )
	unsigned char	*_UxrigaAing;
	Widget	_UxPadreAing;
{
	Widget                  rtrn;
	_UxCAing                *UxContext;
	static int		_Uxinit = 0;

	UxAingContext = UxContext =
		(_UxCAing *) UxNewContext( sizeof(_UxCAing), False );

	rigaAing = _UxrigaAing;
	PadreAing = _UxPadreAing;

	if ( ! _Uxinit )
	{
		_UxIfClassId = UxNewClassId();
		UxAing_start_enable_Id = UxMethodRegister( _UxIfClassId,
					UxAing_start_enable_Name,
					_Aing_start_enable );
		_Uxinit = 1;
	}

	{
		char c1[20],c2[20],c3[20],c4[20],c5[20],c6[20],c7[20];
		Pixmap pix;
		Atom WM_DELETE_WINDOW; /* per close con MWM*/
		
		if(!CanOpenPage(PadreAing))
			return(NULL);
		
		
		sscanf(rigaAing,"%s %s %s %s %s %s %s",tagSelect,c2,c3,c4,c5,c6,unimisSelect);
		aSelect=atof(c5);
		bSelect=atof(c6);
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabelAing,XtDisplay(PadreAing)))
			exit(0);
#endif
		PertSelezionata = 0;
		TempoSelezionato = 0;
		rtrn = _Uxbuild_Aing();
		UxPutClassCode( Aing, _UxIfClassId );

		set_something(tag,XmNfontList,(void*) FontLabelAing);
		set_something(unimis,XmNfontList,(void*) FontLabelAing);
		set_something(Start,XmNfontList,(void*) FontLabelAing);
		set_something(Stop,XmNfontList,(void*) FontLabelAing);
		set_something(tag,XmNlabelString,
		                 (void*) XmStringCreateLtoR(tagSelect,XmSTRING_DEFAULT_CHARSET));
		set_something(unimis,XmNlabelString,
		                 (void*) XmStringCreateLtoR(unimisSelect,XmSTRING_DEFAULT_CHARSET));
#ifndef DESIGN_TIME
		LoadBitmap(testata,&pix,page_aing_icon_bits,page_aing_icon_width,
				page_aing_icon_height);
#endif
		set_something(rtrn,XmNiconPixmap,(void*) pix);
		CreaIndicatore(drawingAing);
#ifndef DESIGN_TIME
		if((key_refresh_aing=
			InsElencoPagine("__AING__",lista_wid_aing,num_wid_aing,
					REFRESH_AING/1000)) == -1)
			return(NULL);
#endif
		
		UxPopupInterface(rtrn, no_grab);
		ConfigureAing(rtrn,0);
#ifndef DESIGN_TIME
		timer_refresh_aing = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (PadreAing),
		            (unsigned long) REFRESH_AING ,refresh_aing, UxContext);
#endif
		WM_DELETE_WINDOW=XmInternAtom(XtDisplay(Aing),"WM_DELETE_WINDOW",False);
		XmAddWMProtocolCallback(Aing,WM_DELETE_WINDOW,activateCB_QuitAing,NULL);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

