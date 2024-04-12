! UIMX ascii 2.8 key: 7916                                                      

*listaScenari.class: formDialog
*listaScenari.classinc:
*listaScenari.classspec:
*listaScenari.classmembers:
*listaScenari.classconstructor:
*listaScenari.classdestructor:
*listaScenari.gbldecl: #include <stdio.h>\
#include <X11/Intrinsic.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "bistrutt.h"\
#include "messaggi.h"\
#include "tabelle_malf.h"\
#include "malfunzioni.h"\
SCENARI scenari_malf;\
SCENARI scenari_frem;\
#include "cursore.h"\
extern swidget create_scenarioMalf();\
#include "malfunzioni.h"\
extern int lista_scenari_malf_active;\
extern int lista_scenari_frem_active;\
Widget listaScenariMalf;\
Widget listaScenariFrem;\
int scenarioValido = 0;\
int leggiPertMalfAttivo = 0;		/* se > 0 il timer di lettura pert e' attivo */\
extern swidget masterMenu;\
extern int _MAX_PERTUR;\
TIPO_PERT *pertMalf;\
TIPO_PERT *pertMalfOld;\
XtIntervalId timer_leggiPertMalf;\
int nuovoScenarioMalf = 0;\
int nuovoScenarioFrem = 0;
*listaScenari.ispecdecl: int scenarioSelect;\
XtIntervalId timer_listaScenari;\

*listaScenari.ispeclist: scenarioSelect, timer_listaScenari
*listaScenari.ispeclist.scenarioSelect: "int", "%scenarioSelect%"
*listaScenari.ispeclist.timer_listaScenari: "XtIntervalId", "%timer_listaScenari%"
*listaScenari.funcdecl: swidget create_listaScenari(listaScenariParent, tipo)\
Widget listaScenariParent;\
int tipo;   /* malf o frem  */
*listaScenari.funcname: create_listaScenari
*listaScenari.funcdef: "swidget", "<create_listaScenari>(%)"
*listaScenari.argdecl: Widget listaScenariParent;\
int tipo;
*listaScenari.arglist: listaScenariParent, tipo
*listaScenari.arglist.listaScenariParent: "Widget", "%listaScenariParent%"
*listaScenari.arglist.tipo: "int", "%tipo%"
*listaScenari.icode: int numScen;   /* numero scenari validi */\

*listaScenari.fcode: timer_listaScenari = 0;\
#ifndef DESIGN_TIME\
if(readConfMalf (rtrn,tipo)>=0)\
   {\
   set_cursor (listaScenariParent,CLOCK);\
   /* attiva il ciclo di lettura delle pert attive (1 in tutto il sistema) */\
   attiva_timer_editPertMalf (masterMenu); \
   UxPopupInterface(rtrn,no_grab);\
   scenarioSelect = -1;\
   switch (tipo)\
      {\
      case MALFUNZIONI:\
      case SOMMARIO_MALF:       \
         listaScenariMalf = rtrn;\
         lista_scenari_malf_active = 1;\
         XtVaSetValues (XtParent(rtrn),\
                  XmNtitle, MALF_SCEN_LIST, XmNiconName, MALF_SCEN_LIST, NULL);\
         readScenari (listaScenariMalf, tipo, &scenari_malf);\
         displayScenari (rtrn, &scenari_malf);\
         break;\
      case FUNZIONI_REMOTE:\
      case SOMMARIO_FREM:\
         listaScenariFrem = rtrn;\
         lista_scenari_frem_active = 1;\
         XtVaSetValues (XtParent(rtrn),\
                  XmNtitle, FREM_SCEN_LIST, XmNiconName, FREM_SCEN_LIST, NULL);\
         XtVaSetValues (malfScenMenuSummarypb,\
                        RES_CONVERT(XmNlabelString,FREM_SUMMARY),NULL);\
         XtVaSetValues (mfScenPopupSummary,\
                        RES_CONVERT(XmNlabelString,FREM_SUMMARY),NULL);\
         readScenari (listaScenariMalf, tipo, &scenari_frem);\
         displayScenari (rtrn, &scenari_frem);\
         break;\
      }\
   gestioneTastiListaScenari (rtrn);     \
   attiva_timer_listaScenari (UxGetWidget(rtrn));\
   set_cursor (listaScenariParent,NORMALE);\
   }\
   else {\
      UxDestroyInterface(rtrn);\
      return(NULL);\
   }\
