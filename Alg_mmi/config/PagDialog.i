! UIMX ascii 2.5 key: 5832                                                      

*PagDialog.class: topLevelShell
*PagDialog.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo PagDialog.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)PagDialog.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <stdlib.h>\
#include "config.h"\
#ifndef DESIGN_TIME\
#include "message.h"\
#endif\
#include "res_edit.h"\
\
#define MAXREGNAME 4\
extern swidget topLevelShell;\
extern Arg args[];\
extern Cardinal lnargs;\
\
/* */\
\
Boolean verifica_nome( );\
void riempi_campi( );\
void SetOptMenu( );\
\
extern char *tmpnam();\
extern void PagSetDefaultValue();\
extern Boolean pagina_load_file( );\
extern Boolean pagina_init( );\
extern Boolean pagina_getres( );\
extern int PagGetType( );\
extern int show_message();
*PagDialog.ispecdecl: int operazione;\
PAGINA *pagina;\
AN_OBJ *listaobj;\
char oldname[100];\
Widget ListaWid[2];\
int tipoPag;
*PagDialog.ispeclist: operazione, pagina, listaobj, oldname, ListaWid, tipoPag
*PagDialog.ispeclist.operazione: "int", "%operazione%"
*PagDialog.ispeclist.pagina: "PAGINA", "*%pagina%"
*PagDialog.ispeclist.listaobj: "AN_OBJ", "*%listaobj%"
*PagDialog.ispeclist.oldname: "unsigned char", "%oldname%[100]"
*PagDialog.ispeclist.ListaWid: "Widget", "%ListaWid%[2]"
*PagDialog.ispeclist.tipoPag: "int", "%tipoPag%"
*PagDialog.funcdecl: swidget create_PagDialog(char *pname,int oper)
*PagDialog.funcname: create_PagDialog
*PagDialog.funcdef: "swidget", "<create_PagDialog>(%)"
*PagDialog.argdecl: unsigned char *pname;\
int oper;
*PagDialog.arglist: pname, oper
*PagDialog.arglist.pname: "unsigned char", "*%pname%"
*PagDialog.arglist.oper: "int", "%oper%"
*PagDialog.icode: char appo[100],nomepag[100],*nome_tmp;\
char filepag[MAXLENFILENAME],filebkg[MAXLENFILENAME];\
XmString cstring;\
\
operazione = oper;\
\
if(pname != NULL)\
   strcpy(nomepag,pname);\
