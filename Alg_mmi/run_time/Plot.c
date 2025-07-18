
/*******************************************************************************
       Plot.c
       (Generated from interface file Plot.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo Plot.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)Plot.i	5.2
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


#ifndef DESIGN_TIME
#include <Xl/Xl.h>
#endif

#include <Ol/OlDatabasePunti.h>

#ifdef SCO_UNIX
#include <Xm/MwmUtil.h>
#else
/*
#include <X11/MwmUtil.h>
*/
#include <Xm/MwmUtil.h>
#endif


#include <Ol/OlPert.h>
#include "other.h"

#include "page_plot_icon.bmp"

extern OlDatabasePuntiObject database_simulatore;
static void CreaGrafico( );
void DestroyPlot( );
static void refresh_plot( );


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
	Widget	UxPlot;
	Widget	UxsfondoPlot;
	Widget	UxdrawingPlot;
	Widget	UxmenuClosePlot;
	Widget	UxClosePlot;
	unsigned char	UxplotSelect[20];
	unsigned char	UxplotunimisSelect[20];
	float	UxaplotSelect;
	float	UxbplotSelect;
	Widget	UxtopLevel_selezionataPlot;
	XtIntervalId	Uxtimer_refresh_plot;
	XmFontList	UxFontLabelPlot;
	int	Uxkey_refresh_plot;
	WidgetList	Uxlista_wid_plot;
	int	Uxnum_wid_plot;
	int	UxindplotSelect;
	XrmDatabase	UxRisDb;
	unsigned char	*UxrigaPlot;
	Widget	UxPadrePlot;
} _UxCPlot;

static _UxCPlot                *UxPlotContext;
#define Plot                    UxPlotContext->UxPlot
#define sfondoPlot              UxPlotContext->UxsfondoPlot
#define drawingPlot             UxPlotContext->UxdrawingPlot
#define menuClosePlot           UxPlotContext->UxmenuClosePlot
#define ClosePlot               UxPlotContext->UxClosePlot
#define plotSelect              UxPlotContext->UxplotSelect
#define plotunimisSelect        UxPlotContext->UxplotunimisSelect
#define aplotSelect             UxPlotContext->UxaplotSelect
#define bplotSelect             UxPlotContext->UxbplotSelect
#define topLevel_selezionataPlot UxPlotContext->UxtopLevel_selezionataPlot
#define timer_refresh_plot      UxPlotContext->Uxtimer_refresh_plot
#define FontLabelPlot           UxPlotContext->UxFontLabelPlot
#define key_refresh_plot        UxPlotContext->Uxkey_refresh_plot
#define lista_wid_plot          UxPlotContext->Uxlista_wid_plot
#define num_wid_plot            UxPlotContext->Uxnum_wid_plot
#define indplotSelect           UxPlotContext->UxindplotSelect
#define RisDb                   UxPlotContext->UxRisDb
#define rigaPlot                UxPlotContext->UxrigaPlot
#define PadrePlot               UxPlotContext->UxPadrePlot


/*******************************************************************************
       The following function is an event-handler for posting menus.
*******************************************************************************/

static void	_UxPlotMenuPost( wgt, client_data, event, ctd )
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;
	int		ctd;

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

Widget	popup_Plot();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void DestroyPlot(Widget w)
{
#ifndef DESIGN_TIME
_UxCPlot *Context;

        Context =(_UxCPlot *) UxGetContext(w);	
	DelElencoPagine(Context->Uxkey_refresh_plot, 
		Context->UxdrawingPlot);
	XSync(XtDisplay(w),False);
	XtRemoveTimeOut(Context->Uxtimer_refresh_plot);
	XtDestroyWidget(Context->UxPlot);
	XrmDestroyDatabase(Context->UxRisDb);
#endif
}




static void CreaGrafico(Widget Drawing)
{
#ifndef DESIGN_TIME
_UxCPlot *Context;
XrmDatabase SaveDb;
Display *display;

	WriteDbPlot();	
        Context =(_UxCPlot *) UxGetContext(Drawing);
	RisDb=XrmGetFileDatabase("TemplateGrafPlot.rtf");
	display=XtDisplay(Drawing);
	SaveDb=display->db;
	
	display->db=RisDb;
	CreaPagina(Context->UxdrawingPlot,&(Context->Uxlista_wid_plot),
		 &(Context->Uxnum_wid_plot));
	Context->UxindplotSelect = SettaGrafPlot(Context->Uxlista_wid_plot[0],Context->UxrigaPlot,
		Context->UxaplotSelect,Context->UxbplotSelect);
	display->db=SaveDb;
	
#endif
}

#ifndef DESIGN_TIME
static void refresh_plot(_UxCPlot *Context)
#else
static void refresh_plot()
#endif
{
#ifndef DESIGN_TIME
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_plot))
        {
        show_warning("Error in refresh");
        return;
        }
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_plot))
     XlRefreshWidget(Context->Uxlista_wid_plot,Context->Uxnum_wid_plot);
	
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_plot))
        {
        show_warning("Error in refresh");
        return;
        }
/*
        carica il timer per il refresh
*/
Context->Uxtimer_refresh_plot = XtAppAddTimeOut (
            XtWidgetToApplicationContext (Context->UxPlot),
            (unsigned long) REFRESH_PLOT ,(XtTimerCallbackProc)refresh_plot, Context);
