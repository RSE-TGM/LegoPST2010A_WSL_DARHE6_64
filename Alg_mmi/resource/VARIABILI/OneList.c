
/*******************************************************************************
       OneList.c
       (Generated from interface file OneList.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ArrowB.h>
#include <Xm/TextF.h>
#include <Xm/PushB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

#include "libutilx.h"

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS 
*/
/*
   modulo OneList.i
   tipo 
   release 5.2
   data 2/6/96
   reserved @(#)OneList.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/*
  Interfaccia per la selezione dei modelli e delle variabili
*/
#include <string.h>
#include <Ol/OlDatabaseTopologia.h>
#include "sim_param.h"
#include "VarEdit.h"
#include "res_edit.h"

extern char *CaricaElencoModelli();
extern char *CaricaElencoVariabili();


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
	Widget	UxOneList;
	Widget	Uxform3;
	Widget	Uxseparator3;
	Widget	UxscrolledWindow1;
	Widget	UxscrolledList1;
	Widget	UxpushButton9;
	Widget	UxpushButton10;
	Widget	UxtextField2;
	Widget	UxarrowButton1;
	Widget	UxarrowButton2;
	Widget	*UxPadroneChiam;
	int	*UxPosModel;
	int	*UxPosVariab;
	int	UxModOrVar;
	Widget	UxParent1;
	Widget	*UxPadrone;
	int	UxTipoLista;
	unsigned char	*UxLista;
} _UxCOneList;

static _UxCOneList             *UxOneListContext;
#define OneList                 UxOneListContext->UxOneList
#define form3                   UxOneListContext->Uxform3
#define separator3              UxOneListContext->Uxseparator3
#define scrolledWindow1         UxOneListContext->UxscrolledWindow1
#define scrolledList1           UxOneListContext->UxscrolledList1
#define pushButton9             UxOneListContext->UxpushButton9
#define pushButton10            UxOneListContext->UxpushButton10
#define textField2              UxOneListContext->UxtextField2
#define arrowButton1            UxOneListContext->UxarrowButton1
#define arrowButton2            UxOneListContext->UxarrowButton2
#define PadroneChiam            UxOneListContext->UxPadroneChiam
#define PosModel                UxOneListContext->UxPosModel
#define PosVariab               UxOneListContext->UxPosVariab
#define ModOrVar                UxOneListContext->UxModOrVar
#define Parent1                 UxOneListContext->UxParent1
#define Padrone                 UxOneListContext->UxPadrone
#define TipoLista               UxOneListContext->UxTipoLista
#define Lista                   UxOneListContext->UxLista



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_OneList();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOneList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOneListContext;
	UxOneListContext = UxContext =
			(_UxCOneList *) UxGetContext( UxWidget );
	{
	Boolean selezione;
	int NumItem,*ListaSel,NumSel,pos;
	char *Def="ALL";
	char Nome[150];
	XmString *ListaItem;
	
	selezione = XmListGetSelectedPos (scrolledList1,&ListaSel,&NumSel);
	get_something (scrolledList1, XmNitems, (void*) &ListaItem);
	get_something (scrolledList1, XmNitemCount, (void*) &NumItem);
	
	/*  Prendo la posizione dell'elemento selezionato se c'e' altrimenti
		prendo la posizione 0 come posizione di default  */
	if (selezione)
	  pos = ListaSel[0] - 1;
	else pos = 0;
	
	if (NumSel != 0)
	  free (ListaSel);
	
	if (NumItem != 0)
	  { 
	  strcpy (Nome,extract_string(ListaItem[pos]));
	  if (ModOrVar == MODELLI)
	    {
	    XmTextFieldSetString (PadroneChiam[3],Nome );
	    set_something (PadroneChiam[0], XmNsensitive, (void*) True);
	    set_something (PadroneChiam[1], XmNsensitive, (void*) True);
	    set_something (PadroneChiam[2], XmNsensitive, (void*) True);
	    XmTextFieldSetString (PadroneChiam[4],Def);
	    XmTextFieldSetString (PadroneChiam[5],"");
	    }
	  else
	    {
	    XmTextFieldSetString (PadroneChiam[1], Nome);
	    set_something (PadroneChiam[0], XmNsensitive, (void*) True);
	    }
	  }
	else
	  {
	  if (ModOrVar == MODELLI)
	    {
	    XmTextFieldSetString (PadroneChiam[3], "" );
	    XmTextFieldSetString (PadroneChiam[4], "" );
	    XmTextFieldSetString (PadroneChiam[5], "" );
	    }
	/* Lore: caso relativo alle variabili. Non vi sono variabili.
	   Annulla il campo testo delle variabili
	*/ 
	  else XmTextFieldSetString (PadroneChiam[1], "" );
	  }
	
	free (PadroneChiam);
	XtDestroyWidget (OneList);
	}
	UxOneListContext = UxSaveCtx;
}