\
switch(oper)\
{\
   case CREATE_PAGE:\
      strcpy(nomepag,"PAGE");\
      strcpy(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
      strcpy(filebkg,nomepag);\
      strcat(filebkg,BKG_EXT);\
   break;\
   case CREATE_REGOLATION:\
      strcpy(nomepag,"REGO");\
      strcpy(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
      strcpy(filebkg,nomepag);\
      strcat(filebkg,BKG_EXT);\
   break;\
   case CREATE_LIBRARY:\
      strcpy(nomepag,"LIB");\
      strcpy(filepag,nomepag);\
      strcat(filepag,LIB_EXT);\
   break;  \
   case COPY_PAGE:\
      strcpy(oldname,nomepag);\
      tmpnam(appo);                /* nome temporaneo */\
      nome_tmp = &appo[5];\
      strcpy(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
      strcpy(filebkg,nomepag);\
      strcat(filebkg,BKG_EXT);\
   break;\
}\
\

*PagDialog.fcode: switch(oper)\
{\
   case CREATE_PAGE:\
      set_something(PagName,XmNmaxLength,MAXCHAR_PAGNAME);\
      cstring = XmStringCreateSimple("Data Page Definition");\
      set_something(labelTitle1,XmNlabelString,cstring);\
      pagina_init(nomepag,&pagina,TIPO_PAGINA);\
      set_something(menu7,XmNsensitive,False); \
      set_something(label_in_use,XmNsensitive,False);	\
      pagina_load_file(pagina,TIPO_PAGINA);\
      PagSetDefaultValue(pagina);\
      riempi_campi(pagina);\
      XmStringFree(cstring);\
   break;\
   case CREATE_LIBRARY:\
      set_something(PagName,XmNmaxLength,MAXCHAR_PAGNAME);\
      cstring = XmStringCreateSimple("Data Library Definition");\
      set_something(labelTitle1,XmNlabelString,cstring);\
      set_something(labelTipo,XmNsensitive,False);\
      set_something(menu4,XmNsensitive,False);\
      XtVaSetValues(menu4_p1_b2,RES_CONVERT(XmNlabelString,"Library"),NULL);\
      set_something(menu7,XmNsensitive,False);\
      set_something(label_in_use,XmNsensitive,False);\
      set_something(pushButton1,XmNsensitive,False);\
      set_something(PagBackground,XmNsensitive,False);\
      set_something(RefreshFrequenzy,XmNsensitive,False);\
      set_something(labelRefreshFrequenzy,XmNsensitive,False);\
      set_something(Hierarchy,XmNsensitive,False);\
      set_something(HierarchyLabel,XmNsensitive,False);\
      pagina_init(nomepag,&pagina,TIPO_LIBRARY); \
      pagina_load_file(pagina,TIPO_LIBRARY);\
      PagSetDefaultValue(pagina);\
      riempi_campi(pagina);\
      XmStringFree(cstring);\
   break;\
   case CREATE_REGOLATION:\
      cstring = XmStringCreateSimple("Data Regolation Definition");\
      set_something(labelTitle1,XmNlabelString,cstring);\
      set_something(PagName,XmNmaxLength,MAXREGNAME);    /* nome len max di 4ch */\
      set_something(labelTipo,XmNsensitive,False);\
      set_something(menu4,XmNsensitive,False);\
      XtVaSetValues(menu4_p1_b2,RES_CONVERT(XmNlabelString,"Regolazione"),NULL);\
\
      pagina_init(nomepag,&pagina,TIPO_PAGINA);\
      pagina_load_file(pagina,TIPO_PAGINA);\
      PagSetDefaultValue(pagina);\
      riempi_campi(pagina);\
      XmStringFree(cstring);\
      \
   break; \
   case MODIFY_PAGE:\
      {\
\
          pagina_init(nomepag,&pagina,TIPO_PAGINA);\
          pagina_load_file(pagina,TIPO_PAGINA);\
          pagina_getres(pagina,&listaobj);\
          tipoPag = PagGetType(pagina);\
          switch(tipoPag)\
          {\
             case TYPE_REGOLAZIONE:\
                cstring = XmStringCreateSimple("Data Regolation Definition");\
                set_something(labelTitle1,XmNlabelString,cstring);\
                set_something(labelTipo,XmNsensitive,False);\
                set_something(menu4,XmNsensitive,False);\
                XtVaSetValues(menu4_p1_b2,RES_CONVERT(XmNlabelString,"Regolazione"),NULL);\
\
             break;\
             case TYPE_SINOTTICO:\
             case TYPE_STAZIONE:\
             case TYPE_TELEPERM:      \
		set_something(menu7,XmNsensitive,False);\
      		set_something(label_in_use,XmNsensitive,False);\
             break;\
\
          }\
\
          riempi_campi(pagina);\
          SetOptMenu(pagina);\
          XmTextFieldSetEditable(PagName,False);\
     } \
   break;\
   case MODIFY_LIBRARY:\
     cstring = XmStringCreateSimple("Data Library Definition");\
     set_something(labelTitle1,XmNlabelString,cstring);\
     set_something(labelTipo,XmNsensitive,False);\
     set_something(menu4,XmNsensitive,False);\
     XtVaSetValues(menu4_p1_b2,RES_CONVERT(XmNlabelString,"Library"),NULL);\
     set_something(menu7,XmNsensitive,False);\
     set_something(label_in_use,XmNsensitive,False);\
     set_something(pushButton1,XmNsensitive,False);\
     set_something(PagBackground,XmNsensitive,False);\
     set_something(RefreshFrequenzy,XmNsensitive,False);\
     set_something(labelRefreshFrequenzy,XmNsensitive,False);\
     set_something(Hierarchy,XmNsensitive,False);\
     set_something(HierarchyLabel,XmNsensitive,False);\
     pagina_init(nomepag,&pagina,TIPO_LIBRARY);\
     pagina_load_file(pagina,TIPO_LIBRARY);\
     pagina_getres(pagina,&listaobj);\
     riempi_campi(pagina);\
     SetOptMenu(pagina);\
     XmTextFieldSetEditable(PagName,False);\
     XmStringFree(cstring);\
   break;\
   case COPY_PAGE:\
      {\
\
          set_something(PagName,XmNmaxLength,MAXCHAR_PAGNAME);\
          pagina_init(nomepag,&pagina,TIPO_PAGINA);\
          pagina_load_file(pagina,TIPO_PAGINA);\
          pagina_getres(pagina,&listaobj);\
          tipoPag = PagGetType(pagina);\
          switch(tipoPag)\
          {\
             case TYPE_REGOLAZIONE:\
                nome_tmp[4] = 0;\
                set_something(PagName,XmNmaxLength,MAXREGNAME);    /* nome len max di 4ch */\
                cstring = XmStringCreateSimple("Data Regolation Definition");\
                set_something(labelTitle1,XmNlabelString,cstring);\
                set_something(labelTipo,XmNsensitive,False);\
                set_something(menu4,XmNsensitive,False);\
                XmStringFree(cstring);\
             break; \
             case TYPE_STAZIONE:\
             case TYPE_SINOTTICO:\
	     case TYPE_TELEPERM:\
                cstring = XmStringCreateSimple("Data Page Definition");\
                set_something(labelTitle1,XmNlabelString,cstring);     \
                set_something(menu7,XmNsensitive,False);\
                set_something(label_in_use,XmNsensitive,False);\
                XmStringFree(cstring);\
             break;\
          }\
          riempi_campi(pagina);\
          SetOptMenu(pagina);\
          XmTextFieldSetString(PagName,nome_tmp);\
    }\
   break;\
}\
\
return(rtrn);\

*PagDialog.auxdecl: /* verifica che nel nome della pagina non ci siano \
   caratteri non validi per il filename */\
 \
Boolean verifica_nome(char *nome)\
{\
   if( (strchr(nome,' ') != NULL) || (strchr(nome,'.') != NULL) )\
      return(False);\
   else\
      return(True);   \
}\
\
 void riempi_campi( PAGINA *pag )\
{   \
   char appo[500], msg[100];\
\
printf("Sono in riempipagina\n");\
   XmTextFieldSetString(PagName,pag->nomepag);\
   XmTextFieldSetString(PagDescription,pag->geom.descriz);\
\
   sprintf(appo,"%d",pag->geom.x); \
   XmTextFieldSetString(PagX,appo);\
\
   sprintf(appo,"%d",pag->geom.y); \
   XmTextFieldSetString(PagY,appo);\
\
   sprintf(appo,"%d",pag->geom.width); \
   XmTextFieldSetString(PagWidth,appo);\
\
   sprintf(appo,"%d",pag->geom.height); \
   XmTextFieldSetString(PagHeight,appo);\
\
   sprintf(appo,"%d",pag->geom.draw_width); \
   XmTextFieldSetString(DrawWidth,appo);\
\
   sprintf(appo,"%d",pag->geom.draw_height); \
   XmTextFieldSetString(DrawHeight,appo);\
\
   if( (operazione != CREATE_PAGE) && (operazione != CREATE_REGOLATION))\
      sprintf(appo,"%d",pag->refreshFreq); \
   else\
      sprintf(appo,"%d",10); \
\
   XmTextFieldSetString(RefreshFrequenzy,appo);\
\
   printf("pag->refreshFreq=%d\n",pag->refreshFreq);\
printf("Valore di gerarchia=%s-in riempi_pag\n",pag->gerarchia);\
   if(operazione == MODIFY_PAGE)\
   	hierarchy_format_new(appo,pag->gerarchia);\
   else\
	strcpy(appo,"[-1][-1][-1][-1][-1][-1]");\
   if(!strcmp(GERARCHIA_KO,appo))\
   {\
      sprintf(msg,"Hierarchy resource not correct! Page:%s\tHierarchy:%s\n",pag->nomepag,pag->gerarchia);\
      /* strcpy(msg,"Hierarchy specification not correct!\n"); */\
      show_message(msg);\
      XmTextFieldSetString(Hierarchy,"");\
   }\
   else {\
      XmTextFieldSetString(Hierarchy,appo);\
   }\
\
   XmTextFieldSetString(PagBackground,pag->geom.background);\
\
}\
\
void SetOptMenu(PAGINA *pag)\
{\
   Widget Pane,Bottone;   \
   WidgetList ListaButton;\
\
   /*  menu' tipo pagina */\
   get_something(menu4,XmNsubMenuId,(char*)&Pane);\
   get_something(Pane,XmNchildren,(char*)&ListaButton);\
   \
   if(!strcmp(pag->geom.tipo,TIPO_SINOTTICO))\
       Bottone = ListaButton[0];\
   else if(!strcmp(pag->geom.tipo,TIPO_STAZIONI))\
       Bottone = ListaButton[1];\
   else if(!strcmp(pag->geom.tipo,TIPO_TELEPERM))\
       Bottone = ListaButton[2];\
   else  /* mi metto al riparo da eventuali sporcate */\
       Bottone = ListaButton[0];\
\
   set_something(menu4,XmNmenuHistory,Bottone);\
\
  /*  menu' in use */\
   get_something(menu7,XmNsubMenuId,(char*)&Pane);\
   get_something(Pane,XmNchildren,(char*)&ListaButton);\
   \
   if(pag->in_use==SCHEME_IN_USE)\
       Bottone = ListaButton[0];\
   else if(pag->in_use==SCHEME_NOT_IN_USE)\
       Bottone = ListaButton[1];\
   else  /* mi metto al riparo da eventuali sporcate */\
       Bottone = ListaButton[0];\
\
   set_something(menu7,XmNmenuHistory,Bottone); \
\
}\
\
\
/* setto le dimensioni di default della pagina\
   di tipo Telepem\
   Le dimensioni sono impostate considerando uno screen 1280x1024\
   \
*/\
void TelepermSetDimension()\
{\
   char appo[500];\
/*\
   int screenW=WidthOfScreen( XtScreen(w) );\
   int screenH=HeightOfScreen( XtScreen(w) );\
*/\
   int screenW = 1280;\
   int screenH = 1024;\
\
   XmTextFieldSetString(PagX,"0");\
\
   XmTextFieldSetString(PagY,"0");\
\
   sprintf(appo,"%d", screenW ); \
   XmTextFieldSetString(PagWidth,appo);\
\
   sprintf(appo,"%d", screenH ); \
   XmTextFieldSetString(PagHeight,appo);\
\
   sprintf(appo,"%d", screenW ); \
   XmTextFieldSetString(DrawWidth,appo);\
\
   sprintf(appo,"%d", screenH - 96 ); \
   XmTextFieldSetString(DrawHeight,appo);\
\
}
*PagDialog.static: true
*PagDialog.name: PagDialog
*PagDialog.parent: NO_PARENT
*PagDialog.x: 68
*PagDialog.y: 185
*PagDialog.height: 800
*PagDialog.width: 610

*form2.class: form
*form2.static: true
*form2.name: form2
*form2.parent: PagDialog
*form2.resizePolicy: "resize_none"
*form2.unitType: "pixels"
*form2.x: 0
*form2.y: 100
*form2.width: 610
*form2.height: 700

*labelName.class: label
*labelName.static: true
*labelName.name: labelName
*labelName.parent: form2
*labelName.x: 10
*labelName.y: 50
*labelName.width: 90
*labelName.height: 30
*labelName.labelString: "Nome Pagina"
*labelName.alignment: "alignment_beginning"

*labelX.class: label
*labelX.static: true
*labelX.name: labelX
*labelX.parent: form2
*labelX.x: 10
*labelX.y: 280
*labelX.width: 20
*labelX.height: 30
*labelX.labelString: "X"
*labelX.alignment: "alignment_beginning"

*labelY.class: label
*labelY.static: true
*labelY.name: labelY
*labelY.parent: form2
*labelY.x: 10
*labelY.y: 325
*labelY.width: 20
*labelY.height: 30
*labelY.labelString: "Y"
*labelY.alignment: "alignment_beginning"

*labelDesc.class: label
*labelDesc.static: true
*labelDesc.name: labelDesc
*labelDesc.parent: form2
*labelDesc.x: 10
*labelDesc.y: 90
*labelDesc.width: 90
*labelDesc.height: 30
*labelDesc.labelString: "Description"
*labelDesc.alignment: "alignment_beginning"

*PagDescription.class: textField
*PagDescription.static: true
*PagDescription.name: PagDescription
*PagDescription.parent: form2
*PagDescription.x: 120
*PagDescription.y: 85
*PagDescription.width: 400
*PagDescription.height: 35

*PagX.class: textField
*PagX.static: true
*PagX.name: PagX
*PagX.parent: form2
*PagX.x: 120
*PagX.y: 280
*PagX.width: 120
*PagX.height: 35
*PagX.text: ""

*PagY.class: textField
*PagY.static: true
*PagY.name: PagY
*PagY.parent: form2
*PagY.x: 120
*PagY.y: 320
*PagY.width: 120
*PagY.height: 35

*PagBackground.class: textField
*PagBackground.static: true
*PagBackground.name: PagBackground
*PagBackground.parent: form2
*PagBackground.x: 120
*PagBackground.y: 590
*PagBackground.width: 250
*PagBackground.height: 35

*labelTitle1.class: label
*labelTitle1.static: true
*labelTitle1.name: labelTitle1
*labelTitle1.parent: form2
*labelTitle1.x: 170
*labelTitle1.y: 10
*labelTitle1.width: 185
*labelTitle1.height: 30
*labelTitle1.labelString: "Data Page Definition"
*labelTitle1.alignment: "alignment_beginning"
*labelTitle1.fontList: "-adobe-helvetica-medium-r-normal--18-180-75-75-p-98-iso8859-1"

*OkButton.class: pushButton
*OkButton.static: true
*OkButton.name: OkButton
*OkButton.parent: form2
*OkButton.x: 20
*OkButton.y: 760
*OkButton.width: 75
*OkButton.height: 35
*OkButton.labelString: "Ok"
*OkButton.activateCallback: {\
#ifndef DESIGN_TIME\
extern XmString SetItemString();\
extern int TagPagSetNew();\
extern void PaginaSetTagPag();\
extern Arg args[];\
extern Cardinal lnargs;\
extern void add_item();\
extern char *extract_string();\
extern PAGEDIT_CONTEXT *pagedit;\
extern Boolean ContextModified;\
extern char *XlConvPathVms();\
extern Boolean XlCopy();\
\
char comando[200],message[500];\
XmString Cpagname,new_item;\
FILE *fp;\
char strRes[100],strVal[100];\
char nomepag[MAXCHAR_PAGNAME];  /* nome della pagina */\
char filepag[MAXLENFILENAME],file1[MAXLENFILENAME],filebkg[MAXLENFILENAME];  \
int i,tipo_pag;\
int WLimit,HLimit,LowLimit;\
Widget WgtOptMenu;\
char stringItem[200];\
PAGINA *pagappo;\
AN_OBJ *obj;\
int tipo_sorg;\
\
/* definisco i limiti sulle dimensioni della pagina in base allo screen */ \
WLimit = XDisplayWidth(UxDisplay,UxScreen)  - 10;\
HLimit = XDisplayHeight(UxDisplay,UxScreen) - 10;  \
LowLimit = MIN_WIDTH;\
\
/* recupero i dati presenti sulla maschera */\
\
strcpy(nomepag,XmTextFieldGetString(PagName));\
\
/* verifica il nome attribuito alla pagina */\
if( verifica_nome(nomepag) == False)\
{\
   SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Invalid Page Name",\
          NULL,False,NULL,False,NULL);\
   return;\
}\
\
\
switch(operazione)\
{\
   case CREATE_PAGE:\
      if( XlGetenv(ENVPAG) == NULL)\
         return;\
      strcpy(filepag,getenv(ENVPAG));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag));\
\
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      pagina->refreshFreq = atoi(XmTextFieldGetString(RefreshFrequenzy));\
/*\
by fabio\
*/\
      format_hierarchy_new(pagina->gerarchia,XmTextFieldGetString(Hierarchy));\
      if( strcmp(GERARCHIA_KO,pagina->gerarchia)==0 )\
            {\
             SetMsg(topLevelShell,NULL,INFMSG,\
                   "ConfigInfo","Hierarchy specification not correct!",\
                    NULL,False,NULL,False,NULL);\
             return;\
              }\
\
\
printf("Pagina gerarc=%s\n",pagina->gerarchia);\
      get_something(menu4,XmNmenuHistory,(char*)&WgtOptMenu);\
      if(WgtOptMenu == menu4_p1_b1)\
         strcpy(pagina->geom.tipo,TIPO_STAZIONI);   \
      else if(WgtOptMenu == menu4_p1_b2)\
         strcpy(pagina->geom.tipo,TIPO_SINOTTICO);\
      else if(WgtOptMenu == menu4_p1_b3)\
         strcpy(pagina->geom.tipo,TIPO_TELEPERM);\
\
	\
      pagina->in_use=SCHEME_NOT_IN_USE;   \
      pagina->snap_pag=DEF_SNAP;\
      \
      if( pagina->refreshFreq < 1)\
      {\
          SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Refresh Frequenzy Values Not Acceptable",NULL,False,NULL,False,NULL);\
          return;\
      }\
\
      if( (fp = fopen(filepag,"r")) != NULL)\
      {\
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Proposed Page Already Exist",NULL,False,NULL,False,NULL);\
         fclose(fp);\
         return;\
      }\
      else\
      {\
         XlCopy(FILEPAGINADEFAULT,filepag); \
         fp = fopen(filepag,"a");\
         strcpy(pagina->nomepag,nomepag);\
         strcpy(pagina->filepag,filepag);\
         pag_wgeometry(fp,pagina);\
      }\
/* aggiorno la struttura del CONTEXT: 'page_num', 'page_list' e 'res_page' */ \
      if(pagedit->pag_num > 0)\
      {\
	 printf("OkButton: prima delle realloc per la CREATE_PAGE!!!\n");\
         pagedit->page_list = realloc(pagedit->page_list,sizeof(char *)*(pagedit->pag_num+1));\
	 pagedit->res_page = realloc(pagedit->res_page, sizeof(INFO_PAGE *)*(pagedit->pag_num+1));\
\
         if(( pagedit->page_list == NULL ) || (pagedit->res_page == NULL))\
            return;\
      }\
      else\
         if(((pagedit->page_list = alloca_memoria(1,sizeof(char *))) == NULL) ||\
		((pagedit->res_page = (INFO_PAGE **)alloca_memoria(1, sizeof(INFO_PAGE *))) == NULL))\
            return;\
      printf("OkButton: prima di allocare la struttura per la nuova pagina!!!\n");\
      if(((pagedit->page_list[pagedit->pag_num] = alloca_memoria(strlen(nomepag)+1,sizeof(char))) == NULL) ||\
	  ((pagedit->res_page[pagedit->pag_num] = (INFO_PAGE *)alloca_memoria(1,sizeof(INFO_PAGE))) == NULL))\
         return;\
      strcpy(pagedit->page_list[pagedit->pag_num],nomepag);\
\
      printf("OkButton: Nomepag:%s Numpag:%d prima dei caricamenti delle nuove info!!!\n", \
		pagedit->page_list[pagedit->pag_num],pagedit->pag_num); \
      strcpy(pagedit->res_page[pagedit->pag_num]->descr_page, pagina->geom.descriz);\
      strcpy(pagedit->res_page[pagedit->pag_num]->type_page, pagina->geom.tipo);\
      pagedit->res_page[pagedit->pag_num]->refresh_freq = pagina->refreshFreq;\
      strcpy(pagedit->res_page[pagedit->pag_num]->hier, pagina->gerarchia);\
      pagedit->res_page[pagedit->pag_num]->in_use = pagina->in_use;\
      fclose(fp);\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
      strcpy(pagina->filebkg,nomepag);\
      strcpy(pagina->filebkg,BKG_EXT);\
/*      TagPagSetNew(pagedit,TYPE_STAZIONE); */\
/* il Set delle TagPag lo lascio per evitare sporcamenti */ \
      PaginaSetTagPag(pagedit,pagina);\
\
      strcpy(pagedit->res_page[pagedit->pag_num]->tagPag,pagina->tagPag);\
\
      pagedit->pag_num++;\
 \
/* aggiungo l'item nella lista delle pagine*/\
      SetItemString(&Cpagname,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,pagina->in_use,pagina->tagPag);\
      add_item(Cpagname,0);\
/* MAURIC */\
      pagina_free(pagina);\
      XmStringFree(Cpagname);\
   break; \
   case CREATE_REGOLATION:\
      if( XlGetenv(ENVPAG) == NULL)\
         return;\
      strcpy(filepag,XlGetenv(ENVPAG));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag)); \
\
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      pagina->refreshFreq = atoi(XmTextFieldGetString(RefreshFrequenzy));    \
      pagina->numTagReg = 0;\
      strcpy(pagina->nextTagRegol,"00");\
      strcpy(pagina->geom.tipo,TIPO_REGOLAZIONE);\
\
/*\
      CAPPE. Per le pagine di regolazione la risorsa 'gerarchia' viene posta uguale a '-1,-1,-1,-1,-1,-1'\
      (pagine fuori dalla gerarchia)????       \
      strcpy(pagina->gerarchia,"-1,-1,-1,-1,-1,-1");\
*/\
\
      get_something(menu7,XmNmenuHistory,(char*)&WgtOptMenu);\
      if(WgtOptMenu == In_use)\
	  pagina->in_use=SCHEME_IN_USE;\
      else if(WgtOptMenu == Not_in_use)\
             pagina->in_use=SCHEME_NOT_IN_USE; \
      pagina->snap_pag=DEF_REG_SNAP;\
      if( pagina->refreshFreq < 1)\
      {\
          SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Refresh Frequenzy Values Not Acceptable",NULL,False,NULL,False,NULL);\
          return;\
      }\
\
      if( (fp = fopen(filepag,"r")) != NULL)\
      {\
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Proposed Page Already Exist",NULL,False,NULL,False,NULL);\
         fclose(fp);\
         return;\
      }\
      else\
      {\
         XlCopy(FILEPAGINADEFAULT,filepag);\
         fp = fopen(filepag,"a");\
         strcpy(pagina->nomepag,nomepag);\
         strcpy(pagina->filepag,filepag);\
         pag_wgeometry(fp,pagina);\
      }\
/* aggiorno la struttura del CONTEXT */ \
      if(pagedit->pag_num > 0)\
      {\
         pagedit->page_list = realloc(pagedit->page_list,sizeof(char *)*(pagedit->pag_num+1));\
	 pagedit->res_page = realloc(pagedit->res_page, sizeof(INFO_PAGE *)*(pagedit->pag_num+1));\
         if(( pagedit->page_list == NULL ) || (pagedit->res_page == NULL))\
            return;\
      }\
      else\
         if(((pagedit->page_list = alloca_memoria(1,sizeof(char *))) == NULL) ||\
	    ((pagedit->res_page = (INFO_PAGE **)alloca_memoria(1, sizeof(INFO_PAGE *))) == NULL))\
            return;\
      if(((pagedit->page_list[pagedit->pag_num] = alloca_memoria(strlen(nomepag)+1,sizeof(char))) == NULL) ||\
         ((pagedit->res_page[pagedit->pag_num] = (INFO_PAGE *)alloca_memoria(1,sizeof(INFO_PAGE))) == NULL))\
         return;\
      strcpy(pagedit->page_list[pagedit->pag_num],nomepag);\
      TagPagSetNew(pagedit,TYPE_REGOLAZIONE);\
      PaginaSetTagPag(pagedit,pagina);\
\
      strcpy(pagedit->res_page[pagedit->pag_num]->descr_page, pagina->geom.descriz);\
      strcpy(pagedit->res_page[pagedit->pag_num]->type_page, pagina->geom.tipo);\
      pagedit->res_page[pagedit->pag_num]->refresh_freq = pagina->refreshFreq;\
      strcpy(pagedit->res_page[pagedit->pag_num]->hier, pagina->gerarchia);\
      pagedit->res_page[pagedit->pag_num]->in_use = pagina->in_use;\
      strcpy(pagedit->res_page[pagedit->pag_num]->tagPag,pagina->tagPag);\
      pagedit->pag_num++;\
\
      printf("Pagina->tagPag = %s\n",pagina->tagPag);\
      sprintf(strRes,"*%s:   %s\n",XlNtagPag,pagina->tagPag);\
      fprintf(fp,"%s",strRes);\
      fclose(fp);\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
      strcpy(pagina->filebkg,nomepag);\
      strcpy(pagina->filebkg,BKG_EXT);\
/* Aggiungo l'item nella lista delle pagine */\
      SetItemString(&Cpagname,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,pagina->in_use,pagina->tagPag);\
      add_item(Cpagname,0);\
/* MAURIC */\
      pagina_free(pagina);\
      XmStringFree(Cpagname);\
   break;\
   case CREATE_LIBRARY:\
      if( XlGetenv(ENVLIB) == NULL)\
         return;\
      strcpy(filepag,XlGetenv(ENVLIB));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,LIB_EXT);\
