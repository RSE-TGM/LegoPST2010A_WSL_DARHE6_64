! UIMX ascii 2.0 key: 2173                                                      

*Description.class: form
*Description.parent: NO_PARENT
*Description.defaultShell: topLevelShell
*Description.static: false
*Description.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Description.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Description.i	1.10\
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
\
extern int Salvato;\
extern int Modifica;\
extern int indice;\
extern char *stringa[];\
extern char *descriz;\
extern char nomevariabile[];\
extern char **simboli;\
extern int numero_var;\
extern FILE *fpDAT,*fpAPPO;\
extern int numero_campioni;\
\
int i,j;\
float tempo,valore;\

*Description.ispecdecl:
*Description.funcdecl: swidget create_Description()\

*Description.funcname: create_Description
*Description.funcdef: "swidget", "<create_Description>(%)"
*Description.icode:
*Description.fcode: return(rtrn);\

*Description.auxdecl:
*Description.name: Description
*Description.resizePolicy: "resize_none"
*Description.unitType: "pixels"
*Description.x: 260
*Description.y: 350
*Description.width: 609
*Description.height: 151

*labelDescription.class: label
*labelDescription.parent: Description
*labelDescription.static: false
*labelDescription.name: labelDescription
*labelDescription.x: 100
*labelDescription.y: 10
*labelDescription.width: 500
*labelDescription.height: 35
*labelDescription.labelString: ""
*labelDescription.alignment: "alignment_beginning"
*labelDescription.recomputeSize: "false"
*labelDescription.fontList: "fixed"
*labelDescription.leftAttachment: "attach_none"
*labelDescription.leftOffset: 0
*labelDescription.rightAttachment: "attach_form"
*labelDescription.rightOffset: 10
*labelDescription.marginLeft: 7

*textDescription.class: textField
*textDescription.parent: Description
*textDescription.static: false
*textDescription.name: textDescription
*textDescription.x: 100
*textDescription.y: 50
*textDescription.width: 500
*textDescription.height: 40
*textDescription.fontList: "fixed"
*textDescription.maxLength: 72
*textDescription.leftAttachment: "attach_none"
*textDescription.leftOffset: 0
*textDescription.rightAttachment: "attach_form"
*textDescription.rightOffset: 10

*pushButton11.class: pushButton
*pushButton11.parent: Description
*pushButton11.static: true
*pushButton11.name: pushButton11
*pushButton11.x: 15
*pushButton11.y: 100
*pushButton11.width: 80
*pushButton11.height: 40
*pushButton11.labelString: "OK"
*pushButton11.activateCallback: {\
char *NuovoNome,*NuovaDescr;\
\
NuovoNome = XmTextFieldGetString (textNomevar);\
NuovaDescr = XmTextFieldGetString (textDescription);\
EseguiCambioVar (NuovoNome,NuovaDescr,indice);\
}

*pushButton12.class: pushButton
*pushButton12.parent: Description
*pushButton12.static: true
*pushButton12.name: pushButton12
*pushButton12.x: 100
*pushButton12.y: 100
*pushButton12.width: 80
*pushButton12.height: 40
*pushButton12.labelString: "CANCEL"
*pushButton12.activateCallback: {\
UxPopdownInterface (Description);\
}

*labelNomevar.class: label
*labelNomevar.parent: Description
*labelNomevar.static: false
*labelNomevar.name: labelNomevar
*labelNomevar.x: 10
*labelNomevar.y: 10
*labelNomevar.width: 80
*labelNomevar.height: 35
*labelNomevar.labelString: ""
*labelNomevar.alignment: "alignment_beginning"
*labelNomevar.recomputeSize: "false"
*labelNomevar.fontList: "fixed"
*labelNomevar.topOffset: 10
*labelNomevar.leftOffset: 10
*labelNomevar.rightAttachment: "attach_widget"
*labelNomevar.rightOffset: 10
*labelNomevar.rightWidget: "labelDescription"
*labelNomevar.marginLeft: 7

*textNomevar.class: textField
*textNomevar.parent: Description
*textNomevar.static: false
*textNomevar.name: textNomevar
*textNomevar.x: 10
*textNomevar.y: 50
*textNomevar.width: 80
*textNomevar.height: 40
*textNomevar.maxLength: 8
*textNomevar.rightAttachment: "attach_widget"
*textNomevar.rightOffset: 10
*textNomevar.rightWidget: "textDescription"
*textNomevar.fontList: "fixed"

