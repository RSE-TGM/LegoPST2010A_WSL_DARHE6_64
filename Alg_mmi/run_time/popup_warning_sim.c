
/*******************************************************************************
       popup_warning_sim.c
       (Generated from interface file popup_warning_sim.i)
       Associated Resource file: popup_warning_sim.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include <string.h>
#include <stdlib.h>

#include <sys/param.h>

#ifdef SCO_UNIX
#include <Xm/MwmUtil.h>
#else
#include <Xm/MwmUtil.h>
#endif

#include <Xm/List.h>
#include <time.h> 
#ifndef DESIGN_TIME
#include <Xl/Xl.h>
#endif


#include <Xl/XlUtilBkg.h>
#include <Ol/OlDatabasePunti.h>

#ifndef DESIGN_TIME
#include <Ol/OlPertP.h>
#else
#include <Ol/OlPert.h>
#endif
#include <Xm/Protocols.h>
#include "other.h"
#include "pagresdef.h"
#include "legommi_icon.bmp"



extern OlDatabasePuntiObject database_simulatore;
extern Boolean topologia_on;
extern char path_sim_correct[FILENAME_MAX];
extern int shr_usr_key;
//extern CursorErrFree(Widget ,Cursor );
//extern int creaOlDbPunti(char *,Widget);


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
	Widget	Uxpopup_warning_sim;
	Widget	UxtopLevel_warning;
	XmFontList	UxFontLabelWarning;
	Cursor	Uxcursor_warning;
	Widget	UxGenitore;
	unsigned char	*UxWarningString;
	swidget	UxUxParent;
} _UxCpopup_warning_sim;

static _UxCpopup_warning_sim   *UxPopup_warning_simContext;
#define popup_warning_sim       UxPopup_warning_simContext->Uxpopup_warning_sim
#define topLevel_warning        UxPopup_warning_simContext->UxtopLevel_warning
#define FontLabelWarning        UxPopup_warning_simContext->UxFontLabelWarning
#define cursor_warning          UxPopup_warning_simContext->Uxcursor_warning
#define Genitore                UxPopup_warning_simContext->UxGenitore
#define WarningString           UxPopup_warning_simContext->UxWarningString
#define UxParent                UxPopup_warning_simContext->UxUxParent



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_popup_warning_sim();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
Widget popup_Warning_sim(char *Warning_, Widget TopWarning_)
{
return(create_popup_warning_sim(Warning_,TopWarning_));
}
#endif

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_popup_warning_sim( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpopup_warning_sim   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPopup_warning_simContext;
	UxPopup_warning_simContext = UxContext =
			(_UxCpopup_warning_sim *) UxGetContext( UxWidget );
	{
	int database_type;
	
	CursorErrFree(popup_warning_sim,cursor_warning);
	PutPagBackground();
	creaOlDbPunti(path_sim_correct,Genitore);
	if(database_simulatore==NULL )
	   {
	    popup_errorDialog("ERROR: Connection with simulator failed",Genitore);
	    }
	}
	UxPopup_warning_simContext = UxSaveCtx;
}

static	void	helpCB_popup_warning_sim( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpopup_warning_sim   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPopup_warning_simContext;
	UxPopup_warning_simContext = UxContext =
			(_UxCpopup_warning_sim *) UxGetContext( UxWidget );
	{
	
	PutPagBackground();
	}
	UxPopup_warning_simContext = UxSaveCtx;
}

static	void	cancelCB_popup_warning_sim( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpopup_warning_sim   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPopup_warning_simContext;
	UxPopup_warning_simContext = UxContext =
			(_UxCpopup_warning_sim *) UxGetContext( UxWidget );
	{
	CursorErrFree(popup_warning_sim,cursor_warning);
	PutPagBackground();
	}
	UxPopup_warning_simContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_popup_warning_sim()
{
	Widget		_UxParent;


	/* Creation of popup_warning_sim */
	_UxParent = UxParent;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "popup_warning_sim_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "popup_warning_sim",
			NULL );

	popup_warning_sim = XtVaCreateWidget( "popup_warning_sim",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_WARNING,
			XmNunitType, XmPIXELS,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNokLabelString, "Retry" ),
			RES_CONVERT( XmNdialogTitle, "WARNING DbPunti" ),
			NULL );
	XtAddCallback( popup_warning_sim, XmNokCallback,
		(XtCallbackProc) okCallback_popup_warning_sim,
		(XtPointer) UxPopup_warning_simContext );
	XtAddCallback( popup_warning_sim, XmNhelpCallback,
		(XtCallbackProc) helpCB_popup_warning_sim,
		(XtPointer) UxPopup_warning_simContext );
	XtAddCallback( popup_warning_sim, XmNcancelCallback,
		(XtCallbackProc) cancelCB_popup_warning_sim,
		(XtPointer) UxPopup_warning_simContext );

	UxPutContext( popup_warning_sim, (char *) UxPopup_warning_simContext );


	XtAddCallback( popup_warning_sim, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxPopup_warning_simContext);


	return ( popup_warning_sim );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_popup_warning_sim( _UxWarningString, _UxUxParent )
	unsigned char	*_UxWarningString;
	swidget	_UxUxParent;
{
	Widget                  rtrn;
	_UxCpopup_warning_sim   *UxContext;
	static int		_Uxinit = 0;

	UxPopup_warning_simContext = UxContext =
		(_UxCpopup_warning_sim *) UxNewContext( sizeof(_UxCpopup_warning_sim), False );

	WarningString = _UxWarningString;
	UxParent = _UxUxParent;

	if ( ! _Uxinit )
	{
		UxLoadResources( "popup_warning_sim.rf" );
		_Uxinit = 1;
	}

	{
		Genitore=UxParent;
		rtrn = _Uxbuild_popup_warning_sim();

		UxPopupInterface(rtrn, no_grab);
		cursor_warning=XlCreateErrCursor(popup_warning_sim);
		XlSetCursor(popup_warning_sim,cursor_warning);
		set_something(popup_warning_sim,XmNmessageString,
				(void*) XmStringCreateLtoR(WarningString, XmSTRING_DEFAULT_CHARSET));
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

