
/*******************************************************************************
	question_operation.c
	(Generated from interface file question_operation.i)
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

#ifndef DESIGN_TIME
/*
   modulo question_operation.i
   tipo 
   release 1.22
   data 5/16/95
   reserved @(#)question_operation.i	1.22
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include "legomain.h"

extern swidget applicationShell1;
extern char path_legocad[];
extern swidget create_vis_msg();

/* 04/07/97 Carlo
*/
extern char *get_select_model_new();

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
	Widget	Uxquestion_operation;
	unsigned char	Uxappo[300];
	unsigned char	Uxpathmodel[300];
	Widget	Uxwchiamante;
	swidget	Uxwgt_call;
	int	Uxtip_q;
} _UxCquestion_operation;

#define question_operation      UxQuestion_operationContext->Uxquestion_operation
#define appo                    UxQuestion_operationContext->Uxappo
#define pathmodel               UxQuestion_operationContext->Uxpathmodel
#define wchiamante              UxQuestion_operationContext->Uxwchiamante
#define wgt_call                UxQuestion_operationContext->Uxwgt_call
#define tip_q                   UxQuestion_operationContext->Uxtip_q

static _UxCquestion_operation	*UxQuestion_operationContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_question_operation();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

delete_model(char *path)
{
  extern swidget create_vis_msg();
  extern char path_modello[];
  extern refresh_lista();
  char comando[256];

  strcpy(comando,"rm -r ");
  strcat(comando,path);

if( !strcmp(path,path_modello) )
{
   create_vis_msg("It's impossibile delete actual Loaded model \n");
   return(-1);
}

  printf("invio il comando %s\n",comando);

  if( (system(comando)) != 0)
     create_vis_msg("Cannot remove selected Model");
  else
     refresh_lista(wchiamante);

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_question_operation( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestion_operation  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestion_operationContext;
	UxQuestion_operationContext = UxContext =
			(_UxCquestion_operation *) UxGetContext( UxWidget );
	{
	extern void overwrite_fileoutedi14();
	
	switch(tip_q)
		{
		case Q_DELETE_MODEL:
	
	           delete_model(pathmodel);
	
		break;
	        case Q_OVERWRITE_FILEOUTEDI14:
	            copy_fileoutedi14();
	        break;
	        case Q_OVERWRITE_COPY_MODEL:
	            system(COPY_MODELLO);
	        break;
	        case SAVE_FORAUS:
	           save_foraus(SAVE_FORAUS);
	           close_interface(wchiamante);
	        break; 
	        case REMOVE_FORAUS:
	           rimuovi_moduli_foraus(wchiamante); 
	        break;
	        case DELETE_FORAUS:
	            delete_foraus(wchiamante);  
	        break;
		}
	UxDestroyInterface(UxWidget);
	}
	UxQuestion_operationContext = UxSaveCtx;
}

static void	cancelCB_question_operation( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestion_operation  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestion_operationContext;
	UxQuestion_operationContext = UxContext =
			(_UxCquestion_operation *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxQuestion_operationContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_question_operation()
{
	Widget	question_operation_shell;

	question_operation_shell = XtVaCreatePopupShell( "question_operation_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 300,
			XmNy, 350,
			XmNwidth, 260,
			XmNheight, 140,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "question_operation",
			NULL );

	question_operation = XtVaCreateWidget( "question_operation",
			xmMessageBoxWidgetClass, question_operation_shell,
			XmNmessageAlignment, XmALIGNMENT_CENTER,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNheight, 140,
			XmNwidth, 260,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( question_operation, (char *) UxQuestion_operationContext );

	XtAddCallback( question_operation, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxQuestion_operationContext );

	XtAddCallback( question_operation, XmNokCallback,
			okCallback_question_operation,
			(XtPointer) UxQuestion_operationContext );
	XtAddCallback( question_operation, XmNcancelCallback,
			cancelCB_question_operation,
			(XtPointer) UxQuestion_operationContext );



	return ( question_operation );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_question_operation( _Uxwgt_call, _Uxtip_q )
	swidget	_Uxwgt_call;
	int	_Uxtip_q;
{
	Widget                  rtrn;
	_UxCquestion_operation  *UxContext;

	UxQuestion_operationContext = UxContext =
		(_UxCquestion_operation *) XtMalloc( sizeof(_UxCquestion_operation) );

	wgt_call = _Uxwgt_call;
	tip_q = _Uxtip_q;
	{
		char *nome_ret;
		
		wchiamante = wgt_call;
		
		printf("ricevo il parametro %d\n",tip_q);
		if(tip_q == Q_DELETE_MODEL)
		{
		strcpy(pathmodel,path_legocad);
		strcat(pathmodel,"/");
		
		nome_ret = get_select_model_new();
		if( (nome_ret == NULL) || (!strlen(nome_ret)) )
		{
		   create_vis_msg("Invalid model name selected");
		   return(0);
		}
		 
		strcat(pathmodel,get_select_model_new());
		}
		rtrn = _Uxbuild_question_operation();

		switch( tip_q )
		{
		   case Q_DELETE_MODEL:
		
		   strcpy(appo,"Do You Really Want Delete ");	
		   sprintf(&appo[strlen(appo)],"%s ?\n",
		                pathmodel);
		   break;
		   case Q_OVERWRITE_FILEOUTEDI14:
		
		   strcpy(appo,"Proposed File Already Exist. Do You Want Overwrite? ");	
		   break;
		   case Q_OVERWRITE_COPY_MODEL:
		
		   strcpy(appo,"Proposed Model Already Exist or Already Used. Do You Want Overwrite? ");	
		   break;
		   case SAVE_FORAUS:
		   strcpy(appo,"Do You Want Overwrite foraus.for? ");	
		   break;
		   case REMOVE_FORAUS:
		   strcpy(appo,"Do You Want delete selected foraus section? ");	
		   break; 
		   case DELETE_FORAUS:
		   strcpy(appo,"Do You Want delete auxiliary fortran file foraus.for? ");	
		   break;
		   default:
		   strcpy(appo,"?? No Message is Set for This Interface ??");
		   break;
		}
		
		UxPutMessageString(rtrn,appo);
		
		XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));
		UxPopupInterface(rtrn, no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_question_operation( _Uxwgt_call, _Uxtip_q )
	swidget	_Uxwgt_call;
	int	_Uxtip_q;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_question_operation( _Uxwgt_call, _Uxtip_q );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

