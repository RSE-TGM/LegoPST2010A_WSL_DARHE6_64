
/*******************************************************************************
       FormSelection.c
       (Generated from interface file FormSelection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo FormSelection.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)FormSelection.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


#include <string.h>

#include <Xl/Xl.h>
#include <Rt/RtMemory.h>

extern void InserisciItem();

void AggiornaLista();


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxFormSelection;
	Widget	UxmainWindow9;
	Widget	UxselectionBox3;
	Widget	UxParente2;
	Widget	*UxRiga2;
	Widget	UxPare;
	Widget	*UxRig;
} _UxCFormSelection;

static _UxCFormSelection       *UxFormSelectionContext;
#define FormSelection           UxFormSelectionContext->UxFormSelection
#define mainWindow9             UxFormSelectionContext->UxmainWindow9
#define selectionBox3           UxFormSelectionContext->UxselectionBox3
#define Parente2                UxFormSelectionContext->UxParente2
#define Riga2                   UxFormSelectionContext->UxRiga2
#define Pare                    UxFormSelectionContext->UxPare
#define Rig                     UxFormSelectionContext->UxRig



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_FormSelection();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void AggiornaLista()
{
char *lista_elementi;
char Comando[200];
Widget Lista;

strcpy (Comando,XlGetenv("LEGOCAD_USER"));
strcat (Comando,"/legocad/libut_reg/libreg/*.frm");
lista_elementi = (char *)XlGetDir (XlConvPathVms(Comando));

/* Prendo dalla selectionbox l'ID della lista */
Lista = (Widget )XmSelectionBoxGetChild (selectionBox3,XmDIALOG_LIST);

XmListDeleteAllItems (Lista);
InserisciItem (lista_elementi,Lista);
XtFree (lista_elementi);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	cancelCB_selectionBox3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFormSelection       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFormSelectionContext;
	UxFormSelectionContext = UxContext =
			(_UxCFormSelection *) UxGetContext( UxWidget );
	{
	set_something (Riga2[0], XmNsensitive, True);
	set_something (Riga2[2], XmNsensitive, True);
	
	XtDestroyWidget (FormSelection);
	}
	UxFormSelectionContext = UxSaveCtx;
}

static	void	okCallback_selectionBox3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFormSelection       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFormSelectionContext;
	UxFormSelectionContext = UxContext =
			(_UxCFormSelection *) UxGetContext( UxWidget );
	{
	Widget Lista;
	char *NomeFile;
	
	Lista = (Widget )XmSelectionBoxGetChild (selectionBox3, XmDIALOG_TEXT);
	
	NomeFile = (char *)XmTextGetString (Lista );
	
	XmTextFieldSetString (Riga2[2], NomeFile);
	XtFree (NomeFile);
	set_something (Riga2[0], XmNsensitive, True);
	set_something (Riga2[2], XmNsensitive, True);
	
	XtDestroyWidget (FormSelection);
	}
	UxFormSelectionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_FormSelection()
{
	Widget		_UxParent;


	/* Creation of FormSelection */
	_UxParent = Parente2;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	FormSelection = XtVaCreatePopupShell( "FormSelection",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 810,
			XmNy, 130,
			XmNwidth, 400,
			XmNheight, 450,
			NULL );
	UxPutContext( FormSelection, (char *) UxFormSelectionContext );


	/* Creation of mainWindow9 */
	mainWindow9 = XtVaCreateManagedWidget( "mainWindow9",
			xmMainWindowWidgetClass,
			FormSelection,
			XmNunitType, XmPIXELS,
			XmNx, 110,
			XmNy, 130,
			XmNwidth, 40,
			XmNheight, 30,
			NULL );
	UxPutContext( mainWindow9, (char *) UxFormSelectionContext );


	/* Creation of selectionBox3 */
	selectionBox3 = XtVaCreateManagedWidget( "selectionBox3",
			xmSelectionBoxWidgetClass,
			mainWindow9,
			RES_CONVERT( XmNokLabelString, "Import" ),
			RES_CONVERT( XmNlistLabelString, "Available forms:" ),
			XmNlabelFontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNselectionLabelString, "Selected form:" ),
			XmNtextColumns, 4,
			XmNtextFontList, UxConvertFontList( "-adobe-new century schoolbook-medium-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNtextString, "" ),
			NULL );
	XtAddCallback( selectionBox3, XmNcancelCallback,
		(XtCallbackProc) cancelCB_selectionBox3,
		(XtPointer) UxFormSelectionContext );
	XtAddCallback( selectionBox3, XmNokCallback,
		(XtCallbackProc) okCallback_selectionBox3,
		(XtPointer) UxFormSelectionContext );

	UxPutContext( selectionBox3, (char *) UxFormSelectionContext );


	XtAddCallback( FormSelection, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxFormSelectionContext);

	XmMainWindowSetAreas( mainWindow9, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, selectionBox3 );

	return ( FormSelection );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_FormSelection( _UxPare, _UxRig )
	Widget	_UxPare;
	Widget	*_UxRig;
{
	Widget                  rtrn;
	_UxCFormSelection       *UxContext;

	UxFormSelectionContext = UxContext =
		(_UxCFormSelection *) UxNewContext( sizeof(_UxCFormSelection), False );

	Pare = _UxPare;
	Rig = _UxRig;

	{
		char *Appo;
		Widget Lista;
		
		Parente2 = Pare;
		Riga2 = Rig;
		rtrn = _Uxbuild_FormSelection();

		/* Aggiorna la lista delle form  */
		AggiornaLista();
		
		/* Setto la selezione di default */
		Lista = (Widget )XmSelectionBoxGetChild (selectionBox3, XmDIALOG_TEXT);
		Appo = (char *)XmTextFieldGetString (Riga2[2]);
		XmTextSetString (Lista,Appo);
		XtFree (Appo);
		
		/*  Setta la posizione dell'interfaccia rispetto al parent  */
		InterfaceSetPos (FormSelection,Parente2);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

