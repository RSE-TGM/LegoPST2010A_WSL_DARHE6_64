
/*******************************************************************************
	dialogShell1.c
	(Generated from interface file dialogShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushBG.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo dialogShell1.i
   tipo 
   release 2.15
   data 4/26/95
   reserved @(#)dialogShell1.i	2.15
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

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
	Widget	UxdialogShell1;
	Widget	UxpanedWindow2;
	Widget	Uxform2;
	Widget	Uxlabel2;
	Widget	Uxlabel8;
	Widget	Uxlabel9;
	Widget	Uxlabel10;
	Widget	UxscrolledWindow4;
	Widget	UxscrolledList5;
	Widget	UxscrolledWindow5;
	Widget	UxscrolledList6;
	Widget	Uxform4;
	Widget	Uxlabel11;
	Widget	Uxlabel12;
	Widget	UxscrolledWindow7;
	Widget	UxscrolledList7;
	Widget	UxscrolledWindow8;
	Widget	UxscrolledList8;
	Widget	UxpushButtonGadget3;
	Widget	UxpushButtonGadget4;
	swidget	Uxpadre;
} _UxCdialogShell1;

#define dialogShell1            UxDialogShell1Context->UxdialogShell1
#define panedWindow2            UxDialogShell1Context->UxpanedWindow2
#define form2                   UxDialogShell1Context->Uxform2
#define label2                  UxDialogShell1Context->Uxlabel2
#define label8                  UxDialogShell1Context->Uxlabel8
#define label9                  UxDialogShell1Context->Uxlabel9
#define label10                 UxDialogShell1Context->Uxlabel10
#define scrolledWindow4         UxDialogShell1Context->UxscrolledWindow4
#define scrolledList5           UxDialogShell1Context->UxscrolledList5
#define scrolledWindow5         UxDialogShell1Context->UxscrolledWindow5
#define scrolledList6           UxDialogShell1Context->UxscrolledList6
#define form4                   UxDialogShell1Context->Uxform4
#define label11                 UxDialogShell1Context->Uxlabel11
#define label12                 UxDialogShell1Context->Uxlabel12
#define scrolledWindow7         UxDialogShell1Context->UxscrolledWindow7
#define scrolledList7           UxDialogShell1Context->UxscrolledList7
#define scrolledWindow8         UxDialogShell1Context->UxscrolledWindow8
#define scrolledList8           UxDialogShell1Context->UxscrolledList8
#define pushButtonGadget3       UxDialogShell1Context->UxpushButtonGadget3
#define pushButtonGadget4       UxDialogShell1Context->UxpushButtonGadget4
#define padre                   UxDialogShell1Context->Uxpadre

static _UxCdialogShell1	*UxDialogShell1Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	popup_dialogShell1();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_dialogShell1()
{

	dialogShell1 = XtVaCreatePopupShell( "dialogShell1",
			xmDialogShellWidgetClass, padre,
			XmNheight, 620,
			XmNwidth, 560,
			XmNy, 110,
			XmNx, 440,
			NULL );

	UxPutContext( dialogShell1, (char *) UxDialogShell1Context );

	panedWindow2 = XtVaCreateWidget( "panedWindow2",
			xmPanedWindowWidgetClass, dialogShell1,
			XmNheight, 510,
			XmNwidth, 440,
			XmNy, 0,
			XmNx, 0,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( panedWindow2, (char *) UxDialogShell1Context );

	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass, panedWindow2,
			XmNheight, 250,
			XmNwidth, 527,
			XmNy, 3,
			XmNx, 3,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxDialogShell1Context );

	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "INPUT TO MODEL" ),
			XmNheight, 20,
			XmNwidth, 210,
			XmNy, 10,
			XmNx, 40,
			NULL );

	UxPutContext( label2, (char *) UxDialogShell1Context );

	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "OUTPUT TO MODEL" ),
			XmNheight, 20,
			XmNwidth, 210,
			XmNy, 10,
			XmNx, 250,
			NULL );

	UxPutContext( label8, (char *) UxDialogShell1Context );

	label9 = XtVaCreateManagedWidget( "label9",
			xmLabelWidgetClass, form2,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "known variables" ),
			XmNheight, 20,
			XmNwidth, 210,
			XmNy, 40,
			XmNx, 20,
			NULL );

	UxPutContext( label9, (char *) UxDialogShell1Context );

	label10 = XtVaCreateManagedWidget( "label10",
			xmLabelWidgetClass, form2,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "unknown variables" ),
			XmNheight, 20,
			XmNwidth, 200,
			XmNy, 40,
			XmNx, 260,
			NULL );

	UxPutContext( label10, (char *) UxDialogShell1Context );

	scrolledWindow4 = XtVaCreateManagedWidget( "scrolledWindow4",
			xmScrolledWindowWidgetClass, form2,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 60,
			XmNx, 20,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow4, (char *) UxDialogShell1Context );

	scrolledList5 = XtVaCreateManagedWidget( "scrolledList5",
			xmListWidgetClass, scrolledWindow4,
			XmNheight, 180,
			XmNwidth, 220,
			NULL );

	UxPutContext( scrolledList5, (char *) UxDialogShell1Context );

	scrolledWindow5 = XtVaCreateManagedWidget( "scrolledWindow5",
			xmScrolledWindowWidgetClass, form2,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 60,
			XmNx, 260,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow5, (char *) UxDialogShell1Context );

	scrolledList6 = XtVaCreateManagedWidget( "scrolledList6",
			xmListWidgetClass, scrolledWindow5,
			XmNheight, 180,
			XmNwidth, 230,
			NULL );

	UxPutContext( scrolledList6, (char *) UxDialogShell1Context );

	form4 = XtVaCreateManagedWidget( "form4",
			xmFormWidgetClass, panedWindow2,
			XmNheight, 319,
			XmNwidth, 527,
			XmNy, 261,
			XmNx, 3,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form4, (char *) UxDialogShell1Context );

	label11 = XtVaCreateManagedWidget( "label11",
			xmLabelWidgetClass, form4,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "known variables" ),
			XmNheight, 20,
			XmNwidth, 210,
			XmNy, 30,
			XmNx, 260,
			NULL );

	UxPutContext( label11, (char *) UxDialogShell1Context );

	label12 = XtVaCreateManagedWidget( "label12",
			xmLabelWidgetClass, form4,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "unknown variables" ),
			XmNheight, 20,
			XmNwidth, 210,
			XmNy, 30,
			XmNx, 30,
			NULL );

	UxPutContext( label12, (char *) UxDialogShell1Context );

	scrolledWindow7 = XtVaCreateManagedWidget( "scrolledWindow7",
			xmScrolledWindowWidgetClass, form4,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 50,
			XmNx, 30,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow7, (char *) UxDialogShell1Context );

	scrolledList7 = XtVaCreateManagedWidget( "scrolledList7",
			xmListWidgetClass, scrolledWindow7,
			XmNheight, 200,
			XmNwidth, 210,
			NULL );

	UxPutContext( scrolledList7, (char *) UxDialogShell1Context );

	scrolledWindow8 = XtVaCreateManagedWidget( "scrolledWindow8",
			xmScrolledWindowWidgetClass, form4,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 50,
			XmNx, 260,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow8, (char *) UxDialogShell1Context );

	scrolledList8 = XtVaCreateManagedWidget( "scrolledList8",
			xmListWidgetClass, scrolledWindow8,
			XmNheight, 200,
			XmNwidth, 230,
			NULL );

	UxPutContext( scrolledList8, (char *) UxDialogShell1Context );

	pushButtonGadget3 = XtVaCreateManagedWidget( "pushButtonGadget3",
			xmPushButtonGadgetClass, form4,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 30,
			XmNwidth, 110,
			XmNy, 270,
			XmNx, 90,
			NULL );

	UxPutContext( pushButtonGadget3, (char *) UxDialogShell1Context );

	pushButtonGadget4 = XtVaCreateManagedWidget( "pushButtonGadget4",
			xmPushButtonGadgetClass, form4,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 110,
			XmNy, 270,
			XmNx, 320,
			NULL );

	UxPutContext( pushButtonGadget4, (char *) UxDialogShell1Context );

	XtAddCallback( dialogShell1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxDialogShell1Context );



	return ( dialogShell1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_popup_dialogShell1( _Uxpadre )
	swidget	_Uxpadre;
{
	Widget                  rtrn;
	_UxCdialogShell1        *UxContext;

	UxDialogShell1Context = UxContext =
		(_UxCdialogShell1 *) XtMalloc( sizeof(_UxCdialogShell1) );

	padre = _Uxpadre;
	rtrn = _Uxbuild_dialogShell1();

	UxPopupInterface(rtrn, no_grab);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	popup_dialogShell1( _Uxpadre )
	swidget	_Uxpadre;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_popup_dialogShell1( _Uxpadre );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

