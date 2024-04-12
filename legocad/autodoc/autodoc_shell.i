! UIMX ascii 2.0 key: 7868                                                      

*autodoc_shell.class: applicationShell
*autodoc_shell.parent: NO_PARENT
*autodoc_shell.static: true
*autodoc_shell.gbldecl: /*\
   modulo autodoc_shell.i\
   tipo \
   release 1.12\
   data 3/31/95\
   reserved @(#)autodoc_shell.i	1.12\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
\
#include "autodoc.h"\
#include "noto_xbm.h"\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE						*/\
/************************************************************************/\
extern Display *display;\
extern int screen_num;\
\
extern char nome_modello[];\
\
extern char page_prefix_var[], page_prefix_dati[];\
extern int num_lines_vert, num_lines_horiz;\
\
extern char file_tempdati[], file_tempvar[];\
#ifndef DESIGN_TIME\
extern byte num_file_f14;\
#endif\
/************************************************************************/\
/* VARIABILI GLOBALI							*/\
/************************************************************************/\
char *font = "-Adobe-Courier-Bold-R-Normal--14-140-*";\
XFontStruct *finfo;\
XmFontList fontList;\
\
Pixmap pixm_noto;\
\
Colormap cmap;\
Pixel color_bg_label, color_select_label;\
\
Boolean open_window_unita = False;\
Boolean open_window_models = False;\
Boolean open_print_config = False;\
Boolean open_note_modello = False;\
#ifndef DESIGN_TIME\
WindowInfoStruct *winfo_list;\
#endif\
\
ModelBlockStruct *lista_blocchi;\
int num_blocchi;\
\
char *note_modello = NULL;
*autodoc_shell.ispecdecl:
*autodoc_shell.funcdecl: swidget create_autodoc_shell()\

*autodoc_shell.funcname: create_autodoc_shell
*autodoc_shell.funcdef: "swidget", "<create_autodoc_shell>(%)"
*autodoc_shell.icode: FILE *fp;
*autodoc_shell.fcode: /* recupera la colormappazza */\
   cmap = DefaultColormap(display, screen_num);\
\
   color_bg_label = get_colore("#4f8f8f");\
   color_select_label = get_colore("#4fafaf");\
\
/* leggi la configurazione della stampante */\
    if ((fp = fopen(FILE_PRINT_CONFIG, "r")) != NULL)\
   {\
      fscanf(fp, "%d %d %s %s", &num_lines_vert, &num_lines_horiz,\
                                page_prefix_dati, page_prefix_var);\
      fclose(fp);\
   }\
\
/* recupera la nota del modello */\
   if ((fp = fopen(FILE_NOTE_MODELLO, "r")) != NULL)\
   {\
      copia_testo_nota(fp, &note_modello);\
      fclose(fp);\
   }\
\
/* Creazione Font per Text */\
   finfo = XLoadQueryFont(display,font);\
   fontList = XmFontListCreate (finfo,XmSTRING_DEFAULT_CHARSET);\
\
/* recupera il nome del modello dal file f01.dat */\
   setta_nome_modello();\
   UxPutLabelString(snome_modello,nome_modello);\
\
/* crea la pixmap NOTO */\
   pixm_noto = crea_pixmap(noto_bits, noto_width, noto_height,\
			   UxGetWidget(autodoc_shell));\
\
/* recupera la lista dei blocchi */\
   get_blocchi_modello( &lista_blocchi, &num_blocchi );\
   ordina_blocchi(lista_blocchi, num_blocchi);\
\
   update_blocks_list(lista_blocchi, num_blocchi, UxGetWidget(slista_blocchi));\
\
   return(rtrn);\

*autodoc_shell.auxdecl: #ifndef DESIGN_TIME\
/*** void blocco_selezionato(w, flag, call_data)\
 ***    Parametri:\
 ***       Widget w:\
 ***       byte flag : indica se VARIABILI o DATI_GEOMETRICI.\
 ***       XmAnyCallbackStruct *call_Data : non utilizzato.\
 ***\
 ***    Descrizione:\
 ***       Callback della del menu EDIT (l'utente ha premuto "Data" o \
 ***       "Variables").\
 ***/\
