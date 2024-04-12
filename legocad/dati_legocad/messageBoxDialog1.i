! UIMX ascii 2.0 key: 8174                                                      

*messageBoxDialog1.class: messageBoxDialog
*messageBoxDialog1.parent: NO_PARENT
*messageBoxDialog1.defaultShell: topLevelShell
*messageBoxDialog1.static: true
*messageBoxDialog1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo messageBoxDialog1.i\
   tipo \
   release 2.15\
   data 4/26/95\
   reserved @(#)messageBoxDialog1.i	2.15\
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

*messageBoxDialog1.ispecdecl:
*messageBoxDialog1.funcdecl: swidget create_vis_msg(MyMessage)\
char *MyMessage;
*messageBoxDialog1.funcname: create_vis_msg
*messageBoxDialog1.funcdef: "swidget", "<create_vis_msg>(%)"
*messageBoxDialog1.argdecl: unsigned char *MyMessage;
*messageBoxDialog1.arglist: MyMessage
*messageBoxDialog1.arglist.MyMessage: "unsigned char", "*%MyMessage%"
*messageBoxDialog1.icode:
*messageBoxDialog1.fcode: UxPutMessageString(rtrn,MyMessage);\
UxPopupInterface(rtrn,no_grab);\
\
return(rtrn);\

*messageBoxDialog1.auxdecl:
*messageBoxDialog1.name: messageBoxDialog1
*messageBoxDialog1.unitType: "pixels"
*messageBoxDialog1.x: 250
*messageBoxDialog1.y: 250
*messageBoxDialog1.width: 270
*messageBoxDialog1.height: 110
*messageBoxDialog1.messageString: ""

