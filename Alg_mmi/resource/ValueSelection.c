
/*******************************************************************************
       ValueSelection.c
       (Generated from interface file ValueSelection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

#include "libutilx.h"

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo ValueSelection.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)ValueSelection.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/*
 * Interfaccia chiamata per l'editing della risorsa
 * input value nelle icone di regolazione; in base
 * al contenuto del file delle form associato
 * all'icona di regolazione
 * visualizza un numero di bottoni pari al numero di form
 * presenti e con etichetta uguale al titolo delle
 * form stesse.
 */
#include <Xm/RowColumn.h>
#ifndef DESIGN_TIME
#include <Xm/TextF.h>
#endif
#include <Xl/XlIconReg.h>
#include <Ol/OlForm.h>
#include "res_edit.h"

extern swidget create_TagsInput();

static int PushTagCB();


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
	Widget	UxValueSelection;
	Widget	UxmainWindow10;
	Widget	Uxform9;
	Widget	Uxseparator10;
	Widget	UxpushButton16;
	Widget	UxpushButton17;
	Widget	UxTitolo;
	Widget	*UxInpRC;
	Widget	UxParentInput;
	Widget	UxContenitore;
	Widget	UxWdgSel;
	OlFormObject	UxFormDiConfigurazione;
	unsigned char	*UxLista;
	Widget	UxPad;
	Widget	*UxRCR;
	Widget	UxOggettoSel;
	OlFormObject	UxFormInput;
} _UxCValueSelection;

static _UxCValueSelection      *UxValueSelectionContext;
#define ValueSelection          UxValueSelectionContext->UxValueSelection
#define mainWindow10            UxValueSelectionContext->UxmainWindow10
#define form9                   UxValueSelectionContext->Uxform9
#define separator10             UxValueSelectionContext->Uxseparator10
#define pushButton16            UxValueSelectionContext->UxpushButton16
#define pushButton17            UxValueSelectionContext->UxpushButton17
#define Titolo                  UxValueSelectionContext->UxTitolo
#define InpRC                   UxValueSelectionContext->UxInpRC
#define ParentInput             UxValueSelectionContext->UxParentInput
#define Contenitore             UxValueSelectionContext->UxContenitore
#define WdgSel                  UxValueSelectionContext->UxWdgSel
#define FormDiConfigurazione    UxValueSelectionContext->UxFormDiConfigurazione
#define Lista                   UxValueSelectionContext->UxLista
#define Pad                     UxValueSelectionContext->UxPad
#define RCR                     UxValueSelectionContext->UxRCR
#define OggettoSel              UxValueSelectionContext->UxOggettoSel
#define FormInput               UxValueSelectionContext->UxFormInput



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_ValueSelection();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