\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag));\
    \
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      strcpy(pagina->geom.tipo,TIPO_LIBRERIA);\
\
      pagina->snap_pag=DEF_REG_SNAP;\
      pagina->in_use=SCHEME_NOT_IN_USE;\
      if( (fp = fopen(filepag,"r")) != NULL)\
      {\
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Proposed Page Already Exist",NULL,False,NULL,False,NULL);\
         fclose(fp);\
         return;\
      }\
      else\
      {\
         XlCopy(FILEPAGINADEFAULT,filepag); \
         if( (fp = fopen(filepag,"a")) == NULL)\
	 {\
	     sprintf(message,"Error opening %s",filepag);\
	     SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo",message,NULL,False,NULL,False,NULL);\
	     return;\
	 }\
         strcpy(pagina->nomepag,nomepag);\
         strcpy(pagina->filepag,filepag);\
         pag_wgeometry(fp,pagina);\
         fclose(fp);\
/* aggiorno la struttura del CONTEXT */ \
      if(pagedit->iconlib_num > 0)\
      {\
         pagedit->iconlib_list = realloc(pagedit->iconlib_list,sizeof(char *)*(pagedit->iconlib_num+1));\
         pagedit->iconlib_label = realloc(pagedit->iconlib_label,sizeof(char *)*(pagedit->iconlib_num+1));\
\
         if( pagedit->iconlib_list == NULL )\
            return;\
      }\
      else\
      {  \
         if((pagedit->iconlib_list = alloca_memoria(1,sizeof(char *))) == NULL)\
            return;\
         if((pagedit->iconlib_label = alloca_memoria(1,sizeof(char *))) == NULL)\
            return;\
      }\
