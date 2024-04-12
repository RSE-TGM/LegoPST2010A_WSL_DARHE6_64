! UIMX ascii 2.5 key: 7496                                                      

*fileSelection.class: fileSelectionBoxDialog
*fileSelection.gbldecl: #include <stdio.h>\
#ifndef DESIGN_TIME\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "cursore.h"\
#include "cont_rec.h"\
#include "file_selection.h"\
#endif\
#include "messaggi.h"\
#ifndef VAR_FOR_CR_PATTERN\
#define VAR_FOR_CR_PATTERN    "*.edf"\
#endif\
#ifndef PREVIEW_FILE_PATTERN\
#define PREVIEW_FILE_PATTERN  "*.view"\
#endif\
extern char *fileSelectionCb();\

*fileSelection.ispecdecl: char file_target[100];\
int r;
*fileSelection.ispeclist: file_target, r
*fileSelection.ispeclist.file_target: "unsigned char", "%file_target%[100]"
*fileSelection.ispeclist.r: "int", "%r%"
*fileSelection.funcdecl: char *create_fileSelection(w,modo,app)\
Widget w;     /* interfaccia chiamante  */\
int modo;     /* lettura / scrittura    */\
int app;      /* funziona chiamante     */
*fileSelection.funcname: create_fileSelection
*fileSelection.funcdef: "unsigned char", "*<create_fileSelection>(%)"
*fileSelection.argdecl: Widget w;\
int modo;\
int app;
*fileSelection.arglist: w, modo, app
*fileSelection.arglist.w: "Widget", "%w%"
*fileSelection.arglist.modo: "int", "%modo%"
*fileSelection.arglist.app: "int", "%app%"
*fileSelection.icode:
*fileSelection.fcode: XtUnmanageChild (\
    XmFileSelectionBoxGetChild(UxGetWidget(rtrn),XmDIALOG_HELP_BUTTON));\
XtUnmanageChild (\
    XmFileSelectionBoxGetChild(UxGetWidget(rtrn),XmDIALOG_DIR_LIST));\
XtUnmanageChild (\
    XmFileSelectionBoxGetChild(UxGetWidget(rtrn),XmDIALOG_DIR_LIST_LABEL));\
#ifndef DESIGN_TIME\
switch (app)\
   {\
   case VAR_FOR_CR:\
      switch (modo)\
         {\
         case CARICA:\
            update_title (UxGetWidget(rtrn),LOAD_FILESEL);\
            break;\
         case SALVA:\
            update_title (UxGetWidget(rtrn),SAVE_FILESEL);\
            break;  \
         }\
      UxPutStrRes (rtrn, XmNpattern,VAR_FOR_CR_PATTERN);\
      break;\
   case PREVIEW_FILE:\
      switch (modo)\
         {\
         case CARICA:   \
            break;\
         case SALVA:\
            break;  \
         }\
      UxPutStrRes (rtrn, XmNpattern,PREVIEW_FILE_PATTERN);\
      break;   \
   }\
#endif\
UxPopupInterface (rtrn, no_grab);\
r = -1;\
while (r != 1)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
return(file_target);\

*fileSelection.auxdecl:
*fileSelection.name.source: public
*fileSelection.static: false
*fileSelection.name: fileSelection
*fileSelection.parent: NO_PARENT
*fileSelection.parentExpression: w
*fileSelection.defaultShell: topLevelShell
*fileSelection.unitType: "pixels"
*fileSelection.x: 430
*fileSelection.y: 380
*fileSelection.width: 290
*fileSelection.height: 380
*fileSelection.dialogStyle: "dialog_primary_application_modal"
*fileSelection.pattern: ""
*fileSelection.textColumns: 60
*fileSelection.okCallbackClientData: UxGetWidget(fileSelection)
*fileSelection.unmapCallback: {\
\
}
*fileSelection.okCallback: {\
#ifndef DESIGN_TIME\
XmFileSelectionBoxCallbackStruct *cbs;\
cbs = (XmFileSelectionBoxCallbackStruct *)UxCallbackArg;\
strcpy (file_target,fileSelectionCb ((Widget)UxClientData,\
                    cbs,\
                    modo,\
                    app));\
r = 1;\
DistruggiInterfaccia(XtParent(fileSelection));\
#endif\
}
*fileSelection.cancelCallback: {\
#ifndef DESIGN_TIME\
XmFileSelectionBoxCallbackStruct *cbs;\
cbs = (XmFileSelectionBoxCallbackStruct *)UxCallbackArg;\
fileSelectionCb ((Widget)UxClientData,\
                    cbs,\
                    modo,\
                    app);\
strcpy (file_target,"");\
r = 1;\
DistruggiInterfaccia (XtParent(fileSelection));\
#endif\
}
*fileSelection.cancelCallbackClientData: UxGetWidget(fileSelection)

