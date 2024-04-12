! UIMX ascii 2.5 key: 7444                                                      

*ColorViewer.class: topLevelShell
*ColorViewer.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ColorViewer.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)ColorViewer.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <string.h>\
#include <Xm/Xm.h>\
#include "res_edit.h"\
\
\
extern Display *UxDisplay;\
extern swidget create_ColorEditor();\
extern swidget create_ColorMapViewer();\

*ColorViewer.ispecdecl: swidget VettoreBottoni[12];\
XrmDatabase RisDbColori;\
int flagINP;\
Widget *FigliRC;\
Colormap Cmap;\
\
int Press;  /* Variabile associata alla seconda pressione del drawnButton\
		dei colori di default   */\
\
Boolean transparent;\
float blinkFreq;\
char StrColor[200];  
*ColorViewer.ispeclist: VettoreBottoni, RisDbColori, flagINP, FigliRC, Cmap, Press, transparent, blinkFreq, StrColor
*ColorViewer.ispeclist.VettoreBottoni: "swidget", "%VettoreBottoni%[12]"
*ColorViewer.ispeclist.RisDbColori: "XrmDatabase", "%RisDbColori%"
*ColorViewer.ispeclist.flagINP: "int", "%flagINP%"
*ColorViewer.ispeclist.FigliRC: "Widget", "*%FigliRC%"
*ColorViewer.ispeclist.Cmap: "Colormap", "%Cmap%"
*ColorViewer.ispeclist.Press: "int", "%Press%"
*ColorViewer.ispeclist.transparent: "Boolean", "%transparent%"
*ColorViewer.ispeclist.blinkFreq: "float", "%blinkFreq%"
*ColorViewer.ispeclist.StrColor: "unsigned char", "%StrColor%[200]"
*ColorViewer.funcdecl: swidget create_ColorViewer(Flag,StrInput,LabButt,Pdb,FigliINP,ChiamCol)\
int Flag;\
char *StrInput;\
XmString LabButt;\
XrmDatabase Pdb;\
Widget *FigliINP,ChiamCol;
*ColorViewer.funcname: create_ColorViewer
*ColorViewer.funcdef: "swidget", "<create_ColorViewer>(%)"
*ColorViewer.argdecl: int Flag;\
unsigned char *StrInput;\
XmString LabButt;\
XrmDatabase Pdb;\
Widget *FigliINP;\
Widget ChiamCol;
*ColorViewer.arglist: Flag, StrInput, LabButt, Pdb, FigliINP, ChiamCol
*ColorViewer.arglist.Flag: "int", "%Flag%"
*ColorViewer.arglist.StrInput: "unsigned char", "*%StrInput%"
*ColorViewer.arglist.LabButt: "XmString", "%LabButt%"
*ColorViewer.arglist.Pdb: "XrmDatabase", "%Pdb%"
*ColorViewer.arglist.FigliINP: "Widget", "*%FigliINP%"
*ColorViewer.arglist.ChiamCol: "Widget", "%ChiamCol%"
*ColorViewer.icode: Pixel PixColor;\
Boolean Result;\
int nStrRead=0;\
\
flagINP = Flag;\
FigliRC = FigliINP;\
RisDbColori = XrmGetFileDatabase("FileColoriDefault");\
XrmSetDatabase (UxDisplay,RisDbColori);\
\
Press  = 0;\
Cmap = DefaultColormap (UxDisplay, DefaultScreen (UxDisplay) );\
\
strcpy(StrColor,"");\
blinkFreq=0;\
nStrRead = sscanf(StrInput,"%s %f %d",StrColor,&blinkFreq,&transparent);\
\
printf("nStrRead = %d\n",nStrRead);\
\
if( nStrRead < 1)\
{\
   printf("Invalid input string");\
   blinkFreq = 0;\
   transparent = 0;\
}\
else if( nStrRead == 1)\
{\
   blinkFreq = 0;\
   transparent = 0;\
}\
\
/*\
printf("color %s  blink (Hz) %f transparent=%d\n",StrColor,blinkFreq,transparent);\
*/\

*ColorViewer.fcode: if ( !CvtStrToPixel (TextNomeColore,StrColor,&PixColor) )\
	set_something (EditItem,XmNsensitive,False);\
else	set_something (EditItem,XmNsensitive,True);\
\
VettoreBottoni [0] = drawnButton1;\
VettoreBottoni [1] = drawnButton2;\
VettoreBottoni [2] = drawnButton3;\
VettoreBottoni [3] = drawnButton4;\
VettoreBottoni [4] = drawnButton5;\
VettoreBottoni [5] = drawnButton6;\
VettoreBottoni [6] = drawnButton7;\
VettoreBottoni [7] = drawnButton8;\
VettoreBottoni [8] = drawnButton9;\
VettoreBottoni [9] = drawnButton10;\
VettoreBottoni[10] = drawnButton11;\
VettoreBottoni[11] = drawnButton12;\
	\
XmTextFieldSetString (TextNomeColore,StrColor);\
set_something (ButtNomeColore, XmNbackground, PixColor);\
set_something (labelColorRes, XmNlabelString, LabButt);\
XrmSetDatabase (UxDisplay,Pdb);\
\
/*  Setta la posizione dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (ColorViewer,ChiamCol);\
\
if (flagINP == CONFIG_VER)\
  {\
  set_something (FigliRC[0], XmNsensitive, False);\
  set_something (FigliRC[1], XmNsensitive, False);\
  }\
\
/* rendo insensitive la label e il Text Field della blink rate\
   se in origine la blink rate non era presente\
*/\
if( nStrRead >= 2)\
   ColorViewer_displayBlinkRate(ColorViewer,&UxEnv);\
else\
   ColorViewer_disableBlinkRate(ColorViewer,&UxEnv);\
