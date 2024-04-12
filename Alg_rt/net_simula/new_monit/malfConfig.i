! UIMX ascii 2.8 key: 2377                                                      

*malfConfig.class: formDialog
*malfConfig.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include "bistrutt.h"\
#include "malfunzioni.h"\
#include "tabelle_malf.h"\
#include "file_selection.h"\
#include "messaggi.h"\
\
extern M_COMPONENT* m_component;\
extern M_COMP_TYPE *m_comp_type;\
extern MALF_SET *malf_set;\
\
extern M_COMP_TYPE *fr_comp_type;\
extern MALF_SET *frem_set;\
extern M_COMPONENT *fr_component;
*malfConfig.ispecdecl: float delay;\
float duration;\
float ramp;\
float secVal1;\
float secVal2;\
float secVal3;\
float secVal4;\
XtIntervalId timer_malfConfig;\
int delayModified;\
int rampModified;\
int durataModified;\
int valSec1Modified;\
int valSec2Modified;\
int valSec3Modified;\
int valSec4Modified;\
unsigned int sfondo;\
unsigned int colorTesto;\
\
/* Widget per var. secondarie  */\
Widget SecVar1;  /* form contenitore  */\
Widget SecVar2;  /* form contenitore  */\
Widget SecVar3;  /* form contenitore  */\
Widget SecVar4;  /* form contenitore  */\
\
Widget secVar1Label; /* label var. secondaria */\
Widget secVar2Label; /* label var. secondaria */\
Widget secVar3Label; /* label var. secondaria */\
Widget secVar4Label; /* label var. secondaria */\
\
Widget secVar1Descr; /* Descrizione var. sec. */\
Widget secVar2Descr; /* Descrizione var. sec. */\
Widget secVar3Descr; /* Descrizione var. sec. */\
Widget secVar4Descr; /* Descrizione var. sec. */\
\
Widget secVar1ValTf; /* text var. sec.        */\
Widget secVar2ValTf; /* text var. sec.        */\
Widget secVar3ValTf; /* text var. sec.        */\
Widget secVar4ValTf; /* text var. sec.        */\
\
Widget secVar1Tb;    /* toggle button var. sec.*/\
Widget secVar2Tb;    /* toggle button var. sec.*/\
Widget secVar3Tb;    /* toggle button var. sec.*/\
Widget secVar4Tb;    /* toggle button var. sec.*/\
\
Widget secVar1Mod;   /* flag entry modificata  */\
Widget secVar2Mod;   /* flag entry modificata  */\
Widget secVar3Mod;   /* flag entry modificata  */\
Widget secVar4Mod;   /* flag entry modificata  */\
\
Widget secVar1ValActLab; /* label valore attuale  */\
Widget secVar2ValActLab; /* label valore attuale  */\
Widget secVar3ValActLab; /* label valore attuale  */\
Widget secVar4ValActLab; /* label valore attuale  */\
\
Widget secVar1ValAct; /* valore attuale          */\
Widget secVar2ValAct; /* valore attuale          */\
Widget secVar3ValAct; /* valore attuale          */\
Widget secVar4ValAct; /* valore attuale          */\
\
/* definizione del tipo di variabile sec.       */\
int pertToggle1;     /* se = 1 pert toggle      */\
int pertToggle2;     /* se = 1 pert toggle      */\
int pertToggle3;     /* se = 1 pert toggle      */\
int pertToggle4;     /* se = 1 pert toggle      */\
\
/* flag di presenza variabile                   */\
int varSecExist1;    /* se = 1 var. sec. esiste */\
int varSecExist2;    /* se = 1 var. sec. esiste */\
int varSecExist3;    /* se = 1 var. sec. esiste */\
int varSecExist4;    /* se = 1 var. sec. esiste */\
\
/* valore precedente                             */\
float valPrec1;\
float valPrec2;\
float valPrec3;\
float valPrec4;
*malfConfig.ispeclist: delay, duration, ramp, secVal1, secVal2, secVal3, secVal4, timer_malfConfig, delayModified, rampModified, durataModified, valSec1Modified, valSec2Modified, valSec3Modified, valSec4Modified, sfondo, colorTesto, SecVar1, SecVar2, SecVar3, SecVar4, secVar1Label, secVar2Label, secVar3Label, secVar4Label, secVar1Descr, secVar2Descr, secVar3Descr, secVar4Descr, secVar1ValTf, secVar2ValTf, secVar3ValTf, secVar4ValTf, secVar1Tb, secVar2Tb, secVar3Tb, secVar4Tb, secVar1Mod, secVar2Mod, secVar3Mod, secVar4Mod, secVar1ValActLab, secVar2ValActLab, secVar3ValActLab, secVar4ValActLab, secVar1ValAct, secVar2ValAct, secVar3ValAct, secVar4ValAct, pertToggle1, pertToggle2, pertToggle3, pertToggle4, varSecExist1, varSecExist2, varSecExist3, varSecExist4, valPrec1, valPrec2, valPrec3, valPrec4
*malfConfig.ispeclist.delay: "float", "%delay%"
*malfConfig.ispeclist.duration: "float", "%duration%"
*malfConfig.ispeclist.ramp: "float", "%ramp%"
*malfConfig.ispeclist.secVal1: "float", "%secVal1%"
*malfConfig.ispeclist.secVal2: "float", "%secVal2%"
*malfConfig.ispeclist.secVal3: "float", "%secVal3%"
*malfConfig.ispeclist.secVal4: "float", "%secVal4%"
*malfConfig.ispeclist.timer_malfConfig: "XtIntervalId", "%timer_malfConfig%"
*malfConfig.ispeclist.delayModified: "int", "%delayModified%"
*malfConfig.ispeclist.rampModified: "int", "%rampModified%"
*malfConfig.ispeclist.durataModified: "int", "%durataModified%"
*malfConfig.ispeclist.valSec1Modified: "int", "%valSec1Modified%"
*malfConfig.ispeclist.valSec2Modified: "int", "%valSec2Modified%"
*malfConfig.ispeclist.valSec3Modified: "int", "%valSec3Modified%"
*malfConfig.ispeclist.valSec4Modified: "int", "%valSec4Modified%"
*malfConfig.ispeclist.sfondo: "unsigned int", "%sfondo%"
*malfConfig.ispeclist.colorTesto: "unsigned int", "%colorTesto%"
*malfConfig.ispeclist.SecVar1: "Widget", "%SecVar1%"
*malfConfig.ispeclist.SecVar2: "Widget", "%SecVar2%"
*malfConfig.ispeclist.SecVar3: "Widget", "%SecVar3%"
*malfConfig.ispeclist.SecVar4: "Widget", "%SecVar4%"
*malfConfig.ispeclist.secVar1Label: "Widget", "%secVar1Label%"
*malfConfig.ispeclist.secVar2Label: "Widget", "%secVar2Label%"
*malfConfig.ispeclist.secVar3Label: "Widget", "%secVar3Label%"
*malfConfig.ispeclist.secVar4Label: "Widget", "%secVar4Label%"
*malfConfig.ispeclist.secVar1Descr: "Widget", "%secVar1Descr%"
*malfConfig.ispeclist.secVar2Descr: "Widget", "%secVar2Descr%"
*malfConfig.ispeclist.secVar3Descr: "Widget", "%secVar3Descr%"
*malfConfig.ispeclist.secVar4Descr: "Widget", "%secVar4Descr%"
*malfConfig.ispeclist.secVar1ValTf: "Widget", "%secVar1ValTf%"
*malfConfig.ispeclist.secVar2ValTf: "Widget", "%secVar2ValTf%"
*malfConfig.ispeclist.secVar3ValTf: "Widget", "%secVar3ValTf%"
*malfConfig.ispeclist.secVar4ValTf: "Widget", "%secVar4ValTf%"
*malfConfig.ispeclist.secVar1Tb: "Widget", "%secVar1Tb%"
*malfConfig.ispeclist.secVar2Tb: "Widget", "%secVar2Tb%"
*malfConfig.ispeclist.secVar3Tb: "Widget", "%secVar3Tb%"
*malfConfig.ispeclist.secVar4Tb: "Widget", "%secVar4Tb%"
*malfConfig.ispeclist.secVar1Mod: "Widget", "%secVar1Mod%"
*malfConfig.ispeclist.secVar2Mod: "Widget", "%secVar2Mod%"
*malfConfig.ispeclist.secVar3Mod: "Widget", "%secVar3Mod%"
*malfConfig.ispeclist.secVar4Mod: "Widget", "%secVar4Mod%"
*malfConfig.ispeclist.secVar1ValActLab: "Widget", "%secVar1ValActLab%"
*malfConfig.ispeclist.secVar2ValActLab: "Widget", "%secVar2ValActLab%"
*malfConfig.ispeclist.secVar3ValActLab: "Widget", "%secVar3ValActLab%"
*malfConfig.ispeclist.secVar4ValActLab: "Widget", "%secVar4ValActLab%"
*malfConfig.ispeclist.secVar1ValAct: "Widget", "%secVar1ValAct%"
*malfConfig.ispeclist.secVar2ValAct: "Widget", "%secVar2ValAct%"
*malfConfig.ispeclist.secVar3ValAct: "Widget", "%secVar3ValAct%"
*malfConfig.ispeclist.secVar4ValAct: "Widget", "%secVar4ValAct%"
*malfConfig.ispeclist.pertToggle1: "int", "%pertToggle1%"
*malfConfig.ispeclist.pertToggle2: "int", "%pertToggle2%"
*malfConfig.ispeclist.pertToggle3: "int", "%pertToggle3%"
*malfConfig.ispeclist.pertToggle4: "int", "%pertToggle4%"
*malfConfig.ispeclist.varSecExist1: "int", "%varSecExist1%"
*malfConfig.ispeclist.varSecExist2: "int", "%varSecExist2%"
*malfConfig.ispeclist.varSecExist3: "int", "%varSecExist3%"
*malfConfig.ispeclist.varSecExist4: "int", "%varSecExist4%"
*malfConfig.ispeclist.valPrec1: "float", "%valPrec1%"
*malfConfig.ispeclist.valPrec2: "float", "%valPrec2%"
*malfConfig.ispeclist.valPrec3: "float", "%valPrec3%"
*malfConfig.ispeclist.valPrec4: "float", "%valPrec4%"
*malfConfig.funcdecl: swidget create_malfConfig(UxParent, indx, tipo)\
swidget UxParent; /* padre                       */\
int indx;         /* numero di entry in scenario */\
int tipo;         /* malf o frem   */
*malfConfig.funcname: create_malfConfig
*malfConfig.funcdef: "swidget", "<create_malfConfig>(%)"
*malfConfig.argdecl: swidget UxParent;\
int indx;\
int tipo;
*malfConfig.arglist: UxParent, indx, tipo
*malfConfig.arglist.UxParent: "swidget", "%UxParent%"
*malfConfig.arglist.indx: "int", "%indx%"
*malfConfig.arglist.tipo: "int", "%tipo%"
*malfConfig.icode: printf ("Richiesto  su indice %d\n",indx);\
delayModified  = 0; \
rampModified = 0;\
durataModified = 0;\
\
valSec1Modified = 0;\
valSec2Modified = 0;\
valSec3Modified = 0;\
valSec4Modified = 0;\
\
pertToggle1 = 0;\
pertToggle2 = 0;\
pertToggle3 = 0;\
pertToggle4 = 0;\
\
varSecExist1 = -1;\
varSecExist2 = -1;\
varSecExist3 = -1;\
varSecExist4 = -1;\
\
valPrec1 = -999.999;\
valPrec2 = -999.999;\
valPrec3 = -999.999;\
valPrec4 = -999.999;
*malfConfig.fcode: /* colore di reset per le deselezioni */\
sfondo = read_background_color (rtrn);\
/* colore di set per tag di modifica */\
colorTesto = read_foreground_color (delayTf);\
\
switch (tipo)\
   {\
   case MALFUNZIONI:\
   case SOMMARIO_MALF:\
      creaCampiVarSec (rtrn, UxParent, m_comp_type, malf_set, m_component);\
      displayDatiMalfConfig (rtrn, UxParent, m_comp_type, malf_set, m_component);\
      break;\
   case FUNZIONI_REMOTE:\
   case SOMMARIO_FREM:\
      creaCampiVarSec (rtrn, UxParent, fr_comp_type, frem_set, fr_component);\
      displayDatiMalfConfig (rtrn, UxParent, fr_comp_type, frem_set, fr_component);\
      break;\
   }\