#endif\
\
return(rtrn);\

*listaScenari.auxdecl: int rimuoviScenario (int n,int t)\
{\
#ifndef DESIGN_TIME\
   deleteScenario (t, n-1);\
   salvaScenariMalf (UxGetWidget(listaScenari),t);\
   gestioneTastiListaScenari (listaScenari);\
   switch (t)\
      {\
      case MALFUNZIONI:\
      case SOMMARIO_MALF:\
         nuovoScenarioMalf = 1;\
         break;\
      case FUNZIONI_REMOTE:\
      case SOMMARIO_FREM:\
         nuovoScenarioFrem = 1;\
         break;\
      }\
\
#endif\
}\
/**************************************/\
int aggListaScenari (w, t)\
Widget w;\
int t;\
{\
SCENARI *s;\
\
   switch (t)\
      {\
      case MALFUNZIONI:\
      case SOMMARIO_MALF:\
         s = &scenari_malf;\
         if (nuovoScenarioMalf)\
            {\
            nuovoScenarioMalf = 0;\
            readScenari (listaScenariParent, t, s);\
            displayScenari (w, s);      \
            gestioneTastiListaScenari (w);\
            }\
            break;\
      case FUNZIONI_REMOTE:\
      case SOMMARIO_FREM:\
         s = &scenari_frem;\
         if (nuovoScenarioFrem)\
            {\
            nuovoScenarioFrem = 0;\
            readScenari (listaScenariParent, t, s);\
            displayScenari (w, s);      \
            gestioneTastiListaScenari (w);\
            }\
         break;\
      }\
}\
/**************************************/\
int deleteScenario (int t, int n)\
{\
SCENARI *s;\
   switch (t)\
      {\
      case MALFUNZIONI:\
      case SOMMARIO_MALF:\
         s = &scenari_malf;\
         break;\
      case FUNZIONI_REMOTE:\
      case SOMMARIO_FREM:\
         s = &scenari_frem;\
         break;\
      }\
   s->valido[n] = -1;\
   s->n --;\
   return (0);\
}\
/**************************************/\
int gestioneTastiListaScenari (Widget w)\
{\
   if (countScenariValidi (&scenari_malf) > MAX_SCENARI)\
      {\
      XtVaSetValues (malfScenMenuNewpb, XmNsensitive, False, NULL);\
      XtVaSetValues (mfScenPopupNew, XmNsensitive, False, NULL); \
      }\
   else\
      {\
      XtVaSetValues (malfScenMenuNewpb, XmNsensitive, True, NULL);\
      XtVaSetValues (mfScenPopupNew, XmNsensitive, True, NULL);  \
      }\
   return (0);\
}
*listaScenari.static: true
*listaScenari.name: listaScenari
*listaScenari.parent: NO_PARENT
*listaScenari.defaultShell: topLevelShell
*listaScenari.width: 400
*listaScenari.height: 340
*listaScenari.isCompound: "true"
*listaScenari.compoundIcon: "formD.xpm"
*listaScenari.compoundName: "form_Dialog"
*listaScenari.x: 670
*listaScenari.y: 490
*listaScenari.unitType: "pixels"
*listaScenari.destroyCallback: {\
switch (tipo)\
   {\
   case MALFUNZIONI:\
   case SOMMARIO_MALF:\
      lista_scenari_malf_active = 0;\
      stop_timer (timer_listaScenari);\
      remove_timer_editPertMalf ();\
      break;\
   case FUNZIONI_REMOTE:\
   case SOMMARIO_FREM:\
      lista_scenari_frem_active = 0;\
      stop_timer (timer_listaScenari);\
      remove_timer_editPertMalf ();\
      break;\
   }\
}
*listaScenari.defaultPosition: "false"

*menu2.class: rowColumn
*menu2.static: true
*menu2.name: menu2
*menu2.parent: listaScenari
*menu2.rowColumnType: "menu_bar"
*menu2.menuAccelerator: "<KeyUp>F10"
*menu2.rightAttachment: "attach_form"
*menu2.leftAttachment: "attach_form"
*menu2.menuHelpWidget: "menu2_top_b2"