\
/* set del menu trasparent in base al valore del XlAnimatedColor\
*/\
if( transparent )\
   set_something(trasparentMenu,XmNmenuHistory,transparentYes);\
else\
   set_something(trasparentMenu,XmNmenuHistory,transparentNo);\
\
\
return(rtrn);\

*ColorViewer.auxdecl: RilasciaDrawnButton (int IndiceSet)\
{\
int i;\
\
for (i=0;i<12;i++)\
	{\
	set_something (VettoreBottoni [i], XmNshadowThickness, 2);\
	set_something (VettoreBottoni [i], XmNshadowType, XmSHADOW_ETCHED_IN);\
	}\
set_something (VettoreBottoni[IndiceSet], XmNshadowThickness, 4);\
set_something (VettoreBottoni[IndiceSet], XmNshadowType, XmSHADOW_IN);\
}
*ColorViewer_displayBlinkRate.class: method
*ColorViewer_displayBlinkRate.name: displayBlinkRate
*ColorViewer_displayBlinkRate.parent: ColorViewer
*ColorViewer_displayBlinkRate.methodType: void
*ColorViewer_displayBlinkRate.methodArgs: 
*ColorViewer_displayBlinkRate.methodBody: char sfreq[20];\
\
sprintf(sfreq,"%f",blinkFreq);\
\
set_something(blink_frequency,XmNvalue,sfreq);

*ColorViewer_disableBlinkRate.class: method
*ColorViewer_disableBlinkRate.name: disableBlinkRate
*ColorViewer_disableBlinkRate.parent: ColorViewer
*ColorViewer_disableBlinkRate.methodType: int
*ColorViewer_disableBlinkRate.methodArgs: 
*ColorViewer_disableBlinkRate.methodBody: set_something(blink_frequency,XmNeditable,False );\
   set_something(blink_frequency,XmNsensitive,False );\
   set_something(BlinkRate,XmNsensitive,False );\


*ColorViewer_enableBlinkRate.class: method
*ColorViewer_enableBlinkRate.name: enableBlinkRate
*ColorViewer_enableBlinkRate.parent: ColorViewer
*ColorViewer_enableBlinkRate.methodType: int
*ColorViewer_enableBlinkRate.methodArgs: 
*ColorViewer_enableBlinkRate.methodBody: set_something(blink_frequency,XmNeditable,True );\
   set_something(blink_frequency,XmNsensitive,True );\
   set_something(BlinkRate,XmNsensitive,True );\


*ColorViewer.static: true
*ColorViewer.name: ColorViewer
*ColorViewer.parent: NO_PARENT
*ColorViewer.parentExpression: ChiamCol
*ColorViewer.x: 583
*ColorViewer.y: 15
*ColorViewer.width: 420
*ColorViewer.height: 400
*ColorViewer.iconName: "Color Viewer"
*ColorViewer.title: "Resource Color Viewer"
*ColorViewer.allowShellResize: "false"

*mainWindow2.class: mainWindow
*mainWindow2.static: true
*mainWindow2.name: mainWindow2
*mainWindow2.parent: ColorViewer
*mainWindow2.unitType: "pixels"
*mainWindow2.x: 0
*mainWindow2.y: 0
*mainWindow2.width: 405
*mainWindow2.height: 360

*form3.class: form
*form3.static: true
*form3.name: form3
*form3.parent: mainWindow2
*form3.resizePolicy: "resize_any"

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: form3
*label2.x: 10
*label2.y: 5
*label2.width: 110
*label2.height: 30
*label2.labelString: "Defaults:"
*label2.topOffset: 0
*label2.bottomAttachment: "attach_position"
*label2.bottomPosition: 12
*label2.leftAttachment: "attach_position"
*label2.leftOffset: 0
*label2.leftPosition: 5
*label2.rightAttachment: "attach_position"
*label2.rightPosition: 30
*label2.topAttachment: "attach_position"
*label2.topPosition: 2

*pushButton3.class: pushButton
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.parent: form3
*pushButton3.x: 110
*pushButton3.y: 255
*pushButton3.width: 85
*pushButton3.height: 35
*pushButton3.labelString: "APPLY"
*pushButton3.activateCallback: {\
Pixel Colore,PixColor;\
char *Str,*brate;\
Boolean Fatto,Result;\
char strOut[40];\
double blink_rate;\
\
Str = (char *)XmTextFieldGetString (TextNomeColore);\
Result = CvtStrToPixel (ButtNomeColore,Str,&PixColor);\
set_something (ButtNomeColore, XmNbackground, PixColor);\
brate = (char *)XmTextFieldGetString (blink_frequency);\
\
blink_rate = atof(brate);\
\
if( blink_rate > 0)\
   sprintf(strOut,"%s %s %d",Str,brate,transparent);\
else\
   sprintf(strOut,"%s",Str);\
\
/*\
printf( "strOut %s\n",strOut);\
*/\
\
if (flagINP == EDITOR_VER)\
	{\
	XmTextFieldSetString (FigliRC[2], strOut);\
	Fatto = CvtStrToPixel (FigliRC[4],Str,&Colore);\
	if (Fatto)\
	  set_something (FigliRC[4],XmNbackground,Colore);\
	}\
else if (flagINP == CONFIG_VER)\
	XmTextFieldSetString (FigliRC[1], Str);\
	\
XtFree (Str);\
XtFree (brate);\
}
*pushButton3.bottomAttachment: "attach_position"
*pushButton3.bottomOffset: 0
*pushButton3.topAttachment: "attach_position"
*pushButton3.topOffset: 0
*pushButton3.topWidget: ""
*pushButton3.bottomPosition: 96
*pushButton3.topPosition: 83
*pushButton3.leftAttachment: "attach_position"
*pushButton3.leftOffset: 0
*pushButton3.leftPosition: 25
*pushButton3.rightAttachment: "attach_position"
*pushButton3.rightPosition: 45

