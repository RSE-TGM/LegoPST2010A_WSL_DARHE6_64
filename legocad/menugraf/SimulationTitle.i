! UIMX ascii 2.0 key: 6138                                                      

*SimulationTitle.class: topLevelShell
*SimulationTitle.parent: NO_PARENT
*SimulationTitle.static: true
*SimulationTitle.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo SimulationTitle.i\
   tipo \
   release 1.7\
   data 3/28/95\
   reserved @(#)SimulationTitle.i	1.7\
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
#ifndef DESIGN_TIME\
#include <grsf22.h>\
extern S_HEAD1 header1;\
#endif
*SimulationTitle.ispecdecl:
*SimulationTitle.funcdecl: swidget create_SimulationTitle()\

*SimulationTitle.funcname: create_SimulationTitle
*SimulationTitle.funcdef: "swidget", "<create_SimulationTitle>(%)"
*SimulationTitle.icode: XmString Stringa;\
char *Valore;
*SimulationTitle.fcode: #ifndef DESIGN_TIME\
Valore = XtNewString (header1.titolo);\
#endif\
XmTextFieldSetString (textTitolo, Valore);\
Stringa = XmStringCreate (Valore, XmSTRING_DEFAULT_CHARSET);\
set_something (label14, XmNlabelString, Stringa);\
XtFree (Valore);\
XmStringFree (Stringa); \
return(rtrn);
*SimulationTitle.auxdecl:
*SimulationTitle.name: SimulationTitle
*SimulationTitle.x: 400
*SimulationTitle.y: 250
*SimulationTitle.width: 480
*SimulationTitle.height: 180
*SimulationTitle.allowShellResize: "true"
*SimulationTitle.iconName: "Simulation title"
*SimulationTitle.title: "Simulation Title"

*form2.class: form
*form2.parent: SimulationTitle
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.unitType: "pixels"
*form2.x: 70
*form2.y: 20
*form2.width: 480
*form2.height: 180

*separator8.class: separator
*separator8.parent: form2
*separator8.static: true
*separator8.name: separator8
*separator8.x: 10
*separator8.y: 100
*separator8.width: 460
*separator8.height: 20
*separator8.leftAttachment: "attach_form"
*separator8.leftOffset: 5
*separator8.rightAttachment: "attach_form"
*separator8.rightOffset: 5
*separator8.topAttachment: "attach_none"
*separator8.topOffset: 0

*textTitolo.class: textField
*textTitolo.parent: form2
*textTitolo.static: true
*textTitolo.name: textTitolo
*textTitolo.x: 10
*textTitolo.y: 60
*textTitolo.width: 460
*textTitolo.height: 40
*textTitolo.leftAttachment: "attach_form"
*textTitolo.leftOffset: 10
*textTitolo.rightAttachment: "attach_form"
*textTitolo.rightOffset: 10
*textTitolo.topAttachment: "attach_none"
*textTitolo.topOffset: 0
*textTitolo.bottomAttachment: "attach_widget"
*textTitolo.bottomOffset: 5
*textTitolo.bottomWidget: "separator8"
*textTitolo.maxLength: 64

*label14.class: label
*label14.parent: form2
*label14.static: true
*label14.name: label14
*label14.x: 20
*label14.y: 10
*label14.width: 440
*label14.height: 50
*label14.labelString: ""
*label14.rightAttachment: "attach_form"
*label14.rightOffset: 10
*label14.topAttachment: "attach_form"
*label14.topOffset: 10
*label14.leftAttachment: "attach_form"
*label14.leftOffset: 10
*label14.bottomAttachment: "attach_widget"
*label14.bottomOffset: 10
*label14.bottomWidget: "textTitolo"
*label14.alignment: "alignment_beginning"

*pushButton15.class: pushButton
*pushButton15.parent: form2
*pushButton15.static: true
*pushButton15.name: pushButton15
*pushButton15.x: 20
*pushButton15.y: 120
*pushButton15.width: 70
*pushButton15.height: 30
*pushButton15.labelString: "OK"
*pushButton15.bottomAttachment: "attach_form"
*pushButton15.bottomOffset: 10
*pushButton15.leftOffset: 10
*pushButton15.topAttachment: "attach_widget"
*pushButton15.topOffset: 5
*pushButton15.topWidget: "separator8"
*pushButton15.activateCallback: {\
char *Valore;\
\
Valore = XmTextFieldGetString (textTitolo);\
#ifndef DESIGN_TIME\
strcpy (header1.titolo,Valore);\
#endif\
CambiaTitolo();\
XtFree (Valore);\
XtDestroyWidget (SimulationTitle);\
}

*pushButton16.class: pushButton
*pushButton16.parent: form2
*pushButton16.static: true
*pushButton16.name: pushButton16
*pushButton16.x: 100
*pushButton16.y: 130
*pushButton16.width: 70
*pushButton16.height: 30
*pushButton16.labelString: "CANCEL"
*pushButton16.bottomAttachment: "attach_form"
*pushButton16.bottomOffset: 10
*pushButton16.leftAttachment: "attach_widget"
*pushButton16.leftOffset: 10
*pushButton16.leftWidget: "pushButton15"
*pushButton16.topAttachment: "attach_widget"
*pushButton16.topOffset: 5
*pushButton16.topWidget: "separator8"
*pushButton16.activateCallback: {\
XtDestroyWidget (SimulationTitle);\
}

