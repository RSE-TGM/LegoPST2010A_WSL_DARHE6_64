! UIMX ascii 2.0 key: 1806                                                      

*exitdialogShell1.class: dialogShell
*exitdialogShell1.parent: NO_PARENT
*exitdialogShell1.static: false
*exitdialogShell1.gbldecl: /*\
   modulo dialogShell1.i\
   tipo \
   release 2.6\
   data 3/20/95\
   reserved @(#)dialogShell1.i	2.6\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/MwmUtil.h>
*exitdialogShell1.ispecdecl:
*exitdialogShell1.funcdecl: swidget create_exitdialogShell1()\

*exitdialogShell1.funcname: create_exitdialogShell1
*exitdialogShell1.funcdef: "swidget", "<create_exitdialogShell1>(%)"
*exitdialogShell1.icode:
*exitdialogShell1.fcode: return(rtrn);\

*exitdialogShell1.auxdecl:
*exitdialogShell1.name: exitdialogShell1
*exitdialogShell1.x: 550
*exitdialogShell1.y: 560
*exitdialogShell1.width: 320
*exitdialogShell1.height: 170
*exitdialogShell1.mwmDecorations: MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU
*exitdialogShell1.mwmFunctions: MWM_FUNC_MOVE | MWM_FUNC_CLOSE
*exitdialogShell1.mwmInputMode: 0
*exitdialogShell1.title: "Exit Application"

*messageBox1.class: messageBox
*messageBox1.parent: exitdialogShell1
*messageBox1.static: true
*messageBox1.name: messageBox1
*messageBox1.resizePolicy: "resize_none"
*messageBox1.unitType: "pixels"
*messageBox1.x: 550
*messageBox1.y: 560
*messageBox1.width: 290
*messageBox1.height: 130
*messageBox1.dialogStyle: "dialog_primary_application_modal"
*messageBox1.dialogTitle: "Filter "
*messageBox1.dialogType: "dialog_question"
*messageBox1.messageString: "Exit from Filter Definition?"
*messageBox1.okCallback: {\
   extern void exit();\
   extern FILE* fpedf;\
   int i=10;\
\
   printf("\nQuit\n");\
   \
   exit(0);\
}

