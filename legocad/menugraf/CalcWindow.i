! UIMX ascii 2.0 key: 5879                                                      

*CalcWindow.class: form
*CalcWindow.parent: NO_PARENT
*CalcWindow.defaultShell: topLevelShell
*CalcWindow.static: false
*CalcWindow.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo CalcWindow.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)CalcWindow.i	1.10\
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
#include <stdlib.h>\
#endif\
#include <Xm/Xm.h>\
#include "menu_graf.h"\
\
extern int TypeCalc;\
extern char **simboli;\
\
float paraA,paraB;\
char *stringaA,*stringaB,*stringaVar,*stringaDescr;\

*CalcWindow.ispecdecl: int ind,ind1,ind2;
*CalcWindow.ispeclist: ind, ind1, ind2
*CalcWindow.ispeclist.ind: "int", "%ind%"
*CalcWindow.ispeclist.ind1: "int", "%ind1%"
*CalcWindow.ispeclist.ind2: "int", "%ind2%"
*CalcWindow.funcdecl: swidget create_CalcWindow(int *Numero)\

*CalcWindow.funcname: create_CalcWindow
*CalcWindow.funcdef: "swidget", "<create_CalcWindow>(%)"
*CalcWindow.argdecl: int *Numero;
*CalcWindow.arglist: Numero
*CalcWindow.arglist.Numero: "int", "*%Numero%"
*CalcWindow.icode: XmString parametro;\
int indVar;\
char strPara[100];\
\
printf ("Indice in entrata:%d\n",Numero[0]);\
\
if (TypeCalc == ELAB_LINEARE)\
	{\
	ind = Numero[0]-1;\
	}\
if (TypeCalc == SOMMA_ALGEBRICA)\
	{\
	ind1 = Numero[0]-1;\
	ind2 = Numero[1]-1;\
	}
*CalcWindow.fcode: if (TypeCalc == ELAB_LINEARE)\
	{\
	set_something (textFieldParA, XmNsensitive, True);\
	set_something (textFieldParB, XmNsensitive, True);\
	indVar = Numero[0] - 1;\
	parametro = XmStringCreate (simboli[indVar], XmSTRING_DEFAULT_CHARSET);\
	set_something (labSourceVar1, XmNlabelString, parametro);\
	strcpy (strPara,"Ax + B\0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labOpType, XmNlabelString, parametro);\
	strcpy (strPara,"                \0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labSourceVar2, XmNlabelString, parametro);\
	strcpy (strPara,"Parameter:\0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labParameter, XmNlabelString, parametro);\
	strcpy (strPara,"A:\0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labParamA, XmNlabelString, parametro);\
	strcpy (strPara,"B:\0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labParamB, XmNlabelString, parametro);\
	}\
if (TypeCalc == SOMMA_ALGEBRICA)\
	{\
	set_something (textFieldParA, XmNsensitive, False);\
	set_something (textFieldParB, XmNsensitive, False);\
	strcpy (strPara,"x + y\0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labOpType, XmNlabelString, parametro);\
	indVar = Numero[0] - 1;\
	parametro = XmStringCreate (simboli[indVar], XmSTRING_DEFAULT_CHARSET);\
	set_something (labSourceVar1, XmNlabelString, parametro);\
	indVar = Numero[1] - 1;\
	parametro = XmStringCreate (simboli[indVar], XmSTRING_DEFAULT_CHARSET);\
	set_something (labSourceVar2, XmNlabelString, parametro);\
	strcpy (strPara,"          \0");\
	parametro = XmStringCreate (strPara, XmSTRING_DEFAULT_CHARSET);\
	set_something (labParameter, XmNlabelString, parametro);\
	set_something (labParamA, XmNlabelString, parametro);\
	set_something (labParamB, XmNlabelString, parametro);	\
	}\
return(rtrn);\
\

*CalcWindow.auxdecl:
*CalcWindow.name: CalcWindow
*CalcWindow.resizePolicy: "resize_none"
*CalcWindow.unitType: "pixels"
*CalcWindow.x: 387
*CalcWindow.y: 13
*CalcWindow.width: 516
*CalcWindow.height: 291

*label8.class: label
*label8.parent: CalcWindow
*label8.static: true
*label8.name: label8
*label8.x: 10
*label8.y: 5
*label8.width: 85
*label8.height: 25
*label8.labelString: "Operation:"
*label8.alignment: "alignment_end"