\
attiva_timer_malfConfig (rtrn);\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*malfConfig.auxdecl: uscitaMalfConfig (Widget w)\
{\
/*** in destroy callback\
   reset_MoreDataFlag (UxParent,indx);\
   stop_timer (timer_malfConfig);\
**************/\
   DistruggiInterfaccia (XtParent(malfConfig));\
}\
/*****************************************************/\
int inModifica (int *flag, Boolean val)\
{\
   if (val == True)   /* setta la flag */\
      *flag = 1;\
   else\
      *flag = 0;\
   return (0);\
}
*malfConfig.static: true
*malfConfig.name: malfConfig
*malfConfig.parent: NO_PARENT
*malfConfig.parentExpression: UxParent
*malfConfig.defaultShell: topLevelShell
*malfConfig.unitType: "pixels"
*malfConfig.x: 500
*malfConfig.y: 170
*malfConfig.width: 260
*malfConfig.height: 480
*malfConfig.noResize: "true"
*malfConfig.destroyCallback: {\
reset_MoreDataFlag (UxParent,indx);\
stop_timer (timer_malfConfig);\
\
}

*frame30.class: frame
*frame30.static: true
*frame30.name: frame30
*frame30.parent: malfConfig
*frame30.x: -267
*frame30.y: 140
*frame30.width: 795
*frame30.height: 50
*frame30.bottomAttachment: "attach_form"
*frame30.leftOffset: 0
*frame30.rightAttachment: "attach_form"
*frame30.leftAttachment: "attach_form"

