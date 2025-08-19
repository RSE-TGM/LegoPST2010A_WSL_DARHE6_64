
/*******************************************************************************
	selectionBoxDialog1.c
	(Generated from interface file selectionBoxDialog1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/* Missing function declarations */
extern void copy_file(char *, char *);
extern swidget create_vis_msg(char *);

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo selectionBoxDialog1.i
   tipo 
   release 1.21
   data 5/12/95
   reserved @(#)selectionBoxDialog1.i	1.21
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include "legomain.h"

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
	Widget	UxselectionBoxDialog1;
	unsigned char	Uxoutput_fil[256];
} _UxCselectionBoxDialog1;

#define selectionBoxDialog1     UxSelectionBoxDialog1Context->UxselectionBoxDialog1
#define output_fil              UxSelectionBoxDialog1Context->Uxoutput_fil

static _UxCselectionBoxDialog1	*UxSelectionBoxDialog1Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_selectionBoxDialog1();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

void copy_fileoutedi14()
{
   copy_file("edi14.out",output_fil);
  create_vis_msg("Result Copy File Terminated!");
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_selectionBoxDialog1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectionBoxDialog1 *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectionBoxDialog1Context;
	UxSelectionBoxDialog1Context = UxContext =
			(_UxCselectionBoxDialog1 *) UxGetContext( UxWidget );
	{
	extern swidget create_question_operation();
	char comando[256];
	char *fileselected; 
	FILE *fp;
	
	strcpy(output_fil,UxGetTextString(selectionBoxDialog1));
	
	printf("output_file = %s\n",output_fil);
	
	if( output_fil[0] == '\0')
	{
	   create_vis_msg("Invalid Selection");
	   return;
	}
	
	if( (fp = fopen(output_fil,"r")) != NULL)
	{
	   fclose(fp);
	   create_question_operation(UxWidget,Q_OVERWRITE_FILEOUTEDI14);
	}       
	else
	{
	   copy_fileoutedi14();
	}
	
	
	
	}
	UxSelectionBoxDialog1Context = UxSaveCtx;
}

static void	cancelCB_selectionBoxDialog1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectionBoxDialog1 *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectionBoxDialog1Context;
	UxSelectionBoxDialog1Context = UxContext =
			(_UxCselectionBoxDialog1 *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxSelectionBoxDialog1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_selectionBoxDialog1()
{
	Widget	selectionBoxDialog1_shell;

	selectionBoxDialog1_shell = XtVaCreatePopupShell( "selectionBoxDialog1_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 340,
			XmNy, 380,
			XmNwidth, 330,
			XmNheight, 370,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "selectionBoxDialog1",
			NULL );

	selectionBoxDialog1 = XtVaCreateWidget( "selectionBoxDialog1",
			xmSelectionBoxWidgetClass, selectionBoxDialog1_shell,
			RES_CONVERT( XmNselectionLabelString, "Save resutl edi14 on file..." ),
			XmNdialogType, XmDIALOG_ERROR,
			XmNheight, 370,
			XmNwidth, 330,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( selectionBoxDialog1, (char *) UxSelectionBoxDialog1Context );

	XtAddCallback( selectionBoxDialog1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxSelectionBoxDialog1Context );

	XtAddCallback( selectionBoxDialog1, XmNokCallback,
			okCallback_selectionBoxDialog1,
			(XtPointer) UxSelectionBoxDialog1Context );
	XtAddCallback( selectionBoxDialog1, XmNcancelCallback,
			cancelCB_selectionBoxDialog1,
			(XtPointer) UxSelectionBoxDialog1Context );



	return ( selectionBoxDialog1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_selectionBoxDialog1()
{
	Widget                  rtrn;
	_UxCselectionBoxDialog1 *UxContext;

	UxSelectionBoxDialog1Context = UxContext =
		(_UxCselectionBoxDialog1 *) XtMalloc( sizeof(_UxCselectionBoxDialog1) );

	rtrn = _Uxbuild_selectionBoxDialog1();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_selectionBoxDialog1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_selectionBoxDialog1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

