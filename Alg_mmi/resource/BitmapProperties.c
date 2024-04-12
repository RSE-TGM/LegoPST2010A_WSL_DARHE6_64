
/*******************************************************************************
       BitmapProperties.c
       (Generated from interface file BitmapProperties.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo BitmapProperties.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)BitmapProperties.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "res_edit.h"


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
	Widget	UxBitmapProperties;
	Widget	Uxform8;
	Widget	UxtextWidthBit;
	Widget	Uxlabel13;
	Widget	UxtextHeightBit;
	Widget	Uxseparator9;
	Widget	Uxlabel11;
	Widget	UxpushButton13;
	Widget	UxpushButton14;
	unsigned char	*UxFileBitmap;
	Widget	UxPadreChiamante;
	unsigned char	*UxNomefINP;
	Widget	UxChiam;
} _UxCBitmapProperties;

static _UxCBitmapProperties    *UxBitmapPropertiesContext;
#define BitmapProperties        UxBitmapPropertiesContext->UxBitmapProperties
#define form8                   UxBitmapPropertiesContext->Uxform8
#define textWidthBit            UxBitmapPropertiesContext->UxtextWidthBit
#define label13                 UxBitmapPropertiesContext->Uxlabel13
#define textHeightBit           UxBitmapPropertiesContext->UxtextHeightBit
#define separator9              UxBitmapPropertiesContext->Uxseparator9
#define label11                 UxBitmapPropertiesContext->Uxlabel11
#define pushButton13            UxBitmapPropertiesContext->UxpushButton13
#define pushButton14            UxBitmapPropertiesContext->UxpushButton14
#define FileBitmap              UxBitmapPropertiesContext->UxFileBitmap
#define PadreChiamante          UxBitmapPropertiesContext->UxPadreChiamante
#define NomefINP                UxBitmapPropertiesContext->UxNomefINP
#define Chiam                   UxBitmapPropertiesContext->UxChiam



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_BitmapProperties();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton13( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCBitmapProperties    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBitmapPropertiesContext;
	UxBitmapPropertiesContext = UxContext =
			(_UxCBitmapProperties *) UxGetContext( UxWidget );
	{
	Boolean WidthBool,HeightBool;
	char stringa[100];
	char *Largh,*Altez;
	
	Largh = (char *)XmTextFieldGetString (textWidthBit);
	WidthBool = NumIntVerifica (Largh);
	
	Altez = (char *)XmTextFieldGetString (textHeightBit);
	HeightBool = NumIntVerifica (Altez);
	
	if (!WidthBool || !HeightBool)
		{
		strcpy (stringa,"Error in dimension input!");
		VisualizzaMessageBox (GENERICA,BitmapProperties,stringa,PadreChiamante);
		}
	else
		{
		EseguiNuovoBitmap (FileBitmap,Largh,Altez,Chiam);
		XtFree (Largh);
		XtFree (Altez);
		XtDestroyWidget (BitmapProperties);
		}
	XtFree (Largh);
	XtFree (Altez);
	}
	UxBitmapPropertiesContext = UxSaveCtx;
}

static	void	activateCB_pushButton14( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCBitmapProperties    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBitmapPropertiesContext;
	UxBitmapPropertiesContext = UxContext =
			(_UxCBitmapProperties *) UxGetContext( UxWidget );
	{
	XtDestroyWidget (BitmapProperties);
	}
	UxBitmapPropertiesContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_BitmapProperties()
{
	Widget		_UxParent;


	/* Creation of BitmapProperties */
	_UxParent = Chiam;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	BitmapProperties = XtVaCreatePopupShell( "BitmapProperties",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 230,
			XmNy, 160,
			XmNwidth, 240,
			XmNheight, 160,
			XmNiconName, "BITMAP Properties",
			XmNtitle, "NEW BITMAP Properties",
			NULL );
	UxPutContext( BitmapProperties, (char *) UxBitmapPropertiesContext );


	/* Creation of form8 */
	form8 = XtVaCreateManagedWidget( "form8",
			xmFormWidgetClass,
			BitmapProperties,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 70,
			XmNy, 40,
			XmNwidth, 240,
			XmNheight, 160,
			NULL );
	UxPutContext( form8, (char *) UxBitmapPropertiesContext );


	/* Creation of textWidthBit */
	textWidthBit = XtVaCreateManagedWidget( "textWidthBit",
			xmTextFieldWidgetClass,
			form8,
			XmNx, 110,
			XmNy, 10,
			XmNwidth, 120,
			XmNheight, 30,
			NULL );
	UxPutContext( textWidthBit, (char *) UxBitmapPropertiesContext );


	/* Creation of label13 */
	label13 = XtVaCreateManagedWidget( "label13",
			xmLabelWidgetClass,
			form8,
			XmNx, 10,
			XmNy, 60,
			XmNwidth, 90,
			XmNheight, 30,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "HEIGHT:" ),
			NULL );
	UxPutContext( label13, (char *) UxBitmapPropertiesContext );


	/* Creation of textHeightBit */
	textHeightBit = XtVaCreateManagedWidget( "textHeightBit",
			xmTextFieldWidgetClass,
			form8,
			XmNx, 110,
			XmNy, 60,
			XmNwidth, 120,
			XmNheight, 30,
			NULL );
	UxPutContext( textHeightBit, (char *) UxBitmapPropertiesContext );


	/* Creation of separator9 */
	separator9 = XtVaCreateManagedWidget( "separator9",
			xmSeparatorWidgetClass,
			form8,
			XmNx, 10,
			XmNy, 100,
			XmNwidth, 220,
			XmNheight, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( separator9, (char *) UxBitmapPropertiesContext );


	/* Creation of label11 */
	label11 = XtVaCreateManagedWidget( "label11",
			xmLabelWidgetClass,
			form8,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 90,
			XmNheight, 30,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "WIDTH:" ),
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 15,
			XmNbottomWidget, label13,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightWidget, textWidthBit,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			NULL );
	UxPutContext( label11, (char *) UxBitmapPropertiesContext );


	/* Creation of pushButton13 */
	pushButton13 = XtVaCreateManagedWidget( "pushButton13",
			xmPushButtonWidgetClass,
			form8,
			XmNx, 10,
			XmNy, 120,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "OK" ),
			NULL );
	XtAddCallback( pushButton13, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton13,
		(XtPointer) UxBitmapPropertiesContext );

	UxPutContext( pushButton13, (char *) UxBitmapPropertiesContext );


	/* Creation of pushButton14 */
	pushButton14 = XtVaCreateManagedWidget( "pushButton14",
			xmPushButtonWidgetClass,
			form8,
			XmNx, 100,
			XmNy, 120,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			NULL );
	XtAddCallback( pushButton14, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton14,
		(XtPointer) UxBitmapPropertiesContext );

	UxPutContext( pushButton14, (char *) UxBitmapPropertiesContext );


	XtAddCallback( BitmapProperties, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxBitmapPropertiesContext);


	return ( BitmapProperties );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_BitmapProperties( _UxNomefINP, _UxChiam )
	unsigned char	*_UxNomefINP;
	Widget	_UxChiam;
{
	Widget                  rtrn;
	_UxCBitmapProperties    *UxContext;

	UxBitmapPropertiesContext = UxContext =
		(_UxCBitmapProperties *) UxNewContext( sizeof(_UxCBitmapProperties), False );

	NomefINP = _UxNomefINP;
	Chiam = _UxChiam;

	{
		FileBitmap = (unsigned char *)XtNewString ((char *)NomefINP);
		PadreChiamante = Chiam;
		rtrn = _Uxbuild_BitmapProperties();

		/*  Setta la posizione dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (BitmapProperties,Chiam);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

