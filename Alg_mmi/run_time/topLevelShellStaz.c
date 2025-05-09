
/*******************************************************************************
       topLevelShellStaz.c
       (Generated from interface file topLevelShellStaz.i)
       Associated Resource file: topLevelShellStaz.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Separator.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo topLevelShellStaz.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)topLevelShellStaz.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <X11/Xlib.h>
#ifdef SCO_UNIX
#include <Xm/MwmUtil.h>
#else
#include <Xm/MwmUtil.h>
#endif

#ifndef DESIGN_TIME
#include <Xl/Xl.h>
#endif

#ifndef DESIGN_TIME
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#else
#include <Xl/XlCore.h>
#include <Xl/XlManager.h>
#endif

#include <Xl/XlChangePage.h>
#include <Ol/OlDatabasePunti.h>

#ifndef DESIGN_TIME
#include <Ol/OlPertP.h>
#else
#include <Ol/OlPert.h>
#endif
#include <Xm/Protocols.h>
#include "page_staz_icon.bmp"

#include "other.h"
#include "res_edit.h"


extern OlDatabasePuntiObject database_simulatore;
extern OlPertObject pert;
extern AN_PAG *pagine;
extern Boolean topologia_on;
                  
static void refresh_page( );
void SetCursorWaitStaz( );
static void activateCB_menu1_p1_b1();


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
	Widget	UxtopLevelShellStaz;
	Widget	UxformStaz;
	Widget	UxscrolledWindowStaz;
	Widget	UxdrawingAreaStaz;
	Widget	Uxmenu1;
	Widget	Uxmenu1_p2;
	Widget	Uxmenu1_p2_b1;
	Widget	Uxmenu1_p2_b2;
	Widget	Uxmenu1_p1_b3;
	Widget	Uxmenu1_p1_b4;
	Widget	Uxmenu1_p1_b1;
	Widget	UxtopLevel_selezionataStaz;
	XtIntervalId	Uxtimer_refresh_staz;
	WidgetList	Uxlista_widStaz;
	int	Uxnum_widStaz;
	Region	Uxregion_staz;
	XmFontList	UxFontLabelStaz;
	int	Uxkey_refresh_staz;
	int	Uxtime_ref_staz;
	BCK_OBJ	*Uxbkg_stazioni;
	Widget	UxListaWidVarStaz[7];
	Widget	Uxwid_attesa_staz;
	int	Uxattesa_staz;
	int	Uxcursor_wait_set_staz;
	Cursor	Uxcursor_wait_staz;
	XrmDatabase	Uxpag_db;
	Pixmap	Uxdrawing_pixmap;
	unsigned char	*UxPaginaStaz;
	Widget	UxPadreStaz;
	unsigned char	*Uxnome_dispStaz;
	BCK_OBJ	*Uxsfondo_staz;
} _UxCtopLevelShellStaz;

static _UxCtopLevelShellStaz   *UxTopLevelShellStazContext;
#define topLevelShellStaz       UxTopLevelShellStazContext->UxtopLevelShellStaz
#define formStaz                UxTopLevelShellStazContext->UxformStaz
#define scrolledWindowStaz      UxTopLevelShellStazContext->UxscrolledWindowStaz
#define drawingAreaStaz         UxTopLevelShellStazContext->UxdrawingAreaStaz
#define menu1                   UxTopLevelShellStazContext->Uxmenu1
#define menu1_p2                UxTopLevelShellStazContext->Uxmenu1_p2
#define menu1_p2_b1             UxTopLevelShellStazContext->Uxmenu1_p2_b1
#define menu1_p2_b2             UxTopLevelShellStazContext->Uxmenu1_p2_b2
#define menu1_p1_b3             UxTopLevelShellStazContext->Uxmenu1_p1_b3
#define menu1_p1_b4             UxTopLevelShellStazContext->Uxmenu1_p1_b4
#define menu1_p1_b1             UxTopLevelShellStazContext->Uxmenu1_p1_b1
#define topLevel_selezionataStaz UxTopLevelShellStazContext->UxtopLevel_selezionataStaz
#define timer_refresh_staz      UxTopLevelShellStazContext->Uxtimer_refresh_staz
#define lista_widStaz           UxTopLevelShellStazContext->Uxlista_widStaz
#define num_widStaz             UxTopLevelShellStazContext->Uxnum_widStaz
#define region_staz             UxTopLevelShellStazContext->Uxregion_staz
#define FontLabelStaz           UxTopLevelShellStazContext->UxFontLabelStaz
#define key_refresh_staz        UxTopLevelShellStazContext->Uxkey_refresh_staz
#define time_ref_staz           UxTopLevelShellStazContext->Uxtime_ref_staz
#define bkg_stazioni            UxTopLevelShellStazContext->Uxbkg_stazioni
#define ListaWidVarStaz         UxTopLevelShellStazContext->UxListaWidVarStaz
#define wid_attesa_staz         UxTopLevelShellStazContext->Uxwid_attesa_staz
#define attesa_staz             UxTopLevelShellStazContext->Uxattesa_staz
#define cursor_wait_set_staz    UxTopLevelShellStazContext->Uxcursor_wait_set_staz
#define cursor_wait_staz        UxTopLevelShellStazContext->Uxcursor_wait_staz
#define pag_db                  UxTopLevelShellStazContext->Uxpag_db
#define drawing_pixmap          UxTopLevelShellStazContext->Uxdrawing_pixmap
#define PaginaStaz              UxTopLevelShellStazContext->UxPaginaStaz
#define PadreStaz               UxTopLevelShellStazContext->UxPadreStaz
#define nome_dispStaz           UxTopLevelShellStazContext->Uxnome_dispStaz
#define sfondo_staz             UxTopLevelShellStazContext->Uxsfondo_staz


/*******************************************************************************
       The following function is an event-handler for posting menus.
*******************************************************************************/

