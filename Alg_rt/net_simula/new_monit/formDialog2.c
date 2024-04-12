
/*******************************************************************************
	formDialog2.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Form.h>


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
	Widget	UxformDialog2;
} _UxCformDialog2;

#define formDialog2             UxFormDialog2Context->UxformDialog2

static _UxCformDialog2	*UxFormDialog2Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_formDialog2();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_formDialog2()
{
	Widget	formDialog2_shell;

	formDialog2_shell = XtVaCreatePopupShell( "formDialog2_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 460,
			XmNy, 610,
			XmNwidth, 420,
			XmNheight, 380,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "formDialog2",
			NULL );

	formDialog2 = XtVaCreateWidget( "formDialog2",
			xmFormWidgetClass, formDialog2_shell,
			XmNheight, 380,
			XmNwidth, 420,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( formDialog2, (char *) UxFormDialog2Context );

	XtAddCallback( formDialog2, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxFormDialog2Context );



	return ( formDialog2 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_formDialog2()
{
	Widget                  rtrn;
	_UxCformDialog2         *UxContext;

	UxFormDialog2Context = UxContext =
		(_UxCformDialog2 *) XtMalloc( sizeof(_UxCformDialog2) );

	rtrn = _Uxbuild_formDialog2();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_formDialog2()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_formDialog2();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

