! UIMX ascii 2.0 key: 7321                                                      

*ViewS01.class: topLevelShell
*ViewS01.parent: NO_PARENT
*ViewS01.static: true
*ViewS01.gbldecl: /*\
   modulo ViewS01.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)ViewS01.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\

*ViewS01.ispecdecl: char *stringa;
*ViewS01.ispeclist: stringa
*ViewS01.ispeclist.stringa: "unsigned char", "*%stringa%"
*ViewS01.funcdecl: swidget create_ViewS01(char *filename)\

*ViewS01.funcname: create_ViewS01
*ViewS01.funcdef: "swidget", "<create_ViewS01>(%)"
*ViewS01.argdecl: unsigned char *filename;
*ViewS01.arglist: filename
*ViewS01.arglist.filename: "unsigned char", "*%filename%"
*ViewS01.icode: extern int view_file();\

*ViewS01.fcode: stringa = NULL;\
   \
view_file(filename,&stringa);\
\
XmTextSetString (scrolledText2,stringa);  \
\
return(rtrn);\

*ViewS01.auxdecl:
*ViewS01.name: ViewS01
*ViewS01.x: 520
*ViewS01.y: 290
*ViewS01.width: 490
*ViewS01.height: 620

*panedWindow4.class: panedWindow
*panedWindow4.parent: ViewS01
*panedWindow4.static: true
*panedWindow4.name: panedWindow4
*panedWindow4.unitType: "pixels"
*panedWindow4.x: 100
*panedWindow4.y: 100
*panedWindow4.width: 280
*panedWindow4.height: 330
*panedWindow4.destroyCallback: {\
\
}

*form6.class: form
*form6.parent: panedWindow4
*form6.static: true
*form6.name: form6
*form6.resizePolicy: "resize_any"
*form6.x: 0
*form6.y: 460
*form6.width: 490
*form6.height: 160
*form6.paneMinimum: 200

*pushButton3.class: pushButton
*pushButton3.parent: form6
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.x: 20
*pushButton3.y: 520
*pushButton3.width: 90
*pushButton3.height: 30
*pushButton3.labelString: "Ok"
*pushButton3.bottomAttachment: "attach_form"
*pushButton3.bottomOffset: 20
*pushButton3.topAttachment: "attach_none"
*pushButton3.topOffset: 20
*pushButton3.topWidget: ""
*pushButton3.leftAttachment: "attach_form"
*pushButton3.leftOffset: 40
*pushButton3.bottomWidget: ""
*pushButton3.activateCallback: {\
if( stringa != NULL)\
   free( stringa );\
UxDestroyInterface(ViewS01);\
}

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.parent: form6
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.scrollingPolicy: "automatic"
*scrolledWindow4.x: 0
*scrolledWindow4.y: 60
*scrolledWindow4.visualPolicy: "constant"
*scrolledWindow4.scrollBarDisplayPolicy: "as_needed"
*scrolledWindow4.shadowThickness: 0
*scrolledWindow4.bottomAttachment: "attach_widget"
*scrolledWindow4.leftAttachment: "attach_form"
*scrolledWindow4.rightAttachment: "attach_form"
*scrolledWindow4.topAttachment: "attach_form"
*scrolledWindow4.topOffset: 60
*scrolledWindow4.bottomOffset: 20
*scrolledWindow4.bottomWidget: "pushButton3"

*scrolledText2.class: scrolledText
*scrolledText2.parent: scrolledWindow4
*scrolledText2.static: true
*scrolledText2.name: scrolledText2
*scrolledText2.width: 480
*scrolledText2.height: 450
*scrolledText2.editMode: "multi_line_edit"
*scrolledText2.editable: "false"

*label3.class: label
*label3.parent: form6
*label3.static: true
*label3.name: label3
*label3.x: 80
*label3.y: 20
*label3.width: 260
*label3.height: 30
*label3.labelString: "View S01"
*label3.fontList: "helvetica_bold18"
*label3.leftAttachment: "attach_form"
*label3.rightAttachment: "attach_form"
*label3.topAttachment: "attach_form"
*label3.bottomAttachment: "attach_widget"
*label3.bottomWidget: "scrolledWindow4"
*label3.bottomOffset: 10

*pushButton4.class: pushButton
*pushButton4.parent: form6
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.x: 280
*pushButton4.y: 510
*pushButton4.width: 90
*pushButton4.height: 30
*pushButton4.labelString: "Cancel"
*pushButton4.topAttachment: "attach_none"
*pushButton4.topOffset: 20
*pushButton4.topWidget: ""
*pushButton4.bottomAttachment: "attach_form"
*pushButton4.bottomOffset: 20
*pushButton4.rightAttachment: "attach_form"
*pushButton4.rightOffset: 20
*pushButton4.leftAttachment: "attach_none"
*pushButton4.leftWidget: ""
*pushButton4.leftOffset: 30
*pushButton4.activateCallback: {\
if( stringa != NULL)\
   XtFree( stringa );\
UxDestroyInterface(ViewS01);\
\
}

