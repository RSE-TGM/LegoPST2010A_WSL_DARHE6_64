! UIMX ascii 2.0 key: 1672                                                      

*nmod_app_shell.class: applicationShell
*nmod_app_shell.parent: NO_PARENT
*nmod_app_shell.static: true
*nmod_app_shell.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nmod_app_shell.i\
   tipo \
   release 2.23\
   data 1/18/96\
   reserved @(#)nmod_app_shell.i	2.23\
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
#include <unistd.h>\
#include <ctype.h>\
#include <string.h>\
\
#include "definizioni.h"\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE					*/\
/****************************************************************/\
\
extern int num_yes_toggle;\
extern swidget nmod_dialog_equations;\
extern char file_jac_temp[];\
\
extern Boolean dbox_userdata_managed;\
extern Boolean dbox_userjac_managed;\
extern Boolean dbox_userresid_managed;\
extern Boolean dbox_usereq_managed;\
\
extern StructVars *variabili;\
extern StructDati *dati_geom;\
\
extern byte jacobian_type;\
\
extern byte tipo_modulo;\
\
extern char nome_modulo[], descr_modulo[];\
extern char *nome_nuovo_modulo, *descr_nuovo_modulo;\
\
extern Arg args[20];\
extern Cardinal argcount;\
extern char message[], *font;\
\
extern Widget UxTopLevel;\
extern Dialog_geometry geom_attention;\
extern Widget attention_wdg;\
\
extern WdgDatiGeometrici *wdati_geometrici;\
extern WdgVariabili *wvar_stato, *wvar_algebriche, *wvar_ingresso;\
\
extern XmString cstring;\
\
/****************************************************************/\
/* VARIABILI GLOBALI 						*/\
/****************************************************************/\
\
/* Variabili globali per dimensionare la matrice jacobiana */\
/* (VALORI DI DEFAULT) */\
int num_var_stato = 0;\
int num_var_algebriche = 0;\
int num_var_ingresso = 0;\
int num_dati_geometrici = 0;\
int jac_rows = 20, \
    jac_cols = 30;\
\
/* variabili utilizzate per memorizzare i text delle window relative */\
/* alle subroutine I2,JC,D1 e residui (NEWMOD) */\
char *str_dichI2 = NULL, *str_codI2 = NULL;\
char *str_dichJC = NULL, *str_codJC = NULL;\
char *str_dichMOD = NULL, *str_codMOD = NULL,*str_resMOD[MAX_EQUAZIONI];\
char *str_signeq[MAX_EQUAZIONI], *str_uniteq[MAX_EQUAZIONI],\
     *str_cosnor[MAX_EQUAZIONI];\
\
Boolean bboard_flag = True;\
Boolean bool_dialog_config = True;\
Boolean bool_dialog_equation = True;\
Boolean nmod_def_managed = False;\
Boolean nmod_def_initialized = False;\
Boolean non_salvato = True;\
\
Widget wconfirm_save;\
Widget _nmod_varsetup;\
Widget scrollw_label1, scrollw_label2, scrollw_label3;\
Widget dialog_setup;\
\
int option_scelto = K_OPT_VOID;\
int posy_text;\
\
JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];\
\
/* variabili utilizzate per l'attivazione dell'editor (view delle subroutine) */\
Widget wtxteditor;  /* variabile TAMPAX */\
Widget weditor[7];  /* widget delle window di editor (1 per ciascuna sub.) */\
char nomitmp[7][256]; /* nomi di file temporanei (come sopra) */\
\
/*************************************************************/\
/* Struttura di callback per l'editor (view delle subroutine */\
/*************************************************************/\
Elenco_callback funz_editor = {\
        { "Done",  editor_done, 0},\
        { NULL, NULL, NULL },\
        { NULL, NULL, NULL }};\
\
Dialog_geometry geom_editor = { TRUE, NULL, NULL, 700, 500};\
\
/****************************************************/\
/* Struttura di callback per gli widget di conferma */\
/****************************************************/\
Elenco_callback rilancia_setup_nmod = {\
        {"Yes", setup_again, YES },\
        {"No" , setup_again, NO  },\
        { NULL, NULL,   NULL    }};\
\
Elenco_callback funz_confirm_save = {\
        {"Yes", confirm_save, YES },\
        {"No" , confirm_save, NO  },\
        { NULL, NULL,   NULL    }};\
\
Elenco_callback funz_confirm_quit = {\
        {"Yes",    confirm_quit, YES    },\
        {"No" ,    confirm_quit, NO     },\
        {"Cancel", confirm_quit, CANCEL }};
*nmod_app_shell.ispecdecl:
*nmod_app_shell.funcdecl: swidget create_nmod_shell(modifica)\
Boolean modifica;\
/* se True indica che si modifica un modulo creato precedentemente con la */\
/* NEWMOD; altrimenti se ne crea uno nuovo */
*nmod_app_shell.funcname: create_nmod_shell
*nmod_app_shell.funcdef: "swidget", "<create_nmod_shell>(%)"
*nmod_app_shell.argdecl: Boolean modifica;
*nmod_app_shell.arglist: modifica
*nmod_app_shell.arglist.modifica: "Boolean", "%modifica%"
*nmod_app_shell.icode: /* carica i widget di testo relativi alle equazioni di stato */\
/* (il default iniziale dell'option menu). */\
option_scelto = K_OPT_ALL;\
\
_nmod_varsetup = UxGetWidget(pb_nmod_varsetup);\
\
/* inizializzazione delle variabili */\
num_var_stato = 0;\
num_var_algebriche = 0;\
num_var_ingresso = 0;\
num_dati_geometrici = 0;\
\
scrollw_label1 = NULL;
*nmod_app_shell.fcode: UxPopupInterface(rtrn, no_grab);\
\
if (modifica)\
{\
   XmTextSetString(UxGetWidget(nmod_text_nome), nome_modulo);\
   XmTextSetString(UxGetWidget(nmod_text_descr), descr_modulo);\
   if (leggi_file_interfaccia() != 0)\
   {\
      sprintf(message,"Cannot read NEWMOD information (check permission).");\
      attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,\
                                         geom_attention);\
   }\
