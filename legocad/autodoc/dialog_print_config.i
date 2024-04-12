! UIMX ascii 2.0 key: 7622                                                      

*dialog_print_config.class: formDialog
*dialog_print_config.parent: NO_PARENT
*dialog_print_config.defaultShell: topLevelShell
*dialog_print_config.static: true
*dialog_print_config.gbldecl: /*\
   modulo dialog_print_config.i\
   tipo \
   release 1.12\
   data 3/31/95\
   reserved @(#)dialog_print_config.i	1.12\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
\
#include "autodoc.h"\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE						*/\
/************************************************************************/\
\
extern int num_lines_vert, num_lines_horiz;\
extern byte tipo_stampante;\
\
extern char page_prefix_dati[], page_prefix_var[];\
\
extern Boolean open_print_config;\
\
/************************************************************************/\
/* VARIABILI GLOBALI 							*/\
/************************************************************************/\
\
static byte temp_tipo_stampante;
*dialog_print_config.ispecdecl:
*dialog_print_config.funcdecl: swidget create_dialog_print_config()\

*dialog_print_config.funcname: create_dialog_print_config
*dialog_print_config.funcdef: "swidget", "<create_dialog_print_config>(%)"
*dialog_print_config.icode: char str[10];\
\
open_print_config = True;
*dialog_print_config.fcode: sprintf(str, "%3d", num_lines_vert);\
XmTextSetString(UxGetWidget(text_num_righe_vr), str);\
sprintf(str, "%3d", num_lines_horiz);\
XmTextSetString(UxGetWidget(text_num_righe_or), str);\
XmTextSetString(UxGetWidget(text_prefix_dati), page_prefix_dati);\
XmTextSetString(UxGetWidget(text_prefix_var), page_prefix_var);\
\
if (tipo_stampante == PRINTER_ASCII)\
   set_something(UxGetWidget(opt_printer), XmNmenuHistory,\
                 UxGetWidget(opt_printer_ascii));\
else\
   set_something(UxGetWidget(opt_printer), XmNmenuHistory,\
                 UxGetWidget(opt_printer_altro));\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*dialog_print_config.auxdecl:
*dialog_print_config.name: dialog_print_config
*dialog_print_config.unitType: "pixels"
*dialog_print_config.x: 242
*dialog_print_config.y: 175
*dialog_print_config.width: 362
*dialog_print_config.height: 300
*dialog_print_config.background: "#4f9f9f"
*dialog_print_config.buttonFontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*dialog_print_config.dialogTitle: "PRINTER CONFIG"
*dialog_print_config.labelFontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*dialog_print_config.noResize: "true"

*label10.class: label
*label10.parent: dialog_print_config
*label10.static: true
*label10.name: label10
*label10.x: 10
*label10.y: 20
*label10.width: 180
*label10.height: 37
*label10.background: "#4f9f9f"
*label10.leftAttachment: "attach_form"
*label10.leftOffset: 10
*label10.topOffset: 10
*label10.alignment: "alignment_beginning"
*label10.labelString: "Printer type:"
*label10.topAttachment: "attach_form"

*label11.class: label
*label11.parent: dialog_print_config
*label11.static: true
*label11.name: label11
*label11.x: 10
*label11.y: 60
*label11.width: 240
*label11.height: 30
*label11.background: "#4f9f9f"
*label11.leftAttachment: "attach_form"
*label11.leftOffset: 10
*label11.topAttachment: "attach_widget"
*label11.topOffset: 20
*label11.topWidget: "label10"
*label11.alignment: "alignment_beginning"
*label11.labelString: "No lines per page (VERTICAL):"