*malfScenMenu.class: rowColumn
*malfScenMenu.static: true
*malfScenMenu.name: malfScenMenu
*malfScenMenu.parent: menu2
*malfScenMenu.rowColumnType: "menu_pulldown"

*malfScenMenuOpenpb.class: pushButton
*malfScenMenuOpenpb.static: true
*malfScenMenuOpenpb.name: malfScenMenuOpenpb
*malfScenMenuOpenpb.parent: malfScenMenu
*malfScenMenuOpenpb.labelString: "Open"
*malfScenMenuOpenpb.createManaged: "true"
*malfScenMenuOpenpb.activateCallback: {\
create_scenarioMalf (UxClientData, tipo, scenarioSelect);\
\
}
*malfScenMenuOpenpb.sensitive: "false"
*malfScenMenuOpenpb.activateCallbackClientData: UxGetWidget (listaScenari)

*malfScenMenuNewpb.class: pushButton
*malfScenMenuNewpb.static: true
*malfScenMenuNewpb.name: malfScenMenuNewpb
*malfScenMenuNewpb.parent: malfScenMenu
*malfScenMenuNewpb.labelString: "New    "
*malfScenMenuNewpb.activateCallback: {\
create_scenarioMalf (UxClientData, tipo, -1);\
}
*malfScenMenuNewpb.activateCallbackClientData: UxGetWidget (listaScenari)

*malfScenMenu_b2.class: separator
*malfScenMenu_b2.static: true
*malfScenMenu_b2.name: malfScenMenu_b2
*malfScenMenu_b2.parent: malfScenMenu

*malfScenMenuExitpb.class: pushButton
*malfScenMenuExitpb.static: true
*malfScenMenuExitpb.name: malfScenMenuExitpb
*malfScenMenuExitpb.parent: malfScenMenu
*malfScenMenuExitpb.labelString: "Quit"
*malfScenMenuExitpb.activateCallback: {\
#ifndef DESIGN_TIME\
uscita_listaScenari (listaScenari,tipo);\
#endif\
}

*menu2_p2.class: rowColumn
*menu2_p2.static: true
*menu2_p2.name: menu2_p2
*menu2_p2.parent: menu2
*menu2_p2.rowColumnType: "menu_pulldown"

*malfScenEditCutpb.class: pushButton
*malfScenEditCutpb.static: true
*malfScenEditCutpb.name: malfScenEditCutpb
*malfScenEditCutpb.parent: menu2_p2
*malfScenEditCutpb.labelString: "Cut   "
*malfScenEditCutpb.createManaged: "true"
*malfScenEditCutpb.activateCallback: {\
rimuoviScenario (scenarioSelect,tipo);\
\
}
*malfScenEditCutpb.sensitive: "false"

*menu2_p3.class: rowColumn
*menu2_p3.static: true
*menu2_p3.name: menu2_p3
*menu2_p3.parent: menu2
*menu2_p3.rowColumnType: "menu_pulldown"

*menu2_p3_b1.class: pushButton
*menu2_p3_b1.static: true
*menu2_p3_b1.name: menu2_p3_b1
*menu2_p3_b1.parent: menu2_p3
*menu2_p3_b1.labelString: "What"
*menu2_p3_b1.activateCallback.source: public
*menu2_p3_b1.activateCallback: 

*menu2_p4.class: rowColumn
*menu2_p4.static: true
*menu2_p4.name: menu2_p4
*menu2_p4.parent: menu2
*menu2_p4.rowColumnType: "menu_pulldown"

