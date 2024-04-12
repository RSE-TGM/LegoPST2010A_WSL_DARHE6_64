! UIMX ascii 2.5 key: 8107                                                      

*topRegoDisplayMode.class: topLevelShell
*topRegoDisplayMode.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo topRegoDisplayMode.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)topRegoDisplayMode.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xl/XlDispReg.h>\
#include <Xl/XlPort.h>\

*topRegoDisplayMode.ispecdecl: int statoDispReg, statoPort, statoInterfacePort;
*topRegoDisplayMode.ispeclist: statoDispReg, statoPort, statoInterfacePort
*topRegoDisplayMode.ispeclist.statoDispReg: "int", "%statoDispReg%"
*topRegoDisplayMode.ispeclist.statoPort: "int", "%statoPort%"
*topRegoDisplayMode.ispeclist.statoInterfacePort: "int", "%statoInterfacePort%"
*topRegoDisplayMode.funcdecl: swidget popup_topRegoDisplayMode(Widget drawing)\

*topRegoDisplayMode.funcname: popup_topRegoDisplayMode
*topRegoDisplayMode.funcdef: "swidget", "<popup_topRegoDisplayMode>(%)"
*topRegoDisplayMode.argdecl: Widget drawing;
*topRegoDisplayMode.arglist: drawing
*topRegoDisplayMode.arglist.drawing: "Widget", "%drawing%"
*topRegoDisplayMode.icode:
*topRegoDisplayMode.fcode: UxPopupInterface(rtrn,no_grab);\
GetRegoDisplayMode(drawing,&statoDispReg, &statoPort, &statoInterfacePort);\
SettaToggle(rtrn);\
return(rtrn);\

*topRegoDisplayMode.auxdecl: SettaToggle(Widget UxWidget)\
{\
#ifndef DESIGN_TIME\
        _UxCtopRegoDisplayMode  *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxTopRegoDisplayModeContext;\
        UxTopRegoDisplayModeContext = UxContext =\
                        (_UxCtopRegoDisplayMode *) UxGetContext( UxWidget );\
#endif\
        {\
	switch(statoDispReg){\
		case DISPREG_UNMANAGED:\
			{\
			XmToggleButtonSetState(toggleDispRegUnmanaged,True,False);\
			break;\
			}\
		case DISPREG_TAG:\
			{\
			XmToggleButtonSetState(toggleDispRegTag,True,False);\
			break;\
			}\
		case DISPREG_MODUL:\
			{\
			XmToggleButtonSetState(toggleDispRegModul,True,False);\
			break;\
			}\
		case DISPREG_VALUE:\
			{\
			XmToggleButtonSetState(toggleDispRegValue,True,False);\
			break;\
			}\
		}\
	switch(statoPort){\
		case PORT_UNMANAGED:\
			{\
			XmToggleButtonSetState(togglePortUnmanaged,True,False);\
			break;\
			}\
		case PORT_MANAGED:\
			{\
			XmToggleButtonSetState(togglePortManaged,True,False);\
			break;\
			}\
		case PORT_TAG:\
			{\
			XmToggleButtonSetState(togglePortTag,True,False);\
			break;\
			}\
		}\
	switch(statoInterfacePort){\
		case INTERFACE_PORT_UNMANAGED:\
			{\
			XmToggleButtonSetState(togglePortInterUnmanaged,True,False);\
			break;\
			}\
		case INTERFACE_PORT_MANAGED:\
			{\
			XmToggleButtonSetState(togglePortInterManaged,True,False);\
			break;\
			}\
		case INTERFACE_PORT_TAG:\
			{\
			XmToggleButtonSetState(togglePortInterTag,True,False);\
			break;\
			}\
		}\
\
\
        \
\
        }\
#ifndef DESIGN_TIME\
        UxTopRegoDisplayModeContext = UxSaveCtx;\
#endif\
}
*topRegoDisplayMode.static: true
*topRegoDisplayMode.name: topRegoDisplayMode
*topRegoDisplayMode.parent: NO_PARENT
*topRegoDisplayMode.x: 414
*topRegoDisplayMode.y: 167
*topRegoDisplayMode.width: 620
*topRegoDisplayMode.height: 300

