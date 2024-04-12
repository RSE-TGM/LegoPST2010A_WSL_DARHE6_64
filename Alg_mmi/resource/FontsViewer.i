! UIMX ascii 2.5 key: 8986                                                      

*FontsViewer.class: topLevelShell
*FontsViewer.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo FontsViewer.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)FontsViewer.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
#include "res_edit.h"\
\
extern swidget create_FontsEditor();\
extern char *WidGetName();\
\
char *CaricaFont ( );\

*FontsViewer.ispecdecl: XrmDatabase RisDbFonts; /*  Puntatore al database dei fonts di \
				default  */\
char VettoreFont[5][200]; /* Vettore contenente le\
				stringhe dei font di default */\
Widget *ListaRC;\

*FontsViewer.ispeclist: RisDbFonts, VettoreFont, ListaRC
*FontsViewer.ispeclist.RisDbFonts: "XrmDatabase", "%RisDbFonts%"
*FontsViewer.ispeclist.VettoreFont: "unsigned char", "%VettoreFont%[5][200]"
*FontsViewer.ispeclist.ListaRC: "Widget", "*%ListaRC%"
*FontsViewer.funcdecl: swidget create_FontsViewer(char *strfont,Widget *ListaINP,Widget ChiamFon)\

*FontsViewer.funcname: create_FontsViewer
*FontsViewer.funcdef: "swidget", "<create_FontsViewer>(%)"
*FontsViewer.argdecl: unsigned char *strfont;\
Widget *ListaINP;\
Widget ChiamFon;
*FontsViewer.arglist: strfont, ListaINP, ChiamFon
*FontsViewer.arglist.strfont: "unsigned char", "*%strfont%"
*FontsViewer.arglist.ListaINP: "Widget", "*%ListaINP%"
*FontsViewer.arglist.ChiamFon: "Widget", "%ChiamFon%"
*FontsViewer.icode: char *StrFont,*Appoggio;\
XFontStruct *FontInfo;\
XmFontList FontList;\
XrmDatabase DbAppo;\
\
DbAppo = XrmGetDatabase (UxDisplay);\
ListaRC = ListaINP;\
RisDbFonts = XrmGetFileDatabase ("FileFontsDefault");\
XrmSetDatabase (UxDisplay,RisDbFonts);\
\
StrFont = (char *)strfont;\

*FontsViewer.fcode: /*  Legge dal database i nomi dei font di default */\
Appoggio = CaricaFont (FontSample1);\
if ( Appoggio[0] == '\0')\
	strcpy (VettoreFont[0],"fixed");\
else strcpy (VettoreFont [0],Appoggio);\
XtFree (Appoggio);\
\
Appoggio = CaricaFont (FontSample2);\
if ( Appoggio[0] == '\0')\
	strcpy (VettoreFont[1],"fixed");\
else strcpy (VettoreFont [1],Appoggio);\
XtFree (Appoggio);\
\
Appoggio = CaricaFont (FontSample3);\
if ( Appoggio[0] == '\0')\
	strcpy (VettoreFont[2],"fixed");\
else strcpy (VettoreFont [2],Appoggio);\
XtFree (Appoggio);\
\
Appoggio = CaricaFont (FontSample4);\
if ( Appoggio[0] == '\0')\
	strcpy (VettoreFont[3],"fixed");\
else strcpy (VettoreFont [3],Appoggio);\
XtFree (Appoggio);\
\
Appoggio = CaricaFont (FontSample5);\
if ( Appoggio[0] == '\0')\
	strcpy (VettoreFont[4],"fixed");\
else strcpy (VettoreFont [4],Appoggio);\
XtFree (Appoggio);\
\
XrmSetDatabase (UxDisplay,DbAppo);\
\
if ( (FontInfo = XLoadQueryFont (UxDisplay,StrFont) ) == NULL)\
	XmTextFieldSetString (TextNomeFont, "Unable to open font!");\
