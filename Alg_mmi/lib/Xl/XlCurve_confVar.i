! UIMX ascii 2.5 key: 3209                                                      

*confVar.class: dialogShell
*confVar.gbldecl: #include <stdio.h>\
#include <stdlib.h>\
\
#include <XlCurve.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "f22_circ.h"\
\
extern swidget create_warningDialog1();\
extern swidget create_selectVar();\
extern Boolean convStringToPix();\
extern Boolean VerifStrFloat();\
\
/* extern char *varInfoApp[NUMMAXVAR];\
extern char *colStringApp[NUMMAXVAR]; */\
\
Boolean RecoveryLoadInfo();\
Boolean RestoreInfo();\
void confVar_agg_name_descr();\
\
\
/* char nome_var[CHAR_LEGO_COD];\
char descr_var[71]; */\

*confVar.ispecdecl: char nome_var[CHAR_LEGO_COD+1];\
char descr_var[71];
*confVar.ispeclist: nome_var, descr_var
*confVar.ispeclist.nome_var: "unsigned char", "%nome_var%[9]"
*confVar.ispeclist.descr_var: "unsigned char", "%descr_var%[71]"
*confVar.funcdecl: swidget create_confVar(UxParent,singleVarInfo,singleColString,path_f22,num_trend)\
swidget UxParent;\
char *singleVarInfo;\
char *singleColString;\
char *path_f22;\
int num_trend;
*confVar.funcname: create_confVar
*confVar.funcdef: "swidget", "<create_confVar>(%)"
*confVar.argdecl: swidget UxParent;\
unsigned char *singleVarInfo;\
unsigned char *singleColString;\
unsigned char *path_f22;\
int num_trend;
*confVar.arglist: UxParent, singleVarInfo, singleColString, path_f22, num_trend
*confVar.arglist.UxParent: "swidget", "%UxParent%"
*confVar.arglist.singleVarInfo: "unsigned char", "*%singleVarInfo%"
*confVar.arglist.singleColString: "unsigned char", "*%singleColString%"
*confVar.arglist.path_f22: "unsigned char", "*%path_f22%"
*confVar.arglist.num_trend: "int", "%num_trend%"
*confVar.icode:
*confVar.fcode: /*\
	Chiamata alla funzione che estrae le singole informazioni dalla stringa\
	infoVarChange[i] e le carica nell'interfaccia.\
*/\
\
   RecoveryLoadInfo(rtrn);\
