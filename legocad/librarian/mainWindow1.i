! UIMX ascii 2.0 key: 5270                                                      

*mainWindow1.class: applicationShell
*mainWindow1.parent: NO_PARENT
*mainWindow1.static: false
*mainWindow1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo mainWindow1.i\
   tipo \
   release 2.24\
   data 5/9/95\
   reserved @(#)mainWindow1.i	2.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
#include <signal.h>\
#include <unistd.h>\
#include <sys/stat.h>\
#include <Xm/Xm.h>\
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
/* 12-1-95 Micheletti */\
#include <aggiunte.h>\
\
/* hyperhelp e' solo su decalpha */\
#ifdef HYPERHELP_USED\
#include "winhelp.h"\
#endif\
\
#define LIBENV "librarian_debug.cfg"\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE					*/\
/****************************************************************/\
\
extern Display *display;\
extern Arg args[];\
extern Cardinal argcount;\
\
extern char *path_legocad, *path_lego, *path_rego;\
extern Boolean nmod_def_managed;\
extern Boolean nmod_def_managed;\
extern Boolean dbox_fileselect_managed;\
extern Boolean dbox_doc_managed;\
\
/* Array di compound strings */\
extern XmString cstrings[], cstring, cstring_null;\
\
extern char message[];\
\
/* Variabili globali del modulo */\
extern char nome_modulo[], descr_modulo[];\
\
extern IconFileRec record;\
\
extern char file_jac_temp[];\
extern Dialog_geometry geom_editor;\
\
extern Widget dialog_test_env;\
\
/****************************************************************/\
/* VARIABILI GLOBALI						*/\
/****************************************************************/\
\
/* Struttura per l'editing del FORTRAN del modulo. */\
/* Per adesso, e' permessa l'editazione di un modulo per volta e quindi */\
/* l'array e' dimensionato a 1. Se in futuro si vuole avere piu' finestre */\
/* di editing contemporaneamente bisogna dimensionare tale array e apportare */\
/* alcune modifiche alla Callback della voce di menu EDIT CODE */\
EditFtnStruct edit_struct[1];\
\
/* Nomi dei percorsi delle varie librerie */\
char *path_librerie[] = {  PATH_LIBUT_UTE,    PATH_LIBUT_STD,\
			   PATH_LIBUTREG_UTE, PATH_LIBUTREG_STD,\
			   PATH_LIBREG_UTE,   PATH_LIBREG_STD,\
			   PATH_LIBGRAF_UTE,  PATH_LIBGRAF_STD  };\
\
\
char *font = "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1";\
\
/*** Questo tipo di specificazione provoca su Alfa il kill dell'XServer\
char *font = "-Adobe-Courier-Bold-R-Normal--14-140-*";\
***/\
XFontStruct *finfo;\
XmFontList fontList;\
\
Find_struct parametri_userlist;\
\
byte tipo_modulo = -1;\
\
Boolean menu_sbloccato;\
Boolean fine_edicole = True;\
Boolean dbox_code_managed, dbox_listamod_managed = False;\
\
Widget dialog_delete;\
Widget weditcode, wwinedit;\
\
/***************************************************/\
/* Struttura di callback per gli widget di conferma*/\
/***************************************************/\
\
static Elenco_callback cancella_modulo = {\
	{"Yes", delete_module, YES },\
	{"No" , delete_module, NO  },\
	{ NULL, NULL,   NULL       }};\
\
/***************************************************/\
/* Callback editor codice FORTRAN		   */\
/***************************************************/\
\
static Elenco_callback funz_edit_code = {\
        {"Ok",    edit_code_callback, C_OK },\
        {"Apply", edit_code_callback, C_APPLY },\
        {"Cancel",edit_code_callback, C_CANCEL }};
*mainWindow1.ispecdecl:
*mainWindow1.funcdecl: swidget create_mainWindow1()\

*mainWindow1.funcname: create_mainWindow1
*mainWindow1.funcdef: "swidget", "<create_mainWindow1>(%)"
*mainWindow1.icode: Widget userlist_find_form;\
FILE *fp;
*mainWindow1.fcode: /* Creazione Font per Text */\
   finfo = XLoadQueryFont(XtDisplay(UxGetWidget(mainWindow1)),font);\
   fontList = XmFontListCreate (finfo,XmSTRING_DEFAULT_CHARSET);\
\
/* Inserimento find di libreria */\
   parametri_userlist.ID_lista = UxGetWidget(lista_moduli_utente);\
   parametri_userlist.num_elem = 100;\
   parametri_userlist.vis_elem = 1;\
   parametri_userlist.pos      = 0;\
\
   argcount=0;\
   XtSetArg(args[argcount],XmNleftAttachment,XmATTACH_FORM);\
   argcount++;\
   XtSetArg(args[argcount],XmNleftOffset,0);\
   argcount++;\
   XtSetArg(args[argcount],XmNrightAttachment,XmATTACH_FORM);\
   argcount++;\
   XtSetArg(args[argcount],XmNrightOffset,0);\
   argcount++;\
   XtSetArg(args[argcount],XmNbottomAttachment,XmATTACH_FORM);\
   argcount++;\
   XtSetArg(args[argcount],XmNbottomOffset,0);\
   argcount++;\
   XtSetArg(args[argcount],XmNtopAttachment,XmATTACH_FORM);\
   argcount++;\
   XtSetArg(args[argcount],XmNtopOffset,0);\
   argcount++;\
   userlist_find_form = find_kit (UxGetWidget(form12),args,argcount,\
                                  &parametri_userlist);\
\
/* Visualizza la lista dei moduli della libreria LIBUT */\
   cambia_tipo_modulo(NULL, LIB_UTENTE, NULL);\
\
/* debug in compilazione moduli */\
   get_debug();\
\
   UxPopupInterface(rtrn, no_grab);\
   return(rtrn);
*mainWindow1.auxdecl: /*** get_debug()\
 ***\
 ***/\
get_debug()\
{\
   extern int scrivi_messaggio();\
   char varenv[256];\
   FILE *fenv; \
\
   strcpy(varenv,"");\
\
   if( (fenv = fopen(LIBENV,"r")) != NULL)\
   {\
       fscanf(fenv,"%s",varenv);\
       fclose(fenv);\
   }\
   else\
   {\
      if( getenv("LEGOCAD_MOD_DEBUG") != NULL )\
         strcpy(varenv,getenv("LEGOCAD_MOD_DEBUG")); \
   } \
\
   if( strcmp(varenv,"YES") == 0 )\
   {\
       XmToggleButtonSetState(tb_debug,True,True);\
   }\
   else if( strcmp(varenv,"NO") == 0 )\
       XmToggleButtonSetState(tb_debug,False,True);\
   else\
   {\
       scrivi_messaggio("Environment variable LEGOCAD_MOD_DEBUG  not set assume default = YES"); \
       XmToggleButtonSetState(tb_debug,True,True);\
   }\
\
}\
\
/*** set_debug(Boolean)\
 ***\
 ***/\
\
set_debug(Boolean yes)\
{\
  Boolean cista=False;\
  char *dove= NULL;\
  char varenv[256]; \
  static char var[256],var2[256];\
\
\
  strcpy(varenv,"");\
  if( getenv("F_FLAGS") != NULL)\
     strcpy(varenv,getenv("F_FLAGS")); \
  strcpy(var,"");\
  strcpy(var2,"");\
\
  if( (dove=strstr(varenv,"-g")) != NULL )\
     cista = True;\
\
  if(yes && !cista )\
  {\
     strcat(varenv," -g");\
  }\
  else if( !yes && cista )\
  {\
     dove[0] = ' ';\
     dove[1] = ' ';    \
  }\
   \
  sprintf(var,"F_FLAGS=%s",varenv);\
\
  putenv(var);\
\
  if( yes )\
    sprintf(var2,"LEGOCAD_MOD_DEBUG=YES");\
  else \
    sprintf(var2,"LEGOCAD_MOD_DEBUG=NO");\
\
printf("settata LEGOCAD_MOD_DEBUG=%s\n",getenv("LEGOCAD_MOD_DEBUG"));\
\
  putenv(var2);\
\
}\
    \
force_compile(Boolean yes)\
{\
   char path[200];\
\
   percorso_libreria(path,LIBUT,LIB_UTENTE);\
}\
 \
/*** scrivi_messaggio(message)\
 ***  Parametri : \
 ***    char *message: messaggio da visualizzare.\
 ***\
 ***  Descrizione:\
 ***    Visualizza il messaggio nella scroll-list dei messaggi della\
 ***    main-window.\
 ***/\
scrivi_messaggio(message)\
char *message;\
{\
    XmTextPosition pos;\
\
    pos = XmTextGetLastPosition(UxGetWidget(finestra_messaggi));\
    XmTextInsert(UxGetWidget(finestra_messaggi),pos, message);\
    XmTextInsert(UxGetWidget(finestra_messaggi),pos+strlen(message),"\n");\
    XmTextSetInsertionPosition(UxGetWidget(finestra_messaggi),\
                               pos+strlen(message)+1);\
}\
\
/*** menu_modulo_non_attivo()\
 *** \
 *** Descrizione:\
 ***   Disattiva alcune voci di menu della main-window nel caso in cui non\
 ***   e' selezionato nessun modulo.\
 ***/\
menu_modulo_non_attivo ()\
{\
\
   set_something (UxGetWidget(pb_edit_ftn),XmNsensitive,False);\
   set_something (UxGetWidget(pb_modify_newmod),XmNsensitive,False);\
   set_something (UxGetWidget(pb_delete),XmNsensitive,False);\
   set_something (UxGetWidget(pb_edicole),XmNsensitive,False);\
/***\
   set_something (UxGetWidget(pb_library),XmNsensitive,False);\
***/\
   menu_sbloccato = False;\
}\
\
\
/*** menu_modulo_attivo()\
 ***\
 *** Descrizione:\
 ***   Attiva alcune voci di menu della main-window nel caso in cui si e'\
 ***   selezionato un modulo.\
 ***/\
menu_modulo_attivo ()\
{\
   set_something (UxGetWidget(pb_edit_ftn),XmNsensitive,True);\
   set_something (UxGetWidget(pb_delete),XmNsensitive,True);\
   set_something (UxGetWidget(pb_edicole),XmNsensitive,True);\
   set_something (UxGetWidget(pb_library),XmNsensitive,True);\
\
/* Abilita la modifica con la NEWMOD nel caso dei moduli di processo */\
   if (tipo_modulo == LIBUT)\
      set_something (UxGetWidget(pb_modify_newmod),XmNsensitive,True);\
\
   menu_sbloccato = True;\
}\
\
/*** delete_module(w,risposta,call_data)\
 ***  Parametri:\
 ***    Widget w: widget\
 ***    int risposta : YES o NO.\
 ***    XmAnyCallbackStruct *call_data : non utilizzato.\
 ***\
 ***  Descrizione:\
 ***    Callback chiamata premendo i Buttons nella dbox di conferma\
 ***    cancellazione di un modulo.\
 ***    Cancella i file del modulo e delle eventuali icone, aggiornando le\
 ***    rispettive liste.\
 ***/\
void delete_module(w,risposta,call_data)\
Widget w;\
int risposta;\
XmAnyCallbackStruct *call_data;\
{\
   char file_to_cancel[256];\
\
   if (risposta == YES)\
   {\
   /* Compongo il nome del file FORTRAN da cancellare */\
      componi_file_modulo(file_to_cancel,nome_modulo,FILE_FTN,tipo_modulo,\
                          LIB_UTENTE);\
\
   /* Cancello il modulo FORTRAN */\
      if (!unlink(file_to_cancel))\
      {\
         sprintf (message," Module %s erased !", nome_modulo);\
         scrivi_messaggio(message);\
      }\
      else\
      {\
         sprintf(message," Couldn't delete file %s. Failure.",file_to_cancel);\
         scrivi_messaggio (message);\
      }\
\
   /* Cancellazione del file INTERFACCIA nel caso libreria moduli processo */\
   /* (LIBUT) */\
      if (tipo_modulo == LIBUT)\
      {\
         componi_file_modulo(file_to_cancel,nome_modulo,FILE_IFACE,tipo_modulo,\
                             LIB_UTENTE);\
\
         if (access(file_to_cancel, F_OK) == 0)\
            unlink(file_to_cancel);\
      }\
\
   /* Cancellazione dei files con estensione DAT e _01.DAT nel caso libreria */\
   /* moduli di regolazione (LIBUTREG) */\
      if (tipo_modulo == LIBUTREG)\
      {\
         componi_file_modulo(file_to_cancel,nome_modulo,FILE_DAT,tipo_modulo,\
                             LIB_UTENTE);\
\
         unlink(file_to_cancel);\
\
         componi_file_modulo(file_to_cancel,nome_modulo,FILE_01DAT,tipo_modulo,\
                             LIB_UTENTE);\
\
         unlink(file_to_cancel);\
      }\
\
   /* Cancello la riga corrispondente nel file lista moduli (processo o */\
   /* regolazione). */\
      if ( cancella_modulo_lista(tipo_modulo) )\
         scrivi_messaggio (" Module row undeleted. Failure.");\
\
   /*************************************************************************/\
   /*   N.B. CANCELLARE ANCHE ICONE E RECORD ICON_LIST (moduli di PROCESSO) */\
   /*************************************************************************/\
      if ( tipo_modulo == LIBUT )\
         if (cancella_record_file_ico(nome_modulo,LIB_UTENTE) == RETURN_ERROR)\
            scrivi_messaggio (" Icon record undeleted. Failure.\n");\
\
   /* nessun modulo selezionato */\
      unselect_module();\
\
   /* Visualizza la lista dei moduli aggiornata */\
      cambia_tipo_modulo(NULL, tipo_modulo, NULL);\
   }\
\
   XtDestroyWidget(dialog_delete);\
}\
\
/*** cancella_modulo_lista(tipo_lib)\
 ***   Parametri:\
 ***     byte tipo_lib : tipo libreria (LIBUT, LIBUTREG o LIBREG)\
 ***\
 ***   Descrizione:\
 ***     Cancellazione della riga di un modulo nel file lista moduli\
 ***     (processo o regolazione).\
 ***/\
cancella_modulo_lista(tipo_lib)\
byte tipo_lib;\
{\
   FILE *fp, *fp_tmp;\
   char buffer[81], file_tmp[256], file_lista[256];\
   char flag;\
\
/* recupera il nome del file dati della libreria corretta */\
   file_dati_lib(file_lista, tipo_lib, LIB_UTENTE);\
\
   if ((fp = fopen(file_lista,"r")) == NULL)\
   {\
      sprintf(buffer,"Can't open file %s for deleting line.",FILE_DATI_LIBUT);\
      scrivi_messaggio(buffer);\
      return (-1);\
   }\
\
   if ((fp_tmp = fopen(tmpnam(file_tmp),"w+")) == NULL)\
   {\
      scrivi_messaggio("Can't open temporary file for deleting line.");\
      return (-1);\
   }\
\
   while (fgets(buffer,80,fp) != NULL)\
      if (strncmp(buffer,nome_modulo,4))\
         fputs (buffer,fp_tmp);\
\
   fclose (fp);\
   fclose (fp_tmp);\
\
   flag = copia_file (file_tmp, file_lista);\
   unlink (file_tmp);\
\
   if ( flag != 0)\
   {\
      scrivi_messaggio ("Couldn't hold file copy. Failure.");\
      return (-1);\
   }\
\
   return (0);\
}\
\
\
/*------------------------------------------------------------\
 *  esiste_foraux\
 *\
 *   carica in meoria il file fortan del modulo 'nome_modulo' \
 *   dalla libreria utente e verifica se e' presente il \
 *   fortran ausiliario.\
 *\
 *----------------------------------------------------------*/\
 \
int esiste_foraux(char *nome_modulo)\
{\
   FILE *fp;\
   char *pattern = {"~FORAUS_"};\
   char *stringa=NULL,*ptr2=NULL;\
   char nomefile[200];\
   struct stat info_file;\
\
   componi_file_modulo(nomefile, nome_modulo, FILE_FTN, LIBUT, LIB_UTENTE);\
   if( (fp = fopen(nomefile,"r")) == NULL)\
   {\
      fclose(fp);\
      return(False);\
   }\
\
   if ( !fstat(fileno(fp),&info_file))\
   {\
      stringa = (char *) XtMalloc ((unsigned) info_file.st_size+1);\
   }\
   else\
      stringa = (char *) XtMalloc (sizeof(char) * 100000);\
\
/* leggo tutto il file */\
   ptr2 = stringa;\
   while (fgets(ptr2,140,fp) != NULL)\
      ptr2 = ptr2+strlen(ptr2);\
\
   if( strstr(stringa,pattern) != NULL)\
   {\
       printf("\n\n\tTROVATO PATTERN IN %s\n",nomefile);\
       fclose(fp);\
       free(stringa);\
       return(True);\
   }\
   else\
   {\
      printf("\n\n\tNON TROVATO PATTERN IN %s\n",nomefile);\
      fclose(fp);\
      free(stringa);\
      return(False);\
   }\
\
}\
\
\
\
/*** aggiungi_modulo_lista(tipo_lib, nome, descr, tag)\
 ***  Parametri:\
 ***    byte tipo_lib : tipo libreria (LIBUT,LIBUTREG,LIBREG)\
 ***    char *nomefile : nome del file lista moduli (processo o regolazione)\
 ***    char *nome, *descr : nome modulo e descrizione\
 ***    Boolean tag : indica se bisogna inserire il tag nella riga (car. !)\
 ***\
 ***  Descrizione:\
 ***    Inserimento o aggiornamento della riga di un modulo nel file lista dei\
 ***    moduli della libreria appropriata (LIBUT,LIBUTREG o LIBREG).\
 ***/\
aggiungi_modulo_lista(tipo_lib, nome, descr, tag)\
byte tipo_lib;\
char *nome, *descr;\
Boolean tag;\
{\
   FILE *fp, *fp_tmp;\
   char buffer[81], nuova_riga[81], flag;\
   char file_tmp[256], file_lista[256];\
   Boolean modulo_inserito = False;\
\
/* recupera il nome del file dati della libreria corretta */\
   file_dati_lib(file_lista, tipo_lib, LIB_UTENTE);\
\
   if ((fp = fopen(file_lista,"r")) == NULL)\
   {\
      sprintf(buffer,"Can't open file %s for inserting line.",FILE_DATI_LIBUT);\
      scrivi_messaggio(buffer);\
      return (-1);\
   }\
\
   if ((fp_tmp = fopen(tmpnam(file_tmp),"w+")) == NULL)\
   {\
      scrivi_messaggio("Can't open file temporary file for inserting line.");\
      return (-1);\
   }\
\
/* Composizione riga da inserire nella lista */\
   sprintf (nuova_riga,"%s  %s\n",nome,descr);\
\
/* se e' presente fortran ausiliario aggiungo il simbolo * idopo il nome */\
   if( esiste_foraux(nome) )\
     nuova_riga[4] = '*';\
\
/* Se si sta copiando da un altro utente, settare il tag '!' */\
   if (tag)\
      nuova_riga[5] = '!';\
\
   while (fgets(buffer,80,fp) != NULL)\
   {\
      if ( !modulo_inserito )\
         if ( strncmp (buffer,nome,4) >= 0 )\
         {\
            fputs (nuova_riga,fp_tmp);\
            modulo_inserito = True;\
\
         /* Se il modulo e' uguale allora passa al modulo successivo */\
            if (strncmp (buffer,nome,4) == 0)\
               if (fgets(buffer,80,fp) == NULL)\
                  break;\
         }\
      fputs (buffer,fp_tmp);\
   }\
\
/* Se la nuova riga va inserita dopo l'ultimo dei moduli */\
   if ( !modulo_inserito )\
      fputs (nuova_riga,fp_tmp);\
\
   fclose (fp);\
   fclose (fp_tmp);\
\
   flag = copia_file (file_tmp,file_lista);\
   unlink (file_tmp);\
\
   if ( flag != 0)\
   {\
      scrivi_messaggio ("Copy failure. Modules list not updated.\n");\
      return (-1);\
   }\
\
   return (0);\
}\
\
/***\
 *** controlla_lista_moduli(tipo_lib, nome_inserito, offset_listamod)\
 ***   Parametri:\
 ***     byte tipo_lib : tipo libreria (LIBUT, LIBUTREG, LIBREG)\
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
byte tipo_lib;\
char *nome_inserito;\
long *offset_listamod;\
{\
  extern Dialog_geometry geom_attention;\
  extern Widget attention_wdg, UxTopLevel;\
  FILE *fp_lista;\
  int  value = 0;\
  char baffer[81], file_lista[256];\
\
/* Apertura file dati  in lettura */\
  file_dati_lib(file_lista, tipo_lib, LIB_UTENTE);\
  if ( (fp_lista = fopen (file_lista,"r")) == NULL)\
  {\
     sprintf(message," Can't open data file for checking module names");\
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
/*** end_edicole(sig, code, scp, addr)\
 ***\
 ***  Descrizione:\
 ***    Registra l'eventuale uscita dal processo EDICOLE,\
 ***    mentre si e' ancora in LIBRARIAN. Viene chiamata dal signal SIGCLD.\
 ***/\
void end_edicole(sig, code, scp, addr)\
int sig, code;\
struct sigcontext *scp;\
char *addr;\
{\
   int status;\
\
/* Per eliminare la folla di ZOMBIE */\
   wait(&status);\
\
   fine_edicole = True;\
}\
\
/*** void cambia_tipo_modulo (w,tipo,zip)\
 ***   Parametri:\
 ***     Widget w: widget\
 ***     byte tipo : tipo libreria selezionata (LIBUT,LIBUTREG,LIBREG)\
 ***     XmPushButtonCallbackStruct *zip: non utilizzato.\
 ***\
 ***   Descrizione:\
 ***     Callback invocata agendo sull'optionMenu del tipo di moduli\
 ***     (processo o regolazione).\
 ***/\
void cambia_tipo_modulo (w,tipo,zip)\
Widget w;\
byte tipo;\
XmPushButtonCallbackStruct *zip;\
{\
   FILE *fp;\
   char nomefile[256];\
\
   if (tipo == tipo_modulo && zip != NULL)\
      return;\
\
   switch (tipo)\
   {\
      case LIBUT:\
         percorso_libreria(nomefile, LIBUT, LIB_UTENTE);\
         set_label(UxGetWidget(label_path_lib), nomefile);\
         set_something(UxGetWidget(pb_create_newmod),XmNsensitive, True);\
\
/*11-1-95 Micheletti */\
         /* set_something(UxGetWidget(pb_stdlib),XmNsensitive, True); */\
         set_something(UxGetWidget(pb_stdlib),XmNsensitive, False); \
         set_something(UxGetWidget(pb_stdlib_base),XmNsensitive, True);\
         set_something(UxGetWidget(pb_stdlib_auxiliary),XmNsensitive,True );\
         set_something(UxGetWidget(pb_stdlib_nuclear),XmNsensitive,True );\
         set_something(UxGetWidget(pb_stdlib_special),XmNsensitive,True );\
\
         strcat(nomefile, FILE_DATI_LIBUT);\
      break;\
\
      case LIBUTREG:\
         percorso_libreria(nomefile, LIBUTREG, LIB_UTENTE);\
         set_label(UxGetWidget(label_path_lib), nomefile);\
         set_something(UxGetWidget(pb_create_newmod),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib),XmNsensitive, False);\
\
/*11-1-95 Micheletti */\
         set_something(UxGetWidget(pb_stdlib_base),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_auxiliary),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_nuclear),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_special),XmNsensitive, False);\
