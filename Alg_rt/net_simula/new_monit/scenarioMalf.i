! UIMX ascii 2.8 key: 8482                                                      

*scenarioMalf.class: formDialog
*scenarioMalf.classinc:
*scenarioMalf.classspec:
*scenarioMalf.classmembers:
*scenarioMalf.classconstructor:
*scenarioMalf.classdestructor:
*scenarioMalf.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "bistrutt.h"\
#include "malfunzioni.h"\
#include "tabelle_malf.h"\
#include "file_selection.h"\
#include "messaggi.h"\
extern swidget create_selezMalf();\
extern swidget selezMalf;\
extern swidget create_malfConfig();\
extern swidget malfConfig;\
extern SCENARI scenari_malf;\
extern SCENARI scenari_frem;\
void openMalfConfig ();\
extern swidget masterMenu;\
swidget sommarioMalf;\
swidget sommarioFrem;\
extern int sommario_malf_active;\
extern int sommario_frem_active;\
\
extern M_COMP_TYPE *m_comp_type;\
extern MALF_SET *malf_set;\
extern M_COMPONENT *m_component;\
\
extern M_COMP_TYPE *fr_comp_type;\
extern MALF_SET *frem_set;\
extern M_COMPONENT *fr_component;
*scenarioMalf.ispecdecl: Widget scenMalfEntryForm[MAX_VAR_SCENARIO];\
Widget menu6_p2_shell[MAX_VAR_SCENARIO];\
Widget menu6_p2[MAX_VAR_SCENARIO];\
Widget scenMalfMenuTarget[MAX_MALF_SET_VALUE][MAX_VAR_SCENARIO];\
Widget menu6[MAX_VAR_SCENARIO];\
Widget scenMalfTb[MAX_VAR_SCENARIO];\
Widget scenMalfMainLabel[MAX_VAR_SCENARIO];\
Widget scenMalfTipoComp[MAX_VAR_SCENARIO];\
Widget scenMalfDescr[MAX_VAR_SCENARIO];\
Widget scenMalfValAtt[MAX_VAR_SCENARIO];\
Widget scenMalfMoreData[MAX_VAR_SCENARIO];\
Widget scenMalfConfig[MAX_VAR_SCENARIO];\
Widget scenMalfDelay[MAX_VAR_SCENARIO];\
Widget scenMalfDurata[MAX_VAR_SCENARIO];\
Widget scenMalfRampa[MAX_VAR_SCENARIO];\
int    scen_malf_select; /* riga selezionata */\
int    malf_select[MAX_VAR_SCENARIO];\
int    itemExpand[MAX_VAR_SCENARIO]; /* indice par callback tasto ... */\
int    col_sfondo_scenMalf;\
SCENARIO scenario;\
XtIntervalId timer_scenarioMalf;\
float tempo_old[MAX_VAR_SCENARIO];\
int primo_giro[MAX_VAR_SCENARIO];\
int moreDataAperto[MAX_VAR_SCENARIO]; /* flag more data gia' emesso */\
float valorePrec[MAX_VAR_SCENARIO];   /* valore precedente per evitare refresh */\
XtIntervalId timer_sommarioMalf;\
int nuovoSnapAggiornamento[MAX_VAR_SCENARIO];   /* aggiorn. var. sec. dopo load ci o bt */
*scenarioMalf.ispeclist: scenMalfEntryForm, menu6_p2_shell, menu6_p2, scenMalfMenuTarget, menu6, scenMalfTb, scenMalfMainLabel, scenMalfTipoComp, scenMalfDescr, scenMalfValAtt, scenMalfMoreData, scenMalfConfig, scenMalfDelay, scenMalfDurata, scenMalfRampa, scen_malf_select, malf_select, itemExpand, col_sfondo_scenMalf, scenario, timer_scenarioMalf, tempo_old, primo_giro, moreDataAperto, valorePrec, timer_sommarioMalf, nuovoSnapAggiornamento
*scenarioMalf.ispeclist.scenMalfEntryForm: "Widget", "%scenMalfEntryForm%[30]"
*scenarioMalf.ispeclist.menu6_p2_shell: "Widget", "%menu6_p2_shell%[30]"
*scenarioMalf.ispeclist.menu6_p2: "Widget", "%menu6_p2%[30]"
*scenarioMalf.ispeclist.scenMalfMenuTarget: "Widget", "%scenMalfMenuTarget%[10][30]"
*scenarioMalf.ispeclist.menu6: "Widget", "%menu6%[30]"
*scenarioMalf.ispeclist.scenMalfTb: "Widget", "%scenMalfTb%[30]"
*scenarioMalf.ispeclist.scenMalfMainLabel: "Widget", "%scenMalfMainLabel%[30]"
*scenarioMalf.ispeclist.scenMalfTipoComp: "Widget", "%scenMalfTipoComp%[30]"
*scenarioMalf.ispeclist.scenMalfDescr: "Widget", "%scenMalfDescr%[30]"
*scenarioMalf.ispeclist.scenMalfValAtt: "Widget", "%scenMalfValAtt%[30]"
*scenarioMalf.ispeclist.scenMalfMoreData: "Widget", "%scenMalfMoreData%[30]"
*scenarioMalf.ispeclist.scenMalfConfig: "Widget", "%scenMalfConfig%[30]"
*scenarioMalf.ispeclist.scenMalfDelay: "Widget", "%scenMalfDelay%[30]"
*scenarioMalf.ispeclist.scenMalfDurata: "Widget", "%scenMalfDurata%[30]"
*scenarioMalf.ispeclist.scenMalfRampa: "Widget", "%scenMalfRampa%[30]"
*scenarioMalf.ispeclist.scen_malf_select: "int", "%scen_malf_select%"
*scenarioMalf.ispeclist.malf_select: "int", "%malf_select%[30]"
*scenarioMalf.ispeclist.itemExpand: "int", "%itemExpand%[30]"
*scenarioMalf.ispeclist.col_sfondo_scenMalf: "int", "%col_sfondo_scenMalf%"
*scenarioMalf.ispeclist.scenario: "SCENARIO", "%scenario%"
*scenarioMalf.ispeclist.timer_scenarioMalf: "XtIntervalId", "%timer_scenarioMalf%"
*scenarioMalf.ispeclist.tempo_old: "float", "%tempo_old%[30]"
*scenarioMalf.ispeclist.primo_giro: "int", "%primo_giro%[30]"
*scenarioMalf.ispeclist.moreDataAperto: "int", "%moreDataAperto%[30]"
*scenarioMalf.ispeclist.valorePrec: "float", "%valorePrec%[30]"
*scenarioMalf.ispeclist.timer_sommarioMalf: "XtIntervalId", "%timer_sommarioMalf%"
*scenarioMalf.ispeclist.nuovoSnapAggiornamento: "int", "%nuovoSnapAggiornamento%[30]"
*scenarioMalf.funcdecl: swidget create_scenarioMalf  (Widget Parent,int tipo,int num_scen)\
/* num_scen indice di selezione in lista (da 1 a ...) */
*scenarioMalf.funcname: create_scenarioMalf
*scenarioMalf.funcdef: "swidget", "<create_scenarioMalf>(%)"
*scenarioMalf.argdecl: Widget Parent;\
int tipo;\
int num_scen;
*scenarioMalf.arglist: Parent, tipo, num_scen
*scenarioMalf.arglist.Parent: "Widget", "%Parent%"
*scenarioMalf.arglist.tipo: "int", "%tipo%"
*scenarioMalf.arglist.num_scen: "int", "%num_scen%"
*scenarioMalf.icode: int i;\
for (i=0; i<MAX_VAR_SCENARIO; i++)\
   {\
   moreDataAperto[i] = 0;\
   primo_giro[i] = 1;\
   valorePrec[i] = -999.999;\
   nuovoSnapAggiornamento[i] = 0;\
   }\