\
   nome_nuovo_modulo = XmTextGetString(UxGetWidget(nmod_text_nome));\
   descr_nuovo_modulo = XmTextGetString(UxGetWidget(nmod_text_descr));\
   nmod_def_initialized = True;\
   set_something (UxGetWidget(pb_nmod_JC),XmNsensitive,\
                  (jacobian_type == NUMERICAL) ? False : True);\
}\
else\
{\
   alloca_text_widget(UxGetWidget(nmod_bboard),5, 5, 5, 5);\
/* jacobiano di tipo ANALITICO per default */\
   jacobian_type = ANALYTICAL;\
\
   menu_newmod_init();\
}\
\
posy_text = 10;\
bboard_flag = False;\
\
nmod_def_managed = True;\
\
non_salvato = False;\
\
return(rtrn);
*nmod_app_shell.auxdecl: /*** setup_again ()\
 ***\
 ***   Descrizione:\
 ***     Callback chiamata premendo i pushButton della finestra\
 ***     di rilancio setup nuovo modulo (NEWMOD).\
 ***/\
void setup_again (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
   switch (which_button)\
   {\
      case YES:\
\
      /* Cancellazione eventuale file jac temporaneo */\
         if (!access(file_jac_temp,F_OK))\
            if ( unlink(file_jac_temp) )\
               printf ("Can't delete jacobian temporary file. Failure.\n");\
\
      /* Visualizzazione finestra setup */\
         create_nmod_dialog_config();\
\
      break;\
  \
      case NO:\
         XtDestroyWidget(dialog_setup);\
      break;\
   }\
}\
\
/*** editor_done(...)\
 ***\
 ***   Descrizione:\
 ***     Callback chiamata dall'editor di libreria (libutilx) \
 ***/\
void editor_done( w, indice, call_data)\
Widget w;\
int indice;\
XmAnyCallbackStruct *call_data;\
{\
   Text_find_struct *ptr;\
\
/* Dealloca la memoria */\
   get_something(weditor[indice], XmNuserData, &ptr);\
   XtFree(ptr);\
 \
/* Cancella file temporaneo */\
#ifdef VMS\
   remove(nomitmp[indice]);\
#else\
   unlink(nomitmp[indice]);\
#endif\
\
/* chiudi la window */\
   XtDestroyWidget(weditor[indice]);\
}\
\
/*** void confirm_save()\
 ***\
 ***   Descrizione:\
 ***     Chiamata dalla window di conferma durante il save quando il modulo\
 ***     esiste gia' nel file lista_moduli.dat\
 ***/\
void confirm_save (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
   if (which_button == YES)\
      salva_e_genera();\
   XtDestroyWidget(wconfirm_save);\
}\
\
/*** void confirm_quit()\
 ***\
 ***   Descrizione:\
 ***     Chiamata quando si esce dalla window della NEWMOD e le informazioni\
 ***     non sono state salvate.\
 ***/\
void confirm_quit (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
   if (which_button == YES)\
      salva_e_genera();\
\
/* Chiudi la window di conferma */\
   XtDestroyWidget(wconfirm_save);\
\
/* Se e' stato premuto 'CANCEL' non uscire dalla window NEWMOD */\
   if (which_button == CANCEL)\
      return; \
\
/* Dealloca la memoria e chiudi la window della NEWMOD */\
   quit_newmod();\
}\
\
/*** salva_e_genera()\
 ***\
 ***   Descrizione:\
 ***     La funzione salva le informazione della NEWMOD, genera il FORTRAN ed \
 ***     aggiorna il file lista_moduli.dat \
 ***/\
salva_e_genera()\
{\
   if ( !salva_interfaccia())\
   {\
      non_salvato = False;\
\
      scrivi_messaggio("NEWMOD information succesfully saved.");\
\
   /* Generazione codice FORTRAN */\
      if (genera_fortran(nome_nuovo_modulo, descr_nuovo_modulo) == 0)\
      {\
         scrivi_messaggio("OK! FORTRAN module generate correctly.");\
\
      /* Aggiorna il file lista_moduli.dat (se necessario) */\
         aggiungi_modulo_lista(LIBUT,nome_nuovo_modulo,descr_nuovo_modulo,True);\
\
      /* Aggiorna il file icon_list.dat (se necesasrio) */\
         copia_nella_libgraf(nome_nuovo_modulo,descr_nuovo_modulo,\
                             ONLY_FORTRAN,FALSE,getenv("LEGOCAD_USER"));\
\
      /* Aggiorna la scroll-list dei moduli di processo (se e' quella */\
      /* visualizzata in questo momento). */\
         if (tipo_modulo == LIBUT)\
         {\
            char nome_e_descr[100];\
\
            cambia_tipo_modulo (NULL,LIBUT,NULL);\
            sprintf(nome_e_descr,"%s  %s",nome_nuovo_modulo,descr_nuovo_modulo);\
            setta_label_modsel(nome_e_descr);\
         }\
      }\
      else\
         scrivi_messaggio("FORTRAN generation error!.");\
   }\
   else\
     scrivi_messaggio("Cannot save NEWMOD information (file busy).");\
}\
\
/***\
 *** menu_newmod_init()\
 ***\
 ***   Descrizione:\
 ***     Disabilita alcune voci di menu della dialog-box della NEWMOD.\
 ***     Tali voci di menu vengono attivate qunado l'utente ha premuto\
 ***     OK e le informazioni sono corrette.\
 ***/\