\
      if( (pagedit->iconlib_list[pagedit->iconlib_num] = alloca_memoria(strlen(nomepag)+1,sizeof(char))) == NULL)\
         return;\
      if( (pagedit->iconlib_label[pagedit->iconlib_num] = alloca_memoria(strlen(nomepag)+1,sizeof(char))) == NULL)\
         return;\
      strcpy(pagedit->iconlib_list[pagedit->iconlib_num],nomepag);\
      strcpy(pagedit->iconlib_label[pagedit->iconlib_num],nomepag);\
      pagedit->iconlib_num++;         \
      }\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
/* Aggiungo l'item nella lista delle pagine */\
      SetItemString(&Cpagname,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,pagina->in_use,pagina->tagPag);\
      add_library_item(Cpagname,0);\
/* MAURIC */\
      pagina_free(pagina);\
      XmStringFree(Cpagname);\
   break;\
   case MODIFY_PAGE:\
      if( XlGetenv(ENVPAG) == NULL)\
         return;\
      strcpy(filepag,XlGetenv(ENVPAG));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag));\
\
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      pagina->refreshFreq = atoi(XmTextFieldGetString(RefreshFrequenzy));\
\
/*\
by fabio\
*/\
\
      format_hierarchy_new(pagina->gerarchia,XmTextFieldGetString(Hierarchy));\
      if( strcmp(GERARCHIA_KO,pagina->gerarchia)==0 )\
              {\
                  SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Hierarchy specification not correct!",NULL,False,NULL,False,NULL);\
                  return;\
              }\
\
printf("Gerarchia modificata=%s\n",pagina->gerarchia);\
/* posso cambiare il tipopagina solo se non e' di regolazione */\
\
      if(tipoPag != TYPE_REGOLAZIONE)\
      {\
          get_something(menu4,XmNmenuHistory,(char*)&WgtOptMenu);\
          if(WgtOptMenu == menu4_p1_b1)\
             strcpy(pagina->geom.tipo,TIPO_STAZIONI);   \
          else if(WgtOptMenu == menu4_p1_b2)\
            strcpy(pagina->geom.tipo,TIPO_SINOTTICO);\
          else if(WgtOptMenu == menu4_p1_b3)\
            strcpy(pagina->geom.tipo,TIPO_TELEPERM);\
\
      }\
\
/* posso cambiare il pagina in_use solo se e' di regolazione */\
\
      if(tipoPag == TYPE_REGOLAZIONE)\
      {\
          get_something(menu7,XmNmenuHistory,(char*)&WgtOptMenu);\
          if(WgtOptMenu == In_use)\
	      pagina->in_use = SCHEME_IN_USE;\
            else if(WgtOptMenu == Not_in_use)\
		pagina->in_use = SCHEME_NOT_IN_USE;\
      }\
\
      if( pagina->refreshFreq < 1)\
      {\
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Refresh Frequenzy Values Not Acceptable",NULL,False,NULL,False,NULL);\
         return;\
      }\
 \
      XrmPutStringResource(&pagina->db,"*nomePag",nomepag);\
      XrmPutStringResource(&pagina->db,"*top_descrizione",pagina->geom.descriz);\
      sprintf(strVal,"%s",pagina->geom.tipo);\
      XrmPutStringResource(&pagina->db,"*top_tipo",strVal);\
      sprintf(strVal,"%d",pagina->geom.x);\
      XrmPutStringResource(&pagina->db,"*top_x",strVal);\
      sprintf(strVal,"%d",pagina->geom.y);\
      XrmPutStringResource(&pagina->db,"*top_y",strVal);\
      sprintf(strVal,"%d",pagina->geom.width);\
      XrmPutStringResource(&pagina->db,"*top_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.height);\
      XrmPutStringResource(&pagina->db,"*top_height",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_width);\
      XrmPutStringResource(&pagina->db,"*drawing_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_height);\
      XrmPutStringResource(&pagina->db,"*drawing_height",strVal);\
      XrmPutStringResource(&pagina->db,"*drawing_background",pagina->geom.background);\
      sprintf(strVal,"%d",pagina->in_use);\
      XrmPutStringResource(&pagina->db,"*schemeInUse",strVal);\
      if(operazione ==  MODIFY_PAGE)\
      {\
         sprintf(strVal,"%d",pagina->refreshFreq);\
         printf("pagina->refreshFreq = %d strVal =%s\n",pagina->refreshFreq,strVal);\
         XrmPutStringResource(&pagina->db,"*refresh_freq",strVal);\
         XrmPutStringResource(&pagina->db,"*gerarchia",pagina->gerarchia);\
      }\
      XrmPutFileDatabase(pagina->db,filepag);\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
