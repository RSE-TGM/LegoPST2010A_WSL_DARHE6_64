! UIMX ascii 2.5 key: 7351                                                      

*AnimateIconSelection.class: topLevelShell
*AnimateIconSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo AnimateIconSelection.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)AnimateIconSelection.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#ifdef VMS\
#include <signal.h>\
#endif\
#include "res_edit.h"\
#include "config.h"\
\
void disableButtonIcSel( );\
void riableButtonIcSel( );\
void InserisciItem ( );\
void RefreshLista( );\

*AnimateIconSelection.ispecdecl: Widget *ListaF,Parente,OggettoSelezionato;\
int TipoIconaA;\
char ColoreBkg[20];\
PROG_DATA *proc_data;\

*AnimateIconSelection.ispeclist: ListaF, Parente, OggettoSelezionato, TipoIconaA, ColoreBkg, proc_data
*AnimateIconSelection.ispeclist.ListaF: "Widget", "*%ListaF%"
*AnimateIconSelection.ispeclist.Parente: "Widget", "%Parente%"
*AnimateIconSelection.ispeclist.OggettoSelezionato: "Widget", "%OggettoSelezionato%"
*AnimateIconSelection.ispeclist.TipoIconaA: "int", "%TipoIconaA%"
*AnimateIconSelection.ispeclist.ColoreBkg: "unsigned char", "%ColoreBkg%[20]"
*AnimateIconSelection.ispeclist.proc_data: "PROG_DATA", "*%proc_data%"
*AnimateIconSelection.funcdecl: swidget create_AnimateIconSelection(TipoAI,Padre1,Figli,OggSel,StringaColore)\
int TipoAI;\
Widget Padre1,*Figli,OggSel;\
char *StringaColore;
*AnimateIconSelection.funcname: create_AnimateIconSelection
*AnimateIconSelection.funcdef: "swidget", "<create_AnimateIconSelection>(%)"
*AnimateIconSelection.argdecl: int TipoAI;\
Widget Padre1;\
Widget *Figli;\
Widget OggSel;\
unsigned char *StringaColore;
*AnimateIconSelection.arglist: TipoAI, Padre1, Figli, OggSel, StringaColore
*AnimateIconSelection.arglist.TipoAI: "int", "%TipoAI%"
*AnimateIconSelection.arglist.Padre1: "Widget", "%Padre1%"
*AnimateIconSelection.arglist.Figli: "Widget", "*%Figli%"
*AnimateIconSelection.arglist.OggSel: "Widget", "%OggSel%"
*AnimateIconSelection.arglist.StringaColore: "unsigned char", "*%StringaColore%"
*AnimateIconSelection.icode: char *Appo;\
Widget Lista;\
\
strcpy (ColoreBkg,StringaColore);\
OggettoSelezionato = OggSel;\
ListaF = Figli; \
TipoIconaA = TipoAI;\
Parente = Padre1;\

*AnimateIconSelection.fcode: /*  Aggiorna la lista delle icone o dei bitmap  */\
RefreshLista();\
\
/*  Setto la selezione di default */\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);\
Appo = (char *)XmTextFieldGetString (ListaF[2]);\
XmTextSetString (Lista,Appo);\
XtFree (Appo);\
\
/*  Setta la posizione dell'interfaccia rispetto al parent  */\
InterfaceSetPos (AnimateIconSelection,Padre1);\
\
return(rtrn);\

*AnimateIconSelection.auxdecl: #ifdef VMS\
/******************************************\
 * callback che effettua la kill \
 * del processo (draw,bitmap editor)\
 * nel parametro  "XtPointer pid" \
 * si trova il pid del processo da uccidere\
 ******************************************/\
static void uccidi_processo(Widget wid,XtPointer pr_dat,XtPointer cb_arg)\
{\
   extern Display *UxDisplay;\
   PROG_DATA *pdata;\
\
   pdata = (PROG_DATA *)pr_dat;\
\
   \
   if(pdata != NULL)\
   {\
      if( pdata->Itimer != 0)\
         XtRemoveTimeOut( pdata->Itimer );\
\
      XSync( UxDisplay );\
\
      if( (kill(pdata->fpid,SIGTERM)) != 0)\
         printf("Kill Process Failed\n");\
      else\
         printf("Kill Process Ok\n");\
   }\
}\
\
/**************************************\
 * rimuove dalla lista delle callback\
 * la callback uccidi processo\
 * perche il processo non esiste piu'\
 **************************************/\
