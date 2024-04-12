! UIMX ascii 2.0 key: 4147                                                      

*abox_file_selection.class: applicationShell
*abox_file_selection.parent: NO_PARENT
*abox_file_selection.static: false
*abox_file_selection.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo abox_file_selection.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)abox_file_selection.i	2.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#include <unistd.h>\
#include <X11/Xlib.h>\
#include <X11/Intrinsic.h>\
\
#ifndef LIBICOFILE\
#include <file_icone.h>\
#define LIBICOFILE\
#endif\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
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
extern Widget attention_wdg;\
extern Dialog_geometry geom_attention;\
\
extern Display *display;\
\
/****************************************************************/\
/* VARIABILI GLOBALI						*/\
/****************************************************************/\
\
char *path_altro_utente;\
\
/* flag che indica se la file selection box e' managed */\
Boolean dbox_fileselect_managed = False;\
\
/* flag che indica se la lista dei moduli e' managed */\
Boolean dbox_list_utente_managed = False;
*abox_file_selection.ispecdecl:
*abox_file_selection.funcdecl: swidget create_file_selection()\

*abox_file_selection.funcname: create_file_selection
*abox_file_selection.funcdef: "swidget", "<create_file_selection>(%)"
*abox_file_selection.icode: Widget wdg;\
   char *path_home, path[256];
*abox_file_selection.fcode: /* Il push-button di 'HELP' ed il text di selezione non vengono visualizzati */\
\
   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),\
                                    XmDIALOG_HELP_BUTTON);\
   XtUnmanageChild (wdg);\
\
   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),\
                                    XmDIALOG_TEXT);\
   XtUnmanageChild (wdg);\
\
   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),\
                                    XmDIALOG_FILTER_TEXT);\
\
/***\
   XtUnmanageChild (wdg);\
***/\
\
/* la scroll-list dei files non viene abilitata per la selezione */\
/* (guardare ma non toccare ...) */\
\
#ifdef CERCA_ERR\
   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),XmDIALOG_LIST);\
   XSelectInput(display, XtWindow(wdg), ExposureMask);\
#endif\
\
   UxPopupInterface (rtrn, no_grab);\
   dbox_fileselect_managed = True;\
\
   return(rtrn);\

*abox_file_selection.auxdecl:
*abox_file_selection.name: abox_file_selection
*abox_file_selection.x: 250
*abox_file_selection.y: 185
*abox_file_selection.width: 400
*abox_file_selection.height: 400
*abox_file_selection.geometry: "+140+255"

*fileSelectionBox1.class: fileSelectionBox
*fileSelectionBox1.parent: abox_file_selection
*fileSelectionBox1.static: false
*fileSelectionBox1.name: fileSelectionBox1
*fileSelectionBox1.unitType: "pixels"
*fileSelectionBox1.x: 250
*fileSelectionBox1.y: 185
*fileSelectionBox1.width: 380
*fileSelectionBox1.height: 380
*fileSelectionBox1.pattern: ""
*fileSelectionBox1.dialogTitle: "MODULE COPY"
*fileSelectionBox1.cancelCallback: {\
dbox_fileselect_managed = False;\
UxDestroyInterface(UxWidget);\
}
*fileSelectionBox1.defaultPosition: "false"
*fileSelectionBox1.okCallback: {\
   XmFileSelectionBoxCallbackStruct *fboxstruct;\
   char path_lista_moduli[256];\
   FILE *fp;\
   byte tipo_lib;\
\
   tipo_lib = (byte) UxClientData;\
\
   fboxstruct = (XmFileSelectionBoxCallbackStruct *) UxCallbackArg;\
\
   path_altro_utente = extract_string(fboxstruct->dir);\
   printf("directory selezionata: %s\n", path_altro_utente);\
\
#ifdef VMS\
   sottodir_vms(path_lista_moduli, path_altro_utente, \
                sottodir_utente(tipo_lib, LIB_UTENTE));\
#else\
   sprintf(path_lista_moduli,"%s%s/",path_altro_utente, \
                                   sottodir_utente(tipo_lib, LIB_UTENTE));\
#endif\
\
   switch (tipo_lib)\
   {\
      case LIBUT:\
           strcat(path_lista_moduli, FILE_DATI_LIBUT);\
           break;\
\
      case LIBUTREG:\
           strcat(path_lista_moduli, FILE_DATI_LIBUTREG);\
           break;\
\
      case LIBREG:\
           strcat(path_lista_moduli, FILE_DATI_LIBREG);\
           break;\
   }\
\
   if (access(path_lista_moduli, F_OK))\
   {\
      sprintf(message,"data file %s doesn't exist.",path_lista_moduli);\
      attention_wdg =  (Widget) attention (UxTopLevel,message,MAPPA,\
                                           geom_attention);\
      scrivi_messaggio(message);\
      return;\
   }\
\
   if ((fp = fopen(path_lista_moduli,"r")) == NULL)\
   {\
      sprintf(message,"Can't open data file %s",path_lista_moduli);\
      attention_wdg =  (Widget) attention (UxTopLevel,message,MAPPA,\
                                           geom_attention);\
      scrivi_messaggio(message);\
      return;\
   }\
\
   create_lista_moduli(fp, tipo_lib, USER_MODULES_SELECTION, \
                       &dbox_list_utente_managed);\
   fclose(fp);\
\
/* Cancellazione della FileSelectionBox */\
   dbox_fileselect_managed = False;\
   UxDestroyInterface(UxWidget);\
\
}
*fileSelectionBox1.noMatchString: "<NO FILES FOUND>"
*fileSelectionBox1.selectionLabelString: "Select the directory of another LEGOCAD user"
*fileSelectionBox1.textString: ""
*fileSelectionBox1.okCallbackClientData: (XtPointer) tipo_modulo

