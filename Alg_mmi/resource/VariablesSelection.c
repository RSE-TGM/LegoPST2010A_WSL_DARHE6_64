
/*******************************************************************************
       VariablesSelection.c
       (Generated from interface file VariablesSelection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <X11/Shell.h>



/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo VariablesSelection.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)VariablesSelection.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/*
  Interfaccia per la selezione 
  1) delle variabili da associare ad una porta di I/O (su icon reg)
  2) delle variabili di cambio colore appartenenti a icon reg
  3) delle variabili in input a oggetto DisplayReg
*/

#include <Xl/XlIconReg.h>
#include <Xl/XlPort.h>
#include <Xl/XlDispReg.h>
#include <Ol/OlForm.h>
#include <Ol/OlForm_regol.h>

#include "libutilx.h"
#include "res_edit.h"


//#include <Xl/Xl.h>
//#include <Xl/XlIconReg.h>
//#include <Xl/XlPort.h>
//#include <Ol/OlConn.h>
//#include <Ol/OlCompiler.h>
//#include <Ol/OlDatabaseTopologia.h>
//#include <Ol/OlForm.h>
//#include <Ol/OlForm_regol.h>

/*
#include <Ol/OlCompiler.h>
#include <Ol/OlCompilerP.h>
#include <Ol/OlConn.h>
#include <Ol/OlConnP.h>
#include <Ol/OlDatabasePunti.h>
#include <Ol/OlDatabasePuntiP.h>
#include <Ol/OlDatabaseTopologia.h>
#include <Ol/OlDatabaseTopologiaP.h>
#include <Ol/OlForm.h>
#include <Ol/OlFormP.h>
#include <Ol/OlForm_regol.h>
#include <Ol/OlPert.h>
#include <Ol/OlPertP.h>
#include <Ol/OlTree.h>
#include <Ol/OlTreeP.h>
*/


#include "res_edit.h"

void InserisciAvVar ( );
void InserisciUsVar ( );
/*
void InterfaceSetPos ( );
*/


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
	Widget	UxVariablesSelection;
	Widget	UxmainWindow12;
	Widget	Uxform11;
	Widget	Uxlabel14;
	Widget	UxTipoVar;
	Widget	Uxseparator12;
	Widget	Uxlabel15;
	Widget	Uxseparator13;
	Widget	UxscrolledWindow8;
	Widget	UxAvailList;
	Widget	Uxlabel16;
	Widget	UxscrolledWindow9;
	Widget	UxUsedList;
	Widget	Uxseparator14;
	Widget	UxpushButton20;
	Widget	UxpushButton21;
	Widget	UxParent5;
	Widget	*UxListaWidgetRC;
	Widget	UxOSelezionato;
	Widget	UxPar5;
	Widget	*UxListaRCInp;
	Widget	UxWSel;
} _UxCVariablesSelection;

