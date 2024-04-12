! UIMX ascii 2.0 key: 3254                                                      

*CopyS01.class: fileSelectionBox
*CopyS01.parent: NO_PARENT
*CopyS01.defaultShell: topLevelShell
*CopyS01.static: true
*CopyS01.gbldecl: /*\
   modulo CopyS01.i\
   tipo \
   release 1.1\
   data 11/23/95\
   reserved @(#)CopyS01.i	1.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "topsim.h"\
#include "lg1_topsim.h"\
\
extern SIMULATORE *simulatore;
*CopyS01.ispecdecl:
*CopyS01.funcdecl: swidget create_CopyS01()\

*CopyS01.funcname: create_CopyS01
*CopyS01.funcdef: "swidget", "<create_CopyS01>(%)"
*CopyS01.icode:
*CopyS01.fcode: return(rtrn);\

*CopyS01.auxdecl: copy_from(char *from)\
{\
    extern int set_wait_cursior(),set_normal_cursor();\
    char comando[512];\
\
    set_wait_cursor();\
\
    sprintf(comando,"cp %s %s",from,simulatore->path);\
    system(comando);\
\
    printf("copy S01 from %s to %s\n",from,simulatore->path);\
    set_normal_cursor();\
}\

*CopyS01.name: CopyS01
*CopyS01.resizePolicy: "resize_none"
*CopyS01.unitType: "pixels"
*CopyS01.x: 433
*CopyS01.y: 388
*CopyS01.width: 421
*CopyS01.height: 415
*CopyS01.selectionLabelString: "Copy S01 from"
*CopyS01.dirMask: "./S01*"
*CopyS01.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*CopyS01.okCallback: {\
char selec[STRLONG];\
\
strcpy(selec,UxGetTextString(CopyS01));\
copy_from(selec);\
UxDestroyInterface(UxWidget);\
}

