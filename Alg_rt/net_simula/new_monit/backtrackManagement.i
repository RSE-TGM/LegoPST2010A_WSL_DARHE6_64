! UIMX ascii 2.8 key: 4755                                                      

*backtrackManagement.class: formDialog
*backtrackManagement.classinc:
*backtrackManagement.classspec:
*backtrackManagement.classmembers:
*backtrackManagement.classconstructor:
*backtrackManagement.classdestructor:
*backtrackManagement.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "bistrutt.h"\
#ifndef DESIGN_TIME\
#include "parametri.h" \
#include "preview.h"\
#endif\
\
extern int _MAX_BACK_TRACK;\
extern int _MAX_SNAP_SHOT;\
extern int freeze_rest;\
\
#include "backtrack.h"\
extern int bt_interface_active;\
#include "cursore.h"\
#include "sked.h"\
#include "messaggi.h"\
BKTAB *bt_header;\
SNTAB *snap_header;\
extern int inizializzazione;\
int backtrack_caricato;\
extern swidget masterMenu;\
XtIntervalId timer_replayOn;\
extern int stato_sim;\
int prec_sel;\
/* flag interblocco tasti INIT/LOAD dal nome del testatore */\
int DragonFlag;
*backtrackManagement.ispecdecl:
*backtrackManagement.funcdecl: swidget create_backtrackManagement(padre_bt)\
Widget padre_bt;
*backtrackManagement.funcname: create_backtrackManagement
*backtrackManagement.funcdef: "swidget", "<create_backtrackManagement>(%)"
*backtrackManagement.argdecl: Widget padre_bt;
*backtrackManagement.arglist: padre_bt
*backtrackManagement.arglist.padre_bt: "Widget", "%padre_bt%"
*backtrackManagement.icode: printf ("inizio colloquio backtrack\n");\
set_cursor (padre_bt,CLOCK);\
bt_interface_active = 1;\
/* preset variabili puntatori ai records */\
prec_sel = 0;\
/* preset sul primo record (indice da 1 a _MAX_BACK_TRACK) */\
bt_sel = 1; \
DragonFlag = 0;\
\

*backtrackManagement.fcode: bt_header = (BKTAB *)malloc(sizeof(BKTAB)*_MAX_BACK_TRACK);\
AllocaAreeBacktrack ();\
read_lista_bt (bt_header);\
display_header_bt (UxGetWidget(BtRc),bt_header);\
\
background_backtrack = read_background_color (UxGetWidget(BtRc));\
/*\
 * per snap di default\
 */\
snap_header = (SNTAB*)malloc(sizeof(SNTAB)*_MAX_SNAP_SHOT);\
read_lista_snap (snap_header);\
\
UxPopupInterface (rtrn, no_grab);\
set_cursor (padre_bt,NORMALE);\
\
return(rtrn);\