static int PushTagCB (swidget wid,int ind_tag, XmAnyCallbackStruct *call_data)
{
	Widget Creato;

#ifndef DESIGN_TIME
        _UxCValueSelection *UxSaveCtx,*UxContext;

        UxSaveCtx = UxValueSelectionContext;
        UxValueSelectionContext = UxContext =
                        (_UxCValueSelection *)UxGetContext(wid);
#endif

	/*  Setta a False l'attributo sensitive del bottone */
	set_something (wid, XmNsensitive, (void*) False);

	Creato = (Widget )create_TagsInput(ValueSelection,wid,
			FormDiConfigurazione,ind_tag,WdgSel,&Lista);

	UxPopupInterface (Creato , no_grab);

#ifndef DESIGN_TIME
        UxValueSelectionContext = UxSaveCtx;
#endif
return (OK);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton16( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCValueSelection      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxValueSelectionContext;
	UxValueSelectionContext = UxContext =
			(_UxCValueSelection *) UxGetContext( UxWidget );
	{
	/*  Rimetto a sensitive i bottoni del widget chiamante  */
	set_something (InpRC[0], XmNsensitive, (void*) True);
	set_something (InpRC[2], XmNsensitive, (void*) True);
	
	XmTextFieldSetString (InpRC[2], Lista);
	
	XtDestroyWidget (ValueSelection);
	}
	UxValueSelectionContext = UxSaveCtx;
}

static	void	activateCB_pushButton17( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCValueSelection      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxValueSelectionContext;
	UxValueSelectionContext = UxContext =
			(_UxCValueSelection *) UxGetContext( UxWidget );
	{
	/*  Rimetto a sensitive i bottoni del padre  */
	set_something (InpRC[0], XmNsensitive, (void*) True);
	set_something (InpRC[2], XmNsensitive, (void*) True);
	
	XtDestroyWidget (ValueSelection);
	}
	UxValueSelectionContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ValueSelection()
{
	Widget		_UxParent;


	/* Creation of ValueSelection */
	_UxParent = Pad;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	ValueSelection = XtVaCreatePopupShell( "ValueSelection",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 640,
			XmNy, 188,
			XmNwidth, 330,
			XmNheight, 170,
			XmNallowShellResize, TRUE,
			NULL );
	UxPutContext( ValueSelection, (char *) UxValueSelectionContext );


	/* Creation of mainWindow10 */
	mainWindow10 = XtVaCreateManagedWidget( "mainWindow10",
			xmMainWindowWidgetClass,
			ValueSelection,
			XmNunitType, XmPIXELS,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 330,
			XmNheight, 170,
			NULL );
	UxPutContext( mainWindow10, (char *) UxValueSelectionContext );


	/* Creation of form9 */
	form9 = XtVaCreateManagedWidget( "form9",
			xmFormWidgetClass,
			mainWindow10,
			NULL );
	UxPutContext( form9, (char *) UxValueSelectionContext );


	/* Creation of separator10 */
	separator10 = XtVaCreateManagedWidget( "separator10",
			xmSeparatorWidgetClass,
			form9,
			XmNx, 2,
			XmNy, 270,
			XmNwidth, 326,
			XmNheight, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 2,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 2,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 60,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNresizable, FALSE,
			NULL );
	UxPutContext( separator10, (char *) UxValueSelectionContext );


	/* Creation of pushButton16 */
	pushButton16 = XtVaCreateManagedWidget( "pushButton16",
			xmPushButtonWidgetClass,
			form9,
			XmNx, 10,
			XmNy, 300,
			XmNwidth, 90,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			NULL );
	XtAddCallback( pushButton16, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton16,
		(XtPointer) UxValueSelectionContext );

	UxPutContext( pushButton16, (char *) UxValueSelectionContext );


	/* Creation of pushButton17 */
	pushButton17 = XtVaCreateManagedWidget( "pushButton17",
			xmPushButtonWidgetClass,
			form9,
			XmNx, 110,
			XmNy, 290,
			XmNwidth, 90,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, pushButton16,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			NULL );
	XtAddCallback( pushButton17, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton17,
		(XtPointer) UxValueSelectionContext );

	UxPutContext( pushButton17, (char *) UxValueSelectionContext );


	/* Creation of Titolo */
	Titolo = XtVaCreateManagedWidget( "Titolo",
			xmLabelWidgetClass,
			form9,
			XmNx, 20,
			XmNy, 10,
			XmNwidth, 280,
			XmNheight, 40,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			RES_CONVERT( XmNlabelString, "" ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1" ),
			NULL );
	UxPutContext( Titolo, (char *) UxValueSelectionContext );


	XtAddCallback( ValueSelection, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxValueSelectionContext);

	XmMainWindowSetAreas( mainWindow10, (Widget) NULL, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form9 );

	return ( ValueSelection );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_ValueSelection( _UxPad, _UxRCR, _UxOggettoSel, _UxFormInput )
	Widget	_UxPad;
	Widget	*_UxRCR;
	Widget	_UxOggettoSel;
	OlFormObject	_UxFormInput;
{
	Widget                  rtrn;
	_UxCValueSelection      *UxContext;

	UxValueSelectionContext = UxContext =
		(_UxCValueSelection *) UxNewContext( sizeof(_UxCValueSelection), False );

	Pad = _UxPad;
	RCR = _UxRCR;
	OggettoSel = _UxOggettoSel;
	FormInput = _UxFormInput;

	{
		char *Tit,*Nome,PerTitolo[200],*Tags,*Stringa,*Buffer;
		char *Appoggio; 
		XmString XmTit;
		Widget Bottone;
		int i,j,NumeroForm,Scarto,NumeroTags;
		
		InpRC = RCR;
		ParentInput = Pad;
		FormDiConfigurazione = FormInput;
		WdgSel = OggettoSel;
		
		Lista = NULL;
		rtrn = _Uxbuild_ValueSelection();

		/*  Scrivo il nome della form come titolo  */
		get_something (OggettoSel, XlNmodulName, (void*) &Nome);
		strcpy (PerTitolo,"FORM NAME: ");
		strcat (PerTitolo,Nome);
		set_something (Titolo, XmNlabelString, (void*) XmStringCreateSimple (PerTitolo));
		
		/*  Costruisco il RowColumn contenente tutti i PushButton */
		Contenitore = XtVaCreateManagedWidget ("Contenitore",
			xmRowColumnWidgetClass, form9,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 60,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 70,
			XmNentryAlignment, XmALIGNMENT_CENTER,
			NULL);
		
		/*  Ricavo il numero delle form presenti */
		NumeroForm = OlGetNumForms (FormInput);
		
		Scarto = 0;
		/*  Costruisco i bottoni per ogni form  */
		for (i=0;i<NumeroForm;i++)
		  {
		  /*  Incremento l'offset per il ridimensionamento della toplevelshell  */
		  Scarto += 30;
		 
		  /*  Leggo il titolo della form  */
		  Tit = OlGetTitle (FormInput,i);
		  XmTit = XmStringCreateSimple (Tit);
		
		  /*  Creo il push button  */
		  Bottone = XtVaCreateManagedWidget ("Bottone",
			xmPushButtonWidgetClass, Contenitore,
			XmNlabelString, XmTit,
			NULL);
#ifndef DESIGN_TIME
		  UxPutContext (Bottone, (char *)UxValueSelectionContext );
#endif
		  XtAddCallback (Bottone, XmNactivateCallback, (XtCallbackProc)PushTagCB, (XtPointer)i);
		
		  XmStringFree (XmTit);
		  }
		
		/*  Controllo se e' presente l'inizializzazione delle form
			altrimenti creo lo stringone con i valori letti dal file  */
		Stringa = (char *)XmTextFieldGetString ((Widget)InpRC[2]);
		if ( (strncmp (Stringa,"no value",8)==0) || (strcmp (Stringa,"")==0) )
		  {
		  /*  La stringa e' vuota e creo quindi leggendo dalla form  */
		  for (i=0;i<NumeroForm;i++)
		    {
		    /*  Prendo le tags della form specificata  */
		    Buffer = OlWriteStrInp (FormInput,&Appoggio,i);
		    if (Buffer != NULL)
		      {
		      if (Lista == NULL)
		        {
		        Lista = XtCalloc (strlen(Buffer)+1,sizeof(char));
		        strcpy (Lista,Buffer);
		        }
		      else
		        {
		        Lista = XtRealloc (Lista,(strlen(Lista)+strlen(Buffer)+2)*sizeof(char));
		        strcat (Lista," ");
		        strcat (Lista,Buffer);
		        }
		      XtFree (Buffer); 
		      }
		    } 
		  }
		else
		  Lista = Stringa;
		
		/*  Ridimensiono la toplevelshell in modo da contenere 
			tutti i bottoni inseriti  */
		set_something (ValueSelection, XmNheight, (void*) 130+Scarto);
		
		/*  Setto la posizione della toplevel secondo il parent  */
		InterfaceSetPos (ValueSelection, Pad);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

