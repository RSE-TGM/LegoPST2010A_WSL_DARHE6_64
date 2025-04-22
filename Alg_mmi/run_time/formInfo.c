
/*******************************************************************************
       formInfo.c
       (Generated from interface file formInfo.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo formInfo.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)formInfo.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>


#include "other.h"


Widget PadreInfo;

static void InserisciTesto();


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
	Widget	UxformInfo;
	Widget	UxlabelInfo;
	Widget	UxformTextInfo;
	Widget	UxscrolledWindow2;
	Widget	UxscrolledTextInfo;
	Widget	UxformButtonInfo;
	Widget	UxpushButtonInfo;
	Widget	UxtopLevel_forminfo;
	XmFontList	UxFontLabelFormInfo;
	XmFontList	UxFontListaFormInfo;
	Widget	Uxwid;
	Widget	UxPadreForminfo;
} _UxCformInfo;

static _UxCformInfo            *UxFormInfoContext;
#define formInfo                UxFormInfoContext->UxformInfo
#define labelInfo               UxFormInfoContext->UxlabelInfo
#define formTextInfo            UxFormInfoContext->UxformTextInfo
#define scrolledWindow2         UxFormInfoContext->UxscrolledWindow2
#define scrolledTextInfo        UxFormInfoContext->UxscrolledTextInfo
#define formButtonInfo          UxFormInfoContext->UxformButtonInfo
#define pushButtonInfo          UxFormInfoContext->UxpushButtonInfo
#define topLevel_forminfo       UxFormInfoContext->UxtopLevel_forminfo
#define FontLabelFormInfo       UxFormInfoContext->UxFontLabelFormInfo
#define FontListaFormInfo       UxFormInfoContext->UxFontListaFormInfo
#define wid                     UxFormInfoContext->Uxwid
#define PadreForminfo           UxFormInfoContext->UxPadreForminfo



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	popup_formInfo();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

static void InserisciTesto(Widget oggettoSel)
{
char testo[10000];
#ifndef DESIGN_TIME
printf("Inserisci testo %s\n",XtName(oggettoSel));
if(!PreparaTestoInfo(oggettoSel,testo))
	return;
set_something(scrolledTextInfo,XmNvalue,(void*) testo);
#endif
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButtonInfo( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCformInfo            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFormInfoContext;
	UxFormInfoContext = UxContext =
			(_UxCformInfo *) UxGetContext( UxWidget );
	{
	FreeFont(FontLabelFormInfo,XtDisplay(formInfo));
	FreeFont(FontListaFormInfo,XtDisplay(formInfo));
	XtDestroyWidget(XtParent(formInfo));
	
	}
	UxFormInfoContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_formInfo()
{
	Widget		_UxParent;


	/* Creation of formInfo */
	_UxParent = PadreInfo;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "formInfo_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNwidth, 470,
			XmNheight, 260,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "formInfo",
			NULL );

	formInfo = XtVaCreateWidget( "formInfo",
			xmFormWidgetClass,
			_UxParent,
			XmNunitType, XmPIXELS,
			XmNwidth, 470,
			XmNheight, 260,
			RES_CONVERT( XmNdialogTitle, "Info" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNrubberPositioning, TRUE,
			NULL );
	UxPutContext( formInfo, (char *) UxFormInfoContext );


	/* Creation of labelInfo */
	labelInfo = XtVaCreateManagedWidget( "labelInfo",
			xmLabelWidgetClass,
			formInfo,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 470,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "Info about ..." ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNhighlightThickness, 0,
			XmNshadowThickness, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrecomputeSize, FALSE,
			NULL );
	UxPutContext( labelInfo, (char *) UxFormInfoContext );


	/* Creation of formTextInfo */
	formTextInfo = XtVaCreateManagedWidget( "formTextInfo",
			xmFormWidgetClass,
			formInfo,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 40,
			XmNwidth, 470,
			XmNheight, 180,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 60,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNrightOffset, 10,
			XmNtopWidget, labelInfo,
			NULL );
	UxPutContext( formTextInfo, (char *) UxFormInfoContext );


	/* Creation of scrolledWindow2 */
	scrolledWindow2 = XtVaCreateManagedWidget( "scrolledWindow2",
			xmScrolledWindowWidgetClass,
			formTextInfo,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNx, 0,
			XmNy, 0,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNshadowThickness, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( scrolledWindow2, (char *) UxFormInfoContext );


	/* Creation of scrolledTextInfo */
	scrolledTextInfo = XtVaCreateManagedWidget( "scrolledTextInfo",
			xmTextWidgetClass,
			scrolledWindow2,
			XmNwidth, 450,
			XmNheight, 140,
			RES_CONVERT( XmNbackground, "#ffffff" ),
			XmNcursorPositionVisible, FALSE,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNeditable, FALSE,
			XmNwordWrap, TRUE,
			XmNvalue, "",
			RES_CONVERT( XmNforeground, "#000000" ),
			NULL );
	UxPutContext( scrolledTextInfo, (char *) UxFormInfoContext );


	/* Creation of formButtonInfo */
	formButtonInfo = XtVaCreateManagedWidget( "formButtonInfo",
			xmFormWidgetClass,
			formInfo,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 20,
			XmNy, 210,
			XmNwidth, 430,
			XmNheight, 60,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( formButtonInfo, (char *) UxFormInfoContext );


	/* Creation of pushButtonInfo */
	pushButtonInfo = XtVaCreateManagedWidget( "pushButtonInfo",
			xmPushButtonWidgetClass,
			formButtonInfo,
			XmNx, 350,
			XmNy, 10,
			XmNwidth, 100,
			XmNheight, 40,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "Close" ),
			XmNleftAttachment, XmATTACH_NONE,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 30,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( pushButtonInfo, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButtonInfo,
		(XtPointer) UxFormInfoContext );

	UxPutContext( pushButtonInfo, (char *) UxFormInfoContext );

	XtVaSetValues(formInfo,
			XmNdefaultButton, pushButtonInfo,
			NULL );


	XtAddCallback( formInfo, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxFormInfoContext);


	return ( formInfo );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_formInfo( _Uxwid, _UxPadreForminfo )
	Widget	_Uxwid;
	Widget	_UxPadreForminfo;
{
	Widget                  rtrn;
	_UxCformInfo            *UxContext;

	UxFormInfoContext = UxContext =
		(_UxCformInfo *) UxNewContext( sizeof(_UxCformInfo), False );

	wid = _Uxwid;
	PadreForminfo = _UxPadreForminfo;

	{
#ifndef DESIGN_TIME
		if(XlIsXlCore(wid))
		     	{
		     	topLevel_forminfo=XtParent(wid);
		     	} 	
		else
			{
		     	topLevel_forminfo=XtParent(XtParent(wid));
			}
#endif
		
		if(XlIsXlComposite(topLevel_forminfo))
			topLevel_forminfo=XtParent(topLevel_forminfo);
		
		PadreInfo=topLevel_forminfo;
		
		
		
		
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LISTA,&FontListaFormInfo,XtDisplay(topLevel_forminfo)))
			exit(0);
		if(!LoadFont(FONT_LABEL,&FontLabelFormInfo,XtDisplay(topLevel_forminfo)))
			exit(0);
#endif
		rtrn = _Uxbuild_formInfo();

		set_something(labelInfo,XmNfontList,(void*) FontLabelFormInfo);
		set_something(pushButtonInfo,XmNfontList,(void*) FontLabelFormInfo);
		set_something(scrolledTextInfo,XmNfontList,(void*) FontListaFormInfo);
		UxPopupInterface(rtrn, no_grab);
		InserisciTesto(wid);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

