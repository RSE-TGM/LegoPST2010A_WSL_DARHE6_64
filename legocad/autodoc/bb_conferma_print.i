! UIMX ascii 2.0 key: 879                                                       

*bb_conferma_print.class: bulletinBoardDialog
*bb_conferma_print.parent: NO_PARENT
*bb_conferma_print.defaultShell: topLevelShell
*bb_conferma_print.static: true
*bb_conferma_print.gbldecl: /*\
   modulo bb_conferma_print.i\
   tipo \
   release 1.11\
   data 3/31/95\
   reserved @(#)bb_conferma_print.i	1.11\
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
#define TOGGLE_ALL_PAGES	0\
#define TOGGLE_DA_PAGE_A_PAGE	1\
#define TOGGLE_CURRENT_PAGE	2
*bb_conferma_print.ispecdecl: char toggle_selezionato;\
swidget swdg_toggle;
*bb_conferma_print.ispeclist: toggle_selezionato, swdg_toggle
*bb_conferma_print.ispeclist.toggle_selezionato: "unsigned char", "%toggle_selezionato%"
*bb_conferma_print.ispeclist.swdg_toggle: "swidget", "%swdg_toggle%"
*bb_conferma_print.funcdecl: swidget create_bb_conferma_print(nome_file, current_page, linee_per_pag,\
                                 len_riga, pag_iniz)\
char *nome_file;\
int current_page, linee_per_pag, len_riga, pag_iniz;\

*bb_conferma_print.funcname: create_bb_conferma_print
*bb_conferma_print.funcdef: "swidget", "<create_bb_conferma_print>(%)"
*bb_conferma_print.argdecl: unsigned char *nome_file;\
int current_page;\
int linee_per_pag;\
int len_riga;\
int pag_iniz;
*bb_conferma_print.arglist: nome_file, current_page, linee_per_pag, len_riga, pag_iniz
*bb_conferma_print.arglist.nome_file: "unsigned char", "*%nome_file%"
*bb_conferma_print.arglist.current_page: "int", "%current_page%"
*bb_conferma_print.arglist.linee_per_pag: "int", "%linee_per_pag%"
*bb_conferma_print.arglist.len_riga: "int", "%len_riga%"
*bb_conferma_print.arglist.pag_iniz: "int", "%pag_iniz%"
*bb_conferma_print.icode:
*bb_conferma_print.fcode: toggle_selezionato = TOGGLE_ALL_PAGES;\
swdg_toggle = toggle_all;\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*bb_conferma_print.auxdecl:
*bb_conferma_print.name: bb_conferma_print
*bb_conferma_print.unitType: "pixels"
*bb_conferma_print.x: 465
*bb_conferma_print.y: 340
*bb_conferma_print.width: 431
*bb_conferma_print.height: 286
*bb_conferma_print.dialogTitle: "PRINT DOCUMENTATION"
*bb_conferma_print.background: "#4f9f9f"
*bb_conferma_print.buttonFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*bb_conferma_print.labelFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*bb_conferma_print.dialogStyle: "dialog_full_application_modal"
*bb_conferma_print.noResize: "true"
*bb_conferma_print.autoUnmanage: "false"

*labelGadget7.class: labelGadget
*labelGadget7.parent: bb_conferma_print
*labelGadget7.static: true
*labelGadget7.name: labelGadget7
*labelGadget7.x: 20
*labelGadget7.y: 10
*labelGadget7.width: 150
*labelGadget7.height: 30
*labelGadget7.labelString: "SELECT:"
*labelGadget7.alignment: "alignment_beginning"

*toggle_all.class: toggleButton
*toggle_all.parent: bb_conferma_print
*toggle_all.static: true
*toggle_all.name: toggle_all
*toggle_all.x: 70
*toggle_all.y: 60
*toggle_all.width: 20
*toggle_all.height: 34
*toggle_all.background: "#4f9f9f"
*toggle_all.set: "true"
*toggle_all.valueChangedCallback: {\
if (toggle_selezionato == TOGGLE_ALL_PAGES)\
   XmToggleButtonSetState(UxGetWidget(toggle_all), True, False);\
else\
   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);\
toggle_selezionato = TOGGLE_ALL_PAGES;\
swdg_toggle = toggle_all;\
}

*toggle_da_a.class: toggleButton
*toggle_da_a.parent: bb_conferma_print
*toggle_da_a.static: true
*toggle_da_a.name: toggle_da_a
*toggle_da_a.x: 70
*toggle_da_a.y: 100
*toggle_da_a.width: 20
*toggle_da_a.height: 34
*toggle_da_a.background: "#4f9f9f"
*toggle_da_a.valueChangedCallback: {\
if (toggle_selezionato == TOGGLE_DA_PAGE_A_PAGE)\
   XmToggleButtonSetState(UxGetWidget(toggle_da_a), True, False);\
else\
   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);\
toggle_selezionato = TOGGLE_DA_PAGE_A_PAGE;\
swdg_toggle = toggle_da_a;\
\
}

*toggle_current.class: toggleButton
*toggle_current.parent: bb_conferma_print
*toggle_current.static: true
*toggle_current.name: toggle_current
*toggle_current.x: 70
*toggle_current.y: 140
*toggle_current.width: 20
*toggle_current.height: 34
*toggle_current.background: "#4f9f9f"
*toggle_current.valueChangedCallback: {\
if (toggle_selezionato == TOGGLE_CURRENT_PAGE)\
   XmToggleButtonSetState(UxGetWidget(toggle_current), True, False);\
else\
   XmToggleButtonSetState(UxGetWidget(swdg_toggle), False, False);\
toggle_selezionato = TOGGLE_CURRENT_PAGE;\
swdg_toggle = toggle_current;\
\
}

*labelGadget8.class: labelGadget
*labelGadget8.parent: bb_conferma_print
*labelGadget8.static: true
*labelGadget8.name: labelGadget8
*labelGadget8.x: 110
*labelGadget8.y: 60
*labelGadget8.width: 130
*labelGadget8.height: 34
*labelGadget8.alignment: "alignment_beginning"
*labelGadget8.labelString: "All Pages"

*labelGadget9.class: labelGadget
*labelGadget9.parent: bb_conferma_print
*labelGadget9.static: true
*labelGadget9.name: labelGadget9
*labelGadget9.x: 110
*labelGadget9.y: 100
*labelGadget9.width: 90
*labelGadget9.height: 34
*labelGadget9.alignment: "alignment_beginning"
*labelGadget9.labelString: "From Page:"

*labelGadget10.class: labelGadget
*labelGadget10.parent: bb_conferma_print
*labelGadget10.static: true
*labelGadget10.name: labelGadget10
*labelGadget10.x: 280
*labelGadget10.y: 100
*labelGadget10.width: 40
*labelGadget10.height: 34
*labelGadget10.alignment: "alignment_beginning"
*labelGadget10.labelString: "to :"

*labelGadget11.class: labelGadget
*labelGadget11.parent: bb_conferma_print
*labelGadget11.static: true
*labelGadget11.name: labelGadget11
*labelGadget11.x: 110
*labelGadget11.y: 140
*labelGadget11.width: 100
*labelGadget11.height: 34
*labelGadget11.alignment: "alignment_beginning"
*labelGadget11.labelString: "Current Page"

*separatorGadget8.class: separatorGadget
*separatorGadget8.parent: bb_conferma_print
*separatorGadget8.static: true
*separatorGadget8.name: separatorGadget8
*separatorGadget8.x: 10
*separatorGadget8.y: 180
*separatorGadget8.width: 410
*separatorGadget8.height: 10

*pushb_print_ok.class: pushButton
*pushb_print_ok.parent: bb_conferma_print
*pushb_print_ok.static: true
*pushb_print_ok.name: pushb_print_ok
*pushb_print_ok.x: 10
*pushb_print_ok.y: 210
*pushb_print_ok.width: 160
*pushb_print_ok.height: 30
*pushb_print_ok.background: "#4f9f9f"
*pushb_print_ok.labelString: "Ok"
*pushb_print_ok.activateCallback: {\
FILE *fp, *fp_temp;\
char *str, file_temp[256], comando[128];\
Boolean flag_stampa = True;\
int i, pag1, pag2;\
\
/***\
tmpnam(file_temp);\
***/\
strcpy(file_temp, "file_stampa");\
\
if ((fp_temp = fopen(file_temp, "w+")) == NULL)\
{\
    crea_errorDialog("Can't open temporary file for printing.\n");\
    XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));\
    return;\
}\
\
switch (toggle_selezionato)\
{\
    case TOGGLE_ALL_PAGES:\
       copia_file(nome_file, file_temp);\
       break;\
\
    case TOGGLE_DA_PAGE_A_PAGE:\
       if ((fp = fopen(nome_file, "r")) == NULL)\
       {\
          crea_errorDialog("Can't open file for printing.");\
          flag_stampa = False;\
          break;\
       }\
\
       str = XmTextGetString(UxGetWidget(text_da));\
       if (!IsNumeric(str) || Empty(str))\
       {\
          crea_errorDialog("Incorrect page number!\n");\
          flag_stampa = False;\
          break;\
       }\
       sscanf(str, "%d", &pag1);\
       XtFree(str);\
\
       str = XmTextGetString(UxGetWidget(text_a));\
       if (!IsNumeric(str) || Empty(str))\
       {\
          crea_errorDialog("Incorrect page number!\n");\
          flag_stampa = False;\
          break;\
       }\
       sscanf(str, "%d", &pag2);\
       XtFree(str);\
\
       if (vai_alla_pagina(fp, linee_per_pag, pag1-pag_iniz) == -1)\
          break;\
\
       for ( i=pag1 ; i<=pag2 ; i++ )\
          if ((str = leggi_pagina(fp, linee_per_pag)) == NULL)\
             break;\
          else\
          {\
             fputs(str, fp_temp);\
             free(str);\
          }\
\
       fclose(fp);\
       break;\
\
    case TOGGLE_CURRENT_PAGE:\
       if ((fp = fopen(nome_file, "r")) == NULL)\
       {\
          crea_errorDialog("Can't open file for printing.");\
          flag_stampa = False;\
       }\
\
       if (vai_alla_pagina(fp, linee_per_pag, current_page-pag_iniz) == -1)\
          break;\
\
       if ((str = leggi_pagina(fp, linee_per_pag)) != NULL)\
       {\
             fputs(str, fp_temp);\
             free(str);\
       }\
\
       fclose(fp);\
       break;\
}\
\
fclose(fp_temp);\
\
#ifdef OSF1 \
   sprintf(comando, "lpr -w%d -z%d -Oz%s  %s", len_riga, linee_per_pag,\
                          (len_riga > 80) ? "landscape" : "portrait",file_temp);\