*backtrackManagement.auxdecl: /******************************************************************/\
void BtSelActivate (parent, dati, reason)\
Widget parent;\
char *dati;\
XmAnyCallbackStruct *reason;\
{\
int tipo_entry;\
/* messo come var. globale per azzeramento da clear del tempo\
static int prec_sel = 0;\
**/\
   \
#ifndef DESIGN_TIME   \
/*   bt_sel = atoi(dati); */  /* da 1 a n  */\
\
   bt_punt = atoi(dati); /* da 1 a n  (numero di item (riga))*/	\
   tipo_entry = reason->reason;\
\
   switch (tipo_entry)\
      {\
      case XmCR_FOCUS:\
	if ((prec_sel>0)&&(prec_sel!=bt_punt)&&(prec_sel!=bt_sel))  \
	   set_colore_riga_bt(prec_sel-1, background_backtrack); \
        if (bt_punt != bt_sel)\
           set_colore_riga_bt(bt_punt-1, colore_app[5]);  \
	break;       	   \
      case XmCR_LOSING_FOCUS:\
         break;\
      case XmCR_ACTIVATE:\
	if ((prec_sel>0)&&(prec_sel!=bt_punt)&&(prec_sel!=bt_sel))  \
	   set_colore_riga_bt(prec_sel-1, background_backtrack); \
        if (bt_punt != bt_sel)\
           set_colore_riga_bt(bt_punt-1, colore_app[5]); \
         break;\
      default:\
         break; \
      }\
/***   \
   printf ("selezionato bt %d record n. %d\n",\
              bt_sel, punt_rec_bt[bt_sel]);  \
   printf ("puntato bt %d record %d\n",\
              bt_punt, punt_rec_bt[bt_punt]);\
***/\
   if ((bt_header+punt_rec_bt[bt_punt])->stat == 1)  /* snap occupato  */\
      {\
      XtVaSetValues (UxGetWidget(btLoadpb), XmNsensitive, True, NULL);\
      XtVaSetValues (UxGetWidget(btViewpb), XmNsensitive, True, NULL);\
      XtVaSetValues (UxGetWidget(BtRcPopupLoad), XmNsensitive, True, NULL);\
      XtVaSetValues (UxGetWidget(BtRcPopupView), XmNsensitive, True, NULL);\
      }\
   else\
      {\
      /* printf ("record %d non occupato\n",n); */\
      XtVaSetValues (UxGetWidget(btLoadpb), XmNsensitive, False, NULL);\
      XtVaSetValues (UxGetWidget(btViewpb), XmNsensitive, False, NULL);\
      XtVaSetValues (UxGetWidget(BtRcPopupLoad), XmNsensitive, False, NULL);\
      XtVaSetValues (UxGetWidget(BtRcPopupView), XmNsensitive, False, NULL);\
      }\
\
   prec_sel = bt_punt;\
\
#endif \
\
   return;\
}\
/******************************************************************/\
int carica_header_bt ()\
{\
#ifndef DESIGN_TIME\
   read_lista_bt (bt_header);\
   display_header_bt (UxGetWidget(BtRc),bt_header);\
#endif\
return (0);\
}\
\
/******************************************************************/\
int exit_replay()\
{\
\
   replay_mode (UxGetWidget(backtrackManagement), False);\
   uscita_backtrack(UxGetWidget(backtrackManagement));\
\
}\
   
*backtrackManagement.name.source: public
*backtrackManagement.static: false
*backtrackManagement.name: backtrackManagement
*backtrackManagement.parent: NO_PARENT
*backtrackManagement.defaultShell: topLevelShell
*backtrackManagement.unitType: "pixels"
*backtrackManagement.x: 369
*backtrackManagement.y: 175
*backtrackManagement.width: 400
*backtrackManagement.height: 602
*backtrackManagement.dialogTitle: "BACKTRACK MANAGEMENT"
*backtrackManagement.destroyCallback: {\
bt_interface_active = 0;\
free (snap_header);\
free (bt_header);\
}

*frame15.class: frame
*frame15.static: true
*frame15.name: frame15
*frame15.parent: backtrackManagement
*frame15.x: 0
*frame15.y: 0
*frame15.width: 400
*frame15.height: 80
*frame15.bottomAttachment: "attach_form"
*frame15.rightAttachment: "attach_form"
*frame15.leftAttachment: "attach_form"

*form22.class: form
*form22.static: true
*form22.name: form22
*form22.parent: frame15
*form22.resizePolicy: "resize_none"
*form22.x: 2
*form22.y: 20
*form22.width: 500
*form22.height: 82
*form22.defaultButton: "btViewpb"

