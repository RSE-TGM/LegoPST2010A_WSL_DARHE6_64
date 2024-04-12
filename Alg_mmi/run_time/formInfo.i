! UIMX ascii 2.5 key: 5764                                                      

*formInfo.class: formDialog
*formInfo.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo formInfo.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)formInfo.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <X11/Intrinsic.h>\
#include <X11/StringDefs.h>\
#include <X11/Xlib.h>\
\
\
#include "other.h"\
\
\
Widget PadreInfo;\
\
static void InserisciTesto();\

*formInfo.ispecdecl: Widget topLevel_forminfo;\
XmFontList FontLabelFormInfo,FontListaFormInfo;\

*formInfo.ispeclist: topLevel_forminfo, FontLabelFormInfo, FontListaFormInfo
*formInfo.ispeclist.topLevel_forminfo: "Widget", "%topLevel_forminfo%"
*formInfo.ispeclist.FontLabelFormInfo: "XmFontList", "%FontLabelFormInfo%"
*formInfo.ispeclist.FontListaFormInfo: "XmFontList", "%FontListaFormInfo%"
*formInfo.funcdecl: swidget popup_formInfo(wid,PadreForminfo)\
Widget wid;\
Widget PadreForminfo;
*formInfo.funcname: popup_formInfo
*formInfo.funcdef: "swidget", "<popup_formInfo>(%)"
*formInfo.argdecl: Widget wid;\
Widget PadreForminfo;
*formInfo.arglist: wid, PadreForminfo
*formInfo.arglist.wid: "Widget", "%wid%"
*formInfo.arglist.PadreForminfo: "Widget", "%PadreForminfo%"
*formInfo.icode: #ifndef DESIGN_TIME\
if(XlIsXlCore(wid))\
     	{\
     	topLevel_forminfo=XtParent(wid);\
     	} 	\
else\
	{\
     	topLevel_forminfo=XtParent(XtParent(wid));\
	}\
#endif\
\
if(XlIsXlComposite(topLevel_forminfo))\
	topLevel_forminfo=XtParent(topLevel_forminfo);\
\
PadreInfo=topLevel_forminfo;\
\
\
\
\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LISTA,&FontListaFormInfo,XtDisplay(topLevel_forminfo)))\
	exit(0);\
if(!LoadFont(FONT_LABEL,&FontLabelFormInfo,XtDisplay(topLevel_forminfo)))\
	exit(0);\
#endif
*formInfo.fcode: set_something(labelInfo,XmNfontList,FontLabelFormInfo);\
set_something(pushButtonInfo,XmNfontList,FontLabelFormInfo);\
set_something(scrolledTextInfo,XmNfontList,FontListaFormInfo);\
UxPopupInterface(rtrn, no_grab);\
InserisciTesto(wid);\
return(rtrn);\

*formInfo.auxdecl: static void InserisciTesto(Widget oggettoSel)\
{\
char testo[10000];\
#ifndef DESIGN_TIME\
printf("Inserisci testo %s\n",XtName(oggettoSel));\
if(!PreparaTestoInfo(oggettoSel,testo))\
	return;\
set_something(scrolledTextInfo,XmNvalue,testo);\
#endif\
}
*formInfo.static: true
*formInfo.name: formInfo
*formInfo.parent: NO_PARENT
*formInfo.parentExpression: PadreInfo
*formInfo.defaultShell: topLevelShell
*formInfo.unitType: "pixels"
*formInfo.width: 470
*formInfo.height: 260
*formInfo.dialogTitle: "Info"
*formInfo.background: "#50a050"
*formInfo.defaultButton: "pushButtonInfo"
*formInfo.rubberPositioning: "true"

*labelInfo.class: label
*labelInfo.static: true
*labelInfo.name: labelInfo
*labelInfo.parent: formInfo
*labelInfo.x: 0
*labelInfo.y: 0
*labelInfo.width: 470
*labelInfo.height: 40
*labelInfo.labelString: "Info about ..."
*labelInfo.background: "#50a050"
*labelInfo.highlightThickness: 0
*labelInfo.shadowThickness: 0
*labelInfo.rightAttachment: "attach_form"
*labelInfo.leftAttachment: "attach_form"
*labelInfo.recomputeSize: "false"

*formTextInfo.class: form
*formTextInfo.static: true
*formTextInfo.name: formTextInfo
*formTextInfo.parent: formInfo
*formTextInfo.resizePolicy: "resize_none"
*formTextInfo.x: 0
*formTextInfo.y: 40
*formTextInfo.width: 470
*formTextInfo.height: 180
*formTextInfo.bottomAttachment: "attach_form"
*formTextInfo.bottomOffset: 60
*formTextInfo.leftOffset: 10
*formTextInfo.rightAttachment: "attach_form"
*formTextInfo.topAttachment: "attach_widget"
*formTextInfo.topOffset: 0
*formTextInfo.leftAttachment: "attach_form"
*formTextInfo.background: "#50a050"
*formTextInfo.rightOffset: 10
*formTextInfo.topWidget: "labelInfo"

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.parent: formTextInfo
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 0
*scrolledWindow2.y: 0
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.bottomAttachment: "attach_form"
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.topAttachment: "attach_form"
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.background: "#50a050"

*scrolledTextInfo.class: scrolledText
*scrolledTextInfo.static: true
*scrolledTextInfo.name: scrolledTextInfo
*scrolledTextInfo.parent: scrolledWindow2
*scrolledTextInfo.width: 450
*scrolledTextInfo.height: 140
*scrolledTextInfo.background: "#ffffff"
*scrolledTextInfo.cursorPositionVisible: "false"
*scrolledTextInfo.editMode: "multi_line_edit"
*scrolledTextInfo.editable: "false"
*scrolledTextInfo.wordWrap: "true"
*scrolledTextInfo.text: ""
*scrolledTextInfo.foreground: "#000000"

*formButtonInfo.class: form
*formButtonInfo.static: true
*formButtonInfo.name: formButtonInfo
*formButtonInfo.parent: formInfo
*formButtonInfo.resizePolicy: "resize_none"
*formButtonInfo.x: 20
*formButtonInfo.y: 210
*formButtonInfo.width: 430
*formButtonInfo.height: 60
*formButtonInfo.rightAttachment: "attach_form"
*formButtonInfo.leftAttachment: "attach_form"
*formButtonInfo.bottomAttachment: "attach_form"
*formButtonInfo.background: "#50a050"

*pushButtonInfo.class: pushButton
*pushButtonInfo.static: true
*pushButtonInfo.name: pushButtonInfo
*pushButtonInfo.parent: formButtonInfo
*pushButtonInfo.x: 350
*pushButtonInfo.y: 10
*pushButtonInfo.width: 100
*pushButtonInfo.height: 40
*pushButtonInfo.background: "#50a050"
*pushButtonInfo.labelString: "Close"
*pushButtonInfo.activateCallback: {\
FreeFont(FontLabelFormInfo,XtDisplay(formInfo));\
FreeFont(FontListaFormInfo,XtDisplay(formInfo));\
XtDestroyWidget(XtParent(formInfo));\
\
}
*pushButtonInfo.leftAttachment: "attach_none"
*pushButtonInfo.leftOffset: 0
*pushButtonInfo.rightAttachment: "attach_form"
*pushButtonInfo.rightOffset: 30
*pushButtonInfo.recomputeSize: "false"

