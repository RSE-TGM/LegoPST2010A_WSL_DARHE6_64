! UIMX ascii 2.0 key: 4289                                                      

*TopSim.class: mainWindow
*TopSim.parent: NO_PARENT
*TopSim.defaultShell: topLevelShell
*TopSim.static: false
*TopSim.gbldecl: /*\
   modulo TopSim.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)TopSim.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <string.h>\
#include <sys/mode.h>\
#include <sys/stat.h>\
#include <X11/Intrinsic.h> \
#include <Xm/Xm.h>\
#include <X11/cursorfont.h> \
#ifndef DESIGN_TIME\
#include "UxXt.h"\
#endif\
\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
#include "questionMsgDb.h"\
#include "topsim.h"\
#include "lg1_topsim.h"\
\
Cursor waitCursor,normalCursor;\
Boolean sccsstate=False;\
\
SIMULATORE *simulatore=NULL;\
Boolean simulator_changed=False;\
swidget SimSelection=NULL;\
swidget ModelDefinitionInterface=NULL;\
\
Find_struct parametri_userlist;\
\
Arg argq[15];\
Cardinal narg;\
\
/* numero di finestre di connessione aperte */\
int fin_conn_open = 0;
*TopSim.ispecdecl: swidget ConnWind1,VarWind1;\
swidget ConnWind2,VarWind2;\
char SimulatoreCorrente[100];\

*TopSim.ispeclist: ConnWind1, VarWind1, ConnWind2, VarWind2, SimulatoreCorrente
*TopSim.ispeclist.ConnWind1: "swidget", "%ConnWind1%"
*TopSim.ispeclist.VarWind1: "swidget", "%VarWind1%"
*TopSim.ispeclist.ConnWind2: "swidget", "%ConnWind2%"
*TopSim.ispeclist.VarWind2: "swidget", "%VarWind2%"
*TopSim.ispeclist.SimulatoreCorrente: "unsigned char", "%SimulatoreCorrente%[100]"
*TopSim.funcdecl: swidget create_TopSim()\

*TopSim.funcname: create_TopSim
*TopSim.funcdef: "swidget", "<create_TopSim>(%)"
*TopSim.icode: Widget userlist_find_form;\
\
SimSelection = NULL; /* inizializzo */\
ModelDefinitionInterface = NULL;\
ConnWind1=VarWind1=ConnWind2=VarWind2=NULL;
*TopSim.fcode: /*** ATTENZIONE --- istruzioni per rilasciare versione ancora in sviluppo  ****/\
\
   /* rendo inattivi i bottoni per gestione SCCS */\
   set_something(MainConfigureSCCS,XmNsensitive,False);\
   set_something(menu1_p6_b1,XmNsensitive,False); \
\
/*** FINE ****/\
\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,False);narg++;\
   XtSetValues(MainConfigureSCCS,argq,narg);\
\
\
/* Inserimento find di libreria */\
   parametri_userlist.ID_lista = UxGetWidget(ListaModelli);\
   parametri_userlist.num_elem = 100;\
   parametri_userlist.vis_elem = 1;\
   parametri_userlist.pos      = 0;\
\
   narg=0;\
   XtSetArg(argq[narg],XmNleftAttachment,XmATTACH_FORM);\
   narg++;\
   XtSetArg(argq[narg],XmNleftOffset,0);\
   narg++;\
   XtSetArg(argq[narg],XmNrightAttachment,XmATTACH_FORM);\
   narg++;\
   XtSetArg(argq[narg],XmNrightOffset,0);\
   narg++;\
   XtSetArg(argq[narg],XmNbottomAttachment,XmATTACH_FORM);\
   narg++;\
   XtSetArg(argq[narg],XmNbottomOffset,0);\
   narg++;\
   XtSetArg(argq[narg],XmNtopAttachment,XmATTACH_FORM);\
   narg++;\
   XtSetArg(argq[narg],XmNtopOffset,0);\
   narg++;\
\
   userlist_find_form = find_kit(UxGetWidget(FindForm),argq,narg,\
                                                 &parametri_userlist);\
\
\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,False);narg++;\
   XtSetValues(MainEditModify,argq,narg);\
   XtSetValues(MainEditDelete,argq,narg);\
   XtSetValues(MainEditConnect,argq,narg);\
   XtSetValues(MainEditDeleteConn,argq,narg);\
   XtSetValues(MainEditAdd,argq,narg);\
\
   aggiorna_sccsstate();\
\
   show_message("\n\nWelcome in  TOPSIM  Simulator Topology Editor\n");\
   show_message("Property of Enel S.p.A. - C.R.A. Researce Center - Milan (ITALY)\n");\
   show_message("Developed by S.d.I. S.r.l. Milan (ITALY)\n\n");        \
\
   waitCursor = XCreateFontCursor(UxDisplay,XC_watch);\
   normalCursor = XCreateFontCursor(UxDisplay,XC_hand1);\
\
\
   return(rtrn);\

