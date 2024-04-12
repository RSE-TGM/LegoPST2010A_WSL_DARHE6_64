! UIMX ascii 2.0 key: 6646                                                      

*fileSelectionBox.class: fileSelectionBox
*fileSelectionBox.parent: NO_PARENT
*fileSelectionBox.defaultShell: topLevelShell
*fileSelectionBox.static: true
*fileSelectionBox.gbldecl: /*\
   modulo fileSelectionBox.i\
   tipo \
   release 1.7\
   data 3/30/95\
   reserved @(#)fileSelectionBox.i	1.7\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
extern Widget toplevel_widget;\
Widget UxTopLevel;\

*fileSelectionBox.ispecdecl:
*fileSelectionBox.funcdecl: swidget create_fileSelectionBox(int *(Okcb()),int *(Cancelcb()), int *(Filtercb()),int *(Helpcb()) )\

*fileSelectionBox.funcname: create_fileSelectionBox
*fileSelectionBox.funcdef: "swidget", "<create_fileSelectionBox>(%)"
*fileSelectionBox.argdecl: int *(*Okcb)();\
int *(*Cancelcb)();\
int *(*Filtercb)();\
int *(*Helpcb)();
*fileSelectionBox.arglist: Okcb, Cancelcb, Filtercb, Helpcb
*fileSelectionBox.arglist.Okcb: "int", "*(*%Okcb%)()"
*fileSelectionBox.arglist.Cancelcb: "int", "*(*%Cancelcb%)()"
*fileSelectionBox.arglist.Filtercb: "int", "*(*%Filtercb%)()"
*fileSelectionBox.arglist.Helpcb: "int", "*(*%Helpcb%)()"
*fileSelectionBox.icode: \
UxTopLevel = toplevel_widget; \

*fileSelectionBox.fcode: UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*fileSelectionBox.auxdecl:
*fileSelectionBox.name: fileSelectionBox
*fileSelectionBox.resizePolicy: "resize_none"
*fileSelectionBox.unitType: "pixels"
*fileSelectionBox.x: 240
*fileSelectionBox.y: 168
*fileSelectionBox.applyCallback: {\
if( (Filtercb) != NULL)\
   Filtercb();\
}
*fileSelectionBox.cancelCallback: {\
if( (Cancelcb) != NULL)\
   Cancelcb(); \
\
UxDestroyInterface(fileSelectionBox);\
}
*fileSelectionBox.helpCallback: {\
if( (Helpcb) != NULL)\
   Helpcb();\
}
*fileSelectionBox.okCallback: {\
if( (Okcb) != NULL)\
   Okcb();\
}

