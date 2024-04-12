! UIMX ascii 2.0 key: 3453                                                      

*selectionBoxDialog1.class: selectionBoxDialog
*selectionBoxDialog1.parent: NO_PARENT
*selectionBoxDialog1.defaultShell: topLevelShell
*selectionBoxDialog1.static: true
*selectionBoxDialog1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo selectionBoxDialog1.i\
   tipo \
   release 1.21\
   data 5/12/95\
   reserved @(#)selectionBoxDialog1.i	1.21\
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
#include "legomain.h"
*selectionBoxDialog1.ispecdecl: char output_fil[256];\

*selectionBoxDialog1.ispeclist: output_fil
*selectionBoxDialog1.ispeclist.output_fil: "unsigned char", "%output_fil%[256]"
*selectionBoxDialog1.funcdecl: swidget create_selectionBoxDialog1()\

*selectionBoxDialog1.funcname: create_selectionBoxDialog1
*selectionBoxDialog1.funcdef: "swidget", "<create_selectionBoxDialog1>(%)"
*selectionBoxDialog1.icode:
*selectionBoxDialog1.fcode: return(rtrn);\

*selectionBoxDialog1.auxdecl: copy_fileoutedi14()\
{\
   copy_file("edi14.out",output_fil);\
  create_vis_msg("Result Copy File Terminated!");\
}
*selectionBoxDialog1.name: selectionBoxDialog1
*selectionBoxDialog1.unitType: "pixels"
*selectionBoxDialog1.x: 340
*selectionBoxDialog1.y: 380
*selectionBoxDialog1.width: 330
*selectionBoxDialog1.height: 370
*selectionBoxDialog1.dialogType: "dialog_error"
*selectionBoxDialog1.selectionLabelString: "Save resutl edi14 on file..."
*selectionBoxDialog1.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*selectionBoxDialog1.okCallback: {\
extern swidget create_question_operation();\
char comando[256];\
char *fileselected; \
FILE *fp;\
\
strcpy(output_fil,UxGetTextString(selectionBoxDialog1));\
\
printf("output_file = %s\n",output_fil);\
\
if( output_fil[0] == NULL)\
{\
   create_vis_msg("Invalid Selection");\
   return;\
}\
\
if( (fp = fopen(output_fil,"r")) != NULL)\
{\
   fclose(fp);\
   create_question_operation(UxWidget,Q_OVERWRITE_FILEOUTEDI14);\
}       \
else\
{\
   copy_fileoutedi14();\
}\
\
\
\
}

