! UIMX ascii 2.0 key: 6686                                                      

*ModelDefinitionWindow.class: topLevelShell
*ModelDefinitionWindow.parent: NO_PARENT
*ModelDefinitionWindow.static: true
*ModelDefinitionWindow.gbldecl: /*\
   modulo ModelDefinitionWindow.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)ModelDefinitionWindow.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
\
#include "topsim.h"\
#include "lg1_topsim.h"\
#include "questionMsgDb.h"\
\
extern SIMULATORE *simulatore;
*ModelDefinitionWindow.ispecdecl: int tipo_modello;\
char OSS[20];\
char host_name[STRLONG];\
MODELLO *localtask;\
swidget selection_wid;\

*ModelDefinitionWindow.ispeclist: tipo_modello, OSS, host_name, localtask, selection_wid
*ModelDefinitionWindow.ispeclist.tipo_modello: "int", "%tipo_modello%"
*ModelDefinitionWindow.ispeclist.OSS: "unsigned char", "%OSS%[20]"
*ModelDefinitionWindow.ispeclist.host_name: "unsigned char", "%host_name%[256]"
*ModelDefinitionWindow.ispeclist.localtask: "MODELLO", "*%localtask%"
*ModelDefinitionWindow.ispeclist.selection_wid: "swidget", "%selection_wid%"
*ModelDefinitionWindow.funcdecl: swidget create_ModelDefinitionWindow(MODELLO *task,int tipo_operaz)\

*ModelDefinitionWindow.funcname: create_ModelDefinitionWindow
*ModelDefinitionWindow.funcdef: "swidget", "<create_ModelDefinitionWindow>(%)"
*ModelDefinitionWindow.argdecl: MODELLO *task;\
int tipo_operaz;
*ModelDefinitionWindow.arglist: task, tipo_operaz
*ModelDefinitionWindow.arglist.task: "MODELLO", "*%task%"
*ModelDefinitionWindow.arglist.tipo_operaz: "int", "%tipo_operaz%"
*ModelDefinitionWindow.icode: selection_wid = NULL;\
if( tipo_operaz == ADDTASK )\
{\
   tipo_modello = 1; /*(PROCESSO)*/\
   strcpy(OSS,getenv("OS"));\
   gethostname(host_name,MAXHOSTNAMELEN);\
}
*ModelDefinitionWindow.fcode: if( tipo_operaz == MODTASK)\
{\
   localtask = task;\
   riempi_campi(localtask);\
   set_menu(tipo_operaz,localtask);\
}\
\
return(rtrn);\

*ModelDefinitionWindow.auxdecl: void set_sel_path(char *path)\
{\
    XmTextFieldSetString(ModelPath,path);\
}\
\
read_input_data(MODELLO *modap)\
{\
   char *appo;\
\
   strcpy(modap->nome,XmTextFieldGetString(ModelName));\
\
   tomaius(modap->nome);\
   strcpy(modap->descr,XmTextFieldGetString(ModelDescription));\
   strcpy(modap->local_path,XmTextFieldGetString(ModelPath));\
   strcpy(modap->remote_path,XmTextFieldGetString(RemoteModelPath));\
   modap->activation_interval = atof(XmTextFieldGetString(ActivationInterval));\
\
\
\
   modap->tipo_task = tipo_modello;\
   strcpy(modap->host,host_name);\
   strcpy(modap->OS,OSS);\
   strcpy(modap->guest,"guest");\
\
\
  printf("nome=%s\n",modap->nome);\
  printf("descr=%s\n",modap->descr);\
  printf("local_path=%s\n",modap->local_path);\
  printf("remote_path=%s\n",modap->remote_path);\
  printf("activation_interval=%f\n",modap->activation_interval);\
  printf("tipo_task=%d\n",modap->tipo_task);\
  printf("host=%s\n",modap->host);\
  printf("OS=%s\n",modap->OS);\
\
}\
\
riempi_campi(MODELLO *mod)\
{\
   char cfloat[50];\
\
   XmTextFieldSetString(ModelName,mod->nome);\
   XmTextFieldSetString(ModelDescription,mod->descr);\
   XmTextFieldSetString(ModelPath,mod->local_path);\
   XmTextFieldSetString(RemoteModelPath,mod->remote_path);\
   XmTextFieldSetString(HostName,mod->host);\
   sprintf(cfloat,"%f",mod->activation_interval);\
   XmTextFieldSetString(ActivationInterval,cfloat);\
\
    tipo_modello = mod->tipo_task;\
\
   strcpy(OSS,mod->OS);\
\
}     \
\
\
set_menu_actual_button(swidget menuId,swidget buttonId)\
{\
   set_something( menuId,XmNmenuHistory, buttonId);\
} \
\
set_menu(int operaz,MODELLO *model)\
{\
 \
  if( operaz == MODTASK )\
  {  \
     /* setto il bottone del tipo modello */ \
     if ( model->tipo_task == PROCESSO )\
        set_menu_actual_button(ModelType,Process);\
     else if  ( model->tipo_task == REGOLAZIONE )\
        set_menu_actual_button(ModelType,Regolation);\
     else if  ( model->tipo_task == NOLEGO )\
        set_menu_actual_button(ModelType,Nolego);\
\
  }\
}
*ModelDefinitionWindow.name: ModelDefinitionWindow
*ModelDefinitionWindow.x: 182
*ModelDefinitionWindow.y: 169
*ModelDefinitionWindow.height: 491
*ModelDefinitionWindow.width: 559