*TopSim.auxdecl: int create_sccsS01();\
Boolean edit_sccsS01();\
\
int distruggi_interfaccie( swidget wid )\
{\
    if( wid == ConnWind1 )\
    {\
       UxDestroyInterface(ConnWind1);\
       UxDestroyInterface(VarWind1);\
    }\
    else if( wid == ConnWind2 )\
    {\
       UxDestroyInterface(ConnWind2);\
       UxDestroyInterface(VarWind2);\
    }\
    else if( wid == VarWind1 )\
    {\
       UxDestroyInterface(ConnWind1);\
       UxDestroyInterface(VarWind1);\
    }\
    else if( wid == VarWind2 )\
    {\
       UxDestroyInterface(ConnWind2);\
       UxDestroyInterface(VarWind2);\
    }\
}\
\
set_wait_cursor()\
{\
   XDefineCursor(UxDisplay,XtWindow(TopSim),waitCursor);\
   XmUpdateDisplay(UxTopLevel);\
}\
\
set_normal_cursor()\
{\
   XDefineCursor(UxDisplay,XtWindow(TopSim),normalCursor);\
}\
\
/*** \
   inizializzazione e lettura del modello \
***/\
\
int init_modello(MODELLO *task)\
{\
   extern Boolean get_working_directory();\
   char path[STRLONG],savepath[STRLONG];\
   char appo[STRLONG];\
   int num_blocchi=0;\
\
/*\
   strcpy(appo,task->nome);\
   tominus(appo);\
   sprintf(path,"%s/legocad/%s",getenv("LEGOCAD_USER"),appo);\
*/\
   printf("init_modello local_path=%s",task->local_path);\
   sprintf(path,"%s",task->local_path);\
\
   get_working_directory(savepath);\
 \
   if(chdir(path) == -1)\
   {\
     printf("CANNOT OPEN MODEL %s\n",path);\
     return(FALSE);\
   }\
 \
   if( read_f01(task) == FALSE )\
   {\
      printf("CANNOT READ F01 OF MODEL %s\n",path);\
      task->num_blocchi=0;\
      return(FALSE);\
   }\
\
   if(chdir(savepath) == -1)\
   {\
     printf("CANNOT RETURN TO SIMULATOR DIRECTORY %s\n",savepath);\
     return(FALSE);\
   }\
\
   return(TRUE);\
}\
\
\
\
/*\
 imposta il menu di edit \
*/\
setta_edit_menu()\
{\
   Cardinal nitem;\
\
/* setto gli item di menu attivi / non attivi */\
\
   narg=0;\
   XtSetArg(argq[narg],XmNselectedItemCount,&nitem);narg++;\
   XtGetValues(ListaModelli,argq,narg);\
\
   if(nitem == 0)\
   {\
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,False);narg++;\
      XtSetValues(MainEditModify,argq,narg);\
      XtSetValues(MainEditDelete,argq,narg);\
      XtSetValues(MainEditConnect,argq,narg);\
      XtSetValues(MainEditDeleteConn,argq,narg);\
   }\
   else if( nitem == 1)\
   {   \
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,True);narg++;\
      XtSetValues(MainEditModify,argq,narg);\
      XtSetValues(MainEditDelete,argq,narg);\
      XtSetValues(MainEditDeleteConn,argq,narg);\
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,False);narg++;\
      XtSetValues(MainEditConnect,argq,narg);\
   }\
   else if( nitem > 1)\
   {\
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,False);narg++;\
      XtSetValues(MainEditModify,argq,narg);\
      XtSetValues(MainEditDeleteConn,argq,narg);\
\
      if( nitem > 2)\
      {\
         narg=0;\
         XtSetArg(argq[narg],XmNsensitive,False);narg++;\
         XtSetValues(MainEditConnect,argq,narg);\
      }\
      else if( nitem == 2)\
      {\
         narg=0;\
         XtSetArg(argq[narg],XmNsensitive,True);narg++;\
         XtSetValues(MainEditConnect,argq,narg);\
      }\
   }\
}\
\
/***\
   crea la lista delle task del simulatore selezionato\
***/ \
void set_listbl(SIMULATORE *sim)\
{\
   MODELLO *mod;\
   char str[200];\
   XmString item;\
   int i;\
\
   XmListDeleteAllItems(ListaModelli);\
\
   for(i=0;i<sim->nmodelli;i++)\
   {\
      mod = sim->modelli[i];\
      sprintf(str,"%s  -  %s",mod->nome,mod->descr);\
      item = XmStringCreateSimple(str);\
      XmListAddItem(ListaModelli,item,0);      \
   } \
}\
\
esiste_task(MODELLO *task)\
{\
   int i,len;\
   char appo1[STRLONG],appo2[STRLONG];\
\
   for(i=0;i<simulatore->nmodelli;i++)\
   {\
\
      len=strlen(task->local_path);\
      if( task->local_path[len-1] =='/')\
         sprintf(appo1,"%s",task->local_path);\
      else\
         sprintf(appo1,"%s/",task->local_path);\
\
      len=strlen(simulatore->modelli[i]->local_path);\
      if( simulatore->modelli[i]->local_path[len-1] =='/')\
         sprintf(appo2,"%s",simulatore->modelli[i]->local_path);\
      else\
         sprintf(appo2,"%s/",simulatore->modelli[i]->local_path);\
      tominus(appo1);\
      tominus(appo2);\
      if( strcmp(appo1,appo2) == NULL)\
         return(TRUE);\
   }\
   return(FALSE);\
}\
\
int add_task(MODELLO *task)\
{\
   extern swidget create_messageDialog();\
   extern MODELLO *alloca_modello();\
   MODELLO *newmod;\
   swidget wid;\
\
\
   if( esiste_task(task) )\
      return(FALSE);\
\
   if( (newmod = alloca_modello()) == NULL)\
   {\
      printf("errore allocazione modelli\n");\
      return(FALSE);\
   }\
\
   memcpy(newmod,task,sizeof(MODELLO));\
\
   if( init_modello( newmod ) == FALSE )\
   {\
      printf("ERRORE la init_modello [%s] e' terminata restituendo un FALSE\n",newmod->nome);\
      return(FALSE);\
   }\
   else\
   {\
      simulatore->modelli[simulatore->nmodelli] = newmod;\
      simulatore->nmodelli++;\
      set_listbl(simulatore);\
   }\
\
   return(TRUE);\
}\
\
int del_all_task_conn()\
{\
   extern int task_delete_all_connections();\
   int i,*lpos,nsel;\
\
   get_model_selected(ListaModelli,&lpos,&nsel);\
\
   if(nsel >0) \
      for(i=0;i<nsel;i++)   \
         task_delete_all_connections( simulatore->modelli[lpos[i]-1] );\
\
}\
\
/***\
   restituisce l'id dello widget della altra varWin\
***/\
\
void getSecVarWin(swidget win1,swidget *win2)\
{\
printf(" getSecVarWin  VarWind1=%d VarWind2=%d\n",VarWind1,VarWind2);\
\
  if( win1 == VarWind1 )\
      *win2 = VarWind2;\
   else if( win1 == VarWind2 )\
      *win2 = VarWind1;\
   else\
      *win2 = NULL; \
printf("ricevo win1=%d, restituisco win2=%d\n",win1,*win2);\
}\
\
\
/***\
  visualizza un messaggio nella window Messages\
***/  \
void show_message(char *mesg)\
{\
   XmTextInsert(scrolledText1,XmTextGetLastPosition(scrolledText1),mesg);\
   XmTextShowPosition(scrolledText1,XmTextGetLastPosition(scrolledText1));\
}\
\
\
/***\
  clear dei messaggi nella window Messages\
***/\
int clear_message()\
{\
   UxPutText(scrolledText1,"");\
}\
\
\
/***\
   setta la directory corrente\
***/ \
void set_working_directory(char *path)\
{\
   strcpy(simulatore->path,path);\
   chdir(path);\
}\
\
/***\
   recupera il path della directory corrente\
***/\
Boolean get_working_directory(char *path)\
{\
   char comando[200];\
   FILE *fp;\
\
   strcpy(comando,"pwd > NomeActDir.tmp");\
   system(comando);\
   if( (fp = fopen("NomeActDir.tmp","r") ) == NULL)\
   {\
      fclose(fp);\
      return(False);\
   }\
\
   fscanf(fp,"%s",path);\
   fclose(fp);\
\
   strcpy(comando,"rm NomeActDir.tmp");\
   system(comando);\
\
   if(strlen(path) == 0)\
      return(False);\
\
   return(True); \
\
}\
\
/***\
   verifica che il nome del direttorio contenuto \
   nella stringa non contenga caratteri non validi\
   ATTUALMENTE verifica solo che non ci siano blank\
***/\
Boolean verifica_nomedir(char *nome)\
{\
   if( strchr(nome,' ') != NULL )\
      return(False);\
\
   return(True);\
}\
\
\
Boolean verifica_lenght(char *str,int len)\
{\
   if( strlen(str) > len)\
      return(False);\
\
   return(True);\
     \
}\
\
\
void ResetSimulatorActive()\
{\
   SimSelection = NULL;\
}\
\
\
/***\
   recupera lo stato del bottone relativo ad SCCS ON/OFF\
   e visualizza nella main window il messaggio associato\
***/\
void aggiorna_sccsstate()\
{\
   XmString xstring;\
\
   sccsstate = XmToggleButtonGetState(MainConfigureSCCS);\
\
   if(sccsstate == True)\
      xstring  = XmStringCreateSimple("SCCS Active");\
   else\
      xstring  = XmStringCreateSimple("SCCS Not Active");\
\
   narg=0;\
   XtSetArg(argq[narg],XmNlabelString,xstring);narg++;\
   XtSetValues(SCCSStateLabel,argq,narg);  \
}\
\
\
get_model_selected(swidget ListaMod,int **positions,int *count )\
{\
   XmListGetSelectedPos(ListaMod,positions,count); \
}\
\
\
/***\
   Imposta le coordinate x,y dove posizionare lo\
   widget \
***/\
    \