\
         strcat(nomefile, FILE_DATI_LIBUTREG);\
      break;\
\
      case LIBREG:\
         percorso_libreria(nomefile, LIBREG, LIB_UTENTE);\
         set_label(UxGetWidget(label_path_lib), nomefile);\
         set_something(UxGetWidget(pb_create_newmod),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib),XmNsensitive, True);\
\
/*11-1-95 Micheletti */\
         set_something(UxGetWidget(pb_stdlib_base),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_auxiliary),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_nuclear),XmNsensitive, False);\
         set_something(UxGetWidget(pb_stdlib_special),XmNsensitive, False);\
\
         strcat(nomefile, FILE_DATI_LIBREG);\
      break;\
   }\
\
   tipo_modulo = tipo;\
   XmListDeselectAllItems(UxGetWidget(lista_moduli_utente));\
   XmListDeleteAllItems(UxGetWidget(lista_moduli_utente));\
\
   if ( (fp = fopen(nomefile, "r")) == NULL )\
   {\
       sprintf(message, "Can't open file %s.",nomefile); \
       scrivi_messaggio (message);\
       return;\
   }\
\
/* Visualizza la lista dei moduli selezionata (processo o regolazione) */\
   riempi_lista_moduli (fp,UxGetWidget(lista_moduli_utente));\
   fclose (fp);\
}\
\
/*** void edit_code_callback(w, par, data)\
 ***   Parametri:\
 ***     Widget w: widget.\
 ***     int par: bottone premuto (C_OK, C_APPLY, C_CANCEL)\
 ***     XmAnyCallbackStruct *data: non utilizzato.\
 ***\
 ***   Descrizione:\
 ***     Funzione di callback per l'editor del codice FORTRAN ***/\
