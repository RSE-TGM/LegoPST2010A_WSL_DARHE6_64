! UIMX ascii 2.0 key: 3101                                                      

*SimulatorSelection.class: fileSelectionBoxDialog
*SimulatorSelection.parent: NO_PARENT
*SimulatorSelection.defaultShell: topLevelShell
*SimulatorSelection.static: true
*SimulatorSelection.gbldecl: /*\
   modulo SimulatorSelection.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)SimulatorSelection.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "topsim.h"\
#include "lg1_topsim.h"\
#include "questionMsgDb.h"\

*SimulatorSelection.ispecdecl: Boolean new_simulator;  /* True se S01 non esiste */\
char *simulator_path;   /* mi aspetto il path completo */\
TIPO_OP idoper;\

*SimulatorSelection.ispeclist: new_simulator, simulator_path, idoper
*SimulatorSelection.ispeclist.new_simulator: "Boolean", "%new_simulator%"
*SimulatorSelection.ispeclist.simulator_path: "unsigned char", "*%simulator_path%"
*SimulatorSelection.ispeclist.idoper: "TIPO_OP", "%idoper%"
*SimulatorSelection.funcdecl: swidget create_SimulatorSelection(TIPO_OP operaz)\

*SimulatorSelection.funcname: create_SimulatorSelection
*SimulatorSelection.funcdef: "swidget", "<create_SimulatorSelection>(%)"
*SimulatorSelection.argdecl: TIPO_OP operaz;
*SimulatorSelection.arglist: operaz
*SimulatorSelection.arglist.operaz: "TIPO_OP", "%operaz%"
*SimulatorSelection.icode: char inidir[STRLONG];\
XmString xstring;\
\
idoper = operaz;\
\
if( getenv("SKED_USER") != NULL)\
   sprintf(inidir,"%s",getenv("SKED_USER"));\
else\
   if( getwd(inidir) == NULL )\
      sprintf(inidir,"%s","./");\

*SimulatorSelection.fcode: switch(operaz)\
{\
    case OPENSIM:\
       simulatorselection_settitle(SimulatorSelection,"Open Simulator");\
    break;\
    case REMOVESIM:\
       simulatorselection_settitle(SimulatorSelection,"Remove Simulator");\
    break;\
    case CREASIM:\
       simulatorselection_settitle(SimulatorSelection,"Create Simulator");\
    break;\
}\
\
xstring = XmStringCreateSimple(inidir);\
set_something(SimulatorSelection,XmNdirectory,xstring);\
\
\
return(rtrn);\

*SimulatorSelection.auxdecl: void simulatorselection_settitle(swidget thiswid,char *title)\
{\
   Arg arg[2];\
   Cardinal narg;\
\
printf("Setto il titolo %s\n",title);\
   narg=0;\
   XtSetArg(arg[narg],XmNtitle,title);narg++;\
   XtSetValues(XtParent(thiswid),arg,narg);   \
}\
\
char *get_selection()\
{\
   char *simul;\
   simul = UxGetTextString(SimulatorSelection);  \
   return(simul);\
}\
\
Boolean simulator_isnew(char *simpath)\
{\
   extern Boolean sccsstate;\
   FILE *fp=NULL;\
   char filename[300]; \
   Boolean new=False;\
\
   switch( idoper )\
   {\
      case CREASIM:\
      case REMOVESIM:\
         /* verifico l'esistenza della directory */  \
         strcpy(filename,simpath);\
      break;\
      case OPENSIM:\
         /* verifico l'esistenza della directory */  \
         if( sccsstate == True )\
            strcpy(filename,simpath);\
         else\
         {  \
            /* verifico l'esistenza del file S01 */  \
            strcpy(filename,"");\
            sprintf(filename,"%s%s",simpath,"/S01");\
         }\
      break;\
   }\
\
\
/* verifico se si puo' accedere al file in lettura */\
\
   if( (fp = fopen(filename,"r")) != NULL)\
      new = False;\
   else\
      new = True;   \
\
   fclose(fp);\
   return(new);\
}\
\
void confermata_remove_simulator()\
{\
   extern Boolean remove_simultor();\
   char *path;\
   \
   printf("Ho ricevuto conferma della rimozione del simulatore %s\n",get_selection());\
\
   path = XtMalloc( strlen(get_selection()) );\
   strcpy(path,get_selection());       \
\
   remove_simulator(path);\
   XtFree(path);\
}\

