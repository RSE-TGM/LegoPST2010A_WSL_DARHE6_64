
/*******************************************************************************
	dbox_user_data.c
	(Generated from interface file dbox_user_data.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/LabelG.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo dbox_user_data.i
   tipo 
   release 2.22
   data 5/9/95
   reserved @(#)dbox_user_data.i	2.22
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/


#include "definizioni.h"

#ifndef LIBUTILX
#include <libutilx.h>
#define LIBUTILX
#endif

/****************************************************************/
/* VARIABILI GLOBALI ESTERNE					*/
/****************************************************************/

extern int lcDestroySwidget(Widget);

extern Boolean non_salvato;

extern Arg args[20];
extern Cardinal argcount;

extern char *str_dichI2, *str_codI2;

extern Widget UxTopLevel;
extern Dialog_geometry geom_attention;
extern Widget attention_wdg;

/****************************************************************/
/* VARIABILI GLOBALI 						*/
/****************************************************************/

Boolean dbox_userdata_managed = False;

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
	Widget	Uxdbox_user_data;
	Widget	Uxdata_pane;
	Widget	Uxform8;
	Widget	UxlabelGadget9;
	Widget	UxscrolledWindow5;
	Widget	Uxform9;
	Widget	UxlabelGadget10;
	Widget	Uxok_data_pb;
	Widget	UxscrolledWindow6;
	Widget	Uxapply_data_pb;
	Widget	Uxcancel_data_pb;
} _UxCdbox_user_data;

#define dbox_user_data          UxDbox_user_dataContext->Uxdbox_user_data
#define data_pane               UxDbox_user_dataContext->Uxdata_pane
#define form8                   UxDbox_user_dataContext->Uxform8
#define labelGadget9            UxDbox_user_dataContext->UxlabelGadget9
#define scrolledWindow5         UxDbox_user_dataContext->UxscrolledWindow5
#define form9                   UxDbox_user_dataContext->Uxform9
#define labelGadget10           UxDbox_user_dataContext->UxlabelGadget10
#define ok_data_pb              UxDbox_user_dataContext->Uxok_data_pb
#define scrolledWindow6         UxDbox_user_dataContext->UxscrolledWindow6
#define apply_data_pb           UxDbox_user_dataContext->Uxapply_data_pb
#define cancel_data_pb          UxDbox_user_dataContext->Uxcancel_data_pb

static _UxCdbox_user_data	*UxDbox_user_dataContext;

Widget	data_decl_scrolledText;
Widget	data_code_scrolledText;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_dbox_userdata();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*** memo_textI2(flag)
 ***   Parametri:
 ***     Boolean flag : indica se la window deve sparire o meno.
 ***
 ***   Descrizione:
 ***     memorizza il contenuto dei text-widget della window dei dati nelle
 ***     variabili globali str_dichI2 e str_codI2 
 ***/
void memo_textI2(flag)
Boolean flag;
{

   non_salvato = True;

/* Dealloca la memoria precedentemente allocata da XmTextGetString() */
   if ( str_dichI2 != NULL )
      XtFree( str_dichI2 );

   if ( str_codI2 != NULL )
      XtFree( str_codI2 );

   str_dichI2 = XmTextGetString(UxGetWidget(data_decl_scrolledText));
   str_codI2 = XmTextGetString(UxGetWidget(data_code_scrolledText));

   if (flag)
   {
      UxDestroySwidget(dbox_user_data);
      dbox_userdata_managed = False;
   }
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_ok_data_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdbox_user_data      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDbox_user_dataContext;
	UxDbox_user_dataContext = UxContext =
			(_UxCdbox_user_data *) UxGetContext( UxWidget );
	{
	memo_textI2(True);
	}
	UxDbox_user_dataContext = UxSaveCtx;
}

static void	activateCB_apply_data_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdbox_user_data      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDbox_user_dataContext;
	UxDbox_user_dataContext = UxContext =
			(_UxCdbox_user_data *) UxGetContext( UxWidget );
	{
	memo_textI2(False);
	}
	UxDbox_user_dataContext = UxSaveCtx;
}

