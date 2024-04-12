
/*******************************************************************************
       ColorEditor.c
       (Generated from interface file ColorEditor.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/PushB.h>
#include <Xm/Scale.h>
#include <Xm/DrawnB.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
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
   modulo ColorEditor.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)ColorEditor.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "res_edit.h"

extern Display *UxDisplay;

Colormap cmap;


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
	Widget	UxColorEditor;
	Widget	UxmainWindow3;
	Widget	Uxform4;
	Widget	Uxlabel4;
	Widget	Uxseparator4;
	Widget	Uxlabel5;
	Widget	Uxlabel6;
	Widget	Uxlabel7;
	Widget	Uxseparator5;
	Widget	Uxlabel8;
	Widget	UxScalaRed;
	Widget	UxScalaGreen;
	Widget	UxScalaBlue;
	Widget	Uxseparator6;
	Widget	UxpushButton7;
	Widget	UxpushButton8;
	Widget	UxpushButton6;
	Widget	UxpushButton5;
	Widget	UxtextField1;
	Pixel	UxOriginalPixel;
	Pixel	UxWorkingPixel;
	XColor	Uxnewcolor;
	int	Uxscreen;
	int	Uxva1;
	int	Uxva2;
	int	Uxva3;
	Widget	UxTesto;
	Pixel	*UxColoreInput;
	Widget	UxTestoInp;
	Widget	UxChiamCEd;
} _UxCColorEditor;

static _UxCColorEditor         *UxColorEditorContext;
#define ColorEditor             UxColorEditorContext->UxColorEditor
#define mainWindow3             UxColorEditorContext->UxmainWindow3
#define form4                   UxColorEditorContext->Uxform4
#define label4                  UxColorEditorContext->Uxlabel4
#define separator4              UxColorEditorContext->Uxseparator4
#define label5                  UxColorEditorContext->Uxlabel5
#define label6                  UxColorEditorContext->Uxlabel6
#define label7                  UxColorEditorContext->Uxlabel7
#define separator5              UxColorEditorContext->Uxseparator5
#define label8                  UxColorEditorContext->Uxlabel8
#define ScalaRed                UxColorEditorContext->UxScalaRed
#define ScalaGreen              UxColorEditorContext->UxScalaGreen
#define ScalaBlue               UxColorEditorContext->UxScalaBlue
#define separator6              UxColorEditorContext->Uxseparator6
#define pushButton7             UxColorEditorContext->UxpushButton7
#define pushButton8             UxColorEditorContext->UxpushButton8
#define pushButton6             UxColorEditorContext->UxpushButton6
#define pushButton5             UxColorEditorContext->UxpushButton5
#define textField1              UxColorEditorContext->UxtextField1
#define OriginalPixel           UxColorEditorContext->UxOriginalPixel
#define WorkingPixel            UxColorEditorContext->UxWorkingPixel
#define newcolor                UxColorEditorContext->Uxnewcolor
#define screen                  UxColorEditorContext->Uxscreen
#define va1                     UxColorEditorContext->Uxva1
#define va2                     UxColorEditorContext->Uxva2
#define va3                     UxColorEditorContext->Uxva3
#define Testo                   UxColorEditorContext->UxTesto
#define ColoreInput             UxColorEditorContext->UxColoreInput
#define TestoInp                UxColorEditorContext->UxTestoInp
#define ChiamCEd                UxColorEditorContext->UxChiamCEd


Widget	ButtNomeColoreOrig;
Widget	ButtNomeColoreWork;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_ColorEditor();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	valueChangedCB_ScalaRed( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaRed, &va1);
	
	newcolor.red = (unsigned short)va1*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor (UxDisplay,cmap,&newcolor);
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1 , vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	dragCB_ScalaRed( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaRed, &va1);
	
	newcolor.red = (unsigned short)va1*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor (UxDisplay,cmap,&newcolor);
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1 , vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	valueChangedCB_ScalaGreen( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaGreen, &va2);
	
	newcolor.green = (unsigned short)va2*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor ( UxDisplay , cmap , &newcolor );
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1 , vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	dragCB_ScalaGreen( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaGreen, &va2);
	
	newcolor.green = (unsigned short)va2*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor ( UxDisplay , cmap , &newcolor );
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1 , vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	valueChangedCB_ScalaBlue( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaBlue, &va3);
	
	newcolor.blue = (unsigned short)va3*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor ( UxDisplay , cmap , &newcolor );
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1, vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	dragCB_ScalaBlue( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	char vstring[20];
	
	XmScaleGetValue (ScalaBlue, &va3);
	
	newcolor.blue = (unsigned short)va3*256;
	XStoreColor (UxDisplay,cmap,&newcolor);
	
	XQueryColor ( UxDisplay , cmap , &newcolor );
	sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);
	XmTextFieldSetString (textField1, vstring);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	activateCB_pushButton7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	XtDestroyWidget (ColorEditor);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	activateCB_pushButton8( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	XColor reset;
	
	reset.pixel = OriginalPixel;
	XQueryColor ( UxDisplay , cmap , &reset );
	reset.pixel = WorkingPixel;
	XStoreColor ( UxDisplay , cmap , &reset );
	set_something (ButtNomeColoreWork, XmNbackground, reset.pixel);
	va1 = (int )( reset.red   / 256 );
	va2 = (int )( reset.green / 256 );
	va3 = (int )( reset.blue  / 256 );
	XmScaleSetValue (ScalaRed, va1);
	XmScaleSetValue (ScalaGreen, va2);
	XmScaleSetValue (ScalaBlue, va3);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	activateCB_pushButton6( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	XColor nuovo;
	Pixel col;
	
	nuovo.pixel = WorkingPixel;
	XQueryColor ( UxDisplay , cmap , &nuovo );
	nuovo.pixel = OriginalPixel;
	XStoreColor(UxDisplay, cmap, &nuovo);
	set_something (ButtNomeColoreOrig, XmNbackground, nuovo.pixel);
	}
	UxColorEditorContext = UxSaveCtx;
}

static	void	activateCB_pushButton5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorEditorContext;
	UxColorEditorContext = UxContext =
			(_UxCColorEditor *) UxGetContext( UxWidget );
	{
	XColor ColoreOutput;
	char *StrOut;
	
	ColoreOutput.pixel = WorkingPixel;
	XQueryColor ( UxDisplay , cmap , &ColoreOutput );
	StrOut = (char *)XtCalloc (15,sizeof(char));
	sprintf (StrOut,"#%04x%04x%04x",ColoreOutput.red,ColoreOutput.green,ColoreOutput.blue);
	XmTextFieldSetString (Testo, StrOut);
	XtFree (StrOut);
	XtDestroyWidget (ColorEditor);
	}
	UxColorEditorContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ColorEditor()
{
	Widget		_UxParent;


	/* Creation of ColorEditor */
	_UxParent = ChiamCEd;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	ColorEditor = XtVaCreatePopupShell( "ColorEditor",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 804,
			XmNy, 94,
			XmNwidth, 390,
			XmNheight, 536,
			XmNiconName, "Color Edit",
			XmNtitle, "Resource Color Editor",
			NULL );
	UxPutContext( ColorEditor, (char *) UxColorEditorContext );


	/* Creation of mainWindow3 */
	mainWindow3 = XtVaCreateManagedWidget( "mainWindow3",
			xmMainWindowWidgetClass,
			ColorEditor,
			XmNunitType, XmPIXELS,
			XmNx, 50,
			XmNy, 30,
			XmNwidth, 390,
			XmNheight, 536,
			NULL );
	UxPutContext( mainWindow3, (char *) UxColorEditorContext );


	/* Creation of form4 */
	form4 = XtVaCreateManagedWidget( "form4",
			xmFormWidgetClass,
			mainWindow3,
			NULL );
	UxPutContext( form4, (char *) UxColorEditorContext );


	/* Creation of label4 */
	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass,
			form4,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 65,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "Color:" ),
			XmNalignment, XmALIGNMENT_END,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomPosition, 10,
			XmNtopPosition, 2,
			NULL );
	UxPutContext( label4, (char *) UxColorEditorContext );


	/* Creation of separator4 */
	separator4 = XtVaCreateManagedWidget( "separator4",
			xmSeparatorWidgetClass,
			form4,
			XmNx, 10,
			XmNy, 60,
			XmNwidth, 350,
			XmNheight, 20,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 14,
			XmNtopPosition, 12,
			NULL );
	UxPutContext( separator4, (char *) UxColorEditorContext );


	/* Creation of label5 */
	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass,
			form4,
			XmNx, 45,
			XmNy, 65,
			XmNwidth, 290,
			XmNheight, 35,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			RES_CONVERT( XmNlabelString, "Color Samples" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 22,
			XmNrightPosition, 90,
			XmNtopPosition, 15,
			XmNleftPosition, 10,
			NULL );
	UxPutContext( label5, (char *) UxColorEditorContext );


	/* Creation of label6 */
	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass,
			form4,
			XmNx, 15,
			XmNy, 115,
			XmNwidth, 150,
			XmNheight, 30,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			RES_CONVERT( XmNlabelString, "Original:" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 31,
			XmNtopPosition, 25,
			XmNleftPosition, 5,
			XmNrightPosition, 45,
			XmNrightAttachment, XmATTACH_POSITION,
			NULL );
	UxPutContext( label6, (char *) UxColorEditorContext );


	/* Creation of label7 */
	label7 = XtVaCreateManagedWidget( "label7",
			xmLabelWidgetClass,
			form4,
			XmNx, 195,
			XmNy, 115,
			XmNwidth, 150,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Working:" ),
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 31,
			XmNtopPosition, 25,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 55,
			XmNrightPosition, 95,
			NULL );
	UxPutContext( label7, (char *) UxColorEditorContext );


	/* Creation of ButtNomeColoreOrig */
	ButtNomeColoreOrig = XtVaCreateManagedWidget( "ButtNomeColoreOrig",
			xmDrawnButtonWidgetClass,
			form4,
			XmNx, 15,
			XmNy, 150,
			XmNwidth, 140,
			XmNheight, 45,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, label6,
			XmNsensitive, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 40,
			XmNtopPosition, 32,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 5,
			XmNrightPosition, 45,
			XmNrightAttachment, XmATTACH_POSITION,
			NULL );
	UxPutContext( ButtNomeColoreOrig, (char *) UxColorEditorContext );


	/* Creation of ButtNomeColoreWork */
	ButtNomeColoreWork = XtVaCreateManagedWidget( "ButtNomeColoreWork",
			xmDrawnButtonWidgetClass,
			form4,
			XmNx, 200,
			XmNy, 150,
			XmNwidth, 140,
			XmNheight, 45,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, label7,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNsensitive, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 40,
			XmNtopPosition, 32,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 55,
			XmNrightPosition, 95,
			NULL );
	UxPutContext( ButtNomeColoreWork, (char *) UxColorEditorContext );


	/* Creation of separator5 */
	separator5 = XtVaCreateManagedWidget( "separator5",
			xmSeparatorWidgetClass,
			form4,
			XmNx, 10,
			XmNy, 205,
			XmNwidth, 350,
			XmNheight, 20,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 43,
			XmNtopPosition, 41,
			NULL );
	UxPutContext( separator5, (char *) UxColorEditorContext );


	/* Creation of label8 */
	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass,
			form4,
			XmNx, 45,
			XmNy, 225,
			XmNwidth, 280,
			XmNheight, 30,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			RES_CONVERT( XmNlabelString, "R G B Components" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 50,
			XmNleftPosition, 3,
			XmNrightPosition, 97,
			XmNtopPosition, 44,
			NULL );
	UxPutContext( label8, (char *) UxColorEditorContext );


	/* Creation of ScalaRed */
	ScalaRed = XtVaCreateManagedWidget( "ScalaRed",
			xmScaleWidgetClass,
			form4,
			XmNx, 20,
			XmNy, 265,
			XmNwidth, 320,
			XmNheight, 65,
			XmNorientation, XmHORIZONTAL,
			XmNmaximum, 255,
			XmNshowValue, TRUE,
			RES_CONVERT( XmNtitleString, "RED" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 3,
			XmNrightPosition, 97,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 63,
			XmNtopPosition, 51,
			NULL );
	XtAddCallback( ScalaRed, XmNvalueChangedCallback,
		(XtCallbackProc) valueChangedCB_ScalaRed,
		(XtPointer) UxColorEditorContext );
	XtAddCallback( ScalaRed, XmNdragCallback,
		(XtCallbackProc) dragCB_ScalaRed,
		(XtPointer) UxColorEditorContext );

	UxPutContext( ScalaRed, (char *) UxColorEditorContext );


	/* Creation of ScalaGreen */
	ScalaGreen = XtVaCreateManagedWidget( "ScalaGreen",
			xmScaleWidgetClass,
			form4,
			XmNx, 15,
			XmNy, 330,
			XmNwidth, 320,
			XmNheight, 65,
			XmNorientation, XmHORIZONTAL,
			XmNmaximum, 255,
			XmNshowValue, TRUE,
			RES_CONVERT( XmNtitleString, "GREEN" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 3,
			XmNrightPosition, 97,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 76,
			XmNtopPosition, 64,
			NULL );
	XtAddCallback( ScalaGreen, XmNvalueChangedCallback,
		(XtCallbackProc) valueChangedCB_ScalaGreen,
		(XtPointer) UxColorEditorContext );
	XtAddCallback( ScalaGreen, XmNdragCallback,
		(XtCallbackProc) dragCB_ScalaGreen,
		(XtPointer) UxColorEditorContext );

	UxPutContext( ScalaGreen, (char *) UxColorEditorContext );


	/* Creation of ScalaBlue */
	ScalaBlue = XtVaCreateManagedWidget( "ScalaBlue",
			xmScaleWidgetClass,
			form4,
			XmNx, 15,
			XmNy, 410,
			XmNwidth, 320,
			XmNheight, 65,
			XmNorientation, XmHORIZONTAL,
			XmNmaximum, 255,
			XmNshowValue, TRUE,
			RES_CONVERT( XmNtitleString, "BLUE" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 3,
			XmNrightPosition, 97,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 89,
			XmNtopPosition, 77,
			NULL );
	XtAddCallback( ScalaBlue, XmNvalueChangedCallback,
		(XtCallbackProc) valueChangedCB_ScalaBlue,
		(XtPointer) UxColorEditorContext );
	XtAddCallback( ScalaBlue, XmNdragCallback,
		(XtCallbackProc) dragCB_ScalaBlue,
		(XtPointer) UxColorEditorContext );

	UxPutContext( ScalaBlue, (char *) UxColorEditorContext );


	/* Creation of separator6 */
	separator6 = XtVaCreateManagedWidget( "separator6",
			xmSeparatorWidgetClass,
			form4,
			XmNx, 5,
			XmNy, 465,
			XmNwidth, 350,
			XmNheight, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 91,
			XmNtopPosition, 90,
			NULL );
	UxPutContext( separator6, (char *) UxColorEditorContext );


	/* Creation of pushButton7 */
	pushButton7 = XtVaCreateManagedWidget( "pushButton7",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 274,
			XmNy, 489,
			XmNwidth, 81,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 92,
			XmNleftPosition, 69,
			XmNrightPosition, 89,
			NULL );
	XtAddCallback( pushButton7, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton7,
		(XtPointer) UxColorEditorContext );

	UxPutContext( pushButton7, (char *) UxColorEditorContext );


	/* Creation of pushButton8 */
	pushButton8 = XtVaCreateManagedWidget( "pushButton8",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 190,
			XmNy, 490,
			XmNwidth, 80,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "RESET" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 92,
			XmNleftPosition, 47,
			XmNrightPosition, 67,
			NULL );
	XtAddCallback( pushButton8, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton8,
		(XtPointer) UxColorEditorContext );

	UxPutContext( pushButton8, (char *) UxColorEditorContext );


	/* Creation of pushButton6 */
	pushButton6 = XtVaCreateManagedWidget( "pushButton6",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 100,
			XmNy, 490,
			XmNwidth, 80,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "APPLY" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 92,
			XmNleftPosition, 25,
			XmNrightPosition, 45,
			NULL );
	XtAddCallback( pushButton6, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton6,
		(XtPointer) UxColorEditorContext );

	UxPutContext( pushButton6, (char *) UxColorEditorContext );


	/* Creation of pushButton5 */
	pushButton5 = XtVaCreateManagedWidget( "pushButton5",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 9,
			XmNy, 489,
			XmNwidth, 81,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 92,
			XmNleftPosition, 3,
			XmNrightPosition, 23,
			NULL );
	XtAddCallback( pushButton5, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton5,
		(XtPointer) UxColorEditorContext );

	UxPutContext( pushButton5, (char *) UxColorEditorContext );


	/* Creation of textField1 */
	textField1 = XtVaCreateManagedWidget( "textField1",
			xmTextFieldWidgetClass,
			form4,
			XmNx, 80,
			XmNy, 10,
			XmNwidth, 295,
			XmNheight, 35,
			XmNmaxLength, 20,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, separator4,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftWidget, label4,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 15,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNsensitive, FALSE,
			XmNbottomPosition, 10,
			XmNtopPosition, 2,
			NULL );
	UxPutContext( textField1, (char *) UxColorEditorContext );


	XtAddCallback( ColorEditor, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxColorEditorContext);

	XmMainWindowSetAreas( mainWindow3, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form4 );

	return ( ColorEditor );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_ColorEditor( _UxColoreInput, _UxTestoInp, _UxChiamCEd )
	Pixel	*_UxColoreInput;
	Widget	_UxTestoInp;
	Widget	_UxChiamCEd;
{
	Widget                  rtrn;
	_UxCColorEditor         *UxContext;

	UxColorEditorContext = UxContext =
		(_UxCColorEditor *) UxNewContext( sizeof(_UxCColorEditor), False );

	ColoreInput = _UxColoreInput;
	TestoInp = _UxTestoInp;
	ChiamCEd = _UxChiamCEd;

	{
		XColor TrovaRGB;
		unsigned long planes[1],pixels[2];
		char mess[50],StrColore[15];
		Status stat;
		
		Testo = TestoInp;
		rtrn = _Uxbuild_ColorEditor();

		/*  Open display  */
		screen = DefaultScreen (UxDisplay);
		cmap = DefaultColormap (UxDisplay,screen);
		
		newcolor.flags = DoRed | DoGreen | DoBlue;
		newcolor.red = 0;
		newcolor.green = 0;
		newcolor.blue = 0;
		
		/*  Alloca read/write cells  */
		stat = XAllocColorCells (UxDisplay,cmap,False,planes,0,pixels,2);
		if (stat != 0)
			{
			WorkingPixel = newcolor.pixel = pixels[0];
			OriginalPixel = pixels[1];
		
			TrovaRGB.pixel = *ColoreInput;
			XQueryColor ( UxDisplay , cmap , &TrovaRGB );
		
			/*  new color-RGB value  */
			newcolor.red   = TrovaRGB.red;
			newcolor.green = TrovaRGB.green;
			newcolor.blue  = TrovaRGB.blue;
		
			/*  Define Initial Color  */
			XStoreColor ( UxDisplay , cmap , &newcolor );
			newcolor.pixel = OriginalPixel;
			XStoreColor ( UxDisplay , cmap , &newcolor );
		
			set_something (ButtNomeColoreWork, XmNbackground, WorkingPixel);
			set_something (ButtNomeColoreOrig, XmNbackground, OriginalPixel);
			sprintf (StrColore,"#%04x%04x%04x",TrovaRGB.red,TrovaRGB.green,TrovaRGB.blue);
			XmTextFieldSetString (textField1, StrColore);
			newcolor.pixel = WorkingPixel;
			va1 = (int )( newcolor.red   / 256 );
			va2 = (int )( newcolor.green / 256 );
			va3 = (int )( newcolor.blue  / 256 );
			XmScaleSetValue (ScalaRed, va1);
			XmScaleSetValue (ScalaGreen, va2);
			XmScaleSetValue (ScalaBlue, va3);
			}
		else
			{
			strcpy (mess,"Unable to alloc color !");
			XmTextFieldSetString (textField1, mess);
			set_something (ScalaRed, XmNsensitive, False);
			set_something (ScalaGreen, XmNsensitive, False);
			set_something (ScalaBlue, XmNsensitive, False);
			set_something (pushButton5, XmNsensitive, False);  /*  OK */
			set_something (pushButton6, XmNsensitive, False);  /*  APPLY */
			set_something (pushButton8, XmNsensitive, False);  /*  RESET */
			}
		
		/*  Setta la posizione dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (ColorEditor,ChiamCEd);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