*scenarioMalf.fcode: if(readConfMalf (rtrn,tipo) >= 0)\
   {\
   attiva_timer_editPertMalf (masterMenu);\
   col_sfondo_scenMalf = read_background_color(rtrn); \
   switch (tipo)\
     {\
     case MALFUNZIONI:\
printf ("MALF: num_scen = %d\n",num_scen);\
        scen_malf_select = -1; /* selezione da lista: no valid preset */\
        clearScenario (&scenario);\
/*      update_title (rtrn,NEW_MALF_SCEN); */\
        if ((num_scen > 0) && (scenari_malf.valido[num_scen-1] > 0)) \
           {\
           caricaScenario (rtrn, &scenari_malf, &scenario, tipo, num_scen);\
           displayScenario (rtrn, &scenario,m_component,\
                      malf_set, m_comp_type);\
           update_title (rtrn,scenari_malf.s[num_scen-1].scen_header.commento);\
           }\
        break;\
      case SOMMARIO_MALF:\
printf ("Richiesta SOMMARIO MALF\n");\
         sommarioMalf = rtrn;\
         sommario_malf_active = 1;\
         scen_malf_select = -1; /* selezione da lista: no valid preset */\
         clearScenario (&scenario);\
         caricaScenario (rtrn, &scenari_malf, &scenario, tipo, num_scen);\
         displayScenario (rtrn, &scenario,m_component,\
                      malf_set, m_comp_type);\
         updateInterfaceFunctions (tipo); /* rimuove tasti non utilizzabili con sommario */\
         update_title (rtrn,MALF_LIST); \
         attiva_timer_sommarioMalf (rtrn);\
         break;\
     case FUNZIONI_REMOTE:\
printf ("FREM: num_scen = %d\n",num_scen);\
        scen_malf_select = -1; /* selezione da lista: no valid preset */\
        clearScenario (&scenario);\
/*      update_title (rtrn,NEW_FREM_SCEN); */\
        if ((num_scen > 0) && (scenari_frem.valido[num_scen-1] > 0)) \
           {\
           caricaScenario (rtrn, &scenari_frem, &scenario, tipo, num_scen);\
           displayScenario (rtrn, &scenario,fr_component,\
                      frem_set, fr_comp_type);\
           update_title (rtrn,scenari_frem.s[num_scen-1].scen_header.commento);\
           }\
        XtVaSetValues (scenMalfMenuShowSummaryMalf,\
                           RES_CONVERT(XmNlabelString,FREM_SUMMARY),NULL);\
        XtVaSetValues (scenMfPopupSummary,\
                           RES_CONVERT(XmNlabelString,FREM_SUMMARY),NULL);\
        break;\
      case SOMMARIO_FREM:\
printf ("Richiesta SOMMARIO FREM\n");\
         sommarioFrem = rtrn;\
         sommario_frem_active = 1;\
         scen_malf_select = -1; /* selezione da lista: no valid preset */\
         clearScenario (&scenario);\
         caricaScenario (rtrn, &scenari_frem, &scenario, tipo, num_scen);\
         displayScenario (rtrn, &scenario,fr_component,\
                      frem_set, fr_comp_type);\
         updateInterfaceFunctions (tipo); /* rimuove tasti non utilizzabili con sommario */\
         update_title (rtrn,FREM_LIST); \
         attiva_timer_sommarioMalf (rtrn);\
         break;\
      }\
   attiva_timer_scenarioMalf (rtrn);\
   UxPopupInterface (rtrn, no_grab);\
   }\
