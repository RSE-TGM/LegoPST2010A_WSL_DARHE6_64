! UIMX ascii 2.5 key: 398                                                       

*optionSet.class: applicationShell
*optionSet.gbldecl: #include <stdio.h>\
extern swidget masterMenu;\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "messaggi.h"\
\
#ifndef DESIGN_TIME\
#include "option.h"\
extern int opt_interface_active;\
extern OPTIONS_FLAGS options;\
extern Boolean *IcProt;\
#endif\
extern int isSuperuser;\

*optionSet.ispecdecl:
*optionSet.funcdecl: swidget create_optionSet()\

*optionSet.funcname: create_optionSet
*optionSet.funcdef: "swidget", "<create_optionSet>(%)"
*optionSet.icode:
*optionSet.fcode: #ifndef DESIGN_TIME\
/* \
 * setta il default \
 */ \
carica_options (UxGetWidget(optionSetForm),OPTION_INIT);\
opt_interface_active = 1;\
#endif\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*optionSet.auxdecl: char *check_if_superuser (flag)\
int flag;\
{\
   if (flag)\
      return ("true");\
   return ("false");\
}
*optionSet.name.source: public
*optionSet.static: false
*optionSet.name: optionSet
*optionSet.parent: NO_PARENT
*optionSet.x: 335
*optionSet.y: 595
*optionSet.width: 320
*optionSet.height: 400

*form7.class: form
*form7.static: true
*form7.name: form7
*form7.parent: optionSet
*form7.resizePolicy: "resize_none"
*form7.unitType: "pixels"
*form7.x: 0
*form7.y: 0
*form7.width: 320
*form7.height: 215

*form12.class: form
*form12.static: true
*form12.name: form12
*form12.parent: form7
*form12.resizePolicy: "resize_none"
*form12.x: 16
*form12.y: 108
*form12.width: 750
*form12.height: 75
*form12.rightAttachment: "attach_form"
*form12.topAttachment: "attach_none"
*form12.topOffset: 0
*form12.leftAttachment: "attach_form"
*form12.bottomAttachment: "attach_form"
*form12.topWidget: ""

*frame12.class: frame
*frame12.static: true
*frame12.name: frame12
*frame12.parent: form12
*frame12.x: 10
*frame12.y: 405
*frame12.width: 795
*frame12.height: 50
*frame12.bottomAttachment: "attach_form"
*frame12.leftOffset: 0
*frame12.rightAttachment: "attach_form"
*frame12.topOffset: 0
*frame12.leftAttachment: "attach_form"
*frame12.topAttachment: "attach_form"

*form21.class: form
*form21.static: true
*form21.name: form21
*form21.parent: frame12
*form21.resizePolicy: "resize_none"
*form21.x: 0
*form21.y: 0
*form21.width: 745
*form21.height: 72

*pushButton6.class: pushButton
*pushButton6.static: true
*pushButton6.name: pushButton6
*pushButton6.parent: form21
*pushButton6.x: 100
*pushButton6.y: 20
*pushButton6.width: 130
*pushButton6.height: 30
*pushButton6.labelString: OPTION_APPLY_LABEL ? OPTION_APPLY_LABEL : "OK"
*pushButton6.leftAttachment: "attach_position"
*pushButton6.leftOffset: 0
*pushButton6.leftPosition: 30
*pushButton6.rightAttachment: "attach_position"
*pushButton6.rightPosition: 70
*pushButton6.activateCallback: {\
#ifndef DESIGN_TIME\
aggiorna_opzioni (UxWidget, &options);\
#endif\
}

*menu6.class: rowColumn
*menu6.static: true
*menu6.name: menu6
*menu6.parent: form7
*menu6.rowColumnType: "menu_bar"
*menu6.rightAttachment: "attach_form"
*menu6.leftAttachment: "attach_form"
*menu6.menuAccelerator: "<KeyUp>F10"

*optionSetMenu.class: rowColumn
*optionSetMenu.static: true
*optionSetMenu.name: optionSetMenu
*optionSetMenu.parent: menu6
*optionSetMenu.rowColumnType: "menu_pulldown"

