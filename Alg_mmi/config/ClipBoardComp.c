
/*******************************************************************************
       ClipBoard.c
       (Generated from interface file ClipBoard.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/DrawingA.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo ClipBoard.i
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)ClipBoard.i	5.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/Xm.h>
#include <Xd/Xd.h>

extern  void *		UxNewContext();

/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	int	mumble;
} _UxCClipBoard;

static _UxCClipBoard           *UxClipBoardContext;


Widget	ClipBoard;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_ClipBoardComp();

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

static Widget	_Uxbuild_ClipBoard()
{
	Widget		_UxParent;


	/* Creation of ClipBoard */
	_UxParent = XtVaCreatePopupShell( "ClipBoard_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 400,
			XmNy, 220,
			XmNwidth, 570,
			XmNheight, 500,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "ClipBoard",
			XmNiconName, "ClipBoard",
			NULL );

	ClipBoard = XtVaCreateManagedWidget( "ClipBoard",
			xmDrawingAreaWidgetClass,
			_UxParent,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNwidth, 570,
			XmNheight, 500,
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			NULL );
	UxPutContext( ClipBoard, (char *) UxClipBoardContext );


	XtAddCallback( ClipBoard, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxClipBoardContext);


	return ( ClipBoard );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_ClipBoardComp()
{
	Widget                  rtrn;
	_UxCClipBoard           *UxContext;

	UxClipBoardContext = UxContext =
		(_UxCClipBoard *) UxNewContext( sizeof(_UxCClipBoard), False );


	{
/*
		CreaClipboardList();
*/
		rtrn = _Uxbuild_ClipBoard();

		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

