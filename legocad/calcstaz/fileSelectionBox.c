
/*******************************************************************************
	fileSelectionBox.c
	(Generated from interface file fileSelectionBox.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo fileSelectionBox.i
   tipo 
   release 1.7
   data 3/30/95
   reserved @(#)fileSelectionBox.i	1.7
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
extern Widget toplevel_widget;
Widget UxTopLevel;

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
	Widget	UxfileSelectionBox;
	int	*(*UxOkcb)();
	int	*(*UxCancelcb)();
	int	*(*UxFiltercb)();
	int	*(*UxHelpcb)();
} _UxCfileSelectionBox;

#define fileSelectionBox        UxFileSelectionBoxContext->UxfileSelectionBox
#define Okcb                    UxFileSelectionBoxContext->UxOkcb
#define Cancelcb                UxFileSelectionBoxContext->UxCancelcb
#define Filtercb                UxFileSelectionBoxContext->UxFiltercb
#define Helpcb                  UxFileSelectionBoxContext->UxHelpcb

static _UxCfileSelectionBox	*UxFileSelectionBoxContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_fileSelectionBox();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBoxContext;
	UxFileSelectionBoxContext = UxContext =
			(_UxCfileSelectionBox *) UxGetContext( UxWidget );
	{
	if( (Okcb) != NULL)
	   Okcb();
	}
	UxFileSelectionBoxContext = UxSaveCtx;
}

static void	helpCB_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBoxContext;
	UxFileSelectionBoxContext = UxContext =
			(_UxCfileSelectionBox *) UxGetContext( UxWidget );
	{
	if( (Helpcb) != NULL)
	   Helpcb();
	}
	UxFileSelectionBoxContext = UxSaveCtx;
}

static void	cancelCB_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBoxContext;
	UxFileSelectionBoxContext = UxContext =
			(_UxCfileSelectionBox *) UxGetContext( UxWidget );
	{
	if( (Cancelcb) != NULL)
	   Cancelcb(); 
	
	UxDestroyInterface(fileSelectionBox);
	}
	UxFileSelectionBoxContext = UxSaveCtx;
}

static void	applyCB_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBoxContext;
	UxFileSelectionBoxContext = UxContext =
			(_UxCfileSelectionBox *) UxGetContext( UxWidget );
	{
	if( (Filtercb) != NULL)
	   Filtercb();
	}
	UxFileSelectionBoxContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_fileSelectionBox()
{
	Widget	fileSelectionBox_shell;

	fileSelectionBox_shell = XtVaCreatePopupShell( "fileSelectionBox_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 240,
			XmNy, 168,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "fileSelectionBox",
			XmNiconName, "fileSelectionBox",
			NULL );

	fileSelectionBox = XtVaCreateManagedWidget( "fileSelectionBox",
			xmFileSelectionBoxWidgetClass, fileSelectionBox_shell,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( fileSelectionBox, (char *) UxFileSelectionBoxContext );

	XtAddCallback( fileSelectionBox, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxFileSelectionBoxContext );

	XtAddCallback( fileSelectionBox, XmNokCallback,
			okCallback_fileSelectionBox,
			(XtPointer) UxFileSelectionBoxContext );
	XtAddCallback( fileSelectionBox, XmNhelpCallback,
			helpCB_fileSelectionBox,
			(XtPointer) UxFileSelectionBoxContext );
	XtAddCallback( fileSelectionBox, XmNcancelCallback,
			cancelCB_fileSelectionBox,
			(XtPointer) UxFileSelectionBoxContext );
	XtAddCallback( fileSelectionBox, XmNapplyCallback,
			applyCB_fileSelectionBox,
			(XtPointer) UxFileSelectionBoxContext );



	return ( fileSelectionBox );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_fileSelectionBox( _UxOkcb, _UxCancelcb, _UxFiltercb, _UxHelpcb )
	int	*(*_UxOkcb)();
	int	*(*_UxCancelcb)();
	int	*(*_UxFiltercb)();
	int	*(*_UxHelpcb)();
{
	Widget                  rtrn;
	_UxCfileSelectionBox    *UxContext;

	UxFileSelectionBoxContext = UxContext =
		(_UxCfileSelectionBox *) XtMalloc( sizeof(_UxCfileSelectionBox) );

	Okcb = _UxOkcb;
	Cancelcb = _UxCancelcb;
	Filtercb = _UxFiltercb;
	Helpcb = _UxHelpcb;
	{
		UxTopLevel = toplevel_widget;
		rtrn = _Uxbuild_fileSelectionBox();

		UxPopupInterface(rtrn,no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_fileSelectionBox( _UxOkcb, _UxCancelcb, _UxFiltercb, _UxHelpcb )
	int	*(*_UxOkcb)();
	int	*(*_UxCancelcb)();
	int	*(*_UxFiltercb)();
	int	*(*_UxHelpcb)();
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_fileSelectionBox( _UxOkcb, _UxCancelcb, _UxFiltercb, _UxHelpcb );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