void rimuovi_callback()\
{\
   XtRemoveCallback(AnimateIconSelection,XmNdestroyCallback,\
                    uccidi_processo,(XtPointer)proc_data);\
}\
\
#endif /* defined VMS */\
\
/*****************************************\
 disabilita i bottoni di Edit e Create\
 ****************************************/\
void disableButtonIcSel()\
{\
   set_something(EditIconItem,XmNsensitive,False);\
   set_something(CreateIconItem,XmNsensitive,False);\
}\
\
/*****************************************\
 riabilita i bottoni di Edit e Create\
 ****************************************/\
void riableButtonIcSel()\
{\
   set_something(EditIconItem,XmNsensitive,True);\
   set_something(CreateIconItem,XmNsensitive,True);\
}\
\
void InserisciItem (char *lista_ele,Widget Lista)\
{\
char Elemento[200],StringaLetta[200];\
XmString XmInserire;\
int i,k;\
\
/*\
	non esistono files\
*/\
if(lista_ele == NULL)\
	return;\
i = 0;\
while ( i < strlen (lista_ele) )\
  {\
  k=0;\
  while ( lista_ele[i] != '.')\
    {\
    Elemento[k] = lista_ele[i];\
    k++;\
    i++;\
    }\
  Elemento[k] = '\0';\
  XmInserire = XmStringCreateSimple (Elemento);\
  XmListAddItemUnselected (Lista,XmInserire,0);\
  XmStringFree (XmInserire);\
  while ( (lista_ele[i] != '\n') && (i<strlen(lista_ele)) )\
    i++;\
  i++;\
  }\
}\
\
void RefreshLista()\
{\
char *lista_elementi;\
char Comando[200];\
Widget Lista;\
\
if (TipoIconaA == SEL_BITMAP)\
	{\
	strcpy (Comando,XlGetenv(ENVICO));\
	strcat (Comando,"/*.bmp");\
	lista_elementi = (char *)XlGetDir (XlConvPathVms(Comando));	\
	}\
if (TipoIconaA == SEL_ICONA)\
	{\
	strcpy (Comando,XlGetenv(ENVICO));\
	strcat (Comando,"/*.ico");\
	lista_elementi = (char *)XlGetDir (XlConvPathVms(Comando));	\
	}\
\
/*  Prendo dalla selection box l'ID della lista degli item  */\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox1,XmDIALOG_LIST);\
\
SettaBottoni (True,selectionBox1);\
\
XmListDeleteAllItems (Lista);\
InserisciItem (lista_elementi,Lista);\
XtFree (lista_elementi);\
}
*AnimateIconSelection.static: true
*AnimateIconSelection.name: AnimateIconSelection
*AnimateIconSelection.parent: NO_PARENT
*AnimateIconSelection.parentExpression: Padre1
*AnimateIconSelection.x: 660
*AnimateIconSelection.y: 150
*AnimateIconSelection.width: 360
*AnimateIconSelection.height: 450
*AnimateIconSelection.allowShellResize: "true"
*AnimateIconSelection.iconName: "Animate Icon Selection"
*AnimateIconSelection.destroyCallback: {\
\
}
*AnimateIconSelection.createCallbackClientData: (XtPointer) 0x0
*AnimateIconSelection.destroyCallbackClientData: (XtPointer) 0x0

*mainWindow8.class: mainWindow
*mainWindow8.static: true
*mainWindow8.name: mainWindow8
*mainWindow8.parent: AnimateIconSelection
*mainWindow8.unitType: "pixels"
*mainWindow8.x: 90
*mainWindow8.y: 150
*mainWindow8.width: 30
*mainWindow8.height: 90

*menu7.class: rowColumn
*menu7.static: true
*menu7.name: menu7
*menu7.parent: mainWindow8
*menu7.rowColumnType: "menu_bar"
*menu7.menuAccelerator: "<KeyUp>F10"

*FileIconPane.class: rowColumn
*FileIconPane.static: true
*FileIconPane.name: FileIconPane
*FileIconPane.parent: menu7
*FileIconPane.rowColumnType: "menu_pulldown"

*EditIconItem.class: pushButton
*EditIconItem.static: true
*EditIconItem.name: EditIconItem
*EditIconItem.parent: FileIconPane
*EditIconItem.labelString: "Edit"
*EditIconItem.mnemonic: "E"
*EditIconItem.activateCallback: {\
Widget Figlio;\
char stringa[100],comando[100],nomefile[200];\
FILE *prova;\
\
Figlio = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);\
\
strcpy (nomefile, getenv (ENVICO) );\
strcat (nomefile,"/");\
strcat (nomefile,XmTextGetString (Figlio));\
\
if (TipoIconaA == SEL_BITMAP)\
	strcat (nomefile,".bmp");\
