! UIMX ascii 2.5 key: 1897                                                      

*VariablesSelection.class: topLevelShell
*VariablesSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo VariablesSelection.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)VariablesSelection.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
/*\
  Interfaccia per la selezione \
  1) delle variabili da associare ad una porta di I/O (su icon reg)\
  2) delle variabili di cambio colore appartenenti a icon reg\
  3) delle variabili in input a oggetto DisplayReg\
*/\
#include <stdio.h>\
#include <Xl/XlIconReg.h>\
#include <Xl/XlPort.h>\
#include <Ol/OlForm.h>\
#include <Ol/OlForm_regol.h>\
#include "res_edit.h"\
\
void InserisciAvVar ( );\
void InserisciUsVar ( );\
/*\
void InterfaceSetPos ( );\
*/
*VariablesSelection.ispecdecl: Widget Parent5;\
Widget *ListaWidgetRC;\
Widget OSelezionato;
*VariablesSelection.ispeclist: Parent5, ListaWidgetRC, OSelezionato
*VariablesSelection.ispeclist.Parent5: "Widget", "%Parent5%"
*VariablesSelection.ispeclist.ListaWidgetRC: "Widget", "*%ListaWidgetRC%"
*VariablesSelection.ispeclist.OSelezionato: "Widget", "%OSelezionato%"
*VariablesSelection.funcdecl: swidget create_VariablesSelection(Widget Par5, /* Top level chiamante\
						  (Resource Editor) */	\
		Widget *ListaRCInp,  /* Lista dei figli della riga del \
					resource editor che e' oggetto di\
					modifica (per disabilitazione\
					bottone richiamo editor e settaggio\
					delle modifiche nel campo testo\
					associato)  */ \
		Widget WSel)  /* oggetto in selezione nella Drawing Area */        \

*VariablesSelection.funcname: create_VariablesSelection
*VariablesSelection.funcdef: "swidget", "<create_VariablesSelection>(%)"
*VariablesSelection.argdecl: Widget Par5;\
Widget *ListaRCInp;\
Widget WSel;
*VariablesSelection.arglist: Par5, ListaRCInp, WSel
*VariablesSelection.arglist.Par5: "Widget", "%Par5%"
*VariablesSelection.arglist.ListaRCInp: "Widget", "*%ListaRCInp%"
*VariablesSelection.arglist.WSel: "Widget", "%WSel%"
*VariablesSelection.icode: char LabTitolo[100];\
int Tipo;\
\
Parent5 = Par5;\
ListaWidgetRC = ListaRCInp;\
OSelezionato = WSel;
*VariablesSelection.fcode: /*  Imposto la label per il tipo della variabile  */\
if ( XlIsPort (OSelezionato) )\
  {\
  get_something (OSelezionato, XlNtipoPort, &Tipo);\
  switch (Tipo)\
    {\
    case INPUT_PORT_A:\
      strcpy (LabTitolo,"ANALOG INPUT");\
      InserisciAvVar (AvailList,INPUT_PORT_A,OSelezionato);\
      InserisciUsVar (UsedList, INPUT_PORT_A,OSelezionato);\
    break;\
    case OUTPUT_PORT_A:\
      strcpy (LabTitolo,"ANALOG OUTPUT"); \
      InserisciAvVar (AvailList,OUTPUT_PORT_A,OSelezionato);\
      InserisciUsVar (UsedList, OUTPUT_PORT_A,OSelezionato);\
    break;\
    case INPUT_PORT_D:\
      strcpy (LabTitolo,"DIGITAL INPUT");\
      InserisciAvVar (AvailList,INPUT_PORT_D,OSelezionato);\
      InserisciUsVar (UsedList, INPUT_PORT_D,OSelezionato);\
    break;\
    case OUTPUT_PORT_D:\
      strcpy (LabTitolo,"DIGITAL OUTPUT");\
      InserisciAvVar (AvailList,OUTPUT_PORT_D,OSelezionato);\
      InserisciUsVar (UsedList, OUTPUT_PORT_D,OSelezionato);\
    break;\
    }\
  }\
else if ( (XlIsIconReg (OSelezionato)) || (XlIsDispReg(OSelezionato)) )\
       {\
       strcpy(LabTitolo,"ALL VARIABLES");\
       InserisciAvVar (AvailList,ALL_VAR,OSelezionato);	\
       }\
