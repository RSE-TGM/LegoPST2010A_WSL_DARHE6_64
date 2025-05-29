
/*******************************************************************************
	bb_conferma_print.c
	(Generated from interface file bb_conferma_print.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/PushB.h>
#include <Xm/SeparatoG.h>
#include <Xm/ToggleB.h>
#include <Xm/LabelG.h>
#include <Xm/BulletinB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo bb_conferma_print.i
   tipo 
   release 1.11
   data 3/31/95
   reserved @(#)bb_conferma_print.i	1.11
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "autodoc.h"

int copia_file(char*, char*);

#define TOGGLE_ALL_PAGES	0
#define TOGGLE_DA_PAGE_A_PAGE	1
#define TOGGLE_CURRENT_PAGE	2

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
	Widget	Uxbb_conferma_print;
	Widget	UxlabelGadget7;
	Widget	Uxtoggle_all;
	Widget	Uxtoggle_da_a;
	Widget	Uxtoggle_current;
	Widget	UxlabelGadget8;
	Widget	UxlabelGadget9;
	Widget	UxlabelGadget10;
	Widget	UxlabelGadget11;
	Widget	UxseparatorGadget8;
	Widget	Uxpushb_print_ok;
	Widget	UxpushButton9;
	Widget	Uxtext_da;
	Widget	Uxtext_a;
	Widget	UxseparatorGadget9;
	unsigned char	Uxtoggle_selezionato;
	swidget	Uxswdg_toggle;
	unsigned char	*Uxnome_file;
	int	Uxcurrent_page;
	int	Uxlinee_per_pag;
	int	Uxlen_riga;
	int	Uxpag_iniz;
} _UxCbb_conferma_print;

#define bb_conferma_print       UxBb_conferma_printContext->Uxbb_conferma_print
#define labelGadget7            UxBb_conferma_printContext->UxlabelGadget7
#define toggle_all              UxBb_conferma_printContext->Uxtoggle_all
#define toggle_da_a             UxBb_conferma_printContext->Uxtoggle_da_a
#define toggle_current          UxBb_conferma_printContext->Uxtoggle_current
#define labelGadget8            UxBb_conferma_printContext->UxlabelGadget8
#define labelGadget9            UxBb_conferma_printContext->UxlabelGadget9
#define labelGadget10           UxBb_conferma_printContext->UxlabelGadget10
#define labelGadget11           UxBb_conferma_printContext->UxlabelGadget11
#define separatorGadget8        UxBb_conferma_printContext->UxseparatorGadget8
#define pushb_print_ok          UxBb_conferma_printContext->Uxpushb_print_ok
#define pushButton9             UxBb_conferma_printContext->UxpushButton9
#define text_da                 UxBb_conferma_printContext->Uxtext_da
#define text_a                  UxBb_conferma_printContext->Uxtext_a
#define separatorGadget9        UxBb_conferma_printContext->UxseparatorGadget9
#define toggle_selezionato      UxBb_conferma_printContext->Uxtoggle_selezionato
#define swdg_toggle             UxBb_conferma_printContext->Uxswdg_toggle
#define nome_file               UxBb_conferma_printContext->Uxnome_file
#define current_page            UxBb_conferma_printContext->Uxcurrent_page
#define linee_per_pag           UxBb_conferma_printContext->Uxlinee_per_pag
#define len_riga                UxBb_conferma_printContext->Uxlen_riga
#define pag_iniz                UxBb_conferma_printContext->Uxpag_iniz

static _UxCbb_conferma_print	*UxBb_conferma_printContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_bb_conferma_print();

Widget	crea_errorDialog( unsigned char	* );


/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	valueChangedCB_toggle_all( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_conferma_print   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_conferma_printContext;
	UxBb_conferma_printContext = UxContext =
			(_UxCbb_conferma_print *) UxGetContext( UxWidget );
	{
	if (toggle_selezionato == TOGGLE_ALL_PAGES)
	   XmToggleButtonSetState(UxGetWidget(toggle_all), True, False);
	else
	   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);
	toggle_selezionato = TOGGLE_ALL_PAGES;
	swdg_toggle = toggle_all;
	}
	UxBb_conferma_printContext = UxSaveCtx;
}

static void	valueChangedCB_toggle_da_a( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_conferma_print   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_conferma_printContext;
	UxBb_conferma_printContext = UxContext =
			(_UxCbb_conferma_print *) UxGetContext( UxWidget );
	{
	if (toggle_selezionato == TOGGLE_DA_PAGE_A_PAGE)
	   XmToggleButtonSetState(UxGetWidget(toggle_da_a), True, False);
	else
	   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);
	toggle_selezionato = TOGGLE_DA_PAGE_A_PAGE;
	swdg_toggle = toggle_da_a;
	
	}
	UxBb_conferma_printContext = UxSaveCtx;
}

static void	valueChangedCB_toggle_current( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_conferma_print   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_conferma_printContext;
	UxBb_conferma_printContext = UxContext =
			(_UxCbb_conferma_print *) UxGetContext( UxWidget );
	{
	if (toggle_selezionato == TOGGLE_CURRENT_PAGE)
	   XmToggleButtonSetState(UxGetWidget(toggle_current), True, False);
	else
	   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);
	toggle_selezionato = TOGGLE_CURRENT_PAGE;
	swdg_toggle = toggle_current;
	
	}
	UxBb_conferma_printContext = UxSaveCtx;
}

static void	activateCB_pushb_print_ok( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_conferma_print   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_conferma_printContext;
	UxBb_conferma_printContext = UxContext =
			(_UxCbb_conferma_print *) UxGetContext( UxWidget );
	{
	FILE *fp, *fp_temp;
	char *str, file_temp[256], comando[128];
	Boolean flag_stampa = True;
	int i, pag1, pag2;
	
	/***
	tmpnam(file_temp);
	***/
	strcpy(file_temp, "file_stampa");
	
	if ((fp_temp = fopen(file_temp, "w+")) == NULL)
	{
	    crea_errorDialog("Can't open temporary file for printing.\n");
	    XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));
	    return;
	}
	
	switch (toggle_selezionato)
	{
	    case TOGGLE_ALL_PAGES:
	       copia_file(nome_file, file_temp);
	       break;
	
	    case TOGGLE_DA_PAGE_A_PAGE:
	       if ((fp = fopen(nome_file, "r")) == NULL)
	       {
	          crea_errorDialog("Can't open file for printing.");
	          flag_stampa = False;
	          break;
	       }
	
	       str = XmTextGetString(UxGetWidget(text_da));
	       if (!IsNumeric(str) || Empty(str))
	       {
	          crea_errorDialog("Incorrect page number!\n");
	          flag_stampa = False;
	          break;
	       }
	       sscanf(str, "%d", &pag1);
	       XtFree(str);
	
	       str = XmTextGetString(UxGetWidget(text_a));
	       if (!IsNumeric(str) || Empty(str))
	       {
	          crea_errorDialog("Incorrect page number!\n");
	          flag_stampa = False;
	          break;
	       }
	       sscanf(str, "%d", &pag2);
	       XtFree(str);
	
	       if (vai_alla_pagina(fp, linee_per_pag, pag1-pag_iniz) == -1)
	          break;
	
	       for ( i=pag1 ; i<=pag2 ; i++ )
	          if ((str = leggi_pagina(fp, linee_per_pag)) == NULL)
	             break;
	          else
	          {
	             fputs(str, fp_temp);
	             free(str);
	          }
	
	       fclose(fp);
	       break;
	
	    case TOGGLE_CURRENT_PAGE:
	       if ((fp = fopen(nome_file, "r")) == NULL)
	       {
	          crea_errorDialog("Can't open file for printing.");
	          flag_stampa = False;
	       }
	
	       if (vai_alla_pagina(fp, linee_per_pag, current_page-pag_iniz) == -1)
	          break;
	
	       if ((str = leggi_pagina(fp, linee_per_pag)) != NULL)
	       {
	             fputs(str, fp_temp);
	             free(str);
	       }
	
	       fclose(fp);
	       break;
	}
	
	fclose(fp_temp);
	
