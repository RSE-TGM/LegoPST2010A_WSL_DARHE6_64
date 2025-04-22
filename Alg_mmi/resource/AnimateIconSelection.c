
/*******************************************************************************
       AnimateIconSelection.c
       (Generated from interface file AnimateIconSelection.i)
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
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo AnimateIconSelection.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)AnimateIconSelection.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#ifdef VMS
#include <signal.h>
#endif
#include "res_edit.h"
#include "config.h"

void disableButtonIcSel( );
void riableButtonIcSel( );
void InserisciItem ( );
void RefreshLista( );


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
	Widget	UxAnimateIconSelection;
	Widget	UxmainWindow8;
	Widget	Uxmenu7;
	Widget	UxFileIconPane;
	Widget	UxEditIconItem;
	Widget	UxCreateIconItem;
	Widget	Uxmenu7_top_b1;
	Widget	UxselectionBox1;
	Widget	*UxListaF;
	Widget	UxParente;
	Widget	UxOggettoSelezionato;
	int	UxTipoIconaA;
	unsigned char	UxColoreBkg[20];
	PROG_DATA	*Uxproc_data;
	int	UxTipoAI;
	Widget	UxPadre1;
	Widget	*UxFigli;
	Widget	UxOggSel;
	unsigned char	*UxStringaColore;
} _UxCAnimateIconSelection;

static _UxCAnimateIconSelection *UxAnimateIconSelectionContext;
#define AnimateIconSelection    UxAnimateIconSelectionContext->UxAnimateIconSelection
#define mainWindow8             UxAnimateIconSelectionContext->UxmainWindow8
#define menu7                   UxAnimateIconSelectionContext->Uxmenu7
#define FileIconPane            UxAnimateIconSelectionContext->UxFileIconPane
#define EditIconItem            UxAnimateIconSelectionContext->UxEditIconItem
#define CreateIconItem          UxAnimateIconSelectionContext->UxCreateIconItem
#define menu7_top_b1            UxAnimateIconSelectionContext->Uxmenu7_top_b1
#define selectionBox1           UxAnimateIconSelectionContext->UxselectionBox1
#define ListaF                  UxAnimateIconSelectionContext->UxListaF
#define Parente                 UxAnimateIconSelectionContext->UxParente
#define OggettoSelezionato      UxAnimateIconSelectionContext->UxOggettoSelezionato
#define TipoIconaA              UxAnimateIconSelectionContext->UxTipoIconaA
#define ColoreBkg               UxAnimateIconSelectionContext->UxColoreBkg
#define proc_data               UxAnimateIconSelectionContext->Uxproc_data
#define TipoAI                  UxAnimateIconSelectionContext->UxTipoAI
#define Padre1                  UxAnimateIconSelectionContext->UxPadre1
#define Figli                   UxAnimateIconSelectionContext->UxFigli
#define OggSel                  UxAnimateIconSelectionContext->UxOggSel
#define StringaColore           UxAnimateIconSelectionContext->UxStringaColore



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_AnimateIconSelection();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

#ifdef VMS
/******************************************
 * callback che effettua la kill 
 * del processo (draw,bitmap editor)
 * nel parametro  "XtPointer pid" 
 * si trova il pid del processo da uccidere
 ******************************************/
static void uccidi_processo(Widget wid,XtPointer pr_dat,XtPointer cb_arg)
{
   extern Display *UxDisplay;
   PROG_DATA *pdata;

   pdata = (PROG_DATA *)pr_dat;

   
   if(pdata != NULL)
   {
      if( pdata->Itimer != 0)
         XtRemoveTimeOut( pdata->Itimer );

      XSync( UxDisplay );

      if( (kill(pdata->fpid,SIGTERM)) != 0)
         printf("Kill Process Failed\n");
      else
         printf("Kill Process Ok\n");
   }
}

/**************************************
 * rimuove dalla lista delle callback
 * la callback uccidi processo
 * perche il processo non esiste piu'
 **************************************/
void rimuovi_callback()
{
   XtRemoveCallback(AnimateIconSelection,XmNdestroyCallback,
                    uccidi_processo,(XtPointer)proc_data);
}

#endif /* defined VMS */

/*****************************************
 disabilita i bottoni di Edit e Create
 ****************************************/
void disableButtonIcSel()
{
   set_something(EditIconItem,XmNsensitive,(void*) False);
   set_something(CreateIconItem,XmNsensitive,(void*) False);
}