\
/*  Setto la label del titolo relativo al tipo della variabile\
	visualizzata  */\
set_something (TipoVar, XmNlabelString, XmStringCreateSimple(LabTitolo));\
\
InterfaceSetPos (VariablesSelection,Parent5);\
\
return(rtrn);\

*VariablesSelection.auxdecl: void InserisciAvVar (Widget Lista,int TVar,Widget WS)\
{\
#ifndef DESIGN_TIME\
char *ListaTag,*Stringa,*Tag,*Descr;\
char *DaLiberare,*EsaminaTag,*TagAppoggio;\
XmString XmTot,XmTag,XmDescr;\
OlFormObject PuntForm;\
int i,j,NumForm,NumLinee,NumTags;\
DESCR_LINE *StrutturaAppoggio;\
Widget Fater;\
\
if ( (XlIsIconReg(WS)) || (XlIsDispReg(WS)) )\
  {\
  if(XlIsDispReg(WS))\
        WS=XtParent(WS);\
  /*  Prendo tutta la lista delle variabili  */\
  get_something (WS, XlNinputValue, &Stringa); \
\
  /*  Prendo dall'oggetto il puntatore alla form  */\
  get_something (WS, XlNobjectForm, &PuntForm);\
\
  /*  Ricavo il numero delle linee della form delle variabili  */\
  NumLinee = OlGetNumLines (PuntForm,0);\
  for (j=0;j<NumLinee;j++)\
    {\
    StrutturaAppoggio = OlGetLineForm (PuntForm,0,j);\
    if (StrutturaAppoggio->line_type == LINE_INP)\
      {\
      Tag = XtNewString ((char *)StrutturaAppoggio->u.input.tag);\
      Descr = EstrTagDescr (PuntForm,OL_FORM_INPUT_VALUE,Tag,2,Stringa);\
      XmTag = XmStringCreateSimple (Tag);\
      XmDescr = XmStringCreateSimple (Descr);\
      XmTot = XmStringConcat (XmTag,XmDescr);\
\
      /*  Aggiungo un item all'oggetto lista  */ \
      XmListAddItemUnselected (Lista,XmTot,0);\
\
      /*  Libero la memoria allocata  */\
      XmStringFree (XmTot);\
      XmStringFree (XmTag);\
      XmStringFree (XmDescr);\
      XtFree (Descr);\
      XtFree (Tag);\
      }\
    } \
  }\
else if (XlIsPort(WS))\
  {\
  /*  Prendo il padre della porta che dovrebbe essere l'IconReg  */\
  Fater = XtParent (WS);\
\
  /*  Prendo il puntatore allo stringone delle tag  */\
  get_something (Fater, XlNinputValue, &Stringa);\
\
  /*  Prendo ul puntatore alla form  */\
  get_something (Fater, XlNobjectForm, &PuntForm);\
\
  /*  Prendo le tags della form delle variabili  */\
  ListaTag = OlGetTags (PuntForm,0);  \
\
  /*  Filtro la lista delle tags secondo il tipo di variabile da \
	visualizzare  */\
  switch (TVar)\
    {\
    case INPUT_PORT_A:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_ANALOG,VAR_NOCOLLEG);\
    break;\
    case INPUT_PORT_D:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_DIGIT,VAR_NOCOLLEG);\
    break;\
    case OUTPUT_PORT_A:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_ANALOG,VAR_NOCOLLEG);\
    break;\
    case OUTPUT_PORT_D:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_DIGIT,VAR_NOCOLLEG);\
    break;\
    }\
\
  /*  Dalla nuova lista delle tags ricavo quelle che non sono\
	state ancora utilizzate in altre porte  */\
  DaLiberare = TagAppoggio;\
  memcpy (&NumTags, TagAppoggio, sizeof(int) );\
  TagAppoggio += sizeof(int);\
  for (i=0;i<NumTags;i++)\
    {\
    EsaminaTag = XtNewString (TagAppoggio);\
    if ( !(is_tag_in_port(Fater,EsaminaTag)) )\
      {\
      Descr = EstrTagDescr(PuntForm,OL_FORM_INPUT_VALUE,EsaminaTag,2,Stringa);\
      XmTag = XmStringCreateSimple (EsaminaTag);\
      XmDescr = XmStringCreateSimple (Descr);\
      XmTot = XmStringConcat (XmTag,XmDescr);\
\
      /*  Aggiungo un item all'oggetto lista  */\
      XmListAddItemUnselected (Lista,XmTot,0);\
\
      /*  Libero la memoria utilizzata  */\
      XmStringFree (XmTag);\
      XmStringFree (XmDescr);\
      XmStringFree (XmTot);\
      XtFree (Descr);\
      XtFree (EsaminaTag);\
      }\
    TagAppoggio += MAX_L_TAGS;\
    }\
  XtFree (DaLiberare);\
  } /* if (XlIsPort(WS)) */\
