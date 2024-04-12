! UIMX ascii 2.0 key: 5231                                                      

*IconvertExitDialog.class: messageBoxDialog
*IconvertExitDialog.parent: NO_PARENT
*IconvertExitDialog.defaultShell: topLevelShell
*IconvertExitDialog.static: true
*IconvertExitDialog.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo IconvertExitDialog.i\
   tipo \
   release 1.3\
   data 3/30/95\
   reserved @(#)IconvertExitDialog.i	1.3\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
#include <stdio.h>\

*IconvertExitDialog.ispecdecl:
*IconvertExitDialog.funcdecl: swidget create_IconvertExitDialog()\

*IconvertExitDialog.funcname: create_IconvertExitDialog
*IconvertExitDialog.funcdef: "swidget", "<create_IconvertExitDialog>(%)"
*IconvertExitDialog.icode:
*IconvertExitDialog.fcode: elimina_button();\
return(rtrn);\

*IconvertExitDialog.auxdecl: /* elimina_button\
\
   elimina i bottoni di help e cancel\
*/\
elimina_button()\
{\
   Widget hb;\
\
   hb = XmMessageBoxGetChild(IconvertExitDialog,XmDIALOG_HELP_BUTTON);\
   XtDestroyWidget(hb);\
   hb = XmMessageBoxGetChild(IconvertExitDialog,XmDIALOG_CANCEL_BUTTON);\
   XtDestroyWidget(hb);\
}\
  
*IconvertExitDialog.name: IconvertExitDialog
*IconvertExitDialog.unitType: "pixels"
*IconvertExitDialog.x: 480
*IconvertExitDialog.y: 470
*IconvertExitDialog.width: 430
*IconvertExitDialog.height: 130
*IconvertExitDialog.messageString: "        Iconvert Run Successifully.\nYou can see results in 'default' diagram page\n           Topology Quit Now. "
*IconvertExitDialog.okCallback: {\
exit(0);\
}

