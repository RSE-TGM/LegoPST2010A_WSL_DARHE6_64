! UIMX ascii 2.0 key: 1609                                                      

*window_models.class: transientShell
*window_models.parent: NO_PARENT
*window_models.static: true
*window_models.gbldecl: /*\
   modulo window_models.i\
   tipo \
   release 1.12\
   data 3/31/95\
   reserved @(#)window_models.i	1.12\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <unistd.h>\
\
#include "autodoc.h"\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE						*/\
/************************************************************************/\
\
extern StructVarianti varianti_modello[];\
extern byte num_varianti, num_file_f14;\
\
extern Boolean open_window_models;\

*window_models.ispecdecl:
*window_models.funcdecl: swidget create_window_models()
*window_models.funcname: create_window_models
*window_models.funcdef: "swidget", "<create_window_models>(%)"
*window_models.icode: open_window_models = True;\

*window_models.fcode: switch (num_varianti)\
{\
    case 5:\
       XmToggleButtonSetState(UxGetWidget(toggleButton5), \
			      varianti_modello[4].abilitato, False);\
       XmTextFieldSetString(UxGetWidget(text_title5),\
                            varianti_modello[4].titolo);\
       XmTextFieldSetString(UxGetWidget(text_path5),\
                            varianti_modello[4].percorso);\
    case 4:\
       XmToggleButtonSetState(UxGetWidget(toggleButton4), \
			      varianti_modello[3].abilitato, False); \
       XmTextFieldSetString(UxGetWidget(text_title4),\
                            varianti_modello[3].titolo);\
       XmTextFieldSetString(UxGetWidget(text_path4),\
                            varianti_modello[3].percorso);\
\
    case 3:\
       XmToggleButtonSetState(UxGetWidget(toggleButton3), \
			      varianti_modello[2].abilitato, False); \
       XmTextFieldSetString(UxGetWidget(text_title3),\
                            varianti_modello[2].titolo);\
       XmTextFieldSetString(UxGetWidget(text_path3),\
                            varianti_modello[2].percorso);\
    case 2:\
       XmToggleButtonSetState(UxGetWidget(toggleButton2), \
			      varianti_modello[1].abilitato, False); \
       XmTextFieldSetString(UxGetWidget(text_title2),\
                            varianti_modello[1].titolo);\
       XmTextFieldSetString(UxGetWidget(text_path2),\
                            varianti_modello[1].percorso);\
    case 1:\
       XmToggleButtonSetState(UxGetWidget(toggleButton1), \
			      varianti_modello[0].abilitato, False); \
       XmTextFieldSetString(UxGetWidget(text_title1),\
                            varianti_modello[0].titolo);\
       XmTextFieldSetString(UxGetWidget(text_path1),\
                            varianti_modello[0].percorso);\
}\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*window_models.auxdecl: /*** salva_steady_version()\
 ***\
 ***   Descrizione: \
 ***      Salva i settaggi relativi alle versioni dello stazionario.\
 ***/\
salva_steady_version()\
{\
   char *str;\
\
   num_file_f14 = 0;\
\
   varianti_modello[0].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton1));\
   varianti_modello[1].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton2));\
   varianti_modello[2].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton3));\
   varianti_modello[3].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton4));\
   varianti_modello[4].abilitato = XmToggleButtonGetState(UxGetWidget(toggleButton5));\
\
   str = XmTextFieldGetString(UxGetWidget(text_path1));\
   if ( varianti_modello[0].abilitato && access(str, F_OK) != 0 )\
   {\
      fprintf(stderr, "file %s doesn't exist!\n", str);\
      varianti_modello[0].abilitato = False;\
   }\
   else\
      if (varianti_modello[0].abilitato)\
         num_file_f14++;\
   strcpy(varianti_modello[0].percorso, str);\
   XmStringFree(str);\
   str = XmTextFieldGetString(UxGetWidget(text_title1));\
   strcpy(varianti_modello[0].titolo, str);\
   XmStringFree(str);\
