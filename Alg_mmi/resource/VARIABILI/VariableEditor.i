! UIMX ascii 2.5 key: 9225                                                      

*VariableEditor.class: formDialog
*VariableEditor.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo VariableEditor.i\
   tipo \
   release 5.2\
   data 2/6/96\
   reserved @(#)VariableEditor.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <string.h>\
#include <Xl/Xl.h>\
#include <Ol/OlDatabaseTopologia.h>\
#include "VarEdit.h"\
#include "PertDef.h"\
#include "UniMis.h"\
#include "res_edit.h"\
#include "sim_param.h"\
\
extern swidget create_OneList();\
extern swidget create_TwoList();\
extern swidget create_PerturbEditor();\
\

*VariableEditor.ispecdecl: swidget DrawA;\
Widget ListaBottoni[6],*RowColInp;\
OlDatabaseTopologiaObject Dbf;\
int *FiltroPerVar,TipoVariabile;\
char *UniMisura; \
Widget OggettoSelezionato,Parent4;\
Boolean FirstTime;
*VariableEditor.ispeclist: DrawA, ListaBottoni, RowColInp, Dbf, FiltroPerVar, TipoVariabile, UniMisura, OggettoSelezionato, Parent4, FirstTime
*VariableEditor.ispeclist.DrawA: "swidget", "%DrawA%"
*VariableEditor.ispeclist.ListaBottoni: "Widget", "%ListaBottoni%[6]"
*VariableEditor.ispeclist.RowColInp: "Widget", "*%RowColInp%"
*VariableEditor.ispeclist.Dbf: "OlDatabaseTopologiaObject", "%Dbf%"
*VariableEditor.ispeclist.FiltroPerVar: "int", "*%FiltroPerVar%"
*VariableEditor.ispeclist.TipoVariabile: "int", "%TipoVariabile%"
*VariableEditor.ispeclist.UniMisura: "unsigned char", "*%UniMisura%"
*VariableEditor.ispeclist.OggettoSelezionato: "Widget", "%OggettoSelezionato%"
*VariableEditor.ispeclist.Parent4: "Widget", "%Parent4%"
*VariableEditor.ispeclist.FirstTime: "Boolean", "%FirstTime%"
*VariableEditor.funcdecl: swidget create_VariableEditor(ListaDA,RCOgget,Padrino,TipoVar,DbTp)\
swidget ListaDA; /* id della drawing area della pagina corrente \
                    serve per la funzionalita' di grab per trovare\
                    l'oggetto attualmente in selezione */\
Widget *RCOgget; /* lista dei figli del Resource Editor appartenenti\
                    alla riga corrente */\
Widget Padrino;  /* Shell chiamante */\
int *TipoVar;    /* Tipo della variabile (se DA,DO ...) */\
OlDatabaseTopologiaObject DbTp; /* Database della topologia */
*VariableEditor.funcname: create_VariableEditor
*VariableEditor.funcdef: "swidget", "<create_VariableEditor>(%)"
*VariableEditor.argdecl: swidget ListaDA;\
Widget *RCOgget;\
Widget Padrino;\
int *TipoVar;\
OlDatabaseTopologiaObject DbTp;
*VariableEditor.arglist: ListaDA, RCOgget, Padrino, TipoVar, DbTp
*VariableEditor.arglist.ListaDA: "swidget", "%ListaDA%"
*VariableEditor.arglist.RCOgget: "Widget", "*%RCOgget%"
*VariableEditor.arglist.Padrino: "Widget", "%Padrino%"
*VariableEditor.arglist.TipoVar: "int", "*%TipoVar%"
*VariableEditor.arglist.DbTp: "OlDatabaseTopologiaObject", "%DbTp%"
*VariableEditor.icode: char *Description,*NomeModello,*NomeBlocco,*NomeVar,*Perturba;\
Boolean  Giusto;\
\
DrawA = ListaDA;\
RowColInp = RCOgget;\
FiltroPerVar = TipoVar;\
Dbf = DbTp;\
Parent4 = Padrino;\
\
FirstTime = True;
*VariableEditor.fcode: ListaBottoni[0] = (Widget )UnitItem;\
ListaBottoni[1] = (Widget )NULL;\
ListaBottoni[2] = (Widget )NULL;\
ListaBottoni[3] = (Widget )NULL;\
ListaBottoni[4] = (Widget )NULL;\
ListaBottoni[5] = (Widget )NULL;\
\
/*  Setta la posizione dell'interfaccia secondo il Parent \
InterfaceSetPos (VariableEditor,Parent4);*/\
\
return(rtrn);\

*VariableEditor.auxdecl: /**** ****************************************************\
        Routine che imposta l'option menu per le unita' di misura\
\
void ModificaOptionUnit\
        (\
	Push			--> Lista dei bottoni dell'option menu;\
        Iniziale                --> Prima lettera del nome della\
                                        variabile;\
	Unita			--> Stringa delle informazioni per le unita\
					di misura;\
        )\
\
        Valore di ritorno       --> Nessun valore di ritorno;\
*********************************************************/\
void ModificaOptionUnit (Widget *Push,char Iniziale,char *Unita)\
{\
Arg arg[2];\
XmString XmEtichetta;\
int pret,i,j,Indice;\
Boolean Trovata;\
char Vuota1[30],Vuota2[30],Str[30],Eti[30],UnitaSel[30];\
\
/* Dalla stringa della unita' di misura in input ricava il nome della \
	unita' di misura  */\
if (Unita != NULL)\
  pret = sscanf (Unita,"%s %s %s",Vuota1,Vuota2,UnitaSel);\
if ( (pret < 3) || (Unita==NULL) ) strcpy (UnitaSel,"");\
\
Indice =0;\
\
/*  Distrugge e reinizializza i bottoni dell'option menu delle\
	unita' di misura  */\
i=0;\
while (i < 6)\
	{\
	if (Push[i] != NULL)\
	  XtDestroyWidget (Push[i]);\
	Push[i] = NULL;\
	i++;\
	}\
\
Trovata = False;\
i = 0;\
#ifndef SCADA_MMI  /* nel caso scada-mmi non ricerca le unita' di misura */\
if (Iniziale != '\0')\
  {\
\
  while ( (SelUniMis[i].type != '!') && (!Trovata) )\
    {\
    if (SelUniMis[i].type == Iniziale)\
      { \
      Trovata = True;\
      j=0;\
      while ( SelUniMis[i].codm[j][0] != ' ' && j<6)\
        {\
        /*  Controlla la selezione di default  */\
	if(strlen(UnitaSel)==0)\
		Indice=0;\
        else if (strncmp(SelUniMis[i].codm[j],UnitaSel,strlen(UnitaSel))==0)\
			Indice = j;\
\
        strcpy (Str,SelUniMis[i].codm[j]);\
        XmEtichetta = XmStringCreateSimple (Str);\
        XtSetArg (arg[0], XmNlabelString, XmEtichetta);\
        Push[j] = XmCreatePushButton (UnitPane, "Bottone", arg, 1);\
        XtManageChild (Push[j]);\
        XmStringFree (XmEtichetta);\
        j++;\
        }\
      }\
      i++;\
    } \
  }\
#endif /* not SCADA_MMI */\
/* Controlla se non e' stata trovato nessun tipo di variabile conosciuto\
	oppure se il campo del nome della variabile era vuoto  */\
if ( (!Trovata) || (Iniziale == '\0') )\
  {\
  for (i=0;i<5;i++)\
    {\
    strcpy (Str,SelUniMis[14].codm[i]);\
    XmEtichetta = XmStringCreateSimple (Str);\
    XtSetArg (arg[0], XmNlabelString, XmEtichetta);\
    Push[i]= XmCreatePushButton (UnitPane, "Bottone", arg, 1);\
    XtManageChild (Push[i]);\
    XmStringFree (XmEtichetta);\
    }\
  }\
\
set_something (Unit, XmNmenuHistory, Push[Indice]);\
\
if (Trovata)\
  {\
  set_something (Unit, XmNsensitive, True);\
  }\
else set_something (Unit, XmNsensitive, False);\
}
*VariableEditor.static: true
*VariableEditor.name: VariableEditor
*VariableEditor.parent: NO_PARENT
*VariableEditor.defaultShell: topLevelShell
*VariableEditor.unitType: "pixels"
*VariableEditor.x: 499
*VariableEditor.y: 374
*VariableEditor.width: 430
*VariableEditor.height: 512
*VariableEditor.dialogStyle: "dialog_primary_application_modal"
*VariableEditor.mapCallback: {\
char *NomeModello,*NomeBlocco,*NomeVar,*Perturba;\
XmString XmStrTipo;\
char *Interpretare;\
Boolean Corretta;\
int uguali;\
Widget Pane,*ListaB;\
char Description[100],*Stringa;\
char *Subs,*Comp;\
XmString XmStr;\
Boolean Giusto;\
Arg arg[2];\
\
TipoVariabile = FiltroPerVar[0];\
UniMisura = NULL;\
\
XmStrTipo = (XmString )ControllaTipoVar (TipoVariabile,pushButton6,Elab);\
set_something (labVariableType,XmNlabelString,XmStrTipo);\
XmStringFree (XmStrTipo);\
\
#ifdef ON_MMI\
Corretta = False;\
\
/*  Disabilito il bottone di Grab della variabile  */\
set_something (pushButton13, XmNsensitive, False);\
\
  /*  Leggo dalla lista degli oggetti in input le label per i\
	component e per i subsystem  */\
  Comp = XmTextFieldGetString (RowColInp[0]);\
  Subs = XmTextFieldGetString (RowColInp[1]);\
  \
  /*  Setta le label dei component e subsystem  */\
  get_something (menu1, XmNsubMenuId, &Pane);\
  get_something (Pane, XmNchildren, &ListaB);\
\
  if (Comp[0] == '\0')\
    set_something (ListaB[1], XmNsensitive, False);\
  else\
    set_something (ListaB[1], XmNsensitive, True);\
\
  if (Subs[0] == '\0')\
    set_something (ListaB[2], XmNsensitive, False);\
  else\
    set_something (ListaB[2], XmNsensitive, True);\
\
  XmStr = XmStringCreateSimple (Comp);\
  set_something (labComponent, XmNlabelString, XmStr);\
  XmStringFree (XmStr);\
  XmStr = XmStringCreateSimple (Subs);\
  set_something (labSubSystem, XmNlabelString, XmStr);\
  XmStringFree (XmStr);\
\
/*  Leggo dal textfield ls stringa della definizione della variabile\
	per poterla interpretare  */\
Interpretare = XmTextFieldGetString (RowColInp[2]);\
\
Corretta = OlReadVariableString (Dbf,Interpretare, &NomeModello, &NomeBlocco,\
	&NomeVar, &Perturba, &UniMisura, TipoVariabile);\
\
#else\
\
/*  Legge se c'e' la descrizione della variabile  */\
Giusto = False;\
strcpy (Description,XmTextFieldGetString (RowColInp[2]));\
\
if (Description[0] != '\0')\
  {\
/*\
 Se esiste in selezione un oggetto del tipo icona animata\
 assume come label del component e del subsystem le\
 label dell'oggetto in selezione\
*/\
  OggettoSelezionato = (Widget )XlGetSelectedWidget (DrawA);\
  if ( XlIsAnimateIcon (OggettoSelezionato) )\
    {\
    /*  Setta le label dei component e subsystem  */\
    XtSetArg (arg[0], XlNcomponent, &Comp);\
    XtSetArg (arg[1], XlNsubsystem, &Subs);\
    XtGetValues (OggettoSelezionato, arg, 2);\
    get_something (menu1, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
\
    if (Comp[0] == '\0')\
       set_something (ListaB[1], XmNsensitive, False);\
    else\
       set_something (ListaB[1], XmNsensitive, True);\
\
    if (Subs[0] == '\0')\
      set_something (ListaB[2], XmNsensitive, False);\
    else\
      set_something (ListaB[2], XmNsensitive, True);\
\
    XmStr = XmStringCreateSimple (Comp);\
    set_something (labComponent, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    XmStr = XmStringCreateSimple (Subs);\
    set_something (labSubSystem, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    }\
  else\
    {\
    XmStr = XmStringCreateSimple (" ");\
    set_something (labComponent, XmNlabelString, XmStr);\
    set_something (labSubSystem, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    get_something (menu1, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
    set_something (ListaB[1], XmNsensitive, False);\
    set_something (ListaB[2], XmNsensitive, False);\
    }\
  Giusto = OlReadVariableString (Dbf,Description,&NomeModello,\
                                &NomeBlocco,&NomeVar,&Perturba,&UniMisura,\
				TipoVariabile);\
  }\
else\
  {\
/*\
 Se non e' specificato il nome della variabile di animazione\
 ed esiste in selezione una icona animata o display ne ricava\
 il nome della variabile di animazione: component\
 e subsystem vengono invece ricavati solo nel caso di icona \
 animata.\
*/ \
  OggettoSelezionato = (Widget )XlGetSelectedWidget (DrawA);\
  if ( XlIsAnimateIcon (OggettoSelezionato))\
    {\
    /*  Setta le label dei component e subsystem  */\
    XtSetArg (arg[0], XlNcomponent, &Comp);\
    XtSetArg (arg[1], XlNsubsystem, &Subs);\
    XtGetValues (OggettoSelezionato, arg, 2);\
\
    get_something (menu1, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
    if (Comp[0] == '\0')\
      set_something (ListaB[1], XmNsensitive, False);\
    else\
      set_something (ListaB[1], XmNsensitive, True);\
\
    if (Subs[0] == '\0')\
      set_something (ListaB[2], XmNsensitive, False);\
    else\
      set_something (ListaB[2], XmNsensitive, True);\
\
    XmStr = XmStringCreateSimple (Comp);\
    set_something (labComponent, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    XmStr = XmStringCreateSimple (Subs);\
    set_something (labSubSystem, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    }\
if(XlIsAnimateIcon(OggettoSelezionato) || XlIsIndic(OggettoSelezionato) )\
    {\
    /*  Prende se c'e' la prima variabile di Cambio Colore  */\
    strcpy (Description,(char *)XlGetFirstVcc (OggettoSelezionato));\
    if (Description[0] != '\0')\
      Giusto = OlReadVariableString (Dbf,Description,&NomeModello,\
                                &NomeBlocco,&NomeVar,&Perturba,&UniMisura,\
				TipoVariabile);\
    else\
      {\
      NomeModello = XtCalloc (1,sizeof(char));\
      NomeBlocco = XtCalloc (1,sizeof(char));\
      NomeVar = XtCalloc (1,sizeof(char));\
      Perturba = XtCalloc (1,sizeof(char));\
      UniMisura = XtCalloc (1,sizeof(char));\
      }\
    }\
  else\
    {\
    XmStr = XmStringCreateSimple (" ");\
    set_something (labComponent, XmNlabelString, XmStr);\
    set_something (labSubSystem, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    get_something (menu1, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
    set_something (ListaB[1], XmNsensitive, False);\
    set_something (ListaB[2], XmNsensitive, False);\
    NomeModello = XtCalloc (1,sizeof(char));\
    NomeBlocco = XtCalloc (1,sizeof(char));\
    NomeVar = XtCalloc (1,sizeof(char));\
    Perturba = XtCalloc (1,sizeof(char));\
    UniMisura = XtCalloc (1,sizeof(char));\
    }\
  }\
#endif\
\
\
/*  Setta a True i bottoni dei blocchi e delle variabili  */\
if (NomeModello[0] != '\0')\
  {\
  set_something (pushButton4, XmNsensitive, True);\
  set_something (pushButton5, XmNsensitive, True);\
  }\
#ifdef SCADA_MMI\
/*\
 Unmanage degli oggetti non utilizzati\
*/\
XtUnmanageChild(labVarType);\
XtUnmanageChild(separator1);\
XtUnmanageChild(label1);\
XtUnmanageChild(pushButton3);\
XtUnmanageChild(menu1);\
XtUnmanageChild(label4);\
XtUnmanageChild(label9);\
XtUnmanageChild(textNomeModello);\
XtUnmanageChild(labVariableType);\
XtUnmanageChild(labComponent);\
XtUnmanageChild(labComp);\
XtUnmanageChild(labSubS);\
XtUnmanageChild(labSubSystem);\
XtUnmanageChild(Unit);\
XtUnmanageChild(separator8);\
/*\
 Riposizionamento degli oggetti\
 rimanenti\
*/\
set_something(XtParent(VariableEditor),XmNheight,260);\
\
set_something(label2, XmNtopPosition, 2);\
/* modifica la label BLOCK nella label TYPE  */\
XmStr = XmStringCreateSimple ("TYPE:");\
set_something(label2, XmNlabelString,XmStr);\
XmStringFree (XmStr);\
set_something(label2, XmNbottomPosition, 10);\
\
set_something(textNomeBlocco, XmNtopPosition, 2);\
set_something(textNomeBlocco, XmNbottomPosition, 15);\
set_something(pushButton4, XmNtopPosition, 2);\
set_something(pushButton4, XmNbottomPosition, 15);\
\
set_something(label3, XmNtopPosition, 19);\
set_something(label3, XmNbottomPosition, 32);\
set_something(textNomeVariabile, XmNtopPosition, 19);\
set_something(textNomeVariabile, XmNbottomPosition, 32);\
set_something(pushButton5, XmNtopPosition, 19);\
set_something(pushButton5, XmNbottomPosition, 32);\
\
set_something(pushButton6, XmNtopPosition, 35);\
set_something(pushButton6, XmNbottomPosition, 48);\
set_something(textNomePerturbazione, XmNtopPosition, 35);\
set_something(textNomePerturbazione, XmNbottomPosition, 48);\
\
set_something(label8,XmNtopPosition, 54);\
set_something(label8,XmNbottomPosition, 60);\
set_something(label8,XmNleftPosition, 2);\
set_something(label8,XmNrightPosition,45);\
set_something(Elab,XmNtopPosition, 51);\
set_something(Elab,XmNbottomPosition,63);\
set_something(Elab,XmNleftPosition,45);\
set_something(Elab,XmNrightPosition,70);\
\
set_something(separator6,XmNtopPosition ,64);\
set_something(separator6,XmNbottomPosition, 67);\
\
set_something(pushButton13,XmNtopPosition,68);\
set_something(pushButton13,XmNbottomPosition,78);\
\
\
\
set_something(separator2,XmNtopPosition ,79);\
set_something(separator2,XmNbottomPosition, 83);\
\
set_something(pushButton7,XmNtopPosition ,85);\
set_something(pushButton7,XmNbottomPosition ,96);\
\
set_something(pushButton8,XmNtopPosition ,85);\
set_something(pushButton8,XmNbottomPosition ,96);\
\
 \
/*\
 Se la stringa di descrizione della variabile non e'\
 completa inserisce come modello SUPERV e come blocchi\
 ALL\
*/\
if (Giusto == False)\
  {\
   XtFree(NomeModello);\
   XtFree(NomeBlocco);\
   NomeModello=XtNewString("SUPERVIS");\
   NomeBlocco=XtNewString("ALL");\
   set_something (pushButton4, XmNsensitive, True);\
   set_something (pushButton5, XmNsensitive, True);\
   }\
#ifdef ON_MMI\
/*\
 Rende impossibile modificare il tipo di variabile\
*/\
set_something (pushButton3, XmNsensitive,False);\
set_something (pushButton4, XmNsensitive,False);\
#endif\
#endif\
/*  Setta i textField  */\
XmTextFieldSetString (textNomeModello,NomeModello);\
XmTextFieldSetString (textNomeBlocco,NomeBlocco);\
XmTextFieldSetString (textNomeVariabile,NomeVar);\
if ( (TipoVariabile==XlRVarDO) || (TipoVariabile==XlRVarAO) || \
	(TipoVariabile==XlRVarXO) )\
  XmTextFieldSetString (textNomePerturbazione,Perturba);\
if ( (TipoVariabile==XlRVarDA) )\
  {\
  XmTextFieldSetString (textNomePerturbazione," ");\
  uguali = strncmp (Perturba,"NOP",3);\
  if (uguali == 0)\
    {\
    get_something (Elab, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
    set_something (Elab, XmNmenuHistory, ListaB[0]);\
    }\
  uguali = strncmp (Perturba,"NOT",3);\
  if (uguali == 0)\
    {\
    get_something (Elab, XmNsubMenuId, &Pane);\
    get_something (Pane, XmNchildren, &ListaB);\
    set_something (Elab, XmNmenuHistory, ListaB[1]);\
    }\
  }\
\
/*  Setta la posizione dell'interfaccia secondo la posizione del Parent  */\
InterfaceSetPos (VariableEditor,Parent4);\
\
}
*VariableEditor.allowShellResize: "false"

*form2.class: form
*form2.static: true
*form2.name: form2
*form2.parent: VariableEditor
*form2.unitType: "pixels"
*form2.x: 0
*form2.y: 0
*form2.noResize: "false"
*form2.rightAttachment: "attach_self"
*form2.leftAttachment: "attach_self"
*form2.bottomAttachment: "attach_self"
*form2.topAttachment: "attach_self"
*form2.height: 550
*form2.width: 450

*labVarType.class: label
*labVarType.static: true
*labVarType.name: labVarType
*labVarType.parent: form2
*labVarType.x: 10
*labVarType.y: 10
*labVarType.width: 100
*labVarType.height: 20
*labVarType.labelString: "Variable type:"
*labVarType.leftAttachment: "attach_position"
*labVarType.leftOffset: 10
*labVarType.topAttachment: "attach_position"
*labVarType.topOffset: 0
*labVarType.topPosition: 2
*labVarType.bottomAttachment: "attach_position"
*labVarType.bottomPosition: 6
*labVarType.rightAttachment: "attach_position"
*labVarType.rightPosition: 25

*separator1.class: separator
*separator1.static: true
*separator1.name: separator1
*separator1.parent: form2
*separator1.x: 2
*separator1.y: 60
*separator1.width: 416
*separator1.height: 10
*separator1.leftAttachment: "attach_position"
*separator1.leftOffset: 0
*separator1.rightAttachment: "attach_position"
*separator1.topAttachment: "attach_position"
*separator1.topOffset: 0
*separator1.topWidget: ""
*separator1.rightOffset: 0
*separator1.bottomAttachment: "attach_position"
*separator1.topPosition: 21
*separator1.bottomPosition: 23
*separator1.leftPosition: 1
*separator1.rightPosition: 99

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: form2
*label1.x: 10
*label1.y: 80
*label1.width: 90
*label1.height: 40
*label1.labelString: "MODEL:"
*label1.alignment: "alignment_beginning"
*label1.topAttachment: "attach_position"
*label1.topOffset: 0
*label1.topWidget: ""
*label1.leftAttachment: "attach_position"
*label1.leftOffset: 0
*label1.leftPosition: 2
*label1.rightAttachment: "attach_position"
*label1.rightPosition: 22
*label1.topPosition: 24
*label1.bottomAttachment: "attach_position"
*label1.bottomPosition: 32

*pushButton3.class: pushButton
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.parent: form2
*pushButton3.x: 320
*pushButton3.y: 80
*pushButton3.width: 50
*pushButton3.height: 40
*pushButton3.labelString: "List.."
*pushButton3.sensitive: "true"
*pushButton3.activateCallback: {\
Widget Selezionato,*ListaWid;\
char *ListaModelli;\
char *p,*Appoggio,*NomeModello,*ListaAppoggio;\
int TipoOption,risul,NumeroBlocchi,NumeroModuli;\
XmString XmSel;\
char *Sel;\
char *ConfrontoAll="All";\
char *ConfrontoComponent="Component";\
char *ConfrontoSubSystem="Sub System";\
\
get_something (menu1, XmNmenuHistory, &Selezionato);\
get_something (Selezionato, XmNlabelString, &XmSel);\
Sel = (char *)extract_string (XmSel);\
\
risul = strcmp (ConfrontoSubSystem,Sel);\
if (risul == 0)\
	{\
	TipoOption = SUBSYSTEM;\
	get_something (labSubSystem, XmNlabelString, &XmSel);\
	Sel = (char *)extract_string (XmSel);\
	ListaModelli = (char *)OlGetModelFromSubSystem (Dbf,Sel);	\
	}\
else ListaModelli = (char *)OlElencoModelli (Dbf);\
\
ListaWid = (Widget *)XtCalloc ( 7,sizeof(Widget) );\
\
ListaWid[0] = (Widget )pushButton3;\
ListaWid[1] = (Widget )pushButton4;\
ListaWid[2] = (Widget )pushButton5;\
ListaWid[3] = (Widget )textNomeModello;\
ListaWid[4] = (Widget )textNomeBlocco;\
ListaWid[5] = (Widget )textNomeVariabile;\
ListaWid[6] = (Widget )NULL;\
\
UxPopupInterface (create_OneList(VariableEditor,ListaWid,MODELLI,ListaModelli),\
					no_grab);\
XtFree (ListaModelli);\
}
*pushButton3.leftAttachment: "attach_position"
*pushButton3.leftOffset: 0
*pushButton3.leftWidget: ""
*pushButton3.rightAttachment: "attach_position"
*pushButton3.rightOffset: 0
*pushButton3.topAttachment: "attach_position"
*pushButton3.topOffset: 0
*pushButton3.topWidget: ""
*pushButton3.leftPosition: 80
*pushButton3.rightPosition: 95
*pushButton3.topPosition: 24
*pushButton3.bottomAttachment: "attach_position"
*pushButton3.bottomPosition: 32

*separator2.class: separator
*separator2.static: true
*separator2.name: separator2
*separator2.parent: form2
*separator2.x: 2
*separator2.y: 280
*separator2.width: 406
*separator2.height: 10
*separator2.leftAttachment: "attach_position"
*separator2.leftOffset: 0
*separator2.rightAttachment: "attach_position"
*separator2.rightOffset: 0
*separator2.topAttachment: "attach_position"
*separator2.topOffset: 0
*separator2.bottomAttachment: "attach_position"
*separator2.bottomOffset: 0
*separator2.bottomPosition: 92
*separator2.topPosition: 90
*separator2.leftPosition: 1
*separator2.rightPosition: 99

*pushButton8.class: pushButton
*pushButton8.static: true
*pushButton8.name: pushButton8
*pushButton8.parent: form2
*pushButton8.x: 100
*pushButton8.y: 300
*pushButton8.width: 80
*pushButton8.height: 30
*pushButton8.labelString: "CANCEL"
*pushButton8.activateCallback: {\
#ifdef ON_MMI\
	XtDestroyWidget ( XtParent(VariableEditor) );\
#else\
	set_something (RowColInp[0], XmNsensitive, True);\
	set_something (RowColInp[2], XmNsensitive, True);\
	UxPopdownInterface (VariableEditor);\
#endif\
}
*pushButton8.bottomAttachment: "attach_position"
*pushButton8.bottomOffset: 0
*pushButton8.topAttachment: "attach_position"
*pushButton8.topOffset: 0
*pushButton8.topWidget: ""
*pushButton8.leftAttachment: "attach_position"
*pushButton8.leftOffset: 0
*pushButton8.bottomPosition: 99
*pushButton8.topPosition: 93
*pushButton8.leftPosition: 27
*pushButton8.rightAttachment: "attach_position"
*pushButton8.rightPosition: 47

*pushButton7.class: pushButton
*pushButton7.static: true
*pushButton7.name: pushButton7
*pushButton7.parent: form2
*pushButton7.x: 10
*pushButton7.y: 300
*pushButton7.width: 80
*pushButton7.height: 30
*pushButton7.labelString: "OK"
*pushButton7.bottomAttachment: "attach_position"
*pushButton7.bottomOffset: 0
*pushButton7.topAttachment: "attach_position"
*pushButton7.topOffset: 0
*pushButton7.topWidget: ""
*pushButton7.leftAttachment: "attach_position"
*pushButton7.leftOffset: 0
*pushButton7.rightAttachment: "attach_position"
*pushButton7.rightOffset: 0
*pushButton7.rightWidget: ""
*pushButton7.activateCallback: {\
int i;\
WidgetClass ClasseOggetto;\
char *modello,*blocco,*variabile,*perturba,*NomeClasse;\
char *Stringa,*Messaggio,Appoggio[20];\
char *Fittizia;\
\
modello = XmTextFieldGetString (textNomeModello);\
blocco = XmTextFieldGetString (textNomeBlocco);\
variabile = XmTextFieldGetString (textNomeVariabile);\
perturba = XmTextFieldGetString (textNomePerturbazione);\
\
if ( (TipoVariabile==XlRVarDA) || (TipoVariabile==XlRVarAA) || \
     (TipoVariabile==XlRVarXA) || (TipoVariabile==XlRVarXX) ||\
     (TipoVariabile==XlRVarAX) || (TipoVariabile==XlRVarDX) ||\
     (TipoVariabile==XlRVarAing) ||(TipoVariabile==XlRVarPlot) )\
  {\
  if ( (modello[0] == '\0')||(blocco[0] == '\0')||(variabile[0] == '\0') )\
	{\
	Messaggio = XtNewString ("Input was incomplete!");\
	VisualizzaMessageBox (GENERICA, VariableEditor, Messaggio,ListaDA);\
	XtFree (Messaggio);\
	}\
  else\
	{\
	Stringa = (char *)WriteInpVariableString (Dbf,modello,blocco,\
			variabile,Elab);\
	Stringa = (char *)WriteUniMisura (Stringa,Unit);\
\
#ifdef ON_MMI\
	ClasseOggetto = XtClass (ListaDA);\
	NomeClasse = XlGetClassName (ClasseOggetto);\
\
	if (strcmp(NomeClasse,"Grafico")==0)\
	  RisettaVariabile (Stringa,ListaDA);\
	else\
	  {\
	  XmTextFieldSetString (RowColInp[3], Stringa );\
	  if(TipoVariabile==XlRVarAing)\
          	ActivateVarAing (RowColInp);\
	  if(TipoVariabile==XlRVarPlot)\
          	ActivateVarPlot (RowColInp);\
	  }\
#else\
	XmTextFieldSetString (RowColInp[2], Stringa);\
	set_something (RowColInp[0], XmNsensitive, True);\
	set_something (RowColInp[2], XmNsensitive, True);\
#endif\
	XtFree (Stringa);\
	XtFree (modello);\
	XtFree (blocco);\
	XtFree (variabile);\
\
#ifdef ON_MMI\
	XtDestroyWidget ( XtParent (VariableEditor) );\
#else\
	UxPopdownInterface (VariableEditor);\
#endif\
	}\
  }\
\
if ( (TipoVariabile==XlRVarDO) || (TipoVariabile==XlRVarAO) || \
     (TipoVariabile==XlRVarXO) ) \
  {\
  if ( (modello[0] == '\0')||(blocco[0] == '\0')||(variabile[0] == '\0')||\
	(perturba[0] == '\0') )\
	{\
	Messaggio = XtNewString ("Input was incomplete!");\
	VisualizzaMessageBox (GENERICA, VariableEditor, Messaggio,VariableEditor);\
	XtFree (Messaggio);\
	}\
  else\
	{\
	Stringa = (char *)WriteOutVariableString (Dbf,modello,blocco,\
					variabile,perturba);\
	Stringa = (char *)WriteUniMisura (Stringa,Unit);\
\
	XmTextFieldSetString (RowColInp[2], Stringa);\
	set_something (RowColInp[0], XmNsensitive, True);\
	set_something (RowColInp[2], XmNsensitive, True);\
	XtFree (Stringa);\
	XtFree (modello);\
	XtFree (blocco);\
	XtFree (variabile);\
	XtFree (perturba);\
\
	UxPopdownInterface (VariableEditor);\
	}\
  }\
}
*pushButton7.bottomPosition: 99
*pushButton7.topPosition: 93
*pushButton7.leftPosition: 5
*pushButton7.rightPosition: 25

*menu1.class: rowColumn
*menu1.static: true
*menu1.name: menu1
*menu1.parent: form2
*menu1.rowColumnType: "menu_option"
*menu1.subMenuId: "OptMenu"
*menu1.x: 290
*menu1.y: 30
*menu1.leftAttachment: "attach_position"
*menu1.leftOffset: 0
*menu1.rightAttachment: "attach_position"
*menu1.rightOffset: 0
*menu1.leftPosition: 73
*menu1.rightPosition: 98
*menu1.topAttachment: "attach_position"
*menu1.topOffset: 0
*menu1.topPosition: 8
*menu1.bottomAttachment: "attach_position"
*menu1.bottomPosition: 14

*OptMenu.class: rowColumn
*OptMenu.static: true
*OptMenu.name: OptMenu
*OptMenu.parent: menu1
*OptMenu.rowColumnType: "menu_pulldown"

*AllItem.class: pushButton
*AllItem.static: true
*AllItem.name: AllItem
*AllItem.parent: OptMenu
*AllItem.labelString: "All"
*AllItem.activateCallback.source: public
*AllItem.activateCallback: 

*ComponentItem.class: pushButton
*ComponentItem.static: true
*ComponentItem.name: ComponentItem
*ComponentItem.parent: OptMenu
*ComponentItem.labelString: "Component"

*SubSystemItem.class: pushButton
*SubSystemItem.static: true
*SubSystemItem.name: SubSystemItem
*SubSystemItem.parent: OptMenu
*SubSystemItem.labelString: "Sub System"

*label4.class: label
*label4.static: true
*label4.name: label4
*label4.parent: form2
*label4.x: 300
*label4.y: 10
*label4.width: 90
*label4.height: 20
*label4.labelString: "Select from:"
*label4.topAttachment: "attach_position"
*label4.topOffset: 0
*label4.leftAttachment: "attach_position"
*label4.leftOffset: 0
*label4.rightAttachment: "attach_position"
*label4.rightOffset: 0
*label4.leftPosition: 73
*label4.rightPosition: 96
*label4.topPosition: 2
*label4.bottomAttachment: "attach_position"
*label4.bottomPosition: 6

*textNomeModello.class: textField
*textNomeModello.static: true
*textNomeModello.name: textNomeModello
*textNomeModello.parent: form2
*textNomeModello.x: 110
*textNomeModello.y: 80
*textNomeModello.width: 200
*textNomeModello.height: 40
*textNomeModello.maxLength: 200
*textNomeModello.sensitive: "true"
*textNomeModello.rightAttachment: "attach_position"
*textNomeModello.rightOffset: 0
*textNomeModello.rightWidget: ""
*textNomeModello.leftAttachment: "attach_position"
*textNomeModello.leftOffset: 0
*textNomeModello.columns: 100
*textNomeModello.editable: "false"
*textNomeModello.topAttachment: "attach_position"
*textNomeModello.topOffset: 0
*textNomeModello.topWidget: ""
*textNomeModello.cursorPositionVisible: "false"
*textNomeModello.leftPosition: 25
*textNomeModello.rightPosition: 77
*textNomeModello.topPosition: 24
*textNomeModello.bottomAttachment: "attach_position"
*textNomeModello.bottomPosition: 32

*textNomeBlocco.class: textField
*textNomeBlocco.static: true
*textNomeBlocco.name: textNomeBlocco
*textNomeBlocco.parent: form2
*textNomeBlocco.x: 110
*textNomeBlocco.y: 130
*textNomeBlocco.width: 200
*textNomeBlocco.height: 40
*textNomeBlocco.maxLength: 200
*textNomeBlocco.sensitive: "true"
*textNomeBlocco.rightAttachment: "attach_position"
*textNomeBlocco.rightOffset: 0
*textNomeBlocco.rightWidget: ""
*textNomeBlocco.leftAttachment: "attach_position"
*textNomeBlocco.leftOffset: 0
*textNomeBlocco.columns: 100
*textNomeBlocco.editable: "false"
*textNomeBlocco.topAttachment: "attach_position"
*textNomeBlocco.topOffset: 0
*textNomeBlocco.topWidget: ""
*textNomeBlocco.cursorPositionVisible: "false"
*textNomeBlocco.leftPosition: 25
*textNomeBlocco.rightPosition: 77
*textNomeBlocco.bottomAttachment: "attach_position"
*textNomeBlocco.bottomPosition: 42
*textNomeBlocco.topPosition: 34

*textNomeVariabile.class: textField
*textNomeVariabile.static: true
*textNomeVariabile.name: textNomeVariabile
*textNomeVariabile.parent: form2
*textNomeVariabile.x: 110
*textNomeVariabile.y: 180
*textNomeVariabile.width: 200
*textNomeVariabile.height: 40
*textNomeVariabile.maxLength: 200
*textNomeVariabile.sensitive: "true"
*textNomeVariabile.rightAttachment: "attach_position"
*textNomeVariabile.rightOffset: 0
*textNomeVariabile.rightWidget: ""
*textNomeVariabile.leftAttachment: "attach_position"
*textNomeVariabile.leftOffset: 0
*textNomeVariabile.columns: 100
*textNomeVariabile.editable: "false"
*textNomeVariabile.topAttachment: "attach_position"
*textNomeVariabile.topOffset: 0
*textNomeVariabile.topWidget: ""
*textNomeVariabile.valueChangedCallback: {\
char *NomeVar;\
\
NomeVar = XmTextFieldGetString (textNomeVariabile);\
ModificaOptionUnit (ListaBottoni,NomeVar[0],(char *)UniMisura);\
XtFree (NomeVar);\
}
*textNomeVariabile.cursorPositionVisible: "false"
*textNomeVariabile.leftPosition: 25
*textNomeVariabile.rightPosition: 77
*textNomeVariabile.bottomAttachment: "attach_position"
*textNomeVariabile.bottomPosition: 52
*textNomeVariabile.topPosition: 44

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: form2
*label2.x: 10
*label2.y: 130
*label2.width: 90
*label2.height: 40
*label2.labelString: "BLOCK:"
*label2.alignment: "alignment_beginning"
*label2.topAttachment: "attach_position"
*label2.topOffset: 0
*label2.topWidget: ""
*label2.leftAttachment: "attach_position"
*label2.leftOffset: 0
*label2.leftPosition: 2
*label2.rightAttachment: "attach_position"
*label2.rightPosition: 22
*label2.bottomAttachment: "attach_position"
*label2.bottomPosition: 42
*label2.topPosition: 34

*pushButton4.class: pushButton
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.parent: form2
*pushButton4.x: 320
*pushButton4.y: 130
*pushButton4.width: 50
*pushButton4.height: 40
*pushButton4.labelString: "List.."
*pushButton4.sensitive: "false"
*pushButton4.activateCallback: {\
Widget Selezionato,*ListaWid,Wdg;\
char *ListaBlocchi,*ListaModuli;\
char *p;\
char *Appoggio="ALL";\
char *ListaDaDistruggere,*NomeModello,*ListaAppoggio,*ListaModuliFilter;\
int TipoOption,NumeroBlocchi,NumeroModuli;\
XmString XmSel;\
char *Sel,*Sel2;\
char *ConfrontoAll="All";\
char *ConfrontoComponent="Component";\
char *ConfrontoSubSystem="Sub System";\
\
NomeModello = XmTextFieldGetString (textNomeModello);\
\
get_something (menu1, XmNmenuHistory, &Selezionato);\
get_something (Selezionato, XmNlabelString, &XmSel);\
Sel = (char *)extract_string (XmSel);\
\
if (strcmp (ConfrontoComponent,Sel) == 0)\
	{\
	TipoOption = COMPONENT;\
	get_something (labComponent, XmNlabelString, &XmSel);\
	Sel2 = (char *)extract_string (XmSel);\
	ListaModuli = (char *)OlElencoModuli (Dbf, NomeModello, Sel2);\
	ListaModuliFilter = (char *)OlGetModulFromComponent (Dbf,Sel2);\
	ListaModuli = (char *)FilterList (ListaModuli,ListaModuliFilter);\
	ListaBlocchi = (char *)OlElencoBlocchi (Dbf,NomeModello,NULL);\
	ListaBlocchi = (char *)BlocksFilterFromComponent (ListaBlocchi,\
						ListaModuli);\
	free (Sel2);\
	/*********************\
		Aggiunta alla lista moduli della voce "all"\
	*********************/\
	ListaDaDistruggere = ListaModuli;\
	memcpy (&NumeroModuli , ListaModuli, sizeof(int) );\
	NumeroModuli++;\
	ListaModuli += sizeof(int);\
	ListaAppoggio = (char *)XtCalloc ( sizeof(int)+(NumeroModuli*5),\
				sizeof(char) );\
	memcpy (ListaAppoggio, &NumeroModuli, sizeof(int) ); \
	p = ListaAppoggio;\
	p += sizeof(int);\
	strncpy (p, Appoggio, strlen(Appoggio));\
	p += 5;\
	memcpy (p, ListaModuli, (NumeroModuli-1)*5);\
	free (ListaDaDistruggere);\
	ListaModuli = ListaAppoggio;	 \
	}\
\
if (strcmp (ConfrontoSubSystem,Sel) == 0)\
	{\
	TipoOption = SUBSYSTEM;\
	get_something (labSubSystem, XmNlabelString, &XmSel);\
	Sel2 = (char *)extract_string (XmSel);\
	ListaBlocchi = (char *)OlGetBlocksFromSubSystem (Dbf,NomeModello,Sel2);\
	ListaModuli = NULL;\
	free (Sel2);\
	}\
\
if (strcmp (ConfrontoAll, Sel) == 0)\
	{\
	TipoOption = ALL;\
	ListaModuli = (char *)OlElencoModuli (Dbf, NomeModello, NULL);\
	ListaBlocchi = (char *)OlElencoBlocchi (Dbf, NomeModello, NULL);\
	/*********************\
		Aggiunta alla lista moduli della voce "all"\
	*********************/\
	ListaDaDistruggere = ListaModuli;\
	memcpy (&NumeroModuli , ListaModuli, sizeof(int) );\
	NumeroModuli++;\
	ListaModuli += sizeof(int);\
	ListaAppoggio = (char *)XtCalloc ( sizeof(int)+(NumeroModuli*5),\
				sizeof(char) );\
	memcpy (ListaAppoggio, &NumeroModuli, sizeof(int) ); \
	p = ListaAppoggio;\
	p += sizeof(int);\
	strncpy (p, Appoggio, strlen(Appoggio));\
	p += 5;\
	memcpy (p, ListaModuli, (NumeroModuli-1)*5);\
	free (ListaDaDistruggere);\
	ListaModuli = ListaAppoggio;	 \
	}\
\
/********************\
	Aggiunta alla lista blocchi della voce "all"  \
********************/\
ListaDaDistruggere = ListaBlocchi;\
memcpy (&NumeroBlocchi , ListaBlocchi, sizeof(int) );\
NumeroBlocchi++;\
ListaBlocchi += sizeof(int);\
ListaAppoggio = (char *)XtCalloc ( sizeof(int)+(NumeroBlocchi*\
				MAX_LUN_NOME_BLOCCO), sizeof(char) );\
memcpy (ListaAppoggio, &NumeroBlocchi, sizeof(int) ); \
p = ListaAppoggio;\
p += sizeof(int);\
memcpy (p, Appoggio, strlen(Appoggio));\
p += MAX_LUN_NOME_BLOCCO;\
memcpy (p, ListaBlocchi, (NumeroBlocchi-1)*MAX_LUN_NOME_BLOCCO);\
free (ListaDaDistruggere);\
ListaBlocchi = ListaAppoggio;	 \
\
ListaWid = (Widget *)XtCalloc ( 5,sizeof(Widget) );\
\
ListaWid[0] = (Widget )pushButton4;\
ListaWid[1] = (Widget )textNomeBlocco;\
ListaWid[2] = (Widget )textNomeVariabile;\
ListaWid[3] = (Widget )textNomeModello;\
ListaWid[4] = (Widget )NULL;\
\
UxPopupInterface (create_TwoList(VariableEditor,Dbf,ListaWid,ListaModuli,ListaBlocchi,\
						TipoOption,OggettoSelezionato),\
						no_grab);\
free (ListaModuli);\
free (ListaBlocchi);\
free (NomeModello);\
free (Sel);\
}
*pushButton4.leftAttachment: "attach_position"
*pushButton4.leftOffset: 0
*pushButton4.leftWidget: ""
*pushButton4.rightAttachment: "attach_position"
*pushButton4.rightOffset: 0
*pushButton4.topAttachment: "attach_position"
*pushButton4.topOffset: 0
*pushButton4.topWidget: ""
*pushButton4.leftPosition: 80
*pushButton4.rightPosition: 95
*pushButton4.bottomAttachment: "attach_position"
*pushButton4.bottomPosition: 42
*pushButton4.topPosition: 34

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: form2
*label3.x: 10
*label3.y: 180
*label3.width: 90
*label3.height: 40
*label3.labelString: "VARIABLE:"
*label3.alignment: "alignment_beginning"
*label3.topAttachment: "attach_position"
*label3.topOffset: 0
*label3.topWidget: ""
*label3.leftAttachment: "attach_position"
*label3.leftOffset: 0
*label3.leftPosition: 2
*label3.rightAttachment: "attach_position"
*label3.rightPosition: 22
*label3.bottomAttachment: "attach_position"
*label3.bottomPosition: 52
*label3.topPosition: 44

*pushButton5.class: pushButton
*pushButton5.static: true
*pushButton5.name: pushButton5
*pushButton5.parent: form2
*pushButton5.x: 320
*pushButton5.y: 180
*pushButton5.width: 50
*pushButton5.height: 40
*pushButton5.labelString: "List.."
*pushButton5.sensitive: "false"
*pushButton5.activateCallback: {\
int Indice,risul;\
Widget *ListaWid;\
char *ListaVariabili;\
char *BloccoAppoggio,*p,*PerVar,*Token;\
char *Confronto="ALL";\
char *NomeModello,*BloccoSel;\
char *Appoggio;\
\
ListaWid = (Widget *)XtCalloc ( 3,sizeof(Widget) );\
\
ListaWid[0] = (Widget )pushButton5;\
ListaWid[1] = (Widget )textNomeVariabile;\
ListaWid[2] = (Widget )NULL;\
\
NomeModello = (char *)XmTextFieldGetString (textNomeModello);\
\
BloccoSel = (char *)XmTextFieldGetString (textNomeBlocco);\
risul = strcmp (Confronto,BloccoSel);\
\
if ( risul == 0 )\
	{\
	ListaVariabili = (char *)OlElencoVariabili (Dbf,NomeModello,NULL,\
							TipoVariabile);\
	}\
else\
	{\
	BloccoAppoggio = XtNewString (BloccoSel);\
	Appoggio = BloccoAppoggio;\
	Token = strstr (BloccoAppoggio,"---->");\
\
	if (Token == NULL)\
		{\
		PerVar = (char *)XtCalloc (sizeof(int)+MAX_LUN_NOME_BLOCCO,\
							sizeof(char));\
		p = PerVar;\
		Indice = 1;\
		memcpy (p, &Indice, sizeof(int) );\
		p+= sizeof(int);\
		strncpy (p, BloccoSel,strlen (BloccoSel));\
		}\
	else\
		{\
		Token = strtok (BloccoAppoggio,"---->");\
		Token = strtok (NULL,"<----");\
		Token ++;\
		PerVar = (char *)OlElencoBlocchi (Dbf,NomeModello,Token);\
		}\
\
	ListaVariabili = (char *)OlElencoVariabili (Dbf,NomeModello,PerVar,\
							TipoVariabile);\
	XtFree (PerVar);\
	XtFree (Appoggio);\
	}\
\
UxPopupInterface (create_OneList(VariableEditor,ListaWid,VARIABILI,ListaVariabili),\
					no_grab);\
XtFree (NomeModello);\
XtFree (BloccoSel);\
XtFree (ListaVariabili);\
\
}
*pushButton5.leftAttachment: "attach_position"
*pushButton5.leftOffset: 0
*pushButton5.leftWidget: ""
*pushButton5.rightAttachment: "attach_position"
*pushButton5.rightOffset: 0
*pushButton5.topAttachment: "attach_position"
*pushButton5.topOffset: 0
*pushButton5.topWidget: ""
*pushButton5.leftPosition: 80
*pushButton5.rightPosition: 95
*pushButton5.bottomAttachment: "attach_position"
*pushButton5.bottomPosition: 52
*pushButton5.topPosition: 44

*pushButton6.class: pushButton
*pushButton6.static: true
*pushButton6.name: pushButton6
*pushButton6.parent: form2
*pushButton6.x: 10
*pushButton6.y: 230
*pushButton6.width: 90
*pushButton6.height: 40
*pushButton6.labelString: "PERTURB."
*pushButton6.sensitive: "true"
*pushButton6.activateCallback: {\
char *Stringa;\
\
Stringa = (char *)XmTextFieldGetString (textNomePerturbazione);\
\
UxPopupInterface (create_PerturbEditor(VariableEditor,Stringa,\
					textNomePerturbazione), no_grab);\
}
*pushButton6.topAttachment: "attach_position"
*pushButton6.topOffset: 0
*pushButton6.topWidget: ""
*pushButton6.recomputeSize: "false"
*pushButton6.leftAttachment: "attach_position"
*pushButton6.leftOffset: 0
*pushButton6.leftPosition: 2
*pushButton6.rightAttachment: "attach_position"
*pushButton6.rightPosition: 22
*pushButton6.bottomAttachment: "attach_position"
*pushButton6.bottomPosition: 62
*pushButton6.topPosition: 54

*textNomePerturbazione.class: textField
*textNomePerturbazione.static: true
*textNomePerturbazione.name: textNomePerturbazione
*textNomePerturbazione.parent: form2
*textNomePerturbazione.x: 110
*textNomePerturbazione.y: 230
*textNomePerturbazione.width: 200
*textNomePerturbazione.height: 40
*textNomePerturbazione.maxLength: 200
*textNomePerturbazione.sensitive: "true"
*textNomePerturbazione.rightAttachment: "attach_position"
*textNomePerturbazione.rightOffset: 0
*textNomePerturbazione.rightWidget: ""
*textNomePerturbazione.leftAttachment: "attach_position"
*textNomePerturbazione.leftOffset: 0
*textNomePerturbazione.columns: 100
*textNomePerturbazione.editable: "false"
*textNomePerturbazione.topAttachment: "attach_position"
*textNomePerturbazione.topOffset: 0
*textNomePerturbazione.topWidget: ""
*textNomePerturbazione.cursorPositionVisible: "false"
*textNomePerturbazione.leftPosition: 25
*textNomePerturbazione.rightPosition: 77
*textNomePerturbazione.bottomAttachment: "attach_position"
*textNomePerturbazione.bottomPosition: 62
*textNomePerturbazione.topPosition: 54

*separator8.class: separator
*separator8.static: true
*separator8.name: separator8
*separator8.parent: form2
*separator8.x: 280
*separator8.y: 10
*separator8.width: 10
*separator8.height: 90
*separator8.orientation: "vertical"
*separator8.bottomAttachment: "attach_position"
*separator8.bottomOffset: 0
*separator8.bottomWidget: ""
*separator8.topAttachment: "attach_position"
*separator8.topOffset: 0
*separator8.leftAttachment: "attach_position"
*separator8.leftOffset: 0
*separator8.leftWidget: ""
*separator8.rightAttachment: "attach_position"
*separator8.rightOffset: 0
*separator8.leftPosition: 67
*separator8.rightPosition: 70
*separator8.topPosition: 1
*separator8.bottomPosition: 20

*labComp.class: label
*labComp.static: true
*labComp.name: labComp
*labComp.parent: form2
*labComp.x: 10
*labComp.y: 40
*labComp.width: 100
*labComp.height: 20
*labComp.labelString: "Component:"
*labComp.leftAttachment: "attach_position"
*labComp.leftOffset: 10
*labComp.topAttachment: "attach_position"
*labComp.topOffset: 0
*labComp.topPosition: 8
*labComp.bottomAttachment: "attach_position"
*labComp.bottomPosition: 12
*labComp.rightAttachment: "attach_position"
*labComp.rightPosition: 25

*labSubS.class: label
*labSubS.static: true
*labSubS.name: labSubS
*labSubS.parent: form2
*labSubS.x: 10
*labSubS.y: 70
*labSubS.width: 100
*labSubS.height: 20
*labSubS.labelString: "Sub System:"
*labSubS.leftAttachment: "attach_position"
*labSubS.leftOffset: 10
*labSubS.topAttachment: "attach_position"
*labSubS.topOffset: 0
*labSubS.topPosition: 14
*labSubS.bottomAttachment: "attach_position"
*labSubS.bottomPosition: 18
*labSubS.rightAttachment: "attach_position"
*labSubS.rightPosition: 25

*label8.class: label
*label8.static: true
*label8.name: label8
*label8.parent: form2
*label8.x: 250
*label8.y: 320
*label8.width: 150
*label8.height: 20
*label8.labelString: "Input Variable Operation"
*label8.topAttachment: "attach_position"
*label8.topOffset: 0
*label8.topWidget: ""
*label8.bottomAttachment: "attach_position"
*label8.bottomPosition: 68
*label8.topPosition: 64
*label8.leftAttachment: "attach_position"
*label8.leftOffset: 0
*label8.leftPosition: 55
*label8.rightAttachment: "attach_position"
*label8.rightPosition: 97

*label9.class: label
*label9.static: true
*label9.name: label9
*label9.parent: form2
*label9.x: 40
*label9.y: 320
*label9.width: 150
*label9.height: 20
*label9.labelString: "Unit Variable"
*label9.topAttachment: "attach_position"
*label9.topOffset: 0
*label9.topWidget: ""
*label9.bottomAttachment: "attach_position"
*label9.bottomPosition: 68
*label9.topPosition: 64
*label9.leftAttachment: "attach_position"
*label9.leftOffset: 0
*label9.leftPosition: 10
*label9.rightAttachment: "attach_position"
*label9.rightPosition: 45

*labComponent.class: label
*labComponent.static: true
*labComponent.name: labComponent
*labComponent.parent: form2
*labComponent.x: 130
*labComponent.y: 40
*labComponent.width: 150
*labComponent.height: 20
*labComponent.alignment: "alignment_beginning"
*labComponent.labelString: ""
*labComponent.leftAttachment: "attach_position"
*labComponent.leftOffset: 5
*labComponent.leftWidget: ""
*labComponent.rightAttachment: "attach_position"
*labComponent.rightOffset: 5
*labComponent.rightWidget: ""
*labComponent.leftPosition: 25
*labComponent.rightPosition: 65
*labComponent.topAttachment: "attach_position"
*labComponent.topOffset: 0
*labComponent.topPosition: 8
*labComponent.bottomAttachment: "attach_position"
*labComponent.bottomPosition: 12

*labSubSystem.class: label
*labSubSystem.static: true
*labSubSystem.name: labSubSystem
*labSubSystem.parent: form2
*labSubSystem.x: 130
*labSubSystem.y: 70
*labSubSystem.width: 150
*labSubSystem.height: 20
*labSubSystem.alignment: "alignment_beginning"
*labSubSystem.labelString: ""
*labSubSystem.leftAttachment: "attach_position"
*labSubSystem.leftOffset: 5
*labSubSystem.leftWidget: ""
*labSubSystem.topAttachment: "attach_position"
*labSubSystem.topOffset: 0
*labSubSystem.rightAttachment: "attach_position"
*labSubSystem.rightOffset: 5
*labSubSystem.rightWidget: ""
*labSubSystem.leftPosition: 25
*labSubSystem.rightPosition: 65
*labSubSystem.topPosition: 14
*labSubSystem.bottomAttachment: "attach_position"
*labSubSystem.bottomPosition: 18

*labVariableType.class: label
*labVariableType.static: true
*labVariableType.name: labVariableType
*labVariableType.parent: form2
*labVariableType.x: 130
*labVariableType.y: 10
*labVariableType.width: 150
*labVariableType.height: 20
*labVariableType.alignment: "alignment_beginning"
*labVariableType.labelString: ""
*labVariableType.leftAttachment: "attach_position"
*labVariableType.leftOffset: 5
*labVariableType.leftWidget: ""
*labVariableType.topAttachment: "attach_position"
*labVariableType.topOffset: 0
*labVariableType.rightAttachment: "attach_position"
*labVariableType.rightOffset: 5
*labVariableType.rightWidget: ""
*labVariableType.leftPosition: 25
*labVariableType.rightPosition: 65
*labVariableType.topPosition: 2
*labVariableType.bottomAttachment: "attach_position"
*labVariableType.bottomPosition: 6

*Unit.class: rowColumn
*Unit.static: true
*Unit.name: Unit
*Unit.parent: form2
*Unit.rowColumnType: "menu_option"
*Unit.subMenuId: "UnitPane"
*Unit.x: 70
*Unit.y: 340
*Unit.topAttachment: "attach_position"
*Unit.topOffset: 0
*Unit.topWidget: ""
*Unit.bottomAttachment: "attach_position"
*Unit.bottomPosition: 76
*Unit.topPosition: 70
*Unit.leftAttachment: "attach_position"
*Unit.leftOffset: 0
*Unit.leftPosition: 13
*Unit.rightAttachment: "attach_position"
*Unit.rightPosition: 40

*UnitPane.class: rowColumn
*UnitPane.static: true
*UnitPane.name: UnitPane
*UnitPane.parent: Unit
*UnitPane.rowColumnType: "menu_pulldown"

*UnitItem.class: pushButton
*UnitItem.static: true
*UnitItem.name: UnitItem
*UnitItem.parent: UnitPane
*UnitItem.labelString: "Da Fare"

*separator6.class: separator
*separator6.static: true
*separator6.name: separator6
*separator6.parent: form2
*separator6.x: 2
*separator6.y: 370
*separator6.width: 428
*separator6.height: 30
*separator6.bottomAttachment: "attach_position"
*separator6.bottomOffset: 0
*separator6.leftAttachment: "attach_position"
*separator6.leftOffset: 0
*separator6.rightAttachment: "attach_position"
*separator6.rightOffset: 0
*separator6.topAttachment: "attach_position"
*separator6.topOffset: 0
*separator6.topWidget: ""
*separator6.bottomPosition: 80
*separator6.topPosition: 78
*separator6.leftPosition: 1
*separator6.rightPosition: 99

*pushButton13.class: pushButton
*pushButton13.static: true
*pushButton13.name: pushButton13
*pushButton13.parent: form2
*pushButton13.x: 20
*pushButton13.y: 320
*pushButton13.width: 370
*pushButton13.height: 40
*pushButton13.bottomAttachment: "attach_position"
*pushButton13.bottomOffset: 0
*pushButton13.bottomWidget: ""
*pushButton13.leftAttachment: "attach_position"
*pushButton13.leftOffset: 0
*pushButton13.rightAttachment: "attach_position"
*pushButton13.rightOffset: 0
*pushButton13.topAttachment: "attach_position"
*pushButton13.topOffset: 0
*pushButton13.topWidget: ""
*pushButton13.labelString: "GRAB SELECTED WIDGET"
*pushButton13.activateCallback: {\
char *Unita,*Comp,*Subs,*Stringa,*NomeMod,*NomeBl,*NomeVa,*Pert;\
Boolean IconaAnimata,Giusto;\
char Messaggio[100];\
Widget Odg,*ListaB,Pane;\
XmString XmStr;\
Arg arg[3];\
int uguali;\
\
char *Nulla='\0';\
\
Odg = (Widget )XlGetSelectedWidget (DrawA);\
if (Odg != NULL)\
  {\
  IconaAnimata = XlIsAnimateIcon (Odg) || XlIsIndic(Odg);\
/*\
 Se l'oggetto in selezione e' del tipo icona animata ricava \
 anche component e subsystem\
*/\
  if (XlIsAnimateIcon (Odg))\
    {\
    XtSetArg (arg[0], XlNcomponent, &Comp);\
    XtSetArg (arg[1], XlNsubsystem, &Subs);\
    XtGetValues (Odg, arg, 2);\
    XmStr = XmStringCreateSimple (Comp);\
    set_something (labComponent, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    XmStr = XmStringCreateSimple (Subs);\
    set_something (labSubSystem, XmNlabelString, XmStr);\
    XmStringFree (XmStr);\
    }\
/*\
 Se l'oggetto in selezione e' icona animata o indicatore\
 ricava il nome della variabile cambio colore\
*/\
  if(XlIsAnimateIcon (Odg) || XlIsIndic(Odg))\
    {\
    Stringa = (char *)XlGetFirstVcc (Odg);\
    if ( (Stringa == NULL) || (Stringa[0]=='\0') )\
      {\
      strcpy (Messaggio,"Variable not defined!");\
      VisualizzaMessageBox (GENERICA, VariableEditor,Messaggio,Odg);\
      }\
    else\
      {\
      Giusto = OlReadVariableString (Dbf,Stringa,&NomeMod,&NomeBl,&NomeVa,\
                                       &Pert,&UniMisura,TipoVariabile);\
      if (Giusto)\
        {\
	XmTextFieldSetString (textNomeModello,NomeMod);\
	XmTextFieldSetString (textNomeBlocco,NomeBl);\
	XmTextFieldSetString (textNomeVariabile,NomeVa);\
	if ( (TipoVariabile==XlRVarDO) || (TipoVariabile==XlRVarAO) || \
		(TipoVariabile==XlRVarXO) )\
	  XmTextFieldSetString (textNomePerturbazione,Pert);\
	if ( (TipoVariabile==XlRVarDA) )\
	  {\
	  XmTextFieldSetString (textNomePerturbazione,Nulla);\
	  uguali = strncmp (Pert,"NOP",3);\
	  if (uguali == 0)\
	    {\
	    get_something (Elab, XmNsubMenuId, &Pane);\
	    get_something (Pane, XmNchildren, &ListaB);\
	    set_something (Elab, XmNmenuHistory, ListaB[1]);\
	    }\
	  uguali = strncmp (Pert,"NOT",3);\
	  if (uguali == 0)\
	    {\
	    get_something (Elab, XmNsubMenuId, &Pane);\
	    get_something (Pane, XmNchildren, &ListaB);\
	    set_something (Elab, XmNmenuHistory, ListaB[0]);\
	    }\
	  }\
	set_something (pushButton4,XmNsensitive,True);\
	set_something (pushButton5,XmNsensitive,True);\
	}\
      else\
        {\
	strcpy (Messaggio,"Error in read variable");\
	VisualizzaMessageBox (GENERICA,VariableEditor,Messaggio,Odg); \
	}\
      }\
    }\
  else\
    {\
    strcpy (Messaggio,"Selected Widget must be AnimateIcon class!");\
    VisualizzaMessageBox (GENERICA,VariableEditor,Messaggio,Odg);\
    }\
  }\
else\
  {\
  strcpy (Messaggio,"Must be selected one object!");\
  VisualizzaMessageBox (GENERICA,VariableEditor,Messaggio,Odg);\
  }\
}
*pushButton13.bottomPosition: 88
*pushButton13.topPosition: 82
*pushButton13.leftPosition: 5
*pushButton13.rightPosition: 95

*Elab.class: rowColumn
*Elab.static: true
*Elab.name: Elab
*Elab.parent: form2
*Elab.rowColumnType: "menu_option"
*Elab.subMenuId: "ElabPane"
*Elab.x: 290
*Elab.y: 340
*Elab.topAttachment: "attach_position"
*Elab.topOffset: 0
*Elab.topWidget: ""
*Elab.bottomAttachment: "attach_position"
*Elab.bottomPosition: 76
*Elab.topPosition: 70
*Elab.leftAttachment: "attach_position"
*Elab.leftOffset: 0
*Elab.leftPosition: 60
*Elab.rightAttachment: "attach_position"
*Elab.rightPosition: 90

*ElabPane.class: rowColumn
*ElabPane.static: true
*ElabPane.name: ElabPane
*ElabPane.parent: Elab
*ElabPane.rowColumnType: "menu_pulldown"

*NOPItem.class: pushButton
*NOPItem.static: true
*NOPItem.name: NOPItem
*NOPItem.parent: ElabPane
*NOPItem.labelString: "NOP"

*NOTItem.class: pushButton
*NOTItem.static: true
*NOTItem.name: NOTItem
*NOTItem.parent: ElabPane
*NOTItem.labelString: "Not"

