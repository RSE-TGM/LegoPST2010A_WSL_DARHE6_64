! UIMX ascii 2.0 key: 3876                                                      

*abox_doc_module.class: applicationShell
*abox_doc_module.parent: NO_PARENT
*abox_doc_module.static: true
*abox_doc_module.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo abox_doc_module.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)abox_doc_module.i	2.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#include <ctype.h>\
#include <X11/Xlib.h>\
#include <X11/Intrinsic.h>\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
#ifndef LIBICOFILE\
#include <file_icone.h>\
#define LIBICOFILE\
#endif\
\
#include "definizioni.h"\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE					*/\
/****************************************************************/\
\
extern Arg args[];\
extern Cardinal argcount;\
\
extern Widget UxTopLevel, attention_wdg;\
extern Dialog_geometry geom_attention;\
\
/* Array di compound strings */\
extern XmString cstrings[], cstring, cstring_null;\
\
extern char message[];\
\
/* VARIABILE GLOBALE DEL NOME DEL MODULO SELEZIONATO */\
extern char nome_modulo[];\
extern char descr_modulo[];\
\
extern byte tipo_modulo;\
\
/****************************************************************/\
/* VARIABILI GLOBALI						*/\
/****************************************************************/\
\
/* dialog-box lista dei moduli */\
Boolean dbox_doclist_managed = False;\
Boolean dbox_doc_managed = False;\
\
/* scroll-list dei moduli */\
swidget dbox_doclist;\
\
char doc_modulo[256], doc_of_module[5];\
\
/* VARIABILE GLOBALE DELLA SEZIONE DI DOCUMENTAZIONE CORRENTE */\
short int sezione_attiva = 0;\
\
Sezioni sezione[] =  {\
                        {"CARD A", "FUNCTION"},\
                        {"CARD B", "TOPOLOGICAL DATA"},\
                        {"CARD C", "PHYSICAL AND GEOMETRICAL DATA"},\
                        {"CARD D",\
                          "MODULE VARIABLES INITIALIZATION"},\
                        {"CARD E", "USER SUBPROGRAMS"},\
                        {"CARD F", "RESIDUALS"},\
                        {"CARD G", "MODULE SUBPROGRAMS"},\
                        {"CARD H", "TEST CASES"}\
                     };\
\
Text_find_struct parametri_doc;
*abox_doc_module.ispecdecl:
*abox_doc_module.funcdecl: swidget create_doc_modulo()\

*abox_doc_module.funcname: create_doc_modulo
*abox_doc_module.funcdef: "swidget", "<create_doc_modulo>(%)"
*abox_doc_module.icode: Widget doc_find_form;
*abox_doc_module.fcode: /* Composizione percorso file documentazione */\
/* Allocazione della memoria per il testo di documentazione */\
/* Recupero della prima sezione di documentazione */\
   prepara_file_doc(nome_modulo);\
\
/* Inserimento find di libreria */\
   parametri_doc.ID_text = UxGetWidget(doc_scroll_text);\
   argcount=0;\
   XtSetArg(args[argcount],XmNleftAttachment,XmATTACH_FORM);argcount++;\
   XtSetArg(args[argcount],XmNleftOffset,0);argcount++;\
   XtSetArg(args[argcount],XmNrightAttachment,XmATTACH_FORM);argcount++;\
   XtSetArg(args[argcount],XmNrightOffset,0);argcount++;\
   XtSetArg(args[argcount],XmNbottomAttachment,XmATTACH_FORM);argcount++;\
   XtSetArg(args[argcount],XmNbottomOffset,0);argcount++;\
   XtSetArg(args[argcount],XmNtopAttachment,XmATTACH_FORM);argcount++;\
   XtSetArg(args[argcount],XmNtopOffset,0);argcount++;\
   doc_find_form = (Widget) find_in_a_text (UxGetWidget(form6),args,argcount,\
                                              &parametri_doc);\
   XtManageChild(doc_find_form);\
\
   UxPopupInterface(rtrn, no_grab);\
   dbox_doc_managed = True;\
\
/* non deve essere piu' utilizzato 11-1-95 \
   da quando la documentazione si trova nella\
   LIBUT UTENTE \
*/ \
XtUnmanageChild( doc_listButton);\
\
   return(rtrn);
*abox_doc_module.auxdecl: /*** void prepara_file_doc(modulo)\
 ***    Parametri:\
 ***       char *modulo : nome del modulo\
 ***\
 ***    Descrizione:\
 ***       Visualizza la prima sezione ("A - FUNZIONE") della documentazione\
 ***       del modulo.\
 ***/ \
