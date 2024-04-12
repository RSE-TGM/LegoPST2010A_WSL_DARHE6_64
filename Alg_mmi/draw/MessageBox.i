! UIMX ascii 2.5 key: 3137                                                      

*MessageBox.class: messageBoxDialog
*MessageBox.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo MessageBox.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)MessageBox.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\

*MessageBox.ispecdecl: Widget Chiamante;\
char *NomeDelFile;
*MessageBox.ispeclist: Chiamante, NomeDelFile
*MessageBox.ispeclist.Chiamante: "Widget", "%Chiamante%"
*MessageBox.ispeclist.NomeDelFile: "unsigned char", "*%NomeDelFile%"
*MessageBox.funcdecl: swidget create_MessageBox(Widget Chia,char *NFile)\

*MessageBox.funcname: create_MessageBox
*MessageBox.funcdef: "swidget", "<create_MessageBox>(%)"
*MessageBox.argdecl: Widget Chia;\
unsigned char *NFile;
*MessageBox.arglist: Chia, NFile
*MessageBox.arglist.Chia: "Widget", "%Chia%"
*MessageBox.arglist.NFile: "unsigned char", "*%NFile%"
*MessageBox.icode: XmString XmMess;\
\
Chiamante = Chia;\
NomeDelFile = NFile;
*MessageBox.fcode: /*  Setto il messaggio da visualizzare  */\
XmMess = XmStringCreateSimple ("File already exist! Overwrite?");\
set_something (MessageBox, XmNmessageString, XmMess);\
return(rtrn);\

*MessageBox.auxdecl:  
*MessageBox.static: true
*MessageBox.name: MessageBox
*MessageBox.parent: NO_PARENT
*MessageBox.parentExpression: Chiamante
*MessageBox.defaultShell: topLevelShell
*MessageBox.unitType: "pixels"
*MessageBox.x: 650
*MessageBox.y: 260
*MessageBox.width: 280
*MessageBox.height: 180
*MessageBox.cancelCallback: {\
XtDestroyWidget (MessageBox);\
}
*MessageBox.okCallback: {\
#ifndef ON_PAGEDIT\
extern Widget FinestraDraw;\
 \
WriteBackground (FinestraDraw,NomeDelFile);\
XtDestroyWidget (Chiamante);\
XtDestroyWidget (MessageBox);\
#endif\
\
}
*MessageBox.labelFontList: "-adobe-itc avant garde gothic-demi-r-normal--14-140-75-75-p-82-iso8859-1"
*MessageBox.dialogStyle: "dialog_primary_application_modal"

