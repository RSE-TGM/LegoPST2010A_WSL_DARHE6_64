! UIMX ascii 2.5 key: 152                                                       

*warningDialog1.class: warningDialog
*warningDialog1.gbldecl: #include <stdio.h>\

*warningDialog1.ispecdecl:
*warningDialog1.funcdecl: swidget create_warningDialog1(UxParent,parametro)\
swidget UxParent;\
int parametro;
*warningDialog1.funcname: create_warningDialog1
*warningDialog1.funcdef: "swidget", "<create_warningDialog1>(%)"
*warningDialog1.argdecl: swidget UxParent;\
int parametro;
*warningDialog1.arglist: UxParent, parametro
*warningDialog1.arglist.UxParent: "swidget", "%UxParent%"
*warningDialog1.arglist.parametro: "int", "%parametro%"
*warningDialog1.icode: XmString msg;
*warningDialog1.fcode: switch (parametro) {\
      case 0:\
         msg=XmStringCreateSimple("Error in 'Var Lego' field!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 1:\
         msg=XmStringCreateSimple("Error in Low Lim field!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 2:\
         msg=XmStringCreateSimple("Low Lim greather than High Lim!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 3:\
         msg=XmStringCreateSimple("Unit Mis string is empty!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 4:\
         msg=XmStringCreateSimple("Error in change color field!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 5:\
         msg=XmStringCreateSimple("Error opening file f22circ!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 6:\
         msg=XmStringCreateSimple("Error reading name-descr variables!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 7:\
         msg=XmStringCreateSimple("Error in High Lim field!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
      case 8:\
         msg=XmStringCreateSimple("Error in selection field!!!");\
         XtVaSetValues(warningDialog1,XmNmessageString,msg,NULL);\
         XtFree(msg);\
         break;\
   }\
   UxPopupInterface(rtrn,no_grab);\
\
return(rtrn);\

*warningDialog1.auxdecl:
*warningDialog1.static: true
*warningDialog1.name: warningDialog1
*warningDialog1.parent: NO_PARENT
*warningDialog1.parentExpression: UxParent
*warningDialog1.defaultShell: topLevelShell
*warningDialog1.msgDialogType: "dialog_warning"
*warningDialog1.width: 400
*warningDialog1.height: 220
*warningDialog1.isCompound: "true"
*warningDialog1.compoundIcon: "warningD.xpm"
*warningDialog1.compoundName: "warning_Dialog"
*warningDialog1.x: 340
*warningDialog1.y: 520
*warningDialog1.unitType: "pixels"
*warningDialog1.dialogStyle: "dialog_full_application_modal"
*warningDialog1.messageAlignment: "alignment_center"
*warningDialog1.background: "WhiteSmoke"