void prepara_file_doc(modulo)\
char modulo[];\
{\
\
/* Composizione percorso file documentazione */\
/* 20-1-95 Micheletti\
   componi_file_modulo(doc_modulo,modulo, FILE_DOC, tipo_modulo, LIB_STANDARD);\
*/\
   componi_file_modulo(doc_modulo,modulo, FILE_DOC, tipo_modulo, LIB_UTENTE);\
\
\
/* recupera la prima sezione di documentazione */\
   if (leggi_sezione_doc(0))\
      scrivi_messaggio ("Couldn't open documentation.");\
\
/* All'apertura della finestra e' disabilitata la ricerca indietro */\
   set_something (UxGetWidget(arrow_prec),XmNsensitive,False);\
   set_something (UxGetWidget(arrow_next),XmNsensitive,True);\
}\
\
/************************************************************/\
/*** leggi_sezione_doc(ind_sez)\
 ***    Parametri:\
 ***      int ind_sez : indice array sezione[].\
 ***\
 ***    Descrizione:\
 ***      Visualizza la parte di documentazione relativa alla sezione\
 ***      indicata.\
 ***/\
leggi_sezione_doc(ind_sez)\
int ind_sez;\
{\
   char  ptr[81], titolo_finestra[30], modulo_lowercase[5];\
   char  *pattern_tmp;\
   int char_counter = 0;\
   FILE *fp_doc;\
   Boolean primo_ciclo;\
   char *stringone=NULL;\
   Boolean first=True; \
\
   if ((fp_doc = fopen (doc_modulo,"r")) == NULL)\
   {\
   /* Se non c'e' nessun modulo selezionato globalmente */\
      if (!strcmp(nome_modulo,""))\
         strcpy (message,"No module selected.");\
      else\
         sprintf (message,"File %s does not exist.", doc_modulo);\
      scrivi_messaggio (message);\
      XmTextSetString(UxGetWidget(doc_scroll_text),"<NO DOCUMENTATION FOUND>");\
      return(1);\
   }\
\
/* Inizializza il Text-Willer */\
   XmTextSetString(UxGetWidget(doc_scroll_text),"");\
\
/* Aggiornamento titolo finestra */\
   sprintf (titolo_finestra,"MODULE %.4s DOCUMENTATION",\
            doc_modulo+strlen(doc_modulo)-8);\
   tomaius (titolo_finestra);\
   set_something (UxGetWidget(abox_doc_module), XmNtitle,titolo_finestra);\
\
/*******************************************************************/ \
/* Leggo il file doc finche' non trovo la sezione da acquisire     */\
/* La ricerca e' limitata a 6 lettere ("CARD $")                   */\
/*******************************************************************/ \
/* N.B. Il pattern "CARD $" dovrebbe cominciare a colonna 70, ma   */\
/* talvolta comincia prima. Per prudenza la ricerca comincia da 68 */\
/*******************************************************************/ \
   while( fgets(ptr,80,fp_doc) != NULL )\
     if ( strlen(ptr) > 68 )\
        if ( confronta_stringhe(ptr+68,sezione[ind_sez].pattern,5) == 0)\
           break;\
\
   if (ind_sez < 7)\
      pattern_tmp = sezione[ind_sez+1].pattern;\
   else\
      pattern_tmp = NULL;\
\
/* Acquisisco finche' non trovo l'inizio della sezione successiva */\
   primo_ciclo = True;\
   while( fgets(ptr,80,fp_doc) != NULL )\
     if ( strlen(ptr) <= 68 || \
          (strlen(ptr) > 68 && confronta_stringhe(ptr+68,pattern_tmp,5)) )\
     {\
        if( stringone )\
           stringone = (char *)XtRealloc(stringone,sizeof(char)*strlen(ptr)+sizeof(char)*strlen(stringone)+4);\
        else\
           stringone = (char *)XtRealloc(stringone,sizeof(char)*strlen(ptr)+4);  \
/*\
        XmTextInsert(UxGetWidget(doc_scroll_text),char_counter,ptr);\
*/\
\
        if( first )\
        {\
           strcpy(stringone,ptr);\
           first=False;\
        }\
        else\
           strcat(stringone,ptr);\
     \
        char_counter += strlen(ptr);\
     }\
     else\
        break;  /* uscita dal ciclo */\
\
   XmTextInsert(UxGetWidget(doc_scroll_text),char_counter,stringone);\
   first = True;\
   free(stringone);\
   stringone = NULL; \
\
   fclose (fp_doc);\
\
/* Fisso il valore della variabile globale della sezione visualizzata */\
   sezione_attiva = ind_sez;\
\
/* Aggiornamento titolo sezione*/\
   set_label(UxGetWidget(label3),sezione[ind_sez].descrizione);\
\
   return (0);\
}\
\
/*****************************************************************/\
/*** cambia_sezione_doc(verso)\
 ***    Parametri:\
 ***       byte verso : SEZIONE_NEXT o SEZIONE_PREC\
 ***\
 ***    Descrizione:\
 ***       Cambia la sezione (successiva o precedente alla sezione corrente).\
 ***/\
