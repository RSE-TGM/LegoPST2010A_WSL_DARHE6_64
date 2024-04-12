! UIMX ascii 2.5 key: 4299                                                      

*editPert.class: formDialog
*editPert.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
XtIntervalId timer_editPert;\
int editPertRate = 3;      /* in secondi */\
#include "messaggi.h"\
extern int edit_pert_interface_active;\
extern int _MAX_PERTUR;\
TIPO_PERT *perturbazioni;\
TIPO_PERT *perturbazioni_old;
*editPert.ispecdecl:
*editPert.funcdecl: swidget create_editPert(UxParent)\
swidget UxParent;
*editPert.funcname: create_editPert
*editPert.funcdef: "swidget", "<create_editPert>(%)"
*editPert.argdecl: swidget UxParent;
*editPert.arglist: UxParent
*editPert.arglist.UxParent: "swidget", "%UxParent%"
*editPert.icode: edit_pert_interface_active = 1;\
perturbazioni = (TIPO_PERT *)malloc (sizeof(TIPO_PERT)*_MAX_PERTUR*2);\
perturbazioni_old = (TIPO_PERT *)malloc (sizeof(TIPO_PERT)*_MAX_PERTUR*2);
*editPert.fcode: leggiPert();\
memcpy (perturbazioni_old,perturbazioni,sizeof(TIPO_PERT)*_MAX_PERTUR*2);\
displayPert (rtrn);\
updateEditPertLabel (editPertFreqUpdateLabel);\
attiva_timer_editPert (UxGetWidget(rtrn));\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*editPert.auxdecl: int uscita_editPert ()\
{\
edit_pert_interface_active = 0;\
free (perturbazioni);\
free (perturbazioni_old);\
stop_timer (timer_editPert);\
DistruggiInterfaccia (XtParent(editPert));\
}\
/******************************************************/\
int leggiPert ()\
{\
   if (SD_editpert (BANCO, perturbazioni,0,_MAX_PERTUR) > 0)\
      fprintf (stderr,"PERT ricevute\n");\
   else\
      fprintf (stderr,"PERT *** ERRORE ricezione PERT ***\n");\
   return (0);\
}\
/******************************************************/\

*editPert.name.source: public
*editPert.static: false
*editPert.name: editPert
*editPert.parent: NO_PARENT
*editPert.defaultShell: topLevelShell
*editPert.unitType: "pixels"
*editPert.x: 410
*editPert.y: 320
*editPert.width: 600
*editPert.height: 560

*editPertMenu.class: rowColumn
*editPertMenu.static: true
*editPertMenu.name: editPertMenu
*editPertMenu.parent: editPert
*editPertMenu.rowColumnType: "menu_bar"
*editPertMenu.rightAttachment: "attach_form"
*editPertMenu.leftAttachment: "attach_form"
*editPertMenu.menuAccelerator: "<KeyUp>F10"

*editPertMenuFile.class: rowColumn
*editPertMenuFile.static: true
*editPertMenuFile.name: editPertMenuFile
*editPertMenuFile.parent: editPertMenu
*editPertMenuFile.rowColumnType: "menu_pulldown"

*editPertMenuFileQuit.class: pushButton
*editPertMenuFileQuit.static: true
*editPertMenuFileQuit.name: editPertMenuFileQuit
*editPertMenuFileQuit.parent: editPertMenuFile
*editPertMenuFileQuit.labelString: "Quit"
*editPertMenuFileQuit.activateCallback: {\
uscita_editPert();\
}

*editPertMenuEdit.class: rowColumn
*editPertMenuEdit.static: true
*editPertMenuEdit.name: editPertMenuEdit
*editPertMenuEdit.parent: editPertMenu
*editPertMenuEdit.rowColumnType: "menu_pulldown"

*editPertMenuEditTimer.class: pushButton
*editPertMenuEditTimer.static: true
*editPertMenuEditTimer.name: editPertMenuEditTimer
*editPertMenuEditTimer.parent: editPertMenuEdit
*editPertMenuEditTimer.labelString: "Set Timer ..."
*editPertMenuEditTimer.activateCallback: {\
richiesta_editPertRate (editPert);\
updateEditPertLabel (editPertFreqUpdateLabel);\
}

*menu10_top_b1.class: cascadeButton
*menu10_top_b1.static: true
*menu10_top_b1.name: menu10_top_b1
*menu10_top_b1.parent: editPertMenu
*menu10_top_b1.labelString: "File"
*menu10_top_b1.subMenuId: "editPertMenuFile"

