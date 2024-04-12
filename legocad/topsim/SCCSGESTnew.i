! UIMX ascii 2.0 key: 6676                                                      

*SCCSGESTnew.class: topLevelShell
*SCCSGESTnew.parent: NO_PARENT
*SCCSGESTnew.static: true
*SCCSGESTnew.gbldecl: /*\
   modulo SCCSGESTnew.i\
   tipo \
   release 1.2\
   data 8/29/95\
   reserved @(#)SCCSGESTnew.i	1.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include "topsim.h"\
#include "lg1_topsim.h"\
\
extern SIMULATORE *simulatore; \
\
#define FILEPRS "prs.dat"     /* file di output sccs prs */\
\
#define COMMENTS   1    /* tipo riga commento */ \
#define MRS        2    /* tipo riga mrs */\
#define MAXLENCOMM 100  \
#define MAXLEN     50\
\
typedef struct {\
                  char ver[MAXLEN];\
                  char date[MAXLEN];\
                  char user[MAXLEN];\
                  char mrs[MAXLENCOMM];\
                  char comments[MAXLENCOMM];\
               } VERSIONI;
*SCCSGESTnew.ispecdecl: char version[20];\
\
\
char filname[120];\
\
\
VERSIONI *svers;\
int nver;\
\
\

*SCCSGESTnew.ispeclist: version, filname, svers, nver
*SCCSGESTnew.ispeclist.version: "unsigned char", "%version%[20]"
*SCCSGESTnew.ispeclist.filname: "unsigned char", "%filname%[120]"
*SCCSGESTnew.ispeclist.svers: "VERSIONI", "*%svers%"
*SCCSGESTnew.ispeclist.nver: "int", "%nver%"
*SCCSGESTnew.funcdecl: swidget create_SCCSGESTnew( char *path )\

*SCCSGESTnew.funcname: create_SCCSGESTnew
*SCCSGESTnew.funcdef: "swidget", "<create_SCCSGESTnew>(%)"
*SCCSGESTnew.argdecl: unsigned char *path;
*SCCSGESTnew.arglist: path
*SCCSGESTnew.arglist.path: "unsigned char", "*%path%"
*SCCSGESTnew.icode: char wdir[100];\
\
\
if( get_working_directory(wdir) == FALSE)\
   return(NULL);\
\
/*\
system("sccs get -l S01");\
*/\
\
nver=0;\
svers=NULL;\

*SCCSGESTnew.fcode: /*\
riempi_lista();\
*/\
crea_file_prs(path,"S01");\
read_file_prs();\
crea_item();\
\
setta_popup_menu(path);\
return(rtrn);\

