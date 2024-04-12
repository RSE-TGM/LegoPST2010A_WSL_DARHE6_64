
/*******************************************************************************
	promptDialog1.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

extern swidget topLevelShell1;

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
} _UxCpromptDialog1;


static _UxCpromptDialog1	*UxPromptDialog1Context;

Widget	promptDialog1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_promptDialog1();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_promptDialog1()
{
	Widget	promptDialog1_shell;

	promptDialog1_shell = XtVaCreatePopupShell( "promptDialog1_shell",
			xmDialogShellWidgetClass, topLevelShell1,
			XmNx, 690,
			XmNy, 40,
			XmNwidth, 435,
			XmNheight, 225,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "promptDialog1",
			NULL );

	promptDialog1 = XtVaCreateWidget( "promptDialog1",
			xmSelectionBoxWidgetClass, promptDialog1_shell,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNheight, 225,
			XmNwidth, 435,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_PROMPT,
			NULL );

	UxPutContext( promptDialog1, (char *) UxPromptDialog1Context );

	XtAddCallback( promptDialog1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxPromptDialog1Context );



	return ( promptDialog1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_promptDialog1()
{
	Widget                  rtrn;
	_UxCpromptDialog1       *UxContext;

	UxPromptDialog1Context = UxContext =
		(_UxCpromptDialog1 *) XtMalloc( sizeof(_UxCpromptDialog1) );

	rtrn = _Uxbuild_promptDialog1();

	UxPopupInterface(rtrn);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_promptDialog1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_promptDialog1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

