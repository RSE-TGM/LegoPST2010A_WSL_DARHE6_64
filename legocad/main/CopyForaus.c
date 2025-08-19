
/*******************************************************************************
	CopyForaus.c
	(Generated from interface file CopyForaus.i)
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

#ifndef DESIGN_TIME
/*
   modulo CopyForaus.i
   tipo 
   release 1.3
   data 5/17/95
   reserved @(#)CopyForaus.i	1.3
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif


#include "legomain.h"

/* Missing function declarations */
extern void copy_file(char *, char *);

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
	Widget	UxCopyForaus;
} _UxCCopyForaus;

#define CopyForaus              UxCopyForausContext->UxCopyForaus

static _UxCCopyForaus	*UxCopyForausContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_CopyForaus();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	cancelCB_CopyForaus( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyForaus          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyForausContext;
	UxCopyForausContext = UxContext =
			(_UxCCopyForaus *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxCopyForausContext = UxSaveCtx;
}

static void	okCallback_CopyForaus( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyForaus          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyForausContext;
	UxCopyForausContext = UxContext =
			(_UxCCopyForaus *) UxGetContext( UxWidget );
	{
	extern char path_modello[];
	char source_file[256];
	char dest_file[256];
	
	strcpy(source_file,UxGetTextString(CopyForaus));
	
	sprintf(dest_file,"%s/%s",path_modello,FILE_FORAUS);
	
	
	copy_file(source_file,dest_file);
	
	UxDestroyInterface(UxWidget);
	}
	UxCopyForausContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_CopyForaus()
{
	Widget	CopyForaus_shell;

	CopyForaus_shell = XtVaCreatePopupShell( "CopyForaus_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 280,
			XmNy, 240,
			XmNwidth, 300,
			XmNheight, 380,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "CopyForaus",
			XmNiconName, "CopyForaus",
			NULL );

	CopyForaus = XtVaCreateManagedWidget( "CopyForaus",
			xmFileSelectionBoxWidgetClass, CopyForaus_shell,
			RES_CONVERT( XmNpattern, "foraus.for" ),
			XmNheight, 380,
			XmNwidth, 300,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( CopyForaus, (char *) UxCopyForausContext );

	XtAddCallback( CopyForaus, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxCopyForausContext );

	XtAddCallback( CopyForaus, XmNcancelCallback,
			cancelCB_CopyForaus,
			(XtPointer) UxCopyForausContext );
	XtAddCallback( CopyForaus, XmNokCallback,
			okCallback_CopyForaus,
			(XtPointer) UxCopyForausContext );



	return ( CopyForaus );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_CopyForaus()
{
	Widget                  rtrn;
	_UxCCopyForaus          *UxContext;

	UxCopyForausContext = UxContext =
		(_UxCCopyForaus *) XtMalloc( sizeof(_UxCCopyForaus) );

	rtrn = _Uxbuild_CopyForaus();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_CopyForaus()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_CopyForaus();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

