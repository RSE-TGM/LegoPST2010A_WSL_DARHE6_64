! UIMX ascii 2.5 key: 2932                                                      

*archiveSavereq.class: form
*archiveSavereq.gbldecl: #include <stdio.h>\
#include <Xm/Text.h>\
\
#ifndef DESIGN_TIME\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include <stdlib.h>\
#include <math.h>\
#include "archivi.h"\
/* #include "interf_attive.h" */\
extern int archsave_interface_active;\
#endif\

*archiveSavereq.ispecdecl:
*archiveSavereq.funcdecl: swidget create_archiveSavereq()\

*archiveSavereq.funcname: create_archiveSavereq
*archiveSavereq.funcdef: "swidget", "<create_archiveSavereq>(%)"
*archiveSavereq.icode: printf ("colloquio archive editing\n");
*archiveSavereq.fcode: #ifndef DESIGN_TIME\
init_dati ();\
archsave_interface_active = 1;\
#endif                \
UxPopupInterface (archiveSavereq, no_grab);\
return(rtrn);\

*archiveSavereq.auxdecl: /*********************************************/\
#ifndef DESIGN_TIME\
int init_dati()\
{\
char stringa[10];\
\
   disco_libero = free_disk();\
   sprintf (stringa,"%d",disco_libero);\
   XmTextSetString (UxGetWidget(archSaveReqDiskavailText),stringa); \
   return(0);\
}\
#endif
*archiveSavereq.name.source: public
*archiveSavereq.static: false
*archiveSavereq.name: archiveSavereq
*archiveSavereq.parent: NO_PARENT
*archiveSavereq.defaultShell: topLevelShell
*archiveSavereq.resizePolicy: "resize_none"
*archiveSavereq.unitType: "pixels"
*archiveSavereq.x: 689
*archiveSavereq.y: 150
*archiveSavereq.width: 418
*archiveSavereq.height: 429
*archiveSavereq.noResize: "true"

*form14.class: form
*form14.static: true
*form14.name: form14
*form14.parent: archiveSavereq
*form14.resizePolicy: "resize_none"
*form14.x: 16
*form14.y: 108
*form14.width: 750
*form14.height: 75
*form14.bottomAttachment: "attach_form"
*form14.leftOffset: 0
*form14.rightAttachment: "attach_form"
*form14.topAttachment: "attach_none"
*form14.topOffset: 0
*form14.leftAttachment: "attach_form"

*frame5.class: frame
*frame5.static: true
*frame5.name: frame5
*frame5.parent: form14
*frame5.x: 10
*frame5.y: 405
*frame5.width: 795
*frame5.height: 50
*frame5.bottomAttachment: "attach_form"
*frame5.leftOffset: 0
*frame5.rightAttachment: "attach_form"
*frame5.topOffset: 0
*frame5.leftAttachment: "attach_form"
*frame5.topAttachment: "attach_form"

*form15.class: form
*form15.static: true
*form15.name: form15
*form15.parent: frame5
*form15.resizePolicy: "resize_none"
*form15.x: 0
*form15.y: 0
*form15.width: 745
*form15.height: 75

*archSaveReqQuitpb.class: pushButton
*archSaveReqQuitpb.static: true
*archSaveReqQuitpb.name: archSaveReqQuitpb
*archSaveReqQuitpb.parent: form15
*archSaveReqQuitpb.x: 493
*archSaveReqQuitpb.y: 35
*archSaveReqQuitpb.width: 202
*archSaveReqQuitpb.height: 30
*archSaveReqQuitpb.labelString: "QUIT"
*archSaveReqQuitpb.bottomAttachment: "attach_form"
*archSaveReqQuitpb.leftAttachment: "attach_self"
*archSaveReqQuitpb.rightAttachment: "attach_form"
*archSaveReqQuitpb.bottomOffset: 15
*archSaveReqQuitpb.rightOffset: 20
*archSaveReqQuitpb.leftPosition: 0
*archSaveReqQuitpb.leftOffset: 100
*archSaveReqQuitpb.topAttachment: "attach_form"
*archSaveReqQuitpb.topOffset: 15
*archSaveReqQuitpb.activateCallback: {\
#ifndef DESIGN_TIME\
archsave_interface_active = 0;\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
#endif\
\
\
}
*archSaveReqQuitpb.activateCallbackClientData: UxGetWidget(archiveSavereq)