*formRegoDisplayMode.class: form
*formRegoDisplayMode.static: true
*formRegoDisplayMode.name: formRegoDisplayMode
*formRegoDisplayMode.parent: topRegoDisplayMode
*formRegoDisplayMode.resizePolicy: "resize_none"
*formRegoDisplayMode.unitType: "pixels"
*formRegoDisplayMode.x: 5
*formRegoDisplayMode.y: 4
*formRegoDisplayMode.width: 546
*formRegoDisplayMode.height: 427

*labelRegoDisplayMode.class: label
*labelRegoDisplayMode.static: true
*labelRegoDisplayMode.name: labelRegoDisplayMode
*labelRegoDisplayMode.parent: formRegoDisplayMode
*labelRegoDisplayMode.x: 10
*labelRegoDisplayMode.y: 10
*labelRegoDisplayMode.width: 98
*labelRegoDisplayMode.height: 29
*labelRegoDisplayMode.labelString: "Display Reg"
*labelRegoDisplayMode.leftOffset: 10
*labelRegoDisplayMode.leftAttachment: "attach_form"
*labelRegoDisplayMode.resizable: "true"
*labelRegoDisplayMode.topAttachment: "attach_form"
*labelRegoDisplayMode.topOffset: 20
*labelRegoDisplayMode.recomputeSize: "true"
*labelRegoDisplayMode.marginBottom: 4
*labelRegoDisplayMode.marginTop: 4
*labelRegoDisplayMode.borderWidth: 0
*labelRegoDisplayMode.alignment: "alignment_beginning"

*labelRegoPortMode.class: label
*labelRegoPortMode.static: true
*labelRegoPortMode.name: labelRegoPortMode
*labelRegoPortMode.parent: formRegoDisplayMode
*labelRegoPortMode.x: 10
*labelRegoPortMode.y: 10
*labelRegoPortMode.width: 98
*labelRegoPortMode.height: 29
*labelRegoPortMode.labelString: "Port"
*labelRegoPortMode.recomputeSize: "true"
*labelRegoPortMode.leftAttachment: "attach_form"
*labelRegoPortMode.leftOffset: 10
*labelRegoPortMode.topAttachment: "attach_widget"
*labelRegoPortMode.topOffset: 25
*labelRegoPortMode.topWidget: "labelRegoDisplayMode"
*labelRegoPortMode.marginBottom: 3
*labelRegoPortMode.marginTop: 3
*labelRegoPortMode.alignment: "alignment_beginning"

*labelRegoPortMode1.class: label
*labelRegoPortMode1.static: true
*labelRegoPortMode1.name: labelRegoPortMode1
*labelRegoPortMode1.parent: formRegoDisplayMode
*labelRegoPortMode1.x: 10
*labelRegoPortMode1.y: 10
*labelRegoPortMode1.width: 98
*labelRegoPortMode1.height: 29
*labelRegoPortMode1.labelString: "Interface port"
*labelRegoPortMode1.recomputeSize: "true"
*labelRegoPortMode1.marginBottom: 3
*labelRegoPortMode1.marginTop: 3
*labelRegoPortMode1.topAttachment: "attach_widget"
*labelRegoPortMode1.topOffset: 25
*labelRegoPortMode1.topWidget: "labelRegoPortMode"
*labelRegoPortMode1.leftOffset: 10
*labelRegoPortMode1.alignment: "alignment_beginning"