*SCCSGESTnew.auxdecl: int crea_file_prs(char *pathf,char *file)\
{\
   char comando[255];\
\
   sprintf(comando,"sccs prs %s/%s > %s",pathf,file,FILEPRS);\
   system(comando);\
}\
\
/* questa routine legge il file generato dalla redirezione su file\
   del comando SCCS PRS\
   la KEYWORD D  definisce l'inizio di un set di righe relative alla versione xx\
   le KEYWORD MRs e COMMENTS  permettono di interpretare le righe ad esse seguenti\
                              come mrs o commento\
*/\
\
int read_file_prs()\
{\
   FILE *fp;\
   char stringa[251];\
   char key[251],spare[251],ver[20],date[20],user[20];\
   char *pnl;\
   int retval;\
   char mrs[251],comments[251];\
   int tipo;\
\
   if( (fp=fopen(FILEPRS,"r")) == NULL)\
      return(FALSE);\
\
   while( fgets(stringa,80,fp) != NULL )\
   {\
\
/* elimino l'eventuale new line sulla stringa */\
      pnl = strstr(stringa,"\n");\
      if( pnl != NULL)\
         *pnl = 0;\
\
/* interpreto le righe */\
      if( strlen(stringa) )\
      {\
\
/* tutto si basa sul riconoscimento delle KEYWORD */\
        sscanf(stringa,"%s",key);\
\
        /* inizia la descrizione di una versione */\
        if( !strcmp(key,"D") )\
        {\
           svers = realloc(svers,sizeof(VERSIONI ) * (nver+1) );\
           sscanf(stringa,"%s%s%s%s%s",spare,svers[nver].ver,svers[nver].date,spare,svers[nver].user);\
           nver++;\
        }\
        else if( !strcmp(key,"MRs:") )\
           tipo = MRS;\
        else if( !strcmp(key,"COMMENTS:") )\
           tipo = COMMENTS;\
        else\
        {\
           if( tipo == MRS)\
           {\
             strcpy(svers[nver].mrs,stringa);\
           }\
           else if( tipo == COMMENTS )\
           {\
              strncat(svers[nver].comments,stringa,MAXLENCOMM-strlen(svers[nver].comments) );\
           }\
           else\
             strcpy(filname,stringa);\
        }\
      }\
   }\
\
   fclose(fp);\
   return(TRUE);\
}\
\
\
/*\
   ogni item viene creato dalla concatenazione di\
   ver data user comment \
   devo creare nitem = nver\
*/\
crea_item()\
{\
   char result[MAXLENCOMM+(MAXLEN*3)];\
   int i;\
   XmString xstring;\
\
 \
   for(i=nver-1;i>=0;i--)\
   {\
      strcpy(result,"");\
      sprintf(result,"%s %s %s %s",svers[i].ver,svers[i].date,svers[i].user,svers[i].comments);\
      xstring = XmStringCreateSimple(result);\
      XmListAddItem(ListVersion1,xstring,1); \
   }\
}\
\
\
\
\
\
\
int get_version_from_cstring(char *strin,char *strout)\
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
\
int esiste_sccsdir(char *lpath) \
{\
   char sccsdir[100];\
\
   strcpy(sccsdir,lpath);\
   strcat(sccsdir,"/SCCS");\
   if( chdir(sccsdir) != 0 ) /* la directory non e' accessibile */\
      return(False);\
\
   chdir(lpath);\
   return(True);\
}\
\
#ifdef OLD_VERS\
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
*/\
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
         XmListAddItem(ListVersion1,xstring,1); \
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
#endif  /*OLD VERSIONE */\
\
\
int rsetta_edit_menu( char *pathq )\
{\
\
    extern int check_file_status();\
    char pathfile[256];\
    int stato;\
\
    sprintf(pathfile,"%s/S01",pathq);\
\
    stato = check_file_status(pathfile);   \
 \
    switch( stato )\
    {\
       case FALSE:\
          set_something(SCCSedit,XmNsensitive,True);\
          set_something(SCCSsave,XmNsensitive,False);\
          set_something(SCCSunedit,XmNsensitive,False);\
          set_something(SCCSinfo,XmNsensitive,True);\
       break;\
       case R_OK:\
          set_something(SCCSedit,XmNsensitive,True);\
          set_something(SCCSsave,XmNsensitive,False);\
          set_something(SCCSunedit,XmNsensitive,False);\
          set_something(SCCSinfo,XmNsensitive,True);\
       break;\
       case W_OK:\
          set_something(SCCSedit,XmNsensitive,False);\
          set_something(SCCSsave,XmNsensitive,True);\
          set_something(SCCSunedit,XmNsensitive,True);\
          set_something(SCCSinfo,XmNsensitive,True);\
       break; \
       case (W_OK+R_OK):\
          set_something(SCCSedit,XmNsensitive,False);\
          set_something(SCCSsave,XmNsensitive,True);\
          set_something(SCCSunedit,XmNsensitive,True);\
          set_something(SCCSinfo,XmNsensitive,True);\
       break; \
    } \
\
}\
\
int setta_popup_menu( char *pathf )\
{\
\
    char appodir[256];\
\
    sprintf(appodir,"%s/SCCS",pathf);\
\
    if( esiste_sccsdir(pathf) == True )\
    { \
      \
       set_something( SCCScreate,XmNsensitive,False );\
       set_something( SCCSedit,XmNsensitive,True );\
       set_something( SCCSsave,XmNsensitive,True );\
       set_something( SCCSunedit,XmNsensitive,True );\
       set_something( SCCSinfo,XmNsensitive,True );\
\
       rsetta_edit_menu(pathf);\
  \
    }\
    else\
    {\
       set_something( SCCScreate,XmNsensitive,True );\
       set_something( SCCSedit,XmNsensitive,False );\
       set_something( SCCSsave,XmNsensitive,False );\
       set_something( SCCSunedit,XmNsensitive,False );\
       set_something( SCCSinfo,XmNsensitive,False );\
    }\
}\
 
