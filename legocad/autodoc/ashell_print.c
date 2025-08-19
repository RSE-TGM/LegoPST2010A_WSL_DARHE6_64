
/*******************************************************************************
	ashell_print.c
	(Generated from interface file ashell_print.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/ArrowB.h>
#include <Xm/LabelG.h>
#include <Xm/Frame.h>
#include <Xm/SeparatoG.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo ashell_print.i
   tipo 
   release 1.11
   data 3/31/95
   reserved @(#)ashell_print.i	1.11
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


#include "autodoc.h"

#define DOCUMENTAZIONE	0
#define INDICE		1

/************************************************************************/
/* VARIABILI GLOBALI ESTERNE						*/
/************************************************************************/

extern Display *display;

extern char nome_modello[];

extern char file_tempdati[], file_tempvar[];

extern byte num_varianti;
extern StructVarianti varianti_modello[];

extern int num_blocchi_modello;
extern int num_lines_vert, num_lines_horiz;

/************************************************************************/
/* VARIABILI GLOBALI							*/
/************************************************************************/

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
	Widget	Uxashell_print;
	Widget	Uxform5;
	Widget	UxpushButton7;
	Widget	Uxpushb_stampa;
	Widget	UxrowColumn2;
	Widget	Uxmenu_opt_print;
	Widget	Uxmenu2_index;
	Widget	Uxmenu2_documentation;
	Widget	Uxmenu2;
	Widget	UxseparatorGadget7;
	Widget	UxpushButton10;
	Widget	Uxframe1;
	Widget	Uxlabel_page_max;
	Widget	Uxframe2;
	Widget	Uxlabel_page_no;
	Widget	UxlabelGadget5;
	Widget	Uxarrow_next_page;
	Widget	Uxarrow_prev_page;
	Widget	UxscrolledWindow5;
	Widget	Uxtext_documentation;
	int	Uxnum_pagina_doc;
	int	Uxmax_righe_doc;
	int	Uxmax_righe_ind;
	int	Uxmax_righe;
	int	Uxmax_page;
	int	Uxmax_page_doc;
	int	Uxmax_page_ind;
	int	Uxpag_ini;
	long	Uxoffs_doc;
	unsigned char	*Uxnome_file_doc;
	unsigned char	*Uxnome_file_ind;
	unsigned char	*Uxnome_file_cur;
	FILE	*Uxfp_doc;
	unsigned char	Uxval_opz;
	byte	Uxtipo_doc;
} _UxCashell_print;

#define ashell_print            UxAshell_printContext->Uxashell_print
#define form5                   UxAshell_printContext->Uxform5
#define pushButton7             UxAshell_printContext->UxpushButton7
#define pushb_stampa            UxAshell_printContext->Uxpushb_stampa
#define rowColumn2              UxAshell_printContext->UxrowColumn2
#define menu_opt_print          UxAshell_printContext->Uxmenu_opt_print
#define menu2_index             UxAshell_printContext->Uxmenu2_index
#define menu2_documentation     UxAshell_printContext->Uxmenu2_documentation
#define menu2                   UxAshell_printContext->Uxmenu2
#define separatorGadget7        UxAshell_printContext->UxseparatorGadget7
#define pushButton10            UxAshell_printContext->UxpushButton10
#define frame1                  UxAshell_printContext->Uxframe1
#define label_page_max          UxAshell_printContext->Uxlabel_page_max
#define frame2                  UxAshell_printContext->Uxframe2
#define label_page_no           UxAshell_printContext->Uxlabel_page_no
#define labelGadget5            UxAshell_printContext->UxlabelGadget5
#define arrow_next_page         UxAshell_printContext->Uxarrow_next_page
#define arrow_prev_page         UxAshell_printContext->Uxarrow_prev_page
#define scrolledWindow5         UxAshell_printContext->UxscrolledWindow5
#define text_documentation      UxAshell_printContext->Uxtext_documentation
#define num_pagina_doc          UxAshell_printContext->Uxnum_pagina_doc
#define max_righe_doc           UxAshell_printContext->Uxmax_righe_doc
#define max_righe_ind           UxAshell_printContext->Uxmax_righe_ind
#define max_righe               UxAshell_printContext->Uxmax_righe
#define max_page                UxAshell_printContext->Uxmax_page
#define max_page_doc            UxAshell_printContext->Uxmax_page_doc
#define max_page_ind            UxAshell_printContext->Uxmax_page_ind
#define pag_ini                 UxAshell_printContext->Uxpag_ini
#define offs_doc                UxAshell_printContext->Uxoffs_doc
#define nome_file_doc           UxAshell_printContext->Uxnome_file_doc
#define nome_file_ind           UxAshell_printContext->Uxnome_file_ind
#define nome_file_cur           UxAshell_printContext->Uxnome_file_cur
#define fp_doc                  UxAshell_printContext->Uxfp_doc
#define val_opz                 UxAshell_printContext->Uxval_opz
#define tipo_doc                UxAshell_printContext->Uxtipo_doc

