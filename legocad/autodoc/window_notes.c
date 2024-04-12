
/*******************************************************************************
	window_notes.c
	(Generated from interface file window_notes.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo window_notes.i
   tipo 
   release 1.12
   data 3/31/95
   reserved @(#)window_notes.i	1.12
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


extern char nome_modello[];

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
	Widget	Uxwindow_notes;
	Widget	Uxform3;
	Widget	Uxlabel1;
	Widget	Uxlb_nome_blocco;
	Widget	Uxlabel5;
	Widget	Uxlb_initial;
	Widget	UxpushButton1;
	Widget	UxpushButton2;
	Widget	UxpushButton3;
	Widget	Uxtext_note;
	unsigned char	**Uxtesto;
	unsigned char	*Uxnome_blocco_note;
	unsigned char	*Uxnota;
	Boolean	*Uxflag_win_note;
} _UxCwindow_notes;

#define window_notes            UxWindow_notesContext->Uxwindow_notes
#define form3                   UxWindow_notesContext->Uxform3
#define label1                  UxWindow_notesContext->Uxlabel1
#define lb_nome_blocco          UxWindow_notesContext->Uxlb_nome_blocco
#define label5                  UxWindow_notesContext->Uxlabel5
#define lb_initial              UxWindow_notesContext->Uxlb_initial
#define pushButton1             UxWindow_notesContext->UxpushButton1
#define pushButton2             UxWindow_notesContext->UxpushButton2
#define pushButton3             UxWindow_notesContext->UxpushButton3
#define text_note               UxWindow_notesContext->Uxtext_note
#define testo                   UxWindow_notesContext->Uxtesto
#define nome_blocco_note        UxWindow_notesContext->Uxnome_blocco_note
#define nota                    UxWindow_notesContext->Uxnota
#define flag_win_note           UxWindow_notesContext->Uxflag_win_note

static _UxCwindow_notes	*UxWindow_notesContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_window_notes();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*** void conferma_note_inserite(testo_nota, chiudi)
 ***    Parametri:
 ***      Boolean chiudi : indica se la window deve essere chiusa
 ***
 ***    Descrizione:
 ***      conferma l'inserimento o la modifica della nota
 ***/
void conferma_note_inserite(testo_nota, chiudi)
char **testo_nota;
Boolean chiudi;
{
   if (*testo_nota != NULL)
      XtFree(*testo_nota);

   *testo_nota = XmTextGetString(UxGetWidget(text_note));

   if (chiudi)
   {
#ifndef DESIGN_TIME
      *flag_win_note = False;
#endif
      UxDestroySwidget(window_notes);
   }
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_notes        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_notesContext;
	UxWindow_notesContext = UxContext =
			(_UxCwindow_notes *) UxGetContext( UxWidget );
	{
	conferma_note_inserite(testo, True);
	}
	UxWindow_notesContext = UxSaveCtx;
}

static void	activateCB_pushButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_notes        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_notesContext;
	UxWindow_notesContext = UxContext =
			(_UxCwindow_notes *) UxGetContext( UxWidget );
	{
	conferma_note_inserite(testo, False);
	}
	UxWindow_notesContext = UxSaveCtx;
}