*SCCSGESTnew.name: SCCSGESTnew
*SCCSGESTnew.x: 410
*SCCSGESTnew.y: 360
*SCCSGESTnew.width: 400
*SCCSGESTnew.height: 450

*form3.class: form
*form3.parent: SCCSGESTnew
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.unitType: "pixels"
*form3.x: 170
*form3.y: 300
*form3.width: 70
*form3.height: 40

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.parent: form3
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.scrollingPolicy: "application_defined"
*scrolledWindow3.x: 20
*scrolledWindow3.y: 50
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.leftOffset: 20
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.rightOffset: 20
*scrolledWindow3.topAttachment: "attach_form"
*scrolledWindow3.topOffset: 50
*scrolledWindow3.bottomAttachment: "attach_form"
*scrolledWindow3.bottomOffset: 50

*ListVersion1.class: scrolledList
*ListVersion1.parent: scrolledWindow3
*ListVersion1.static: true
*ListVersion1.name: ListVersion1
*ListVersion1.width: 320
*ListVersion1.height: 260
*ListVersion1.selectionPolicy: "single_select"
*ListVersion1.singleSelectionCallback: {\
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
get_version_from_cstring(cstring,version);\
\
printf("versione=%s\n",version);\
\
\
}

*menu6.class: rowColumn
*menu6.parent: ListVersion1
*menu6.static: true
*menu6.name: menu6
*menu6.rowColumnType: "menu_popup"
*menu6.menuAccelerator: "<KeyUp>F4"

*SCCSmenuEdit.class: rowColumn
*SCCSmenuEdit.parent: menu6
*SCCSmenuEdit.static: true
*SCCSmenuEdit.name: SCCSmenuEdit
*SCCSmenuEdit.rowColumnType: "menu_pulldown"

*SCCSgetB.class: pushButton
*SCCSgetB.parent: SCCSmenuEdit
*SCCSgetB.static: true
*SCCSgetB.name: SCCSgetB
*SCCSgetB.labelString: "Get (Read Only)"
*SCCSgetB.activateCallback: {\
  extern Boolean get_sccsS01();\
  printf("sccs get -r%s S01",version); \
\
   get_sccsS01(version);\
}

*SCCSeditB.class: pushButton
*SCCSeditB.parent: SCCSmenuEdit
*SCCSeditB.static: true
*SCCSeditB.name: SCCSeditB
*SCCSeditB.labelString: "Edit (read/write)"
*SCCSeditB.activateCallback: {\
   extern Boolean edit_sccsS01();\
\
   printf("sccs edit -r%s S01\n",version);\
\
   edit_sccsS01(version);\
\
}

*SCCSmenuDelta.class: rowColumn
*SCCSmenuDelta.parent: menu6
*SCCSmenuDelta.static: true
*SCCSmenuDelta.name: SCCSmenuDelta
*SCCSmenuDelta.rowColumnType: "menu_pulldown"

*SCCSdelgetB.class: pushButton
*SCCSdelgetB.parent: SCCSmenuDelta
*SCCSdelgetB.static: true
*SCCSdelgetB.name: SCCSdelgetB
*SCCSdelgetB.labelString: "Delget (delta+get)"
*SCCSdelgetB.activateCallback: {\
   extern Boolean delta_sccsS01();\
   extern Boolean get_sccsS01();\
\
   delta_sccsS01();\
   get_sccsS01(version); \
}