*pushButton4.class: pushButton
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.parent: form3
*pushButton4.x: 205
*pushButton4.y: 255
*pushButton4.width: 85
*pushButton4.height: 35
*pushButton4.labelString: "CANCEL"
*pushButton4.activateCallback: {\
if (flagINP == EDITOR_VER)\
	{\
	/*  Ritorna a sensitive il pushbutton e il textfield chiamante  */\
	set_something (FigliRC[0], XmNsensitive, True);\
	set_something (FigliRC[2], XmNsensitive, True);\
	}\
\
XtDestroyWidget (ColorViewer);\
}
*pushButton4.bottomAttachment: "attach_position"
*pushButton4.bottomOffset: 0
*pushButton4.topAttachment: "attach_position"
*pushButton4.topOffset: 0
*pushButton4.topWidget: ""
*pushButton4.bottomPosition: 96
*pushButton4.topPosition: 83
*pushButton4.leftAttachment: "attach_position"
*pushButton4.leftOffset: 0
*pushButton4.leftPosition: 47
*pushButton4.rightAttachment: "attach_position"
*pushButton4.rightPosition: 67

*pushButton2.class: pushButton
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.parent: form3
*pushButton2.x: 15
*pushButton2.y: 255
*pushButton2.width: 85
*pushButton2.height: 35
*pushButton2.labelString: "OK"
*pushButton2.activateCallback: {\
int i,j;\
Boolean Fatto;\
Pixel Colore,Punto;\
char StrPix[15],*vstring;\
char *brate;\
char strOut[40];\
XColor Pix;\
double blink_rate;\
\
if (flagINP == DRAW_VER)\
	{\
	Fatto = False;\
	j = 0;\
	i = 0;\
	while (Fatto==False)\
		{\
		get_something (VettoreBottoni[j], XmNbackground, &Punto); \
		set_something (FigliRC[i],XmNbackground,Punto);\
		j++;\
		i++;\
		if (i==12)\
			{\
			j=0;\
			i=16;\
			}\
		if (i==28) Fatto=True;\
		}\
	}			\
else if (flagINP == EDITOR_VER)\
	{\
	set_something (FigliRC[0], XmNsensitive, True);\
	set_something (FigliRC[2], XmNsensitive, True);\
	vstring = (char *)XmTextFieldGetString (TextNomeColore);\
	Fatto = CvtStrToPixel (FigliRC[4],vstring, &Colore);\
	if (Fatto)\
		set_something (FigliRC[4],XmNbackground,Colore);\
\
        brate = (char *)XmTextFieldGetString (blink_frequency);\
\
        blink_rate = atof(brate);\
      \
        if( blink_rate > 0)\
           sprintf(strOut,"%s %s %d",vstring,brate,transparent);\
        else\
           sprintf(strOut,"%s",vstring);\
/* \
        printf("strOut = %s\n",strOut);\
*/\
\
	XmTextFieldSetString (FigliRC[2], strOut);\
	XtFree (vstring);\
        XtFree( brate );\
	}\
else if (flagINP == CONFIG_VER)\
	{\
	set_something (FigliRC[0], XmNsensitive, True);\
	set_something (FigliRC[1], XmNsensitive, True);\
	vstring = (char *)XmTextFieldGetString (TextNomeColore);\
	XmTextFieldSetString (FigliRC[1], vstring);\
	XtFree (vstring);\
	}\
\
/*  Setta i background della palette di default nel database  */\
\
for (i=0;i<12;i++)\
	{\
	get_something (VettoreBottoni[i] , XmNbackground, &Pix.pixel);\
	XQueryColor (UxDisplay, Cmap, &Pix);\
	sprintf (StrPix,"#%04x%04x%04x",Pix.red,Pix.green,Pix.blue);\
	XlSetResourceByWidget (&RisDbColori,VettoreBottoni[i],\
					XmNbackground,StrPix);\
	}\
\
XrmPutFileDatabase (RisDbColori,"FileColoriDefault");\
XtDestroyWidget (ColorViewer);\
}
*pushButton2.bottomAttachment: "attach_position"
*pushButton2.bottomOffset: 0
*pushButton2.topAttachment: "attach_position"
*pushButton2.topOffset: 0
*pushButton2.topWidget: ""
*pushButton2.bottomPosition: 96
*pushButton2.topPosition: 83
*pushButton2.leftAttachment: "attach_position"
*pushButton2.leftOffset: 0
*pushButton2.leftPosition: 3
*pushButton2.rightAttachment: "attach_position"
*pushButton2.rightPosition: 23

*separator3.class: separator
*separator3.static: true
*separator3.name: separator3
*separator3.parent: form3
*separator3.x: 5
*separator3.y: 235
*separator3.width: 395
*separator3.height: 15
*separator3.leftAttachment: "attach_position"
*separator3.leftOffset: 0
*separator3.rightAttachment: "attach_position"
*separator3.rightOffset: 0
*separator3.topAttachment: "attach_position"
*separator3.topOffset: 0
*separator3.topWidget: ""
*separator3.bottomAttachment: "attach_position"
*separator3.bottomOffset: 0
*separator3.bottomWidget: ""
*separator3.leftPosition: 1
*separator3.rightPosition: 99
*separator3.bottomPosition: 83
*separator3.topPosition: 80

*ButtNomeColore.class: drawnButton
*ButtNomeColore.static: true
*ButtNomeColore.name: ButtNomeColore
*ButtNomeColore.parent: form3
*ButtNomeColore.x: 15
*ButtNomeColore.y: 196
*ButtNomeColore.width: 140
*ButtNomeColore.height: 44
*ButtNomeColore.leftAttachment: "attach_form"
*ButtNomeColore.leftOffset: 15
*ButtNomeColore.topAttachment: "attach_position"
*ButtNomeColore.topOffset: 0
*ButtNomeColore.topWidget: ""
*ButtNomeColore.sensitive: "false"
*ButtNomeColore.bottomAttachment: "attach_position"
*ButtNomeColore.bottomOffset: 0
*ButtNomeColore.bottomWidget: ""
*ButtNomeColore.bottomPosition: 63
*ButtNomeColore.topPosition: 53

