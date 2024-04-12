! UIMX ascii 2.5 key: 3300                                                      

*confRunTime.class: dialogShell
*confRunTime.gbldecl: #include <stdio.h>\
#include <stdlib.h>\
\
#include <XlCurve.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "f22_circ.h"\
\
extern swidget create_confVar();\
\
/*\
extern char *varInfoChange[NUMMAXVAR];\
extern char *colTrendString[NUMMAXVAR];\
extern Boolean change_conf_OK;\
char *varInfoApp[NUMMAXVAR];\
char *colStringApp[NUMMAXVAR];\
char path_source_f22[MAXPATHNAME];\
*/
*confRunTime.ispecdecl: char **varInfoApp;\
char **colStringApp;\

*confRunTime.ispeclist: varInfoApp, colStringApp
*confRunTime.ispeclist.varInfoApp: "unsigned char", "**%varInfoApp%"
*confRunTime.ispeclist.colStringApp: "unsigned char", "**%colStringApp%"
*confRunTime.funcdecl: swidget create_confRunTime(UxParent,numCurveConf,sorgDati,varInfo,colString,conf_OK)\
swidget UxParent;\
int numCurveConf;\
char *sorgDati;\
char **varInfo;\
char **colString;\
int *conf_OK;\

*confRunTime.funcname: create_confRunTime
*confRunTime.funcdef: "swidget", "<create_confRunTime>(%)"
*confRunTime.argdecl: swidget UxParent;\
int numCurveConf;\
unsigned char *sorgDati;\
unsigned char **varInfo;\
unsigned char **colString;\
int *conf_OK;
*confRunTime.arglist: UxParent, numCurveConf, sorgDati, varInfo, colString, conf_OK
*confRunTime.arglist.UxParent: "swidget", "%UxParent%"
*confRunTime.arglist.numCurveConf: "int", "%numCurveConf%"
*confRunTime.arglist.sorgDati: "unsigned char", "*%sorgDati%"
*confRunTime.arglist.varInfo: "unsigned char", "**%varInfo%"
*confRunTime.arglist.colString: "unsigned char", "**%colString%"
*confRunTime.arglist.conf_OK: "int", "*%conf_OK%"
*confRunTime.icode: int i;
*confRunTime.fcode: printf("create_confRunTime: ENTRATO!!!\n");\
\
varInfoApp = (unsigned char **)calloc(NUMMAXVAR, sizeof(char *));\
colStringApp = (unsigned char **)calloc(NUMMAXVAR, sizeof(char *));\
\
/* strcpy(path_f22,sorgDati); */\
\
if(numCurveConf<10)\
   XtVaSetValues(pushBut10,XmNsensitive,False,NULL);\
if(numCurveConf<9)\
   XtVaSetValues(pushBut9,XmNsensitive,False,NULL);\
if(numCurveConf<8)\
   XtVaSetValues(pushBut8,XmNsensitive,False,NULL);\
if(numCurveConf<7)\
   XtVaSetValues(pushBut7,XmNsensitive,False,NULL);\
if(numCurveConf<6)\
   XtVaSetValues(pushBut6,XmNsensitive,False,NULL);\
if(numCurveConf<5)\
   XtVaSetValues(pushBut5,XmNsensitive,False,NULL);\
if(numCurveConf<4)\
   XtVaSetValues(pushBut4,XmNsensitive,False,NULL);\
if(numCurveConf<3)\
   XtVaSetValues(pushBut3,XmNsensitive,False,NULL);\
if(numCurveConf<2)\
   XtVaSetValues(pushBut2,XmNsensitive,False,NULL);\
/*\
	Inizializzazione delle variabili d'appoggio.\
*/\
for(i=0;i<numCurveConf;i++) {\
   varInfoApp[i]=(unsigned char *)calloc(MAXLENINFOVAR,sizeof(char));\
   strcpy(varInfoApp[i],varInfo[i]);\
}\
\
for(i=0;i<numCurveConf;i++) {\
   colStringApp[i]=(unsigned char *)calloc(15,sizeof(char));\
   strcpy(colStringApp[i],colString[i]);\
\
printf("create_confRunTime: varInfoApp[%d]=%s\n",i,varInfoApp[i]);\
\
}\
\
\
UxPopupInterface(rtrn,no_grab);\
\
printf("create_confRunTime: USCITO!!!\n");\
\
return(rtrn);\

