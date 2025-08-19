
/*******************************************************************************
	IconvertDialog.c
	(Generated from interface file IconvertDialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>
#include <stdlib.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo IconvertDialog.i
   tipo 
   release 1.3
   data 3/30/95
   reserved @(#)IconvertDialog.i	1.3
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif


/*******************************************************************************
	The definition of the context structure:
	If you create multiple instances of your interface, the context
	structure ensures that your callbacks use the variables for the
	correct instance.

	For each swidget in the interface, each argument to the Interface
	function, and each variable in the Instance Specific section of the
	Declarations Editor, there is an entry in the context structure.
	and a #define.  The #define makes the variable name refer to the
	corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxIconvertDialog;
} _UxCIconvertDialog;

#define IconvertDialog          UxIconvertDialogContext->UxIconvertDialog

static _UxCIconvertDialog	*UxIconvertDialogContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_IconvertDialog();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

int quitting()
{
    exit(0);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_IconvertDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCIconvertDialog      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxIconvertDialogContext;
	UxIconvertDialogContext = UxContext =
			(_UxCIconvertDialog *) UxGetContext( UxWidget );
	{
	/* faccio girare iconvert */
	extern swidget create_IconvertExitDialog();
	system("iconvert");
	UxPopupInterface(create_IconvertExitDialog(),no_grab);
	}
	UxIconvertDialogContext = UxSaveCtx;
}

static void	cancelCB_IconvertDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCIconvertDialog      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxIconvertDialogContext;
	UxIconvertDialogContext = UxContext =
			(_UxCIconvertDialog *) UxGetContext( UxWidget );
	{
	/* quit del programma topologia */
	exit(0);
	}
	UxIconvertDialogContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_IconvertDialog()
{
	Widget	IconvertDialog_shell;

	IconvertDialog_shell = XtVaCreatePopupShell( "IconvertDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 390,
			XmNy, 400,
			XmNwidth, 420,
			XmNheight, 160,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "IconvertDialog",
			NULL );

	IconvertDialog = XtVaCreateWidget( "IconvertDialog",
			xmMessageBoxWidgetClass, IconvertDialog_shell,
			RES_CONVERT( XmNcancelLabelString, "No" ),
			RES_CONVERT( XmNokLabelString, "Yes" ),
			RES_CONVERT( XmNmessageString, "Differnces between icon and list\nDo you want RUN ICONVERT?" ),
			XmNheight, 160,
			XmNwidth, 420,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( IconvertDialog, (char *) UxIconvertDialogContext );

	XtAddCallback( IconvertDialog, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxIconvertDialogContext );

	XtAddCallback( IconvertDialog, XmNokCallback,
			okCallback_IconvertDialog,
			(XtPointer) UxIconvertDialogContext );
	XtAddCallback( IconvertDialog, XmNcancelCallback,
			cancelCB_IconvertDialog,
			(XtPointer) UxIconvertDialogContext );



	return ( IconvertDialog );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_IconvertDialog()
{
	Widget                  rtrn;
	_UxCIconvertDialog      *UxContext;

	UxIconvertDialogContext = UxContext =
		(_UxCIconvertDialog *) XtMalloc( sizeof(_UxCIconvertDialog) );

	rtrn = _Uxbuild_IconvertDialog();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_IconvertDialog()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_IconvertDialog();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