*archSaveReqpb.class: pushButton
*archSaveReqpb.static: true
*archSaveReqpb.name: archSaveReqpb
*archSaveReqpb.parent: form15
*archSaveReqpb.x: 30
*archSaveReqpb.y: 405
*archSaveReqpb.width: 205
*archSaveReqpb.height: 30
*archSaveReqpb.labelString: "SAVE"
*archSaveReqpb.bottomAttachment: "attach_form"
*archSaveReqpb.bottomOffset: 15
*archSaveReqpb.leftOffset: 20
*archSaveReqpb.rightAttachment: "attach_self"
*archSaveReqpb.rightOffset: 100
*archSaveReqpb.leftAttachment: "attach_form"
*archSaveReqpb.topAttachment: "attach_form"
*archSaveReqpb.topOffset: 15
*archSaveReqpb.activateCallback: {\
#ifndef DESIGN_TIME\
char testo[20];\
\
archsavetinit = 0.0;\
archsavetfin = 0.0;\
\
if (read_txt (UxGetWidget(archSaveReqTinitText),testo))\
   {\
   printf ("testo 1 non valido\n");\
   strcpy (testo,"0.0");\
   write_txt(UxGetWidget(archSaveReqTinitText),testo);\
   }\
archsavetinit = (float)atof(testo);\
printf ("testo = %s %f\n",testo,archsavetinit);\
\
if (read_txt (UxGetWidget(archSaveReqTfinText),testo))\
   {\
   printf ("testo 2 non valido\n");\
   strcpy (testo,"0.0");\
   write_txt(UxGetWidget(archSaveReqTfinText),testo);\
   }\
archsavetfin = (float)atof(testo);\
printf ("testo = %s %f\n",testo,archsavetfin);\
\
disco_libero = free_disk();\
sprintf (testo,"%d",disco_libero);\
write_txt(UxGetWidget(archSaveReqDiskavailText),testo);\
\
read_txt (UxGetWidget(archSaveReqCommText),testo);\
strcpy (comm_arch_save, testo);\
\
if (!check_data_save_req())\
   {\
   richiesta_save_arch();\
   printf ("save ok\n");\
   }\
else\
   {\
   printf ("save no\n");\
   }\
#endif\
}

*frame6.class: frame
*frame6.static: true
*frame6.name: frame6
*frame6.parent: archiveSavereq
*frame6.x: 0
*frame6.y: 265
*frame6.width: 415
*frame6.height: 85
*frame6.bottomAttachment: "attach_widget"
*frame6.bottomWidget: "form14"
*frame6.rightAttachment: "attach_form"
*frame6.leftAttachment: "attach_form"

*form13.class: form
*form13.static: true
*form13.name: form13
*form13.parent: frame6
*form13.resizePolicy: "resize_none"
*form13.x: 0
*form13.y: 305
*form13.width: 420
*form13.height: 74
*form13.marginHeight: 0
*form13.marginWidth: 0
*form13.rubberPositioning: "false"
*form13.dialogTitle: ""

*label13.class: label
*label13.static: true
*label13.name: label13
*label13.parent: form13
*label13.x: 20
*label13.y: 5
*label13.width: 285
*label13.height: 25
*label13.labelString: "Comment:"
*label13.alignment: "alignment_beginning"

