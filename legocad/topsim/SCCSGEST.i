! UIMX ascii 2.0 key: 689                                                       

*SCCSGEST.class: topLevelShell
*SCCSGEST.parent: NO_PARENT
*SCCSGEST.static: true
*SCCSGEST.gbldecl: /*\
   modulo SCCSGEST.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)SCCSGEST.i	1.24\
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

*SCCSGEST.ispecdecl: Arg args[5];\
Cardinal nargs;\
char versione[20];
*SCCSGEST.ispeclist: args, nargs, versione
*SCCSGEST.ispeclist.args: "Arg", "%args%[5]"
*SCCSGEST.ispeclist.nargs: "Cardinal", "%nargs%"
*SCCSGEST.ispeclist.versione: "unsigned char", "%versione%[20]"
*SCCSGEST.funcdecl: swidget create_SCCSGEST(TIPO_OP tipop, char *simpath )\

*SCCSGEST.funcname: create_SCCSGEST
*SCCSGEST.funcdef: "swidget", "<create_SCCSGEST>(%)"
*SCCSGEST.argdecl: TIPO_OP tipop;\
unsigned char *simpath;
*SCCSGEST.arglist: tipop, simpath
*SCCSGEST.arglist.tipop: "TIPO_OP", "%tipop%"
*SCCSGEST.arglist.simpath: "unsigned char", "*%simpath%"
*SCCSGEST.icode: extern SIMULATORE *alloca_simulatore();\
extern SIMULATORE *simulatore; \
\
extern void set_working_directory();\
extern Boolean get_working_directory();\
char wdir[100];\
\
\
printf("simpath = [%s]\n",simpath);\
\
set_working_directory(simpath);\
\
\
if( get_working_directory(wdir) == FALSE)\
   return(NULL);\
\
printf("wdir = [%s]\n",wdir);\
\
\
printf("set dir %s\nactual directory for Simulator %s\n",simpath,wdir);\
\
 \
/* ricavo il file l.S01 che contiene \
   la storia delle revisioni del file S01 */\
\
system("sccs get -l S01");\
\

*SCCSGEST.fcode: if( tipop == SAVESIM )\
{\
  disabilita_getbutton();\
  riempi_lista();\
}\
else if( tipop == OPENSIM )\
{\
  disabilita_deltabutton();\
  riempi_lista();\
}\
\
return(rtrn);\