void blocco_selezionato(w, flag, call_data)\
Widget w;\
byte flag;\
XmAnyCallbackStruct *call_data;\
{\
   int num_sel;\
   XmStringTable items_sel;\
   char *str, *nome_blocco, *descr_blocco;\
   WindowInfoStruct *winfo;\
\
/* verifica che sia stato selezionato un blocco dalla lista */\
   get_something(UxGetWidget(slista_blocchi),XmNselectedItemCount, &num_sel);\
   \
   if ( num_sel == 0 )\
   {\
      fprintf(stderr,"You must select ONE block!\n");\
      return;\
   }\
\
   get_something(UxGetWidget(slista_blocchi),XmNselectedItems,&items_sel);\
\
   str = (char *) extract_string(items_sel[0]);\
   nome_blocco = (char *) XtCalloc(9,sizeof(char));\
   descr_blocco = (char *) XtCalloc(51,sizeof(char));\
   copy_n_car(nome_blocco,str,8);\
   copy_n_car(descr_blocco,str+14,50);\
   printf("blocco selezionato: %s\n", nome_blocco);\
\
   winfo = new_struct_info(flag);\
\
/* Attiva la window delle informazioni aggiuntive */\
   winfo->swindow = create_info_ashell(nome_blocco,descr_blocco,flag,winfo);\
}\
\
/*** Pixel get_colore( color_string )\
 ***    Parametri:\
 ***       char *color_string: terna RGB in formaggio HEX.\
 ***\
 ***    Descrizione\
 ***       Alloca il colore.\
 ***/\
Pixel get_colore( color_string )\
char *color_string;\
{\
   XColor rgb;\
\
   XParseColor(display, cmap, color_string, &rgb);\
   if (XAllocColor( display, cmap, &rgb) != 0)\
      printf("non riesco ad allocare!\n");\
   return(rgb.pixel);\
}\
\
/*** Pixmap crea_pixmap( bits, w, h)\
 ***    Parametri:\
 ***       char *bits : bitmap \
 ***       int w, h : dimensioni della bitmap;\
 ***\
 ***    Descrizione:\
 ***       crea una pixmap dalla bitmap.\
 ***/\
Pixmap crea_pixmap(bits, w, h)\
char *bits;\
short w, h;\
{\
   Pixmap icona;\
   Window  win;\
   int screen_num;\
   Pixel back;\
\
   screen_num = DefaultScreen(display);\
\
   back = get_colore("#4f9f9f");\
\
   icona = XCreatePixmapFromBitmapData( display, \
                        RootWindow(display, screen_num), bits, w, h,\
                        BlackPixel(display,screen_num), back,\
                        DefaultDepth(display,screen_num));\
   return(icona);\
}\
\
/*** WindowInfoStruct *new_struct_info(flag)\
 ***    Parametri:\
 ***       byte flag: tipo della window delle info aggiuntive\
 ***                  (DATI_GEOMETRICI, VARIABILI, VARIABILI_N_F14)\
 ***\
 ***    Descrizione:\
 ***       Aggiunge un item in fondo alla lista winfo_list.\
 ***/\
WindowInfoStruct *new_struct_info(flag)\
byte flag;\
{\
   WindowInfoStruct *winfo, *winfoprec;\
\
   if (winfo_list == NULL)\
   {\
      winfo_list = (WindowInfoStruct *) malloc(sizeof(WindowInfoStruct));\
      winfo = winfo_list;\
   }\
   else\
   {\
      for ( winfo = winfo_list; winfo != NULL ; \
            winfoprec = winfo, winfo = winfo->next );\
      winfoprec->next = (WindowInfoStruct *) malloc(sizeof(WindowInfoStruct));\
      winfo = winfoprec->next;\
   }\
\
   winfo->next = NULL;\
   winfo->flag = flag;\
\
   return(winfo);\
}\
#endif
*autodoc_shell.name: autodoc_shell
*autodoc_shell.x: 90
*autodoc_shell.y: 150
*autodoc_shell.width: 650
*autodoc_shell.height: 450
*autodoc_shell.iconName: "MODEL DOCUMENTATION"
*autodoc_shell.title: "LEGOCAD MODEL DOCUMENTATION"
*autodoc_shell.destroyCallback: {\
printf("MI HANNO DISTRUTTO!!!\n");\
}
*autodoc_shell.background: "#4f9f9f"
*autodoc_shell.defaultFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*mainWindow1.class: mainWindow
*mainWindow1.parent: autodoc_shell
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.unitType: "pixels"
*mainWindow1.x: 0
*mainWindow1.y: 0
*mainWindow1.width: 400
*mainWindow1.height: 500
*mainWindow1.background: "#4f9f9f"

*menu_principale.class: rowColumn
*menu_principale.parent: mainWindow1
*menu_principale.static: true
*menu_principale.name: menu_principale
*menu_principale.rowColumnType: "menu_bar"
*menu_principale.menuAccelerator: "<KeyUp>F10"
*menu_principale.shadowThickness: 2
*menu_principale.spacing: 20
*menu_principale.background: "#4f9f9f"

