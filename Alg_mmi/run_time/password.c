
/*******************************************************************************
       password.c
       (Generated from interface file password.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include <Ol/OlPert.h>
#include "other.h"

int password_ok;


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
	Widget	Uxpassword;
	Widget	UxPadrePassword;
} _UxCpassword;

static _UxCpassword            *UxPasswordContext;
#define password                UxPasswordContext->Uxpassword
#define PadrePassword           UxPasswordContext->UxPadrePassword



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	popup_password();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	cancelCB_password( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpassword            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPasswordContext;
	UxPasswordContext = UxContext =
			(_UxCpassword *) UxGetContext( UxWidget );
	{
	password_ok = 0;
	}
	UxPasswordContext = UxSaveCtx;
}

static	void	helpCB_password( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpassword            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPasswordContext;
	UxPasswordContext = UxContext =
			(_UxCpassword *) UxGetContext( UxWidget );
	{
	password_ok = 0;
	}
	UxPasswordContext = UxSaveCtx;
}

static	void	okCallback_password( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCpassword            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPasswordContext;
	UxPasswordContext = UxContext =
			(_UxCpassword *) UxGetContext( UxWidget );
	{
	XmString ret;
	char * pass;
	extern char *extract_string();
	
	/* definizioni per uscita da teleperm 
	   in questo caso questa callback effettua la chiusura
	   di mmi ma se siamo in debug (cioe' la risorsa della
	   applicazione decorazioni e' a 1) fa solo la chiusura della
	   pagina. 
	*/
	int decorOn=0;
	char *tipo;
	XrmValue value;
	char risorsa[50];
	char appo[50];
	
	extern void quit_proc();
	extern void telep_chiudi_pag();
	
	get_something(password,XmNtextString,(void*) &ret);
	pass=extract_string(ret);
	
	/* GESTIONE TELEPERM
	   esco direttamente da mmi senza neanche controllare la pwd
	   mi baso solo sul fatto che il parent e' teleperm.
	   Se sono in debug (decorazioni = 1) chiudo la pagina.
	*/
	if( strcmp(XtName(PadrePassword),"teleperm") == 0)
	{
	   sprintf(risorsa,"teleperm.decorazioni");
	   XrmGetResource(UxDisplay->db,risorsa,(char*)NULL,&tipo,&value);
	   strncpy(appo,value.addr,(int)value.size);
	   decorOn = atoi(appo);
	
	   password_ok = 1;
	  
	   if( decorOn != 0)
	      telep_chiudi_pag(PadrePassword);
	   else 
	      quit_proc();
	     
	   return;
	}
	 
#ifndef DESIGN_TIME
	if(strcmp(pass,PASSWORD)==0)
		{
		password_ok = 1;
		}
	else
		{
		popup_errorDialog("Error in password",PadrePassword);
		password_ok = 0;
		}
#endif
	
	}
	UxPasswordContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_password()
{
	Widget		_UxParent;


	/* Creation of password */
	_UxParent = XtVaCreatePopupShell( "password_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 170,
			XmNy, 110,
			XmNwidth, 310,
			XmNheight, 200,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "password",
			NULL );

	password = XtVaCreateWidget( "password",
			xmSelectionBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_PROMPT,
			XmNunitType, XmPIXELS,
			XmNwidth, 310,
			XmNheight, 200,
			RES_CONVERT( XmNforeground, "#000000" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNselectionLabelString, "Insert password" ),
			XmNtextColumns, 10,
			NULL );
	XtAddCallback( password, XmNcancelCallback,
		(XtCallbackProc) cancelCB_password,
		(XtPointer) UxPasswordContext );
	XtAddCallback( password, XmNhelpCallback,
		(XtCallbackProc) helpCB_password,
		(XtPointer) UxPasswordContext );
	XtAddCallback( password, XmNokCallback,
		(XtCallbackProc) okCallback_password,
		(XtPointer) UxPasswordContext );

	UxPutContext( password, (char *) UxPasswordContext );


	XtAddCallback( password, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxPasswordContext);


	return ( password );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_password( _UxPadrePassword )
	Widget	_UxPadrePassword;
{
	Widget                  rtrn;
	_UxCpassword            *UxContext;

	UxPasswordContext = UxContext =
		(_UxCpassword *) UxNewContext( sizeof(_UxCpassword), False );

	PadrePassword = _UxPadrePassword;

	{
		XmFontList FontLabel;
		
		
#ifndef DESIGN_TIME
		if(!LoadFont(FONT_LABEL,&FontLabel,XtDisplay(PadrePassword)))
			exit(0);
#endif
		
		password_ok = 0;
		rtrn = _Uxbuild_password();

		set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_SELECTION_LABEL),(void*) XmNfontList,(char*)FontLabel);
		set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT),(void*) XmNfontList,(char*)FontLabel);
#ifndef DESIGN_TIME
		XtVaSetValues(XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT),
			RES_CONVERT( XmNbackground, "white" ),
		        RES_CONVERT( XmNforeground, "white" ),NULL);
#endif
		UxPopupInterface(rtrn, no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

