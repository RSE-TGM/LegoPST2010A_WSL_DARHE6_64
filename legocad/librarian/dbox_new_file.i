! UIMX ascii 2.0 key: 5493                                                      

*dbox_new_file.class: formDialog
*dbox_new_file.parent: NO_PARENT
*dbox_new_file.defaultShell: topLevelShell
*dbox_new_file.static: true
*dbox_new_file.gbldecl: #include <stdio.h>\
#include <Xm/Xm.h>\
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
/*** SCANCELLARE ***/\
#define LIB_UTENTE	0\
/*******************/\
\
#include "definizioni.h"\
\
extern Arg args[];\
extern Cardinal argcount;\
\
/* Array di compound strings */\
extern XmString cstrings[], cstring, cstring_null;\
\
/* VARIABILE GLOBALE DEL NOME DEL MODULO SELEZIONATO */\
extern char nome_modulo[];\
extern char descr_modulo[];\
\
extern int tipo_modulo;\
\
extern char *path_altro_utente;\
extern char file_moduli_libut[];\
\
extern long int offset_listamod;\
\
/* Variabili globali relative al modulo da copiare */\
char module_sorg[5], module_descr[80];\
Boolean nome_mod_cambiato = False;\
\
/***************************************************/\
/* Struttura di callback per gli widget di conferma*/\
/***************************************************/\
static Elenco_callback copre_modulo = {\
	{"Yes", overwrite_yes, 0 },\
	{"No" , overwrite_no,  0  },\
	{ NULL, NULL,          NULL} }; \

*dbox_new_file.ispecdecl:
*dbox_new_file.funcdecl: swidget create_dbox_new_file()\

*dbox_new_file.funcname: create_dbox_new_file
*dbox_new_file.funcdef: "swidget", "<create_dbox_new_file>(%)"
*dbox_new_file.icode: Widget text_file, text_descr;\
int last_pos;\
char file_sorg[256];\

*dbox_new_file.fcode: UxPopupInterface (rtrn, no_grab);\
\
text_file = UxGetWidget(filenameText);\
\
/* Estrapola le 4 lettere del nome del modulo */\
sprintf (module_sorg,"%.4s",file_sorg+(strlen(file_sorg)-6));\
tomaius(module_sorg);\
XmTextSetString (text_file,module_sorg);\
\
/* Seleziona la parola */\
last_pos = XmTextGetLastPosition (text_file);\
XmTextSetSelection (text_file,0,last_pos,CurrentTime);\
\
/* Se esiste il file lista_moduli.dat nella directory sorgente */\
/* recupera e visualizza la descrizione */\
if ( !recupera_descr(module_sorg, module_descr) )\
    XmTextSetString (UxGetWidget(descripText), module_descr);\
\
XtSetKeyboardFocus (UxGetWidget(okButton),text_file);\
return(rtrn);\

*dbox_new_file.auxdecl: /***\
 *** controlla_lista_moduli(tipo_lib, nome_inserito, offset_listamod)\
 ***   Parametri:\
 ***     unsigned char tipo_lib : tipo libreria (LIBUT, LIBUTREG, LIBREG)\
 ***     char *nome_inserito : nome del modulo\
 ***     long *offset_listamod : offset del file lista moduli dove si trova il\
 ***                             modulo (se esiste). (uscita)\
 ***\
 ***   Descrizione:\
 ***     La funzione controlla se il nome di un modulo e' gia' presente nel file\
 ***     lista dei moduli dell'utente.Viene chiamata per tutte e due le attivita'\
 ***     di copia di un modulo (da altro utente o da libreria standard).\
 ***\
 ***   VALORI RITORNATI:\
 ***     0	tutto ok: il nome di modulo non si trova nella lista\
 ***     1	il modulo esiste ed ha il tag '!' \
 ***    -1	il modulo esiste e non ha il tag '!' \
 ***/\