*menu_file.class: rowColumn
*menu_file.parent: menu_principale
*menu_file.static: true
*menu_file.name: menu_file
*menu_file.rowColumnType: "menu_pulldown"
*menu_file.labelString: "File"
*menu_file.mnemonic: "F"
*menu_file.background: "#4f9f9f"

*menu_cs_print.class: cascadeButton
*menu_cs_print.parent: menu_file
*menu_cs_print.static: true
*menu_cs_print.name: menu_cs_print
*menu_cs_print.labelString: "Print"
*menu_cs_print.subMenuId: "menu_print"
*menu_cs_print.background: "#4f9f9f"
*menu_cs_print.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*menu_pb_save.class: pushButton
*menu_pb_save.parent: menu_file
*menu_pb_save.static: true
*menu_pb_save.name: menu_pb_save
*menu_pb_save.labelString: "Save info"
*menu_pb_save.mnemonic: "S"
*menu_pb_save.background: "#4f9f9f"
*menu_pb_save.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*menu_pb_save.activateCallback: {\
FILE *fp_note;\
\
copia_file(file_tempdati, FILE_INFO_DATI);\
copia_file(file_tempvar, FILE_INFO_VAR);\
\
/* salva le note del modello */\
if ((fp_note = fopen(FILE_NOTE_MODELLO, "w+")) != NULL)\
{\
   if (note_modello == NULL)\
      fputs("", fp_note);\
   else\
      fputs(note_modello, fp_note);\
   fclose(fp_note);\
}\
}

*menu_pb_quit.class: pushButton
*menu_pb_quit.parent: menu_file
*menu_pb_quit.static: true
*menu_pb_quit.name: menu_pb_quit
*menu_pb_quit.labelString: "Quit"
*menu_pb_quit.mnemonic: "Q"
*menu_pb_quit.activateCallback: {\
UxDestroySwidget(autodoc_shell);\
\
unlink(file_tempdati);\
unlink(file_tempvar);\
\
exit(0);\
}
*menu_pb_quit.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*menu_pb_quit.background: "#4f9f9f"

*menu_print.class: rowColumn
*menu_print.parent: menu_file
*menu_print.static: true
*menu_print.name: menu_print
*menu_print.rowColumnType: "menu_pulldown"
*menu_print.background: "#4f9f9f"
*menu_print.labelString: "Print"

*pb_print_data.class: pushButton
*pb_print_data.parent: menu_print
*pb_print_data.static: true
*pb_print_data.name: pb_print_data
*pb_print_data.labelString: "Data doc."
*pb_print_data.mnemonic: "D"
*pb_print_data.background: "#4f9f9f"
*pb_print_data.activateCallback: {\
create_ashell_print(DOC_DATI);\
}
*pb_print_data.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*pb_print_var.class: pushButton
*pb_print_var.parent: menu_print
*pb_print_var.static: true
*pb_print_var.name: pb_print_var
*pb_print_var.labelString: "Variables doc."
*pb_print_var.mnemonic: "V"
*pb_print_var.background: "#4f9f9f"
*pb_print_var.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pb_print_var.activateCallback: {\
create_ashell_print(DOC_VARIABILI);\
}

*pb_print_steady.class: pushButton
*pb_print_steady.parent: menu_print
*pb_print_steady.static: true
*pb_print_steady.name: pb_print_steady
*pb_print_steady.labelString: "Steady state(s) doc."
*pb_print_steady.background: "#4f9f9f"
*pb_print_steady.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pb_print_steady.activateCallback: {\
create_ashell_print(DOC_STAZIONARI);\
}

*menu_edit.class: rowColumn
*menu_edit.parent: menu_principale
*menu_edit.static: true
*menu_edit.name: menu_edit
*menu_edit.rowColumnType: "menu_pulldown"
*menu_edit.labelString: "Edit"
*menu_edit.mnemonic: "E"
*menu_edit.background: "#4f9f9f"

*menu_pb_data.class: pushButton
*menu_pb_data.parent: menu_edit
*menu_pb_data.static: true
*menu_pb_data.name: menu_pb_data
*menu_pb_data.labelString: "Data"
*menu_pb_data.mnemonic: "D"
*menu_pb_data.activateCallback.source: public
*menu_pb_data.activateCallback: blocco_selezionato
*menu_pb_data.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*menu_pb_data.activateCallbackClientData: (XtPointer) DATI_GEOMETRICI
*menu_pb_data.background: "#4f9f9f"