else\
	{\
	XmTextFieldSetString (TextNomeFont, StrFont);\
	FontList = XmFontListCreate (FontInfo, XmSTRING_DEFAULT_CHARSET);\
	set_something (LabelFont , XmNfontList, FontList);\
	}\
\
/*  Setta la posizione dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (FontsViewer,ChiamFon);\
\
return(rtrn);
*FontsViewer.auxdecl: char *CaricaFont (swidget sw)\
{\
XrmValue xrm_value;\
char *str_type;\
char str_sorg[100];\
char *buffer;\
\
buffer = XtCalloc (200, sizeof(char));\
\
strcpy (str_sorg,WidGetName(sw));\
strcat (str_sorg,".nomeFont");\
\
if ( XrmGetResource(RisDbFonts,str_sorg,"CNomeFont",&str_type,&xrm_value) )\
	strncpy (buffer, xrm_value.addr, (int)xrm_value.size);\
return (buffer);\
}
*FontsViewer.static: true
*FontsViewer.name: FontsViewer
*FontsViewer.parent: NO_PARENT
*FontsViewer.parentExpression: ChiamFon
*FontsViewer.x: -7
*FontsViewer.y: -8
*FontsViewer.width: 380
*FontsViewer.height: 500
*FontsViewer.iconName: "Font Viewer"
*FontsViewer.title: "Resource Font Viewer"
*FontsViewer.allowShellResize: "true"

*mainWindow5.class: mainWindow
*mainWindow5.static: true
*mainWindow5.name: mainWindow5
*mainWindow5.parent: FontsViewer
*mainWindow5.unitType: "pixels"
*mainWindow5.x: 25
*mainWindow5.y: 10
*mainWindow5.width: 380
*mainWindow5.height: 500

*menu5.class: rowColumn
*menu5.static: true
*menu5.name: menu5
*menu5.parent: mainWindow5
*menu5.rowColumnType: "menu_bar"
*menu5.menuAccelerator: "<KeyUp>F10"

*EditFontPane.class: rowColumn
*EditFontPane.static: true
*EditFontPane.name: EditFontPane
*EditFontPane.parent: menu5
*EditFontPane.rowColumnType: "menu_pulldown"

*EditFontItem.class: pushButton
*EditFontItem.static: true
*EditFontItem.name: EditFontItem
*EditFontItem.parent: EditFontPane
*EditFontItem.labelString: "Edit Font"
*EditFontItem.mnemonic: "F"
*EditFontItem.activateCallback: UxPopupInterface (create_FontsEditor(TextNomeFont,FontsViewer),no_grab);\


*menu5_top_b1.class: cascadeButton
*menu5_top_b1.static: true
*menu5_top_b1.name: menu5_top_b1
*menu5_top_b1.parent: menu5
*menu5_top_b1.labelString: "Edit"
*menu5_top_b1.mnemonic: "E"
*menu5_top_b1.subMenuId: "EditFontPane"

*form5.class: form
*form5.static: true
*form5.name: form5
*form5.parent: mainWindow5

*separator7.class: separator
*separator7.static: true
*separator7.name: separator7
*separator7.parent: form5
*separator7.x: 5
*separator7.y: 240
*separator7.width: 380
*separator7.height: 20
*separator7.leftAttachment: "attach_form"
*separator7.leftOffset: 5
*separator7.rightAttachment: "attach_form"
*separator7.rightOffset: 5
*separator7.topAttachment: "attach_none"
*separator7.topOffset: 0
*separator7.topWidget: ""

*FontSample5.class: toggleButton
*FontSample5.static: true
*FontSample5.name: FontSample5
*FontSample5.parent: form5
*FontSample5.x: 10
*FontSample5.y: 220
*FontSample5.width: 360
*FontSample5.height: 35
*FontSample5.indicatorType: "one_of_many"
*FontSample5.indicatorSize: 20
*FontSample5.alignment: "alignment_beginning"
*FontSample5.labelString: "This is an example of a Font"
*FontSample5.marginLeft: 40
*FontSample5.leftAttachment: "attach_form"
*FontSample5.leftOffset: 10
*FontSample5.rightAttachment: "attach_form"
*FontSample5.rightOffset: 10
*FontSample5.bottomAttachment: "attach_widget"
*FontSample5.bottomOffset: 5
*FontSample5.bottomWidget: "separator7"
*FontSample5.topAttachment: "attach_none"
*FontSample5.armCallback: {\
XmFontList Fontl;\
\
set_something (FontSample1, XmNset, False);\
set_something (FontSample2, XmNset, False);\
set_something (FontSample3, XmNset, False);\
set_something (FontSample4, XmNset, False);\
\
get_something (FontSample5, XmNfontList, &Fontl);\
set_something (LabelFont , XmNfontList, Fontl);\
\
XmTextFieldSetString (TextNomeFont, VettoreFont[4]);\
}
*FontSample5.recomputeSize: "false"

*FontSample4.class: toggleButton
*FontSample4.static: true
*FontSample4.name: FontSample4
*FontSample4.parent: form5
*FontSample4.x: 10
*FontSample4.y: 175
*FontSample4.width: 360
*FontSample4.height: 35
*FontSample4.indicatorType: "one_of_many"
*FontSample4.indicatorSize: 20
*FontSample4.alignment: "alignment_beginning"
*FontSample4.labelString: "This is an example of a Font"
*FontSample4.marginLeft: 40
*FontSample4.leftAttachment: "attach_form"
*FontSample4.leftOffset: 10
*FontSample4.rightAttachment: "attach_form"
*FontSample4.rightOffset: 10
*FontSample4.bottomAttachment: "attach_widget"
*FontSample4.bottomOffset: 5
*FontSample4.bottomWidget: "FontSample5"
*FontSample4.armCallback: {\
XmFontList Fontl;\
\
set_something (FontSample1, XmNset, False);\
set_something (FontSample2, XmNset, False);\
set_something (FontSample3, XmNset, False);\
set_something (FontSample5, XmNset, False);\
\
get_something (FontSample4, XmNfontList, &Fontl);\
set_something (LabelFont, XmNfontList, Fontl);\
\
XmTextFieldSetString (TextNomeFont, VettoreFont[3]);\
}
*FontSample4.recomputeSize: "false"

*FontSample3.class: toggleButton
*FontSample3.static: true
*FontSample3.name: FontSample3
*FontSample3.parent: form5
*FontSample3.x: 10
*FontSample3.y: 130
*FontSample3.width: 360
*FontSample3.height: 35
*FontSample3.indicatorType: "one_of_many"
*FontSample3.indicatorSize: 20
*FontSample3.alignment: "alignment_beginning"
*FontSample3.labelString: "This is an example of a Font"
*FontSample3.marginLeft: 40
*FontSample3.leftAttachment: "attach_form"
*FontSample3.leftOffset: 10
*FontSample3.rightAttachment: "attach_form"
*FontSample3.rightOffset: 10
*FontSample3.bottomAttachment: "attach_widget"
*FontSample3.bottomOffset: 5
*FontSample3.bottomWidget: "FontSample4"
*FontSample3.armCallback: {\
XmFontList Fontl;\
\
set_something (FontSample1, XmNset, False);\
set_something (FontSample2, XmNset, False);\
set_something (FontSample4, XmNset, False);\
set_something (FontSample5, XmNset, False);\
\
get_something (FontSample3, XmNfontList , &Fontl);\
set_something (LabelFont, XmNfontList, Fontl);\
\
XmTextFieldSetString (TextNomeFont , VettoreFont[2]);\
}
*FontSample3.recomputeSize: "false"

*FontSample2.class: toggleButton
*FontSample2.static: true
*FontSample2.name: FontSample2
*FontSample2.parent: form5
*FontSample2.x: 10
*FontSample2.y: 90
*FontSample2.width: 360
*FontSample2.height: 35
*FontSample2.indicatorType: "one_of_many"
*FontSample2.indicatorSize: 20
*FontSample2.alignment: "alignment_beginning"
*FontSample2.labelString: "This is an example of a Font"
*FontSample2.marginLeft: 40
*FontSample2.leftAttachment: "attach_form"
*FontSample2.leftOffset: 10
*FontSample2.rightAttachment: "attach_form"
*FontSample2.rightOffset: 10
*FontSample2.bottomAttachment: "attach_widget"
*FontSample2.bottomOffset: 5
*FontSample2.bottomWidget: "FontSample3"
*FontSample2.armCallback: {\
XmFontList Fontl;\
\
set_something (FontSample1, XmNset, False);\
set_something (FontSample3, XmNset, False);\
set_something (FontSample4, XmNset, False);\
set_something (FontSample5, XmNset, False);\
\
get_something (FontSample2, XmNfontList, &Fontl);\
set_something (LabelFont, XmNfontList, Fontl); \
\
XmTextFieldSetString (TextNomeFont , VettoreFont[1]);\
}
*FontSample2.recomputeSize: "false"

*FontSample1.class: toggleButton
*FontSample1.static: true
*FontSample1.name: FontSample1
*FontSample1.parent: form5
*FontSample1.x: 10
*FontSample1.y: 40
*FontSample1.width: 360
*FontSample1.height: 35
*FontSample1.leftAttachment: "attach_form"
*FontSample1.leftOffset: 10
*FontSample1.rightAttachment: "attach_form"
*FontSample1.rightOffset: 10
*FontSample1.topAttachment: "attach_none"
*FontSample1.topOffset: 5
*FontSample1.topWidget: ""
*FontSample1.indicatorType: "one_of_many"
*FontSample1.indicatorSize: 20
*FontSample1.alignment: "alignment_beginning"
*FontSample1.labelString: "This is an example of a Font"
*FontSample1.marginLeft: 40
*FontSample1.bottomAttachment: "attach_widget"
*FontSample1.bottomOffset: 5
*FontSample1.bottomWidget: "FontSample2"
*FontSample1.armCallback: {\
XmFontList Fontl;\
\
set_something (FontSample2, XmNset, False);\
set_something (FontSample3, XmNset, False);\
set_something (FontSample4, XmNset, False);\
set_something (FontSample5, XmNset, False);\
\
get_something (FontSample1, XmNfontList , &Fontl);\
set_something (LabelFont, XmNfontList, Fontl);\
\
XmTextFieldSetString (TextNomeFont, VettoreFont[0]);\
}
*FontSample1.recomputeSize: "false"

*label9.class: label
*label9.static: true
*label9.name: label9
*label9.parent: form5
*label9.x: 5
*label9.y: 10
*label9.width: 110
*label9.height: 30
*label9.labelString: "Defaults:"
*label9.bottomAttachment: "attach_widget"
*label9.bottomOffset: 5
*label9.bottomWidget: "FontSample1"
*label9.topAttachment: "attach_form"
*label9.topOffset: 5

*label10.class: label
*label10.static: true
*label10.name: label10
*label10.parent: form5
*label10.x: 10
*label10.y: 260
*label10.width: 110
*label10.height: 30
*label10.labelString: "Selected Font:"
*label10.topAttachment: "attach_widget"
*label10.topOffset: 5
*label10.topWidget: "separator7"

*LabelFont.class: label
*LabelFont.static: true
*LabelFont.name: LabelFont
*LabelFont.parent: form5
*LabelFont.x: 10
*LabelFont.y: 300
*LabelFont.width: 360
*LabelFont.height: 40
*LabelFont.labelString: "This is an example of a selected Font"
*LabelFont.leftAttachment: "attach_form"
*LabelFont.leftOffset: 10
*LabelFont.rightAttachment: "attach_form"
*LabelFont.rightOffset: 10
*LabelFont.topAttachment: "attach_widget"
*LabelFont.topOffset: 5
*LabelFont.topWidget: "label10"

*label12.class: label
*label12.static: true
*label12.name: label12
*label12.parent: form5
*label12.x: 10
*label12.y: 345
*label12.width: 80
*label12.height: 40
*label12.labelString: "FontName:"
*label12.topAttachment: "attach_widget"
*label12.topOffset: 5
*label12.topWidget: "LabelFont"

*separator8.class: separator
*separator8.static: true
*separator8.name: separator8
*separator8.parent: form5
*separator8.x: 0
*separator8.y: 390
*separator8.width: 380
*separator8.height: 20
*separator8.leftAttachment: "attach_form"
*separator8.leftOffset: 5
*separator8.rightAttachment: "attach_form"
*separator8.rightOffset: 5

*pushButton10.class: pushButton
*pushButton10.static: true
*pushButton10.name: pushButton10
*pushButton10.parent: form5
*pushButton10.x: 260
*pushButton10.y: 420
*pushButton10.width: 85
*pushButton10.height: 35
*pushButton10.labelString: "CANCEL"
*pushButton10.activateCallback: {\
/*  Ritorna a sensitive il pushbutton e il textfield chiamante */\
set_something (ListaRC[0], XmNsensitive, True);\
set_something (ListaRC[2], XmNsensitive, True);\
\
XtDestroyWidget (FontsViewer);\
}
*pushButton10.leftAttachment: "attach_position"
*pushButton10.leftOffset: 0
*pushButton10.topAttachment: "attach_widget"
*pushButton10.topOffset: 5
*pushButton10.topWidget: "separator8"
*pushButton10.bottomAttachment: "attach_form"
*pushButton10.bottomOffset: 15
*pushButton10.leftPosition: 65
*pushButton10.rightAttachment: "attach_position"
*pushButton10.rightPosition: 90

