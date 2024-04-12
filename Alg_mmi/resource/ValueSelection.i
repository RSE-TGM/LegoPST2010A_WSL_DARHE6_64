! UIMX ascii 2.5 key: 1306                                                      

*ValueSelection.class: topLevelShell
*ValueSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ValueSelection.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)ValueSelection.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
/*\
 * Interfaccia chiamata per l'editing della risorsa\
 * input value nelle icone di regolazione; in base\
 * al contenuto del file delle form associato\
 * all'icona di regolazione\
 * visualizza un numero di bottoni pari al numero di form\
 * presenti e con etichetta uguale al titolo delle\
 * form stesse.\
 */\
#include <stdio.h>\
#include <Xm/RowColumn.h>\
#ifndef DESIGN_TIME\
#include <Xm/TextF.h>\
#endif\
#include <Xl/XlIconReg.h>\
#include <Ol/OlForm.h>\
#include "res_edit.h"\
\
extern swidget create_TagsInput();\
\
int PushTagCB();
*ValueSelection.ispecdecl: Widget *InpRC;\
Widget ParentInput;\
Widget Contenitore;\
Widget WdgSel;\
OlFormObject FormDiConfigurazione;\
char *Lista;
*ValueSelection.ispeclist: InpRC, ParentInput, Contenitore, WdgSel, FormDiConfigurazione, Lista
*ValueSelection.ispeclist.InpRC: "Widget", "*%InpRC%"
*ValueSelection.ispeclist.ParentInput: "Widget", "%ParentInput%"
*ValueSelection.ispeclist.Contenitore: "Widget", "%Contenitore%"
*ValueSelection.ispeclist.WdgSel: "Widget", "%WdgSel%"
*ValueSelection.ispeclist.FormDiConfigurazione: "OlFormObject", "%FormDiConfigurazione%"
*ValueSelection.ispeclist.Lista: "unsigned char", "*%Lista%"
*ValueSelection.funcdecl: swidget create_ValueSelection(Widget Pad, /* Shell dell'oggetto chiamante */\
		Widget *RCR,              /* Lista dei figli del RowCol del\
					     resource editor su cui si sta\
					     lavorando (contiene bottone di \
					     attivazione, text field ecc.. ) */	\
		Widget OggettoSel,        /* Oggetto selez. nella drawing area */\
		OlFormObject FormInput)   /* oggetto form in utilizzo */ \

*ValueSelection.funcname: create_ValueSelection
*ValueSelection.funcdef: "swidget", "<create_ValueSelection>(%)"
*ValueSelection.argdecl: Widget Pad;\
Widget *RCR;\
Widget OggettoSel;\
OlFormObject FormInput;
*ValueSelection.arglist: Pad, RCR, OggettoSel, FormInput
*ValueSelection.arglist.Pad: "Widget", "%Pad%"
*ValueSelection.arglist.RCR: "Widget", "*%RCR%"
*ValueSelection.arglist.OggettoSel: "Widget", "%OggettoSel%"
*ValueSelection.arglist.FormInput: "OlFormObject", "%FormInput%"
*ValueSelection.icode: char *Tit,*Nome,PerTitolo[200],*Tags,*Stringa,*Buffer;\
char *Appoggio; \
XmString XmTit;\
Widget Bottone;\
int i,j,NumeroForm,Scarto,NumeroTags;\
\
InpRC = RCR;\
ParentInput = Pad;\
FormDiConfigurazione = FormInput;\
WdgSel = OggettoSel;\
\
Lista = NULL;
*ValueSelection.fcode: /*  Scrivo il nome della form come titolo  */\
get_something (OggettoSel, XlNmodulName, &Nome);\
strcpy (PerTitolo,"FORM NAME: ");\
strcat (PerTitolo,Nome);\
set_something (Titolo, XmNlabelString, XmStringCreateSimple (PerTitolo));\
\
/*  Costruisco il RowColumn contenente tutti i PushButton */\
Contenitore = XtVaCreateManagedWidget ("Contenitore",\
	xmRowColumnWidgetClass, form9,\
	XmNrightAttachment, XmATTACH_FORM,\
	XmNrightOffset, 10,\
	XmNleftAttachment, XmATTACH_FORM,\
	XmNleftOffset, 10,\
	XmNtopAttachment, XmATTACH_FORM,\
	XmNtopOffset, 60,\
	XmNbottomAttachment, XmATTACH_FORM,\
	XmNbottomOffset, 70,\
	XmNentryAlignment, XmALIGNMENT_CENTER,\
	NULL);\
\
/*  Ricavo il numero delle form presenti */\
NumeroForm = OlGetNumForms (FormInput);\
\
Scarto = 0;\
/*  Costruisco i bottoni per ogni form  */\
for (i=0;i<NumeroForm;i++)\
  {\
  /*  Incremento l'offset per il ridimensionamento della toplevelshell  */\
  Scarto += 30;\
 \
  /*  Leggo il titolo della form  */\
  Tit = OlGetTitle (FormInput,i);\
  XmTit = XmStringCreateSimple (Tit);\
\
  /*  Creo il push button  */\
  Bottone = XtVaCreateManagedWidget ("Bottone",\
	xmPushButtonWidgetClass, Contenitore,\
	XmNlabelString, XmTit,\
	NULL);\
#ifndef DESIGN_TIME\
  UxPutContext (Bottone, (char *)UxValueSelectionContext );\
#endif\
  XtAddCallback (Bottone, XmNactivateCallback, PushTagCB, i);\
\
  XmStringFree (XmTit);\
  }\
\
/*  Controllo se e' presente l'inizializzazione delle form\
	altrimenti creo lo stringone con i valori letti dal file  */\