\
   str = XmTextFieldGetString(UxGetWidget(text_path2));\
   if ( varianti_modello[1].abilitato && access(str, F_OK) != 0 )\
   {\
      fprintf(stderr, "file %s doesn't exist!\n", str);\
      varianti_modello[1].abilitato = False;\
   }\
   else\
      if (varianti_modello[1].abilitato)\
         num_file_f14++;\
   strcpy(varianti_modello[1].percorso, str);\
   XmStringFree(str);\
   str = XmTextFieldGetString(UxGetWidget(text_title2));\
   strcpy(varianti_modello[1].titolo, str);\
   XmStringFree(str);\
\
   str = XmTextFieldGetString(UxGetWidget(text_path3));\
   if ( varianti_modello[2].abilitato && access(str, F_OK) != 0 )\
   {\
      fprintf(stderr, "file %s doesn't exist!\n", str);\
      varianti_modello[2].abilitato = False;\
   }\
   else\
      if (varianti_modello[2].abilitato)\
         num_file_f14++;\
   strcpy(varianti_modello[2].percorso, str);\
   XmStringFree(str);\
   str = XmTextFieldGetString(UxGetWidget(text_title3));\
   strcpy(varianti_modello[2].titolo, str);\
   XmStringFree(str);\
\
   str = XmTextFieldGetString(UxGetWidget(text_path4));\
   if ( varianti_modello[3].abilitato && access(str, F_OK) != 0 )\
   {\
      fprintf(stderr, "file %s doesn't exist!\n", str);\
      varianti_modello[3].abilitato = False;\
   }\
   else\
      if (varianti_modello[3].abilitato)\
         num_file_f14++;\
   strcpy(varianti_modello[3].percorso, str);\
   XmStringFree(str);\
   str = XmTextFieldGetString(UxGetWidget(text_title4));\
   strcpy(varianti_modello[3].titolo, str);\
   XmStringFree(str);\
\
   str = XmTextFieldGetString(UxGetWidget(text_path5));\
   if ( varianti_modello[4].abilitato && access(str, F_OK) != 0 )\
   {\
      fprintf(stderr, "file %s doesn't exist!\n", str);\
      varianti_modello[4].abilitato = False;\
   }\
   else\
      if (varianti_modello[4].abilitato)\
         num_file_f14++;\
   strcpy(varianti_modello[4].percorso, str);\
   XmStringFree(str);\
   str = XmTextFieldGetString(UxGetWidget(text_title5));\
   strcpy(varianti_modello[4].titolo, str);\
   XmStringFree(str);\
}\

*window_models.name: window_models
*window_models.x: 606
*window_models.y: 132
*window_models.width: 610
*window_models.height: 380
*window_models.background: "#4f9f9f"
*window_models.defaultFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*window_models.title: "MODELS VARIANT"
*window_models.allowShellResize: "false"

*form4.class: form
*form4.parent: window_models
*form4.static: true
*form4.name: form4
*form4.resizePolicy: "resize_none"
*form4.unitType: "pixels"
*form4.x: 0
*form4.y: 10
*form4.width: 650
*form4.height: 380
*form4.background: "#4f9f9f"

*labelGadget2.class: labelGadget
*labelGadget2.parent: form4
*labelGadget2.static: true
*labelGadget2.name: labelGadget2
*labelGadget2.x: 35
*labelGadget2.y: 20
*labelGadget2.width: 235
*labelGadget2.height: 20
*labelGadget2.alignment: "alignment_beginning"
*labelGadget2.labelString: "STEADY STATE IDENTIFIER"
*labelGadget2.leftOffset: 35
*labelGadget2.leftAttachment: "attach_form"

*labelGadget4.class: labelGadget
*labelGadget4.parent: form4
*labelGadget4.static: true
*labelGadget4.name: labelGadget4
*labelGadget4.x: 280
*labelGadget4.y: 20
*labelGadget4.width: 270
*labelGadget4.height: 20
*labelGadget4.labelString: "FILE PATHNAME"
*labelGadget4.leftAttachment: "attach_position"
*labelGadget4.leftOffset: 0
*labelGadget4.leftPosition: 50
*labelGadget4.rightAttachment: "attach_form"
*labelGadget4.rightOffset: 10
*labelGadget4.alignment: "alignment_beginning"