cambia_sezione_doc(verso)\
byte verso;\
{\
   Boolean status; /* stato Sensitive True/False per gli arrow button */\
\
   switch (verso)\
   {\
      case SEZIONE_NEXT:\
\
         if (sezione_attiva < 7)\
         {\
            set_something (UxGetWidget(arrow_prec),XmNsensitive,True);\
            sezione_attiva++;\
            if (sezione_attiva == 7)\
                set_something (UxGetWidget(arrow_next),XmNsensitive,False);\
         }\
         break;\
\
      case SEZIONE_PREC:\
\
        if (sezione_attiva > 0)\
        {\
\
            set_something (UxGetWidget(arrow_next),XmNsensitive,True);\
            sezione_attiva--;\
            if (sezione_attiva == 0)\
                set_something (UxGetWidget(arrow_prec),XmNsensitive,False);\
        }\
        break;\
   }  /* Fine switch */\
\
   leggi_sezione_doc (sezione_attiva);\
}\
\
/*****************************************************************/\
/*** confronta_stringhe(stringa1, stringa2, numchar)\
 ***   Parametri:\
 ***      char *stringa1, *stringa2;\
 ***      int numchar : Numero di caratteri da confrontare.\
 ***\
 ***   Descrizione:\
 ***      Confronta due stringhe a partire dal primo carattere non-blank.\
 ***/\
confronta_stringhe(stringa1, stringa2, numchar)\
char *stringa1, *stringa2;\
int numchar;\
{\
   if (stringa1 == NULL || stringa2 == NULL)\
      return(-1);\
\
   /* Confronto tra le due stringhe finche' non si arriva alla fine\
      di una delle due  o  all'ultimo carattere da confrontare */\
   while (*stringa1 != '\0' && *stringa2 != '\0'  && numchar)\
   {\
\
     /* Posizionamento sul primo carattere non blank o tab di stringa1 */\
     while ( (*stringa1 == ' ' || *stringa1 == '\t' || *stringa1 == '\n')\
            && *stringa1 != '\0')\
         stringa1++;\
\
     /* Posizionamento sul primo carattere non blank o tab di stringa 2 */\
     while ( (*stringa2 == ' ' || *stringa2 == '\t' || *stringa2 == '\n')\
            && *stringa2 != '\0')\
         stringa2++;\
\
    /* Confronto tra le due stringhe, carattere per carattere, a partire\
       dall'ultimo blank o tab per arrivare al successivo o a fine stringa \
       o all'ultimo carattere da confrontare */\
     while (*stringa2 == *stringa1 && *stringa2 != ' ' && *stringa2 != '\t'\
            && *stringa2 != '\n' && *stringa2 != '\0' && numchar)\
     {\
        stringa2++;\
        stringa1++;\
        numchar--;\
     }\
\
    /* Se le stringhe differiscono prima di arrivare all'ultimo carattere */\
     if ( !((*stringa1 == ' ' || *stringa1 == '\n' || *stringa1 == '\t' ||\
           *stringa1 == '\0' ) &&\
          (*stringa2 == ' ' || *stringa2 == '\n' || *stringa2 == '\t' ||\
           *stringa2 == '\0' )) && numchar &&\
           *stringa2 != *stringa1)\
        return (-1);\
   } \
\
   /* Se una stringa e' composta da un numero di caratteri < numchar iniziale */\
   /* alla fine del confronto tra le stringhe numchar non vale 0 */\
   if (numchar > 0)\
      return (-1);\
\
   /* ALTRIMENTI LE STRINGHE SONO IDENTICHE */\
   return (0);\
}
*abox_doc_module.name: abox_doc_module
*abox_doc_module.x: 70
*abox_doc_module.y: 580
*abox_doc_module.width: 800
*abox_doc_module.height: 520
*abox_doc_module.iconName: "LEGOdoc"
*abox_doc_module.title: "MODULE DOCUMENTATION"
*abox_doc_module.geometry: "+80+185"

*form2.class: form
*form2.parent: abox_doc_module
*form2.static: true
*form2.name: form2
*form2.unitType: "pixels"
*form2.x: 0
*form2.y: 10
*form2.width: 800
*form2.height: 390