else if (TipoIconaA == SEL_ICONA)\
	strcat (nomefile,".ico");\
\
prova = fopen(nomefile,"r");\
if ( (prova == NULL) || (nomefile[strlen(nomefile) -1] == '/') )\
	{\
	strcpy (stringa,"Unable to open file!");\
	VisualizzaMessageBox (GENERICA,AnimateIconSelection,stringa,OggettoSelezionato);\
	}\
else\
	{\
	if (TipoIconaA == SEL_BITMAP)\
		proc_data = EseguiBitmap (nomefile,selectionBox1);\
	else if (TipoIconaA == SEL_ICONA)\
		proc_data = EseguiIcona (nomefile,selectionBox1,ColoreBkg,OggettoSelezionato);\
#ifdef VMS\
/* aggancio la callback sulla destroy della interfaccia per il kill del processo */\
        XtAddCallback(AnimateIconSelection,XmNdestroyCallback,\
                      uccidi_processo,(XtPointer)proc_data);\
#endif\
	}\
}

*CreateIconItem.class: pushButton
*CreateIconItem.static: true
*CreateIconItem.name: CreateIconItem
*CreateIconItem.parent: FileIconPane
*CreateIconItem.labelString: "Create..."
*CreateIconItem.mnemonic: "C"
*CreateIconItem.activateCallback: {\
char nomefile[200],stringa[100];\
Widget Figlio;\
FILE *prova;\
extern swidget create_BitmapProperties( );\
\
Figlio = (Widget)XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);\
\
strcpy (nomefile, (char *)getenv (ENVICO) );\
strcat (nomefile,"/");\
strcat (nomefile,XmTextGetString (Figlio));\
\
if (TipoIconaA == SEL_BITMAP)\
	strcat (nomefile,".bmp");\
else if (TipoIconaA == SEL_ICONA)\
	strcat (nomefile,".ico");\
\
prova = fopen (nomefile, "r");\
if ( (prova == NULL) && (nomefile[strlen(nomefile)-1] != '/') )\
	{\
	if (TipoIconaA == SEL_BITMAP)\
		UxPopupInterface (create_BitmapProperties(nomefile,\
						selectionBox1),no_grab);\
	else if (TipoIconaA == SEL_ICONA)\
           {\
		proc_data = EseguiIcona (nomefile,selectionBox1,ColoreBkg,OggettoSelezionato);\
#ifdef VMS\
/* sulla destroy faccio la kill del processo */\
                XtAddCallback(AnimateIconSelection, XmNdestroyCallback,\
                              uccidi_processo, proc_data);\
#endif\
           }\
	}\
else\
	{\
	strcpy (stringa,"File already exist!Open on edit mode?");\
	if (TipoIconaA == SEL_BITMAP)\
	  VisualizzaMessageBox (BITMAP,selectionBox1,stringa,OggettoSelezionato);\
	else if (TipoIconaA == SEL_ICONA)\
	  VisualizzaMessageBox (ICONA,selectionBox1,stringa,OggettoSelezionato);\
	}\
}

*menu7_top_b1.class: cascadeButton
*menu7_top_b1.static: true
*menu7_top_b1.name: menu7_top_b1
*menu7_top_b1.parent: menu7
*menu7_top_b1.labelString: "File"
*menu7_top_b1.subMenuId: "FileIconPane"

*selectionBox1.class: selectionBox
*selectionBox1.static: true
*selectionBox1.name: selectionBox1
*selectionBox1.parent: mainWindow8
*selectionBox1.okLabelString: "Import"
*selectionBox1.listLabelString: "Available Animate Icon"
*selectionBox1.cancelCallback: {\
char comando[200];\
\
set_something (ListaF[0], XmNsensitive, True);\
set_something (ListaF[2], XmNsensitive, True);\
XtDestroyWidget (AnimateIconSelection);\
}
*selectionBox1.okCallback: {\
Widget Lista;\
XmString *ListaItem,XmSelezionato;\
int selezione,posizione,*ListaSel,NumSel;\
char comando[200],*NomeFile;\
\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox1, XmDIALOG_TEXT);\
\
NomeFile = (char *)XmTextGetString (Lista );\
\
XmTextFieldSetString (ListaF[2], NomeFile);\
XtFree (NomeFile);\
set_something (ListaF[0], XmNsensitive, True);\
set_something (ListaF[2], XmNsensitive, True);\
XtDestroyWidget (AnimateIconSelection);\
}
*selectionBox1.autoUnmanage: "false"