*text_path1.class: textField
*text_path1.parent: form4
*text_path1.static: true
*text_path1.name: text_path1
*text_path1.x: 305
*text_path1.y: 60
*text_path1.width: 295
*text_path1.height: 35
*text_path1.background: "#4f9f9f"
*text_path1.leftAttachment: "attach_position"
*text_path1.leftOffset: 0
*text_path1.leftPosition: 50
*text_path1.rightAttachment: "attach_form"
*text_path1.rightOffset: 10
*text_path1.topAttachment: "attach_widget"
*text_path1.topOffset: 20
*text_path1.topWidget: "labelGadget2"
*text_path1.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_path1.maxLength: 256

*pushButton4.class: pushButton
*pushButton4.parent: form4
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.x: 30
*pushButton4.y: 350
*pushButton4.width: 190
*pushButton4.height: 30
*pushButton4.background: "#4f9f9f"
*pushButton4.labelString: "View"
*pushButton4.bottomAttachment: "attach_form"
*pushButton4.bottomOffset: 20
*pushButton4.leftAttachment: "attach_form"
*pushButton4.leftOffset: 20
*pushButton4.topAttachment: "attach_none"
*pushButton4.rightAttachment: "attach_position"
*pushButton4.rightPosition: 40
*pushButton4.activateCallback: {\
WindowInfoStruct *winfo;\
\
salva_steady_version();\
\
/* istanzia un nuovo item nella lista */\
winfo = new_struct_info(VARIABILI_N_F14);\
\
/* visualizza le variabili del i vari file f14.dat */\
winfo->swindow = create_info_ashell(NULL, NULL, VARIABILI_N_F14, winfo);\
}

*pushButton5.class: pushButton
*pushButton5.parent: form4
*pushButton5.static: true
*pushButton5.name: pushButton5
*pushButton5.x: 360
*pushButton5.y: 350
*pushButton5.width: 180
*pushButton5.height: 30
*pushButton5.background: "#4f9f9f"
*pushButton5.labelString: "Done"
*pushButton5.bottomAttachment: "attach_form"
*pushButton5.bottomOffset: 20
*pushButton5.leftAttachment: "attach_position"
*pushButton5.leftOffset: 0
*pushButton5.leftPosition: 60
*pushButton5.rightAttachment: "attach_form"
*pushButton5.rightOffset: 20
*pushButton5.topAttachment: "attach_none"
*pushButton5.activateCallback: {\
salva_steady_version();\
unlink(DOC_SSTATE_MODELLO); /* obbliga a ricreare la documentazione */\
open_window_models = False;\
UxDestroySwidget(window_models);\
}

*toggleButton1.class: toggleButton
*toggleButton1.parent: form4
*toggleButton1.static: true
*toggleButton1.name: toggleButton1
*toggleButton1.x: 0
*toggleButton1.y: 60
*toggleButton1.width: 20
*toggleButton1.height: 30
*toggleButton1.background: "#4f9f9f"
*toggleButton1.leftAttachment: "attach_form"
*toggleButton1.leftOffset: 5
*toggleButton1.topAttachment: "attach_widget"
*toggleButton1.topOffset: 25
*toggleButton1.topWidget: "labelGadget2"

*toggleButton2.class: toggleButton
*toggleButton2.parent: form4
*toggleButton2.static: true
*toggleButton2.name: toggleButton2
*toggleButton2.x: 0
*toggleButton2.y: 110
*toggleButton2.width: 20
*toggleButton2.height: 30
*toggleButton2.background: "#4f9f9f"
*toggleButton2.leftOffset: 5
*toggleButton2.topAttachment: "attach_widget"
*toggleButton2.topOffset: 20
*toggleButton2.topWidget: "toggleButton1"
*toggleButton2.leftAttachment: "attach_form"

*toggleButton3.class: toggleButton
*toggleButton3.parent: form4
*toggleButton3.static: true
*toggleButton3.name: toggleButton3
*toggleButton3.x: 10
*toggleButton3.y: 160
*toggleButton3.width: 20
*toggleButton3.height: 30
*toggleButton3.background: "#4f9f9f"
*toggleButton3.leftAttachment: "attach_form"
*toggleButton3.leftOffset: 5
*toggleButton3.topAttachment: "attach_widget"
*toggleButton3.topOffset: 20
*toggleButton3.topWidget: "toggleButton2"