*pb_ok_print_config.class: pushButton
*pb_ok_print_config.parent: dialog_print_config
*pb_ok_print_config.static: true
*pb_ok_print_config.name: pb_ok_print_config
*pb_ok_print_config.x: 20
*pb_ok_print_config.y: 150
*pb_ok_print_config.width: 176
*pb_ok_print_config.height: 30
*pb_ok_print_config.background: "#4f9f9f"
*pb_ok_print_config.bottomAttachment: "attach_form"
*pb_ok_print_config.bottomOffset: 10
*pb_ok_print_config.labelString: "Ok"
*pb_ok_print_config.leftAttachment: "attach_form"
*pb_ok_print_config.leftOffset: 20
*pb_ok_print_config.rightAttachment: "attach_position"
*pb_ok_print_config.rightPosition: 40
*pb_ok_print_config.topAttachment: "attach_none"
*pb_ok_print_config.activateCallback: {\
char *str;\
int num;\
FILE *fp;\
\
str = XmTextFieldGetString(UxGetWidget(text_num_righe_vr));\
if (IsNumeric(str))\
   sscanf(str,"%d",&num);\
XmStringFree(str);\
\
/* cancella i file di documentazione cosi' il programma e' costretto a */\
/* ricrearli con i nuovi parametri */\
if (num != num_lines_vert)\
{\
   unlink(DOC_DATI_MODELLO);\
   unlink(DOC_VAR_MODELLO);\
   unlink(DOC_SSTATE_MODELLO);\
}\
num_lines_vert = num;\
\
str = XmTextFieldGetString(UxGetWidget(text_num_righe_or));\
if (IsNumeric(str))\
   sscanf(str,"%d",&num);\
XmStringFree(str);\
\
/* cancella i file di documentazione cosi' il programma e' costretto a */\
/* ricrearli con i nuovi parametri */\
if (num != num_lines_horiz)\
{\
   unlink(DOC_VAR_MODELLO);\
   unlink(DOC_SSTATE_MODELLO);\
}\
num_lines_horiz = num;\
 \
str = XmTextFieldGetString(UxGetWidget(text_prefix_dati));\
strcpy(page_prefix_dati, str);\
XmStringFree(str);\
 \
str = XmTextFieldGetString(UxGetWidget(text_prefix_var));\
strcpy(page_prefix_var, str);\
XmStringFree(str);\
\
tipo_stampante = temp_tipo_stampante;\
\
/* salva la configurazione */\
if ((fp = fopen(FILE_PRINT_CONFIG,"w")) != NULL)\
{\
   fprintf(fp, "%d %d %s %s", num_lines_vert, num_lines_horiz, page_prefix_dati,\
			      page_prefix_var);\
   fclose(fp);\
}\
\
open_print_config = False;\
UxDestroySwidget(dialog_print_config);\
}

*pb_cancel_print_config.class: pushButton
*pb_cancel_print_config.parent: dialog_print_config
*pb_cancel_print_config.static: true
*pb_cancel_print_config.name: pb_cancel_print_config
*pb_cancel_print_config.x: 294
*pb_cancel_print_config.y: 150
*pb_cancel_print_config.width: 176
*pb_cancel_print_config.height: 30
*pb_cancel_print_config.background: "#4f9f9f"
*pb_cancel_print_config.bottomAttachment: "attach_form"
*pb_cancel_print_config.bottomOffset: 10
*pb_cancel_print_config.labelString: "Cancel"
*pb_cancel_print_config.leftAttachment: "attach_position"
*pb_cancel_print_config.leftOffset: 0
*pb_cancel_print_config.leftPosition: 60
*pb_cancel_print_config.rightAttachment: "attach_form"
*pb_cancel_print_config.rightOffset: 20
*pb_cancel_print_config.topAttachment: "attach_none"
*pb_cancel_print_config.activateCallback: {\
open_print_config = False;\
UxDestroySwidget(dialog_print_config);\
}

