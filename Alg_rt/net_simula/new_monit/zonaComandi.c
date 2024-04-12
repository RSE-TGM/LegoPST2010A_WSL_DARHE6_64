
/*******************************************************************************
	zonaComandi.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

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
	Widget	UxzonaComandi;
	Widget	Uxform21;
	Widget	Uxframe7;
	Widget	Uxform22;
	Widget	UxpushButton12;
	Widget	UxpushButton13;
} _UxCzonaComandi;

#define zonaComandi             UxZonaComandiContext->UxzonaComandi
#define form21                  UxZonaComandiContext->Uxform21
#define frame7                  UxZonaComandiContext->Uxframe7
#define form22                  UxZonaComandiContext->Uxform22
#define pushButton12            UxZonaComandiContext->UxpushButton12
#define pushButton13            UxZonaComandiContext->UxpushButton13

static _UxCzonaComandi	*UxZonaComandiContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_zonaComandi();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_zonaComandi()
{
	Widget	zonaComandi_shell;

	zonaComandi_shell = XtVaCreatePopupShell( "zonaComandi_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 680,
			XmNy, 420,
			XmNwidth, 425,
			XmNheight, 75,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "zonaComandi",
			XmNiconName, "zonaComandi",
			NULL );

	zonaComandi = XtVaCreateManagedWidget( "zonaComandi",
			xmFormWidgetClass, zonaComandi_shell,
			XmNheight, 75,
			XmNwidth, 425,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( zonaComandi, (char *) UxZonaComandiContext );

	form21 = XtVaCreateManagedWidget( "form21",
			xmFormWidgetClass, zonaComandi,
			XmNheight, 75,
			XmNwidth, 750,
			XmNy, 108,
			XmNx, 16,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form21, (char *) UxZonaComandiContext );

	frame7 = XtVaCreateManagedWidget( "frame7",
			xmFrameWidgetClass, zonaComandi,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 50,
			XmNwidth, 795,
			XmNy, 405,
			XmNx, 10,
			NULL );

	UxPutContext( frame7, (char *) UxZonaComandiContext );

	form22 = XtVaCreateManagedWidget( "form22",
			xmFormWidgetClass, frame7,
			XmNheight, 75,
			XmNwidth, 745,
			XmNy, 0,
			XmNx, 0,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form22, (char *) UxZonaComandiContext );

	pushButton12 = XtVaCreateManagedWidget( "pushButton12",
			xmPushButtonWidgetClass, form22,
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

	UxPutContext( pushButton12, (char *) UxZonaComandiContext );

	pushButton13 = XtVaCreateManagedWidget( "pushButton13",
			xmPushButtonWidgetClass, form22,
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

	UxPutContext( pushButton13, (char *) UxZonaComandiContext );

	XtAddCallback( zonaComandi, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxZonaComandiContext );



	return ( zonaComandi );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_zonaComandi()
{
	Widget                  rtrn;
	_UxCzonaComandi         *UxContext;

	UxZonaComandiContext = UxContext =
		(_UxCzonaComandi *) XtMalloc( sizeof(_UxCzonaComandi) );

	rtrn = _Uxbuild_zonaComandi();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_zonaComandi()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_zonaComandi();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

