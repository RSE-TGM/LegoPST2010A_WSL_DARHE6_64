
/*******************************************************************************
       errorDialog.c
       (Generated from interface file errorDialog.i)
       Associated Resource file: errorDialog.rf
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
   release 5.1
   data 11/13/95
   reserved @(#)errorDialog.i	5.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "config.h"


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
	int	mumble;
} _UxCerrorDialog;

static _UxCerrorDialog         *UxErrorDialogContext;


Widget	errorDialog;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_errorDialog();

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
	
	if(error_level == SEVERE)
	   exit(1);
	
	
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
	_UxParent = XtVaCreatePopupShell( "errorDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 500,
			XmNy, 400,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "errorDialog",
			NULL );

	errorDialog = XtVaCreateWidget( "errorDialog",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_ERROR,
			XmNunitType, XmPIXELS,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNallowOverlap, TRUE,
			NULL );
	XtAddCallback( errorDialog, XmNokCallback,
		(XtCallbackProc) okCallback_errorDialog,
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

Widget	create_errorDialog()
{
	Widget                  rtrn;
	_UxCerrorDialog         *UxContext;
	static int		_Uxinit = 0;

	UxErrorDialogContext = UxContext =
		(_UxCerrorDialog *) UxNewContext( sizeof(_UxCerrorDialog), False );


	if ( ! _Uxinit )
	{
		UxLoadResources( "errorDialog.rf" );
		_Uxinit = 1;
	}

	rtrn = _Uxbuild_errorDialog();

	XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON));
	XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON));
	return(rtrn);
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

