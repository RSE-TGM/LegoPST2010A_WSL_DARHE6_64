! UIMX ascii 2.0 key: 6613                                                      

*formDialog1.class: formDialog
*formDialog1.parent: NO_PARENT
*formDialog1.parentExpression: padre
*formDialog1.defaultShell: topLevelShell
*formDialog1.static: true
*formDialog1.gbldecl: #include <stdio.h>\

*formDialog1.ispecdecl:
*formDialog1.funcdecl: swidget create_formDialog1(padre)\
swidget padre;\

*formDialog1.funcname: create_formDialog1
*formDialog1.funcdef: "swidget", "<create_formDialog1>(%)"
*formDialog1.argdecl: swidget padre;
*formDialog1.arglist: padre
*formDialog1.arglist.padre: "swidget", "%padre%"
*formDialog1.icode:
*formDialog1.fcode: return(rtrn);\

*formDialog1.auxdecl:
*formDialog1.name: formDialog1
*formDialog1.unitType: "pixels"
*formDialog1.x: 80
*formDialog1.y: 220
*formDialog1.width: 410
*formDialog1.height: 530

*panedWindow1.class: panedWindow
*panedWindow1.parent: formDialog1
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.x: 0
*panedWindow1.y: 0
*panedWindow1.width: 410
*panedWindow1.height: 530

*form2.class: form
*form2.parent: panedWindow1
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.x: 0
*form2.y: 0
*form2.width: 410
*form2.height: 270

*form3.class: form
*form3.parent: panedWindow1
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.x: 0
*form3.y: 250
*form3.width: 410
*form3.height: 270