return(rtrn);\

*scenarioMalf.auxdecl: int gestioneTastiScenarioMalf (Widget w)\
{\
SCENARI *s;\
   switch (tipo)\
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
   if (countScenariValidi (s) >= MAX_SCENARI)\
      {\
      XtVaSetValues (scenMalfMenuFileSaveDef, XmNsensitive, False, NULL);\
      XtVaSetValues (scenMfPopupSave, XmNsensitive, False, NULL);\
      }\
   else\
      {\
      XtVaSetValues (scenMalfMenuFileSaveDef, XmNsensitive, True, NULL);\
      XtVaSetValues (scenMfPopupSave, XmNsensitive, True, NULL);\
      }\
   return (0);\
}\
/*********************************************/\
int clearScenario (SCENARIO *s)\
{\
int i;\
s->scen_header.numvar = 0;\
strcpy (s->scen_header.commento,"ENTER COMMENT");\
for (i=0; i<MAX_VAR_SCENARIO; i++)\
   {\
   s->rec[i].valido = -1;\
   s->rec[i].non_configurata = 0;\
   }\
return (0);\
}\
/*********************************************/\
/************************\
void openMalfConfig (w, data, reason)\
Widget w;\
char *data;\
XmPushButtonCallbackStruct *reason;\
{\
int n;\
_UxCscenarioMalf *Ctx;\
   Ctx = (_UxCscenarioMalf *)UxGetWidget (w);\
   memcpy (&n, data, sizeof(int));\
#ifndef DESIGN_TIME\
   if (Ctx->UxmoreDataAperto[n] == 0)\
      {\
      create_malfConfig (Ctx->UxscenarioMalf,n,tipo);\
      Ctx->UxmoreDataAperto[n] = 1;\
      }\
#endif\
}\
*****************************/\
/*********************************************/\
int updateInterfaceFunctions (int t)\
{\
   switch (t)\
      {\
      case MALFUNZIONI:\
      case FUNZIONI_REMOTE:\
         break;\
      case SOMMARIO_MALF:\
      case SOMMARIO_FREM:\
/* elimina i tasti dal popup */\
         XtUnmanageChild (scenMfPopupSave);\
         XtUnmanageChild (scenMalfRcPopupAdd);\
         XtUnmanageChild (scenMalfPopupDel);\
         XtUnmanageChild (scenMfPopupSep1);\
         XtUnmanageChild (scenMfPopupSep2);\
         XtUnmanageChild (scenMfPopupSummary);\
/* elimina i tast1 di attivazione   */\
/**         XtUnmanageChild (actMalfScenpb);\
         XtUnmanageChild (deactMalfScenpb);\
         XtManageChild (deactMalfScenSommpb);**/\
/* elimina i tasti del menu edit */\
         XtUnmanageChild (malfMenu_top_Edit);\
         XtUnmanageChild (scenMalfMenuEdit);\
/* elimina i tasti del menu Show */\
         XtUnmanageChild (malfMenu_top_Show);\
         XtUnmanageChild (scenMalfMenuShow);\
/* elimina i tasti dal menu File */\
         XtUnmanageChild (scenMalfMenuFileSaveDef);\
         XtUnmanageChild (scenMalfMenuFileSep1);\
         break;\
      }\
}\
/***************************************************/\
int uscita_scenarioMalf ()\
{\
DistruggiInterfaccia (XtParent(scenarioMalf));\
}
*scenarioMalf.static: true
*scenarioMalf.name: scenarioMalf
*scenarioMalf.parent: NO_PARENT
*scenarioMalf.defaultShell: topLevelShell
*scenarioMalf.width: 750
*scenarioMalf.height: 390
*scenarioMalf.isCompound: "true"
*scenarioMalf.compoundIcon: "formD.xpm"
*scenarioMalf.compoundName: "form_Dialog"
*scenarioMalf.x: 360
*scenarioMalf.y: 470
*scenarioMalf.unitType: "pixels"
*scenarioMalf.focusCallback: {\
/*printf ("valutazione tasti nscen Focus = %d\n",num_scen);*/\
if (num_scen < 0) \
   gestioneTastiScenarioMalf (UxWidget);\
}
*scenarioMalf.destroyCallback: {\
if (tipo == SOMMARIO_MALF)\
   {\
   stop_timer (timer_sommarioMalf);\
   sommario_malf_active = 0;\
   }\
else if (tipo == SOMMARIO_FREM)\
   {\
   stop_timer (timer_sommarioMalf);\
   sommario_frem_active = 0;\
   }\
stop_timer (timer_scenarioMalf);\
remove_timer_editPertMalf();\
}
*scenarioMalf.defaultPosition: "false"

