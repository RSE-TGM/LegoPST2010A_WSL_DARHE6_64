
/*******************************************************************************
	NormParamDialog.c
	(Generated from interface file NormParamDialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/LabelG.h>
#include <Xm/BulletinB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo NormParamDialog.i
   tipo 
   release 2.15
   data 4/26/95
   reserved @(#)NormParamDialog.i	2.15
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

extern char dati_norm[10][7];

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
	Widget	UxNormParamDialog;
	Widget	UxlabelGadget5;
	Widget	UxlabelGadget6;
	Widget	UxlabelGadget7;
	Widget	UxlabelGadget8;
	Widget	UxlabelGadget9;
	Widget	UxlabelGadget10;
	Widget	UxlabelGadget12;
	Widget	UxlabelGadget13;
	Widget	Uxp0_text;
	Widget	Uxh0_text;
	Widget	Uxt0_text;
	Widget	Uxw0_text;
	Widget	Uxdp0_text;
	Widget	Uxv0_text;
	Widget	Uxr0_text;
	Widget	Uxl0_text;
	Widget	UxpushButton1;
	Widget	UxpushButton2;
} _UxCNormParamDialog;

#define NormParamDialog         UxNormParamDialogContext->UxNormParamDialog
#define labelGadget5            UxNormParamDialogContext->UxlabelGadget5
#define labelGadget6            UxNormParamDialogContext->UxlabelGadget6
#define labelGadget7            UxNormParamDialogContext->UxlabelGadget7
#define labelGadget8            UxNormParamDialogContext->UxlabelGadget8
#define labelGadget9            UxNormParamDialogContext->UxlabelGadget9
#define labelGadget10           UxNormParamDialogContext->UxlabelGadget10
#define labelGadget12           UxNormParamDialogContext->UxlabelGadget12
#define labelGadget13           UxNormParamDialogContext->UxlabelGadget13
#define p0_text                 UxNormParamDialogContext->Uxp0_text
#define h0_text                 UxNormParamDialogContext->Uxh0_text
#define t0_text                 UxNormParamDialogContext->Uxt0_text
#define w0_text                 UxNormParamDialogContext->Uxw0_text
#define dp0_text                UxNormParamDialogContext->Uxdp0_text
#define v0_text                 UxNormParamDialogContext->Uxv0_text
#define r0_text                 UxNormParamDialogContext->Uxr0_text
#define l0_text                 UxNormParamDialogContext->Uxl0_text
#define pushButton1             UxNormParamDialogContext->UxpushButton1
#define pushButton2             UxNormParamDialogContext->UxpushButton2

static _UxCNormParamDialog	*UxNormParamDialogContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	popup_NormParamDialog();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*
  load_dati_norm():
	carica nei campi testo i valori attuali dei parametri
        di normalizzazione
*/
load_dati_norm()
{
UxPutText(p0_text,dati_norm[0]);
UxPutText(h0_text,dati_norm[1]);
UxPutText(w0_text,dati_norm[2]);
UxPutText(t0_text,dati_norm[3]);
UxPutText(r0_text,dati_norm[4]);
UxPutText(l0_text,dati_norm[5]);
UxPutText(v0_text,dati_norm[6]);
UxPutText(dp0_text,dati_norm[7]);
}