*archSaveReqCommText.class: textField
*archSaveReqCommText.static: true
*archSaveReqCommText.name: archSaveReqCommText
*archSaveReqCommText.parent: form13
*archSaveReqCommText.x: 20
*archSaveReqCommText.y: 35
*archSaveReqCommText.width: 378
*archSaveReqCommText.height: 30
*archSaveReqCommText.leftOffset: 20
*archSaveReqCommText.rightAttachment: "attach_form"
*archSaveReqCommText.rightOffset: 20
*archSaveReqCommText.leftAttachment: "attach_form"
*archSaveReqCommText.text: ""
*archSaveReqCommText.topAttachment: "attach_widget"
*archSaveReqCommText.topOffset: 0
*archSaveReqCommText.topWidget: "label13"
*archSaveReqCommText.bottomAttachment: "attach_form"
*archSaveReqCommText.bottomOffset: 10

*archSaveReqMenu.class: rowColumn
*archSaveReqMenu.static: true
*archSaveReqMenu.name: archSaveReqMenu
*archSaveReqMenu.parent: archiveSavereq
*archSaveReqMenu.rowColumnType: "menu_bar"
*archSaveReqMenu.rightAttachment: "attach_form"
*archSaveReqMenu.leftAttachment: "attach_form"
*archSaveReqMenu.menuHelpWidget: "archSaveReqMenuHelpcb"
*archSaveReqMenu.menuAccelerator: "<KeyUp>F10"

*archSaveMenuFile.class: rowColumn
*archSaveMenuFile.static: true
*archSaveMenuFile.name: archSaveMenuFile
*archSaveMenuFile.parent: archSaveReqMenu
*archSaveMenuFile.rowColumnType: "menu_pulldown"

*archSaveMenuFileQuit.class: pushButton
*archSaveMenuFileQuit.static: true
*archSaveMenuFileQuit.name: archSaveMenuFileQuit
*archSaveMenuFileQuit.parent: archSaveMenuFile
*archSaveMenuFileQuit.labelString: "Quit"
*archSaveMenuFileQuit.activateCallback: {\
#ifndef DESIGN_TIME\
archsave_interface_active = 0;\
XtDestroyWidget(XtParent(UxGetWidget(archiveSavereq)));\
#endif\
}

*archSaveReqMenuHelp.class: rowColumn
*archSaveReqMenuHelp.static: true
*archSaveReqMenuHelp.name: archSaveReqMenuHelp
*archSaveReqMenuHelp.parent: archSaveReqMenu
*archSaveReqMenuHelp.rowColumnType: "menu_pulldown"

*archSaveReqMenuHelpComm.class: pushButton
*archSaveReqMenuHelpComm.static: true
*archSaveReqMenuHelpComm.name: archSaveReqMenuHelpComm
*archSaveReqMenuHelpComm.parent: archSaveReqMenuHelp
*archSaveReqMenuHelpComm.labelString: "Command"
*archSaveReqMenuHelpComm.activateCallback.source: public
*archSaveReqMenuHelpComm.activateCallback: 

*archSaveReqMenuFilecb.class: cascadeButton
*archSaveReqMenuFilecb.static: true
*archSaveReqMenuFilecb.name: archSaveReqMenuFilecb
*archSaveReqMenuFilecb.parent: archSaveReqMenu
*archSaveReqMenuFilecb.labelString: "File"
*archSaveReqMenuFilecb.subMenuId: "archSaveMenuFile"

*archSaveReqMenuHelpcb.class: cascadeButton
*archSaveReqMenuHelpcb.static: true
*archSaveReqMenuHelpcb.name: archSaveReqMenuHelpcb
*archSaveReqMenuHelpcb.parent: archSaveReqMenu
*archSaveReqMenuHelpcb.labelString: "Help"
*archSaveReqMenuHelpcb.subMenuId: "archSaveReqMenuHelp"

