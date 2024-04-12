! UIMX ascii 2.0 key: 3704                                                      

*applEditf01.class: applicationShell
*applEditf01.parent: NO_PARENT
*applEditf01.static: true
*applEditf01.gbldecl: /*\
   modulo applicationShell1.i\
   tipo \
   release 2.6\
   data 3/20/95\
   reserved @(#)applicationShell1.i	2.6\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/MainW.h>\
#include <libutilx.h>\
/*\
   #include <UxMainW.h>\
*/\
\
char filename[FILENAME_MAX];\
char font[100];\
Widget texto;\
int editare;\
Dialog_geometry geom;\
Elenco_callback funz;\
extern Widget editor();\

*applEditf01.ispecdecl:
*applEditf01.funcdecl: swidget create_applEditf01()\

*applEditf01.funcname: create_applEditf01
*applEditf01.funcdef: "swidget", "<create_applEditf01>(%)"
*applEditf01.icode:
*applEditf01.fcode: return(rtrn);\

*applEditf01.auxdecl: void OkCB()\
{\
   exit(0);\
}\
\
lancia_edit(char *fname,int edit)\
{\
   Arg args[20];\
   int narg;\
   char butt_label[10];\
   swidget gost;\
\
   geom.default_pos = False;   \
   geom.x = 20;\
   geom.y = 100;\
   geom.width = 750;\
   geom.height = 650;\
\
\
   strcpy(font,"8x13");\
\
   strcpy(butt_label,"Ok");\
   funz[0].button_label = butt_label;\
   funz[0].callback = OkCB;\
\
\
\
\
   narg = 0;\
   XtSetArg(args[narg],XmNminWidth,500); narg++;\
   XtSetArg(args[narg],XmNminHeight,400); narg++;   \
/**\
   gost = UxCreateMainWindow("Main",UxTopLevel);\
   UxCreateWidget(gost);\
**/\
  \
  gost = lcCreateMainWindow("Main",UxTopLevel);\
  editor(gost,&texto,fname,edit,font,funz,geom);\
\
   \
\
}
*applEditf01.name: applEditf01
*applEditf01.x: 139
*applEditf01.y: 109
*applEditf01.width: 320
*applEditf01.height: 320

*form1.class: form
*form1.parent: applEditf01
*form1.static: false
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.unitType: "pixels"
*form1.x: 50
*form1.y: 40
*form1.width: 290
*form1.height: 270

*fileBox1.class: fileSelectionBox
*fileBox1.parent: form1
*fileBox1.static: true
*fileBox1.name: fileBox1
*fileBox1.resizePolicy: "resize_none"
*fileBox1.x: 10
*fileBox1.y: 10
*fileBox1.width: 300
*fileBox1.height: 300
*fileBox1.okCallback: {\
char butt_label[10];\
\
geom.default_pos = True;\
geom.x = 200;\
geom.y = 100;\
geom.width = 10;\
geom.height = 20;\
\
editare = False;\
\
strcpy(filename,UxGetTextString(fileBox1));\
\
strcpy(font,"8x13");\
\
strcpy(butt_label,"Ok");\
funz[0].button_label = butt_label;\
funz[0].callback = OkCB;\
\
\
editor(UxGetWidget(form1),&texto,filename,editare,font,funz,geom);\
\
}
*fileBox1.cancelCallback: {\
exit(0);\
}

