! UIMX ascii 2.0 key: 6114                                                      

*ashell_print.class: applicationShell
*ashell_print.parent: NO_PARENT
*ashell_print.static: true
*ashell_print.gbldecl: /*\
   modulo ashell_print.i\
   tipo \
   release 1.11\
   data 3/31/95\
   reserved @(#)ashell_print.i	1.11\
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
#define DOCUMENTAZIONE	0\
#define INDICE		1\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE						*/\
/************************************************************************/\
\
extern Display *display;\
\
extern char nome_modello[];\
\
extern char file_tempdati[], file_tempvar[];\
\
extern byte num_varianti;\
extern StructVarianti varianti_modello[];\
\
extern int num_blocchi_modello;\
extern int num_lines_vert, num_lines_horiz;\
\
/************************************************************************/\
/* VARIABILI GLOBALI							*/\
/************************************************************************/
*ashell_print.ispecdecl: int num_pagina_doc, max_righe_doc, max_righe_ind, max_righe;\
int max_page, max_page_doc, max_page_ind;\
int pag_ini;\
long offs_doc;\
char *nome_file_doc, *nome_file_ind, *nome_file_cur;\
FILE *fp_doc;\
char val_opz;
*ashell_print.ispeclist: num_pagina_doc, max_righe_doc, max_righe_ind, max_righe, max_page, max_page_doc, max_page_ind, pag_ini, offs_doc, nome_file_doc, nome_file_ind, nome_file_cur, fp_doc, val_opz
*ashell_print.ispeclist.num_pagina_doc: "int", "%num_pagina_doc%"
*ashell_print.ispeclist.max_righe_doc: "int", "%max_righe_doc%"
*ashell_print.ispeclist.max_righe_ind: "int", "%max_righe_ind%"
*ashell_print.ispeclist.max_righe: "int", "%max_righe%"
*ashell_print.ispeclist.max_page: "int", "%max_page%"
*ashell_print.ispeclist.max_page_doc: "int", "%max_page_doc%"
*ashell_print.ispeclist.max_page_ind: "int", "%max_page_ind%"
*ashell_print.ispeclist.pag_ini: "int", "%pag_ini%"
*ashell_print.ispeclist.offs_doc: "long", "%offs_doc%"
*ashell_print.ispeclist.nome_file_doc: "unsigned char", "*%nome_file_doc%"
*ashell_print.ispeclist.nome_file_ind: "unsigned char", "*%nome_file_ind%"
*ashell_print.ispeclist.nome_file_cur: "unsigned char", "*%nome_file_cur%"
*ashell_print.ispeclist.fp_doc: "FILE", "*%fp_doc%"
*ashell_print.ispeclist.val_opz: "unsigned char", "%val_opz%"
*ashell_print.funcdecl: swidget create_ashell_print(tipo_doc)\
byte tipo_doc;\