set_wind_position(Widget wid,Position x,Position y)\
{\
   narg=0;\
   XtSetArg(argq[narg],XmNx,x);narg++;\
   XtSetArg(argq[narg],XmNy,y);narg++;\
   XtSetValues(wid,argq,narg);\
}\
\
\
/***\
   set insensitive dell main menu \
***/\
void filepane_setinsensitive(TIPO_OP operaz)\
{\
    narg=0;\
    XtSetArg(argq[narg],XmNsensitive,False);narg++;\
\
    switch(operaz)\
    {\
       case CREASIM:\
           XtSetValues(MainFileOpen,argq,narg);\
           XtSetValues(MainFileRemove,argq,narg);\
\
           narg=0;\
           XtSetArg(argq[narg],XmNsensitive,True);narg++;\
           XtSetValues(MainEditAdd,argq,narg);\
\
\
       break;  \
       case OPENSIM:\
\
           XtSetValues(MainFileCreate,argq,narg);\
           XtSetValues(MainFileRemove,argq,narg);\
\
           narg=0;\
           XtSetArg(argq[narg],XmNsensitive,True);narg++;\
           XtSetValues(MainEditAdd,argq,narg);\
\
       break;\
       case REMOVESIM:\
           XtSetValues(MainFileCreate,argq,narg);\
           XtSetValues(MainFileOpen,argq,narg);\
       break;\
    } \
}\
\
\
/***\
   set sensitive del main menu\
***/\
 \