*TextNomeColore.class: textField
*TextNomeColore.static: true
*TextNomeColore.name: TextNomeColore
*TextNomeColore.parent: form3
*TextNomeColore.x: 165
*TextNomeColore.y: 185
*TextNomeColore.width: 225
*TextNomeColore.height: 45
*TextNomeColore.maxLength: 50
*TextNomeColore.bottomAttachment: "attach_position"
*TextNomeColore.bottomOffset: 0
*TextNomeColore.bottomWidget: ""
*TextNomeColore.leftAttachment: "attach_widget"
*TextNomeColore.leftOffset: 10
*TextNomeColore.leftWidget: "ButtNomeColore"
*TextNomeColore.rightAttachment: "attach_form"
*TextNomeColore.rightOffset: 15
*TextNomeColore.topAttachment: "attach_position"
*TextNomeColore.topOffset: 0
*TextNomeColore.topWidget: ""
*TextNomeColore.bottomPosition: 63
*TextNomeColore.topPosition: 53

*separator2.class: separator
*separator2.static: true
*separator2.name: separator2
*separator2.parent: form3
*separator2.x: 0
*separator2.y: 150
*separator2.width: 380
*separator2.height: 20
*separator2.leftAttachment: "attach_position"
*separator2.leftOffset: 0
*separator2.rightAttachment: "attach_position"
*separator2.rightOffset: 0
*separator2.topAttachment: "attach_position"
*separator2.topOffset: 0
*separator2.topWidget: ""
*separator2.bottomAttachment: "attach_position"
*separator2.bottomOffset: 0
*separator2.bottomWidget: ""
*separator2.leftPosition: 1
*separator2.rightPosition: 99
*separator2.bottomPosition: 52
*separator2.topPosition: 50

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: form3
*label3.x: 5
*label3.y: 125
*label3.width: 120
*label3.height: 30
*label3.labelString: "Resource name:"
*label3.alignment: "alignment_end"
*label3.topAttachment: "attach_position"
*label3.bottomAttachment: "attach_position"
*label3.bottomOffset: 0
*label3.bottomWidget: ""
*label3.bottomPosition: 50
*label3.leftAttachment: "attach_position"
*label3.leftOffset: 0
*label3.leftPosition: 5
*label3.rightAttachment: "attach_position"
*label3.rightPosition: 35
*label3.topPosition: 35

*separator1.class: separator
*separator1.static: true
*separator1.name: separator1
*separator1.parent: form3
*separator1.x: 10
*separator1.y: 100
*separator1.width: 380
*separator1.height: 20
*separator1.leftOffset: 0
*separator1.leftAttachment: "attach_position"
*separator1.rightAttachment: "attach_position"
*separator1.rightOffset: 0
*separator1.bottomAttachment: "attach_position"
*separator1.bottomOffset: 0
*separator1.bottomWidget: ""
*separator1.topAttachment: "attach_position"
*separator1.topOffset: 0
*separator1.resizable: "false"
*separator1.bottomPosition: 33
*separator1.leftPosition: 1
*separator1.rightPosition: 99
*separator1.topPosition: 30

*labelColorRes.class: label
*labelColorRes.static: true
*labelColorRes.name: labelColorRes
*labelColorRes.parent: form3
*labelColorRes.x: 135
*labelColorRes.y: 95
*labelColorRes.width: 250
*labelColorRes.height: 30
*labelColorRes.labelString: ""
*labelColorRes.topAttachment: "attach_position"
*labelColorRes.topOffset: 0
*labelColorRes.topWidget: ""
*labelColorRes.rightAttachment: "attach_position"
*labelColorRes.rightOffset: 0
*labelColorRes.leftAttachment: "attach_position"
*labelColorRes.leftOffset: 0
*labelColorRes.leftWidget: ""
*labelColorRes.bottomAttachment: "attach_position"
*labelColorRes.bottomOffset: 0
*labelColorRes.bottomWidget: ""
*labelColorRes.alignment: "alignment_center"
*labelColorRes.bottomPosition: 50
*labelColorRes.leftPosition: 36
*labelColorRes.rightPosition: 97
*labelColorRes.topPosition: 35

*drawnButton12.class: drawnButton
*drawnButton12.static: true
*drawnButton12.name: drawnButton12
*drawnButton12.parent: form3
*drawnButton12.width: 60
*drawnButton12.height: 20
*drawnButton12.highlightOnEnter: "true"
*drawnButton12.pushButtonEnabled: "false"
*drawnButton12.highlightThickness: 2
*drawnButton12.shadowType: "shadow_etched_in"
*drawnButton12.shadowThickness: 2
*drawnButton12.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 12)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[11], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 12;\
	RilasciaDrawnButton (11);\