menu_newmod_init()\
{\
/* Disabilita l'accesso alle sezioni USER (I2,JC,D1,resid.,D1) */\
   set_something (UxGetWidget(pb_nmod_I2),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_JC),XmNsensitive, False);\
   set_something (UxGetWidget(pb_nmod_residual),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_D1),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vI2),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vJC),XmNsensitive, False);\
   set_something (UxGetWidget(pb_nmod_vMOD),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vD1),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vI3),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vI4),XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_vC1),XmNsensitive,False);\
\
/* La matrice jacobiana e il salvataggio su file vengono imbibiti */\
   set_something (UxGetWidget(pb_nmod_jactopology), XmNsensitive,False);\
   set_something (UxGetWidget(pb_nmod_save), XmNsensitive,False);\
\
   nmod_def_initialized = False;\
}\
\
/*** quit_newmod()\
 ***\
 ***    Descrizione:\
 ***       Dealloca la memoria utilizzata durante la sessione NEWMOD e \
 ***       ritorna al menu principale.\
 ***/\
quit_newmod()\
{\
   int i,j;\
\
   UxDestroySwidget(nmod_app_shell);\
   nmod_def_managed = False;\
\
   scrivi_messaggio("Deallocating memory ... wait please!");\
\
/* Dealloca la memoria utilizzata per i text-widget delle variabili e dei */\
/* dati geometrici */\
   XtFree(wvar_stato);\
   wvar_stato = NULL;\
\
   XtFree(wvar_algebriche);\
   wvar_algebriche = NULL;\
\
   XtFree(wvar_ingresso);\
   wvar_ingresso = NULL;\
\
   XtFree(wdati_geometrici);\
   wdati_geometrici = NULL;\
   \
/* Deallocazione delle stringhe utilizzate per l'inserimento del codice */\
/* utente ed altro */\
   if (nmod_def_initialized)\
   {\
      XtFree(variabili);\
      variabili = NULL;\
      XtFree(dati_geom);\
      dati_geom = NULL;\
\
      XtFree(str_dichI2);\
      str_dichI2 = NULL;\
\
      XtFree(str_codI2);\
      str_codI2 = NULL;\
\
      XtFree(str_dichJC);\
      str_dichJC = NULL;\
\
      XtFree(str_codJC);\
      str_codJC = NULL;\
\
      for ( i=0 ; i<jac_rows ; i++ )\
         for ( j=0 ; j<jac_cols ; j++ )\
         {\
            XtFree(jactoggstruct[i][j].stringa);\
            jactoggstruct[i][j].stringa = NULL;\
         }\
\
      XtFree(str_dichMOD);\
      str_dichMOD = NULL;\
    \
      XtFree(str_codMOD);\
      str_codMOD = NULL;\
\
      for ( i=0 ; i<MAX_EQUAZIONI ; i++ )\
      {\
         XtFree(str_resMOD[i]);\
         str_resMOD[i] = NULL;\
\
         XtFree(str_signeq[i]);\
         str_signeq[i] = NULL;\
\
         XtFree(str_uniteq[i]);\
         str_uniteq[i] = NULL;\
      \
         XtFree(str_cosnor[i]);  \
         str_cosnor[i] = NULL;\
      }\
   }\
   scrivi_messaggio("Done.");\
}
*nmod_app_shell.name: nmod_app_shell
*nmod_app_shell.x: 172
*nmod_app_shell.y: 58
*nmod_app_shell.width: 650
*nmod_app_shell.height: 600
*nmod_app_shell.title: "NEWMOD - NEW MODULE DEFINITION"
*nmod_app_shell.geometry: "+115+215"
*nmod_app_shell.keyboardFocusPolicy: "explicit"

*nmod_form.class: form
*nmod_form.parent: nmod_app_shell
*nmod_form.static: true
*nmod_form.name: nmod_form
*nmod_form.unitType: "pixels"
*nmod_form.x: 20
*nmod_form.y: 10
*nmod_form.width: 100
*nmod_form.height: 100

*nmod_pb_ok.class: pushButton
*nmod_pb_ok.parent: nmod_form
*nmod_pb_ok.static: true
*nmod_pb_ok.name: nmod_pb_ok
*nmod_pb_ok.x: 20
*nmod_pb_ok.y: 530
*nmod_pb_ok.width: 70
*nmod_pb_ok.height: 30
*nmod_pb_ok.labelString: "Ok"
*nmod_pb_ok.bottomAttachment: "attach_form"
*nmod_pb_ok.bottomOffset: 10
*nmod_pb_ok.leftOffset: 10
*nmod_pb_ok.topAttachment: "attach_none"
*nmod_pb_ok.topOffset: 0
*nmod_pb_ok.activateCallback: {\
if ( controlla_input_def(UxGetWidget(nmod_text_nome), UxGetWidget(nmod_text_descr)) )\
   return;\
else\
{\
   non_salvato = True;\
   sprintf(message," Ok. New module definitions correct.");\
   attention_wdg = (Widget) attention (UxTopLevel,message,MAPPA,geom_attention);   \
   scrivi_messaggio (message);\
\
/* Abilitazione voci di menu jacobiano */\
   set_something (UxGetWidget(pb_nmod_jactopology),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_save),XmNsensitive,True);\
\
/* Abilitazione voci di menu user sections */\
   set_something (UxGetWidget(pb_nmod_I2),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_residual),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_D1),XmNsensitive,True);\