static	void	activateCB_pushButton10( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOneList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOneListContext;
	UxOneListContext = UxContext =
			(_UxCOneList *) UxGetContext( UxWidget );
	{
	if (ModOrVar == MODELLI)
	  set_something (PadroneChiam[0], XmNsensitive, (void*) True);
	else
	  set_something (PadroneChiam[0], XmNsensitive, (void*) True);
	free (PadroneChiam);
	XtDestroyWidget (OneList);
	}
	UxOneListContext = UxSaveCtx;
}

static	void	activateCB_arrowButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOneList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOneListContext;
	UxOneListContext = UxContext =
			(_UxCOneList *) UxGetContext( UxWidget );
	{
	char *Ricerca,Messaggio[50];
	XmString XmRicerca,*XmRicercaList;
	int NumeroElementi,Posizione,*ListaSel,NumSel;
	Boolean Selezionato;
	
	Ricerca = XmTextFieldGetString (textField2);
	XmRicerca = XmStringCreateSimple (Ricerca);
	
	get_something (scrolledList1, XmNitems, (void*) &XmRicercaList);
	get_something (scrolledList1, XmNitemCount, (void*) &NumeroElementi);
	
	Selezionato = XmListGetSelectedPos (scrolledList1, &ListaSel, &NumSel);
	if (Selezionato)
		Posizione = RicercaXmString (XmRicercaList,(XmString)XmRicerca,NumeroElementi,
					SU,ListaSel[NumSel-1]);
	else 	Posizione = RicercaXmString (XmRicercaList,(XmString)XmRicerca,NumeroElementi,
					SU,NumeroElementi+1);
	if (Posizione == 0)
		{
		strcpy (Messaggio,"String not found!\0");
		VisualizzaMessageBox (GENERICA,OneList,Messaggio,scrolledList1);
		}
	else
		{
		XmListSelectPos (scrolledList1,Posizione,True);
		XmListSetPos (scrolledList1,Posizione);
		}
	}
	UxOneListContext = UxSaveCtx;
}

