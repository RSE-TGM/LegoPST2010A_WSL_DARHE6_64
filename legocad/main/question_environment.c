
/*******************************************************************************
	question_environment.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/* Missing function declarations */
extern int testa_ambiente();

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo question_environment.i
   tipo 
   release 2.25
   data 5/12/95
   reserved @(#)question_environment.i	2.25
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
extern char path_legocad[FILENAME_MAX]; /* path_name che individua la sottodirectory
                           legocad per l'utente */
extern char path_libut[FILENAME_MAX];  /* path_name che individua la libreria dei moduli
			  di processo */
extern char path_libreg[FILENAME_MAX]; /* path_name che individua la libreria dei moduli
                             di regolazione */

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
	Widget	Uxquestion_environment;
	unsigned char	Uxapp[300];
	int	Uxtipo_q;
} _UxCquestion_environment;

#define question_environment    UxQuestion_environmentContext->Uxquestion_environment
#define app                     UxQuestion_environmentContext->Uxapp
#define tipo_q                  UxQuestion_environmentContext->Uxtipo_q

static _UxCquestion_environment	*UxQuestion_environmentContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_question_environment();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_question_environment( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestion_environment *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestion_environmentContext;
	UxQuestion_environmentContext = UxContext =
			(_UxCquestion_environment *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	switch(tipo_q)
		{
		case K_CREATE_LEGOCAD_ENV:
		break;
		case K_COPY_LEGOCAD_LIBUT:
		break;
		case K_COPY_LEGOCAD_LIBREG:
		break;
		}
	}
	UxQuestion_environmentContext = UxSaveCtx;
}

static void	cancelCB_question_environment( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestion_environment *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestion_environmentContext;
	UxQuestion_environmentContext = UxContext =
			(_UxCquestion_environment *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxQuestion_environmentContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_question_environment()
{
	Widget	question_environment_shell;

	question_environment_shell = XtVaCreatePopupShell( "question_environment_shell",
			xmDialogShellWidgetClass, applicationShell1,
			XmNx, 340,
			XmNy, 355,
			XmNwidth, 325,
			XmNheight, 150,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "question_environment",
			NULL );

	question_environment = XtVaCreateWidget( "question_environment",
			xmMessageBoxWidgetClass, question_environment_shell,
			XmNmessageAlignment, XmALIGNMENT_BEGINNING,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNheight, 150,
			XmNwidth, 325,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( question_environment, (char *) UxQuestion_environmentContext );

	XtAddCallback( question_environment, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxQuestion_environmentContext );

	XtAddCallback( question_environment, XmNokCallback,
			okCallback_question_environment,
			(XtPointer) 0x0 );
	XtAddCallback( question_environment, XmNcancelCallback,
			cancelCB_question_environment,
			(XtPointer) UxQuestion_environmentContext );



	return ( question_environment );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_question_environment( _Uxtipo_q )
	int	_Uxtipo_q;
{
	Widget                  rtrn;
	_UxCquestion_environment *UxContext;

	UxQuestion_environmentContext = UxContext =
		(_UxCquestion_environment *) XtMalloc( sizeof(_UxCquestion_environment) );

	tipo_q = _Uxtipo_q;
	rtrn = _Uxbuild_question_environment();

	app[0]=0;
	if(testa_ambiente()) /* True se librerie presenti */
			{
			strcpy (app,"LEGOCAD ENVIRONMENT IS PROPERLY CONFIGURED:\n\
CREATION OF NEW LEGOCAD ENVIRONMENT\n\
MAY CAUSE MODIFICATION IN PREEXISTENT MODELS !!!\n\n");
			}
	strcat(app,"Operations Requested:\n");	
	if(tipo_q & K_COPY_LEGOCAD_LIBUT)
		sprintf(&app[strlen(app)],"Copy Defaults Modules Library in %s \n",
	                path_libut);
	if(tipo_q & K_COPY_LEGOCAD_LIBREG)
		sprintf(&app[strlen(app)],"Copy Defaults Control Modules Library in %s \n",
			path_libreg);
	if(tipo_q & K_CREATE_LEGOCAD_LIBUT)
		strcat(app,"Create Modules Library\n");
	if(tipo_q & K_CREATE_LEGOCAD_LIBREG)
		strcat(app,"Create Modules Library");
	UxPutMessageString(rtrn,app);
	
	XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));
	UxPopupInterface(rtrn, no_grab);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_question_environment( _Uxtipo_q )
	int	_Uxtipo_q;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_question_environment( _Uxtipo_q );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

