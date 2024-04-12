/**********************************************************************
*
*       C Source:               nyi.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 16 17:11:50 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: nyi.c,2 %  (%full_filespec: 1,csrc,nyi.c,2 %)";
#endif
/*
   modulo nyi.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)nyi.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)nyi.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*******************************************************************************
	nyi.c

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

#include <Xl/XlGrafico.h>
#include "nyi.h"

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
	S_XLGRAFICO *UxPXlGrafico;
	Widget	Uxnyi;
} _UxCnyi;

#define nyi_Graf		UxNyiContext->UxPXlGrafico
#define nyi                     UxNyiContext->Uxnyi

static _UxCnyi	*UxNyiContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_nyi();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_nyi(PuntGraf)
S_XLGRAFICO *PuntGraf;
{
	Widget	nyi_shell;

/*  Setto il puntatore alla struttura delle variabili del grafics  */
nyi_Graf = PuntGraf;

	nyi_shell = XtVaCreatePopupShell( "nyi_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNtitle, "nyi",
			NULL );

	nyi = XtVaCreateWidget( "nyi",
			xmMessageBoxWidgetClass, nyi_shell,
			RES_CONVERT( XmNmessageString, "Comando non ancora implementato" ),
			XmNdefaultPosition, TRUE,
			XmNautoUnmanage, TRUE,
			NULL );

	UxPutContext( nyi, (char *) UxNyiContext );

	create_proc( nyi,
			4, (XtPointer) NULL );

	XtAddCallback( nyi, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxNyiContext );

	return ( nyi );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_nyi(PuntGraf)
S_XLGRAFICO *PuntGraf;
{
	Widget                  rtrn;
	_UxCnyi                 *UxContext;

	UxNyiContext = UxContext =
		(_UxCnyi *) XtMalloc( sizeof(_UxCnyi) );

	rtrn = _Uxbuild_nyi(PuntGraf);

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_nyi(PuntGraf)
S_XLGRAFICO *PuntGraf;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_nyi(PuntGraf);

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