*rowColumn2.class: rowColumn
*rowColumn2.static: true
*rowColumn2.name: rowColumn2
*rowColumn2.parent: archiveSavereq
*rowColumn2.x: 0
*rowColumn2.y: 25
*rowColumn2.width: 418
*rowColumn2.height: 440
*rowColumn2.rightAttachment: "attach_form"
*rowColumn2.rightOffset: 0
*rowColumn2.leftAttachment: "attach_form"
*rowColumn2.bottomAttachment: "attach_widget"
*rowColumn2.bottomWidget: "frame6"
*rowColumn2.topAttachment: "attach_widget"
*rowColumn2.topWidget: "archSaveReqMenu"
*rowColumn2.topOffset: 20

*form16.class: form
*form16.static: true
*form16.name: form16
*form16.parent: rowColumn2
*form16.resizePolicy: "resize_none"
*form16.x: 5
*form16.y: 5
*form16.width: 485
*form16.height: 45
*form16.fractionBase: 10

*label15.class: label
*label15.static: true
*label15.name: label15
*label15.parent: form16
*label15.x: 0
*label15.y: 15
*label15.width: 150
*label15.height: 25
*label15.rightAttachment: "attach_position"
*label15.rightPosition: 3
*label15.topOffset: 0
*label15.leftAttachment: "attach_form"
*label15.bottomAttachment: "attach_form"
*label15.topAttachment: "attach_form"
*label15.labelString: "Initial time:"
*label15.alignment: "alignment_end"

*archSaveReqTinitText.class: textField
*archSaveReqTinitText.static: true
*archSaveReqTinitText.name: archSaveReqTinitText
*archSaveReqTinitText.parent: form16
*archSaveReqTinitText.x: 165
*archSaveReqTinitText.y: 10
*archSaveReqTinitText.width: 227
*archSaveReqTinitText.height: 35
*archSaveReqTinitText.rightAttachment: "attach_form"
*archSaveReqTinitText.leftAttachment: "attach_position"
*archSaveReqTinitText.leftPosition: 4
*archSaveReqTinitText.rightOffset: 20
*archSaveReqTinitText.bottomAttachment: "attach_none"
*archSaveReqTinitText.topAttachment: "attach_none"
*archSaveReqTinitText.text: ""
*archSaveReqTinitText.activateCallback: {\
#ifndef DESIGN_TIME\
char testo[MAX_LUN_COMMENTO];\
   if (read_txt(UxWidget,testo))\
      {\
      printf ("entry non corretta \n");\
      strcpy (testo,"0.0");\
      write_txt(UxWidget,testo);\
      }\
#endif\
}
*archSaveReqTinitText.losingFocusCallback: {\
#ifndef DESIGN_TIME\
char testo[MAX_LUN_COMMENTO];\
   if (read_txt(UxWidget,testo))\
      {\
      printf ("entry non corretta \n");\
      strcpy (testo,"0.0");\
      write_txt(UxWidget,testo);\
      }\
#endif\
}

*form17.class: form
*form17.static: true
*form17.name: form17
*form17.parent: rowColumn2
*form17.resizePolicy: "resize_none"
*form17.x: 13
*form17.y: 13
*form17.width: 485
*form17.height: 45
*form17.fractionBase: 10

*label16.class: label
*label16.static: true
*label16.name: label16
*label16.parent: form17
*label16.x: 0
*label16.y: 10
*label16.width: 150
*label16.height: 25
*label16.rightAttachment: "attach_position"
*label16.rightPosition: 3
*label16.topOffset: 0
*label16.leftAttachment: "attach_form"
*label16.bottomAttachment: "attach_form"
*label16.topAttachment: "attach_form"
*label16.labelString: "Final time:"
*label16.alignment: "alignment_end"