static	void	activateCB_arrowButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCOneList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOneListContext;
	UxOneListContext = UxContext =
			(_UxCOneList *) UxGetContext( UxWidget );
	{
	char *Ricerca,Messaggio[50];
	XmString XmRicerca,*XmRicercaList;
	int NumeroElementi,Posizione,*ListaSel,NumSel;
	Boolean Selezionato;
	
	Ricerca = XmTextFieldGetString (textField2);
	XmRicerca = XmStringCreateSimple (Ricerca);
	
	get_something (scrolledList1, XmNitems, (void*) &XmRicercaList);
	get_something (scrolledList1, XmNitemCount, (void*) &NumeroElementi);
	
	Selezionato = XmListGetSelectedPos (scrolledList1, &ListaSel, &NumSel);
	if (Selezionato)
		Posizione = RicercaXmString (XmRicercaList,(XmString)XmRicerca,NumeroElementi,
					GIU,ListaSel[NumSel-1]);
	else 	Posizione = RicercaXmString (XmRicercaList,(XmString)XmRicerca,NumeroElementi,
					GIU,0);
	if (Posizione == 0)
		{
		strcpy (Messaggio,"String not found!\0");
		VisualizzaMessageBox (GENERICA,OneList,Messaggio,scrolledList1);
		}
	else
		{
		XmListSelectPos (scrolledList1,Posizione,True);
		XmListSetPos (scrolledList1,Posizione);
		}
	}
	UxOneListContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_OneList()
{


	/* Creation of OneList */
	OneList = XtVaCreatePopupShell( "OneList",
			topLevelShellWidgetClass,
			UxTopLevel,
			XmNx, 650,
			XmNy, 29,
			XmNwidth, 460,
			XmNheight, 300,
			XmNiconName, "Selection Window",
			NULL );
	UxPutContext( OneList, (char *) UxOneListContext );


	/* Creation of form3 */
	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass,
			OneList,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 80,
			XmNy, 80,
			XmNwidth, 80,
			XmNheight, 90,
			NULL );
	UxPutContext( form3, (char *) UxOneListContext );


	/* Creation of separator3 */
	separator3 = XtVaCreateManagedWidget( "separator3",
			xmSeparatorWidgetClass,
			form3,
			XmNx, 2,
			XmNy, 240,
			XmNwidth, 440,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomPosition, 82,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNtopPosition, 80,
			NULL );
	UxPutContext( separator3, (char *) UxOneListContext );


	/* Creation of scrolledWindow1 */
	scrolledWindow1 = XtVaCreateManagedWidget( "scrolledWindow1",
			xmScrolledWindowWidgetClass,
			form3,
			XmNx, 20,
			XmNy, 20,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNbottomPosition, 66,
			XmNleftPosition, 5,
			XmNrightPosition, 95,
			XmNtopPosition, 5,
			NULL );
	UxPutContext( scrolledWindow1, (char *) UxOneListContext );


	/* Creation of scrolledList1 */
	scrolledList1 = XtVaCreateManagedWidget( "scrolledList1",
			xmListWidgetClass,
			scrolledWindow1,
			XmNwidth, 420,
			XmNheight, 170,
			XmNlistSizePolicy, XmCONSTANT,
			NULL );
	UxPutContext( scrolledList1, (char *) UxOneListContext );


	/* Creation of pushButton9 */
	pushButton9 = XtVaCreateManagedWidget( "pushButton9",
			xmPushButtonWidgetClass,
			form3,
			XmNx, 20,
			XmNy, 260,
			XmNwidth, 80,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomPosition, 98,
			XmNtopPosition, 85,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 25,
			NULL );
	XtAddCallback( pushButton9, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton9,
		(XtPointer) UxOneListContext );

	UxPutContext( pushButton9, (char *) UxOneListContext );


	/* Creation of pushButton10 */
	pushButton10 = XtVaCreateManagedWidget( "pushButton10",
			xmPushButtonWidgetClass,
			form3,
			XmNx, 110,
			XmNy, 260,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 85,
			XmNleftPosition, 26,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 46,
			NULL );
	XtAddCallback( pushButton10, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton10,
		(XtPointer) UxOneListContext );

	UxPutContext( pushButton10, (char *) UxOneListContext );


	/* Creation of textField2 */
	textField2 = XtVaCreateManagedWidget( "textField2",
			xmTextFieldWidgetClass,
			form3,
			XmNx, 20,
			XmNy, 200,
			XmNwidth, 130,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNmaxLength, 80,
			XmNbottomPosition, 78,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 68,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 35,
			NULL );
	UxPutContext( textField2, (char *) UxOneListContext );


	/* Creation of arrowButton1 */
	arrowButton1 = XtVaCreateManagedWidget( "arrowButton1",
			xmArrowButtonWidgetClass,
			form3,
			XmNx, 150,
			XmNy, 200,
			XmNwidth, 30,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomPosition, 78,
			XmNtopPosition, 68,
			XmNleftPosition, 38,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 45,
			NULL );
	XtAddCallback( arrowButton1, XmNactivateCallback,
		(XtCallbackProc) activateCB_arrowButton1,
		(XtPointer) UxOneListContext );

	UxPutContext( arrowButton1, (char *) UxOneListContext );


	/* Creation of arrowButton2 */
	arrowButton2 = XtVaCreateManagedWidget( "arrowButton2",
			xmArrowButtonWidgetClass,
			form3,
			XmNx, 180,
			XmNy, 200,
			XmNwidth, 30,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNarrowDirection, XmARROW_DOWN,
			XmNbottomPosition, 78,
			XmNtopPosition, 68,
			XmNleftPosition, 45,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 52,
			NULL );
	XtAddCallback( arrowButton2, XmNactivateCallback,
		(XtCallbackProc) activateCB_arrowButton2,
		(XtPointer) UxOneListContext );

	UxPutContext( arrowButton2, (char *) UxOneListContext );


	XtAddCallback( OneList, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxOneListContext);


	return ( OneList );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_OneList( _UxParent1, _UxPadrone, _UxTipoLista, _UxLista )
	Widget	_UxParent1;
	Widget	*_UxPadrone;
	int	_UxTipoLista;
	unsigned char	*_UxLista;
{
	Widget                  rtrn;
	_UxCOneList             *UxContext;

	UxOneListContext = UxContext =
		(_UxCOneList *) UxNewContext( sizeof(_UxCOneList), False );

	Parent1 = _UxParent1;
	Padrone = _UxPadrone;
	TipoLista = _UxTipoLista;
	Lista = _UxLista;

	{
		PadroneChiam = Padrone;
		ModOrVar = TipoLista;
		
		set_something (PadroneChiam[0], XmNsensitive, (void*) False);
		rtrn = _Uxbuild_OneList();

		if (ModOrVar == MODELLI)
			CaricaLista (scrolledList1,Lista,MAX_LUN_NOME_MODELLO,MODELLI);
		else CaricaLista (scrolledList1,Lista,MAX_LUN_NOME_VAR+MAX_LUN_DESCR_VAR,VARIABILI);
		
		/*  Setta la posizione dell'interfaccia secondo la posizione del Parent  */
		InterfaceSetPos (OneList,Parent1);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

