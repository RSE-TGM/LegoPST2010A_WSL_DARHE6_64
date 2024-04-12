
/*******************************************************************************
	ViewS01.c
	(Generated from interface file ViewS01.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo ViewS01.i
   tipo 
   release 1.24
   data 8/29/95
   reserved @(#)ViewS01.i	1.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


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
	Widget	UxViewS01;
	Widget	UxpanedWindow4;
	Widget	Uxform6;
	Widget	UxpushButton3;
	Widget	UxscrolledWindow4;
	Widget	UxscrolledText2;
	Widget	Uxlabel3;
	Widget	UxpushButton4;
	unsigned char	*Uxstringa;
	unsigned char	*Uxfilename;
} _UxCViewS01;

#define ViewS01                 UxViewS01Context->UxViewS01
#define panedWindow4            UxViewS01Context->UxpanedWindow4
#define form6                   UxViewS01Context->Uxform6
#define pushButton3             UxViewS01Context->UxpushButton3
#define scrolledWindow4         UxViewS01Context->UxscrolledWindow4
#define scrolledText2           UxViewS01Context->UxscrolledText2
#define label3                  UxViewS01Context->Uxlabel3
#define pushButton4             UxViewS01Context->UxpushButton4
#define stringa                 UxViewS01Context->Uxstringa
#define filename                UxViewS01Context->Uxfilename

static _UxCViewS01	*UxViewS01Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_ViewS01();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	destroyCB_panedWindow4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCViewS01             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxViewS01Context;
	UxViewS01Context = UxContext =
			(_UxCViewS01 *) UxGetContext( UxWidget );
	{
	
	}
	UxViewS01Context = UxSaveCtx;
}

static void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCViewS01             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxViewS01Context;
	UxViewS01Context = UxContext =
			(_UxCViewS01 *) UxGetContext( UxWidget );
	{
	if( stringa != NULL)
	   free( stringa );
	UxDestroyInterface(ViewS01);
	}
	UxViewS01Context = UxSaveCtx;
}

static void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCViewS01             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxViewS01Context;
	UxViewS01Context = UxContext =
			(_UxCViewS01 *) UxGetContext( UxWidget );
	{
	if( stringa != NULL)
	   XtFree( stringa );
	UxDestroyInterface(ViewS01);
	
	}
	UxViewS01Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ViewS01()
{

	ViewS01 = XtVaCreatePopupShell( "ViewS01",
			topLevelShellWidgetClass, UxTopLevel,
			XmNheight, 620,
			XmNwidth, 490,
			XmNy, 290,
			XmNx, 520,
			NULL );

	UxPutContext( ViewS01, (char *) UxViewS01Context );

	panedWindow4 = XtVaCreateManagedWidget( "panedWindow4",
			xmPanedWindowWidgetClass, ViewS01,
			XmNheight, 330,
			XmNwidth, 280,
			XmNy, 100,
			XmNx, 100,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( panedWindow4, (char *) UxViewS01Context );

	form6 = XtVaCreateManagedWidget( "form6",
			xmFormWidgetClass, panedWindow4,
			XmNpaneMinimum, 200,
			XmNheight, 160,
			XmNwidth, 490,
			XmNy, 460,
			XmNx, 0,
			XmNresizePolicy, XmRESIZE_ANY,
			NULL );

	UxPutContext( form6, (char *) UxViewS01Context );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, form6,
			XmNbottomWidget, NULL,
			XmNleftOffset, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopWidget, NULL,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_NONE,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 90,
			XmNy, 520,
			XmNx, 20,
			NULL );

	UxPutContext( pushButton3, (char *) UxViewS01Context );

	scrolledWindow4 = XtVaCreateManagedWidget( "scrolledWindow4",
			xmScrolledWindowWidgetClass, form6,
			XmNbottomWidget, pushButton3,
			XmNbottomOffset, 20,
			XmNtopOffset, 60,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmAS_NEEDED,
			XmNvisualPolicy, XmCONSTANT,
			XmNy, 60,
			XmNx, 0,
			XmNscrollingPolicy, XmAUTOMATIC,
			NULL );

	UxPutContext( scrolledWindow4, (char *) UxViewS01Context );

	scrolledText2 = XtVaCreateManagedWidget( "scrolledText2",
			xmTextWidgetClass, scrolledWindow4,
			XmNeditable, FALSE,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNheight, 450,
			XmNwidth, 480,
			NULL );

	UxPutContext( scrolledText2, (char *) UxViewS01Context );

	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass, form6,
			XmNbottomOffset, 10,
			XmNbottomWidget, scrolledWindow4,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNfontList, UxConvertFontList( "helvetica_bold18" ),
			RES_CONVERT( XmNlabelString, "View S01" ),
			XmNheight, 30,
			XmNwidth, 260,
			XmNy, 20,
			XmNx, 80,
			NULL );

	UxPutContext( label3, (char *) UxViewS01Context );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, form6,
			XmNleftOffset, 30,
			XmNleftWidget, NULL,
			XmNleftAttachment, XmATTACH_NONE,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNtopWidget, NULL,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 90,
			XmNy, 510,
			XmNx, 280,
			NULL );

	UxPutContext( pushButton4, (char *) UxViewS01Context );

	XtAddCallback( ViewS01, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxViewS01Context );

	XtAddCallback( panedWindow4, XmNdestroyCallback,
			destroyCB_panedWindow4,
			(XtPointer) UxViewS01Context );

	XtAddCallback( pushButton3, XmNactivateCallback,
			activateCB_pushButton3,
			(XtPointer) UxViewS01Context );

	XtAddCallback( pushButton4, XmNactivateCallback,
			activateCB_pushButton4,
			(XtPointer) UxViewS01Context );



	return ( ViewS01 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_ViewS01( _Uxfilename )
	unsigned char	*_Uxfilename;
{
	Widget                  rtrn;
	_UxCViewS01             *UxContext;

	UxViewS01Context = UxContext =
		(_UxCViewS01 *) XtMalloc( sizeof(_UxCViewS01) );

	filename = _Uxfilename;
	{
		extern int view_file();
		rtrn = _Uxbuild_ViewS01();

		stringa = NULL;
		   
		view_file(filename,&stringa);
		
		XmTextSetString (scrolledText2,stringa);  
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_ViewS01( _Uxfilename )
	unsigned char	*_Uxfilename;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_ViewS01( _Uxfilename );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