*scenMalfMenu.class: rowColumn
*scenMalfMenu.static: true
*scenMalfMenu.name: scenMalfMenu
*scenMalfMenu.parent: scenarioMalf
*scenMalfMenu.rowColumnType: "menu_bar"
*scenMalfMenu.menuAccelerator: "<KeyUp>F10"
*scenMalfMenu.packing: "pack_tight"
*scenMalfMenu.menuHelpWidget: "malfMenu_top_b3"
*scenMalfMenu.createManaged: "true"
*scenMalfMenu.rightAttachment: "attach_form"
*scenMalfMenu.leftAttachment: "attach_form"

*scenMalfMenuFile1.class: rowColumn
*scenMalfMenuFile1.static: true
*scenMalfMenuFile1.name: scenMalfMenuFile1
*scenMalfMenuFile1.parent: scenMalfMenu
*scenMalfMenuFile1.rowColumnType: "menu_pulldown"

*scenMalfMenuFileSaveDef.class: pushButton
*scenMalfMenuFileSaveDef.static: true
*scenMalfMenuFileSaveDef.name: scenMalfMenuFileSaveDef
*scenMalfMenuFileSaveDef.parent: scenMalfMenuFile1
*scenMalfMenuFileSaveDef.labelString: SaveMenuLabel
*scenMalfMenuFileSaveDef.activateCallback: {\
#ifndef DESIGN_TIME\
save_scenmalf (scenarioMalf,tipo,num_scen);\
nuovoScenarioNotify (scenarioMalf,Parent);\
#endif\
}
*scenMalfMenuFileSaveDef.createCallback: {\
\
}