*text_num_righe_vr.class: textField
*text_num_righe_vr.parent: dialog_print_config
*text_num_righe_vr.static: true
*text_num_righe_vr.name: text_num_righe_vr
*text_num_righe_vr.x: 260
*text_num_righe_vr.y: 60
*text_num_righe_vr.width: 100
*text_num_righe_vr.height: 35
*text_num_righe_vr.background: "#4f9f9f"
*text_num_righe_vr.leftAttachment: "attach_widget"
*text_num_righe_vr.leftOffset: 10
*text_num_righe_vr.leftWidget: "label11"
*text_num_righe_vr.topAttachment: "attach_widget"
*text_num_righe_vr.topOffset: 20
*text_num_righe_vr.topWidget: "label10"
*text_num_righe_vr.rightAttachment: "attach_form"
*text_num_righe_vr.rightOffset: 10
*text_num_righe_vr.maxLength: 3

*rowColumn1.class: rowColumn
*rowColumn1.parent: dialog_print_config
*rowColumn1.static: true
*rowColumn1.name: rowColumn1
*rowColumn1.x: 190
*rowColumn1.y: 10
*rowColumn1.width: 170
*rowColumn1.height: 37
*rowColumn1.background: "#4f9f9f"
*rowColumn1.leftAttachment: "attach_widget"
*rowColumn1.leftOffset: 0
*rowColumn1.leftWidget: "label10"
*rowColumn1.topAttachment: "attach_form"
*rowColumn1.topOffset: 10
*rowColumn1.rightAttachment: "attach_form"
*rowColumn1.rightOffset: 10

*menu1.class: rowColumn
*menu1.parent: rowColumn1
*menu1.static: true
*menu1.name: menu1
*menu1.rowColumnType: "menu_option"
*menu1.subMenuId: "opt_printer"
*menu1.x: 196
*menu1.y: 3
*menu1.background: "#4f9f9f"
*menu1.height: 30

*opt_printer.class: rowColumn
*opt_printer.parent: menu1
*opt_printer.static: true
*opt_printer.name: opt_printer
*opt_printer.rowColumnType: "menu_pulldown"

*opt_printer_ascii.class: pushButton
*opt_printer_ascii.parent: opt_printer
*opt_printer_ascii.static: true
*opt_printer_ascii.name: opt_printer_ascii
*opt_printer_ascii.labelString: "ASCII"
*opt_printer_ascii.activateCallback: {\
temp_tipo_stampante = 0;  /* ASCII */\
}
*opt_printer_ascii.background: "#4f9f9f"
*opt_printer_ascii.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"

*opt_printer_altro.class: pushButton
*opt_printer_altro.parent: opt_printer
*opt_printer_altro.static: true
*opt_printer_altro.name: opt_printer_altro
*opt_printer_altro.labelString: "Altre Stmp"
*opt_printer_altro.background: "#4f9f9f"
*opt_printer_altro.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*opt_printer_altro.activateCallback: {\
temp_tipo_stampante = 1; /* POSTSCRIPT */\
}

*label7.class: label
*label7.parent: dialog_print_config
*label7.static: true
*label7.name: label7
*label7.x: 10
*label7.y: 90
*label7.width: 240
*label7.height: 30
*label7.background: "#4f9f9f"
*label7.labelString: "No lines per page (HORIZONTAL):"
*label7.topAttachment: "attach_widget"
*label7.topOffset: 10
*label7.topWidget: "label11"

*text_num_righe_or.class: textField
*text_num_righe_or.parent: dialog_print_config
*text_num_righe_or.static: true
*text_num_righe_or.name: text_num_righe_or
*text_num_righe_or.x: 260
*text_num_righe_or.y: 100
*text_num_righe_or.width: 80
*text_num_righe_or.height: 35
*text_num_righe_or.rightAttachment: "attach_form"
*text_num_righe_or.rightOffset: 10
*text_num_righe_or.background: "#4f9f9f"
*text_num_righe_or.topAttachment: "attach_widget"
*text_num_righe_or.topOffset: 10
*text_num_righe_or.topWidget: "label11"
*text_num_righe_or.leftAttachment: "attach_widget"
*text_num_righe_or.leftOffset: 10
*text_num_righe_or.leftWidget: "label7"
*text_num_righe_or.maxLength: 3

