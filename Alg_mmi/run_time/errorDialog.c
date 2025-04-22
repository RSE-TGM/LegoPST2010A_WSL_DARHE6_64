
/*******************************************************************************
       errorDialog.c
       (Generated from interface file errorDialog.i)
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

/*
        Inizio sezione per SCCS
*/
/*
   modulo errorDialog.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)errorDialog.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "other.h"


Widget PadreError;


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
	Widget	UxerrorDialog;
	Widget	UxtopLevel_error;
	XmFontList	UxFontLabelError;
	Cursor	Uxcursor_errore;
	unsigned char	*UxErrore;
	Widget	UxTopError;
} _UxCerrorDialog;

static _UxCerrorDialog         *UxErrorDialogContext;
#define errorDialog             UxErrorDialogContext->UxerrorDialog
#define topLevel_error          UxErrorDialogContext->UxtopLevel_error
#define FontLabelError          UxErrorDialogContext->UxFontLabelError
#define cursor_errore           UxErrorDialogContext->Uxcursor_errore
#define Errore                  UxErrorDialogContext->UxErrore
#define TopError                UxErrorDialogContext->UxTopError



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_errorDialog();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

CursorErrFree(Widget wid,Cursor cur)
{
XlUnsetCursor(wid);
XlFreeCursor(wid,cur);
}

#ifndef DESIGN_TIME
Widget popup_errorDialog(char *Errore_, Widget TopError_)
{
return(create_errorDialog(Errore_,TopError_));
}
#endif

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_errorDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCerrorDialog         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxErrorDialogContext;
	UxErrorDialogContext = UxContext =
			(_UxCerrorDialog *) UxGetContext( UxWidget );
	{
	CursorErrFree(errorDialog,cursor_errore);
	PutPagBackground();
	}
	UxErrorDialogContext = UxSaveCtx;
}

static	void	cancelCB_errorDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCerrorDialog         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxErrorDialogContext;
	UxErrorDialogContext = UxContext =
			(_UxCerrorDialog *) UxGetContext( UxWidget );
	{
	CursorErrFree(errorDialog,cursor_errore);
	PutPagBackground();
	}
	UxErrorDialogContext = UxSaveCtx;
}

static	void	helpCB_errorDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCerrorDialog         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxErrorDialogContext;
	UxErrorDialogContext = UxContext =
			(_UxCerrorDialog *) UxGetContext( UxWidget );
	{
	
	PutPagBackground();
	}
	UxErrorDialogContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_errorDialog()
{
	Widget		_UxParent;


	/* Creation of errorDialog */
	_UxParent = PadreError;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "errorDialog_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 220,
			XmNy, 600,
			XmNwidth, 450,
			XmNheight, 300,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "errorDialog",
			NULL );

	errorDialog = XtVaCreateWidget( "errorDialog",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_ERROR,
			XmNunitType, XmPIXELS,
			XmNwidth, 450,
			XmNheight, 300,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNdialogTitle, "Error" ),
			RES_CONVERT( XmNmessageString, "Error !!!" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			NULL );
	XtAddCallback( errorDialog, XmNokCallback,
		(XtCallbackProc) okCallback_errorDialog,
		(XtPointer) UxErrorDialogContext );
	XtAddCallback( errorDialog, XmNcancelCallback,
		(XtCallbackProc) cancelCB_errorDialog,
		(XtPointer) UxErrorDialogContext );
	XtAddCallback( errorDialog, XmNhelpCallback,
		(XtCallbackProc) helpCB_errorDialog,
		(XtPointer) UxErrorDialogContext );

	UxPutContext( errorDialog, (char *) UxErrorDialogContext );


	XtAddCallback( errorDialog, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxErrorDialogContext);


	return ( errorDialog );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_errorDialog( _UxErrore, _UxTopError )
	unsigned char	*_UxErrore;
	Widget	_UxTopError;
{
	Widget                  rtrn;
	_UxCerrorDialog         *UxContext;

	UxErrorDialogContext = UxContext =
		(_UxCerrorDialog *) UxNewContext( sizeof(_UxCerrorDialog), False );

	Errore = _UxErrore;
	TopError = _UxTopError;

	{
		char message[200];
		
		PadreError=TopError;
		topLevel_error=TopError;
		
		/*
			risalgo alla topLevel
		*/
		PadreError=ToTopLevel(PadreError);
		
		printf("ERRORE - %s\n",Errore);
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabelError,XtDisplay(topLevel_error)))
			exit(0);
#endif
		rtrn = _Uxbuild_errorDialog();

		UxPopupInterface(rtrn, no_grab);
		cursor_errore=XlCreateErrCursor(errorDialog);
		XlSetCursor(errorDialog,cursor_errore);
		set_something(errorDialog,XmNmessageString,
				(void*) XmStringCreateLtoR(Errore, XmSTRING_DEFAULT_CHARSET));
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),(void*) XmNfontList,FontLabelError);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),(void*) XmNfontList,FontLabelError);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),(void*) XmNfontList,FontLabelError);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),(void*) XmNfontList,FontLabelError);
		sprintf(message,"%s\n",Errore);
		show_warning(message);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

