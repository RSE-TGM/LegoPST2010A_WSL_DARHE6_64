
/*******************************************************************************
       questionDialogQuit.c
       (Generated from interface file questionDialogQuit.i)
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
   modulo questionDialogQuit.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)questionDialogQuit.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "libutilx.h"
extern  void *		UxNewContext();

/*
	font utilizzati
*/
#define FONT_TASTI "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define FONT_LISTA "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define FONT_LABEL "-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1"
#define OPERAZIONE_NOP			0
#define OPERAZIONE_XAING		1
#define OPERAZIONE_XPLOT		2
#define OPERAZIONE_XSTAZ		3
#define OPERAZIONE_INFO			4
#define OPERAZIONE_REG			5

#define REFRESH_AING			1000
#define REFRESH_PLOT			1000
#define DELTA_PLOT			120
#define COLOR_PLOT			"yellow"

Boolean LoadFont(char *, XmFontList *, Display *);

//#include "other.h"


extern int password_ok;


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
	Widget	UxquestionDialogQuit;
	Widget	UxPadreDialogQuit;
	Widget	Ux_PadreDialogQuit;
	Boolean	Uxscada_on;
} _UxCquestionDialogQuit;

static _UxCquestionDialogQuit  *UxQuestionDialogQuitContext;
#define questionDialogQuit      UxQuestionDialogQuitContext->UxquestionDialogQuit
#define PadreDialogQuit         UxQuestionDialogQuitContext->UxPadreDialogQuit
#define _PadreDialogQuit        UxQuestionDialogQuitContext->Ux_PadreDialogQuit
#define scada_on                UxQuestionDialogQuitContext->Uxscada_on



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_questionDialogQuit();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_questionDialogQuit( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCquestionDialogQuit  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionDialogQuitContext;
	UxQuestionDialogQuitContext = UxContext =
			(_UxCquestionDialogQuit *) UxGetContext( UxWidget );
	{
	extern void quit_proc();
	
	if(password_ok == 1)
		quit_proc();
	}
	UxQuestionDialogQuitContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_questionDialogQuit()
{
	Widget		_UxParent;


	/* Creation of questionDialogQuit */
	_UxParent = PadreDialogQuit;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "questionDialogQuit_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 442,
			XmNy, 150,
			XmNwidth, 288,
			XmNheight, 222,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "questionDialogQuit",
			NULL );

	questionDialogQuit = XtVaCreateWidget( "questionDialogQuit",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_QUESTION,
			XmNunitType, XmPIXELS,
			XmNwidth, 288,
			XmNheight, 222,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNmessageString, "Exit LegoMMI ?" ),
			RES_CONVERT( XmNdialogTitle, "Exit" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			XmNnoResize, FALSE,
			XmNresizePolicy, XmRESIZE_ANY,
			NULL );
	XtAddCallback( questionDialogQuit, XmNokCallback,
		(XtCallbackProc) okCallback_questionDialogQuit,
		(XtPointer) UxQuestionDialogQuitContext );

	UxPutContext( questionDialogQuit, (char *) UxQuestionDialogQuitContext );


	XtAddCallback( questionDialogQuit, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxQuestionDialogQuitContext);


	return ( questionDialogQuit );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_questionDialogQuit( _Ux_PadreDialogQuit, _Uxscada_on )
	Widget	_Ux_PadreDialogQuit;
	Boolean	_Uxscada_on;
{
	Widget                  rtrn;
	_UxCquestionDialogQuit  *UxContext;

	UxQuestionDialogQuitContext = UxContext =
		(_UxCquestionDialogQuit *) UxNewContext( sizeof(_UxCquestionDialogQuit), False );

	_PadreDialogQuit = _Ux_PadreDialogQuit;
	scada_on = _Uxscada_on;

	{
		extern swidget popup_password();
		XmFontList FontLabel;
		
		PadreDialogQuit= _PadreDialogQuit;
		
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabel,XtDisplay(PadreDialogQuit)))
			exit(0);
#endif
		rtrn = _Uxbuild_questionDialogQuit();

		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),(void*) XmNfontList,(char*)FontLabel);
		UxPopupInterface(rtrn, no_grab);
		
		if(scada_on)
			{
			password_ok = 0;
			popup_password(PadreDialogQuit);
			}
		else
			password_ok = 1;
		
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

