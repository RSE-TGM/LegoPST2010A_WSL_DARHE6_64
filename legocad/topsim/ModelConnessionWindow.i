! UIMX ascii 2.0 key: 6637                                                      

*ModelConnessionWindow.class: mainWindow
*ModelConnessionWindow.parent: NO_PARENT
*ModelConnessionWindow.defaultShell: topLevelShell
*ModelConnessionWindow.static: true
*ModelConnessionWindow.gbldecl: /*\
   modulo ModelConnessionWindow.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)ModelConnessionWindow.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "topsim.h"\
#include "lg1_topsim.h"\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
/***\
Find_struct parametri_ulist;\
Arg argb[15];\
Cardinal nargb;\
***/
*ModelConnessionWindow.ispecdecl: Widget WindVariable;\
MODELLO *ltask;\
Find_struct parametri_ulist;\
Arg argb[15];\
Cardinal nargb;
*ModelConnessionWindow.ispeclist: WindVariable, ltask, parametri_ulist, argb, nargb
*ModelConnessionWindow.ispeclist.WindVariable: "Widget", "%WindVariable%"
*ModelConnessionWindow.ispeclist.ltask: "MODELLO", "*%ltask%"
*ModelConnessionWindow.ispeclist.parametri_ulist: "Find_struct", "%parametri_ulist%"
*ModelConnessionWindow.ispeclist.argb: "Arg", "%argb%[15]"
*ModelConnessionWindow.ispeclist.nargb: "Cardinal", "%nargb%"
*ModelConnessionWindow.funcdecl: swidget create_ModelConnessionWindow(MODELLO *model)\

*ModelConnessionWindow.funcname: create_ModelConnessionWindow
*ModelConnessionWindow.funcdef: "swidget", "<create_ModelConnessionWindow>(%)"
*ModelConnessionWindow.argdecl: MODELLO *model;
*ModelConnessionWindow.arglist: model
*ModelConnessionWindow.arglist.model: "MODELLO", "*%model%"
*ModelConnessionWindow.icode: extern int fin_conn_open;\
char *salva_context;\
Widget block_find_form;\
ltask = model;
*ModelConnessionWindow.fcode: {\
   set_titolo(ltask);\
\
   set_lista_blocchi(ltask);\
\
\
/* Inserimento find di libreria */\
   parametri_ulist.ID_lista = UxGetWidget(blListSL1);\
   parametri_ulist.num_elem = 100;\
   parametri_ulist.vis_elem = 1;\
   parametri_ulist.pos      = 0;\
\
   nargb=0;\
   XtSetArg(argb[nargb],XmNleftAttachment,XmATTACH_FORM);\
   nargb++;\
   XtSetArg(argb[nargb],XmNleftOffset,0);\
   nargb++;\
   XtSetArg(argb[nargb],XmNrightAttachment,XmATTACH_FORM);\
   nargb++;\
   XtSetArg(argb[nargb],XmNrightOffset,0);\
   nargb++;\
   XtSetArg(argb[nargb],XmNbottomAttachment,XmATTACH_FORM);\
   nargb++;\
   XtSetArg(argb[nargb],XmNbottomOffset,0);\
   nargb++;\
   XtSetArg(argb[nargb],XmNtopAttachment,XmATTACH_FORM);\
   nargb++;\
   XtSetArg(argb[nargb],XmNtopOffset,0);\
   nargb++;\
\
\
   block_find_form = find_kit(UxGetWidget(findBlock),argb,nargb,\
                                                 &parametri_ulist);\
\
   fin_conn_open++;\
\
\
   return(rtrn);\
\
}
*ModelConnessionWindow.auxdecl: void set_titolo(MODELLO *task)\
{\
   XmString xstring;\
\
   xstring=XmStringCreateSimple(task->nome);\
   set_something(modNameLb1,XmNlabelString,xstring);\
\
   xstring=XmStringCreateSimple(task->descr);\
   set_something(descrMod,XmNlabelString,xstring);\
}\
\
void set_lista_blocchi(MODELLO *task)\
{\
   int i;\
   char cstring[STRLONG];\
   XmString xstring;\
\
   for(i=0;i<task->num_blocchi;i++)\
   {\
      sprintf(cstring,"%s%s  %s",task->blocchi[i].sigla_modulo,task->blocchi[i].sigla_blocco,task->blocchi[i].descr_blocco);\
      xstring =  XmStringCreateSimple(cstring);\
      XmListAddItem(blListSL1,xstring,0);\
   }\
}\
\
void set_connwind_closure(Widget wind)\
{\
   WindVariable = wind;\
}\