static _UxCVariablesSelection  *UxVariablesSelectionContext;
#define VariablesSelection      UxVariablesSelectionContext->UxVariablesSelection
#define mainWindow12            UxVariablesSelectionContext->UxmainWindow12
#define form11                  UxVariablesSelectionContext->Uxform11
#define label14                 UxVariablesSelectionContext->Uxlabel14
#define TipoVar                 UxVariablesSelectionContext->UxTipoVar
#define separator12             UxVariablesSelectionContext->Uxseparator12
#define label15                 UxVariablesSelectionContext->Uxlabel15
#define separator13             UxVariablesSelectionContext->Uxseparator13
#define scrolledWindow8         UxVariablesSelectionContext->UxscrolledWindow8
#define AvailList               UxVariablesSelectionContext->UxAvailList
#define label16                 UxVariablesSelectionContext->Uxlabel16
#define scrolledWindow9         UxVariablesSelectionContext->UxscrolledWindow9
#define UsedList                UxVariablesSelectionContext->UxUsedList
#define separator14             UxVariablesSelectionContext->Uxseparator14
#define pushButton20            UxVariablesSelectionContext->UxpushButton20
#define pushButton21            UxVariablesSelectionContext->UxpushButton21
#define Parent5                 UxVariablesSelectionContext->UxParent5
#define ListaWidgetRC           UxVariablesSelectionContext->UxListaWidgetRC
#define OSelezionato            UxVariablesSelectionContext->UxOSelezionato
#define Par5                    UxVariablesSelectionContext->UxPar5
#define ListaRCInp              UxVariablesSelectionContext->UxListaRCInp
#define WSel                    UxVariablesSelectionContext->UxWSel



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_VariablesSelection();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void InserisciAvVar (Widget Lista,int TVar,Widget WS)
{
#ifndef DESIGN_TIME
char *ListaTag,*Stringa,*Tag,*Descr;
char *DaLiberare,*EsaminaTag,*TagAppoggio;
XmString XmTot,XmTag,XmDescr;
OlFormObject PuntForm;
int i,j,NumForm,NumLinee,NumTags;
DESCR_LINE *StrutturaAppoggio;
Widget Fater;

if ( (XlIsIconReg(WS)) || (XlIsDispReg(WS)) )
  {
  if(XlIsDispReg(WS))
        WS=XtParent(WS);
  /*  Prendo tutta la lista delle variabili  */
  get_something (WS, XlNinputValue, (void*) &Stringa); 

  /*  Prendo dall'oggetto il puntatore alla form  */
  get_something (WS, XlNobjectForm, (void*) &PuntForm);

  /*  Ricavo il numero delle linee della form delle variabili  */
  NumLinee = OlGetNumLines (PuntForm,0);
  for (j=0;j<NumLinee;j++)
    {
    StrutturaAppoggio = OlGetLineForm (PuntForm,0,j);
    if (StrutturaAppoggio->line_type == LINE_INP)
      {
      Tag = XtNewString ((char *)StrutturaAppoggio->u.input.tag);
      Descr = EstrTagDescr (PuntForm,OL_FORM_INPUT_VALUE,Tag,2,Stringa);
      XmTag = XmStringCreateSimple (Tag);
      XmDescr = XmStringCreateSimple (Descr);
      XmTot = XmStringConcat (XmTag,XmDescr);

      /*  Aggiungo un item all'oggetto lista  */ 
      XmListAddItemUnselected (Lista,XmTot,0);

      /*  Libero la memoria allocata  */
      XmStringFree (XmTot);
      XmStringFree (XmTag);
      XmStringFree (XmDescr);
      XtFree (Descr);
      XtFree (Tag);
      }
    } 
  }
else if (XlIsPort(WS))
  {
  /*  Prendo il padre della porta che dovrebbe essere l'IconReg  */
  Fater = XtParent (WS);

  /*  Prendo il puntatore allo stringone delle tag  */
  get_something (Fater, XlNinputValue, (void*) &Stringa);

  /*  Prendo ul puntatore alla form  */
  get_something (Fater, XlNobjectForm, (void*) &PuntForm);

  /*  Prendo le tags della form delle variabili  */
  ListaTag = OlGetTags (PuntForm,0);  

  /*  Filtro la lista delle tags secondo il tipo di variabile da 
	visualizzare  */
  switch (TVar)
    {
    case INPUT_PORT_A:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_ANALOG,VAR_NOCOLLEG);
    break;
    case INPUT_PORT_D:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_DIGIT,VAR_NOCOLLEG);
    break;
    case OUTPUT_PORT_A:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_ANALOG,VAR_NOCOLLEG);
    break;
    case OUTPUT_PORT_D:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_DIGIT,VAR_NOCOLLEG);
    break;
    }

  /*  Dalla nuova lista delle tags ricavo quelle che non sono
	state ancora utilizzate in altre porte  */
  DaLiberare = TagAppoggio;
  memcpy (&NumTags, TagAppoggio, sizeof(int) );
  TagAppoggio += sizeof(int);
  for (i=0;i<NumTags;i++)
    {
    EsaminaTag = XtNewString (TagAppoggio);
    if ( !(is_tag_in_port(Fater,EsaminaTag)) )
      {
      Descr = EstrTagDescr(PuntForm,OL_FORM_INPUT_VALUE,EsaminaTag,2,Stringa);
      XmTag = XmStringCreateSimple (EsaminaTag);
      XmDescr = XmStringCreateSimple (Descr);
      XmTot = XmStringConcat (XmTag,XmDescr);

      /*  Aggiungo un item all'oggetto lista  */
      XmListAddItemUnselected (Lista,XmTot,0);

      /*  Libero la memoria utilizzata  */
      XmStringFree (XmTag);
      XmStringFree (XmDescr);
      XmStringFree (XmTot);
      XtFree (Descr);
      XtFree (EsaminaTag);
      }
    TagAppoggio += MAX_L_TAGS;
    }
  XtFree (DaLiberare);
  } /* if (XlIsPort(WS)) */