*SimulatorSelection.name: SimulatorSelection
*SimulatorSelection.unitType: "pixels"
*SimulatorSelection.x: 467
*SimulatorSelection.y: 295
*SimulatorSelection.height: 372
*SimulatorSelection.dialogType: "dialog_question"
*SimulatorSelection.fileTypeMask: "file_directory"
*SimulatorSelection.fileListLabelString: "Simulator"
*SimulatorSelection.helpLabelString: "View S01"
*SimulatorSelection.okCallback: {\
extern swidget create_questionDialog();\
extern swidget create_messageDialog();\
extern Boolean open_simulator();\
extern Boolean sccsstate;\
extern SIMULATORE *simulatore;\
\
 \
swidget wid;\
\
/* verifico la selezione effettuata  */\
\
simulator_path = get_selection();\
new_simulator = simulator_isnew(simulator_path);\
\
\
printf("Selezione effettuata %s\n",simulator_path);\
printf("operazione richiesta %d\n",idoper);\
\
/* in base alla quale verifico le operazioni da svolgere */\
switch( idoper )\
{\
   case CREASIM:\
      if( !new_simulator )\
      {\
         printf("Operazione di creazione non concessa, il simulatore gia' esiste\n"); \
         wid = create_messageDialog(UxWidget,idoper);\
         UxPopupInterface(wid,no_grab);\
      }\
      else\
      {\
          /* open di un simulatore */\
          if( create_simulator(simulator_path) == True)\
          {\
             printf("Create del simulatore andata a buon fine\n");\
\
             /* open del simulatore creato */\
             if( open_simulator(simulator_path) == True)\
                printf("Open del simulatore andata a buon fine\n");\
             else\
                printf("Open del simulatore NON andata a buon fine\n");\
          }\
          else\
             printf("Create del simulatore NON andata a buon fine\n");\
\
           UxDestroyInterface(UxWidget);            \
         } \
   break;\
   case OPENSIM:\
      if( new_simulator )\
      {\
         wid = create_messageDialog(UxWidget,idoper);\
         UxPopupInterface(wid,no_grab);  \
      }\
      else\
      {\
\
/**** dal 27-7-95 la gestione SCCS viene fatta separatamente\
         if(sccsstate && exist_sccsdir(simulator_path) )\
         {\
            wid = create_SCCSGEST(idoper,simulator_path);\
            UxPopupInterface(wid,no_grab);\
         }\
         else\
***/\
         {\
             /* open di un simulatore */\
             if( open_simulator(simulator_path) == True)\
                printf("Open del simulatore andata a buon fine\n");\
             else\
                printf("Open del simulatore NON andata a buon fine\n");\
\
             UxDestroyInterface(UxWidget);            \
         } \
      }\
   break;\
   case REMOVESIM:\
      if( new_simulator )\
      {\
printf("Tento di rimuovere un simulatore che risulta nuovo\n");\
         wid = create_messageDialog(UxWidget,idoper);\
         UxPopupInterface(wid,no_grab);\
      }\
      else\
      {\
         printf("selezione =%s , simulatore->path=%s\n",simulator_path,simulatore->path);\
         if( strcmp(simulator_path,simulatore->path) )\
         {\
         wid = create_questionDialog(UxWidget,idoper);\
         UxPopupInterface(wid,no_grab);       \
         }\
         else\
         {\
         wid = create_messageDialog(UxWidget,idoper);\
         UxPopupInterface(wid,no_grab);\
         }\
      }\
   break;\
}\
\
\
\
}
*SimulatorSelection.selectionLabelString: "Simulator Selected"
*SimulatorSelection.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*SimulatorSelection.destroyCallback: {\
extern void ResetSimulatorActive();\
extern void filepane_setsensitive();\
\
ResetSimulatorActive();\
filepane_setsensitive();\
\
\
}
*SimulatorSelection.helpCallback: {\
swidget wid;\
char *pathfile,*filename;\
\
pathfile = get_selection();\
filename = XtMalloc(strlen(pathfile) + 5);\
\
strcpy(filename,pathfile);\
strcat(filename,"/S01");\
\
wid = create_ViewS01( filename );\
UxPopupInterface(wid,no_grab);\
}
*SimulatorSelection.width: 532

