! UIMX ascii 2.0 key: 3261                                                      

*window_notes.class: applicationShell
*window_notes.parent: NO_PARENT
*window_notes.static: true
*window_notes.gbldecl: /*\
   modulo window_notes.i\
   tipo \
   release 1.12\
   data 3/31/95\
   reserved @(#)window_notes.i	1.12\
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
extern char nome_modello[];
*window_notes.ispecdecl:
*window_notes.funcdecl: swidget create_window_notes(testo, nome_blocco_note, nota,flag_win_note)\
char **testo;\
char *nome_blocco_note;  /* nome del blocco */\
char *nota; /* nota del blocco. Se la nota e' relativa al blocco */\
	       /* in generale tale valore deve esse NULL */\
Boolean *flag_win_note;\

*window_notes.funcname: create_window_notes
*window_notes.funcdef: "swidget", "<create_window_notes>(%)"
*window_notes.argdecl: unsigned char **testo;\
unsigned char *nome_blocco_note;\
unsigned char *nota;\
Boolean *flag_win_note;
*window_notes.arglist: testo, nome_blocco_note, nota, flag_win_note
*window_notes.arglist.testo: "unsigned char", "**%testo%"
*window_notes.arglist.nome_blocco_note: "unsigned char", "*%nome_blocco_note%"
*window_notes.arglist.nota: "unsigned char", "*%nota%"
*window_notes.arglist.flag_win_note: "Boolean", "*%flag_win_note%"
*window_notes.icode: printf("nome del blocco: %s\n", nome_blocco_note);
*window_notes.fcode: if (nome_blocco_note == NULL)\
{\
   UxPutLabelString(label1,"Note of the model:");\
   UxPutLabelString(lb_nome_blocco, nome_modello);\
   UxDestroySwidget(lb_initial);\
}\
else\
{\
   UxPutLabelString(label1,"Note of the block");\
   UxPutLabelString(lb_nome_blocco, nome_blocco_note);\
\
   if (nota == NULL)\
   {\
      UxDestroySwidget(label5);\
      UxDestroySwidget(lb_initial);\
   }\
   else\
      UxPutLabelString(lb_initial, nota);\
}\
\
if (*testo != NULL)\
   XmTextSetString(UxGetWidget(text_note), *testo);\
\
*flag_win_note = True;\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*window_notes.auxdecl: /*** void conferma_note_inserite(testo_nota, chiudi)\
 ***    Parametri:\
 ***      Boolean chiudi : indica se la window deve essere chiusa\
 ***\
 ***    Descrizione:\
 ***      conferma l'inserimento o la modifica della nota\
 ***/\
void conferma_note_inserite(testo_nota, chiudi)\
char **testo_nota;\
Boolean chiudi;\
{\
   if (*testo_nota != NULL)\
      XtFree(*testo_nota);\
\
   *testo_nota = XmTextGetString(UxGetWidget(text_note));\
\
   if (chiudi)\
   {\
#ifndef DESIGN_TIME\
      *flag_win_note = False;\
#endif\
      UxDestroySwidget(window_notes);\
   }\
}
*window_notes.name: window_notes
*window_notes.x: 240
*window_notes.y: 230
*window_notes.width: 500
*window_notes.height: 400
*window_notes.defaultFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*window_notes.title: "NOTES"
*window_notes.background: "#4f9f9f"

*form3.class: form
*form3.parent: window_notes
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.unitType: "pixels"
*form3.x: 10
*form3.y: 30
*form3.width: 480
*form3.height: 330
*form3.background: "#4f9f9f"

*label1.class: label
*label1.parent: form3
*label1.static: true
*label1.name: label1
*label1.x: 10
*label1.y: 20
*label1.width: 150
*label1.height: 20
*label1.alignment: "alignment_beginning"
*label1.labelString: "Notes of the block:"
*label1.leftAttachment: "attach_form"
*label1.leftOffset: 10
*label1.topAttachment: "attach_form"
*label1.topOffset: 20
*label1.background: "#4f9f9f"

*lb_nome_blocco.class: label
*lb_nome_blocco.parent: form3
*lb_nome_blocco.static: true
*lb_nome_blocco.name: lb_nome_blocco
*lb_nome_blocco.x: 170
*lb_nome_blocco.y: 20
*lb_nome_blocco.width: 90
*lb_nome_blocco.height: 20
*lb_nome_blocco.alignment: "alignment_beginning"
*lb_nome_blocco.labelString: ""
*lb_nome_blocco.leftAttachment: "attach_widget"
*lb_nome_blocco.leftOffset: 10
*lb_nome_blocco.leftWidget: "label1"
*lb_nome_blocco.topAttachment: "attach_form"
*lb_nome_blocco.topOffset: 20
*lb_nome_blocco.background: "#4f9f9f"

