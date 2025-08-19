
/*******************************************************************************
	messageDialog.c
	(Generated from interface file messageDialog.i)
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

/*
   modulo messageDialog.i
   tipo 
   release 1.24
   data 8/29/95
   reserved @(#)messageDialog.i	1.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "questionMsgDb.h"

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
	Widget	UxmessageDialog;
	swidget	Uxwcaller;
	TIPO_OP	Uxmidop;
} _UxCmessageDialog;

#define messageDialog           UxMessageDialogContext->UxmessageDialog
#define wcaller                 UxMessageDialogContext->Uxwcaller
#define midop                   UxMessageDialogContext->Uxmidop

static _UxCmessageDialog	*UxMessageDialogContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_messageDialog();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* elimina_help_button
   
   elimina il bottone di help 
*/
int melimina_help_button()
{
   Widget hb;
  
   hb = XmMessageBoxGetChild(messageDialog,XmDIALOG_HELP_BUTTON);
   XtDestroyWidget(hb);
   return 0;
}

/* set_message 
 
 set del messaggio sulla message box
*/

int mset_message(char *mess)
{
   Arg args[1];
   Cardinal nargs;
   XmString mesg;

   mesg = XmStringCreateSimple(mess);
   nargs=0;
   XtSetArg(args[nargs],XmNmessageString,mesg);nargs++;
   XtSetValues(messageDialog,args,nargs);
   return 0;
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_messageDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmessageDialog       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMessageDialogContext;
	UxMessageDialogContext = UxContext =
			(_UxCmessageDialog *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxMessageDialogContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_messageDialog()
{
	Widget	messageDialog_shell;

	messageDialog_shell = XtVaCreatePopupShell( "messageDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 973,
			XmNy, 146,
			XmNwidth, 280,
			XmNheight, 140,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "messageDialog",
			NULL );

	messageDialog = XtVaCreateWidget( "messageDialog",
			xmMessageBoxWidgetClass, messageDialog_shell,
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			RES_CONVERT( XmNhelpLabelString, "Help" ),
			RES_CONVERT( XmNmessageString, " Message on operation" ),
			XmNheight, 140,
			XmNwidth, 280,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_MESSAGE,
			NULL );

	UxPutContext( messageDialog, (char *) UxMessageDialogContext );

	XtAddCallback( messageDialog, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxMessageDialogContext );

	XtAddCallback( messageDialog, XmNokCallback,
			okCallback_messageDialog,
			(XtPointer) UxMessageDialogContext );



	return ( messageDialog );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_messageDialog( _Uxwcaller, _Uxmidop )
	swidget	_Uxwcaller;
	TIPO_OP	_Uxmidop;
{
	Widget                  rtrn;
	_UxCmessageDialog       *UxContext;

	UxMessageDialogContext = UxContext =
		(_UxCmessageDialog *) XtMalloc( sizeof(_UxCmessageDialog) );

	wcaller = _Uxwcaller;
	midop = _Uxmidop;
	rtrn = _Uxbuild_messageDialog();

	melimina_help_button();
	
	switch( midop)
	{
	   case BYEBYE:
	   case CREASIM:
	   case OPENSIM:
	   case REMOVESIM:
	   case ADDTASK:
	     mset_message(message[midop]);
	   break;
	   default:
	     mset_message("Operazione non riconosciuta. Chiedere assistenza tecnica");
	   break;  
	}
	
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_messageDialog( _Uxwcaller, _Uxmidop )
	swidget	_Uxwcaller;
	TIPO_OP	_Uxmidop;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_messageDialog( _Uxwcaller, _Uxmidop );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