void edit_code_callback(w, par, data)\
Widget w;\
int par;\
XmAnyCallbackStruct *data;\
{\
   Text_find_struct *ptr;\
   char *buffer_to_save, nomefile[256];\
   FILE *fp_ftn;\
   long lung, offset;\
   EditFtnStruct *edit_data;\
\
   if (par == C_OK || par == C_APPLY)\
   {   \
   /* struttura edit del modulo */\
      get_something(weditcode, XmNuserData, &edit_data);\
\
   /* Percorso del file FORTRAN da editare. */\
      componi_file_modulo(nomefile,edit_data->nome_mod,FILE_FTN,\
                          edit_data->tipo_lib,LIB_UTENTE);\
      printf ("salva su file : %s\n", nomefile);\
     \
      if ((fp_ftn = fopen (nomefile,"w+")) == NULL)\
      {\
         sprintf (message,"Can't open file %s for updating.",nomefile);\
         scrivi_messaggio (message);\
      }\
      else\
      {\
      /* Salva il contenuto del text-widget sul file */\
         buffer_to_save = XmTextGetString(weditcode);\
         lung = strlen(buffer_to_save);\
\
      /* Se e' stato accidentalmente cancellato */\
      /* inserisce il carattere di fine riga */\
         if ( buffer_to_save[lung-1] != '\n')\
            strcat(buffer_to_save,"\n");\
\
         fputs (buffer_to_save, fp_ftn);\
         fclose (fp_ftn);\
         XtFree (buffer_to_save);\
\
      /* Setta il tag '!' alla posizione 6  */   \
      /* Recupera l'offset del nome del modulo nel file lista selezionato */\
      /* (LIBUT, LIBUTREG, LIBREG) */\
         if (controlla_lista_moduli (edit_data->tipo_lib, edit_data->nome_mod,\
                                     &offset) == -1)\
            apponi_tag_record(edit_data->tipo_lib, offset);\
      }\
   }\
\
/* Chiudi la window di editor se necessario (Ok o Cancel) */\
   if (par == C_CANCEL || par == C_OK)\
   {\
\
   /* Dealloca la struttura utlizzata dall'editor per il find */\
      get_something(wwinedit, XmNuserData, &ptr);\
      XtFree(ptr);\
\
      dbox_code_managed = False;\
      XtDestroyWidget(wwinedit);\
   }\
}\
\
/*** unselect_module()\
 ***    Nessun parametro.\
 ***\
 ***    Descrizione:\
 ***      La funzione viene chiamata per deselezionare il modulo corrente \
 ***/\