*ashell_print.funcname: create_ashell_print
*ashell_print.funcdef: "swidget", "<create_ashell_print>(%)"
*ashell_print.argdecl: byte tipo_doc;
*ashell_print.arglist: tipo_doc
*ashell_print.arglist.tipo_doc: "byte", "%tipo_doc%"
*ashell_print.icode: int i;\
Boolean genera = False;\
XmString cstring;\
char *str, buf[20];\
\
/* controllo esistenza dei file di documentazione */\
/* Se tali file esistono viene effettuato il controllo sulle date di ultima */\
/* modifica */\
switch (tipo_doc)\
{\
   case DOC_DATI:\
        if (confronta_date(DOC_DATI_MODELLO,FILE_INFO_DATI) <= 0 ||\
            confronta_date(DOC_DATI_MODELLO,"f14.dat") <= 0)\
           crea_docdati(&max_page_doc, &max_page_ind);\
        else\
        {\
           max_page_ind = conta_pagine_doc(IND_DATI_MODELLO, num_lines_vert);\
           max_page_doc = conta_pagine_doc(DOC_DATI_MODELLO, num_lines_vert) +\
                          max_page_ind;\
        }\
\
        nome_file_doc = DOC_DATI_MODELLO;\
	max_righe_doc = num_lines_vert;\
        nome_file_ind = IND_DATI_MODELLO;\
	max_righe_ind = num_lines_vert;\
	break;\
\
   case DOC_VARIABILI:\
        if (confronta_date(DOC_VAR_MODELLO,FILE_INFO_VAR) <= 0 ||\
            confronta_date(DOC_VAR_MODELLO,"f01.dat") <= 0)\
	   crea_docvar(&max_page_doc, &max_page_ind);\
        else\
        {\
           max_page_ind = conta_pagine_doc(IND_VAR_MODELLO, num_lines_vert);\
           max_page_doc = conta_pagine_doc(DOC_VAR_MODELLO, num_lines_horiz)+\
                          max_page_ind;\
\
        }\
\
        nome_file_doc = DOC_VAR_MODELLO;\
	max_righe_doc = num_lines_horiz;\
        nome_file_ind = IND_VAR_MODELLO;\
	max_righe_ind = num_lines_vert;\
	break;\
\
   case DOC_STAZIONARI:\
        for (i=0, genera = False ; i<num_varianti ; i++ )\
           if (varianti_modello[i].abilitato)\
              if (confronta_date(DOC_SSTATE_MODELLO,\
                                 varianti_modello[i].percorso) <= 0)\
              {\
                 genera = True;\
                 break;\
              }\
\
        if (genera)\
           crea_sstate_doc(&max_page_doc);\
        else\
           max_page_doc = conta_pagine_doc(DOC_SSTATE_MODELLO, num_lines_horiz);\
\
        nome_file_doc = DOC_SSTATE_MODELLO;\
        max_righe_doc = num_lines_horiz;\
        nome_file_ind = NULL;\
	max_righe_ind = 0;\
        \
	break;\
}
*ashell_print.fcode: if ((fp_doc = fopen(nome_file_doc,"r")) == NULL)\
{\
   crea_errorDialog("error while opening documentation file.\n");\
   return;\
}\
\
if (tipo_doc == DOC_STAZIONARI)\
   pag_ini = 1;\
else\
   pag_ini = max_page_ind+1;\
num_pagina_doc = pag_ini;\
max_page = max_page_doc;\
max_righe = max_righe_doc;\
offs_doc = 0L;\
nome_file_cur = nome_file_doc;\
val_opz = DOCUMENTAZIONE;\
\
str = leggi_pagina(fp_doc, max_righe);\
\
XmTextSetString(UxGetWidget(text_documentation), str);\
free(str);\
\
sprintf(buf, "%d", pag_ini);\
set_label(UxGetWidget(label_page_no), buf);\
\
sprintf(buf, "%d", max_page);\
set_label(UxGetWidget(label_page_max), buf);\
\
if (tipo_doc == DOC_STAZIONARI)\
   XtVaSetValues(UxGetWidget(menu2_index), XmNsensitive, False, NULL);\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*ashell_print.auxdecl:
*ashell_print.name: ashell_print
*ashell_print.x: 210
*ashell_print.y: 290
*ashell_print.width: 710
*ashell_print.height: 450
*ashell_print.background: "#4f9f9f"
*ashell_print.iconName: "PRINT PREVIEW"
*ashell_print.title: "PRINT PREVIEW"

*form5.class: form
*form5.parent: ashell_print
*form5.static: true
*form5.name: form5
*form5.resizePolicy: "resize_none"
*form5.unitType: "pixels"
*form5.x: 30
*form5.y: 30
*form5.width: 660
*form5.height: 360
*form5.background: "#4f9f9f"
*form5.labelFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*pushButton7.class: pushButton
*pushButton7.parent: form5
*pushButton7.static: true
*pushButton7.name: pushButton7
*pushButton7.x: 440
*pushButton7.y: 410
*pushButton7.width: 120
*pushButton7.height: 30
*pushButton7.background: "#4f9f9f"
*pushButton7.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushButton7.labelString: "Cancel"
*pushButton7.bottomAttachment: "attach_form"
*pushButton7.bottomOffset: 10
*pushButton7.leftAttachment: "attach_position"
*pushButton7.leftOffset: 0
*pushButton7.leftPosition: 60
*pushButton7.rightAttachment: "attach_form"
*pushButton7.rightOffset: 20
*pushButton7.topAttachment: "attach_none"
*pushButton7.topOffset: 0
*pushButton7.activateCallback: {\
if (fp_doc != NULL)\
   fclose(fp_doc);\
\
UxDestroySwidget(ashell_print);\
}

