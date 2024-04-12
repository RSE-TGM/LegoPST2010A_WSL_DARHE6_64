
/*******************************************************************************
	IconvertExitDialog.c
	(Generated from interface file IconvertExitDialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo IconvertExitDialog.i
   tipo 
   release 1.3
   data 3/30/95
   reserved @(#)IconvertExitDialog.i	1.3
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
	Widget	UxIconvertExitDialog;
} _UxCIconvertExitDialog;

#define IconvertExitDialog      UxIconvertExitDialogContext->UxIconvertExitDialog

static _UxCIconvertExitDialog	*UxIconvertExitDialogContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_IconvertExitDialog();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* elimina_button

   elimina i bottoni di help e cancel
*/
elimina_button()
{
   Widget hb;

   hb = XmMessageBoxGetChild(IconvertExitDialog,XmDIALOG_HELP_BUTTON);
   XtDestroyWidget(hb);
   hb = XmMessageBoxGetChild(IconvertExitDialog,XmDIALOG_CANCEL_BUTTON);
   XtDestroyWidget(hb);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_IconvertExitDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCIconvertExitDialog  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxIconvertExitDialogContext;
	UxIconvertExitDialogContext = UxContext =
			(_UxCIconvertExitDialog *) UxGetContext( UxWidget );
	{
	exit(0);
	}
	UxIconvertExitDialogContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_IconvertExitDialog()
{
	Widget	IconvertExitDialog_shell;

	IconvertExitDialog_shell = XtVaCreatePopupShell( "IconvertExitDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 480,
			XmNy, 470,
			XmNwidth, 430,
			XmNheight, 130,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "IconvertExitDialog",
			NULL );

	IconvertExitDialog = XtVaCreateWidget( "IconvertExitDialog",
			xmMessageBoxWidgetClass, IconvertExitDialog_shell,
			RES_CONVERT( XmNmessageString, "        Iconvert Run Successifully.\nYou can see results in 'default' diagram page\n           Topology Quit Now. " ),
			XmNheight, 130,
			XmNwidth, 430,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( IconvertExitDialog, (char *) UxIconvertExitDialogContext );

	XtAddCallback( IconvertExitDialog, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxIconvertExitDialogContext );

	XtAddCallback( IconvertExitDialog, XmNokCallback,
			okCallback_IconvertExitDialog,
			(XtPointer) UxIconvertExitDialogContext );



	return ( IconvertExitDialog );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_IconvertExitDialog()
{
	Widget                  rtrn;
	_UxCIconvertExitDialog  *UxContext;

	UxIconvertExitDialogContext = UxContext =
		(_UxCIconvertExitDialog *) XtMalloc( sizeof(_UxCIconvertExitDialog) );

	rtrn = _Uxbuild_IconvertExitDialog();

	elimina_button();
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_IconvertExitDialog()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_IconvertExitDialog();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

