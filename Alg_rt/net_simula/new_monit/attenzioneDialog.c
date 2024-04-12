
/*******************************************************************************
       attenzioneDialog.c
       (Generated from interface file attenzioneDialog.i)
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

#ifndef DESIGN_TIME
#include "parametri.h"
#endif
int risposta;
char *messaggio;


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
	Widget	Uxpadre_warn;
	unsigned char	*Uxwarning_message;
	int	Uxmodo;
} _UxCattenzioneDialog;

static _UxCattenzioneDialog    *UxAttenzioneDialogContext;
#define padre_warn              UxAttenzioneDialogContext->Uxpadre_warn
#define warning_message         UxAttenzioneDialogContext->Uxwarning_message
#define modo                    UxAttenzioneDialogContext->Uxmodo


Widget	attenzioneDialog;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

int	create_attenzioneDialog();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	cancelCB_attenzioneDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCattenzioneDialog    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAttenzioneDialogContext;
	UxAttenzioneDialogContext = UxContext =
			(_UxCattenzioneDialog *) UxGetContext( UxWidget );
	{
	risposta = FALSE;
	}
	UxAttenzioneDialogContext = UxSaveCtx;
}

static	void	okCallback_attenzioneDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCattenzioneDialog    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAttenzioneDialogContext;
	UxAttenzioneDialogContext = UxContext =
			(_UxCattenzioneDialog *) UxGetContext( UxWidget );
	{
	risposta = TRUE;
	}
	UxAttenzioneDialogContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_attenzioneDialog()
{
	Widget		_UxParent;


	/* Creation of attenzioneDialog */
	_UxParent = padre_warn;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "attenzioneDialog_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 630,
			XmNy, 65,
			XmNwidth, 440,
			XmNheight, 215,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "attenzioneDialog",
			NULL );

	attenzioneDialog = XtVaCreateWidget( "attenzioneDialog",
			xmMessageBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_WARNING,
			XmNunitType, XmPIXELS,
			XmNwidth, 440,
			XmNheight, 215,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNmessageString, messaggio ),
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			NULL );
	XtAddCallback( attenzioneDialog, XmNcancelCallback,
		(XtCallbackProc) cancelCB_attenzioneDialog,
		(XtPointer) UxAttenzioneDialogContext );
	XtAddCallback( attenzioneDialog, XmNokCallback,
		(XtCallbackProc) okCallback_attenzioneDialog,
		(XtPointer) UxAttenzioneDialogContext );

	UxPutContext( attenzioneDialog, (char *) UxAttenzioneDialogContext );


	XtAddCallback( attenzioneDialog, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxAttenzioneDialogContext);


	return ( attenzioneDialog );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

int	create_attenzioneDialog( _Uxpadre_warn, _Uxwarning_message, _Uxmodo )
	Widget	_Uxpadre_warn;
	unsigned char	*_Uxwarning_message;
	int	_Uxmodo;
{
	Widget                  rtrn;
	_UxCattenzioneDialog    *UxContext;

	UxAttenzioneDialogContext = UxContext =
		(_UxCattenzioneDialog *) UxNewContext( sizeof(_UxCattenzioneDialog), False );

	padre_warn = _Uxpadre_warn;
	warning_message = _Uxwarning_message;
	modo = _Uxmodo;

	{
		risposta = -1;
		messaggio = (char *)malloc (strlen(warning_message)+1);
		strcpy (messaggio,warning_message);
		rtrn = _Uxbuild_attenzioneDialog();

		/* elimino comunque il tasto HELP */
		XtUnmanageChild (
		    XmMessageBoxGetChild(UxGetWidget(rtrn),XmDIALOG_HELP_BUTTON));
		
#ifndef DESIGN_TIME
		
		switch (modo)
		   {
		   case DIALOG_ERROR:
			XtVaSetValues (rtrn, 
				XmNbackground, colore_app[COLORE_DIALOG_ERROR],
				XmNdialogType, modo, NULL);
			XtUnmanageChild (
		    		XmMessageBoxGetChild(UxGetWidget(rtrn),
				XmDIALOG_CANCEL_BUTTON));
			break;
		   case DIALOG_INFORMATION:
			XtVaSetValues (rtrn, XmNdialogType, modo, NULL);
			XtUnmanageChild (
		    		XmMessageBoxGetChild(UxGetWidget(rtrn),
				XmDIALOG_CANCEL_BUTTON));
			break;
		   case DIALOG_MESSAGE:
			XtVaSetValues (rtrn, XmNdialogType, modo, NULL);
			break;
		   case DIALOG_QUESTION:
			XtVaSetValues (rtrn, XmNdialogType, modo, NULL);
			break;
		   case DIALOG_WARNING:
			XtVaSetValues (rtrn, 
				XmNbackground, colore_app[COLORE_DIALOG_ERROR],
				XmNdialogType, modo, NULL);
			XtUnmanageChild (
		    		XmMessageBoxGetChild(UxGetWidget(rtrn),
				XmDIALOG_CANCEL_BUTTON));
			break;
		   case DIALOG_WORKING:
			XtVaSetValues (rtrn, XmNdialogType, modo, NULL);
			XtUnmanageChild (
		    		XmMessageBoxGetChild(UxGetWidget(rtrn),
				XmDIALOG_CANCEL_BUTTON));
			break;
		   default:
			break;
		   }
		
#endif
		
		UxPopupInterface (rtrn,no_grab);
		while (risposta == -1)
		   {
		   XtAppProcessEvent (UxAppContext,XtIMAll);
		   XSync (UxDisplay,0);
		   }
		printf ("chiusura warning\n");
		return(risposta);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