#endif
}

void InserisciUsVar (Widget Lista,int TVar,Widget WS)
{
#ifndef DESIGN_TIME
char *ListaTag,*Stringa,*Tag,*Descr;
char *DaLiberare,*EsaminaTag,*TagAppoggio;
XmString XmTot,XmTag,XmDescr;
OlFormObject PuntForm;
int i,j,NumForm,NumLinee,NumTags;
DESCR_LINE *StrutturaAppoggio;
Widget Fater;

if (XlIsPort(WS))
  {
  /*  Prendo il padre della porta che dovrebbe essere l'IconReg  */
  Fater = XtParent (WS);

  /*  Prendo il puntatore allo stringone delle tag  */
  get_something (Fater, XlNinputValue, (void*) &Stringa);

  /*  Prendo ul puntatore alla form  */
  get_something (Fater, XlNobjectForm, (void*) &PuntForm);

  /*  Prendo le tags della form delle variabili  */
  ListaTag = OlGetTags (PuntForm,0);  

  /*  Filtro la lista delle tags secondo il tipo di variabile da 
	visualizzare  */
  switch (TVar)
    {
    case INPUT_PORT_A:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_ANALOG,VAR_NOCOLLEG);
    break;
    case INPUT_PORT_D:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_DIGIT,VAR_NOCOLLEG);
    break;
    case OUTPUT_PORT_A:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_ANALOG,VAR_NOCOLLEG);
    break;
    case OUTPUT_PORT_D:
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_DIGIT,VAR_NOCOLLEG);
    break;
    }

  /*  Dalla nuova lista delle tags ricavo quelle che sono gia'
	state utilizzate in altre porte  */
  DaLiberare = TagAppoggio;
  memcpy (&NumTags, TagAppoggio, sizeof(int) );
  TagAppoggio += sizeof(int);
  for (i=0;i<NumTags;i++)
    {
    EsaminaTag = XtNewString (TagAppoggio);
    if ( is_tag_in_port(Fater,EsaminaTag) )
      {
      Descr = EstrTagDescr(PuntForm,OL_FORM_INPUT_VALUE,EsaminaTag,2,Stringa);
      XmTag = XmStringCreateSimple (EsaminaTag);
      XmDescr = XmStringCreateSimple (Descr);
      XmTot = XmStringConcat (XmTag,XmDescr);

      /*  Aggiungo un item all'oggetto lista  */
      XmListAddItemUnselected (Lista,XmTot,0);

      /*  Libero la memoria utilizzata  */
      XmStringFree (XmTag);
      XmStringFree (XmDescr);
      XmStringFree (XmTot);
      XtFree (Descr);
      XtFree (EsaminaTag);
      }
    TagAppoggio += MAX_L_TAGS;
    }
  XtFree (DaLiberare);
  } /* if (XlIsPort(WS)) */