*form56.class: form
*form56.static: true
*form56.name: form56
*form56.parent: frame30
*form56.resizePolicy: "resize_none"
*form56.x: 0
*form56.y: 0
*form56.width: 745
*form56.height: 72
*form56.defaultButton: ""

*applyMalfConfigpb.class: pushButton
*applyMalfConfigpb.static: true
*applyMalfConfigpb.name: applyMalfConfigpb
*applyMalfConfigpb.parent: form56
*applyMalfConfigpb.x: 100
*applyMalfConfigpb.y: 20
*applyMalfConfigpb.width: 130
*applyMalfConfigpb.height: 40
*applyMalfConfigpb.labelString: APPLYLABEL ? APPLYLABEL : "OK"
*applyMalfConfigpb.leftAttachment: "attach_position"
*applyMalfConfigpb.leftOffset: 0
*applyMalfConfigpb.leftPosition: 30
*applyMalfConfigpb.rightAttachment: "attach_position"
*applyMalfConfigpb.rightPosition: 70
*applyMalfConfigpb.activateCallback: {\
applyMalfConfig (malfConfig,UxParent);\
}
*applyMalfConfigpb.bottomAttachment: "attach_form"
*applyMalfConfigpb.bottomOffset: 12
*applyMalfConfigpb.topAttachment: "attach_form"
*applyMalfConfigpb.topOffset: 12

