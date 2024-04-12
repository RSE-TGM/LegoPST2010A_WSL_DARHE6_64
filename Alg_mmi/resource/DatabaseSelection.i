! UIMX ascii 2.5 key: 6006                                                      

*DatabaseSelection.class: topLevelShell
*DatabaseSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo DatabaseSelection.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)DatabaseSelection.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
/*\
 *  Interfaccia utilizzata per la selezione dei Component e Subsistem\
 *  utilizzate nella come filtro nella selezione delle variabili\
 */\
\
#include <stdio.h>\
#include <Ol/OlDatabaseTopologia.h>\
#include "res_edit.h"\
\
void InserisciElementi ( );\
\

*DatabaseSelection.ispecdecl: Widget *RigaInp1;
*DatabaseSelection.ispeclist: RigaInp1
*DatabaseSelection.ispeclist.RigaInp1: "Widget", "*%RigaInp1%"
*DatabaseSelection.funcdecl: swidget create_DatabaseSelection(Widget Parente1, /* Shell del chiamante */\
		int TipoInput,    /* distingue se selezione dai Component o\
				     dai Subsistem */	\
		Widget *Riga,     /* Lista dei figli riga corrente del \
				    res. edit. */\
		OlDatabaseTopologiaObject Dbase1) /* Database topologia in uso */\

*DatabaseSelection.funcname: create_DatabaseSelection
*DatabaseSelection.funcdef: "swidget", "<create_DatabaseSelection>(%)"
*DatabaseSelection.argdecl: Widget Parente1;\
int TipoInput;\
Widget *Riga;\
OlDatabaseTopologiaObject Dbase1;
*DatabaseSelection.arglist: Parente1, TipoInput, Riga, Dbase1
*DatabaseSelection.arglist.Parente1: "Widget", "%Parente1%"
*DatabaseSelection.arglist.TipoInput: "int", "%TipoInput%"
*DatabaseSelection.arglist.Riga: "Widget", "*%Riga%"
*DatabaseSelection.arglist.Dbase1: "OlDatabaseTopologiaObject", "%Dbase1%"
*DatabaseSelection.icode: char *Lista,*StrDef;\
Widget Oggetto;\
\
RigaInp1 = Riga;
*DatabaseSelection.fcode: if (TipoInput == SEL_SUBS)\
  Lista = (char *)OlGetSubSystem(Dbase1);\
if (TipoInput == SEL_COMP)\
  Lista = (char *)OlGetComponent(Dbase1);\
/*  Carico la lista degli item  */\
Oggetto = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_LIST);\
InserisciElementi (Oggetto,Lista);\
XtFree (Lista);\
\
/*  Setto la selezione di default  */\
Oggetto = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_TEXT);\
StrDef = (char *)XmTextFieldGetString (RigaInp1[2]);\
XmTextSetString (Oggetto,StrDef);\
XtFree (StrDef);\
\
/*  Setta la posiozne dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (DatabaseSelection,Parente1);\
\
return(rtrn);\

*DatabaseSelection.auxdecl: void InserisciElementi (Widget WdgLista,char *ChrLista)\
{\
XmString XmAppoggio;\
int i,Numero;\
\
/*  Controllo nel caso la lista sia vuota  */\
if (ChrLista)\
  {\
  memcpy (&Numero,ChrLista,sizeof(int));\
  ChrLista += sizeof(int);\
\
  for (i=0;i<Numero;i++)\
    {\
    XmAppoggio = XmStringCreateSimple (ChrLista);\
    XmListAddItemUnselected (WdgLista, XmAppoggio, 0);\
    XmStringFree (XmAppoggio);\
    ChrLista += 25;\
    }\
  }\
}\

*DatabaseSelection.static: true
*DatabaseSelection.name: DatabaseSelection
*DatabaseSelection.parent: NO_PARENT
*DatabaseSelection.parentExpression: Parente1
*DatabaseSelection.x: 610
*DatabaseSelection.y: 110
*DatabaseSelection.width: 410
*DatabaseSelection.height: 390

*mainWindow7.class: mainWindow
*mainWindow7.static: true
*mainWindow7.name: mainWindow7
*mainWindow7.parent: DatabaseSelection
*mainWindow7.unitType: "pixels"
*mainWindow7.x: 70
*mainWindow7.y: 70
*mainWindow7.width: 10
*mainWindow7.height: 70

*menu6.class: rowColumn
*menu6.static: true
*menu6.name: menu6
*menu6.parent: mainWindow7
*menu6.rowColumnType: "menu_bar"

*DatabasePane.class: rowColumn
*DatabasePane.static: true
*DatabasePane.name: DatabasePane
*DatabasePane.parent: menu6
*DatabasePane.rowColumnType: "menu_pulldown"

*DatabaseEditItem.class: pushButton
*DatabaseEditItem.static: true
*DatabaseEditItem.name: DatabaseEditItem
*DatabaseEditItem.parent: DatabasePane
*DatabaseEditItem.labelString: "Edit"

*DatabaseCreateItem.class: pushButton
*DatabaseCreateItem.static: true
*DatabaseCreateItem.name: DatabaseCreateItem
*DatabaseCreateItem.parent: DatabasePane
*DatabaseCreateItem.labelString: "Create..."

*menu6_top_b1.class: cascadeButton
*menu6_top_b1.static: true
*menu6_top_b1.name: menu6_top_b1
*menu6_top_b1.parent: menu6
*menu6_top_b1.labelString: "File"
*menu6_top_b1.subMenuId: "DatabasePane"

*selectionBox2.class: selectionBox
*selectionBox2.static: true
*selectionBox2.name: selectionBox2
*selectionBox2.parent: mainWindow7
*selectionBox2.okLabelString: "Import"
*selectionBox2.okCallback: {\
Widget Lista;\
char *NomeFile;\
\
Lista = (Widget )XmSelectionBoxGetChild (selectionBox2, XmDIALOG_TEXT);\
\
NomeFile = (char *)XmTextGetString (Lista );\
\
XmTextFieldSetString (RigaInp1[2], NomeFile);\
XtFree (NomeFile);\
set_something (RigaInp1[0], XmNsensitive, True);\
set_something (RigaInp1[2], XmNsensitive, True);\
\
XtDestroyWidget (DatabaseSelection);\
}
*selectionBox2.cancelCallback: {\
set_something (RigaInp1[0], XmNsensitive, True);\
set_something (RigaInp1[2], XmNsensitive, True);\
\
XtDestroyWidget (DatabaseSelection);\
}