unselect_module()\
{\
/* Riporto la label del modulo selezionato a '<none>'  */\
   set_label(UxGetWidget(selected_module_label),"<none>"); \
\
/* Svuoto le variabili globali di nome e descrizione modulo */\
   nome_modulo[0]  = '\0';\
   descr_modulo[0] = '\0';\
\
/* Blocco i menu */\
   menu_modulo_non_attivo();\
}\
\
/*** char *componi_file_modulo(nomefile, nome_mod, tipo_file, tipo_lib,\
 ***                           quale_lib)\
 ***   Parametri:\
 ***     char *nomefile : nome del file (uscita)\
 ***     char *nome_mod : nome del modulo\
 ***     byte tipo_file : tipo file (FORTRAN, DOC, INTERFACCIA, DATI)\
 ***     byte tipo_lib : tipo libreria (LIBUT, LIBUTREG o LIBREG)\
 ***     byte quale_lib : quale libreria: utente (LIB_UTENTE) oppure\
 ***                               standard (LIB_STANDARD).\
 ***\
 ***   Descrizione:\
 ***     Restituisce il nome del file dati corretto.\
 ***/\
char *componi_file_modulo(nomefile, nome_mod, tipo_file, tipo_lib, quale_lib)\
char *nomefile, *nome_mod;\
byte tipo_file, tipo_lib, quale_lib;\
{\
   char minus_nome[10];\
\
   strcpy(minus_nome, nome_mod);\
   tominus(minus_nome);\
\
   switch (tipo_file)\
   {\
      case FILE_FTN:\
#ifdef VMS\
           strcat(minus_nome,".ftn");\
#else\
           strcat(minus_nome,".f");\
#endif\
           break;\
\
      case FILE_DOC:\
           strcat(minus_nome,".doc");\
           break;\
\
      case FILE_IFACE:\
           strcat(minus_nome,".i");\
           break;\
\
      case FILE_DAT:\
           strcat(minus_nome,".dat");\
           break;\
\
      case FILE_01DAT:\
           strcat(minus_nome,"_01.dat");\
           break;\
   }\
\
   percorso_libreria(nomefile, tipo_lib, quale_lib);\
   strcat(nomefile, minus_nome);\
   return(nomefile);\
}\
\
/*** char *file_dati_lib(nomefile, tipo_lib, quale_lib)\
 ***   Parametri:\
 ***     char *nomefile : nome del file (uscita)\
 ***     byte tipo_lib : tipo libreria (LIBUT,LIBUTREG,LIBREG,LIBGRAF)\
 ***     byte quale_lib : quale libreria: utente (LIB_UTENTE) oppure\
 ***                               standard (LIB_STANDARD).\
 ***\
 ***   Descrizione:\
 ***     Restituisce il nome del file dati corretto.\
 ***/\
char *file_dati_lib(nomefile, tipo_lib, quale_lib)\
char *nomefile;\
byte tipo_lib, quale_lib;\
{\
   char *file_lista;\
\
   switch (tipo_lib)\
   {\
       case LIBUT:\
            file_lista = FILE_DATI_LIBUT;\
            break;\
\
       case LIBUTREG:\
            file_lista = FILE_DATI_LIBUTREG;\
            break;\
\
       case LIBREG:\
            file_lista = FILE_DATI_LIBREG;\
            break;\
\
       case LIBGRAF:\
            file_lista = FILE_ICONE_MODP;\
            break;\
\
       default:\
            return(NULL);\
            break;\
   }\
\
   percorso_libreria(nomefile, tipo_lib, quale_lib);\
\
   strcat(nomefile,file_lista);\
   return(nomefile);\
}\
\
/*** char *sottodir_utente(tipo_lib, quale_lib)\
 ***   Parametri:\
 ***     byte tipo_lib : tipo libreria.\
 ***     byte quale_lib : quale libreria (standard o utente?)\
 ***\
 ***   Descrizione:\
 ***     Restituisce il sottodirettorio della directory legocad dell'utente \
 ***/\
char *sottodir_utente(tipo_lib, quale_lib)\
byte tipo_lib, quale_lib;\
{\
\
/* 12-1-95 Micheletti */\
/***\
   return(path_librerie[2*tipo_lib+quale_lib]);\
***/\
\
/*\
   questa modifica puo' essere migliorata adattando la matrice\
   path_librerie per gestire gli ulteriori casi\
   prima di farla pero' e' necessario verificare l'impatto\
   sugli altri programmi.\
   Inoltre se viene cambiata la matrice deve essere rivista\
   la routine percorso_libreria. \
*/ \
\
   if( (quale_lib == LIB_UTENTE) || (quale_lib == LIB_STANDARD) )\
      return(path_librerie[2*tipo_lib+quale_lib]);\
   else if( quale_lib == LIB_STANDARD_BASE )\
      return( PATH_LIBUT_STD_BASE );\
   else if( quale_lib == LIB_STANDARD_AUXILIARY )\
      return( PATH_LIBUT_STD_AUXILIARY );\
   else if( quale_lib == LIB_STANDARD_NUCLEAR )\
      return( PATH_LIBUT_STD_NUCLEAR );\
   else if( quale_lib == LIB_STANDARD_SPECIAL )\
      return( PATH_LIBUT_STD_SPECIAL );\
   else if( quale_lib == LIB_STANDARD_GENERAL )\
      return( PATH_LIBUT_STD_GENERAL );\
}\
\
/*** char *percorso_libreria(percorso, tipo_lib, quale_lib)\
 ***   Parametri:\
 ***     char *percorso : percorso libreria (uscita)\
 ***     byte tipo_lib : tipo libreria (LIBUT, LIBUTREG o LIBREG).\
 ***     byte quale_lib : quale libreria: utente (LIB_UTENTE) oppure\
 ***                               standard (LIB_STANDARD).\
 ***  Restituisce il giusto percorso della libreria.\
 ***/\
char *percorso_libreria(percorso, tipo_lib, quale_lib)\
char *percorso;\
byte tipo_lib, quale_lib;\
{\
   char *path_base, *subdir;\
\
   if ( (quale_lib == LIB_UTENTE)  ) \
      path_base = path_legocad;\
   else if (tipo_lib== LIBREG)\
      path_base = path_rego;\
   else \
      path_base = path_lego;\
\
   subdir = sottodir_utente(tipo_lib, quale_lib);\
\
#ifdef VMS\
   sottodir_vms(percorso, path_base, subdir);\
#else\
   sprintf(percorso, "%s/%s/", path_base, subdir);\
#endif\
}\
\
/*** test_environment()\
 ***\
 ***   Descrizione:\
 ***     Attiva il processo make per il controllo dell'ambiente LEGOCAD\
 ***     dell'utente.\
 ***/\
test_environment()\
{\
    return(esegui_comando(TEST_ENVIRONMENT));\
}\
\
/*** crea_environment()\
 ***\
 ***   Descrizione:\
 ***     Attiva il processo make per la creazione dell'ambiente LEGOCAD\
 ***     dell'utente extra-vergine.\
 ***/\
crea_environment()\
{\
    return(lancia_comando(display,CREA_ENVIRONMENT));\
}\
\
/*** copia_std_environment()\
 ***\
 ***   Descrizione:\
 ***     Attiva il processo make per la copia della libreria standard \
 ***     nell'ambiente LEGOCAD dell'utente (vergihe o no).\
 ***/\
copia_std_environment()\
{\
    return(lancia_comando(display,COPIA_STD_ENVIRONMENT));\
}\
\
/*** cad_crealibut()\
 ***\
 ***   Descrizione:\
 ***      Compila e crea la libreria libut (moduli di processo)\
 ***/\
cad_crealibut()\
{\
    return(lancia_comando(display,CREA_LIBUT));\
}\
\
/*** cad_crealibut_reg()\
 ***\
 ***   Descrizione:\
 ***      Compila e crea la libreria libut_reg (moduli di regolazione)\
 ***/\
cad_crealibut_reg()\
{\
    return(lancia_comando(display,CREA_LIBUT_REG));\
}\
\
/*** cad_crealibreg()\
 ***\
 ***   Descrizione:\
 ***      Compila e crea la libreria libreg (moduletti di regolazione)\
 ***/\
cad_crealibreg()\
{\
    return(lancia_comando(display,CREA_LIBREG));\
}\
\
/*** cad_crealg1()\
 ***\
 ***   Descrizione:\
 ***      Compila e crea l'applicativo LEGOCAD LG1\
 ***/\
cad_crealg1()\
{\
    return(lancia_comando(display,CREA_LG1));\
}\
\
/*** show_error( mess )\
 ***   Parametri:\
 ***     char mess: messaggio di errore da visualizzare\
 ***\
 ***   Descrizione:\
 ***      Visualizza un messaggio di errore nella window dei messaggi\
 ***      (chiamata da esegui_comando() -> lc_errore())\
 ***/\