*ModelConnessionWindow.name: ModelConnessionWindow
*ModelConnessionWindow.unitType: "pixels"
*ModelConnessionWindow.x: 800
*ModelConnessionWindow.y: 5
*ModelConnessionWindow.width: 560
*ModelConnessionWindow.height: 400
*ModelConnessionWindow.background: "GhostWhite"

*menuBar1.class: rowColumn
*menuBar1.parent: ModelConnessionWindow
*menuBar1.static: true
*menuBar1.name: menuBar1
*menuBar1.rowColumnType: "menu_bar"
*menuBar1.menuAccelerator: "<KeyUp>F10"
*menuBar1.spacing: 0

*filePane1.class: rowColumn
*filePane1.parent: menuBar1
*filePane1.static: true
*filePane1.name: filePane1
*filePane1.rowColumnType: "menu_pulldown"
*filePane1.spacing: 0

*Close.class: pushButton
*Close.parent: filePane1
*Close.static: true
*Close.name: Close
*Close.labelString: "Close"
*Close.activateCallback: {\
extern int fin_conn_open;\
extern int distruggi_interfaccie();\
\
fin_conn_open--;\
distruggi_interfaccie(WindVariable );\
\
/*\
UxDestroyInterface( WindVariable );\
UxDestroyInterface( ModelConnessionWindow );\
*/\
\
}

*OptionPane1.class: rowColumn
*OptionPane1.parent: menuBar1
*OptionPane1.static: true
*OptionPane1.name: OptionPane1
*OptionPane1.rowColumnType: "menu_pulldown"

*SetDefFilter1.class: cascadeButtonGadget
*SetDefFilter1.parent: OptionPane1
*SetDefFilter1.static: true
*SetDefFilter1.name: SetDefFilter1
*SetDefFilter1.labelString: "Set Default Filter"
*SetDefFilter1.subMenuId: "DefaultFilterPane1"

*separator13.class: separatorGadget
*separator13.parent: OptionPane1
*separator13.static: true
*separator13.name: separator13

*DefineFilter1.class: pushButtonGadget
*DefineFilter1.parent: OptionPane1
*DefineFilter1.static: true
*DefineFilter1.name: DefineFilter1
*DefineFilter1.labelString: "Define Filter"
*DefineFilter1.activateCallback.source: public
*DefineFilter1.activateCallback: 

*DefaultFilterPane1.class: rowColumn
*DefaultFilterPane1.parent: OptionPane1
*DefaultFilterPane1.static: true
*DefaultFilterPane1.name: DefaultFilterPane1
*DefaultFilterPane1.rowColumnType: "menu_pulldown"

*NoFilterDef1.class: pushButtonGadget
*NoFilterDef1.parent: DefaultFilterPane1
*NoFilterDef1.static: true
*NoFilterDef1.name: NoFilterDef1
*NoFilterDef1.labelString: "No Filter"
*NoFilterDef1.activateCallback.source: public
*NoFilterDef1.activateCallback: 

*fileCascade1.class: cascadeButton
*fileCascade1.parent: menuBar1
*fileCascade1.static: true
*fileCascade1.name: fileCascade1
*fileCascade1.labelString: "Model"
*fileCascade1.mnemonic: "F"
*fileCascade1.subMenuId: "filePane1"

*menuBar_top_b1.class: cascadeButton
*menuBar_top_b1.parent: menuBar1
*menuBar_top_b1.static: true
*menuBar_top_b1.name: menuBar_top_b1
*menuBar_top_b1.labelString: "Options"
*menuBar_top_b1.mnemonic: "O"
*menuBar_top_b1.subMenuId: "OptionPane1"

*mainPW1.class: panedWindow
*mainPW1.parent: ModelConnessionWindow
*mainPW1.static: true
*mainPW1.name: mainPW1
*mainPW1.sashIndent: -10
*mainPW1.spacing: 20
*mainPW1.background: "#7E88AB"

*mainForm1.class: form
*mainForm1.parent: mainPW1
*mainForm1.static: true
*mainForm1.name: mainForm1
*mainForm1.resizePolicy: "resize_none"
*mainForm1.x: 15
*mainForm1.y: 10
*mainForm1.width: 530
*mainForm1.height: 450
*mainForm1.paneMaximum: 1000
*mainForm1.allowResize: "false"
*mainForm1.paneMinimum: 250

*modNameLb1.class: label
*modNameLb1.parent: mainForm1
*modNameLb1.static: false
*modNameLb1.name: modNameLb1
*modNameLb1.x: 105
*modNameLb1.y: 55
*modNameLb1.width: 330
*modNameLb1.height: 35
*modNameLb1.leftAttachment: "attach_form"
*modNameLb1.leftOffset: 5
*modNameLb1.rightAttachment: "attach_form"
*modNameLb1.rightOffset: 5
*modNameLb1.labelString: "No model selected"
*modNameLb1.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"
*modNameLb1.topAttachment: "attach_form"
*modNameLb1.topOffset: 10
*modNameLb1.highlightThickness: 0
*modNameLb1.highlightOnEnter: "false"
*modNameLb1.highlightColor: "#cccc22224444"
*modNameLb1.shadowThickness: 0
*modNameLb1.traversalOn: "false"

