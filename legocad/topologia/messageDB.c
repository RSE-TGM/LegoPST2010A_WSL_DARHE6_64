
/*******************************************************************************
	messageDB.c
	(Generated from interface file messageDB.i)
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
   modulo messageDB.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)messageDB.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

#include "message_type.h"

MESSAGE message;

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
	int	mumble;
} _UxCmessageDB;


static _UxCmessageDB	*UxMessageDBContext;

Widget	messageDB;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_messageDB();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

messageDB_activate ( message )
char *message;
{

   extern swidget messageDB;
   extern swidget lg1MainWindow;


   UxPutMessageString(messageDB,message);
   UxPopupInterface(messageDB,no_grab);
/*   set_win_cursors( "busy" );
*/
}



show_error( mess )
char *mess;
{
   extern MESSAGE message;

   message = MSG_ERROR;

   messageDB_activate( mess );
}

fatal_err( mess )
char *mess;
{
   extern MESSAGE message;

   message = MSG_FATAL_ERROR;

   messageDB_activate( mess );
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_messageDB( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmessageDB           *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMessageDBContext;
	UxMessageDBContext = UxContext =
			(_UxCmessageDB *) UxGetContext( UxWidget );
	{
	
	/***
	reset_win_cursors();
	***/
	
	switch ( message ) {
	
	   case MSG_ERROR:
	   case MSG_MADE_CONN: 
	   case MSG_WARNING_CONN: 
	                    break;
	   case MSG_FATAL_ERROR:
	      exit(0);
	    break;
	}
	
	}
	UxMessageDBContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_messageDB()
{
	Widget	messageDB_shell;

	messageDB_shell = XtVaCreatePopupShell( "messageDB_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 825,
			XmNy, 120,
			XmNwidth, 380,
			XmNheight, 260,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "messageDB",
			NULL );

	messageDB = XtVaCreateWidget( "messageDB",
			xmMessageBoxWidgetClass, messageDB_shell,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNheight, 260,
			XmNwidth, 380,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_ERROR,
			NULL );

	UxPutContext( messageDB, (char *) UxMessageDBContext );

	XtAddCallback( messageDB, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxMessageDBContext );

	XtAddCallback( messageDB, XmNokCallback,
			okCallback_messageDB,
			(XtPointer) UxMessageDBContext );



	return ( messageDB );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_messageDB()
{
	Widget                  rtrn;
	_UxCmessageDB           *UxContext;

	UxMessageDBContext = UxContext =
		(_UxCmessageDB *) XtMalloc( sizeof(_UxCmessageDB) );

	{
		Widget wid;
		rtrn = _Uxbuild_messageDB();

		wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );
		XtUnmanageChild( wid );
		
		wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_CANCEL_BUTTON );
		XtUnmanageChild( wid );
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_messageDB()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_messageDB();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

