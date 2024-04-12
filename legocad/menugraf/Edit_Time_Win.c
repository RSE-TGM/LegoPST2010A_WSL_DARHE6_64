
/*******************************************************************************
	Edit_Time_Win.c
	(Generated from interface file Edit_Time_Win.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/TextF.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo Edit_Time_Win.i
   tipo 
   release 1.10
   data 3/28/95
   reserved @(#)Edit_Time_Win.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include "menu_graf.h"

extern int Scelta;

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
	Widget	Uxlabel2;
	Widget	Uxlabel4;
	Widget	Uxseparator1;
	Widget	UxpushButton1;
	Widget	UxpushButton2;
	Widget	Uxlabel1;
	Widget	Uxlabel3;
} _UxCEdit_Time_Win;

#define label2                  UxEdit_Time_WinContext->Uxlabel2
#define label4                  UxEdit_Time_WinContext->Uxlabel4
#define separator1              UxEdit_Time_WinContext->Uxseparator1
#define pushButton1             UxEdit_Time_WinContext->UxpushButton1
#define pushButton2             UxEdit_Time_WinContext->UxpushButton2
#define label1                  UxEdit_Time_WinContext->Uxlabel1
#define label3                  UxEdit_Time_WinContext->Uxlabel3

static _UxCEdit_Time_Win	*UxEdit_Time_WinContext;

Widget	Edit_Time_Win;
Widget	Titolo_edit;
Widget	Edt_start_time;
Widget	Edt_stop_time;
Widget	Etichetta_start;
Widget	Etichetta_stop;
Widget	textField_Start;
Widget	textField_Stop;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_Edit_Time_Win();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	valueChangedCB_textField_Start( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEdit_Time_Win       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdit_Time_WinContext;
	UxEdit_Time_WinContext = UxContext =
			(_UxCEdit_Time_Win *) UxGetContext( UxWidget );
	{
	
	}
	UxEdit_Time_WinContext = UxSaveCtx;
}

static void	activateCB_pushButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEdit_Time_Win       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdit_Time_WinContext;
	UxEdit_Time_WinContext = UxContext =
			(_UxCEdit_Time_Win *) UxGetContext( UxWidget );
	{
	if (Scelta == EXTRACT_TIME) F22_extract ();
	if (Scelta == SHIFT_TIME) F22_shift ();
	}
	UxEdit_Time_WinContext = UxSaveCtx;
}

static void	activateCB_pushButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEdit_Time_Win       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdit_Time_WinContext;
	UxEdit_Time_WinContext = UxContext =
			(_UxCEdit_Time_Win *) UxGetContext( UxWidget );
	UxPopdownInterface (Edit_Time_Win);
	UxEdit_Time_WinContext = UxSaveCtx;
}

static void	valueChangedCB_textField_Stop( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEdit_Time_Win       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdit_Time_WinContext;
	UxEdit_Time_WinContext = UxContext =
			(_UxCEdit_Time_Win *) UxGetContext( UxWidget );
	{
	
	}
	UxEdit_Time_WinContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Edit_Time_Win()
{
	Widget	Edit_Time_Win_shell;

	Edit_Time_Win_shell = XtVaCreatePopupShell( "Edit_Time_Win_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 440,
			XmNy, 525,
			XmNwidth, 544,
			XmNheight, 213,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Edit_Time_Win",
			XmNiconName, "Edit_Time_Win",
			NULL );

	Edit_Time_Win = XtVaCreateManagedWidget( "Edit_Time_Win",
			xmFormWidgetClass, Edit_Time_Win_shell,
			XmNheight, 213,
			XmNwidth, 544,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( Edit_Time_Win, (char *) UxEdit_Time_WinContext );

	Titolo_edit = XtVaCreateManagedWidget( "Titolo_edit",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-bold-r-normal--18-180-75-75-p-113-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "" ),
			XmNheight, 40,
			XmNwidth, 265,
			XmNy, 5,
			XmNx, 140,
			NULL );

	UxPutContext( Titolo_edit, (char *) UxEdit_Time_WinContext );

	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			XmNalignment, XmALIGNMENT_END,
			RES_CONVERT( XmNlabelString, "Start time:" ),
			XmNheight, 30,
			XmNwidth, 110,
			XmNy, 55,
			XmNx, 15,
			NULL );

	UxPutContext( label2, (char *) UxEdit_Time_WinContext );

	Edt_start_time = XtVaCreateManagedWidget( "Edt_start_time",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			RES_CONVERT( XmNlabelString, "" ),
			XmNalignment, XmALIGNMENT_END,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 50,
			XmNx, 125,
			NULL );

	UxPutContext( Edt_start_time, (char *) UxEdit_Time_WinContext );

	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			XmNalignment, XmALIGNMENT_END,
			RES_CONVERT( XmNlabelString, "Stop time:" ),
			XmNheight, 30,
			XmNwidth, 95,
			XmNy, 55,
			XmNx, 305,
			NULL );

	UxPutContext( label4, (char *) UxEdit_Time_WinContext );

	Edt_stop_time = XtVaCreateManagedWidget( "Edt_stop_time",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			RES_CONVERT( XmNlabelString, "" ),
			XmNalignment, XmALIGNMENT_END,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 50,
			XmNx, 400,
			NULL );

	UxPutContext( Edt_stop_time, (char *) UxEdit_Time_WinContext );

	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass, Edit_Time_Win,
			XmNseparatorType, XmSINGLE_DASHED_LINE,
			XmNorientation, XmVERTICAL,
			XmNheight, 100,
			XmNwidth, 25,
			XmNy, 50,
			XmNx, 260,
			NULL );

	UxPutContext( separator1, (char *) UxEdit_Time_WinContext );

	Etichetta_start = XtVaCreateManagedWidget( "Etichetta_start",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			XmNalignment, XmALIGNMENT_END,
			RES_CONVERT( XmNlabelString, "New start time:" ),
			XmNheight, 30,
			XmNwidth, 110,
			XmNy, 105,
			XmNx, 15,
			NULL );

	UxPutContext( Etichetta_start, (char *) UxEdit_Time_WinContext );

	Etichetta_stop = XtVaCreateManagedWidget( "Etichetta_stop",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			XmNalignment, XmALIGNMENT_END,
			RES_CONVERT( XmNlabelString, "New stop time:" ),
			XmNheight, 30,
			XmNwidth, 105,
			XmNy, 105,
			XmNx, 295,
			NULL );

	UxPutContext( Etichetta_stop, (char *) UxEdit_Time_WinContext );

	textField_Start = XtVaCreateManagedWidget( "textField_Start",
			xmTextFieldWidgetClass, Edit_Time_Win,
			XmNmaxLength, 8,
			XmNheight, 35,
			XmNwidth, 125,
			XmNy, 100,
			XmNx, 125,
			NULL );

	UxPutContext( textField_Start, (char *) UxEdit_Time_WinContext );

	pushButton1 = XtVaCreateManagedWidget( "pushButton1",
			xmPushButtonWidgetClass, Edit_Time_Win,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 35,
			XmNwidth, 90,
			XmNy, 160,
			XmNx, 20,
			NULL );

	UxPutContext( pushButton1, (char *) UxEdit_Time_WinContext );

	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass, Edit_Time_Win,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNheight, 35,
			XmNwidth, 90,
			XmNy, 160,
			XmNx, 120,
			NULL );

	UxPutContext( pushButton2, (char *) UxEdit_Time_WinContext );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "sec." ),
			XmNheight, 30,
			XmNwidth, 45,
			XmNy, 55,
			XmNx, 210,
			NULL );

	UxPutContext( label1, (char *) UxEdit_Time_WinContext );

	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass, Edit_Time_Win,
			XmNrecomputeSize, FALSE,
			XmNfontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "sec." ),
			XmNheight, 30,
			XmNwidth, 45,
			XmNy, 55,
			XmNx, 485,
			NULL );

	UxPutContext( label3, (char *) UxEdit_Time_WinContext );

	textField_Stop = XtVaCreateManagedWidget( "textField_Stop",
			xmTextFieldWidgetClass, Edit_Time_Win,
			XmNmaxLength, 8,
			XmNsensitive, TRUE,
			XmNheight, 35,
			XmNwidth, 120,
			XmNy, 100,
			XmNx, 400,
			NULL );

	UxPutContext( textField_Stop, (char *) UxEdit_Time_WinContext );

	XtAddCallback( Edit_Time_Win, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxEdit_Time_WinContext );

	XtAddCallback( textField_Start, XmNvalueChangedCallback,
			valueChangedCB_textField_Start,
			(XtPointer) UxEdit_Time_WinContext );

	XtAddCallback( pushButton1, XmNactivateCallback,
			activateCB_pushButton1,
			(XtPointer) UxEdit_Time_WinContext );

	XtAddCallback( pushButton2, XmNactivateCallback,
			activateCB_pushButton2,
			(XtPointer) UxEdit_Time_WinContext );

	XtAddCallback( textField_Stop, XmNvalueChangedCallback,
			valueChangedCB_textField_Stop,
			(XtPointer) UxEdit_Time_WinContext );



	return ( Edit_Time_Win );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_Edit_Time_Win()
{
	Widget                  rtrn;
	_UxCEdit_Time_Win       *UxContext;

	UxEdit_Time_WinContext = UxContext =
		(_UxCEdit_Time_Win *) XtMalloc( sizeof(_UxCEdit_Time_Win) );

	rtrn = _Uxbuild_Edit_Time_Win();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_Edit_Time_Win()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_Edit_Time_Win();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