\
      /* Aggiornamento del context */\
      for(i=0; i<pagedit->pag_num; i++)\
         if(!strcmp(pagedit->page_list[i],nomepag))\
            break;\
      printf("MODIFY_PAGE-agg context- Nomepag:%s  Indice:%d\n",pagedit->page_list[i],i);\
      strcpy(pagedit->res_page[i]->descr_page, pagina->geom.descriz);\
      strcpy(pagedit->res_page[i]->type_page, pagina->geom.tipo);\
      pagedit->res_page[i]->refresh_freq = pagina->refreshFreq;\
      strcpy(pagedit->res_page[i]->hier, pagina->gerarchia);\
      pagedit->res_page[i]->in_use = pagina->in_use;\
      strcpy(pagedit->res_page[i]->tagPag,pagina->tagPag);\
\
      /* Aggiungi l'item nella lista delle pagine */\
      SetItemString(&new_item,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,\
                    pagina->in_use,pagina->tagPag);\
      modify_item(new_item,i);\
/* MAURIC */\
      pagina_free(pagina);\
      libera_memoria(listaobj);\
      XmStringFree(new_item); \
   break;\
   case MODIFY_LIBRARY:\
      if( XlGetenv(ENVLIB) == NULL)\
         return;\
\
      strcpy(filepag,XlGetenv(ENVLIB));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,LIB_EXT);\