*labOpType.class: label
*labOpType.parent: CalcWindow
*labOpType.static: true
*labOpType.name: labOpType
*labOpType.x: 95
*labOpType.y: 5
*labOpType.width: 414
*labOpType.height: 25
*labOpType.alignment: "alignment_beginning"
*labOpType.labelString: ""
*labOpType.rightAttachment: "attach_form"
*labOpType.rightOffset: 30
*labOpType.leftAttachment: "attach_widget"
*labOpType.leftOffset: 15
*labOpType.leftWidget: "label8"
*labOpType.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*label9.class: label
*label9.parent: CalcWindow
*label9.static: true
*label9.name: label9
*label9.x: 15
*label9.y: 50
*label9.width: 120
*label9.height: 20
*label9.labelString: "Source Variables:"
*label9.topOffset: 55

*labSourceVar1.class: label
*labSourceVar1.parent: CalcWindow
*labSourceVar1.static: true
*labSourceVar1.name: labSourceVar1
*labSourceVar1.x: 10
*labSourceVar1.y: 75
*labSourceVar1.width: 496
*labSourceVar1.height: 25
*labSourceVar1.leftOffset: 10
*labSourceVar1.rightAttachment: "attach_form"
*labSourceVar1.rightOffset: 10
*labSourceVar1.leftAttachment: "attach_form"
*labSourceVar1.labelString: ""
*labSourceVar1.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"
*labSourceVar1.topOffset: 75
*labSourceVar1.alignment: "alignment_beginning"

*labSourceVar2.class: label
*labSourceVar2.parent: CalcWindow
*labSourceVar2.static: true
*labSourceVar2.name: labSourceVar2
*labSourceVar2.x: 10
*labSourceVar2.y: 100
*labSourceVar2.width: 496
*labSourceVar2.height: 25
*labSourceVar2.labelString: ""
*labSourceVar2.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"
*labSourceVar2.rightAttachment: "attach_form"
*labSourceVar2.rightOffset: 10
*labSourceVar2.leftAttachment: "attach_form"
*labSourceVar2.leftOffset: 10
*labSourceVar2.topOffset: 100
*labSourceVar2.alignment: "alignment_beginning"

*label10.class: label
*label10.parent: CalcWindow
*label10.static: true
*label10.name: label10
*label10.x: 10
*label10.y: 140
*label10.width: 115
*label10.height: 20
*label10.labelString: "Target Variable:"
*label10.topOffset: 145

*label11.class: label
*label11.parent: CalcWindow
*label11.static: true
*label11.name: label11
*label11.x: 15
*label11.y: 160
*label11.width: 85
*label11.height: 25
*label11.alignment: "alignment_end"
*label11.labelString: "name:"
*label11.topOffset: 165

*label12.class: label
*label12.parent: CalcWindow
*label12.static: true
*label12.name: label12
*label12.x: 15
*label12.y: 195
*label12.width: 85
*label12.height: 25
*label12.alignment: "alignment_end"
*label12.labelString: "description:"
*label12.topOffset: 195

*textFieldDescr.class: textField
*textFieldDescr.parent: CalcWindow
*textFieldDescr.static: true
*textFieldDescr.name: textFieldDescr
*textFieldDescr.x: 100
*textFieldDescr.y: 180
*textFieldDescr.width: 375
*textFieldDescr.height: 25
*textFieldDescr.maxLength: 72
*textFieldDescr.columns: 80
*textFieldDescr.bottomAttachment: "attach_none"
*textFieldDescr.bottomOffset: 35
*textFieldDescr.rightAttachment: "attach_form"
*textFieldDescr.rightOffset: 30
*textFieldDescr.leftAttachment: "attach_widget"
*textFieldDescr.leftOffset: 2
*textFieldDescr.leftWidget: "label12"
*textFieldDescr.topAttachment: "attach_form"
*textFieldDescr.topOffset: 195
*textFieldDescr.topWidget: ""
*textFieldDescr.marginHeight: 2
*textFieldDescr.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"