*blListLb1.class: label
*blListLb1.parent: mainForm1
*blListLb1.static: true
*blListLb1.name: blListLb1
*blListLb1.x: 25
*blListLb1.y: 155
*blListLb1.width: 110
*blListLb1.height: 15
*blListLb1.leftAttachment: "attach_form"
*blListLb1.leftOffset: 5
*blListLb1.topAttachment: "attach_widget"
*blListLb1.topOffset: 25
*blListLb1.topWidget: "modNameLb1"
*blListLb1.alignment: "alignment_center"
*blListLb1.labelString: "Blocks in model"
*blListLb1.rightAttachment: "attach_form"
*blListLb1.rightOffset: 5
*blListLb1.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*findBlock.class: rowColumn
*findBlock.parent: mainForm1
*findBlock.static: true
*findBlock.name: findBlock
*findBlock.x: 30
*findBlock.y: 390
*findBlock.width: 422
*findBlock.height: 32
*findBlock.bottomAttachment: "attach_form"
*findBlock.bottomOffset: 20
*findBlock.leftAttachment: "attach_form"
*findBlock.orientation: "horizontal"
*findBlock.rightAttachment: "attach_form"
*findBlock.rightOffset: 30
*findBlock.leftOffset: 30
*findBlock.numColumns: 2
*findBlock.packing: "pack_tight"
*findBlock.resizable: "true"

*blListSW1.class: scrolledWindow
*blListSW1.parent: mainForm1
*blListSW1.static: true
*blListSW1.name: blListSW1
*blListSW1.scrollingPolicy: "application_defined"
*blListSW1.x: 30
*blListSW1.y: 100
*blListSW1.visualPolicy: "variable"
*blListSW1.scrollBarDisplayPolicy: "static"
*blListSW1.shadowThickness: 0
*blListSW1.bottomAttachment: "attach_widget"
*blListSW1.bottomOffset: 10
*blListSW1.bottomWidget: "findBlock"
*blListSW1.leftAttachment: "attach_form"
*blListSW1.leftOffset: 30
*blListSW1.rightAttachment: "attach_form"
*blListSW1.rightOffset: 30
*blListSW1.topAttachment: "attach_widget"
*blListSW1.topOffset: 5
*blListSW1.topWidget: "blListLb1"
*blListSW1.height: 310

*blListSL1.class: scrolledList
*blListSL1.parent: blListSW1
*blListSL1.static: true
*blListSL1.name: blListSL1
*blListSL1.width: 494
*blListSL1.height: 279
*blListSL1.selectionPolicy: "single_select"
*blListSL1.listSpacing: 0
*blListSL1.scrollBarDisplayPolicy: "as_needed"
*blListSL1.listSizePolicy: "constant"
*blListSL1.highlightThickness: 0
*blListSL1.shadowThickness: 2
*blListSL1.listMarginHeight: 5
*blListSL1.listMarginWidth: 5
*blListSL1.extendedSelectionCallback: {\
\
}
*blListSL1.singleSelectionCallback: {\
/*\
   devo recuperare il blocco selezionato dalla lista \
   e ricostruire la varWin con le variabili del nuovo blocco \
   posso fare in due modi \
\
	1) ditruggere la varwin e ricostruirla con il nuovo blocco\
\
 	2) distruggere solo il contenuto della varwin e \
	   riempirla con i dati del nuovo blocco\
*/\
\
/* provo la soluzione 2) */\
\
extern int change_active_block();\
\
int *pos_list,count;\
\
XmListGetSelectedPos(blListSL1,&pos_list,&count);\
\
if( count == 1)\
   change_active_block(ltask,pos_list[0]-1,WindVariable);\
}
*blListSL1.selectedItemCount: 0
*blListSL1.visibleItemCount: 50

*descrMod.class: label
*descrMod.parent: mainForm1
*descrMod.static: true
*descrMod.name: descrMod
*descrMod.x: 7
*descrMod.y: 33
*descrMod.width: 515
*descrMod.height: 36
*descrMod.topAttachment: "attach_widget"
*descrMod.topOffset: 0
*descrMod.topWidget: "modNameLb1"
*descrMod.bottomWidget: "blListLb1"
*descrMod.bottomAttachment: "attach_widget"
*descrMod.leftAttachment: "attach_form"
*descrMod.leftOffset: 5
*descrMod.rightAttachment: "attach_form"
*descrMod.rightOffset: 5

