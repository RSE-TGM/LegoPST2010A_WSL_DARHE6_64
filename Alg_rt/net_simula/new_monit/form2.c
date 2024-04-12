
/*******************************************************************************
	form2.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
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
	Widget	Uxmenu1;
	Widget	Uxmenu1_p1;
	Widget	Uxmenu1_p1_b2;
	Widget	Uxmenu1_p1_b3;
	Widget	Uxmenu1_p1_b4;
	Widget	Uxmenu1_p1_b5;
	Widget	Uxmenu1_top_b1;
	Widget	Uxmenu1_p2;
	Widget	Uxmenu1_p2_b1;
	Widget	Uxmenu1_p2_b2;
	Widget	Uxmenu1_p2_b3;
	Widget	Uxmenu1_top_b2;
	Widget	Uxmenu1_p3;
	Widget	Uxmenu1_p3_b1;
	Widget	Uxmenu1_top_b3;
	Widget	Uxmenu1_p4;
	Widget	Uxmenu1_p4_b2;
	Widget	Uxmenu1_p4_b3;
	Widget	Uxmenu1_p4_b4;
	Widget	Uxmenu1_p4_b5;
	Widget	Uxmenu1_p4_b6;
	Widget	Uxmenu1_p4_b7;
	Widget	Uxmenu1_top_b4;
	Widget	UxpushButton3;
	Widget	UxpushButton4;
	Widget	UxpushButton5;
} _UxCform2;

#define menu1                   UxForm2Context->Uxmenu1
#define menu1_p1                UxForm2Context->Uxmenu1_p1
#define menu1_p1_b2             UxForm2Context->Uxmenu1_p1_b2
#define menu1_p1_b3             UxForm2Context->Uxmenu1_p1_b3
#define menu1_p1_b4             UxForm2Context->Uxmenu1_p1_b4
#define menu1_p1_b5             UxForm2Context->Uxmenu1_p1_b5
#define menu1_top_b1            UxForm2Context->Uxmenu1_top_b1
#define menu1_p2                UxForm2Context->Uxmenu1_p2
#define menu1_p2_b1             UxForm2Context->Uxmenu1_p2_b1
#define menu1_p2_b2             UxForm2Context->Uxmenu1_p2_b2
#define menu1_p2_b3             UxForm2Context->Uxmenu1_p2_b3
#define menu1_top_b2            UxForm2Context->Uxmenu1_top_b2
#define menu1_p3                UxForm2Context->Uxmenu1_p3
#define menu1_p3_b1             UxForm2Context->Uxmenu1_p3_b1
#define menu1_top_b3            UxForm2Context->Uxmenu1_top_b3
#define menu1_p4                UxForm2Context->Uxmenu1_p4
#define menu1_p4_b2             UxForm2Context->Uxmenu1_p4_b2
#define menu1_p4_b3             UxForm2Context->Uxmenu1_p4_b3
#define menu1_p4_b4             UxForm2Context->Uxmenu1_p4_b4
#define menu1_p4_b5             UxForm2Context->Uxmenu1_p4_b5
#define menu1_p4_b6             UxForm2Context->Uxmenu1_p4_b6
#define menu1_p4_b7             UxForm2Context->Uxmenu1_p4_b7
#define menu1_top_b4            UxForm2Context->Uxmenu1_top_b4
#define pushButton3             UxForm2Context->UxpushButton3
#define pushButton4             UxForm2Context->UxpushButton4
#define pushButton5             UxForm2Context->UxpushButton5

static _UxCform2	*UxForm2Context;

Widget	form2;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_form2();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_menu1_p1_b2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("open \n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p1_b3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("save\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p1_b5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("quit\n"); }
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p2_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("init da ci **********\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p2_b2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("init da backtrack ********\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p2_b3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("richiesta clear\n"); }
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p3_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("richiesta snapshot\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p4_b2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("registrazioni di backtrack\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p4_b3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("registrazioni CR\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p4_b4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("I&T al\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_menu1_p4_b5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{printf ("perf. analisys\n");}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{
	printf ("RICHIESTA DI RUN\n");
	}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{
	printf ("richiesta di FREEZE\n");
	}
	UxForm2Context = UxSaveCtx;
}

static void	activateCB_pushButton5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCform2               *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForm2Context;
	UxForm2Context = UxContext =
			(_UxCform2 *) UxGetContext( UxWidget );
	{
	printf ("richiesta di STEP\n");
	}
	UxForm2Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_form2()
{
	Widget	form2_shell;
	Widget	menu1_p1_shell;
	Widget	menu1_p2_shell;
	Widget	menu1_p3_shell;
	Widget	menu1_p4_shell;

	form2_shell = XtVaCreatePopupShell( "form2_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 488,
			XmNy, 634,
			XmNwidth, 591,
			XmNheight, 129,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "form2",
			XmNiconName, "form2",
			NULL );

	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass, form2_shell,
			XmNbuttonFontList, UxConvertFontList( "courb12" ),
			XmNtextFontList, UxConvertFontList( "courb12" ),
			XmNautoUnmanage, FALSE,
			XmNallowOverlap, FALSE,
			XmNheight, 129,
			XmNwidth, 591,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxForm2Context );

	menu1 = XtVaCreateManagedWidget( "menu1",
			xmRowColumnWidgetClass, form2,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			NULL );

	UxPutContext( menu1, (char *) UxForm2Context );

	menu1_p1_shell = XtVaCreatePopupShell ("menu1_p1_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1_p1 = XtVaCreateWidget( "menu1_p1",
			xmRowColumnWidgetClass, menu1_p1_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( menu1_p1, (char *) UxForm2Context );

	menu1_p1_b2 = XtVaCreateManagedWidget( "menu1_p1_b2",
			xmPushButtonWidgetClass, menu1_p1,
			RES_CONVERT( XmNmnemonic, "O" ),
			RES_CONVERT( XmNlabelString, "Open" ),
			NULL );

	UxPutContext( menu1_p1_b2, (char *) UxForm2Context );

	menu1_p1_b3 = XtVaCreateManagedWidget( "menu1_p1_b3",
			xmPushButtonWidgetClass, menu1_p1,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Save" ),
			NULL );

	UxPutContext( menu1_p1_b3, (char *) UxForm2Context );

	menu1_p1_b4 = XtVaCreateManagedWidget( "menu1_p1_b4",
			xmSeparatorWidgetClass, menu1_p1,
			NULL );

	UxPutContext( menu1_p1_b4, (char *) UxForm2Context );

	menu1_p1_b5 = XtVaCreateManagedWidget( "menu1_p1_b5",
			xmPushButtonWidgetClass, menu1_p1,
			RES_CONVERT( XmNmnemonic, "Q" ),
			RES_CONVERT( XmNlabelString, "Quit" ),
			NULL );

	UxPutContext( menu1_p1_b5, (char *) UxForm2Context );

	menu1_top_b1 = XtVaCreateManagedWidget( "menu1_top_b1",
			xmCascadeButtonWidgetClass, menu1,
			RES_CONVERT( XmNmnemonic, "F" ),
			XmNsubMenuId, menu1_p1,
			RES_CONVERT( XmNlabelString, "File" ),
			NULL );

	UxPutContext( menu1_top_b1, (char *) UxForm2Context );

	menu1_p2_shell = XtVaCreatePopupShell ("menu1_p2_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1_p2 = XtVaCreateWidget( "menu1_p2",
			xmRowColumnWidgetClass, menu1_p2_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( menu1_p2, (char *) UxForm2Context );

	menu1_p2_b1 = XtVaCreateManagedWidget( "menu1_p2_b1",
			xmPushButtonWidgetClass, menu1_p2,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "from I.C." ),
			NULL );

	UxPutContext( menu1_p2_b1, (char *) UxForm2Context );

	menu1_p2_b2 = XtVaCreateManagedWidget( "menu1_p2_b2",
			xmPushButtonWidgetClass, menu1_p2,
			RES_CONVERT( XmNmnemonic, "B" ),
			RES_CONVERT( XmNlabelString, "from Backtrack" ),
			NULL );

	UxPutContext( menu1_p2_b2, (char *) UxForm2Context );

	menu1_p2_b3 = XtVaCreateManagedWidget( "menu1_p2_b3",
			xmPushButtonWidgetClass, menu1_p2,
			RES_CONVERT( XmNmnemonic, "C" ),
			RES_CONVERT( XmNlabelString, "Clear" ),
			NULL );

	UxPutContext( menu1_p2_b3, (char *) UxForm2Context );

	menu1_top_b2 = XtVaCreateManagedWidget( "menu1_top_b2",
			xmCascadeButtonWidgetClass, menu1,
			XmNsubMenuId, menu1_p2,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "Init" ),
			NULL );

	UxPutContext( menu1_top_b2, (char *) UxForm2Context );

	menu1_p3_shell = XtVaCreatePopupShell ("menu1_p3_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1_p3 = XtVaCreateWidget( "menu1_p3",
			xmRowColumnWidgetClass, menu1_p3_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( menu1_p3, (char *) UxForm2Context );

	menu1_p3_b1 = XtVaCreateManagedWidget( "menu1_p3_b1",
			xmPushButtonWidgetClass, menu1_p3,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Snapshot management" ),
			NULL );

	UxPutContext( menu1_p3_b1, (char *) UxForm2Context );

	menu1_top_b3 = XtVaCreateManagedWidget( "menu1_top_b3",
			xmCascadeButtonWidgetClass, menu1,
			XmNsubMenuId, menu1_p3,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Snapshot" ),
			NULL );

	UxPutContext( menu1_top_b3, (char *) UxForm2Context );

	menu1_p4_shell = XtVaCreatePopupShell ("menu1_p4_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu1_p4 = XtVaCreateWidget( "menu1_p4",
			xmRowColumnWidgetClass, menu1_p4_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( menu1_p4, (char *) UxForm2Context );

	menu1_p4_b2 = XtVaCreateManagedWidget( "menu1_p4_b2",
			xmPushButtonWidgetClass, menu1_p4,
			RES_CONVERT( XmNmnemonic, "B" ),
			RES_CONVERT( XmNlabelString, "Backtrack management" ),
			NULL );

	UxPutContext( menu1_p4_b2, (char *) UxForm2Context );

	menu1_p4_b3 = XtVaCreateManagedWidget( "menu1_p4_b3",
			xmPushButtonWidgetClass, menu1_p4,
			RES_CONVERT( XmNmnemonic, "C" ),
			RES_CONVERT( XmNlabelString, "Continuos recording" ),
			NULL );

	UxPutContext( menu1_p4_b3, (char *) UxForm2Context );

	menu1_p4_b4 = XtVaCreateManagedWidget( "menu1_p4_b4",
			xmPushButtonWidgetClass, menu1_p4,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "Instructor & Trainee A.L." ),
			NULL );

	UxPutContext( menu1_p4_b4, (char *) UxForm2Context );

	menu1_p4_b5 = XtVaCreateManagedWidget( "menu1_p4_b5",
			xmPushButtonWidgetClass, menu1_p4,
			RES_CONVERT( XmNmnemonic, "P" ),
			RES_CONVERT( XmNlabelString, "Performance analisys" ),
			NULL );

	UxPutContext( menu1_p4_b5, (char *) UxForm2Context );

	menu1_p4_b6 = XtVaCreateManagedWidget( "menu1_p4_b6",
			xmSeparatorGadgetClass, menu1_p4,
			NULL );

	UxPutContext( menu1_p4_b6, (char *) UxForm2Context );

	menu1_p4_b7 = XtVaCreateManagedWidget( "menu1_p4_b7",
			xmPushButtonWidgetClass, menu1_p4,
			RES_CONVERT( XmNmnemonic, "A" ),
			RES_CONVERT( XmNlabelString, "Archivio" ),
			NULL );

	UxPutContext( menu1_p4_b7, (char *) UxForm2Context );

	menu1_top_b4 = XtVaCreateManagedWidget( "menu1_top_b4",
			xmCascadeButtonWidgetClass, menu1,
			XmNsubMenuId, menu1_p4,
			RES_CONVERT( XmNmnemonic, "R" ),
			RES_CONVERT( XmNlabelString, "Recording" ),
			NULL );

	UxPutContext( menu1_top_b4, (char *) UxForm2Context );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "RUN" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 30,
			NULL );

	UxPutContext( pushButton3, (char *) UxForm2Context );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "FREEZE" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 210,
			NULL );

	UxPutContext( pushButton4, (char *) UxForm2Context );

	pushButton5 = XtVaCreateManagedWidget( "pushButton5",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "STEP" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 390,
			NULL );

	UxPutContext( pushButton5, (char *) UxForm2Context );

	XtAddCallback( form2, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p1_b2, XmNactivateCallback,
			activateCB_menu1_p1_b2,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p1_b3, XmNactivateCallback,
			activateCB_menu1_p1_b3,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p1_b5, XmNactivateCallback,
			activateCB_menu1_p1_b5,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p2_b1, XmNactivateCallback,
			activateCB_menu1_p2_b1,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p2_b2, XmNactivateCallback,
			activateCB_menu1_p2_b2,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p2_b3, XmNactivateCallback,
			activateCB_menu1_p2_b3,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p3_b1, XmNactivateCallback,
			activateCB_menu1_p3_b1,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p4_b2, XmNactivateCallback,
			activateCB_menu1_p4_b2,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p4_b3, XmNactivateCallback,
			activateCB_menu1_p4_b3,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p4_b4, XmNactivateCallback,
			activateCB_menu1_p4_b4,
			(XtPointer) UxForm2Context );

	XtAddCallback( menu1_p4_b5, XmNactivateCallback,
			activateCB_menu1_p4_b5,
			(XtPointer) UxForm2Context );

	XtAddCallback( pushButton3, XmNactivateCallback,
			activateCB_pushButton3,
			(XtPointer) UxForm2Context );

	XtAddCallback( pushButton4, XmNactivateCallback,
			activateCB_pushButton4,
			(XtPointer) UxForm2Context );

	XtAddCallback( pushButton5, XmNactivateCallback,
			activateCB_pushButton5,
			(XtPointer) UxForm2Context );



	return ( form2 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_form2()
{
	Widget                  rtrn;
	_UxCform2               *UxContext;

	UxForm2Context = UxContext =
		(_UxCform2 *) XtMalloc( sizeof(_UxCform2) );

	{
		printf ("creazione form2 *********\n");
		rtrn = _Uxbuild_form2();

		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_form2()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_form2();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