static void	_UxtopLevelShellStazMenuPost( wgt, client_data, event, ctd )
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;
	int ctd;

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

Widget	popup_topLevelShellStaz();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void SetCursorWaitStaz(Widget w)
{
#ifndef DESIGN_TIME
_UxCtopLevelShellStaz *Context;
Context =(_UxCtopLevelShellStaz *) UxGetContext( w);

XlSetCursor(Context->UxdrawingAreaStaz,Context->Uxcursor_wait_staz);
Context->Uxcursor_wait_set_staz = 1;

#endif
}

void UnsetCursorWaitStaz(Widget w)
{
#ifndef DESIGN_TIME
_UxCtopLevelShellStaz *Context;
Context =(_UxCtopLevelShellStaz *) UxGetContext( w);

if(Context->Uxcursor_wait_set_staz == 1)
	{
	Context->Uxcursor_wait_set_staz = 0;
	XlUnsetCursor(Context->UxdrawingAreaStaz);
	}
#endif
}

void IcoSelectStaz(w)
 Widget w;
{
XlCoreWidget wcore;
XlManagerWidget wmanager;
Widget drawing;
#ifndef DESIGN_TIME
_UxCtopLevelShellStaz *Context;
#endif
 

#ifndef DESIGN_TIME
/* Ricavo il context */
drawing=XtParent(w);

#ifndef DESIGN_TIME
if(XlIsXlComposite(drawing))
	drawing=XtParent(drawing);
#endif

Context =(_UxCtopLevelShellStaz *) UxGetContext( drawing);
#endif
printf("IcoSelectStaz\n");
#ifndef DESIGN_TIME
		if(XlIsGraficoSingle(w))
		    {
		/*
		Uso la ActivateChangeVar solo quando mmi e' invocato 
		con il flag -Topologia. (ActivateChangeVar utilizza il Variable
		Editor che utilizza la topologia caricata in shm).
		*/
		    if(topologia_on)			
		        if(!ActivateChangeVar(w,Context->UxdrawingAreaStaz,
				&(Context->UxListaWidVarStaz[0])))
			    popup_errorDialog("Error changig tag",
				Context->UxdrawingAreaStaz);
		    }
#endif


}