*scenMalfMenuFileSep1.class: separator
*scenMalfMenuFileSep1.static: true
*scenMalfMenuFileSep1.name: scenMalfMenuFileSep1
*scenMalfMenuFileSep1.parent: scenMalfMenuFile1

*scenMalfMenuFileQuitpb.class: pushButton
*scenMalfMenuFileQuitpb.static: true
*scenMalfMenuFileQuitpb.name: scenMalfMenuFileQuitpb
*scenMalfMenuFileQuitpb.parent: scenMalfMenuFile1
*scenMalfMenuFileQuitpb.labelString: QuitMenuLabel
*scenMalfMenuFileQuitpb.activateCallback: {\
uscita_scenarioMalf ();\
}
*scenMalfMenuFileQuitpb.activateCallbackClientData: (XtPointer) 0x0

*scenMalfMenuEdit.class: rowColumn
*scenMalfMenuEdit.static: true
*scenMalfMenuEdit.name: scenMalfMenuEdit
*scenMalfMenuEdit.parent: scenMalfMenu
*scenMalfMenuEdit.rowColumnType: "menu_pulldown"

*scenMalfEditAdd.class: pushButton
*scenMalfEditAdd.static: true
*scenMalfEditAdd.name: scenMalfEditAdd
*scenMalfEditAdd.parent: scenMalfMenuEdit
*scenMalfEditAdd.labelString: AddItemLabel
*scenMalfEditAdd.activateCallback: {\
#ifndef DESIGN_TIME\
/**\
create_selezMalf (UxGetWidget(scenarioMalf),&scenario,tipo); **/\
create_selVar (UxGetWidget(scenarioMalf),\
                &scenario,tipo,\
                scenari_malf.s[num_scen-1].scen_header.commento); \
#endif\
}

*scenMalfMenuEdit_b3.class: separator
*scenMalfMenuEdit_b3.static: true
*scenMalfMenuEdit_b3.name: scenMalfMenuEdit_b3
*scenMalfMenuEdit_b3.parent: scenMalfMenuEdit

*scenMalfEditDel.class: pushButton
*scenMalfEditDel.static: true
*scenMalfEditDel.name: scenMalfEditDel
*scenMalfEditDel.parent: scenMalfMenuEdit
*scenMalfEditDel.labelString: CutMenuLabel
*scenMalfEditDel.activateCallback: {\
delete_item_scen_malf (UxWidget);\
\
}
*scenMalfEditDel.sensitive: "false"

*scenMalfMenuHelp.class: rowColumn
*scenMalfMenuHelp.static: true
*scenMalfMenuHelp.name: scenMalfMenuHelp
*scenMalfMenuHelp.parent: scenMalfMenu
*scenMalfMenuHelp.rowColumnType: "menu_pulldown"