*menu10.class: rowColumn
*menu10.static: true
*menu10.name: menu10
*menu10.parent: malfConfig
*menu10.rowColumnType: "menu_bar"
*menu10.rightAttachment: "attach_form"
*menu10.leftAttachment: "attach_form"
*menu10.menuAccelerator: "<KeyUp>F10"

*malfConfigFile.class: rowColumn
*malfConfigFile.static: true
*malfConfigFile.name: malfConfigFile
*malfConfigFile.parent: menu10
*malfConfigFile.rowColumnType: "menu_pulldown"

*malfConfigFileQuitpb.class: pushButton
*malfConfigFileQuitpb.static: true
*malfConfigFileQuitpb.name: malfConfigFileQuitpb
*malfConfigFileQuitpb.parent: malfConfigFile
*malfConfigFileQuitpb.labelString: "Quit"
*malfConfigFileQuitpb.activateCallback: uscitaMalfConfig (malfConfig);

*menu10_top_b3.class: cascadeButton
*menu10_top_b3.static: true
*menu10_top_b3.name: menu10_top_b3
*menu10_top_b3.parent: menu10
*menu10_top_b3.labelString: "File"
*menu10_top_b3.subMenuId: "malfConfigFile"

*form58.class: form
*form58.static: true
*form58.name: form58
*form58.parent: malfConfig
*form58.resizePolicy: "resize_none"
*form58.x: 0
*form58.y: 10
*form58.width: 250
*form58.height: 370
*form58.topOffset: 0
*form58.rightAttachment: "attach_form"
*form58.leftAttachment: "attach_form"
*form58.bottomAttachment: "attach_widget"
*form58.bottomWidget: "frame30"
*form58.topAttachment: "attach_widget"
*form58.topWidget: "menu10"
*form58.defaultButton: "applyMalfConfigpb"