/*****************************************
 riabilita i bottoni di Edit e Create
 ****************************************/
void riableButtonIcSel()
{
   set_something(EditIconItem,XmNsensitive,(void*) True);
   set_something(CreateIconItem,XmNsensitive,(void*) True);
}

void InserisciItem (char *lista_ele,Widget Lista)
{
char Elemento[200],StringaLetta[200];
XmString XmInserire;
int i,k;

/*
	non esistono files
*/
if(lista_ele == NULL)
	return;
i = 0;
while ( i < strlen (lista_ele) )
  {
  k=0;
  while ( lista_ele[i] != '.')
    {
    Elemento[k] = lista_ele[i];
    k++;
    i++;
    }
  Elemento[k] = '\0';
  XmInserire = XmStringCreateSimple (Elemento);
  XmListAddItemUnselected (Lista,XmInserire,0);
  XmStringFree (XmInserire);
  while ( (lista_ele[i] != '\n') && (i<strlen(lista_ele)) )
    i++;
  i++;
  }
}

void RefreshLista()
{
char *lista_elementi;
char Comando[200];
Widget Lista;

if (TipoIconaA == SEL_BITMAP)
	{
	strcpy (Comando,XlGetenv(ENVICO));
/*	strcat (Comando,"/*.bmp"); */
	lista_elementi = (char *)XlGetDir2 (XlConvPathVms(Comando),"bmp");	
	}
if (TipoIconaA == SEL_ICONA)
	{
	strcpy (Comando,XlGetenv(ENVICO));
/*	strcat (Comando,"/*.ico"); */
	lista_elementi = (char *)XlGetDir2 (XlConvPathVms(Comando),"ico");	
	}

/*  Prendo dalla selection box l'ID della lista degli item  */
Lista = (Widget )XmSelectionBoxGetChild (selectionBox1,XmDIALOG_LIST);

SettaBottoni (True,selectionBox1);

XmListDeleteAllItems (Lista);
InserisciItem (lista_elementi,Lista);
XtFree (lista_elementi);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	destroyCB_AnimateIconSelection( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAnimateIconSelection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAnimateIconSelectionContext;
	UxAnimateIconSelectionContext = UxContext =
			(_UxCAnimateIconSelection *) UxGetContext( UxWidget );
	{
	
	}
	UxAnimateIconSelectionContext = UxSaveCtx;
}

static	void	activateCB_EditIconItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAnimateIconSelection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAnimateIconSelectionContext;
	UxAnimateIconSelectionContext = UxContext =
			(_UxCAnimateIconSelection *) UxGetContext( UxWidget );
	{
	Widget Figlio;
	char stringa[100],comando[100],nomefile[200];
	FILE *prova;
	
	Figlio = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);
	
	strcpy (nomefile, getenv (ENVICO) );
	strcat (nomefile,"/");
	strcat (nomefile,XmTextGetString (Figlio));
	
	if (TipoIconaA == SEL_BITMAP)
		strcat (nomefile,".bmp");
	else if (TipoIconaA == SEL_ICONA)
		strcat (nomefile,".ico");
	
	prova = fopen(nomefile,"r");
	if ( (prova == NULL) || (nomefile[strlen(nomefile) -1] == '/') )
		{
		strcpy (stringa,"Unable to open file!");
		VisualizzaMessageBox (GENERICA,AnimateIconSelection,stringa,OggettoSelezionato);
		}
	else
		{
		if (TipoIconaA == SEL_BITMAP)
			proc_data = EseguiBitmap (nomefile,selectionBox1);
		else if (TipoIconaA == SEL_ICONA)
			proc_data = EseguiIcona (nomefile,selectionBox1,ColoreBkg,OggettoSelezionato);
#ifdef VMS
	/* aggancio la callback sulla destroy della interfaccia per il kill del processo */
	        XtAddCallback(AnimateIconSelection,XmNdestroyCallback,
	                      uccidi_processo,(XtPointer)proc_data);
#endif
		}
	}
	UxAnimateIconSelectionContext = UxSaveCtx;
}

