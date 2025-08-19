
/*******************************************************************************
	EditDescrDialog1.c
	(Generated from interface file EditDescrDialog1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/SelectioB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo EditDescrDialog1.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)EditDescrDialog1.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

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
	Widget	Uxform1;
	Widget	Uxlabel1;
} _UxCEditDescrDialog1;

#define form1                   UxEditDescrDialog1Context->Uxform1
#define label1                  UxEditDescrDialog1Context->Uxlabel1

static _UxCEditDescrDialog1	*UxEditDescrDialog1Context;

Widget	EditDescrDialog1;
Widget	BlocName;
Widget	ModuleName;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_EditDescrDialog1();
int tomaius(char*);

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_EditDescrDialog1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEditDescrDialog1    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEditDescrDialog1Context;
	UxEditDescrDialog1Context = UxContext =
			(_UxCEditDescrDialog1 *) UxGetContext( UxWidget );
	{
	extern void set_new_descr(); 
	
	char descr[100],bname[10];
	
	strcpy(descr,UxGetTextString(UxWidget));
	strcpy(bname,UxGetText(BlocName));
	tomaius(bname);
	if( strcmp(bname,"") )
	{
	   strncat(bname,"    ",(4-strlen(bname)) );
	   printf("blocco %s descrizione  %s\n",bname,descr);
	   set_new_descr(bname,descr);
	}
	else
	   printf("Operazione Errata -> Nome Blocco nullo %s \n",bname);
	}
	UxEditDescrDialog1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_EditDescrDialog1()
{
	Widget	EditDescrDialog1_shell;

	EditDescrDialog1_shell = XtVaCreatePopupShell( "EditDescrDialog1_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 409,
			XmNy, 319,
			XmNwidth, 440,
			XmNheight, 226,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "EditDescrDialog1",
			NULL );

	EditDescrDialog1 = XtVaCreateWidget( "EditDescrDialog1",
			xmSelectionBoxWidgetClass, EditDescrDialog1_shell,
			XmNshadowType, XmSHADOW_IN,
			XmNtextColumns, 50,
			RES_CONVERT( XmNselectionLabelString, "" ),
			RES_CONVERT( XmNdialogTitle, "Edit Description" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNheight, 226,
			XmNwidth, 440,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_PROMPT,
			NULL );

	UxPutContext( EditDescrDialog1, (char *) UxEditDescrDialog1Context );

	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass, EditDescrDialog1,
			XmNheight, 32,
			XmNwidth, 424,
			XmNy, 20,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form1, (char *) UxEditDescrDialog1Context );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "Nome Blocco" ),
			XmNheight, 30,
			XmNwidth, 90,
			XmNy, 0,
			XmNx, 0,
			NULL );

	UxPutContext( label1, (char *) UxEditDescrDialog1Context );

	BlocName = XtVaCreateManagedWidget( "BlocName",
			xmTextFieldWidgetClass, form1,
			XmNmaxLength, 4,
			XmNcolumns, 4,
			RES_CONVERT( XmNhighlightColor, "#7E88AB" ),
			XmNeditable, TRUE,
			XmNheight, 30,
			XmNwidth, 70,
			XmNy, 0,
			XmNx, 160,
			NULL );

	UxPutContext( BlocName, (char *) UxEditDescrDialog1Context );

	ModuleName = XtVaCreateManagedWidget( "ModuleName",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "ModField" ),
			XmNheight, 30,
			XmNwidth, 60,
			XmNy, 0,
			XmNx, 100,
			NULL );

	UxPutContext( ModuleName, (char *) UxEditDescrDialog1Context );

	XtAddCallback( EditDescrDialog1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxEditDescrDialog1Context );

	XtAddCallback( EditDescrDialog1, XmNokCallback,
			okCallback_EditDescrDialog1,
			(XtPointer) UxEditDescrDialog1Context );



	return ( EditDescrDialog1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_EditDescrDialog1()
{
	Widget                  rtrn;
	_UxCEditDescrDialog1    *UxContext;

	UxEditDescrDialog1Context = UxContext =
		(_UxCEditDescrDialog1 *) XtMalloc( sizeof(_UxCEditDescrDialog1) );

	{
		Widget wdescr;
		Arg arg[3];
		Cardinal narg;
		rtrn = _Uxbuild_EditDescrDialog1();

		/* limito la length della descrizione a 55 char */
		wdescr = XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);
		
		narg = 0;
		XtSetArg(arg[narg],XmNcolumns,50);narg++;
		XtSetArg(arg[narg],XmNmaxLength, 50);narg++;
		XtSetValues(wdescr,arg,narg);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_EditDescrDialog1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_EditDescrDialog1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