#endif\
}\
\
void InserisciUsVar (Widget Lista,int TVar,Widget WS)\
{\
#ifndef DESIGN_TIME\
char *ListaTag,*Stringa,*Tag,*Descr;\
char *DaLiberare,*EsaminaTag,*TagAppoggio;\
XmString XmTot,XmTag,XmDescr;\
OlFormObject PuntForm;\
int i,j,NumForm,NumLinee,NumTags;\
DESCR_LINE *StrutturaAppoggio;\
Widget Fater;\
\
if (XlIsPort(WS))\
  {\
  /*  Prendo il padre della porta che dovrebbe essere l'IconReg  */\
  Fater = XtParent (WS);\
\
  /*  Prendo il puntatore allo stringone delle tag  */\
  get_something (Fater, XlNinputValue, &Stringa);\
\
  /*  Prendo ul puntatore alla form  */\
  get_something (Fater, XlNobjectForm, &PuntForm);\
\
  /*  Prendo le tags della form delle variabili  */\
  ListaTag = OlGetTags (PuntForm,0);  \
\
  /*  Filtro la lista delle tags secondo il tipo di variabile da \
	visualizzare  */\
  switch (TVar)\
    {\
    case INPUT_PORT_A:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_ANALOG,VAR_NOCOLLEG);\
    break;\
    case INPUT_PORT_D:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_IN,VAR_DIGIT,VAR_NOCOLLEG);\
    break;\
    case OUTPUT_PORT_A:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_ANALOG,VAR_NOCOLLEG);\
    break;\
    case OUTPUT_PORT_D:\
	TagAppoggio = OlFiltraTags (ListaTag,VAR_OUT,VAR_DIGIT,VAR_NOCOLLEG);\
    break;\
    }\
\
  /*  Dalla nuova lista delle tags ricavo quelle che sono gia'\
	state utilizzate in altre porte  */\
  DaLiberare = TagAppoggio;\
  memcpy (&NumTags, TagAppoggio, sizeof(int) );\
  TagAppoggio += sizeof(int);\
  for (i=0;i<NumTags;i++)\
    {\
    EsaminaTag = XtNewString (TagAppoggio);\
    if ( is_tag_in_port(Fater,EsaminaTag) )\
      {\
      Descr = EstrTagDescr(PuntForm,OL_FORM_INPUT_VALUE,EsaminaTag,2,Stringa);\
      XmTag = XmStringCreateSimple (EsaminaTag);\
      XmDescr = XmStringCreateSimple (Descr);\
      XmTot = XmStringConcat (XmTag,XmDescr);\
\
      /*  Aggiungo un item all'oggetto lista  */\
      XmListAddItemUnselected (Lista,XmTot,0);\
\
      /*  Libero la memoria utilizzata  */\
      XmStringFree (XmTag);\
      XmStringFree (XmDescr);\
      XmStringFree (XmTot);\
      XtFree (Descr);\
      XtFree (EsaminaTag);\
      }\
    TagAppoggio += MAX_L_TAGS;\
    }\
  XtFree (DaLiberare);\
  } /* if (XlIsPort(WS)) */\
#endif\
}
*VariablesSelection.static: true
*VariablesSelection.name: VariablesSelection
*VariablesSelection.parent: NO_PARENT
*VariablesSelection.parentExpression: Parent5
*VariablesSelection.x: 516
*VariablesSelection.y: 181
*VariablesSelection.width: 450
*VariablesSelection.height: 550

*mainWindow12.class: mainWindow
*mainWindow12.static: true
*mainWindow12.name: mainWindow12
*mainWindow12.parent: VariablesSelection
*mainWindow12.unitType: "pixels"
*mainWindow12.x: 140
*mainWindow12.y: 270
*mainWindow12.width: 450
*mainWindow12.height: 470

