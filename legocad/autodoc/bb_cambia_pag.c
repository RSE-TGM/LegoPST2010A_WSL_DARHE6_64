
/*******************************************************************************
	bb_cambia_pag.c
	(Generated from interface file bb_cambia_pag.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/BulletinB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo bb_cambia_pag.i
   tipo 
   release 1.10
   data 3/31/95
   reserved @(#)bb_cambia_pag.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


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
	Widget	Uxbb_cambia_pag;
	Widget	Uxlabel8;
	Widget	Uxtext_page_no;
	Widget	Uxseparator1;
	Widget	UxpushButton11;
	FILE	*Uxfp;
	int	Uxmax_righe_d;
	swidget	Uxtext_doc;
	swidget	Uxlabel_pag;
	long	*Uxoffs;
	int	*Uxnum_pag;
	int	Uxpagina_ini;
} _UxCbb_cambia_pag;

#define bb_cambia_pag           UxBb_cambia_pagContext->Uxbb_cambia_pag
#define label8                  UxBb_cambia_pagContext->Uxlabel8
#define text_page_no            UxBb_cambia_pagContext->Uxtext_page_no
#define separator1              UxBb_cambia_pagContext->Uxseparator1
#define pushButton11            UxBb_cambia_pagContext->UxpushButton11
#define fp                      UxBb_cambia_pagContext->Uxfp
#define max_righe_d             UxBb_cambia_pagContext->Uxmax_righe_d
#define text_doc                UxBb_cambia_pagContext->Uxtext_doc
#define label_pag               UxBb_cambia_pagContext->Uxlabel_pag
#define offs                    UxBb_cambia_pagContext->Uxoffs
#define num_pag                 UxBb_cambia_pagContext->Uxnum_pag
#define pagina_ini              UxBb_cambia_pagContext->Uxpagina_ini

static _UxCbb_cambia_pag	*UxBb_cambia_pagContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_bb_cambia_pag();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton11( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_cambia_pag       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_cambia_pagContext;
	UxBb_cambia_pagContext = UxContext =
			(_UxCbb_cambia_pag *) UxGetContext( UxWidget );
	{
	char *str, buf[20];
	int num;
	long temp_offs;
	
	str = XmTextGetString(UxGetWidget(text_page_no));
	if (str != NULL)
	{
	   sscanf(str,"%d", &num);
	   free(str);
	   if (num == -1)
	      return;
	}
	else
	{
	   crea_errorDialog("Missing page number...");
	   return;
	}
	
	if (num-pagina_ini <= 0)
	   return;
	
	printf("vai alla pagina %d\n", num-pagina_ini);
	
	if ((temp_offs = vai_alla_pagina(fp, max_righe_d, num-pagina_ini)) == -1)
	{
	   crea_errorDialog("Page not found!");
	   return;
	}
	
	*num_pag = num;
	*offs = temp_offs;
	
	str = leggi_pagina(fp, max_righe_d);
	XmTextSetString(UxGetWidget(text_doc), str);
	free(str);
	
	sprintf(buf, "%d", *num_pag);
	set_label(UxGetWidget(label_pag), buf);
	
	UxDestroySwidget(bb_cambia_pag);
	}
	UxBb_cambia_pagContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_bb_cambia_pag()
{
	Widget	bb_cambia_pag_shell;

	bb_cambia_pag_shell = XtVaCreatePopupShell( "bb_cambia_pag_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 270,
			XmNy, 680,
			XmNwidth, 310,
			XmNheight, 180,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "bb_cambia_pag",
			NULL );

	bb_cambia_pag = XtVaCreateWidget( "bb_cambia_pag",
			xmBulletinBoardWidgetClass, bb_cambia_pag_shell,
			XmNnoResize, TRUE,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNdialogTitle, "CHANGE PAGE" ),
			XmNheight, 180,
			XmNwidth, 310,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( bb_cambia_pag, (char *) UxBb_cambia_pagContext );

	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass, bb_cambia_pag,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNlabelString, "Go to page:" ),
			XmNheight, 34,
			XmNwidth, 130,
			XmNy, 10,
			XmNx, 20,
			NULL );

	UxPutContext( label8, (char *) UxBb_cambia_pagContext );

	text_page_no = XtVaCreateManagedWidget( "text_page_no",
			xmTextWidgetClass, bb_cambia_pag,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 100,
			XmNy, 10,
			XmNx, 160,
			NULL );

	UxPutContext( text_page_no, (char *) UxBb_cambia_pagContext );

	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass, bb_cambia_pag,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 10,
			XmNwidth, 300,
			XmNy, 50,
			XmNx, -10,
			NULL );

	UxPutContext( separator1, (char *) UxBb_cambia_pagContext );

	pushButton11 = XtVaCreateManagedWidget( "pushButton11",
			xmPushButtonWidgetClass, bb_cambia_pag,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 34,
			XmNwidth, 140,
			XmNy, 70,
			XmNx, 80,
			NULL );

	UxPutContext( pushButton11, (char *) UxBb_cambia_pagContext );

	XtAddCallback( bb_cambia_pag, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxBb_cambia_pagContext );

	XtAddCallback( pushButton11, XmNactivateCallback,
			activateCB_pushButton11,
			(XtPointer) UxBb_cambia_pagContext );



	return ( bb_cambia_pag );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_bb_cambia_pag( _Uxfp, _Uxmax_righe_d, _Uxtext_doc, _Uxlabel_pag, _Uxoffs, _Uxnum_pag, _Uxpagina_ini )
	FILE	*_Uxfp;
	int	_Uxmax_righe_d;
	swidget	_Uxtext_doc;
	swidget	_Uxlabel_pag;
	long	*_Uxoffs;
	int	*_Uxnum_pag;
	int	_Uxpagina_ini;
{
	Widget                  rtrn;
	_UxCbb_cambia_pag       *UxContext;

	UxBb_cambia_pagContext = UxContext =
		(_UxCbb_cambia_pag *) XtMalloc( sizeof(_UxCbb_cambia_pag) );

	fp = _Uxfp;
	max_righe_d = _Uxmax_righe_d;
	text_doc = _Uxtext_doc;
	label_pag = _Uxlabel_pag;
	offs = _Uxoffs;
	num_pag = _Uxnum_pag;
	pagina_ini = _Uxpagina_ini;
	{
		char buf[20];
		rtrn = _Uxbuild_bb_cambia_pag();

		sprintf(buf,"%d",*num_pag);
		XmTextSetString(UxGetWidget(text_page_no), buf);
		
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

Widget	create_bb_cambia_pag( _Uxfp, _Uxmax_righe_d, _Uxtext_doc, _Uxlabel_pag, _Uxoffs, _Uxnum_pag, _Uxpagina_ini )
	FILE	*_Uxfp;
	int	_Uxmax_righe_d;
	swidget	_Uxtext_doc;
	swidget	_Uxlabel_pag;
	long	*_Uxoffs;
	int	*_Uxnum_pag;
	int	_Uxpagina_ini;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_bb_cambia_pag( _Uxfp, _Uxmax_righe_d, _Uxtext_doc, _Uxlabel_pag, _Uxoffs, _Uxnum_pag, _Uxpagina_ini );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

