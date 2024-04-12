! UIMX ascii 2.0 key: 7590                                                      

*nameSessionReq.class: form
*nameSessionReq.parent: NO_PARENT
*nameSessionReq.defaultShell: topLevelShell
*nameSessionReq.static: true
*nameSessionReq.gbldecl: #include <stdio.h>\
char titolo[100];
*nameSessionReq.ispecdecl:
*nameSessionReq.funcdecl: swidget create_nameSessionReq(s)\
char *s;
*nameSessionReq.funcname: create_nameSessionReq
*nameSessionReq.funcdef: "swidget", "<create_nameSessionReq>(%)"
*nameSessionReq.argdecl: unsigned char *s;
*nameSessionReq.arglist: s
*nameSessionReq.arglist.s: "unsigned char", "*%s%"
*nameSessionReq.icode:
*nameSessionReq.fcode: return(rtrn);\

*nameSessionReq.auxdecl:
*nameSessionReq.name: nameSessionReq
*nameSessionReq.resizePolicy: "resize_none"
*nameSessionReq.unitType: "pixels"
*nameSessionReq.x: 579
*nameSessionReq.y: 47
*nameSessionReq.width: 450
*nameSessionReq.height: 200
*nameSessionReq.noResize: "true"

*form10.class: form
*form10.parent: nameSessionReq
*form10.static: true
*form10.name: form10
*form10.resizePolicy: "resize_none"
*form10.x: 16
*form10.y: 108
*form10.width: 750
*form10.height: 75
*form10.bottomAttachment: "attach_form"
*form10.leftOffset: 0
*form10.rightAttachment: "attach_form"
*form10.topAttachment: "attach_none"
*form10.topOffset: 0
*form10.leftAttachment: "attach_form"

*frame4.class: frame
*frame4.parent: form10
*frame4.static: true
*frame4.name: frame4
*frame4.x: 10
*frame4.y: 405
*frame4.width: 795
*frame4.height: 50
*frame4.bottomAttachment: "attach_form"
*frame4.leftOffset: 0
*frame4.rightAttachment: "attach_form"
*frame4.topOffset: 0
*frame4.leftAttachment: "attach_form"
*frame4.topAttachment: "attach_form"

*form11.class: form
*form11.parent: frame4
*form11.static: true
*form11.name: form11
*form11.resizePolicy: "resize_none"
*form11.x: 0
*form11.y: 0
*form11.width: 745
*form11.height: 72

*pushButton3.class: pushButton
*pushButton3.parent: form11
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.x: 493
*pushButton3.y: 35
*pushButton3.width: 202
*pushButton3.height: 30
*pushButton3.labelString: "QUIT"
*pushButton3.bottomAttachment: "attach_form"
*pushButton3.leftAttachment: "attach_self"
*pushButton3.rightAttachment: "attach_form"
*pushButton3.bottomOffset: 15
*pushButton3.rightOffset: 20
*pushButton3.leftPosition: 0
*pushButton3.leftOffset: 100
*pushButton3.topAttachment: "attach_form"
*pushButton3.topOffset: 15

*pushButton4.class: pushButton
*pushButton4.parent: form11
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.x: 30
*pushButton4.y: 405
*pushButton4.width: 205
*pushButton4.height: 30
*pushButton4.labelString: "SAVE"
*pushButton4.bottomAttachment: "attach_form"
*pushButton4.bottomOffset: 15
*pushButton4.leftOffset: 20
*pushButton4.rightAttachment: "attach_self"
*pushButton4.rightOffset: 100
*pushButton4.leftAttachment: "attach_form"
*pushButton4.topAttachment: "attach_form"
*pushButton4.topOffset: 15

*label11.class: label
*label11.parent: nameSessionReq
*label11.static: true
*label11.name: label11
*label11.x: 0
*label11.y: 0
*label11.width: 580
*label11.height: 30
*label11.labelString: "Session name"
*label11.background: "red"
*label11.rightAttachment: "attach_form"
*label11.leftAttachment: "attach_form"

*form12.class: form
*form12.parent: nameSessionReq
*form12.static: true
*form12.name: form12
*form12.resizePolicy: "resize_none"
*form12.x: 20
*form12.y: 45
*form12.width: 540
*form12.height: 80
*form12.rightAttachment: "attach_form"
*form12.rightOffset: 0
*form12.leftAttachment: "attach_form"
*form12.leftOffset: 0
*form12.resizable: "true"

*label12.class: label
*label12.parent: form12
*label12.static: true
*label12.name: label12
*label12.x: 0
*label12.y: 20
*label12.width: 110
*label12.height: 37
*label12.labelString: "Title:"

*textField1.class: textField
*textField1.parent: form12
*textField1.static: true
*textField1.name: textField1
*textField1.x: 90
*textField1.y: 25
*textField1.width: 445
*textField1.height: 35
*textField1.rightAttachment: "attach_form"
*textField1.leftAttachment: "attach_widget"
*textField1.leftWidget: "label12"
*textField1.rightOffset: 20