\
UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*confVar.auxdecl: Boolean RecoveryLoadInfo(w)\
Widget w;\
{\
_UxCconfVar  *UxSaveCtx, *UxContext;\
int i,length,size;\
char str_app[MAXLENINFOVAR],str_single_info[100],lab_titolo[10];\
char *str_app1,*p;\
char *str_end[NUMINFOVAR];\
XmString compound;\
Widget Button, Pane;\
WidgetList ListaButton;\
\
printf("RecoveryLoadInfo: ENTRATO!!!\n");\
\
   UxSaveCtx = UxConfVarContext;\
   UxConfVarContext = UxContext = (_UxCconfVar *) UxGetContext(w);\
/*\
	Setting della label titolo.\
*/\
   sprintf(lab_titolo,"Trend %d",num_trend);\
   compound=XmStringCreateSimple(lab_titolo);\
   XtVaSetValues(labelTit,XmNlabelString,compound,NULL);\
   XmStringFree(compound);\
   strcpy(str_app,singleVarInfo);\
   if(strcmp(str_app,"")!=0) {\
\
printf("RecoveryLoadInfo: str_curr=%s\n",str_app);\
\
/*\
	Recupero le singole informazioni. Non inserisco controlli sulla correttezza di cio'\
	che viene estratto. Tali controlli sono fatti precedentemente.\
*/\
      i=0;\
      while((str_app1=strchr(str_app, '|')) != NULL) {\
         length=strlen(str_app)-strlen(str_app1);\
         strncpy(str_single_info, str_app, length);\
         str_single_info[length] = '\0';\
         size=strlen(str_single_info);\
         p=(char *)XtCalloc(size,sizeof(char));\
         strcpy(p,str_single_info);\
         str_end[i]=p;\
\
printf("RecoveryLoadInfo: str_end[%d]=%s\n",i,str_end[i]);\
\
         i++;\
         strcpy(str_app,(str_app1+1));\
      }\
/*\
	Caricamento delle singole informazioni nell'interfaccia.\
*/\
      XmTextFieldSetString(textField1,singleColString);   \
      XmTextFieldSetString(textField2,str_end[0]);\
      XmTextFieldSetString(textField3,str_end[2]);\
      XmTextFieldSetString(textField4,str_end[3]);\
      XmTextFieldSetString(textField5,str_end[4]);\
      XmTextFieldSetString(textField6,str_end[5]);\
/*\
	Setto il valore del tipo di unita' di misura nell'option menu.\
*/\
      get_something(optionMenu1,XmNsubMenuId,&Pane);\
      get_something(Pane,XmNchildren,&ListaButton);\
      if(strcmp(str_end[6],PERCENT)==0)\
         Button = ListaButton[1];\
      else if(strcmp(str_end[6],PERUNIT)==0)\
         Button = ListaButton[2];\
      else\
         Button = ListaButton[0];\
\
      set_something(optionMenu1,XmNmenuHistory,Button);	\
/*\
	Libero la struttura str_end allocata dinamicamente.\
*/\
      for(i=0;i<NUMINFOVAR;i++)\
         XtFree(str_end[i]);\
   }\
   else {\
/*\
	La variabile corrente non e' ancora stata configurata. Carico stringhe vuote\
	nell'interfaccia.\
*/\
      XmTextFieldSetString(textField1,singleColString);\
      XmTextFieldSetString(textField2,"");\
      XmTextFieldSetString(textField3,"");\
      XmTextFieldSetString(textField4,"");\
      XmTextFieldSetString(textField5,"");\
      XmTextFieldSetString(textField6,"");\
\
      get_something(optionMenu1,XmNsubMenuId,&Pane);\
      get_something(Pane,XmNchildren,&ListaButton);\
      Button = ListaButton[0];\
      set_something(optionMenu1,XmNmenuHistory,Button);\
   }\
   UxConfVarContext = UxSaveCtx;\
printf("RecoveryLoadInfo: USCITO!!!\n");\
\
}\
\
\
Boolean RestoreInfo(w)\
Widget w;\
{\
int i,num_empty;\
char *single_info[NUMINFOVAR];\
char all_info[MAXLENINFOVAR];\
char *color_str;\
Pixel pix;\
Widget WgtSelMenu, Pane;\
WidgetList ListaButton;\
_UxCconfVar  *UxSaveCtx, *UxContext;\
\
printf("RestoreInfo: ENTRATO!!!\n");\
\
\
   UxSaveCtx = UxConfVarContext;\
   UxConfVarContext = UxContext = (_UxCconfVar *) UxGetContext(w);\
/*\
	Recupero delle singole informazioni da interfaccia.\
*/\
   color_str=XmTextFieldGetString(textField1);   \
   single_info[0]=XmTextFieldGetString(textField2);\
   single_info[1]=XmTextFieldGetString(textField2);\
   single_info[2]=XmTextFieldGetString(textField3);\
   single_info[3]=XmTextFieldGetString(textField4);\
   single_info[4]=XmTextFieldGetString(textField5);\
   single_info[5]=XmTextFieldGetString(textField6);\
\
   get_something(optionMenu1,XmNmenuHistory,&WgtSelMenu);\
   get_something(optionMenu1,XmNsubMenuId,&Pane);\
   get_something(Pane,XmNchildren,&ListaButton);\
   single_info[6] = (char *)calloc(4,sizeof(char));\
   if(WgtSelMenu == ListaButton[0])\
      strcpy(single_info[6],ENGINEER);\
   else if(WgtSelMenu == ListaButton[1])\
      strcpy(single_info[6],PERCENT);\
   else\
      strcpy(single_info[6],PERUNIT);\
/*\
   Controlli sui valori caricati nell'interfaccia.\
*/\
printf("RestoreInfo: prima dei controlli sui dati inseriti\n"); \
   num_empty=0;\
   for(i=0;i<(NUMINFOVAR-1);i++) {\
printf("RestoreInfo: single_info[%d]=%s\n",i,single_info[i]);\
      if(strcmp(single_info[i],"")==0)\
         num_empty++;\
   }\
   if(num_empty!=(NUMINFOVAR-1)) {\
/*\
	La variabile corrente e' stata configurata. Controllo sulla correttezza dei valori.\
*/\
      if((strlen(single_info[0])>CHAR_LEGO_COD)||(strcmp(single_info[0],"")==0)) {\
         create_warningDialog1(confVar,0);\
         return(False);\
      }\
      if((strcmp(single_info[3],"")==0)||(VerifStrFloat(single_info[3])==False)) {\
         create_warningDialog1(confVar,1);\
         return(False);\
      }\
      if((strcmp(single_info[4],"")==0)||(VerifStrFloat(single_info[4])==False)) {\
         create_warningDialog1(confVar,7);\
         return(False);\
      }\
      if(atof(single_info[3])>=atof(single_info[4])) {\
         create_warningDialog1(confVar,2);\
         return(False);\
      }   \
      if(strcmp(single_info[5],"")==0) {\
         create_warningDialog1(confVar,3);\
         return(False);\
      }\
      if(convStringToPix(confVar,color_str,&pix)==False) {\
         create_warningDialog1(confVar,4);\
         return(False);\
      }\
/*\
	Controlli andati a buon fine. Compongo la stringa con le informazioni separate da\
	pipes.\
*/\
      strcpy(all_info,single_info[0]);\
      strcat(all_info,"|");\
      XtFree(single_info[0]);\
      for(i=1;i<NUMINFOVAR;i++) {\
         if(strcmp(single_info[i],"")==0)\
            strcpy(single_info[i],"---");\
         strcat(all_info,single_info[i]);\
         XtFree(single_info[i]);\
         strcat(all_info,"|");\
      }\
      strcpy(singleVarInfo,all_info);\
      strcpy(singleColString,color_str);\
      printf("RestoreInfo: singleVarInfo=%s\n",singleVarInfo);\
  }\
  else {\
/*\
	I campi informazione non sono stati caricati. Salvo una stringa nulla. Variabile non\
	configurata.\
*/\
      strcpy(singleVarInfo,"");\
  }\
  UxConfVarContext = UxSaveCtx;\
\
printf("RestoreInfo: USCITO!!!\n");\
\
return(True);\
}\
\
\
void confVar_agg_name_descr(w)\
Widget w;\
{\
printf("confVar_agg_name_descr: nome_var=%s\tdescr_var=%s\n",nome_var,descr_var);\
   confVar_agg_text_field(w,&UxEnv);\
}\
\