#ifndef DESIGN_TIME
static void refresh_page(_UxCtopLevelShellStaz *Context)
#else
static void refresh_page()
#endif
{
int i;
#ifndef DESIGN_TIME
if(Context->Uxattesa_staz != -1)
	{
	++ Context->Uxattesa_staz;
	if(Context->Uxattesa_staz ==2)
		{
		Context->Uxwid_attesa_staz=popup_Attesa(Context->UxdrawingAreaStaz);
		
		}
	}
if(Context->Uxwid_attesa_staz != NULL)
	SettaAttesa(Context->Uxwid_attesa_staz,Context->Uxtime_ref_staz);

if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_staz))
        {
        show_warning("Error in refresh");
        return;
        }
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_staz))   
   {
   Context->Uxattesa_staz = -1;
   if(Context->Uxwid_attesa_staz != NULL)
	{
	XtDestroyWidget(Context->Uxwid_attesa_staz);
	Context->Uxwid_attesa_staz=NULL;
	}
	UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);
	XlRefreshWidget(Context->Uxlista_widStaz,Context->Uxnum_widStaz);

   }
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_staz))
        {
        show_warning("Error in refresh");
        return;
        }
/*
        carica il timer per il refresh
*/
Context->Uxtimer_refresh_staz = XtAppAddTimeOut (
            XtWidgetToApplicationContext (Context->UxtopLevelShellStaz),
            (unsigned long) (Context->Uxtime_ref_staz*100) ,
		(XtTimerCallbackProc)refresh_page, Context);
#endif
}

void PageStazSelect(Widget w, char *nomePagina, int tipoApertura)
{
Widget Pagina_new = NULL;
#ifndef DESIGN_TIME
_UxCtopLevelShellStaz *Context;
int num_pag;

Context =(_UxCtopLevelShellStaz *) UxGetContext(w);

SetCursorWaitStaz(Context->UxdrawingAreaStaz);

if(nomePagina!=NULL)
     {
	if(tipoApertura != CLOSE_PAGE)
	{
        if(!PaginaAperta(Context->UxtopLevel_selezionataStaz,nomePagina))
                {
	if(!CanOpenPage(w))
		{
		UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);
		return;
		}
		
        num_pag=NumeroPagina(nomePagina);
        Pagina_new=create_topLevelShell1(nomePagina,
                        Context->UxtopLevel_selezionataStaz,
                        Context->Uxnome_dispStaz,pagine[num_pag].sfondo);
        if(Pagina_new==NULL)
                {
                popup_errorDialog("Errore Creazione pagina",
                        w/*Context->UxdrawingAreaStaz*/);
		UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);
                return;
                }
                }
	}
        if((tipoApertura == CHANGE_PAGE)||(tipoApertura == CLOSE_PAGE))
                {
		DelElencoPagine(Context->Uxkey_refresh_staz, 
			Context->UxdrawingAreaStaz);
		XSync(XtDisplay(w),False);
                XtRemoveTimeOut(Context->Uxtimer_refresh_staz);
                XtDestroyWidget(Context->UxtopLevelShellStaz);
                }
        }
UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);
#endif	
}

void ClosePageStaz(Widget w)
{
#ifndef DESIGN_TIME
_UxCtopLevelShellStaz *Context;
 
	Context =(_UxCtopLevelShellStaz *) UxGetContext(w);
        DelElencoPagine(Context->Uxkey_refresh_staz, 
		Context->UxdrawingAreaStaz);
	XSync(XtDisplay(w),False);
	XtRemoveTimeOut(Context->Uxtimer_refresh_staz);
	XlFreeCursor(Context->UxtopLevelShellStaz,Context->Uxcursor_wait_staz);
	if(drawing_pixmap)
		XFreePixmap(XtDisplay(w),drawing_pixmap);
	XtDestroyWidget(Context->UxtopLevelShellStaz);
        XrmDestroyDatabase(Context->Uxpag_db);
	printf("Close Page Stazioni\n");
#endif
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	exposeCB_drawingAreaStaz( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShellStaz   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShellStazContext;
	UxTopLevelShellStazContext = UxContext =
			(_UxCtopLevelShellStaz *) UxGetContext( UxWidget );
	{
	disegna_bck(UxWidget,bkg_stazioni,UxCallbackArg,&(region_staz),False);
	}
	UxTopLevelShellStazContext = UxSaveCtx;
}

static	void	activateCB_menu1_p2_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShellStaz   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShellStazContext;
	UxTopLevelShellStazContext = UxContext =
			(_UxCtopLevelShellStaz *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	if(!PrintScreen(drawingAreaStaz,nome_dispStaz,PaginaStaz,False,bkg_stazioni))
		popup_errorDialog("Printer not available",drawingAreaStaz);
#endif
	}
	UxTopLevelShellStazContext = UxSaveCtx;
}

