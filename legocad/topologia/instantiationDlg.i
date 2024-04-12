! UIMX ascii 2.0 key: 3297                                                      

*instantiationDlg.class: bulletinBoard
*instantiationDlg.parent: NO_PARENT
*instantiationDlg.defaultShell: topLevelShell
*instantiationDlg.static: false
*instantiationDlg.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo instantiationDlg.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)instantiationDlg.i	2.24\
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
#include "UxSubproc.h"\
#include "lg1.h"\
extern char blockname[];\
extern handle id_subproc;\
int num_modulo;\
void istanzia_blocco();\
char s_num_modulo[10];\

*instantiationDlg.ispecdecl:
*instantiationDlg.funcdecl: swidget create_instantiationDlg()\

*instantiationDlg.funcname: create_instantiationDlg
*instantiationDlg.funcdef: "swidget", "<create_instantiationDlg>(%)"
*instantiationDlg.icode:
*instantiationDlg.fcode: return(rtrn);\

*instantiationDlg.auxdecl: void istanzia_blocco(pid,status,h)\
int pid,status;\
handle h;\
{\
    extern void add_block();\
    Arg argo[3];\
    Cardinal nargo=0;\
\
    printf("\n istanzia blocco richiamata pid = %d status = %d",pid,status);\
\
    nargo=0;\
    XtSetArg(argo[0],XmNvalue,"");nargo++;\
    XtSetValues(output_text,argo,nargo);\
    XtSetValues(input_text,argo,nargo);\
\
    UxPopdownInterface(instantiationDlg);\
\
    add_block(PROCESSO);\
\
}
*instantiationDlg.name: instantiationDlg
*instantiationDlg.resizePolicy: "resize_none"
*instantiationDlg.unitType: "pixels"
*instantiationDlg.x: 310
*instantiationDlg.y: 156
*instantiationDlg.width: 510
*instantiationDlg.height: 580
*instantiationDlg.dialogTitle: "Instantiation Dialog"
*instantiationDlg.mapCallback: {\
\
}
*instantiationDlg.mappedWhenManaged: "true"
*instantiationDlg.destroyCallback: {\
\
}
*instantiationDlg.createCallback: {\
\
}
*instantiationDlg.unmapCallback: {\
\
}
*instantiationDlg.defaultButton: "send_button"

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: instantiationDlg
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 10
*scrolledWindow1.y: 20
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.destroyCallback: {\
printf("DESTROY VALLBACK DELLA SCROLLED WINDOW\n");\
}

*output_text.class: scrolledText
*output_text.parent: scrolledWindow1
*output_text.static: false
*output_text.name: output_text
*output_text.width: 490
*output_text.height: 480
*output_text.scrollHorizontal: "false"
*output_text.scrollVertical: "true"
*output_text.scrollLeftSide: "false"

*input_text.class: text
*input_text.parent: instantiationDlg
*input_text.static: true
*input_text.name: input_text
*input_text.x: 10
*input_text.y: 520
*input_text.width: 390
*input_text.height: 40

*send_button.class: pushButton
*send_button.parent: instantiationDlg
*send_button.static: true
*send_button.name: send_button
*send_button.x: 410
*send_button.y: 510
*send_button.width: 70
*send_button.height: 40
*send_button.labelString: "Send"
*send_button.activateCallback: {\
char s[128];\
strcpy(s,UxGetText(input_text));\
printf("stringa in input sulla window %s\n",s);\
\
UxSendSubproc(id_subproc, s);\
\
}
*send_button.showAsDefault: 1