controlla_lista_moduli(tipo_lib, nome_inserito, offset_listamod)\
unsigned char tipo_lib;\
char *nome_inserito;\
long *offset_listamod;\
{\
  extern Dialog_geometry geom_attention;\
  extern Widget attention_wdg, UxTopLevel;\
  FILE *fp_lista;\
  int  value = 0;\
  char baffer[81], file_lista[256], *message;\
\
/* Apertura file dati  in lettura */\
  file_dati_lib(file_lista, tipo_lib, LIB_UTENTE);\
  if ( (fp_lista = fopen (file_lista,"r")) == NULL)\
  {\
     message = " Can't open data file for checking module names";\
     attention_wdg = (Widget) attention (UxTopLevel, message, MAPPA,\
					 geom_attention);\
     scrivi_messaggio(message);\
     return;\
  }\
\
  /* Controllo che il nome del modulo non esista gia' */\
  while ( fgets(baffer,80,fp_lista) != NULL)\
  {\
     if (!strncmp(baffer,nome_inserito,4))\
     {\
     /* Se c'e' anche il tag '!' NON bisogna copiare */\
        if (baffer[5] == '!')\
           value = 1;\
        else /* Se non c'e' il tag il file va copiato */\
           value = -1;\
\
      /* Setto l'offset */\
         *offset_listamod = ftell (fp_lista) - strlen(baffer);\
         fclose(fp_lista);\
         return (value); \
     }\
  }\
\
  fclose(fp_lista);\
  return (value);\
}\
\
/*******************************************************/\
recupera_descr (modulo, module_descr)\
char *modulo, module_descr[];\
{\
   char  lista_moduli[256], message[100];\
   char  buffer[81];\
   FILE *fp_listamod;\
\
   module_descr[0] = '\0'; /* inizialmente la descrizione e' vuota */\
   strcpy (lista_moduli,path_altro_utente);\
   strcat (lista_moduli,"lista_moduli.dat");\
\
   /* Se il file lista_moduli.dat esiste nella directory utente */\
   if (access(lista_moduli,F_OK) == 0)\
   {\
      if ( (fp_listamod = fopen (lista_moduli,"r")) == NULL )\
      {\
          sprintf (message," Can't open file %s.",lista_moduli);\
          scrivi_messaggio(message);\
          return (-1);\
      }\
   }\
   else /* Il file non esiste */\
      return (-1);\
\
   /* Ricerca del nome del modulo prescelto */\
   while (fgets (buffer,80,fp_listamod) != NULL) \
      if (!strncmp (modulo,buffer,4))\
      {\
         sprintf(module_descr, "%.50s", buffer+6);\
         module_descr[strlen(module_descr)-1] = '\0';\
         fclose (fp_listamod); \
         return (0);\
      }\
\
   /* Se per sventura il modulo non e' elencato */\
   fclose (fp_listamod);\
   return (-1);\
}\
\
/*******************************************************/\
/*** sostituisci_nome_ftn ()\
 ***\
 *** Funzione chiamata quando si copia un modulo cambiando nome.\
 *** Sostituisce il vecchio col nuovo nel codice FORTRAN.\
 ***/\
sostituisci_nome_ftn ()\
{\
   FILE *fp;\
   char baffer[81], bulfus[81], file_ftn[20], message[80];\
   char *trovato;\
   int  pos_found;\
   long int offset = 0;\
\
   strcpy (file_ftn,"libut/");\
   strcat (file_ftn,nome_modulo);\
   strcat (file_ftn,".f");\
   tominus (file_ftn);\
\
   if ((fp = fopen (file_ftn,"r+")) == NULL)\
      return (-1);\
\
   while ( fgets(baffer,80,fp) != NULL )\
   {\
      if ( (trovato = (char *) Utstrstr(baffer,module_sorg)) != NULL)\
      {\
         pos_found = trovato - baffer;            \
         sprintf (bulfus,"%.*s%s%s", \
                  pos_found,baffer,nome_modulo,\
                  baffer+pos_found+strlen(nome_modulo)); \
         XtFree (trovato);\
      }\
      else\
         strcpy (bulfus,baffer);\
\
      fseek (fp,offset,SEEK_SET);\
      fputs (bulfus,fp);\
      ftell(fp);\
      offset += strlen(bulfus);\
   }\
   fclose (fp);\
\
   sprintf (message," All occurrencies of %s replaced by %s in %s.",\
            module_sorg,nome_modulo,file_ftn+6);\
   scrivi_messaggio (message);\
   return (0);\
}
*dbox_new_file.name: dbox_new_file
*dbox_new_file.unitType: "pixels"
*dbox_new_file.x: 675
*dbox_new_file.y: 150
*dbox_new_file.width: 460
*dbox_new_file.height: 200
*dbox_new_file.dialogTitle: "NEW MODULE INSTANTIATION"
*dbox_new_file.defaultButton: "okButton"
*dbox_new_file.cancelButton: ""
*dbox_new_file.autoUnmanage: "false"
*dbox_new_file.dialogStyle: "dialog_full_application_modal"
*dbox_new_file.defaultPosition: "false"