*textFieldVar.class: textField
*textFieldVar.parent: CalcWindow
*textFieldVar.static: true
*textFieldVar.name: textFieldVar
*textFieldVar.x: 100
*textFieldVar.y: 160
*textFieldVar.width: 110
*textFieldVar.height: 25
*textFieldVar.maxLength: 8
*textFieldVar.columns: 15
*textFieldVar.leftAttachment: "attach_widget"
*textFieldVar.leftOffset: 2
*textFieldVar.leftWidget: "label11"
*textFieldVar.topOffset: 165
*textFieldVar.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"
*textFieldVar.text: ""
*textFieldVar.marginHeight: 2

*separator4.class: separator
*separator4.parent: CalcWindow
*separator4.static: true
*separator4.name: separator4
*separator4.x: 5
*separator4.y: 115
*separator4.width: 505
*separator4.height: 10
*separator4.bottomAttachment: "attach_widget"
*separator4.bottomOffset: 2
*separator4.bottomWidget: "label10"
*separator4.rightAttachment: "attach_form"
*separator4.rightOffset: 5
*separator4.leftAttachment: "attach_form"
*separator4.leftOffset: 5
*separator4.topAttachment: "attach_widget"
*separator4.topOffset: 2
*separator4.topWidget: "labSourceVar2"

*separator5.class: separator
*separator5.parent: CalcWindow
*separator5.static: true
*separator5.name: separator5
*separator5.x: 5
*separator5.y: 215
*separator5.width: 505
*separator5.height: 10
*separator5.rightAttachment: "attach_form"
*separator5.rightOffset: 5
*separator5.leftAttachment: "attach_form"
*separator5.leftOffset: 5
*separator5.topAttachment: "attach_widget"
*separator5.topOffset: 2
*separator5.topWidget: "textFieldDescr"

*separator6.class: separator
*separator6.parent: CalcWindow
*separator6.static: true
*separator6.name: separator6
*separator6.x: 0
*separator6.y: 30
*separator6.width: 505
*separator6.height: 10
*separator6.rightAttachment: "attach_form"
*separator6.rightOffset: 5
*separator6.topAttachment: "attach_widget"
*separator6.topOffset: 2
*separator6.topWidget: "labOpType"
*separator6.leftAttachment: "attach_form"
*separator6.leftOffset: 5
*separator6.bottomAttachment: "attach_widget"
*separator6.bottomOffset: 2
*separator6.bottomWidget: "label9"

*pushButton13.class: pushButton
*pushButton13.parent: CalcWindow
*pushButton13.static: true
*pushButton13.name: pushButton13
*pushButton13.x: 15
*pushButton13.y: 240
*pushButton13.width: 90
*pushButton13.height: 35
*pushButton13.labelString: "OK"
*pushButton13.topAttachment: "attach_widget"
*pushButton13.topOffset: 10
*pushButton13.topWidget: "separator5"
*pushButton13.bottomAttachment: "attach_form"
*pushButton13.bottomOffset: 15
*pushButton13.activateCallback: {\
extern int EseguiElabLineare();\
extern int EseguiSommaAlg(); \
\
if (TypeCalc == ELAB_LINEARE)\
	{\
	stringaA = XmTextFieldGetString (textFieldParA);\
	stringaB = XmTextFieldGetString (textFieldParB);\
	stringaVar = XmTextFieldGetString (textFieldVar);\
	stringaDescr = XmTextFieldGetString (textFieldDescr);\
\
	paraA = atof (stringaA);\
	paraB = atof (stringaB);\
\
	printf ("Prima della chiamata:%d\n",ind);\
\
	EseguiElabLineare (ind,stringaVar,stringaDescr,paraA,paraB);\
\
	XtFree (stringaA);\
	XtFree (stringaB);\
	XtFree (stringaVar);\
	XtFree (stringaDescr);\
	}\
\
if (TypeCalc == SOMMA_ALGEBRICA)\
	{\
	stringaVar = XmTextFieldGetString (textFieldVar);\
	stringaDescr = XmTextFieldGetString (textFieldDescr);\
	printf ("Prima della chiamata:%d\n",ind1);\
	printf ("Prima della chiamata:%d\n",ind2); \
\
	EseguiSommaAlg (ind1,ind2,stringaVar,stringaDescr);\
\
	XtFree (stringaVar);\
	XtFree (stringaDescr);\
	}\
}