\
/* Se l'utente ha scelto lo jacobiano numerico */\
/* la sezione JC e' inibita */\
   set_something (UxGetWidget(pb_nmod_JC), XmNsensitive,\
                  (jacobian_type == NUMERICAL) ? False : True);\
\
   set_something (UxGetWidget(pb_nmod_vI2),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vJC),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vMOD),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vD1),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vI3),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vI4),XmNsensitive,True);\
   set_something (UxGetWidget(pb_nmod_vC1),XmNsensitive,True);\
\
}\
}

*rowColumn1.class: rowColumn
*rowColumn1.parent: nmod_form
*rowColumn1.static: true
*rowColumn1.name: rowColumn1
*rowColumn1.unitType: "pixels"
*rowColumn1.x: 0
*rowColumn1.y: 0
*rowColumn1.width: 580
*rowColumn1.height: 30
*rowColumn1.leftAttachment: "attach_form"
*rowColumn1.leftOffset: 0
*rowColumn1.rightAttachment: "attach_form"
*rowColumn1.rightOffset: 0
*rowColumn1.topAttachment: "attach_form"
*rowColumn1.topOffset: 0
*rowColumn1.spacing: 20
*rowColumn1.packing: "pack_tight"
*rowColumn1.bottomAttachment: "attach_none"
*rowColumn1.bottomOffset: 0
*rowColumn1.marginHeight: 0
*rowColumn1.marginWidth: 0

*nmod_menubar.class: rowColumn
*nmod_menubar.parent: rowColumn1
*nmod_menubar.static: true
*nmod_menubar.name: nmod_menubar
*nmod_menubar.rowColumnType: "menu_bar"
*nmod_menubar.menuAccelerator: "<KeyUp>F10"
*nmod_menubar.x: 0
*nmod_menubar.y: 0
*nmod_menubar.height: 30
*nmod_menubar.spacing: 20

*mb_nmod_file.class: rowColumn
*mb_nmod_file.parent: nmod_menubar
*mb_nmod_file.static: true
*mb_nmod_file.name: mb_nmod_file
*mb_nmod_file.rowColumnType: "menu_pulldown"

*pb_nmod_save.class: pushButton
*pb_nmod_save.parent: mb_nmod_file
*pb_nmod_save.static: false
*pb_nmod_save.name: pb_nmod_save
*pb_nmod_save.labelString: "Save and Generate FTN"
*pb_nmod_save.mnemonic: "S"
*pb_nmod_save.activateCallback: {\
long offset;\
\
if (controlla_lista_moduli(LIBUT, nome_nuovo_modulo, &offset))\
{\
   sprintf(message,"The module %s already exist. Overwrite it?",\
                   nome_nuovo_modulo);\
   wconfirm_save = (Widget) conferma (UxTopLevel,message,funz_confirm_save); \
}\
else\
   salva_e_genera();\
}

*pb_nmod_quit.class: pushButton
*pb_nmod_quit.parent: mb_nmod_file
*pb_nmod_quit.static: true
*pb_nmod_quit.name: pb_nmod_quit
*pb_nmod_quit.labelString: "Quit"
*pb_nmod_quit.mnemonic: "Q"
*pb_nmod_quit.activateCallback: {\
if (non_salvato && nmod_def_initialized)\
{\
   sprintf(message,"You have made changes.\nDo you wan't save information",\
                   nome_nuovo_modulo);\
   wconfirm_save = (Widget) conferma (UxTopLevel,message,funz_confirm_quit); \
}\
else\
   quit_newmod();\
\
}

*mb_nmod_config.class: rowColumn
*mb_nmod_config.parent: nmod_menubar
*mb_nmod_config.static: true
*mb_nmod_config.name: mb_nmod_config
*mb_nmod_config.rowColumnType: "menu_pulldown"

*pb_nmod_varsetup.class: pushButton
*pb_nmod_varsetup.parent: mb_nmod_config
*pb_nmod_varsetup.static: false
*pb_nmod_varsetup.name: pb_nmod_varsetup
*pb_nmod_varsetup.labelString: "I/O variables setup"
*pb_nmod_varsetup.mnemonic: "v"
*pb_nmod_varsetup.activateCallback: {\
if (!bool_dialog_equation)\
   sprintf(message,"You must close the window of the jacobian configuration!");\
\
if (dbox_userjac_managed)\
   sprintf(message,"You must close the window of the JC subroutine!");\
\
if (dbox_userresid_managed)\
   sprintf(message,"You must close the window of the residual subroutine!");\
\
if (dbox_usereq_managed)\
   sprintf(message,"You must close the window of the D1 subroutine!");\
\
if (!bool_dialog_equation || dbox_userjac_managed || dbox_userresid_managed ||\
    dbox_usereq_managed)\
{\
    attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,geom_attention);\
    return;\
}\
\
if (!bool_dialog_config)\
{\
   scrivi_messaggio ("Setup window already in use.");\
   return;\
}\
\
if (nmod_def_initialized)\
{\
   sprintf(message,"WARNING: Modifications to module setup will result\n");\
   strcat(message,"in resetting jacobian topology. Continue anyway ?");\
   dialog_setup = (Widget) conferma(UxTopLevel,message,rilancia_setup_nmod);\
   XtManageChild (dialog_setup);\
}\
else\
{\
   bool_dialog_config = False;\
   create_nmod_dialog_config();\
}\
}