*secVar.class: form
*secVar.static: true
*secVar.name: secVar
*secVar.parent: form58
*secVar.resizePolicy: "resize_none"
*secVar.x: 0
*secVar.y: 0
*secVar.width: 260
*secVar.height: 320
*secVar.rightAttachment: "attach_form"
*secVar.topAttachment: "attach_none"
*secVar.topOffset: 0
*secVar.bottomAttachment: "attach_form"
*secVar.leftAttachment: "attach_form"

*secVarRc.class: rowColumn
*secVarRc.static: true
*secVarRc.name: secVarRc
*secVarRc.parent: secVar
*secVarRc.x: 10
*secVarRc.y: 20
*secVarRc.width: 200
*secVarRc.height: 200
*secVarRc.bottomAttachment: "attach_form"
*secVarRc.leftOffset: 0
*secVarRc.rightAttachment: "attach_form"
*secVarRc.leftAttachment: "attach_form"
*secVarRc.topAttachment: "attach_form"

*menu11.class: rowColumn
*menu11.static: true
*menu11.name: menu11
*menu11.parent: form58
*menu11.rowColumnType: "menu_popup"

*malfConfigPopupQuit.class: pushButton
*malfConfigPopupQuit.static: true
*malfConfigPopupQuit.name: malfConfigPopupQuit
*malfConfigPopupQuit.parent: menu11
*malfConfigPopupQuit.labelString: "Quit"
*malfConfigPopupQuit.activateCallback: {\
uscitaMalfConfig (malfConfig);\
}

*malfParam.class: form
*malfParam.static: true
*malfParam.name: malfParam
*malfParam.parent: form58
*malfParam.resizePolicy: "resize_none"
*malfParam.x: 0
*malfParam.y: 10
*malfParam.width: 290
*malfParam.height: 120
*malfParam.noResize: "true"
*malfParam.topOffset: 0
*malfParam.rightAttachment: "attach_form"
*malfParam.leftAttachment: "attach_form"
*malfParam.bottomAttachment: "attach_widget"
*malfParam.bottomWidget: "secVar"
*malfParam.topAttachment: "attach_form"

*durationTf.class: text
*durationTf.static: true
*durationTf.name: durationTf
*durationTf.parent: malfParam
*durationTf.x: 160
*durationTf.y: 40
*durationTf.width: 90
*durationTf.height: 25
*durationTf.marginHeight: 2
*durationTf.gainPrimaryCallback: {\
durataModified = 1;\
}
*durationTf.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

*rampTf.class: text
*rampTf.static: true
*rampTf.name: rampTf
*rampTf.parent: malfParam
*rampTf.x: 160
*rampTf.y: 70
*rampTf.width: 90
*rampTf.height: 25
*rampTf.marginHeight: 2
*rampTf.gainPrimaryCallback: {\
rampModified  = 1;\
}
*rampTf.createManaged: "false"
*rampTf.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

*label26.class: label
*label26.static: true
*label26.name: label26
*label26.parent: malfParam
*label26.x: 10
*label26.y: 10
*label26.width: 130
*label26.height: 25
*label26.borderWidth: 0
*label26.labelString: DELAY_LABEL
*label26.alignment: "alignment_beginning"
*label26.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

*label27.class: label
*label27.static: true
*label27.name: label27
*label27.parent: malfParam
*label27.x: 10
*label27.y: 40
*label27.width: 130
*label27.height: 25
*label27.borderWidth: 0
*label27.labelString: DURATION_LABEL
*label27.alignment: "alignment_beginning"
*label27.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

*label28.class: label
*label28.static: true
*label28.name: label28
*label28.parent: malfParam
*label28.x: 10
*label28.y: 70
*label28.width: 130
*label28.height: 25
*label28.borderWidth: 0
*label28.labelString: RAMP_LABEL
*label28.alignment: "alignment_beginning"
*label28.createManaged: "false"
*label28.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

*separator4.class: separator
*separator4.static: true
*separator4.name: separator4
*separator4.parent: malfParam
*separator4.x: 10
*separator4.y: 120
*separator4.width: 240
*separator4.height: 10
*separator4.topOffset: 0
*separator4.bottomAttachment: "attach_form"
*separator4.topAttachment: "attach_none"

*delayTf.class: text
*delayTf.static: true
*delayTf.name: delayTf
*delayTf.parent: malfParam
*delayTf.x: 160
*delayTf.y: 10
*delayTf.width: 90
*delayTf.height: 25
*delayTf.marginHeight: 2
*delayTf.gainPrimaryCallback: {\
delayModified = 1;\
\
}
*delayTf.fontList: "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-8"