*rowColRegoDisplayMode.class: rowColumn
*rowColRegoDisplayMode.static: true
*rowColRegoDisplayMode.name: rowColRegoDisplayMode
*rowColRegoDisplayMode.parent: formRegoDisplayMode
*rowColRegoDisplayMode.x: -109
*rowColRegoDisplayMode.y: 10
*rowColRegoDisplayMode.width: 322
*rowColRegoDisplayMode.height: 46
*rowColRegoDisplayMode.packing: "pack_column"
*rowColRegoDisplayMode.radioBehavior: "true"
*rowColRegoDisplayMode.resizeHeight: "true"
*rowColRegoDisplayMode.resizeWidth: "true"
*rowColRegoDisplayMode.orientation: "horizontal"
*rowColRegoDisplayMode.labelString: ""
*rowColRegoDisplayMode.leftAttachment.source: public
*rowColRegoDisplayMode.leftAttachment: "attach_none"
*rowColRegoDisplayMode.leftOffset: 10
*rowColRegoDisplayMode.rightAttachment: "attach_form"
*rowColRegoDisplayMode.rightOffset: 10
*rowColRegoDisplayMode.leftWidget: "labelRegoDisplayMode"
*rowColRegoDisplayMode.topAttachment: "attach_form"
*rowColRegoDisplayMode.topOffset: 20
*rowColRegoDisplayMode.entryAlignment: "alignment_beginning"
*rowColRegoDisplayMode.borderWidth: 1

*toggleDispRegUnmanaged.class: toggleButton
*toggleDispRegUnmanaged.static: true
*toggleDispRegUnmanaged.name: toggleDispRegUnmanaged
*toggleDispRegUnmanaged.parent: rowColRegoDisplayMode
*toggleDispRegUnmanaged.x: 20
*toggleDispRegUnmanaged.y: 3
*toggleDispRegUnmanaged.width: 285
*toggleDispRegUnmanaged.height: 25
*toggleDispRegUnmanaged.labelString: "Unmanaged"
*toggleDispRegUnmanaged.selectColor: "#00c600"

*toggleDispRegTag.class: toggleButton
*toggleDispRegTag.static: true
*toggleDispRegTag.name: toggleDispRegTag
*toggleDispRegTag.parent: rowColRegoDisplayMode
*toggleDispRegTag.x: 20
*toggleDispRegTag.y: 3
*toggleDispRegTag.width: 82
*toggleDispRegTag.height: 22
*toggleDispRegTag.labelString: "Tag"
*toggleDispRegTag.selectColor: "#00c600"
*toggleDispRegTag.alignment: "alignment_beginning"
*toggleDispRegTag.marginLeft: 2
*toggleDispRegTag.fillOnSelect: "true"

*toggleDispRegModul.class: toggleButton
*toggleDispRegModul.static: true
*toggleDispRegModul.name: toggleDispRegModul
*toggleDispRegModul.parent: rowColRegoDisplayMode
*toggleDispRegModul.x: 20
*toggleDispRegModul.y: 3
*toggleDispRegModul.width: 76
*toggleDispRegModul.height: 20
*toggleDispRegModul.labelString: "Modul"
*toggleDispRegModul.selectColor: "#00c600"

*toggleDispRegValue.class: toggleButton
*toggleDispRegValue.static: true
*toggleDispRegValue.name: toggleDispRegValue
*toggleDispRegValue.parent: rowColRegoDisplayMode
*toggleDispRegValue.x: 20
*toggleDispRegValue.y: 3
*toggleDispRegValue.width: 80
*toggleDispRegValue.height: 20
*toggleDispRegValue.labelString: "Value"
*toggleDispRegValue.selectColor: "#00c600"

*rowColRegoPortMode.class: rowColumn
*rowColRegoPortMode.static: true
*rowColRegoPortMode.name: rowColRegoPortMode
*rowColRegoPortMode.parent: formRegoDisplayMode
*rowColRegoPortMode.x: -109
*rowColRegoPortMode.y: 10
*rowColRegoPortMode.width: 322
*rowColRegoPortMode.height: 46
*rowColRegoPortMode.packing: "pack_column"
*rowColRegoPortMode.radioBehavior: "true"
*rowColRegoPortMode.resizeHeight: "true"
*rowColRegoPortMode.resizeWidth: "true"
*rowColRegoPortMode.orientation: "horizontal"
*rowColRegoPortMode.labelString: ""
*rowColRegoPortMode.entryAlignment: "alignment_beginning"
*rowColRegoPortMode.borderWidth: 1
*rowColRegoPortMode.leftOffset: 10
*rowColRegoPortMode.rightAttachment: "attach_form"
*rowColRegoPortMode.rightOffset: 10
*rowColRegoPortMode.topAttachment: "attach_widget"
*rowColRegoPortMode.topOffset: 20
*rowColRegoPortMode.topWidget: "rowColRegoDisplayMode"

