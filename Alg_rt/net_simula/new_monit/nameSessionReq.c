
/*******************************************************************************
	nameSessionReq.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
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
	Widget	UxnameSessionReq;
	Widget	Uxform10;
	Widget	Uxframe4;
	Widget	Uxform11;
	Widget	UxpushButton3;
	Widget	UxpushButton4;
	Widget	Uxlabel11;
	Widget	Uxform12;
	Widget	Uxlabel12;
	Widget	UxtextField1;
} _UxCnameSessionReq;

#define nameSessionReq          UxNameSessionReqContext->UxnameSessionReq
#define form10                  UxNameSessionReqContext->Uxform10
#define frame4                  UxNameSessionReqContext->Uxframe4
#define form11                  UxNameSessionReqContext->Uxform11
#define pushButton3             UxNameSessionReqContext->UxpushButton3
#define pushButton4             UxNameSessionReqContext->UxpushButton4
#define label11                 UxNameSessionReqContext->Uxlabel11
#define form12                  UxNameSessionReqContext->Uxform12
#define label12                 UxNameSessionReqContext->Uxlabel12
#define textField1              UxNameSessionReqContext->UxtextField1

static _UxCnameSessionReq	*UxNameSessionReqContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_nameSessionReq();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_nameSessionReq()
{
	Widget	nameSessionReq_shell;

	nameSessionReq_shell = XtVaCreatePopupShell( "nameSessionReq_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 579,
			XmNy, 47,
			XmNwidth, 450,
			XmNheight, 200,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "nameSessionReq",
			XmNiconName, "nameSessionReq",
			NULL );

	nameSessionReq = XtVaCreateManagedWidget( "nameSessionReq",
			xmFormWidgetClass, nameSessionReq_shell,
			XmNnoResize, TRUE,
			XmNheight, 200,
			XmNwidth, 450,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( nameSessionReq, (char *) UxNameSessionReqContext );

	form10 = XtVaCreateManagedWidget( "form10",
			xmFormWidgetClass, nameSessionReq,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 75,
			XmNwidth, 750,
			XmNy, 108,
			XmNx, 16,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form10, (char *) UxNameSessionReqContext );

	frame4 = XtVaCreateManagedWidget( "frame4",
			xmFrameWidgetClass, form10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 50,
			XmNwidth, 795,
			XmNy, 405,
			XmNx, 10,
			NULL );

	UxPutContext( frame4, (char *) UxNameSessionReqContext );

	form11 = XtVaCreateManagedWidget( "form11",
			xmFormWidgetClass, frame4,
			XmNheight, 72,
			XmNwidth, 745,
			XmNy, 0,
			XmNx, 0,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form11, (char *) UxNameSessionReqContext );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, form11,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftOffset, 100,
			XmNleftPosition, 0,
			XmNrightOffset, 20,
			XmNbottomOffset, 15,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_SELF,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "QUIT" ),
			XmNheight, 30,
			XmNwidth, 202,
			XmNy, 35,
			XmNx, 493,
			NULL );

	UxPutContext( pushButton3, (char *) UxNameSessionReqContext );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, form11,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 100,
			XmNrightAttachment, XmATTACH_SELF,
			XmNleftOffset, 20,
			XmNbottomOffset, 15,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "SAVE" ),
			XmNheight, 30,
			XmNwidth, 205,
			XmNy, 405,
			XmNx, 30,
			NULL );

	UxPutContext( pushButton4, (char *) UxNameSessionReqContext );

	label11 = XtVaCreateManagedWidget( "label11",
			xmLabelWidgetClass, nameSessionReq,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "red" ),
			RES_CONVERT( XmNlabelString, "Session name" ),
			XmNheight, 30,
			XmNwidth, 580,
			XmNy, 0,
			XmNx, 0,
			NULL );

	UxPutContext( label11, (char *) UxNameSessionReqContext );

	form12 = XtVaCreateManagedWidget( "form12",
			xmFormWidgetClass, nameSessionReq,
			XmNresizable, TRUE,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 80,
			XmNwidth, 540,
			XmNy, 45,
			XmNx, 20,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form12, (char *) UxNameSessionReqContext );

	label12 = XtVaCreateManagedWidget( "label12",
			xmLabelWidgetClass, form12,
			RES_CONVERT( XmNlabelString, "Title:" ),
			XmNheight, 37,
			XmNwidth, 110,
			XmNy, 20,
			XmNx, 0,
			NULL );

	UxPutContext( label12, (char *) UxNameSessionReqContext );

	textField1 = XtVaCreateManagedWidget( "textField1",
			xmTextFieldWidgetClass, form12,
			XmNrightOffset, 20,
			XmNleftWidget, label12,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNheight, 35,
			XmNwidth, 445,
			XmNy, 25,
			XmNx, 90,
			NULL );

	UxPutContext( textField1, (char *) UxNameSessionReqContext );

	XtAddCallback( nameSessionReq, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxNameSessionReqContext );



	return ( nameSessionReq );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_nameSessionReq()
{
	Widget                  rtrn;
	_UxCnameSessionReq      *UxContext;

	UxNameSessionReqContext = UxContext =
		(_UxCnameSessionReq *) XtMalloc( sizeof(_UxCnameSessionReq) );

	rtrn = _Uxbuild_nameSessionReq();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_nameSessionReq()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_nameSessionReq();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