*SCCSGEST.auxdecl: int get_version_from_string(char *strin,char *strout)\
{\
  int i;\
  char *ini=NULL,*fin=NULL;\
  Boolean stop = False;\
\
/*\
   si suppone che la stringa di input abbia il formato\
   "  5.4 data time user"\
*/\
\
\
  for(i=0;i<strlen(strin);i++)\
     if( strin[i] == '*' )\
        strin[i] = ' ';   \
\
  for(i=0;i<strlen(strin);i++)\
  {\
     /* setto l'inizio dopo i blank iniziali */\
     if( strin[i] != ' ' && !stop )\
     {\
        ini = &(strin[i]);\
        printf("ini =%s\n",ini);\
        stop = True;\
     }\
       \
     /* setto la fine al primo blank successivo a inizio */  \
     if( ini != NULL && strin[i] == ' ')\
     {\
        fin = &(strin[i]);\
        *fin = 0;\
        printf("fin =%s\n",fin);\
        break;\
     }\
  }\
\
/* copio i caratteri individuati */\
  strncpy(strout,ini,(fin-ini)+1);\
\
}\
\
int exist_sccsdir(char *path)\
{\
   char sccsdir[100];\
\
   strcpy(sccsdir,path);\
   strcat(sccsdir,"/SCCS");\
   if( chdir(sccsdir) != 0 ) /* la directory non e' accessibile */\
      return(False);\
\
   return(True);\
}\
\
void get_vers_selected()\
{\
}\
\
\
void leggi_lS01(FILE *fp)\
{\
   char str[100],result[200],*appo;\
   int n;\
   XmString xstring;\
   char vers[100];\
   char comm[100];\
   int reiniz;          /* =1 se riga vuota  =0 se c'e qualcosa*/\
   int commento;        /* =0 riga di versione =1 riga di commento */  \
\
/* leggo il file l.S01 generato con il comando sccs get -l S01 \
   il quale e' strutturato cosi'\
      riga della versione del file\
      riga di commento (opzionale) questa riga puo' non esserci\
      riga (possono essere anche di piu') con 1 solo char \
*/ \
\
   reiniz = 0;\
   commento = 0;\
   n=0;\
   while( fgets(str,80,fp) != NULL)\
   {\
/* ho letto una riga con 1 solo char */\
      if( strlen(str) == 1)\
         reiniz = 1;\
      else \
         reiniz = 0;\
\
/* creo l'item */ \
      if( reiniz && commento)\
      {\
            appo = strchr(vers,'\n');\
            if( appo )\
               *appo = ' ';\
            appo = strchr(vers,'\t');\
            if( appo )\
              *appo = ' ';\
            appo = strchr(comm,'\n');\
            if( appo )\
               *appo = ' ';\
            appo = strchr(comm,'\t');\
            if( appo )\
               *appo = ' ';\
\
         sprintf(result,"%s  - %s",vers,comm);\
\
         xstring = XmStringCreateSimple(result);\
         XmListAddItem(ListVersion,xstring,1); \
         strcpy(result,"");\
\
         commento = 0;\
\
      }\
       \
/* se ho letto qualcosa */  \
      if( !reiniz )\
      {\
\
/* ho un commento se ho gia' letto la versione */\
         if( commento )\
            strcpy(comm,str);\
\
\
/* ho una versione o all'inizio della lettura del file o\
   se ho gia' costruito l'item cioe' ho letto una riga vuota\
   quindi la prossima riga sara' sicuramente una versione  \
*/\
         if( !commento ) \
         {  \
            strcpy(vers,str);\
            commento = 1;\
         }\
\
      }\
      else\
      {\
         strcpy(vers,"");\
         strcpy(comm,""); \
      }\
\
    }      \
}\
\
\
\
void riempi_lista()\
{\
   FILE *fp;\
  \
   if( (fp = fopen("l.S01","r")) != NULL)\
      leggi_lS01(fp);\
  \
   fclose(fp);\
}\
\
void abilita_getbutton()\
{\
   nargs=0;\
   XtSetArg(args[nargs],XmNsensitive,True);nargs++;\
   XtSetValues(getButton,args,nargs);   \
   XtSetValues(editButton,args,nargs); \
}\
\
void disabilita_getbutton()\
{\
   nargs=0;\
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;\
   XtSetValues(getButton,args,nargs);   \
   XtSetValues(editButton,args,nargs); \
}\
\
void abilita_deltabutton()\
{\
   nargs=0;\
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;\
   XtSetValues(deltaButton,args,nargs);   \
}\
\
void disabilita_deltabutton()\
{\
   nargs=0;\
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;\
   XtSetValues(deltaButton,args,nargs);   \
}\

*SCCSGEST.name: SCCSGEST
*SCCSGEST.x: 410
*SCCSGEST.y: 350
*SCCSGEST.width: 360
*SCCSGEST.height: 400

*form5.class: form
*form5.parent: SCCSGEST
*form5.static: true
*form5.name: form5
*form5.resizePolicy: "resize_none"
*form5.unitType: "pixels"
*form5.x: 100
*form5.y: 70
*form5.width: 160
*form5.height: 190

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.parent: form5
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.x: 20
*scrolledWindow5.y: 50
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0
*scrolledWindow5.bottomAttachment: "attach_form"
*scrolledWindow5.bottomOffset: 60
*scrolledWindow5.topAttachment: "attach_form"
*scrolledWindow5.topOffset: 40
*scrolledWindow5.rightAttachment: "attach_form"
*scrolledWindow5.rightOffset: 10
*scrolledWindow5.leftAttachment: "attach_form"
*scrolledWindow5.leftOffset: 10

*ListVersion.class: scrolledList
*ListVersion.parent: scrolledWindow5
*ListVersion.static: true
*ListVersion.name: ListVersion
*ListVersion.width: 320
*ListVersion.height: 260
*ListVersion.selectionPolicy: "single_select"
*ListVersion.singleSelectionCallback: {\
char cstring[STRLONG];\
XmString item;\
\
\
/* recupero l'item selezionato tramite gli arg della callback */\
\
item = XmStringCopy( ((XmListCallbackStruct *)UxCallbackArg)->item );\
strcpy(cstring,extract_string(item));\
\
printf("Selezione =%s\n",cstring);\
\
/* recupero dalla stringa dell'item la versione */\
get_version_from_string(cstring,versione);\
\
printf("versione=%s\n",versione);\
\
\
}