*togglePortUnmanaged.class: toggleButton
*togglePortUnmanaged.static: true
*togglePortUnmanaged.name: togglePortUnmanaged
*togglePortUnmanaged.parent: rowColRegoPortMode
*togglePortUnmanaged.x: 20
*togglePortUnmanaged.y: 3
*togglePortUnmanaged.width: 285
*togglePortUnmanaged.height: 25
*togglePortUnmanaged.labelString: "Unmanaged"
*togglePortUnmanaged.selectColor: "#00c600"

*togglePortManaged.class: toggleButton
*togglePortManaged.static: true
*togglePortManaged.name: togglePortManaged
*togglePortManaged.parent: rowColRegoPortMode
*togglePortManaged.x: 20
*togglePortManaged.y: 3
*togglePortManaged.width: 82
*togglePortManaged.height: 22
*togglePortManaged.labelString: "Managed"
*togglePortManaged.selectColor: "#00c600"

*togglePortTag.class: toggleButton
*togglePortTag.static: true
*togglePortTag.name: togglePortTag
*togglePortTag.parent: rowColRegoPortMode
*togglePortTag.x: 20
*togglePortTag.y: 3
*togglePortTag.width: 76
*togglePortTag.height: 20
*togglePortTag.labelString: "Tag"
*togglePortTag.selectColor: "#00c600"

*rowColRegoInterPortMode.class: rowColumn
*rowColRegoInterPortMode.static: true
*rowColRegoInterPortMode.name: rowColRegoInterPortMode
*rowColRegoInterPortMode.parent: formRegoDisplayMode
*rowColRegoInterPortMode.x: -109
*rowColRegoInterPortMode.y: 10
*rowColRegoInterPortMode.width: 322
*rowColRegoInterPortMode.height: 46
*rowColRegoInterPortMode.packing: "pack_column"
*rowColRegoInterPortMode.radioBehavior: "true"
*rowColRegoInterPortMode.resizeHeight: "true"
*rowColRegoInterPortMode.resizeWidth: "true"
*rowColRegoInterPortMode.orientation: "horizontal"
*rowColRegoInterPortMode.labelString: ""
*rowColRegoInterPortMode.entryAlignment: "alignment_beginning"
*rowColRegoInterPortMode.borderWidth: 1
*rowColRegoInterPortMode.rightAttachment: "attach_form"
*rowColRegoInterPortMode.rightOffset: 10
*rowColRegoInterPortMode.topAttachment: "attach_widget"
*rowColRegoInterPortMode.topOffset: 20
*rowColRegoInterPortMode.topWidget: "rowColRegoPortMode"

*togglePortInterUnmanaged.class: toggleButton
*togglePortInterUnmanaged.static: true
*togglePortInterUnmanaged.name: togglePortInterUnmanaged
*togglePortInterUnmanaged.parent: rowColRegoInterPortMode
*togglePortInterUnmanaged.x: 20
*togglePortInterUnmanaged.y: 3
*togglePortInterUnmanaged.width: 285
*togglePortInterUnmanaged.height: 25
*togglePortInterUnmanaged.labelString: "Unmanaged"
*togglePortInterUnmanaged.selectColor: "#00c600"

*togglePortInterManaged.class: toggleButton
*togglePortInterManaged.static: true
*togglePortInterManaged.name: togglePortInterManaged
*togglePortInterManaged.parent: rowColRegoInterPortMode
*togglePortInterManaged.x: 20
*togglePortInterManaged.y: 3
*togglePortInterManaged.width: 82
*togglePortInterManaged.height: 22
*togglePortInterManaged.labelString: "Managed"
*togglePortInterManaged.selectColor: "#00c600"

