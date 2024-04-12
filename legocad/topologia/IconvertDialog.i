! UIMX ascii 2.0 key: 5362                                                      

*IconvertDialog.class: questionDialog
*IconvertDialog.parent: NO_PARENT
*IconvertDialog.defaultShell: topLevelShell
*IconvertDialog.static: true
*IconvertDialog.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo IconvertDialog.i\
   tipo \
   release 1.3\
   data 3/30/95\
   reserved @(#)IconvertDialog.i	1.3\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
#include <stdio.h>\

*IconvertDialog.ispecdecl:
*IconvertDialog.funcdecl: swidget create_IconvertDialog()\

*IconvertDialog.funcname: create_IconvertDialog
*IconvertDialog.funcdef: "swidget", "<create_IconvertDialog>(%)"
*IconvertDialog.icode:
*IconvertDialog.fcode: return(rtrn);\

*IconvertDialog.auxdecl: quitting()\
{\
    exit(0);\
}
*IconvertDialog.name: IconvertDialog
*IconvertDialog.dialogType: "dialog_question"
*IconvertDialog.unitType: "pixels"
*IconvertDialog.x: 390
*IconvertDialog.y: 400
*IconvertDialog.width: 420
*IconvertDialog.height: 160
*IconvertDialog.messageString: "Differnces between icon and list\nDo you want RUN ICONVERT?"
*IconvertDialog.okLabelString: "Yes"
*IconvertDialog.cancelLabelString: "No"
*IconvertDialog.cancelCallback: {\
/* quit del programma topologia */\
exit(0);\
}
*IconvertDialog.okCallback: {\
/* faccio girare iconvert */\
extern swidget create_IconvertExitDialog();\
system("iconvert");\
UxPopupInterface(create_IconvertExitDialog(),no_grab);\
}

