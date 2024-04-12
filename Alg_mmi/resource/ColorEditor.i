! UIMX ascii 2.5 key: 8266                                                      

*ColorEditor.class: topLevelShell
*ColorEditor.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ColorEditor.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)ColorEditor.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <X11/Xutil.h>\
#include <X11/Xos.h>\
#include "res_edit.h"\
\
extern Display *UxDisplay;\
\
Colormap cmap;\

*ColorEditor.ispecdecl: Pixel OriginalPixel,WorkingPixel;\
XColor newcolor;\
int screen;\
int va1,va2,va3;\
Widget Testo;
*ColorEditor.ispeclist: OriginalPixel, WorkingPixel, newcolor, screen, va1, va2, va3, Testo
*ColorEditor.ispeclist.OriginalPixel: "Pixel", "%OriginalPixel%"
*ColorEditor.ispeclist.WorkingPixel: "Pixel", "%WorkingPixel%"
*ColorEditor.ispeclist.newcolor: "XColor", "%newcolor%"
*ColorEditor.ispeclist.screen: "int", "%screen%"
*ColorEditor.ispeclist.va1: "int", "%va1%"
*ColorEditor.ispeclist.va2: "int", "%va2%"
*ColorEditor.ispeclist.va3: "int", "%va3%"
*ColorEditor.ispeclist.Testo: "Widget", "%Testo%"
*ColorEditor.funcdecl: swidget create_ColorEditor(Pixel *ColoreInput,Widget TestoInp,\
			Widget ChiamCEd)\

*ColorEditor.funcname: create_ColorEditor
*ColorEditor.funcdef: "swidget", "<create_ColorEditor>(%)"
*ColorEditor.argdecl: Pixel *ColoreInput;\
Widget TestoInp;\
Widget ChiamCEd;
*ColorEditor.arglist: ColoreInput, TestoInp, ChiamCEd
*ColorEditor.arglist.ColoreInput: "Pixel", "*%ColoreInput%"
*ColorEditor.arglist.TestoInp: "Widget", "%TestoInp%"
*ColorEditor.arglist.ChiamCEd: "Widget", "%ChiamCEd%"
*ColorEditor.icode: XColor TrovaRGB;\
unsigned long planes[1],pixels[2];\
char mess[50],StrColore[15];\
Status stat;\
\
Testo = TestoInp;
*ColorEditor.fcode: /*  Open display  */\
screen = DefaultScreen (UxDisplay);\
cmap = DefaultColormap (UxDisplay,screen);\
\
newcolor.flags = DoRed | DoGreen | DoBlue;\
newcolor.red = 0;\
newcolor.green = 0;\
newcolor.blue = 0;\
\
/*  Alloca read/write cells  */\
stat = XAllocColorCells (UxDisplay,cmap,False,planes,0,pixels,2);\
if (stat != 0)\
	{\
	WorkingPixel = newcolor.pixel = pixels[0];\
	OriginalPixel = pixels[1];\
\
	TrovaRGB.pixel = *ColoreInput;\
	XQueryColor ( UxDisplay , cmap , &TrovaRGB );\
\
	/*  new color-RGB value  */\
	newcolor.red   = TrovaRGB.red;\
	newcolor.green = TrovaRGB.green;\
	newcolor.blue  = TrovaRGB.blue;\
\
	/*  Define Initial Color  */\
	XStoreColor ( UxDisplay , cmap , &newcolor );\
	newcolor.pixel = OriginalPixel;\
	XStoreColor ( UxDisplay , cmap , &newcolor );\
\
	set_something (ButtNomeColoreWork, XmNbackground, WorkingPixel);\
	set_something (ButtNomeColoreOrig, XmNbackground, OriginalPixel);\
	sprintf (StrColore,"#%04x%04x%04x",TrovaRGB.red,TrovaRGB.green,TrovaRGB.blue);\
	XmTextFieldSetString (textField1, StrColore);\
	newcolor.pixel = WorkingPixel;\
	va1 = (int )( newcolor.red   / 256 );\
	va2 = (int )( newcolor.green / 256 );\
	va3 = (int )( newcolor.blue  / 256 );\
	XmScaleSetValue (ScalaRed, va1);\
	XmScaleSetValue (ScalaGreen, va2);\
	XmScaleSetValue (ScalaBlue, va3);\
	}\
