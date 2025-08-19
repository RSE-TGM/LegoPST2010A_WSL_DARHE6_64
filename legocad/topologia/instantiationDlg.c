
/*******************************************************************************
	instantiationDlg.c
	(Generated from interface file instantiationDlg.i)
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/BulletinB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo instantiationDlg.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)instantiationDlg.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

#include "UxSubproc.h"
#include "lg1.h"
extern char blockname[];
extern handle id_subproc;
int num_modulo;
void istanzia_blocco();
char s_num_modulo[10];

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
	Widget	UxscrolledWindow1;
	Widget	Uxinput_text;
	Widget	Uxsend_button;
} _UxCinstantiationDlg;

#define scrolledWindow1         UxInstantiationDlgContext->UxscrolledWindow1
#define input_text              UxInstantiationDlgContext->Uxinput_text
#define send_button             UxInstantiationDlgContext->Uxsend_button

static _UxCinstantiationDlg	*UxInstantiationDlgContext;

Widget	instantiationDlg;
Widget	output_text;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_instantiationDlg();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

void istanzia_blocco(pid,status,h)
int pid,status;
handle h;
{
    extern void add_block();
    Arg argo[3];
    Cardinal nargo=0;

    printf("\n istanzia blocco richiamata pid = %d status = %d",pid,status);

    nargo=0;
    XtSetArg(argo[0],XmNvalue,"");nargo++;
    XtSetValues(output_text,argo,nargo);
    XtSetValues(input_text,argo,nargo);

    UxPopdownInterface(instantiationDlg);

    add_block(PROCESSO);

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	unmapCB_instantiationDlg( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

static void	createCB_instantiationDlg( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

static void	destroyCB_instantiationDlg( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

static void	mapCB_instantiationDlg( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

static void	destroyCB_scrolledWindow1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	printf("DESTROY VALLBACK DELLA SCROLLED WINDOW\n");
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

static void	activateCB_send_button( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCinstantiationDlg    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxInstantiationDlgContext;
	UxInstantiationDlgContext = UxContext =
			(_UxCinstantiationDlg *) UxGetContext( UxWidget );
	{
	char s[128];
	strcpy(s,UxGetText(input_text));
	fprintf(stderr, ">>(%d) stringa in input sulla window %s\n",getpid(), s);
	
	UxSendSubproc(id_subproc, s);
	
	}
	UxInstantiationDlgContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_instantiationDlg()
{
	Widget	instantiationDlg_shell;

	instantiationDlg_shell = XtVaCreatePopupShell( "instantiationDlg_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 310,
			XmNy, 156,
			XmNwidth, 510,
			XmNheight, 580,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "instantiationDlg",
			XmNiconName, "instantiationDlg",
			NULL );

	instantiationDlg = XtVaCreateManagedWidget( "instantiationDlg",
			xmBulletinBoardWidgetClass, instantiationDlg_shell,
			XmNmappedWhenManaged, TRUE,
			RES_CONVERT( XmNdialogTitle, "Instantiation Dialog" ),
			XmNheight, 580,
			XmNwidth, 510,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( instantiationDlg, (char *) UxInstantiationDlgContext );

	createCB_instantiationDlg( instantiationDlg,
			(XtPointer) UxInstantiationDlgContext, (XtPointer) NULL );

	scrolledWindow1 = XtVaCreateManagedWidget( "scrolledWindow1",
			xmScrolledWindowWidgetClass, instantiationDlg,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 20,
			XmNx, 10,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow1, (char *) UxInstantiationDlgContext );

	output_text = XtVaCreateManagedWidget( "output_text",
			xmTextWidgetClass, scrolledWindow1,
			XmNscrollLeftSide, FALSE,
			XmNscrollVertical, TRUE,
			XmNscrollHorizontal, FALSE,
			XmNheight, 480,
			XmNwidth, 490,
			NULL );

	UxPutContext( output_text, (char *) UxInstantiationDlgContext );

	input_text = XtVaCreateManagedWidget( "input_text",
			xmTextWidgetClass, instantiationDlg,
			XmNheight, 40,
			XmNwidth, 390,
			XmNy, 520,
			XmNx, 10,
			NULL );

	UxPutContext( input_text, (char *) UxInstantiationDlgContext );

	send_button = XtVaCreateManagedWidget( "send_button",
			xmPushButtonWidgetClass, instantiationDlg,
			XmNshowAsDefault, 1,
			RES_CONVERT( XmNlabelString, "Send" ),
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 510,
			XmNx, 410,
			NULL );

	UxPutContext( send_button, (char *) UxInstantiationDlgContext );

	XtAddCallback( instantiationDlg, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxInstantiationDlgContext );

	XtVaSetValues(instantiationDlg,
			XmNdefaultButton, send_button,
			NULL );

	XtAddCallback( instantiationDlg, XmNunmapCallback,
			unmapCB_instantiationDlg,
			(XtPointer) UxInstantiationDlgContext );
	XtAddCallback( instantiationDlg, XmNdestroyCallback,
			destroyCB_instantiationDlg,
			(XtPointer) UxInstantiationDlgContext );
	XtAddCallback( instantiationDlg, XmNmapCallback,
			mapCB_instantiationDlg,
			(XtPointer) UxInstantiationDlgContext );

	XtAddCallback( scrolledWindow1, XmNdestroyCallback,
			destroyCB_scrolledWindow1,
			(XtPointer) UxInstantiationDlgContext );

	XtAddCallback( send_button, XmNactivateCallback,
			activateCB_send_button,
			(XtPointer) UxInstantiationDlgContext );



	return ( instantiationDlg );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_instantiationDlg()
{
	Widget                  rtrn;
	_UxCinstantiationDlg    *UxContext;

	UxInstantiationDlgContext = UxContext =
		(_UxCinstantiationDlg *) XtMalloc( sizeof(_UxCinstantiationDlg) );

	rtrn = _Uxbuild_instantiationDlg();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_instantiationDlg()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_instantiationDlg();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

