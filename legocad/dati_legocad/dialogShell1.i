! UIMX ascii 2.0 key: 5071                                                      

*dialogShell1.class: dialogShell
*dialogShell1.parent: NO_PARENT
*dialogShell1.parentExpression: padre
*dialogShell1.static: true
*dialogShell1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dialogShell1.i\
   tipo \
   release 2.15\
   data 4/26/95\
   reserved @(#)dialogShell1.i	2.15\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
#include <stdio.h>\

*dialogShell1.ispecdecl:
*dialogShell1.funcdecl: swidget popup_dialogShell1(padre)\
swidget padre;
*dialogShell1.funcname: popup_dialogShell1
*dialogShell1.funcdef: "swidget", "<popup_dialogShell1>(%)"
*dialogShell1.argdecl: swidget padre;
*dialogShell1.arglist: padre
*dialogShell1.arglist.padre: "swidget", "%padre%"
*dialogShell1.icode:
*dialogShell1.fcode: UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*dialogShell1.auxdecl:
*dialogShell1.name: dialogShell1
*dialogShell1.x: 440
*dialogShell1.y: 110
*dialogShell1.width: 560
*dialogShell1.height: 620

*panedWindow2.class: panedWindow
*panedWindow2.parent: dialogShell1
*panedWindow2.static: true
*panedWindow2.name: panedWindow2
*panedWindow2.unitType: "pixels"
*panedWindow2.x: 0
*panedWindow2.y: 0
*panedWindow2.width: 440
*panedWindow2.height: 510

*form2.class: form
*form2.parent: panedWindow2
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.x: 3
*form2.y: 3
*form2.width: 527
*form2.height: 250

*label2.class: label
*label2.parent: form2
*label2.static: true
*label2.name: label2
*label2.x: 40
*label2.y: 10
*label2.width: 210
*label2.height: 20
*label2.labelString: "INPUT TO MODEL"

*label8.class: label
*label8.parent: form2
*label8.static: true
*label8.name: label8
*label8.x: 250
*label8.y: 10
*label8.width: 210
*label8.height: 20
*label8.labelString: "OUTPUT TO MODEL"

*label9.class: label
*label9.parent: form2
*label9.static: true
*label9.name: label9
*label9.x: 20
*label9.y: 40
*label9.width: 210
*label9.height: 20
*label9.labelString: "known variables"
*label9.alignment: "alignment_beginning"

*label10.class: label
*label10.parent: form2
*label10.static: true
*label10.name: label10
*label10.x: 260
*label10.y: 40
*label10.width: 200
*label10.height: 20
*label10.labelString: "unknown variables"
*label10.alignment: "alignment_beginning"

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.parent: form2
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.scrollingPolicy: "application_defined"
*scrolledWindow4.x: 20
*scrolledWindow4.y: 60
*scrolledWindow4.visualPolicy: "variable"
*scrolledWindow4.scrollBarDisplayPolicy: "static"
*scrolledWindow4.shadowThickness: 0

*scrolledList5.class: scrolledList
*scrolledList5.parent: scrolledWindow4
*scrolledList5.static: true
*scrolledList5.name: scrolledList5
*scrolledList5.width: 220
*scrolledList5.height: 180

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.parent: form2
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.x: 260
*scrolledWindow5.y: 60
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0

*scrolledList6.class: scrolledList
*scrolledList6.parent: scrolledWindow5
*scrolledList6.static: true
*scrolledList6.name: scrolledList6
*scrolledList6.width: 230
*scrolledList6.height: 180

*form4.class: form
*form4.parent: panedWindow2
*form4.static: true
*form4.name: form4
*form4.resizePolicy: "resize_none"
*form4.x: 3
*form4.y: 261
*form4.width: 527
*form4.height: 319

*label11.class: label
*label11.parent: form4
*label11.static: true
*label11.name: label11
*label11.x: 260
*label11.y: 30
*label11.width: 210
*label11.height: 20
*label11.labelString: "known variables"
*label11.alignment: "alignment_beginning"

*label12.class: label
*label12.parent: form4
*label12.static: true
*label12.name: label12
*label12.x: 30
*label12.y: 30
*label12.width: 210
*label12.height: 20
*label12.labelString: "unknown variables"
*label12.alignment: "alignment_beginning"

*scrolledWindow7.class: scrolledWindow
*scrolledWindow7.parent: form4
*scrolledWindow7.static: true
*scrolledWindow7.name: scrolledWindow7
*scrolledWindow7.scrollingPolicy: "application_defined"
*scrolledWindow7.x: 30
*scrolledWindow7.y: 50
*scrolledWindow7.visualPolicy: "variable"
*scrolledWindow7.scrollBarDisplayPolicy: "static"
*scrolledWindow7.shadowThickness: 0

*scrolledList7.class: scrolledList
*scrolledList7.parent: scrolledWindow7
*scrolledList7.static: true
*scrolledList7.name: scrolledList7
*scrolledList7.width: 210
*scrolledList7.height: 200

*scrolledWindow8.class: scrolledWindow
*scrolledWindow8.parent: form4
*scrolledWindow8.static: true
*scrolledWindow8.name: scrolledWindow8
*scrolledWindow8.scrollingPolicy: "application_defined"
*scrolledWindow8.x: 260
*scrolledWindow8.y: 50
*scrolledWindow8.visualPolicy: "variable"
*scrolledWindow8.scrollBarDisplayPolicy: "static"
*scrolledWindow8.shadowThickness: 0

*scrolledList8.class: scrolledList
*scrolledList8.parent: scrolledWindow8
*scrolledList8.static: true
*scrolledList8.name: scrolledList8
*scrolledList8.width: 230
*scrolledList8.height: 200

*pushButtonGadget3.class: pushButtonGadget
*pushButtonGadget3.parent: form4
*pushButtonGadget3.static: true
*pushButtonGadget3.name: pushButtonGadget3
*pushButtonGadget3.x: 90
*pushButtonGadget3.y: 270
*pushButtonGadget3.width: 110
*pushButtonGadget3.height: 30
*pushButtonGadget3.labelString: "OK"

*pushButtonGadget4.class: pushButtonGadget
*pushButtonGadget4.parent: form4
*pushButtonGadget4.static: true
*pushButtonGadget4.name: pushButtonGadget4
*pushButtonGadget4.x: 320
*pushButtonGadget4.y: 270
*pushButtonGadget4.width: 110
*pushButtonGadget4.height: 30
*pushButtonGadget4.labelString: "Cancel"

