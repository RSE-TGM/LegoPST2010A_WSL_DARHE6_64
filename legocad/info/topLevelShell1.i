! UIMX ascii 2.0 key: 9471                                                      

*topLevelShell1.class: topLevelShell
*topLevelShell1.parent: NO_PARENT
*topLevelShell1.static: true
*topLevelShell1.gbldecl: /*\
   modulo topLevelShell1.i\
   tipo \
   release 1.12\
   data 5/4/95\
   reserved @(#)topLevelShell1.i	1.12\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <sys/stat.h>\
#include <Xm/TextF.h>\
#include "linfo.h"\
\
extern int whatConfiguration;\
extern Boolean editabile;\
\
Arg arg[20];\
Cardinal narg;\
\

*topLevelShell1.ispecdecl: DESCRMODELLO descrmod;  /* descrizione modello (descr.dat) */ \
LTM          *ltm;      /* elenco moduli (crealtm.dat) */\
FORAUS       dforaus;   /* foraus.for */ \
\
int nrighedescr;\
int nmoduli;\
\
WidgetList LWidDescr;\
Cardinal nLWidDescr;\
Widget testo_descr;\

*topLevelShell1.ispeclist: descrmod, ltm, dforaus, nrighedescr, nmoduli, LWidDescr, nLWidDescr, testo_descr
*topLevelShell1.ispeclist.descrmod: "DESCRMODELLO", "%descrmod%"
*topLevelShell1.ispeclist.ltm: "LTM", "*%ltm%"
*topLevelShell1.ispeclist.dforaus: "FORAUS", "%dforaus%"
*topLevelShell1.ispeclist.nrighedescr: "int", "%nrighedescr%"
*topLevelShell1.ispeclist.nmoduli: "int", "%nmoduli%"
*topLevelShell1.ispeclist.LWidDescr: "WidgetList", "%LWidDescr%"
*topLevelShell1.ispeclist.nLWidDescr: "Cardinal", "%nLWidDescr%"
*topLevelShell1.ispeclist.testo_descr: "Widget", "%testo_descr%"
*topLevelShell1.funcdecl: swidget create_topLevelShell1()\

*topLevelShell1.funcname: create_topLevelShell1
*topLevelShell1.funcdef: "swidget", "<create_topLevelShell1>(%)"
*topLevelShell1.icode:
*topLevelShell1.fcode: if( editabile == False)\
   UxPutSensitive(FileSave,"false");\
