! UIMX ascii 2.0 key: 4908                                                      

*ModelDefinitionWindow.class: topLevelShell
*ModelDefinitionWindow.parent: NO_PARENT
*ModelDefinitionWindow.static: true
*ModelDefinitionWindow.gbldecl: #include <stdio.h>\
\

*ModelDefinitionWindow.ispecdecl:
*ModelDefinitionWindow.funcdecl: swidget create_ModelDefinitionWindow()\

*ModelDefinitionWindow.funcname: create_ModelDefinitionWindow
*ModelDefinitionWindow.icode:
*ModelDefinitionWindow.fcode: return(rtrn);\

*ModelDefinitionWindow.auxdecl:
*ModelDefinitionWindow.name: ModelDefinitionWindow
*ModelDefinitionWindow.x: 210
*ModelDefinitionWindow.y: 200
*ModelDefinitionWindow.height: 376
*ModelDefinitionWindow.width: 541

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
*LModelName.x: 10
*LModelName.y: 65
*LModelName.width: 130
*LModelName.height: 30
*LModelName.labelString: "Model Name:"
*LModelName.topAttachment: "attach_widget"
*LModelName.topOffset: 20
*LModelName.topWidget: "separatorGadget1"
*LModelName.leftAttachment: "attach_form"
*LModelName.leftOffset: 20
*LModelName.alignment: "alignment_beginning"

*LModelDescription.class: label
*LModelDescription.parent: form4
*LModelDescription.static: true
*LModelDescription.name: LModelDescription
*LModelDescription.x: 10
*LModelDescription.y: 105
*LModelDescription.width: 130
*LModelDescription.height: 30
*LModelDescription.labelString: "Description:"
*LModelDescription.leftAttachment: "attach_form"
*LModelDescription.leftOffset: 20
*LModelDescription.topAttachment: "attach_widget"
*LModelDescription.topOffset: 10
*LModelDescription.topWidget: "LModelName"
*LModelDescription.alignment: "alignment_beginning"

*ModelType.class: rowColumn
*ModelType.parent: form4
*ModelType.static: true
*ModelType.name: ModelType
*ModelType.rowColumnType: "menu_option"
*ModelType.subMenuId: "PModelType"
*ModelType.rightAttachment: "attach_none"
*ModelType.rightOffset: 0
*ModelType.leftAttachment: "attach_form"
*ModelType.leftOffset: 150
*ModelType.topAttachment: "attach_widget"
*ModelType.topOffset: 10
*ModelType.topWidget: "LModelDescription"

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

*Regolation.class: pushButton
*Regolation.parent: PModelType
*Regolation.static: true
*Regolation.name: Regolation
*Regolation.labelString: "Regolation"

*HostName.class: rowColumn
*HostName.parent: form4
*HostName.static: true
*HostName.name: HostName
*HostName.rowColumnType: "menu_option"
*HostName.subMenuId: "PHostName"
*HostName.leftAttachment: "attach_widget"
*HostName.leftOffset: 10
*HostName.leftWidget: "ModelType"
*HostName.topAttachment: "attach_widget"
*HostName.topWidget: "LModelDescription"
*HostName.topOffset: 10

*PHostName.class: rowColumn
*PHostName.parent: HostName
*PHostName.static: true
*PHostName.name: PHostName
*PHostName.rowColumnType: "menu_pulldown"

*Local.class: pushButton
*Local.parent: PHostName
*Local.static: true
*Local.name: Local
*Local.labelString: "Local"

*Host.class: pushButton
*Host.parent: PHostName
*Host.static: true
*Host.name: Host
*Host.labelString: "HostNamexxx"

*OS.class: rowColumn
*OS.parent: form4
*OS.static: true
*OS.name: OS
*OS.rowColumnType: "menu_option"
*OS.subMenuId: "POS"
*OS.leftAttachment: "attach_widget"
*OS.leftOffset: 10
*OS.leftWidget: "HostName"
*OS.topAttachment: "attach_widget"
*OS.topOffset: 10
*OS.topWidget: "LModelDescription"
*OS.rightAttachment: "attach_none"

*POS.class: rowColumn
*POS.parent: OS
*POS.static: true
*POS.name: POS
*POS.rowColumnType: "menu_pulldown"

*DefOS.class: pushButton
*DefOS.parent: POS
*DefOS.static: true
*DefOS.name: DefOS
*DefOS.labelString: "OS"

*OSAIX.class: pushButton
*OSAIX.parent: POS
*OSAIX.static: true
*OSAIX.name: OSAIX
*OSAIX.labelString: "AIX"

*OSVMS.class: pushButton
*OSVMS.parent: POS
*OSVMS.static: true
*OSVMS.name: OSVMS
*OSVMS.labelString: "VMS"

*OSOSF1.class: pushButton
*OSOSF1.parent: POS
*OSOSF1.static: true
*OSOSF1.name: OSOSF1
*OSOSF1.labelString: "Osf1"

*LModelPath.class: label
*LModelPath.parent: form4
*LModelPath.static: true
*LModelPath.name: LModelPath
*LModelPath.x: 10
*LModelPath.y: 183
*LModelPath.width: 130
*LModelPath.height: 27
*LModelPath.leftAttachment: "attach_form"
*LModelPath.leftOffset: 20
*LModelPath.topAttachment: "attach_widget"
*LModelPath.topOffset: 13
*LModelPath.topWidget: "ModelType"
*LModelPath.labelString: "Model Path:"
*LModelPath.alignment: "alignment_beginning"