*pb_nmod_jactopology.class: pushButton
*pb_nmod_jactopology.parent: mb_nmod_config
*pb_nmod_jactopology.static: false
*pb_nmod_jactopology.name: pb_nmod_jactopology
*pb_nmod_jactopology.labelString: "Jacobian matrix topology"
*pb_nmod_jactopology.mnemonic: "t"
*pb_nmod_jactopology.activateCallback: {\
if (dbox_userjac_managed)\
{\
   sprintf(message,"You must close the window of the JC subroutine!");\
   attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,geom_attention);\
   return;\
}\
\
if (bool_dialog_equation)\
{\
   create_dialog_equation();\
   bool_dialog_equation = False;\
}\
\
}

*mb_nmod_user.class: rowColumn
*mb_nmod_user.parent: nmod_menubar
*mb_nmod_user.static: true
*mb_nmod_user.name: mb_nmod_user
*mb_nmod_user.rowColumnType: "menu_pulldown"

*pb_nmod_I2.class: pushButton
*pb_nmod_I2.parent: mb_nmod_user
*pb_nmod_I2.static: true
*pb_nmod_I2.name: pb_nmod_I2
*pb_nmod_I2.labelString: "Data  Section (I2)"
*pb_nmod_I2.mnemonic: "D"
*pb_nmod_I2.activateCallback: {\
if (!dbox_userdata_managed)\
   create_dbox_userdata();\
}

*pb_nmod_JC.class: pushButton
*pb_nmod_JC.parent: mb_nmod_user
*pb_nmod_JC.static: false
*pb_nmod_JC.name: pb_nmod_JC
*pb_nmod_JC.labelString: "Jacobian Section (JC)"
*pb_nmod_JC.mnemonic: "J"
*pb_nmod_JC.activateCallback: {\
if (!dbox_userjac_managed)\
   create_dbox_userjac();\
}

*pb_nmod_residual.class: pushButton
*pb_nmod_residual.parent: mb_nmod_user
*pb_nmod_residual.static: false
*pb_nmod_residual.name: pb_nmod_residual
*pb_nmod_residual.labelString: "Residuals Section"
*pb_nmod_residual.mnemonic: "R"
*pb_nmod_residual.activateCallback: {\
if (!dbox_userresid_managed)\
   create_dbox_userresid();\
}

*pb_nmod_D1.class: pushButton
*pb_nmod_D1.parent: mb_nmod_user
*pb_nmod_D1.static: false
*pb_nmod_D1.name: pb_nmod_D1
*pb_nmod_D1.labelString: "Equations Section (D1)"
*pb_nmod_D1.mnemonic: "E"
*pb_nmod_D1.activateCallback: {\
if (!dbox_usereq_managed)\
   create_dbox_usereq();\
}

*mb_nmod_view.class: rowColumn
*mb_nmod_view.parent: nmod_menubar
*mb_nmod_view.static: true
*mb_nmod_view.name: mb_nmod_view
*mb_nmod_view.rowColumnType: "menu_pulldown"