*SCCSdeleditB.class: pushButton
*SCCSdeleditB.parent: SCCSmenuDelta
*SCCSdeleditB.static: true
*SCCSdeleditB.name: SCCSdeleditB
*SCCSdeleditB.labelString: "Deledit (delta+edit)"
*SCCSdeleditB.activateCallback: {\
   extern Boolean edit_sccsS01();\
   extern Boolean delta_sccsS01();\
\
   delta_sccsS01();\
   edit_sccsS01(version);\
}

*menu6_p1_title.class: label
*menu6_p1_title.parent: menu6
*menu6_p1_title.static: true
*menu6_p1_title.name: menu6_p1_title
*menu6_p1_title.labelString: "SCCS"

*SCCSseparator.class: separatorGadget
*SCCSseparator.parent: menu6
*SCCSseparator.static: true
*SCCSseparator.name: SCCSseparator

*SCCScreate.class: pushButton
*SCCScreate.parent: menu6
*SCCScreate.static: true
*SCCScreate.name: SCCScreate
*SCCScreate.labelString: "Create"
*SCCScreate.activateCallback: {\
   int create_sccsS01();\
\
   printf("sccs create S01\n");\
   create_sccsS01();\
}

*SCCSedit.class: cascadeButton
*SCCSedit.parent: menu6
*SCCSedit.static: true
*SCCSedit.name: SCCSedit
*SCCSedit.labelString: "Edit"
*SCCSedit.subMenuId: "SCCSmenuEdit"

*SCCSsave.class: cascadeButtonGadget
*SCCSsave.parent: menu6
*SCCSsave.static: true
*SCCSsave.name: SCCSsave
*SCCSsave.labelString: "Save"
*SCCSsave.subMenuId: "SCCSmenuDelta"

*SCCSunedit.class: pushButton
*SCCSunedit.parent: menu6
*SCCSunedit.static: true
*SCCSunedit.name: SCCSunedit
*SCCSunedit.labelString: "Unedit"
*SCCSunedit.activateCallback: {\
   extern Boolean unedit_sccsS01();\
\
   unedit_sccsS01();\
\
}

*SCCSinfo.class: pushButton
*SCCSinfo.parent: menu6
*SCCSinfo.static: true
*SCCSinfo.name: SCCSinfo
*SCCSinfo.labelString: "Info"
*SCCSinfo.activateCallback: {\
   extern Boolean info_sccsS01();\
\
   info_sccsS01();\
}

*label2.class: label
*label2.parent: form3
*label2.static: true
*label2.name: label2
*label2.x: 20
*label2.y: 10
*label2.width: 320
*label2.height: 30
*label2.labelString: "SCCS Version of Sim1"
*label2.topAttachment: "attach_form"
*label2.topOffset: 10
*label2.rightAttachment: "attach_form"
*label2.rightOffset: 20
*label2.leftAttachment: "attach_form"
*label2.leftOffset: 20
*label2.bottomAttachment: "attach_widget"
*label2.bottomWidget: "scrolledWindow3"
*label2.bottomOffset: 5

*cancelButton1.class: pushButton
*cancelButton1.parent: form3
*cancelButton1.static: true
*cancelButton1.name: cancelButton1
*cancelButton1.x: 20
*cancelButton1.y: 370
*cancelButton1.width: 80
*cancelButton1.height: 30
*cancelButton1.labelString: "Ok"
*cancelButton1.activateCallback: {\
UxDestroyInterface(XtParent(UxWidget));\
}
*cancelButton1.topAttachment: "attach_widget"
*cancelButton1.topOffset: 10
*cancelButton1.topWidget: "scrolledWindow3"
*cancelButton1.bottomAttachment: "attach_form"
*cancelButton1.bottomOffset: 10
*cancelButton1.leftAttachment: "attach_form"
*cancelButton1.leftOffset: 20
*cancelButton1.rightAttachment: "attach_form"
*cancelButton1.rightOffset: 20