save_dati_norm()
{
char *str;
str=UxGetText(p0_text);
strcpy(dati_norm[0],str);
str=UxGetText(h0_text);
strcpy(dati_norm[1],str);
str=UxGetText(w0_text);
strcpy(dati_norm[2],str);
str=UxGetText(t0_text);
strcpy(dati_norm[3],str);
str=UxGetText(r0_text);
strcpy(dati_norm[4],str);
str=UxGetText(l0_text);
strcpy(dati_norm[5],str);
str=UxGetText(v0_text);
strcpy(dati_norm[6],str);
str=UxGetText(dp0_text);
strcpy(dati_norm[7],str);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCNormParamDialog     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxNormParamDialogContext;
	UxNormParamDialogContext = UxContext =
			(_UxCNormParamDialog *) UxGetContext( UxWidget );
	{
	save_dati_norm();
	}
	UxNormParamDialogContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_NormParamDialog()
{
	Widget	NormParamDialog_shell;

	NormParamDialog_shell = XtVaCreatePopupShell( "NormParamDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 365,
			XmNy, 248,
			XmNwidth, 254,
			XmNheight, 311,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "NormParamDialog",
			NULL );

	NormParamDialog = XtVaCreateWidget( "NormParamDialog",
			xmBulletinBoardWidgetClass, NormParamDialog_shell,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNdialogTitle, "Normalization parameters" ),
			XmNheight, 311,
			XmNwidth, 254,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( NormParamDialog, (char *) UxNormParamDialogContext );

	labelGadget5 = XtVaCreateManagedWidget( "labelGadget5",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Pressure (P0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 20,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget5, (char *) UxNormParamDialogContext );

	labelGadget6 = XtVaCreateManagedWidget( "labelGadget6",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Entalphy (H0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 50,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget6, (char *) UxNormParamDialogContext );

	labelGadget7 = XtVaCreateManagedWidget( "labelGadget7",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Flow (W0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 80,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget7, (char *) UxNormParamDialogContext );

	labelGadget8 = XtVaCreateManagedWidget( "labelGadget8",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Length (L0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 170,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget8, (char *) UxNormParamDialogContext );

	labelGadget9 = XtVaCreateManagedWidget( "labelGadget9",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Temperature (T0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 110,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget9, (char *) UxNormParamDialogContext );

	labelGadget10 = XtVaCreateManagedWidget( "labelGadget10",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Density (R0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 140,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget10, (char *) UxNormParamDialogContext );

	labelGadget12 = XtVaCreateManagedWidget( "labelGadget12",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Volume (V0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 200,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget12, (char *) UxNormParamDialogContext );

	labelGadget13 = XtVaCreateManagedWidget( "labelGadget13",
			xmLabelGadgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Pressure diff.(DP0):" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 140,
			XmNy, 233,
			XmNx, 10,
			NULL );

	UxPutContext( labelGadget13, (char *) UxNormParamDialogContext );

	p0_text = XtVaCreateManagedWidget( "p0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNresizeHeight, TRUE,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 17,
			XmNx, 160,
			NULL );

	UxPutContext( p0_text, (char *) UxNormParamDialogContext );

	h0_text = XtVaCreateManagedWidget( "h0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 50,
			XmNx, 160,
			NULL );

	UxPutContext( h0_text, (char *) UxNormParamDialogContext );

	t0_text = XtVaCreateManagedWidget( "t0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 107,
			XmNx, 160,
			NULL );

	UxPutContext( t0_text, (char *) UxNormParamDialogContext );

	w0_text = XtVaCreateManagedWidget( "w0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 77,
			XmNx, 160,
			NULL );

	UxPutContext( w0_text, (char *) UxNormParamDialogContext );

	dp0_text = XtVaCreateManagedWidget( "dp0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 230,
			XmNx, 160,
			NULL );

	UxPutContext( dp0_text, (char *) UxNormParamDialogContext );

	v0_text = XtVaCreateManagedWidget( "v0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 197,
			XmNx, 160,
			NULL );

	UxPutContext( v0_text, (char *) UxNormParamDialogContext );

	r0_text = XtVaCreateManagedWidget( "r0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 137,
			XmNx, 160,
			NULL );

	UxPutContext( r0_text, (char *) UxNormParamDialogContext );

	l0_text = XtVaCreateManagedWidget( "l0_text",
			xmTextWidgetClass, NormParamDialog,
			XmNresizeWidth, TRUE,
			XmNmaxLength, 6,
			XmNresizeHeight, TRUE,
			XmNmarginWidth, 2,
			XmNmarginHeight, 1,
			XmNheight, 27,
			XmNwidth, 70,
			XmNy, 170,
			XmNx, 160,
			NULL );

	UxPutContext( l0_text, (char *) UxNormParamDialogContext );

	pushButton1 = XtVaCreateManagedWidget( "pushButton1",
			xmPushButtonWidgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 30,
			XmNwidth, 70,
			XmNy, 270,
			XmNx, 30,
			NULL );

	UxPutContext( pushButton1, (char *) UxNormParamDialogContext );

	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass, NormParamDialog,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 70,
			XmNy, 270,
			XmNx, 140,
			NULL );

	UxPutContext( pushButton2, (char *) UxNormParamDialogContext );

	XtAddCallback( NormParamDialog, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxNormParamDialogContext );

	XtAddCallback( pushButton1, XmNactivateCallback,
			activateCB_pushButton1,
			(XtPointer) UxNormParamDialogContext );



	return ( NormParamDialog );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_popup_NormParamDialog()
{
	Widget                  rtrn;
	_UxCNormParamDialog     *UxContext;

	UxNormParamDialogContext = UxContext =
		(_UxCNormParamDialog *) XtMalloc( sizeof(_UxCNormParamDialog) );

	rtrn = _Uxbuild_NormParamDialog();

	load_dati_norm(); /* inserisce i dati di normalizzazione 
	                     nei campi testo */
	UxPopupInterface(rtrn, no_grab);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	popup_NormParamDialog()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_popup_NormParamDialog();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