void filepane_setsensitive()\
{\
    narg=0;\
    XtSetArg(argq[narg],XmNsensitive,True);narg++;\
\
    XtSetValues(MainFileCreate,argq,narg);\
    XtSetValues(MainFileOpen,argq,narg);\
    XtSetValues(MainFileRemove,argq,narg);\
}\
\
\
/***\
   visualizza il nome del simulatore selezionato\
   nella main window\
***/\
\
void set_simnome(char *nome)\
{\
   XmString xstring;\
  \
   xstring = XmStringCreateSimple(nome);\
   narg=0;\
   XtSetArg(argq[narg],XmNlabelString,xstring);narg++;\
   XtSetValues(NomeSimulatore,argq,narg);\
}\
\
\
\
\
/***\
   visualizza il nome del simulatore e la lista delle task\
   del simulatore selezionato\
***/\
void display_data(SIMULATORE *sim)\
{\
\
   set_simnome(sim->nome);   \
\
   set_listbl(sim);\
\
}\
\
/***\
   open del simulatrore selezionato \
***/\
Boolean open_simulator(char *path)\
{\
   extern int read_S01data();\
   extern void libera_simulatore();\
   extern SIMULATORE * alloca_simulatore();\
   char filename[100];\
   char wdir[100];\
\
   if(path == NULL)\
      return(False);\
\
   strcpy(filename,path);\
   strcat(filename,"/S01");       \
\
   if( simulatore != NULL)\
      libera_simulatore(simulatore);\
\
   if( (simulatore = alloca_simulatore()) != NULL  )\
   {\
\
      if( read_S01data( filename, simulatore ) != True)\
         return( False );\
\
      display_data(simulatore);\
\
      strcpy(SimulatoreCorrente,filename);\
\
      get_working_directory(wdir);\
\
      set_working_directory(path);\
\
      simulator_changed = False; \
      return(True);\
   }\
   else\
      return(False);\
   \
} \
\
/***\
***/\
Boolean writeS01_vuoto(char *path,char *nome)\
{\
   char *filename;\
   FILE *fp;\
\
   filename = XtMalloc( (strlen(path) + strlen("/S01") +2) );\
   strcpy(filename,path);\
   strcat(filename,"/S01"); \
    \
   if( (fp = fopen(filename,"w")) == NULL)\
   {\
      printf("Cannot write S01 file\n");\
      return(False);\
   } \
\
   fprintf(fp,"%s\n","****");\
   fprintf(fp,"%s\n",nome);  \
   fprintf(fp,"%s\n","****");\
   fclose(fp);\
   XtFree(filename); \
   return(True);\
}\
\
/***\
   crea la directory SCCS nel direttorio indicato\
***/\
void crea_sccsdir(char *pathname)\
{\
   char comando[256],appo[256];\
\
   sprintf(comando,"mkdir %s/SCCS",pathname);\
   system(comando);   \
\
   chdir(pathname);\
\
   sprintf(comando,"sccs create S01");\
   system(comando);\
\
}\
\
/***\
   crea un nuovo simulatore \
***/\
Boolean create_simulator(char *path)\
{\
   char comando[100];\
   char *nome,*point;\
\
   if( path != NULL )\
   {\
\
      /* ricerco l'ultimo slash e recupero il nome del simulatore */\
      point = strrchr(path,'/'); \
      point++;\
\
      /* il nome del simulatore non puo' essere pi' lungo di 8 ch */\
      if( verifica_lenght(point,0) || !verifica_lenght(point,8))\
      { \
         printf("Error. Simulator Name too long or invalid\n");\
         return(False);\
      } \
\
      if( (nome = XtMalloc( strlen(point) )) == NULL)\
      {\
         printf("create_simulator: Error in Malloc\n");\
         return(False);\
      }\
      strcpy(nome,point);     \
  \
      if( verifica_nomedir(nome) == False)\
      {\
         printf("il nome digitato contiene caratteri non validi\n");\
         return(False);\
      }\
\
      strcpy(comando,"mkdir ");\
      strcat(comando,path); \
      system(comando);\
\
      /* creo un file S01 */\
      if( writeS01_vuoto(path,nome) == False)\
      { \
         printf("Error Writing file S01\n");\
         XtFree(nome);\
         return(False);\
      }      \
\
      /* se richiesto crea anche la directory SCCS */\
      if(sccsstate)\
      {\
         crea_sccsdir(path);\
         create_sccsS01();\
         edit_sccsS01(" ");\
      }\
\
      XtFree(nome);\
      return(True);\
   }\
   else\
      return(False);\
}\
\
/***\
   rimuove un simulatore \
***/\
\
Boolean remove_simulator(char *path)\
{\
/* ATTENZIONE QUESTA ROUTINE NON VERIFICA SE SI STA\
   FACENDO LA CANCELLAZIONE DELLA DIRECTORY \
   ATTUALE OVE SI E' POSIZIONATI!!! \
   IN QUESTO CASO POSSONO VERIFICARSI PROBLEMI\
*/\
 \
   char comando[200],filename[100];\
   FILE *fp; \
\
\
   strcpy(filename,path);\
   strcat(filename,"/S01");\
 \
   if( (fp = fopen (filename,"r")) == NULL)\
   {\
      printf("\n\tERROR - File %s is not in directory \n\tThis directory does not appear as Simulator Directory", filename);\
      return(False);\
   }  \
   fclose(fp);\
\
/* elimino tutti i file,sottodirectory  e la directory 'path'\
   senza richiedere ultriore conferma all'operatore */\
\
   strcpy(comando,"rm -rf ");\
   strcat(comando,path);\
   system(comando);\
   UxDestroyInterface(SimSelection);\
}\
\
/***\
   aggiunge una task al simulatore\
***/\
\
Boolean aggiungi_task(MODELLO *task)\
{\
   extern MODELLO *alloca_modello();\
\
   /* devo incrementare il numero dei modelli del simulatore \
      e allocare un nuovo MODELLO \
   */\
   simulatore->modelli[simulatore->nmodelli] = alloca_modello();\
   simulatore->nmodelli++;\
}\
\
\
compatta_modelli(int indice_start)\
{\
   int i;\
\
   for(i=indice_start;i<=simulatore->nmodelli-2;i++)\
   {       \
       simulatore->modelli[i] = simulatore->modelli[i+1];\
   }\
   simulatore->modelli[simulatore->nmodelli-1] = 0;\
}\
\
/***\
   rimuove una task ad un simulatore\
***/\
\
Boolean rimuovi_task(MODELLO *task)\
{\
   int i;\
   extern int task_delete_all_connections();\
\
   \
   task_delete_all_connections( task );\
\
   for(i=0;i<simulatore->nmodelli;i++)\
   {\
      if( simulatore->modelli[i] == task )\
      {\
         libera_modello(task);\
         simulatore->modelli[i] = NULL;\
         compatta_modelli(i);\
         simulatore->nmodelli--;\
      }\
   }\
}\
\
confermata_remove_task()\
{\
   int *lpos,nsel;\
\
   get_model_selected(ListaModelli,&lpos,&nsel);\
\
   if(nsel >0)    \
   {\
      rimuovi_task(simulatore->modelli[lpos[0]-1]);\
      XmListDeletePos(ListaModelli,lpos[0]);\
   }\
\
   if( nsel > 1)   \
      confermata_remove_task();\
\
   setta_edit_menu();    \
}\
\
\
\
/*---------------------------------------------------------------------------*/\
/*************************  COMANDI SCCS *************************************/\
/*---------------------------------------------------------------------------*/\
/***\
   UNEDIT SCCS\
***/\
Boolean unedit_sccsS01()\
{\
   char comando[256],path[256];\
\
   get_working_directory(path); \
   chdir(path); \
\
   strcpy(comando,"sccs unedit S01");\
   system(comando);\
\
   return(True);\
\
}\
\
/***\
   INFO SCCS\
***/\
Boolean info_sccsS01()\
{\
   extern swidget create_ViewS01();\
   char comando[256],path[256];\
   swidget sw;\
\
   get_working_directory(path); \
   chdir(path);  \
\
   strcpy(comando,"sccs info > info");\
   system(comando);\
\
   sw=create_ViewS01("info");\
   UxPopupInterface(sw,no_grab);\
   return(True);\
\
}\
\
/***\
   GET SCCS\
***/\
Boolean get_sccsS01(char *vers)\
{\
   char comando[256],path[256];\
\
   get_working_directory(path); \
   chdir(path);     \
\
   sprintf(comando,"sccs get -r%s S01",vers);\
   printf("Invio il comando %s\n",comando);\
   system(comando);\
   return(True);\
}\
\
/*** \
   EDIT SCCS\
***/\
Boolean edit_sccsS01(char *vers)\
{\
   char comando[256],path[256];;\
\
   get_working_directory(path); \
   chdir(path);   \
\
   sprintf(comando,"sccs edit -r%s S01",vers);\
   printf("Invio il comando %s\n",comando);\
   system(comando);\
   return(True);\
}\
\
/***\
   DELTA SCCS\
***/\
Boolean delta_sccsS01()\
{\
   char comando[256],path[100];\
\
   get_working_directory(path); \
   chdir(path);   \
   save_S01(path);\
\
   strcpy(comando,"sccs delta -ycommento S01");\
   printf("Invio il comando %s\n",comando);\
   system(comando);\
\
   return(True);\
}\
\
/***\
   CREATE SCCS\
***/\
int create_sccsS01()\
{\
   char comando[256],path[256],sccsdir[256];\
\
   get_working_directory(path); \
   chdir(path);   \
\
   sprintf(comando,"mkdir %s/SCCS",path);\
   system(comando);\
 \
   strcpy(comando,"sccs create S01");\
   printf("Invio il comando %s\n",comando);\
   system(comando);\
\
   return(True);\
}\
\
/*---------------------------------------------------------------------------*/\
/************************* FINE COMANDI SCCS *********************************/\
/*---------------------------------------------------------------------------*/\