*pushb_stampa.class: pushButton
*pushb_stampa.parent: form5
*pushb_stampa.static: true
*pushb_stampa.name: pushb_stampa
*pushb_stampa.x: 120
*pushb_stampa.y: 420
*pushb_stampa.width: 120
*pushb_stampa.height: 30
*pushb_stampa.background: "#4f9f9f"
*pushb_stampa.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushb_stampa.labelString: "Print"
*pushb_stampa.bottomAttachment: "attach_form"
*pushb_stampa.bottomOffset: 10
*pushb_stampa.leftAttachment: "attach_form"
*pushb_stampa.leftOffset: 20
*pushb_stampa.rightAttachment: "attach_position"
*pushb_stampa.rightPosition: 40
*pushb_stampa.topAttachment: "attach_none"
*pushb_stampa.topOffset: 0
*pushb_stampa.activateCallback: {\
int lung_riga;\
\
#ifndef DESIGN_TIME\
if (tipo_doc == DOC_STAZIONARI || (tipo_doc == DOC_VARIABILI && \
                                   val_opz == DOCUMENTAZIONE) )\
   lung_riga = MAX_COL_HOR;\
else\
   lung_riga = MAX_COL_VER;\
#endif\
create_bb_conferma_print(nome_file_cur, num_pagina_doc, max_righe, lung_riga,\
                         pag_ini-1);\
}

*rowColumn2.class: rowColumn
*rowColumn2.parent: form5
*rowColumn2.static: true
*rowColumn2.name: rowColumn2
*rowColumn2.x: 20
*rowColumn2.y: 30
*rowColumn2.width: 150
*rowColumn2.height: 40
*rowColumn2.background: "#4f9f9f"
*rowColumn2.leftOffset: 10
*rowColumn2.topOffset: 10
*rowColumn2.topAttachment: "attach_form"

*menu2.class: rowColumn
*menu2.parent: rowColumn2
*menu2.static: true
*menu2.name: menu2
*menu2.rowColumnType: "menu_option"
*menu2.subMenuId: "menu_opt_print"
*menu2.background: "#4f9f9f"

*menu_opt_print.class: rowColumn
*menu_opt_print.parent: menu2
*menu_opt_print.static: true
*menu_opt_print.name: menu_opt_print
*menu_opt_print.rowColumnType: "menu_pulldown"
*menu_opt_print.background: "#4f9f9f"
*menu_opt_print.menuHistory: "menu2_documentation"

*menu2_index.class: pushButton
*menu2_index.parent: menu_opt_print
*menu2_index.static: true
*menu2_index.name: menu2_index
*menu2_index.labelString: "INDEX"
*menu2_index.background: "#4f9f9f"
*menu2_index.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*menu2_index.activateCallback: {\
char buf[20], *str;\
XmString cstring;\
\
if ((fp_doc = fopen(nome_file_ind,"r")) == NULL)\
   crea_errorDialog("error while opening documentation file");\
\
\
max_page = max_page_ind;\
max_righe = max_righe_ind;\
offs_doc = 0L;\
nome_file_cur = nome_file_ind;\
val_opz = INDICE;\
pag_ini = 1;\
num_pagina_doc = pag_ini;\
\
str = leggi_pagina(fp_doc, max_righe);\
\
XmTextSetString(UxGetWidget(text_documentation), str);\
free(str);\
\
sprintf(buf, "%d", pag_ini);\
set_label(UxGetWidget(label_page_no),buf);\
\
sprintf(buf, "%d", max_page);\
set_label(UxGetWidget(label_page_max), buf);\
}

