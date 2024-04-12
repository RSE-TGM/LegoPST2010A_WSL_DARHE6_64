! UIMX ascii 2.5 key: 4622                                                      

*TagsInput.class: topLevelShell
*TagsInput.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo TagsInput.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)TagsInput.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
/*\
 * interfaccia che presenta il contenuto delle form.\
   Presenta i campi editabili e le label descritte dalla\
   form riempite dei valori di default (se non e' mai stato\
   fatto l'input dei valori) o i valori contenuti nella stringa \
   descrittiva (stringone) che costituisce la risorsa\
   input value.\
   E' utilizzata per le diverse form presenti (per regolazione \
   sia input dati che input variabili).\
*/\
\
#include <stdio.h>\
#include <Xm/RowColumn.h>\
#include <Xm/ToggleB.h>\
#ifndef DESIGN_TIME\
#include <Xm/TextF.h>\
#endif\
#include <Xl/XlIconReg.h>\
#include <Ol/OlForm.h>\
\
extern Widget CreaLabel();\
extern Widget CreaTextField();\
\
char *LeggiParametro( );\
char *PosizionaPuntatore ( );\
char *EstraiTags ( );\

*TagsInput.ispecdecl: Widget BottoneTag;\
Widget SelectedWidget;\
Widget Cont0;\
OlFormObject FormDiConf;\
int IndiceForm;\
char **ValoriInput;
*TagsInput.ispeclist: BottoneTag, SelectedWidget, Cont0, FormDiConf, IndiceForm, ValoriInput
*TagsInput.ispeclist.BottoneTag: "Widget", "%BottoneTag%"
*TagsInput.ispeclist.SelectedWidget: "Widget", "%SelectedWidget%"
*TagsInput.ispeclist.Cont0: "Widget", "%Cont0%"
*TagsInput.ispeclist.FormDiConf: "OlFormObject", "%FormDiConf%"
*TagsInput.ispeclist.IndiceForm: "int", "%IndiceForm%"
*TagsInput.ispeclist.ValoriInput: "unsigned char", "**%ValoriInput%"
*TagsInput.funcdecl: swidget create_TagsInput(Widget Parente3, /* Top level shell della interfaccia\
                                             value selection */\
                         Widget Bot,      /* bottone chiamante (appartiene alla\
                                             interfaccia value sel.) */ \
                         OlFormObject Frm,  /* oggetto form */\
                         int Index,         /* indice della form: per regolaz.\
                                               0 = variabili  1 = dati  */\
		         Widget OggSelezionato,  /* oggetto selezionato nella\
                                                    drawing area (per reg. e'\
						    IconReg  */\
                         char **TagsInp)    /* puntatore al puntatore del valore\
					       della risorsa input value\
						(stringone) */\

*TagsInput.funcname: create_TagsInput
*TagsInput.funcdef: "swidget", "<create_TagsInput>(%)"
*TagsInput.argdecl: Widget Parente3;\
Widget Bot;\
OlFormObject Frm;\
int Index;\
Widget OggSelezionato;\
unsigned char **TagsInp;
*TagsInput.arglist: Parente3, Bot, Frm, Index, OggSelezionato, TagsInp
*TagsInput.arglist.Parente3: "Widget", "%Parente3%"
*TagsInput.arglist.Bot: "Widget", "%Bot%"
*TagsInput.arglist.Frm: "OlFormObject", "%Frm%"
*TagsInput.arglist.Index: "int", "%Index%"
*TagsInput.arglist.OggSelezionato: "Widget", "%OggSelezionato%"
*TagsInput.arglist.TagsInp: "unsigned char", "**%TagsInp%"
*TagsInput.icode: XmString XmTit,Etichetta,XmTotale;\
DESCR_LINE *RigaLetta;\
char *RigaDescrizione;\
int i,indice;\
Widget Cont,Wid,Wid1,Wid2,Wid3,WidAppo;\
Boolean GiaDefinita;\
char *Value,*Descrizione,*StringaAppoggio;\
\
BottoneTag = Bot;\
FormDiConf = Frm;\
IndiceForm = Index;\
SelectedWidget = OggSelezionato;\
ValoriInput = TagsInp;
*TagsInput.fcode: /*  Scrivo il titolo della window  */\
get_something (BottoneTag, XmNlabelString, &Etichetta);\
XmTit = XmStringCreateSimple ("Tags of ");\
XmTotale = XmStringConcat (XmTit,Etichetta);\
set_something (TitoloForm, XmNlabelString, XmTotale);\
XmStringFree (XmTit);\
XmStringFree (XmTotale);  \
\
/*  Posizione il puntatore StringaAppoggio in modo opportuno  */\
StringaAppoggio = PosizionaPuntatore (FormDiConf,IndiceForm,*ValoriInput);\
\
/*  Costruisco il rowcolumn che conterra' tutte le tags e le descrizioni  */\
Cont0 = XtVaCreateManagedWidget ("Cont0",\
	xmRowColumnWidgetClass, TagsWindow,\
	XmNisAligned, False,\
	NULL);\
