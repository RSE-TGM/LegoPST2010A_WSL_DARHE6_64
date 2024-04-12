! UIMX ascii 2.0 key: 9791                                                      

*note_dialog.class: dialogShell
*note_dialog.parent: NO_PARENT
*note_dialog.static: true
*note_dialog.gbldecl: #include <stdio.h>\

*note_dialog.funcdecl: swidget create_note_dialog()\

*note_dialog.funcname: create_note_dialog
*note_dialog.funcdef: "swidget", "<create_note_dialog>(%)"
*note_dialog.fcode: return(rtrn);\

*note_dialog.name: note_dialog
*note_dialog.x: 250
*note_dialog.y: 250
*note_dialog.width: 440
*note_dialog.height: 510
*note_dialog.title: "KNOWN - UNKNOWN"

*panedWindow1.class: panedWindow
*panedWindow1.parent: note_dialog
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.unitType: "pixels"
*panedWindow1.x: 0
*panedWindow1.y: 0
*panedWindow1.width: 440
*panedWindow1.height: 510

*form2.class: form
*form2.parent: panedWindow1
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

*label3.class: label
*label3.parent: form2
*label3.static: true
*label3.name: label3
*label3.x: 250
*label3.y: 10
*label3.width: 210
*label3.height: 20
*label3.labelString: "OUTPUT TO MODEL"

*label6.class: label
*label6.parent: form2
*label6.static: true
*label6.name: label6
*label6.x: 20
*label6.y: 40
*label6.width: 210
*label6.height: 20
*label6.labelString: "known variables"
*label6.alignment: "alignment_beginning"

*label7.class: label
*label7.parent: form2
*label7.static: true
*label7.name: label7
*label7.x: 260
*label7.y: 40
*label7.width: 200
*label7.height: 20
*label7.labelString: "unknown variables"
*label7.alignment: "alignment_beginning"

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form2
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 20
*scrolledWindow1.y: 60
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0

*scrolledList1.class: scrolledList
*scrolledList1.parent: scrolledWindow1
*scrolledList1.static: true
*scrolledList1.name: scrolledList1
*scrolledList1.width: 220
*scrolledList1.height: 180

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.parent: form2
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.scrollingPolicy: "application_defined"
*scrolledWindow4.x: 260
*scrolledWindow4.y: 60
*scrolledWindow4.visualPolicy: "variable"
*scrolledWindow4.scrollBarDisplayPolicy: "static"
*scrolledWindow4.shadowThickness: 0

*scrolledList2.class: scrolledList
*scrolledList2.parent: scrolledWindow4
*scrolledList2.static: true
*scrolledList2.name: scrolledList2
*scrolledList2.width: 230
*scrolledList2.height: 180

*form3.class: form
*form3.parent: panedWindow1
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.x: 3
*form3.y: 261
*form3.width: 527
*form3.height: 319

*label4.class: label
*label4.parent: form3
*label4.static: true
*label4.name: label4
*label4.x: 260
*label4.y: 30
*label4.width: 210
*label4.height: 20
*label4.labelString: "known variables"
*label4.alignment: "alignment_beginning"

*label5.class: label
*label5.parent: form3
*label5.static: true
*label5.name: label5
*label5.x: 30
*label5.y: 30
*label5.width: 210
*label5.height: 20
*label5.labelString: "unknown variables"
*label5.alignment: "alignment_beginning"

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.parent: form3
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.x: 30
*scrolledWindow5.y: 50
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0

*scrolledList3.class: scrolledList
*scrolledList3.parent: scrolledWindow5
*scrolledList3.static: true
*scrolledList3.name: scrolledList3
*scrolledList3.width: 210
*scrolledList3.height: 200

*scrolledWindow6.class: scrolledWindow
*scrolledWindow6.parent: form3
*scrolledWindow6.static: true
*scrolledWindow6.name: scrolledWindow6
*scrolledWindow6.scrollingPolicy: "application_defined"
*scrolledWindow6.x: 260
*scrolledWindow6.y: 50
*scrolledWindow6.visualPolicy: "variable"
*scrolledWindow6.scrollBarDisplayPolicy: "static"
*scrolledWindow6.shadowThickness: 0

*scrolledList4.class: scrolledList
*scrolledList4.parent: scrolledWindow6
*scrolledList4.static: true
*scrolledList4.name: scrolledList4
*scrolledList4.width: 230
*scrolledList4.height: 200

*pushButtonGadget1.class: pushButtonGadget
*pushButtonGadget1.parent: form3
*pushButtonGadget1.static: true
*pushButtonGadget1.name: pushButtonGadget1
*pushButtonGadget1.x: 90
*pushButtonGadget1.y: 270
*pushButtonGadget1.width: 110
*pushButtonGadget1.height: 30
*pushButtonGadget1.labelString: "OK"

*pushButtonGadget2.class: pushButtonGadget
*pushButtonGadget2.parent: form3
*pushButtonGadget2.static: true
*pushButtonGadget2.name: pushButtonGadget2
*pushButtonGadget2.x: 320
*pushButtonGadget2.y: 270
*pushButtonGadget2.width: 110
*pushButtonGadget2.height: 30
*pushButtonGadget2.labelString: "Cancel"

