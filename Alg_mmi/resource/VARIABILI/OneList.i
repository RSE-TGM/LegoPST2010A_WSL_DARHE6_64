! UIMX ascii 2.5 key: 4569                                                      

*OneList.class: topLevelShell
*OneList.gbldecl: /*\
        Inizio sezione per SCCS \
*/\
/*\
   modulo OneList.i\
   tipo \
   release 5.2\
   data 2/6/96\
   reserved @(#)OneList.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
/*\
  Interfaccia per la selezione dei modelli e delle variabili\
*/\
#include <stdio.h>\
#include <string.h>\
#include <Ol/OlDatabaseTopologia.h>\
#include "sim_param.h"\
#include "VarEdit.h"\
#include "res_edit.h"\
\
extern char *CaricaElencoModelli();\
extern char *CaricaElencoVariabili();\

*OneList.ispecdecl: Widget *PadroneChiam;\
int *PosModel;\
int *PosVariab;\
int ModOrVar;
*OneList.ispeclist: PadroneChiam, PosModel, PosVariab, ModOrVar
*OneList.ispeclist.PadroneChiam: "Widget", "*%PadroneChiam%"
*OneList.ispeclist.PosModel: "int", "*%PosModel%"
*OneList.ispeclist.PosVariab: "int", "*%PosVariab%"
*OneList.ispeclist.ModOrVar: "int", "%ModOrVar%"
*OneList.funcdecl: swidget create_OneList(Parent1,Padrone,TipoLista,Lista)\
Widget Parent1;   /* Shell chiamante */\
Widget *Padrone;  /* Elenco di Widgets appartenenti alla\
                     interfaccia di VariableEditor che \
                     devono essere modificati in seguito\
                     alla selezione effettuata \
                     Es: inserimento della scritta ALL nel\
                         text field dei blocchi     */\
int TipoLista;    /* Distingue se lista di variabili o lista di modelli */\
char *Lista;      /* Lista delle variabili o dei modelli\
                     memorizzata come intero seguito dalle stringhe */ \

*OneList.funcname: create_OneList
*OneList.funcdef: "swidget", "<create_OneList>(%)"
*OneList.argdecl: Widget Parent1;\
Widget *Padrone;\
int TipoLista;\
unsigned char *Lista;
*OneList.arglist: Parent1, Padrone, TipoLista, Lista
*OneList.arglist.Parent1: "Widget", "%Parent1%"
*OneList.arglist.Padrone: "Widget", "*%Padrone%"
*OneList.arglist.TipoLista: "int", "%TipoLista%"
*OneList.arglist.Lista: "unsigned char", "*%Lista%"
*OneList.icode: PadroneChiam = Padrone;\
ModOrVar = TipoLista;\
\
set_something (PadroneChiam[0], XmNsensitive, False);
*OneList.fcode: if (ModOrVar == MODELLI)\
	CaricaLista (scrolledList1,Lista,MAX_LUN_NOME_MODELLO,MODELLI);\
else CaricaLista (scrolledList1,Lista,MAX_LUN_NOME_VAR+MAX_LUN_DESCR_VAR,VARIABILI);\
\
/*  Setta la posizione dell'interfaccia secondo la posizione del Parent  */\
InterfaceSetPos (OneList,Parent1);\
\
return(rtrn);\

*OneList.auxdecl:
*OneList.static: true
*OneList.name: OneList
*OneList.parent: NO_PARENT
*OneList.x: 650
*OneList.y: 29
*OneList.width: 460
*OneList.height: 300
*OneList.iconName: "Selection Window"

*form3.class: form
*form3.static: true
*form3.name: form3
*form3.parent: OneList
*form3.resizePolicy: "resize_none"
*form3.unitType: "pixels"
*form3.x: 80
*form3.y: 80
*form3.width: 80
*form3.height: 90

*separator3.class: separator
*separator3.static: true
*separator3.name: separator3
*separator3.parent: form3
*separator3.x: 2
*separator3.y: 240
*separator3.width: 440
*separator3.height: 10
*separator3.bottomAttachment: "attach_position"
*separator3.bottomOffset: 0
*separator3.leftAttachment: "attach_position"
*separator3.leftOffset: 0
*separator3.rightAttachment: "attach_position"
*separator3.rightOffset: 0
*separator3.topAttachment: "attach_position"
*separator3.topOffset: 0
*separator3.bottomPosition: 82
*separator3.leftPosition: 1
*separator3.rightPosition: 99
*separator3.topPosition: 80

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.parent: form3
*scrolledWindow1.x: 20
*scrolledWindow1.y: 20
*scrolledWindow1.leftAttachment: "attach_position"
*scrolledWindow1.leftOffset: 0
*scrolledWindow1.rightAttachment: "attach_position"
*scrolledWindow1.rightOffset: 0
*scrolledWindow1.topAttachment: "attach_position"
*scrolledWindow1.topOffset: 0
*scrolledWindow1.bottomAttachment: "attach_position"
*scrolledWindow1.bottomOffset: 0
*scrolledWindow1.bottomWidget: ""
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.bottomPosition: 66
*scrolledWindow1.leftPosition: 5
*scrolledWindow1.rightPosition: 95
*scrolledWindow1.topPosition: 5

