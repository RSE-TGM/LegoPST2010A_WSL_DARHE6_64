
/*******************************************************************************
       CloseQuestion.c
       (Generated from interface file CloseQuestion.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo CloseQuestion.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)CloseQuestion.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


#include "other.h"

#include <Rt/RtMemory.h>

Widget PadreClose;


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
	Widget	UxCloseQuestion;
	Widget	UxPaginaSinottico;
	Widget	UxPaginaDrawing;
	XmFontList	UxFontLabelClose;
	Widget	UxTop;
	Widget	UxDrawing;
	XtIntervalId	*Uxtimer;
	int	Uxkey;
} _UxCCloseQuestion;

static _UxCCloseQuestion       *UxCloseQuestionContext;
#define CloseQuestion           UxCloseQuestionContext->UxCloseQuestion
#define PaginaSinottico         UxCloseQuestionContext->UxPaginaSinottico
#define PaginaDrawing           UxCloseQuestionContext->UxPaginaDrawing
#define FontLabelClose          UxCloseQuestionContext->UxFontLabelClose
#define Top                     UxCloseQuestionContext->UxTop
#define Drawing                 UxCloseQuestionContext->UxDrawing
#define timer                   UxCloseQuestionContext->Uxtimer
#define key                     UxCloseQuestionContext->Uxkey



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	popup_CloseQuestion();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_CloseQuestion( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCCloseQuestion       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCloseQuestionContext;
	UxCloseQuestionContext = UxContext =
			(_UxCCloseQuestion *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	DelElencoPagine(key, PaginaDrawing);
	XSync(XtDisplay(UxWidget),False);
#endif
	XtRemoveTimeOut(*timer);
	XtDestroyWidget(PaginaSinottico);
	}
	UxCloseQuestionContext = UxSaveCtx;
}

static	void	destroyCB_CloseQuestion( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCCloseQuestion       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCloseQuestionContext;
	UxCloseQuestionContext = UxContext =
			(_UxCCloseQuestion *) UxGetContext( UxWidget );
	{
	
	}
	UxCloseQuestionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_CloseQuestion()
{
	Widget		_UxParent;


	/* Creation of CloseQuestion */
	_UxParent = PadreClose;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "CloseQuestion_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 381,
			XmNy, 135,
			XmNwidth, 544,
			XmNheight, 149,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "CloseQuestion",
			NULL );

	CloseQuestion = XtVaCreateWidget( "CloseQuestion",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_QUESTION,
			XmNunitType, XmPIXELS,
			XmNwidth, 544,
			XmNheight, 149,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNmessageString, "Close the page ?" ),
			RES_CONVERT( XmNhelpLabelString, "Help" ),
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			RES_CONVERT( XmNokLabelString, "Ok" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			NULL );
	XtAddCallback( CloseQuestion, XmNokCallback,
		(XtCallbackProc) okCallback_CloseQuestion,
		(XtPointer) UxCloseQuestionContext );
	XtAddCallback( CloseQuestion, XmNdestroyCallback,
		(XtCallbackProc) destroyCB_CloseQuestion,
		(XtPointer) UxCloseQuestionContext );

	UxPutContext( CloseQuestion, (char *) UxCloseQuestionContext );


	XtAddCallback( CloseQuestion, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxCloseQuestionContext);


	return ( CloseQuestion );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_CloseQuestion( _UxTop, _UxDrawing, _Uxtimer, _Uxkey )
	Widget	_UxTop;
	Widget	_UxDrawing;
	XtIntervalId	*_Uxtimer;
	int	_Uxkey;
{
	Widget                  rtrn;
	_UxCCloseQuestion       *UxContext;

	UxCloseQuestionContext = UxContext =
		(_UxCCloseQuestion *) UxNewContext( sizeof(_UxCCloseQuestion), False );

	Top = _UxTop;
	Drawing = _UxDrawing;
	timer = _Uxtimer;
	key = _Uxkey;

	{
		PaginaSinottico= Top;
		PaginaDrawing=Drawing;
		
		PadreClose= Top;
		
#if defined SCADA_MMI
#ifndef DESIGN_TIME
		DelElencoPagine(key, PaginaDrawing);
#endif
		XtRemoveTimeOut(*timer);
		XtDestroyWidget(PaginaSinottico);
		return(NULL);
#endif
		
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabelClose,XtDisplay(PadreClose)))
			exit(0);
#endif
		rtrn = _Uxbuild_CloseQuestion();

		UxPopupInterface(rtrn, no_grab);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),(void*) XmNfontList,FontLabelClose);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),(void*) XmNfontList,FontLabelClose);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),(void*) XmNfontList,FontLabelClose);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),(void*) XmNfontList,FontLabelClose);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

