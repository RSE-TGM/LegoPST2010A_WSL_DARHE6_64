! UIMX ascii 2.5 key: 5471                                                      

*BitmapProperties.class: topLevelShell
*BitmapProperties.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo BitmapProperties.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)BitmapProperties.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "res_edit.h"\

*BitmapProperties.ispecdecl: char *FileBitmap;\
Widget PadreChiamante;
*BitmapProperties.ispeclist: FileBitmap, PadreChiamante
*BitmapProperties.ispeclist.FileBitmap: "unsigned char", "*%FileBitmap%"
*BitmapProperties.ispeclist.PadreChiamante: "Widget", "%PadreChiamante%"
*BitmapProperties.funcdecl: swidget create_BitmapProperties(NomefINP,Chiam)\
char *NomefINP;\
Widget Chiam;\

*BitmapProperties.funcname: create_BitmapProperties
*BitmapProperties.funcdef: "swidget", "<create_BitmapProperties>(%)"
*BitmapProperties.argdecl: unsigned char *NomefINP;\
Widget Chiam;
*BitmapProperties.arglist: NomefINP, Chiam
*BitmapProperties.arglist.NomefINP: "unsigned char", "*%NomefINP%"
*BitmapProperties.arglist.Chiam: "Widget", "%Chiam%"
*BitmapProperties.icode: FileBitmap = (unsigned char *)XtNewString ((char *)NomefINP);\
PadreChiamante = Chiam;
*BitmapProperties.fcode: /*  Setta la posizione dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (BitmapProperties,Chiam);\
\
return(rtrn);\

*BitmapProperties.auxdecl:
*BitmapProperties.static: true
*BitmapProperties.name: BitmapProperties
*BitmapProperties.parent: NO_PARENT
*BitmapProperties.parentExpression: Chiam
*BitmapProperties.x: 230
*BitmapProperties.y: 160
*BitmapProperties.width: 240
*BitmapProperties.height: 160
*BitmapProperties.iconName: "BITMAP Properties"
*BitmapProperties.title: "NEW BITMAP Properties"

*form8.class: form
*form8.static: true
*form8.name: form8
*form8.parent: BitmapProperties
*form8.resizePolicy: "resize_none"
*form8.unitType: "pixels"
*form8.x: 70
*form8.y: 40
*form8.width: 240
*form8.height: 160

*textWidthBit.class: textField
*textWidthBit.static: true
*textWidthBit.name: textWidthBit
*textWidthBit.parent: form8
*textWidthBit.x: 110
*textWidthBit.y: 10
*textWidthBit.width: 120
*textWidthBit.height: 30

*label13.class: label
*label13.static: true
*label13.name: label13
*label13.parent: form8
*label13.x: 10
*label13.y: 60
*label13.width: 90
*label13.height: 30
*label13.alignment: "alignment_beginning"
*label13.labelString: "HEIGHT:"

*textHeightBit.class: textField
*textHeightBit.static: true
*textHeightBit.name: textHeightBit
*textHeightBit.parent: form8
*textHeightBit.x: 110
*textHeightBit.y: 60
*textHeightBit.width: 120
*textHeightBit.height: 30

*separator9.class: separator
*separator9.static: true
*separator9.name: separator9
*separator9.parent: form8
*separator9.x: 10
*separator9.y: 100
*separator9.width: 220
*separator9.height: 20
*separator9.leftAttachment: "attach_form"
*separator9.leftOffset: 0
*separator9.rightAttachment: "attach_form"

*label11.class: label
*label11.static: true
*label11.name: label11
*label11.parent: form8
*label11.x: 10
*label11.y: 10
*label11.width: 90
*label11.height: 30
*label11.alignment: "alignment_beginning"
*label11.labelString: "WIDTH:"
*label11.bottomAttachment: "attach_widget"
*label11.bottomOffset: 15
*label11.bottomWidget: "label13"
*label11.leftAttachment: "attach_form"
*label11.leftOffset: 10
*label11.rightAttachment: "attach_widget"
*label11.rightOffset: 10
*label11.rightWidget: "textWidthBit"
*label11.topAttachment: "attach_form"
*label11.topOffset: 10

*pushButton13.class: pushButton
*pushButton13.static: true
*pushButton13.name: pushButton13
*pushButton13.parent: form8
*pushButton13.x: 10
*pushButton13.y: 120
*pushButton13.width: 80
*pushButton13.height: 30
*pushButton13.labelString: "OK"
*pushButton13.activateCallback: {\
Boolean WidthBool,HeightBool;\
char stringa[100];\
char *Largh,*Altez;\
\
Largh = (char *)XmTextFieldGetString (textWidthBit);\
WidthBool = NumIntVerifica (Largh);\
\
Altez = (char *)XmTextFieldGetString (textHeightBit);\
HeightBool = NumIntVerifica (Altez);\
\
if (!WidthBool || !HeightBool)\
	{\
	strcpy (stringa,"Error in dimension input!");\
	VisualizzaMessageBox (GENERICA,BitmapProperties,stringa,PadreChiamante);\
	}\
else\
	{\
	EseguiNuovoBitmap (FileBitmap,Largh,Altez,Chiam);\
	XtFree (Largh);\
	XtFree (Altez);\
	XtDestroyWidget (BitmapProperties);\
	}\
XtFree (Largh);\
XtFree (Altez);\
}

*pushButton14.class: pushButton
*pushButton14.static: true
*pushButton14.name: pushButton14
*pushButton14.parent: form8
*pushButton14.x: 100
*pushButton14.y: 120
*pushButton14.width: 80
*pushButton14.height: 30
*pushButton14.labelString: "CANCEL"
*pushButton14.activateCallback: {\
XtDestroyWidget (BitmapProperties);\
}