*btQuitpb.class: pushButton
*btQuitpb.static: true
*btQuitpb.name: btQuitpb
*btQuitpb.parent: form22
*btQuitpb.x: 715
*btQuitpb.y: 15
*btQuitpb.width: 100
*btQuitpb.height: 52
*btQuitpb.labelString: QUITLABEL
*btQuitpb.bottomAttachment: "attach_form"
*btQuitpb.leftAttachment: "attach_position"
*btQuitpb.rightAttachment: "attach_form"
*btQuitpb.rightOffset: 20
*btQuitpb.topAttachment: "attach_form"
*btQuitpb.topOffset: 15
*btQuitpb.bottomOffset: 15
*btQuitpb.activateCallback: {\
#ifndef DESIGN_TIME\
/*\
 * uscita per annullamento backtrack\
 */\
\
printf("QUIT bktk_man: freeze_rest = %d\n",freeze_rest);\
\
if (stato_sim == STATO_REPLAY) {\
   replay_mode (UxWidget,False); /* termina replay */\
}\
uscita_backtrack ((Widget)UxClientData);\
#endif\
}
*btQuitpb.leftPosition: 80
*btQuitpb.activateCallbackClientData: UxGetWidget(backtrackManagement)

*btLoadpb.class: pushButton
*btLoadpb.static: true
*btLoadpb.name: btLoadpb
*btLoadpb.parent: form22
*btLoadpb.x: 20
*btLoadpb.y: 15
*btLoadpb.width: 100
*btLoadpb.height: 52
*btLoadpb.labelString: LOADLABEL
*btLoadpb.bottomAttachment: "attach_form"
*btLoadpb.bottomOffset: 15
*btLoadpb.rightAttachment: "attach_position"
*btLoadpb.rightPosition: 20
*btLoadpb.rightOffset: 0
*btLoadpb.leftAttachment: "attach_form"
*btLoadpb.leftOffset: 20
*btLoadpb.topAttachment: "attach_form"
*btLoadpb.topOffset: 15
*btLoadpb.sensitive: "false"
*btLoadpb.activateCallback: {\
#ifndef DESIGN_TIME\
DragonFlag = 0;   /* interblocco tasto init */\
if (bt_sel > 0)\
   set_colore_riga_bt(bt_sel-1,background_backtrack);\
bt_sel = bt_punt;\
/* disabilito i tasti init ( se attivati prima del tempo danno problemi \
   (non va in freeze)\
 */\
XtVaSetValues (UxGetWidget(btInitpb),XmNsensitive,False, NULL);\
XtVaSetValues (UxGetWidget(BtRcPopupInit), XmNsensitive,False, NULL);\
\
if (!carica_bt ((Widget)UxClientData, punt_rec_bt[bt_sel]+1))\
   {\
   set_colore_riga_bt(bt_sel-1, colore_app[0]);\
   abilita_replay_mode (UxWidget);\
   update_btload (UxWidget,bt_sel);\
   XtVaSetValues (UxGetWidget(btInitpb),XmNsensitive,True,NULL);\
   XtVaSetValues (UxGetWidget(BtRcPopupInit), XmNsensitive,    True,  NULL);\
   }\
else\
   {\
   XtVaSetValues (UxGetWidget(btInitpb),XmNsensitive,False,NULL);\
   XtVaSetValues (UxGetWidget(BtRcPopupInit), XmNsensitive,False, NULL);\
   }\
DragonFlag = 1;   	\
#endif\
}
*btLoadpb.activateCallbackClientData: backtrackManagement

*btInitpb.class: pushButton
*btInitpb.static: true
*btInitpb.name: btInitpb
*btInitpb.parent: form22
*btInitpb.x: 148
*btInitpb.y: 15
*btInitpb.width: 100
*btInitpb.height: 52
*btInitpb.labelString: INITLABEL
*btInitpb.bottomAttachment: "attach_form"
*btInitpb.bottomOffset: 15
*btInitpb.leftAttachment: "attach_widget"
*btInitpb.leftOffset: 20
*btInitpb.leftWidget: "btLoadpb"
*btInitpb.rightAttachment: "attach_position"
*btInitpb.topAttachment: "attach_form"
*btInitpb.topOffset: 15
*btInitpb.sensitive: "false"
*btInitpb.activateCallback: {\
#ifndef DESIGN_TIME\
if (DragonFlag == 1)\
   {\
   btload_ok ((Widget)UxClientData);\
   switch_to_freeze((Widget)UxClientData);\
   bt_interface_active = 0;\
   DistruggiInterfaccia (XtParent((Widget)UxClientData));\
   }\
#endif\
}
*btInitpb.rightPosition: 40
*btInitpb.activateCallbackClientData: UxGetWidget(backtrackManagement)