*confVar_agg_text_field.class: method
*confVar_agg_text_field.name: agg_text_field
*confVar_agg_text_field.parent: confVar
*confVar_agg_text_field.methodType: void
*confVar_agg_text_field.methodArgs: 
*confVar_agg_text_field.methodBody: printf("confVar_agg_text_field: nome_var=%s\tdescr_var=%s\n",nome_var,descr_var);\
\
XmTextFieldSetString(textField2,nome_var);\
XmTextFieldSetString(textField3,descr_var);\
\
/* XtVaSetValues(textField2,XmNtextValue,nome_var,NULL);\
XtVaSetValues(textField3,XmNtextValue,descr_var,NULL);   */

*confVar.static: true
*confVar.name: confVar
*confVar.parent: NO_PARENT
*confVar.parentExpression: UxParent
*confVar.width: 630
*confVar.height: 230
*confVar.isCompound: "true"
*confVar.compoundIcon: "dialogS.xpm"
*confVar.compoundName: "dialog_Shell"
*confVar.x: 500
*confVar.y: 450

*form4.class: form
*form4.static: true
*form4.name: form4
*form4.parent: confVar
*form4.width: 1015
*form4.height: 180
*form4.resizePolicy: "resize_none"
*form4.isCompound: "true"
*form4.compoundIcon: "form.xpm"
*form4.compoundName: "form_"
*form4.x: 20
*form4.y: 10
*form4.unitType: "pixels"
*form4.dialogStyle: "dialog_modeless"
*form4.background: "WhiteSmoke"