#else\
   sprintf(comando, "qprt -w%d -l%d -z%s -r %s", len_riga, linee_per_pag,\
                          (len_riga > 80) ? "1" : "0", file_temp);\
#endif\
\
printf("comando di stampa: %s\n", comando);\
\
system(comando);\
\
\
XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));\
}

*pushButton9.class: pushButton
*pushButton9.parent: bb_conferma_print
*pushButton9.static: true
*pushButton9.name: pushButton9
*pushButton9.x: 260
*pushButton9.y: 210
*pushButton9.width: 160
*pushButton9.height: 30
*pushButton9.background: "#4f9f9f"
*pushButton9.labelString: "Cancel"
*pushButton9.activateCallback: {\
XtDestroyWidget(XtParent(UxGetWidget(bb_conferma_print)));\
}

*text_da.class: text
*text_da.parent: bb_conferma_print
*text_da.static: true
*text_da.name: text_da
*text_da.x: 210
*text_da.y: 100
*text_da.width: 60
*text_da.height: 34
*text_da.background: "#4f9f9f"

*text_a.class: text
*text_a.parent: bb_conferma_print
*text_a.static: true
*text_a.name: text_a
*text_a.x: 320
*text_a.y: 100
*text_a.width: 60
*text_a.height: 34
*text_a.background: "#4f9f9f"

*separatorGadget9.class: separatorGadget
*separatorGadget9.parent: bb_conferma_print
*separatorGadget9.static: true
*separatorGadget9.name: separatorGadget9
*separatorGadget9.x: 10
*separatorGadget9.y: 40
*separatorGadget9.width: 410
*separatorGadget9.height: 10

