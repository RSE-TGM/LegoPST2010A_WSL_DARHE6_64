
/*******************************************************************************
       TagsInput.c
       (Generated from interface file TagsInput.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo TagsInput.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)TagsInput.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/*
 * interfaccia che presenta il contenuto delle form.
   Presenta i campi editabili e le label descritte dalla
   form riempite dei valori di default (se non e' mai stato
   fatto l'input dei valori) o i valori contenuti nella stringa 
   descrittiva (stringone) che costituisce la risorsa
   input value.
   E' utilizzata per le diverse form presenti (per regolazione 
   sia input dati che input variabili).
*/

#include <Xm/RowColumn.h>
#include <Xm/ToggleB.h>
#ifndef DESIGN_TIME
#include <Xm/TextF.h>
#endif
#include <Xl/XlIconReg.h>
#include <Ol/OlForm.h>

extern Widget CreaLabel();
extern Widget CreaTextField();

char *LeggiParametro( );
char *PosizionaPuntatore ( );
char *EstraiTags ( );


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
	Widget	UxTagsInput;
	Widget	UxmainWindow11;
	Widget	Uxform10;
	Widget	Uxseparator11;
	Widget	UxpushButton18;
	Widget	UxpushButton19;
	Widget	UxTitoloForm;
	Widget	UxTagsWindow;
	Widget	UxBottoneTag;
	Widget	UxSelectedWidget;
	Widget	UxCont0;
	OlFormObject	UxFormDiConf;
	int	UxIndiceForm;
	unsigned char	**UxValoriInput;
	Widget	UxParente3;
	Widget	UxBot;
	OlFormObject	UxFrm;
	int	UxIndex;
	Widget	UxOggSelezionato;
	unsigned char	**UxTagsInp;
} _UxCTagsInput;

static _UxCTagsInput           *UxTagsInputContext;
#define TagsInput               UxTagsInputContext->UxTagsInput
#define mainWindow11            UxTagsInputContext->UxmainWindow11
#define form10                  UxTagsInputContext->Uxform10
#define separator11             UxTagsInputContext->Uxseparator11
#define pushButton18            UxTagsInputContext->UxpushButton18
#define pushButton19            UxTagsInputContext->UxpushButton19
#define TitoloForm              UxTagsInputContext->UxTitoloForm
#define TagsWindow              UxTagsInputContext->UxTagsWindow
#define BottoneTag              UxTagsInputContext->UxBottoneTag
#define SelectedWidget          UxTagsInputContext->UxSelectedWidget
#define Cont0                   UxTagsInputContext->UxCont0
#define FormDiConf              UxTagsInputContext->UxFormDiConf
#define IndiceForm              UxTagsInputContext->UxIndiceForm
#define ValoriInput             UxTagsInputContext->UxValoriInput
#define Parente3                UxTagsInputContext->UxParente3
#define Bot                     UxTagsInputContext->UxBot
#define Frm                     UxTagsInputContext->UxFrm
#define Index                   UxTagsInputContext->UxIndex
#define OggSelezionato          UxTagsInputContext->UxOggSelezionato
#define TagsInp                 UxTagsInputContext->UxTagsInp



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_TagsInput();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

/******************************************************
	Legge dalla lista di tutti i defaults della form il parametro
	puntato dalla Stringa e lo ritorna e fa puntare Stringa 
	al parametro successivo della lista  
******************************************************/
char *LeggiParametro(char **Stringa)
{
char *StrRet,Ritorno[200];
char *Appoggio;
int i;

Appoggio = *Stringa;
i = 0;
while (Appoggio[0] != '|')
  {
  Ritorno[i] = Appoggio[0];
  Appoggio++;
  i++;
  }
Appoggio++;
Ritorno[i] = '\0';

/*  Faccio puntare stringa al nuovo parametro  */
if(Appoggio[0] != NULL)
        {
	while (Appoggio[0] != '|') Appoggio++;
	Appoggio++;
	}
*Stringa = Appoggio;

StrRet = XtCalloc ( strlen(Ritorno)+1 , sizeof(char) );
strcpy (StrRet,Ritorno);
return (StrRet);
}

