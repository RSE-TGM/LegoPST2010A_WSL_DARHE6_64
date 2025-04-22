
/*******************************************************************************
       TwoList.c
       (Generated from interface file TwoList.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/ArrowB.h>
#include <Xm/TextF.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo TwoList.i
   tipo 
   release 5.2
   data 2/6/96
   reserved @(#)TwoList.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <string.h>
#include <Ol/OlDatabaseTopologia.h>
#include "VarEdit.h"
#include "res_edit.h"
#include "sim_param.h"


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
	Widget	UxTwoList;
	Widget	Uxform4;
	Widget	Uxseparator4;
	Widget	UxpushButton11;
	Widget	UxpushButton12;
	Widget	UxtextField3;
	Widget	UxarrowButton3;
	Widget	UxarrowButton4;
	Widget	UxscrolledWindow3;
	Widget	UxscrolledList3;
	Widget	Uxseparator5;
	Widget	UxscrolledWindow2;
	Widget	UxscrolledList2;
	Widget	Uxlabel5;
	Widget	Uxlabel6;
	Widget	UxpushButton16;
	Widget	*UxPadChiam;
	Widget	UxOggetto2;
	OlDatabaseTopologiaObject	UxDbt;
	unsigned char	*UxListaDeiModuli;
	unsigned char	*UxListaDeiBlocchi;
	int	*UxPosBloc;
	int	UxOptSel;
	Widget	UxParent2;
	OlDatabaseTopologiaObject	UxDbTop;
	Widget	*UxPadInp;
	unsigned char	*UxModuli;
	unsigned char	*UxBlocchi;
	int	UxOpzione;
	Widget	UxOggSel;
} _UxCTwoList;

static _UxCTwoList             *UxTwoListContext;
#define TwoList                 UxTwoListContext->UxTwoList
#define form4                   UxTwoListContext->Uxform4
#define separator4              UxTwoListContext->Uxseparator4
#define pushButton11            UxTwoListContext->UxpushButton11
#define pushButton12            UxTwoListContext->UxpushButton12
#define textField3              UxTwoListContext->UxtextField3
#define arrowButton3            UxTwoListContext->UxarrowButton3
#define arrowButton4            UxTwoListContext->UxarrowButton4
#define scrolledWindow3         UxTwoListContext->UxscrolledWindow3
#define scrolledList3           UxTwoListContext->UxscrolledList3
#define separator5              UxTwoListContext->Uxseparator5
#define scrolledWindow2         UxTwoListContext->UxscrolledWindow2
#define scrolledList2           UxTwoListContext->UxscrolledList2
#define label5                  UxTwoListContext->Uxlabel5
#define label6                  UxTwoListContext->Uxlabel6
#define pushButton16            UxTwoListContext->UxpushButton16
#define PadChiam                UxTwoListContext->UxPadChiam
#define Oggetto2                UxTwoListContext->UxOggetto2
#define Dbt                     UxTwoListContext->UxDbt
#define ListaDeiModuli          UxTwoListContext->UxListaDeiModuli
#define ListaDeiBlocchi         UxTwoListContext->UxListaDeiBlocchi
#define PosBloc                 UxTwoListContext->UxPosBloc
#define OptSel                  UxTwoListContext->UxOptSel
#define Parent2                 UxTwoListContext->UxParent2
#define DbTop                   UxTwoListContext->UxDbTop
#define PadInp                  UxTwoListContext->UxPadInp
#define Moduli                  UxTwoListContext->UxModuli
#define Blocchi                 UxTwoListContext->UxBlocchi
#define Opzione                 UxTwoListContext->UxOpzione
#define OggSel                  UxTwoListContext->UxOggSel



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_TwoList();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton11( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTwoList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTwoListContext;
	UxTwoListContext = UxContext =
			(_UxCTwoList *) UxGetContext( UxWidget );
	{
	Boolean selezione;
	int *ListaSel,NumSel,pos;
	char *NomeAppo,*DefVar,*NomeModello,NomeModulo[5],*Nome;
	XmString *ListaItem;
	
	selezione = XmListGetSelectedPos (scrolledList2,&ListaSel,&NumSel);
	get_something (scrolledList2, XmNitems, (void*) &ListaItem);
	
	if (selezione)
		{
		pos = ListaSel[0] - 1;
		Nome = XtNewString ((char *)extract_string(ListaItem[pos]));
		XmTextFieldSetString (PadChiam[1],Nome );
		XmTextFieldSetString (PadChiam[2],"");
		set_something (PadChiam[0], XmNsensitive, (void*) True);
		if (pos != 0)
		  {
#ifndef ON_MMI
		  if ( XlIsAnimateIcon (Oggetto2) )
		    {
		    NomeModello = XmTextFieldGetString (PadChiam[3]);
		    NomeAppo = Nome;
		    NomeAppo += 32;
		    strncpy (NomeModulo,NomeAppo,4);
		    DefVar = (char *)OlGetDefVarCC (Dbt,NomeModulo,Nome,NomeModello);
		    if (DefVar)
		      XmTextFieldSetString (PadChiam[2],DefVar);
		    free (DefVar);
		    free (NomeModello);
		    free (Nome);
	            }
#endif
	          }
		}
	else
		{
		Nome = XtNewString ((char *)extract_string(ListaItem[0]));
		XmTextFieldSetString (PadChiam[1],Nome);
		XmTextFieldSetString (PadChiam[2],"");
		set_something (PadChiam[0], XmNsensitive, (void*) True);
		free (Nome);
		}
	
	if (selezione)
	  free (ListaSel);
	free (PadChiam);
	XtDestroyWidget (TwoList);
	}
	UxTwoListContext = UxSaveCtx;
}

static	void	activateCB_pushButton12( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTwoList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTwoListContext;
	UxTwoListContext = UxContext =
			(_UxCTwoList *) UxGetContext( UxWidget );
	{
	set_something (PadChiam[0], XmNsensitive, (void*) True);
	free (PadChiam);
	XtDestroyWidget (TwoList);
	}
	UxTwoListContext = UxSaveCtx;
}

static	void	activateCB_arrowButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTwoList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTwoListContext;
	UxTwoListContext = UxContext =
			(_UxCTwoList *) UxGetContext( UxWidget );
	{
	char *Ricerca,Messaggio[50];
	XmString XmRicerca,*XmRicercaList;
	int NumeroElementi,Posizione,*ListaSel,NumSel;
	Boolean Selezionato;
	
	Ricerca = XmTextFieldGetString (textField3);
	XmRicerca = XmStringCreateSimple (Ricerca);
	
	get_something (scrolledList2, XmNitems, (void*) &XmRicercaList);
	get_something (scrolledList2, XmNitemCount, (void*) &NumeroElementi);
	
	Selezionato = XmListGetSelectedPos (scrolledList2, &ListaSel, &NumSel);
	if (Selezionato)
		Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,
					SU,ListaSel[NumSel-1]);
	else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,
					SU,NumeroElementi+1);
	if (Posizione == 0)
		{
		strcpy (Messaggio,"String not found!\0");
		VisualizzaMessageBox (GENERICA,TwoList,Messaggio,scrolledList2);
		}
	else
		{
		XmListSelectPos (scrolledList2,Posizione,True);
		XmListSetPos (scrolledList2,Posizione);
		}
	}
	UxTwoListContext = UxSaveCtx;
}

static	void	activateCB_arrowButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTwoList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTwoListContext;
	UxTwoListContext = UxContext =
			(_UxCTwoList *) UxGetContext( UxWidget );
	{
	char *Ricerca,Messaggio[50];
	XmString XmRicerca,*XmRicercaList;
	int NumeroElementi,Posizione,*ListaSel,NumSel;
	Boolean Selezionato;
	
	Ricerca = XmTextFieldGetString (textField3);
	XmRicerca = XmStringCreateSimple (Ricerca);
	
	get_something (scrolledList2, XmNitems, (void*) &XmRicercaList);
	get_something (scrolledList2, XmNitemCount, (void*) &NumeroElementi);
	
	Selezionato = XmListGetSelectedPos (scrolledList2, &ListaSel, &NumSel);
	if (Selezionato)
		Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,
					GIU,ListaSel[NumSel-1]);
	else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,
					GIU,0);
	if (Posizione == 0)
		{
		strcpy (Messaggio,"String not found!\0");
		VisualizzaMessageBox (GENERICA,TwoList,Messaggio,scrolledList2);
		}
	else
		{
		XmListSelectPos (scrolledList2,Posizione,True);
		XmListSetPos (scrolledList2,Posizione);
		}
	}
	UxTwoListContext = UxSaveCtx;
}

static	void	activateCB_pushButton16( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTwoList             *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTwoListContext;
	UxTwoListContext = UxContext =
			(_UxCTwoList *) UxGetContext( UxWidget );
	{
	XmString *ListaXm;
	int pos,posiz,*ListaSel,NumSel,selezionato;
	char *ListaModuliFilter,*ListaBl,*Stringa;
	char *ListaDaDistruggere,*NomeMod;
	int NumeroBlocchi;
	char Appo[200],*Appoggio,*p,*ListaAppoggio;
	
	selezionato = 0;
	NomeMod = XmTextFieldGetString (PadChiam[3]);
	selezionato = XmListGetSelectedPos (scrolledList3, &ListaSel, &NumSel);
	get_something (scrolledList3, XmNitems, (void*) &ListaXm);
	
	if ( (selezionato==1) && (ListaSel[0] != 1) )
	  {
	  posiz = ListaSel[0]-1;
	  Stringa = (char *)extract_string (ListaXm[posiz]);
	
	  switch (OptSel)
	    {
	    case COMPONENT:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);
	    break;
	    case ALL:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);
	    break;
	    case SUBSYSTEM:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);
	    break;
	    }
	  XtFree (Stringa);
	  }
	else
	  {
	  Stringa = (char *)extract_string (ListaXm[0]);
	  switch (OptSel)
	    {
	    case COMPONENT:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);
	      ListaModuliFilter = (char *)OlGetModulFromComponent (Dbt,Stringa);
	      ListaBl = (char *)BlocksFilterFromComponent (ListaBl,ListaModuliFilter);
	      XtFree (ListaModuliFilter);
	    break;
	    case ALL:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);
	    break;
	    case SUBSYSTEM:
	      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);
	    break;
	    }
	  XtFree (Stringa);
	  }
	XmListDeleteAllItems (scrolledList2);
	XtFree (ListaSel);
	
	/********************
		Lettura dalla lista dei moduli della voce selezionata
	********************/
	selezionato = 0;
	selezionato = XmListGetSelectedPos (scrolledList3, &ListaSel, &NumSel); 
	
	if ( (selezionato==0) || (ListaSel[0]==1) )
		{
		Appoggio = XtNewString ("-- ALL --");
		}
	else
		{
		strcpy (Appo," ALL ---->");
		get_something (scrolledList3, XmNitems, (void*) &ListaXm);
		pos = ListaSel[0]-1;
		Appoggio = XtNewString (extract_string (ListaXm[pos]) );
		strcat (Appo,Appoggio);
		strcat (Appo,"<----");
		XtFree (Appoggio);
		Appoggio = XtCalloc (strlen(Appo)+1,sizeof(char));
		strcpy (Appoggio,Appo); 
		}
	
	/********************
		Aggiunta alla lista blocchi della voce "all"  
	********************/
	ListaDaDistruggere = ListaBl;
	memcpy (&NumeroBlocchi , ListaBl, sizeof(int) );
	NumeroBlocchi++;
	
	ListaBl += sizeof(int);
	ListaAppoggio = (char *)XtCalloc ( sizeof(int)+(NumeroBlocchi*
					MAX_LUN_NOME_BLOCCO), sizeof(char) );
	memcpy (ListaAppoggio, &NumeroBlocchi, sizeof(int) ); 
	p = ListaAppoggio;
	p += sizeof(int);
	strcpy (p, Appoggio);
	p += MAX_LUN_NOME_BLOCCO;
	XtFree (Appoggio);
	memcpy (p, ListaBl, (NumeroBlocchi-1)*MAX_LUN_NOME_BLOCCO);
	
	XtFree (ListaDaDistruggere);
	
	ListaBl = ListaAppoggio;	 
	
	CaricaLista (scrolledList2,ListaBl,MAX_LUN_NOME_BLOCCO,GENERALE);
	XtFree (NomeMod);
	XtFree (ListaSel);
	}
	UxTwoListContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_TwoList()
{


	/* Creation of TwoList */
	TwoList = XtVaCreatePopupShell( "TwoList",
			topLevelShellWidgetClass,
			UxTopLevel,
			XmNx, 95,
			XmNy, 153,
			XmNwidth, 460,
			XmNheight, 590,
			XmNiconName, "Selection Window",
			NULL );
	UxPutContext( TwoList, (char *) UxTwoListContext );


	/* Creation of form4 */
	form4 = XtVaCreateManagedWidget( "form4",
			xmFormWidgetClass,
			TwoList,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 110,
			XmNy, 220,
			XmNwidth, 460,
			XmNheight, 590,
			NULL );
	UxPutContext( form4, (char *) UxTwoListContext );


	/* Creation of separator4 */
	separator4 = XtVaCreateManagedWidget( "separator4",
			xmSeparatorWidgetClass,
			form4,
			XmNx, 7,
			XmNy, 532,
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
			XmNbottomPosition, 92,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNtopPosition, 91,
			NULL );
	UxPutContext( separator4, (char *) UxTwoListContext );


	/* Creation of pushButton11 */
	pushButton11 = XtVaCreateManagedWidget( "pushButton11",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 25,
			XmNy, 552,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 93,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 25,
			NULL );
	XtAddCallback( pushButton11, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton11,
		(XtPointer) UxTwoListContext );

	UxPutContext( pushButton11, (char *) UxTwoListContext );


	/* Creation of pushButton12 */
	pushButton12 = XtVaCreateManagedWidget( "pushButton12",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 115,
			XmNy, 552,
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
			XmNtopPosition, 93,
			XmNleftPosition, 27,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 47,
			NULL );
	XtAddCallback( pushButton12, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton12,
		(XtPointer) UxTwoListContext );

	UxPutContext( pushButton12, (char *) UxTwoListContext );


	/* Creation of textField3 */
	textField3 = XtVaCreateManagedWidget( "textField3",
			xmTextFieldWidgetClass,
			form4,
			XmNx, 25,
			XmNy, 492,
			XmNwidth, 130,
			XmNheight, 30,
			XmNmaxLength, 80,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 89,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 4,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 32,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 83,
			NULL );
	UxPutContext( textField3, (char *) UxTwoListContext );


	/* Creation of arrowButton3 */
	arrowButton3 = XtVaCreateManagedWidget( "arrowButton3",
			xmArrowButtonWidgetClass,
			form4,
			XmNx, 155,
			XmNy, 492,
			XmNwidth, 30,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 89,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 34,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 41,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 83,
			NULL );
	XtAddCallback( arrowButton3, XmNactivateCallback,
		(XtCallbackProc) activateCB_arrowButton3,
		(XtPointer) UxTwoListContext );

	UxPutContext( arrowButton3, (char *) UxTwoListContext );


	/* Creation of arrowButton4 */
	arrowButton4 = XtVaCreateManagedWidget( "arrowButton4",
			xmArrowButtonWidgetClass,
			form4,
			XmNx, 185,
			XmNy, 492,
			XmNwidth, 30,
			XmNheight, 30,
			XmNarrowDirection, XmARROW_DOWN,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 89,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 42,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 49,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 83,
			NULL );
	XtAddCallback( arrowButton4, XmNactivateCallback,
		(XtCallbackProc) activateCB_arrowButton4,
		(XtPointer) UxTwoListContext );

	UxPutContext( arrowButton4, (char *) UxTwoListContext );


	/* Creation of scrolledWindow3 */
	scrolledWindow3 = XtVaCreateManagedWidget( "scrolledWindow3",
			xmScrolledWindowWidgetClass,
			form4,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNx, 20,
			XmNy, 50,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNshadowThickness, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 32,
			XmNleftPosition, 5,
			XmNrightPosition, 95,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 8,
			NULL );
	UxPutContext( scrolledWindow3, (char *) UxTwoListContext );


	/* Creation of scrolledList3 */
	scrolledList3 = XtVaCreateManagedWidget( "scrolledList3",
			xmListWidgetClass,
			scrolledWindow3,
			XmNwidth, 410,
			XmNheight, 150,
			XmNlistSizePolicy, XmRESIZE_IF_POSSIBLE,
			NULL );
	UxPutContext( scrolledList3, (char *) UxTwoListContext );


	/* Creation of separator5 */
	separator5 = XtVaCreateManagedWidget( "separator5",
			xmSeparatorWidgetClass,
			form4,
			XmNx, 10,
			XmNy, 210,
			XmNwidth, 420,
			XmNheight, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 36,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNtopPosition, 34,
			NULL );
	UxPutContext( separator5, (char *) UxTwoListContext );


	/* Creation of scrolledWindow2 */
	scrolledWindow2 = XtVaCreateManagedWidget( "scrolledWindow2",
			xmScrolledWindowWidgetClass,
			form4,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNx, 25,
			XmNy, 312,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNshadowThickness, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 82,
			XmNleftPosition, 5,
			XmNrightPosition, 95,
			XmNtopPosition, 44,
			NULL );
	UxPutContext( scrolledWindow2, (char *) UxTwoListContext );


	/* Creation of scrolledList2 */
	scrolledList2 = XtVaCreateManagedWidget( "scrolledList2",
			xmListWidgetClass,
			scrolledWindow2,
			XmNwidth, 420,
			XmNheight, 170,
			XmNlistSizePolicy, XmRESIZE_IF_POSSIBLE,
			NULL );
	UxPutContext( scrolledList2, (char *) UxTwoListContext );


	/* Creation of label5 */
	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass,
			form4,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 120,
			XmNheight, 30,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			RES_CONVERT( XmNlabelString, "MODULES" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNbottomPosition, 7,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 50,
			XmNtopPosition, 2,
			NULL );
	UxPutContext( label5, (char *) UxTwoListContext );


	/* Creation of label6 */
	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass,
			form4,
			XmNx, 20,
			XmNy, 230,
			XmNwidth, 120,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "BLOCKS" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 50,
			XmNbottomPosition, 43,
			XmNtopPosition, 37,
			NULL );
	UxPutContext( label6, (char *) UxTwoListContext );


	/* Creation of pushButton16 */
	pushButton16 = XtVaCreateManagedWidget( "pushButton16",
			xmPushButtonWidgetClass,
			form4,
			XmNx, 210,
			XmNy, 550,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "FILTER" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 98,
			XmNtopPosition, 93,
			XmNleftPosition, 49,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 69,
			NULL );
	XtAddCallback( pushButton16, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton16,
		(XtPointer) UxTwoListContext );

	UxPutContext( pushButton16, (char *) UxTwoListContext );


	XtAddCallback( TwoList, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTwoListContext);


	return ( TwoList );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_TwoList( _UxParent2, _UxDbTop, _UxPadInp, _UxModuli, _UxBlocchi, _UxOpzione, _UxOggSel )
	Widget	_UxParent2;
	OlDatabaseTopologiaObject	_UxDbTop;
	Widget	*_UxPadInp;
	unsigned char	*_UxModuli;
	unsigned char	*_UxBlocchi;
	int	_UxOpzione;
	Widget	_UxOggSel;
{
	Widget                  rtrn;
	_UxCTwoList             *UxContext;

	UxTwoListContext = UxContext =
		(_UxCTwoList *) UxNewContext( sizeof(_UxCTwoList), False );

	Parent2 = _UxParent2;
	DbTop = _UxDbTop;
	PadInp = _UxPadInp;
	Moduli = _UxModuli;
	Blocchi = _UxBlocchi;
	Opzione = _UxOpzione;
	OggSel = _UxOggSel;

	{
		int Num;
		
		PadChiam = PadInp;
		ListaDeiModuli = Moduli;
		ListaDeiBlocchi = Blocchi;
		OptSel = Opzione;
		Dbt = DbTop;
		Oggetto2 = OggSel;
		
		set_something (PadChiam[0], XmNsensitive, (void*) False);
		rtrn = _Uxbuild_TwoList();

		if (ListaDeiModuli == NULL)
			{
			set_something (scrolledList3, XmNsensitive, (void*) False);
			set_something (pushButton16, XmNsensitive, (void*) False);
			}
		else
			CaricaLista (scrolledList3,ListaDeiModuli,5,GENERALE);
		
		CaricaLista (scrolledList2,ListaDeiBlocchi,MAX_LUN_NOME_BLOCCO,GENERALE);
		
		/*  Setta la posizione dell'interfaccia secondo il Parent  */
		InterfaceSetPos (TwoList,Parent2);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

