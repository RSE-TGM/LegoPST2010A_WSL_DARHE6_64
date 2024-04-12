! UIMX ascii 2.0 key: 7973                                                      

*dialogShell1.class: dialogShell
*dialogShell1.parent: NO_PARENT
*dialogShell1.static: true
*dialogShell1.gbldecl: #include <stdio.h>\

*dialogShell1.ispecdecl:
*dialogShell1.funcdecl: swidget popup_dialogShell1()\

*dialogShell1.funcname: popup_dialogShell1
*dialogShell1.funcdef: "swidget", "<popup_dialogShell1>(%)"
*dialogShell1.icode:
*dialogShell1.fcode: UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*dialogShell1.auxdecl:
*dialogShell1.name: dialogShell1
*dialogShell1.x: 190
*dialogShell1.y: 680
*dialogShell1.width: 340
*dialogShell1.height: 180

*messageBox1.class: messageBox
*messageBox1.parent: dialogShell1
*messageBox1.static: true
*messageBox1.name: messageBox1
*messageBox1.resizePolicy: "resize_any"
*messageBox1.unitType: "pixels"
*messageBox1.x: 168
*messageBox1.y: 465
*messageBox1.width: 310
*messageBox1.height: 140
*messageBox1.okCallback: {\
  extern void	exit();\
\
  exit(0);\
}
*messageBox1.dialogStyle: "dialog_primary_application_modal"
*messageBox1.dialogTitle: "Exit Dialog"
*messageBox1.dialogType: "dialog_question"
*messageBox1.messageString: "Exit From Application?"