*pushButton9.class: pushButton
*pushButton9.static: true
*pushButton9.name: pushButton9
*pushButton9.parent: form5
*pushButton9.x: 130
*pushButton9.y: 420
*pushButton9.width: 85
*pushButton9.height: 35
*pushButton9.labelString: "APPLY"
*pushButton9.leftAttachment: "attach_position"
*pushButton9.leftOffset: 0
*pushButton9.rightAttachment: "attach_position"
*pushButton9.rightOffset: 0
*pushButton9.rightWidget: ""
*pushButton9.topAttachment: "attach_widget"
*pushButton9.topOffset: 5
*pushButton9.topWidget: "separator8"
*pushButton9.bottomAttachment: "attach_form"
*pushButton9.bottomOffset: 15
*pushButton9.leftPosition: 35
*pushButton9.rightPosition: 60
*pushButton9.activateCallback: {\
XFontStruct *FontInfo;\
XmFontList FontList;\
char *StrFont;\
int SettaFont;\
Boolean Value;\
\
StrFont = (char *)XmTextFieldGetString (TextNomeFont);\
SettaFont = 0;\
if ( XmToggleButtonGetState(FontSample1) ) SettaFont = 1;\
if ( XmToggleButtonGetState(FontSample2) ) SettaFont = 2;\
if ( XmToggleButtonGetState(FontSample3) ) SettaFont = 3;\
if ( XmToggleButtonGetState(FontSample4) ) SettaFont = 4;\
if ( XmToggleButtonGetState(FontSample5) ) SettaFont = 5;\
\
if ( (FontInfo = XLoadQueryFont (UxDisplay,StrFont) ) == NULL)\
	XmTextFieldSetString (TextNomeFont, "Unable to open font!");\
else\
	{\
	FontList = XmFontListCreate (FontInfo, XmSTRING_DEFAULT_CHARSET);\
	set_something (LabelFont , XmNfontList, FontList);\
	XmTextFieldSetString (ListaRC[2], StrFont);\
	switch (SettaFont)\
	{\
	case 1:\
		set_something (FontSample1,XmNfontList,FontList);\
		strcpy (VettoreFont[0],StrFont);\
	break;\
	case 2:\
		set_something (FontSample2,XmNfontList,FontList);\
		strcpy (VettoreFont[1],StrFont);\
	break;\
	case 3:\
		set_something (FontSample3,XmNfontList,FontList);\
		strcpy (VettoreFont[2],StrFont);\
	break;\
	case 4:\
		set_something (FontSample4,XmNfontList,FontList);\
		strcpy (VettoreFont[3],StrFont);\
	break;\
	case 5:\
		set_something (FontSample5,XmNfontList,FontList);\
		strcpy (VettoreFont[4],StrFont);\
	break;\
	}\
	}\
XtFree (StrFont);\
}

