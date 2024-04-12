! UIMX ascii 2.0 key: 4864                                                      

*fileSelectionBox1.class: fileSelectionBox
*fileSelectionBox1.parent: NO_PARENT
*fileSelectionBox1.defaultShell: topLevelShell
*fileSelectionBox1.static: false
*fileSelectionBox1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo fileSelectionBox1.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)fileSelectionBox1.i	1.10\
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
\
extern swidget Menu_graf;\
extern char *path_22dat,f22source[],f22target[],f22undo[];\
extern XmString label_path_f22;\
extern int non_f22;\
extern char *getcwd();\
\
char *path_22dat_appo;\

*fileSelectionBox1.ispecdecl:
*fileSelectionBox1.funcdecl: swidget create_fileSelectionBox1()\

*fileSelectionBox1.funcname: create_fileSelectionBox1
*fileSelectionBox1.funcdef: "swidget", "<create_fileSelectionBox1>(%)"
*fileSelectionBox1.icode:
*fileSelectionBox1.fcode: return(rtrn);\

*fileSelectionBox1.auxdecl:
*fileSelectionBox1.name: fileSelectionBox1
*fileSelectionBox1.resizePolicy: "resize_none"
*fileSelectionBox1.unitType: "pixels"
*fileSelectionBox1.x: 400
*fileSelectionBox1.y: 515
*fileSelectionBox1.width: 415
*fileSelectionBox1.height: 462
*fileSelectionBox1.cancelCallback: {\
UxPopdownInterface (fileSelectionBox1);\
}
*fileSelectionBox1.okCallback: {\
char appogg[100],cdo[200];\
Widget Figlio;\
\
CancellazioneF22();\
Figlio = XmFileSelectionBoxGetChild (fileSelectionBox1,XmDIALOG_TEXT);\
path_22dat_appo = XmTextGetString (Figlio);\
path_22dat = XmTextGetString (Figlio);\
\
strcpy (appogg,getcwd((char *)NULL,50));\
strcpy (f22source,tempnam(appogg, (char *)NULL ));\
strcpy (f22target,tempnam(appogg, (char *)NULL ));\
strcpy (f22undo,tempnam(appogg, (char *)NULL ));\
\
strcpy (path_22dat,f22source);\
strcat (path_22dat_appo,"\0");\
strcpy (cdo,"cp \0");\
strcat (cdo,path_22dat_appo);\
strcat (cdo," ");\
strcat (cdo,f22source);\
\
system (cdo);\
\
Carica_f22();\
\
if (!non_f22) UxPopdownInterface (fileSelectionBox1);\
}
*fileSelectionBox1.textString.source: public
*fileSelectionBox1.textString: "/usr/users/svilcad/masperi/UxXt.c"
*fileSelectionBox1.pattern: "*"
*fileSelectionBox1.dirMask: ""