*menu10_top_b2.class: cascadeButton
*menu10_top_b2.static: true
*menu10_top_b2.name: menu10_top_b2
*menu10_top_b2.parent: editPertMenu
*menu10_top_b2.labelString: "Edit"
*menu10_top_b2.subMenuId: "editPertMenuEdit"

*frameComm.class: frame
*frameComm.static: true
*frameComm.name: frameComm
*frameComm.parent: editPert
*frameComm.x: 48
*frameComm.y: 288
*frameComm.width: 690
*frameComm.height: 80
*frameComm.bottomAttachment: "attach_form"
*frameComm.leftOffset: 0
*frameComm.rightAttachment: "attach_form"
*frameComm.leftAttachment: "attach_form"

*form53.class: form
*form53.static: true
*form53.name: form53
*form53.parent: frameComm
*form53.resizePolicy: "resize_none"
*form53.x: 2
*form53.y: 20
*form53.width: 851
*form53.height: 82
*form53.defaultButton: ""
*form53.unmapCallback: {\
\
}

*editPertQuitpb.class: pushButton
*editPertQuitpb.static: true
*editPertQuitpb.name: editPertQuitpb
*editPertQuitpb.parent: form53
*editPertQuitpb.x: 240
*editPertQuitpb.y: 10
*editPertQuitpb.width: 100
*editPertQuitpb.height: 52
*editPertQuitpb.labelString: "QUIT"
*editPertQuitpb.bottomAttachment: "attach_form"
*editPertQuitpb.leftAttachment: "attach_position"
*editPertQuitpb.rightAttachment: "attach_position"
*editPertQuitpb.rightOffset: 0
*editPertQuitpb.topAttachment: "attach_form"
*editPertQuitpb.topOffset: 15
*editPertQuitpb.bottomOffset: 15
*editPertQuitpb.activateCallback: {\
uscita_editPert ();\
\
}
*editPertQuitpb.activateCallbackClientData: UxGetWidget(editPert)
*editPertQuitpb.leftPosition: 40
*editPertQuitpb.leftOffset: 0
*editPertQuitpb.rightPosition: 60

*panedWindow3.class: panedWindow
*panedWindow3.static: true
*panedWindow3.name: panedWindow3
*panedWindow3.parent: editPert
*panedWindow3.x: 110
*panedWindow3.y: 130
*panedWindow3.width: 360
*panedWindow3.height: 260
*panedWindow3.bottomAttachment: "attach_widget"
*panedWindow3.bottomWidget: "frameComm"
*panedWindow3.leftOffset: 0
*panedWindow3.rightAttachment: "attach_form"
*panedWindow3.topAttachment: "attach_widget"
*panedWindow3.topWidget: "editPertMenu"
*panedWindow3.leftAttachment: "attach_form"

*form54.class: form
*form54.static: true
*form54.name: form54
*form54.parent: panedWindow3
*form54.resizePolicy: "resize_none"
*form54.x: 70
*form54.y: 50
*form54.width: 380
*form54.height: 130
*form54.paneMinimum: 200

*editPertAttScrollWin.class: scrolledWindow
*editPertAttScrollWin.static: true
*editPertAttScrollWin.name: editPertAttScrollWin
*editPertAttScrollWin.parent: form54
*editPertAttScrollWin.scrollingPolicy: "application_defined"
*editPertAttScrollWin.x: 0
*editPertAttScrollWin.y: 30
*editPertAttScrollWin.visualPolicy: "variable"
*editPertAttScrollWin.scrollBarDisplayPolicy: "static"
*editPertAttScrollWin.shadowThickness: 0
*editPertAttScrollWin.width: 180
*editPertAttScrollWin.bottomAttachment: "attach_form"
*editPertAttScrollWin.bottomOffset: 5
*editPertAttScrollWin.leftOffset: 5
*editPertAttScrollWin.rightAttachment: "attach_form"
*editPertAttScrollWin.rightOffset: 5
*editPertAttScrollWin.leftAttachment: "attach_form"
*editPertAttScrollWin.topAttachment: "attach_form"
*editPertAttScrollWin.topOffset: 30