#if defined OSF1 || defined LINUX
	   sprintf(comando, "lpr -w%d -z%d -Oz%s  %s", len_riga, linee_per_pag,
	                          (len_riga > 80) ? "landscape" : "portrait",file_temp);
#else
	   sprintf(comando, "qprt -w%d -l%d -z%s -r %s", len_riga, linee_per_pag,
	                          (len_riga > 80) ? "1" : "0", file_temp);
#endif
	
	printf("comando di stampa: %s\n", comando);
	
	system(comando);
	
	
	XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));
	}
	UxBb_conferma_printContext = UxSaveCtx;
}

static void	activateCB_pushButton9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCbb_conferma_print   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBb_conferma_printContext;
	UxBb_conferma_printContext = UxContext =
			(_UxCbb_conferma_print *) UxGetContext( UxWidget );
	{
	XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));
	}
	UxBb_conferma_printContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_bb_conferma_print()
{
	Widget	bb_conferma_print_shell;

	bb_conferma_print_shell = XtVaCreatePopupShell( "bb_conferma_print_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 465,
			XmNy, 340,
			XmNwidth, 431,
			XmNheight, 286,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "bb_conferma_print",
			NULL );

	bb_conferma_print = XtVaCreateWidget( "bb_conferma_print",
			xmBulletinBoardWidgetClass, bb_conferma_print_shell,
			XmNautoUnmanage, FALSE,
			XmNnoResize, TRUE,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNlabelFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			XmNbuttonFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNdialogTitle, "PRINT DOCUMENTATION" ),
			XmNheight, 286,
			XmNwidth, 431,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( bb_conferma_print, (char *) UxBb_conferma_printContext );

	labelGadget7 = XtVaCreateManagedWidget( "labelGadget7",
			xmLabelGadgetClass, bb_conferma_print,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "SELECT:" ),
			XmNheight, 30,
			XmNwidth, 150,
			XmNy, 10,
			XmNx, 20,
			NULL );

	UxPutContext( labelGadget7, (char *) UxBb_conferma_printContext );

	toggle_all = XtVaCreateManagedWidget( "toggle_all",
			xmToggleButtonWidgetClass, bb_conferma_print,
			XmNset, TRUE,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 20,
			XmNy, 60,
			XmNx, 70,
			NULL );

	UxPutContext( toggle_all, (char *) UxBb_conferma_printContext );

	toggle_da_a = XtVaCreateManagedWidget( "toggle_da_a",
			xmToggleButtonWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 20,
			XmNy, 100,
			XmNx, 70,
			NULL );

	UxPutContext( toggle_da_a, (char *) UxBb_conferma_printContext );

	toggle_current = XtVaCreateManagedWidget( "toggle_current",
			xmToggleButtonWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 20,
			XmNy, 140,
			XmNx, 70,
			NULL );

	UxPutContext( toggle_current, (char *) UxBb_conferma_printContext );

	labelGadget8 = XtVaCreateManagedWidget( "labelGadget8",
			xmLabelGadgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "All Pages" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 34,
			XmNwidth, 130,
			XmNy, 60,
			XmNx, 110,
			NULL );

	UxPutContext( labelGadget8, (char *) UxBb_conferma_printContext );

	labelGadget9 = XtVaCreateManagedWidget( "labelGadget9",
			xmLabelGadgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "From Page:" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 34,
			XmNwidth, 90,
			XmNy, 100,
			XmNx, 110,
			NULL );

	UxPutContext( labelGadget9, (char *) UxBb_conferma_printContext );

	labelGadget10 = XtVaCreateManagedWidget( "labelGadget10",
			xmLabelGadgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "to :" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 34,
			XmNwidth, 40,
			XmNy, 100,
			XmNx, 280,
			NULL );

	UxPutContext( labelGadget10, (char *) UxBb_conferma_printContext );

	labelGadget11 = XtVaCreateManagedWidget( "labelGadget11",
			xmLabelGadgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "Current Page" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 34,
			XmNwidth, 100,
			XmNy, 140,
			XmNx, 110,
			NULL );

	UxPutContext( labelGadget11, (char *) UxBb_conferma_printContext );

	separatorGadget8 = XtVaCreateManagedWidget( "separatorGadget8",
			xmSeparatorGadgetClass, bb_conferma_print,
			XmNheight, 10,
			XmNwidth, 410,
			XmNy, 180,
			XmNx, 10,
			NULL );

	UxPutContext( separatorGadget8, (char *) UxBb_conferma_printContext );

	pushb_print_ok = XtVaCreateManagedWidget( "pushb_print_ok",
			xmPushButtonWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "Ok" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 160,
			XmNy, 210,
			XmNx, 10,
			NULL );

	UxPutContext( pushb_print_ok, (char *) UxBb_conferma_printContext );

	pushButton9 = XtVaCreateManagedWidget( "pushButton9",
			xmPushButtonWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 160,
			XmNy, 210,
			XmNx, 260,
			NULL );

	UxPutContext( pushButton9, (char *) UxBb_conferma_printContext );

	text_da = XtVaCreateManagedWidget( "text_da",
			xmTextWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 60,
			XmNy, 100,
			XmNx, 210,
			NULL );

	UxPutContext( text_da, (char *) UxBb_conferma_printContext );

	text_a = XtVaCreateManagedWidget( "text_a",
			xmTextWidgetClass, bb_conferma_print,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 60,
			XmNy, 100,
			XmNx, 320,
			NULL );

	UxPutContext( text_a, (char *) UxBb_conferma_printContext );

	separatorGadget9 = XtVaCreateManagedWidget( "separatorGadget9",
			xmSeparatorGadgetClass, bb_conferma_print,
			XmNheight, 10,
			XmNwidth, 410,
			XmNy, 40,
			XmNx, 10,
			NULL );

	UxPutContext( separatorGadget9, (char *) UxBb_conferma_printContext );

	XtAddCallback( bb_conferma_print, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxBb_conferma_printContext );

	XtAddCallback( toggle_all, XmNvalueChangedCallback,
			valueChangedCB_toggle_all,
			(XtPointer) UxBb_conferma_printContext );

	XtAddCallback( toggle_da_a, XmNvalueChangedCallback,
			valueChangedCB_toggle_da_a,
			(XtPointer) UxBb_conferma_printContext );

	XtAddCallback( toggle_current, XmNvalueChangedCallback,
			valueChangedCB_toggle_current,
			(XtPointer) UxBb_conferma_printContext );

	XtAddCallback( pushb_print_ok, XmNactivateCallback,
			activateCB_pushb_print_ok,
			(XtPointer) UxBb_conferma_printContext );

	XtAddCallback( pushButton9, XmNactivateCallback,
			activateCB_pushButton9,
			(XtPointer) UxBb_conferma_printContext );



	return ( bb_conferma_print );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_bb_conferma_print( _Uxnome_file, _Uxcurrent_page, _Uxlinee_per_pag, _Uxlen_riga, _Uxpag_iniz )
	unsigned char	*_Uxnome_file;
	int	_Uxcurrent_page;
	int	_Uxlinee_per_pag;
	int	_Uxlen_riga;
	int	_Uxpag_iniz;
{
	Widget                  rtrn;
	_UxCbb_conferma_print   *UxContext;

	UxBb_conferma_printContext = UxContext =
		(_UxCbb_conferma_print *) XtMalloc( sizeof(_UxCbb_conferma_print) );

	nome_file = _Uxnome_file;
	current_page = _Uxcurrent_page;
	linee_per_pag = _Uxlinee_per_pag;
	len_riga = _Uxlen_riga;
	pag_iniz = _Uxpag_iniz;
	rtrn = _Uxbuild_bb_conferma_print();

	toggle_selezionato = TOGGLE_ALL_PAGES;
	swdg_toggle = toggle_all;
	UxPopupInterface(rtrn, no_grab);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_bb_conferma_print( _Uxnome_file, _Uxcurrent_page, _Uxlinee_per_pag, _Uxlen_riga, _Uxpag_iniz )
	unsigned char	*_Uxnome_file;
	int	_Uxcurrent_page;
	int	_Uxlinee_per_pag;
	int	_Uxlen_riga;
	int	_Uxpag_iniz;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_bb_conferma_print( _Uxnome_file, _Uxcurrent_page, _Uxlinee_per_pag, _Uxlen_riga, _Uxpag_iniz );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