*TopSim.name: TopSim
*TopSim.unitType: "pixels"
*TopSim.x: 350
*TopSim.y: 210
*TopSim.width: 590
*TopSim.height: 680

*menu1.class: rowColumn
*menu1.parent: TopSim
*menu1.static: true
*menu1.name: menu1
*menu1.rowColumnType: "menu_bar"
*menu1.menuAccelerator: "<KeyUp>F10"

*MainFile.class: rowColumn
*MainFile.parent: menu1
*MainFile.static: true
*MainFile.name: MainFile
*MainFile.rowColumnType: "menu_pulldown"

*MainFileCreate.class: pushButton
*MainFileCreate.parent: MainFile
*MainFileCreate.static: true
*MainFileCreate.name: MainFileCreate
*MainFileCreate.labelString: "Create Sim"
*MainFileCreate.activateCallback: {\
   extern swidget create_SimulatorSelection();\
   extern void simulatorselection_settitle(); \
   extern swidget create_msgToUser();\
\
   if( fin_conn_open )\
   {\
      create_msgToUser(0,"Connections Window Already Open. Close First");\
      return;\
   }\
\
   if( SimSelection == NULL)\
   {\
      SimSelection = create_SimulatorSelection(CREASIM);\
      UxPopupInterface(SimSelection,no_grab);\
      filepane_setinsensitive(CREASIM);\
   }\
   else\
      XRaiseWindow( UxDisplay, XtWindow(XtParent(SimSelection)) );\
  \
}

*MainFileOpen.class: pushButton
*MainFileOpen.parent: MainFile
*MainFileOpen.static: true
*MainFileOpen.name: MainFileOpen
*MainFileOpen.labelString: "Open Sim"
*MainFileOpen.activateCallback: {\
   extern swidget create_SimulatorSelection();\
   extern swidget create_msgToUser();\
\
   if( fin_conn_open)\
   {\
      create_msgToUser(0,"Connections Window Already Open. Close First");\
      return;\
   }\
\
   if( SimSelection == NULL )\
   {\
      SimSelection = create_SimulatorSelection(OPENSIM);\
      UxPopupInterface( SimSelection,no_grab);\
      filepane_setinsensitive(OPENSIM);\
   }\
   else\
     XRaiseWindow( UxDisplay,XtWindow( XtParent(SimSelection)) );\
\
   if( simulator_changed )\
     create_msgToUser(0,"WARNING Current Model Not Save");\
}

*MainFileRemove.class: pushButton
*MainFileRemove.parent: MainFile
*MainFileRemove.static: true
*MainFileRemove.name: MainFileRemove
*MainFileRemove.labelString: "Remove Sim"
*MainFileRemove.activateCallback: {\
   extern swidget create_SimulatorSelection();\
\
   if( SimSelection == NULL )\
   {\
      SimSelection = create_SimulatorSelection(REMOVESIM);\
      UxPopupInterface(SimSelection,no_grab);\
      filepane_setinsensitive(REMOVESIM);\
   }\
   else\
     XRaiseWindow( UxDisplay, XtWindow(XtParent(SimSelection)) );\
\
}

*MainFileSave.class: pushButton
*MainFileSave.parent: MainFile
*MainFileSave.static: true
*MainFileSave.name: MainFileSave
*MainFileSave.labelString: "Save S01"
*MainFileSave.activateCallback: {\
   extern swidget create_SCCSGEST();\
   extern int exist_sccsdir();\
   extern swidget create_msgToUser();\
   swidget wid;\
   char path[100];\
   Boolean Model_Save;\
\
/* ancora non viene testata la gestione\
   con SCCS  per il momento si suppone \
   SCCS ON */\
 \
printf("callback save \n");\
\
/***\
   aggiorna_sccsstate();\
***/\
\
   get_working_directory(path);\
\
/***\
   if(sccsstate && exist_sccsdir(path) )\
   {\
      wid = create_SCCSGEST(SAVESIM,path);\
      UxPopupInterface(wid,no_grab);\
   }\
   else\
***/\
\
   {\
      set_wait_cursor();\
      printf("chiamo la save_S01\n");\
\
      Model_Save = save_S01(path);\
\
      if( !Model_Save )\
         create_msgToUser(0,"ERROR  MODEL NOT SAVED. VERIFY PERMISSION ON S01");\
      else\
         if( check_delta_time() != TRUE )\
            create_msgToUser(0,"WARNING This Model Have ACTIVATION INTERVAL Not Correct. MODEL SAVE OK");\
         else\
            create_msgToUser(0,"MODEL SAVE OK");\
\
       set_normal_cursor();\
\
   } \
   simulator_changed = False;\
\
}

*MainFileSaveAs.class: pushButton
*MainFileSaveAs.parent: MainFile
*MainFileSaveAs.static: true
*MainFileSaveAs.name: MainFileSaveAs
*MainFileSaveAs.labelString: "Save As.."
*MainFileSaveAs.activateCallback.source: public
*MainFileSaveAs.activateCallback: 

*MainFileExit.class: pushButton
*MainFileExit.parent: MainFile
*MainFileExit.static: true
*MainFileExit.name: MainFileExit
*MainFileExit.labelString: "Exit"
*MainFileExit.activateCallback: {\
extern swidget create_questionDialog();\
swidget wid;\
\
wid = create_questionDialog(MainFileExit,BYEBYE);\
UxPopupInterface(wid,no_grab);\
}

