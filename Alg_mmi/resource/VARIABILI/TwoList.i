! UIMX ascii 2.5 key: 5104                                                      

*TwoList.class: topLevelShell
*TwoList.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo TwoList.i\
   tipo \
   release 5.2\
   data 2/6/96\
   reserved @(#)TwoList.i	5.2\
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
#include <Ol/OlDatabaseTopologia.h>\
#include "VarEdit.h"\
#include "res_edit.h"\
#include "sim_param.h"\

*TwoList.ispecdecl: Widget *PadChiam,Oggetto2;\
OlDatabaseTopologiaObject Dbt;\
char *ListaDeiModuli,*ListaDeiBlocchi;\
int *PosBloc;\
int OptSel;
*TwoList.ispeclist: PadChiam, Oggetto2, Dbt, ListaDeiModuli, ListaDeiBlocchi, PosBloc, OptSel
*TwoList.ispeclist.PadChiam: "Widget", "*%PadChiam%"
*TwoList.ispeclist.Oggetto2: "Widget", "%Oggetto2%"
*TwoList.ispeclist.Dbt: "OlDatabaseTopologiaObject", "%Dbt%"
*TwoList.ispeclist.ListaDeiModuli: "unsigned char", "*%ListaDeiModuli%"
*TwoList.ispeclist.ListaDeiBlocchi: "unsigned char", "*%ListaDeiBlocchi%"
*TwoList.ispeclist.PosBloc: "int", "*%PosBloc%"
*TwoList.ispeclist.OptSel: "int", "%OptSel%"
*TwoList.funcdecl: swidget create_TwoList(Parent2,DbTop,PadInp,Moduli,Blocchi,Opzione,OggSel)\
OlDatabaseTopologiaObject DbTop;  /* Database della topologia */\
Widget Parent2;  /* Shell chiamante */\
Widget *PadInp;  /* Lista degli oggetti appartenente alla window di Variable\
                    Editor che devono essere modificati a seguito di\
                    selezione effettuata */\
Widget OggSel;   /* Oggetto selezionato nella drawing area */\
char *Moduli,*Blocchi; /* liste dei moduli e dei blocchi codificate con \
                           intero in testa */\
int Opzione;           /* specifica se deve essere disabilitata la gestione \
                          della lista dei moduli (caso di selezione da subsystem)\
                       */\

*TwoList.funcname: create_TwoList
*TwoList.funcdef: "swidget", "<create_TwoList>(%)"
*TwoList.argdecl: Widget Parent2;\
OlDatabaseTopologiaObject DbTop;\
Widget *PadInp;\
unsigned char *Moduli;\
unsigned char *Blocchi;\
int Opzione;\
Widget OggSel;
*TwoList.arglist: Parent2, DbTop, PadInp, Moduli, Blocchi, Opzione, OggSel
*TwoList.arglist.Parent2: "Widget", "%Parent2%"
*TwoList.arglist.DbTop: "OlDatabaseTopologiaObject", "%DbTop%"
*TwoList.arglist.PadInp: "Widget", "*%PadInp%"
*TwoList.arglist.Moduli: "unsigned char", "*%Moduli%"
*TwoList.arglist.Blocchi: "unsigned char", "*%Blocchi%"
*TwoList.arglist.Opzione: "int", "%Opzione%"
*TwoList.arglist.OggSel: "Widget", "%OggSel%"
*TwoList.icode: int Num;\
\
PadChiam = PadInp;\
ListaDeiModuli = Moduli;\
ListaDeiBlocchi = Blocchi;\
OptSel = Opzione;\
Dbt = DbTop;\
Oggetto2 = OggSel;\
\
set_something (PadChiam[0], XmNsensitive, False);
*TwoList.fcode: if (ListaDeiModuli == NULL)\
	{\
	set_something (scrolledList3, XmNsensitive, False);\
	set_something (pushButton16, XmNsensitive, False);\
	}\
else\
	CaricaLista (scrolledList3,ListaDeiModuli,5,GENERALE);\
\
CaricaLista (scrolledList2,ListaDeiBlocchi,MAX_LUN_NOME_BLOCCO,GENERALE);\
\
/*  Setta la posizione dell'interfaccia secondo il Parent  */\
InterfaceSetPos (TwoList,Parent2);\
\
return(rtrn);\

*TwoList.auxdecl:  
*TwoList.static: true
*TwoList.name: TwoList
*TwoList.parent: NO_PARENT
*TwoList.x: 95
*TwoList.y: 153
*TwoList.width: 460
*TwoList.height: 590
*TwoList.iconName: "Selection Window"

*form4.class: form
*form4.static: true
*form4.name: form4
*form4.parent: TwoList
*form4.resizePolicy: "resize_none"
*form4.unitType: "pixels"
*form4.x: 110
*form4.y: 220
*form4.width: 460
*form4.height: 590

*separator4.class: separator
*separator4.static: true
*separator4.name: separator4
*separator4.parent: form4
*separator4.x: 7
*separator4.y: 532
*separator4.width: 440
*separator4.height: 10
*separator4.bottomAttachment: "attach_position"
*separator4.bottomOffset: 0
*separator4.leftAttachment: "attach_position"
*separator4.leftOffset: 0
*separator4.rightAttachment: "attach_position"
*separator4.rightOffset: 0
*separator4.topAttachment: "attach_position"
*separator4.topOffset: 0
*separator4.bottomPosition: 92
*separator4.leftPosition: 1
*separator4.rightPosition: 99
*separator4.topPosition: 91

*pushButton11.class: pushButton
*pushButton11.static: true
*pushButton11.name: pushButton11
*pushButton11.parent: form4
*pushButton11.x: 25
*pushButton11.y: 552
*pushButton11.width: 80
*pushButton11.height: 30
*pushButton11.labelString: "OK"
*pushButton11.bottomAttachment: "attach_position"
*pushButton11.bottomOffset: 0
*pushButton11.leftAttachment: "attach_position"
*pushButton11.leftOffset: 0
*pushButton11.topAttachment: "attach_position"
*pushButton11.topOffset: 0
*pushButton11.topWidget: ""
*pushButton11.activateCallback: {\
Boolean selezione;\
int *ListaSel,NumSel,pos;\
char *NomeAppo,*DefVar,*NomeModello,NomeModulo[5],*Nome;\
XmString *ListaItem;\
\
selezione = XmListGetSelectedPos (scrolledList2,&ListaSel,&NumSel);\
get_something (scrolledList2, XmNitems, &ListaItem);\
\
if (selezione)\
	{\
	pos = ListaSel[0] - 1;\
	Nome = XtNewString ((char *)extract_string(ListaItem[pos]));\
	XmTextFieldSetString (PadChiam[1],Nome );\
	XmTextFieldSetString (PadChiam[2],"");\
	set_something (PadChiam[0], XmNsensitive, True);\
	if (pos != 0)\
	  {\
#ifndef ON_MMI\
	  if ( XlIsAnimateIcon (Oggetto2) )\
	    {\
	    NomeModello = XmTextFieldGetString (PadChiam[3]);\
	    NomeAppo = Nome;\
	    NomeAppo += 32;\
	    strncpy (NomeModulo,NomeAppo,4);\
	    DefVar = (char *)OlGetDefVarCC (Dbt,NomeModulo,Nome,NomeModello);\
	    if (DefVar)\
	      XmTextFieldSetString (PadChiam[2],DefVar);\
	    free (DefVar);\
	    free (NomeModello);\
	    free (Nome);\
            }\
#endif\
          }\
	}\
else\
	{\
	Nome = XtNewString ((char *)extract_string(ListaItem[0]));\
	XmTextFieldSetString (PadChiam[1],Nome);\
	XmTextFieldSetString (PadChiam[2],"");\
	set_something (PadChiam[0], XmNsensitive, True);\
	free (Nome);\
	}\
\
if (selezione)\
  free (ListaSel);\
free (PadChiam);\
XtDestroyWidget (TwoList);\
}
*pushButton11.bottomPosition: 98
*pushButton11.topPosition: 93
*pushButton11.leftPosition: 5
*pushButton11.rightAttachment: "attach_position"
*pushButton11.rightPosition: 25

*pushButton12.class: pushButton
*pushButton12.static: true
*pushButton12.name: pushButton12
*pushButton12.parent: form4
*pushButton12.x: 115
*pushButton12.y: 552
*pushButton12.width: 80
*pushButton12.height: 30
*pushButton12.labelString: "CANCEL"
*pushButton12.activateCallback: {\
set_something (PadChiam[0], XmNsensitive, True);\
free (PadChiam);\
XtDestroyWidget (TwoList);\
}
*pushButton12.bottomAttachment: "attach_position"
*pushButton12.bottomOffset: 0
*pushButton12.leftAttachment: "attach_position"
*pushButton12.leftOffset: 0
*pushButton12.leftWidget: ""
*pushButton12.topAttachment: "attach_position"
*pushButton12.topOffset: 0
*pushButton12.topWidget: ""
*pushButton12.bottomPosition: 98
*pushButton12.topPosition: 93
*pushButton12.leftPosition: 27
*pushButton12.rightAttachment: "attach_position"
*pushButton12.rightPosition: 47

*textField3.class: textField
*textField3.static: true
*textField3.name: textField3
*textField3.parent: form4
*textField3.x: 25
*textField3.y: 492
*textField3.width: 130
*textField3.height: 30
*textField3.maxLength: 80
*textField3.bottomAttachment: "attach_position"
*textField3.bottomOffset: 0
*textField3.bottomWidget: ""
*textField3.bottomPosition: 89
*textField3.leftAttachment: "attach_position"
*textField3.leftOffset: 0
*textField3.leftPosition: 4
*textField3.rightAttachment: "attach_position"
*textField3.rightPosition: 32
*textField3.topAttachment: "attach_position"
*textField3.topPosition: 83

*arrowButton3.class: arrowButton
*arrowButton3.static: true
*arrowButton3.name: arrowButton3
*arrowButton3.parent: form4
*arrowButton3.x: 155
*arrowButton3.y: 492
*arrowButton3.width: 30
*arrowButton3.height: 30
*arrowButton3.bottomAttachment: "attach_position"
*arrowButton3.bottomOffset: 0
*arrowButton3.bottomWidget: ""
*arrowButton3.activateCallback: {\
char *Ricerca,Messaggio[50];\
XmString XmRicerca,*XmRicercaList;\
int NumeroElementi,Posizione,*ListaSel,NumSel;\
Boolean Selezionato;\
\
Ricerca = XmTextFieldGetString (textField3);\
XmRicerca = XmStringCreateSimple (Ricerca);\
\
get_something (scrolledList2, XmNitems, &XmRicercaList);\
get_something (scrolledList2, XmNitemCount, &NumeroElementi);\
\
Selezionato = XmListGetSelectedPos (scrolledList2, &ListaSel, &NumSel);\
if (Selezionato)\
	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				SU,ListaSel[NumSel-1]);\
else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				SU,NumeroElementi+1);\
if (Posizione == 0)\
	{\
	strcpy (Messaggio,"String not found!\0");\
	VisualizzaMessageBox (GENERICA,TwoList,Messaggio,scrolledList2);\
	}\