*form4.class: form
*form4.parent: ModelDefinitionWindow
*form4.static: true
*form4.name: form4
*form4.resizePolicy: "resize_none"
*form4.unitType: "pixels"
*form4.x: 100
*form4.y: 100
*form4.height: 376
*form4.width: 541

*Modellabel.class: label
*Modellabel.parent: form4
*Modellabel.static: true
*Modellabel.name: Modellabel
*Modellabel.x: 80
*Modellabel.y: 0
*Modellabel.width: 360
*Modellabel.height: 30
*Modellabel.labelString: "Model Definition"
*Modellabel.leftAttachment: "attach_form"
*Modellabel.leftOffset: 5
*Modellabel.rightAttachment: "attach_form"
*Modellabel.rightOffset: 5
*Modellabel.topAttachment: "attach_form"
*Modellabel.topOffset: 10
*Modellabel.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"

*separatorGadget1.class: separatorGadget
*separatorGadget1.parent: form4
*separatorGadget1.static: true
*separatorGadget1.name: separatorGadget1
*separatorGadget1.x: 10
*separatorGadget1.y: 30
*separatorGadget1.width: 100
*separatorGadget1.height: 3
*separatorGadget1.topAttachment: "attach_widget"
*separatorGadget1.topOffset: 2
*separatorGadget1.topWidget: "Modellabel"
*separatorGadget1.rightAttachment: "attach_form"
*separatorGadget1.rightOffset: 0
*separatorGadget1.leftAttachment: "attach_form"
*separatorGadget1.leftOffset: 0

*LModelName.class: label
*LModelName.parent: form4
*LModelName.static: true
*LModelName.name: LModelName
*LModelName.x: 40
*LModelName.y: 120
*LModelName.width: 80
*LModelName.height: 30
*LModelName.labelString: "Model Name:"
*LModelName.alignment: "alignment_beginning"

*LModelDescription.class: label
*LModelDescription.parent: form4
*LModelDescription.static: true
*LModelDescription.name: LModelDescription
*LModelDescription.x: 40
*LModelDescription.y: 180
*LModelDescription.width: 80
*LModelDescription.height: 30
*LModelDescription.labelString: "Description:"
*LModelDescription.alignment: "alignment_beginning"

*ModelType.class: rowColumn
*ModelType.parent: form4
*ModelType.static: true
*ModelType.name: ModelType
*ModelType.rowColumnType: "menu_option"
*ModelType.subMenuId: "PModelType"
*ModelType.x: 180
*ModelType.y: 230

*PModelType.class: rowColumn
*PModelType.parent: ModelType
*PModelType.static: true
*PModelType.name: PModelType
*PModelType.rowColumnType: "menu_pulldown"

*Process.class: pushButton
*Process.parent: PModelType
*Process.static: true
*Process.name: Process
*Process.labelString: "Process"
*Process.activateCallback: tipo_modello = PROCESSO;\


