
/*******************************************************************************
       DatabaseSelection.c
       (Generated from interface file DatabaseSelection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <Xm/Text.h>
#include <Xm/TextF.h> // <--- AGGIUNGI QUESTO HEADER
#include <Xm/List.h>

/*
#include <Xm/Xm.h>
#include <Xm/XmP.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/TextF.h> // <--- AGGIUNGI QUESTO HEADER
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/MainW.h>
*/


#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo DatabaseSelection.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)DatabaseSelection.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/*
 *  Interfaccia utilizzata per la selezione dei Component e Subsistem
 *  utilizzate nella come filtro nella selezione delle variabili
 */

#include <Ol/OlDatabaseTopologia.h>
#include "libutilx.h"
#include "res_edit.h"

void InserisciElementi ( );
char *OlGetSubSystem (OlDatabaseTopologiaObject );
char *OlGetComponent (OlDatabaseTopologiaObject );


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
	Widget	UxDatabaseSelection;
	Widget	UxmainWindow7;
	Widget	Uxmenu6;
	Widget	UxDatabasePane;
	Widget	UxDatabaseEditItem;
	Widget	UxDatabaseCreateItem;
	Widget	Uxmenu6_top_b1;
	Widget	UxselectionBox2;
	Widget	*UxRigaInp1;
	Widget	UxParente1;
	int	UxTipoInput;
	Widget	*UxRiga;
	OlDatabaseTopologiaObject	UxDbase1;
} _UxCDatabaseSelection;

static _UxCDatabaseSelection   *UxDatabaseSelectionContext;
#define DatabaseSelection       UxDatabaseSelectionContext->UxDatabaseSelection
#define mainWindow7             UxDatabaseSelectionContext->UxmainWindow7
#define menu6                   UxDatabaseSelectionContext->Uxmenu6
#define DatabasePane            UxDatabaseSelectionContext->UxDatabasePane
#define DatabaseEditItem        UxDatabaseSelectionContext->UxDatabaseEditItem
#define DatabaseCreateItem      UxDatabaseSelectionContext->UxDatabaseCreateItem
#define menu6_top_b1            UxDatabaseSelectionContext->Uxmenu6_top_b1
#define selectionBox2           UxDatabaseSelectionContext->UxselectionBox2
#define RigaInp1                UxDatabaseSelectionContext->UxRigaInp1
#define Parente1                UxDatabaseSelectionContext->UxParente1
#define TipoInput               UxDatabaseSelectionContext->UxTipoInput
#define Riga                    UxDatabaseSelectionContext->UxRiga
#define Dbase1                  UxDatabaseSelectionContext->UxDbase1



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_DatabaseSelection();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void InserisciElementi (Widget WdgLista,char *ChrLista)
{
XmString XmAppoggio;
int i,Numero;

/*  Controllo nel caso la lista sia vuota  */
if (ChrLista)
  {
  memcpy (&Numero,ChrLista,sizeof(int));
  ChrLista += sizeof(int);

  for (i=0;i<Numero;i++)
    {
    XmAppoggio = XmStringCreateSimple (ChrLista);
    XmListAddItemUnselected (WdgLista, XmAppoggio, 0);
    XmStringFree (XmAppoggio);
    ChrLista += 25;
    }
  }
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_selectionBox2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCDatabaseSelection   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDatabaseSelectionContext;
	UxDatabaseSelectionContext = UxContext =
			(_UxCDatabaseSelection *) UxGetContext( UxWidget );
	{
	Widget Lista;
	char *NomeFile;
	
	Lista = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_TEXT);
	
	NomeFile = (char *)XmTextGetString (Lista );
	
	XmTextFieldSetString (RigaInp1[2], NomeFile);
	XtFree (NomeFile);
	set_something (RigaInp1[0], XmNsensitive, (void*) True);
	set_something (RigaInp1[2], XmNsensitive, (void*) True);
	
	XtDestroyWidget (DatabaseSelection);
	}
	UxDatabaseSelectionContext = UxSaveCtx;
}