*confRunTime.auxdecl:
*confRunTime.static: true
*confRunTime.name: confRunTime
*confRunTime.parent: NO_PARENT
*confRunTime.parentExpression: UxParent
*confRunTime.width: 380
*confRunTime.height: 300
*confRunTime.isCompound: "true"
*confRunTime.compoundIcon: "dialogS.xpm"
*confRunTime.compoundName: "dialog_Shell"
*confRunTime.x: 470
*confRunTime.y: 560

*form2.class: form
*form2.static: true
*form2.name: form2
*form2.parent: confRunTime
*form2.width: 450
*form2.height: 250
*form2.resizePolicy: "resize_none"
*form2.isCompound: "true"
*form2.compoundIcon: "form.xpm"
*form2.compoundName: "form_"
*form2.x: 0
*form2.y: 10
*form2.unitType: "pixels"
*form2.noResize: "true"
*form2.dialogStyle: "dialog_full_application_modal"
*form2.background: "WhiteSmoke"

*labTitle.class: label
*labTitle.static: true
*labTitle.name: labTitle
*labTitle.parent: form2
*labTitle.isCompound: "true"
*labTitle.compoundIcon: "label.xpm"
*labTitle.compoundName: "label_"
*labTitle.x: 85
*labTitle.y: 10
*labTitle.width: 280
*labTitle.height: 20
*labTitle.labelString: "Configuration trends"
*labTitle.fontList: "-adobe-courier-bold-r-normal--14-140-75-75-m-90-iso8859-1"
*labTitle.background: "WhiteSmoke"
*labTitle.borderWidth: 1
*labTitle.leftOffset: 70

*rowColumn2.class: rowColumn
*rowColumn2.static: true
*rowColumn2.name: rowColumn2
*rowColumn2.parent: form2
*rowColumn2.width: 430
*rowColumn2.height: 140
*rowColumn2.isCompound: "true"
*rowColumn2.compoundIcon: "row.xpm"
*rowColumn2.compoundName: "row_Column"
*rowColumn2.x: 10
*rowColumn2.y: 40
*rowColumn2.numColumns: 5
*rowColumn2.packing: "pack_column"
*rowColumn2.radioAlwaysOne: "false"
*rowColumn2.adjustMargin: "true"
*rowColumn2.marginHeight: 30
*rowColumn2.marginWidth: 10
*rowColumn2.navigationType: "tab_group"
*rowColumn2.spacing: 20
*rowColumn2.isAligned: "false"
*rowColumn2.entryAlignment: "alignment_center"
*rowColumn2.adjustLast: "true"
*rowColumn2.resizable: "false"
*rowColumn2.rightAttachment: "attach_none"
*rowColumn2.rightOffset: 10
*rowColumn2.leftAttachment: "attach_form"
*rowColumn2.leftOffset: 10
*rowColumn2.resizeHeight: "false"
*rowColumn2.resizeWidth: "false"
*rowColumn2.topOffset: 60
*rowColumn2.background: "WhiteSmoke"
*rowColumn2.borderWidth: 1

*pushBut1.class: pushButton
*pushBut1.static: true
*pushBut1.name: pushBut1
*pushBut1.parent: rowColumn2
*pushBut1.isCompound: "true"
*pushBut1.compoundIcon: "push.xpm"
*pushBut1.compoundName: "push_Button"
*pushBut1.x: 30
*pushBut1.y: 30
*pushBut1.height: 30
*pushBut1.width: 63
*pushBut1.labelString: "Trend 1"
*pushBut1.recomputeSize: "false"
*pushBut1.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut1.activateCallback: {\
create_confVar(confRunTime,varInfoApp[0],colStringApp[0],sorgDati,1);\
\
}
*pushBut1.background: "WhiteSmoke"

*pushBut6.class: pushButton
*pushBut6.static: true
*pushBut6.name: pushBut6
*pushBut6.parent: rowColumn2
*pushBut6.isCompound: "true"
*pushBut6.compoundIcon: "push.xpm"
*pushBut6.compoundName: "push_Button"
*pushBut6.x: 20
*pushBut6.y: 30
*pushBut6.height: 30
*pushBut6.width: 60
*pushBut6.labelString: "Trend 6"
*pushBut6.recomputeSize: "false"
*pushBut6.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut6.activateCallback: {\
create_confVar(confRunTime,varInfoApp[5],colStringApp[5],sorgDati,6);\
}
*pushBut6.background: "WhiteSmoke"

*pushBut2.class: pushButton
*pushBut2.static: true
*pushBut2.name: pushBut2
*pushBut2.parent: rowColumn2
*pushBut2.isCompound: "true"
*pushBut2.compoundIcon: "push.xpm"
*pushBut2.compoundName: "push_Button"
*pushBut2.x: 100
*pushBut2.y: 30
*pushBut2.height: 30
*pushBut2.width: 60
*pushBut2.labelString: "Trend 2"
*pushBut2.recomputeSize: "false"
*pushBut2.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut2.activateCallback: {\
create_confVar(confRunTime,varInfoApp[1],colStringApp[1],sorgDati,2);\
}
*pushBut2.background: "WhiteSmoke"

