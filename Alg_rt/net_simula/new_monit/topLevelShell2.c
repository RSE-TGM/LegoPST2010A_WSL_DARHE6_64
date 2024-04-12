
/*******************************************************************************
	topLevelShell2.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <X11/Shell.h>


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
	Widget	UxtopLevelShell2;
	Widget	Uxform2;
	Widget	UxscrolledWindow1;
	Widget	UxrowColumn1;
	Widget	Uxform3;
	Widget	Uxlabel2;
	Widget	Uxlabel4;
	Widget	Uxtext2;
	Widget	Uxform4;
	Widget	Uxlabel5;
	Widget	Uxlabel6;
	Widget	Uxtext3;
	Widget	Uxform5;
	Widget	Uxlabel7;
	Widget	Uxlabel8;
	Widget	Uxtext4;
	Widget	Uxform6;
	Widget	Uxlabel9;
	Widget	Uxlabel10;
	Widget	Uxtext5;
} _UxCtopLevelShell2;

#define topLevelShell2          UxTopLevelShell2Context->UxtopLevelShell2
#define form2                   UxTopLevelShell2Context->Uxform2
#define scrolledWindow1         UxTopLevelShell2Context->UxscrolledWindow1
#define rowColumn1              UxTopLevelShell2Context->UxrowColumn1
#define form3                   UxTopLevelShell2Context->Uxform3
#define label2                  UxTopLevelShell2Context->Uxlabel2
#define label4                  UxTopLevelShell2Context->Uxlabel4
#define text2                   UxTopLevelShell2Context->Uxtext2
#define form4                   UxTopLevelShell2Context->Uxform4
#define label5                  UxTopLevelShell2Context->Uxlabel5
#define label6                  UxTopLevelShell2Context->Uxlabel6
#define text3                   UxTopLevelShell2Context->Uxtext3
#define form5                   UxTopLevelShell2Context->Uxform5
#define label7                  UxTopLevelShell2Context->Uxlabel7
#define label8                  UxTopLevelShell2Context->Uxlabel8
#define text4                   UxTopLevelShell2Context->Uxtext4
#define form6                   UxTopLevelShell2Context->Uxform6
#define label9                  UxTopLevelShell2Context->Uxlabel9
#define label10                 UxTopLevelShell2Context->Uxlabel10
#define text5                   UxTopLevelShell2Context->Uxtext5

static _UxCtopLevelShell2	*UxTopLevelShell2Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_topLevelShell2();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_topLevelShell2()
{

	topLevelShell2 = XtVaCreatePopupShell( "topLevelShell2",
			topLevelShellWidgetClass, UxTopLevel,
			XmNheight, 459,
			XmNwidth, 758,
			XmNy, 384,
			XmNx, 339,
			NULL );

	UxPutContext( topLevelShell2, (char *) UxTopLevelShell2Context );

	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass, topLevelShell2,
			XmNheight, 350,
			XmNwidth, 685,
			XmNy, 40,
			XmNx, 35,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxTopLevelShell2Context );

	scrolledWindow1 = XtVaCreateManagedWidget( "scrolledWindow1",
			xmScrolledWindowWidgetClass, form2,
			XmNleftOffset, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 30,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 315,
			XmNwidth, 720,
			XmNy, 55,
			XmNx, 25,
			XmNscrollingPolicy, XmAUTOMATIC,
			NULL );

	UxPutContext( scrolledWindow1, (char *) UxTopLevelShell2Context );

	rowColumn1 = XtVaCreateManagedWidget( "rowColumn1",
			xmRowColumnWidgetClass, scrolledWindow1,
			XmNresizeHeight, FALSE,
			XmNmarginWidth, 0,
			XmNmarginHeight, 0,
			XmNheight, 315,
			XmNwidth, 780,
			XmNy, 4,
			XmNx, 2,
			NULL );

	UxPutContext( rowColumn1, (char *) UxTopLevelShell2Context );

	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass, rowColumn1,
			XmNheight, 30,
			XmNwidth, 835,
			XmNy, 0,
			XmNx, 0,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form3, (char *) UxTopLevelShell2Context );

	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 10,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 25,
			XmNwidth, 35,
			XmNy, 5,
			XmNx, 0,
			NULL );

	UxPutContext( label2, (char *) UxTopLevelShell2Context );

	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftWidget, label2,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNheight, 25,
			XmNwidth, 40,
			XmNy, 5,
			XmNx, 45,
			NULL );

	UxPutContext( label4, (char *) UxTopLevelShell2Context );

	text2 = XtVaCreateManagedWidget( "text2",
			xmTextWidgetClass, form3,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftWidget, label4,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 20,
			XmNwidth, 710,
			XmNy, 5,
			XmNx, 120,
			NULL );

	UxPutContext( text2, (char *) UxTopLevelShell2Context );

	form4 = XtVaCreateManagedWidget( "form4",
			xmFormWidgetClass, rowColumn1,
			XmNheight, 30,
			XmNwidth, 835,
			XmNy, 10,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form4, (char *) UxTopLevelShell2Context );

	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass, form4,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 10,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 25,
			XmNwidth, 35,
			XmNy, 5,
			XmNx, 0,
			NULL );

	UxPutContext( label5, (char *) UxTopLevelShell2Context );

	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass, form4,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftWidget, label5,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNheight, 25,
			XmNwidth, 40,
			XmNy, 5,
			XmNx, 45,
			NULL );

	UxPutContext( label6, (char *) UxTopLevelShell2Context );

	text3 = XtVaCreateManagedWidget( "text3",
			xmTextWidgetClass, form4,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftWidget, label6,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 20,
			XmNwidth, 710,
			XmNy, 5,
			XmNx, 120,
			NULL );

	UxPutContext( text3, (char *) UxTopLevelShell2Context );

	form5 = XtVaCreateManagedWidget( "form5",
			xmFormWidgetClass, rowColumn1,
			XmNheight, 30,
			XmNwidth, 835,
			XmNy, 43,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form5, (char *) UxTopLevelShell2Context );

	label7 = XtVaCreateManagedWidget( "label7",
			xmLabelWidgetClass, form5,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 10,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 25,
			XmNwidth, 35,
			XmNy, 5,
			XmNx, 0,
			NULL );

	UxPutContext( label7, (char *) UxTopLevelShell2Context );

	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass, form5,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftWidget, label7,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNheight, 25,
			XmNwidth, 40,
			XmNy, 5,
			XmNx, 45,
			NULL );

	UxPutContext( label8, (char *) UxTopLevelShell2Context );

	text4 = XtVaCreateManagedWidget( "text4",
			xmTextWidgetClass, form5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftWidget, label8,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 20,
			XmNwidth, 710,
			XmNy, 5,
			XmNx, 120,
			NULL );

	UxPutContext( text4, (char *) UxTopLevelShell2Context );

	form6 = XtVaCreateManagedWidget( "form6",
			xmFormWidgetClass, rowColumn1,
			XmNheight, 30,
			XmNwidth, 835,
			XmNy, 10,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form6, (char *) UxTopLevelShell2Context );

	label9 = XtVaCreateManagedWidget( "label9",
			xmLabelWidgetClass, form6,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 10,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 25,
			XmNwidth, 35,
			XmNy, 5,
			XmNx, 0,
			NULL );

	UxPutContext( label9, (char *) UxTopLevelShell2Context );

	label10 = XtVaCreateManagedWidget( "label10",
			xmLabelWidgetClass, form6,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftWidget, label9,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNheight, 25,
			XmNwidth, 40,
			XmNy, 5,
			XmNx, 45,
			NULL );

	UxPutContext( label10, (char *) UxTopLevelShell2Context );

	text5 = XtVaCreateManagedWidget( "text5",
			xmTextWidgetClass, form6,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftWidget, label10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 20,
			XmNwidth, 710,
			XmNy, 5,
			XmNx, 120,
			NULL );

	UxPutContext( text5, (char *) UxTopLevelShell2Context );

	XtAddCallback( topLevelShell2, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxTopLevelShell2Context );



	return ( topLevelShell2 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_topLevelShell2()
{
	Widget                  rtrn;
	_UxCtopLevelShell2      *UxContext;

	UxTopLevelShell2Context = UxContext =
		(_UxCtopLevelShell2 *) XtMalloc( sizeof(_UxCtopLevelShell2) );

	rtrn = _Uxbuild_topLevelShell2();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_topLevelShell2()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_topLevelShell2();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