*form11.class: form
*form11.static: true
*form11.name: form11
*form11.parent: mainWindow12

*label14.class: label
*label14.static: true
*label14.name: label14
*label14.parent: form11
*label14.x: 10
*label14.y: 10
*label14.width: 200
*label14.height: 40
*label14.leftAttachment: "attach_form"
*label14.leftOffset: 10
*label14.topAttachment: "attach_form"
*label14.topOffset: 10
*label14.fontList: "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1"
*label14.labelString: "Variable type:"
*label14.alignment: "alignment_end"

*TipoVar.class: label
*TipoVar.static: true
*TipoVar.name: TipoVar
*TipoVar.parent: form11
*TipoVar.x: 210
*TipoVar.y: 10
*TipoVar.width: 230
*TipoVar.height: 40
*TipoVar.alignment: "alignment_center"
*TipoVar.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*TipoVar.labelString: ""
*TipoVar.leftAttachment: "attach_widget"
*TipoVar.leftOffset: 0
*TipoVar.leftWidget: "label14"
*TipoVar.topAttachment: "attach_form"
*TipoVar.topOffset: 20
*TipoVar.resizable: "false"

*separator12.class: separator
*separator12.static: true
*separator12.name: separator12
*separator12.parent: form11
*separator12.x: 10
*separator12.y: 60
*separator12.width: 430
*separator12.height: 10
*separator12.leftAttachment: "attach_form"
*separator12.leftOffset: 2
*separator12.rightAttachment: "attach_form"
*separator12.rightOffset: 2

*label15.class: label
*label15.static: true
*label15.name: label15
*label15.parent: form11
*label15.x: 10
*label15.y: 75
*label15.width: 280
*label15.height: 25
*label15.fontList: "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1"
*label15.labelString: "Available Variables:"
*label15.alignment: "alignment_beginning"
*label15.leftAttachment: "attach_form"
*label15.leftOffset: 10
*label15.topAttachment: "attach_widget"
*label15.topOffset: 5
*label15.topWidget: "separator12"

*separator13.class: separator
*separator13.static: true
*separator13.name: separator13
*separator13.parent: form11
*separator13.x: 0
*separator13.y: 280
*separator13.width: 450
*separator13.height: 10
*separator13.bottomAttachment: "attach_form"
*separator13.leftAttachment: "attach_form"
*separator13.leftOffset: 2
*separator13.rightAttachment: "attach_form"
*separator13.rightOffset: 2
*separator13.topAttachment: "attach_none"
*separator13.topOffset: 0
*separator13.bottomOffset: 230

*scrolledWindow8.class: scrolledWindow
*scrolledWindow8.static: true
*scrolledWindow8.name: scrolledWindow8
*scrolledWindow8.parent: form11
*scrolledWindow8.scrollingPolicy: "application_defined"
*scrolledWindow8.x: 10
*scrolledWindow8.y: 110
*scrolledWindow8.visualPolicy: "variable"
*scrolledWindow8.scrollBarDisplayPolicy: "static"
*scrolledWindow8.shadowThickness: 0
*scrolledWindow8.leftAttachment: "attach_form"
*scrolledWindow8.leftOffset: 20
*scrolledWindow8.rightAttachment: "attach_form"
*scrolledWindow8.rightOffset: 20
*scrolledWindow8.topAttachment: "attach_widget"
*scrolledWindow8.topOffset: 10
*scrolledWindow8.topWidget: "label15"
*scrolledWindow8.bottomAttachment: "attach_widget"
*scrolledWindow8.bottomOffset: 10
*scrolledWindow8.bottomWidget: "separator13"

*AvailList.class: scrolledList
*AvailList.static: true
*AvailList.name: AvailList
*AvailList.parent: scrolledWindow8
*AvailList.width: 430
*AvailList.height: 160

*label16.class: label
*label16.static: true
*label16.name: label16
*label16.parent: form11
*label16.x: 10
*label16.y: 290
*label16.width: 280
*label16.height: 25
*label16.fontList: "-bitstream-terminal-medium-r-normal-gs-18-180-75-75-c-110-iso8859-1"
*label16.labelString: "Used Variables:"
*label16.alignment: "alignment_beginning"
*label16.topAttachment: "attach_widget"
*label16.topOffset: 5
*label16.topWidget: "separator13"