*btViewpb.class: pushButton
*btViewpb.static: true
*btViewpb.name: btViewpb
*btViewpb.parent: form22
*btViewpb.x: 275
*btViewpb.y: 15
*btViewpb.width: 100
*btViewpb.height: 52
*btViewpb.labelString: VIEWLABEL
*btViewpb.sensitive: "false"
*btViewpb.bottomAttachment: "attach_form"
*btViewpb.bottomOffset: 15
*btViewpb.leftAttachment: "attach_widget"
*btViewpb.leftOffset: 20
*btViewpb.leftWidget: "btInitpb"
*btViewpb.rightAttachment: "attach_position"
*btViewpb.topAttachment: "attach_form"
*btViewpb.topOffset: 15
*btViewpb.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
/**\
sprintf (testo,"BT %d",bt_sel);\
printf ("preview bt n. %d \n",punt_rec_bt[bt_sel]+1);\
create_previewSnap (BT_VIEW, punt_rec_bt[bt_sel]+1, testo);\
**/\
sprintf (testo,"BT %d",bt_punt);\
printf ("preview bt n. %d \n",punt_rec_bt[bt_punt]+1);\
create_previewSnap (BT_VIEW, punt_rec_bt[bt_punt]+1, testo);\
#endif\
}
*btViewpb.rightPosition: 60

*btMenu.class: rowColumn
*btMenu.static: true
*btMenu.name: btMenu
*btMenu.parent: backtrackManagement
*btMenu.rowColumnType: "menu_bar"
*btMenu.menuAccelerator: "<KeyUp>F10"
*btMenu.rightAttachment: "attach_form"
*btMenu.leftAttachment: "attach_form"
*btMenu.menuHelpWidget: "bt_menu_help"

*btMenuFile.class: rowColumn
*btMenuFile.static: true
*btMenuFile.name: btMenuFile
*btMenuFile.parent: btMenu
*btMenuFile.rowColumnType: "menu_pulldown"

*btMenuFilepb.class: pushButton
*btMenuFilepb.static: true
*btMenuFilepb.name: btMenuFilepb
*btMenuFilepb.parent: btMenuFile
*btMenuFilepb.labelString: QuitMenuLabel
*btMenuFilepb.activateCallback: {\
uscita_backtrack (UxGetWidget(backtrackManagement));\
}

*btMenuReplay.class: rowColumn
*btMenuReplay.static: true
*btMenuReplay.name: btMenuReplay
*btMenuReplay.parent: btMenu
*btMenuReplay.rowColumnType: "menu_pulldown"

*btMenuReplayOntb.class: toggleButton
*btMenuReplayOntb.static: true
*btMenuReplayOntb.name: btMenuReplayOntb
*btMenuReplayOntb.parent: btMenuReplay
*btMenuReplayOntb.labelString: "Start Replay"
*btMenuReplayOntb.valueChangedCallback: {\
printf ("replay on\n");\
#ifndef DESIGN_TIME\
SD_replay (BANCO);\
#endif\
}
*btMenuReplayOntb.visibleWhenOff: "true"

*btMenuReplay_b3.class: separator
*btMenuReplay_b3.static: true
*btMenuReplay_b3.name: btMenuReplay_b3
*btMenuReplay_b3.parent: btMenuReplay

