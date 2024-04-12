
/*******************************************************************************
	Description.c
	(Generated from interface file Description.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo Description.i
   tipo 
   release 1.10
   data 3/28/95
   reserved @(#)Description.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif


extern int Salvato;
extern int Modifica;
extern int indice;
extern char *stringa[];
extern char *descriz;
extern char nomevariabile[];
extern char **simboli;
extern int numero_var;
extern FILE *fpDAT,*fpAPPO;
extern int numero_campioni;

int i,j;
float tempo,valore;

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
	Widget	UxpushButton11;
	Widget	UxpushButton12;
} _UxCDescription;

#define pushButton11            UxDescriptionContext->UxpushButton11
#define pushButton12            UxDescriptionContext->UxpushButton12

static _UxCDescription	*UxDescriptionContext;

Widget	Description;
Widget	labelDescription;
Widget	textDescription;
Widget	labelNomevar;
Widget	textNomevar;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_Description();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton11( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCDescription         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDescriptionContext;
	UxDescriptionContext = UxContext =
			(_UxCDescription *) UxGetContext( UxWidget );
	{
	char *NuovoNome,*NuovaDescr;
	
	NuovoNome = XmTextFieldGetString (textNomevar);
	NuovaDescr = XmTextFieldGetString (textDescription);
	EseguiCambioVar (NuovoNome,NuovaDescr,indice);
	}
	UxDescriptionContext = UxSaveCtx;
}

static void	activateCB_pushButton12( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCDescription         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDescriptionContext;
	UxDescriptionContext = UxContext =
			(_UxCDescription *) UxGetContext( UxWidget );
	{
	UxPopdownInterface (Description);
	}
	UxDescriptionContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Description()
{
	Widget	Description_shell;

	Description_shell = XtVaCreatePopupShell( "Description_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 260,
			XmNy, 350,
			XmNwidth, 609,
			XmNheight, 151,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Description",
			XmNiconName, "Description",
			NULL );

	Description = XtVaCreateManagedWidget( "Description",
			xmFormWidgetClass, Description_shell,
			XmNheight, 151,
			XmNwidth, 609,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( Description, (char *) UxDescriptionContext );

	labelDescription = XtVaCreateManagedWidget( "labelDescription",
			xmLabelWidgetClass, Description,
			XmNmarginLeft, 7,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_NONE,
			XmNfontList, UxConvertFontList( "fixed" ),
			XmNrecomputeSize, FALSE,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "" ),
			XmNheight, 35,
			XmNwidth, 500,
			XmNy, 10,
			XmNx, 100,
			NULL );

	UxPutContext( labelDescription, (char *) UxDescriptionContext );

	textDescription = XtVaCreateManagedWidget( "textDescription",
			xmTextFieldWidgetClass, Description,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_NONE,
			XmNmaxLength, 72,
			XmNfontList, UxConvertFontList( "fixed" ),
			XmNheight, 40,
			XmNwidth, 500,
			XmNy, 50,
			XmNx, 100,
			NULL );

	UxPutContext( textDescription, (char *) UxDescriptionContext );

	pushButton11 = XtVaCreateManagedWidget( "pushButton11",
			xmPushButtonWidgetClass, Description,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 40,
			XmNwidth, 80,
			XmNy, 100,
			XmNx, 15,
			NULL );

	UxPutContext( pushButton11, (char *) UxDescriptionContext );

	pushButton12 = XtVaCreateManagedWidget( "pushButton12",
			xmPushButtonWidgetClass, Description,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNheight, 40,
			XmNwidth, 80,
			XmNy, 100,
			XmNx, 100,
			NULL );

	UxPutContext( pushButton12, (char *) UxDescriptionContext );

	labelNomevar = XtVaCreateManagedWidget( "labelNomevar",
			xmLabelWidgetClass, Description,
			XmNmarginLeft, 7,
			XmNrightWidget, labelDescription,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNtopOffset, 10,
			XmNfontList, UxConvertFontList( "fixed" ),
			XmNrecomputeSize, FALSE,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "" ),
			XmNheight, 35,
			XmNwidth, 80,
			XmNy, 10,
			XmNx, 10,
			NULL );

	UxPutContext( labelNomevar, (char *) UxDescriptionContext );

	textNomevar = XtVaCreateManagedWidget( "textNomevar",
			xmTextFieldWidgetClass, Description,
			XmNfontList, UxConvertFontList( "fixed" ),
			XmNrightWidget, textDescription,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNmaxLength, 8,
			XmNheight, 40,
			XmNwidth, 80,
			XmNy, 50,
			XmNx, 10,
			NULL );

	UxPutContext( textNomevar, (char *) UxDescriptionContext );

	XtAddCallback( Description, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxDescriptionContext );

	XtAddCallback( pushButton11, XmNactivateCallback,
			activateCB_pushButton11,
			(XtPointer) UxDescriptionContext );

	XtAddCallback( pushButton12, XmNactivateCallback,
			activateCB_pushButton12,
			(XtPointer) UxDescriptionContext );



	return ( Description );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_Description()
{
	Widget                  rtrn;
	_UxCDescription         *UxContext;

	UxDescriptionContext = UxContext =
		(_UxCDescription *) XtMalloc( sizeof(_UxCDescription) );

	rtrn = _Uxbuild_Description();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_Description()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_Description();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