*pushBut7.class: pushButton
*pushBut7.static: true
*pushBut7.name: pushBut7
*pushBut7.parent: rowColumn2
*pushBut7.isCompound: "true"
*pushBut7.compoundIcon: "push.xpm"
*pushBut7.compoundName: "push_Button"
*pushBut7.x: 180
*pushBut7.y: 30
*pushBut7.height: 30
*pushBut7.width: 60
*pushBut7.labelString: "Trend 7"
*pushBut7.recomputeSize: "false"
*pushBut7.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut7.activateCallback: {\
create_confVar(confRunTime,varInfoApp[6],colStringApp[6],sorgDati,7);\
}
*pushBut7.background: "WhiteSmoke"

*pushBut3.class: pushButton
*pushBut3.static: true
*pushBut3.name: pushBut3
*pushBut3.parent: rowColumn2
*pushBut3.isCompound: "true"
*pushBut3.compoundIcon: "push.xpm"
*pushBut3.compoundName: "push_Button"
*pushBut3.x: 260
*pushBut3.y: 30
*pushBut3.height: 30
*pushBut3.width: 60
*pushBut3.labelString: "Trend 3"
*pushBut3.recomputeSize: "false"
*pushBut3.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut3.activateCallback: {\
create_confVar(confRunTime,varInfoApp[2],colStringApp[2],sorgDati,3);\
}
*pushBut3.background: "WhiteSmoke"

*pushBut8.class: pushButton
*pushBut8.static: true
*pushBut8.name: pushBut8
*pushBut8.parent: rowColumn2
*pushBut8.isCompound: "true"
*pushBut8.compoundIcon: "push.xpm"
*pushBut8.compoundName: "push_Button"
*pushBut8.x: 340
*pushBut8.y: 30
*pushBut8.height: 30
*pushBut8.width: 60
*pushBut8.labelString: "Trend 8"
*pushBut8.recomputeSize: "false"
*pushBut8.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut8.activateCallback: {\
create_confVar(confRunTime,varInfoApp[7],colStringApp[7],sorgDati,8);\
}
*pushBut8.background: "WhiteSmoke"

*pushBut4.class: pushButton
*pushBut4.static: true
*pushBut4.name: pushBut4
*pushBut4.parent: rowColumn2
*pushBut4.isCompound: "true"
*pushBut4.compoundIcon: "push.xpm"
*pushBut4.compoundName: "push_Button"
*pushBut4.x: 100
*pushBut4.y: 30
*pushBut4.height: 30
*pushBut4.width: 60
*pushBut4.labelString: "Trend 4"
*pushBut4.recomputeSize: "false"
*pushBut4.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut4.activateCallback: {\
create_confVar(confRunTime,varInfoApp[3],colStringApp[3],sorgDati,4);\
}
*pushBut4.background: "WhiteSmoke"

*pushBut9.class: pushButton
*pushBut9.static: true
*pushBut9.name: pushBut9
*pushBut9.parent: rowColumn2
*pushBut9.isCompound: "true"
*pushBut9.compoundIcon: "push.xpm"
*pushBut9.compoundName: "push_Button"
*pushBut9.x: 180
*pushBut9.y: 30
*pushBut9.height: 30
*pushBut9.width: 60
*pushBut9.labelString: "Trend 9"
*pushBut9.recomputeSize: "false"
*pushBut9.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut9.activateCallback: {\
create_confVar(confRunTime,varInfoApp[8],colStringApp[8],sorgDati,9);\
}
*pushBut9.background: "WhiteSmoke"

*pushBut5.class: pushButton
*pushBut5.static: true
*pushBut5.name: pushBut5
*pushBut5.parent: rowColumn2
*pushBut5.isCompound: "true"
*pushBut5.compoundIcon: "push.xpm"
*pushBut5.compoundName: "push_Button"
*pushBut5.x: 260
*pushBut5.y: 30
*pushBut5.height: 30
*pushBut5.width: 60
*pushBut5.labelString: "Trend 5"
*pushBut5.recomputeSize: "false"
*pushBut5.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut5.activateCallback: {\
create_confVar(confRunTime,varInfoApp[4],colStringApp[4],sorgDati,5);\
}
*pushBut5.background: "WhiteSmoke"

