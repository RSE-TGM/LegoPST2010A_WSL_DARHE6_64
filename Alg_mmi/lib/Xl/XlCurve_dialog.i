! UIMX ascii 2.5 key: 7435                                                      

*handleVar.class: dialogShell
*handleVar.gbldecl: #include <stdio.h>\
\

*handleVar.ispecdecl:
*handleVar.funcdecl: swidget create_handleVar(swidget UxParent,swidget curve_obj,int *toggle_state,int *num_scale_vis)\

*handleVar.funcname: create_handleVar
*handleVar.funcdef: "swidget", "<create_handleVar>(%)"
*handleVar.argdecl: swidget UxParent;\
swidget curve_obj;\
int *toggle_state;\
int *num_scale_vis;
*handleVar.arglist: UxParent, curve_obj, toggle_state, num_scale_vis
*handleVar.arglist.UxParent: "swidget", "%UxParent%"
*handleVar.arglist.curve_obj: "swidget", "%curve_obj%"
*handleVar.arglist.toggle_state: "int", "*%toggle_state%"
*handleVar.arglist.num_scale_vis: "int", "*%num_scale_vis%"
*handleVar.icode:
*handleVar.fcode: printf("create_handleVar: toggle_state=%d\tnum_scale_vis=%d\n",*toggle_state,*num_scale_vis);\
\
switch (*toggle_state) {\
   case 1:\
      XmToggleButtonSetState(toggleButton1,True,False);\
      break;\
   case 2:\
      XmToggleButtonSetState(toggleButton2,True,False);\
      break;\
   case 3:\
      XmToggleButtonSetState(toggleButton3,True,False);\
      break;\
}\
UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*handleVar.auxdecl:
*handleVar.static: true
*handleVar.name: handleVar
*handleVar.parent: NO_PARENT
*handleVar.parentExpression: UxParent
*handleVar.width: 250
*handleVar.height: 380
*handleVar.isCompound: "true"
*handleVar.compoundIcon: "dialogS.xpm"
*handleVar.compoundName: "dialog_Shell"
*handleVar.x: 700
*handleVar.y: 650
*handleVar.createManaged: "false"

*form1.class: form
*form1.static: true
*form1.name: form1
*form1.parent: handleVar
*form1.width: 250
*form1.height: 260
*form1.resizePolicy: "resize_none"
*form1.isCompound: "true"
*form1.compoundIcon: "form.xpm"
*form1.compoundName: "form_"
*form1.x: 10
*form1.y: 10
*form1.unitType: "pixels"
*form1.background: "WhiteSmoke"
*form1.dialogStyle: "dialog_full_application_modal"
*form1.noResize: "true"

*title.class: label
*title.static: true
*title.name: title
*title.parent: form1
*title.isCompound: "true"
*title.compoundIcon: "label.xpm"
*title.compoundName: "label_"
*title.x: 5
*title.y: 0
*title.width: 240
*title.height: 20
*title.background: "WhiteSmoke"
*title.borderWidth: 1
*title.alignment: "alignment_beginning"

*rowColumn1.class: rowColumn
*rowColumn1.static: true
*rowColumn1.name: rowColumn1
*rowColumn1.parent: form1
*rowColumn1.width: 200
*rowColumn1.height: 170
*rowColumn1.isCompound: "true"
*rowColumn1.compoundIcon: "row.xpm"
*rowColumn1.compoundName: "row_Column"
*rowColumn1.x: 10
*rowColumn1.y: 50
*rowColumn1.entryAlignment: "alignment_beginning"
*rowColumn1.packing: "pack_column"
*rowColumn1.spacing: 5
*rowColumn1.background: "WhiteSmoke"
*rowColumn1.radioBehavior: "true"
*rowColumn1.radioAlwaysOne: "false"

*toggleButton1.class: toggleButton
*toggleButton1.static: true
*toggleButton1.name: toggleButton1
*toggleButton1.parent: rowColumn1
*toggleButton1.isCompound: "true"
*toggleButton1.compoundIcon: "toggle.xpm"
*toggleButton1.compoundName: "toggle_Button"
*toggleButton1.x: 20
*toggleButton1.y: 20
*toggleButton1.height: 30
*toggleButton1.background: "WhiteSmoke"
*toggleButton1.width: 180
*toggleButton1.recomputeSize: "false"
*toggleButton1.fontList: "-adobe-courier-bold-r-normal--14-100-100-100-m-90-iso8859-1"

*toggleButton2.class: toggleButton
*toggleButton2.static: true
*toggleButton2.name: toggleButton2
*toggleButton2.parent: rowColumn1
*toggleButton2.isCompound: "true"
*toggleButton2.compoundIcon: "toggle.xpm"
*toggleButton2.compoundName: "toggle_Button"
*toggleButton2.x: 13
*toggleButton2.y: 13
*toggleButton2.height: 30
*toggleButton2.background: "WhiteSmoke"
*toggleButton2.recomputeSize: "false"
*toggleButton2.fontList: "-adobe-courier-bold-r-normal--14-100-100-100-m-90-iso8859-1"

*toggleButton3.class: toggleButton
*toggleButton3.static: true
*toggleButton3.name: toggleButton3
*toggleButton3.parent: rowColumn1
*toggleButton3.isCompound: "true"
*toggleButton3.compoundIcon: "toggle.xpm"
*toggleButton3.compoundName: "toggle_Button"
*toggleButton3.x: 13
*toggleButton3.y: 41
*toggleButton3.height: 30
*toggleButton3.background: "WhiteSmoke"
*toggleButton3.fontList: "-adobe-courier-bold-r-normal--14-100-100-100-m-90-iso8859-1"

*pushButOk.class: pushButton
*pushButOk.static: true
*pushButOk.name: pushButOk
*pushButOk.parent: form1
*pushButOk.isCompound: "true"
*pushButOk.compoundIcon: "push.xpm"
*pushButOk.compoundName: "push_Button"
*pushButOk.x: 20
*pushButOk.y: 220
*pushButOk.height: 35
*pushButOk.width: 60
*pushButOk.topOffset: 100
*pushButOk.background: "WhiteSmoke"
*pushButOk.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButOk.labelString: "OK"
*pushButOk.alignment: "alignment_beginning"
*pushButOk.activateCallback: {\
/*\
   Si controlla quale toggle e' stato settato e si assegna\
   opportunamente il parametro ricevuto dalla callback.\
*/\
if(XmToggleButtonGetState(toggleButton1)) \
   *toggle_state=1;\
else if(XmToggleButtonGetState(toggleButton2)) {\
   *toggle_state=2;\
   *num_scale_vis=(*num_scale_vis)+1;\
   printf("DIALOGSHELL1: num_scale_vis=%d\n",*num_scale_vis);\
}\
else if(XmToggleButtonGetState(toggleButton3))\
   *toggle_state=3;\
else\
   *toggle_state=0;\
 \
XtDestroyWidget(UxThisWidget);\
\
\
}

*pb_exit.class: pushButton
*pb_exit.static: true
*pb_exit.name: pb_exit
*pb_exit.parent: form1
*pb_exit.isCompound: "true"
*pb_exit.compoundIcon: "push.xpm"
*pb_exit.compoundName: "push_Button"
*pb_exit.x: 120
*pb_exit.y: 220
*pb_exit.height: 35
*pb_exit.width: 120
*pb_exit.background: "WhiteSmoke"
*pb_exit.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pb_exit.alignment: "alignment_beginning"
*pb_exit.activateCallback: {\
XtDestroyWidget(UxThisWidget);\
\
\
}

