! UIMX ascii 2.5 key: 8548                                                      

*DefineContext.class: topLevelShell
*DefineContext.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo DefineContext2.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)DefineContext2.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <unistd.h>\
#include <sys/access.h>\
#include "config.h"\
\
int operaz;\
\
extern Arg args[];\
extern Cardinal lnargs;\
extern PAGEDIT_CONTEXT *pagedit;\
\
void display_context_data( );\
void aggiorna_ctx( );\
extern void TopMenuSetInsensitive( );\
extern void TopMenuSetSensitive( );
*DefineContext.ispecdecl: PAGEDIT_CONTEXT *ctxappo;\
unsigned char ContextName[150];
*DefineContext.ispeclist: ctxappo, ContextName
*DefineContext.ispeclist.ctxappo: "PAGEDIT_CONTEXT", "*%ctxappo%"
*DefineContext.ispeclist.ContextName: "unsigned char", "%ContextName%[150]"
*DefineContext.funcdecl: swidget creat_DefineContext(char *nomeCtx, int i_op )\

*DefineContext.funcname: creat_DefineContext
*DefineContext.funcdef: "swidget", "<creat_DefineContext>(%)"
*DefineContext.argdecl: unsigned char *nomeCtx;\
int i_op;
*DefineContext.arglist: nomeCtx, i_op
*DefineContext.arglist.nomeCtx: "unsigned char", "*%nomeCtx%"
*DefineContext.arglist.i_op: "int", "%i_op%"
*DefineContext.icode: operaz = i_op;\
strcpy(ContextName,nomeCtx);
*DefineContext.fcode: if(i_op == MOD_CONTEXT)\
{\
\
   ctxappo = pagedit; \
   display_context_data(ctxappo);\
\
}\
return(rtrn);\

*DefineContext.auxdecl: void display_context_data(PAGEDIT_CONTEXT *ctx)\
{\
   char *listaDisplay;\
   int i;\
\
/* creo le compound string dei dati e setto\
   le label della interfaccia con i valori */\
\
   \
   XmTextFieldSetString( ProjectDescription, ctx->descrizione );\
   XmTextFieldSetString( PagesPath,XlConvDirVms(ctx->pages));\
   XmTextFieldSetString( ObjectLibraryPath, XlConvDirVms(ctx->objectLibrary));\
   XmTextFieldSetString( AnimateIconLibraryPath,XlConvDirVms( ctx->animatedIconLibrary));\
   XmTextFieldSetString( SimulatorPath, XlConvDirVms(ctx->simulator));\
   XmTextFieldSetString( Hostname, ctx->hostname);\
   XmTextFieldSetString( HostnameS, ctx->hostnameS);\
\
   if( (listaDisplay = alloca_memoria(ctxappo->num_display*MAXCHARDISPLAY,sizeof(char)) ) == NULL)\
          return;\
\
   for(i=0;i<ctxappo->num_display;i++)\
   {\
       strcat(listaDisplay,ctx->elenco_display[i]);\
       strcat(listaDisplay," ");\
   }\
\
   XmTextFieldSetString( DisplayList, listaDisplay);\
  \
}\
\
void aggiorna_ctx(PAGEDIT_CONTEXT *ctx)\
{\
      char *listaDisplay=NULL,*save=NULL;\
      char appo[30];\
      int i,ndisplay = 0;\
\
     \
      strcpy(ctx->descrizione,XmTextFieldGetString(ProjectDescription));\
      strcpy(ctx->pages,XlUnconvDirVms(XmTextFieldGetString(PagesPath)));\
      strcpy(ctx->objectLibrary,XlUnconvDirVms(XmTextFieldGetString(ObjectLibraryPath)));\
      strcpy(ctx->animatedIconLibrary,XlUnconvDirVms(XmTextFieldGetString(AnimateIconLibraryPath)));\
      strcpy(ctx->simulator,XlUnconvDirVms(XmTextFieldGetString(SimulatorPath)));\
      strcpy(ctx->hostname,XmTextFieldGetString(Hostname));\
      strcpy(ctx->hostnameS,XmTextFieldGetString(HostnameS));\
      listaDisplay =  XmTextFieldGetString(DisplayList);\
  \
      save = listaDisplay;\
\
\
      listaDisplay[strlen(listaDisplay)+1] = '\0';\
\
      while( (sscanf(listaDisplay,"%s",appo)) > 0)\
      {\
         printf("listaDisplay = %s\n",listaDisplay);\
         printf("letto appo=%s\n",appo);\
\
\
         if(ndisplay == 0)\
         {\
            if((ctx->elenco_display = alloca_memoria(1,sizeof(char *))) == NULL)\
               return;\
         }\
         else\
            ctx->elenco_display = realloc(ctx->elenco_display,(ndisplay+1)*sizeof(char *));\
\
         if( (ctx->elenco_display[ndisplay] = alloca_memoria(strlen(appo)+2,sizeof(char))) == NULL)\
            return;\
\
         strcpy(ctx->elenco_display[ndisplay],appo);\
\
         listaDisplay += strlen(appo)+1;\
\
         while( *listaDisplay == ' ')\
            listaDisplay++;\
\
\
         ndisplay++;\
      }\
      ctx->num_display = ndisplay;\
}\

