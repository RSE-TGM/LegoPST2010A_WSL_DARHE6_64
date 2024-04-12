! UIMX ascii 2.5 key: 4671                                                      

*FormSelection.class: topLevelShell
*FormSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo FormSelection.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)FormSelection.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
\
#include <string.h>\
\
#include <Xl/Xl.h>\
#include <Rt/RtMemory.h>\
\
extern void InserisciItem();\
\
void AggiornaLista();
*FormSelection.ispecdecl: Widget Parente2,*Riga2;
*FormSelection.ispeclist: Parente2, Riga2
*FormSelection.ispeclist.Parente2: "Widget", "%Parente2%"
*FormSelection.ispeclist.Riga2: "Widget", "*%Riga2%"
*FormSelection.funcdecl: swidget create_FormSelection(Widget Pare, /* Shell del chiamante */\
		Widget *Rig)    /* Figli del Row Col del \
                                   resource editor in oggetto\
				   di editing */\

*FormSelection.funcname: create_FormSelection
*FormSelection.funcdef: "swidget", "<create_FormSelection>(%)"
*FormSelection.argdecl: Widget Pare;\
Widget *Rig;
*FormSelection.arglist: Pare, Rig
*FormSelection.arglist.Pare: "Widget", "%Pare%"
*FormSelection.arglist.Rig: "Widget", "*%Rig%"
*FormSelection.icode: char *Appo;\
Widget Lista;\
\
Parente2 = Pare;\
Riga2 = Rig;
*FormSelection.fcode: /* Aggiorna la lista delle form  */\
AggiornaLista();\
\
/* Setto la selezione di default */\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox3, XmDIALOG_TEXT);\
Appo = (char *)XmTextFieldGetString (Riga2[2]);\
XmTextSetString (Lista,Appo);\
XtFree (Appo);\
\
/*  Setta la posizione dell'interfaccia rispetto al parent  */\
InterfaceSetPos (FormSelection,Parente2);\
\
return(rtrn);\

*FormSelection.auxdecl: void AggiornaLista()\
{\
char *lista_elementi;\
char Comando[200];\
Widget Lista;\
\
strcpy (Comando,XlGetenv("LEGOCAD_USER"));\
strcat (Comando,"/legocad/libut_reg/libreg/*.frm");\
lista_elementi = (char *)XlGetDir (XlConvPathVms(Comando));\
\
/* Prendo dalla selectionbox l'ID della lista */\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox3,XmDIALOG_LIST);\
\
XmListDeleteAllItems (Lista);\
InserisciItem (lista_elementi,Lista);\
XtFree (lista_elementi);\
}
*FormSelection.static: true
*FormSelection.name: FormSelection
*FormSelection.parent: NO_PARENT
*FormSelection.parentExpression: Parente2
*FormSelection.x: 810
*FormSelection.y: 130
*FormSelection.width: 400
*FormSelection.height: 450

*mainWindow9.class: mainWindow
*mainWindow9.static: true
*mainWindow9.name: mainWindow9
*mainWindow9.parent: FormSelection
*mainWindow9.unitType: "pixels"
*mainWindow9.x: 110
*mainWindow9.y: 130
*mainWindow9.width: 40
*mainWindow9.height: 30

*selectionBox3.class: selectionBox
*selectionBox3.static: true
*selectionBox3.name: selectionBox3
*selectionBox3.parent: mainWindow9
*selectionBox3.cancelCallback: {\
set_something (Riga2[0], XmNsensitive, True);\
set_something (Riga2[2], XmNsensitive, True);\
\
XtDestroyWidget (FormSelection);\
}
*selectionBox3.okCallback: {\
Widget Lista;\
char *NomeFile;\
\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox3, XmDIALOG_TEXT);\
\
NomeFile = (char *)XmTextGetString (Lista );\
\
XmTextFieldSetString (Riga2[2], NomeFile);\
XtFree (NomeFile);\
set_something (Riga2[0], XmNsensitive, True);\
set_something (Riga2[2], XmNsensitive, True);\
\
XtDestroyWidget (FormSelection);\
}
*selectionBox3.okLabelString: "Import"
*selectionBox3.listLabelString: "Available forms:"
*selectionBox3.labelFontList: "-adobe-new century schoolbook-medium-r-normal--14-140-75-75-p-82-iso8859-1"
*selectionBox3.selectionLabelString: "Selected form:"
*selectionBox3.textColumns: 4
*selectionBox3.textFontList: "-adobe-new century schoolbook-medium-r-normal--14-140-75-75-p-82-iso8859-1"
*selectionBox3.textString: ""