/**************************************************************
	Restituisce un puntatore al primo parametro nella lista dei defaults
	della form shiftando secondo l'indice di form richiesto
**************************************************************/
char *PosizionaPuntatore (OlFormObject frm,int indice_form,char *Str)
{
int NumeroDelleForm,NumeroDelleTags;
int i,indice,Numero;
char *Ritorno;

indice=0;

/*  Se l'indice di form e' maggiore di quelle esistenti ritorno 
	subito NULL  */ 
NumeroDelleForm = OlGetNumForms (frm);
if ( indice_form >= NumeroDelleForm )
  return (NULL);

/*  Se il numero delle tags della form specificata e' uguale a 0
	ritorno subito NULL  */
NumeroDelleTags = OlGetNumTags (frm,indice_form);
if ( NumeroDelleTags == 0 )
  return (NULL);

Ritorno = strstr(Str,"|");
Ritorno++;

while (indice<indice_form)
  {
  Numero = OlGetNumTags (frm,indice);
  if (Numero==0) return (NULL);
  for (i=0;i<(Numero*4);i++)
    {
    Ritorno = strstr (Ritorno,"|");
    Ritorno++;
    }
  indice++; 
  }

return (Ritorno);
}

/********************************************************
	Restituisce una stringa contenente i dati e le descrizioni delle 
	tag relative alla form richiesta 
********************************************************/
char *EstraiTags (OlFormObject form,int indice_form,char *Stringone)
{
char *Ritorno,*Appoggio,*PuntInizio,*PuntFine;

Appoggio = XtNewString (Stringone);

PuntInizio = PosizionaPuntatore (form,indice_form,Appoggio);
if (PuntInizio==NULL)
  return (NULL);

PuntInizio -= 1;

PuntFine = PosizionaPuntatore (form,indice_form+1,Appoggio);
if (PuntFine != NULL)
  (PuntFine-2)[0] = '\0';

Ritorno = XtNewString (PuntInizio);
XtFree (Appoggio);

return (Ritorno);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton18( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTagsInput           *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTagsInputContext;
	UxTagsInputContext = UxContext =
			(_UxCTagsInput *) UxGetContext( UxWidget );
	{
	Widget *ListaFigli,*FigliSet;
	int i,NumFigli,NumFigliSet,IndiceCiclo;
	char *Fittizio;
	char *PuntInizio;
	char *PuntCursore;
	char *PuntAppoggio;
	char *NuovaStringa=NULL;
	char *Value,*Descr;
	
	/*  Salvo il puntatore della stringa  */
	PuntAppoggio = XtNewString (*ValoriInput);
	
	/*  Estraggo i dati relativi alle form precedenti a quella che mi interessa */
	for (i=0;i<IndiceForm;i++)
	  {
	  PuntCursore = EstraiTags(FormDiConf,i,PuntAppoggio);
	  if (NuovaStringa==NULL)
	    {
	    NuovaStringa = XtCalloc (strlen (PuntCursore)+1,sizeof(char));
	    strcpy (NuovaStringa,PuntCursore);
	    } 
	  else
	    {
	    NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+
				strlen(PuntCursore)+2)*sizeof(char));
	    strcat (NuovaStringa," ");
	    strcat (NuovaStringa,PuntCursore);
	    }
	  XtFree (PuntCursore);
	  }
	
	/*  Prendo i figli del rowcolumn che contiene tutti i dati  */
	get_something (Cont0, XmNchildren, &ListaFigli);
	get_something (Cont0, XmNnumChildren, &NumFigli);
	for (i=0;i<NumFigli;i++)
	  {
	  get_something (ListaFigli[i], XmNchildren, &FigliSet);
	  get_something (ListaFigli[i], XmNnumChildren, &NumFigliSet);
	  if (NumFigliSet > 1)
	    {
	    /*  E' una riga con i text filed per i valori  */
	    Value = (char *)XmTextFieldGetString (FigliSet[1]);
	    Descr = (char *)XmTextFieldGetString (FigliSet[2]);
	    /*  Rialloco la stringa per contenere i nuovi dati  */
	    if (NuovaStringa == NULL)
	      {
	      NuovaStringa = XtCalloc (strlen(Value)+strlen(Descr)+6,sizeof(char));
	      strcpy (NuovaStringa,"|");
	      if(strlen(Value)==0)
		strcat(NuovaStringa," ");
	      else
	      	strcat (NuovaStringa,Value);
	      strcat (NuovaStringa,"| |");
	      if(strlen(Descr)==0)
		strcat(NuovaStringa," ");
	      else
	      	strcat (NuovaStringa,Descr);
	      strcat (NuovaStringa,"|");
	      }
	    else
	      {
	      NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+
			strlen(Value)+strlen(Descr)+7)*sizeof(char));
				/*  4 PIPE di separazione,2 spazi e il terminatore */
	      /*  Accodo Value e Descr separati dal PIPE  */ 
	      strcat (NuovaStringa," |");
	      if(strlen(Value)==0)
		strcat(NuovaStringa," ");
	      else
	      	strcat (NuovaStringa,Value);
	      strcat (NuovaStringa,"| |");
	      if(strlen(Descr)==0)
		strcat(NuovaStringa," ");
	      else
	      	strcat (NuovaStringa,Descr);
	      strcat (NuovaStringa,"|");
	      }
	    XtFree (Value);
	    XtFree (Descr);
	    }
	  }
	
	/*  Libero la vecchia lista  */
	XtFree (PuntAppoggio);
	
	/*  Accodo alla lista una eventuale parte restante della stringa  */
	IndiceCiclo = OlGetNumForms (FormDiConf);
	i=IndiceForm+1;
	while (i<IndiceCiclo)
	  {
	  PuntCursore = EstraiTags (FormDiConf,IndiceForm+1,*ValoriInput);
	  if (PuntCursore != NULL)
	    {
	    NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+
				strlen(PuntCursore)+2)*sizeof(char));
	    strcat (NuovaStringa," ");
	    strcat (NuovaStringa,PuntCursore);
	    }
	  i++;
	  }
	
	*ValoriInput = NuovaStringa;
	
	/*  Rimetto a sensitive il bottone chiamante  */
	set_something (BottoneTag, XmNsensitive, True);
	
	XtDestroyWidget (TagsInput);
	}
	UxTagsInputContext = UxSaveCtx;
}

