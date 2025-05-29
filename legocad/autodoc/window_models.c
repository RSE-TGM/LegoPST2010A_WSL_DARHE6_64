
/*******************************************************************************
	window_models.c
	(Generated from interface file window_models.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SeparatoG.h>
#include <Xm/ToggleB.h>
#include <Xm/PushB.h>
#include <Xm/TextF.h>
#include <Xm/LabelG.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo window_models.i
   tipo 
   release 1.12
   data 3/31/95
   reserved @(#)window_models.i	1.12
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <unistd.h>

#include "autodoc.h"

/************************************************************************/
/* VARIABILI GLOBALI ESTERNE						*/
/************************************************************************/

extern StructVarianti varianti_modello[];
extern byte num_varianti, num_file_f14;

extern Boolean open_window_models;

extern void lcDestroySwidget(Widget);

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
	Widget	Uxwindow_models;
	Widget	Uxform4;
	Widget	UxlabelGadget2;
	Widget	UxlabelGadget4;
	Widget	Uxtext_path1;
	Widget	UxpushButton4;
	Widget	UxpushButton5;
	Widget	UxtoggleButton1;
	Widget	UxtoggleButton2;
	Widget	UxtoggleButton3;
	Widget	UxtoggleButton4;
	Widget	UxtoggleButton5;
	Widget	Uxtext_title1;
	Widget	Uxtext_title2;
	Widget	Uxtext_path2;
	Widget	Uxtext_title3;
	Widget	Uxtext_path3;
	Widget	Uxtext_title4;
	Widget	Uxtext_path4;
	Widget	Uxtext_title5;
	Widget	Uxtext_path5;
	Widget	UxseparatorGadget2;
} _UxCwindow_models;

#define window_models           UxWindow_modelsContext->Uxwindow_models
#define form4                   UxWindow_modelsContext->Uxform4
#define labelGadget2            UxWindow_modelsContext->UxlabelGadget2
#define labelGadget4            UxWindow_modelsContext->UxlabelGadget4
#define text_path1              UxWindow_modelsContext->Uxtext_path1
#define pushButton4             UxWindow_modelsContext->UxpushButton4
#define pushButton5             UxWindow_modelsContext->UxpushButton5
#define toggleButton1           UxWindow_modelsContext->UxtoggleButton1
#define toggleButton2           UxWindow_modelsContext->UxtoggleButton2
#define toggleButton3           UxWindow_modelsContext->UxtoggleButton3
#define toggleButton4           UxWindow_modelsContext->UxtoggleButton4
#define toggleButton5           UxWindow_modelsContext->UxtoggleButton5
#define text_title1             UxWindow_modelsContext->Uxtext_title1
#define text_title2             UxWindow_modelsContext->Uxtext_title2
#define text_path2              UxWindow_modelsContext->Uxtext_path2
#define text_title3             UxWindow_modelsContext->Uxtext_title3
#define text_path3              UxWindow_modelsContext->Uxtext_path3
#define text_title4             UxWindow_modelsContext->Uxtext_title4
#define text_path4              UxWindow_modelsContext->Uxtext_path4
#define text_title5             UxWindow_modelsContext->Uxtext_title5
#define text_path5              UxWindow_modelsContext->Uxtext_path5
#define separatorGadget2        UxWindow_modelsContext->UxseparatorGadget2

static _UxCwindow_models	*UxWindow_modelsContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_window_models();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*** salva_steady_version()
 ***
 ***   Descrizione: 
 ***      Salva i settaggi relativi alle versioni dello stazionario.
 ***/