*menu2_documentation.class: pushButton
*menu2_documentation.parent: menu_opt_print
*menu2_documentation.static: true
*menu2_documentation.name: menu2_documentation
*menu2_documentation.labelString: "DOCUMENTATION"
*menu2_documentation.background: "#4f9f9f"
*menu2_documentation.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*menu2_documentation.activateCallback: {\
char buf[20], *str;\
XmString cstring;\
\
if (fp_doc != NULL)\
   fclose (fp_doc);\
\
if ((fp_doc = fopen(nome_file_doc,"r")) == NULL)\
   crea_errorDialog("error while opening index documentation file");\
\
max_page = max_page_doc;\
max_righe = max_righe_doc;\
offs_doc = 0L;\
nome_file_cur = nome_file_doc;\
val_opz = DOCUMENTAZIONE;\
\
if (tipo_doc == DOC_STAZIONARI)\
   pag_ini = 1;\
else\
   pag_ini = max_page_ind+1;\
\
num_pagina_doc = pag_ini;\
\
str = leggi_pagina(fp_doc, max_righe);\
\
XmTextSetString(UxGetWidget(text_documentation), str);\
free(str);\
\
sprintf(buf, "%d", pag_ini);\
set_label(UxGetWidget(label_page_no), buf);\
\
sprintf(buf, "%d", max_page);\
set_label(UxGetWidget(label_page_max), buf);\
}

*separatorGadget7.class: separatorGadget
*separatorGadget7.parent: form5
*separatorGadget7.static: true
*separatorGadget7.name: separatorGadget7
*separatorGadget7.x: 10
*separatorGadget7.y: 400
*separatorGadget7.width: 690
*separatorGadget7.height: 10
*separatorGadget7.bottomAttachment: "attach_widget"
*separatorGadget7.bottomOffset: 10
*separatorGadget7.bottomWidget: "pushButton7"
*separatorGadget7.leftAttachment: "attach_form"
*separatorGadget7.leftOffset: 10
*separatorGadget7.rightAttachment: "attach_form"
*separatorGadget7.rightOffset: 10
*separatorGadget7.topAttachment: "attach_none"
*separatorGadget7.topOffset: 0

*pushButton10.class: pushButton
*pushButton10.parent: form5
*pushButton10.static: true
*pushButton10.name: pushButton10
*pushButton10.x: 620
*pushButton10.y: 10
*pushButton10.width: 80
*pushButton10.height: 34
*pushButton10.background: "#4f9f9f"
*pushButton10.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushButton10.labelString: "Go to..."
*pushButton10.rightAttachment: "attach_form"
*pushButton10.rightOffset: 10
*pushButton10.activateCallback: {\
\
create_bb_cambia_pag(fp_doc, max_righe, text_documentation, label_page_no,\
                             &offs_doc, &num_pagina_doc, pag_ini-1);\
                             \
}

*frame1.class: frame
*frame1.parent: form5
*frame1.static: true
*frame1.name: frame1
*frame1.x: 564
*frame1.y: 8
*frame1.width: 50
*frame1.height: 34
*frame1.background: "#4f9f9f"
*frame1.rightAttachment: "attach_widget"
*frame1.rightOffset: 10
*frame1.rightWidget: "pushButton10"
*frame1.topAttachment: "attach_form"
*frame1.topOffset: 10

*label_page_max.class: labelGadget
*label_page_max.parent: frame1
*label_page_max.static: true
*label_page_max.name: label_page_max
*label_page_max.x: 650
*label_page_max.y: 40
*label_page_max.width: 50
*label_page_max.height: 30
*label_page_max.labelString: "1"
*label_page_max.recomputeSize: "false"

*frame2.class: frame
*frame2.parent: form5
*frame2.static: true
*frame2.name: frame2
*frame2.x: 496
*frame2.y: 8
*frame2.width: 50
*frame2.height: 34
*frame2.background: "#4f9f9f"
*frame2.leftAttachment: "attach_none"
*frame2.leftOffset: 0
*frame2.rightAttachment: "attach_widget"
*frame2.rightOffset: 10
*frame2.topOffset: 10
*frame2.topAttachment: "attach_form"
*frame2.rightWidget: "frame1"

*label_page_no.class: labelGadget
*label_page_no.parent: frame2
*label_page_no.static: true
*label_page_no.name: label_page_no
*label_page_no.x: 650
*label_page_no.y: 40
*label_page_no.width: 50
*label_page_no.height: 30
*label_page_no.labelString: "1"
*label_page_no.recomputeSize: "false"

*labelGadget5.class: labelGadget
*labelGadget5.parent: form5
*labelGadget5.static: true
*labelGadget5.name: labelGadget5
*labelGadget5.x: 430
*labelGadget5.y: 8
*labelGadget5.width: 56
*labelGadget5.height: 34
*labelGadget5.labelString: "Page:"
*labelGadget5.leftAttachment: "attach_none"
*labelGadget5.leftOffset: 0
*labelGadget5.rightAttachment: "attach_widget"
*labelGadget5.rightOffset: 10
*labelGadget5.rightWidget: "frame2"
*labelGadget5.topOffset: 10
*labelGadget5.topAttachment: "attach_form"

