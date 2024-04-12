! UIMX ascii 2.5 key: 4866                                                      

*archiveEdit.class: form
*archiveEdit.gbldecl: #include <stdio.h>\

*archiveEdit.ispecdecl:
*archiveEdit.funcdecl: swidget create_archiveEdit()\

*archiveEdit.funcname: create_archiveEdit
*archiveEdit.funcdef: "swidget", "<create_archiveEdit>(%)"
*archiveEdit.icode: printf ("colloquio edit archivi\n");
*archiveEdit.fcode: UxPopupInterface (archiveEdit, no_grab);\
return(rtrn);\

*archiveEdit.auxdecl:
*archiveEdit.name.source: public
*archiveEdit.static: false
*archiveEdit.name: archiveEdit
*archiveEdit.parent: NO_PARENT
*archiveEdit.defaultShell: topLevelShell
*archiveEdit.resizePolicy: "resize_none"
*archiveEdit.unitType: "pixels"
*archiveEdit.x: 665
*archiveEdit.y: 115
*archiveEdit.width: 510
*archiveEdit.height: 385

*form24.class: form
*form24.static: true
*form24.name: form24
*form24.parent: archiveEdit
*form24.resizePolicy: "resize_none"
*form24.x: 16
*form24.y: 108
*form24.width: 750
*form24.height: 75
*form24.rightAttachment: "attach_form"
*form24.topOffset: 0
*form24.leftAttachment: "attach_form"
*form24.bottomAttachment: "attach_form"

*frame9.class: frame
*frame9.static: true
*frame9.name: frame9
*frame9.parent: form24
*frame9.x: 10
*frame9.y: 405
*frame9.width: 795
*frame9.height: 50
*frame9.bottomAttachment: "attach_form"
*frame9.leftOffset: 0
*frame9.rightAttachment: "attach_form"
*frame9.topOffset: 0
*frame9.leftAttachment: "attach_form"
*frame9.topAttachment: "attach_form"

*form25.class: form
*form25.static: true
*form25.name: form25
*form25.parent: frame9
*form25.resizePolicy: "resize_none"
*form25.x: 0
*form25.y: 0
*form25.width: 745
*form25.height: 75