static	void	cancelCB_selectionBox2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCDatabaseSelection   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDatabaseSelectionContext;
	UxDatabaseSelectionContext = UxContext =
			(_UxCDatabaseSelection *) UxGetContext( UxWidget );
	{
	set_something (RigaInp1[0], XmNsensitive, (void*) True);
	set_something (RigaInp1[2], XmNsensitive, (void*) True);
	
	XtDestroyWidget (DatabaseSelection);
	}
	UxDatabaseSelectionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_DatabaseSelection()
{
	Widget		_UxParent;
	Widget		DatabasePane_shell;


	/* Creation of DatabaseSelection */
	_UxParent = Parente1;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	DatabaseSelection = XtVaCreatePopupShell( "DatabaseSelection",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 610,
			XmNy, 110,
			XmNwidth, 410,
			XmNheight, 390,
			NULL );
	UxPutContext( DatabaseSelection, (char *) UxDatabaseSelectionContext );


	/* Creation of mainWindow7 */
	mainWindow7 = XtVaCreateManagedWidget( "mainWindow7",
			xmMainWindowWidgetClass,
			DatabaseSelection,
			XmNunitType, XmPIXELS,
			XmNx, 70,
			XmNy, 70,
			XmNwidth, 10,
			XmNheight, 70,
			NULL );
	UxPutContext( mainWindow7, (char *) UxDatabaseSelectionContext );


	/* Creation of menu6 */
	menu6 = XtVaCreateManagedWidget( "menu6",
			xmRowColumnWidgetClass,
			mainWindow7,
			XmNrowColumnType, XmMENU_BAR,
			NULL );
	UxPutContext( menu6, (char *) UxDatabaseSelectionContext );


	/* Creation of DatabasePane */
	DatabasePane_shell = XtVaCreatePopupShell ("DatabasePane_shell",
			xmMenuShellWidgetClass, menu6,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	DatabasePane = XtVaCreateWidget( "DatabasePane",
			xmRowColumnWidgetClass,
			DatabasePane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( DatabasePane, (char *) UxDatabaseSelectionContext );


	/* Creation of DatabaseEditItem */
	DatabaseEditItem = XtVaCreateManagedWidget( "DatabaseEditItem",
			xmPushButtonWidgetClass,
			DatabasePane,
			RES_CONVERT( XmNlabelString, "Edit" ),
			NULL );
	UxPutContext( DatabaseEditItem, (char *) UxDatabaseSelectionContext );


	/* Creation of DatabaseCreateItem */
	DatabaseCreateItem = XtVaCreateManagedWidget( "DatabaseCreateItem",
			xmPushButtonWidgetClass,
			DatabasePane,
			RES_CONVERT( XmNlabelString, "Create..." ),
			NULL );
	UxPutContext( DatabaseCreateItem, (char *) UxDatabaseSelectionContext );


	/* Creation of menu6_top_b1 */
	menu6_top_b1 = XtVaCreateManagedWidget( "menu6_top_b1",
			xmCascadeButtonWidgetClass,
			menu6,
			RES_CONVERT( XmNlabelString, "File" ),
			XmNsubMenuId, DatabasePane,
			NULL );
	UxPutContext( menu6_top_b1, (char *) UxDatabaseSelectionContext );


	/* Creation of selectionBox2 */
	selectionBox2 = XtVaCreateManagedWidget( "selectionBox2",
			xmSelectionBoxWidgetClass,
			mainWindow7,
			RES_CONVERT( XmNokLabelString, "Import" ),
			NULL );
	XtAddCallback( selectionBox2, XmNokCallback,
		(XtCallbackProc) okCallback_selectionBox2,
		(XtPointer) UxDatabaseSelectionContext );
	XtAddCallback( selectionBox2, XmNcancelCallback,
		(XtCallbackProc) cancelCB_selectionBox2,
		(XtPointer) UxDatabaseSelectionContext );

	UxPutContext( selectionBox2, (char *) UxDatabaseSelectionContext );


	XtAddCallback( DatabaseSelection, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxDatabaseSelectionContext);

	XmMainWindowSetAreas( mainWindow7, menu6, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, selectionBox2 );

	return ( DatabaseSelection );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_DatabaseSelection( _UxParente1, _UxTipoInput, _UxRiga, _UxDbase1 )
	Widget	_UxParente1;
	int	_UxTipoInput;
	Widget	*_UxRiga;
	OlDatabaseTopologiaObject	_UxDbase1;
{
	Widget                  rtrn;
	_UxCDatabaseSelection   *UxContext;

	UxDatabaseSelectionContext = UxContext =
		(_UxCDatabaseSelection *) UxNewContext( sizeof(_UxCDatabaseSelection), False );

	Parente1 = _UxParente1;
	TipoInput = _UxTipoInput;
	Riga = _UxRiga;
	Dbase1 = _UxDbase1;

	{
		char *Lista,*StrDef;
		Widget Oggetto;
		
		RigaInp1 = Riga;
		rtrn = _Uxbuild_DatabaseSelection();

		if (TipoInput == SEL_SUBS)
		  Lista = (char *)OlGetSubSystem(Dbase1);
		if (TipoInput == SEL_COMP)
		  Lista = (char *)OlGetComponent(Dbase1);
		/*  Carico la lista degli item  */
		Oggetto = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_LIST);
		InserisciElementi (Oggetto,Lista);
		XtFree (Lista);
		
		/*  Setto la selezione di default  */
		Oggetto = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_TEXT);
		StrDef = (char *)XmTextFieldGetString (RigaInp1[2]);
		XmTextSetString (Oggetto,StrDef);
		XtFree (StrDef);
		
		/*  Setta la posiozne dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (DatabaseSelection,Parente1);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