*archSaveReqTfinText.class: textField
*archSaveReqTfinText.static: true
*archSaveReqTfinText.name: archSaveReqTfinText
*archSaveReqTfinText.parent: form17
*archSaveReqTfinText.x: 165
*archSaveReqTfinText.y: 10
*archSaveReqTfinText.width: 227
*archSaveReqTfinText.height: 35
*archSaveReqTfinText.rightAttachment: "attach_form"
*archSaveReqTfinText.leftAttachment: "attach_position"
*archSaveReqTfinText.leftPosition: 4
*archSaveReqTfinText.rightOffset: 20
*archSaveReqTfinText.text: ""
*archSaveReqTfinText.activateCallback: {\
#ifndef DESIGN_TIME\
char testo[MAX_LUN_COMMENTO];\
   if (read_txt(UxWidget,testo))\
      {\
      printf ("entry non corretta \n"); \
      strcpy (testo,"0.0");\
      write_txt(UxWidget,testo);\
\
      }\
#endif\
}
*archSaveReqTfinText.losingFocusCallback: {\
#ifndef DESIGN_TIME\
char testo[MAX_LUN_COMMENTO];\
   if (read_txt(UxWidget,testo))\
      {\
      printf ("entry non corretta \n");\
      strcpy (testo,"0.0");\
      write_txt(UxWidget,testo);\
      }\
#endif\
}

*form18.class: form
*form18.static: true
*form18.name: form18
*form18.parent: rowColumn2
*form18.resizePolicy: "resize_none"
*form18.x: 13
*form18.y: 61
*form18.width: 485
*form18.height: 45
*form18.fractionBase: 10

*label17.class: label
*label17.static: true
*label17.name: label17
*label17.parent: form18
*label17.x: 5
*label17.y: 10
*label17.width: 150
*label17.height: 25
*label17.rightAttachment: "attach_position"
*label17.rightPosition: 3
*label17.topOffset: 0
*label17.leftAttachment: "attach_form"
*label17.bottomAttachment: "attach_form"
*label17.topAttachment: "attach_form"
*label17.labelString: "Required disk:"
*label17.alignment: "alignment_end"

*archSaveReqDiskText.class: textField
*archSaveReqDiskText.static: true
*archSaveReqDiskText.name: archSaveReqDiskText
*archSaveReqDiskText.parent: form18
*archSaveReqDiskText.x: 165
*archSaveReqDiskText.y: 10
*archSaveReqDiskText.width: 227
*archSaveReqDiskText.height: 35
*archSaveReqDiskText.rightAttachment: "attach_form"
*archSaveReqDiskText.leftAttachment: "attach_position"
*archSaveReqDiskText.leftPosition: 4
*archSaveReqDiskText.rightOffset: 20
*archSaveReqDiskText.editable: "false"
*archSaveReqDiskText.cursorPositionVisible: "false"
*archSaveReqDiskText.text: ""

*form19.class: form
*form19.static: true
*form19.name: form19
*form19.parent: rowColumn2
*form19.resizePolicy: "resize_any"
*form19.x: 5
*form19.y: 220
*form19.width: 412
*form19.height: 48
*form19.fractionBase: 10

*label18.class: label
*label18.static: true
*label18.name: label18
*label18.parent: form19
*label18.x: 5
*label18.y: 10
*label18.width: 150
*label18.height: 25
*label18.rightAttachment: "attach_position"
*label18.rightPosition: 3
*label18.topOffset: 0
*label18.leftAttachment: "attach_form"
*label18.bottomAttachment: "attach_form"
*label18.topAttachment: "attach_form"
*label18.labelString: "Available disk:"
*label18.alignment: "alignment_end"

*archSaveReqDiskavailText.class: textField
*archSaveReqDiskavailText.static: true
*archSaveReqDiskavailText.name: archSaveReqDiskavailText
*archSaveReqDiskavailText.parent: form19
*archSaveReqDiskavailText.x: 234
*archSaveReqDiskavailText.y: 10
*archSaveReqDiskavailText.width: 331
*archSaveReqDiskavailText.height: 35
*archSaveReqDiskavailText.rightAttachment: "attach_form"
*archSaveReqDiskavailText.leftAttachment: "attach_position"
*archSaveReqDiskavailText.leftPosition: 4
*archSaveReqDiskavailText.rightOffset: 20
*archSaveReqDiskavailText.resizeWidth: "true"
*archSaveReqDiskavailText.text: ""