\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag));\
 \
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      XrmPutStringResource(&pagina->db,"*nomePag",nomepag);\
      XrmPutStringResource(&pagina->db,"*top_descrizione",pagina->geom.descriz);\
      sprintf(strVal,"%s",pagina->geom.tipo);\
      XrmPutStringResource(&pagina->db,"*top_tipo",strVal);\
      sprintf(strVal,"%d",pagina->geom.x);\
      XrmPutStringResource(&pagina->db,"*top_x",strVal);\
      sprintf(strVal,"%d",pagina->geom.y);\
      XrmPutStringResource(&pagina->db,"*top_y",strVal);\
      sprintf(strVal,"%d",pagina->geom.width);\
      XrmPutStringResource(&pagina->db,"*top_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.height);\
      XrmPutStringResource(&pagina->db,"*top_height",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_width);\
      XrmPutStringResource(&pagina->db,"*drawing_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_height);\
      XrmPutStringResource(&pagina->db,"*drawing_height",strVal);\
      XrmPutStringResource(&pagina->db,"*drawing_background",pagina->geom.background);\
      sprintf(strVal,"%d",pagina->in_use);\
      XrmPutStringResource(&pagina->db,"*schemeInUse",strVal);\
      XrmPutFileDatabase(pagina->db,filepag);\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
      /* Ricerca della posizione della pagina nella lista */ \
      for(i=0;i<pagedit->iconlib_num;i++)\
         if(!strcmp(nomepag,pagedit->iconlib_list[i]))\
            break;\
      /* Aggiungi l'item nella lista delle pagine */\
      SetItemString(&new_item,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,\
                    pagina->in_use,pagina->tagPag);\
      modify_library_item(new_item,i);\
/* MAURIC */\
      pagina_free(pagina);\
      libera_memoria(listaobj);\
      XmStringFree(new_item);\
   break;\
   case COPY_PAGE:\
      if( XlGetenv(ENVPAG) == NULL)\
         return;\
\
      strcpy(filepag,XlGetenv(ENVPAG));\
      strcat(filepag,"/");\
      strcat(filepag,nomepag);\
      strcat(filepag,PAG_EXT);\
\
/* convers. per VMS */\
      strcpy(filepag,XlConvPathVms(filepag));\
      strcpy(pagina->geom.descriz, XmTextFieldGetString(PagDescription));\
      pagina->geom.x =  atoi(XmTextFieldGetString(PagX));\
      pagina->geom.y =  atoi(XmTextFieldGetString(PagY));\
      pagina->geom.width = atoi(XmTextFieldGetString(PagWidth));\
      pagina->geom.height = atoi(XmTextFieldGetString(PagHeight));\
      pagina->geom.draw_width = atoi(XmTextFieldGetString(DrawWidth));\
      pagina->geom.draw_height = atoi(XmTextFieldGetString(DrawHeight));\
      strcpy(pagina->geom.background,XmTextFieldGetString(PagBackground));\
      pagina->refreshFreq = atoi(XmTextFieldGetString(RefreshFrequenzy));\
      format_hierarchy_new(pagina->gerarchia,XmTextFieldGetString(Hierarchy));\
\
      if( (fp = fopen(filepag,"r")) != NULL)\
      {\
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Proposed Page Already Exist",NULL,False,NULL,False,NULL);\
         return;\
      }\
      else\
      {\
         if( strcmp(GERARCHIA_KO,pagina->gerarchia)==0 )\
         {\
            SetMsg(topLevelShell,NULL,INFMSG,\
                   "ConfigInfo","Hierarchy specification not correct!",\
                    NULL,False,NULL,False,NULL);\
            return;\
         }\
\
         if( pagina->refreshFreq < 1)\
           {\
              SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo","Refresh Frequenzy Values Not Acceptable",NULL,False,NULL,False,NULL);\
              return;\
           }         \
         \
         if( pagina_init(oldname,&pagappo,TIPO_PAGINA) == True )\
         {\
            pagina_load_file(pagappo,TIPO_PAGINA);\
            pagina_getres(pagappo,&obj);\
            tipo_sorg = PagGetType(pagappo);\
         } \
\
/* copio il .pag */\
         strcpy(file1,XlGetenv(ENVPAG));\
         strcat(file1,"/");\
         strcat(file1,oldname);\
         strcat(file1,PAG_EXT);\
         strcpy(file1,XlConvPathVms(file1));\
         XlCopy(file1,filepag);\
\
/* copio il .bkg */\
         strcpy(file1,XlGetenv(ENVPAG));\
         strcat(file1,"/");\
         strcat(file1,oldname);\
         strcat(file1,BKG_EXT);\
         strcpy(file1,XlConvPathVms(file1));\
         strcpy(filebkg,XlGetenv(ENVPAG));\
         strcat(filebkg,"/");\
         strcat(filebkg,nomepag);\
         strcat(filebkg,BKG_EXT);\
         strcpy(filebkg,XlConvPathVms(filebkg));\
         XlCopy(file1,filebkg);\
\
      }\
\
      if(pagedit->pag_num > 0)\
      {\
         pagedit->page_list = realloc(pagedit->page_list,sizeof(char *)*(pagedit->pag_num+1));\
	 pagedit->res_page = realloc(pagedit->res_page, sizeof(INFO_PAGE *)*(pagedit->pag_num+1));\
         if(( pagedit->page_list == NULL ) || (pagedit->res_page == NULL))\
            return;\
      }\
      else\
         if(((pagedit->page_list = alloca_memoria(1,sizeof(char *))) == NULL) || \
	    ((pagedit->res_page = (INFO_PAGE **)alloca_memoria(1, sizeof(INFO_PAGE *))) == NULL))\
            return;\