*scrolledList1.class: scrolledList
*scrolledList1.static: true
*scrolledList1.name: scrolledList1
*scrolledList1.parent: scrolledWindow1
*scrolledList1.width: 420
*scrolledList1.height: 170
*scrolledList1.listSizePolicy: "constant"

*pushButton9.class: pushButton
*pushButton9.static: true
*pushButton9.name: pushButton9
*pushButton9.parent: form3
*pushButton9.x: 20
*pushButton9.y: 260
*pushButton9.width: 80
*pushButton9.height: 30
*pushButton9.bottomAttachment: "attach_position"
*pushButton9.bottomOffset: 0
*pushButton9.topAttachment: "attach_position"
*pushButton9.topOffset: 0
*pushButton9.topWidget: ""
*pushButton9.labelString: "OK"
*pushButton9.activateCallback: {\
Boolean selezione;\
int NumItem,*ListaSel,NumSel,pos;\
char *Def="ALL";\
char Nome[150];\
XmString *ListaItem;\
\
selezione = XmListGetSelectedPos (scrolledList1,&ListaSel,&NumSel);\
get_something (scrolledList1, XmNitems, &ListaItem);\
get_something (scrolledList1, XmNitemCount, &NumItem);\
\
/*  Prendo la posizione dell'elemento selezionato se c'e' altrimenti\
	prendo la posizione 0 come posizione di default  */\
if (selezione)\
  pos = ListaSel[0] - 1;\
else pos = 0;\
\
if (NumSel != 0)\
  free (ListaSel);\
\
if (NumItem != 0)\
  { \
  strcpy (Nome,extract_string(ListaItem[pos]));\
  if (ModOrVar == MODELLI)\
    {\
    XmTextFieldSetString (PadroneChiam[3],Nome );\
    set_something (PadroneChiam[0], XmNsensitive, True);\
    set_something (PadroneChiam[1], XmNsensitive, True);\
    set_something (PadroneChiam[2], XmNsensitive, True);\
    XmTextFieldSetString (PadroneChiam[4],Def);\
    XmTextFieldSetString (PadroneChiam[5],"");\
    }\
  else\
    {\
    XmTextFieldSetString (PadroneChiam[1], Nome);\
    set_something (PadroneChiam[0], XmNsensitive, True);\
    }\
  }\
else\
  {\
  if (ModOrVar == MODELLI)\
    {\
    XmTextFieldSetString (PadroneChiam[3], "" );\
    XmTextFieldSetString (PadroneChiam[4], "" );\
    XmTextFieldSetString (PadroneChiam[5], "" );\
    }\
/* Lore: caso relativo alle variabili. Non vi sono variabili.\
   Annulla il campo testo delle variabili\
*/ \
  else XmTextFieldSetString (PadroneChiam[1], "" );\
  }\
\
free (PadroneChiam);\
XtDestroyWidget (OneList);\
}
*pushButton9.bottomPosition: 98
*pushButton9.topPosition: 85
*pushButton9.leftAttachment: "attach_position"
*pushButton9.leftOffset: 0
*pushButton9.leftPosition: 5
*pushButton9.rightAttachment: "attach_position"
*pushButton9.rightPosition: 25

*pushButton10.class: pushButton
*pushButton10.static: true
*pushButton10.name: pushButton10
*pushButton10.parent: form3
*pushButton10.x: 110
*pushButton10.y: 260
*pushButton10.width: 80
*pushButton10.height: 30
*pushButton10.labelString: "CANCEL"
*pushButton10.bottomAttachment: "attach_position"
*pushButton10.bottomOffset: 0
*pushButton10.leftAttachment: "attach_position"
*pushButton10.leftOffset: 0
*pushButton10.leftWidget: ""
*pushButton10.topAttachment: "attach_position"
*pushButton10.topOffset: 0
*pushButton10.topWidget: ""
*pushButton10.activateCallback: {\
if (ModOrVar == MODELLI)\
  set_something (PadroneChiam[0], XmNsensitive, True);\
else\
  set_something (PadroneChiam[0], XmNsensitive, True);\
free (PadroneChiam);\
XtDestroyWidget (OneList);\
}
*pushButton10.bottomPosition: 98
*pushButton10.topPosition: 85
*pushButton10.leftPosition: 26
*pushButton10.rightAttachment: "attach_position"
*pushButton10.rightPosition: 46