static _UxCashell_print	*UxAshell_printContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_ashell_print();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	if (fp_doc != NULL)
	   fclose(fp_doc);
	
	UxDestroySwidget(ashell_print);
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_pushb_stampa( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	int lung_riga;
	
#ifndef DESIGN_TIME
	if (tipo_doc == DOC_STAZIONARI || (tipo_doc == DOC_VARIABILI && 
	                                   val_opz == DOCUMENTAZIONE) )
	   lung_riga = MAX_COL_HOR;
	else
	   lung_riga = MAX_COL_VER;
#endif
	create_bb_conferma_print(nome_file_cur, num_pagina_doc, max_righe, lung_riga,
	                         pag_ini-1);
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_menu2_index( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	char buf[20], *str;
	XmString cstring;
	
	if ((fp_doc = fopen(nome_file_ind,"r")) == NULL)
	   crea_errorDialog("error while opening documentation file");
	
	
	max_page = max_page_ind;
	max_righe = max_righe_ind;
	offs_doc = 0L;
	nome_file_cur = nome_file_ind;
	val_opz = INDICE;
	pag_ini = 1;
	num_pagina_doc = pag_ini;
	
	str = leggi_pagina(fp_doc, max_righe);
	
	XmTextSetString(UxGetWidget(text_documentation), str);
	free((void*)str);
	
	sprintf(buf, "%d", pag_ini);
	set_label(UxGetWidget(label_page_no),buf);
	
	sprintf(buf, "%d", max_page);
	set_label(UxGetWidget(label_page_max), buf);
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_menu2_documentation( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	char buf[20], *str;
	XmString cstring;
	
	if (fp_doc != NULL)
	   fclose (fp_doc);
	
	if ((fp_doc = fopen(nome_file_doc,"r")) == NULL)
	   crea_errorDialog("error while opening index documentation file");
	
	max_page = max_page_doc;
	max_righe = max_righe_doc;
	offs_doc = 0L;
	nome_file_cur = nome_file_doc;
	val_opz = DOCUMENTAZIONE;
	
	if (tipo_doc == DOC_STAZIONARI)
	   pag_ini = 1;
	else
	   pag_ini = max_page_ind+1;
	
	num_pagina_doc = pag_ini;
	
	str = leggi_pagina(fp_doc, max_righe);
	
	XmTextSetString(UxGetWidget(text_documentation), str);
	free(str);
	
	sprintf(buf, "%d", pag_ini);
	set_label(UxGetWidget(label_page_no), buf);
	
	sprintf(buf, "%d", max_page);
	set_label(UxGetWidget(label_page_max), buf);
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_pushButton10( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	
	create_bb_cambia_pag(fp_doc, max_righe, text_documentation, label_page_no,
	                             &offs_doc, &num_pagina_doc, pag_ini-1);
	                             
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_arrow_next_page( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	char *str, strnum[10];
	XmString cstring;
	long offs;
	
	if (num_pagina_doc >= max_page)
	   return;
	
	if ((offs = pagina_succ(fp_doc, max_righe, offs_doc)) == -1)
	   return;
	
	offs_doc = offs;
	
	str = leggi_pagina(fp_doc, max_righe);
	XmTextSetString(UxGetWidget(text_documentation), str);
	free(str);
	
	num_pagina_doc++;
	
	sprintf(strnum, "%4d", num_pagina_doc);
	cstring=CREATE_CSTRING(strnum);
	XtVaSetValues(UxGetWidget(label_page_no), XmNlabelString, cstring, NULL);
	XmStringFree(cstring);
	}
	UxAshell_printContext = UxSaveCtx;
}

static void	activateCB_arrow_prev_page( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCashell_print        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAshell_printContext;
	UxAshell_printContext = UxContext =
			(_UxCashell_print *) UxGetContext( UxWidget );
	{
	char *str, strnum[10];
	XmString cstring;
	
	if (num_pagina_doc <= pag_ini)
	   return;
	
	offs_doc = pagina_prec(fp_doc, max_righe, offs_doc);
	
	str = leggi_pagina(fp_doc, max_righe);
	XmTextSetString(UxGetWidget(text_documentation), str);
	free(str);
	
	num_pagina_doc--;
	sprintf(strnum, "%4d", num_pagina_doc);
	cstring=CREATE_CSTRING(strnum);
	XtVaSetValues(UxGetWidget(label_page_no), XmNlabelString, cstring, NULL);
	XmStringFree(cstring);
	}
	UxAshell_printContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ashell_print()
{
	Widget	menu_opt_print_shell;

	ashell_print = XtVaCreatePopupShell( "ashell_print",
			applicationShellWidgetClass, UxTopLevel,
			XmNtitle, "PRINT PREVIEW",
			XmNiconName, "PRINT PREVIEW",
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 450,
			XmNwidth, 710,
			XmNy, 290,
			XmNx, 210,
			NULL );

	UxPutContext( ashell_print, (char *) UxAshell_printContext );

	form5 = XtVaCreateManagedWidget( "form5",
			xmFormWidgetClass, ashell_print,
			XmNlabelFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 360,
			XmNwidth, 660,
			XmNy, 30,
			XmNx, 30,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form5, (char *) UxAshell_printContext );

	pushButton7 = XtVaCreateManagedWidget( "pushButton7",
			xmPushButtonWidgetClass, form5,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 60,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 120,
			XmNy, 410,
			XmNx, 440,
			NULL );

	UxPutContext( pushButton7, (char *) UxAshell_printContext );

	pushb_stampa = XtVaCreateManagedWidget( "pushb_stampa",
			xmPushButtonWidgetClass, form5,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightPosition, 40,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Print" ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 120,
			XmNy, 420,
			XmNx, 120,
			NULL );

	UxPutContext( pushb_stampa, (char *) UxAshell_printContext );

	rowColumn2 = XtVaCreateManagedWidget( "rowColumn2",
			xmRowColumnWidgetClass, form5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNleftOffset, 10,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 40,
			XmNwidth, 150,
			XmNy, 30,
			XmNx, 20,
			NULL );

	UxPutContext( rowColumn2, (char *) UxAshell_printContext );

	menu_opt_print_shell = XtVaCreatePopupShell ("menu_opt_print_shell",
			xmMenuShellWidgetClass, rowColumn2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu_opt_print = XtVaCreateWidget( "menu_opt_print",
			xmRowColumnWidgetClass, menu_opt_print_shell,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( menu_opt_print, (char *) UxAshell_printContext );

	menu2_index = XtVaCreateManagedWidget( "menu2_index",
			xmPushButtonWidgetClass, menu_opt_print,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNlabelString, "INDEX" ),
			NULL );

	UxPutContext( menu2_index, (char *) UxAshell_printContext );

	menu2_documentation = XtVaCreateManagedWidget( "menu2_documentation",
			xmPushButtonWidgetClass, menu_opt_print,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			RES_CONVERT( XmNlabelString, "DOCUMENTATION" ),
			NULL );

	UxPutContext( menu2_documentation, (char *) UxAshell_printContext );

	menu2 = XtVaCreateManagedWidget( "menu2",
			xmRowColumnWidgetClass, rowColumn2,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNsubMenuId, menu_opt_print,
			XmNrowColumnType, XmMENU_OPTION,
			NULL );

	UxPutContext( menu2, (char *) UxAshell_printContext );

	separatorGadget7 = XtVaCreateManagedWidget( "separatorGadget7",
			xmSeparatorGadgetClass, form5,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, pushButton7,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 10,
			XmNwidth, 690,
			XmNy, 400,
			XmNx, 10,
			NULL );

	UxPutContext( separatorGadget7, (char *) UxAshell_printContext );

	pushButton10 = XtVaCreateManagedWidget( "pushButton10",
			xmPushButtonWidgetClass, form5,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Go to..." ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 80,
			XmNy, 10,
			XmNx, 620,
			NULL );

	UxPutContext( pushButton10, (char *) UxAshell_printContext );

	frame1 = XtVaCreateManagedWidget( "frame1",
			xmFrameWidgetClass, form5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightWidget, pushButton10,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 50,
			XmNy, 8,
			XmNx, 564,
			NULL );

	UxPutContext( frame1, (char *) UxAshell_printContext );

	label_page_max = XtVaCreateManagedWidget( "label_page_max",
			xmLabelGadgetClass, frame1,
			XmNrecomputeSize, FALSE,
			RES_CONVERT( XmNlabelString, "1" ),
			XmNheight, 30,
			XmNwidth, 50,
			XmNy, 40,
			XmNx, 650,
			NULL );

	UxPutContext( label_page_max, (char *) UxAshell_printContext );

	frame2 = XtVaCreateManagedWidget( "frame2",
			xmFrameWidgetClass, form5,
			XmNrightWidget, frame1,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 50,
			XmNy, 8,
			XmNx, 496,
			NULL );

	UxPutContext( frame2, (char *) UxAshell_printContext );

	label_page_no = XtVaCreateManagedWidget( "label_page_no",
			xmLabelGadgetClass, frame2,
			XmNrecomputeSize, FALSE,
			RES_CONVERT( XmNlabelString, "1" ),
			XmNheight, 30,
			XmNwidth, 50,
			XmNy, 40,
			XmNx, 650,
			NULL );

	UxPutContext( label_page_no, (char *) UxAshell_printContext );

	labelGadget5 = XtVaCreateManagedWidget( "labelGadget5",
			xmLabelGadgetClass, form5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNrightWidget, frame2,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNlabelString, "Page:" ),
			XmNheight, 34,
			XmNwidth, 56,
			XmNy, 8,
			XmNx, 430,
			NULL );

	UxPutContext( labelGadget5, (char *) UxAshell_printContext );

	arrow_next_page = XtVaCreateManagedWidget( "arrow_next_page",
			xmArrowButtonWidgetClass, form5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightWidget, labelGadget5,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNleftAttachment, XmATTACH_NONE,
			XmNarrowDirection, XmARROW_DOWN,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 40,
			XmNy, 8,
			XmNx, 370,
			NULL );

	UxPutContext( arrow_next_page, (char *) UxAshell_printContext );

	arrow_prev_page = XtVaCreateManagedWidget( "arrow_prev_page",
			xmArrowButtonWidgetClass, form5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightWidget, arrow_next_page,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNleftAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 34,
			XmNwidth, 40,
			XmNy, 8,
			XmNx, 320,
			NULL );

	UxPutContext( arrow_prev_page, (char *) UxAshell_printContext );

	scrolledWindow5 = XtVaCreateManagedWidget( "scrolledWindow5",
			xmScrolledWindowWidgetClass, form5,
			XmNscrollBarPlacement, XmBOTTOM_RIGHT,
			XmNbottomWidget, separatorGadget7,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNtopWidget, arrow_next_page,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 80,
			XmNx, 10,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow5, (char *) UxAshell_printContext );

	text_documentation = XtVaCreateManagedWidget( "text_documentation",
			xmTextWidgetClass, scrolledWindow5,
			XmNeditable, FALSE,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 300,
			XmNwidth, 690,
			NULL );

	UxPutContext( text_documentation, (char *) UxAshell_printContext );

	XtAddCallback( ashell_print, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( pushButton7, XmNactivateCallback,
			activateCB_pushButton7,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( pushb_stampa, XmNactivateCallback,
			activateCB_pushb_stampa,
			(XtPointer) UxAshell_printContext );

	XtVaSetValues(menu_opt_print,
			XmNmenuHistory, menu2_documentation,
			NULL );

	XtAddCallback( menu2_index, XmNactivateCallback,
			activateCB_menu2_index,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( menu2_documentation, XmNactivateCallback,
			activateCB_menu2_documentation,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( pushButton10, XmNactivateCallback,
			activateCB_pushButton10,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( arrow_next_page, XmNactivateCallback,
			activateCB_arrow_next_page,
			(XtPointer) UxAshell_printContext );

	XtAddCallback( arrow_prev_page, XmNactivateCallback,
			activateCB_arrow_prev_page,
			(XtPointer) UxAshell_printContext );



	return ( ashell_print );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_ashell_print( _Uxtipo_doc )
	byte	_Uxtipo_doc;
{
	Widget                  rtrn;
	_UxCashell_print        *UxContext;

	UxAshell_printContext = UxContext =
		(_UxCashell_print *) XtMalloc( sizeof(_UxCashell_print) );

	tipo_doc = _Uxtipo_doc;
	{
		int i;
		Boolean genera = False;
		XmString cstring;
		char *str, buf[20];
		
		/* controllo esistenza dei file di documentazione */
		/* Se tali file esistono viene effettuato il controllo sulle date di ultima */
		/* modifica */
		switch (tipo_doc)
		{
		   case DOC_DATI:
		        if (confronta_date(DOC_DATI_MODELLO,FILE_INFO_DATI) <= 0 ||
		            confronta_date(DOC_DATI_MODELLO,"f14.dat") <= 0)
		           crea_docdati(&max_page_doc, &max_page_ind);
		        else
		        {
		           max_page_ind = conta_pagine_doc(IND_DATI_MODELLO, num_lines_vert);
		           max_page_doc = conta_pagine_doc(DOC_DATI_MODELLO, num_lines_vert) +
		                          max_page_ind;
		        }
		
		        nome_file_doc = DOC_DATI_MODELLO;
			max_righe_doc = num_lines_vert;
		        nome_file_ind = IND_DATI_MODELLO;
			max_righe_ind = num_lines_vert;
			break;
		
		   case DOC_VARIABILI:
		        if (confronta_date(DOC_VAR_MODELLO,FILE_INFO_VAR) <= 0 ||
		            confronta_date(DOC_VAR_MODELLO,"f01.dat") <= 0)
			   crea_docvar(&max_page_doc, &max_page_ind);
		        else
		        {
		           max_page_ind = conta_pagine_doc(IND_VAR_MODELLO, num_lines_vert);
		           max_page_doc = conta_pagine_doc(DOC_VAR_MODELLO, num_lines_horiz)+
		                          max_page_ind;
		
		        }
		
		        nome_file_doc = DOC_VAR_MODELLO;
			max_righe_doc = num_lines_horiz;
		        nome_file_ind = IND_VAR_MODELLO;
			max_righe_ind = num_lines_vert;
			break;
		
		   case DOC_STAZIONARI:
		        for (i=0, genera = False ; i<num_varianti ; i++ )
		           if (varianti_modello[i].abilitato)
		              if (confronta_date(DOC_SSTATE_MODELLO,
		                                 varianti_modello[i].percorso) <= 0)
		              {
		                 genera = True;
		                 break;
		              }
		
		        if (genera)
		           crea_sstate_doc(&max_page_doc);
		        else
		           max_page_doc = conta_pagine_doc(DOC_SSTATE_MODELLO, num_lines_horiz);
		
		        nome_file_doc = DOC_SSTATE_MODELLO;
		        max_righe_doc = num_lines_horiz;
		        nome_file_ind = NULL;
			max_righe_ind = 0;
		        
			break;
		}
		rtrn = _Uxbuild_ashell_print();

		if ((fp_doc = fopen(nome_file_doc,"r")) == NULL)
		{
		   crea_errorDialog("error while opening documentation file.\n");
		   return(NULL);
		}
		
		if (tipo_doc == DOC_STAZIONARI)
		   pag_ini = 1;
		else
		   pag_ini = max_page_ind+1;
		num_pagina_doc = pag_ini;
		max_page = max_page_doc;
		max_righe = max_righe_doc;
		offs_doc = 0L;
		nome_file_cur = nome_file_doc;
		val_opz = DOCUMENTAZIONE;
		
		str = leggi_pagina(fp_doc, max_righe);
		
		XmTextSetString(UxGetWidget(text_documentation), str);
		free(str);
		
		sprintf(buf, "%d", pag_ini);
		set_label(UxGetWidget(label_page_no), buf);
		
		sprintf(buf, "%d", max_page);
		set_label(UxGetWidget(label_page_max), buf);
		
		if (tipo_doc == DOC_STAZIONARI)
		   XtVaSetValues(UxGetWidget(menu2_index), XmNsensitive, False, NULL);
		
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

Widget	create_ashell_print( _Uxtipo_doc )
	byte	_Uxtipo_doc;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_ashell_print( _Uxtipo_doc );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