*scrolledWindow9.class: scrolledWindow
*scrolledWindow9.static: true
*scrolledWindow9.name: scrolledWindow9
*scrolledWindow9.parent: form11
*scrolledWindow9.scrollingPolicy: "application_defined"
*scrolledWindow9.x: 20
*scrolledWindow9.y: 321
*scrolledWindow9.visualPolicy: "variable"
*scrolledWindow9.scrollBarDisplayPolicy: "static"
*scrolledWindow9.shadowThickness: 0
*scrolledWindow9.leftAttachment: "attach_form"
*scrolledWindow9.leftOffset: 20
*scrolledWindow9.rightAttachment: "attach_form"
*scrolledWindow9.rightOffset: 20
*scrolledWindow9.topAttachment: "attach_widget"
*scrolledWindow9.topOffset: 10
*scrolledWindow9.topWidget: "label16"

*UsedList.class: scrolledList
*UsedList.static: true
*UsedList.name: UsedList
*UsedList.parent: scrolledWindow9
*UsedList.width: 410
*UsedList.height: 110
*UsedList.ancestorSensitive: "false"
*UsedList.sensitive: "false"

*separator14.class: separator
*separator14.static: true
*separator14.name: separator14
*separator14.parent: form11
*separator14.x: 0
*separator14.y: 430
*separator14.width: 450
*separator14.height: 10
*separator14.topAttachment: "attach_widget"
*separator14.topOffset: 10
*separator14.topWidget: "scrolledWindow9"
*separator14.leftAttachment: "attach_form"
*separator14.leftOffset: 2
*separator14.rightAttachment: "attach_form"
*separator14.rightOffset: 2
*separator14.bottomAttachment: "attach_form"
*separator14.bottomOffset: 60

*pushButton20.class: pushButton
*pushButton20.static: true
*pushButton20.name: pushButton20
*pushButton20.parent: form11
*pushButton20.x: 10
*pushButton20.y: 500
*pushButton20.width: 80
*pushButton20.height: 40
*pushButton20.labelString: "OK"
*pushButton20.bottomAttachment: "attach_form"
*pushButton20.bottomOffset: 10
*pushButton20.activateCallback: {\
Boolean Selezione;\
int Posizione,*PosSelected,NumSelected=0;\
XmString *ListaXm;\
char Ritorno[3],ItemSel[200];\
\
/*  Prendo dalla lista delle variabili l'item selezionato  */\
Selezione = XmListGetSelectedPos (AvailList , &PosSelected, &NumSelected);\
\
/*  Esegue l'operazione solo se e' selezionato un item  */\
if (Selezione)\
  {\
  if (NumSelected==1)\
    {\
    /*  Prende dall'oggetto lista l'elenco degli item sotto\
		forma di lista di XmString  */\
    get_something (AvailList, XmNitems, &ListaXm);\
    Posizione = PosSelected[0]-1;\
    strcpy ( ItemSel,extract_string (ListaXm[Posizione]) );\
    strncpy (Ritorno,ItemSel,2);\
    Ritorno[2] = '\0';\
    XmTextFieldSetString (ListaWidgetRC[2],Ritorno);\
    XtFree (PosSelected);\
    }\
  }\
\
/*  Rimetto a sensitive i bottoni chiamanti  */\
set_something (ListaWidgetRC[0], XmNsensitive, True);\
set_something (ListaWidgetRC[2], XmNsensitive, True);\
\
XtDestroyWidget (VariablesSelection);\
}

*pushButton21.class: pushButton
*pushButton21.static: true
*pushButton21.name: pushButton21
*pushButton21.parent: form11
*pushButton21.x: 100
*pushButton21.y: 440
*pushButton21.width: 80
*pushButton21.height: 40
*pushButton21.labelString: "CANCEL"
*pushButton21.bottomAttachment: "attach_form"
*pushButton21.bottomOffset: 10
*pushButton21.leftAttachment: "attach_widget"
*pushButton21.leftOffset: 10
*pushButton21.leftWidget: "pushButton20"
*pushButton21.activateCallback: {\
/*  Rimetto a sensitive i bottoni chiamanti  */\
set_something (ListaWidgetRC[0], XmNsensitive, True);\
set_something (ListaWidgetRC[2], XmNsensitive, True);\
\
XtDestroyWidget (VariablesSelection);\
}

