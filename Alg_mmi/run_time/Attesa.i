! UIMX ascii 2.5 key: 9273                                                      

*Attesa.class: dialogShell
*Attesa.gbldecl: #include <stdio.h>\
\
#include <Rt/RtMemory.h>\

*Attesa.ispecdecl: int valore;
*Attesa.ispeclist: valore
*Attesa.ispeclist.valore: "int", "%valore%"
*Attesa.funcdecl: swidget popup_Attesa(Widget padreAttesa)\

*Attesa.funcname: popup_Attesa
*Attesa.funcdef: "swidget", "<popup_Attesa>(%)"
*Attesa.argdecl: Widget padreAttesa;
*Attesa.arglist: padreAttesa
*Attesa.arglist.padreAttesa: "Widget", "%padreAttesa%"
*Attesa.icode: valore =0;
*Attesa.fcode: UxPopupInterface(rtrn,XtGrabExclusive );\
return(rtrn);\

*Attesa.auxdecl: SettaAttesa(Widget wid,int delta)\
{\
#ifndef DESIGN_TIME\
_UxCAttesa *Context;\
\
        Context =(_UxCAttesa *) UxGetContext(wid);\
	Context->Uxvalore = Context->Uxvalore + delta;\
	if(Context->Uxvalore > 100)\
		Context->Uxvalore = 0;\
	set_something(Context->UxscaleAttesa,XmNvalue,Context->Uxvalore);\
\
#endif\
}
*Attesa.static: true
*Attesa.name: Attesa
*Attesa.parent: NO_PARENT
*Attesa.parentExpression: padreAttesa
*Attesa.x: 430
*Attesa.y: 220
*Attesa.width: 430
*Attesa.height: 200

*formAttesa.class: form
*formAttesa.static: true
*formAttesa.name: formAttesa
*formAttesa.parent: Attesa
*formAttesa.resizePolicy: "resize_none"
*formAttesa.unitType: "pixels"
*formAttesa.x: 296
*formAttesa.y: 143
*formAttesa.width: 400
*formAttesa.height: 190
*formAttesa.background: "#50a050"

*labelAttesa.class: label
*labelAttesa.static: true
*labelAttesa.name: labelAttesa
*labelAttesa.parent: formAttesa
*labelAttesa.x: 50
*labelAttesa.y: 130
*labelAttesa.width: 290
*labelAttesa.height: 40
*labelAttesa.background: "#50a050"
*labelAttesa.labelString: "Wait"
*labelAttesa.shadowThickness: 0
*labelAttesa.topShadowColor: "#50a0a0"
*labelAttesa.bottomShadowColor: "#a05050"
*labelAttesa.bottomAttachment: "attach_form"
*labelAttesa.bottomOffset: 20
*labelAttesa.leftAttachment: "attach_form"
*labelAttesa.leftOffset: 20
*labelAttesa.rightAttachment: "attach_form"
*labelAttesa.rightOffset: 20
*labelAttesa.borderWidth: 4
*labelAttesa.borderColor: "#5050a0"

*scaleAttesa.class: scale
*scaleAttesa.static: true
*scaleAttesa.name: scaleAttesa
*scaleAttesa.parent: formAttesa
*scaleAttesa.x: 50
*scaleAttesa.y: 40
*scaleAttesa.width: 320
*scaleAttesa.height: 50
*scaleAttesa.orientation: "horizontal"
*scaleAttesa.background: "#50a050"
*scaleAttesa.leftAttachment: "attach_form"
*scaleAttesa.leftOffset: 20
*scaleAttesa.rightAttachment: "attach_form"
*scaleAttesa.rightOffset: 20
*scaleAttesa.topAttachment: "attach_form"
*scaleAttesa.topOffset: 20
*scaleAttesa.foreground: "#50a050"