*togglePortInterTag.class: toggleButton
*togglePortInterTag.static: true
*togglePortInterTag.name: togglePortInterTag
*togglePortInterTag.parent: rowColRegoInterPortMode
*togglePortInterTag.x: 20
*togglePortInterTag.y: 3
*togglePortInterTag.width: 76
*togglePortInterTag.height: 20
*togglePortInterTag.labelString: "Tag"
*togglePortInterTag.selectColor: "#00c600"

*buttonOkRegoDisplayMode.class: pushButton
*buttonOkRegoDisplayMode.static: true
*buttonOkRegoDisplayMode.name: buttonOkRegoDisplayMode
*buttonOkRegoDisplayMode.parent: formRegoDisplayMode
*buttonOkRegoDisplayMode.x: 14
*buttonOkRegoDisplayMode.y: 380
*buttonOkRegoDisplayMode.width: 95
*buttonOkRegoDisplayMode.height: 38
*buttonOkRegoDisplayMode.labelString: "Ok"
*buttonOkRegoDisplayMode.recomputeSize: "false"
*buttonOkRegoDisplayMode.leftAttachment: "attach_form"
*buttonOkRegoDisplayMode.leftOffset: 10
*buttonOkRegoDisplayMode.bottomAttachment: "attach_form"
*buttonOkRegoDisplayMode.bottomOffset: 10
*buttonOkRegoDisplayMode.activateCallback: {\
if(XmToggleButtonGetState(toggleDispRegUnmanaged))\
	statoDispReg=DISPREG_UNMANAGED;\
if(XmToggleButtonGetState(toggleDispRegTag))\
	statoDispReg=DISPREG_TAG;\
if(XmToggleButtonGetState(toggleDispRegModul))\
	statoDispReg=DISPREG_MODUL;\
if(XmToggleButtonGetState(toggleDispRegValue))\
	statoDispReg=DISPREG_VALUE;\
if(XmToggleButtonGetState(togglePortUnmanaged))\
	statoPort=PORT_UNMANAGED;\
if(XmToggleButtonGetState(togglePortManaged))\
	statoPort=PORT_MANAGED;\
if(XmToggleButtonGetState(togglePortTag))\
	statoPort=PORT_TAG;\
if(XmToggleButtonGetState(togglePortInterUnmanaged))\
	statoInterfacePort=INTERFACE_PORT_UNMANAGED;\
if(XmToggleButtonGetState(togglePortInterManaged))\
	statoInterfacePort=INTERFACE_PORT_MANAGED;\
if(XmToggleButtonGetState(togglePortInterTag))\
	statoInterfacePort=INTERFACE_PORT_TAG;\
\
\
\
SetRegoDisplayMode(drawing,statoDispReg, statoPort, statoInterfacePort);\
XtDestroyWidget(topRegoDisplayMode);\
}

*buttonCancelRegoDisplayMode.class: pushButton
*buttonCancelRegoDisplayMode.static: true
*buttonCancelRegoDisplayMode.name: buttonCancelRegoDisplayMode
*buttonCancelRegoDisplayMode.parent: formRegoDisplayMode
*buttonCancelRegoDisplayMode.x: 125
*buttonCancelRegoDisplayMode.y: 382
*buttonCancelRegoDisplayMode.width: 83
*buttonCancelRegoDisplayMode.height: 38
*buttonCancelRegoDisplayMode.labelString: "Cancel"
*buttonCancelRegoDisplayMode.recomputeSize: "false"
*buttonCancelRegoDisplayMode.bottomAttachment: "attach_form"
*buttonCancelRegoDisplayMode.bottomOffset: 10
*buttonCancelRegoDisplayMode.leftAttachment: "attach_widget"
*buttonCancelRegoDisplayMode.leftOffset: 20
*buttonCancelRegoDisplayMode.leftWidget: "buttonOkRegoDisplayMode"
*buttonCancelRegoDisplayMode.activateCallback: {\
XtDestroyWidget(topRegoDisplayMode);\
}