*textField2.class: textField
*textField2.static: true
*textField2.name: textField2
*textField2.parent: form3
*textField2.x: 20
*textField2.y: 200
*textField2.width: 130
*textField2.height: 30
*textField2.bottomAttachment: "attach_position"
*textField2.bottomOffset: 0
*textField2.bottomWidget: ""
*textField2.leftAttachment: "attach_position"
*textField2.leftOffset: 0
*textField2.maxLength: 80
*textField2.bottomPosition: 78
*textField2.topAttachment: "attach_position"
*textField2.topPosition: 68
*textField2.leftPosition: 5
*textField2.rightAttachment: "attach_position"
*textField2.rightPosition: 35

*arrowButton1.class: arrowButton
*arrowButton1.static: true
*arrowButton1.name: arrowButton1
*arrowButton1.parent: form3
*arrowButton1.x: 150
*arrowButton1.y: 200
*arrowButton1.width: 30
*arrowButton1.height: 30
*arrowButton1.bottomAttachment: "attach_position"
*arrowButton1.bottomOffset: 0
*arrowButton1.bottomWidget: ""
*arrowButton1.leftAttachment: "attach_position"
*arrowButton1.leftOffset: 0
*arrowButton1.topAttachment: "attach_position"
*arrowButton1.topOffset: 0
*arrowButton1.activateCallback: {\
char *Ricerca,Messaggio[50];\
XmString XmRicerca,*XmRicercaList;\
int NumeroElementi,Posizione,*ListaSel,NumSel;\
Boolean Selezionato;\
\
Ricerca = XmTextFieldGetString (textField2);\
XmRicerca = XmStringCreateSimple (Ricerca);\
\
get_something (scrolledList1, XmNitems, &XmRicercaList);\
get_something (scrolledList1, XmNitemCount, &NumeroElementi);\
\
Selezionato = XmListGetSelectedPos (scrolledList1, &ListaSel, &NumSel);\
if (Selezionato)\
	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				SU,ListaSel[NumSel-1]);\
else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				SU,NumeroElementi+1);\
if (Posizione == 0)\
	{\
	strcpy (Messaggio,"String not found!\0");\
	VisualizzaMessageBox (GENERICA,OneList,Messaggio,scrolledList1);\
	}\
else\
	{\
	XmListSelectPos (scrolledList1,Posizione,True);\
	XmListSetPos (scrolledList1,Posizione);\
	}\
}
*arrowButton1.bottomPosition: 78
*arrowButton1.topPosition: 68
*arrowButton1.leftPosition: 38
*arrowButton1.rightAttachment: "attach_position"
*arrowButton1.rightPosition: 45

*arrowButton2.class: arrowButton
*arrowButton2.static: true
*arrowButton2.name: arrowButton2
*arrowButton2.parent: form3
*arrowButton2.x: 180
*arrowButton2.y: 200
*arrowButton2.width: 30
*arrowButton2.height: 30
*arrowButton2.bottomAttachment: "attach_position"
*arrowButton2.bottomOffset: 0
*arrowButton2.bottomWidget: ""
*arrowButton2.leftAttachment: "attach_position"
*arrowButton2.leftOffset: 0
*arrowButton2.topAttachment: "attach_position"
*arrowButton2.topOffset: 0
*arrowButton2.arrowDirection: "arrow_down"
*arrowButton2.activateCallback: {\
char *Ricerca,Messaggio[50];\
XmString XmRicerca,*XmRicercaList;\
int NumeroElementi,Posizione,*ListaSel,NumSel;\
Boolean Selezionato;\
\
Ricerca = XmTextFieldGetString (textField2);\
XmRicerca = XmStringCreateSimple (Ricerca);\
\
get_something (scrolledList1, XmNitems, &XmRicercaList);\
get_something (scrolledList1, XmNitemCount, &NumeroElementi);\
\
Selezionato = XmListGetSelectedPos (scrolledList1, &ListaSel, &NumSel);\
if (Selezionato)\
	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				GIU,ListaSel[NumSel-1]);\
else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				GIU,0);\
if (Posizione == 0)\
	{\
	strcpy (Messaggio,"String not found!\0");\
	VisualizzaMessageBox (GENERICA,OneList,Messaggio,scrolledList1);\
	}\
else\
	{\
	XmListSelectPos (scrolledList1,Posizione,True);\
	XmListSetPos (scrolledList1,Posizione);\
	}\
}
*arrowButton2.bottomPosition: 78
*arrowButton2.topPosition: 68
*arrowButton2.leftPosition: 45
*arrowButton2.rightAttachment: "attach_position"
*arrowButton2.rightPosition: 52

