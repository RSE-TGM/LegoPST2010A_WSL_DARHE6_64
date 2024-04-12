! UIMX ascii 2.5 key: 7467                                                      

*selectVar.class: selectionBox
*selectVar.gbldecl: #include <stdio.h>\
\
#include <XlCurve.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "f22_circ.h"\
\
#define DEFAULT_F22_STR   "libera"\
\
extern swidget create_warningDialog1();\
extern void confVar_agg_name_descr();\
\
/*\
extern char path_source_f22[MAXPATHNAME];\
*/\
\

*selectVar.ispecdecl:
*selectVar.funcdecl: swidget create_selectVar(UxParent,wid_parent,nome,descriz,path_source_f22)\
Widget UxParent;\
Widget wid_parent;\
char *nome;\
char *descriz;\
char *path_source_f22;
*selectVar.funcname: create_selectVar
*selectVar.funcdef: "swidget", "<create_selectVar>(%)"
*selectVar.argdecl: Widget UxParent;\
Widget wid_parent;\
unsigned char *nome;\
unsigned char *descriz;\
unsigned char *path_source_f22;
*selectVar.arglist: UxParent, wid_parent, nome, descriz, path_source_f22
*selectVar.arglist.UxParent: "Widget", "%UxParent%"
*selectVar.arglist.wid_parent: "Widget", "%wid_parent%"
*selectVar.arglist.nome: "unsigned char", "*%nome%"
*selectVar.arglist.descriz: "unsigned char", "*%descriz%"
*selectVar.arglist.path_source_f22: "unsigned char", "*%path_source_f22%"
*selectVar.icode: F22CIRC_VAR *nome_descr;\
int num_var,num_var_select;\
int count;\
PUNT_FILE_F22 punt_f22;\
\
XmString *str;\
int i;\
char nome_descr_str[100],str_app_load[CHAR_LEGO_COD];\
\

*selectVar.fcode: if(f22_open_file_new(path_source_f22,&punt_f22)==0) {\
      UxPopupInterface(rtrn,no_grab);\
      create_warningDialog1(rtrn,5);\
   }\
   else {\
      if(f22_leggo_nomi_var(punt_f22,&nome_descr,&num_var)==0) {\
         UxPopupInterface(rtrn,no_grab);\
         create_warningDialog1(rtrn,6);\
         f22_close_file(punt_f22);\
      }\
      else {\
/*\
	Lettura dei nomi delle variabili andata a buon fine. Caricamento nell'interfaccia.\
*/\
         f22_close_file(punt_f22);\
         count=0;\
         strncpy(str_app_load,nome_descr[count].nomevar,strlen(DEFAULT_F22_STR));\
         str_app_load[strlen(DEFAULT_F22_STR)]='\0';\
         while((count<num_var)&&(strcmp(str_app_load,DEFAULT_F22_STR)!=0)) {\
            count++;\
            if(count!=num_var) {\
               strncpy(str_app_load,nome_descr[count].nomevar,strlen(DEFAULT_F22_STR));\
               str_app_load[strlen(DEFAULT_F22_STR)]='\0';\
            }\
         }\
         num_var_select=count;\
printf("SELECTION_BOX: num_var_select = %d\n",num_var_select);\
         str = (XmString *)XtMalloc(num_var_select * sizeof(XmString));\
         for(i=0;i<num_var_select;i++) {                                           \
            strcpy(nome_descr_str,nome_descr[i].nomevar);\
            strcat(nome_descr_str,nome_descr[i].descvar);\
            str[i]=XmStringCreateSimple(nome_descr_str);\
         }\
         XtVaSetValues(rtrn,XmNlistItems,str,XmNlistItemCount,num_var_select,XmNmustMatch,True,NULL);\
         XtSetSensitive(\
              XmSelectionBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),False);\
         for(i=0;i<num_var_select;i++)\
            XmStringFree(str[i]);\
         XtFree(str);\
         UxPopupInterface(rtrn,no_grab);\
      }\
   }                \
\
return(rtrn);\

*selectVar.auxdecl: void activateCB_ok(w,client_data,cbs)\
Widget w;\
XtPointer client_data;\
XmSelectionBoxCallbackStruct *cbs;\
{\
\
int lungh;\
char str_glob[100];\
char *value;\
char nome_start[CHAR_LEGO_COD+1],str_app[CHAR_LEGO_COD+1],descr_app[100],*str_app1;\
\
switch (cbs->reason) {\
 case XmCR_NO_MATCH:\
 {\
printf("SELECTION_BOX: XmCR_NO_MATCH:!!!!!\n");\
   create_warningDialog1(selectVar,8);\
   break;\
 }\
 case XmCR_OK:\
 {\
   XmStringGetLtoR(cbs->value,XmSTRING_DEFAULT_CHARSET,&value);\
   strcpy(str_glob,value);\
   XmStringFree(value);\
   strncpy(nome_start,str_glob,CHAR_LEGO_COD);\
   nome_start[CHAR_LEGO_COD]='\0';\
   strcpy(descr_app,(str_glob+CHAR_LEGO_COD));\
\
printf("activateCB_ok: stringa_sel=%s\tnome_start=%s\tdescr_app=%s\n",str_glob,nome_start,descr_app);\
\
   if((str_app1=strchr(nome_start,' '))!=NULL) {\
      lungh=(strlen(nome_start)-strlen(str_app1));\
printf("activateCB_ok: lungh=%d\n",lungh);\
      strncpy(str_app,nome_start,lungh);\
      str_app[lungh]='\0';\
   }\
   else {\
      strcpy(str_app,nome_start);\
   }\
\
   strcpy(nome,str_app);\
   /* strcpy(nome,nome_start);  */\
printf("activateCB_ok: nome=%s\tnome_start=%s\n",nome,nome_start);\
   strcpy(descriz,descr_app);\
\
printf("activateCB_ok: nome=%s\tdescriz=%s\n",nome,descriz);\
\
   confVar_agg_name_descr(wid_parent);\
\
   UxDestroyInterface(selectVar);\
   break;\
 }\
 default:\
 {\
printf("SELECTION_BOX: default!!!!!\n");\
   create_warningDialog1(selectVar,8);\
   break;\
 }\
}\
}\

*selectVar.static: true
*selectVar.name: selectVar
*selectVar.parent: NO_PARENT
*selectVar.parentExpression: UxParent
*selectVar.defaultShell: topLevelShell
*selectVar.width: 500
*selectVar.height: 400
*selectVar.isCompound: "true"
*selectVar.compoundIcon: "selectpx.xpm"
*selectVar.compoundName: "selection_Box"
*selectVar.x: 790
*selectVar.y: 640
*selectVar.unitType: "pixels"
*selectVar.listLabelString: "Variables"
*selectVar.cancelCallback: {\
UxDestroyInterface(UxThisWidget);\
}
*selectVar.okCallback.source: public
*selectVar.okCallback: activateCB_ok
*selectVar.dialogType: "dialog_selection"
*selectVar.background: "WhiteSmoke"