\
	get_something (VettoreBottoni[11], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton12.recomputeSize: "false"
*drawnButton12.x: 240
*drawnButton12.y: 70
*drawnButton12.topAttachment: "attach_position"
*drawnButton12.topOffset: 0
*drawnButton12.bottomAttachment: "attach_position"
*drawnButton12.bottomOffset: 0
*drawnButton12.bottomWidget: ""
*drawnButton12.resizable: "false"
*drawnButton12.leftAttachment: "attach_position"
*drawnButton12.leftOffset: 0
*drawnButton12.rightAttachment: "attach_position"
*drawnButton12.rightOffset: 0
*drawnButton12.bottomPosition: 28
*drawnButton12.topPosition: 22
*drawnButton12.leftPosition: 83
*drawnButton12.rightPosition: 97

*drawnButton6.class: drawnButton
*drawnButton6.static: true
*drawnButton6.name: drawnButton6
*drawnButton6.parent: form3
*drawnButton6.width: 60
*drawnButton6.height: 20
*drawnButton6.highlightOnEnter: "true"
*drawnButton6.pushButtonEnabled: "false"
*drawnButton6.highlightThickness: 2
*drawnButton6.shadowType: "shadow_etched_in"
*drawnButton6.shadowThickness: 2
*drawnButton6.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 6)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[5], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 6;\
	RilasciaDrawnButton (5);\
	get_something (VettoreBottoni[5], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton6.recomputeSize: "false"
*drawnButton6.bottomAttachment: "attach_position"
*drawnButton6.bottomOffset: 0
*drawnButton6.bottomWidget: "drawnButton12"
*drawnButton6.rightAttachment: "attach_position"
*drawnButton6.rightOffset: 0
*drawnButton6.topOffset: 0
*drawnButton6.resizable: "false"
*drawnButton6.leftAttachment: "attach_position"
*drawnButton6.topAttachment: "attach_position"
*drawnButton6.leftOffset: 0
*drawnButton6.rightWidget: ""
*drawnButton6.bottomPosition: 21
*drawnButton6.topPosition: 15
*drawnButton6.leftPosition: 83
*drawnButton6.rightPosition: 97

*drawnButton11.class: drawnButton
*drawnButton11.static: true
*drawnButton11.name: drawnButton11
*drawnButton11.parent: form3
*drawnButton11.width: 60
*drawnButton11.height: 20
*drawnButton11.highlightOnEnter: "true"
*drawnButton11.pushButtonEnabled: "false"
*drawnButton11.highlightThickness: 2
*drawnButton11.shadowType: "shadow_etched_in"
*drawnButton11.shadowThickness: 2
*drawnButton11.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 11)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[10], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 11;\
	RilasciaDrawnButton (10);\
\
	get_something (VettoreBottoni[10], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton11.recomputeSize: "false"
*drawnButton11.x: 220
*drawnButton11.y: 80
*drawnButton11.topAttachment: "attach_position"
*drawnButton11.topOffset: 0
*drawnButton11.bottomAttachment: "attach_position"
*drawnButton11.bottomOffset: 0
*drawnButton11.bottomWidget: ""
*drawnButton11.leftAttachment: "attach_position"
*drawnButton11.leftOffset: 0
*drawnButton11.resizable: "false"
*drawnButton11.rightAttachment: "attach_position"
*drawnButton11.rightOffset: 0
*drawnButton11.rightWidget: "drawnButton12"
*drawnButton11.bottomPosition: 28
*drawnButton11.topPosition: 22
*drawnButton11.leftPosition: 67
*drawnButton11.rightPosition: 81

*drawnButton5.class: drawnButton
*drawnButton5.static: true
*drawnButton5.name: drawnButton5
*drawnButton5.parent: form3
*drawnButton5.width: 60
*drawnButton5.height: 20
*drawnButton5.highlightOnEnter: "true"
*drawnButton5.pushButtonEnabled: "false"
*drawnButton5.highlightThickness: 2
*drawnButton5.shadowType: "shadow_etched_in"
*drawnButton5.shadowThickness: 2
*drawnButton5.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 5)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[4], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 5;\
	RilasciaDrawnButton (4);\
	get_something (VettoreBottoni[4], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton5.recomputeSize: "false"
*drawnButton5.bottomAttachment: "attach_position"
*drawnButton5.bottomOffset: 0
*drawnButton5.bottomWidget: "drawnButton11"
*drawnButton5.topAttachment: "attach_position"
*drawnButton5.topOffset: 0
*drawnButton5.rightAttachment: "attach_position"
*drawnButton5.rightOffset: 0
*drawnButton5.resizable: "false"
*drawnButton5.leftAttachment: "attach_position"
*drawnButton5.leftOffset: 0
*drawnButton5.rightWidget: "drawnButton6"
*drawnButton5.bottomPosition: 21
*drawnButton5.topPosition: 15
*drawnButton5.leftPosition: 67
*drawnButton5.rightPosition: 81

*drawnButton10.class: drawnButton
*drawnButton10.static: true
*drawnButton10.name: drawnButton10
*drawnButton10.parent: form3
*drawnButton10.width: 60
*drawnButton10.height: 20
*drawnButton10.highlightOnEnter: "true"
*drawnButton10.pushButtonEnabled: "false"
*drawnButton10.highlightThickness: 2
*drawnButton10.shadowType: "shadow_etched_in"
*drawnButton10.shadowThickness: 2
*drawnButton10.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 10)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[9], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 10;\
	RilasciaDrawnButton (9);\