*malfScenMenuSummarypb.class: pushButton
*malfScenMenuSummarypb.static: true
*malfScenMenuSummarypb.name: malfScenMenuSummarypb
*malfScenMenuSummarypb.parent: menu2_p4
*malfScenMenuSummarypb.labelString: MALF_SUMMARY
*malfScenMenuSummarypb.activateCallback: {\
\
switch (tipo)\
   {\
   case MALFUNZIONI:\
   case SOMMARIO_MALF:\
	attiva_sommario (masterMenu,SOMMARIO_MALF);\
	break;\
   case FUNZIONI_REMOTE:\
   case SOMMARIO_FREM:\
	attiva_sommario (masterMenu,SOMMARIO_FREM);\
	break;\
   }\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.parent: menu2
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "malfScenMenu"

*menu2_top_b1.class: cascadeButton
*menu2_top_b1.static: true
*menu2_top_b1.name: menu2_top_b1
*menu2_top_b1.parent: menu2
*menu2_top_b1.labelString: "Edit"
*menu2_top_b1.subMenuId: "menu2_p2"

*menu2_top_b2.class: cascadeButton
*menu2_top_b2.static: true
*menu2_top_b2.name: menu2_top_b2
*menu2_top_b2.parent: menu2
*menu2_top_b2.labelString: "Help"
*menu2_top_b2.subMenuId: "menu2_p3"

*menu2_top_b3.class: cascadeButton
*menu2_top_b3.static: true
*menu2_top_b3.name: menu2_top_b3
*menu2_top_b3.parent: menu2
*menu2_top_b3.labelString: "Show"
*menu2_top_b3.subMenuId: "menu2_p4"

*form30.class: form
*form30.static: true
*form30.name: form30
*form30.parent: listaScenari
*form30.resizePolicy: "resize_none"
*form30.x: 5
*form30.y: 260
*form30.width: 855
*form30.height: 75
*form30.rightAttachment: "attach_form"
*form30.leftAttachment: "attach_form"
*form30.bottomAttachment: "attach_form"

*frame14.class: frame
*frame14.static: true
*frame14.name: frame14
*frame14.parent: form30
*frame14.x: 5
*frame14.y: 340
*frame14.width: 765
*frame14.height: 80
*frame14.bottomAttachment: "attach_form"
*frame14.leftOffset: 0
*frame14.rightAttachment: "attach_form"
*frame14.leftAttachment: "attach_form"
*frame14.topAttachment: "attach_form"

*form31.class: form
*form31.static: true
*form31.name: form31
*form31.parent: frame14
*form31.resizePolicy: "resize_none"
*form31.x: 0
*form31.y: 0
*form31.width: 745
*form31.height: 75

*scenariMalfQuitpb1.class: pushButton
*scenariMalfQuitpb1.static: true
*scenariMalfQuitpb1.name: scenariMalfQuitpb1
*scenariMalfQuitpb1.parent: form31
*scenariMalfQuitpb1.x: 240
*scenariMalfQuitpb1.y: 10
*scenariMalfQuitpb1.width: 130
*scenariMalfQuitpb1.height: 45
*scenariMalfQuitpb1.labelString: "QUIT"
*scenariMalfQuitpb1.activateCallback: {\
#ifndef DESIGN_TIME\
uscita_listaScenari (listaScenari,tipo);\
#endif\
}
*scenariMalfQuitpb1.bottomAttachment: "attach_form"
*scenariMalfQuitpb1.bottomOffset: 15
*scenariMalfQuitpb1.leftAttachment: "attach_position"
*scenariMalfQuitpb1.leftOffset: 0
*scenariMalfQuitpb1.rightAttachment: "attach_position"
*scenariMalfQuitpb1.rightOffset: 0
*scenariMalfQuitpb1.topAttachment: "attach_form"
*scenariMalfQuitpb1.topOffset: 15
*scenariMalfQuitpb1.rightPosition: 60
*scenariMalfQuitpb1.leftPosition: 40

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.parent: listaScenari
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.x: 20
*scrolledWindow5.y: 105
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0
*scrolledWindow5.height: 250
*scrolledWindow5.rightAttachment: "attach_form"
*scrolledWindow5.rightOffset: 20
*scrolledWindow5.leftAttachment: "attach_form"
*scrolledWindow5.leftOffset: 20
*scrolledWindow5.topOffset: 20
*scrolledWindow5.topAttachment: "attach_widget"
*scrolledWindow5.topWidget: "menu2"
*scrolledWindow5.bottomAttachment: "attach_widget"
*scrolledWindow5.bottomOffset: 20
*scrolledWindow5.bottomWidget: "form30"

*scrollListaScen.class: scrolledList
*scrollListaScen.static: true
*scrollListaScen.name: scrollListaScen
*scrollListaScen.parent: scrolledWindow5
*scrollListaScen.width: 660
*scrollListaScen.height: 300
*scrollListaScen.selectionPolicy: "single_select"
*scrollListaScen.visibleItemCount: 20
*scrollListaScen.singleSelectionCallback: {\
SCENARI *s;\
XmListCallbackStruct *reason;\
reason = (XmListCallbackStruct *)UxCallbackArg;\
scenarioSelect = reason->item_position;\
\
switch (tipo)\
   {\
   case MALFUNZIONI:\
      s = &scenari_malf;\
      break;\
   case FUNZIONI_REMOTE:\
      s = &scenari_frem;\
      break;\
   }\
if (s->valido[scenarioSelect-1] > 0)\
   {\
   XtVaSetValues (malfScenMenuOpenpb,XmNsensitive,True,NULL);\
   XtVaSetValues (malfScenEditCutpb,XmNsensitive,True,NULL);\
   XtVaSetValues (mfScenPopupOpen,XmNsensitive,True,NULL);\
   XtVaSetValues (mfScenPopupCut,XmNsensitive,True,NULL);\
   scenarioValido = 1;\
   }\
else\
   {\
   XtVaSetValues (malfScenMenuOpenpb,XmNsensitive,False,NULL);\
   XtVaSetValues (malfScenEditCutpb,XmNsensitive,False,NULL);\
   XtVaSetValues (mfScenPopupOpen,XmNsensitive,False,NULL);\
   XtVaSetValues (mfScenPopupCut,XmNsensitive,False,NULL);\
   scenarioValido = 0;\
   }\
}

*menu12.class: rowColumn
*menu12.static: true
*menu12.name: menu12
*menu12.parent: scrollListaScen
*menu12.rowColumnType: "menu_popup"
*menu12.menuAccelerator: "Shift <KeyUp>F10"

*mfScenPopupOpen.class: pushButton
*mfScenPopupOpen.static: true
*mfScenPopupOpen.name: mfScenPopupOpen
*mfScenPopupOpen.parent: menu12
*mfScenPopupOpen.labelString: "Open"
*mfScenPopupOpen.activateCallback: {\
create_scenarioMalf (UxClientData, tipo, scenarioSelect);\
}

*mfScenPopupNew.class: pushButton
*mfScenPopupNew.static: true
*mfScenPopupNew.name: mfScenPopupNew
*mfScenPopupNew.parent: menu12
*mfScenPopupNew.labelString: "New ..."
*mfScenPopupNew.activateCallback: {\
create_scenarioMalf (UxClientData, tipo, -1);\
}

*menu12_p1_b4.class: separator
*menu12_p1_b4.static: true
*menu12_p1_b4.name: menu12_p1_b4
*menu12_p1_b4.parent: menu12

*mfScenPopupCut.class: pushButton
*mfScenPopupCut.static: true
*mfScenPopupCut.name: mfScenPopupCut
*mfScenPopupCut.parent: menu12
*mfScenPopupCut.labelString: "Cut "
*mfScenPopupCut.activateCallback: {\
rimuoviScenario (scenarioSelect,tipo);\
}

*menu12_p1_b5.class: separator
*menu12_p1_b5.static: true
*menu12_p1_b5.name: menu12_p1_b5
*menu12_p1_b5.parent: menu12

*mfScenPopupSummary.class: pushButton
*mfScenPopupSummary.static: true
*mfScenPopupSummary.name: mfScenPopupSummary
*mfScenPopupSummary.parent: menu12
*mfScenPopupSummary.labelString: MALF_SUMMARY
*mfScenPopupSummary.activateCallback: {\
switch (tipo)\
   {\
   case MALFUNZIONI:\
   case SOMMARIO_MALF:\
	attiva_sommario (masterMenu,SOMMARIO_MALF);\
	break;\
   case FUNZIONI_REMOTE:\
   case SOMMARIO_FREM:\
	attiva_sommario (masterMenu,SOMMARIO_FREM);\
	break;\
   }\
\
\
}

*menu12_p1_b8.class: separator
*menu12_p1_b8.static: true
*menu12_p1_b8.name: menu12_p1_b8
*menu12_p1_b8.parent: menu12

*mfScenPopupQuit.class: pushButton
*mfScenPopupQuit.static: true
*mfScenPopupQuit.name: mfScenPopupQuit
*mfScenPopupQuit.parent: menu12
*mfScenPopupQuit.labelString: "Quit"
*mfScenPopupQuit.activateCallback: {\
#ifndef DESIGN_TIME\
   uscita_listaScenari (listaScenari,tipo);\
#endif\
}