*frame2.class: frame
*frame2.parent: form2
*frame2.static: true
*frame2.name: frame2
*frame2.unitType: "pixels"
*frame2.x: 10
*frame2.y: 10
*frame2.width: 670
*frame2.height: 30
*frame2.rightAttachment: "attach_form"
*frame2.rightOffset: 10
*frame2.leftAttachment: "attach_form"
*frame2.leftOffset: 10
*frame2.topOffset: 10
*frame2.topAttachment: "attach_form"

*label3.class: label
*label3.parent: frame2
*label3.static: true
*label3.name: label3
*label3.x: 50
*label3.y: 10
*label3.width: 570
*label3.height: 30
*label3.labelString: "SECTION TITLE"

*arrow_prec.class: arrowButton
*arrow_prec.parent: form2
*arrow_prec.static: true
*arrow_prec.name: arrow_prec
*arrow_prec.x: 10
*arrow_prec.y: 350
*arrow_prec.width: 40
*arrow_prec.height: 30
*arrow_prec.bottomAttachment: "attach_form"
*arrow_prec.bottomOffset: 10
*arrow_prec.leftAttachment: "attach_form"
*arrow_prec.leftOffset: 10
*arrow_prec.topAttachment: "attach_none"
*arrow_prec.topOffset: 0
*arrow_prec.activateCallback: {\
cambia_sezione_doc(SEZIONE_PREC);\
}

*arrow_next.class: arrowButton
*arrow_next.parent: form2
*arrow_next.static: true
*arrow_next.name: arrow_next
*arrow_next.x: 70
*arrow_next.y: 360
*arrow_next.width: 40
*arrow_next.height: 30
*arrow_next.bottomAttachment: "attach_form"
*arrow_next.bottomOffset: 10
*arrow_next.leftAttachment: "attach_widget"
*arrow_next.leftOffset: 10
*arrow_next.leftWidget: "arrow_prec"
*arrow_next.arrowDirection: "arrow_down"
*arrow_next.activateCallback: {\
cambia_sezione_doc(SEZIONE_NEXT);\
}

*doc_cancelButton.class: pushButton
*doc_cancelButton.parent: form2
*doc_cancelButton.static: true
*doc_cancelButton.name: doc_cancelButton
*doc_cancelButton.x: 630
*doc_cancelButton.y: 410
*doc_cancelButton.width: 60
*doc_cancelButton.height: 30
*doc_cancelButton.activateCallback: {\
/* Cancella la finestra di documentazione */\
   UxDestroySwidget(abox_doc_module);\
   dbox_doc_managed = False;\
\
/* Cancella l'eventuale lista di files *.DOC rimasta aperta */\
   if (dbox_doclist_managed)\
   {\
      UxDestroySwidget(dbox_doclist);\
      dbox_doclist_managed = False;\
   }\
\
}
*doc_cancelButton.bottomAttachment: "attach_form"
*doc_cancelButton.bottomOffset: 10
*doc_cancelButton.labelString: "Cancel"
*doc_cancelButton.leftAttachment: "attach_none"
*doc_cancelButton.leftOffset: 0
*doc_cancelButton.rightAttachment: "attach_form"
*doc_cancelButton.rightOffset: 10

*labelGadget1.class: labelGadget
*labelGadget1.parent: form2
*labelGadget1.static: true
*labelGadget1.name: labelGadget1
*labelGadget1.x: 110
*labelGadget1.y: 420
*labelGadget1.width: 200
*labelGadget1.height: 30
*labelGadget1.bottomAttachment: "attach_form"
*labelGadget1.bottomOffset: 10
*labelGadget1.leftAttachment: "attach_widget"
*labelGadget1.leftOffset: 10
*labelGadget1.leftWidget: "arrow_next"
*labelGadget1.topAttachment: "attach_none"
*labelGadget1.topOffset: 0
*labelGadget1.alignment: "alignment_beginning"
*labelGadget1.labelString: "Move to another section"
*labelGadget1.rightAttachment: "attach_none"
*labelGadget1.rightOffset: 0

*separatorGadget4.class: separatorGadget
*separatorGadget4.parent: form2
*separatorGadget4.static: true
*separatorGadget4.name: separatorGadget4
*separatorGadget4.x: 20
*separatorGadget4.y: 480
*separatorGadget4.width: 760
*separatorGadget4.height: 10
*separatorGadget4.bottomAttachment: "attach_widget"
*separatorGadget4.bottomOffset: 5
*separatorGadget4.bottomWidget: "arrow_prec"
*separatorGadget4.leftAttachment: "attach_form"
*separatorGadget4.leftOffset: 10
*separatorGadget4.rightAttachment: "attach_form"
*separatorGadget4.rightOffset: 10
*separatorGadget4.topAttachment: "attach_none"
*separatorGadget4.topOffset: 0