*scenMalfMenuHelppb.class: pushButton
*scenMalfMenuHelppb.static: true
*scenMalfMenuHelppb.name: scenMalfMenuHelppb
*scenMalfMenuHelppb.parent: scenMalfMenuHelp
*scenMalfMenuHelppb.labelString: "Commands"
*scenMalfMenuHelppb.mnemonic: "C"
*scenMalfMenuHelppb.activateCallback: {printf ("help comandi\n");}

*scenMalfMenuShow.class: rowColumn
*scenMalfMenuShow.static: true
*scenMalfMenuShow.name: scenMalfMenuShow
*scenMalfMenuShow.parent: scenMalfMenu
*scenMalfMenuShow.rowColumnType: "menu_pulldown"

*scenMalfMenuShowSummaryMalf.class: pushButton
*scenMalfMenuShowSummaryMalf.static: true
*scenMalfMenuShowSummaryMalf.name: scenMalfMenuShowSummaryMalf
*scenMalfMenuShowSummaryMalf.parent: scenMalfMenuShow
*scenMalfMenuShowSummaryMalf.labelString: MALF_SUMMARY
*scenMalfMenuShowSummaryMalf.activateCallback: {\
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
}

*malfMenu_top_File.class: cascadeButton
*malfMenu_top_File.static: true
*malfMenu_top_File.name: malfMenu_top_File
*malfMenu_top_File.parent: scenMalfMenu
*malfMenu_top_File.labelString: FileMenuLabel
*malfMenu_top_File.subMenuId: "scenMalfMenuFile1"
*malfMenu_top_File.cascadingCallback: {\
printf ("valutazione tasti nscen cascade= %d\n",num_scen);\
if (num_scen < 0) /* e' stato richiesto un nuovo scenario */\
   gestioneTastiScenarioMalf (UxWidget);\
}

*malfMenu_top_Edit.class: cascadeButton
*malfMenu_top_Edit.static: true
*malfMenu_top_Edit.name: malfMenu_top_Edit
*malfMenu_top_Edit.parent: scenMalfMenu
*malfMenu_top_Edit.labelString: EditMenuLabel
*malfMenu_top_Edit.subMenuId: "scenMalfMenuEdit"

*malfMenu_top_b3.class: cascadeButton
*malfMenu_top_b3.static: true
*malfMenu_top_b3.name: malfMenu_top_b3
*malfMenu_top_b3.parent: scenMalfMenu
*malfMenu_top_b3.labelString: HelpMenuLabel
*malfMenu_top_b3.subMenuId: "scenMalfMenuHelp"

*malfMenu_top_Show.class: cascadeButton
*malfMenu_top_Show.static: true
*malfMenu_top_Show.name: malfMenu_top_Show
*malfMenu_top_Show.parent: scenMalfMenu
*malfMenu_top_Show.labelString: ShowMenuLabel
*malfMenu_top_Show.subMenuId: "scenMalfMenuShow"

*frame16.class: frame
*frame16.static: true
*frame16.name: frame16
*frame16.parent: scenarioMalf
*frame16.x: 48
*frame16.y: 288
*frame16.width: 690
*frame16.height: 80
*frame16.leftOffset: 0
*frame16.rightAttachment: "attach_form"
*frame16.leftAttachment: "attach_form"
*frame16.bottomAttachment: "attach_form"

*form32.class: form
*form32.static: true
*form32.name: form32
*form32.parent: frame16
*form32.resizePolicy: "resize_none"
*form32.x: 2
*form32.y: 20
*form32.width: 851
*form32.height: 82
*form32.defaultButton: "actMalfScenpb"