*pushButton14.class: pushButton
*pushButton14.parent: CalcWindow
*pushButton14.static: true
*pushButton14.name: pushButton14
*pushButton14.x: 120
*pushButton14.y: 240
*pushButton14.width: 90
*pushButton14.height: 35
*pushButton14.labelString: "CANCEL"
*pushButton14.bottomAttachment: "attach_form"
*pushButton14.bottomOffset: 15
*pushButton14.leftAttachment: "attach_widget"
*pushButton14.leftOffset: 15
*pushButton14.leftWidget: "pushButton13"
*pushButton14.topAttachment: "attach_widget"
*pushButton14.topOffset: 10
*pushButton14.topWidget: "separator5"
*pushButton14.activateCallback: UxPopdownInterface (CalcWindow);

*labParameter.class: label
*labParameter.parent: CalcWindow
*labParameter.static: true
*labParameter.name: labParameter
*labParameter.x: 240
*labParameter.y: 140
*labParameter.width: 115
*labParameter.height: 20
*labParameter.labelString: ""
*labParameter.rightAttachment: "attach_form"
*labParameter.rightOffset: 10
*labParameter.topAttachment: "attach_widget"
*labParameter.topOffset: 2
*labParameter.topWidget: "separator4"

*labParamA.class: label
*labParamA.parent: CalcWindow
*labParamA.static: true
*labParamA.name: labParamA
*labParamA.x: 245
*labParamA.y: 160
*labParamA.width: 40
*labParamA.height: 20
*labParamA.labelString: ""
*labParamA.topAttachment: "attach_widget"
*labParamA.topOffset: 0
*labParamA.topWidget: "labParameter"
*labParamA.bottomAttachment: "attach_widget"
*labParamA.bottomOffset: 10
*labParamA.bottomWidget: "textFieldDescr"
*labParamA.alignment: "alignment_end"

*textFieldParA.class: textField
*textFieldParA.parent: CalcWindow
*textFieldParA.static: true
*textFieldParA.name: textFieldParA
*textFieldParA.x: 285
*textFieldParA.y: 160
*textFieldParA.width: 65
*textFieldParA.height: 25
*textFieldParA.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"
*textFieldParA.marginHeight: 2
*textFieldParA.maxLength: 7
*textFieldParA.leftAttachment: "attach_widget"
*textFieldParA.leftOffset: 2
*textFieldParA.leftWidget: "labParamA"

*labParamB.class: label
*labParamB.parent: CalcWindow
*labParamB.static: true
*labParamB.name: labParamB
*labParamB.x: 377
*labParamB.y: 160
*labParamB.width: 40
*labParamB.height: 25
*labParamB.labelString: ""
*labParamB.topOffset: 0
*labParamB.topWidget: "labParameter"
*labParamB.topAttachment: "attach_widget"
*labParamB.leftAttachment: "attach_none"
*labParamB.leftOffset: 0
*labParamB.leftWidget: ""
*labParamB.alignment: "alignment_end"

*textFieldParB.class: textField
*textFieldParB.parent: CalcWindow
*textFieldParB.static: true
*textFieldParB.name: textFieldParB
*textFieldParB.x: 420
*textFieldParB.y: 160
*textFieldParB.width: 65
*textFieldParB.height: 25
*textFieldParB.marginHeight: 2
*textFieldParB.maxLength: 7
*textFieldParB.topAttachment: "attach_widget"
*textFieldParB.topOffset: 0
*textFieldParB.topWidget: "labParameter"
*textFieldParB.rightAttachment: "attach_form"
*textFieldParB.rightOffset: 30
*textFieldParB.leftOffset: 2
*textFieldParB.leftAttachment: "attach_widget"
*textFieldParB.leftWidget: "labParamB"
*textFieldParB.fontList: "-adobe-helvetica-bold-r-normal--10-100-75-75-p-60-iso8859-1"

*separator7.class: separator
*separator7.parent: CalcWindow
*separator7.static: true
*separator7.name: separator7
*separator7.x: 240
*separator7.y: 140
*separator7.width: 13
*separator7.height: 53
*separator7.orientation: "vertical"
*separator7.bottomAttachment: "attach_widget"
*separator7.bottomOffset: 5
*separator7.bottomWidget: "textFieldDescr"
*separator7.leftAttachment: "attach_widget"
*separator7.leftOffset: 20
*separator7.leftWidget: "textFieldVar"
*separator7.rightAttachment: "attach_widget"
*separator7.rightOffset: 5
*separator7.rightWidget: "labParamA"
*separator7.topAttachment: "attach_widget"
*separator7.topOffset: 5
*separator7.topWidget: "separator4"

