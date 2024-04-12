! UIMX ascii 2.0 key: 562                                                       

*CopyForaus.class: fileSelectionBox
*CopyForaus.parent: NO_PARENT
*CopyForaus.defaultShell: topLevelShell
*CopyForaus.static: true
*CopyForaus.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo CopyForaus.i\
   tipo \
   release 1.3\
   data 5/17/95\
   reserved @(#)CopyForaus.i	1.3\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
\
#include <stdio.h>\
#include "legomain.h"
*CopyForaus.ispecdecl:
*CopyForaus.funcdecl: swidget create_CopyForaus()\

*CopyForaus.funcname: create_CopyForaus
*CopyForaus.funcdef: "swidget", "<create_CopyForaus>(%)"
*CopyForaus.icode:
*CopyForaus.fcode: return(rtrn);\

*CopyForaus.auxdecl:
*CopyForaus.name: CopyForaus
*CopyForaus.resizePolicy: "resize_none"
*CopyForaus.unitType: "pixels"
*CopyForaus.x: 280
*CopyForaus.y: 240
*CopyForaus.width: 300
*CopyForaus.height: 380
*CopyForaus.pattern: "foraus.for"
*CopyForaus.okCallback: {\
extern char path_modello[];\
char source_file[256];\
char dest_file[256];\
\
strcpy(source_file,UxGetTextString(CopyForaus));\
\
sprintf(dest_file,"%s/%s",path_modello,FILE_FORAUS);\
\
\
copy_file(source_file,dest_file);\
\
UxDestroyInterface(UxWidget);\
}
*CopyForaus.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}