*MainEdit.class: rowColumn
*MainEdit.parent: menu1
*MainEdit.static: true
*MainEdit.name: MainEdit
*MainEdit.rowColumnType: "menu_pulldown"

*MainEditModify.class: pushButton
*MainEditModify.parent: MainEdit
*MainEditModify.static: true
*MainEditModify.name: MainEditModify
*MainEditModify.labelString: "Modify Task"
*MainEditModify.activateCallback: {\
   extern swidget create_ModelDefinitionWindow();\
   int *lpos,nsel;\
\
   get_model_selected(ListaModelli,&lpos,&nsel);\
\
   if( ModelDefinitionInterface == NULL ) \
   {\
      if( nsel == 1 )\
      {\
         printf("simulatore->modelli[lpos-1]=%d\n",simulatore->modelli[lpos[0]-1]);\
         ModelDefinitionInterface  =  create_ModelDefinitionWindow(simulatore->modelli[lpos[0]-1],MODTASK);\
         UxPopupInterface(ModelDefinitionInterface,no_grab);\
      }\
      else\
         show_message("\nYou must select One model.\n");\
   }\
   else \
   {\
       XRaiseWindow( UxDisplay, XtWindow(ModelDefinitionInterface) );\
   }\
}

*MainEditDelete.class: pushButton
*MainEditDelete.parent: MainEdit
*MainEditDelete.static: true
*MainEditDelete.name: MainEditDelete
*MainEditDelete.labelString: "Delete Task"
*MainEditDelete.activateCallback: {\
   swidget wid;\
   int *position,count=0;\
\
   get_model_selected(ListaModelli,&position,&count);\
   if( count )\
   {\
      wid = create_questionDialog(MainEditDelete,DELTASK);\
      UxPopupInterface(wid,no_grab);\
   }\
   else\
      show_message("\nYou must select One model.\n");\
}

*MainEditDeleteConn.class: pushButton
*MainEditDeleteConn.parent: MainEdit
*MainEditDeleteConn.static: true
*MainEditDeleteConn.name: MainEditDeleteConn
*MainEditDeleteConn.labelString: "Delete All Task Connections"
*MainEditDeleteConn.activateCallback: {\
   int *position,count=0;\
   swidget wid;\
\
\
   get_model_selected(ListaModelli,&position,&count);\
   if( count )\
   {\
       wid = create_questionDialog(MainEditDelete,DELALLCONN);\
      UxPopupInterface(wid,no_grab);\
   }\
   else\
      show_message("\nYou must select One model.\n");\
}

*MainEditAdd.class: pushButton
*MainEditAdd.parent: MainEdit
*MainEditAdd.static: true
*MainEditAdd.name: MainEditAdd
*MainEditAdd.labelString: "Add Task"
*MainEditAdd.activateCallback: {\
   extern swidget create_ModelDefinitionWindow();\
   int lpos,nsel;\
   char *app=NULL;\
\
\
   if( ModelDefinitionInterface == NULL ) \
   {\
      ModelDefinitionInterface  =  create_ModelDefinitionWindow(app,ADDTASK);\
      UxPopupInterface(ModelDefinitionInterface,no_grab);\
   }\
   else \
      XRaiseWindow( UxDisplay, XtWindow(ModelDefinitionInterface) );\
\
}

*MainEditConnect.class: pushButton
*MainEditConnect.parent: MainEdit
*MainEditConnect.static: true
*MainEditConnect.name: MainEditConnect
*MainEditConnect.labelString: "Connect Task"
*MainEditConnect.activateCallback: {\
extern swidget create_msgToUser();\
extern swidget create_ModelConnessionWindow();\
extern swidget create_topVarWin1();\
extern void set_connwind_closure();\
char *str_type[20];\
XrmValue value;\
char oldcolor[50];\
int *position,count;\
MODELLO *mod1,*mod2;\
int ind_mod1,ind_mod2;\
\
if( fin_conn_open )\
{\
   create_msgToUser(0,"Connections Window Already Open. Close First");\
   return;\
}\
\
/* recupero i due modelli selezionati */\
get_model_selected(ListaModelli,&position,&count);\
if( count != 2)\
   return;\
\
printf("position[0]-1 = %d\n",position[0]-1);\
printf("position[1]-1 = %d\n",position[1]-1);\
\
mod1 = simulatore->modelli[position[0]-1];\
mod2 = simulatore->modelli[position[1]-1];\
\
ind_mod1=position[0]-1;\
ind_mod2=position[1]-1;\
\
printf("mod1 = %s ind_mod1=%d\n",mod1->nome,ind_mod1);\
printf("mod2 = %s ind_mod2=%d\n",mod2->nome,ind_mod2);\
\
/* recupero il colore di background della applicazione */\
XrmGetResource( (UxDisplay->db) ,"topsim.background","Topsim.Background",str_type,&value);\
strncpy(oldcolor,value.addr,(int)value.size);\
\
/* setto il background della shell di connessione 1 */\
XrmPutStringResource( &(UxDisplay->db) ,"*background",COLWINDCONN1);\
\
/* creo le interfacce */\
ConnWind1 = create_ModelConnessionWindow(mod1);\
UxPopupInterface(ConnWind1,no_grab);\
\
sleep(1);\
\
VarWind1 = create_topVarWin1(mod1,ind_mod1,position[0]-1);\
UxPopupInterface(VarWind1,no_grab);\
set_connwind_closure(VarWind1);\
\
/* setto la loro posizione */\
set_wind_position(ConnWind1,XCONN1,YCONN1);\
set_wind_position(VarWind1,XCONN1,YVAR);\
\
/* setto il background della shell di connessione 2 */\
XrmPutStringResource(&(UxDisplay->db),"*background",COLWINDCONN2);\
\
/* creo la Connession Window 2 */\
ConnWind2 = create_ModelConnessionWindow(mod2);\
UxPopupInterface(ConnWind2,no_grab);\
VarWind2 = create_topVarWin1(mod2,ind_mod2,position[1]-1);\
UxPopupInterface(VarWind2,no_grab);\
set_connwind_closure(VarWind2);\
\
/* setto la posizione */\
set_wind_position(ConnWind2,XCONN2,YCONN2);\
set_wind_position(VarWind2,XCONN2,YVAR);\
\
/* rispristino il colore di background iniziale */\
XrmPutStringResource( &(UxDisplay->db) ,"*background",oldcolor);\
\
}