*toggleButton4.class: toggleButton
*toggleButton4.parent: form4
*toggleButton4.static: true
*toggleButton4.name: toggleButton4
*toggleButton4.x: 0
*toggleButton4.y: 210
*toggleButton4.width: 20
*toggleButton4.height: 30
*toggleButton4.background: "#4f9f9f"
*toggleButton4.leftAttachment: "attach_form"
*toggleButton4.leftOffset: 5
*toggleButton4.topAttachment: "attach_widget"
*toggleButton4.topOffset: 20
*toggleButton4.topWidget: "toggleButton3"

*toggleButton5.class: toggleButton
*toggleButton5.parent: form4
*toggleButton5.static: true
*toggleButton5.name: toggleButton5
*toggleButton5.x: 5
*toggleButton5.y: 265
*toggleButton5.width: 20
*toggleButton5.height: 25
*toggleButton5.background: "#4f9f9f"
*toggleButton5.leftAttachment: "attach_form"
*toggleButton5.leftOffset: 5
*toggleButton5.topAttachment: "attach_widget"
*toggleButton5.topOffset: 20
*toggleButton5.topWidget: "toggleButton4"

*text_title1.class: textField
*text_title1.parent: form4
*text_title1.static: true
*text_title1.name: text_title1
*text_title1.x: 35
*text_title1.y: 60
*text_title1.width: 258
*text_title1.height: 35
*text_title1.background: "#4f9f9f"
*text_title1.leftAttachment: "attach_widget"
*text_title1.leftOffset: 10
*text_title1.leftWidget: "toggleButton1"
*text_title1.rightAttachment: "attach_position"
*text_title1.rightPosition: 48
*text_title1.topAttachment: "attach_widget"
*text_title1.topOffset: 20
*text_title1.topWidget: "labelGadget2"
*text_title1.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_title1.maxLength: 14

*text_title2.class: textField
*text_title2.parent: form4
*text_title2.static: true
*text_title2.name: text_title2
*text_title2.x: 35
*text_title2.y: 110
*text_title2.width: 258
*text_title2.height: 35
*text_title2.background: "#4f9f9f"
*text_title2.leftAttachment: "attach_widget"
*text_title2.leftOffset: 10
*text_title2.leftWidget: "toggleButton2"
*text_title2.rightAttachment: "attach_position"
*text_title2.rightPosition: 48
*text_title2.topAttachment: "attach_widget"
*text_title2.topOffset: 15
*text_title2.topWidget: "toggleButton1"
*text_title2.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_title2.maxLength: 14

*text_path2.class: textField
*text_path2.parent: form4
*text_path2.static: true
*text_path2.name: text_path2
*text_path2.x: 305
*text_path2.y: 110
*text_path2.width: 295
*text_path2.height: 35
*text_path2.background: "#4f9f9f"
*text_path2.leftAttachment: "attach_position"
*text_path2.leftOffset: 0
*text_path2.leftPosition: 50
*text_path2.rightAttachment: "attach_form"
*text_path2.rightOffset: 10
*text_path2.topAttachment: "attach_widget"
*text_path2.topOffset: 15
*text_path2.topWidget: "toggleButton1"
*text_path2.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_path2.maxLength: 256

*text_title3.class: textField
*text_title3.parent: form4
*text_title3.static: true
*text_title3.name: text_title3
*text_title3.x: 35
*text_title3.y: 160
*text_title3.width: 258
*text_title3.height: 35
*text_title3.background: "#4f9f9f"
*text_title3.leftAttachment: "attach_widget"
*text_title3.leftOffset: 10
*text_title3.leftWidget: "toggleButton3"
*text_title3.rightAttachment: "attach_position"
*text_title3.rightPosition: 48
*text_title3.topAttachment: "attach_widget"
*text_title3.topOffset: 15
*text_title3.topWidget: "toggleButton2"
*text_title3.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_title3.maxLength: 14