*pb_nmod_vI2.class: pushButton
*pb_nmod_vI2.parent: mb_nmod_view
*pb_nmod_vI2.static: true
*pb_nmod_vI2.name: pb_nmod_vI2
*pb_nmod_vI2.labelString: "Data Section (I2)"
*pb_nmod_vI2.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[0]);\
   if ((fp = fopen(nomitmp[0],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 0;  /* indice array */\
\
   genmodI2(fp, nome_nuovo_modulo, descr_nuovo_modulo, dati_geom,\
	        num_dati_geometrici, variabili, numero_variabili,\
                str_dichI2, str_codI2);\
\
   fclose(fp);\
\
   weditor[0] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[0], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE I2 (DATA SECTION)");\
   set_something(weditor[0], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*pb_nmod_vI3.class: pushButton
*pb_nmod_vI3.parent: mb_nmod_view
*pb_nmod_vI3.static: true
*pb_nmod_vI3.name: pb_nmod_vI3
*pb_nmod_vI3.labelString: "Variable List Section (I3)"
*pb_nmod_vI3.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[1]);\
   if ((fp = fopen(nomitmp[1],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 1;  /* indice array */\
\
   genmodI3(fp, nome_nuovo_modulo, variabili, numero_variabili,\
                num_var_stato, num_var_algebriche);\
\
   fclose(fp);\
\
   weditor[1] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[1], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE I3 (VARIABLE LIST SECTION)");\
   set_something(weditor[1], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
\
}

*pb_nmod_vI4.class: pushButton
*pb_nmod_vI4.parent: mb_nmod_view
*pb_nmod_vI4.static: true
*pb_nmod_vI4.name: pb_nmod_vI4
*pb_nmod_vI4.labelString: "Subroutine I4"
*pb_nmod_vI4.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[2]);\
   if ((fp = fopen(nomitmp[2],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 2;  /* indice array */\
\
   genmodI4(fp, nome_nuovo_modulo);\
\
   fclose(fp);\
\
   weditor[2] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[2], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE I4");\
   set_something(weditor[2], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*pb_nmod_vC1.class: pushButton
*pb_nmod_vC1.parent: mb_nmod_view
*pb_nmod_vC1.static: true
*pb_nmod_vC1.name: pb_nmod_vC1
*pb_nmod_vC1.labelString: "Residual Evaluation (C1)"
*pb_nmod_vC1.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[3]);\
   if ((fp = fopen(nomitmp[3],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 3;  /* indice array */\
\
   genmodC1(fp, nome_nuovo_modulo, descr_nuovo_modulo, jacobian_type,\
                dati_geom, num_dati_geometrici,\
                variabili, numero_variabili);\
\
   fclose(fp);\
\
   weditor[3] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[3], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE C1 (RESIDUAL EVALUATION)");\
   set_something(weditor[3], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*pb_nmod_vJC.class: pushButton
*pb_nmod_vJC.parent: mb_nmod_view
*pb_nmod_vJC.static: true
*pb_nmod_vJC.name: pb_nmod_vJC
*pb_nmod_vJC.labelString: "Jacobian section (JC)"
*pb_nmod_vJC.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[4]);\
   if ((fp = fopen(nomitmp[4],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 4;  /* indice array */\
\
   genmodJC(fp, nome_nuovo_modulo, dati_geom, num_dati_geometrici,\
                variabili, numero_variabili, num_var_stato, num_var_algebriche,\
                jactoggstruct, str_dichJC, str_codJC);\
\
   fclose(fp);\
\
   weditor[4] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[4], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE JC (JACOBIAN SECTION)");\
   set_something(weditor[4], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*pb_nmod_vMOD.class: pushButton
*pb_nmod_vMOD.parent: mb_nmod_view
*pb_nmod_vMOD.static: true
*pb_nmod_vMOD.name: pb_nmod_vMOD
*pb_nmod_vMOD.labelString: "Residual Section"
*pb_nmod_vMOD.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[5]);\
   if ((fp = fopen(nomitmp[5],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 5;  /* indice array */\
\
   genmodMOD(fp, nome_nuovo_modulo, descr_nuovo_modulo, dati_geom,\
	        num_dati_geometrici, variabili, numero_variabili,num_var_stato,\
	        num_var_algebriche, str_dichMOD, str_codMOD, str_resMOD);\
\
   fclose(fp);\
\
   weditor[5] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[5], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE RESIDUAL");\
   set_something(weditor[5], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*pb_nmod_vD1.class: pushButton
*pb_nmod_vD1.parent: mb_nmod_view
*pb_nmod_vD1.static: true
*pb_nmod_vD1.name: pb_nmod_vD1
*pb_nmod_vD1.labelString: "Equations Section (D1)"
*pb_nmod_vD1.activateCallback: {\
   FILE *fp;\
   int numero_variabili;\
\
   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;\
\
/* nome file temporaneo */\
   tmpnam(nomitmp[6]);\
   if ((fp = fopen(nomitmp[6],"w")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file!");\
      return;\
   }\
\
   funz_editor[0].parametro = 6;  /* indice array */\
\
   genmodD1(fp, nome_nuovo_modulo, descr_nuovo_modulo, variabili, \
		numero_variabili, num_var_stato, num_var_algebriche,\
		jactoggstruct, str_signeq, str_uniteq, str_cosnor);\
\
   fclose(fp);\
\
   weditor[6] = (Widget) editor(UxTopLevel, &wtxteditor, nomitmp[6], False,\
                                font, funz_editor, geom_editor);\
   cstring = CREATE_CSTRING("VIEW SUBROUTINE D1 (EQUATION SECTION)");\
   set_something(weditor[6], XmNdialogTitle, cstring);\
   XmStringFree(cstring);\
}

*menu1_top_b3.class: cascadeButtonGadget
*menu1_top_b3.parent: nmod_menubar
*menu1_top_b3.static: true
*menu1_top_b3.name: menu1_top_b3
*menu1_top_b3.labelString: "File"
*menu1_top_b3.subMenuId: "mb_nmod_file"
*menu1_top_b3.mnemonic: "F"

*menu1_top_b4.class: cascadeButtonGadget
*menu1_top_b4.parent: nmod_menubar
*menu1_top_b4.static: true
*menu1_top_b4.name: menu1_top_b4
*menu1_top_b4.labelString: "Module configuration"
*menu1_top_b4.mnemonic: "M"
*menu1_top_b4.subMenuId: "mb_nmod_config"

*nmod_menubar_top_b1.class: cascadeButtonGadget
*nmod_menubar_top_b1.parent: nmod_menubar
*nmod_menubar_top_b1.static: true
*nmod_menubar_top_b1.name: nmod_menubar_top_b1
*nmod_menubar_top_b1.labelString: "User"
*nmod_menubar_top_b1.mnemonic: "U"
*nmod_menubar_top_b1.subMenuId: "mb_nmod_user"

*nmod_menubar_top_b2.class: cascadeButtonGadget
*nmod_menubar_top_b2.parent: nmod_menubar
*nmod_menubar_top_b2.static: true
*nmod_menubar_top_b2.name: nmod_menubar_top_b2
*nmod_menubar_top_b2.labelString: "View code"
*nmod_menubar_top_b2.subMenuId: "mb_nmod_view"
*nmod_menubar_top_b2.mnemonic: "V"

*nmod_label_nome.class: label
*nmod_label_nome.parent: nmod_form
*nmod_label_nome.static: true
*nmod_label_nome.name: nmod_label_nome
*nmod_label_nome.x: 10
*nmod_label_nome.y: 30
*nmod_label_nome.width: 100
*nmod_label_nome.height: 30
*nmod_label_nome.alignment: "alignment_beginning"
*nmod_label_nome.labelString: "Module name:"
*nmod_label_nome.topOffset: 15
*nmod_label_nome.topAttachment: "attach_widget"
*nmod_label_nome.topWidget: "rowColumn1"

*nmod_text_nome.class: text
*nmod_text_nome.parent: nmod_form
*nmod_text_nome.static: true
*nmod_text_nome.name: nmod_text_nome
*nmod_text_nome.x: 130
*nmod_text_nome.y: 30
*nmod_text_nome.width: 80
*nmod_text_nome.height: 35
*nmod_text_nome.columns: 4
*nmod_text_nome.leftAttachment: "attach_widget"
*nmod_text_nome.leftOffset: 5
*nmod_text_nome.leftWidget: "nmod_label_nome"
*nmod_text_nome.topOffset: 10
*nmod_text_nome.maxLength: 4
*nmod_text_nome.topAttachment: "attach_widget"
*nmod_text_nome.topWidget: "rowColumn1"
*nmod_text_nome.modifyVerifyCallback.source: public
*nmod_text_nome.modifyVerifyCallback: text_maius_callback

*nmod_label_descr.class: label
*nmod_label_descr.parent: nmod_form
*nmod_label_descr.static: true
*nmod_label_descr.name: nmod_label_descr
*nmod_label_descr.x: 230
*nmod_label_descr.y: 30
*nmod_label_descr.width: 90
*nmod_label_descr.height: 30
*nmod_label_descr.alignment: "alignment_beginning"
*nmod_label_descr.labelString: "Description:"
*nmod_label_descr.leftAttachment: "attach_widget"
*nmod_label_descr.leftOffset: 15
*nmod_label_descr.leftWidget: "nmod_text_nome"
*nmod_label_descr.topOffset: 15
*nmod_label_descr.topAttachment: "attach_widget"
*nmod_label_descr.topWidget: "rowColumn1"

*nmod_text_descr.class: text
*nmod_text_descr.parent: nmod_form
*nmod_text_descr.static: true
*nmod_text_descr.name: nmod_text_descr
*nmod_text_descr.x: 330
*nmod_text_descr.y: 30
*nmod_text_descr.width: 250
*nmod_text_descr.height: 35
*nmod_text_descr.columns: 50
*nmod_text_descr.leftAttachment: "attach_widget"
*nmod_text_descr.leftOffset: 5
*nmod_text_descr.leftWidget: "nmod_label_descr"
*nmod_text_descr.rightAttachment: "attach_form"
*nmod_text_descr.rightOffset: 10
*nmod_text_descr.topOffset: 10
*nmod_text_descr.maxLength: 50
*nmod_text_descr.topAttachment: "attach_widget"
*nmod_text_descr.topWidget: "rowColumn1"

*nmod_sep1.class: separatorGadget
*nmod_sep1.parent: nmod_form
*nmod_sep1.static: true
*nmod_sep1.name: nmod_sep1
*nmod_sep1.x: 10
*nmod_sep1.y: 70
*nmod_sep1.width: 564
*nmod_sep1.height: 2
*nmod_sep1.rightAttachment: "attach_form"
*nmod_sep1.rightOffset: 10
*nmod_sep1.topAttachment: "attach_widget"
*nmod_sep1.topOffset: 10
*nmod_sep1.topWidget: "nmod_label_nome"
*nmod_sep1.leftAttachment: "attach_form"
*nmod_sep1.leftOffset: 10

*nmod_menu_opt.class: rowColumn
*nmod_menu_opt.parent: nmod_form
*nmod_menu_opt.static: true
*nmod_menu_opt.name: nmod_menu_opt
*nmod_menu_opt.unitType: "pixels"
*nmod_menu_opt.x: 20
*nmod_menu_opt.y: 110
*nmod_menu_opt.width: 200
*nmod_menu_opt.height: 35
*nmod_menu_opt.leftOffset: 10
*nmod_menu_opt.topAttachment: "attach_widget"
*nmod_menu_opt.topOffset: 10
*nmod_menu_opt.topWidget: "nmod_sep1"
*nmod_menu_opt.leftAttachment: "attach_form"
*nmod_menu_opt.marginHeight: 0
*nmod_menu_opt.marginWidth: 0
*nmod_menu_opt.spacing: 0
*nmod_menu_opt.whichButton: 1

*nmod_menu1.class: rowColumn
*nmod_menu1.parent: nmod_menu_opt
*nmod_menu1.static: true
*nmod_menu1.name: nmod_menu1
*nmod_menu1.rowColumnType: "menu_option"
*nmod_menu1.subMenuId: "nmod_menu_p1"
*nmod_menu1.x: 0
*nmod_menu1.y: -10
*nmod_menu1.height: 35
*nmod_menu1.width: 200
*nmod_menu1.marginHeight: 0
*nmod_menu1.marginWidth: 0
*nmod_menu1.spacing: 0
*nmod_menu1.whichButton: 1
*nmod_menu1.menuHistory: "opt_all"

*nmod_menu_p1.class: rowColumn
*nmod_menu_p1.parent: nmod_menu1
*nmod_menu_p1.static: true
*nmod_menu_p1.name: nmod_menu_p1
*nmod_menu_p1.rowColumnType: "menu_pulldown"
*nmod_menu_p1.height: 35
*nmod_menu_p1.width: 200

*opt_stato.class: pushButton
*opt_stato.parent: nmod_menu_p1
*opt_stato.static: true
*opt_stato.name: opt_stato
*opt_stato.labelString: "State output variables"
*opt_stato.activateCallback: {\
cambia_tipo_text(UxGetWidget(nmod_bboard), K_OPT_STATO, True);\
}
*opt_stato.mnemonic: "S"

*opt_ingresso.class: pushButton
*opt_ingresso.parent: nmod_menu_p1
*opt_ingresso.static: true
*opt_ingresso.name: opt_ingresso
*opt_ingresso.labelString: "Algebraic output variables"
*opt_ingresso.activateCallback: {\
cambia_tipo_text(UxGetWidget(nmod_bboard), K_OPT_ALGEBRAIC, True);\
}
*opt_ingresso.mnemonic: "g"

*opt_out.class: pushButton
*opt_out.parent: nmod_menu_p1
*opt_out.static: true
*opt_out.name: opt_out
*opt_out.labelString: "Input variables"
*opt_out.activateCallback: {\
cambia_tipo_text(UxGetWidget(nmod_bboard), K_OPT_INGRESSO, True);\
}
*opt_out.mnemonic: "I"

*opt_all.class: pushButton
*opt_all.parent: nmod_menu_p1
*opt_all.static: true
*opt_all.name: opt_all
*opt_all.labelString: "All variables"
*opt_all.activateCallback: {\
cambia_tipo_text(UxGetWidget(nmod_bboard), K_OPT_ALL, True);\
}
*opt_all.mnemonic: "A"

*nmod_menu_p1_b6.class: separator
*nmod_menu_p1_b6.parent: nmod_menu_p1
*nmod_menu_p1_b6.static: true
*nmod_menu_p1_b6.name: nmod_menu_p1_b6

*opt_dati.class: pushButton
*opt_dati.parent: nmod_menu_p1
*opt_dati.static: true
*opt_dati.name: opt_dati
*opt_dati.labelString: "Geometrical data"
*opt_dati.activateCallback: {\
cambia_tipo_text(UxGetWidget(nmod_bboard), K_OPT_DATI,True);\
}
*opt_dati.mnemonic: "d"

*nmod_sep2.class: separatorGadget
*nmod_sep2.parent: nmod_form
*nmod_sep2.static: true
*nmod_sep2.name: nmod_sep2
*nmod_sep2.x: 10
*nmod_sep2.y: 150
*nmod_sep2.width: 564
*nmod_sep2.height: 7
*nmod_sep2.leftAttachment: "attach_form"
*nmod_sep2.leftOffset: 10
*nmod_sep2.rightAttachment: "attach_form"
*nmod_sep2.rightOffset: 10
*nmod_sep2.topAttachment: "attach_widget"
*nmod_sep2.topOffset: 10
*nmod_sep2.topWidget: "nmod_menu_opt"

*nmod_label_tit1.class: label
*nmod_label_tit1.parent: nmod_form
*nmod_label_tit1.static: false
*nmod_label_tit1.name: nmod_label_tit1
*nmod_label_tit1.x: 20
*nmod_label_tit1.y: 210
*nmod_label_tit1.width: 140
*nmod_label_tit1.height: 20
*nmod_label_tit1.alignment: "alignment_beginning"
*nmod_label_tit1.labelString: "Description"
*nmod_label_tit1.leftAttachment: "attach_form"
*nmod_label_tit1.leftOffset: 20
*nmod_label_tit1.topAttachment: "attach_widget"
*nmod_label_tit1.topOffset: 10
*nmod_label_tit1.topWidget: "nmod_sep2"

*nmod_label_tit2.class: label
*nmod_label_tit2.parent: nmod_form
*nmod_label_tit2.static: false
*nmod_label_tit2.name: nmod_label_tit2
*nmod_label_tit2.x: 270
*nmod_label_tit2.y: 210
*nmod_label_tit2.height: 20
*nmod_label_tit2.alignment: "alignment_beginning"
*nmod_label_tit2.labelString: "FORTRAN symbol"
*nmod_label_tit2.topAttachment: "attach_widget"
*nmod_label_tit2.topOffset: 10
*nmod_label_tit2.topWidget: "nmod_sep2"

*nmod_label_tit3.class: label
*nmod_label_tit3.parent: nmod_form
*nmod_label_tit3.static: false
*nmod_label_tit3.name: nmod_label_tit3
*nmod_label_tit3.x: 420
*nmod_label_tit3.y: 210
*nmod_label_tit3.width: 130
*nmod_label_tit3.height: 20
*nmod_label_tit3.alignment: "alignment_beginning"
*nmod_label_tit3.labelString: "normalization value"
*nmod_label_tit3.topAttachment: "attach_widget"
*nmod_label_tit3.topOffset: 10
*nmod_label_tit3.topWidget: "nmod_sep2"

*nmod_scroll_window.class: scrolledWindow
*nmod_scroll_window.parent: nmod_form
*nmod_scroll_window.static: true
*nmod_scroll_window.name: nmod_scroll_window
*nmod_scroll_window.scrollingPolicy: "automatic"
*nmod_scroll_window.unitType: "pixels"
*nmod_scroll_window.x: 10
*nmod_scroll_window.y: 200
*nmod_scroll_window.width: 564
*nmod_scroll_window.height: 327
*nmod_scroll_window.leftOffset: 10
*nmod_scroll_window.rightAttachment: "attach_form"
*nmod_scroll_window.rightOffset: 10
*nmod_scroll_window.leftAttachment: "attach_form"
*nmod_scroll_window.bottomAttachment: "attach_widget"
*nmod_scroll_window.bottomOffset: 10
*nmod_scroll_window.bottomWidget: "nmod_pb_ok"
*nmod_scroll_window.topAttachment: "attach_widget"
*nmod_scroll_window.topOffset: 10
*nmod_scroll_window.topWidget: "nmod_label_tit1"

*nmod_bboard.class: bulletinBoard
*nmod_bboard.parent: nmod_scroll_window
*nmod_bboard.static: false
*nmod_bboard.name: nmod_bboard
*nmod_bboard.resizePolicy: "resize_any"
*nmod_bboard.unitType: "pixels"
*nmod_bboard.x: 0
*nmod_bboard.y: 0
*nmod_bboard.width: 1
*nmod_bboard.height: 1
*nmod_bboard.createCallback: {\
\
}