*form5.class: form
*form5.static: true
*form5.name: form5
*form5.parent: form4
*form5.width: 995
*form5.height: 45
*form5.resizePolicy: "resize_none"
*form5.isCompound: "true"
*form5.compoundIcon: "form.xpm"
*form5.compoundName: "form_"
*form5.x: 5
*form5.y: 130
*form5.borderWidth: 1
*form5.background: "WhiteSmoke"
*form5.rightAttachment: "attach_form"
*form5.rightOffset: 5
*form5.leftAttachment: "attach_form"
*form5.leftOffset: 5

*pushButok.class: pushButton
*pushButok.static: true
*pushButok.name: pushButok
*pushButok.parent: form5
*pushButok.isCompound: "true"
*pushButok.compoundIcon: "push.xpm"
*pushButok.compoundName: "push_Button"
*pushButok.x: 20
*pushButok.y: 5
*pushButok.height: 35
*pushButok.width: 100
*pushButok.labelString: "Ok"
*pushButok.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButok.activateCallback: {\
if(RestoreInfo(confVar)==True)\
   UxDestroyInterface(confVar);\
}
*pushButok.background: "WhiteSmoke"

*pushButdelete.class: pushButton
*pushButdelete.static: true
*pushButdelete.name: pushButdelete
*pushButdelete.parent: form5
*pushButdelete.isCompound: "true"
*pushButdelete.compoundIcon: "push.xpm"
*pushButdelete.compoundName: "push_Button"
*pushButdelete.x: 269
*pushButdelete.y: 5
*pushButdelete.height: 35
*pushButdelete.width: 100
*pushButdelete.labelString: "Delete"
*pushButdelete.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButdelete.activateCallback: {\
/*\
	Delete del contenuto di tutti i text fields.\
*/\
      XmTextFieldSetString(textField1,"");   \
      XmTextFieldSetString(textField2,"");\
      XmTextFieldSetString(textField3,"");\
      XmTextFieldSetString(textField4,"");\
      XmTextFieldSetString(textField5,"");\
      XmTextFieldSetString(textField6,"");\
\
}
*pushButdelete.background: "WhiteSmoke"
*pushButdelete.leftAttachment: "attach_widget"
*pushButdelete.leftOffset: 20
*pushButdelete.leftWidget: "pushButok"
*pushButdelete.topOffset: 5

*pushButcancel.class: pushButton
*pushButcancel.static: true
*pushButcancel.name: pushButcancel
*pushButcancel.parent: form5
*pushButcancel.isCompound: "true"
*pushButcancel.compoundIcon: "push.xpm"
*pushButcancel.compoundName: "push_Button"
*pushButcancel.x: 180
*pushButcancel.y: 5
*pushButcancel.height: 35
*pushButcancel.width: 100
*pushButcancel.labelString: "Cancel"
*pushButcancel.leftAttachment: "attach_widget"
*pushButcancel.leftOffset: 20
*pushButcancel.leftWidget: "pushButdelete"
*pushButcancel.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButcancel.activateCallback: {\
UxDestroyInterface(confVar);\
}
*pushButcancel.background: "WhiteSmoke"

*form6.class: form
*form6.static: true
*form6.name: form6
*form6.parent: form4
*form6.width: 180
*form6.height: 80
*form6.resizePolicy: "resize_none"
*form6.isCompound: "true"
*form6.compoundIcon: "form.xpm"
*form6.compoundName: "form_"
*form6.x: 5
*form6.y: 45
*form6.borderWidth: 1
*form6.background: "WhiteSmoke"
*form6.topOffset: 10

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: form6
*label1.isCompound: "true"
*label1.compoundIcon: "label.xpm"
*label1.compoundName: "label_"
*label1.x: 10
*label1.y: 10
*label1.height: 25
*label1.width: 60
*label1.labelString: "Color"
*label1.alignment: "alignment_beginning"
*label1.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label1.background: "WhiteSmoke"