\
      if(((pagedit->page_list[pagedit->pag_num] = alloca_memoria(strlen(nomepag)+1,sizeof(char))) == NULL) ||\
         ((pagedit->res_page[pagedit->pag_num] = (INFO_PAGE *)alloca_memoria(1,sizeof(INFO_PAGE))) == NULL))\
        return;\
\
      XrmPutStringResource(&pagina->db,"*nomePag",nomepag);\
      XrmPutStringResource(&pagina->db,"*top_descrizione",pagina->geom.descriz);\
      sprintf(strVal,"%s",pagina->geom.tipo);\
      XrmPutStringResource(&pagina->db,"*top_tipo",strVal);\
      sprintf(strVal,"%d",pagina->geom.x);\
      XrmPutStringResource(&pagina->db,"*top_x",strVal);\
      sprintf(strVal,"%d",pagina->geom.y);\
      XrmPutStringResource(&pagina->db,"*top_y",strVal);\
      sprintf(strVal,"%d",pagina->geom.width);\
      XrmPutStringResource(&pagina->db,"*top_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.height);\
      XrmPutStringResource(&pagina->db,"*top_height",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_width);\
      XrmPutStringResource(&pagina->db,"*drawing_width",strVal);\
      sprintf(strVal,"%d",pagina->geom.draw_height);\
      XrmPutStringResource(&pagina->db,"*drawing_height",strVal);\
      XrmPutStringResource(&pagina->db,"*drawing_background",pagina->geom.background);\
      sprintf(strVal,"%d",pagina->in_use);\
      XrmPutStringResource(&pagina->db,"*schemeInUse",strVal);\
\
\
      sprintf(strVal,"%d",pagina->refreshFreq);\
      XrmPutStringResource(&pagina->db,"*refresh_freq",strVal);\
/*\
by fabio\
*/\
      sprintf(strVal,"%d",pagina->snap_pag);\
      XrmPutStringResource(&pagina->db,"*snap_pag",strVal);\
      XrmPutStringResource(&pagina->db,"*gerarchia",pagina->gerarchia);\
      strcpy(pagina->nomepag,nomepag);\
      strcpy(pagina->filepag,filepag);\
\
/* se duplico una regolazione devo aggiornare la nuova PagTag */\
      if(tipo_sorg == TYPE_REGOLAZIONE)\
      { \
         PaginaSetTagPag(pagedit,pagina);\
         sprintf(strVal,"%s",pagina->tagPag);\
         XrmPutStringResource(&pagina->db,"*tagPag",strVal);\
         TagPagSetNew(pagedit,TYPE_REGOLAZIONE);\
      }\
\
      /* CAPPE. Aggiornamento del context */\
      strcpy(pagedit->page_list[pagedit->pag_num],nomepag);\
      strcpy(pagedit->res_page[pagedit->pag_num]->descr_page, pagina->geom.descriz);\
      strcpy(pagedit->res_page[pagedit->pag_num]->type_page, pagina->geom.tipo);\
      pagedit->res_page[pagedit->pag_num]->refresh_freq = pagina->refreshFreq;\
      strcpy(pagedit->res_page[pagedit->pag_num]->hier, pagina->gerarchia);\
      pagedit->res_page[pagedit->pag_num]->in_use = pagina->in_use;\
      strcpy(pagedit->res_page[pagedit->pag_num]->tagPag,pagina->tagPag);\
      pagedit->pag_num++;\
\
\
      XrmPutFileDatabase(pagina->db,XlConvPathVms(filepag));\
\
      SetItemString(&Cpagname,pagina->nomepag,pagina->geom.tipo,pagina->geom.descriz,pagina->in_use,pagina->tagPag);\
      add_item(Cpagname,0);\
      if(tipo_sorg == TYPE_REGOLAZIONE)\
                        SettaTagInPag(nomepag,NULL);\
/* MAURIC */\
      libera_memoria(listaobj);\
      libera_memoria(obj);\
      pagina_free(pagappo);\
      pagina_free(pagina);\
      XmStringFree(Cpagname);\
   break;\
}\
\
\
/* aggiungo il salvataggio del file context \
by Carlo\
*/\
if( new_save_context( pagedit ) != True )\
{\
    SetMsg(topLevelShell,NULL,INFMSG,\
               "ConfigInfo","Save of Context failed.",\
               NULL,False,NULL,False,NULL);\
    ContextModified = True;\
}\
\
XtDestroyWidget(PagDialog);\
\
#endif\
}

*CancelButton.class: pushButton
*CancelButton.static: true
*CancelButton.name: CancelButton
*CancelButton.parent: form2
*CancelButton.x: 120
*CancelButton.y: 760
*CancelButton.width: 75
*CancelButton.height: 35
*CancelButton.labelString: "Cancel"
*CancelButton.activateCallback: {\
/* MAURIC */\
pagina_free(pagina);\
XtDestroyWidget(PagDialog);\
}

*labelTitle2.class: label
*labelTitle2.static: true
*labelTitle2.name: labelTitle2
*labelTitle2.parent: form2
*labelTitle2.x: 20
*labelTitle2.y: 250
*labelTitle2.width: 175
*labelTitle2.height: 30
*labelTitle2.labelString: "Window Size and Position"
*labelTitle2.alignment: "alignment_beginning"
*labelTitle2.fontList: "-adobe-helvetica-medium-r-normal--14-140-75-75-p-77-iso8859-1"

*labelTitle3.class: label
*labelTitle3.static: true
*labelTitle3.name: labelTitle3
*labelTitle3.parent: form2
*labelTitle3.x: 20
*labelTitle3.y: 470
*labelTitle3.width: 195
*labelTitle3.height: 30
*labelTitle3.labelString: "Drawing Area Size and Color"
*labelTitle3.alignment: "alignment_beginning"
*labelTitle3.fontList: "-adobe-helvetica-medium-r-normal--14-140-75-75-p-77-iso8859-1"

*labelHeight1.class: label
*labelHeight1.static: true
*labelHeight1.name: labelHeight1
*labelHeight1.parent: form2
*labelHeight1.x: 10
*labelHeight1.y: 405
*labelHeight1.width: 55
*labelHeight1.height: 30
*labelHeight1.labelString: "Height "
*labelHeight1.alignment: "alignment_beginning"

*labelWidth1.class: label
*labelWidth1.static: true
*labelWidth1.name: labelWidth1
*labelWidth1.parent: form2
*labelWidth1.x: 10
*labelWidth1.y: 365
*labelWidth1.width: 55
*labelWidth1.height: 30
*labelWidth1.labelString: "Width "
*labelWidth1.alignment: "alignment_beginning"

*PagHeight.class: textField
*PagHeight.static: true
*PagHeight.name: PagHeight
*PagHeight.parent: form2
*PagHeight.x: 120
*PagHeight.y: 400
*PagHeight.width: 121
*PagHeight.height: 35

*PagWidth.class: textField
*PagWidth.static: true
*PagWidth.name: PagWidth
*PagWidth.parent: form2
*PagWidth.x: 120
*PagWidth.y: 360
*PagWidth.width: 120
*PagWidth.height: 35

*labelHeight2.class: label
*labelHeight2.static: true
*labelHeight2.name: labelHeight2
*labelHeight2.parent: form2
*labelHeight2.x: 10
*labelHeight2.y: 540
*labelHeight2.width: 69
*labelHeight2.height: 30
*labelHeight2.labelString: "Height "
*labelHeight2.alignment: "alignment_beginning"

*DrawHeight.class: textField
*DrawHeight.static: true
*DrawHeight.name: DrawHeight
*DrawHeight.parent: form2
*DrawHeight.x: 120
*DrawHeight.y: 540
*DrawHeight.width: 125
*DrawHeight.height: 35

*labelWidth2.class: label
*labelWidth2.static: true
*labelWidth2.name: labelWidth2
*labelWidth2.parent: form2
*labelWidth2.x: 10
*labelWidth2.y: 500
*labelWidth2.width: 71
*labelWidth2.height: 30
*labelWidth2.labelString: "Width "
*labelWidth2.alignment: "alignment_beginning"

*DrawWidth.class: textField
*DrawWidth.static: true
*DrawWidth.name: DrawWidth
*DrawWidth.parent: form2
*DrawWidth.x: 120
*DrawWidth.y: 500
*DrawWidth.width: 126
*DrawWidth.height: 35

*pushButton1.class: pushButton
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.parent: form2
*pushButton1.x: 10
*pushButton1.y: 590
*pushButton1.width: 100
*pushButton1.height: 30
*pushButton1.labelString: "Background"
*pushButton1.activateCallback: {\
extern swidget create_ColorViewer();\
swidget ColorInterface;\
char InitColor[100];\
XmString LabelButton;\
\
strcpy(InitColor,XmTextFieldGetString(PagBackground));\
\
LabelButton = XmStringCreateSimple("Page Background");\
\
ListaWid[0] = pushButton1;\
ListaWid[1] = PagBackground;\
ColorInterface = create_ColorViewer(CONFIG_VER,InitColor,\
                                    LabelButton,UxDisplay->db,\
				    ListaWid,PagDialog);\
\
if(ColorInterface)\
   UxPopupInterface(ColorInterface,no_grab);\
\
}

*labelTipo.class: label
*labelTipo.static: true
*labelTipo.name: labelTipo
*labelTipo.parent: form2
*labelTipo.x: 10
*labelTipo.y: 140
*labelTipo.width: 90
*labelTipo.height: 30
*labelTipo.labelString: "Tipo Pagina"
*labelTipo.alignment: "alignment_beginning"

*PagName.class: textField
*PagName.static: true
*PagName.name: PagName
*PagName.parent: form2
*PagName.x: 120
*PagName.y: 40
*PagName.width: 175
*PagName.height: 35
*PagName.maxLength: 4
*PagName.columns: 20

*menu4.class: rowColumn
*menu4.static: true
*menu4.name: menu4
*menu4.parent: form2
*menu4.rowColumnType: "menu_option"
*menu4.subMenuId: "menu4_p1"
*menu4.x: 158
*menu4.y: 139

*menu4_p1.class: rowColumn
*menu4_p1.static: true
*menu4_p1.name: menu4_p1
*menu4_p1.parent: menu4
*menu4_p1.rowColumnType: "menu_pulldown"

*menu4_p1_b2.class: pushButton
*menu4_p1_b2.static: true
*menu4_p1_b2.name: menu4_p1_b2
*menu4_p1_b2.parent: menu4_p1
*menu4_p1_b2.labelString: "Sinottico"

*menu4_p1_b1.class: pushButton
*menu4_p1_b1.static: true
*menu4_p1_b1.name: menu4_p1_b1
*menu4_p1_b1.parent: menu4_p1
*menu4_p1_b1.labelString: "Stazioni"

*menu4_p1_b3.class: pushButton
*menu4_p1_b3.static: true
*menu4_p1_b3.name: menu4_p1_b3
*menu4_p1_b3.parent: menu4_p1
*menu4_p1_b3.labelString: "Teleperm"
*menu4_p1_b3.activateCallback: {\
   /* selezioando il tipo teleperm\
      imposto X,Y,Width,Height della pagina\
      con i valori pre-definiti dal tipo teleperm\
      che dovra' occupare l'intero screen\
   */\
\
   TelepermSetDimension( ); \
\
}

*labelRefreshFrequenzy.class: label
*labelRefreshFrequenzy.static: true
*labelRefreshFrequenzy.name: labelRefreshFrequenzy
*labelRefreshFrequenzy.parent: form2
*labelRefreshFrequenzy.x: 8
*labelRefreshFrequenzy.y: 221
*labelRefreshFrequenzy.width: 190
*labelRefreshFrequenzy.height: 30
*labelRefreshFrequenzy.labelString: "Refresh Frequezy (dec. sec.)"
*labelRefreshFrequenzy.alignment: "alignment_beginning"

*RefreshFrequenzy.class: textField
*RefreshFrequenzy.static: true
*RefreshFrequenzy.name: RefreshFrequenzy
*RefreshFrequenzy.parent: form2
*RefreshFrequenzy.x: 202
*RefreshFrequenzy.y: 217
*RefreshFrequenzy.width: 40
*RefreshFrequenzy.height: 35
*RefreshFrequenzy.text: ""

*label_in_use.class: label
*label_in_use.static: true
*label_in_use.name: label_in_use
*label_in_use.parent: form2
*label_in_use.x: 7
*label_in_use.y: 173
*label_in_use.width: 145
*label_in_use.height: 26
*label_in_use.labelString: "Regolation scheme"
*label_in_use.alignment: "alignment_beginning"

*menu7.class: rowColumn
*menu7.static: true
*menu7.name: menu7
*menu7.parent: form2
*menu7.rowColumnType: "menu_option"
*menu7.subMenuId: "menu_in_use"
*menu7.x: 157
*menu7.y: 171

*menu_in_use.class: rowColumn
*menu_in_use.static: true
*menu_in_use.name: menu_in_use
*menu_in_use.parent: menu7
*menu_in_use.rowColumnType: "menu_pulldown"

*In_use.class: pushButton
*In_use.static: true
*In_use.name: In_use
*In_use.parent: menu_in_use
*In_use.labelString: "In use"

*Not_in_use.class: pushButton
*Not_in_use.static: true
*Not_in_use.name: Not_in_use
*Not_in_use.parent: menu_in_use
*Not_in_use.labelString: "Not in use"

*HierarchyLabel.class: label
*HierarchyLabel.static: true
*HierarchyLabel.name: HierarchyLabel
*HierarchyLabel.parent: form2
*HierarchyLabel.x: 20
*HierarchyLabel.y: 640
*HierarchyLabel.width: 120
*HierarchyLabel.height: 30
*HierarchyLabel.alignment: "alignment_beginning"
*HierarchyLabel.fontList: "-adobe-helvetica-medium-r-normal--14-100-100-100-p-76-iso8859-1"
*HierarchyLabel.labelString: "Hierarchy Position"

*Hierarchy.class: textField
*Hierarchy.static: true
*Hierarchy.name: Hierarchy
*Hierarchy.parent: form2
*Hierarchy.x: 120
*Hierarchy.y: 670
*Hierarchy.width: 240
*Hierarchy.height: 35

