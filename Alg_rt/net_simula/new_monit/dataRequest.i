! UIMX ascii 2.8 key: 4228                                                      

*dataRequest.class: promptDialog
*dataRequest.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "bistrutt.h"\
char stringa[MAX_LUN_COMMENTO];\
int risp;
*dataRequest.ispecdecl:
*dataRequest.funcdecl: char *create_dataRequest(w,label_string,act)\
Widget w;\
char *label_string;\
char *act;\
\

*dataRequest.funcname: create_dataRequest
*dataRequest.funcdef: "char", "*<create_dataRequest>(%)"
*dataRequest.argdecl: Widget w;\
char *label_string;\
char *act;
*dataRequest.arglist: w, label_string, act
*dataRequest.arglist.w: "Widget", "%w%"
*dataRequest.arglist.label_string: "char", "*%label_string%"
*dataRequest.arglist.act: "char", "*%act%"
*dataRequest.icode: risp = 0;
*dataRequest.fcode: XtUnmanageChild (\
    XmSelectionBoxGetChild(UxGetWidget(rtrn),XmDIALOG_HELP_BUTTON));\
UxPopupInterface (rtrn,no_grab);\
\
while (risp == 0)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
printf ("chiusura sessionName\n");\
risp = 0;\
\
return(&stringa[0]);\

*dataRequest.auxdecl:
*dataRequest.static: true
*dataRequest.name: dataRequest
*dataRequest.parent: NO_PARENT
*dataRequest.parentExpression: w
*dataRequest.defaultShell: topLevelShell
*dataRequest.dialogType: "dialog_prompt"
*dataRequest.width: 360
*dataRequest.height: 160
*dataRequest.isCompound: "true"
*dataRequest.compoundIcon: "promptD.xpm"
*dataRequest.compoundName: "prompt_Dialog"
*dataRequest.x: 844
*dataRequest.y: 619
*dataRequest.unitType: "pixels"
*dataRequest.cancelLabelString: "Quit"
*dataRequest.createManaged: "false"
*dataRequest.selectionLabelString: label_string ? label_string : ""
*dataRequest.textString: act ? act : ""
*dataRequest.okCallbackClientData: dataRequest
*dataRequest.okCallback: {\
Widget campo_testo; \
Widget padre; \
char *t;\
\
   padre = (Widget)UxClientData;\
   campo_testo = XmSelectionBoxGetChild(padre,XmDIALOG_TEXT);\
   t = XmTextGetString (campo_testo);\
   strcpy (stringa,t);\
   XtFree (t);\
   DistruggiInterfaccia (XtParent(padre));\
   risp = 1;\
   \
\
}
*dataRequest.autoUnmanage: "false"
*dataRequest.cancelCallback: {\
Widget padre; \
   padre = (Widget)UxClientData;\
   strcpy (stringa,"");\
   DistruggiInterfaccia (XtParent(padre)); \
   risp = 1;  \
   return;\
\
}
*dataRequest.cancelCallbackClientData: dataRequest
*dataRequest.childPlacement: "place_above_selection"
*dataRequest.dialogStyle: "dialog_primary_application_modal"

