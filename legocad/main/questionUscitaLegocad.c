
/*******************************************************************************
	questionUscitaLegocad.c
	(Generated from interface file questionUscitaLegocad.i)
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
   modulo questionUscitaLegocad.i
   tipo 
   release 2.25
   data 5/12/95
   reserved @(#)questionUscitaLegocad.i	2.25
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#ifdef HYPERHELP_USED
#include "winhelp.h"
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
	Widget	UxquestionUscitaLegocad;
	unsigned char	*Uxmess;
} _UxCquestionUscitaLegocad;

#define questionUscitaLegocad   UxQuestionUscitaLegocadContext->UxquestionUscitaLegocad
#define mess                    UxQuestionUscitaLegocadContext->Uxmess

static _UxCquestionUscitaLegocad	*UxQuestionUscitaLegocadContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_questionUscitaLegocad();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_questionUscitaLegocad( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionUscitaLegocad *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionUscitaLegocadContext;
	UxQuestionUscitaLegocadContext = UxContext =
			(_UxCquestionUscitaLegocad *) UxGetContext( UxWidget );
	{
	/* uccide eventuali processi ancora attivi */
	kill_proc_legocad();
	UxDestroyInterface(questionUscitaLegocad);
#ifdef HYPERHELP_USED
	WinHelp(UxDisplay,"",HELP_QUIT,0);
#endif
	exit(0);
	}
	UxQuestionUscitaLegocadContext = UxSaveCtx;
}

static void	cancelCB_questionUscitaLegocad( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionUscitaLegocad *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionUscitaLegocadContext;
	UxQuestionUscitaLegocadContext = UxContext =
			(_UxCquestionUscitaLegocad *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(questionUscitaLegocad);
	}
	UxQuestionUscitaLegocadContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_questionUscitaLegocad()
{
	Widget	questionUscitaLegocad_shell;

	questionUscitaLegocad_shell = XtVaCreatePopupShell( "questionUscitaLegocad_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 575,
			XmNy, 70,
			XmNwidth, 305,
			XmNheight, 150,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "questionUscitaLegocad",
			NULL );

	questionUscitaLegocad = XtVaCreateWidget( "questionUscitaLegocad",
			xmMessageBoxWidgetClass, questionUscitaLegocad_shell,
			RES_CONVERT( XmNdialogTitle, "EXIT LEGOCAD" ),
			RES_CONVERT( XmNmessageString, mess ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNdefaultButtonType, XmDIALOG_CANCEL_BUTTON,
			XmNheight, 150,
			XmNwidth, 305,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( questionUscitaLegocad, (char *) UxQuestionUscitaLegocadContext );

	XtAddCallback( questionUscitaLegocad, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxQuestionUscitaLegocadContext );

	XtAddCallback( questionUscitaLegocad, XmNokCallback,
			okCallback_questionUscitaLegocad,
			(XtPointer) UxQuestionUscitaLegocadContext );
	XtAddCallback( questionUscitaLegocad, XmNcancelCallback,
			cancelCB_questionUscitaLegocad,
			(XtPointer) UxQuestionUscitaLegocadContext );



	return ( questionUscitaLegocad );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_questionUscitaLegocad( _Uxmess )
	unsigned char	*_Uxmess;
{
	Widget                  rtrn;
	_UxCquestionUscitaLegocad *UxContext;

	UxQuestionUscitaLegocadContext = UxContext =
		(_UxCquestionUscitaLegocad *) XtMalloc( sizeof(_UxCquestionUscitaLegocad) );

	mess = _Uxmess;
	rtrn = _Uxbuild_questionUscitaLegocad();

	XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_questionUscitaLegocad( _Uxmess )
	unsigned char	*_Uxmess;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_questionUscitaLegocad( _Uxmess );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