*quitMalfScenpb.class: pushButton
*quitMalfScenpb.static: true
*quitMalfScenpb.name: quitMalfScenpb
*quitMalfScenpb.parent: form32
*quitMalfScenpb.x: 530
*quitMalfScenpb.y: 15
*quitMalfScenpb.width: 80
*quitMalfScenpb.height: 30
*quitMalfScenpb.labelString: QUITLABEL 
*quitMalfScenpb.bottomAttachment: "attach_form"
*quitMalfScenpb.leftAttachment: "attach_position"
*quitMalfScenpb.rightAttachment: "attach_form"
*quitMalfScenpb.rightOffset: 20
*quitMalfScenpb.topAttachment: "attach_form"
*quitMalfScenpb.topOffset: 15
*quitMalfScenpb.bottomOffset: 15
*quitMalfScenpb.activateCallback: {\
uscita_scenarioMalf ();\
}
*quitMalfScenpb.activateCallbackClientData: scenarioMalf
*quitMalfScenpb.leftPosition: 80

*actMalfScenpb.class: pushButton
*actMalfScenpb.name.source: public
*actMalfScenpb.static: false
*actMalfScenpb.name: actMalfScenpb
*actMalfScenpb.parent: form32
*actMalfScenpb.x: 20
*actMalfScenpb.y: 15
*actMalfScenpb.width: 80
*actMalfScenpb.height: 30
*actMalfScenpb.labelString: ACT_LABEL
*actMalfScenpb.bottomAttachment: "attach_form"
*actMalfScenpb.bottomOffset: 15
*actMalfScenpb.rightAttachment: "attach_none"
*actMalfScenpb.rightPosition: 0
*actMalfScenpb.rightOffset: 0
*actMalfScenpb.leftAttachment: "attach_form"
*actMalfScenpb.leftOffset: 20
*actMalfScenpb.topAttachment: "attach_form"
*actMalfScenpb.topOffset: 15
*actMalfScenpb.sensitive: "true"
*actMalfScenpb.activateCallback: {\
attivaMalfSelect (UxWidget,ACTIVATION);\
\
}
*actMalfScenpb.activateCallbackClientData: (XtPointer) 0x0

*deactMalfScenpb.class: pushButton
*deactMalfScenpb.static: true
*deactMalfScenpb.name: deactMalfScenpb
*deactMalfScenpb.parent: form32
*deactMalfScenpb.x: 149
*deactMalfScenpb.y: 15
*deactMalfScenpb.width: 80
*deactMalfScenpb.height: 30
*deactMalfScenpb.labelString: DEACT_LABEL
*deactMalfScenpb.bottomAttachment: "attach_form"
*deactMalfScenpb.bottomOffset: 15
*deactMalfScenpb.leftAttachment: "attach_position"
*deactMalfScenpb.leftOffset: 0
*deactMalfScenpb.leftWidget: ""
*deactMalfScenpb.rightAttachment: "attach_none"
*deactMalfScenpb.topAttachment: "attach_form"
*deactMalfScenpb.topOffset: 15
*deactMalfScenpb.sensitive: "true"
*deactMalfScenpb.activateCallback: {\
attivaMalfSelect (UxWidget,DEACTIVATION);\
\
}
*deactMalfScenpb.rightPosition: 0
*deactMalfScenpb.leftPosition: 20

*scenarioMalfScrollWin.class: scrolledWindow
*scenarioMalfScrollWin.static: true
*scenarioMalfScrollWin.name: scenarioMalfScrollWin
*scenarioMalfScrollWin.parent: scenarioMalf
*scenarioMalfScrollWin.scrollingPolicy: "automatic"
*scenarioMalfScrollWin.x: 15
*scenarioMalfScrollWin.y: 60
*scenarioMalfScrollWin.width: 500
*scenarioMalfScrollWin.height: 255
*scenarioMalfScrollWin.bottomAttachment: "attach_widget"
*scenarioMalfScrollWin.bottomOffset: 20
*scenarioMalfScrollWin.bottomWidget: "frame16"
*scenarioMalfScrollWin.leftOffset: 20
*scenarioMalfScrollWin.rightAttachment: "attach_form"
*scenarioMalfScrollWin.rightOffset: 20
*scenarioMalfScrollWin.leftAttachment: "attach_form"
*scenarioMalfScrollWin.topAttachment: "attach_widget"
*scenarioMalfScrollWin.topOffset: 20
*scenarioMalfScrollWin.topWidget: "scenMalfMenu"