*menu_pb_variables.class: pushButton
*menu_pb_variables.parent: menu_edit
*menu_pb_variables.static: true
*menu_pb_variables.name: menu_pb_variables
*menu_pb_variables.labelString: "Variables"
*menu_pb_variables.mnemonic: "V"
*menu_pb_variables.activateCallback.source: public
*menu_pb_variables.activateCallback: blocco_selezionato
*menu_pb_variables.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*menu_pb_variables.activateCallbackClientData: (XtPointer) VARIABILI
*menu_pb_variables.background: "#4f9f9f"

*menu_config.class: rowColumn
*menu_config.parent: menu_principale
*menu_config.static: true
*menu_config.name: menu_config
*menu_config.rowColumnType: "menu_pulldown"
*menu_config.labelString: "Config"
*menu_config.mnemonic: "C"
*menu_config.background: "#4f9f9f"

*menu_pb_unit.class: pushButton
*menu_pb_unit.parent: menu_config
*menu_pb_unit.static: true
*menu_pb_unit.name: menu_pb_unit
*menu_pb_unit.labelString: "Unit ..."
*menu_pb_unit.mnemonic: "U"
*menu_pb_unit.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*menu_pb_unit.background: "#4f9f9f"
*menu_pb_unit.activateCallback: {\
if ( !open_window_unita )\
   create_window_unita();\
}

*menu_pb_models.class: pushButton
*menu_pb_models.parent: menu_config
*menu_pb_models.static: true
*menu_pb_models.name: menu_pb_models
*menu_pb_models.labelString: "Steady state version"
*menu_pb_models.mnemonic: "M"
*menu_pb_models.background: "#4f9f9f"
*menu_pb_models.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*menu_pb_models.activateCallback: {\
if (!open_window_models)\
   create_window_models();\
}