*label4.class: label
*label4.parent: dialog_print_config
*label4.static: true
*label4.name: label4
*label4.x: 10
*label4.y: 130
*label4.width: 240
*label4.height: 35
*label4.topAttachment: "attach_widget"
*label4.topOffset: 10
*label4.topWidget: "label7"
*label4.alignment: "alignment_beginning"
*label4.background: "#4f9f9f"
*label4.labelString: "Page prefix geometrical data:"
*label4.leftAttachment: "attach_form"
*label4.leftOffset: 10

*text_prefix_dati.class: textField
*text_prefix_dati.parent: dialog_print_config
*text_prefix_dati.static: true
*text_prefix_dati.name: text_prefix_dati
*text_prefix_dati.x: 260
*text_prefix_dati.y: 140
*text_prefix_dati.width: 80
*text_prefix_dati.height: 35
*text_prefix_dati.background: "#4f9f9f"
*text_prefix_dati.topAttachment: "attach_widget"
*text_prefix_dati.topOffset: 10
*text_prefix_dati.topWidget: "label7"
*text_prefix_dati.leftAttachment: "attach_widget"
*text_prefix_dati.leftOffset: 10
*text_prefix_dati.leftWidget: "label4"
*text_prefix_dati.rightAttachment: "attach_form"
*text_prefix_dati.rightOffset: 10
*text_prefix_dati.maxLength: 5

*label9.class: label
*label9.parent: dialog_print_config
*label9.static: true
*label9.name: label9
*label9.x: 20
*label9.y: 157
*label9.width: 240
*label9.height: 35
*label9.alignment: "alignment_beginning"
*label9.background: "#4f9f9f"
*label9.labelString: "Page prefix variables:"
*label9.leftAttachment: "attach_form"
*label9.leftOffset: 10
*label9.topAttachment: "attach_widget"
*label9.topOffset: 5
*label9.topWidget: "label4"
*label9.bottomAttachment: "attach_none"

*text_prefix_var.class: textField
*text_prefix_var.parent: dialog_print_config
*text_prefix_var.static: true
*text_prefix_var.name: text_prefix_var
*text_prefix_var.x: 270
*text_prefix_var.y: 157
*text_prefix_var.width: 80
*text_prefix_var.height: 35
*text_prefix_var.background: "#4f9f9f"
*text_prefix_var.maxLength: 5
*text_prefix_var.leftAttachment: "attach_widget"
*text_prefix_var.leftOffset: 10
*text_prefix_var.topAttachment: "attach_widget"
*text_prefix_var.topOffset: 5
*text_prefix_var.topWidget: "label4"
*text_prefix_var.rightAttachment: "attach_form"
*text_prefix_var.rightOffset: 10
*text_prefix_var.leftWidget: "label9"
*text_prefix_var.bottomAttachment: "attach_none"

*separatorGadget6.class: separatorGadget
*separatorGadget6.parent: dialog_print_config
*separatorGadget6.static: true
*separatorGadget6.name: separatorGadget6
*separatorGadget6.x: 10
*separatorGadget6.y: 110
*separatorGadget6.width: 470
*separatorGadget6.height: 10
*separatorGadget6.bottomAttachment: "attach_widget"
*separatorGadget6.bottomOffset: 10
*separatorGadget6.bottomWidget: "pb_ok_print_config"
*separatorGadget6.leftAttachment: "attach_form"
*separatorGadget6.leftOffset: 5
*separatorGadget6.rightAttachment: "attach_form"
*separatorGadget6.rightOffset: 5
*separatorGadget6.topAttachment: "attach_widget"
*separatorGadget6.topOffset: 10
*separatorGadget6.topWidget: "label9"