*pushButton16.class: pushButton
*pushButton16.static: true
*pushButton16.name: pushButton16
*pushButton16.parent: form25
*pushButton16.y: 15
*pushButton16.width: 138
*pushButton16.height: 41
*pushButton16.labelString: "QUIT"
*pushButton16.bottomAttachment: "attach_form"
*pushButton16.leftAttachment: "attach_self"
*pushButton16.rightAttachment: "attach_form"
*pushButton16.bottomOffset: 15
*pushButton16.rightOffset: 20
*pushButton16.leftPosition: 0
*pushButton16.topAttachment: "attach_form"
*pushButton16.topOffset: 15
*pushButton16.x: 535
*pushButton16.activateCallback: {\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*pushButton16.activateCallbackClientData: UxGetWidget(archiveEdit)

*pushButton17.class: pushButton
*pushButton17.static: true
*pushButton17.name: pushButton17
*pushButton17.parent: form25
*pushButton17.x: 30
*pushButton17.y: 405
*pushButton17.width: 120
*pushButton17.height: 30
*pushButton17.labelString: "LOAD"
*pushButton17.bottomAttachment: "attach_form"
*pushButton17.bottomOffset: 15
*pushButton17.leftOffset: 20
*pushButton17.rightAttachment: "attach_self"
*pushButton17.leftAttachment: "attach_form"
*pushButton17.topAttachment: "attach_form"
*pushButton17.topOffset: 15
*pushButton17.rightPosition: 10
*pushButton17.activateCallback: {\
/*kjkkj*/\
}

*pushButton18.class: pushButton
*pushButton18.static: true
*pushButton18.name: pushButton18
*pushButton18.parent: form25
*pushButton18.x: 165
*pushButton18.y: 20
*pushButton18.width: 120
*pushButton18.height: 30
*pushButton18.labelString: "DELETE"
*pushButton18.bottomAttachment: "attach_form"
*pushButton18.bottomOffset: 15
*pushButton18.leftAttachment: "attach_widget"
*pushButton18.leftWidget: "pushButton17"
*pushButton18.rightAttachment: "attach_self"
*pushButton18.rightOffset: 50
*pushButton18.topAttachment: "attach_form"
*pushButton18.topOffset: 15
*pushButton18.leftOffset: 15

*label19.class: label
*label19.static: true
*label19.name: label19
*label19.parent: archiveEdit
*label19.x: 0
*label19.y: 0
*label19.width: 675
*label19.height: 30
*label19.rightAttachment: "attach_form"
*label19.leftAttachment: "attach_form"
*label19.topOffset: 0
*label19.background: "red"

*form26.class: form
*form26.static: true
*form26.name: form26
*form26.parent: archiveEdit
*form26.resizePolicy: "resize_none"
*form26.x: 0
*form26.y: 30
*form26.width: 675
*form26.height: 250
*form26.rightAttachment: "attach_form"
*form26.leftAttachment: "attach_form"
*form26.leftOffset: 20
*form26.rightOffset: 20
*form26.bottomAttachment: "attach_widget"
*form26.bottomWidget: "form24"
*form26.topAttachment: "attach_widget"
*form26.topWidget: "label19"
*form26.topOffset: 20
*form26.bottomOffset: 20

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.parent: form26
*scrolledWindow2.scrollingPolicy: "automatic"
*scrolledWindow2.x: 0
*scrolledWindow2.y: 0
*scrolledWindow2.width: 680
*scrolledWindow2.height: 250
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.bottomAttachment: "attach_form"
*scrolledWindow2.topAttachment: "attach_form"

*rowColumn3.class: rowColumn
*rowColumn3.static: true
*rowColumn3.name: rowColumn3
*rowColumn3.parent: scrolledWindow2
*rowColumn3.x: 2
*rowColumn3.y: 2
*rowColumn3.width: 705
*rowColumn3.height: 415

*form20.class: form
*form20.static: true
*form20.name: form20
*form20.parent: rowColumn3
*form20.resizePolicy: "resize_none"
*form20.x: 0
*form20.y: 3
*form20.width: 598
*form20.height: 32

*label20.class: label
*label20.static: true
*label20.name: label20
*label20.parent: form20
*label20.x: 0
*label20.y: 0
*label20.width: 37
*label20.height: 32
*label20.bottomAttachment: "attach_form"
*label20.topAttachment: "attach_form"
*label20.leftOffset: 0
*label20.background: "green"

*label21.class: label
*label21.static: true
*label21.name: label21
*label21.parent: form20
*label21.x: 37
*label21.y: 0
*label21.width: 108
*label21.height: 32
*label21.bottomAttachment: "attach_form"
*label21.topAttachment: "attach_form"
*label21.leftAttachment: "attach_widget"
*label21.leftOffset: 0
*label21.leftWidget: "label20"
*label21.rightAttachment: "attach_self"
*label21.rightPosition: 20
*label21.background: "green"

*label22.class: label
*label22.static: true
*label22.name: label22
*label22.parent: form20
*label22.x: 218
*label22.y: 0
*label22.width: 321
*label22.height: 32
*label22.bottomAttachment: "attach_form"
*label22.topAttachment: "attach_form"
*label22.leftAttachment: "attach_widget"
*label22.leftOffset: 0
*label22.leftWidget: "label21"
*label22.rightAttachment: "attach_self"
*label22.rightOffset: 80
*label22.background: "green"

*label23.class: label
*label23.static: true
*label23.name: label23
*label23.parent: form20
*label23.x: 540
*label23.y: 0
*label23.width: 61
*label23.height: 32
*label23.bottomAttachment: "attach_form"
*label23.topAttachment: "attach_form"
*label23.leftAttachment: "attach_widget"
*label23.leftOffset: 0
*label23.rightAttachment: "attach_form"
*label23.leftWidget: "label22"
*label23.background: "green"