*btMenuReplayOfftb.class: toggleButton
*btMenuReplayOfftb.static: true
*btMenuReplayOfftb.name: btMenuReplayOfftb
*btMenuReplayOfftb.parent: btMenuReplay
*btMenuReplayOfftb.labelString: "Stop Replay"
*btMenuReplayOfftb.valueChangedCallback: {\
printf ("replay off\n");\
#ifndef DESIGN_TIME\
SD_backtrack (BANCO);\
#endif\
}
*btMenuReplayOfftb.set: "true"
*btMenuReplayOfftb.visibleWhenOff: "true"

*btMenuModi.class: rowColumn
*btMenuModi.static: true
*btMenuModi.name: btMenuModi
*btMenuModi.parent: btMenu
*btMenuModi.rowColumnType: "menu_pulldown"
*btMenuModi.createManaged: "false"

*btMenuModiFbcb.class: cascadeButton
*btMenuModiFbcb.static: true
*btMenuModiFbcb.name: btMenuModiFbcb
*btMenuModiFbcb.parent: btMenuModi
*btMenuModiFbcb.labelString: "Direction"
*btMenuModiFbcb.subMenuId: "btMenuModiAvind"

*btMenuModiAmcb.class: cascadeButton
*btMenuModiAmcb.static: true
*btMenuModiAmcb.name: btMenuModiAmcb
*btMenuModiAmcb.parent: btMenuModi
*btMenuModiAmcb.labelString: "Auto/Man"
*btMenuModiAmcb.subMenuId: "btMenuModiAutoman"

*btMenuModiAvind.class: rowColumn
*btMenuModiAvind.static: true
*btMenuModiAvind.name: btMenuModiAvind
*btMenuModiAvind.parent: btMenuModi
*btMenuModiAvind.rowColumnType: "menu_pulldown"
*btMenuModiAvind.radioBehavior: "true"

*btMenuModiAvindForwtb.class: toggleButton
*btMenuModiAvindForwtb.static: true
*btMenuModiAvindForwtb.name: btMenuModiAvindForwtb
*btMenuModiAvindForwtb.parent: btMenuModiAvind
*btMenuModiAvindForwtb.labelString: "Forward"
*btMenuModiAvindForwtb.valueChangedCallback: {printf ("direzione avanti\n");}
*btMenuModiAvindForwtb.visibleWhenOff: "true"

*btMenuModiAvindBacktb.class: toggleButton
*btMenuModiAvindBacktb.static: true
*btMenuModiAvindBacktb.name: btMenuModiAvindBacktb
*btMenuModiAvindBacktb.parent: btMenuModiAvind
*btMenuModiAvindBacktb.labelString: "Backward"
*btMenuModiAvindBacktb.valueChangedCallback: {printf ("direzione indietro\n");}
*btMenuModiAvindBacktb.set: "true"
*btMenuModiAvindBacktb.visibleWhenOff: "true"

*btMenuModiAutoman.class: rowColumn
*btMenuModiAutoman.static: true
*btMenuModiAutoman.name: btMenuModiAutoman
*btMenuModiAutoman.parent: btMenuModi
*btMenuModiAutoman.rowColumnType: "menu_pulldown"
*btMenuModiAutoman.radioBehavior: "true"

*btMenuModiAutomanAutotb.class: toggleButton
*btMenuModiAutomanAutotb.static: true
*btMenuModiAutomanAutotb.name: btMenuModiAutomanAutotb
*btMenuModiAutomanAutotb.parent: btMenuModiAutoman
*btMenuModiAutomanAutotb.labelString: "Automatic load"
*btMenuModiAutomanAutotb.valueChangedCallback: {printf ("backtrack auto\n");}
*btMenuModiAutomanAutotb.visibleWhenOff: "true"