*getButton.class: pushButton
*getButton.parent: form5
*getButton.static: true
*getButton.name: getButton
*getButton.x: 20
*getButton.y: 340
*getButton.width: 50
*getButton.height: 30
*getButton.labelString: "Get"
*getButton.activateCallback: {\
extern void set_working_directory();\
extern Boolean open_simulator();\
extern swidget SimSelection;\
extern Boolean get_sccsS01();\
\
/*\
   e' necessario adesso recuperare in  read only (get) la versione\
   che l'utente ha selezionato sulla lista\
*/\
\
set_working_directory(simpath);\
\
printf("\n\n Attenzione! in questa versione viene estratto in \n ReadOnly la  versione di S01 %s\n",versione);\
\
get_sccsS01(versione);\
\
/* open di un simulatore */\
if( open_simulator(simpath) == True)\
   printf("Open del simulatore andata a buon fine\n");\
else\
   printf("Open del simulatore NON andata a buon fine\n");\
\
UxDestroyInterface(SimSelection);\
UxDestroyInterface(XtParent(UxWidget));                         \
\
}
*getButton.bottomAttachment: "attach_form"
*getButton.bottomOffset: 10
*getButton.topAttachment: "attach_widget"
*getButton.topOffset: 10
*getButton.topWidget: "scrolledWindow5"
*getButton.leftAttachment: "attach_form"
*getButton.leftOffset: 10

*editButton.class: pushButton
*editButton.parent: form5
*editButton.static: true
*editButton.name: editButton
*editButton.x: 90
*editButton.y: 340
*editButton.width: 50
*editButton.height: 30
*editButton.labelString: "Edit"
*editButton.activateCallback: {\
extern void set_working_directory();\
extern Boolean open_simulator();\
extern swidget SimSelection;\
extern Boolean edit_sccsS01();\
\
\
set_working_directory(simpath);\
\
printf("\n\n Attenzione! in questa versione viene estratto in \n WriteMode la ultima versione di S01\n");\
\
edit_sccsS01(versione);\
\
/* open di un simulatore */\
if( open_simulator(simpath) == True)\
   printf("Open del simulatore andata a buon fine\n");\
else\
   printf("Open del simulatore NON andata a buon fine\n");\
\
UxDestroyInterface(SimSelection);\
UxDestroyInterface(XtParent(UxWidget));                         \
\
}
*editButton.bottomAttachment: "attach_form"
*editButton.bottomOffset: 10
*editButton.topAttachment: "attach_widget"
*editButton.topOffset: 10
*editButton.topWidget: "scrolledWindow5"
*editButton.leftAttachment: "attach_form"
*editButton.leftOffset: 80

*deltaButton.class: pushButton
*deltaButton.parent: form5
*deltaButton.static: true
*deltaButton.name: deltaButton
*deltaButton.x: 170
*deltaButton.y: 340
*deltaButton.width: 50
*deltaButton.height: 30
*deltaButton.labelString: "Delta"
*deltaButton.activateCallback: {\
extern swidget SimSelection;\
extern Boolean delta_sccsS01();\
\
delta_sccsS01();\
\
UxDestroyInterface(XtParent(UxWidget));                         \
\
}
*deltaButton.bottomAttachment: "attach_form"
*deltaButton.bottomOffset: 10
*deltaButton.topAttachment: "attach_widget"
*deltaButton.topOffset: 10
*deltaButton.topWidget: "scrolledWindow5"
*deltaButton.leftAttachment: "attach_form"
*deltaButton.leftOffset: 150

*cancelButton.class: pushButton
*cancelButton.parent: form5
*cancelButton.static: true
*cancelButton.name: cancelButton
*cancelButton.x: 290
*cancelButton.y: 340
*cancelButton.width: 80
*cancelButton.height: 30
*cancelButton.labelString: "Cancel"
*cancelButton.activateCallback: {\
UxDestroyInterface(XtParent(UxWidget));\
}
*cancelButton.bottomAttachment: "attach_form"
*cancelButton.bottomOffset: 10
*cancelButton.topAttachment: "attach_widget"
*cancelButton.topOffset: 10
*cancelButton.topWidget: "scrolledWindow5"
*cancelButton.rightAttachment: "attach_form"
*cancelButton.rightOffset: 10
*cancelButton.leftAttachment: "attach_self"

*label4.class: label
*label4.parent: form5
*label4.static: true
*label4.name: label4
*label4.x: 20
*label4.y: 10
*label4.width: 320
*label4.height: 30
*label4.labelString: "SCCS Version of Sim1"
*label4.bottomAttachment: "attach_widget"
*label4.bottomOffset: 5
*label4.bottomWidget: "scrolledWindow5"
*label4.topAttachment: "attach_form"
*label4.topOffset: 5
*label4.leftAttachment: "attach_form"
*label4.leftOffset: 10
*label4.rightAttachment: "attach_form"
*label4.rightOffset: 10

