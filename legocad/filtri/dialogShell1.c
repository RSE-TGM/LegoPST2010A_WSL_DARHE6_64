
/*******************************************************************************
	dialogShell1.c
	(Generated from interface file dialogShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo dialogShell1.i
   tipo 
   release 2.6
   data 3/20/95
   reserved @(#)dialogShell1.i	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/MwmUtil.h>

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
	Widget	UxmessageBox1;
} _UxCexitdialogShell1;

#define messageBox1             UxExitdialogShell1Context->UxmessageBox1

static _UxCexitdialogShell1	*UxExitdialogShell1Context;

Widget	exitdialogShell1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_exitdialogShell1();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_messageBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCexitdialogShell1    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxExitdialogShell1Context;
	UxExitdialogShell1Context = UxContext =
			(_UxCexitdialogShell1 *) UxGetContext( UxWidget );
	{
	   extern void exit();
	   extern FILE* fpedf;
	   int i=10;
	
	   printf("\nQuit\n");
	   
	   exit(0);
	}
	UxExitdialogShell1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_exitdialogShell1()
{

	exitdialogShell1 = XtVaCreatePopupShell( "exitdialogShell1",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNtitle, "Exit Application",
			XmNheight, 170,
			XmNwidth, 320,
			XmNy, 560,
			XmNx, 550,
			NULL );

	UxPutContext( exitdialogShell1, (char *) UxExitdialogShell1Context );

	messageBox1 = XtVaCreateWidget( "messageBox1",
			xmMessageBoxWidgetClass, exitdialogShell1,
			RES_CONVERT( XmNmessageString, "Exit from Filter Definition?" ),
			XmNdialogType, XmDIALOG_QUESTION,
			RES_CONVERT( XmNdialogTitle, "Filter " ),
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNheight, 130,
			XmNwidth, 290,
			XmNy, 560,
			XmNx, 550,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( messageBox1, (char *) UxExitdialogShell1Context );

	XtAddCallback( exitdialogShell1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxExitdialogShell1Context );

	XtVaSetValues(exitdialogShell1,
			XmNmwmInputMode, 0,
			XmNmwmFunctions, MWM_FUNC_MOVE | MWM_FUNC_CLOSE,
			XmNmwmDecorations, MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU,
			NULL );

	XtAddCallback( messageBox1, XmNokCallback,
			okCallback_messageBox1,
			(XtPointer) UxExitdialogShell1Context );



	return ( exitdialogShell1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_exitdialogShell1()
{
	Widget                  rtrn;
	_UxCexitdialogShell1    *UxContext;

	UxExitdialogShell1Context = UxContext =
		(_UxCexitdialogShell1 *) XtMalloc( sizeof(_UxCexitdialogShell1) );

	rtrn = _Uxbuild_exitdialogShell1();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_exitdialogShell1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_exitdialogShell1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