\
\
{\
   if(whatConfiguration == 2)\
   {\
      DisplayDescriz(); \
      DisplayListaMod();\
      DisplayForaus();\
   }\
   else\
   {\
      XtResizeWidget(topLevelShell1,520,250,0);\
      DisplayDescriz(); \
      XtDestroyWidget(form2);\
      XtDestroyWidget(form3);\
   } \
   return(rtrn);\
}
*topLevelShell1.auxdecl: save_descr()\
{\
   FILE *fp;\
\
   AllocaDescrmodello(&descrmod,strlen( XmTextGetString(testo_descr) ) );\
   strcpy(descrmod.descrizione,XmTextGetString (testo_descr) );\
   printf("Salvo la descrizione \n\n %s\n\n",descrmod.descrizione);\
\
   if( (fp = fopen(FNAME_DESCR,"w")) != NULL)\
      fprintf(fp,"%s",descrmod.descrizione);\
\
   fclose(fp); \
\
}\
\
void DisplayDescriz()\
{\
   char *stringa=NULL;\
\
   if( FileExist( FNAME_DESCR) == False)\
      return;\
      \
   read_file(FNAME_DESCR,&stringa);\
   if( stringa != NULL) \
   {\
      AllocaDescrmodello(&descrmod,strlen(stringa));\
      strcpy( descrmod.descrizione, stringa );\
      XtFree( stringa );\
   }\
\
\
/* Creazione del Text widget  */\
   narg=0;\
\
/*\
   XtSetArg(arg[narg],XmNrightAttachment,XmATTACH_FORM); narg++;\
*/\
   XtSetArg(arg[narg],XmNtopAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNleftAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNbottomAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNbottomOffset,5); narg++;\
   XtSetArg(arg[narg],XmNrightOffset,5); narg++;\
   XtSetArg(arg[narg],XmNleftOffset,5); narg++;\
   XtSetArg(arg[narg],XmNtopOffset,50); narg++;\
   XtSetArg(arg[narg],XmNcolumns,70); narg++;\
   XtSetArg(arg[narg],XmNmaxLength,400); narg++;\
\
   XtSetArg(arg[narg],XmNrows,60); narg++;\
   if( editabile == True )\
   { \
      XtSetArg(arg[narg],XmNeditable,True); narg++;\
   }\
   else\
   { \
      XtSetArg(arg[narg],XmNeditable,False); narg++;\
   } \
\
   XtSetArg(arg[narg],XmNeditMode,XmMULTI_LINE_EDIT); narg++;\
   XtSetArg(arg[narg],XmNscrollingPolicy,XmAUTOMATIC); narg++;\
   XtSetArg(arg[narg],XmNvisualPolicy,XmCONSTANT); narg++;   \
\
   XtSetArg(arg[narg],XmNscrollHorizontal,False); narg++;       \
   XtSetArg(arg[narg],XmNwordWrap,True); narg++;      \
   XtSetArg(arg[narg],XmNmarginWidth,10); narg++;       \
\
   testo_descr=XmCreateScrolledText(form1,"testo_descr",arg,narg);\
   XtManageChild (testo_descr);\
\
   XmTextSetString (testo_descr,descrmod.descrizione);\
\
}\
\
void DisplayListaMod()\
{\
   extern char pathmodel[];\
   XmString item;\
   Widget Lista;\
   int i,position = 0;\
   char cstring[L_NOMEMODULO+L_DESCRMODELLO+2];\
\
   Lista = scrolledList2; \
\
\
   if( ReadCrealtm(pathmodel,&ltm,&nmoduli) == FALSE)\
      return;\
\
   for(i=0;i<nmoduli;i++)\
   {\
      if(ltm[i].rout_std)\
         sprintf(cstring,"%s *  %s",ltm[i].nome_modulo, ltm[i].descr_modulo);\
      else\
         sprintf(cstring,"%s    %s",ltm[i].nome_modulo, ltm[i].descr_modulo);\
      item = XmStringCreateSimple(cstring);\
      XmListAddItem(Lista,item,position);\
   }\
}\
\
\
void DisplayForaus()\
{\
   extern char pathmodel[];\
   char filename[256];\
   Widget testo;\
   char *stringa = NULL;\
\
   strcpy(filename,pathmodel);\
   strcat(filename,"/"); \
   strcat(filename,FNAME_FORAUS_USER);\
 \
   if( FileExist( filename ) == False)\
      return;\
\
/* legge il file foraus.for e \
   lo bufferrizza nella stringa \
   che viene allocata dalla routine \
   di lettura del file\
*/\
   \
\
   read_file(filename,&stringa);\
   AllocaForaus(&dforaus,strlen(stringa));\
\
   strcpy( dforaus.foraus, stringa );\
\
/* Dealloca la memoria utilizzata*/\
   XtFree(stringa); \
\
/* Creazione del Text widget  */\
   narg=0;\
\
   XtSetArg(arg[narg],XmNtopAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNrightAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNleftAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNbottomAttachment,XmATTACH_FORM); narg++;\
   XtSetArg(arg[narg],XmNbottomOffset,5); narg++;\
   XtSetArg(arg[narg],XmNrightOffset,5); narg++;\
   XtSetArg(arg[narg],XmNleftOffset,5); narg++;\
   XtSetArg(arg[narg],XmNtopOffset,50); narg++;\
   XtSetArg(arg[narg],XmNcolumns,110); narg++;\
\
   XtSetArg(arg[narg],XmNrows,60); narg++;\
   XtSetArg(arg[narg],XmNeditable,False); narg++;\
   XtSetArg(arg[narg],XmNeditMode,XmMULTI_LINE_EDIT); narg++;\
   XtSetArg(arg[narg],XmNscrollingPolicy,XmAUTOMATIC); narg++;\
   XtSetArg(arg[narg],XmNvisualPolicy,XmCONSTANT); narg++;\
\
   testo=XmCreateScrolledText(form3,"testo",arg,narg);\
   XtManageChild (testo);\
\
   XmTextSetString (testo,dforaus.foraus);\
\
}
*topLevelShell1.name: topLevelShell1
*topLevelShell1.x: 140
*topLevelShell1.y: 150
*topLevelShell1.width: 520
*topLevelShell1.height: 670
*topLevelShell1.title: "Model Info"