\
/*  Leggo i valori dalla form  */\
indice = OlGetNumLines (FormDiConf,IndiceForm);\
for (i=0;i<indice;i++)\
  {\
  /*  Leggo la singola riga  */\
  RigaLetta = OlGetLineForm (FormDiConf, IndiceForm, i);\
  if (RigaLetta != NULL)\
    {\
    Cont = XtVaCreateManagedWidget ("Rigone",\
	xmRowColumnWidgetClass, Cont0,\
	XmNorientation, XmHORIZONTAL,\
	XmNisAligned, False,\
	NULL);\
\
    if (RigaLetta->line_type == LINE_INP)\
      {\
	/*  Carico il valore e la descrizione  */\
	Value = LeggiParametro (&StringaAppoggio);\
	Descrizione = LeggiParametro (&StringaAppoggio);\
\
      /*  Inserisco una linea di input  */\
      /*  Creo gli widget di riga  */\
	Wid1 = XtVaCreateManagedWidget ("Wid1",\
		xmLabelWidgetClass, Cont,\
		XmNlabelString, XmStringCreateSimple (RigaLetta->u.input.tag),\
		XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),\
		XmNrecomputeSize, False,\
		XmNalignment, XmALIGNMENT_BEGINNING,\
		NULL);\
#ifndef DESIGN_TIME\
	Wid2 = XtVaCreateManagedWidget ("Wid2",\
		xmTextFieldWidgetClass, Cont,\
		XmNvalue, Value,\
		XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),\
		NULL);\
	Wid3 = XtVaCreateManagedWidget ("Wid3",\
		xmTextFieldWidgetClass, Cont,\
		XmNvalue, Descrizione,\
		XmNresizeWidth, True,\
		XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),\
		NULL); \
#endif\
      }\
    else\
      {\
      /*  Inserisco una linea di sola descrizione  */\
	Wid = XtVaCreateManagedWidget ("Wid",\
		xmLabelWidgetClass, Cont,\
		XmNlabelString, XmStringCreateSimple(RigaLetta->u.descr.descr),\
		XmNrecomputeSize, False,\
		XmNfontList,UxConvertFontList( "-bitstream-terminal-medium-r-normal--18-180-75-75-c-110-iso8859-1" ),\
		XmNalignment, XmALIGNMENT_CENTER,\
		NULL);\
      }\
    }\
  else\
    {\
    /*  Errore nella lettura della riga  */\
    }\
  }\
\
/*  Setto la posizione dell'interfaccia secondo il parent  */\
InterfaceSetPos (TagsInput, Parente3);\
\
return(rtrn);\

*TagsInput.auxdecl: /******************************************************\
	Legge dalla lista di tutti i defaults della form il parametro\
	puntato dalla Stringa e lo ritorna e fa puntare Stringa \
	al parametro successivo della lista  \
******************************************************/\
char *LeggiParametro(char **Stringa)\
{\
char *StrRet,Ritorno[200];\
char *Appoggio;\
int i;\
\
Appoggio = *Stringa;\
i = 0;\
while (Appoggio[0] != '|')\
  {\
  Ritorno[i] = Appoggio[0];\
  Appoggio++;\
  i++;\
  }\
Appoggio++;\
Ritorno[i] = '\0';\
\
/*  Faccio puntare stringa al nuovo parametro  */\
if(Appoggio[0] != NULL)\
        {\
	while (Appoggio[0] != '|') Appoggio++;\
	Appoggio++;\
	}\
*Stringa = Appoggio;\
\
StrRet = XtCalloc ( strlen(Ritorno)+1 , sizeof(char) );\
strcpy (StrRet,Ritorno);\
return (StrRet);\
}\
\
/**************************************************************\
	Restituisce un puntatore al primo parametro nella lista dei defaults\
	della form shiftando secondo l'indice di form richiesto\
**************************************************************/\
char *PosizionaPuntatore (OlFormObject frm,int indice_form,char *Str)\
{\
int NumeroDelleForm,NumeroDelleTags;\
int i,indice,Numero;\
char *Ritorno;\
\
indice=0;\
\
/*  Se l'indice di form e' maggiore di quelle esistenti ritorno \
	subito NULL  */ \
NumeroDelleForm = OlGetNumForms (frm);\
if ( indice_form >= NumeroDelleForm )\
  return (NULL);\
\
/*  Se il numero delle tags della form specificata e' uguale a 0\
	ritorno subito NULL  */\
NumeroDelleTags = OlGetNumTags (frm,indice_form);\
if ( NumeroDelleTags == 0 )\
  return (NULL);\
\
Ritorno = strstr(Str,"|");\
Ritorno++;\
\
while (indice<indice_form)\
  {\
  Numero = OlGetNumTags (frm,indice);\
  if (Numero==0) return (NULL);\
  for (i=0;i<(Numero*4);i++)\
    {\
    Ritorno = strstr (Ritorno,"|");\
    Ritorno++;\
    }\
  indice++; \
  }\
\
return (Ritorno);\
}\
\
/********************************************************\
	Restituisce una stringa contenente i dati e le descrizioni delle \
	tag relative alla form richiesta \
********************************************************/\
char *EstraiTags (OlFormObject form,int indice_form,char *Stringone)\
{\
char *Ritorno,*Appoggio,*PuntInizio,*PuntFine;\
\
Appoggio = XtNewString (Stringone);\
\
PuntInizio = PosizionaPuntatore (form,indice_form,Appoggio);\
if (PuntInizio==NULL)\
  return (NULL);\
\
PuntInizio -= 1;\
\
PuntFine = PosizionaPuntatore (form,indice_form+1,Appoggio);\
if (PuntFine != NULL)\
  (PuntFine-2)[0] = '\0';\
\
Ritorno = XtNewString (PuntInizio);\
XtFree (Appoggio);\
\
return (Ritorno);\
}
*TagsInput.static: true
*TagsInput.name: TagsInput
*TagsInput.parent: NO_PARENT
*TagsInput.x: 655
*TagsInput.y: 99
*TagsInput.width: 600
*TagsInput.height: 440