*text_path3.class: textField
*text_path3.parent: form4
*text_path3.static: true
*text_path3.name: text_path3
*text_path3.x: 305
*text_path3.y: 160
*text_path3.width: 295
*text_path3.height: 35
*text_path3.background: "#4f9f9f"
*text_path3.leftAttachment: "attach_position"
*text_path3.leftOffset: 0
*text_path3.leftPosition: 50
*text_path3.rightAttachment: "attach_form"
*text_path3.rightOffset: 10
*text_path3.topAttachment: "attach_widget"
*text_path3.topOffset: 15
*text_path3.topWidget: "toggleButton2"
*text_path3.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_path3.maxLength: 256

*text_title4.class: textField
*text_title4.parent: form4
*text_title4.static: true
*text_title4.name: text_title4
*text_title4.x: 35
*text_title4.y: 210
*text_title4.width: 258
*text_title4.height: 35
*text_title4.background: "#4f9f9f"
*text_title4.leftAttachment: "attach_widget"
*text_title4.leftOffset: 10
*text_title4.leftWidget: "toggleButton4"
*text_title4.rightAttachment: "attach_position"
*text_title4.rightPosition: 48
*text_title4.topAttachment: "attach_widget"
*text_title4.topOffset: 15
*text_title4.topWidget: "toggleButton3"
*text_title4.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_title4.maxLength: 14

*text_path4.class: textField
*text_path4.parent: form4
*text_path4.static: true
*text_path4.name: text_path4
*text_path4.x: 305
*text_path4.y: 210
*text_path4.width: 295
*text_path4.height: 35
*text_path4.background: "#4f9f9f"
*text_path4.leftAttachment: "attach_position"
*text_path4.leftOffset: 0
*text_path4.leftPosition: 50
*text_path4.rightAttachment: "attach_form"
*text_path4.rightOffset: 10
*text_path4.topAttachment: "attach_widget"
*text_path4.topOffset: 15
*text_path4.topWidget: "toggleButton3"
*text_path4.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_path4.maxLength: 256

*text_title5.class: textField
*text_title5.parent: form4
*text_title5.static: true
*text_title5.name: text_title5
*text_title5.x: 35
*text_title5.y: 260
*text_title5.width: 258
*text_title5.height: 35
*text_title5.background: "#4f9f9f"
*text_title5.leftAttachment: "attach_widget"
*text_title5.leftOffset: 10
*text_title5.leftWidget: "toggleButton5"
*text_title5.rightAttachment: "attach_position"
*text_title5.rightPosition: 48
*text_title5.topAttachment: "attach_widget"
*text_title5.topOffset: 15
*text_title5.topWidget: "toggleButton4"
*text_title5.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_title5.maxLength: 14

*text_path5.class: textField
*text_path5.parent: form4
*text_path5.static: true
*text_path5.name: text_path5
*text_path5.x: 305
*text_path5.y: 260
*text_path5.width: 295
*text_path5.height: 35
*text_path5.background: "#4f9f9f"
*text_path5.leftAttachment: "attach_position"
*text_path5.leftOffset: 0
*text_path5.leftPosition: 50
*text_path5.rightAttachment: "attach_form"
*text_path5.rightOffset: 10
*text_path5.topAttachment: "attach_widget"
*text_path5.topOffset: 15
*text_path5.topWidget: "toggleButton4"
*text_path5.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_path5.maxLength: 256

*separatorGadget2.class: separatorGadget
*separatorGadget2.parent: form4
*separatorGadget2.static: true
*separatorGadget2.name: separatorGadget2
*separatorGadget2.x: 30
*separatorGadget2.y: 320
*separatorGadget2.width: 510
*separatorGadget2.height: 10
*separatorGadget2.bottomAttachment: "attach_widget"
*separatorGadget2.bottomOffset: 10
*separatorGadget2.bottomWidget: "pushButton4"
*separatorGadget2.leftAttachment: "attach_form"
*separatorGadget2.leftOffset: 5
*separatorGadget2.rightAttachment: "attach_form"
*separatorGadget2.rightOffset: 5
*separatorGadget2.topAttachment: "attach_widget"
*separatorGadget2.topOffset: 10
*separatorGadget2.topWidget: "toggleButton5"