*Regolation.class: pushButton
*Regolation.parent: PModelType
*Regolation.static: true
*Regolation.name: Regolation
*Regolation.labelString: "Regolation"
*Regolation.activateCallback: tipo_modello = REGOLAZIONE;

*Nolego.class: pushButton
*Nolego.parent: PModelType
*Nolego.static: true
*Nolego.name: Nolego
*Nolego.labelString: "Not LEGO"
*Nolego.activateCallback: tipo_modello = NOLEGO;

*MOS.class: rowColumn
*MOS.parent: form4
*MOS.static: true
*MOS.name: MOS
*MOS.rowColumnType: "menu_option"
*MOS.subMenuId: "POS"
*MOS.x: 390
*MOS.y: 280

*POS.class: rowColumn
*POS.parent: MOS
*POS.static: true
*POS.name: POS
*POS.rowColumnType: "menu_pulldown"

*DefOS.class: pushButton
*DefOS.parent: POS
*DefOS.static: true
*DefOS.name: DefOS
*DefOS.labelString: "Default"
*DefOS.activateCallback: strcpy(OSS,getenv("OS"));\


*OSAIX.class: pushButton
*OSAIX.parent: POS
*OSAIX.static: true
*OSAIX.name: OSAIX
*OSAIX.labelString: "AIX"
*OSAIX.activateCallback: strcpy(OSS,"AIX");

*OSVMS.class: pushButton
*OSVMS.parent: POS
*OSVMS.static: true
*OSVMS.name: OSVMS
*OSVMS.labelString: "VMS"
*OSVMS.activateCallback: strcpy(OSS,"VMS");

*OSOSF1.class: pushButton
*OSOSF1.parent: POS
*OSOSF1.static: true
*OSOSF1.name: OSOSF1
*OSOSF1.labelString: "OSF1"
*OSOSF1.activateCallback: strcpy(OSS,"OSF1");

*LActivationInterval.class: label
*LActivationInterval.parent: form4
*LActivationInterval.static: true
*LActivationInterval.name: LActivationInterval
*LActivationInterval.x: 40
*LActivationInterval.y: 380
*LActivationInterval.width: 130
*LActivationInterval.height: 30
*LActivationInterval.labelString: "Activation Interval:"
*LActivationInterval.alignment: "alignment_beginning"

*pushButton1.class: pushButton
*pushButton1.parent: form4
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 60
*pushButton1.y: 431
*pushButton1.width: 90
*pushButton1.height: 30
*pushButton1.labelString: "Ok"
*pushButton1.leftAttachment: "attach_form"
*pushButton1.leftOffset: 60
*pushButton1.topAttachment: "attach_widget"
*pushButton1.topOffset: 30
*pushButton1.topWidget: "LActivationInterval"
*pushButton1.activateCallback: {\
extern Boolean simulator_changed;\
extern int add_task();\
extern swidget ModelDefinitionInterface;\
extern int check_delta_time();\
extern void set_lista_bl();\
MODELLO qtask;\
swidget wid;\
extern swidget create_messageDialog();\
extern swidget create_msgToUser(); \
Boolean tempi;\
\
if( tipo_operaz == ADDTASK )\
{\
   read_input_data(&qtask);\
\
\
   if( add_task(&qtask) != TRUE )\
   {\
      wid = create_messageDialog(ModelDefinitionWindow,ADDTASK);\
      UxPopupInterface(wid,no_grab); \
   }\
   else\
   {\
      tempi = check_delta_time();\
      if( !tempi )\
         create_msgToUser(0,"WARNING Input Data ACTIVATION INTERVAL Not Correct"); \
      simulator_changed=True;\
      ModelDefinitionInterface = NULL;\
\
      UxDestroyInterface(ModelDefinitionWindow);\
   }\
}\
else\
{\
   read_input_data(localtask);\
\
   tempi = check_delta_time();\
   if( !tempi )\
      create_msgToUser(0,"WARNING Input Data ACTIVATION INTERVAL Not Correct");\
\
   simulator_changed=True;\
   ModelDefinitionInterface = NULL;\
\
   set_listbl(simulatore);\
\
   UxDestroyInterface(ModelDefinitionWindow);\
}\
}