static void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_notes        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_notesContext;
	UxWindow_notesContext = UxContext =
			(_UxCwindow_notes *) UxGetContext( UxWidget );
	{
	*flag_win_note = False;
	UxDestroySwidget(window_notes);
	}
	UxWindow_notesContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_window_notes()
{

	window_notes = XtVaCreatePopupShell( "window_notes",
			applicationShellWidgetClass, UxTopLevel,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNtitle, "NOTES",
			XmNdefaultFontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			XmNheight, 400,
			XmNwidth, 500,
			XmNy, 230,
			XmNx, 240,
			NULL );

	UxPutContext( window_notes, (char *) UxWindow_notesContext );

	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass, window_notes,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 330,
			XmNwidth, 480,
			XmNy, 30,
			XmNx, 10,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form3, (char *) UxWindow_notesContext );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Notes of the block:" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 150,
			XmNy, 20,
			XmNx, 10,
			NULL );

	UxPutContext( label1, (char *) UxWindow_notesContext );

	lb_nome_blocco = XtVaCreateManagedWidget( "lb_nome_blocco",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftWidget, label1,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 90,
			XmNy, 20,
			XmNx, 170,
			NULL );

	UxPutContext( lb_nome_blocco, (char *) UxWindow_notesContext );

	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftWidget, lb_nome_blocco,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "note:" ),
			XmNheight, 20,
			XmNwidth, 80,
			XmNy, 20,
			XmNx, 290,
			NULL );

	UxPutContext( label5, (char *) UxWindow_notesContext );

	lb_initial = XtVaCreateManagedWidget( "lb_initial",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNleftWidget, label5,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 100,
			XmNy, 20,
			XmNx, 390,
			NULL );

	UxPutContext( lb_initial, (char *) UxWindow_notesContext );

	pushButton1 = XtVaCreateManagedWidget( "pushButton1",
			xmPushButtonWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNrightPosition, 30,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 120,
			XmNy, 350,
			XmNx, 10,
			NULL );

	UxPutContext( pushButton1, (char *) UxWindow_notesContext );

	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNrightPosition, 64,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 36,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Apply" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 360,
			XmNx, 180,
			NULL );

	UxPutContext( pushButton2, (char *) UxWindow_notesContext );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, form3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNleftPosition, 70,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 120,
			XmNy, 350,
			XmNx, 340,
			NULL );

	UxPutContext( pushButton3, (char *) UxWindow_notesContext );

	text_note = XtVaCreateManagedWidget( "text_note",
			xmTextWidgetClass, form3,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNtopWidget, label1,
			XmNtopOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, pushButton1,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 240,
			XmNwidth, 480,
			XmNy, 90,
			XmNx, 10,
			NULL );

	UxPutContext( text_note, (char *) UxWindow_notesContext );

	XtAddCallback( window_notes, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxWindow_notesContext );

	XtAddCallback( pushButton1, XmNactivateCallback,
			activateCB_pushButton1,
			(XtPointer) UxWindow_notesContext );

	XtAddCallback( pushButton2, XmNactivateCallback,
			activateCB_pushButton2,
			(XtPointer) UxWindow_notesContext );

	XtAddCallback( pushButton3, XmNactivateCallback,
			activateCB_pushButton3,
			(XtPointer) UxWindow_notesContext );



	return ( window_notes );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_window_notes( _Uxtesto, _Uxnome_blocco_note, _Uxnota, _Uxflag_win_note )
	unsigned char	**_Uxtesto;
	unsigned char	*_Uxnome_blocco_note;
	unsigned char	*_Uxnota;
	Boolean	*_Uxflag_win_note;
{
	Widget                  rtrn;
	_UxCwindow_notes        *UxContext;

	UxWindow_notesContext = UxContext =
		(_UxCwindow_notes *) XtMalloc( sizeof(_UxCwindow_notes) );

	testo = _Uxtesto;
	nome_blocco_note = _Uxnome_blocco_note;
	nota = _Uxnota;
	flag_win_note = _Uxflag_win_note;
	{
		printf("nome del blocco: %s\n", nome_blocco_note);
		rtrn = _Uxbuild_window_notes();

		if (nome_blocco_note == NULL)
		{
		   UxPutLabelString(label1,"Note of the model:");
		   UxPutLabelString(lb_nome_blocco, nome_modello);
		   UxDestroySwidget(lb_initial);
		}
		else
		{
		   UxPutLabelString(label1,"Note of the block");
		   UxPutLabelString(lb_nome_blocco, nome_blocco_note);
		
		   if (nota == NULL)
		   {
		      UxDestroySwidget(label5);
		      UxDestroySwidget(lb_initial);
		   }
		   else
		      UxPutLabelString(lb_initial, nota);
		}
		
		if (*testo != NULL)
		   XmTextSetString(UxGetWidget(text_note), *testo);
		
		*flag_win_note = True;
		
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

Widget	create_window_notes( _Uxtesto, _Uxnome_blocco_note, _Uxnota, _Uxflag_win_note )
	unsigned char	**_Uxtesto;
	unsigned char	*_Uxnome_blocco_note;
	unsigned char	*_Uxnota;
	Boolean	*_Uxflag_win_note;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_window_notes( _Uxtesto, _Uxnome_blocco_note, _Uxnota, _Uxflag_win_note );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