show_error(mess)\
char *mess;\
{\
   scrivi_messaggio(mess);\
}\
\
/*** show_warning( mess )\
 ***   Parametri:\
 ***     char mess: messaggio di errore da visualizzare\
 ***\
 ***   Descrizione:\
 ***      Visualizza un messaggio di warning nella window dei messaggi\
 ***      (chiamata da esegui_comando() -> lc_errore())\
 ***/\
show_warning(mess)\
char *mess;\
{\
   scrivi_messaggio(mess);\
}\
\
/*** chiudi_prog_legocad()\
 ***\
 ***   Descrizione:\
 ***     Fine applicativo (chiamato da close_prog_legocad() nel file lc_ops.c)\
 ***/\
chiudi_prog_legocad()\
{\
   XtCloseDisplay(display);\
   exit(1);\
}\
\
/*** void conf_test_env(w,risposta,call_data)\
 ***  Parametri:\
 ***    Widget w: widget\
 ***    int risposta : 	0 -> crea ambiente vuoto\
 ***		       	1 -> crea e copia tutta la libreria standard\
 ***			2 -> esci e torna a casa\
 ***    XmAnyCallbackStruct *call_data : non utilizzato.\
 ***\
 ***  Descrizione:\
 ***    Callback chiamata durante il test sull'ambiente LEGOCAD.\
 ***/\
void conf_test_env(w,risposta,call_data)\
Widget w;\
int risposta;\
XmAnyCallbackStruct *call_data;\
{\
   switch (risposta)\
   {\
      case 0 :\
         crea_environment();\
         break;\
\
      case 1:\
         copia_std_environment();\
\
      /* Aggiorna la lista dei moduli */\
         cambia_tipo_modulo(NULL, LIB_UTENTE, NULL);\
         break;\
\
      case 2:\
         chiudi_prog_legocad();\
         break;\
   }\
\
   XtDestroyWidget(dialog_test_env);\
}\
\
#ifdef HYPERHELP_USED\
/**\
*** void hhelp_doc_modulo\
*** parametri: nessuno\
*** descrizione: richiama hyperhelp viewer visualizzando\
***              la documentazione del modulo selezionato\
*** Note: questa funzione viene chiamata solo se la l'eseguibile\
***       e' stato generato con -DHYPERHELP_USED\
**/\
\
void hhelp_doc_modulo()\
{\
  static char tok[100];\
\
   if( tipo_modulo == LIBUT )\
   {\
     printf("Help for Process Module %s\n",nome_modulo);\
     sprintf(tok,"%s process module",nome_modulo);\
\
   }\
   else if( tipo_modulo ==  LIBREG )\
   {\
     strcpy(tok,nome_modulo);\
     strcat(tok," regulation module");  \
     printf("Help for Regulation Module %s\n",nome_modulo);  \
     printf("Start HyperHelp with parameter [%s]\n",tok); \
     WinHelp(UxDisplay,"lglibreg.hlp",HELP_KEY,(unsigned long)tok);\
   }\
}\
#endif
*mainWindow1.name: mainWindow1
*mainWindow1.title: "USER MODULES LIBRARY"
*mainWindow1.iconName: "LIBRARIAN"
*mainWindow1.x: 238
*mainWindow1.y: 480
*mainWindow1.width: 600
*mainWindow1.height: 800

*mainWindow2.class: mainWindow
*mainWindow2.parent: mainWindow1
*mainWindow2.static: true
*mainWindow2.name: mainWindow2
*mainWindow2.x: 238
*mainWindow2.y: 480
*mainWindow2.width: 600
*mainWindow2.height: 800

*form1.class: form
*form1.parent: mainWindow2
*form1.static: true
*form1.name: form1
*form1.width: 549
*form1.height: 400

*panedWindow1.class: panedWindow
*panedWindow1.parent: form1
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.unitType: "pixels"
*panedWindow1.x: 0
*panedWindow1.y: 0
*panedWindow1.width: 680
*panedWindow1.height: 769
*panedWindow1.rightAttachment: "attach_form"
*panedWindow1.bottomAttachment: "attach_form"
*panedWindow1.leftAttachment: "attach_form"
*panedWindow1.topAttachment: "attach_form"

*form10.class: form
*form10.parent: panedWindow1
*form10.static: true
*form10.name: form10
*form10.unitType: "pixels"
*form10.x: 3
*form10.y: 0
*form10.width: 594
*form10.height: 373

*form3.class: form
*form3.parent: form10
*form3.static: true
*form3.name: form3
*form3.unitType: "pixels"
*form3.x: 10
*form3.y: 336
*form3.width: 580
*form3.height: 40
*form3.bottomAttachment: "attach_form"
*form3.bottomOffset: 10
*form3.leftAttachment: "attach_form"
*form3.leftOffset: 10
*form3.rightAttachment: "attach_form"
*form3.rightOffset: 5

*static_module_label.class: label
*static_module_label.parent: form3
*static_module_label.static: true
*static_module_label.name: static_module_label
*static_module_label.x: 230
*static_module_label.y: 5
*static_module_label.width: 130
*static_module_label.height: 30
*static_module_label.alignment: "alignment_beginning"
*static_module_label.labelString: "Selected module:"
*static_module_label.bottomAttachment: "attach_form"
*static_module_label.bottomOffset: 0
*static_module_label.leftAttachment: "attach_form"
*static_module_label.leftOffset: 0
*static_module_label.topAttachment: "attach_form"
*static_module_label.topOffset: 0

*selected_module_label.class: label
*selected_module_label.parent: form3
*selected_module_label.static: false
*selected_module_label.name: selected_module_label
*selected_module_label.x: 140
*selected_module_label.y: 20
*selected_module_label.width: 90
*selected_module_label.height: 30
*selected_module_label.alignment: "alignment_beginning"
*selected_module_label.foreground: "yellow"
*selected_module_label.labelString: "<none>"
*selected_module_label.bottomAttachment: "attach_form"
*selected_module_label.bottomOffset: 0
*selected_module_label.leftAttachment: "attach_widget"
*selected_module_label.leftOffset: 10
*selected_module_label.leftWidget: "static_module_label"
*selected_module_label.rightAttachment: "attach_form"
*selected_module_label.topAttachment: "attach_form"
*selected_module_label.topOffset: 0
*selected_module_label.resizable: "false"
*selected_module_label.rightOffset: 5

*separatorGadget6.class: separatorGadget
*separatorGadget6.parent: form10
*separatorGadget6.static: true
*separatorGadget6.name: separatorGadget6
*separatorGadget6.x: 10
*separatorGadget6.y: 310
*separatorGadget6.width: 580
*separatorGadget6.height: 10
*separatorGadget6.bottomAttachment: "attach_widget"
*separatorGadget6.bottomOffset: 0
*separatorGadget6.bottomWidget: "form3"
*separatorGadget6.leftAttachment: "attach_form"
*separatorGadget6.leftOffset: 10
*separatorGadget6.rightAttachment: "attach_form"
*separatorGadget6.rightOffset: 10
*separatorGadget6.topAttachment: "attach_none"
*separatorGadget6.topOffset: 0

*form12.class: form
*form12.parent: form10
*form12.static: true
*form12.name: form12
*form12.unitType: "pixels"
*form12.x: 10
*form12.y: 270
*form12.width: 580
*form12.height: 40
*form12.bottomAttachment: "attach_widget"
*form12.bottomOffset: 5
*form12.bottomWidget: "separatorGadget6"
*form12.leftAttachment: "attach_form"
*form12.leftOffset: 10
*form12.topAttachment: "attach_none"
*form12.topOffset: 0
*form12.rightAttachment: "attach_form"

*label_user_path.class: label
*label_user_path.parent: form10
*label_user_path.static: true
*label_user_path.name: label_user_path
*label_user_path.x: 10
*label_user_path.y: 20
*label_user_path.width: 160
*label_user_path.height: 20
*label_user_path.topOffset: 20
*label_user_path.topAttachment: "attach_form"
*label_user_path.alignment: "alignment_beginning"
*label_user_path.labelString: "USER LIBRARY PATH:"
*label_user_path.leftAttachment: "attach_form"
*label_user_path.leftOffset: 10
*label_user_path.recomputeSize: "false"

*label_path_lib.class: label
*label_path_lib.parent: form10
*label_path_lib.static: true
*label_path_lib.name: label_path_lib
*label_path_lib.x: 140
*label_path_lib.y: 20
*label_path_lib.width: 440
*label_path_lib.height: 20
*label_path_lib.alignment: "alignment_beginning"
*label_path_lib.labelString: ""
*label_path_lib.leftAttachment: "attach_widget"
*label_path_lib.leftOffset: 10
*label_path_lib.leftWidget: "label_user_path"
*label_path_lib.topAttachment: "attach_form"
*label_path_lib.topOffset: 20
*label_path_lib.rightAttachment: "attach_form"
*label_path_lib.rightOffset: 10
*label_path_lib.foreground: "Red"

*labelGadget17.class: labelGadget
*labelGadget17.parent: form10
*labelGadget17.static: true
*labelGadget17.name: labelGadget17
*labelGadget17.x: 0
*labelGadget17.y: 10
*labelGadget17.width: 180
*labelGadget17.height: 30
*labelGadget17.bottomAttachment: "attach_none"
*labelGadget17.leftAttachment: "attach_form"
*labelGadget17.leftOffset: 10
*labelGadget17.rightAttachment: "attach_none"
*labelGadget17.topAttachment: "attach_widget"
*labelGadget17.topOffset: 10
*labelGadget17.labelString: "USER MODULES"
*labelGadget17.alignment: "alignment_beginning"
*labelGadget17.topWidget: "label_user_path"

