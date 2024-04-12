! UIMX ascii 2.0 key: 4398                                                      

*bb_cambia_pag.class: bulletinBoardDialog
*bb_cambia_pag.parent: NO_PARENT
*bb_cambia_pag.defaultShell: topLevelShell
*bb_cambia_pag.static: true
*bb_cambia_pag.gbldecl: /*\
   modulo bb_cambia_pag.i\
   tipo \
   release 1.10\
   data 3/31/95\
   reserved @(#)bb_cambia_pag.i	1.10\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\

*bb_cambia_pag.ispecdecl:
*bb_cambia_pag.funcdecl: swidget create_bb_cambia_pag(fp,max_righe_d,text_doc,label_pag,offs,num_pag,\
                             pagina_ini)\
FILE *fp;\
int max_righe_d;\
swidget text_doc, label_pag;\
long *offs;\
int *num_pag, pagina_ini;\

*bb_cambia_pag.funcname: create_bb_cambia_pag
*bb_cambia_pag.funcdef: "swidget", "<create_bb_cambia_pag>(%)"
*bb_cambia_pag.argdecl: FILE *fp;\
int max_righe_d;\
swidget text_doc;\
swidget label_pag;\
long *offs;\
int *num_pag;\
int pagina_ini;
*bb_cambia_pag.arglist: fp, max_righe_d, text_doc, label_pag, offs, num_pag, pagina_ini
*bb_cambia_pag.arglist.fp: "FILE", "*%fp%"
*bb_cambia_pag.arglist.max_righe_d: "int", "%max_righe_d%"
*bb_cambia_pag.arglist.text_doc: "swidget", "%text_doc%"
*bb_cambia_pag.arglist.label_pag: "swidget", "%label_pag%"
*bb_cambia_pag.arglist.offs: "long", "*%offs%"
*bb_cambia_pag.arglist.num_pag: "int", "*%num_pag%"
*bb_cambia_pag.arglist.pagina_ini: "int", "%pagina_ini%"
*bb_cambia_pag.icode: char buf[20];
*bb_cambia_pag.fcode: sprintf(buf,"%d",*num_pag);\
XmTextSetString(UxGetWidget(text_page_no), buf);\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*bb_cambia_pag.auxdecl:
*bb_cambia_pag.name: bb_cambia_pag
*bb_cambia_pag.unitType: "pixels"
*bb_cambia_pag.x: 270
*bb_cambia_pag.y: 680
*bb_cambia_pag.width: 310
*bb_cambia_pag.height: 180
*bb_cambia_pag.dialogTitle: "CHANGE PAGE"
*bb_cambia_pag.background: "#4f9f9f"
*bb_cambia_pag.dialogStyle: "dialog_full_application_modal"
*bb_cambia_pag.noResize: "true"

*label8.class: label
*label8.parent: bb_cambia_pag
*label8.static: true
*label8.name: label8
*label8.x: 20
*label8.y: 10
*label8.width: 130
*label8.height: 34
*label8.labelString: "Go to page:"
*label8.background: "#4f9f9f"
*label8.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*text_page_no.class: text
*text_page_no.parent: bb_cambia_pag
*text_page_no.static: true
*text_page_no.name: text_page_no
*text_page_no.x: 160
*text_page_no.y: 10
*text_page_no.width: 100
*text_page_no.height: 34
*text_page_no.background: "#4f9f9f"

*separator1.class: separator
*separator1.parent: bb_cambia_pag
*separator1.static: true
*separator1.name: separator1
*separator1.x: -10
*separator1.y: 50
*separator1.width: 300
*separator1.height: 10
*separator1.background: "#4f9f9f"

*pushButton11.class: pushButton
*pushButton11.parent: bb_cambia_pag
*pushButton11.static: true
*pushButton11.name: pushButton11
*pushButton11.x: 80
*pushButton11.y: 70
*pushButton11.width: 140
*pushButton11.height: 34
*pushButton11.labelString: "Ok"
*pushButton11.background: "#4f9f9f"
*pushButton11.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushButton11.activateCallback: {\
char *str, buf[20];\
int num;\
long temp_offs;\
\
str = XmTextGetString(UxGetWidget(text_page_no));\
if (str != NULL)\
{\
   sscanf(str,"%d", &num);\
   free(str);\
   if (num == -1)\
      return;\
}\
else\
{\
   crea_errorDialog("Missing page number...");\
   return;\
}\
\
if (num-pagina_ini <= 0)\
   return;\
\
printf("vai alla pagina %d\n", num-pagina_ini);\
\
if ((temp_offs = vai_alla_pagina(fp, max_righe_d, num-pagina_ini)) == -1)\
{\
   crea_errorDialog("Page not found!");\
   return;\
}\
\
*num_pag = num;\
*offs = temp_offs;\
\
str = leggi_pagina(fp, max_righe_d);\
XmTextSetString(UxGetWidget(text_doc), str);\
free(str);\
\
sprintf(buf, "%d", *num_pag);\
set_label(UxGetWidget(label_pag), buf);\
\
UxDestroySwidget(bb_cambia_pag);\
}