*scenMalfRc.class: rowColumn
*scenMalfRc.static: true
*scenMalfRc.name: scenMalfRc
*scenMalfRc.parent: scenarioMalfScrollWin
*scenMalfRc.x: 2
*scenMalfRc.y: 2
*scenMalfRc.width: 600
*scenMalfRc.height: 230

*scenMalfRcPopupMenu.class: rowColumn
*scenMalfRcPopupMenu.static: true
*scenMalfRcPopupMenu.name: scenMalfRcPopupMenu
*scenMalfRcPopupMenu.parent: scenarioMalf
*scenMalfRcPopupMenu.rowColumnType: "menu_popup"
*scenMalfRcPopupMenu.menuAccelerator: "Shift <KeyUp>F10"

*scenMfPopupSave.class: pushButton
*scenMfPopupSave.static: true
*scenMfPopupSave.name: scenMfPopupSave
*scenMfPopupSave.parent: scenMalfRcPopupMenu
*scenMfPopupSave.labelString: SaveMenuLabel
*scenMfPopupSave.activateCallback: {\
#ifndef DESIGN_TIME\
save_scenmalf (scenarioMalf,tipo,num_scen);\
nuovoScenarioNotify (scenarioMalf,Parent);\
#endif\
}
*scenMfPopupSave.createCallback: {\
if (num_scen < 0) /* e' stato richiesto un nuovo scenario */\
   gestioneTastiScenarioMalf (UxWidget);\
}

*scenMfPopupSep1.class: separator
*scenMfPopupSep1.static: true
*scenMfPopupSep1.name: scenMfPopupSep1
*scenMfPopupSep1.parent: scenMalfRcPopupMenu

*scenMalfRcPopupAdd.class: pushButton
*scenMalfRcPopupAdd.static: true
*scenMalfRcPopupAdd.name: scenMalfRcPopupAdd
*scenMalfRcPopupAdd.parent: scenMalfRcPopupMenu
*scenMalfRcPopupAdd.labelString: AddItemLabel
*scenMalfRcPopupAdd.activateCallback: {\
#ifndef DESIGN_TIME\
/***\
create_selezMalf (UxGetWidget(scenarioMalf),&scenario,tipo);\
***/\
create_selVar (UxGetWidget(scenarioMalf),\
                &scenario,tipo,\
                scenari_malf.s[num_scen-1].scen_header.commento);\
#endif\
}

*scenMalfPopupDel.class: pushButton
*scenMalfPopupDel.static: true
*scenMalfPopupDel.name: scenMalfPopupDel
*scenMalfPopupDel.parent: scenMalfRcPopupMenu
*scenMalfPopupDel.labelString: CutMenuLabel
*scenMalfPopupDel.activateCallback: {\
delete_item_scen_malf (UxWidget);\
}
*scenMalfPopupDel.sensitive: "false"

*scenMfPopupSep2.class: separator
*scenMfPopupSep2.static: true
*scenMfPopupSep2.name: scenMfPopupSep2
*scenMfPopupSep2.parent: scenMalfRcPopupMenu

*scenMfPopupSummary.class: pushButton
*scenMfPopupSummary.static: true
*scenMfPopupSummary.name: scenMfPopupSummary
*scenMfPopupSummary.parent: scenMalfRcPopupMenu
*scenMfPopupSummary.labelString: MALF_SUMMARY
*scenMfPopupSummary.activateCallback: {\
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
}

*scenMfPopupSep3.class: separator
*scenMfPopupSep3.static: true
*scenMfPopupSep3.name: scenMfPopupSep3
*scenMfPopupSep3.parent: scenMalfRcPopupMenu

*scenMalfRcPopupQuit.class: pushButton
*scenMalfRcPopupQuit.static: true
*scenMalfRcPopupQuit.name: scenMalfRcPopupQuit
*scenMalfRcPopupQuit.parent: scenMalfRcPopupMenu
*scenMalfRcPopupQuit.labelString: QuitMenuLabel
*scenMalfRcPopupQuit.activateCallback: {\
uscita_scenarioMalf ();\
}
*scenMalfRcPopupQuit.activateCallbackClientData: scenarioMalf