*scrolledWindow13.class: scrolledWindow
*scrolledWindow13.parent: form10
*scrolledWindow13.static: true
*scrolledWindow13.name: scrolledWindow13
*scrolledWindow13.scrollingPolicy: "application_defined"
*scrolledWindow13.unitType: "pixels"
*scrolledWindow13.x: 0
*scrolledWindow13.y: 50
*scrolledWindow13.visualPolicy: "variable"
*scrolledWindow13.scrollBarDisplayPolicy: "static"
*scrolledWindow13.shadowThickness: 0
*scrolledWindow13.bottomAttachment: "attach_widget"
*scrolledWindow13.bottomPosition: 0
*scrolledWindow13.leftAttachment: "attach_form"
*scrolledWindow13.leftOffset: 10
*scrolledWindow13.rightAttachment: "attach_form"
*scrolledWindow13.rightOffset: 10
*scrolledWindow13.topAttachment: "attach_widget"
*scrolledWindow13.topOffset: 5
*scrolledWindow13.topWidget: "labelGadget17"
*scrolledWindow13.bottomOffset: 5
*scrolledWindow13.bottomWidget: "form12"

*lista_moduli_utente.class: scrolledList
*lista_moduli_utente.parent: scrolledWindow13
*lista_moduli_utente.static: false
*lista_moduli_utente.name: lista_moduli_utente
*lista_moduli_utente.width: 590
*lista_moduli_utente.height: 310
*lista_moduli_utente.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*lista_moduli_utente.selectionPolicy: "single_select"
*lista_moduli_utente.singleSelectionCallback: {\
   int n;\
   XmStringTable items;\
   char *buffer;\
\
   get_something(UxGetWidget(lista_moduli_utente), XmNselectedItems, &items);\
   get_something(UxGetWidget(lista_moduli_utente), XmNselectedItemCount, &n);\
\
   if ( n == 0 )\
      unselect_module();\
   else\
   {\
      buffer = extract_string(items[0]);\
      setta_label_modsel(buffer);\
      XtFree(buffer);\
   }\
}
*lista_moduli_utente.listSizePolicy: "variable"
*lista_moduli_utente.scrollBarDisplayPolicy: "static"

*menu_tipolib.class: rowColumn
*menu_tipolib.parent: form10
*menu_tipolib.static: true
*menu_tipolib.name: menu_tipolib
*menu_tipolib.rowColumnType: "menu_option"
*menu_tipolib.subMenuId: "opt_tipolib"
*menu_tipolib.leftAttachment: "attach_none"
*menu_tipolib.rightAttachment: "attach_form"
*menu_tipolib.rightOffset: 10
*menu_tipolib.topAttachment: "attach_widget"
*menu_tipolib.topOffset: 10
*menu_tipolib.topWidget: "label_path_lib"
*menu_tipolib.labelString: "Library:"

*opt_tipolib.class: rowColumn
*opt_tipolib.parent: menu_tipolib
*opt_tipolib.static: true
*opt_tipolib.name: opt_tipolib
*opt_tipolib.rowColumnType: "menu_pulldown"
*opt_tipolib.labelString: "Library:"

*show_libut_pb.class: pushButton
*show_libut_pb.parent: opt_tipolib
*show_libut_pb.static: true
*show_libut_pb.name: show_libut_pb
*show_libut_pb.labelString: "libut"
*show_libut_pb.activateCallback.source: public
*show_libut_pb.activateCallback: cambia_tipo_modulo
*show_libut_pb.activateCallbackClientData: (XtPointer) LIBUT

*show_libutreg_pb.class: pushButton
*show_libutreg_pb.parent: opt_tipolib
*show_libutreg_pb.static: true
*show_libutreg_pb.name: show_libutreg_pb
*show_libutreg_pb.labelString: "libut_reg"
*show_libutreg_pb.activateCallback.source: public
*show_libutreg_pb.activateCallback: cambia_tipo_modulo
*show_libutreg_pb.activateCallbackClientData: (XtPointer) LIBUTREG

*show_libreg_pb.class: pushButton
*show_libreg_pb.parent: opt_tipolib
*show_libreg_pb.static: true
*show_libreg_pb.name: show_libreg_pb
*show_libreg_pb.labelString: "libreg"
*show_libreg_pb.activateCallback.source: public
*show_libreg_pb.activateCallback: cambia_tipo_modulo
*show_libreg_pb.activateCallbackClientData: (XtPointer) LIBREG

*form11.class: form
*form11.parent: panedWindow1
*form11.static: true
*form11.name: form11
*form11.unitType: "pixels"
*form11.x: 0
*form11.y: 380
*form11.width: 600
*form11.height: 380

*frame1.class: frame
*frame1.parent: form11
*frame1.static: true
*frame1.name: frame1
*frame1.unitType: "pixels"
*frame1.x: 10
*frame1.y: 61
*frame1.width: 600
*frame1.height: 30
*frame1.bottomAttachment: "attach_none"
*frame1.leftAttachment: "attach_form"
*frame1.leftOffset: 10
*frame1.rightAttachment: "attach_form"
*frame1.rightOffset: 10
*frame1.topAttachment: "attach_form"
*frame1.topOffset: 10

*labelGadget3.class: labelGadget
*labelGadget3.parent: frame1
*labelGadget3.static: true
*labelGadget3.name: labelGadget3
*labelGadget3.x: 170
*labelGadget3.y: 10
*labelGadget3.width: 240
*labelGadget3.height: 30
*labelGadget3.labelString: "MESSAGES"

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: form11
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.unitType: "pixels"
*scrolledWindow2.x: 10
*scrolledWindow2.y: 105
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.leftOffset: 10
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.rightOffset: 10
*scrolledWindow2.topOffset: 10
*scrolledWindow2.topAttachment: "attach_widget"
*scrolledWindow2.topWidget: "frame1"
*scrolledWindow2.bottomAttachment: "attach_form"
*scrolledWindow2.bottomOffset: 20

*finestra_messaggi.class: scrolledText
*finestra_messaggi.parent: scrolledWindow2
*finestra_messaggi.static: true
*finestra_messaggi.name: finestra_messaggi
*finestra_messaggi.unitType: "pixels"
*finestra_messaggi.x: 10
*finestra_messaggi.y: 105
*finestra_messaggi.columns: 80
*finestra_messaggi.editMode: "multi_line_edit"
*finestra_messaggi.editable: "false"
*finestra_messaggi.resizeHeight: "true"
*finestra_messaggi.resizeWidth: "true"
*finestra_messaggi.fontList: "*Courier-Bold-R-Normal--14-*"
*finestra_messaggi.cursorPositionVisible: "false"
*finestra_messaggi.verifyBell: "false"

*message_menu.class: rowColumn
*message_menu.parent: finestra_messaggi
*message_menu.static: true
*message_menu.name: message_menu
*message_menu.rowColumnType: "menu_popup"
*message_menu.menuAccelerator: "<KeyUp>F4"
*message_menu.entryAlignment: "alignment_center"

*menu1_p1_title.class: label
*menu1_p1_title.parent: message_menu
*menu1_p1_title.static: true
*menu1_p1_title.name: menu1_p1_title
*menu1_p1_title.labelString: "MESSAGE"

*popup_separator.class: separatorGadget
*popup_separator.parent: message_menu
*popup_separator.static: true
*popup_separator.name: popup_separator

*popup_pbutton.class: pushButton
*popup_pbutton.parent: message_menu
*popup_pbutton.static: true
*popup_pbutton.name: popup_pbutton
*popup_pbutton.labelString: "   Clear window"
*popup_pbutton.accelerator: ""
*popup_pbutton.acceleratorText: ""
*popup_pbutton.activateCallback: {\
XmTextSetString(UxGetWidget(finestra_messaggi),"");\
}
*popup_pbutton.marginRight: 0

*menubar.class: rowColumn
*menubar.parent: mainWindow2
*menubar.static: true
*menubar.name: menubar
*menubar.rowColumnType: "menu_bar"
*menubar.menuAccelerator: "<KeyUp>F10"
*menubar.spacing: 25
*menubar.height: 35

*mb_file.class: rowColumn
*mb_file.parent: menubar
*mb_file.static: true
*mb_file.name: mb_file
*mb_file.rowColumnType: "menu_pulldown"

*pb_quit.class: pushButton
*pb_quit.parent: mb_file
*pb_quit.static: true
*pb_quit.name: pb_quit
*pb_quit.labelString: "Quit"
*pb_quit.activateCallback: {\
   FILE *fenv;\
\
/* Cancellazione eventuale file jac temporaneo */\
if (!access(file_jac_temp,F_OK))\
   if ( unlink(file_jac_temp) )\
      printf ("Can't delete jacobian temporary file. Failure.\n");\
\
if( (fenv = fopen(LIBENV,"w")) != NULL)\
{\
   \
   fprintf(fenv,"%s",getenv("LEGOCAD_MOD_DEBUG"));\
   fclose(fenv);\
}\
\
XtCloseDisplay(display);\
exit(0);   \
}
*pb_quit.mnemonic: "Q"