*pushButton1.class: pushButton
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.parent: form6
*pushButton1.isCompound: "true"
*pushButton1.compoundIcon: "push.xpm"
*pushButton1.compoundName: "push_Button"
*pushButton1.x: 10
*pushButton1.y: 50
*pushButton1.width: 35
*pushButton1.height: 35
*pushButton1.labelString: "..."
*pushButton1.topAttachment: "attach_widget"
*pushButton1.topOffset: 5
*pushButton1.topWidget: "label1"
*pushButton1.sensitive: "false"
*pushButton1.background: "WhiteSmoke"

*textField1.class: textField
*textField1.static: true
*textField1.name: textField1
*textField1.parent: form6
*textField1.width: 120
*textField1.isCompound: "true"
*textField1.compoundIcon: "textfield.xpm"
*textField1.compoundName: "text_Field"
*textField1.x: 69
*textField1.y: 49
*textField1.leftAttachment: "attach_widget"
*textField1.leftOffset: 5
*textField1.leftWidget: "pushButton1"
*textField1.height: 35
*textField1.topAttachment: "attach_widget"
*textField1.topOffset: 5
*textField1.topWidget: "label1"
*textField1.text: ""
*textField1.background: "WhiteSmoke"

*form7.class: form
*form7.static: true
*form7.name: form7
*form7.parent: form4
*form7.width: 410
*form7.height: 80
*form7.resizePolicy: "resize_none"
*form7.isCompound: "true"
*form7.compoundIcon: "form.xpm"
*form7.compoundName: "form_"
*form7.x: 195
*form7.y: 45
*form7.borderWidth: 1
*form7.background: "WhiteSmoke"
*form7.topOffset: 10

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: form7
*label2.isCompound: "true"
*label2.compoundIcon: "label.xpm"
*label2.compoundName: "label_"
*label2.x: 50
*label2.y: 10
*label2.height: 25
*label2.width: 90
*label2.labelString: "Var Lego"
*label2.alignment: "alignment_beginning"
*label2.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label2.background: "WhiteSmoke"

*pushButton2.class: pushButton
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.parent: form7
*pushButton2.isCompound: "true"
*pushButton2.compoundIcon: "push.xpm"
*pushButton2.compoundName: "push_Button"
*pushButton2.x: 10
*pushButton2.y: 45
*pushButton2.width: 35
*pushButton2.height: 35
*pushButton2.labelString: "..."
*pushButton2.topOffset: 5
*pushButton2.topAttachment: "attach_widget"
*pushButton2.topWidget: "label2"
*pushButton2.activateCallback: {\
create_selectVar(NO_PARENT,confVar,nome_var,descr_var,path_f22);\
}
*pushButton2.background: "WhiteSmoke"

*textField2.class: textField
*textField2.static: true
*textField2.name: textField2
*textField2.parent: form7
*textField2.width: 100
*textField2.isCompound: "true"
*textField2.compoundIcon: "textfield.xpm"
*textField2.compoundName: "text_Field"
*textField2.x: 69
*textField2.y: 49
*textField2.height: 35
*textField2.leftAttachment: "attach_widget"
*textField2.leftOffset: 5
*textField2.leftWidget: "pushButton2"
*textField2.topAttachment: "attach_widget"
*textField2.topOffset: 5
*textField2.topWidget: "label2"
*textField2.background: "WhiteSmoke"

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: form7
*label3.isCompound: "true"
*label3.compoundIcon: "label.xpm"
*label3.compoundName: "label_"
*label3.x: 159
*label3.y: 9
*label3.height: 25
*label3.width: 140
*label3.labelString: "Description"
*label3.alignment: "alignment_beginning"
*label3.leftAttachment: "attach_widget"
*label3.leftOffset: 15
*label3.leftWidget: "label2"
*label3.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label3.background: "WhiteSmoke"

*textField3.class: textField
*textField3.static: true
*textField3.name: textField3
*textField3.parent: form7
*textField3.width: 250
*textField3.isCompound: "true"
*textField3.compoundIcon: "textfield.xpm"
*textField3.compoundName: "text_Field"
*textField3.x: 3199
*textField3.y: 49
*textField3.height: 35
*textField3.leftAttachment: "attach_widget"
*textField3.leftOffset: 5
*textField3.leftWidget: "textField2"
*textField3.topAttachment: "attach_widget"
*textField3.topOffset: 5
*textField3.topWidget: "label3"
*textField3.background: "WhiteSmoke"
*textField3.rightAttachment: "attach_none"
*textField3.rightOffset: 0