else\
	{\
	XmListSelectPos (scrolledList2,Posizione,True);\
	XmListSetPos (scrolledList2,Posizione);\
	}\
}
*arrowButton3.bottomPosition: 89
*arrowButton3.leftAttachment: "attach_position"
*arrowButton3.leftOffset: 0
*arrowButton3.leftPosition: 34
*arrowButton3.rightAttachment: "attach_position"
*arrowButton3.rightPosition: 41
*arrowButton3.topAttachment: "attach_position"
*arrowButton3.topPosition: 83

*arrowButton4.class: arrowButton
*arrowButton4.static: true
*arrowButton4.name: arrowButton4
*arrowButton4.parent: form4
*arrowButton4.x: 185
*arrowButton4.y: 492
*arrowButton4.width: 30
*arrowButton4.height: 30
*arrowButton4.arrowDirection: "arrow_down"
*arrowButton4.bottomAttachment: "attach_position"
*arrowButton4.bottomOffset: 0
*arrowButton4.bottomWidget: ""
*arrowButton4.activateCallback: {\
char *Ricerca,Messaggio[50];\
XmString XmRicerca,*XmRicercaList;\
int NumeroElementi,Posizione,*ListaSel,NumSel;\
Boolean Selezionato;\
\
Ricerca = XmTextFieldGetString (textField3);\
XmRicerca = XmStringCreateSimple (Ricerca);\
\
get_something (scrolledList2, XmNitems, &XmRicercaList);\
get_something (scrolledList2, XmNitemCount, &NumeroElementi);\
\
Selezionato = XmListGetSelectedPos (scrolledList2, &ListaSel, &NumSel);\
if (Selezionato)\
	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				GIU,ListaSel[NumSel-1]);\