\
	get_something (VettoreBottoni[9], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton10.recomputeSize: "false"
*drawnButton10.bottomAttachment: "attach_position"
*drawnButton10.bottomOffset: 0
*drawnButton10.bottomWidget: ""
*drawnButton10.rightAttachment: "attach_position"
*drawnButton10.rightOffset: 0
*drawnButton10.rightWidget: "drawnButton11"
*drawnButton10.leftAttachment: "attach_position"
*drawnButton10.leftOffset: 0
*drawnButton10.resizable: "false"
*drawnButton10.topAttachment: "attach_position"
*drawnButton10.topOffset: 0
*drawnButton10.bottomPosition: 28
*drawnButton10.topPosition: 22
*drawnButton10.leftPosition: 51
*drawnButton10.rightPosition: 65

*drawnButton9.class: drawnButton
*drawnButton9.static: true
*drawnButton9.name: drawnButton9
*drawnButton9.parent: form3
*drawnButton9.width: 60
*drawnButton9.height: 20
*drawnButton9.highlightOnEnter: "true"
*drawnButton9.pushButtonEnabled: "false"
*drawnButton9.highlightThickness: 2
*drawnButton9.shadowType: "shadow_etched_in"
*drawnButton9.shadowThickness: 2
*drawnButton9.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 9)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[8], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 9;\
	RilasciaDrawnButton (8);\
	get_something (VettoreBottoni[8], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton9.recomputeSize: "false"
*drawnButton9.bottomAttachment: "attach_position"
*drawnButton9.bottomOffset: 0
*drawnButton9.bottomWidget: ""
*drawnButton9.rightAttachment: "attach_position"
*drawnButton9.rightOffset: 0
*drawnButton9.rightWidget: "drawnButton10"
*drawnButton9.resizable: "false"
*drawnButton9.leftAttachment: "attach_position"
*drawnButton9.topAttachment: "attach_position"
*drawnButton9.topOffset: 0
*drawnButton9.leftOffset: 0
*drawnButton9.bottomPosition: 28
*drawnButton9.topPosition: 22
*drawnButton9.leftPosition: 35
*drawnButton9.rightPosition: 49

*drawnButton8.class: drawnButton
*drawnButton8.static: true
*drawnButton8.name: drawnButton8
*drawnButton8.parent: form3
*drawnButton8.width: 60
*drawnButton8.height: 20
*drawnButton8.highlightOnEnter: "true"
*drawnButton8.pushButtonEnabled: "false"
*drawnButton8.highlightThickness: 2
*drawnButton8.shadowType: "shadow_etched_in"
*drawnButton8.shadowThickness: 2
*drawnButton8.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 8)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[7], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 8;\
	RilasciaDrawnButton (7);\
	get_something (VettoreBottoni[7], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton8.recomputeSize: "false"
*drawnButton8.bottomAttachment: "attach_position"
*drawnButton8.bottomOffset: 0
*drawnButton8.bottomWidget: ""
*drawnButton8.rightAttachment: "attach_position"
*drawnButton8.rightOffset: 0
*drawnButton8.rightWidget: "drawnButton9"
*drawnButton8.resizable: "false"
*drawnButton8.leftAttachment: "attach_position"
*drawnButton8.topAttachment: "attach_position"
*drawnButton8.topOffset: 0
*drawnButton8.leftOffset: 0
*drawnButton8.bottomPosition: 28
*drawnButton8.topPosition: 22
*drawnButton8.leftPosition: 19
*drawnButton8.rightPosition: 33

*drawnButton7.class: drawnButton
*drawnButton7.static: true
*drawnButton7.name: drawnButton7
*drawnButton7.parent: form3
*drawnButton7.width: 60
*drawnButton7.height: 20
*drawnButton7.highlightOnEnter: "true"
*drawnButton7.pushButtonEnabled: "false"
*drawnButton7.highlightThickness: 2
*drawnButton7.shadowType: "shadow_etched_in"
*drawnButton7.shadowThickness: 2
*drawnButton7.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 7)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[6], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 7;\
	RilasciaDrawnButton (6);\
	get_something (VettoreBottoni[6], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton7.recomputeSize: "false"
*drawnButton7.bottomAttachment: "attach_position"
*drawnButton7.bottomOffset: 0
*drawnButton7.bottomWidget: ""
*drawnButton7.rightAttachment: "attach_position"
*drawnButton7.rightOffset: 0
*drawnButton7.rightWidget: "drawnButton8"
*drawnButton7.resizable: "false"
*drawnButton7.leftAttachment: "attach_position"
*drawnButton7.topAttachment: "attach_position"
*drawnButton7.topOffset: 0
*drawnButton7.leftOffset: 0
*drawnButton7.bottomPosition: 28
*drawnButton7.topPosition: 22
*drawnButton7.leftPosition: 3
*drawnButton7.rightPosition: 17

*drawnButton4.class: drawnButton
*drawnButton4.static: true
*drawnButton4.name: drawnButton4
*drawnButton4.parent: form3
*drawnButton4.width: 60
*drawnButton4.height: 20
*drawnButton4.highlightOnEnter: "true"
*drawnButton4.pushButtonEnabled: "false"
*drawnButton4.highlightThickness: 2
*drawnButton4.shadowType: "shadow_etched_in"
*drawnButton4.shadowThickness: 2
*drawnButton4.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 4)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[3], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 4;\
	RilasciaDrawnButton (3);\
	get_something (VettoreBottoni[3], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton4.recomputeSize: "false"
*drawnButton4.topAttachment: "attach_position"
*drawnButton4.topOffset: 0
*drawnButton4.rightAttachment: "attach_position"
*drawnButton4.rightOffset: 0
*drawnButton4.rightWidget: "drawnButton5"
*drawnButton4.bottomAttachment: "attach_position"
*drawnButton4.bottomOffset: 0
*drawnButton4.bottomWidget: "drawnButton10"
*drawnButton4.resizable: "false"
*drawnButton4.leftAttachment: "attach_position"
*drawnButton4.leftOffset: 0
*drawnButton4.bottomPosition: 21
*drawnButton4.topPosition: 15
*drawnButton4.leftPosition: 51
*drawnButton4.rightPosition: 65

*drawnButton3.class: drawnButton
*drawnButton3.static: true
*drawnButton3.name: drawnButton3
*drawnButton3.parent: form3
*drawnButton3.width: 60
*drawnButton3.height: 20
*drawnButton3.highlightOnEnter: "true"
*drawnButton3.pushButtonEnabled: "false"
*drawnButton3.highlightThickness: 2
*drawnButton3.shadowType: "shadow_etched_in"
*drawnButton3.shadowThickness: 2
*drawnButton3.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 3)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[2], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 3;\
	RilasciaDrawnButton (2);\
