! UIMX ascii 2.0 key: 5286                                                      

*Message.class: messageBoxDialog
*Message.parent: NO_PARENT
*Message.defaultShell: topLevelShell
*Message.static: false
*Message.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Message.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Message.i	1.10\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
\
extern swidget Menu_graf;\
extern swidget fileSelectionBox1,create_fileSelectionBox1();\
extern int Input_Message;\
extern int Salvato;\

*Message.ispecdecl:
*Message.funcdecl: swidget create_Message()\

*Message.funcname: create_Message
*Message.funcdef: "swidget", "<create_Message>(%)"
*Message.icode:
*Message.fcode: return(rtrn);\

*Message.auxdecl:
*Message.name: Message
*Message.unitType: "pixels"
*Message.x: 235
*Message.y: 240
*Message.width: 330
*Message.height: 175
*Message.messageAlignment: "alignment_center"
*Message.autoUnmanage: "true"
*Message.allowOverlap: "true"
*Message.mappedWhenManaged: "true"
*Message.allowShellResize: "false"
*Message.dialogStyle: "dialog_full_application_modal"
*Message.dialogTitle: "Message"
*Message.messageString: ""
*Message.dialogType: "dialog_error"
*Message.noResize: "false"
*Message.okCallback: {\
Position PosX,PosY;\
\
if (Input_Message == 1)\
{\
	Salvato = 1;\
	Input_Message == 0;\
	fileSelectionBox1 = create_fileSelectionBox1();\
	get_something (Menu_graf, XmNx, &PosX);\
	get_something (Menu_graf, XmNy, &PosY);\
	set_something (fileSelectionBox1, XmNx, PosX+10);\
	set_something (fileSelectionBox1, XmNy, PosY+10);\
	UxPopupInterface(fileSelectionBox1,no_grab);\
}\
}