else 	Posizione = RicercaXmString (XmRicercaList,XmRicerca,NumeroElementi,\
				GIU,0);\
if (Posizione == 0)\
	{\
	strcpy (Messaggio,"String not found!\0");\
	VisualizzaMessageBox (GENERICA,TwoList,Messaggio,scrolledList2);\
	}\
else\
	{\
	XmListSelectPos (scrolledList2,Posizione,True);\
	XmListSetPos (scrolledList2,Posizione);\
	}\
}
*arrowButton4.bottomPosition: 89
*arrowButton4.leftAttachment: "attach_position"
*arrowButton4.leftOffset: 0
*arrowButton4.leftPosition: 42
*arrowButton4.rightAttachment: "attach_position"
*arrowButton4.rightPosition: 49
*arrowButton4.topAttachment: "attach_position"
*arrowButton4.topPosition: 83

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.parent: form4
*scrolledWindow3.scrollingPolicy: "application_defined"
*scrolledWindow3.x: 20
*scrolledWindow3.y: 50
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.leftAttachment: "attach_position"
*scrolledWindow3.leftOffset: 0
*scrolledWindow3.rightAttachment: "attach_position"
*scrolledWindow3.rightOffset: 0
*scrolledWindow3.bottomAttachment: "attach_position"
*scrolledWindow3.bottomPosition: 32
*scrolledWindow3.leftPosition: 5
*scrolledWindow3.rightPosition: 95
*scrolledWindow3.topAttachment: "attach_position"
*scrolledWindow3.topOffset: 0
*scrolledWindow3.topPosition: 8