*mb_module.class: rowColumn
*mb_module.parent: menubar
*mb_module.static: true
*mb_module.name: mb_module
*mb_module.rowColumnType: "menu_pulldown"

*cb_call_newmod.class: cascadeButtonGadget
*cb_call_newmod.parent: mb_module
*cb_call_newmod.static: true
*cb_call_newmod.name: cb_call_newmod
*cb_call_newmod.labelString: "Call (NEWMOD)"
*cb_call_newmod.mnemonic: "N"
*cb_call_newmod.subMenuId: "mb_call_newmod"

*cb_copy.class: cascadeButtonGadget
*cb_copy.parent: mb_module
*cb_copy.static: true
*cb_copy.name: cb_copy
*cb_copy.labelString: "Copy from"
*cb_copy.mnemonic: "y"
*cb_copy.subMenuId: "mb_copy"

*pb_edit_ftn.class: pushButton
*pb_edit_ftn.parent: mb_module
*pb_edit_ftn.static: true
*pb_edit_ftn.name: pb_edit_ftn
*pb_edit_ftn.labelString: "Edit  code"
*pb_edit_ftn.mnemonic: "c"
*pb_edit_ftn.activateCallback: {\
char nomefile[256];\
static char *font_text = "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1";\
if (!dbox_code_managed)\
{\
/* Percorso del file FORTRAN da editare. */\
   componi_file_modulo(nomefile,nome_modulo,FILE_FTN,tipo_modulo,LIB_UTENTE);\
   printf ("FILE FTN: %s\n",nomefile);\
\
   wwinedit = (Widget) editor(UxTopLevel,&weditcode,nomefile,True,font_text,\
                              funz_edit_code,geom_editor);\
   if (wwinedit == NULL)\
   {\
      sprintf (message,"Can't open file %s for processing.", nomefile);\
      scrivi_messaggio (message);      \
   }\
   else\
   {\
      dbox_code_managed = True;\
\
   /* Memorizza nello userData i dati relativi al modulo */\
      strcpy(edit_struct[0].nome_mod, nome_modulo);\
      strcpy(edit_struct[0].descr_mod, descr_modulo);\
      edit_struct[0].tipo_lib = tipo_modulo;\
\
      set_something(weditcode, XmNuserData, (XtPointer) edit_struct);\
   }\
}\
}

*pb_delete.class: pushButton
*pb_delete.parent: mb_module
*pb_delete.static: true
*pb_delete.name: pb_delete
*pb_delete.labelString: "Delete"
*pb_delete.mnemonic: "D"
*pb_delete.activateCallback: {\
sprintf (message, "Do you really want to delete the module %s ?", nome_modulo);\
dialog_delete = (Widget) conferma (UxTopLevel, message, cancella_modulo);\
XtManageChild (dialog_delete);\
}

*mb_call_newmod.class: rowColumn
*mb_call_newmod.parent: mb_module
*mb_call_newmod.static: true
*mb_call_newmod.name: mb_call_newmod
*mb_call_newmod.rowColumnType: "menu_pulldown"

*pb_create_newmod.class: pushButton
*pb_create_newmod.parent: mb_call_newmod
*pb_create_newmod.static: true
*pb_create_newmod.name: pb_create_newmod
*pb_create_newmod.labelString: "Create"
*pb_create_newmod.mnemonic: "C"
*pb_create_newmod.activateCallback: {\
if ( nmod_def_managed )\
{\
    scrivi_messaggio("NEWMOD definition window already in use.");\
    return;\
}\
\
create_nmod_shell(False);\
}

*pb_modify_newmod.class: pushButton
*pb_modify_newmod.parent: mb_call_newmod
*pb_modify_newmod.static: true
*pb_modify_newmod.name: pb_modify_newmod
*pb_modify_newmod.labelString: "Modify"
*pb_modify_newmod.mnemonic: "M"
*pb_modify_newmod.activateCallback: {\
char nome_file[256];\
\
if ( nmod_def_managed )\
{\
    scrivi_messaggio("NEWMOD definition window already in use.");\
    return;\
}\
\
/* percorso del file interfaccia (libreria moduli di processo LIBUT) */\
componi_file_modulo(nome_file,nome_modulo,FILE_IFACE,LIBUT,LIB_UTENTE);\
\
if ( access(nome_file, F_OK) )\
{\
    scrivi_messaggio("The module doesn't contain NEWMOD information.");\
    return;\
}\
\
/* Chiama la NEWMOD per le modifiche */\
create_nmod_shell(True);\
}

*mb_copy.class: rowColumn
*mb_copy.parent: mb_module
*mb_copy.static: true
*mb_copy.name: mb_copy
*mb_copy.rowColumnType: "menu_pulldown"

*pb_user.class: pushButton
*pb_user.parent: mb_copy
*pb_user.static: true
*pb_user.name: pb_user
*pb_user.labelString: "Different user"
*pb_user.mnemonic: "u"
*pb_user.activateCallback: {\
/* crea la dialog-box di selezione files per la copia */\
if ( !dbox_fileselect_managed )\
   create_file_selection();\
}

*pb_stdlib.class: pushButton
*pb_stdlib.parent: mb_copy
*pb_stdlib.static: true
*pb_stdlib.name: pb_stdlib
*pb_stdlib.labelString: "Standard library"
*pb_stdlib.mnemonic: "l"
*pb_stdlib.activateCallback: {\
  char *path_lib, file_lista[256];\
  FILE *fp;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
   if (dbox_listamod_managed)\
   {\
      scrivi_messaggio ("Modules list window already in use.");\
      return;\
   }\
\
/* Composizione percorso e nome file lista dei moduli di libreria */\
\
   file_dati_lib(file_lista, tipo_modulo, LIB_STANDARD);\
printf("tipo_modulo = [%d]\n",tipo_modulo);\
\
\
/* Se il file lista_moduli.dat di libreria non esiste */\
/* ritorna con errore */\
printf("File lista dei moduli [%s]\n",file_lista);\
   if ( (fp = fopen (file_lista, "r")) == NULL )\
   {\
      scrivi_messaggio ("Can't open data file.");\
      return;\
   }\
\
/* Visualizza la lista moduli e setta la reason della lista */\
   create_lista_moduli(fp,tipo_modulo,STDLIB_MODULES_COPY,\
                       &dbox_listamod_managed);\
\
   fclose(fp);\
}

*pb_stdlib_base.class: pushButton
*pb_stdlib_base.parent: mb_copy
*pb_stdlib_base.static: true
*pb_stdlib_base.name: pb_stdlib_base
*pb_stdlib_base.labelString: "Base Standard Library"
*pb_stdlib_base.activateCallback: {\
  char *path_lib, file_lista[256];\
  FILE *fp;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
   if (dbox_listamod_managed)\
   {\
      scrivi_messaggio ("Modules list window already in use.");\
      return;\
   }\
\
/* Composizione percorso e nome file lista_moduli.dat di libreria */\
   file_dati_lib(file_lista, tipo_modulo, LIB_STANDARD_BASE);\
\
/* Se il file lista_moduli.dat di libreria non esiste */\
/* ritorna con errore */\
   if ( (fp = fopen (file_lista, "r")) == NULL )\
   {\
      scrivi_messaggio ("Can't open data file.");\
      return;\
   }\
\
/* Visualizza la lista moduli e setta la reason della lista */\
   create_lista_moduli(fp,tipo_modulo,STDLIBBASE_MODULES_COPY,\
                       &dbox_listamod_managed);\
\
   fclose(fp);\
}

*pb_stdlib_auxiliary.class: pushButton
*pb_stdlib_auxiliary.parent: mb_copy
*pb_stdlib_auxiliary.static: true
*pb_stdlib_auxiliary.name: pb_stdlib_auxiliary
*pb_stdlib_auxiliary.labelString: "Auxiliary Standard Library"
*pb_stdlib_auxiliary.activateCallback: {\
  char *path_lib, file_lista[256];\
  FILE *fp;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
   if (dbox_listamod_managed)\
   {\
      scrivi_messaggio ("Modules list window already in use.");\
      return;\
   }\
\
/* Composizione percorso e nome file lista_moduli.dat di libreria */\
   file_dati_lib(file_lista, tipo_modulo, LIB_STANDARD_AUXILIARY);\
\
/* Se il file lista_moduli.dat di libreria non esiste */\
/* ritorna con errore */\
   if ( (fp = fopen (file_lista, "r")) == NULL )\
   {\
      scrivi_messaggio ("Can't open data file.");\
      return;\
   }\
\
/* Visualizza la lista moduli e setta la reason della lista */\
   create_lista_moduli(fp,tipo_modulo,STDLIBAUXILIARY_MODULES_COPY,\
                       &dbox_listamod_managed);\
\
   fclose(fp);\
}

