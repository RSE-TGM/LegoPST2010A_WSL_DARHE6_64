
/*******************************************************************************
	messageBoxDialog1.c
	(Generated from interface file messageBoxDialog1.i)
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
   modulo messageBoxDialog1.i
   tipo 
   release 2.15
   data 4/26/95
   reserved @(#)messageBoxDialog1.i	2.15
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
	Widget	UxmessageBoxDialog1;
	unsigned char	*UxMyMessage;
} _UxCmessageBoxDialog1;

#define messageBoxDialog1       UxMessageBoxDialog1Context->UxmessageBoxDialog1
#define MyMessage               UxMessageBoxDialog1Context->UxMyMessage

static _UxCmessageBoxDialog1	*UxMessageBoxDialog1Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_vis_msg();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_messageBoxDialog1()
{
	Widget	messageBoxDialog1_shell;

	messageBoxDialog1_shell = XtVaCreatePopupShell( "messageBoxDialog1_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 250,
			XmNy, 250,
			XmNwidth, 270,
			XmNheight, 110,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "messageBoxDialog1",
			NULL );

	messageBoxDialog1 = XtVaCreateWidget( "messageBoxDialog1",
			xmMessageBoxWidgetClass, messageBoxDialog1_shell,
			RES_CONVERT( XmNmessageString, "" ),
			XmNheight, 110,
			XmNwidth, 270,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( messageBoxDialog1, (char *) UxMessageBoxDialog1Context );

	XtAddCallback( messageBoxDialog1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxMessageBoxDialog1Context );



	return ( messageBoxDialog1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_vis_msg( _UxMyMessage )
	unsigned char	*_UxMyMessage;
{
	Widget                  rtrn;
	_UxCmessageBoxDialog1   *UxContext;

	UxMessageBoxDialog1Context = UxContext =
		(_UxCmessageBoxDialog1 *) XtMalloc( sizeof(_UxCmessageBoxDialog1) );

	MyMessage = _UxMyMessage;
	rtrn = _Uxbuild_messageBoxDialog1();

	UxPutMessageString(rtrn,MyMessage);
	UxPopupInterface(rtrn,no_grab);
	
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_vis_msg( _UxMyMessage )
	unsigned char	*_UxMyMessage;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_vis_msg( _UxMyMessage );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