\
	get_something (VettoreBottoni[2], XmNbackground, &ColoreSfondo.pixel);\
 \
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton3.recomputeSize: "false"
*drawnButton3.topAttachment: "attach_position"
*drawnButton3.topOffset: 0
*drawnButton3.rightAttachment: "attach_position"
*drawnButton3.rightOffset: 0
*drawnButton3.rightWidget: "drawnButton4"
*drawnButton3.bottomAttachment: "attach_position"
*drawnButton3.bottomOffset: 0
*drawnButton3.bottomWidget: "drawnButton9"
*drawnButton3.resizable: "false"
*drawnButton3.leftAttachment: "attach_position"
*drawnButton3.leftOffset: 0
*drawnButton3.bottomPosition: 21
*drawnButton3.topPosition: 15
*drawnButton3.leftPosition: 35
*drawnButton3.rightPosition: 49

*drawnButton2.class: drawnButton
*drawnButton2.static: true
*drawnButton2.name: drawnButton2
*drawnButton2.parent: form3
*drawnButton2.width: 60
*drawnButton2.height: 20
*drawnButton2.highlightOnEnter: "true"
*drawnButton2.pushButtonEnabled: "false"
*drawnButton2.highlightThickness: 2
*drawnButton2.shadowType: "shadow_etched_in"
*drawnButton2.shadowThickness: 2
*drawnButton2.activateCallback: {\
XColor ColoreSfondo;\
char vstring[40];\
Pixel Pal;\
\
if (Press == 2)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[1], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 2;\
	RilasciaDrawnButton (1);\
	get_something (VettoreBottoni[1], XmNbackground, &ColoreSfondo.pixel);\
\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton2.recomputeSize: "false"
*drawnButton2.bottomAttachment: "attach_position"
*drawnButton2.bottomOffset: 0
*drawnButton2.bottomWidget: "drawnButton8"
*drawnButton2.leftAttachment: "attach_position"
*drawnButton2.leftOffset: 0
*drawnButton2.rightAttachment: "attach_position"
*drawnButton2.rightOffset: 0
*drawnButton2.rightWidget: "drawnButton3"
*drawnButton2.topAttachment: "attach_position"
*drawnButton2.topOffset: 0
*drawnButton2.resizable: "false"
*drawnButton2.bottomPosition: 21
*drawnButton2.topPosition: 15
*drawnButton2.leftPosition: 19
*drawnButton2.rightPosition: 33

*drawnButton1.class: drawnButton
*drawnButton1.static: true
*drawnButton1.name: drawnButton1
*drawnButton1.parent: form3
*drawnButton1.width: 60
*drawnButton1.height: 20
*drawnButton1.highlightOnEnter: "true"
*drawnButton1.pushButtonEnabled: "false"
*drawnButton1.highlightThickness: 2
*drawnButton1.shadowType: "shadow_etched_in"
*drawnButton1.shadowThickness: 2
*drawnButton1.activateCallback: {\
XColor ColoreSfondo;\
Pixel Pal;\
char vstring[40];\
\
if (Press == 1)\
	{\
	get_something (ButtNomeColore, XmNbackground, &Pal);\
	set_something (VettoreBottoni[0], XmNbackground, Pal);\
	}\
else\
	{\
	Press = 1;\
	RilasciaDrawnButton (0);\
\
	get_something (VettoreBottoni[0], XmNbackground, &ColoreSfondo.pixel);\
	set_something (ButtNomeColore, XmNbackground, ColoreSfondo.pixel);\
	XQueryColor (UxDisplay, Cmap, &ColoreSfondo);\
	sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,\
				ColoreSfondo.blue);\
	set_something (TextNomeColore, XmNvalue, vstring);\
	}\
}
*drawnButton1.recomputeSize: "false"
*drawnButton1.rightAttachment: "attach_position"
*drawnButton1.rightOffset: 0
*drawnButton1.rightWidget: "drawnButton2"
*drawnButton1.leftAttachment: "attach_position"
*drawnButton1.leftOffset: 0
*drawnButton1.bottomAttachment: "attach_position"
*drawnButton1.bottomOffset: 0
*drawnButton1.bottomWidget: "drawnButton7"
*drawnButton1.topAttachment: "attach_position"
*drawnButton1.topOffset: 0
*drawnButton1.resizable: "false"
*drawnButton1.bottomPosition: 21
*drawnButton1.topPosition: 15
*drawnButton1.leftPosition: 3
*drawnButton1.rightPosition: 17

*BlinkRate.class: label
*BlinkRate.static: true
*BlinkRate.name: BlinkRate
*BlinkRate.parent: form3
*BlinkRate.x: 15
*BlinkRate.y: 240
*BlinkRate.width: 140
*BlinkRate.height: 30
*BlinkRate.labelString: "Blink freq. (Hz):"
*BlinkRate.alignment: "alignment_end"
*BlinkRate.bottomAttachment: "attach_position"
*BlinkRate.bottomPosition: 80
*BlinkRate.topAttachment: "attach_position"
*BlinkRate.topOffset: 0
*BlinkRate.topPosition: 71
*BlinkRate.labelInsensitivePixmap: "/usr/include/X11/bitmaps/dimple1"

*blink_frequency.class: textField
*blink_frequency.static: true
*blink_frequency.name: blink_frequency
*blink_frequency.parent: form3
*blink_frequency.x: 170
*blink_frequency.y: 239
*blink_frequency.width: 70
*blink_frequency.height: 32
*blink_frequency.maxLength: 50
*blink_frequency.bottomAttachment: "attach_position"
*blink_frequency.bottomPosition: 80
*blink_frequency.topAttachment: "attach_position"
*blink_frequency.topPosition: 71
*blink_frequency.leftAttachment: "attach_widget"
*blink_frequency.leftOffset: 10
*blink_frequency.leftWidget: "BlinkRate"
*blink_frequency.rightAttachment: "attach_form"
*blink_frequency.rightOffset: 15