*pb_stdlib_nuclear.class: pushButton
*pb_stdlib_nuclear.parent: mb_copy
*pb_stdlib_nuclear.static: true
*pb_stdlib_nuclear.name: pb_stdlib_nuclear
*pb_stdlib_nuclear.labelString: "Nuclear Standard Library"
*pb_stdlib_nuclear.activateCallback: {\
  char *path_lib, file_lista[256];\
  FILE *fp;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
   if (dbox_listamod_managed)\
   {\
      scrivi_messaggio ("Modules list window already in use.");\
      return;\
   }\
\
/* Composizione percorso e nome file lista_moduli.dat di libreria */\
   file_dati_lib(file_lista, tipo_modulo, LIB_STANDARD_NUCLEAR);\
\
/* Se il file lista_moduli.dat di libreria non esiste */\
/* ritorna con errore */\
   if ( (fp = fopen (file_lista, "r")) == NULL )\
   {\
      scrivi_messaggio ("Can't open data file.");\
      return;\
   }\
\
/* Visualizza la lista moduli e setta la reason della lista */\
   create_lista_moduli(fp,tipo_modulo,STDLIBNUCLEAR_MODULES_COPY,\
                       &dbox_listamod_managed);\
\
   fclose(fp);\
}

*pb_stdlib_special.class: pushButton
*pb_stdlib_special.parent: mb_copy
*pb_stdlib_special.static: true
*pb_stdlib_special.name: pb_stdlib_special
*pb_stdlib_special.labelString: "Special Standard Library"
*pb_stdlib_special.activateCallback: {\
  char *path_lib, file_lista[256];\
  FILE *fp;\
\
/* Se la dialogBox di selezione dei moduli */\
/* e' visualizzata, ritorna */\
   if (dbox_listamod_managed)\
   {\
      scrivi_messaggio ("Modules list window already in use.");\
      return;\
   }\
\
/* Composizione percorso e nome file lista_moduli.dat di libreria */\
   file_dati_lib(file_lista, tipo_modulo, LIB_STANDARD_SPECIAL);\
\
/* Se il file lista_moduli.dat di libreria non esiste */\
/* ritorna con errore */\
   if ( (fp = fopen (file_lista, "r")) == NULL )\
   {\
      scrivi_messaggio ("Can't open data file.");\
      return;\
   }\
\
/* Visualizza la lista moduli e setta la reason della lista */\
   create_lista_moduli(fp,tipo_modulo,STDLIBSPECIAL_MODULES_COPY,\
                       &dbox_listamod_managed);\
\
   fclose(fp);\
}

*mb_icon.class: rowColumn
*mb_icon.parent: menubar
*mb_icon.static: true
*mb_icon.name: mb_icon
*mb_icon.rowColumnType: "menu_pulldown"

*pb_edicole.class: pushButton
*pb_edicole.parent: mb_icon
*pb_edicole.static: true
*pb_edicole.name: pb_edicole
*pb_edicole.labelString: "Edit (EDICOLE)"
*pb_edicole.mnemonic: "E"
*pb_edicole.activateCallback: {\
char *path, program[256];\
int   pid, i, status;\
\
\
  if ( !fine_edicole )\
  {\
     scrivi_messaggio ("EDICOLE already in use.");\
     return;\
  }\
\
  scrivi_messaggio ("Loading EDICOLE...");\
  fine_edicole = False;\
\
/* abilita la ricezione del segnale di terminazione del child */\
  signal(SIGCLD, end_edicole);\
\
#ifndef VMS\
\
/* Attiva un nuovo sotto-processo per l'editazione della bitmap */\
  pid = fork();\
\
#else\
\
  pid = vfork();\
\
#endif\
\
  if ( pid == 0 )\
  {\
     path = (char *) getenv ("LEGOCAD_BIN");\
     strcpy (program,path);\
     strcat (program,"/edicole");\
\
     execl (program,"edicole","-module",nome_modulo,"&", (char *)0);\
  }\
}

*mb_doc.class: rowColumn
*mb_doc.parent: menubar
*mb_doc.static: true
*mb_doc.name: mb_doc
*mb_doc.rowColumnType: "menu_pulldown"

*pb_view.class: pushButton
*pb_view.parent: mb_doc
*pb_view.static: true
*pb_view.name: pb_view
*pb_view.labelString: "View"
*pb_view.mnemonic: "V"
*pb_view.activateCallback: {\
#if defined HYPERHELP_USED\
   /* utilizzo hyperhelp per la documentazione dei moduli */\
   hhelp_doc_modulo();\
#else\
   /* utilizzo i file documentazione di libreria */\
  if (!dbox_doc_managed)\
    create_doc_modulo();\
#endif\
}

*mb_compile.class: rowColumn
*mb_compile.parent: menubar
*mb_compile.static: true
*mb_compile.name: mb_compile
*mb_compile.rowColumnType: "menu_pulldown"

*pb_library.class: pushButton
*pb_library.parent: mb_compile
*pb_library.static: true
*pb_library.name: pb_library
*pb_library.labelString: "Library"
*pb_library.mnemonic: "L"
*pb_library.activateCallback: {\
int flag;\
\
switch (tipo_modulo)\
{\
    case LIBUT:\
         flag = cad_crealibut();\
         break;\
\
    case LIBUTREG:\
         flag = cad_crealibut_reg();\
         break;\
\
    case LIBREG:\
         flag = cad_crealibreg();\
         break;\
}\
}

*mb_options.class: rowColumn
*mb_options.parent: menubar
*mb_options.static: true
*mb_options.name: mb_options
*mb_options.rowColumnType: "menu_pulldown"

*tb_debug.class: toggleButton
*tb_debug.parent: mb_options
*tb_debug.static: true
*tb_debug.name: tb_debug
*tb_debug.labelString: "Compiler Debug OFF"
*tb_debug.mnemonic: "g"
*tb_debug.indicatorType: "one_of_many"
*tb_debug.valueChangedCallback: {\
Boolean stato;\
XmString xmstr;\
\
stato = XmToggleButtonGetState(UxWidget);\
\
if( stato )\
    xmstr = XmStringCreateSimple("Compiler Debug ON");\
else\
    xmstr = XmStringCreateSimple("Compiler Debug OFF");\
\
set_something(UxWidget,XmNlabelString,xmstr);\
\
set_debug(stato);\
}

*mb_options_b3.class: cascadeButton
*mb_options_b3.parent: mb_options
*mb_options_b3.static: true
*mb_options_b3.name: mb_options_b3
*mb_options_b3.labelString: "Touch"
*mb_options_b3.subMenuId: "mb_force"

*mb_force.class: rowColumn
*mb_force.parent: mb_options
*mb_force.static: true
*mb_force.name: mb_force
*mb_force.rowColumnType: "menu_pulldown"

*mb_force_all.class: pushButton
*mb_force_all.parent: mb_force
*mb_force_all.static: true
*mb_force_all.name: mb_force_all
*mb_force_all.labelString: "All Module"
*mb_force_all.activateCallback: {\
char direc[256];\
char comando[256];\
\
percorso_libreria(direc, LIBUT, LIB_UTENTE);\
\
sprintf(comando,"touch -c %s*.f\n",direc);\
\
system(comando);\
}

*mb_force_selected.class: pushButton
*mb_force_selected.parent: mb_force
*mb_force_selected.static: true
*mb_force_selected.name: mb_force_selected
*mb_force_selected.labelString: "Selected Module"
*mb_force_selected.activateCallback: {\
char nomefile[256];\
static char *font_text = "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1";\
char comando[256];\
\
if (!dbox_code_managed)\
{\
/* Percorso del file FORTRAN da editare. */\
   componi_file_modulo(nomefile,nome_modulo,FILE_FTN,tipo_modulo,LIB_UTENTE);\
\
   if( strcmp(nomefile,"") != 0)\
   {\
      sprintf(comando,"touch -c %s\n",nomefile);\
      system(comando);\
   }\
   else\
      scrivi_messaggio("No Module Selected");\
}\
}

*menu1_top_b1.class: cascadeButtonGadget
*menu1_top_b1.parent: menubar
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "mb_file"
*menu1_top_b1.mnemonic: "F"

*menu1_top_b2.class: cascadeButtonGadget
*menu1_top_b2.parent: menubar
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.labelString: "Module"
*menu1_top_b2.subMenuId: "mb_module"
*menu1_top_b2.mnemonic: "M"
*menu1_top_b2.activateCallback: {\
\
}

*menubar_top_b1.class: cascadeButtonGadget
*menubar_top_b1.parent: menubar
*menubar_top_b1.static: true
*menubar_top_b1.name: menubar_top_b1
*menubar_top_b1.labelString: "Icon"
*menubar_top_b1.mnemonic: "I"
*menubar_top_b1.subMenuId: "mb_icon"

*menubar_top_b2.class: cascadeButtonGadget
*menubar_top_b2.parent: menubar
*menubar_top_b2.static: true
*menubar_top_b2.name: menubar_top_b2
*menubar_top_b2.labelString: "Documentation"
*menubar_top_b2.mnemonic: "D"
*menubar_top_b2.subMenuId: "mb_doc"

*menubar_top_b3.class: cascadeButtonGadget
*menubar_top_b3.parent: menubar
*menubar_top_b3.static: true
*menubar_top_b3.name: menubar_top_b3
*menubar_top_b3.labelString: "Compile"
*menubar_top_b3.mnemonic: "C"
*menubar_top_b3.subMenuId: "mb_compile"

*menubar_top_b4.class: cascadeButtonGadget
*menubar_top_b4.parent: menubar
*menubar_top_b4.static: true
*menubar_top_b4.name: menubar_top_b4
*menubar_top_b4.labelString: "Options"
*menubar_top_b4.mnemonic: "O"
*menubar_top_b4.subMenuId: "mb_options"

