
/*******************************************************************************
	errorDialog1.c
	(Generated from interface file errorDialog1.i)
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
   modulo errorDialog1.i
   tipo 
   release 1.10
   data 3/31/95
   reserved @(#)errorDialog1.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

void lcDestroySwidget(Widget);

#ifndef DESIGN_TIME
#define CH_SET                   XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR(string,CH_SET))
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
	Widget	UxerrorDialog1;
	unsigned char	*Uxmessaggio;
} _UxCerrorDialog1;

#define errorDialog1            UxErrorDialog1Context->UxerrorDialog1
#define messaggio               UxErrorDialog1Context->Uxmessaggio

static _UxCerrorDialog1	*UxErrorDialog1Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	crea_errorDialog();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_errorDialog1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCerrorDialog1        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxErrorDialog1Context;
	UxErrorDialog1Context = UxContext =
			(_UxCerrorDialog1 *) UxGetContext( UxWidget );
	{
	UxDestroySwidget(errorDialog1);
	}
	UxErrorDialog1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_errorDialog1()
{
	Widget	errorDialog1_shell;

	errorDialog1_shell = XtVaCreatePopupShell( "errorDialog1_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 110,
			XmNy, 630,
			XmNwidth, 450,
			XmNheight, 250,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "errorDialog1",
			NULL );

	errorDialog1 = XtVaCreateWidget( "errorDialog1",
			xmMessageBoxWidgetClass, errorDialog1_shell,
			RES_CONVERT( XmNdialogTitle, "Error!" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNnoResize, TRUE,
			XmNresizePolicy, XmRESIZE_ANY,
			XmNbuttonFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			XmNtextFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNhelpLabelString, "" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNcancelLabelString, "" ),
			XmNheight, 250,
			XmNwidth, 450,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_ERROR,
			NULL );

	UxPutContext( errorDialog1, (char *) UxErrorDialog1Context );

	XtAddCallback( errorDialog1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxErrorDialog1Context );

	XtAddCallback( errorDialog1, XmNokCallback,
			okCallback_errorDialog1,
			(XtPointer) UxErrorDialog1Context );



	return ( errorDialog1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_crea_errorDialog( _Uxmessaggio )
	unsigned char	*_Uxmessaggio;
{
	Widget                  rtrn;
	_UxCerrorDialog1        *UxContext;

	UxErrorDialog1Context = UxContext =
		(_UxCerrorDialog1 *) XtMalloc( sizeof(_UxCerrorDialog1) );

	messaggio = _Uxmessaggio;
	{
		XmString cstring;
		rtrn = _Uxbuild_errorDialog1();

		XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(errorDialog1), XmDIALOG_CANCEL_BUTTON));
		XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(errorDialog1), XmDIALOG_HELP_BUTTON));
		
		cstring = CREATE_CSTRING(messaggio);
		XtVaSetValues(UxGetWidget(errorDialog1), XmNmessageString, cstring, NULL);
		XmStringFree(cstring);
		
		UxPopupInterface(rtrn, no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	crea_errorDialog( _Uxmessaggio )
	unsigned char	*_Uxmessaggio;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_crea_errorDialog( _Uxmessaggio );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

