! UIMX ascii 2.5 key: 8951                                                      

*resourceSetting.class: formDialog
*resourceSetting.gbldecl: #include <stdio.h>\
#include "risorse.h"\
#include "messaggi.h"\
#include "risorse_default.h"\
\
RESOURCE_DEF *Rdef; /* risorse configurabili da utente */\

*resourceSetting.ispecdecl: int n_entries;	/* numero di risorse di categoria */\
int selectedCategory;\
/* widget per option menu */\
Widget optMenuForm;\
Widget optMenuShell;\
Widget optMenuRc;\
Widget *optMenuItem;\
Widget optMenu;\
/* widget per risorse */\
int    *indx;    /* indice nella struttura risorse */\
Widget *resForm;\
Widget *resLabel;\
Widget *resText;\
Widget *resMoreButton;
*resourceSetting.ispeclist: n_entries, selectedCategory, optMenuForm, optMenuShell, optMenuRc, optMenuItem, optMenu, indx, resForm, resLabel, resText, resMoreButton
*resourceSetting.ispeclist.n_entries: "int", "%n_entries%"
*resourceSetting.ispeclist.selectedCategory: "int", "%selectedCategory%"
*resourceSetting.ispeclist.optMenuForm: "Widget", "%optMenuForm%"
*resourceSetting.ispeclist.optMenuShell: "Widget", "%optMenuShell%"
*resourceSetting.ispeclist.optMenuRc: "Widget", "%optMenuRc%"
*resourceSetting.ispeclist.optMenuItem: "Widget", "*%optMenuItem%"
*resourceSetting.ispeclist.optMenu: "Widget", "%optMenu%"
*resourceSetting.ispeclist.indx: "int", "*%indx%"
*resourceSetting.ispeclist.resForm: "Widget", "*%resForm%"
*resourceSetting.ispeclist.resLabel: "Widget", "*%resLabel%"
*resourceSetting.ispeclist.resText: "Widget", "*%resText%"
*resourceSetting.ispeclist.resMoreButton: "Widget", "*%resMoreButton%"
*resourceSetting.funcdecl: swidget create_resourceSetting(UxParent)\
swidget UxParent;
*resourceSetting.funcname: create_resourceSetting
*resourceSetting.funcdef: "swidget", "<create_resourceSetting>(%)"
*resourceSetting.argdecl: swidget UxParent;
*resourceSetting.arglist: UxParent
*resourceSetting.arglist.UxParent: "swidget", "%UxParent%"
*resourceSetting.icode: n_entries = 0;
*resourceSetting.fcode: caricaDatiRisorse (rtrn);\
displayRisorse (rtrn);\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*resourceSetting.auxdecl:
*resourceSetting.static: true
*resourceSetting.name: resourceSetting
*resourceSetting.parent: NO_PARENT
*resourceSetting.parentExpression: UxParent
*resourceSetting.defaultShell: topLevelShell
*resourceSetting.unitType: "pixels"
*resourceSetting.x: 240
*resourceSetting.y: 430
*resourceSetting.width: 420
*resourceSetting.height: 460
*resourceSetting.destroyCallback: {\
clearResourceList (UxWidget);\
}

*applyFrame.class: frame
*applyFrame.static: true
*applyFrame.name: applyFrame
*applyFrame.parent: resourceSetting
*applyFrame.x: -267
*applyFrame.y: 140
*applyFrame.width: 795
*applyFrame.height: 50
*applyFrame.bottomAttachment: "attach_form"
*applyFrame.leftOffset: 0
*applyFrame.rightAttachment: "attach_form"
*applyFrame.leftAttachment: "attach_form"

*form33.class: form
*form33.static: true
*form33.name: form33
*form33.parent: applyFrame
*form33.resizePolicy: "resize_none"
*form33.x: 0
*form33.y: 0
*form33.width: 745
*form33.height: 72
*form33.defaultButton: ""

*applyResourceSetting.class: pushButton
*applyResourceSetting.static: true
*applyResourceSetting.name: applyResourceSetting
*applyResourceSetting.parent: form33
*applyResourceSetting.x: 100
*applyResourceSetting.y: 20
*applyResourceSetting.width: 130
*applyResourceSetting.height: 40
*applyResourceSetting.labelString: APPLYLABEL
*applyResourceSetting.leftAttachment: "attach_position"
*applyResourceSetting.leftOffset: 0
*applyResourceSetting.leftPosition: 30
*applyResourceSetting.rightAttachment: "attach_position"
*applyResourceSetting.rightPosition: 70
*applyResourceSetting.activateCallback: {\
applyResource (UxWidget);\
}
*applyResourceSetting.bottomAttachment: "attach_form"
*applyResourceSetting.bottomOffset: 12
*applyResourceSetting.topAttachment: "attach_form"
*applyResourceSetting.topOffset: 12