#endif
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton20( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCVariablesSelection  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxVariablesSelectionContext;
	UxVariablesSelectionContext = UxContext =
			(_UxCVariablesSelection *) UxGetContext( UxWidget );
	{
	Boolean Selezione;
	int Posizione,*PosSelected,NumSelected=0;
	XmString *ListaXm;
	char Ritorno[3],ItemSel[200];
	
	/*  Prendo dalla lista delle variabili l'item selezionato  */
	Selezione = XmListGetSelectedPos (AvailList , &PosSelected, &NumSelected);
	
	/*  Esegue l'operazione solo se e' selezionato un item  */
	if (Selezione)
	  {
	  if (NumSelected==1)
	    {
	    /*  Prende dall'oggetto lista l'elenco degli item sotto
			forma di lista di XmString  */
	    get_something (AvailList, XmNitems, (void*) &ListaXm);
	    Posizione = PosSelected[0]-1;
	    strcpy ( ItemSel,extract_string (ListaXm[Posizione]) );
	    strncpy (Ritorno,ItemSel,2);
	    Ritorno[2] = '\0';
	    XmTextFieldSetString (ListaWidgetRC[2],Ritorno);
	    XtFree ((char*)PosSelected);
	    }
	  }
	
	/*  Rimetto a sensitive i bottoni chiamanti  */
	set_something_val (ListaWidgetRC[0], XmNsensitive, (XtArgVal)True);
	set_something_val (ListaWidgetRC[2], XmNsensitive, (XtArgVal)True);
	
	XtDestroyWidget (VariablesSelection);
	}
	UxVariablesSelectionContext = UxSaveCtx;
}