*MainUtilities.class: rowColumn
*MainUtilities.parent: menu1
*MainUtilities.static: true
*MainUtilities.name: MainUtilities
*MainUtilities.rowColumnType: "menu_pulldown"

*MainUtilitiesCopy.class: pushButton
*MainUtilitiesCopy.parent: MainUtilities
*MainUtilitiesCopy.static: true
*MainUtilitiesCopy.name: MainUtilitiesCopy
*MainUtilitiesCopy.labelString: "Copy S01"
*MainUtilitiesCopy.activateCallback: {\
swidget swid;\
extern swidget create_CopyS01(); \
\
swid = create_CopyS01();\
UxPopupInterface(swid,no_grab);\
}

*MainUtilitiesView.class: pushButton
*MainUtilitiesView.parent: MainUtilities
*MainUtilitiesView.static: true
*MainUtilitiesView.name: MainUtilitiesView
*MainUtilitiesView.labelString: "View S01"
*MainUtilitiesView.activateCallback: {\
extern swidget create_ViewS01();\
swidget wid;\
\
wid = create_ViewS01(SimulatoreCorrente);\
UxPopupInterface(wid,no_grab);\
}

*MainConfigure.class: rowColumn
*MainConfigure.parent: menu1
*MainConfigure.static: true
*MainConfigure.name: MainConfigure
*MainConfigure.rowColumnType: "menu_pulldown"

*MainConfigureSCCS.class: toggleButtonGadget
*MainConfigureSCCS.parent: MainConfigure
*MainConfigureSCCS.static: true
*MainConfigureSCCS.name: MainConfigureSCCS
*MainConfigureSCCS.labelString: "SCCS"
*MainConfigureSCCS.set: "false"
*MainConfigureSCCS.visibleWhenOff: "true"
*MainConfigureSCCS.valueChangedCallback: aggiorna_sccsstate();

*MainCompi.class: rowColumn
*MainCompi.parent: menu1
*MainCompi.static: true
*MainCompi.name: MainCompi
*MainCompi.rowColumnType: "menu_pulldown"

*MainNetCompi.class: pushButton
*MainNetCompi.parent: MainCompi
*MainNetCompi.static: true
*MainNetCompi.name: MainNetCompi
*MainNetCompi.labelString: "net_compi"
*MainNetCompi.activateCallback: {\
      set_wait_cursor();\
      system("net_compi > compi.out"); \
      show_message("Compilation Done.\nYou can see output results on file net_compi.out.\n");\
      set_normal_cursor();\
}

*MainView.class: pushButton
*MainView.parent: MainCompi
*MainView.static: true
*MainView.name: MainView
*MainView.labelString: "View results"
*MainView.activateCallback: {\
extern swidget create_ViewS01();\
swidget wid;\
\
wid = create_ViewS01("net_compi.out");\
UxPopupInterface(wid,no_grab);\
}

*SCCS.class: rowColumn
*SCCS.parent: menu1
*SCCS.static: true
*SCCS.name: SCCS
*SCCS.rowColumnType: "menu_pulldown"

*menu1_p6_b1.class: pushButton
*menu1_p6_b1.parent: SCCS
*menu1_p6_b1.static: true
*menu1_p6_b1.name: menu1_p6_b1
*menu1_p6_b1.labelString: "SCCS Interface"
*menu1_p6_b1.activateCallback: {\
   extern swidget create_SCCSGESTnew();\
   swidget sw;\
\
   sw = create_SCCSGESTnew(simulatore->path);\
   UxPopupInterface(sw,no_grab);\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: menu1
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "MainFile"

*menu1_top_b2.class: cascadeButton
*menu1_top_b2.parent: menu1
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.labelString: "Edit"
*menu1_top_b2.subMenuId: "MainEdit"

*menu1_top_b3.class: cascadeButton
*menu1_top_b3.parent: menu1
*menu1_top_b3.static: true
*menu1_top_b3.name: menu1_top_b3
*menu1_top_b3.labelString: "Utilities"
*menu1_top_b3.subMenuId: "MainUtilities"

*menu1_top_b4.class: cascadeButton
*menu1_top_b4.parent: menu1
*menu1_top_b4.static: true
*menu1_top_b4.name: menu1_top_b4
*menu1_top_b4.labelString: "Configure"
*menu1_top_b4.subMenuId: "MainConfigure"

*menu1_top_b5.class: cascadeButton
*menu1_top_b5.parent: menu1
*menu1_top_b5.static: true
*menu1_top_b5.name: menu1_top_b5
*menu1_top_b5.labelString: "Compile"
*menu1_top_b5.subMenuId: "MainCompi"

*menu1_top_b6.class: cascadeButton
*menu1_top_b6.parent: menu1
*menu1_top_b6.static: true
*menu1_top_b6.name: menu1_top_b6
*menu1_top_b6.labelString: "SCCS"
*menu1_top_b6.subMenuId: "SCCS"

*panedWindow2.class: panedWindow
*panedWindow2.parent: TopSim
*panedWindow2.static: true
*panedWindow2.name: panedWindow2

*form2.class: form
*form2.parent: panedWindow2
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.x: 10
*form2.y: 10
*form2.width: 570
*form2.height: 510
*form2.paneMinimum: 400

*Titolo.class: label
*Titolo.parent: form2
*Titolo.static: true
*Titolo.name: Titolo
*Titolo.x: 130
*Titolo.y: 10
*Titolo.width: 290
*Titolo.height: 40
*Titolo.labelString: "SIMULATOR TOPOLOGY"
*Titolo.fontList: "helvetica_oblique14"
*Titolo.topAttachment: "attach_form"
*Titolo.topOffset: 5
*Titolo.leftAttachment: "attach_form"
*Titolo.rightAttachment: "attach_form"
*Titolo.leftOffset: 5
*Titolo.rightOffset: 5

*NomeSimulatore.class: label
*NomeSimulatore.parent: form2
*NomeSimulatore.static: true
*NomeSimulatore.name: NomeSimulatore
*NomeSimulatore.x: 5
*NomeSimulatore.y: 50
*NomeSimulatore.width: 420
*NomeSimulatore.height: 40
*NomeSimulatore.labelString: "NOME DEL SIMULATORE"
*NomeSimulatore.fontList: "helvetica_bold18"
*NomeSimulatore.leftAttachment: "attach_form"
*NomeSimulatore.leftOffset: 5
*NomeSimulatore.rightAttachment: "attach_form"
*NomeSimulatore.rightOffset: 5
*NomeSimulatore.topAttachment: "attach_widget"
*NomeSimulatore.topWidget: "Titolo"
*NomeSimulatore.topOffset: 5

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: form2
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 4
*scrolledWindow2.y: 132
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.bottomAttachment: "attach_form"
*scrolledWindow2.bottomOffset: 50
*scrolledWindow2.topAttachment: "attach_form"
*scrolledWindow2.topOffset: 140
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.rightOffset: 10
*scrolledWindow2.leftOffset: 10
*scrolledWindow2.leftAttachment: "attach_form"

*ListaModelli.class: scrolledList
*ListaModelli.parent: scrolledWindow2
*ListaModelli.static: true
*ListaModelli.name: ListaModelli
*ListaModelli.width: 564
*ListaModelli.height: 381
*ListaModelli.selectionPolicy: "multiple_select"
*ListaModelli.multipleSelectionCallback: {\
Cardinal nitem;\
\
/* setto gli item di menu attivi / non attivi */\
\
narg=0;\
XtSetArg(argq[narg],XmNselectedItemCount,&nitem);narg++;\
XtGetValues(ListaModelli,argq,narg);\
\
if(nitem == 0)\
{\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,False);narg++;\
   XtSetValues(MainEditModify,argq,narg);\
   XtSetValues(MainEditDelete,argq,narg);\
   XtSetValues(MainEditConnect,argq,narg);\
   XtSetValues(MainEditDeleteConn,argq,narg);\
}\
else if( nitem == 1)\
{\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,True);narg++;\
   XtSetValues(MainEditModify,argq,narg);\
   XtSetValues(MainEditDelete,argq,narg);\
   XtSetValues(MainEditDeleteConn,argq,narg);\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,False);narg++;\
   XtSetValues(MainEditConnect,argq,narg);\
}\
else if( nitem > 1)\
{\
   narg=0;\
   XtSetArg(argq[narg],XmNsensitive,False);narg++;\
   XtSetValues(MainEditModify,argq,narg);\
   XtSetValues(MainEditDeleteConn,argq,narg);\
\
   if( nitem > 2)\
   {\
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,False);narg++;\
      XtSetValues(MainEditConnect,argq,narg);\
   }\
   else if( nitem == 2)\
   {\
      narg=0;\
      XtSetArg(argq[narg],XmNsensitive,True);narg++;\
      XtSetValues(MainEditConnect,argq,narg);\
   }\
}\
\
\
}

