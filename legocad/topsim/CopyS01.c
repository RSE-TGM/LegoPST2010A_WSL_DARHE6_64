
/*******************************************************************************
	CopyS01.c
	(Generated from interface file CopyS01.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo CopyS01.i
   tipo 
   release 1.1
   data 11/23/95
   reserved @(#)CopyS01.i	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "topsim.h"
#include "lg1_topsim.h"

extern SIMULATORE *simulatore;

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
	Widget	UxCopyS01;
} _UxCCopyS01;

#define CopyS01                 UxCopyS01Context->UxCopyS01

static _UxCCopyS01	*UxCopyS01Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_CopyS01();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

copy_from(char *from)
{
    extern int set_wait_cursior(),set_normal_cursor();
    char comando[512];

    set_wait_cursor();

    sprintf(comando,"cp %s %s",from,simulatore->path);
    system(comando);

    printf("copy S01 from %s to %s\n",from,simulatore->path);
    set_normal_cursor();
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_CopyS01( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyS01             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyS01Context;
	UxCopyS01Context = UxContext =
			(_UxCCopyS01 *) UxGetContext( UxWidget );
	{
	char selec[STRLONG];
	
	strcpy(selec,UxGetTextString(CopyS01));
	copy_from(selec);
	UxDestroyInterface(UxWidget);
	}
	UxCopyS01Context = UxSaveCtx;
}

static void	cancelCB_CopyS01( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyS01             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyS01Context;
	UxCopyS01Context = UxContext =
			(_UxCCopyS01 *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxCopyS01Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_CopyS01()
{
	Widget	CopyS01_shell;

	CopyS01_shell = XtVaCreatePopupShell( "CopyS01_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 433,
			XmNy, 388,
			XmNwidth, 421,
			XmNheight, 415,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "CopyS01",
			XmNiconName, "CopyS01",
			NULL );

	CopyS01 = XtVaCreateManagedWidget( "CopyS01",
			xmFileSelectionBoxWidgetClass, CopyS01_shell,
			RES_CONVERT( XmNdirMask, "./S01*" ),
			RES_CONVERT( XmNselectionLabelString, "Copy S01 from" ),
			XmNheight, 415,
			XmNwidth, 421,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( CopyS01, (char *) UxCopyS01Context );

	XtAddCallback( CopyS01, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxCopyS01Context );

	XtAddCallback( CopyS01, XmNokCallback,
			okCallback_CopyS01,
			(XtPointer) UxCopyS01Context );
	XtAddCallback( CopyS01, XmNcancelCallback,
			cancelCB_CopyS01,
			(XtPointer) UxCopyS01Context );



	return ( CopyS01 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_CopyS01()
{
	Widget                  rtrn;
	_UxCCopyS01             *UxContext;

	UxCopyS01Context = UxContext =
		(_UxCCopyS01 *) XtMalloc( sizeof(_UxCCopyS01) );

	rtrn = _Uxbuild_CopyS01();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_CopyS01()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_CopyS01();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

