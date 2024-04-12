
/*******************************************************************************
	EditVarDescr.c
	(Generated from interface file EditVarDescr.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo EditVarDescr.i
   tipo 
   release 2.25
   data 5/10/95
   reserved @(#)EditVarDescr.i	2.25
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif
extern swidget fintavarWin;

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
	int	mumble;
} _UxCEditVarDescr;


static _UxCEditVarDescr	*UxEditVarDescrContext;

Widget	EditVarDescr;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_EditVarDescr();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_EditVarDescr( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCEditVarDescr        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEditVarDescrContext;
	UxEditVarDescrContext = UxContext =
			(_UxCEditVarDescr *) UxGetContext( UxWidget );
	{
	extern void set_new_var_descr();
	XtPointer *parametri;
	union {
	         short  ind_bloc_piu_var[2];
	         char come_char[4];
	         char *parametri;
	      } param_rec;
	
	char appo[100];
	
	param_rec.parametri = UxGetUserData(UxWidget);
	
	printf("ho ricevuto indice blocco = %d\n",param_rec.ind_bloc_piu_var[0]);
	printf("ho ricevuto indice variab = %d\n",param_rec.ind_bloc_piu_var[1]);
	
	strcpy( appo,UxGetTextString(UxWidget) );
	printf("stringa cambiata %s\n",appo);
	
	set_new_var_descr(XtParent(XtParent(UxWidget)),appo);
	UxDestroyInterface(UxWidget);
	}
	UxEditVarDescrContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_EditVarDescr()
{
	Widget	EditVarDescr_shell;

	EditVarDescr_shell = XtVaCreatePopupShell( "EditVarDescr_shell",
			xmDialogShellWidgetClass, fintavarWin,
			XmNx, 470,
			XmNy, 610,
			XmNwidth, 550,
			XmNheight, 150,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "EditVarDescr",
			NULL );

	EditVarDescr = XtVaCreateWidget( "EditVarDescr",
			xmSelectionBoxWidgetClass, EditVarDescr_shell,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNtextColumns, 55,
			RES_CONVERT( XmNselectionLabelString, "Descrizione Variabile" ),
			XmNheight, 150,
			XmNwidth, 550,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_PROMPT,
			NULL );

	UxPutContext( EditVarDescr, (char *) UxEditVarDescrContext );

	XtAddCallback( EditVarDescr, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxEditVarDescrContext );

	XtAddCallback( EditVarDescr, XmNokCallback,
			okCallback_EditVarDescr,
			(XtPointer) UxEditVarDescrContext );



	return ( EditVarDescr );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_EditVarDescr()
{
	Widget                  rtrn;
	_UxCEditVarDescr        *UxContext;

	UxEditVarDescrContext = UxContext =
		(_UxCEditVarDescr *) XtMalloc( sizeof(_UxCEditVarDescr) );

	{
		Widget wdescr;
		Arg arg[3];
		Cardinal narg;
		rtrn = _Uxbuild_EditVarDescr();

		/* limito la length della descrizione a 55 char */
		wdescr = XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);
		
		narg = 0;
		XtSetArg(arg[narg],XmNcolumns,55);narg++;
		XtSetArg(arg[narg],XmNmaxLength, 55);narg++;
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

Widget	create_EditVarDescr()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_EditVarDescr();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