else\
	{\
	strcpy (mess,"Unable to alloc color !");\
	XmTextFieldSetString (textField1, mess);\
	set_something (ScalaRed, XmNsensitive, False);\
	set_something (ScalaGreen, XmNsensitive, False);\
	set_something (ScalaBlue, XmNsensitive, False);\
	set_something (pushButton5, XmNsensitive, False);  /*  OK */\
	set_something (pushButton6, XmNsensitive, False);  /*  APPLY */\
	set_something (pushButton8, XmNsensitive, False);  /*  RESET */\
	}\
\
/*  Setta la posizione dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (ColorEditor,ChiamCEd);\
\
return(rtrn);
*ColorEditor.auxdecl:
*ColorEditor.static: true
*ColorEditor.name: ColorEditor
*ColorEditor.parent: NO_PARENT
*ColorEditor.parentExpression: ChiamCEd
*ColorEditor.x: 804
*ColorEditor.y: 94
*ColorEditor.width: 390
*ColorEditor.height: 536
*ColorEditor.iconName: "Color Edit"
*ColorEditor.title: "Resource Color Editor"

*mainWindow3.class: mainWindow
*mainWindow3.static: true
*mainWindow3.name: mainWindow3
*mainWindow3.parent: ColorEditor
*mainWindow3.unitType: "pixels"
*mainWindow3.x: 50
*mainWindow3.y: 30
*mainWindow3.width: 390
*mainWindow3.height: 536

*form4.class: form
*form4.static: true
*form4.name: form4
*form4.parent: mainWindow3

*label4.class: label
*label4.static: true
*label4.name: label4
*label4.parent: form4
*label4.x: 10
*label4.y: 10
*label4.width: 65
*label4.height: 35
*label4.labelString: "Color:"
*label4.alignment: "alignment_end"
*label4.leftAttachment: "attach_form"
*label4.leftOffset: 10
*label4.topAttachment: "attach_position"
*label4.topOffset: 0
*label4.bottomAttachment: "attach_position"
*label4.bottomOffset: 0
*label4.bottomPosition: 10
*label4.topPosition: 2

*separator4.class: separator
*separator4.static: true
*separator4.name: separator4
*separator4.parent: form4
*separator4.x: 10
*separator4.y: 60
*separator4.width: 350
*separator4.height: 20
*separator4.rightAttachment: "attach_position"
*separator4.rightOffset: 0
*separator4.topAttachment: "attach_position"
*separator4.topOffset: 0
*separator4.topWidget: ""
*separator4.leftAttachment: "attach_position"
*separator4.leftOffset: 0
*separator4.leftPosition: 1
*separator4.rightPosition: 99
*separator4.bottomAttachment: "attach_position"
*separator4.bottomPosition: 14
*separator4.topPosition: 12

*label5.class: label
*label5.static: true
*label5.name: label5
*label5.parent: form4
*label5.x: 45
*label5.y: 65
*label5.width: 290
*label5.height: 35
*label5.leftAttachment: "attach_position"
*label5.leftOffset: 0
*label5.rightAttachment: "attach_position"
*label5.rightOffset: 0
*label5.topAttachment: "attach_position"
*label5.topOffset: 0
*label5.topWidget: ""
*label5.labelString: "Color Samples"
*label5.bottomAttachment: "attach_position"
*label5.bottomPosition: 22
*label5.rightPosition: 90
*label5.topPosition: 15
*label5.leftPosition: 10

*label6.class: label
*label6.static: true
*label6.name: label6
*label6.parent: form4
*label6.x: 15
*label6.y: 115
*label6.width: 150
*label6.height: 30
*label6.leftAttachment: "attach_position"
*label6.leftOffset: 0
*label6.topAttachment: "attach_position"
*label6.topOffset: 0
*label6.topWidget: ""
*label6.labelString: "Original:"
*label6.bottomAttachment: "attach_position"
*label6.bottomPosition: 31
*label6.topPosition: 25
*label6.leftPosition: 5
*label6.rightPosition: 45
*label6.rightAttachment: "attach_position"

*label7.class: label
*label7.static: true
*label7.name: label7
*label7.parent: form4
*label7.x: 195
*label7.y: 115
*label7.width: 150
*label7.height: 30
*label7.labelString: "Working:"
*label7.topAttachment: "attach_position"
*label7.topOffset: 0
*label7.topWidget: ""
*label7.rightAttachment: "attach_position"
*label7.rightOffset: 0
*label7.bottomAttachment: "attach_position"
*label7.bottomPosition: 31
*label7.topPosition: 25
*label7.leftAttachment: "attach_position"
*label7.leftPosition: 55
*label7.rightPosition: 95

*ButtNomeColoreOrig.class: drawnButton
*ButtNomeColoreOrig.name.source: public
*ButtNomeColoreOrig.static: false
*ButtNomeColoreOrig.name: ButtNomeColoreOrig
*ButtNomeColoreOrig.parent: form4
*ButtNomeColoreOrig.x: 15
*ButtNomeColoreOrig.y: 150
*ButtNomeColoreOrig.width: 140
*ButtNomeColoreOrig.height: 45
*ButtNomeColoreOrig.topAttachment: "attach_position"
*ButtNomeColoreOrig.topOffset: 0
*ButtNomeColoreOrig.topWidget: "label6"
*ButtNomeColoreOrig.sensitive: "false"
*ButtNomeColoreOrig.bottomAttachment: "attach_position"
*ButtNomeColoreOrig.bottomPosition: 40
*ButtNomeColoreOrig.topPosition: 32
*ButtNomeColoreOrig.leftAttachment: "attach_position"
*ButtNomeColoreOrig.leftOffset: 0
*ButtNomeColoreOrig.leftPosition: 5
*ButtNomeColoreOrig.rightPosition: 45
*ButtNomeColoreOrig.rightAttachment: "attach_position"

*ButtNomeColoreWork.class: drawnButton
*ButtNomeColoreWork.name.source: public
*ButtNomeColoreWork.static: false
*ButtNomeColoreWork.name: ButtNomeColoreWork
*ButtNomeColoreWork.parent: form4
*ButtNomeColoreWork.x: 200
*ButtNomeColoreWork.y: 150
*ButtNomeColoreWork.width: 140
*ButtNomeColoreWork.height: 45
*ButtNomeColoreWork.topAttachment: "attach_position"
*ButtNomeColoreWork.topOffset: 0
*ButtNomeColoreWork.topWidget: "label7"
*ButtNomeColoreWork.rightAttachment: "attach_position"
*ButtNomeColoreWork.rightOffset: 0
*ButtNomeColoreWork.sensitive: "false"
*ButtNomeColoreWork.bottomAttachment: "attach_position"
*ButtNomeColoreWork.bottomPosition: 40
*ButtNomeColoreWork.topPosition: 32
*ButtNomeColoreWork.leftAttachment: "attach_position"
*ButtNomeColoreWork.leftPosition: 55
*ButtNomeColoreWork.rightPosition: 95

*separator5.class: separator
*separator5.static: true
*separator5.name: separator5
*separator5.parent: form4
*separator5.x: 10
*separator5.y: 205
*separator5.width: 350
*separator5.height: 20
*separator5.leftOffset: 0
*separator5.rightAttachment: "attach_position"
*separator5.rightOffset: 0
*separator5.leftAttachment: "attach_position"
*separator5.topAttachment: "attach_position"
*separator5.topOffset: 0
*separator5.topWidget: ""
*separator5.leftPosition: 1
*separator5.rightPosition: 99
*separator5.bottomAttachment: "attach_position"
*separator5.bottomPosition: 43
*separator5.topPosition: 41

*label8.class: label
*label8.static: true
*label8.name: label8
*label8.parent: form4
*label8.x: 45
*label8.y: 225
*label8.width: 280
*label8.height: 30
*label8.leftAttachment: "attach_position"
*label8.leftOffset: 0
*label8.rightAttachment: "attach_position"
*label8.rightOffset: 0
*label8.topAttachment: "attach_position"
*label8.topOffset: 0
*label8.topWidget: ""
*label8.labelString: "R G B Components"
*label8.bottomAttachment: "attach_position"
*label8.bottomPosition: 50
*label8.leftPosition: 3
*label8.rightPosition: 97
*label8.topPosition: 44

*ScalaRed.class: scale
*ScalaRed.static: true
*ScalaRed.name: ScalaRed
*ScalaRed.parent: form4
*ScalaRed.x: 20
*ScalaRed.y: 265
*ScalaRed.width: 320
*ScalaRed.height: 65
*ScalaRed.orientation: "horizontal"
*ScalaRed.maximum: 255
*ScalaRed.showValue: "true"
*ScalaRed.titleString: "RED"
*ScalaRed.leftAttachment: "attach_position"
*ScalaRed.leftOffset: 0
*ScalaRed.rightAttachment: "attach_position"
*ScalaRed.rightOffset: 0
*ScalaRed.topAttachment: "attach_position"
*ScalaRed.topOffset: 0
*ScalaRed.topWidget: ""
*ScalaRed.valueChangedCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaRed, &va1);\
\
newcolor.red = (unsigned short)va1*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor (UxDisplay,cmap,&newcolor);\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1 , vstring);\
}
*ScalaRed.dragCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaRed, &va1);\
\
newcolor.red = (unsigned short)va1*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor (UxDisplay,cmap,&newcolor);\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1 , vstring);\
}
*ScalaRed.leftPosition: 3
*ScalaRed.rightPosition: 97
*ScalaRed.bottomAttachment: "attach_position"
*ScalaRed.bottomPosition: 63
*ScalaRed.topPosition: 51

*ScalaGreen.class: scale
*ScalaGreen.static: true
*ScalaGreen.name: ScalaGreen
*ScalaGreen.parent: form4
*ScalaGreen.x: 15
*ScalaGreen.y: 330
*ScalaGreen.width: 320
*ScalaGreen.height: 65
*ScalaGreen.orientation: "horizontal"
*ScalaGreen.maximum: 255
*ScalaGreen.showValue: "true"
*ScalaGreen.titleString: "GREEN"
*ScalaGreen.valueChangedCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaGreen, &va2);\
\
newcolor.green = (unsigned short)va2*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor ( UxDisplay , cmap , &newcolor );\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1 , vstring);\
}
*ScalaGreen.dragCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaGreen, &va2);\
\
newcolor.green = (unsigned short)va2*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor ( UxDisplay , cmap , &newcolor );\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1 , vstring);\
}
*ScalaGreen.leftAttachment: "attach_position"
*ScalaGreen.leftOffset: 0
*ScalaGreen.rightAttachment: "attach_position"
*ScalaGreen.rightOffset: 0
*ScalaGreen.topAttachment: "attach_position"
*ScalaGreen.topOffset: 0
*ScalaGreen.topWidget: ""
*ScalaGreen.leftPosition: 3
*ScalaGreen.rightPosition: 97
*ScalaGreen.bottomAttachment: "attach_position"
*ScalaGreen.bottomPosition: 76
*ScalaGreen.topPosition: 64

*ScalaBlue.class: scale
*ScalaBlue.static: true
*ScalaBlue.name: ScalaBlue
*ScalaBlue.parent: form4
*ScalaBlue.x: 15
*ScalaBlue.y: 410
*ScalaBlue.width: 320
*ScalaBlue.height: 65
*ScalaBlue.orientation: "horizontal"
*ScalaBlue.maximum: 255
*ScalaBlue.showValue: "true"
*ScalaBlue.titleString: "BLUE"
*ScalaBlue.valueChangedCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaBlue, &va3);\
\
newcolor.blue = (unsigned short)va3*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor ( UxDisplay , cmap , &newcolor );\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1, vstring);\
}
*ScalaBlue.dragCallback: {\
char vstring[20];\
\
XmScaleGetValue (ScalaBlue, &va3);\
\
newcolor.blue = (unsigned short)va3*256;\
XStoreColor (UxDisplay,cmap,&newcolor);\
\
XQueryColor ( UxDisplay , cmap , &newcolor );\
sprintf (vstring,"#%04x%04x%04x",newcolor.red,newcolor.green,newcolor.blue);\
XmTextFieldSetString (textField1, vstring);\
}
*ScalaBlue.leftAttachment: "attach_position"
*ScalaBlue.leftOffset: 0
*ScalaBlue.rightAttachment: "attach_position"
*ScalaBlue.rightOffset: 0
*ScalaBlue.topAttachment: "attach_position"
*ScalaBlue.topOffset: 0
*ScalaBlue.topWidget: ""
*ScalaBlue.leftPosition: 3
*ScalaBlue.rightPosition: 97
*ScalaBlue.bottomAttachment: "attach_position"
*ScalaBlue.bottomPosition: 89
*ScalaBlue.topPosition: 77

*separator6.class: separator
*separator6.static: true
*separator6.name: separator6
*separator6.parent: form4
*separator6.x: 5
*separator6.y: 465
*separator6.width: 350
*separator6.height: 10
*separator6.leftAttachment: "attach_position"
*separator6.leftOffset: 0
*separator6.rightAttachment: "attach_position"
*separator6.rightOffset: 0
*separator6.topAttachment: "attach_position"
*separator6.topOffset: 0
*separator6.topWidget: ""
*separator6.leftPosition: 1
*separator6.rightPosition: 99
*separator6.bottomAttachment: "attach_position"
*separator6.bottomPosition: 91
*separator6.topPosition: 90

*pushButton7.class: pushButton
*pushButton7.static: true
*pushButton7.name: pushButton7
*pushButton7.parent: form4
*pushButton7.x: 274
*pushButton7.y: 489
*pushButton7.width: 81
*pushButton7.height: 35
*pushButton7.labelString: "CANCEL"
*pushButton7.activateCallback: {\
XtDestroyWidget (ColorEditor);\
}
*pushButton7.bottomAttachment: "attach_position"
*pushButton7.bottomOffset: 0
*pushButton7.leftAttachment: "attach_position"
*pushButton7.leftOffset: 0
*pushButton7.rightAttachment: "attach_position"
*pushButton7.rightOffset: 0
*pushButton7.topAttachment: "attach_position"
*pushButton7.topOffset: 0
*pushButton7.topWidget: ""
*pushButton7.bottomPosition: 98
*pushButton7.topPosition: 92
*pushButton7.leftPosition: 69
*pushButton7.rightPosition: 89

*pushButton8.class: pushButton
*pushButton8.static: true
*pushButton8.name: pushButton8
*pushButton8.parent: form4
*pushButton8.x: 190
*pushButton8.y: 490
*pushButton8.width: 80
*pushButton8.height: 35
*pushButton8.labelString: "RESET"
*pushButton8.activateCallback: {\
XColor reset;\
\
reset.pixel = OriginalPixel;\
XQueryColor ( UxDisplay , cmap , &reset );\
reset.pixel = WorkingPixel;\
XStoreColor ( UxDisplay , cmap , &reset );\
set_something (ButtNomeColoreWork, XmNbackground, reset.pixel);\
va1 = (int )( reset.red   / 256 );\
va2 = (int )( reset.green / 256 );\
va3 = (int )( reset.blue  / 256 );\
XmScaleSetValue (ScalaRed, va1);\
XmScaleSetValue (ScalaGreen, va2);\
XmScaleSetValue (ScalaBlue, va3);\
}
*pushButton8.bottomAttachment: "attach_position"
*pushButton8.bottomOffset: 0
*pushButton8.leftAttachment: "attach_position"
*pushButton8.leftOffset: 0
*pushButton8.rightAttachment: "attach_position"
*pushButton8.rightOffset: 0
*pushButton8.rightWidget: ""
*pushButton8.topAttachment: "attach_position"
*pushButton8.topOffset: 0
*pushButton8.topWidget: ""
*pushButton8.bottomPosition: 98
*pushButton8.topPosition: 92
*pushButton8.leftPosition: 47
*pushButton8.rightPosition: 67

*pushButton6.class: pushButton
*pushButton6.static: true
*pushButton6.name: pushButton6
*pushButton6.parent: form4
*pushButton6.x: 100
*pushButton6.y: 490
*pushButton6.width: 80
*pushButton6.height: 35
*pushButton6.labelString: "APPLY"
*pushButton6.activateCallback: {\
XColor nuovo;\
Pixel col;\
\
nuovo.pixel = WorkingPixel;\
XQueryColor ( UxDisplay , cmap , &nuovo );\
nuovo.pixel = OriginalPixel;\
XStoreColor(UxDisplay, cmap, &nuovo);\
set_something (ButtNomeColoreOrig, XmNbackground, nuovo.pixel);\
}
*pushButton6.bottomAttachment: "attach_position"
*pushButton6.bottomOffset: 0
*pushButton6.leftAttachment: "attach_position"
*pushButton6.leftOffset: 0
*pushButton6.rightAttachment: "attach_position"
*pushButton6.rightOffset: 0
*pushButton6.rightWidget: ""
*pushButton6.topAttachment: "attach_position"
*pushButton6.topOffset: 0
*pushButton6.topWidget: ""
*pushButton6.bottomPosition: 98
*pushButton6.topPosition: 92
*pushButton6.leftPosition: 25
*pushButton6.rightPosition: 45

*pushButton5.class: pushButton
*pushButton5.static: true
*pushButton5.name: pushButton5
*pushButton5.parent: form4
*pushButton5.x: 9
*pushButton5.y: 489
*pushButton5.width: 81
*pushButton5.height: 35
*pushButton5.labelString: "OK"
*pushButton5.activateCallback: {\
XColor ColoreOutput;\
char *StrOut;\
\
ColoreOutput.pixel = WorkingPixel;\
XQueryColor ( UxDisplay , cmap , &ColoreOutput );\
StrOut = (char *)XtCalloc (15,sizeof(char));\
sprintf (StrOut,"#%04x%04x%04x",ColoreOutput.red,ColoreOutput.green,ColoreOutput.blue);\
XmTextFieldSetString (Testo, StrOut);\
XtFree (StrOut);\
XtDestroyWidget (ColorEditor);\
}
*pushButton5.bottomAttachment: "attach_position"
*pushButton5.bottomOffset: 0
*pushButton5.leftAttachment: "attach_position"
*pushButton5.leftOffset: 0
*pushButton5.rightAttachment: "attach_position"
*pushButton5.rightOffset: 0
*pushButton5.rightWidget: ""
*pushButton5.topAttachment: "attach_position"
*pushButton5.topOffset: 0
*pushButton5.topWidget: ""
*pushButton5.bottomPosition: 98
*pushButton5.topPosition: 92
*pushButton5.leftPosition: 3
*pushButton5.rightPosition: 23

*textField1.class: textField
*textField1.static: true
*textField1.name: textField1
*textField1.parent: form4
*textField1.x: 80
*textField1.y: 10
*textField1.width: 295
*textField1.height: 35
*textField1.maxLength: 20
*textField1.bottomAttachment: "attach_position"
*textField1.bottomOffset: 0
*textField1.bottomWidget: "separator4"
*textField1.leftAttachment: "attach_widget"
*textField1.leftOffset: 5
*textField1.leftWidget: "label4"
*textField1.rightAttachment: "attach_form"
*textField1.rightOffset: 15
*textField1.topAttachment: "attach_position"
*textField1.topOffset: 0
*textField1.sensitive: "false"
*textField1.bottomPosition: 10
*textField1.topPosition: 2

