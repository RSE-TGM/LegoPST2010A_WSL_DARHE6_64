
/*******************************************************************************
	edi14FileSelection.c
	(Generated from interface file edi14FileSelection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>

/* Missing function declarations */
extern swidget create_vis_msg(char *);

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo edi14FileSelection.i
   tipo 
   release 1.21
   data 5/12/95
   reserved @(#)edi14FileSelection.i	1.21
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#ifndef DESIGN_TIME
#include <stdlib.h>
#endif
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
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
	Widget	Uxedi14FileSelection;
	unsigned char	Uxinput_file[256];
	unsigned char	Uxoutput_file[256];
	unsigned char	Uxpattern[256];
	int	Uxtipo_oper;
} _UxCedi14FileSelection;

#define edi14FileSelection      UxEdi14FileSelectionContext->Uxedi14FileSelection
#define input_file              UxEdi14FileSelectionContext->Uxinput_file
#define output_file             UxEdi14FileSelectionContext->Uxoutput_file
#define pattern                 UxEdi14FileSelectionContext->Uxpattern
#define tipo_oper               UxEdi14FileSelectionContext->Uxtipo_oper

static _UxCedi14FileSelection	*UxEdi14FileSelectionContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_edi14FileSelection();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

int fine_edi14c()
{
   create_vis_msg("edi14c Completed");
   
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_edi14FileSelection( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCedi14FileSelection  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdi14FileSelectionContext;
	UxEdi14FileSelectionContext = UxContext =
			(_UxCedi14FileSelection *) UxGetContext( UxWidget );
	{
	char fileselected[256],comando[256];
	FILE *fp;
	char *nomeappo = {"uscita.tmp"};
	
	strcpy(input_file,UxGetTextString(edi14FileSelection));
	
	printf("passo il parametro di input %s\n",input_file);
	
	/* 
	fileselected = strrchr(input_file,'/');
	fileselected += 1;
	*/
	strcpy(fileselected,input_file);
	
	if( *fileselected == 0)
	{
	   create_vis_msg("Invalid Selection");
	   return;
	}
	
	printf("fileselecetd %s\n",fileselected);
	fp = fopen(nomeappo,"w");
	fprintf(fp,"%s\n",fileselected);
	fclose(fp);
	
	strcpy(comando,getenv("LEGO_BIN"));
	strcat(comando,"/edi14c < ");
	strcat(comando,nomeappo);
	strcat( comando," > output_edi14.out"); 
	
	system( comando );
	
	fine_edi14c();
	   
	}
	UxEdi14FileSelectionContext = UxSaveCtx;
}

static void	cancelCB_edi14FileSelection( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCedi14FileSelection  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEdi14FileSelectionContext;
	UxEdi14FileSelectionContext = UxContext =
			(_UxCedi14FileSelection *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	}
	UxEdi14FileSelectionContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_edi14FileSelection()
{
	Widget	edi14FileSelection_shell;

	edi14FileSelection_shell = XtVaCreatePopupShell( "edi14FileSelection_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 520,
			XmNy, 320,
			XmNwidth, 300,
			XmNheight, 330,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "edi14FileSelection",
			NULL );

	edi14FileSelection = XtVaCreateWidget( "edi14FileSelection",
			xmFileSelectionBoxWidgetClass, edi14FileSelection_shell,
			RES_CONVERT( XmNpattern, "*" ),
			XmNheight, 330,
			XmNwidth, 300,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( edi14FileSelection, (char *) UxEdi14FileSelectionContext );

	XtAddCallback( edi14FileSelection, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxEdi14FileSelectionContext );

	XtAddCallback( edi14FileSelection, XmNokCallback,
			okCallback_edi14FileSelection,
			(XtPointer) UxEdi14FileSelectionContext );
	XtAddCallback( edi14FileSelection, XmNcancelCallback,
			cancelCB_edi14FileSelection,
			(XtPointer) UxEdi14FileSelectionContext );



	return ( edi14FileSelection );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_edi14FileSelection( _Uxtipo_oper )
	int	_Uxtipo_oper;
{
	Widget                  rtrn;
	_UxCedi14FileSelection  *UxContext;

	UxEdi14FileSelectionContext = UxContext =
		(_UxCedi14FileSelection *) XtMalloc( sizeof(_UxCedi14FileSelection) );

	tipo_oper = _Uxtipo_oper;
	{
		Widget wid;
		Arg arg[5];
		Cardinal narg;
		XmString cstring;
		char filterstr[256];
		rtrn = _Uxbuild_edi14FileSelection();

		/* unmanage help button */
		wid = XmFileSelectionBoxGetChild(edi14FileSelection,XmDIALOG_HELP_BUTTON);
		XtUnmanageChild( wid );
		
		if( tipo_oper == EDI14_INPUT_SELECTION)
		{
		   /* recupero l'id widget del textfield di Filtro e lo setto come 'f14.*' */
		   wid = XmFileSelectionBoxGetChild(edi14FileSelection,XmDIALOG_FILTER_TEXT);
		
		   strcpy(pattern,XmTextGetString(wid));
		
		
		   strcpy( &(pattern[strlen(pattern)-1]) , "f14.*");
		
		
		/* effettuo la ricerca dei file f14.* */ 
		   cstring = XmStringCreateSimple(pattern);   
		   XmFileSelectionDoSearch(edi14FileSelection,cstring);
		
		   printf("setto la stringa di filtro a %s\n",pattern);
		   XmTextSetString(wid,pattern);
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

Widget	create_edi14FileSelection( _Uxtipo_oper )
	int	_Uxtipo_oper;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_edi14FileSelection( _Uxtipo_oper );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

