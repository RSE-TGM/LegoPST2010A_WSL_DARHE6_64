
/*******************************************************************************
       Message.c
       (Generated from interface file Message.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"
#include "libutilx.h"

#include <Xm/MessageB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo Message.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)Message.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/Xm.h>
#include <Xl/Xl.h>
#include "res_edit.h"

extern void EseguiLoadBitmap();
extern void EseguiCaricaIcona();
extern int EseguiLoadResource( );


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
	int	UxIngresso;
	Widget	UxOggetto;
	Widget	UxOggettoParametro;
	int	UxTipoMsg;
	Widget	UxChiamante;
	Widget	UxPar;
} _UxCMessage;

static _UxCMessage             *UxMessageContext;
#define Ingresso                UxMessageContext->UxIngresso
#define Oggetto                 UxMessageContext->UxOggetto
#define OggettoParametro        UxMessageContext->UxOggettoParametro
#define TipoMsg                 UxMessageContext->UxTipoMsg
#define Chiamante               UxMessageContext->UxChiamante
#define Par                     UxMessageContext->UxPar


Widget	Message;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_Message();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	cancelCB_Message( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCMessage             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMessageContext;
	UxMessageContext = UxContext =
			(_UxCMessage *) UxGetContext( UxWidget );
	{
	XtDestroyWidget (Message);
	}
	UxMessageContext = UxSaveCtx;
}

static	void	okCallback_Message( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCMessage             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMessageContext;
	UxMessageContext = UxContext =
			(_UxCMessage *) UxGetContext( UxWidget );
	{
	Arg arg[3];
	switch (Ingresso)
		{
		case LOAD:
			EseguiLoadResources();
		break;
		case BITMAP:
			EseguiLoadBitmap(Chiamante);
		break;
		case ICONA:
			EseguiCaricaIcona(Chiamante,"#000000000000",OggettoParametro);
		break;
		case CLOSE:
		if (OggettoParametro)
			{
			XtSetArg (arg[0], XlNinEdit, False);
			XtSetArg (arg[1], XlNwEdit, NULL);
			XtSetValues (OggettoParametro, arg, 2);
			}
		XtDestroyWidget (Chiamante);
		break;
		}
	XtDestroyWidget (Message);
	}
	UxMessageContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Message()
{
	Widget		_UxParent;


	/* Creation of Message */
	_UxParent = Chiamante;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "Message_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 654,
			XmNy, 249,
			XmNwidth, 320,
			XmNheight, 145,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Message",
			NULL );

	Message = XtVaCreateWidget( "Message",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNunitType, XmPIXELS,
			XmNwidth, 320,
			XmNheight, 145,
			NULL );
	XtAddCallback( Message, XmNcancelCallback,
		(XtCallbackProc) cancelCB_Message,
		(XtPointer) UxMessageContext );
	XtAddCallback( Message, XmNokCallback,
		(XtCallbackProc) okCallback_Message,
		(XtPointer) UxMessageContext );

	UxPutContext( Message, (char *) UxMessageContext );


	XtAddCallback( Message, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxMessageContext);


	return ( Message );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_Message( _UxTipoMsg, _UxChiamante, _UxPar )
	int	_UxTipoMsg;
	Widget	_UxChiamante;
	Widget	_UxPar;
{
	Widget                  rtrn;
	_UxCMessage             *UxContext;

	UxMessageContext = UxContext =
		(_UxCMessage *) UxNewContext( sizeof(_UxCMessage), False );

	TipoMsg = _UxTipoMsg;
	Chiamante = _UxChiamante;
	Par = _UxPar;

	{
		Position Px,Py;
		Dimension WidC,WidM,HeiC,HeiM;
		
		Ingresso = TipoMsg;
		Oggetto = Chiamante;
		OggettoParametro = Par;
		rtrn = _Uxbuild_Message();

		get_something (Chiamante, XmNx, (void*) &Px);
		get_something (Chiamante, XmNy, (void*) &Py);
		get_something (Chiamante, XmNwidth, (void*) &WidC);
		get_something (Chiamante, XmNheight, (void*) &HeiC);
		get_something (Message, XmNwidth, (void*) &WidM);
		get_something (Message, XmNheight, (void*) &HeiM);
		
		Px += (Position )(WidC-WidM)/2;
		Py += (Position )(HeiC-HeiM)/2;
		
		set_something (rtrn, XmNx, (void*) Px);
		set_something (rtrn, XmNy, (void*) Py);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

