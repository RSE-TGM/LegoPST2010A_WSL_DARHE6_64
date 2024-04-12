! UIMX ascii 2.0 key: 1133                                                      

*NormParamDialog.class: bulletinBoardDialog
*NormParamDialog.parent: NO_PARENT
*NormParamDialog.defaultShell: topLevelShell
*NormParamDialog.static: true
*NormParamDialog.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo NormParamDialog.i\
   tipo \
   release 2.15\
   data 4/26/95\
   reserved @(#)NormParamDialog.i	2.15\
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
extern char dati_norm[10][7];
*NormParamDialog.ispecdecl:
*NormParamDialog.funcdecl: swidget popup_NormParamDialog()\

*NormParamDialog.funcname: popup_NormParamDialog
*NormParamDialog.funcdef: "swidget", "<popup_NormParamDialog>(%)"
*NormParamDialog.icode:
*NormParamDialog.fcode: load_dati_norm(); /* inserisce i dati di normalizzazione \
                     nei campi testo */\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*NormParamDialog.auxdecl: /*\
  load_dati_norm():\
	carica nei campi testo i valori attuali dei parametri\
        di normalizzazione\
*/\
load_dati_norm()\
{\
UxPutText(p0_text,dati_norm[0]);\
UxPutText(h0_text,dati_norm[1]);\
UxPutText(w0_text,dati_norm[2]);\
UxPutText(t0_text,dati_norm[3]);\
UxPutText(r0_text,dati_norm[4]);\
UxPutText(l0_text,dati_norm[5]);\
UxPutText(v0_text,dati_norm[6]);\
UxPutText(dp0_text,dati_norm[7]);\
}\
\
save_dati_norm()\
{\
char *str;\
str=UxGetText(p0_text);\
strcpy(dati_norm[0],str);\
str=UxGetText(h0_text);\
strcpy(dati_norm[1],str);\
str=UxGetText(w0_text);\
strcpy(dati_norm[2],str);\
str=UxGetText(t0_text);\
strcpy(dati_norm[3],str);\
str=UxGetText(r0_text);\
strcpy(dati_norm[4],str);\
str=UxGetText(l0_text);\
strcpy(dati_norm[5],str);\
str=UxGetText(v0_text);\
strcpy(dati_norm[6],str);\
str=UxGetText(dp0_text);\
strcpy(dati_norm[7],str);\
}\

*NormParamDialog.name: NormParamDialog
*NormParamDialog.unitType: "pixels"
*NormParamDialog.x: 365
*NormParamDialog.y: 248
*NormParamDialog.width: 254
*NormParamDialog.height: 311
*NormParamDialog.dialogTitle: "Normalization parameters"
*NormParamDialog.dialogStyle: "dialog_full_application_modal"
*NormParamDialog.resizePolicy: "resize_none"

*labelGadget5.class: labelGadget
*labelGadget5.parent: NormParamDialog
*labelGadget5.static: true
*labelGadget5.name: labelGadget5
*labelGadget5.x: 10
*labelGadget5.y: 20
*labelGadget5.width: 120
*labelGadget5.height: 20
*labelGadget5.alignment: "alignment_beginning"
*labelGadget5.labelString: "Pressure (P0):"

*labelGadget6.class: labelGadget
*labelGadget6.parent: NormParamDialog
*labelGadget6.static: true
*labelGadget6.name: labelGadget6
*labelGadget6.x: 10
*labelGadget6.y: 50
*labelGadget6.width: 120
*labelGadget6.height: 20
*labelGadget6.alignment: "alignment_beginning"
*labelGadget6.labelString: "Entalphy (H0):"

*labelGadget7.class: labelGadget
*labelGadget7.parent: NormParamDialog
*labelGadget7.static: true
*labelGadget7.name: labelGadget7
*labelGadget7.x: 10
*labelGadget7.y: 80
*labelGadget7.width: 120
*labelGadget7.height: 20
*labelGadget7.alignment: "alignment_beginning"
*labelGadget7.labelString: "Flow (W0):"

*labelGadget8.class: labelGadget
*labelGadget8.parent: NormParamDialog
*labelGadget8.static: true
*labelGadget8.name: labelGadget8
*labelGadget8.x: 10
*labelGadget8.y: 170
*labelGadget8.width: 120
*labelGadget8.height: 20
*labelGadget8.alignment: "alignment_beginning"
*labelGadget8.labelString: "Length (L0):"

*labelGadget9.class: labelGadget
*labelGadget9.parent: NormParamDialog
*labelGadget9.static: true
*labelGadget9.name: labelGadget9
*labelGadget9.x: 10
*labelGadget9.y: 110
*labelGadget9.width: 120
*labelGadget9.height: 20
*labelGadget9.alignment: "alignment_beginning"
*labelGadget9.labelString: "Temperature (T0):"

*labelGadget10.class: labelGadget
*labelGadget10.parent: NormParamDialog
*labelGadget10.static: true
*labelGadget10.name: labelGadget10
*labelGadget10.x: 10
*labelGadget10.y: 140
*labelGadget10.width: 120
*labelGadget10.height: 20
*labelGadget10.alignment: "alignment_beginning"
*labelGadget10.labelString: "Density (R0):"

*labelGadget12.class: labelGadget
*labelGadget12.parent: NormParamDialog
*labelGadget12.static: true
*labelGadget12.name: labelGadget12
*labelGadget12.x: 10
*labelGadget12.y: 200
*labelGadget12.width: 120
*labelGadget12.height: 20
*labelGadget12.alignment: "alignment_beginning"
*labelGadget12.labelString: "Volume (V0):"

*labelGadget13.class: labelGadget
*labelGadget13.parent: NormParamDialog
*labelGadget13.static: true
*labelGadget13.name: labelGadget13
*labelGadget13.x: 10
*labelGadget13.y: 233
*labelGadget13.width: 140
*labelGadget13.height: 20
*labelGadget13.alignment: "alignment_beginning"
*labelGadget13.labelString: "Pressure diff.(DP0):"

*p0_text.class: text
*p0_text.parent: NormParamDialog
*p0_text.static: true
*p0_text.name: p0_text
*p0_text.x: 160
*p0_text.y: 17
*p0_text.width: 70
*p0_text.height: 27
*p0_text.resizeHeight: "true"
*p0_text.marginHeight: 1
*p0_text.marginWidth: 2
*p0_text.maxLength: 6
*p0_text.resizeWidth: "true"

*h0_text.class: text
*h0_text.parent: NormParamDialog
*h0_text.static: true
*h0_text.name: h0_text
*h0_text.x: 160
*h0_text.y: 50
*h0_text.width: 70
*h0_text.height: 27
*h0_text.marginHeight: 1
*h0_text.marginWidth: 2
*h0_text.resizeHeight: "true"
*h0_text.maxLength: 6
*h0_text.resizeWidth: "true"

*t0_text.class: text
*t0_text.parent: NormParamDialog
*t0_text.static: true
*t0_text.name: t0_text
*t0_text.x: 160
*t0_text.y: 107
*t0_text.width: 70
*t0_text.height: 27
*t0_text.marginHeight: 1
*t0_text.marginWidth: 2
*t0_text.resizeHeight: "true"
*t0_text.maxLength: 6
*t0_text.resizeWidth: "true"

*w0_text.class: text
*w0_text.parent: NormParamDialog
*w0_text.static: true
*w0_text.name: w0_text
*w0_text.x: 160
*w0_text.y: 77
*w0_text.width: 70
*w0_text.height: 27
*w0_text.marginHeight: 1
*w0_text.marginWidth: 2
*w0_text.resizeHeight: "true"
*w0_text.maxLength: 6
*w0_text.resizeWidth: "true"

*dp0_text.class: text
*dp0_text.parent: NormParamDialog
*dp0_text.static: true
*dp0_text.name: dp0_text
*dp0_text.x: 160
*dp0_text.y: 230
*dp0_text.width: 70
*dp0_text.height: 27
*dp0_text.marginHeight: 1
*dp0_text.marginWidth: 2
*dp0_text.resizeHeight: "true"
*dp0_text.maxLength: 6
*dp0_text.resizeWidth: "true"

*v0_text.class: text
*v0_text.parent: NormParamDialog
*v0_text.static: true
*v0_text.name: v0_text
*v0_text.x: 160
*v0_text.y: 197
*v0_text.width: 70
*v0_text.height: 27
*v0_text.marginHeight: 1
*v0_text.marginWidth: 2
*v0_text.resizeHeight: "true"
*v0_text.maxLength: 6
*v0_text.resizeWidth: "true"

*r0_text.class: text
*r0_text.parent: NormParamDialog
*r0_text.static: true
*r0_text.name: r0_text
*r0_text.x: 160
*r0_text.y: 137
*r0_text.width: 70
*r0_text.height: 27
*r0_text.marginHeight: 1
*r0_text.marginWidth: 2
*r0_text.resizeHeight: "true"
*r0_text.maxLength: 6
*r0_text.resizeWidth: "true"

*l0_text.class: text
*l0_text.parent: NormParamDialog
*l0_text.static: true
*l0_text.name: l0_text
*l0_text.x: 160
*l0_text.y: 170
*l0_text.width: 70
*l0_text.height: 27
*l0_text.marginHeight: 1
*l0_text.marginWidth: 2
*l0_text.resizeHeight: "true"
*l0_text.maxLength: 6
*l0_text.resizeWidth: "true"

*pushButton1.class: pushButton
*pushButton1.parent: NormParamDialog
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 30
*pushButton1.y: 270
*pushButton1.width: 70
*pushButton1.height: 30
*pushButton1.labelString: "OK"
*pushButton1.activateCallback: {\
save_dati_norm();\
}

*pushButton2.class: pushButton
*pushButton2.parent: NormParamDialog
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 140
*pushButton2.y: 270
*pushButton2.width: 70
*pushButton2.height: 30
*pushButton2.labelString: "Cancel"