static void	activateCB_cancel_data_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdbox_user_data      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDbox_user_dataContext;
	UxDbox_user_dataContext = UxContext =
			(_UxCdbox_user_data *) UxGetContext( UxWidget );
	{
	UxDestroySwidget (dbox_user_data);
	dbox_userdata_managed = False;
	}
	UxDbox_user_dataContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_dbox_user_data()
{

	dbox_user_data = XtVaCreatePopupShell( "dbox_user_data",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNgeometry, "+190+250",
			XmNtitle, "I2 DATA SECTION - NEWMOD ",
			XmNheight, 500,
			XmNwidth, 700,
			XmNy, 440,
			XmNx, 540,
			NULL );

	UxPutContext( dbox_user_data, (char *) UxDbox_user_dataContext );

	data_pane = XtVaCreateWidget( "data_pane",
			xmPanedWindowWidgetClass, dbox_user_data,
			XmNheight, 450,
			XmNwidth, 694,
			XmNy, 0,
			XmNx, 0,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( data_pane, (char *) UxDbox_user_dataContext );

	form8 = XtVaCreateManagedWidget( "form8",
			xmFormWidgetClass, data_pane,
			XmNheight, 200,
			XmNwidth, 690,
			XmNy, 0,
			XmNx, 3,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( form8, (char *) UxDbox_user_dataContext );

	labelGadget9 = XtVaCreateManagedWidget( "labelGadget9",
			xmLabelGadgetClass, form8,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNlabelString, "Declarations" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 150,
			XmNy, 0,
			XmNx, 20,
			NULL );

	UxPutContext( labelGadget9, (char *) UxDbox_user_dataContext );

	scrolledWindow5 = XtVaCreateManagedWidget( "scrolledWindow5",
			xmScrolledWindowWidgetClass, form8,
			XmNbottomOffset, 10,
			XmNtopWidget, labelGadget9,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 30,
			XmNx, 10,
			XmNunitType, XmPIXELS,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow5, (char *) UxDbox_user_dataContext );

	data_decl_scrolledText = XtVaCreateManagedWidget( "data_decl_scrolledText",
			xmTextWidgetClass, scrolledWindow5,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNresizeWidth, TRUE,
			XmNresizeHeight, TRUE,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNcolumns, 80,
			XmNy, 0,
			XmNx, 0,
			XmNheight, 160,
			XmNwidth, 680,
			NULL );

	UxPutContext( data_decl_scrolledText, (char *) UxDbox_user_dataContext );

	form9 = XtVaCreateManagedWidget( "form9",
			xmFormWidgetClass, data_pane,
			XmNheight, 300,
			XmNwidth, 690,
			XmNy, 210,
			XmNx, 10,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( form9, (char *) UxDbox_user_dataContext );

	labelGadget10 = XtVaCreateManagedWidget( "labelGadget10",
			xmLabelGadgetClass, form9,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "User code" ),
			XmNbottomAttachment, XmATTACH_NONE,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 160,
			XmNy, 10,
			XmNx, 20,
			NULL );

	UxPutContext( labelGadget10, (char *) UxDbox_user_dataContext );

	ok_data_pb = XtVaCreateManagedWidget( "ok_data_pb",
			xmPushButtonWidgetClass, form9,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 0,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 30,
			XmNwidth, 100,
			XmNy, 300,
			XmNx, 20,
			NULL );

	UxPutContext( ok_data_pb, (char *) UxDbox_user_dataContext );

	scrolledWindow6 = XtVaCreateManagedWidget( "scrolledWindow6",
			xmScrolledWindowWidgetClass, form9,
			XmNtopWidget, labelGadget10,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, ok_data_pb,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 40,
			XmNx, 10,
			XmNunitType, XmPIXELS,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow6, (char *) UxDbox_user_dataContext );

	data_code_scrolledText = XtVaCreateManagedWidget( "data_code_scrolledText",
			xmTextWidgetClass, scrolledWindow6,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNresizeWidth, TRUE,
			XmNresizeHeight, TRUE,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNcolumns, 80,
			XmNy, 0,
			XmNx, 0,
			XmNheight, 220,
			XmNwidth, 690,
			NULL );

	UxPutContext( data_code_scrolledText, (char *) UxDbox_user_dataContext );

	apply_data_pb = XtVaCreateManagedWidget( "apply_data_pb",
			xmPushButtonWidgetClass, form9,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftWidget, ok_data_pb,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Apply" ),
			XmNheight, 28,
			XmNwidth, 90,
			XmNy, 300,
			XmNx, 140,
			NULL );

	UxPutContext( apply_data_pb, (char *) UxDbox_user_dataContext );

	cancel_data_pb = XtVaCreateManagedWidget( "cancel_data_pb",
			xmPushButtonWidgetClass, form9,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftWidget, apply_data_pb,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 28,
			XmNwidth, 90,
			XmNy, 300,
			XmNx, 250,
			NULL );

	UxPutContext( cancel_data_pb, (char *) UxDbox_user_dataContext );

	XtAddCallback( dbox_user_data, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxDbox_user_dataContext );

	XtAddCallback( data_decl_scrolledText, XmNmodifyVerifyCallback,
			text_maius_callback,
			(XtPointer) UxDbox_user_dataContext );

	XtAddCallback( ok_data_pb, XmNactivateCallback,
			activateCB_ok_data_pb,
			(XtPointer) UxDbox_user_dataContext );

	XtAddCallback( data_code_scrolledText, XmNmodifyVerifyCallback,
			text_maius_callback,
			(XtPointer) UxDbox_user_dataContext );

	XtAddCallback( apply_data_pb, XmNactivateCallback,
			activateCB_apply_data_pb,
			(XtPointer) UxDbox_user_dataContext );

	XtAddCallback( cancel_data_pb, XmNactivateCallback,
			activateCB_cancel_data_pb,
			(XtPointer) UxDbox_user_dataContext );



	return ( dbox_user_data );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_dbox_userdata()
{
	Widget                  rtrn;
	_UxCdbox_user_data      *UxContext;

	UxDbox_user_dataContext = UxContext =
		(_UxCdbox_user_data *) XtMalloc( sizeof(_UxCdbox_user_data) );

	rtrn = _Uxbuild_dbox_user_data();

	UxPopupInterface (rtrn, no_grab);
	dbox_userdata_managed = True;
	
	/* aggiorna i text-widget (dichiarazione e codice) */
	if ( str_dichI2 != NULL)
	   XmTextSetString(UxGetWidget(data_decl_scrolledText), str_dichI2);
	
	if ( str_codI2 != NULL)
	   XmTextSetString(UxGetWidget(data_code_scrolledText), str_codI2);
	
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_dbox_userdata()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_dbox_userdata();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