*mainWindow11.class: mainWindow
*mainWindow11.static: true
*mainWindow11.name: mainWindow11
*mainWindow11.parent: TagsInput
*mainWindow11.unitType: "pixels"
*mainWindow11.x: 40
*mainWindow11.y: 60
*mainWindow11.width: 600
*mainWindow11.height: 440

*form10.class: form
*form10.static: true
*form10.name: form10
*form10.parent: mainWindow11

*separator11.class: separator
*separator11.static: true
*separator11.name: separator11
*separator11.parent: form10
*separator11.x: 10
*separator11.y: 270
*separator11.width: 550
*separator11.height: 10
*separator11.bottomAttachment: "attach_form"
*separator11.bottomOffset: 60
*separator11.leftAttachment: "attach_form"
*separator11.leftOffset: 2
*separator11.rightAttachment: "attach_form"
*separator11.rightOffset: 2
*separator11.topAttachment: "attach_none"
*separator11.topOffset: 0

*pushButton18.class: pushButton
*pushButton18.static: true
*pushButton18.name: pushButton18
*pushButton18.parent: form10
*pushButton18.x: 10
*pushButton18.y: 300
*pushButton18.width: 90
*pushButton18.height: 40
*pushButton18.bottomAttachment: "attach_form"
*pushButton18.bottomOffset: 10
*pushButton18.leftAttachment: "attach_form"
*pushButton18.leftOffset: 10
*pushButton18.topAttachment: "attach_none"
*pushButton18.topOffset: 0
*pushButton18.labelString: "OK"
*pushButton18.activateCallback: {\
Widget *ListaFigli,*FigliSet;\
int i,NumFigli,NumFigliSet,IndiceCiclo;\
char *Fittizio;\
char *PuntInizio;\
char *PuntCursore;\
char *PuntAppoggio;\
char *NuovaStringa=NULL;\
char *Value,*Descr;\
\
/*  Salvo il puntatore della stringa  */\
PuntAppoggio = XtNewString (*ValoriInput);\
\
/*  Estraggo i dati relativi alle form precedenti a quella che mi interessa */\
for (i=0;i<IndiceForm;i++)\
  {\
  PuntCursore = EstraiTags(FormDiConf,i,PuntAppoggio);\
  if (NuovaStringa==NULL)\
    {\
    NuovaStringa = XtCalloc (strlen (PuntCursore)+1,sizeof(char));\
    strcpy (NuovaStringa,PuntCursore);\
    } \
  else\
    {\
    NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+\
			strlen(PuntCursore)+2)*sizeof(char));\
    strcat (NuovaStringa," ");\
    strcat (NuovaStringa,PuntCursore);\
    }\
  XtFree (PuntCursore);\
  }\