*menu_pb_printconf.class: pushButton
*menu_pb_printconf.parent: menu_config
*menu_pb_printconf.static: true
*menu_pb_printconf.name: menu_pb_printconf
*menu_pb_printconf.labelString: "Print ..."
*menu_pb_printconf.mnemonic: "P"
*menu_pb_printconf.background: "#4f9f9f"
*menu_pb_printconf.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*menu_pb_printconf.activateCallback: {\
if (!open_print_config)\
   create_dialog_print_config();\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: menu_principale
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "menu_file"
*menu1_top_b1.mnemonic: "F"
*menu1_top_b1.background: "#4f9f9f"

*menu1_top_b2.class: cascadeButton
*menu1_top_b2.parent: menu_principale
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.labelString: "Edit"
*menu1_top_b2.subMenuId: "menu_edit"
*menu1_top_b2.mnemonic: "E"
*menu1_top_b2.background: "#4f9f9f"

*menu1_top_b3.class: cascadeButton
*menu1_top_b3.parent: menu_principale
*menu1_top_b3.static: true
*menu1_top_b3.name: menu1_top_b3
*menu1_top_b3.labelString: "Config"
*menu1_top_b3.subMenuId: "menu_config"
*menu1_top_b3.mnemonic: "C"
*menu1_top_b3.background: "#4f9f9f"

*form_mainWindow1.class: form
*form_mainWindow1.parent: mainWindow1
*form_mainWindow1.static: true
*form_mainWindow1.name: form_mainWindow1
*form_mainWindow1.background: "#4f9f9f"

*pb_note_modello.class: pushButton
*pb_note_modello.parent: form_mainWindow1
*pb_note_modello.static: true
*pb_note_modello.name: pb_note_modello
*pb_note_modello.x: 10
*pb_note_modello.y: 10
*pb_note_modello.width: 70
*pb_note_modello.height: 30
*pb_note_modello.leftAttachment: "attach_none"
*pb_note_modello.leftOffset: 10
*pb_note_modello.topAttachment: "attach_form"
*pb_note_modello.topOffset: 10
*pb_note_modello.labelString: "NOTE"
*pb_note_modello.background: "#4F7F7F"
*pb_note_modello.foreground: "WHITE"
*pb_note_modello.activateCallback: {\
if ( !open_note_modello )\
   create_window_notes(&note_modello, NULL, NULL, &open_note_modello);\
}
*pb_note_modello.rightAttachment: "attach_form"
*pb_note_modello.rightOffset: 10

*labelGadget1.class: labelGadget
*labelGadget1.parent: form_mainWindow1
*labelGadget1.static: true
*labelGadget1.name: labelGadget1
*labelGadget1.x: 90
*labelGadget1.y: 15
*labelGadget1.width: 120
*labelGadget1.height: 20
*labelGadget1.labelString: "MODEL NAME: "
*labelGadget1.leftOffset: 10
*labelGadget1.leftAttachment: "attach_form"
*labelGadget1.alignment: "alignment_beginning"
*labelGadget1.fontList: ""
*labelGadget1.leftWidget: ""
*labelGadget1.topAttachment: "attach_form"
*labelGadget1.topOffset: 15

*snome_modello.class: labelGadget
*snome_modello.parent: form_mainWindow1
*snome_modello.static: true
*snome_modello.name: snome_modello
*snome_modello.x: 230
*snome_modello.y: 10
*snome_modello.width: 410
*snome_modello.height: 20
*snome_modello.labelString: "< ... >"
*snome_modello.leftAttachment: "attach_widget"
*snome_modello.leftOffset: 10
*snome_modello.leftWidget: "labelGadget1"
*snome_modello.rightAttachment: "attach_widget"
*snome_modello.rightOffset: 10
*snome_modello.alignment: "alignment_beginning"
*snome_modello.fontList: ""
*snome_modello.topAttachment: "attach_form"
*snome_modello.topOffset: 15
*snome_modello.rightWidget: "pb_note_modello"

*labelGadget3.class: labelGadget
*labelGadget3.parent: form_mainWindow1
*labelGadget3.static: true
*labelGadget3.name: labelGadget3
*labelGadget3.x: 10
*labelGadget3.y: 60
*labelGadget3.width: 120
*labelGadget3.height: 20
*labelGadget3.leftOffset: 10
*labelGadget3.topAttachment: "attach_widget"
*labelGadget3.topOffset: 20
*labelGadget3.topWidget: "labelGadget1"
*labelGadget3.leftAttachment: "attach_form"
*labelGadget3.alignment: "alignment_beginning"
*labelGadget3.labelString: "BLOCKS LIST:"
*labelGadget3.fontList: ""

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form_mainWindow1
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 50
*scrolledWindow1.y: 180
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.bottomOffset: 10
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.leftOffset: 10
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.rightOffset: 10
*scrolledWindow1.topAttachment: "attach_widget"
*scrolledWindow1.topOffset: 10
*scrolledWindow1.topWidget: "labelGadget3"
*scrolledWindow1.background: "#4f9f9f"

*slista_blocchi.class: scrolledList
*slista_blocchi.parent: scrolledWindow1
*slista_blocchi.static: false
*slista_blocchi.name: slista_blocchi
*slista_blocchi.width: 570
*slista_blocchi.height: 230
*slista_blocchi.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-*"
*slista_blocchi.background: "#4f9f9f"

*opt_menu1.class: rowColumn
*opt_menu1.parent: slista_blocchi
*opt_menu1.static: true
*opt_menu1.name: opt_menu1
*opt_menu1.rowColumnType: "menu_popup"
*opt_menu1.menuAccelerator: "<KeyUp>F4"
*opt_menu1.background: "#4f9f9f"

*opt_labelG1.class: labelGadget
*opt_labelG1.parent: opt_menu1
*opt_labelG1.static: true
*opt_labelG1.name: opt_labelG1
*opt_labelG1.labelString: "EDIT"
*opt_labelG1.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"

*opt_separatorG1.class: separatorGadget
*opt_separatorG1.parent: opt_menu1
*opt_separatorG1.static: true
*opt_separatorG1.name: opt_separatorG1

*opt_pb_data.class: pushButton
*opt_pb_data.parent: opt_menu1
*opt_pb_data.static: true
*opt_pb_data.name: opt_pb_data
*opt_pb_data.labelString: "Data"
*opt_pb_data.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*opt_pb_data.activateCallback.source: public
*opt_pb_data.activateCallback: blocco_selezionato
*opt_pb_data.activateCallbackClientData: (XtPointer) DATI_GEOMETRICI
*opt_pb_data.background: "#4f9f9f"

*opt_pb_variables.class: pushButton
*opt_pb_variables.parent: opt_menu1
*opt_pb_variables.static: true
*opt_pb_variables.name: opt_pb_variables
*opt_pb_variables.labelString: "Variables"
*opt_pb_variables.fontList: "-Adobe-Helvetica-Bold-R-Normal--14-140-75-75-P-82-ISO8859-1"
*opt_pb_variables.activateCallback.source: public
*opt_pb_variables.activateCallback: blocco_selezionato
*opt_pb_variables.activateCallbackClientData: (XtPointer) VARIABILI
*opt_pb_variables.background: "#4f9f9f"

