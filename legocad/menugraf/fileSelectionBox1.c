
/*******************************************************************************
	fileSelectionBox1.c
	(Generated from interface file fileSelectionBox1.i)
	Associated Resource file: fileSelectionBox1.rf
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
   modulo fileSelectionBox1.i
   tipo 
   release 1.10
   data 3/28/95
   reserved @(#)fileSelectionBox1.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif


extern swidget Menu_graf;
extern char *path_22dat,f22source[],f22target[],f22undo[];
extern XmString label_path_f22;
extern int non_f22;
extern char *getcwd();

char *path_22dat_appo;

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
} _UxCfileSelectionBox1;


static _UxCfileSelectionBox1	*UxFileSelectionBox1Context;

Widget	fileSelectionBox1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_fileSelectionBox1();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox1   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBox1Context;
	UxFileSelectionBox1Context = UxContext =
			(_UxCfileSelectionBox1 *) UxGetContext( UxWidget );
	{
	char appogg[100],cdo[200];
	Widget Figlio;
	
	CancellazioneF22();
	Figlio = XmFileSelectionBoxGetChild (fileSelectionBox1,XmDIALOG_TEXT);
	path_22dat_appo = XmTextGetString (Figlio);
	path_22dat = XmTextGetString (Figlio);
	
	strcpy (appogg,getcwd((char *)NULL,50));
	strcpy (f22source,tempnam(appogg, (char *)NULL ));
	strcpy (f22target,tempnam(appogg, (char *)NULL ));
	strcpy (f22undo,tempnam(appogg, (char *)NULL ));
	
	strcpy (path_22dat,f22source);
	strcat (path_22dat_appo,"\0");
	strcpy (cdo,"cp \0");
	strcat (cdo,path_22dat_appo);
	strcat (cdo," ");
	strcat (cdo,f22source);
	
	system (cdo);
	
	Carica_f22();
	
	if (!non_f22) UxPopdownInterface (fileSelectionBox1);
	}
	UxFileSelectionBox1Context = UxSaveCtx;
}

static void	cancelCB_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCfileSelectionBox1   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFileSelectionBox1Context;
	UxFileSelectionBox1Context = UxContext =
			(_UxCfileSelectionBox1 *) UxGetContext( UxWidget );
	{
	UxPopdownInterface (fileSelectionBox1);
	}
	UxFileSelectionBox1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_fileSelectionBox1()
{
	Widget	fileSelectionBox1_shell;

	fileSelectionBox1_shell = XtVaCreatePopupShell( "fileSelectionBox1_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 400,
			XmNy, 515,
			XmNwidth, 415,
			XmNheight, 462,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "fileSelectionBox1",
			XmNiconName, "fileSelectionBox1",
			NULL );

	fileSelectionBox1 = XtVaCreateManagedWidget( "fileSelectionBox1",
			xmFileSelectionBoxWidgetClass, fileSelectionBox1_shell,
			RES_CONVERT( XmNdirMask, "" ),
			RES_CONVERT( XmNpattern, "*" ),
			XmNheight, 462,
			XmNwidth, 415,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( fileSelectionBox1, (char *) UxFileSelectionBox1Context );

	XtAddCallback( fileSelectionBox1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxFileSelectionBox1Context );

	XtAddCallback( fileSelectionBox1, XmNokCallback,
			okCallback_fileSelectionBox1,
			(XtPointer) UxFileSelectionBox1Context );
	XtAddCallback( fileSelectionBox1, XmNcancelCallback,
			cancelCB_fileSelectionBox1,
			(XtPointer) UxFileSelectionBox1Context );



	return ( fileSelectionBox1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_fileSelectionBox1()
{
	Widget                  rtrn;
	_UxCfileSelectionBox1   *UxContext;

	UxFileSelectionBox1Context = UxContext =
		(_UxCfileSelectionBox1 *) XtMalloc( sizeof(_UxCfileSelectionBox1) );

	rtrn = _Uxbuild_fileSelectionBox1();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_fileSelectionBox1()
{
	Widget			_Uxrtrn;
	static int		_Uxinit = 0;

	if ( ! _Uxinit )
	{
		UxLoadResources( "fileSelectionBox1.rf" );
		_Uxinit = 1;
	}

	_Uxrtrn = _Ux_create_fileSelectionBox1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