void salva_steady_version()
{
   char *str;

   num_file_f14 = 0;

   varianti_modello[0].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton1));
   varianti_modello[1].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton2));
   varianti_modello[2].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton3));
   varianti_modello[3].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton4));
   varianti_modello[4].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton5));

   str = XmTextFieldGetString(UxGetWidget(text_path1));
   if ( varianti_modello[0].abilitato && access(str, F_OK) != 0 )
   {
      fprintf(stderr, "file %s doesn't exist!\n", str);
      varianti_modello[0].abilitato = False;
   }
   else
      if (varianti_modello[0].abilitato)
         num_file_f14++;
   strcpy(varianti_modello[0].percorso, str);
   XmStringFree((XmString)str);
   str = XmTextFieldGetString(UxGetWidget(text_title1));
   strcpy(varianti_modello[0].titolo, str);
   XmStringFree((XmString)str);

   str = XmTextFieldGetString(UxGetWidget(text_path2));
   if ( varianti_modello[1].abilitato && access(str, F_OK) != 0 )
   {
      fprintf(stderr, "file %s doesn't exist!\n", str);
      varianti_modello[1].abilitato = False;
   }
   else
      if (varianti_modello[1].abilitato)
         num_file_f14++;
   strcpy(varianti_modello[1].percorso, str);
   XmStringFree((XmString)str);
   str = XmTextFieldGetString(UxGetWidget(text_title2));
   strcpy(varianti_modello[1].titolo, str);
   XmStringFree((XmString)str);

   str = XmTextFieldGetString(UxGetWidget(text_path3));
   if ( varianti_modello[2].abilitato && access(str, F_OK) != 0 )
   {
      fprintf(stderr, "file %s doesn't exist!\n", str);
      varianti_modello[2].abilitato = False;
   }
   else
      if (varianti_modello[2].abilitato)
         num_file_f14++;
   strcpy(varianti_modello[2].percorso, str);
   XmStringFree((XmString)str);
   str = XmTextFieldGetString(UxGetWidget(text_title3));
   strcpy(varianti_modello[2].titolo, str);
   XmStringFree((XmString)str);

   str = XmTextFieldGetString(UxGetWidget(text_path4));
   if ( varianti_modello[3].abilitato && access(str, F_OK) != 0 )
   {
      fprintf(stderr, "file %s doesn't exist!\n", str);
      varianti_modello[3].abilitato = False;
   }
   else
      if (varianti_modello[3].abilitato)
         num_file_f14++;
   strcpy(varianti_modello[3].percorso, str);
   XmStringFree((XmString)str);
   str = XmTextFieldGetString(UxGetWidget(text_title4));
   strcpy(varianti_modello[3].titolo, str);
   XmStringFree((XmString)str);

   str = XmTextFieldGetString(UxGetWidget(text_path5));
   if ( varianti_modello[4].abilitato && access(str, F_OK) != 0 )
   {
      fprintf(stderr, "file %s doesn't exist!\n", str);
      varianti_modello[4].abilitato = False;
   }
   else
      if (varianti_modello[4].abilitato)
         num_file_f14++;
   strcpy(varianti_modello[4].percorso, str);
   XmStringFree((XmString)str);
   str = XmTextFieldGetString(UxGetWidget(text_title5));
   strcpy(varianti_modello[4].titolo, str);
   XmStringFree((XmString)str);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_models       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_modelsContext;
	UxWindow_modelsContext = UxContext =
			(_UxCwindow_models *) UxGetContext( UxWidget );
	{
	WindowInfoStruct *winfo;
	
	salva_steady_version();
	
	/* istanzia un nuovo item nella lista */
	winfo = new_struct_info(VARIABILI_N_F14);
	
	/* visualizza le variabili del i vari file f14.dat */
	winfo->swindow = create_info_ashell(NULL, NULL, VARIABILI_N_F14, winfo);
	}
	UxWindow_modelsContext = UxSaveCtx;
}