*optionSetMenuSavepb.class: pushButton
*optionSetMenuSavepb.static: true
*optionSetMenuSavepb.name: optionSetMenuSavepb
*optionSetMenuSavepb.parent: optionSetMenu
*optionSetMenuSavepb.labelString: "Save "
*optionSetMenuSavepb.activateCallback: {\
#ifndef  DESIGN_TIME\
if (SD_optsave (BANCO, &options,IcProt) > 0)\
   fprintf (stderr,"OPZIONI salvate\n");\
else\
   fprintf (stderr,"*** errore save opzioni\n");\
#endif\
}

*optionSetMenu_b2.class: separator
*optionSetMenu_b2.static: true
*optionSetMenu_b2.name: optionSetMenu_b2
*optionSetMenu_b2.parent: optionSetMenu

*optionSetMenuLoadpb.class: pushButton
*optionSetMenuLoadpb.static: true
*optionSetMenuLoadpb.name: optionSetMenuLoadpb
*optionSetMenuLoadpb.parent: optionSetMenu
*optionSetMenuLoadpb.labelString: "Load "
*optionSetMenuLoadpb.activateCallback: {\
#ifndef DESIGN_TIME \
printf ("load Options\n");\
read_options();\
opt_interface_active = 0;\
DistruggiInterfaccia (optionSet);\
aggiorna_opzioni (UxWidget, &options);\
#endif\
}

*optionSetMenu_b4.class: separator
*optionSetMenu_b4.static: true
*optionSetMenu_b4.name: optionSetMenu_b4
*optionSetMenu_b4.parent: optionSetMenu

*optionSetMenuQuitpb.class: pushButton
*optionSetMenuQuitpb.static: true
*optionSetMenuQuitpb.name: optionSetMenuQuitpb
*optionSetMenuQuitpb.parent: optionSetMenu
*optionSetMenuQuitpb.labelString: "Quit"
*optionSetMenuQuitpb.activateCallback: {\
#ifndef DESIGN_TIME\
opt_interface_active = 0;  /* reset memoria interfaccia attiva */\
DistruggiInterfaccia ((Widget)UxClientData);\
#endif\
}
*optionSetMenuQuitpb.activateCallbackClientData: UxGetWidget(optionSet)

*menu6_top_b2.class: cascadeButton
*menu6_top_b2.static: true
*menu6_top_b2.name: menu6_top_b2
*menu6_top_b2.parent: menu6
*menu6_top_b2.labelString: "File"
*menu6_top_b2.subMenuId: "optionSetMenu"

*frame11.class: frame
*frame11.static: true
*frame11.name: frame11
*frame11.parent: form7
*frame11.x: 0
*frame11.y: 5
*frame11.width: 434
*frame11.height: 55
*frame11.rightAttachment: "attach_form"
*frame11.topOffset: 0
*frame11.leftAttachment: "attach_form"
*frame11.topAttachment: "attach_widget"
*frame11.topWidget: "menu6"

*form11.class: form
*form11.static: true
*form11.name: form11
*form11.parent: frame11
*form11.resizePolicy: "resize_none"
*form11.x: 2
*form11.y: 2
*form11.width: 430
*form11.height: 38

*optionSelection.class: rowColumn
*optionSelection.static: true
*optionSelection.name: optionSelection
*optionSelection.parent: form11
*optionSelection.rowColumnType: "menu_option"
*optionSelection.subMenuId: "optSelectionMenu"
*optionSelection.labelString: "Current Selection :"
*optionSelection.rightAttachment: "attach_form"
*optionSelection.bottomAttachment: "attach_form"
*optionSelection.topAttachment: "attach_form"
*optionSelection.whichButton: 1

*optSelectionMenu.class: rowColumn
*optSelectionMenu.static: true
*optSelectionMenu.name: optSelectionMenu
*optSelectionMenu.parent: optionSelection
*optSelectionMenu.rowColumnType: "menu_pulldown"

*optSelMenuInitpb.class: pushButton
*optSelMenuInitpb.static: true
*optSelMenuInitpb.name: optSelMenuInitpb
*optSelMenuInitpb.parent: optSelectionMenu
*optSelMenuInitpb.labelString: "Init      "
*optSelMenuInitpb.activateCallback: {\
printf ("richiesta init \n");\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_INIT);\
#endif\
}

*optSelMenuSnappb.class: pushButton
*optSelMenuSnappb.static: true
*optSelMenuSnappb.name: optSelMenuSnappb
*optSelMenuSnappb.parent: optSelectionMenu
*optSelMenuSnappb.labelString: "Snapshot  "
*optSelMenuSnappb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_SNAPSHOT);\
#endif\
}

