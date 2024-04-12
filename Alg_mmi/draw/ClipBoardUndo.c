/**********************************************************************
*
*       C Source:               ClipBoardUndo.c
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Tue Dec  3 15:19:09 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ClipBoardUndo.c-2 %  (%full_filespec: ClipBoardUndo.c-2:csrc:1 %)";
#endif

/*******************************************************************************
	ClipBoardUndo.c
	(Not generated with AIC!!!! )
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/DrawingA.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include <Xm/Xm.h>
#include <Xd/Xd.h>


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
} _UxCClipBoardUndo;


static _UxCClipBoardUndo	*UxClipBoardUndoContext;

Widget	ClipBoardUndo;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_ClipBoardUndo();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ClipBoardUndo()
{
	Widget	ClipBoardUndo_shell;

	ClipBoardUndo_shell = XtVaCreatePopupShell( "ClipBoardUndo_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 400,
			XmNy, 220,
			XmNwidth, 570,
			XmNheight, 500,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "ClipBoardUndo",
			XmNiconName, "ClipBoardUndo",
			NULL );

	ClipBoardUndo = XtVaCreateManagedWidget( "ClipBoardUndo",
			xmDrawingAreaWidgetClass, ClipBoardUndo_shell,
			XmNmarginWidth, 0,
			XmNmarginHeight, 0,
			XmNheight, 500,
			XmNwidth, 570,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( ClipBoardUndo, (char *) UxClipBoardUndoContext );

	XtAddCallback( ClipBoardUndo, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxClipBoardUndoContext );



	return ( ClipBoardUndo );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_ClipBoardUndo()
{
	Widget                  rtrn;
	_UxCClipBoardUndo           *UxContext;

	UxClipBoardUndoContext = UxContext =
		(_UxCClipBoardUndo *) XtMalloc( sizeof(_UxCClipBoardUndo) );

	{
		/*CreaClipboardUndoList();   CAPPE */
		rtrn = _Uxbuild_ClipBoardUndo();

		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_ClipBoardUndo()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_ClipBoardUndo();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