static void	activateCB_pushButton5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_models       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_modelsContext;
	UxWindow_modelsContext = UxContext =
			(_UxCwindow_models *) UxGetContext( UxWidget );
	{
	salva_steady_version();
	unlink(DOC_SSTATE_MODELLO); /* obbliga a ricreare la documentazione */
	open_window_models = False;
	UxDestroySwidget(window_models);
	}
	UxWindow_modelsContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_window_models()
{

	window_models = XtVaCreatePopupShell( "window_models",
			transientShellWidgetClass, UxTopLevel,
			XmNallowShellResize, FALSE,
			XmNtitle, "MODELS VARIANT",
			XmNdefaultFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 380,
			XmNwidth, 610,
			XmNy, 132,
			XmNx, 606,
			NULL );

	UxPutContext( window_models, (char *) UxWindow_modelsContext );

	form4 = XtVaCreateManagedWidget( "form4",
			xmFormWidgetClass, window_models,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 380,
			XmNwidth, 650,
			XmNy, 10,
			XmNx, 0,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form4, (char *) UxWindow_modelsContext );

	labelGadget2 = XtVaCreateManagedWidget( "labelGadget2",
			xmLabelGadgetClass, form4,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 35,
			RES_CONVERT( XmNlabelString, "STEADY STATE IDENTIFIER" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 235,
			XmNy, 20,
			XmNx, 35,
			NULL );

	UxPutContext( labelGadget2, (char *) UxWindow_modelsContext );

	labelGadget4 = XtVaCreateManagedWidget( "labelGadget4",
			xmLabelGadgetClass, form4,
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNlabelString, "FILE PATHNAME" ),
			XmNheight, 20,
			XmNwidth, 270,
			XmNy, 20,
			XmNx, 280,
			NULL );

	UxPutContext( labelGadget4, (char *) UxWindow_modelsContext );

	text_path1 = XtVaCreateManagedWidget( "text_path1",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 256,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, labelGadget2,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 295,
			XmNy, 60,
			XmNx, 305,
			NULL );

	UxPutContext( text_path1, (char *) UxWindow_modelsContext );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, form4,
			XmNrightPosition, 40,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "View" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 190,
			XmNy, 350,
			XmNx, 30,
			NULL );

	UxPutContext( pushButton4, (char *) UxWindow_modelsContext );

	pushButton5 = XtVaCreateManagedWidget( "pushButton5",
			xmPushButtonWidgetClass, form4,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 60,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Done" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 180,
			XmNy, 350,
			XmNx, 360,
			NULL );

	UxPutContext( pushButton5, (char *) UxWindow_modelsContext );

	toggleButton1 = XtVaCreateManagedWidget( "toggleButton1",
			xmToggleButtonWidgetClass, form4,
			XmNtopWidget, labelGadget2,
			XmNtopOffset, 25,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 20,
			XmNy, 60,
			XmNx, 0,
			NULL );

	UxPutContext( toggleButton1, (char *) UxWindow_modelsContext );

	toggleButton2 = XtVaCreateManagedWidget( "toggleButton2",
			xmToggleButtonWidgetClass, form4,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopWidget, toggleButton1,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 20,
			XmNy, 110,
			XmNx, 0,
			NULL );

	UxPutContext( toggleButton2, (char *) UxWindow_modelsContext );

	toggleButton3 = XtVaCreateManagedWidget( "toggleButton3",
			xmToggleButtonWidgetClass, form4,
			XmNtopWidget, toggleButton2,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 20,
			XmNy, 160,
			XmNx, 10,
			NULL );

	UxPutContext( toggleButton3, (char *) UxWindow_modelsContext );

	toggleButton4 = XtVaCreateManagedWidget( "toggleButton4",
			xmToggleButtonWidgetClass, form4,
			XmNtopWidget, toggleButton3,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 20,
			XmNy, 210,
			XmNx, 0,
			NULL );

	UxPutContext( toggleButton4, (char *) UxWindow_modelsContext );

	toggleButton5 = XtVaCreateManagedWidget( "toggleButton5",
			xmToggleButtonWidgetClass, form4,
			XmNtopWidget, toggleButton4,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 25,
			XmNwidth, 20,
			XmNy, 265,
			XmNx, 5,
			NULL );

	UxPutContext( toggleButton5, (char *) UxWindow_modelsContext );

	text_title1 = XtVaCreateManagedWidget( "text_title1",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 14,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, labelGadget2,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftWidget, toggleButton1,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 258,
			XmNy, 60,
			XmNx, 35,
			NULL );

	UxPutContext( text_title1, (char *) UxWindow_modelsContext );

	text_title2 = XtVaCreateManagedWidget( "text_title2",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 14,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton1,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftWidget, toggleButton2,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 258,
			XmNy, 110,
			XmNx, 35,
			NULL );

	UxPutContext( text_title2, (char *) UxWindow_modelsContext );

	text_path2 = XtVaCreateManagedWidget( "text_path2",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 256,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton1,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 295,
			XmNy, 110,
			XmNx, 305,
			NULL );

	UxPutContext( text_path2, (char *) UxWindow_modelsContext );

	text_title3 = XtVaCreateManagedWidget( "text_title3",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 14,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton2,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftWidget, toggleButton3,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 258,
			XmNy, 160,
			XmNx, 35,
			NULL );

	UxPutContext( text_title3, (char *) UxWindow_modelsContext );

	text_path3 = XtVaCreateManagedWidget( "text_path3",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 256,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton2,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 295,
			XmNy, 160,
			XmNx, 305,
			NULL );

	UxPutContext( text_path3, (char *) UxWindow_modelsContext );

	text_title4 = XtVaCreateManagedWidget( "text_title4",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 14,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton3,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftWidget, toggleButton4,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 258,
			XmNy, 210,
			XmNx, 35,
			NULL );

	UxPutContext( text_title4, (char *) UxWindow_modelsContext );

	text_path4 = XtVaCreateManagedWidget( "text_path4",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 256,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton3,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 295,
			XmNy, 210,
			XmNx, 305,
			NULL );

	UxPutContext( text_path4, (char *) UxWindow_modelsContext );

	text_title5 = XtVaCreateManagedWidget( "text_title5",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 14,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton4,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftWidget, toggleButton5,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 258,
			XmNy, 260,
			XmNx, 35,
			NULL );

	UxPutContext( text_title5, (char *) UxWindow_modelsContext );

	text_path5 = XtVaCreateManagedWidget( "text_path5",
			xmTextFieldWidgetClass, form4,
			XmNmaxLength, 256,
			XmNfontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1" ),
			XmNtopWidget, toggleButton4,
			XmNtopOffset, 15,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 35,
			XmNwidth, 295,
			XmNy, 260,
			XmNx, 305,
			NULL );

	UxPutContext( text_path5, (char *) UxWindow_modelsContext );

	separatorGadget2 = XtVaCreateManagedWidget( "separatorGadget2",
			xmSeparatorGadgetClass, form4,
			XmNtopWidget, toggleButton5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, pushButton4,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 10,
			XmNwidth, 510,
			XmNy, 320,
			XmNx, 30,
			NULL );

	UxPutContext( separatorGadget2, (char *) UxWindow_modelsContext );

	XtAddCallback( window_models, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxWindow_modelsContext );

	XtAddCallback( pushButton4, XmNactivateCallback,
			activateCB_pushButton4,
			(XtPointer) UxWindow_modelsContext );

	XtAddCallback( pushButton5, XmNactivateCallback,
			activateCB_pushButton5,
			(XtPointer) UxWindow_modelsContext );



	return ( window_models );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_window_models()
{
	Widget                  rtrn;
	_UxCwindow_models       *UxContext;

	UxWindow_modelsContext = UxContext =
		(_UxCwindow_models *) XtMalloc( sizeof(_UxCwindow_models) );

	{
		open_window_models = True;
		rtrn = _Uxbuild_window_models();

		switch (num_varianti)
		{
		    case 5:
		       XmToggleButtonSetState(UxGetWidget(toggleButton5), 
					      varianti_modello[4].abilitato, False);
		       XmTextFieldSetString(UxGetWidget(text_title5),
		                            varianti_modello[4].titolo);
		       XmTextFieldSetString(UxGetWidget(text_path5),
		                            varianti_modello[4].percorso);
		    case 4:
		       XmToggleButtonSetState(UxGetWidget(toggleButton4), 
					      varianti_modello[3].abilitato, False); 
		       XmTextFieldSetString(UxGetWidget(text_title4),
		                            varianti_modello[3].titolo);
		       XmTextFieldSetString(UxGetWidget(text_path4),
		                            varianti_modello[3].percorso);
		
		    case 3:
		       XmToggleButtonSetState(UxGetWidget(toggleButton3), 
					      varianti_modello[2].abilitato, False); 
		       XmTextFieldSetString(UxGetWidget(text_title3),
		                            varianti_modello[2].titolo);
		       XmTextFieldSetString(UxGetWidget(text_path3),
		                            varianti_modello[2].percorso);
		    case 2:
		       XmToggleButtonSetState(UxGetWidget(toggleButton2), 
					      varianti_modello[1].abilitato, False); 
		       XmTextFieldSetString(UxGetWidget(text_title2),
		                            varianti_modello[1].titolo);
		       XmTextFieldSetString(UxGetWidget(text_path2),
		                            varianti_modello[1].percorso);
		    case 1:
		       XmToggleButtonSetState(UxGetWidget(toggleButton1), 
					      varianti_modello[0].abilitato, False); 
		       XmTextFieldSetString(UxGetWidget(text_title1),
		                            varianti_modello[0].titolo);
		       XmTextFieldSetString(UxGetWidget(text_path1),
		                            varianti_modello[0].percorso);
		}
		
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

Widget	create_window_models()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_window_models();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