*label5.class: label
*label5.parent: form3
*label5.static: true
*label5.name: label5
*label5.x: 290
*label5.y: 20
*label5.width: 80
*label5.height: 20
*label5.labelString: "note:"
*label5.alignment: "alignment_beginning"
*label5.leftAttachment: "attach_widget"
*label5.leftOffset: 20
*label5.leftWidget: "lb_nome_blocco"
*label5.topAttachment: "attach_form"
*label5.topOffset: 20
*label5.background: "#4f9f9f"

*lb_initial.class: label
*lb_initial.parent: form3
*lb_initial.static: true
*lb_initial.name: lb_initial
*lb_initial.x: 390
*lb_initial.y: 20
*lb_initial.width: 100
*lb_initial.height: 20
*lb_initial.alignment: "alignment_beginning"
*lb_initial.labelString: ""
*lb_initial.rightAttachment: "attach_form"
*lb_initial.rightOffset: 10
*lb_initial.topAttachment: "attach_form"
*lb_initial.topOffset: 20
*lb_initial.leftAttachment: "attach_widget"
*lb_initial.leftOffset: 10
*lb_initial.leftWidget: "label5"
*lb_initial.background: "#4f9f9f"

*pushButton1.class: pushButton
*pushButton1.parent: form3
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 10
*pushButton1.y: 350
*pushButton1.width: 120
*pushButton1.height: 30
*pushButton1.labelString: "Ok"
*pushButton1.bottomAttachment: "attach_form"
*pushButton1.bottomOffset: 10
*pushButton1.rightAttachment: "attach_position"
*pushButton1.topAttachment: "attach_none"
*pushButton1.topOffset: 0
*pushButton1.leftAttachment: "attach_form"
*pushButton1.leftOffset: 10
*pushButton1.rightPosition: 30
*pushButton1.background: "#4f9f9f"
*pushButton1.activateCallback: {\
conferma_note_inserite(testo, True);\
}

*pushButton2.class: pushButton
*pushButton2.parent: form3
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 180
*pushButton2.y: 360
*pushButton2.width: 140
*pushButton2.height: 30
*pushButton2.labelString: "Apply"
*pushButton2.bottomAttachment: "attach_form"
*pushButton2.bottomOffset: 10
*pushButton2.leftAttachment: "attach_position"
*pushButton2.leftOffset: 0
*pushButton2.leftPosition: 36
*pushButton2.rightAttachment: "attach_position"
*pushButton2.rightOffset: 0
*pushButton2.topAttachment: "attach_none"
*pushButton2.topOffset: 0
*pushButton2.rightPosition: 64
*pushButton2.background: "#4f9f9f"
*pushButton2.activateCallback: {\
conferma_note_inserite(testo, False);\
}

*pushButton3.class: pushButton
*pushButton3.parent: form3
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.x: 340
*pushButton3.y: 350
*pushButton3.width: 120
*pushButton3.height: 30
*pushButton3.labelString: "Cancel"
*pushButton3.bottomAttachment: "attach_form"
*pushButton3.bottomOffset: 10
*pushButton3.leftAttachment: "attach_position"
*pushButton3.leftOffset: 0
*pushButton3.leftPosition: 70
*pushButton3.topAttachment: "attach_none"
*pushButton3.topOffset: 0
*pushButton3.rightAttachment: "attach_form"
*pushButton3.rightOffset: 10
*pushButton3.activateCallback: {\
*flag_win_note = False;\
UxDestroySwidget(window_notes);\
}
*pushButton3.background: "#4f9f9f"

*text_note.class: text
*text_note.parent: form3
*text_note.static: true
*text_note.name: text_note
*text_note.x: 10
*text_note.y: 90
*text_note.width: 480
*text_note.height: 240
*text_note.bottomAttachment: "attach_widget"
*text_note.bottomOffset: 10
*text_note.bottomWidget: "pushButton1"
*text_note.leftAttachment: "attach_form"
*text_note.leftOffset: 10
*text_note.rightAttachment: "attach_form"
*text_note.rightOffset: 10
*text_note.topAttachment: "attach_widget"
*text_note.topOffset: 20
*text_note.topWidget: "label1"
*text_note.background: "#4f9f9f"
*text_note.editMode: "multi_line_edit"