*DefineContext.static: true
*DefineContext.name: DefineContext
*DefineContext.parent: NO_PARENT
*DefineContext.x: 548
*DefineContext.y: 122
*DefineContext.width: 600
*DefineContext.height: 550

*form7.class: form
*form7.static: true
*form7.name: form7
*form7.parent: DefineContext
*form7.resizePolicy: "resize_none"
*form7.unitType: "pixels"
*form7.x: 100
*form7.y: 150
*form7.width: 560
*form7.height: 470
*form7.mapCallback: {\
\
}

*PagesLabel.class: label
*PagesLabel.static: true
*PagesLabel.name: PagesLabel
*PagesLabel.parent: form7
*PagesLabel.x: 20
*PagesLabel.y: 110
*PagesLabel.width: 130
*PagesLabel.height: 30
*PagesLabel.labelString: "Pages"
*PagesLabel.alignment: "alignment_beginning"

*PagesPath.class: textField
*PagesPath.static: true
*PagesPath.name: PagesPath
*PagesPath.parent: form7
*PagesPath.x: 210
*PagesPath.y: 110
*PagesPath.width: 340
*PagesPath.height: 30
*PagesPath.marginHeight: 1
*PagesPath.marginWidth: 2

*ObjectLibraryLabel.class: label
*ObjectLibraryLabel.static: true
*ObjectLibraryLabel.name: ObjectLibraryLabel
*ObjectLibraryLabel.parent: form7
*ObjectLibraryLabel.x: 20
*ObjectLibraryLabel.y: 150
*ObjectLibraryLabel.width: 170
*ObjectLibraryLabel.height: 30
*ObjectLibraryLabel.labelString: "Object Library"
*ObjectLibraryLabel.alignment: "alignment_beginning"

*ObjectLibraryPath.class: textField
*ObjectLibraryPath.static: true
*ObjectLibraryPath.name: ObjectLibraryPath
*ObjectLibraryPath.parent: form7
*ObjectLibraryPath.x: 210
*ObjectLibraryPath.y: 150
*ObjectLibraryPath.width: 340
*ObjectLibraryPath.height: 30
*ObjectLibraryPath.marginHeight: 1
*ObjectLibraryPath.marginWidth: 2

*AnimateIconLibraryLabel.class: label
*AnimateIconLibraryLabel.static: true
*AnimateIconLibraryLabel.name: AnimateIconLibraryLabel
*AnimateIconLibraryLabel.parent: form7
*AnimateIconLibraryLabel.x: 20
*AnimateIconLibraryLabel.y: 200
*AnimateIconLibraryLabel.width: 130
*AnimateIconLibraryLabel.height: 30
*AnimateIconLibraryLabel.labelString: "Animated Icon Library"
*AnimateIconLibraryLabel.alignment: "alignment_beginning"

*AnimateIconLibraryPath.class: textField
*AnimateIconLibraryPath.static: true
*AnimateIconLibraryPath.name: AnimateIconLibraryPath
*AnimateIconLibraryPath.parent: form7
*AnimateIconLibraryPath.x: 210
*AnimateIconLibraryPath.y: 200
*AnimateIconLibraryPath.width: 340
*AnimateIconLibraryPath.height: 30
*AnimateIconLibraryPath.marginHeight: 1
*AnimateIconLibraryPath.marginWidth: 2

*SimulatorLabel.class: label
*SimulatorLabel.static: true
*SimulatorLabel.name: SimulatorLabel
*SimulatorLabel.parent: form7
*SimulatorLabel.x: 20
*SimulatorLabel.y: 250
*SimulatorLabel.width: 130
*SimulatorLabel.height: 30
*SimulatorLabel.labelString: "Simulator"
*SimulatorLabel.alignment: "alignment_beginning"

