
/*******************************************************************************
       ColorMapViewer.c
       (Generated from interface file ColorMapViewer.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo ColorMapViewer.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)ColorMapViewer.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <Xm/Label.h>
#include "res_edit.h"

extern Display *UxDisplay;


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxColorMapViewer;
	Widget	UxmainWindow6;
	Widget	Uxform7;
	Widget	Uxframe1;
	Widget	UxrowColumn1;
	Widget	UxpushButton12;
	Widget	UxPadre;
} _UxCColorMapViewer;

static _UxCColorMapViewer      *UxColorMapViewerContext;
#define ColorMapViewer          UxColorMapViewerContext->UxColorMapViewer
#define mainWindow6             UxColorMapViewerContext->UxmainWindow6
#define form7                   UxColorMapViewerContext->Uxform7
#define frame1                  UxColorMapViewerContext->Uxframe1
#define rowColumn1              UxColorMapViewerContext->UxrowColumn1
#define pushButton12            UxColorMapViewerContext->UxpushButton12
#define Padre                   UxColorMapViewerContext->UxPadre



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_ColorMapViewer();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton12( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorMapViewer      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorMapViewerContext;
	UxColorMapViewerContext = UxContext =
			(_UxCColorMapViewer *) UxGetContext( UxWidget );
	{
	XtDestroyWidget (ColorMapViewer);
	}
	UxColorMapViewerContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ColorMapViewer()
{
	Widget		_UxParent;


	/* Creation of ColorMapViewer */
	_UxParent = Padre;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	ColorMapViewer = XtVaCreatePopupShell( "ColorMapViewer",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 580,
			XmNy, 110,
			XmNwidth, 210,
			XmNheight, 250,
			XmNiconName, "Color Map Viewer",
			XmNtitle, "System Color Map",
			XmNallowShellResize, TRUE,
			NULL );
	UxPutContext( ColorMapViewer, (char *) UxColorMapViewerContext );


	/* Creation of mainWindow6 */
	mainWindow6 = XtVaCreateManagedWidget( "mainWindow6",
			xmMainWindowWidgetClass,
			ColorMapViewer,
			XmNunitType, XmPIXELS,
			XmNx, 40,
			XmNy, 10,
			XmNwidth, 210,
			XmNheight, 250,
			NULL );
	UxPutContext( mainWindow6, (char *) UxColorMapViewerContext );


	/* Creation of form7 */
	form7 = XtVaCreateManagedWidget( "form7",
			xmFormWidgetClass,
			mainWindow6,
			XmNnoResize, FALSE,
			XmNwidth, 210,
			XmNheight, 250,
			NULL );
	UxPutContext( form7, (char *) UxColorMapViewerContext );


	/* Creation of frame1 */
	frame1 = XtVaCreateManagedWidget( "frame1",
			xmFrameWidgetClass,
			form7,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 190,
			XmNheight, 190,
			XmNborderWidth, 0,
			XmNshadowType, XmSHADOW_ETCHED_OUT,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 50,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			NULL );
	UxPutContext( frame1, (char *) UxColorMapViewerContext );


	/* Creation of rowColumn1 */
	rowColumn1 = XtVaCreateManagedWidget( "rowColumn1",
			xmRowColumnWidgetClass,
			frame1,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 190,
			XmNheight, 190,
			RES_CONVERT( XmNbackground, "#50a0a0" ),
			RES_CONVERT( XmNentryClass, "" ),
			XmNnumColumns, 8,
			XmNpacking, XmPACK_COLUMN,
			XmNorientation, XmVERTICAL,
			XmNisAligned, FALSE,
			XmNresizeHeight, TRUE,
			XmNresizeWidth, TRUE,
			NULL );
	UxPutContext( rowColumn1, (char *) UxColorMapViewerContext );


	/* Creation of pushButton12 */
	pushButton12 = XtVaCreateManagedWidget( "pushButton12",
			xmPushButtonWidgetClass,
			form7,
			XmNx, 260,
			XmNy, 230,
			XmNwidth, 110,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 40,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 60,
			NULL );
	XtAddCallback( pushButton12, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton12,
		(XtPointer) UxColorMapViewerContext );

	UxPutContext( pushButton12, (char *) UxColorMapViewerContext );


	XtAddCallback( ColorMapViewer, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxColorMapViewerContext);

	XmMainWindowSetAreas( mainWindow6, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form7 );

	return ( ColorMapViewer );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_ColorMapViewer( _UxPadre )
	Widget	_UxPadre;
{
	Widget                  rtrn;
	_UxCColorMapViewer      *UxContext;

	UxColorMapViewerContext = UxContext =
		(_UxCColorMapViewer *) UxNewContext( sizeof(_UxCColorMapViewer), False );

	Padre = _UxPadre;

	{
		XVisualInfo visual_info;
		Widget Wid;
		int default_depth,i;
		XmString Str;
		int NumeroMAX,j;
		Visual *default_visual;
		
		static char *visual_class[] = {
			"StaticGray",
			"GrayScale",
			"StaticColor",
			"PseudoColor",
			"TrueColor",
			"DirectColor"  };
		
		i = 5;
		rtrn = _Uxbuild_ColorMapViewer();

		default_depth = DefaultDepth (UxDisplay, DefaultScreen (UxDisplay) );
		
		while (!XMatchVisualInfo (UxDisplay,DefaultScreen (UxDisplay),default_depth,
				i--, &visual_info) )
			;
		Str = XmStringCreateSimple (" ");
		
		NumeroMAX = visual_info.red_mask+visual_info.green_mask+visual_info.blue_mask;
		for (j=0;j<64;j++)
			{
			Wid = XtVaCreateManagedWidget ("label",
				xmLabelWidgetClass, rowColumn1,
				XmNwidth, 20,
				XmNheight, 20,
				XmNsensitive, True,
				XmNbackground, j,
				XmNrecomputeSize, False,
				XmNlabelString, Str,
				NULL);
			}
		
		/* Setta la posizione dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (ColorMapViewer,Padre);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