*form8.class: form
*form8.static: true
*form8.name: form8
*form8.parent: form4
*form8.width: 390
*form8.height: 80
*form8.resizePolicy: "resize_none"
*form8.isCompound: "true"
*form8.compoundIcon: "form.xpm"
*form8.compoundName: "form_"
*form8.x: 615
*form8.y: 45
*form8.borderWidth: 1
*form8.background: "WhiteSmoke"
*form8.topOffset: 10
*form8.rightAttachment: "attach_form"
*form8.rightOffset: 5
*form8.leftAttachment: "attach_widget"
*form8.leftOffset: 10
*form8.leftWidget: "form7"

*label4.class: label
*label4.static: true
*label4.name: label4
*label4.parent: form8
*label4.isCompound: "true"
*label4.compoundIcon: "label.xpm"
*label4.compoundName: "label_"
*label4.x: 10
*label4.y: 10
*label4.height: 25
*label4.width: 90
*label4.labelString: "Low Lim"
*label4.alignment: "alignment_beginning"
*label4.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label4.background: "WhiteSmoke"

*label5.class: label
*label5.static: true
*label5.name: label5
*label5.parent: form8
*label5.isCompound: "true"
*label5.compoundIcon: "label.xpm"
*label5.compoundName: "label_"
*label5.x: 119
*label5.y: 9
*label5.height: 25
*label5.width: 90
*label5.labelString: "High Lim"
*label5.alignment: "alignment_beginning"
*label5.leftAttachment: "attach_widget"
*label5.leftOffset: 5
*label5.leftWidget: "label4"
*label5.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label5.background: "WhiteSmoke"

*label6.class: label
*label6.static: true
*label6.name: label6
*label6.parent: form8
*label6.isCompound: "true"
*label6.compoundIcon: "label.xpm"
*label6.compoundName: "label_"
*label6.x: 219
*label6.y: 9
*label6.height: 25
*label6.width: 90
*label6.labelString: "Unit Mis"
*label6.alignment: "alignment_beginning"
*label6.leftAttachment: "attach_widget"
*label6.leftOffset: 5
*label6.leftWidget: "label5"
*label6.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label6.background: "WhiteSmoke"

*textField4.class: textField
*textField4.static: true
*textField4.name: textField4
*textField4.parent: form8
*textField4.width: 90
*textField4.isCompound: "true"
*textField4.compoundIcon: "textfield.xpm"
*textField4.compoundName: "text_Field"
*textField4.x: 9
*textField4.y: 49
*textField4.height: 35
*textField4.topAttachment: "attach_widget"
*textField4.topOffset: 5
*textField4.topWidget: "label4"
*textField4.background: "WhiteSmoke"

*textField5.class: textField
*textField5.static: true
*textField5.name: textField5
*textField5.parent: form8
*textField5.width: 90
*textField5.isCompound: "true"
*textField5.compoundIcon: "textfield.xpm"
*textField5.compoundName: "text_Field"
*textField5.x: 119
*textField5.y: 49
*textField5.height: 35
*textField5.leftAttachment: "attach_widget"
*textField5.leftOffset: 5
*textField5.leftWidget: "textField4"
*textField5.topAttachment: "attach_widget"
*textField5.topOffset: 5
*textField5.topWidget: "label5"
*textField5.background: "WhiteSmoke"

*textField6.class: textField
*textField6.static: true
*textField6.name: textField6
*textField6.parent: form8
*textField6.width: 90
*textField6.isCompound: "true"
*textField6.compoundIcon: "textfield.xpm"
*textField6.compoundName: "text_Field"
*textField6.x: 219
*textField6.y: 49
*textField6.height: 35
*textField6.leftAttachment: "attach_widget"
*textField6.leftOffset: 5
*textField6.leftWidget: "textField5"
*textField6.topAttachment: "attach_widget"
*textField6.topOffset: 5
*textField6.topWidget: "label6"
*textField6.background: "WhiteSmoke"
*textField6.borderWidth: 0