*SimulatorPath.class: textField
*SimulatorPath.static: true
*SimulatorPath.name: SimulatorPath
*SimulatorPath.parent: form7
*SimulatorPath.x: 210
*SimulatorPath.y: 250
*SimulatorPath.width: 340
*SimulatorPath.height: 30
*SimulatorPath.marginHeight: 1
*SimulatorPath.marginWidth: 2

*ConfirmButton.class: pushButton
*ConfirmButton.static: true
*ConfirmButton.name: ConfirmButton
*ConfirmButton.parent: form7
*ConfirmButton.x: 30
*ConfirmButton.y: 480
*ConfirmButton.width: 70
*ConfirmButton.height: 30
*ConfirmButton.labelString: "Ok"
*ConfirmButton.activateCallback: {\
        {\
        extern void richiedi_change_database();\
        extern int setPageditEnv();\
        extern int display_resources();\
        extern int new_save_context();\
        extern swidget ContextSelection;\
        extern PAGEDIT_CONTEXT *pagedit;\
        extern int display_resources();\
        PAGEDIT_CONTEXT pagappo;\
        char *listaDisplay,appo[30];\
        int num_display = 0;\
        FILE *fp;\
        char mesg[200];\
\
        switch(operaz)\
        {\
           case LOAD_CONTEXT:\
           break;\
           case DEF_CONTEXT:\
              strcpy(pagappo.descrizione,XmTextFieldGetString(ProjectDescription));\
              strcpy(pagappo.pages,XlUnconvDirVms(XmTextFieldGetString(PagesPath)));\
              strcpy(pagappo.objectLibrary,XlUnconvDirVms(XmTextFieldGetString(ObjectLibraryPath)));\
              strcpy(pagappo.animatedIconLibrary,XlUnconvDirVms(XmTextFieldGetString(AnimateIconLibraryPath)));\
              strcpy(pagappo.simulator,XlUnconvDirVms(XmTextFieldGetString(SimulatorPath)));\
              strcpy(pagappo.hostname,XmTextFieldGetString(Hostname));\
              strcpy(pagappo.hostnameS,XmTextFieldGetString(HostnameS));\
              listaDisplay =  XmTextFieldGetString(DisplayList);\
\
\
              while( (sscanf(listaDisplay,"%s",appo)) > 0)\
              {\
                 num_display++;\
                 listaDisplay += strlen(appo);\
                 printf("display name %s num.%d\n",appo,num_display);\
              }\
\
              if( (fp=fopen(ContextName,"w")) == NULL)\
              {\
                 printf("errore fopen %s\n",ContextName);\
                 return;\
              }\
\
/* 21-10-96 Carlo\
\
test accesso direttori \
*/\
\
if( verifica_direttori_context(&pagappo) != True )\
   return;\
\
\
\
\
        /* salvo su file il context nuovo */\
              fprintf(fp,"%s","*objectLibraries:");\
              fprintf(fp,"%s",pagappo.objectLibrary);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*animatedIconLibraries:");\
              fprintf(fp,"%s",pagappo.animatedIconLibrary);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*numDisplay:");\
              fprintf(fp,"%d",num_display);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*displayList:");\
              fprintf(fp,"%s",listaDisplay);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*pag_num:");\
              fprintf(fp,"%d",0);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*page_list:");\
              fprintf(fp,"%s","");\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*iconlib_num:");\
              fprintf(fp,"%d",0);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*iconlib_list:");\
              fprintf(fp,"%s","");\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*iconlib_label:");\
              fprintf(fp,"%s","");\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*simulator:");\
              fprintf(fp,"%s",pagappo.simulator);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*pages:");\
              fprintf(fp,"%s",pagappo.pages);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*description:");\
              fprintf(fp,"%s",pagappo.descrizione);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*hostName:");\
              fprintf(fp,"%s",pagappo.hostname);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s","*hostNameS:");\
              fprintf(fp,"%s",pagappo.hostnameS);\
              fprintf(fp,"%s","\n");\
              fprintf(fp,"%s:","*nextTagPag: 00");\
              fprintf(fp,"%s","\n");\
              \
              fclose(fp);\
\
        /* effettuo la load del Context appena creato */\
              if(ContextLoad(ContextName,&pagedit))\
              {\
                 display_resources(pagedit);\
                 TopMenuSetSensitive();\
                 richiedi_change_database();\
              }\
              else\
              {\
                 sprintf(mesg,"Context File Not Found %s.\n",pagedit->fileContext);\
                 show_message(mesg);\
                 TopMenuSetInsensitive();\
              }\
           break;\
           case MOD_CONTEXT:\
           {\
/* provo a non farlo 22-10-96\
              char *appo,*start;\
\
              appo = start = ContextName;\
\
              while(*appo != '\0')\
              {\
                 if( *appo == '/')\
                 {\
                    appo++;\
                    start =  appo;\
                 }\
                 else\
                    appo++;\
              }\
\
             strcpy(ctxappo->fileContext,start);\
*/\
             aggiorna_ctx(ctxappo);\
\
/* 21-10-96 Carlo \
    verifico l'accessibilita dei direttori\
*/\
if( verifica_direttori_context( ctxappo ) != True)\
   return;             \
\
\
        /* salvo il context modificato */\
             new_save_context(ctxappo);\
        /* ed effettuo la load del nuovo context */\
             if(ContextLoad(ContextName,&pagedit))\
             {\
                display_resources(pagedit);\
                TopMenuSetSensitive();\
                richiedi_change_database();\
             }\
           }\
           break;\
           }\
\
           UxDestroyInterface(DefineContext);\
        }\
        \
\
}