*arrow_next_page.class: arrowButton
*arrow_next_page.parent: form5
*arrow_next_page.static: true
*arrow_next_page.name: arrow_next_page
*arrow_next_page.x: 370
*arrow_next_page.y: 8
*arrow_next_page.width: 40
*arrow_next_page.height: 34
*arrow_next_page.background: "#4f9f9f"
*arrow_next_page.arrowDirection: "arrow_down"
*arrow_next_page.leftAttachment: "attach_none"
*arrow_next_page.rightAttachment: "attach_widget"
*arrow_next_page.rightOffset: 20
*arrow_next_page.rightWidget: "labelGadget5"
*arrow_next_page.topAttachment: "attach_form"
*arrow_next_page.topOffset: 10
*arrow_next_page.activateCallback: {\
char *str, strnum[10];\
XmString cstring;\
long offs;\
\
if (num_pagina_doc >= max_page)\
   return;\
\
if ((offs = pagina_succ(fp_doc, max_righe, offs_doc)) == -1)\
   return;\
\
offs_doc = offs;\
\
str = leggi_pagina(fp_doc, max_righe);\
XmTextSetString(UxGetWidget(text_documentation), str);\
free(str);\
\
num_pagina_doc++;\
\
sprintf(strnum, "%4d", num_pagina_doc);\
cstring=CREATE_CSTRING(strnum);\
XtVaSetValues(UxGetWidget(label_page_no), XmNlabelString, cstring, NULL);\
XmStringFree(cstring);\
}

*arrow_prev_page.class: arrowButton
*arrow_prev_page.parent: form5
*arrow_prev_page.static: true
*arrow_prev_page.name: arrow_prev_page
*arrow_prev_page.x: 320
*arrow_prev_page.y: 8
*arrow_prev_page.width: 40
*arrow_prev_page.height: 34
*arrow_prev_page.background: "#4f9f9f"
*arrow_prev_page.leftAttachment: "attach_none"
*arrow_prev_page.rightAttachment: "attach_widget"
*arrow_prev_page.rightOffset: 10
*arrow_prev_page.rightWidget: "arrow_next_page"
*arrow_prev_page.topAttachment: "attach_form"
*arrow_prev_page.topOffset: 10
*arrow_prev_page.activateCallback: {\
char *str, strnum[10];\
XmString cstring;\
\
if (num_pagina_doc <= pag_ini)\
   return;\
\
offs_doc = pagina_prec(fp_doc, max_righe, offs_doc);\
\
str = leggi_pagina(fp_doc, max_righe);\
XmTextSetString(UxGetWidget(text_documentation), str);\
free(str);\
\
num_pagina_doc--;\
sprintf(strnum, "%4d", num_pagina_doc);\
cstring=CREATE_CSTRING(strnum);\
XtVaSetValues(UxGetWidget(label_page_no), XmNlabelString, cstring, NULL);\
XmStringFree(cstring);\
}

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.parent: form5
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.x: 10
*scrolledWindow5.y: 80
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0
*scrolledWindow5.background: "#4f9f9f"
*scrolledWindow5.leftAttachment: "attach_form"
*scrolledWindow5.leftOffset: 10
*scrolledWindow5.rightAttachment: "attach_form"
*scrolledWindow5.rightOffset: 10
*scrolledWindow5.topAttachment: "attach_widget"
*scrolledWindow5.topOffset: 10
*scrolledWindow5.topWidget: "arrow_next_page"
*scrolledWindow5.bottomAttachment: "attach_widget"
*scrolledWindow5.bottomOffset: 10
*scrolledWindow5.bottomWidget: "separatorGadget7"
*scrolledWindow5.scrollBarPlacement: "bottom_right"

*text_documentation.class: scrolledText
*text_documentation.parent: scrolledWindow5
*text_documentation.static: true
*text_documentation.name: text_documentation
*text_documentation.width: 690
*text_documentation.height: 300
*text_documentation.background: "#4f9f9f"
*text_documentation.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*text_documentation.editMode: "multi_line_edit"
*text_documentation.editable: "false"