*SCCSStateLabel.class: label
*SCCSStateLabel.parent: form2
*SCCSStateLabel.static: true
*SCCSStateLabel.name: SCCSStateLabel
*SCCSStateLabel.x: 235
*SCCSStateLabel.y: 95
*SCCSStateLabel.width: 106
*SCCSStateLabel.height: 31
*SCCSStateLabel.labelString: "SCCS Active"
*SCCSStateLabel.fontList: "helvetica12"
*SCCSStateLabel.labelType: "string"
*SCCSStateLabel.leftAttachment: "attach_form"
*SCCSStateLabel.leftOffset: 5
*SCCSStateLabel.rightAttachment: "attach_form"
*SCCSStateLabel.rightOffset: 5
*SCCSStateLabel.alignment: "alignment_center"

*FindForm.class: form
*FindForm.parent: form2
*FindForm.static: true
*FindForm.name: FindForm
*FindForm.resizePolicy: "resize_none"
*FindForm.x: 10
*FindForm.y: 472
*FindForm.width: 566
*FindForm.height: 32
*FindForm.leftPosition: 0
*FindForm.bottomAttachment: "attach_form"
*FindForm.bottomOffset: 10
*FindForm.topAttachment: "attach_widget"
*FindForm.topOffset: 10
*FindForm.topWidget: "scrolledWindow2"
*FindForm.leftOffset: 5
*FindForm.rightAttachment: "attach_form"
*FindForm.rightOffset: 5
*FindForm.leftAttachment: "attach_form"

*form1.class: form
*form1.parent: panedWindow2
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.x: 0
*form1.y: 619
*form1.width: 590
*form1.height: 27
*form1.paneMinimum: 100

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form1
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 11
*scrolledWindow1.y: 10
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.topAttachment: "attach_form"
*scrolledWindow1.bottomOffset: 10
*scrolledWindow1.leftOffset: 5
*scrolledWindow1.rightOffset: 5
*scrolledWindow1.topOffset: 25

*scrolledText1.class: scrolledText
*scrolledText1.parent: scrolledWindow1
*scrolledText1.static: true
*scrolledText1.name: scrolledText1
*scrolledText1.width: 562
*scrolledText1.height: 105
*scrolledText1.editable: "false"
*scrolledText1.editMode: "multi_line_edit"
*scrolledText1.pendingDelete: "false"

*menu2.class: rowColumn
*menu2.parent: scrolledText1
*menu2.static: true
*menu2.name: menu2
*menu2.rowColumnType: "menu_popup"
*menu2.menuAccelerator: "<KeyUp>F4"

*menu2_p1_b1.class: labelGadget
*menu2_p1_b1.parent: menu2
*menu2_p1_b1.static: true
*menu2_p1_b1.name: menu2_p1_b1
*menu2_p1_b1.labelString: "MESSAGE"

*menu2_p1_b3.class: separatorGadget
*menu2_p1_b3.parent: menu2
*menu2_p1_b3.static: true
*menu2_p1_b3.name: menu2_p1_b3

*menu2_p1_b2.class: pushButton
*menu2_p1_b2.parent: menu2
*menu2_p1_b2.static: true
*menu2_p1_b2.name: menu2_p1_b2
*menu2_p1_b2.labelString: "Clear Window"
*menu2_p1_b2.mnemonic: "C"
*menu2_p1_b2.activateCallback: {\
   clear_message();\
}

*label1.class: label
*label1.parent: form1
*label1.static: true
*label1.name: label1
*label1.x: 7
*label1.y: 4
*label1.width: 143
*label1.height: 18
*label1.bottomAttachment: "attach_widget"
*label1.bottomOffset: 5
*label1.bottomWidget: "scrolledWindow1"
*label1.topAttachment: "attach_form"
*label1.topOffset: 5
*label1.labelString: "Messages"
*label1.alignment: "alignment_beginning"
*label1.rightAttachment: "attach_form"
*label1.rightOffset: 5
*label1.leftAttachment: "attach_form"
*label1.leftOffset: 5