\
/*  Prendo i figli del rowcolumn che contiene tutti i dati  */\
get_something (Cont0, XmNchildren, &ListaFigli);\
get_something (Cont0, XmNnumChildren, &NumFigli);\
for (i=0;i<NumFigli;i++)\
  {\
  get_something (ListaFigli[i], XmNchildren, &FigliSet);\
  get_something (ListaFigli[i], XmNnumChildren, &NumFigliSet);\
  if (NumFigliSet > 1)\
    {\
    /*  E' una riga con i text filed per i valori  */\
    Value = (char *)XmTextFieldGetString (FigliSet[1]);\
    Descr = (char *)XmTextFieldGetString (FigliSet[2]);\
    /*  Rialloco la stringa per contenere i nuovi dati  */\
    if (NuovaStringa == NULL)\
      {\
      NuovaStringa = XtCalloc (strlen(Value)+strlen(Descr)+6,sizeof(char));\
      strcpy (NuovaStringa,"|");\
      if(strlen(Value)==0)\
	strcat(NuovaStringa," ");\
      else\
      	strcat (NuovaStringa,Value);\
      strcat (NuovaStringa,"| |");\
      if(strlen(Descr)==0)\
	strcat(NuovaStringa," ");\
      else\
      	strcat (NuovaStringa,Descr);\
      strcat (NuovaStringa,"|");\
      }\
    else\
      {\
      NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+\
		strlen(Value)+strlen(Descr)+7)*sizeof(char));\
			/*  4 PIPE di separazione,2 spazi e il terminatore */\
      /*  Accodo Value e Descr separati dal PIPE  */ \
      strcat (NuovaStringa," |");\
      if(strlen(Value)==0)\
	strcat(NuovaStringa," ");\
      else\
      	strcat (NuovaStringa,Value);\
      strcat (NuovaStringa,"| |");\
      if(strlen(Descr)==0)\
	strcat(NuovaStringa," ");\
      else\
      	strcat (NuovaStringa,Descr);\
      strcat (NuovaStringa,"|");\
      }\
    XtFree (Value);\
    XtFree (Descr);\
    }\
  }\
\
/*  Libero la vecchia lista  */\
XtFree (PuntAppoggio);\
\
/*  Accodo alla lista una eventuale parte restante della stringa  */\
IndiceCiclo = OlGetNumForms (FormDiConf);\
i=IndiceForm+1;\
while (i<IndiceCiclo)\
  {\
  PuntCursore = EstraiTags (FormDiConf,IndiceForm+1,*ValoriInput);\
  if (PuntCursore != NULL)\
    {\
    NuovaStringa = XtRealloc (NuovaStringa,(strlen(NuovaStringa)+\
			strlen(PuntCursore)+2)*sizeof(char));\
    strcat (NuovaStringa," ");\
    strcat (NuovaStringa,PuntCursore);\
    }\
  i++;\
  }\
\
*ValoriInput = NuovaStringa;\
\
/*  Rimetto a sensitive il bottone chiamante  */\
set_something (BottoneTag, XmNsensitive, True);\
\
XtDestroyWidget (TagsInput);\
}

*pushButton19.class: pushButton
*pushButton19.static: true
*pushButton19.name: pushButton19
*pushButton19.parent: form10
*pushButton19.x: 110
*pushButton19.y: 300
*pushButton19.width: 90
*pushButton19.height: 40
*pushButton19.labelString: "CANCEL"
*pushButton19.bottomAttachment: "attach_form"
*pushButton19.bottomOffset: 10
*pushButton19.leftAttachment: "attach_widget"
*pushButton19.leftOffset: 10
*pushButton19.leftWidget: "pushButton18"
*pushButton19.topAttachment: "attach_none"
*pushButton19.topOffset: 0
*pushButton19.activateCallback: {\
/*  Rimetto a sensitive il bottone chiamante */\
set_something (BottoneTag, XmNsensitive, True);\
\
XtDestroyWidget (TagsInput);\
}

*TitoloForm.class: label
*TitoloForm.static: true
*TitoloForm.name: TitoloForm
*TitoloForm.parent: form10
*TitoloForm.x: 160
*TitoloForm.y: 10
*TitoloForm.width: 280
*TitoloForm.height: 40
*TitoloForm.labelString: ""
*TitoloForm.leftAttachment: "attach_form"
*TitoloForm.leftOffset: 10
*TitoloForm.rightAttachment: "attach_form"
*TitoloForm.rightOffset: 10
*TitoloForm.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"

*TagsWindow.class: scrolledWindow
*TagsWindow.static: true
*TagsWindow.name: TagsWindow
*TagsWindow.parent: form10
*TagsWindow.scrollingPolicy: "automatic"
*TagsWindow.x: 20
*TagsWindow.y: 60
*TagsWindow.width: 560
*TagsWindow.height: 210
*TagsWindow.bottomAttachment: "attach_form"
*TagsWindow.bottomOffset: 85
*TagsWindow.leftAttachment: "attach_form"
*TagsWindow.rightAttachment: "attach_form"
*TagsWindow.rightOffset: 20
*TagsWindow.topAttachment: "attach_form"
*TagsWindow.topOffset: 70
*TagsWindow.leftOffset: 20