static	void	activateCB_pushButton19( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCTagsInput           *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTagsInputContext;
	UxTagsInputContext = UxContext =
			(_UxCTagsInput *) UxGetContext( UxWidget );
	{
	/*  Rimetto a sensitive il bottone chiamante */
	set_something (BottoneTag, XmNsensitive, True);
	
	XtDestroyWidget (TagsInput);
	}
	UxTagsInputContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_TagsInput()
{


	/* Creation of TagsInput */
	TagsInput = XtVaCreatePopupShell( "TagsInput",
			topLevelShellWidgetClass,
			UxTopLevel,
			XmNx, 655,
			XmNy, 99,
			XmNwidth, 600,
			XmNheight, 440,
			NULL );
	UxPutContext( TagsInput, (char *) UxTagsInputContext );


	/* Creation of mainWindow11 */
	mainWindow11 = XtVaCreateManagedWidget( "mainWindow11",
			xmMainWindowWidgetClass,
			TagsInput,
			XmNunitType, XmPIXELS,
			XmNx, 40,
			XmNy, 60,
			XmNwidth, 600,
			XmNheight, 440,
			NULL );
	UxPutContext( mainWindow11, (char *) UxTagsInputContext );


	/* Creation of form10 */
	form10 = XtVaCreateManagedWidget( "form10",
			xmFormWidgetClass,
			mainWindow11,
			NULL );
	UxPutContext( form10, (char *) UxTagsInputContext );


	/* Creation of separator11 */
	separator11 = XtVaCreateManagedWidget( "separator11",
			xmSeparatorWidgetClass,
			form10,
			XmNx, 10,
			XmNy, 270,
			XmNwidth, 550,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 60,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 2,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			NULL );
	UxPutContext( separator11, (char *) UxTagsInputContext );


	/* Creation of pushButton18 */
	pushButton18 = XtVaCreateManagedWidget( "pushButton18",
			xmPushButtonWidgetClass,
			form10,
			XmNx, 10,
			XmNy, 300,
			XmNwidth, 90,
			XmNheight, 40,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			RES_CONVERT( XmNlabelString, "OK" ),
			NULL );
	XtAddCallback( pushButton18, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton18,
		(XtPointer) UxTagsInputContext );

	UxPutContext( pushButton18, (char *) UxTagsInputContext );


	/* Creation of pushButton19 */
	pushButton19 = XtVaCreateManagedWidget( "pushButton19",
			xmPushButtonWidgetClass,
			form10,
			XmNx, 110,
			XmNy, 300,
			XmNwidth, 90,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, pushButton18,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			NULL );
	XtAddCallback( pushButton19, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton19,
		(XtPointer) UxTagsInputContext );

	UxPutContext( pushButton19, (char *) UxTagsInputContext );


	/* Creation of TitoloForm */
	TitoloForm = XtVaCreateManagedWidget( "TitoloForm",
			xmLabelWidgetClass,
			form10,
			XmNx, 160,
			XmNy, 10,
			XmNwidth, 280,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1" ),
			NULL );
	UxPutContext( TitoloForm, (char *) UxTagsInputContext );


	/* Creation of TagsWindow */
	TagsWindow = XtVaCreateManagedWidget( "TagsWindow",
			xmScrolledWindowWidgetClass,
			form10,
			XmNscrollingPolicy, XmAUTOMATIC,
			XmNx, 20,
			XmNy, 60,
			XmNwidth, 560,
			XmNheight, 210,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 85,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 70,
			XmNleftOffset, 20,
			NULL );
	UxPutContext( TagsWindow, (char *) UxTagsInputContext );


	XtAddCallback( TagsInput, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTagsInputContext);

	XmMainWindowSetAreas( mainWindow11, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form10 );

	return ( TagsInput );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_TagsInput( _UxParente3, _UxBot, _UxFrm, _UxIndex, _UxOggSelezionato, _UxTagsInp )
	Widget	_UxParente3;
	Widget	_UxBot;
	OlFormObject	_UxFrm;
	int	_UxIndex;
	Widget	_UxOggSelezionato;
	unsigned char	**_UxTagsInp;
{
	Widget                  rtrn;
	_UxCTagsInput           *UxContext;

	UxTagsInputContext = UxContext =
		(_UxCTagsInput *) UxNewContext( sizeof(_UxCTagsInput), False );

	Parente3 = _UxParente3;
	Bot = _UxBot;
	Frm = _UxFrm;
	Index = _UxIndex;
	OggSelezionato = _UxOggSelezionato;
	TagsInp = _UxTagsInp;

	{
		XmString XmTit,Etichetta,XmTotale;
		DESCR_LINE *RigaLetta;
		char *RigaDescrizione;
		int i,indice;
		Widget Cont,Wid,Wid1,Wid2,Wid3,WidAppo;
		Boolean GiaDefinita;
		char *Value,*Descrizione,*StringaAppoggio;
		
		BottoneTag = Bot;
		FormDiConf = Frm;
		IndiceForm = Index;
		SelectedWidget = OggSelezionato;
		ValoriInput = TagsInp;
		rtrn = _Uxbuild_TagsInput();

		/*  Scrivo il titolo della window  */
		get_something (BottoneTag, XmNlabelString, &Etichetta);
		XmTit = XmStringCreateSimple ("Tags of ");
		XmTotale = XmStringConcat (XmTit,Etichetta);
		set_something (TitoloForm, XmNlabelString, XmTotale);
		XmStringFree (XmTit);
		XmStringFree (XmTotale);  
		
		/*  Posizione il puntatore StringaAppoggio in modo opportuno  */
		StringaAppoggio = PosizionaPuntatore (FormDiConf,IndiceForm,*ValoriInput);
		
		/*  Costruisco il rowcolumn che conterra' tutte le tags e le descrizioni  */
		Cont0 = XtVaCreateManagedWidget ("Cont0",
			xmRowColumnWidgetClass, TagsWindow,
			XmNisAligned, False,
			NULL);
		
		/*  Leggo i valori dalla form  */
		indice = OlGetNumLines (FormDiConf,IndiceForm);
		for (i=0;i<indice;i++)
		  {
		  /*  Leggo la singola riga  */
		  RigaLetta = OlGetLineForm (FormDiConf, IndiceForm, i);
		  if (RigaLetta != NULL)
		    {
		    Cont = XtVaCreateManagedWidget ("Rigone",
			xmRowColumnWidgetClass, Cont0,
			XmNorientation, XmHORIZONTAL,
			XmNisAligned, False,
			NULL);
		
		    if (RigaLetta->line_type == LINE_INP)
		      {
			/*  Carico il valore e la descrizione  */
			Value = LeggiParametro (&StringaAppoggio);
			Descrizione = LeggiParametro (&StringaAppoggio);
		
		      /*  Inserisco una linea di input  */
		      /*  Creo gli widget di riga  */
			Wid1 = XtVaCreateManagedWidget ("Wid1",
				xmLabelWidgetClass, Cont,
				XmNlabelString, XmStringCreateSimple (RigaLetta->u.input.tag),
				XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),
				XmNrecomputeSize, False,
				XmNalignment, XmALIGNMENT_BEGINNING,
				NULL);
#ifndef DESIGN_TIME
			Wid2 = XtVaCreateManagedWidget ("Wid2",
				xmTextFieldWidgetClass, Cont,
				XmNvalue, Value,
				XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),
				NULL);
			Wid3 = XtVaCreateManagedWidget ("Wid3",
				xmTextFieldWidgetClass, Cont,
				XmNvalue, Descrizione,
				XmNresizeWidth, True,
				XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),
				NULL); 
#endif
		      }
		    else
		      {
		      /*  Inserisco una linea di sola descrizione  */
			Wid = XtVaCreateManagedWidget ("Wid",
				xmLabelWidgetClass, Cont,
				XmNlabelString, XmStringCreateSimple(RigaLetta->u.descr.descr),
				XmNrecomputeSize, False,
				XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),
				XmNalignment, XmALIGNMENT_CENTER,
				NULL);
		      }
		    }
		  else
		    {
		    /*  Errore nella lettura della riga  */
		    }
		  }
		
		/*  Setto la posizione dell'interfaccia secondo il parent  */
		InterfaceSetPos (TagsInput, Parente3);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