*btMenuModiAutomanMan.class: toggleButton
*btMenuModiAutomanMan.static: true
*btMenuModiAutomanMan.name: btMenuModiAutomanMan
*btMenuModiAutomanMan.parent: btMenuModiAutoman
*btMenuModiAutomanMan.labelString: "Manual Load"
*btMenuModiAutomanMan.valueChangedCallback: {printf ("backtrack manuale\n");}
*btMenuModiAutomanMan.set: "true"
*btMenuModiAutomanMan.visibleWhenOff: "true"

*btMenuEdit.class: rowColumn
*btMenuEdit.static: true
*btMenuEdit.name: btMenuEdit
*btMenuEdit.parent: btMenu
*btMenuEdit.rowColumnType: "menu_pulldown"

*btMenuEditRecpb.class: pushButton
*btMenuEditRecpb.static: true
*btMenuEditRecpb.name: btMenuEditRecpb
*btMenuEditRecpb.parent: btMenuEdit
*btMenuEditRecpb.labelString: "Set Record. Freq. ..."
*btMenuEditRecpb.activateCallback: {\
richiesta_timer_bt (backtrackManagement);\
}

*btMenuEditPrespb.class: pushButton
*btMenuEditPrespb.static: true
*btMenuEditPrespb.name: btMenuEditPrespb
*btMenuEditPrespb.parent: btMenuEdit
*btMenuEditPrespb.labelString: "Timer Auto Bt"
*btMenuEditPrespb.activateCallback: {printf ("richiesta timer auto\n");}
*btMenuEditPrespb.createManaged: "false"

*btMenuHelp.class: rowColumn
*btMenuHelp.static: true
*btMenuHelp.name: btMenuHelp
*btMenuHelp.parent: btMenu
*btMenuHelp.rowColumnType: "menu_pulldown"

*btMenuHelppb.class: pushButton
*btMenuHelppb.static: true
*btMenuHelppb.name: btMenuHelppb
*btMenuHelppb.parent: btMenuHelp
*btMenuHelppb.labelString: "Comandi"
*btMenuHelppb.activateCallback: {printf ("help comandi\n");}

*bt_menu_file.class: cascadeButton
*bt_menu_file.static: true
*bt_menu_file.name: bt_menu_file
*bt_menu_file.parent: btMenu
*bt_menu_file.labelString: "File"
*bt_menu_file.subMenuId: "btMenuFile"

*bt_menu_replay.class: cascadeButton
*bt_menu_replay.static: true
*bt_menu_replay.name: bt_menu_replay
*bt_menu_replay.parent: btMenu
*bt_menu_replay.labelString: "Replay"
*bt_menu_replay.subMenuId: "btMenuReplay"
*bt_menu_replay.createManaged: "false"

*bt_menu_mode.class: cascadeButton
*bt_menu_mode.static: true
*bt_menu_mode.name: bt_menu_mode
*bt_menu_mode.parent: btMenu
*bt_menu_mode.labelString: "Mode"
*bt_menu_mode.subMenuId: "btMenuModi"
*bt_menu_mode.createManaged: "false"

*bt_menu_edit.class: cascadeButton
*bt_menu_edit.static: true
*bt_menu_edit.name: bt_menu_edit
*bt_menu_edit.parent: btMenu
*bt_menu_edit.labelString: "Edit"
*bt_menu_edit.subMenuId: "btMenuEdit"

*bt_menu_help.class: cascadeButton
*bt_menu_help.static: true
*bt_menu_help.name: bt_menu_help
*bt_menu_help.parent: btMenu
*bt_menu_help.labelString: "Help"
*bt_menu_help.subMenuId: "btMenuHelp"

*bulletinBoard2.class: bulletinBoard
*bulletinBoard2.static: true
*bulletinBoard2.name: bulletinBoard2
*bulletinBoard2.parent: backtrackManagement
*bulletinBoard2.resizePolicy: "resize_none"
*bulletinBoard2.x: 10
*bulletinBoard2.y: 30
*bulletinBoard2.width: 590
*bulletinBoard2.height: 50
*bulletinBoard2.leftOffset: 0
*bulletinBoard2.rightAttachment: "attach_form"
*bulletinBoard2.leftAttachment: "attach_form"
*bulletinBoard2.topAttachment: "attach_widget"
*bulletinBoard2.topOffset: 0
*bulletinBoard2.topWidget: "btMenu"