*okButton.class: pushButton
*okButton.parent: dbox_new_file
*okButton.static: true
*okButton.name: okButton
*okButton.x: 10
*okButton.y: 130
*okButton.width: 50
*okButton.height: 40
*okButton.bottomAttachment: "attach_form"
*okButton.bottomOffset: 10
*okButton.topAttachment: "attach_none"
*okButton.topOffset: 0
*okButton.labelString: "Ok"
*okButton.activateCallback: {\
extern swidget selected_module_label;\
extern Boolean menu_sbloccato;\
extern Dialog_geometry geom_attention;\
extern Widget attention_wdg;\
extern Widget UxTopLevel;\
char *newname, *newdescript, file_dest[20];\
char modulo_attivo[80], modulo_lowercase[5];\
char message[80], warning[100];\
int modulo_esiste;\
FILE *fp_listamod;\
Widget conferma_copia;\
long offset;\
 \
newname = XmTextGetString(UxGetWidget(filenameText));\
newdescript = XmTextGetString(UxGetWidget(descripText));\
\
/* CONTROLLO che il NOME del modulo sia composto da 4 char stampabili */\
if ( (strlen(newname)!=4) || contiene_blanks(newname) )\
{\
   sprintf ( message," Module name must consist of exactly 4 printable characters.");\
   attention_wdg = (Widget) attention (UxTopLevel, message, MAPPA, geom_attention);\
   scrivi_messaggio (message);\
   return; \
}\
\
/* Smaneggia la finestra */\
XtUnmanageChild (UxGetWidget(dbox_new_file));\
\
/* Se e' stato modificato il nome del modulo */\
if (strcmp(module_sorg,newname))\
   nome_mod_cambiato = True;\
else\
   nome_mod_cambiato = False;\
\
\
/* Controllo che il nome del modulo non esista gia' */\
if ( (modulo_esiste = controlla_lista_moduli(tipo_modulo,newname,offset)) )\
{          \
   sprintf (warning,\
            "Module %s was previously imported / modified. Overwrite it ?",\
            newname);\
\
   conferma_copia = (Widget) conferma (UxTopLevel,warning,copre_modulo);\
   strcpy (nome_modulo,newname);\
   strcpy (descr_modulo,newdescript);\
   return;\
}\
else\
{\
/* Aggiorna la label e le variabili globali sul modulo attivo */\
   strcpy (nome_modulo,newname);\
   strcpy (descr_modulo,newdescript);\
   sprintf (modulo_attivo,"%s  %s\n",newname,newdescript);\
   set_something ( UxGetWidget(selected_module_label),XmNlabelString,\
                   CREATE_CSTRING (modulo_attivo) );\
\
/* COPIA FILE sorgente nella libut */\
   copia_nella_libreria(tipo_modulo, newname, newdescript, False );\
\
/* Se e' stato modificato il nome del modulo destinazione */\
/* sostituire il vecchio nome nel FORTRAN */\
   if ( nome_mod_cambiato )\
      if ( sostituisci_nome_ftn() )\
      {\
          scrivi_messaggio (" Substitution in FORTRAN code impossible. Failure.");\
          return;\
      }\
\
/********************************************************/\
/*   N.B. COPIARE ANCHE ICONE E RECORD ICON_LIST        */\
/********************************************************/\
   copia_nella_libgraf(); \
\
/* Liberalizza i menu */\
   if (menu_sbloccato == False)\
      menu_modulo_attivo();\
} /* FINE else ET callback */\
\
}

