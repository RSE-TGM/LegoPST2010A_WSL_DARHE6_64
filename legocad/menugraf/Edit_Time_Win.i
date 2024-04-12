! UIMX ascii 2.0 key: 9699                                                      

*Edit_Time_Win.class: form
*Edit_Time_Win.parent: NO_PARENT
*Edit_Time_Win.defaultShell: topLevelShell
*Edit_Time_Win.static: false
*Edit_Time_Win.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Edit_Time_Win.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Edit_Time_Win.i	1.10\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
#include "menu_graf.h"\
\
extern int Scelta;\

*Edit_Time_Win.ispecdecl:
*Edit_Time_Win.funcdecl: swidget create_Edit_Time_Win()\

*Edit_Time_Win.funcname: create_Edit_Time_Win
*Edit_Time_Win.funcdef: "swidget", "<create_Edit_Time_Win>(%)"
*Edit_Time_Win.icode:
*Edit_Time_Win.fcode: return(rtrn);\

*Edit_Time_Win.auxdecl:
*Edit_Time_Win.name: Edit_Time_Win
*Edit_Time_Win.resizePolicy: "resize_none"
*Edit_Time_Win.unitType: "pixels"
*Edit_Time_Win.x: 440
*Edit_Time_Win.y: 525
*Edit_Time_Win.width: 544
*Edit_Time_Win.height: 213

*Titolo_edit.class: label
*Titolo_edit.parent: Edit_Time_Win
*Titolo_edit.static: false
*Titolo_edit.name: Titolo_edit
*Titolo_edit.x: 140
*Titolo_edit.y: 5
*Titolo_edit.width: 265
*Titolo_edit.height: 40
*Titolo_edit.labelString: ""
*Titolo_edit.fontList: "-adobe-new century schoolbook-bold-r-normal--18-180-75-75-p-113-iso8859-1"
*Titolo_edit.recomputeSize: "false"

*label2.class: label
*label2.parent: Edit_Time_Win
*label2.static: true
*label2.name: label2
*label2.x: 15
*label2.y: 55
*label2.width: 110
*label2.height: 30
*label2.labelString: "Start time:"
*label2.alignment: "alignment_end"
*label2.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*label2.recomputeSize: "false"

*Edt_start_time.class: label
*Edt_start_time.parent: Edit_Time_Win
*Edt_start_time.static: false
*Edt_start_time.name: Edt_start_time
*Edt_start_time.x: 125
*Edt_start_time.y: 50
*Edt_start_time.width: 80
*Edt_start_time.height: 30
*Edt_start_time.alignment: "alignment_end"
*Edt_start_time.labelString: ""
*Edt_start_time.recomputeSize: "false"

*label4.class: label
*label4.parent: Edit_Time_Win
*label4.static: true
*label4.name: label4
*label4.x: 305
*label4.y: 55
*label4.width: 95
*label4.height: 30
*label4.labelString: "Stop time:"
*label4.alignment: "alignment_end"
*label4.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*label4.recomputeSize: "false"

*Edt_stop_time.class: label
*Edt_stop_time.parent: Edit_Time_Win
*Edt_stop_time.static: false
*Edt_stop_time.name: Edt_stop_time
*Edt_stop_time.x: 400
*Edt_stop_time.y: 50
*Edt_stop_time.width: 80
*Edt_stop_time.height: 30
*Edt_stop_time.alignment: "alignment_end"
*Edt_stop_time.labelString: ""
*Edt_stop_time.recomputeSize: "false"

*separator1.class: separator
*separator1.parent: Edit_Time_Win
*separator1.static: true
*separator1.name: separator1
*separator1.x: 260
*separator1.y: 50
*separator1.width: 25
*separator1.height: 100
*separator1.orientation: "vertical"
*separator1.separatorType: "single_dashed_line"

*Etichetta_start.class: label
*Etichetta_start.parent: Edit_Time_Win
*Etichetta_start.static: false
*Etichetta_start.name: Etichetta_start
*Etichetta_start.x: 15
*Etichetta_start.y: 105
*Etichetta_start.width: 110
*Etichetta_start.height: 30
*Etichetta_start.labelString: "New start time:"
*Etichetta_start.alignment: "alignment_end"
*Etichetta_start.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*Etichetta_start.recomputeSize: "false"

*Etichetta_stop.class: label
*Etichetta_stop.parent: Edit_Time_Win
*Etichetta_stop.static: false
*Etichetta_stop.name: Etichetta_stop
*Etichetta_stop.x: 295
*Etichetta_stop.y: 105
*Etichetta_stop.width: 105
*Etichetta_stop.height: 30
*Etichetta_stop.labelString: "New stop time:"
*Etichetta_stop.alignment: "alignment_end"
*Etichetta_stop.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*Etichetta_stop.recomputeSize: "false"

*textField_Start.class: textField
*textField_Start.parent: Edit_Time_Win
*textField_Start.static: false
*textField_Start.name: textField_Start
*textField_Start.x: 125
*textField_Start.y: 100
*textField_Start.width: 125
*textField_Start.height: 35
*textField_Start.valueChangedCallback: {\
\
}
*textField_Start.maxLength: 8

*pushButton1.class: pushButton
*pushButton1.parent: Edit_Time_Win
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 20
*pushButton1.y: 160
*pushButton1.width: 90
*pushButton1.height: 35
*pushButton1.labelString: "OK"
*pushButton1.activateCallback: {\
if (Scelta == EXTRACT_TIME) F22_extract ();\
if (Scelta == SHIFT_TIME) F22_shift ();\
}

*pushButton2.class: pushButton
*pushButton2.parent: Edit_Time_Win
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 120
*pushButton2.y: 160
*pushButton2.width: 90
*pushButton2.height: 35
*pushButton2.labelString: "CANCEL"
*pushButton2.activateCallback: UxPopdownInterface (Edit_Time_Win);

*label1.class: label
*label1.parent: Edit_Time_Win
*label1.static: true
*label1.name: label1
*label1.x: 210
*label1.y: 55
*label1.width: 45
*label1.height: 30
*label1.labelString: "sec."
*label1.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*label1.recomputeSize: "false"

*label3.class: label
*label3.parent: Edit_Time_Win
*label3.static: true
*label3.name: label3
*label3.x: 485
*label3.y: 55
*label3.width: 45
*label3.height: 30
*label3.labelString: "sec."
*label3.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"
*label3.recomputeSize: "false"

*textField_Stop.class: textField
*textField_Stop.parent: Edit_Time_Win
*textField_Stop.static: false
*textField_Stop.name: textField_Stop
*textField_Stop.x: 400
*textField_Stop.y: 100
*textField_Stop.width: 120
*textField_Stop.height: 35
*textField_Stop.valueChangedCallback: {\
\
}
*textField_Stop.sensitive: "true"
*textField_Stop.maxLength: 8