static	void	activateCB_menu1_p2_b2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShellStaz   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShellStazContext;
	UxTopLevelShellStazContext = UxContext =
			(_UxCtopLevelShellStaz *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	if(PrintSetup(drawingAreaStaz)==NULL)
		popup_errorDialog("Printer not available",drawingAreaStaz);
#endif
	}
	UxTopLevelShellStazContext = UxSaveCtx;
}

static	void	activateCB_menu1_p1_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShellStaz   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShellStazContext;
	UxTopLevelShellStazContext = UxContext =
			(_UxCtopLevelShellStaz *) UxGetContext( UxWidget );
	{
	printf("Chiusura della pagina\n");
	if(!CanClosePage(PaginaStaz))
		{
		popup_errorDialog("Unable to close this page",drawingAreaStaz);
		return;
		}
#ifndef DESIGN_TIME
	popup_CloseQuestion(topLevelShellStaz,drawingAreaStaz,&(timer_refresh_staz),
		key_refresh_staz);
#endif
	
	}
	UxTopLevelShellStazContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_topLevelShellStaz()
{
	Widget		_UxParent;
	Widget		menu1_shell;
	Widget		menu1_p2_shell;


	/* Creation of topLevelShellStaz */
	_UxParent = topLevel_selezionataStaz;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	topLevelShellStaz = XtVaCreatePopupShell( "topLevelShellStaz",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 110,
			XmNy, 30,
			XmNwidth, 1060,
			XmNheight, 900,
			RES_CONVERT( XmNbackground, "#000000" ),
			XmNmwmDecorations, MWM_DECOR_TITLE | MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE | MWM_DECOR_MAXIMIZE,
			XmNdeleteResponse, XmDO_NOTHING,
			NULL );
	UxPutContext( topLevelShellStaz, (char *) UxTopLevelShellStazContext );


	/* Creation of formStaz */
	formStaz = XtVaCreateManagedWidget( "formStaz",
			xmFormWidgetClass,
			topLevelShellStaz,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 880,
			XmNheight, 870,
			NULL );
	UxPutContext( formStaz, (char *) UxTopLevelShellStazContext );


	/* Creation of scrolledWindowStaz */
	scrolledWindowStaz = XtVaCreateManagedWidget( "scrolledWindowStaz",
			xmScrolledWindowWidgetClass,
			formStaz,
			XmNscrollingPolicy, XmAUTOMATIC,
			XmNx, 10,
			XmNy, 0,
			XmNwidth, 1100,
			XmNheight, 940,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( scrolledWindowStaz, (char *) UxTopLevelShellStazContext );


	/* Creation of drawingAreaStaz */
	drawingAreaStaz = XtVaCreateManagedWidget( "drawingAreaStaz",
			xmDrawingAreaWidgetClass,
			scrolledWindowStaz,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 4,
			XmNy, 14,
			XmNwidth, 1200,
			XmNheight, 1190,
			RES_CONVERT( XmNbackground, "#000000" ),
			RES_CONVERT( XmNborderColor, "#000000" ),
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	XtAddCallback( drawingAreaStaz, XmNexposeCallback,
		(XtCallbackProc) exposeCB_drawingAreaStaz,
		(XtPointer) UxTopLevelShellStazContext );

	UxPutContext( drawingAreaStaz, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1 */
	menu1_shell = XtVaCreatePopupShell ("menu1_shell",
			xmMenuShellWidgetClass, drawingAreaStaz,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1 = XtVaCreateWidget( "menu1",
			xmRowColumnWidgetClass,
			menu1_shell,
			XmNrowColumnType, XmMENU_POPUP,
			XmNmenuAccelerator, "<KeyUp>F4",
			NULL );
	UxPutContext( menu1, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p2 */
	menu1_p2_shell = XtVaCreatePopupShell ("menu1_p2_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1_p2 = XtVaCreateWidget( "menu1_p2",
			xmRowColumnWidgetClass,
			menu1_p2_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu1_p2, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p2_b1 */
	menu1_p2_b1 = XtVaCreateManagedWidget( "menu1_p2_b1",
			xmPushButtonWidgetClass,
			menu1_p2,
			RES_CONVERT( XmNlabelString, "print" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu1_p2_b1, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu1_p2_b1,
		(XtPointer) UxTopLevelShellStazContext );

	UxPutContext( menu1_p2_b1, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p2_b2 */
	menu1_p2_b2 = XtVaCreateManagedWidget( "menu1_p2_b2",
			xmPushButtonWidgetClass,
			menu1_p2,
			RES_CONVERT( XmNlabelString, "Printer setup" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu1_p2_b2, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu1_p2_b2,
		(XtPointer) UxTopLevelShellStazContext );

	UxPutContext( menu1_p2_b2, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p1_b3 */
	menu1_p1_b3 = XtVaCreateManagedWidget( "menu1_p1_b3",
			xmCascadeButtonWidgetClass,
			menu1,
			RES_CONVERT( XmNlabelString, "Harcopy" ),
			XmNsubMenuId, menu1_p2,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu1_p1_b3, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p1_b4 */
	menu1_p1_b4 = XtVaCreateManagedWidget( "menu1_p1_b4",
			xmSeparatorWidgetClass,
			menu1,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu1_p1_b4, (char *) UxTopLevelShellStazContext );


	/* Creation of menu1_p1_b1 */
	menu1_p1_b1 = XtVaCreateManagedWidget( "menu1_p1_b1",
			xmPushButtonWidgetClass,
			menu1,
			RES_CONVERT( XmNlabelString, "Close the page" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu1_p1_b1, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu1_p1_b1,
		(XtPointer) UxTopLevelShellStazContext );

	UxPutContext( menu1_p1_b1, (char *) UxTopLevelShellStazContext );


	XtAddCallback( topLevelShellStaz, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTopLevelShellStazContext);

	XtAddEventHandler(drawingAreaStaz, ButtonPressMask,
			False, (XtEventHandler) _UxtopLevelShellStazMenuPost, (XtPointer) menu1 );

	return ( topLevelShellStaz );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_topLevelShellStaz( _UxPaginaStaz, _UxPadreStaz, _Uxnome_dispStaz, _Uxsfondo_staz )
	unsigned char	*_UxPaginaStaz;
	Widget	_UxPadreStaz;
	unsigned char	*_Uxnome_dispStaz;
	BCK_OBJ	*_Uxsfondo_staz;
{
	Widget                  rtrn;
	_UxCtopLevelShellStaz   *UxContext;
	static int		_Uxinit = 0;

	UxTopLevelShellStazContext = UxContext =
		(_UxCtopLevelShellStaz *) UxNewContext( sizeof(_UxCtopLevelShellStaz), False );

	PaginaStaz = _UxPaginaStaz;
	PadreStaz = _UxPadreStaz;
	nome_dispStaz = _Uxnome_dispStaz;
	sfondo_staz = _Uxsfondo_staz;

	if ( ! _Uxinit )
	{
		UxLoadResources( "topLevelShellStaz.rf" );
		_Uxinit = 1;
	}

	{
		int top_x,top_y,top_width,top_height,drawing_width,drawing_height;
		char *top_tipo, *top_descrizione;
		Pixel *drawing_background;
		int dim[4];
		int num_b;
		Pixmap pix;
		Atom WM_DELETE_WINDOW; /* per close con MWM*/
		printf("Selezionata la Pagina di stazioni %s\n",PaginaStaz);
		
		topLevel_selezionataStaz=PadreStaz;
		cursor_wait_set_staz = 0;
		drawing_pixmap=0;
#ifndef DESIGN_TIME
		if(!(pag_db=CaricaDB(XtDisplay(topLevel_selezionataStaz),PaginaStaz)))
			return(False);
		
		
		if(!GetResTopLevel(PadreStaz,&top_x,&top_y,&top_width,&top_height,&time_ref_staz,
				&top_tipo,&top_descrizione))
			return(False);
		if(!GetResDrawing(PadreStaz,&drawing_width,&drawing_height,(Pixel *)&drawing_background, &drawing_pixmap))
				return(False);
#endif
		printf("Caricate le risorse\n");
		rtrn = _Uxbuild_topLevelShellStaz();

		/*
		  inizializza la regione di ridisegno
		*/
		if(sfondo_staz!=NULL)
			{
		 	num_b=1;
		 	while(sfondo_staz[num_b-1].tipo>0)
		  		num_b++;
		 	(bkg_stazioni)=(BCK_OBJ*)XtCalloc(num_b,sizeof(BCK_OBJ));
		 	memcpy((bkg_stazioni),sfondo_staz,num_b*sizeof(BCK_OBJ));
			AllocaColoriSfondo(topLevelShellStaz,bkg_stazioni);
			}
		else
			leggi_file_bck(PadreStaz,PaginaStaz,"bkg",&(bkg_stazioni),dim);
		
		region_staz=NULL;
		/* setto il nome della pagina */
		set_something(topLevelShellStaz,XmNtitle,(void*) PaginaStaz);
		set_something(topLevelShellStaz,XmNiconName,(void*) PaginaStaz);
		set_something(topLevelShellStaz,XmNx,(void*) top_x);
		set_something(topLevelShellStaz,XmNy,(void*) top_y);
		set_something(topLevelShellStaz,XmNwidth,(void*) top_width);
		set_something(topLevelShellStaz,XmNheight,(void*) top_height);
		set_something(drawingAreaStaz,XmNwidth,(void*) drawing_width);
		set_something(drawingAreaStaz,XmNheight,(void*) drawing_height);
		if(drawing_pixmap)
			set_something(drawingAreaStaz,XmNbackgroundPixmap,(void*) drawing_pixmap);
		else
			set_something(drawingAreaStaz,XmNbackground,(void*) drawing_background);
#ifndef DESIGN_TIME
		LoadBitmap(scrolledWindowStaz,&pix,page_staz_icon_bits,page_staz_icon_width,page_staz_icon_height);
#endif
		set_something(rtrn,XmNiconPixmap,(void*) pix);
#ifndef DESIGN_TIME
		LoadFont(FONT_LABEL,&FontLabelStaz,XtDisplay(rtrn));
#endif
		set_something(menu1_p1_b1,XmNfontList,(void*) FontLabelStaz);
		set_something(menu1_p1_b3,XmNfontList,(void*) FontLabelStaz);
		set_something(menu1_p2_b1,XmNfontList,(void*) FontLabelStaz);
		set_something(menu1_p2_b2,XmNfontList,(void*) FontLabelStaz);
		
		
#ifndef DESIGN_TIME
		if(!CreaPagina(drawingAreaStaz,&lista_widStaz, &num_widStaz))
			return(NULL);
#endif
		/*
			inserisco la drawing area nell'elenco delle pagine attive
		*/
#ifndef DESIGN_TIME
		if((key_refresh_staz=InsElencoPagine(PaginaStaz,lista_widStaz,num_widStaz,time_ref_staz)) == -1)
			return(NULL);
#endif
		UxPopupInterface(rtrn, no_grab);
		/*
			creo il cursore di wait
		*/
		cursor_wait_staz = XlCreateWaitCursor(rtrn);
		SetCursorWaitStaz(drawingAreaStaz);
		wid_attesa_staz=NULL;
		attesa_staz = 0;
		timer_refresh_staz = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (topLevelShellStaz),
		            (unsigned long) (time_ref_staz*100) ,(XtTimerCallbackProc)refresh_page, UxContext);
		RaisePlotAing();
		/*
		Quando uso la close della MWM della decorazione attivo la finestra di close
		*/
		 WM_DELETE_WINDOW=XmInternAtom(XtDisplay(topLevelShellStaz),"WM_DELETE_WINDOW",False);
		XmAddWMProtocolCallback(topLevelShellStaz,WM_DELETE_WINDOW,activateCB_menu1_p1_b1,NULL);
		
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