*scrolledList3.class: scrolledList
*scrolledList3.static: true
*scrolledList3.name: scrolledList3
*scrolledList3.parent: scrolledWindow3
*scrolledList3.width: 410
*scrolledList3.height: 150
*scrolledList3.listSizePolicy: "resize_if_possible"

*separator5.class: separator
*separator5.static: true
*separator5.name: separator5
*separator5.parent: form4
*separator5.x: 10
*separator5.y: 210
*separator5.width: 420
*separator5.height: 10
*separator5.leftAttachment: "attach_position"
*separator5.leftOffset: 0
*separator5.rightAttachment: "attach_position"
*separator5.rightOffset: 0
*separator5.topAttachment: "attach_position"
*separator5.topOffset: 0
*separator5.topWidget: ""
*separator5.bottomAttachment: "attach_position"
*separator5.bottomPosition: 36
*separator5.leftPosition: 1
*separator5.rightPosition: 99
*separator5.topPosition: 34

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.parent: form4
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 25
*scrolledWindow2.y: 312
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.leftAttachment: "attach_position"
*scrolledWindow2.leftOffset: 0
*scrolledWindow2.rightAttachment: "attach_position"
*scrolledWindow2.rightOffset: 0
*scrolledWindow2.topAttachment: "attach_position"
*scrolledWindow2.topOffset: 0
*scrolledWindow2.topWidget: ""
*scrolledWindow2.bottomAttachment: "attach_position"
*scrolledWindow2.bottomOffset: 0
*scrolledWindow2.bottomWidget: ""
*scrolledWindow2.bottomPosition: 82
*scrolledWindow2.leftPosition: 5
*scrolledWindow2.rightPosition: 95
*scrolledWindow2.topPosition: 44

*scrolledList2.class: scrolledList
*scrolledList2.static: true
*scrolledList2.name: scrolledList2
*scrolledList2.parent: scrolledWindow2
*scrolledList2.width: 420
*scrolledList2.height: 170
*scrolledList2.listSizePolicy: "resize_if_possible"

*label5.class: label
*label5.static: true
*label5.name: label5
*label5.parent: form4
*label5.x: 20
*label5.y: 10
*label5.width: 120
*label5.height: 30
*label5.bottomAttachment: "attach_position"
*label5.bottomOffset: 0
*label5.bottomWidget: ""
*label5.leftAttachment: "attach_position"
*label5.leftOffset: 0
*label5.topAttachment: "attach_position"
*label5.topOffset: 0
*label5.labelString: "MODULES"
*label5.alignment: "alignment_beginning"
*label5.bottomPosition: 7
*label5.leftPosition: 5
*label5.rightAttachment: "attach_position"
*label5.rightPosition: 50
*label5.topPosition: 2

*label6.class: label
*label6.static: true
*label6.name: label6
*label6.parent: form4
*label6.x: 20
*label6.y: 230
*label6.width: 120
*label6.height: 30
*label6.labelString: "BLOCKS"
*label6.alignment: "alignment_beginning"
*label6.bottomAttachment: "attach_position"
*label6.bottomOffset: 0
*label6.bottomWidget: ""
*label6.leftAttachment: "attach_position"
*label6.leftOffset: 0
*label6.topAttachment: "attach_position"
*label6.topOffset: 0
*label6.topWidget: ""
*label6.leftPosition: 5
*label6.rightAttachment: "attach_position"
*label6.rightPosition: 50
*label6.bottomPosition: 43
*label6.topPosition: 37

