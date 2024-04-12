! UIMX ascii 2.0 key: 1144                                                      

*FilterWindow.class: topLevelShell
*FilterWindow.parent: NO_PARENT
*FilterWindow.static: true
*FilterWindow.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo FilterWindow.i\
   tipo \
   release 1.4\
   data 3/28/95\
   reserved @(#)FilterWindow.i	1.4\
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
#include "menu_graf.h"\
#ifndef DESIGN_TIME\
#include <math.h>\
#include <grsf22.h>\
extern char nomi_var[NUM_VAR+1][LUN_NOME+1];\
#endif\
extern char **simboli;\
extern swidget Message;
*FilterWindow.ispecdecl: int Index; 
*FilterWindow.ispeclist: Index
*FilterWindow.ispeclist.Index: "int", "%Index%"
*FilterWindow.funcdecl: swidget create_FilterWindow(Position x,Position y,int Ind)\

*FilterWindow.funcname: create_FilterWindow
*FilterWindow.funcdef: "swidget", "<create_FilterWindow>(%)"
*FilterWindow.argdecl: Position x;\
Position y;\
int Ind;
*FilterWindow.arglist: x, y, Ind
*FilterWindow.arglist.x: "Position", "%x%"
*FilterWindow.arglist.y: "Position", "%y%"
*FilterWindow.arglist.Ind: "int", "%Ind%"
*FilterWindow.icode: XmString Stringa;\
char descriz[72];\
int i,j;\
\
Index = Ind;
*FilterWindow.fcode: Stringa = XmStringCreate (simboli[Index], XmSTRING_DEFAULT_CHARSET);\
set_something (labSourceVarF, XmNlabelString, Stringa);\
\
#ifndef DESIGN_TIME\
XmTextFieldSetString (textFieldVarF, nomi_var[Index]);\
\
j=0;\
for (i=8;i<LUN_SIMB+1;i++)\
	{\
	descriz [j] = simboli[Index][i];\
	j++;\
	}\
XmTextFieldSetString (textFieldDescrF,descriz);\
#endif\
\
set_something (FilterWindow, XmNx, x+10);\
set_something (FilterWindow, XmNy, y+10);\
\
return(rtrn);\

*FilterWindow.auxdecl: /************************************************\
          Controlla se la stringa in input e' un float\
************************************************/\
\
Boolean NumFloVerifica(char *Stringa)\
{\
int i,lunghezza;\
\
lunghezza = strlen (Stringa);\
for (i=0;i<lunghezza;i++)\
        if ( (!isdigit(Stringa[i])) && (Stringa[i] != '.') ) return (False);\
return (True);\
}\

*FilterWindow.name: FilterWindow
*FilterWindow.x: 41
*FilterWindow.y: 603
*FilterWindow.width: 800
*FilterWindow.height: 250
*FilterWindow.iconName: "FILTER"
*FilterWindow.title: "Filter Dialog"
*FilterWindow.allowShellResize: "true"

*form3.class: form
*form3.parent: FilterWindow
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.unitType: "pixels"
*form3.x: 0
*form3.y: 10
*form3.width: 770
*form3.height: 250

*label15.class: label
*label15.parent: form3
*label15.static: true
*label15.name: label15
*label15.x: 10
*label15.y: 5
*label15.width: 170
*label15.height: 25
*label15.labelString: "Filter Type:"
*label15.leftAttachment: "attach_form"
*label15.leftOffset: 10
*label15.rightAttachment: "attach_none"
*label15.rightOffset: 10
*label15.topAttachment: "attach_form"
*label15.topOffset: 5

*toggleButton1.class: toggleButton
*toggleButton1.parent: form3
*toggleButton1.static: true
*toggleButton1.name: toggleButton1
*toggleButton1.x: 20
*toggleButton1.y: 30
*toggleButton1.width: 160
*toggleButton1.height: 30
*toggleButton1.indicatorType: "one_of_many"
*toggleButton1.indicatorSize: 20
*toggleButton1.labelString: "BESSEL"
*toggleButton1.leftAttachment: "attach_form"
*toggleButton1.leftOffset: 10
*toggleButton1.topAttachment: "attach_widget"
*toggleButton1.topOffset: 5
*toggleButton1.topWidget: "label15"
*toggleButton1.alignment: "alignment_beginning"
*toggleButton1.marginLeft: 30
*toggleButton1.armCallback: {\
XmToggleButtonSetState (toggleButton2, False, False);\
}
*toggleButton1.disarmCallback: {\
XmToggleButtonSetState (toggleButton1, True, False);\
}

*toggleButton2.class: toggleButton
*toggleButton2.parent: form3
*toggleButton2.static: true
*toggleButton2.name: toggleButton2
*toggleButton2.x: 10
*toggleButton2.y: 70
*toggleButton2.width: 160
*toggleButton2.height: 30
*toggleButton2.indicatorType: "one_of_many"
*toggleButton2.indicatorSize: 20
*toggleButton2.labelString: "BUTTERWORTH"
*toggleButton2.alignment: "alignment_beginning"
*toggleButton2.marginLeft: 30
*toggleButton2.topAttachment: "attach_widget"
*toggleButton2.topOffset: 5
*toggleButton2.topWidget: "toggleButton1"
*toggleButton2.armCallback: {\
XmToggleButtonSetState (toggleButton1, False, False);\
}
*toggleButton2.disarmCallback: {\
XmToggleButtonSetState (toggleButton2, True, False);\
}

*separator9.class: separator
*separator9.parent: form3
*separator9.static: true
*separator9.name: separator9
*separator9.x: 5
*separator9.y: 105
*separator9.width: 175
*separator9.height: 15
*separator9.leftAttachment: "attach_form"
*separator9.leftOffset: 5
*separator9.rightAttachment: "attach_none"
*separator9.rightOffset: 5
*separator9.topAttachment: "attach_widget"
*separator9.topOffset: 5
*separator9.topWidget: "toggleButton2"

*label16.class: label
*label16.parent: form3
*label16.static: true
*label16.name: label16
*label16.x: 10
*label16.y: 125
*label16.width: 170
*label16.height: 30
*label16.leftAttachment: "attach_form"
*label16.leftOffset: 10
*label16.rightAttachment: "attach_none"
*label16.rightOffset: 10
*label16.topAttachment: "attach_widget"
*label16.topOffset: 5
*label16.topWidget: "separator9"
*label16.labelString: "Cut Frequency:"

*textFCut.class: textField
*textFCut.parent: form3
*textFCut.static: true
*textFCut.name: textFCut
*textFCut.x: 30
*textFCut.y: 160
*textFCut.width: 120
*textFCut.height: 30
*textFCut.topAttachment: "attach_widget"
*textFCut.topOffset: 5
*textFCut.topWidget: "label16"
*textFCut.maxLength: 10

*separator10.class: separator
*separator10.parent: form3
*separator10.static: true
*separator10.name: separator10
*separator10.x: 50
*separator10.y: 195
*separator10.width: 230
*separator10.height: 15
*separator10.leftAttachment: "attach_form"
*separator10.leftOffset: 5
*separator10.rightAttachment: "attach_form"
*separator10.rightOffset: 5
*separator10.topAttachment: "attach_widget"
*separator10.topOffset: 5
*separator10.topWidget: "textFCut"

*pushButton17.class: pushButton
*pushButton17.parent: form3
*pushButton17.static: true
*pushButton17.name: pushButton17
*pushButton17.x: 20
*pushButton17.y: 210
*pushButton17.width: 70
*pushButton17.height: 30
*pushButton17.bottomAttachment: "attach_form"
*pushButton17.bottomOffset: 5
*pushButton17.leftAttachment: "attach_form"
*pushButton17.leftOffset: 10
*pushButton17.topAttachment: "attach_widget"
*pushButton17.topOffset: 5
*pushButton17.topWidget: "separator10"
*pushButton17.labelString: "OK"
*pushButton17.activateCallback: {\
XmString Messaggio;\
char *Valore,*Nome,*Descrizione;\
float FreqCut;\
Boolean Tog1,Tog2;\
char *ritorno;\
\
Tog1 = XmToggleButtonGetState (toggleButton1);\
Tog2 = XmToggleButtonGetState (toggleButton2);\
Valore = XmTextFieldGetString (textFCut);\
Nome = XmTextFieldGetString (textFieldVarF);\
\
ritorno = EseguiControlliInput (Tog1,Tog2,Valore,Nome);\
if (ritorno == NULL)\
	{\
	FreqCut = atof (Valore);\
	Descrizione = XmTextFieldGetString (textFieldDescrF);\
\
	if ( XmToggleButtonGetState(toggleButton1) )\
		EseguiFiltro (Index,BESSEL,Nome,Descrizione,FreqCut);\
	else if ( XmToggleButtonGetState (toggleButton2) )\
		EseguiFiltro (Index,BUTTERWORTH,Nome,Descrizione,FreqCut);\
	XtDestroyWidget (FilterWindow);\
	}\
else\
	{\
	Messaggio = XmStringCreate (ritorno, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNmessageString, Messaggio);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	XtFree (ritorno);\
	}\
}

*pushButton18.class: pushButton
*pushButton18.parent: form3
*pushButton18.static: true
*pushButton18.name: pushButton18
*pushButton18.x: 90
*pushButton18.y: 210
*pushButton18.width: 70
*pushButton18.height: 30
*pushButton18.labelString: "CANCEL"
*pushButton18.bottomAttachment: "attach_form"
*pushButton18.bottomOffset: 5
*pushButton18.leftAttachment: "attach_widget"
*pushButton18.leftOffset: 10
*pushButton18.leftWidget: "pushButton17"
*pushButton18.topAttachment: "attach_widget"
*pushButton18.topOffset: 5
*pushButton18.topWidget: "separator10"
*pushButton18.activateCallback: {\
XtDestroyWidget (FilterWindow);\
}

*separator11.class: separator
*separator11.parent: form3
*separator11.static: true
*separator11.name: separator11
*separator11.x: 186
*separator11.y: 80
*separator11.width: 13
*separator11.height: 53
*separator11.orientation: "vertical"
*separator11.bottomAttachment: "attach_widget"
*separator11.bottomOffset: 5
*separator11.bottomWidget: "separator10"
*separator11.leftAttachment: "attach_widget"
*separator11.leftOffset: 10
*separator11.leftWidget: "separator9"
*separator11.topOffset: 5
*separator11.topAttachment: "attach_form"

*label17.class: label
*label17.parent: form3
*label17.static: true
*label17.name: label17
*label17.x: 206
*label17.y: 10
*label17.width: 120
*label17.height: 20
*label17.labelString: "Source Variables:"
*label17.leftAttachment: "attach_widget"
*label17.leftOffset: 10
*label17.leftWidget: "separator11"
*label17.topAttachment: "attach_form"
*label17.topOffset: 10

*labSourceVarF.class: label
*labSourceVarF.parent: form3
*labSourceVarF.static: true
*labSourceVarF.name: labSourceVarF
*labSourceVarF.x: 216
*labSourceVarF.y: 40
*labSourceVarF.width: 496
*labSourceVarF.height: 25
*labSourceVarF.labelString: ""
*labSourceVarF.fontList: "fixed"
*labSourceVarF.alignment: "alignment_beginning"
*labSourceVarF.leftAttachment: "attach_widget"
*labSourceVarF.leftOffset: 10
*labSourceVarF.leftWidget: "separator11"
*labSourceVarF.rightAttachment: "attach_form"
*labSourceVarF.rightOffset: 10
*labSourceVarF.topAttachment: "attach_widget"
*labSourceVarF.topOffset: 10
*labSourceVarF.topWidget: "label17"

*separator12.class: separator
*separator12.parent: form3
*separator12.static: true
*separator12.name: separator12
*separator12.x: 216
*separator12.y: 80
*separator12.width: 505
*separator12.height: 10
*separator12.leftAttachment: "attach_widget"
*separator12.leftOffset: 5
*separator12.leftWidget: "separator11"
*separator12.rightAttachment: "attach_form"
*separator12.rightOffset: 5
*separator12.topAttachment: "attach_none"
*separator12.topOffset: 0

*label19.class: label
*label19.parent: form3
*label19.static: true
*label19.name: label19
*label19.x: 219
*label19.y: 160
*label19.width: 85
*label19.height: 25
*label19.alignment: "alignment_end"
*label19.labelString: "description:"
*label19.leftAttachment: "attach_widget"
*label19.leftOffset: 10
*label19.leftWidget: "separator11"

*label20.class: label
*label20.parent: form3
*label20.static: true
*label20.name: label20
*label20.x: 214
*label20.y: 105
*label20.width: 115
*label20.height: 20
*label20.labelString: "Target Variable:"
*label20.leftAttachment: "attach_widget"
*label20.leftOffset: 10
*label20.leftWidget: "separator11"
*label20.topAttachment: "attach_widget"
*label20.topOffset: 10
*label20.topWidget: "separator12"

*label18.class: label
*label18.parent: form3
*label18.static: true
*label18.name: label18
*label18.x: 219
*label18.y: 125
*label18.width: 85
*label18.height: 25
*label18.alignment: "alignment_end"
*label18.labelString: "name:"
*label18.leftAttachment: "attach_widget"
*label18.leftOffset: 10
*label18.leftWidget: "separator11"
*label18.topAttachment: "attach_widget"
*label18.topOffset: 5
*label18.topWidget: "label20"

*textFieldVarF.class: textField
*textFieldVarF.parent: form3
*textFieldVarF.static: true
*textFieldVarF.name: textFieldVarF
*textFieldVarF.x: 306
*textFieldVarF.y: 125
*textFieldVarF.width: 110
*textFieldVarF.height: 25
*textFieldVarF.maxLength: 8
*textFieldVarF.columns: 15
*textFieldVarF.fontList: "fixed"
*textFieldVarF.text: ""
*textFieldVarF.marginHeight: 2
*textFieldVarF.leftAttachment: "attach_widget"
*textFieldVarF.leftOffset: 10
*textFieldVarF.leftWidget: "label18"

*textFieldDescrF.class: textField
*textFieldDescrF.parent: form3
*textFieldDescrF.static: true
*textFieldDescrF.name: textFieldDescrF
*textFieldDescrF.x: 306
*textFieldDescrF.y: 160
*textFieldDescrF.width: 375
*textFieldDescrF.height: 25
*textFieldDescrF.maxLength: 72
*textFieldDescrF.columns: 72
*textFieldDescrF.marginHeight: 2
*textFieldDescrF.fontList: "fixed"
*textFieldDescrF.leftAttachment: "attach_widget"
*textFieldDescrF.leftOffset: 10
*textFieldDescrF.leftWidget: "label19"
*textFieldDescrF.rightAttachment: "attach_form"
*textFieldDescrF.rightOffset: 10
*textFieldDescrF.topAttachment: "attach_widget"
*textFieldDescrF.topOffset: 10
*textFieldDescrF.topWidget: "textFieldVarF"