*transparentLabel.class: label
*transparentLabel.static: true
*transparentLabel.name: transparentLabel
*transparentLabel.parent: form3
*transparentLabel.x: 20
*transparentLabel.y: 232
*transparentLabel.width: 130
*transparentLabel.height: 30
*transparentLabel.labelString: "Transparent:"
*transparentLabel.alignment: "alignment_end"
*transparentLabel.labelInsensitivePixmap: "/usr/include/X11/bitmaps/dimple1"
*transparentLabel.bottomAttachment: "attach_position"
*transparentLabel.bottomPosition: 71
*transparentLabel.leftOffset: 15
*transparentLabel.topOffset: 0
*transparentLabel.topAttachment: "attach_position"
*transparentLabel.topPosition: 63

*trasparentMenu.class: rowColumn
*trasparentMenu.static: true
*trasparentMenu.name: trasparentMenu
*trasparentMenu.parent: form3
*trasparentMenu.rowColumnType: "menu_option"
*trasparentMenu.subMenuId: "transparentPane"
*trasparentMenu.x: 170
*trasparentMenu.y: 230
*trasparentMenu.bottomAttachment: "attach_position"
*trasparentMenu.bottomPosition: 71
*trasparentMenu.topAttachment: "attach_position"
*trasparentMenu.topOffset: 0
*trasparentMenu.topPosition: 63
*trasparentMenu.rightAttachment: "attach_form"
*trasparentMenu.rightOffset: 180
*trasparentMenu.marginHeight: 0

*transparentPane.class: rowColumn
*transparentPane.static: true
*transparentPane.name: transparentPane
*transparentPane.parent: trasparentMenu
*transparentPane.rowColumnType: "menu_pulldown"

*transparentNo.class: pushButton
*transparentNo.static: true
*transparentNo.name: transparentNo
*transparentNo.parent: transparentPane
*transparentNo.labelString: "No"
*transparentNo.activateCallback: {\
transparent = False;\
}

*transparentYes.class: pushButton
*transparentYes.static: true
*transparentYes.name: transparentYes
*transparentYes.parent: transparentPane
*transparentYes.labelString: "Yes"
*transparentYes.activateCallback: {\
transparent = True;\
}

*menu3.class: rowColumn
*menu3.static: true
*menu3.name: menu3
*menu3.parent: mainWindow2
*menu3.rowColumnType: "menu_bar"
*menu3.menuAccelerator: "<KeyUp>F10"

*EditColorPane.class: rowColumn
*EditColorPane.static: true
*EditColorPane.name: EditColorPane
*EditColorPane.parent: menu3
*EditColorPane.rowColumnType: "menu_pulldown"

*EditItem.class: pushButton
*EditItem.static: true
*EditItem.name: EditItem
*EditItem.parent: EditColorPane
*EditItem.labelString: "Edit Color"
*EditItem.mnemonic: "E"
*EditItem.activateCallback: {\
Pixel Colore;\
Widget Creato;\
\
get_something (ButtNomeColore, XmNbackground, &Colore);\
\
Creato = (Widget )create_ColorEditor(&Colore,TextNomeColore,ColorViewer);\
UxPopupInterface (Creato , no_grab);\
}

*GrabItem.class: pushButton
*GrabItem.static: true
*GrabItem.name: GrabItem
*GrabItem.parent: EditColorPane
*GrabItem.labelString: "Grab Color"
*GrabItem.mnemonic: "G"
*GrabItem.activateCallback: {\
Colormap cmap;\
XImage *Immagine;\
XEvent report;\
int cicla;\
XColor Pix;\
char Str[15];\
\
cicla = 1;\
cmap = DefaultColormap (UxDisplay, DefaultScreen (UxDisplay) );\
\
/*  Ciclo di attivazione della lettura della pressione del bottone del mouse */\
while ( cicla )\
	{\
	XNextEvent (UxDisplay, &report);\
	switch (report.type)\
		{\
		case Expose:\
			XtDispatchEvent (&report);\
		break;\
		case ButtonPress:\
			/*  Crea l'immagine del punto dove e stato premuto \
				il bottone del mouse  */\
			Immagine = XGetImage (UxDisplay, report.xbutton.window,\
				report.xbutton.x,report.xbutton.y,1,1,\
				AllPlanes,XYPixmap);\
			/*  Se e' stata caricata l'immagine prende il pixel \
				del punto dove e' avvenuta la pressione\
				del bottone del mouse   */\
			if (Immagine == NULL)\
				printf ("Image non caricata!!\n");\
			else\
				{\
				Pix.pixel = XGetPixel (Immagine,0,0);\
				/*  Setta il pixel come sfondo del bottone */\
				set_something (ButtNomeColore,XmNbackground,Pix.pixel);\
				/*  Trova le informazioni RGB relative al pixel */\
				XQueryColor (UxDisplay, cmap, &Pix);\
				/*  Crea la stringa con il nome del colore  */\
				sprintf (Str,"#%04x%04x%04x",Pix.red,Pix.green,\
					Pix.blue);\
				XmTextFieldSetString (TextNomeColore,Str);\
				cicla = 0;\
				}\
		break;\
		}\
	}\
}

*ColorItem.class: pushButton
*ColorItem.static: true
*ColorItem.name: ColorItem
*ColorItem.parent: EditColorPane
*ColorItem.labelString: "Color Map"
*ColorItem.mnemonic: "C"
*ColorItem.activateCallback: {\
Widget Creato;\
\
Creato = (Widget)create_ColorMapViewer(ColorViewer);\
UxPopupInterface (Creato ,no_grab);\
}

*menu3_top_b1.class: cascadeButton
*menu3_top_b1.static: true
*menu3_top_b1.name: menu3_top_b1
*menu3_top_b1.parent: menu3
*menu3_top_b1.labelString: "Edit"
*menu3_top_b1.mnemonic: "E"
*menu3_top_b1.subMenuId: "EditColorPane"