#endif	
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	resizeCB_drawingPlot( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCPlot                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPlotContext;
	UxPlotContext = UxContext =
			(_UxCPlot *) UxGetContext( UxWidget );
	{
	Dimension w,h;
	
	
	get_something(drawingPlot,XmNwidth,(void*) &w);
	get_something(drawingPlot,XmNheight,(void*) &h);
	
	printf("Eseguito resize sulla plot  w=%d  h=%d\n",w,h);
	w -=20;
	h -=20;
	
	set_something_val(lista_wid_plot[0],XlNwidth0,(XtArgVal) w);
	set_something_val(lista_wid_plot[0],XlNheight0,(XtArgVal)h);
	}
	UxPlotContext = UxSaveCtx;
}

static	void	activateCB_ClosePlot( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCPlot                *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPlotContext;
	UxPlotContext = UxContext =
			(_UxCPlot *) UxGetContext( UxWidget );
	{
	DestroyPlot(UxWidget);
	}
	UxPlotContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Plot()
{
	Widget		menuClosePlot_shell;


	/* Creation of Plot */
	Plot = XtVaCreatePopupShell( "Plot",
			topLevelShellWidgetClass,
			UxTopLevel,
			XmNx, 260,
			XmNy, 330,
			XmNwidth, 400,
			XmNheight, 240,
			XmNmwmDecorations, MWM_DECOR_BORDER | MWM_DECOR_MINIMIZE | MWM_DECOR_RESIZEH,
			XmNiconName, plotSelect,
			XmNtitle, plotSelect,
			XmNminHeight, 100,
			XmNminWidth, 200,
			NULL );
	UxPutContext( Plot, (char *) UxPlotContext );


	/* Creation of sfondoPlot */
	sfondoPlot = XtVaCreateManagedWidget( "sfondoPlot",
			xmFormWidgetClass,
			Plot,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 0,
			XmNy, 10,
			XmNwidth, 280,
			XmNheight, 180,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( sfondoPlot, (char *) UxPlotContext );


	/* Creation of drawingPlot */
	drawingPlot = XtVaCreateManagedWidget( "drawingPlot",
			xmDrawingAreaWidgetClass,
			sfondoPlot,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 380,
			XmNheight, 220,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( drawingPlot, XmNresizeCallback,
		(XtCallbackProc) resizeCB_drawingPlot,
		(XtPointer) UxPlotContext );

	UxPutContext( drawingPlot, (char *) UxPlotContext );


	/* Creation of menuClosePlot */
	menuClosePlot_shell = XtVaCreatePopupShell ("menuClosePlot_shell",
			xmMenuShellWidgetClass, drawingPlot,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menuClosePlot = XtVaCreateWidget( "menuClosePlot",
			xmRowColumnWidgetClass,
			menuClosePlot_shell,
			XmNrowColumnType, XmMENU_POPUP,
			NULL );
	UxPutContext( menuClosePlot, (char *) UxPlotContext );


	/* Creation of ClosePlot */
	ClosePlot = XtVaCreateManagedWidget( "ClosePlot",
			xmPushButtonWidgetClass,
			menuClosePlot,
			RES_CONVERT( XmNlabelString, "Close" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( ClosePlot, XmNactivateCallback,
		(XtCallbackProc) activateCB_ClosePlot,
		(XtPointer) UxPlotContext );

	UxPutContext( ClosePlot, (char *) UxPlotContext );


	XtAddCallback( Plot, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxPlotContext);

	XtAddEventHandler(drawingPlot, ButtonPressMask,
			False, (XtEventHandler) _UxPlotMenuPost, (XtPointer) menuClosePlot );

	return ( Plot );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_Plot( _UxrigaPlot, _UxPadrePlot )
	unsigned char	*_UxrigaPlot;
	Widget	_UxPadrePlot;
{
	Widget                  rtrn;
	_UxCPlot                *UxContext;

	UxPlotContext = UxContext =
		(_UxCPlot *) UxNewContext( sizeof(_UxCPlot), False );

	rigaPlot = _UxrigaPlot;
	PadrePlot = _UxPadrePlot;

	{
		char c1[20],c2[20],c3[20],c4[20],c5[20],c6[20],c7[20];
		Pixmap pix;
		
		if(!CanOpenPage(PadrePlot))
			return(NULL);
		
		sscanf(rigaPlot,"%s %s %s %s %s %s %s",plotSelect,c2,c3,c4,c5,c6,plotunimisSelect);
		aplotSelect=atof(c5);
		bplotSelect=atof(c6);
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabelPlot,XtDisplay(PadrePlot)))
			exit(0);
#endif
		rtrn = _Uxbuild_Plot();

		set_something_val(ClosePlot,XmNfontList,(XtArgVal)FontLabelPlot);
		
#ifndef DESIGN_TIME
		LoadBitmap(drawingPlot,&pix,page_plot_icon_bits,page_plot_icon_width,
				page_plot_icon_height);
#endif
		set_something_val(rtrn,XmNiconPixmap,(XtArgVal)pix);
		
		CreaGrafico(drawingPlot);
#ifndef DESIGN_TIME
		if((key_refresh_plot=
			InsElencoPagine("__PLOT__",lista_wid_plot,num_wid_plot,
					REFRESH_PLOT/1000)) == -1)
			return(NULL);
#endif
		
		UxPopupInterface(rtrn, no_grab);
#ifndef DESIGN_TIME
		timer_refresh_plot = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (PadrePlot),
		            (unsigned long) REFRESH_PLOT ,(XtTimerCallbackProc)refresh_plot, UxContext);
#endif
		
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