*NoConfirmButton.class: pushButton
*NoConfirmButton.static: true
*NoConfirmButton.name: NoConfirmButton
*NoConfirmButton.parent: form7
*NoConfirmButton.x: 120
*NoConfirmButton.y: 480
*NoConfirmButton.width: 70
*NoConfirmButton.height: 30
*NoConfirmButton.labelString: "Cancel"
*NoConfirmButton.activateCallback: {\
UxDestroyInterface(DefineContext);\
}

*DisplayLabel.class: label
*DisplayLabel.static: true
*DisplayLabel.name: DisplayLabel
*DisplayLabel.parent: form7
*DisplayLabel.x: 20
*DisplayLabel.y: 300
*DisplayLabel.width: 130
*DisplayLabel.height: 30
*DisplayLabel.labelString: "Display List"
*DisplayLabel.alignment: "alignment_beginning"

*ProjectDescriptionLabel.class: label
*ProjectDescriptionLabel.static: true
*ProjectDescriptionLabel.name: ProjectDescriptionLabel
*ProjectDescriptionLabel.parent: form7
*ProjectDescriptionLabel.x: 20
*ProjectDescriptionLabel.y: 70
*ProjectDescriptionLabel.width: 130
*ProjectDescriptionLabel.height: 30
*ProjectDescriptionLabel.labelString: "Description"
*ProjectDescriptionLabel.alignment: "alignment_beginning"

*ProjectDescription.class: textField
*ProjectDescription.static: true
*ProjectDescription.name: ProjectDescription
*ProjectDescription.parent: form7
*ProjectDescription.x: 210
*ProjectDescription.y: 70
*ProjectDescription.width: 340
*ProjectDescription.height: 30
*ProjectDescription.marginHeight: 1
*ProjectDescription.marginWidth: 2

*DisplayList.class: textField
*DisplayList.static: true
*DisplayList.name: DisplayList
*DisplayList.parent: form7
*DisplayList.x: 210
*DisplayList.y: 300
*DisplayList.width: 340
*DisplayList.height: 30
*DisplayList.marginHeight: 1
*DisplayList.marginWidth: 2

*DisplayLabel1.class: label
*DisplayLabel1.static: true
*DisplayLabel1.name: DisplayLabel1
*DisplayLabel1.parent: form7
*DisplayLabel1.x: 20
*DisplayLabel1.y: 350
*DisplayLabel1.width: 180
*DisplayLabel1.height: 30
*DisplayLabel1.labelString: "Simulator machine"
*DisplayLabel1.alignment: "alignment_beginning"

*Hostname.class: textField
*Hostname.static: true
*Hostname.name: Hostname
*Hostname.parent: form7
*Hostname.x: 210
*Hostname.y: 350
*Hostname.width: 340
*Hostname.height: 30
*Hostname.marginHeight: 1
*Hostname.marginWidth: 2

*HostnameS.class: textField
*HostnameS.static: true
*HostnameS.name: HostnameS
*HostnameS.parent: form7
*HostnameS.x: 210
*HostnameS.y: 400
*HostnameS.width: 340
*HostnameS.height: 30
*HostnameS.marginHeight: 1
*HostnameS.marginWidth: 2

*DisplayLabel2.class: label
*DisplayLabel2.static: true
*DisplayLabel2.name: DisplayLabel2
*DisplayLabel2.parent: form7
*DisplayLabel2.x: 20
*DisplayLabel2.y: 400
*DisplayLabel2.width: 170
*DisplayLabel2.height: 30
*DisplayLabel2.labelString: "Scada machine"
*DisplayLabel2.alignment: "alignment_beginning"