static	void	activateCB_CreateIconItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAnimateIconSelection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAnimateIconSelectionContext;
	UxAnimateIconSelectionContext = UxContext =
			(_UxCAnimateIconSelection *) UxGetContext( UxWidget );
	{
	char nomefile[200],stringa[100];
	Widget Figlio;
	FILE *prova;
	extern swidget create_BitmapProperties( );
	
	Figlio = (Widget)XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);
	
	strcpy (nomefile, (char *)getenv (ENVICO) );
	strcat (nomefile,"/");
	strcat (nomefile,XmTextGetString (Figlio));
	
	if (TipoIconaA == SEL_BITMAP)
		strcat (nomefile,".bmp");
	else if (TipoIconaA == SEL_ICONA)
		strcat (nomefile,".ico");
	
	prova = fopen (nomefile, "r");
	if ( (prova == NULL) && (nomefile[strlen(nomefile)-1] != '/') )
		{
		if (TipoIconaA == SEL_BITMAP)
			UxPopupInterface (create_BitmapProperties(nomefile,
							selectionBox1),no_grab);
		else if (TipoIconaA == SEL_ICONA)
	           {
			proc_data = EseguiIcona (nomefile,selectionBox1,ColoreBkg,OggettoSelezionato);
#ifdef VMS
	/* sulla destroy faccio la kill del processo */
	                XtAddCallback(AnimateIconSelection, XmNdestroyCallback,
	                              uccidi_processo, proc_data);
#endif
	           }
		}
	else
		{
		strcpy (stringa,"File already exist!Open on edit mode?");
		if (TipoIconaA == SEL_BITMAP)
		  VisualizzaMessageBox (BITMAP,selectionBox1,stringa,OggettoSelezionato);
		else if (TipoIconaA == SEL_ICONA)
		  VisualizzaMessageBox (ICONA,selectionBox1,stringa,OggettoSelezionato);
		}
	}
	UxAnimateIconSelectionContext = UxSaveCtx;
}

static	void	cancelCB_selectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAnimateIconSelection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAnimateIconSelectionContext;
	UxAnimateIconSelectionContext = UxContext =
			(_UxCAnimateIconSelection *) UxGetContext( UxWidget );
	{
	char comando[200];
	
	set_something (ListaF[0], XmNsensitive, (void*) True);
	set_something (ListaF[2], XmNsensitive, (void*) True);
	XtDestroyWidget (AnimateIconSelection);
	}
	UxAnimateIconSelectionContext = UxSaveCtx;
}