*resourceSettingMenu.class: rowColumn
*resourceSettingMenu.static: true
*resourceSettingMenu.name: resourceSettingMenu
*resourceSettingMenu.parent: resourceSetting
*resourceSettingMenu.rowColumnType: "menu_bar"
*resourceSettingMenu.menuAccelerator: "<KeyUp>F10"
*resourceSettingMenu.rightAttachment: "attach_form"
*resourceSettingMenu.leftAttachment: "attach_form"

*resourceSettingFile.class: rowColumn
*resourceSettingFile.static: true
*resourceSettingFile.name: resourceSettingFile
*resourceSettingFile.parent: resourceSettingMenu
*resourceSettingFile.rowColumnType: "menu_pulldown"

*resourceSettingFileQuit.class: pushButton
*resourceSettingFileQuit.static: true
*resourceSettingFileQuit.name: resourceSettingFileQuit
*resourceSettingFileQuit.parent: resourceSettingFile
*resourceSettingFileQuit.labelString: QuitMenuLabel
*resourceSettingFileQuit.activateCallback: {\
DistruggiInterfaccia (resourceSetting);\
}

*menu15_top_b1.class: cascadeButton
*menu15_top_b1.static: true
*menu15_top_b1.name: menu15_top_b1
*menu15_top_b1.parent: resourceSettingMenu
*menu15_top_b1.labelString: FileMenuLabel
*menu15_top_b1.subMenuId: "resourceSettingFile"

*form57.class: form
*form57.static: true
*form57.name: form57
*form57.parent: resourceSetting
*form57.resizePolicy: "resize_none"
*form57.x: 50
*form57.y: 80
*form57.width: 330
*form57.height: 290
*form57.bottomAttachment: "attach_widget"
*form57.bottomWidget: "applyFrame"
*form57.leftOffset: 0
*form57.rightAttachment: "attach_form"
*form57.leftAttachment: "attach_form"
*form57.topAttachment: "attach_widget"
*form57.topWidget: "resourceSettingMenu"

*resourceSettingCategSelectForm.class: form
*resourceSettingCategSelectForm.static: true
*resourceSettingCategSelectForm.name: resourceSettingCategSelectForm
*resourceSettingCategSelectForm.parent: form57
*resourceSettingCategSelectForm.resizePolicy: "resize_none"
*resourceSettingCategSelectForm.x: 20
*resourceSettingCategSelectForm.y: 10
*resourceSettingCategSelectForm.width: 380
*resourceSettingCategSelectForm.height: 50
*resourceSettingCategSelectForm.rightAttachment: "attach_form"
*resourceSettingCategSelectForm.leftAttachment: "attach_form"
*resourceSettingCategSelectForm.topOffset: 0

*ResSetForm.class: form
*ResSetForm.static: true
*ResSetForm.name: ResSetForm
*ResSetForm.parent: form57
*ResSetForm.resizePolicy: "resize_none"
*ResSetForm.x: 20
*ResSetForm.y: 120
*ResSetForm.width: 360
*ResSetForm.height: 190
*ResSetForm.rightAttachment: "attach_form"
*ResSetForm.leftAttachment: "attach_form"
*ResSetForm.bottomAttachment: "attach_form"
*ResSetForm.topAttachment: "attach_widget"
*ResSetForm.topWidget: "resourceSettingCategSelectForm"

*scrollWindResSet.class: scrolledWindow
*scrollWindResSet.static: true
*scrollWindResSet.name: scrollWindResSet
*scrollWindResSet.parent: ResSetForm
*scrollWindResSet.scrollingPolicy: "application_defined"
*scrollWindResSet.x: 40
*scrollWindResSet.y: 30
*scrollWindResSet.visualPolicy: "variable"
*scrollWindResSet.scrollBarDisplayPolicy: "static"
*scrollWindResSet.shadowThickness: 2
*scrollWindResSet.bottomAttachment: "attach_form"
*scrollWindResSet.bottomOffset: 20
*scrollWindResSet.leftOffset: 20
*scrollWindResSet.rightAttachment: "attach_form"
*scrollWindResSet.rightOffset: 20
*scrollWindResSet.topAttachment: "attach_form"
*scrollWindResSet.topOffset: 20
*scrollWindResSet.leftAttachment: "attach_form"

*resourceSettingResRc.class: rowColumn
*resourceSettingResRc.static: true
*resourceSettingResRc.name: resourceSettingResRc
*resourceSettingResRc.parent: scrollWindResSet
*resourceSettingResRc.x: 20
*resourceSettingResRc.y: 20
*resourceSettingResRc.width: 350
*resourceSettingResRc.height: 160