*pushButton16.class: pushButton
*pushButton16.static: true
*pushButton16.name: pushButton16
*pushButton16.parent: form4
*pushButton16.x: 210
*pushButton16.y: 550
*pushButton16.width: 80
*pushButton16.height: 30
*pushButton16.labelString: "FILTER"
*pushButton16.bottomAttachment: "attach_position"
*pushButton16.bottomOffset: 0
*pushButton16.leftAttachment: "attach_position"
*pushButton16.leftOffset: 0
*pushButton16.leftWidget: ""
*pushButton16.topAttachment: "attach_position"
*pushButton16.topOffset: 0
*pushButton16.topWidget: ""
*pushButton16.activateCallback: {\
XmString *ListaXm;\
int pos,posiz,*ListaSel,NumSel,selezionato;\
char *ListaModuliFilter,*ListaBl,*Stringa;\
char *ListaDaDistruggere,*NomeMod;\
int NumeroBlocchi;\
char Appo[200],*Appoggio,*p,*ListaAppoggio;\
\
selezionato = 0;\
NomeMod = XmTextFieldGetString (PadChiam[3]);\
selezionato = XmListGetSelectedPos (scrolledList3, &ListaSel, &NumSel);\
get_something (scrolledList3, XmNitems, &ListaXm);\
\
if ( (selezionato==1) && (ListaSel[0] != 1) )\
  {\
  posiz = ListaSel[0]-1;\
  Stringa = (char *)extract_string (ListaXm[posiz]);\
\
  switch (OptSel)\
    {\
    case COMPONENT:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);\
    break;\
    case ALL:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);\
    break;\
    case SUBSYSTEM:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,Stringa);\
    break;\
    }\
  XtFree (Stringa);\
  }\
else\
  {\
  Stringa = (char *)extract_string (ListaXm[0]);\
  switch (OptSel)\
    {\
    case COMPONENT:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);\
      ListaModuliFilter = (char *)OlGetModulFromComponent (Dbt,Stringa);\
      ListaBl = (char *)BlocksFilterFromComponent (ListaBl,ListaModuliFilter);\
      XtFree (ListaModuliFilter);\
    break;\
    case ALL:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);\
    break;\
    case SUBSYSTEM:\
      ListaBl = (char *)OlElencoBlocchi (Dbt,NomeMod,NULL);\
    break;\
    }\
  XtFree (Stringa);\
  }\
XmListDeleteAllItems (scrolledList2);\
XtFree (ListaSel);\
\
/********************\
	Lettura dalla lista dei moduli della voce selezionata\
********************/\
selezionato = 0;\
selezionato = XmListGetSelectedPos (scrolledList3, &ListaSel, &NumSel); \
\
if ( (selezionato==0) || (ListaSel[0]==1) )\
	{\
	Appoggio = XtNewString ("-- ALL --");\
	}\
else\
	{\
	strcpy (Appo," ALL ---->");\
	get_something (scrolledList3, XmNitems, &ListaXm);\
	pos = ListaSel[0]-1;\
	Appoggio = XtNewString (extract_string (ListaXm[pos]) );\
	strcat (Appo,Appoggio);\
	strcat (Appo,"<----");\
	XtFree (Appoggio);\
	Appoggio = XtCalloc (strlen(Appo)+1,sizeof(char));\
	strcpy (Appoggio,Appo); \
	}\
\
/********************\
	Aggiunta alla lista blocchi della voce "all"  \
********************/\
ListaDaDistruggere = ListaBl;\
memcpy (&NumeroBlocchi , ListaBl, sizeof(int) );\
NumeroBlocchi++;\
\
ListaBl += sizeof(int);\
ListaAppoggio = (char *)XtCalloc ( sizeof(int)+(NumeroBlocchi*\
				MAX_LUN_NOME_BLOCCO), sizeof(char) );\
memcpy (ListaAppoggio, &NumeroBlocchi, sizeof(int) ); \
p = ListaAppoggio;\
p += sizeof(int);\
strcpy (p, Appoggio);\
p += MAX_LUN_NOME_BLOCCO;\
XtFree (Appoggio);\
memcpy (p, ListaBl, (NumeroBlocchi-1)*MAX_LUN_NOME_BLOCCO);\
\
XtFree (ListaDaDistruggere);\
\
ListaBl = ListaAppoggio;	 \
\
CaricaLista (scrolledList2,ListaBl,MAX_LUN_NOME_BLOCCO,GENERALE);\
XtFree (NomeMod);\
XtFree (ListaSel);\
}
*pushButton16.bottomPosition: 98
*pushButton16.topPosition: 93
*pushButton16.leftPosition: 49
*pushButton16.rightAttachment: "attach_position"
*pushButton16.rightPosition: 69