*mainWindow1.class: mainWindow
*mainWindow1.parent: topLevelShell1
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.unitType: "pixels"
*mainWindow1.x: 20
*mainWindow1.y: 20
*mainWindow1.width: 460
*mainWindow1.height: 620

*panedWindow1.class: panedWindow
*panedWindow1.parent: mainWindow1
*panedWindow1.static: true
*panedWindow1.name: panedWindow1

*form1.class: form
*form1.parent: panedWindow1
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.x: 3
*form1.y: 3
*form1.width: 507
*form1.height: 177
*form1.allowResize: "true"
*form1.skipAdjust: "true"
*form1.paneMinimum: 100

*label1.class: label
*label1.parent: form1
*label1.static: true
*label1.name: label1
*label1.x: 160
*label1.y: 0
*label1.width: 190
*label1.height: 30
*label1.labelString: "Description and Note"

*form2.class: form
*form2.parent: panedWindow1
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.x: 3
*form2.y: 248
*form2.width: 517
*form2.height: 192
*form2.allowResize: "true"
*form2.skipAdjust: "true"
*form2.paneMinimum: 200

*label2.class: label
*label2.parent: form2
*label2.static: true
*label2.name: label2
*label2.x: 170
*label2.y: 0
*label2.width: 170
*label2.height: 30
*label2.labelString: "Module List"

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form2
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 20
*scrolledWindow1.y: 40
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.topAttachment: "attach_form"
*scrolledWindow1.bottomOffset: 5
*scrolledWindow1.leftOffset: 5
*scrolledWindow1.rightOffset: 5
*scrolledWindow1.topOffset: 50

*scrolledList2.class: scrolledList
*scrolledList2.parent: scrolledWindow1
*scrolledList2.static: true
*scrolledList2.name: scrolledList2
*scrolledList2.width: 470
*scrolledList2.selectionPolicy: "single_select"
*scrolledList2.scrollBarDisplayPolicy: "as_needed"
*scrolledList2.traversalOn: "false"
*scrolledList2.listSizePolicy: "constant"

*form3.class: form
*form3.parent: panedWindow1
*form3.static: true
*form3.name: form3
*form3.resizePolicy: "resize_none"
*form3.x: 3
*form3.y: 520
*form3.width: 517
*form3.height: 116
*form3.paneMinimum: 200

*label3.class: label
*label3.parent: form3
*label3.static: true
*label3.name: label3
*label3.x: 170
*label3.y: 0
*label3.width: 180
*label3.height: 30
*label3.labelString: "foraus.for"

*menu1.class: rowColumn
*menu1.parent: mainWindow1
*menu1.static: true
*menu1.name: menu1
*menu1.rowColumnType: "menu_bar"
*menu1.menuAccelerator: "<KeyUp>F10"

*File.class: rowColumn
*File.parent: menu1
*File.static: true
*File.name: File
*File.rowColumnType: "menu_pulldown"

*FileSave.class: pushButton
*FileSave.parent: File
*FileSave.static: true
*FileSave.name: FileSave
*FileSave.labelString: "Save"
*FileSave.activateCallback: {\
\
   printf("viene salvato il file descr.dat \n");\
/* se editabile == True */\
\
   if(editabile == True)\
      save_descr();\
}

*FileQuit.class: pushButton
*FileQuit.parent: File
*FileQuit.static: true
*FileQuit.name: FileQuit
*FileQuit.labelString: "Quit"
*FileQuit.activateCallback: exit(0);

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: menu1
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "File"