*cancelButton.class: pushButton
*cancelButton.parent: dbox_new_file
*cancelButton.static: true
*cancelButton.name: cancelButton
*cancelButton.x: 80
*cancelButton.y: 130
*cancelButton.width: 100
*cancelButton.height: 40
*cancelButton.bottomAttachment: "attach_form"
*cancelButton.bottomOffset: 10
*cancelButton.leftAttachment: "attach_widget"
*cancelButton.leftOffset: 10
*cancelButton.leftWidget: "okButton"
*cancelButton.topAttachment: "attach_none"
*cancelButton.topOffset: 0
*cancelButton.labelString: "Cancel"
*cancelButton.activateCallback: {\
XtUnmanageChild (UxGetWidget(dbox_new_file));\
\
}

*separatorGadget1.class: separatorGadget
*separatorGadget1.parent: dbox_new_file
*separatorGadget1.static: true
*separatorGadget1.name: separatorGadget1
*separatorGadget1.x: 10
*separatorGadget1.y: 90
*separatorGadget1.width: 430
*separatorGadget1.height: 10
*separatorGadget1.bottomAttachment: "attach_widget"
*separatorGadget1.bottomOffset: 5
*separatorGadget1.bottomWidget: "okButton"
*separatorGadget1.rightAttachment: "attach_form"
*separatorGadget1.rightOffset: 10
*separatorGadget1.topAttachment: "attach_none"
*separatorGadget1.topOffset: 0

*labelGadget4.class: labelGadget
*labelGadget4.parent: dbox_new_file
*labelGadget4.static: true
*labelGadget4.name: labelGadget4
*labelGadget4.x: 10
*labelGadget4.y: 95
*labelGadget4.width: 119
*labelGadget4.height: 40
*labelGadget4.alignment: "alignment_beginning"
*labelGadget4.labelString: "DESCRIPTION: "
*labelGadget4.topAttachment: "attach_none"
*labelGadget4.topOffset: 0
*labelGadget4.bottomAttachment: "attach_widget"
*labelGadget4.bottomOffset: 10
*labelGadget4.bottomWidget: "separatorGadget1"
*labelGadget4.rightAttachment: "attach_position"
*labelGadget4.rightPosition: 28
*labelGadget4.leftAttachment: "attach_form"
*labelGadget4.leftOffset: 10

*descripText.class: text
*descripText.parent: dbox_new_file
*descripText.static: true
*descripText.name: descripText
*descripText.x: 120
*descripText.y: 40
*descripText.width: 240
*descripText.height: 35
*descripText.columns: 50
*descripText.leftAttachment: "attach_position"
*descripText.leftOffset: 0
*descripText.leftWidget: ""
*descripText.maxLength: 50
*descripText.rightAttachment: "attach_form"
*descripText.rightOffset: 10
*descripText.topAttachment: "attach_none"
*descripText.topOffset: 0
*descripText.topWidget: ""
*descripText.bottomAttachment: "attach_widget"
*descripText.bottomOffset: 10
*descripText.bottomWidget: "separatorGadget1"
*descripText.leftPosition: 30

*labelGadget2.class: labelGadget
*labelGadget2.parent: dbox_new_file
*labelGadget2.static: true
*labelGadget2.name: labelGadget2
*labelGadget2.x: 10
*labelGadget2.y: 10
*labelGadget2.width: 100
*labelGadget2.height: 40
*labelGadget2.labelString: "MODULE: "
*labelGadget2.topOffset: 0
*labelGadget2.alignment: "alignment_beginning"
*labelGadget2.bottomAttachment: "attach_widget"
*labelGadget2.bottomOffset: 15
*labelGadget2.bottomWidget: "labelGadget4"
*labelGadget2.topAttachment: "attach_none"

*filenameText.class: text
*filenameText.parent: dbox_new_file
*filenameText.static: true
*filenameText.name: filenameText
*filenameText.x: 130
*filenameText.y: 10
*filenameText.width: 130
*filenameText.height: 35
*filenameText.leftAttachment: "attach_position"
*filenameText.leftOffset: 0
*filenameText.leftPosition: 30
*filenameText.topOffset: 0
*filenameText.columns: 4
*filenameText.maxLength: 4
*filenameText.bottomAttachment: "attach_widget"
*filenameText.bottomOffset: 20
*filenameText.bottomWidget: "descripText"
*filenameText.topAttachment: "attach_none"