*pushBut10.class: pushButton
*pushBut10.static: true
*pushBut10.name: pushBut10
*pushBut10.parent: rowColumn2
*pushBut10.isCompound: "true"
*pushBut10.compoundIcon: "push.xpm"
*pushBut10.compoundName: "push_Button"
*pushBut10.x: 260
*pushBut10.y: 80
*pushBut10.height: 30
*pushBut10.width: 60
*pushBut10.labelString: "Trend 10"
*pushBut10.recomputeSize: "false"
*pushBut10.fontList: "-adobe-courier-bold-r-normal--12-120-75-75-m-70-iso8859-1"
*pushBut10.activateCallback: {\
create_confVar(confRunTime,varInfoApp[9],colStringApp[9],sorgDati,10);\
}
*pushBut10.background: "WhiteSmoke"

*form3.class: form
*form3.static: true
*form3.name: form3
*form3.parent: form2
*form3.width: 430
*form3.height: 50
*form3.resizePolicy: "resize_none"
*form3.isCompound: "true"
*form3.compoundIcon: "form.xpm"
*form3.compoundName: "form_"
*form3.x: 10
*form3.y: 190
*form3.leftOffset: 10
*form3.background: "WhiteSmoke"
*form3.borderWidth: 1

*okBut.class: pushButton
*okBut.static: true
*okBut.name: okBut
*okBut.parent: form3
*okBut.isCompound: "true"
*okBut.compoundIcon: "push.xpm"
*okBut.compoundName: "push_Button"
*okBut.x: 50
*okBut.y: 10
*okBut.height: 35
*okBut.width: 100
*okBut.labelString: "Ok"
*okBut.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*okBut.activateCallback: {\
int i,length;\
char *str_app1,*str_app2,str_lego1[CHAR_LEGO_COD+1],str_lego2[CHAR_LEGO_COD+1];\
\
*conf_OK=PARAM_CHANGE;\
for(i=0;i<numCurveConf;i++) {\
   str_app1=strchr(varInfo[i], '|');\
   str_app2=strchr(varInfoApp[i], '|');\
   if((str_app1==NULL)||(str_app2==NULL)) {\
      if((str_app1==NULL)&&(str_app2!=NULL)) {\
/*\
	Aggiunta una variabile.\
*/\
        *conf_OK=CURVE_CHANGE;\
      }\
      else {\
         if((str_app1!=NULL)&&(str_app2==NULL)) {\
/*\
	Eliminata una variabile.\
*/\
            *conf_OK=CURVE_CHANGE;\
         }\
      }           \
   }\
   else {\
      length=strlen(varInfo[i])-strlen(str_app1);\
      strncpy(str_lego1, varInfo[i], length);\
      str_lego1[length]='\0';\
      length=strlen(varInfoApp[i])-strlen(str_app2);\
      strncpy(str_lego2, varInfoApp[i], length);\
      str_lego2[length]='\0';\
printf("okBut: str_lego1=%s\tstr_lego2=%s\n",str_lego1,str_lego2);\
      if(strcmp(str_lego1,str_lego2)!=0)\
/*\
	E' cambiato il codice lego di una delle variabili. Leggere tutti i campioni\
	dal file f22.\
*/\
         *conf_OK=CURVE_CHANGE;\
   }\
}\
\
for(i=0;i<numCurveConf;i++) {\
   strcpy(varInfo[i],varInfoApp[i]);\
   free(varInfoApp[i]);\
}\
free(varInfoApp);\
\
for(i=0;i<numCurveConf;i++) {\
   strcpy(colString[i],colStringApp[i]);\
   free(colStringApp[i]);\
}\
free(colStringApp);\
\
UxDestroyInterface(UxThisWidget);\
}
*okBut.background: "WhiteSmoke"

*cancelBut.class: pushButton
*cancelBut.static: true
*cancelBut.name: cancelBut
*cancelBut.parent: form3
*cancelBut.isCompound: "true"
*cancelBut.compoundIcon: "push.xpm"
*cancelBut.compoundName: "push_Button"
*cancelBut.x: 240
*cancelBut.y: 10
*cancelBut.height: 35
*cancelBut.width: 100
*cancelBut.labelString: "Cancel"
*cancelBut.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*cancelBut.activateCallback: {\
int i;\
\
for(i=0;i<numCurveConf;i++)\
   free(varInfoApp[i]);\
free(varInfoApp);\
\
for(i=0;i<numCurveConf;i++)\
   free(colStringApp[i]);\
free(colStringApp);\
\
UxDestroyInterface(UxThisWidget);\
}
*cancelBut.background: "WhiteSmoke"