static	void	okCallback_selectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCAnimateIconSelection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAnimateIconSelectionContext;
	UxAnimateIconSelectionContext = UxContext =
			(_UxCAnimateIconSelection *) UxGetContext( UxWidget );
	{
	Widget Lista;
	XmString *ListaItem,XmSelezionato;
	int selezione,posizione,*ListaSel,NumSel;
	char comando[200],*NomeFile;
	
	Lista = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);
	
	NomeFile = (char *)XmTextGetString (Lista );
	
	XmTextFieldSetString (ListaF[2], NomeFile);
	XtFree (NomeFile);
	set_something (ListaF[0], XmNsensitive, (void*) True);
	set_something (ListaF[2], XmNsensitive, (void*) True);
	XtDestroyWidget (AnimateIconSelection);
	}
	UxAnimateIconSelectionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_AnimateIconSelection()
{
	Widget		_UxParent;
	Widget		FileIconPane_shell;


	/* Creation of AnimateIconSelection */
	_UxParent = Padre1;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	AnimateIconSelection = XtVaCreatePopupShell( "AnimateIconSelection",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 660,
			XmNy, 150,
			XmNwidth, 360,
			XmNheight, 450,
			XmNallowShellResize, TRUE,
			XmNiconName, "Animate Icon Selection",
			NULL );
	XtAddCallback( AnimateIconSelection, XmNdestroyCallback,
		(XtCallbackProc) destroyCB_AnimateIconSelection,
		(XtPointer) 0x0 );

	UxPutContext( AnimateIconSelection, (char *) UxAnimateIconSelectionContext );


	/* Creation of mainWindow8 */
	mainWindow8 = XtVaCreateManagedWidget( "mainWindow8",
			xmMainWindowWidgetClass,
			AnimateIconSelection,
			XmNunitType, XmPIXELS,
			XmNx, 90,
			XmNy, 150,
			XmNwidth, 30,
			XmNheight, 90,
			NULL );
	UxPutContext( mainWindow8, (char *) UxAnimateIconSelectionContext );


	/* Creation of menu7 */
	menu7 = XtVaCreateManagedWidget( "menu7",
			xmRowColumnWidgetClass,
			mainWindow8,
			XmNrowColumnType, XmMENU_BAR,
			XmNmenuAccelerator, "<KeyUp>F10",
			NULL );
	UxPutContext( menu7, (char *) UxAnimateIconSelectionContext );


	/* Creation of FileIconPane */
	FileIconPane_shell = XtVaCreatePopupShell ("FileIconPane_shell",
			xmMenuShellWidgetClass, menu7,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	FileIconPane = XtVaCreateWidget( "FileIconPane",
			xmRowColumnWidgetClass,
			FileIconPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( FileIconPane, (char *) UxAnimateIconSelectionContext );


	/* Creation of EditIconItem */
	EditIconItem = XtVaCreateManagedWidget( "EditIconItem",
			xmPushButtonWidgetClass,
			FileIconPane,
			RES_CONVERT( XmNlabelString, "Edit" ),
			RES_CONVERT( XmNmnemonic, "E" ),
			NULL );
	XtAddCallback( EditIconItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_EditIconItem,
		(XtPointer) UxAnimateIconSelectionContext );

	UxPutContext( EditIconItem, (char *) UxAnimateIconSelectionContext );


	/* Creation of CreateIconItem */
	CreateIconItem = XtVaCreateManagedWidget( "CreateIconItem",
			xmPushButtonWidgetClass,
			FileIconPane,
			RES_CONVERT( XmNlabelString, "Create..." ),
			RES_CONVERT( XmNmnemonic, "C" ),
			NULL );
	XtAddCallback( CreateIconItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_CreateIconItem,
		(XtPointer) UxAnimateIconSelectionContext );

	UxPutContext( CreateIconItem, (char *) UxAnimateIconSelectionContext );


	/* Creation of menu7_top_b1 */
	menu7_top_b1 = XtVaCreateManagedWidget( "menu7_top_b1",
			xmCascadeButtonWidgetClass,
			menu7,
			RES_CONVERT( XmNlabelString, "File" ),
			XmNsubMenuId, FileIconPane,
			NULL );
	UxPutContext( menu7_top_b1, (char *) UxAnimateIconSelectionContext );


	/* Creation of selectionBox1 */
	selectionBox1 = XtVaCreateManagedWidget( "selectionBox1",
			xmSelectionBoxWidgetClass,
			mainWindow8,
			RES_CONVERT( XmNokLabelString, "Import" ),
			RES_CONVERT( XmNlistLabelString, "Available Animate Icon" ),
			XmNautoUnmanage, FALSE,
			NULL );
	XtAddCallback( selectionBox1, XmNcancelCallback,
		(XtCallbackProc) cancelCB_selectionBox1,
		(XtPointer) UxAnimateIconSelectionContext );
	XtAddCallback( selectionBox1, XmNokCallback,
		(XtCallbackProc) okCallback_selectionBox1,
		(XtPointer) UxAnimateIconSelectionContext );

	UxPutContext( selectionBox1, (char *) UxAnimateIconSelectionContext );


	XtAddCallback( AnimateIconSelection, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxAnimateIconSelectionContext);

	XmMainWindowSetAreas( mainWindow8, menu7, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, selectionBox1 );

	return ( AnimateIconSelection );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_AnimateIconSelection( _UxTipoAI, _UxPadre1, _UxFigli, _UxOggSel, _UxStringaColore )
	int	_UxTipoAI;
	Widget	_UxPadre1;
	Widget	*_UxFigli;
	Widget	_UxOggSel;
	unsigned char	*_UxStringaColore;
{
	Widget                  rtrn;
	_UxCAnimateIconSelection *UxContext;

	UxAnimateIconSelectionContext = UxContext =
		(_UxCAnimateIconSelection *) UxNewContext( sizeof(_UxCAnimateIconSelection), False );

	TipoAI = _UxTipoAI;
	Padre1 = _UxPadre1;
	Figli = _UxFigli;
	OggSel = _UxOggSel;
	StringaColore = _UxStringaColore;

	{
		char *Appo;
		Widget Lista;
		
		strcpy (ColoreBkg,StringaColore);
		OggettoSelezionato = OggSel;
		ListaF = Figli; 
		TipoIconaA = TipoAI;
		Parente = Padre1;
		rtrn = _Uxbuild_AnimateIconSelection();

		/*  Aggiorna la lista delle icone o dei bitmap  */
		RefreshLista();
		
		/*  Setto la selezione di default */
		Lista = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);
		Appo = (char *)XmTextFieldGetString (ListaF[2]);
		XmTextSetString (Lista,Appo);
		XtFree (Appo);
		
		/*  Setta la posizione dell'interfaccia rispetto al parent  */
		InterfaceSetPos (AnimateIconSelection,Padre1);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