static	void	activateCB_pushButton21( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCVariablesSelection  *UxSaveCtx, *UxContext;

	UxSaveCtx = UxVariablesSelectionContext;
	UxVariablesSelectionContext = UxContext =
			(_UxCVariablesSelection *) UxGetContext( UxWidget );
	{
	/*  Rimetto a sensitive i bottoni chiamanti  */
	set_something_val (ListaWidgetRC[0], XmNsensitive, (XtArgVal)True);
	set_something_val (ListaWidgetRC[2], XmNsensitive, (XtArgVal)True);
	
	XtDestroyWidget (VariablesSelection);
	}
	UxVariablesSelectionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_VariablesSelection()
{
	Widget		_UxParent;


	/* Creation of VariablesSelection */
	_UxParent = Parent5;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	VariablesSelection = XtVaCreatePopupShell( "VariablesSelection",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 516,
			XmNy, 181,
			XmNwidth, 450,
			XmNheight, 550,
			NULL );
	UxPutContext( VariablesSelection, (char *) UxVariablesSelectionContext );


	/* Creation of mainWindow12 */
	mainWindow12 = XtVaCreateManagedWidget( "mainWindow12",
			xmMainWindowWidgetClass,
			VariablesSelection,
			XmNunitType, XmPIXELS,
			XmNx, 140,
			XmNy, 270,
			XmNwidth, 450,
			XmNheight, 470,
			NULL );
	UxPutContext( mainWindow12, (char *) UxVariablesSelectionContext );


	/* Creation of form11 */
	form11 = XtVaCreateManagedWidget( "form11",
			xmFormWidgetClass,
			mainWindow12,
			NULL );
	UxPutContext( form11, (char *) UxVariablesSelectionContext );


	/* Creation of label14 */
	label14 = XtVaCreateManagedWidget( "label14",
			xmLabelWidgetClass,
			form11,
			XmNx, 10,
			XmNy, 10,
			XmNwidth, 200,
			XmNheight, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNfontList, UxConvertFontList( "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "Variable type:" ),
			XmNalignment, XmALIGNMENT_END,
			NULL );
	UxPutContext( label14, (char *) UxVariablesSelectionContext );


	/* Creation of TipoVar */
	TipoVar = XtVaCreateManagedWidget( "TipoVar",
			xmLabelWidgetClass,
			form11,
			XmNx, 210,
			XmNy, 10,
			XmNwidth, 230,
			XmNheight, 40,
			XmNalignment, XmALIGNMENT_CENTER,
			XmNfontList, UxConvertFontList( "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "" ),
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 0,
			XmNleftWidget, label14,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 20,
			XmNresizable, FALSE,
			NULL );
	UxPutContext( TipoVar, (char *) UxVariablesSelectionContext );


	/* Creation of separator12 */
	separator12 = XtVaCreateManagedWidget( "separator12",
			xmSeparatorWidgetClass,
			form11,
			XmNx, 10,
			XmNy, 60,
			XmNwidth, 430,
			XmNheight, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 2,
			NULL );
	UxPutContext( separator12, (char *) UxVariablesSelectionContext );


	/* Creation of label15 */
	label15 = XtVaCreateManagedWidget( "label15",
			xmLabelWidgetClass,
			form11,
			XmNx, 10,
			XmNy, 75,
			XmNwidth, 280,
			XmNheight, 25,
			XmNfontList, UxConvertFontList( "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "Available Variables:" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator12,
			NULL );
	UxPutContext( label15, (char *) UxVariablesSelectionContext );


	/* Creation of separator13 */
	separator13 = XtVaCreateManagedWidget( "separator13",
			xmSeparatorWidgetClass,
			form11,
			XmNx, 0,
			XmNy, 280,
			XmNwidth, 450,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 2,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNbottomOffset, 230,
			NULL );
	UxPutContext( separator13, (char *) UxVariablesSelectionContext );


	/* Creation of scrolledWindow8 */
	scrolledWindow8 = XtVaCreateManagedWidget( "scrolledWindow8",
			xmScrolledWindowWidgetClass,
			form11,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNx, 10,
			XmNy, 110,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNshadowThickness, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, label15,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomWidget, separator13,
			NULL );
	UxPutContext( scrolledWindow8, (char *) UxVariablesSelectionContext );


	/* Creation of AvailList */
	AvailList = XtVaCreateManagedWidget( "AvailList",
			xmListWidgetClass,
			scrolledWindow8,
			XmNwidth, 430,
			XmNheight, 160,
			NULL );
	UxPutContext( AvailList, (char *) UxVariablesSelectionContext );


	/* Creation of label16 */
	label16 = XtVaCreateManagedWidget( "label16",
			xmLabelWidgetClass,
			form11,
			XmNx, 10,
			XmNy, 290,
			XmNwidth, 280,
			XmNheight, 25,
			XmNfontList, UxConvertFontList( "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "Used Variables:" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator13,
			NULL );
	UxPutContext( label16, (char *) UxVariablesSelectionContext );


	/* Creation of scrolledWindow9 */
	scrolledWindow9 = XtVaCreateManagedWidget( "scrolledWindow9",
			xmScrolledWindowWidgetClass,
			form11,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNx, 20,
			XmNy, 321,
			XmNvisualPolicy, XmVARIABLE,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNshadowThickness, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, label16,
			NULL );
	UxPutContext( scrolledWindow9, (char *) UxVariablesSelectionContext );


	/* Creation of UsedList */
	UsedList = XtVaCreateManagedWidget( "UsedList",
			xmListWidgetClass,
			scrolledWindow9,
			XmNwidth, 410,
			XmNheight, 110,
			XmNancestorSensitive, FALSE,
			XmNsensitive, FALSE,
			NULL );
	UxPutContext( UsedList, (char *) UxVariablesSelectionContext );


	/* Creation of separator14 */
	separator14 = XtVaCreateManagedWidget( "separator14",
			xmSeparatorWidgetClass,
			form11,
			XmNx, 0,
			XmNy, 430,
			XmNwidth, 450,
			XmNheight, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, scrolledWindow9,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 2,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 60,
			NULL );
	UxPutContext( separator14, (char *) UxVariablesSelectionContext );


	/* Creation of pushButton20 */
	pushButton20 = XtVaCreateManagedWidget( "pushButton20",
			xmPushButtonWidgetClass,
			form11,
			XmNx, 10,
			XmNy, 500,
			XmNwidth, 80,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			NULL );
	XtAddCallback( pushButton20, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton20,
		(XtPointer) UxVariablesSelectionContext );

	UxPutContext( pushButton20, (char *) UxVariablesSelectionContext );


	/* Creation of pushButton21 */
	pushButton21 = XtVaCreateManagedWidget( "pushButton21",
			xmPushButtonWidgetClass,
			form11,
			XmNx, 100,
			XmNy, 440,
			XmNwidth, 80,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, pushButton20,
			NULL );
	XtAddCallback( pushButton21, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton21,
		(XtPointer) UxVariablesSelectionContext );

	UxPutContext( pushButton21, (char *) UxVariablesSelectionContext );


	XtAddCallback( VariablesSelection, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxVariablesSelectionContext);

	XmMainWindowSetAreas( mainWindow12, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form11 );

	return ( VariablesSelection );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_VariablesSelection( _UxPar5, _UxListaRCInp, _UxWSel )
	Widget	_UxPar5;
	Widget	*_UxListaRCInp;
	Widget	_UxWSel;
{
	Widget                  rtrn;
	_UxCVariablesSelection  *UxContext;

	UxVariablesSelectionContext = UxContext =
		(_UxCVariablesSelection *) UxNewContext( sizeof(_UxCVariablesSelection), False );

	Par5 = _UxPar5;
	ListaRCInp = _UxListaRCInp;
	WSel = _UxWSel;

	{
		char LabTitolo[100];
		int Tipo;
		
		Parent5 = Par5;
		ListaWidgetRC = ListaRCInp;
		OSelezionato = WSel;
		rtrn = _Uxbuild_VariablesSelection();

		/*  Imposto la label per il tipo della variabile  */
		if ( XlIsPort (OSelezionato) )
		  {
		  get_something (OSelezionato, XlNtipoPort, (void*) &Tipo);
		  switch (Tipo)
		    {
		    case INPUT_PORT_A:
		      strcpy (LabTitolo,"ANALOG INPUT");
		      InserisciAvVar (AvailList,INPUT_PORT_A,OSelezionato);
		      InserisciUsVar (UsedList, INPUT_PORT_A,OSelezionato);
		    break;
		    case OUTPUT_PORT_A:
		      strcpy (LabTitolo,"ANALOG OUTPUT"); 
		      InserisciAvVar (AvailList,OUTPUT_PORT_A,OSelezionato);
		      InserisciUsVar (UsedList, OUTPUT_PORT_A,OSelezionato);
		    break;
		    case INPUT_PORT_D:
		      strcpy (LabTitolo,"DIGITAL INPUT");
		      InserisciAvVar (AvailList,INPUT_PORT_D,OSelezionato);
		      InserisciUsVar (UsedList, INPUT_PORT_D,OSelezionato);
		    break;
		    case OUTPUT_PORT_D:
		      strcpy (LabTitolo,"DIGITAL OUTPUT");
		      InserisciAvVar (AvailList,OUTPUT_PORT_D,OSelezionato);
		      InserisciUsVar (UsedList, OUTPUT_PORT_D,OSelezionato);
		    break;
		    }
		  }
		else if ( (XlIsIconReg (OSelezionato)) || (XlIsDispReg(OSelezionato)) )
		       {
		       strcpy(LabTitolo,"ALL VARIABLES");
		       InserisciAvVar (AvailList,ALL_VAR,OSelezionato);	
		       }
		
		/*  Setto la label del titolo relativo al tipo della variabile
			visualizzata  */
		set_something_val (TipoVar, XmNlabelString, (XtArgVal)XmStringCreateSimple(LabTitolo));
		
		InterfaceSetPos (VariablesSelection,Parent5);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

