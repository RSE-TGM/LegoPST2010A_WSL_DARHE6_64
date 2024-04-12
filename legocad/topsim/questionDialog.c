
/*******************************************************************************
	questionDialog.c
	(Generated from interface file questionDialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo questionDialog.i
   tipo 
   release 1.24
   data 8/29/95
   reserved @(#)questionDialog.i	1.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "topsim.h"
#include "lg1_topsim.h"
#include "questionMsgDb.h"

extern SIMULATORE *simulatore;

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
	Widget	UxquestionDialog;
	swidget	Uxwcallers;
	TIPO_OP	Uxnidop;
} _UxCquestionDialog;

#define questionDialog          UxQuestionDialogContext->UxquestionDialog
#define wcallers                UxQuestionDialogContext->Uxwcallers
#define nidop                   UxQuestionDialogContext->Uxnidop

static _UxCquestionDialog	*UxQuestionDialogContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_questionDialog();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* elimina_help_button
   
   elimina il bottone di help 
*/
qelimina_help_button()
{
   Widget hb;
  
   hb = XmMessageBoxGetChild(questionDialog,XmDIALOG_HELP_BUTTON);
   XtDestroyWidget(hb);
}

/* set_message 
 
 set del messaggio sulla message box
*/

qset_message(char *mess)
{
   Arg args[1];
   Cardinal nargs;
   XmString mesg;

   mesg = XmStringCreateSimple(mess);
   nargs=0;
   XtSetArg(args[nargs],XmNmessageString,mesg);nargs++;
   XtSetValues(questionDialog,args,nargs);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_questionDialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionDialog      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionDialogContext;
	UxQuestionDialogContext = UxContext =
			(_UxCquestionDialog *) UxGetContext( UxWidget );
	{
	extern void confermata_remove_simulator();
	extern Boolean simulator_changed;
	switch( nidop)
	{
	   case BYEBYE:
	     if( simulatore != NULL)
	        libera_simulatore(simulatore);
	 
	     printf("Topsim Normally Terminated\n"); 
	     exit();
	   break;
	   case OPENSIM:
	      /* do nothing */
	   break;  
	   case REMOVESIM:
	      /* non  rimuovere la interfaccia di selezione */
	      confermata_remove_simulator();
	   break; 
	   case DELTASK:
	      simulator_changed=True;
	      confermata_remove_task();
	   break;
	   case DELCONN:
	   break;   
	   case DELALLCONN:
	      simulator_changed=True;
	      del_all_task_conn();
	   break;
	   default:
	     printf("Operazione non riconosciuta\n");
	   break;  
	}
	}
	UxQuestionDialogContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_questionDialog()
{
	Widget	questionDialog_shell;

	questionDialog_shell = XtVaCreatePopupShell( "questionDialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 260,
			XmNy, 310,
			XmNwidth, 280,
			XmNheight, 140,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "questionDialog",
			NULL );

	questionDialog = XtVaCreateWidget( "questionDialog",
			xmMessageBoxWidgetClass, questionDialog_shell,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNhelpLabelString, "Help" ),
			RES_CONVERT( XmNmessageString, "Confirm Operation ?" ),
			XmNheight, 140,
			XmNwidth, 280,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( questionDialog, (char *) UxQuestionDialogContext );

	XtAddCallback( questionDialog, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxQuestionDialogContext );

	XtAddCallback( questionDialog, XmNokCallback,
			okCallback_questionDialog,
			(XtPointer) UxQuestionDialogContext );



	return ( questionDialog );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_questionDialog( _Uxwcallers, _Uxnidop )
	swidget	_Uxwcallers;
	TIPO_OP	_Uxnidop;
{
	Widget                  rtrn;
	_UxCquestionDialog      *UxContext;

	UxQuestionDialogContext = UxContext =
		(_UxCquestionDialog *) XtMalloc( sizeof(_UxCquestionDialog) );

	wcallers = _Uxwcallers;
	nidop = _Uxnidop;
	{
		extern Boolean simulator_changed;
		rtrn = _Uxbuild_questionDialog();

		qelimina_help_button();
		
		switch( nidop)
		{
		   case BYEBYE:
		     if(!simulator_changed)
		        qset_message(question[nidop]);
		     else
		        qset_message("WARNING SIMULATOR MODIFIED. Do you want Really Exit?");
		   break;
		   case OPENSIM:
		   case REMOVESIM:
		   case DELTASK:        
		     qset_message(question[nidop]);
		   break;
		   case DELCONN:
		   break;
		   case DELALLCONN:
		     qset_message(question[nidop]);
		   break;    
		   default:
		     qset_message("Codice di uscita non riconosciuto.");
		   break;  
		}
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_questionDialog( _Uxwcallers, _Uxnidop )
	swidget	_Uxwcallers;
	TIPO_OP	_Uxnidop;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_questionDialog( _Uxwcallers, _Uxnidop );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