*editPertAttScrollList.class: scrolledList
*editPertAttScrollList.static: true
*editPertAttScrollList.name: editPertAttScrollList
*editPertAttScrollList.parent: editPertAttScrollWin
*editPertAttScrollList.width: 170
*editPertAttScrollList.height: 115
*editPertAttScrollList.singleSelectionCallback: {\
\
}
*editPertAttScrollList.automaticSelection: "true"
*editPertAttScrollList.selectionPolicy: "single_select"

*label12.class: label
*label12.static: true
*label12.name: label12
*label12.parent: form54
*label12.x: 10
*label12.y: 0
*label12.width: 190
*label12.height: 30
*label12.bottomAttachment: "attach_widget"
*label12.bottomOffset: 2
*label12.bottomWidget: "editPertAttScrollWin"
*label12.leftOffset: 5
*label12.topAttachment: "attach_form"
*label12.topOffset: 2
*label12.alignment: "alignment_beginning"
*label12.labelString: ACT_PERT_LABEL

*editPertFreqUpdateLabel.class: label
*editPertFreqUpdateLabel.static: true
*editPertFreqUpdateLabel.name: editPertFreqUpdateLabel
*editPertFreqUpdateLabel.parent: form54
*editPertFreqUpdateLabel.x: 10
*editPertFreqUpdateLabel.y: 0
*editPertFreqUpdateLabel.width: 190
*editPertFreqUpdateLabel.height: 30
*editPertFreqUpdateLabel.alignment: "alignment_beginning"
*editPertFreqUpdateLabel.bottomAttachment: "attach_widget"
*editPertFreqUpdateLabel.bottomOffset: 2
*editPertFreqUpdateLabel.bottomWidget: "editPertAttScrollWin"
*editPertFreqUpdateLabel.leftAttachment: "attach_none"
*editPertFreqUpdateLabel.leftOffset: 0
*editPertFreqUpdateLabel.rightAttachment: "attach_form"
*editPertFreqUpdateLabel.rightOffset: 20
*editPertFreqUpdateLabel.topAttachment: "attach_form"
*editPertFreqUpdateLabel.topOffset: 2
*editPertFreqUpdateLabel.labelString: PERT_FREQ_UPD

*form55.class: form
*form55.static: true
*form55.name: form55
*form55.parent: panedWindow3
*form55.resizePolicy: "resize_none"
*form55.x: 70
*form55.y: 50
*form55.width: 380
*form55.height: 130

*editPertUnattScrollWin.class: scrolledWindow
*editPertUnattScrollWin.static: true
*editPertUnattScrollWin.name: editPertUnattScrollWin
*editPertUnattScrollWin.parent: form55
*editPertUnattScrollWin.scrollingPolicy: "application_defined"
*editPertUnattScrollWin.x: 0
*editPertUnattScrollWin.y: 30
*editPertUnattScrollWin.visualPolicy: "variable"
*editPertUnattScrollWin.scrollBarDisplayPolicy: "static"
*editPertUnattScrollWin.shadowThickness: 0
*editPertUnattScrollWin.width: 180
*editPertUnattScrollWin.rightAttachment: "attach_form"
*editPertUnattScrollWin.rightOffset: 5
*editPertUnattScrollWin.leftAttachment: "attach_form"
*editPertUnattScrollWin.leftOffset: 5
*editPertUnattScrollWin.bottomAttachment: "attach_form"
*editPertUnattScrollWin.bottomOffset: 5
*editPertUnattScrollWin.topAttachment: "attach_form"
*editPertUnattScrollWin.topOffset: 30

*editPertUnattScrollList.class: scrolledList
*editPertUnattScrollList.static: true
*editPertUnattScrollList.name: editPertUnattScrollList
*editPertUnattScrollList.parent: editPertUnattScrollWin
*editPertUnattScrollList.width: 170
*editPertUnattScrollList.height: 115
*editPertUnattScrollList.singleSelectionCallback: {\
\
}
*editPertUnattScrollList.automaticSelection: "true"
*editPertUnattScrollList.selectionPolicy: "single_select"

*label14.class: label
*label14.static: true
*label14.name: label14
*label14.parent: form55
*label14.x: 10
*label14.y: 0
*label14.width: 190
*label14.height: 30
*label14.bottomAttachment: "attach_widget"
*label14.bottomOffset: 2
*label14.bottomWidget: "editPertUnattScrollWin"
*label14.topAttachment: "attach_form"
*label14.topOffset: 2
*label14.leftOffset: 5
*label14.alignment: "alignment_beginning"
*label14.labelString: UNACT_PERT_LABEL