*optSelMenuIcProtpb.class: pushButton
*optSelMenuIcProtpb.static: true
*optSelMenuIcProtpb.name: optSelMenuIcProtpb
*optSelMenuIcProtpb.parent: optSelectionMenu
*optSelMenuIcProtpb.labelString: "I.C. prot."
*optSelMenuIcProtpb.createManaged: check_if_superuser (isSuperuser)
*optSelMenuIcProtpb.activateCallback: {\
#ifndef DESIGN_TIME\
   carica_options (UxGetWidget(optionSetForm),OPTION_ICPROTECT);\
#endif\
}

*optSelMenuRecpb.class: pushButton
*optSelMenuRecpb.static: true
*optSelMenuRecpb.name: optSelMenuRecpb
*optSelMenuRecpb.parent: optSelectionMenu
*optSelMenuRecpb.labelString: "Recording "
*optSelMenuRecpb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_RECORDING);\
#endif\
}

*optSelMenuMffrpb.class: pushButton
*optSelMenuMffrpb.static: true
*optSelMenuMffrpb.name: optSelMenuMffrpb
*optSelMenuMffrpb.parent: optSelectionMenu
*optSelMenuMffrpb.labelString: "Mf/Fr   "
*optSelMenuMffrpb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_MFFR);\
#endif\
}\

*optSelMenuMffrpb.createManaged: "true"

*optSelMenuArchivepb.class: pushButton
*optSelMenuArchivepb.static: true
*optSelMenuArchivepb.name: optSelMenuArchivepb
*optSelMenuArchivepb.parent: optSelectionMenu
*optSelMenuArchivepb.labelString: "Archive   "
*optSelMenuArchivepb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_ARCHIVE);\
#endif\
}\

*optSelMenuArchivepb.createManaged: "true"

*optSelMenuShowpb.class: pushButton
*optSelMenuShowpb.static: true
*optSelMenuShowpb.name: optSelMenuShowpb
*optSelMenuShowpb.parent: optSelectionMenu
*optSelMenuShowpb.labelString: "Show   "
*optSelMenuShowpb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_options (UxGetWidget(optionSetForm),OPTION_SHOW);\
#endif\
}\

*optSelMenuShowpb.createManaged: "true"

*optSelectionMenu_b7.class: separator
*optSelectionMenu_b7.static: true
*optSelectionMenu_b7.name: optSelectionMenu_b7
*optSelectionMenu_b7.parent: optSelectionMenu

*optSelMenuDisplaypb.class: pushButton
*optSelMenuDisplaypb.static: true
*optSelMenuDisplaypb.name: optSelMenuDisplaypb
*optSelMenuDisplaypb.parent: optSelectionMenu
*optSelMenuDisplaypb.labelString: "Display"
*optSelMenuDisplaypb.activateCallback: {\
   printf ("richiesta display \n");\
#ifndef DESIGN_TIME\
   carica_options (UxGetWidget(optionSetForm),OPTION_DISPLAY);\
#endif\
}   

*optSelnMenuProgLaunchpb.class: pushButton
*optSelnMenuProgLaunchpb.static: true
*optSelnMenuProgLaunchpb.name: optSelnMenuProgLaunchpb
*optSelnMenuProgLaunchpb.parent: optSelectionMenu
*optSelnMenuProgLaunchpb.labelString: "User Programs"
*optSelnMenuProgLaunchpb.activateCallback: {\
printf ("user programs\n");\
#ifndef DESIGN_TIME\
   carica_options (UxGetWidget(optionSetForm),OPTION_USERPROG);\
#endif\
}

*frame10.class: frame
*frame10.static: true
*frame10.name: frame10
*frame10.parent: form7
*frame10.x: 5
*frame10.y: 35
*frame10.width: 190
*frame10.height: 90
*frame10.bottomAttachment: "attach_widget"
*frame10.bottomWidget: "form12"
*frame10.leftOffset: 0
*frame10.topAttachment: "attach_widget"
*frame10.topWidget: "frame11"
*frame10.rightAttachment: "attach_form"
*frame10.leftAttachment: "attach_form"

*optionSetForm.class: form
*optionSetForm.static: true
*optionSetForm.name: optionSetForm
*optionSetForm.parent: frame10
*optionSetForm.resizePolicy: "resize_none"
*optionSetForm.x: 2
*optionSetForm.y: -25
*optionSetForm.width: 423
*optionSetForm.height: 225