*replaySelectionbt.class: toggleButton
*replaySelectionbt.static: true
*replaySelectionbt.name: replaySelectionbt
*replaySelectionbt.parent: bulletinBoard2
*replaySelectionbt.x: 200
*replaySelectionbt.y: 10
*replaySelectionbt.width: 200
*replaySelectionbt.height: 20
*replaySelectionbt.labelString: REPLAY_MODE_LABEL ? REPLAY_MODE_LABEL : "Replay"
*replaySelectionbt.valueChangedCallback: {\
Boolean stato;\
stato = ((XmToggleButtonCallbackStruct *)UxCallbackArg)->set;\
replay_mode (UxWidget, stato);\
}
*replaySelectionbt.sensitive: "false"

*replaySelectionLabel.class: label
*replaySelectionLabel.static: true
*replaySelectionLabel.name: replaySelectionLabel
*replaySelectionLabel.parent: bulletinBoard2
*replaySelectionLabel.x: 90
*replaySelectionLabel.y: 30
*replaySelectionLabel.width: 310
*replaySelectionLabel.height: 20
*replaySelectionLabel.labelString: ""

*btLoadLabel.class: label
*btLoadLabel.static: true
*btLoadLabel.name: btLoadLabel
*btLoadLabel.parent: bulletinBoard2
*btLoadLabel.x: 50
*btLoadLabel.y: 10
*btLoadLabel.width: 100
*btLoadLabel.height: 20
*btLoadLabel.labelString: BT_ACT_LOAD
*btLoadLabel.alignment: "alignment_end"

*btLoadNumber.class: label
*btLoadNumber.static: true
*btLoadNumber.name: btLoadNumber
*btLoadNumber.parent: bulletinBoard2
*btLoadNumber.x: 150
*btLoadNumber.y: 10
*btLoadNumber.width: 40
*btLoadNumber.height: 20
*btLoadNumber.labelString: "0"

*backtrackScrollW.class: scrolledWindow
*backtrackScrollW.static: true
*backtrackScrollW.name: backtrackScrollW
*backtrackScrollW.parent: backtrackManagement
*backtrackScrollW.scrollingPolicy: "automatic"
*backtrackScrollW.x: 15
*backtrackScrollW.y: 91
*backtrackScrollW.width: 385
*backtrackScrollW.height: 416
*backtrackScrollW.rightAttachment: "attach_form"
*backtrackScrollW.rightOffset: 15
*backtrackScrollW.leftAttachment: "attach_form"
*backtrackScrollW.leftOffset: 15
*backtrackScrollW.topAttachment: "attach_widget"
*backtrackScrollW.topOffset: 10
*backtrackScrollW.topWidget: "bulletinBoard2"
*backtrackScrollW.bottomAttachment: "attach_widget"
*backtrackScrollW.bottomOffset: 15
*backtrackScrollW.bottomWidget: "frame15"
*backtrackScrollW.topPosition: 0

*BtRc.class: rowColumn
*BtRc.static: true
*BtRc.name: BtRc
*BtRc.parent: backtrackScrollW
*BtRc.x: 2
*BtRc.y: 2
*BtRc.width: 350
*BtRc.height: 400

*menu5.class: rowColumn
*menu5.static: true
*menu5.name: menu5
*menu5.parent: BtRc
*menu5.rowColumnType: "menu_popup"
*menu5.menuAccelerator: "Shift <KeyUp>F10"