Stringa = (char *)XmTextFieldGetString ((Widget)InpRC[2]);\
if ( (strncmp (Stringa,"no value",8)==0) || (strcmp (Stringa,"")==0) )\
  {\
  /*  La stringa e' vuota e creo quindi leggendo dalla form  */\
  for (i=0;i<NumeroForm;i++)\
    {\
    /*  Prendo le tags della form specificata  */\
    Buffer = OlWriteStrInp (FormInput,&Appoggio,i);\
    if (Buffer != NULL)\
      {\
      if (Lista == NULL)\
        {\
        Lista = XtCalloc (strlen(Buffer)+1,sizeof(char));\
        strcpy (Lista,Buffer);\
        }\
      else\
        {\
        Lista = XtRealloc (Lista,(strlen(Lista)+strlen(Buffer)+2)*sizeof(char));\
        strcat (Lista," ");\
        strcat (Lista,Buffer);\
        }\
      XtFree (Buffer); \
      }\
    } \
  }\
else\
  Lista = Stringa;\
\
/*  Ridimensiono la toplevelshell in modo da contenere \
	tutti i bottoni inseriti  */\
set_something (ValueSelection, XmNheight, 130+Scarto);\
\
/*  Setto la posizione della toplevel secondo il parent  */\
InterfaceSetPos (ValueSelection, Pad);\
return(rtrn);
*ValueSelection.auxdecl: static int PushTagCB (swidget wid,int ind_tag, XmAnyCallbackStruct *call_data)\
{\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCValueSelection *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxValueSelectionContext;\
        UxValueSelectionContext = UxContext =\
                        (_UxCValueSelection *)UxGetContext(wid);\
#endif\
\
	/*  Setta a False l'attributo sensitive del bottone */\
	set_something (wid, XmNsensitive, False);\
\
	Creato = (Widget )create_TagsInput(ValueSelection,wid,\
			FormDiConfigurazione,ind_tag,WdgSel,&Lista);\
\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxValueSelectionContext = UxSaveCtx;\
#endif\
return (OK);\
}\

*ValueSelection.static: true
*ValueSelection.name: ValueSelection
*ValueSelection.parent: NO_PARENT
*ValueSelection.parentExpression: Pad
*ValueSelection.x: 640
*ValueSelection.y: 188
*ValueSelection.width: 330
*ValueSelection.height: 170
*ValueSelection.allowShellResize: "true"

*mainWindow10.class: mainWindow
*mainWindow10.static: true
*mainWindow10.name: mainWindow10
*mainWindow10.parent: ValueSelection
*mainWindow10.unitType: "pixels"
*mainWindow10.x: 0
*mainWindow10.y: 0
*mainWindow10.width: 330
*mainWindow10.height: 170

*form9.class: form
*form9.static: true
*form9.name: form9
*form9.parent: mainWindow10

*separator10.class: separator
*separator10.static: true
*separator10.name: separator10
*separator10.parent: form9
*separator10.x: 2
*separator10.y: 270
*separator10.width: 326
*separator10.height: 10
*separator10.leftAttachment: "attach_form"
*separator10.leftOffset: 2
*separator10.rightAttachment: "attach_form"
*separator10.rightOffset: 2
*separator10.bottomAttachment: "attach_form"
*separator10.bottomOffset: 60
*separator10.topAttachment: "attach_none"
*separator10.topOffset: 0
*separator10.resizable: "false"

*pushButton16.class: pushButton
*pushButton16.static: true
*pushButton16.name: pushButton16
*pushButton16.parent: form9
*pushButton16.x: 10
*pushButton16.y: 300
*pushButton16.width: 90
*pushButton16.height: 40
*pushButton16.labelString: "OK"
*pushButton16.bottomAttachment: "attach_form"
*pushButton16.bottomOffset: 10
*pushButton16.topAttachment: "attach_none"
*pushButton16.topOffset: 0
*pushButton16.topWidget: ""
*pushButton16.activateCallback: {\
/*  Rimetto a sensitive i bottoni del widget chiamante  */\
set_something (InpRC[0], XmNsensitive, True);\
set_something (InpRC[2], XmNsensitive, True);\
\
XmTextFieldSetString (InpRC[2], Lista);\
\
XtDestroyWidget (ValueSelection);\
}

*pushButton17.class: pushButton
*pushButton17.static: true
*pushButton17.name: pushButton17
*pushButton17.parent: form9
*pushButton17.x: 110
*pushButton17.y: 290
*pushButton17.width: 90
*pushButton17.height: 40
*pushButton17.labelString: "CANCEL"
*pushButton17.bottomAttachment: "attach_form"
*pushButton17.bottomOffset: 10
*pushButton17.leftAttachment: "attach_widget"
*pushButton17.leftOffset: 10
*pushButton17.leftWidget: "pushButton16"
*pushButton17.topAttachment: "attach_none"
*pushButton17.topOffset: 0
*pushButton17.topWidget: ""
*pushButton17.activateCallback: {\
/*  Rimetto a sensitive i bottoni del padre  */\
set_something (InpRC[0], XmNsensitive, True);\
set_something (InpRC[2], XmNsensitive, True);\
\
XtDestroyWidget (ValueSelection);\
}

*Titolo.class: label
*Titolo.static: true
*Titolo.name: Titolo
*Titolo.parent: form9
*Titolo.x: 20
*Titolo.y: 10
*Titolo.width: 280
*Titolo.height: 40
*Titolo.bottomAttachment: "attach_none"
*Titolo.bottomOffset: 0
*Titolo.bottomWidget: ""
*Titolo.leftAttachment: "attach_form"
*Titolo.leftOffset: 10
*Titolo.rightAttachment: "attach_form"
*Titolo.rightOffset: 10
*Titolo.topAttachment: "attach_form"
*Titolo.topOffset: 10
*Titolo.labelString: ""
*Titolo.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"