*pushButton11.class: pushButton
*pushButton11.static: true
*pushButton11.name: pushButton11
*pushButton11.parent: form5
*pushButton11.x: 17
*pushButton11.y: 416
*pushButton11.width: 85
*pushButton11.height: 35
*pushButton11.labelString: "OK"
*pushButton11.activateCallback: {\
XmFontList FontL;\
char *Stringa;\
\
Stringa = (char *)XmTextFieldGetString (TextNomeFont);\
XmTextFieldSetString (ListaRC[2], Stringa);\
\
/*  Ritorna a sensitive il pushButton e il textfield chiamante */\
set_something (ListaRC[0], XmNsensitive, True);\
set_something (ListaRC[2], XmNsensitive, True);\
\
XlSetResourceByWidget (&RisDbFonts,FontSample1,XmNfontList,VettoreFont[0]);\
XlSetResourceByWidget (&RisDbFonts,FontSample2,XmNfontList,VettoreFont[1]);\
XlSetResourceByWidget (&RisDbFonts,FontSample3,XmNfontList,VettoreFont[2]);\
XlSetResourceByWidget (&RisDbFonts,FontSample4,XmNfontList,VettoreFont[3]);\
XlSetResourceByWidget (&RisDbFonts,FontSample5,XmNfontList,VettoreFont[4]);\
\
XlSetResourceByWidget (&RisDbFonts,FontSample1,"nomeFont",VettoreFont[0]);\
XlSetResourceByWidget (&RisDbFonts,FontSample2,"nomeFont",VettoreFont[1]);\
XlSetResourceByWidget (&RisDbFonts,FontSample3,"nomeFont",VettoreFont[2]);\
XlSetResourceByWidget (&RisDbFonts,FontSample4,"nomeFont",VettoreFont[3]);\
XlSetResourceByWidget (&RisDbFonts,FontSample5,"nomeFont",VettoreFont[4]);\
\
XrmPutFileDatabase (RisDbFonts,"FileFontsDefault");\
XtFree (Stringa);\
XtDestroyWidget (FontsViewer);\
}
*pushButton11.leftAttachment: "attach_position"
*pushButton11.leftOffset: 0
*pushButton11.rightAttachment: "attach_position"
*pushButton11.rightOffset: 0
*pushButton11.rightWidget: ""
*pushButton11.topAttachment: "attach_widget"
*pushButton11.topOffset: 5
*pushButton11.topWidget: "separator8"
*pushButton11.bottomAttachment: "attach_form"
*pushButton11.bottomOffset: 15
*pushButton11.leftPosition: 5
*pushButton11.rightPosition: 30

*TextNomeFont.class: textField
*TextNomeFont.static: true
*TextNomeFont.name: TextNomeFont
*TextNomeFont.parent: form5
*TextNomeFont.x: 100
*TextNomeFont.y: 350
*TextNomeFont.width: 270
*TextNomeFont.height: 40
*TextNomeFont.leftAttachment: "attach_widget"
*TextNomeFont.leftOffset: 5
*TextNomeFont.leftWidget: "label12"
*TextNomeFont.rightAttachment: "attach_form"
*TextNomeFont.rightOffset: 10
*TextNomeFont.topAttachment: "attach_widget"
*TextNomeFont.topOffset: 5
*TextNomeFont.topWidget: "LabelFont"