*pushButton2.class: pushButton
*pushButton2.parent: form4
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 409
*pushButton2.y: 431
*pushButton2.width: 90
*pushButton2.height: 30
*pushButton2.labelString: "Cancel"
*pushButton2.topAttachment: "attach_widget"
*pushButton2.topWidget: "LActivationInterval"
*pushButton2.topOffset: 30
*pushButton2.rightAttachment: "attach_form"
*pushButton2.rightOffset: 60
*pushButton2.activateCallback: {\
extern swidget ModelDefinitionInterface;\
\
ModelDefinitionInterface = NULL;\
\
UxDestroyInterface( ModelDefinitionWindow );\
}

*ModelName.class: textField
*ModelName.parent: form4
*ModelName.static: true
*ModelName.name: ModelName
*ModelName.x: 190
*ModelName.y: 120
*ModelName.width: 167
*ModelName.height: 30
*ModelName.editable: "false"

*ModelDescription.class: textField
*ModelDescription.parent: form4
*ModelDescription.static: true
*ModelDescription.name: ModelDescription
*ModelDescription.x: 190
*ModelDescription.y: 180
*ModelDescription.width: 342
*ModelDescription.height: 30

*modelPath.class: pushButton
*modelPath.parent: form4
*modelPath.static: true
*modelPath.name: modelPath
*modelPath.x: 30
*modelPath.y: 60
*modelPath.width: 124
*modelPath.height: 31
*modelPath.labelString: "Local Path"
*modelPath.activateCallback: {\
{\
   extern swidget create_ModelSelection();\
\
   selection_wid = create_ModelSelection(XtParent(UxWidget));\
   UxPopupInterface(selection_wid,no_grab);\
}\
}

*ModelPath.class: textField
*ModelPath.parent: form4
*ModelPath.static: true
*ModelPath.name: ModelPath
*ModelPath.x: 190
*ModelPath.y: 60
*ModelPath.width: 341
*ModelPath.height: 34

*RemoteModelPath.class: textField
*RemoteModelPath.parent: form4
*RemoteModelPath.static: true
*RemoteModelPath.name: RemoteModelPath
*RemoteModelPath.x: 190
*RemoteModelPath.y: 330
*RemoteModelPath.width: 340
*RemoteModelPath.height: 30

*ActivationInterval.class: textField
*ActivationInterval.parent: form4
*ActivationInterval.static: true
*ActivationInterval.name: ActivationInterval
*ActivationInterval.x: 190
*ActivationInterval.y: 380
*ActivationInterval.width: 147
*ActivationInterval.height: 30

*LActivationInterval1.class: label
*LActivationInterval1.parent: form4
*LActivationInterval1.static: true
*LActivationInterval1.name: LActivationInterval1
*LActivationInterval1.x: 40
*LActivationInterval1.y: 330
*LActivationInterval1.width: 90
*LActivationInterval1.height: 30
*LActivationInterval1.labelString: "Remote Path:"
*LActivationInterval1.alignment: "alignment_beginning"

*LModelType.class: label
*LModelType.parent: form4
*LModelType.static: true
*LModelType.name: LModelType
*LModelType.x: 40
*LModelType.y: 230
*LModelType.width: 79
*LModelType.height: 35
*LModelType.labelString: "Model Type:"
*LModelType.alignment: "alignment_beginning"

*LHostName.class: label
*LHostName.parent: form4
*LHostName.static: true
*LHostName.name: LHostName
*LHostName.x: 40
*LHostName.y: 280
*LHostName.width: 80
*LHostName.height: 30
*LHostName.labelString: "Host Name:"
*LHostName.alignment: "alignment_beginning"

*LOS.class: label
*LOS.parent: form4
*LOS.static: true
*LOS.name: LOS
*LOS.x: 350
*LOS.y: 280
*LOS.width: 30
*LOS.height: 30
*LOS.labelString: "OS:"
*LOS.alignment: "alignment_beginning"

*HostName.class: textField
*HostName.parent: form4
*HostName.static: true
*HostName.name: HostName
*HostName.x: 190
*HostName.y: 280
*HostName.width: 140
*HostName.height: 30