*label7.class: label
*label7.static: true
*label7.name: label7
*label7.parent: form8
*label7.isCompound: "true"
*label7.compoundIcon: "label.xpm"
*label7.compoundName: "label_"
*label7.x: 230
*label7.y: 9
*label7.height: 25
*label7.width: 90
*label7.labelString: "Unit Type"
*label7.alignment: "alignment_beginning"
*label7.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*label7.background: "WhiteSmoke"
*label7.leftAttachment: "attach_widget"
*label7.leftOffset: 5
*label7.leftWidget: "label6"
*label7.topOffset: 10

*optionMenu1.class: rowColumn
*optionMenu1.static: true
*optionMenu1.name: optionMenu1
*optionMenu1.parent: form8
*optionMenu1.rowColumnType: "menu_option"
*optionMenu1.subMenuId: "optionMenu_p1"
*optionMenu1.isCompound: "true"
*optionMenu1.compoundIcon: "optionM.xpm"
*optionMenu1.compoundName: "option_Menu"
*optionMenu1.compoundEditor: {\
extern swidget UxGUIMePopup UXPROTO((swidget, swidget, int, int));\
UxGUIMePopup(UxThisWidget, NULL, 2, 0);\
}
*optionMenu1.x: 289
*optionMenu1.y: 39
*optionMenu1.width: 80
*optionMenu1.height: 35
*optionMenu1.leftAttachment: "attach_widget"
*optionMenu1.leftOffset: 3
*optionMenu1.leftWidget: "textField6"
*optionMenu1.topAttachment: "attach_widget"
*optionMenu1.topOffset: 5
*optionMenu1.topWidget: "label7"
*optionMenu1.ancestorSensitive: "true"
*optionMenu1.marginHeight: 0
*optionMenu1.marginWidth: 0
*optionMenu1.spacing: 0
*optionMenu1.background: "WhiteSmoke"
*optionMenu1.menuHistory: "optionMenuPc"
*optionMenu1.borderWidth: 0
*optionMenu1.rightAttachment: "attach_none"
*optionMenu1.rightOffset: 0

*optionMenu_p1.class: rowColumn
*optionMenu_p1.static: true
*optionMenu_p1.name: optionMenu_p1
*optionMenu_p1.parent: optionMenu1
*optionMenu_p1.rowColumnType: "menu_pulldown"
*optionMenu_p1.ancestorSensitive: "true"
*optionMenu_p1.shadowThickness: 0
*optionMenu_p1.width: 43

*optionMenuEng.class: pushButton
*optionMenuEng.static: true
*optionMenuEng.name: optionMenuEng
*optionMenuEng.parent: optionMenu_p1
*optionMenuEng.labelString: "ENG"
*optionMenuEng.marginHeight: 2
*optionMenuEng.marginWidth: 2
*optionMenuEng.x: 0
*optionMenuEng.y: 0
*optionMenuEng.background: "WhiteSmoke"
*optionMenuEng.borderWidth: 1

*optionMenuPc.class: pushButton
*optionMenuPc.static: true
*optionMenuPc.name: optionMenuPc
*optionMenuPc.parent: optionMenu_p1
*optionMenuPc.labelString: "PC"
*optionMenuPc.background: "WhiteSmoke"
*optionMenuPc.borderWidth: 1

*optionMenuPu.class: pushButton
*optionMenuPu.static: true
*optionMenuPu.name: optionMenuPu
*optionMenuPu.parent: optionMenu_p1
*optionMenuPu.labelString: "PU"
*optionMenuPu.background: "WhiteSmoke"
*optionMenuPu.borderWidth: 1

*labelTit.class: label
*labelTit.static: true
*labelTit.name: labelTit
*labelTit.parent: form4
*labelTit.isCompound: "true"
*labelTit.compoundIcon: "label.xpm"
*labelTit.compoundName: "label_"
*labelTit.x: 370
*labelTit.y: 10
*labelTit.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*labelTit.labelString: "Trend"
*labelTit.height: 30
*labelTit.width: 150
*labelTit.topOffset: 5
*labelTit.leftAttachment: "attach_form"
*labelTit.leftPosition: 0
*labelTit.background: "WhiteSmoke"
*labelTit.borderWidth: 1
*labelTit.leftOffset: 432