*form6.class: form
*form6.parent: form2
*form6.static: true
*form6.name: form6
*form6.unitType: "pixels"
*form6.x: 20
*form6.y: 430
*form6.width: 770
*form6.height: 40
*form6.bottomAttachment: "attach_widget"
*form6.bottomOffset: 5
*form6.bottomWidget: "separatorGadget4"
*form6.leftAttachment: "attach_form"
*form6.leftOffset: 10
*form6.topAttachment: "attach_none"
*form6.topOffset: 0

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.parent: form2
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.scrollingPolicy: "automatic"
*scrolledWindow3.unitType: "pixels"
*scrolledWindow3.x: 10
*scrolledWindow3.y: 50
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.bottomAttachment: "attach_widget"
*scrolledWindow3.bottomOffset: 10
*scrolledWindow3.bottomWidget: "form6"
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.leftOffset: 10
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.rightOffset: 10
*scrolledWindow3.topAttachment: "attach_widget"
*scrolledWindow3.topOffset: 10
*scrolledWindow3.topWidget: "frame2"

*doc_scroll_text.class: scrolledText
*doc_scroll_text.parent: scrolledWindow3
*doc_scroll_text.static: true
*doc_scroll_text.name: doc_scroll_text
*doc_scroll_text.width: 790
*doc_scroll_text.height: 350
*doc_scroll_text.columns: 81
*doc_scroll_text.editMode: "multi_line_edit"
*doc_scroll_text.editable: "false"
*doc_scroll_text.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*doc_scroll_text.resizeHeight: "true"
*doc_scroll_text.resizeWidth: "true"

*doc_loadButton.class: pushButton
*doc_loadButton.parent: form2
*doc_loadButton.static: true
*doc_loadButton.name: doc_loadButton
*doc_loadButton.x: 660
*doc_loadButton.y: 480
*doc_loadButton.width: 60
*doc_loadButton.height: 30
*doc_loadButton.bottomAttachment: "attach_form"
*doc_loadButton.bottomOffset: 10
*doc_loadButton.labelString: "Load"
*doc_loadButton.leftAttachment: "attach_none"
*doc_loadButton.leftOffset: 0
*doc_loadButton.rightAttachment: "attach_widget"
*doc_loadButton.rightOffset: 20
*doc_loadButton.rightWidget: "doc_cancelButton"
*doc_loadButton.topAttachment: "attach_none"
*doc_loadButton.topOffset: 0
*doc_loadButton.activateCallback: {\
/* Se c'e' un modulo selezionato lo carica */\
if (strcmp(nome_modulo,""))\
{\
   prepara_file_doc(nome_modulo);\
   return;\
}\
\
}

*doc_listButton.class: pushButton
*doc_listButton.parent: form2
*doc_listButton.static: true
*doc_listButton.name: doc_listButton
*doc_listButton.x: 560
*doc_listButton.y: 480
*doc_listButton.width: 60
*doc_listButton.height: 30
*doc_listButton.bottomAttachment: "attach_form"
*doc_listButton.bottomOffset: 10
*doc_listButton.labelString: "List"
*doc_listButton.leftAttachment: "attach_none"
*doc_listButton.leftOffset: 0
*doc_listButton.rightAttachment: "attach_widget"
*doc_listButton.rightOffset: 20
*doc_listButton.rightWidget: "doc_loadButton"
*doc_listButton.topAttachment: "attach_none"
*doc_listButton.topOffset: 0
*doc_listButton.activateCallback: {\
char file_lista[256];\
FILE *fpd;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
if ( dbox_doclist_managed )\
{\
   sprintf(message," Modules list window already in use.");\
   attention_wdg = (Widget) attention (UxTopLevel, message, MAPPA,\
                                       geom_attention);\
   scrivi_messaggio (message);\
   return;\
}\
\
file_dati_lib(file_lista, tipo_modulo, LIB_UTENTE);\
\
/* Se il file lista dei moduli (LIBUT,LIBUTREG,LIBREG) non esiste esci */\
if ((fpd = fopen (file_lista, "r")) == NULL)\
{\
   scrivi_messaggio ("Can't open data file.");\
   return;\
}\
\
/* Visualizza la lista dei moduli della libreria appropriata */\
dbox_doclist = create_lista_moduli(fpd,tipo_modulo,STDLIB_MODULES_DOC,\
                                   &dbox_doclist_managed);\
fclose(fpd);\
\
}