*LRemoteModelPath.class: label
*LRemoteModelPath.parent: form4
*LRemoteModelPath.static: true
*LRemoteModelPath.name: LRemoteModelPath
*LRemoteModelPath.x: 10
*LRemoteModelPath.y: 220
*LRemoteModelPath.width: 130
*LRemoteModelPath.height: 20
*LRemoteModelPath.labelString: "Remote Model Path:"
*LRemoteModelPath.leftAttachment: "attach_form"
*LRemoteModelPath.leftOffset: 20
*LRemoteModelPath.topAttachment: "attach_widget"
*LRemoteModelPath.topOffset: 20
*LRemoteModelPath.topWidget: "LModelPath"
*LRemoteModelPath.alignment: "alignment_beginning"

*LActivationInterval.class: label
*LActivationInterval.parent: form4
*LActivationInterval.static: true
*LActivationInterval.name: LActivationInterval
*LActivationInterval.x: 10
*LActivationInterval.y: 250
*LActivationInterval.width: 130
*LActivationInterval.height: 30
*LActivationInterval.labelString: "Activation Interval:"
*LActivationInterval.leftAttachment: "attach_form"
*LActivationInterval.leftOffset: 20
*LActivationInterval.topAttachment: "attach_widget"
*LActivationInterval.topWidget: "LRemoteModelPath"
*LActivationInterval.topOffset: 13
*LActivationInterval.alignment: "alignment_beginning"

*pushButton1.class: pushButton
*pushButton1.parent: form4
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 60
*pushButton1.y: 300
*pushButton1.width: 90
*pushButton1.height: 30
*pushButton1.labelString: "Ok"
*pushButton1.leftAttachment: "attach_form"
*pushButton1.leftOffset: 60
*pushButton1.topAttachment: "attach_widget"
*pushButton1.topOffset: 30
*pushButton1.topWidget: "LActivationInterval"
*pushButton1.activateCallback: {\
UxDestroyInterface(ModelDefinitionWindow);\
}

*pushButton2.class: pushButton
*pushButton2.parent: form4
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 270
*pushButton2.y: 300
*pushButton2.width: 90
*pushButton2.height: 30
*pushButton2.labelString: "Cancel"
*pushButton2.topAttachment: "attach_widget"
*pushButton2.topWidget: "LActivationInterval"
*pushButton2.topOffset: 30
*pushButton2.rightAttachment: "attach_form"
*pushButton2.rightOffset: 60
*pushButton2.activateCallback: {\
UxDestroyInterface( ModelDefinitionWindow );\
}

*ModelName.class: textField
*ModelName.parent: form4
*ModelName.static: true
*ModelName.name: ModelName
*ModelName.x: 150
*ModelName.y: 50
*ModelName.width: 170
*ModelName.height: 30
*ModelName.topAttachment: "attach_widget"
*ModelName.topOffset: 20
*ModelName.topWidget: "separatorGadget1"
*ModelName.leftAttachment: "attach_widget"
*ModelName.leftOffset: 10
*ModelName.leftWidget: "LModelName"

*ModelDescription.class: textField
*ModelDescription.parent: form4
*ModelDescription.static: true
*ModelDescription.name: ModelDescription
*ModelDescription.x: 150
*ModelDescription.y: 100
*ModelDescription.width: 310
*ModelDescription.height: 30
*ModelDescription.leftAttachment: "attach_widget"
*ModelDescription.leftOffset: 10
*ModelDescription.leftWidget: "LModelDescription"
*ModelDescription.topAttachment: "attach_widget"
*ModelDescription.topOffset: 10
*ModelDescription.topWidget: "ModelName"

*ModelPath.class: textField
*ModelPath.parent: form4
*ModelPath.static: true
*ModelPath.name: ModelPath
*ModelPath.x: 160
*ModelPath.y: 183
*ModelPath.width: 260
*ModelPath.height: 30
*ModelPath.leftAttachment: "attach_widget"
*ModelPath.leftOffset: 10
*ModelPath.leftWidget: "LModelPath"
*ModelPath.topAttachment: "attach_widget"
*ModelPath.topOffset: 10
*ModelPath.topWidget: "HostName"

*RemoteModelPath.class: textField
*RemoteModelPath.parent: form4
*RemoteModelPath.static: true
*RemoteModelPath.name: RemoteModelPath
*RemoteModelPath.x: 160
*RemoteModelPath.y: 220
*RemoteModelPath.width: 260
*RemoteModelPath.height: 30
*RemoteModelPath.leftAttachment: "attach_widget"
*RemoteModelPath.leftOffset: 10
*RemoteModelPath.leftWidget: "LRemoteModelPath"
*RemoteModelPath.topAttachment: "attach_widget"
*RemoteModelPath.topOffset: 10
*RemoteModelPath.topWidget: "ModelPath"

*ActivationInterval.class: textField
*ActivationInterval.parent: form4
*ActivationInterval.static: true
*ActivationInterval.name: ActivationInterval
*ActivationInterval.x: 160
*ActivationInterval.y: 260
*ActivationInterval.width: 260
*ActivationInterval.height: 30
*ActivationInterval.leftAttachment: "attach_widget"
*ActivationInterval.leftOffset: 10
*ActivationInterval.leftWidget: "LActivationInterval"
*ActivationInterval.topAttachment: "attach_widget"
*ActivationInterval.topOffset: 10
*ActivationInterval.topWidget: "RemoteModelPath"