*BtRcPopupView.class: pushButton
*BtRcPopupView.static: true
*BtRcPopupView.name: BtRcPopupView
*BtRcPopupView.parent: menu5
*BtRcPopupView.labelString: ViewMenuLabel
*BtRcPopupView.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
/**\
printf ("preview bt n. %d (popup)\n",bt_sel);\
sprintf (testo,"BT %d",bt_sel);\
create_previewSnap(BT_VIEW,punt_rec_bt[bt_sel]+1,testo);\
**/\
printf ("preview bt n. %d (popup)\n",bt_punt);\
sprintf (testo,"BT %d",bt_punt);\
create_previewSnap(BT_VIEW,punt_rec_bt[bt_punt]+1,testo);\
#endif\
}
*BtRcPopupView.sensitive: "false"

*menu5_p1_b5.class: separator
*menu5_p1_b5.static: true
*menu5_p1_b5.name: menu5_p1_b5
*menu5_p1_b5.parent: menu5

*BtRcPopupLoad.class: pushButton
*BtRcPopupLoad.static: true
*BtRcPopupLoad.name: BtRcPopupLoad
*BtRcPopupLoad.parent: menu5
*BtRcPopupLoad.labelString: LoadMenuLabel
*BtRcPopupLoad.activateCallback: {\
#ifndef DESIGN_TIME\
DragonFlag = 0;   /* interblocco tasto init */\
if (bt_sel > 0)\
   set_colore_riga_bt(bt_sel-1,background_backtrack);\
bt_sel = bt_punt;\
if (!carica_bt (UxGetWidget(backtrackManagement), punt_rec_bt[bt_sel]+1))\
   {\
   set_colore_riga_bt(bt_sel-1, colore_app[0]);\
   abilita_replay_mode (UxWidget);\
   update_btload (UxWidget,bt_sel);\
   XtVaSetValues (UxGetWidget(btInitpb), XmNsensitive,    True,  NULL);\
   XtVaSetValues (UxGetWidget(BtRcPopupInit), XmNsensitive,    True,  NULL);\
   }\
else\
   {\
   XtVaSetValues (UxGetWidget(btInitpb), XmNsensitive,    False, NULL);\
   XtVaSetValues (UxGetWidget(BtRcPopupInit), XmNsensitive,    False, NULL);\
   }\
DragonFlag = 1;   	   	\
#endif\
}
*BtRcPopupLoad.sensitive: "false"

*BtRcPopupInit.class: pushButton
*BtRcPopupInit.static: true
*BtRcPopupInit.name: BtRcPopupInit
*BtRcPopupInit.parent: menu5
*BtRcPopupInit.labelString: InitMenuLabel
*BtRcPopupInit.activateCallback: {\
#ifndef DESIGN_TIME\
if (DragonFlag == 1)\
   {\
   btload_ok ((Widget)UxClientData);\
   switch_to_freeze((Widget)UxClientData);\
   bt_interface_active = 0;\
   DistruggiInterfaccia (XtParent((Widget)UxClientData));\
   }\
#endif\
}
*BtRcPopupInit.sensitive: "false"
*BtRcPopupInit.activateCallbackClientData: UxGetWidget(backtrackManagement)

*menu5_p1_b6.class: separator
*menu5_p1_b6.static: true
*menu5_p1_b6.name: menu5_p1_b6
*menu5_p1_b6.parent: menu5

*BtRcPopupQuit.class: pushButton
*BtRcPopupQuit.static: true
*BtRcPopupQuit.name: BtRcPopupQuit
*BtRcPopupQuit.parent: menu5
*BtRcPopupQuit.labelString: QuitMenuLabel
*BtRcPopupQuit.activateCallback: {\
#ifndef DESIGN_TIME\
/*\
 * uscita per annullamento backtrack\
 */\
if (stato_sim == STATO_REPLAY)\
   replay_mode (UxWidget,False); /* termina replay */\
uscita_backtrack (UxGetWidget(backtrackManagement));\
#endif\
}

