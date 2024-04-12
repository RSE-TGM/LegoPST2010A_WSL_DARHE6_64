! UIMX ascii 2.0 key: 5023                                                      

*ModelSelection.class: fileSelectionBoxDialog
*ModelSelection.parent: NO_PARENT
*ModelSelection.parentExpression: parent
*ModelSelection.defaultShell: topLevelShell
*ModelSelection.static: true
*ModelSelection.gbldecl: /*\
   modulo ModelSelection.i\
   tipo \
   release 1.22\
   data 8/29/95\
   reserved @(#)ModelSelection.i	1.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "topsim.h"
*ModelSelection.ispecdecl:
*ModelSelection.funcdecl: swidget create_ModelSelection(swidget parent)\

*ModelSelection.funcname: create_ModelSelection
*ModelSelection.funcdef: "swidget", "<create_ModelSelection>(%)"
*ModelSelection.argdecl: swidget parent;
*ModelSelection.arglist: parent
*ModelSelection.arglist.parent: "swidget", "%parent%"
*ModelSelection.icode: char inidir[STRLONG];\
XmString xstring;\
\
if( getenv("LEGOCAD_USER") != NULL)\
   sprintf(inidir,"%s/legocad",getenv("LEGOCAD_USER"));\
else\
   if( getwd(inidir) == NULL )\
      sprintf(inidir,"%s","./");
*ModelSelection.fcode: xstring = XmStringCreateSimple(inidir);\
set_something(ModelSelection,XmNdirectory,xstring);\
\
\
return(rtrn);\

*ModelSelection.auxdecl:
*ModelSelection.name: ModelSelection
*ModelSelection.unitType: "pixels"
*ModelSelection.x: 432
*ModelSelection.y: 255
*ModelSelection.width: 255
*ModelSelection.height: 308
*ModelSelection.okCallback: {\
extern void set_sel_path();\
char lpath[STRLONG];\
\
strcpy(lpath, UxGetTextString(ModelSelection));  \
set_sel_path(lpath);\
\
UxDestroyInterface(UxWidget);\
}
*ModelSelection.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*ModelSelection.fileTypeMask: "file_directory"

