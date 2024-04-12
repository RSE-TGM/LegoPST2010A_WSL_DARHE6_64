! UIMX ascii 2.5 key: 7387                                                      

*sessionName.class: formDialog
*sessionName.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include "parametri.h"\
#include "messaggi.h"\
\
extern swidget topLevelShell1;\
extern swidget masterMenu;\
\
extern XtAppContext   UxAppContext;\
char cbdata[20];\
static int risposta = 0;
*sessionName.ispecdecl:
*sessionName.funcdecl: swidget create_sessionName(tit)\
char *tit;
*sessionName.funcname: create_sessionName
*sessionName.funcdef: "swidget", "<create_sessionName>(%)"
*sessionName.argdecl: unsigned char *tit;
*sessionName.arglist: tit
*sessionName.arglist.tit: "unsigned char", "*%tit%"
*sessionName.icode: printf ("creazione session Name\n");\

*sessionName.fcode: UxPopupInterface (rtrn, no_grab);\
while (risposta == 0)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
printf ("chiusura sessionName\n");\
risposta = 0;\
strcpy (tit, cbdata);\
\
return(rtrn);\

*sessionName.auxdecl:
*sessionName.name.source: public
*sessionName.static: false
*sessionName.name: sessionName
*sessionName.parent: NO_PARENT
*sessionName.parentExpression: masterMenu
*sessionName.defaultShell: topLevelShell
*sessionName.unitType: "pixels"
*sessionName.x: 379
*sessionName.y: 267
*sessionName.width: 460
*sessionName.height: 225
*sessionName.dialogStyle: "dialog_primary_application_modal"
*sessionName.defaultButton: "sessionNameSavepb"

*form5.class: form
*form5.static: true
*form5.name: form5
*form5.parent: sessionName
*form5.resizePolicy: "resize_none"
*form5.x: 16
*form5.y: 108
*form5.width: 750
*form5.height: 75
*form5.bottomAttachment: "attach_form"
*form5.leftOffset: 0
*form5.rightAttachment: "attach_form"
*form5.leftAttachment: "attach_form"

*frame7.class: frame
*frame7.static: true
*frame7.name: frame7
*frame7.parent: form5
*frame7.x: 10
*frame7.y: 405
*frame7.width: 795
*frame7.height: 50
*frame7.bottomAttachment: "attach_form"
*frame7.leftOffset: 0
*frame7.rightAttachment: "attach_form"
*frame7.topOffset: 0
*frame7.leftAttachment: "attach_form"
*frame7.topAttachment: "attach_form"

*form6.class: form
*form6.static: true
*form6.name: form6
*form6.parent: frame7
*form6.resizePolicy: "resize_none"
*form6.x: 0
*form6.y: 0
*form6.width: 745
*form6.height: 72
*form6.defaultButton: "sessionNameSavepb"

*sessionNameQuitpb.class: pushButton
*sessionNameQuitpb.static: true
*sessionNameQuitpb.name: sessionNameQuitpb
*sessionNameQuitpb.parent: form6
*sessionNameQuitpb.x: 493
*sessionNameQuitpb.y: 35
*sessionNameQuitpb.width: 202
*sessionNameQuitpb.height: 30
*sessionNameQuitpb.labelString: "QUIT"
*sessionNameQuitpb.bottomAttachment: "attach_form"
*sessionNameQuitpb.leftAttachment: "attach_self"
*sessionNameQuitpb.rightAttachment: "attach_form"
*sessionNameQuitpb.bottomOffset: 15
*sessionNameQuitpb.rightOffset: 20
*sessionNameQuitpb.leftPosition: 0
*sessionNameQuitpb.leftOffset: 100
*sessionNameQuitpb.topAttachment: "attach_form"
*sessionNameQuitpb.topOffset: 15
*sessionNameQuitpb.activateCallback: {\
   fprintf (stderr,"quit option\n");\
   risposta = 2;\
   /* mantiene il titolo precedente */\
   strcpy (cbdata, tit);\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
\
}
*sessionNameQuitpb.activateCallbackClientData: UxGetWidget(sessionName)

*sessionNameSavepb.class: pushButton
*sessionNameSavepb.static: true
*sessionNameSavepb.name: sessionNameSavepb
*sessionNameSavepb.parent: form6
*sessionNameSavepb.x: 30
*sessionNameSavepb.y: 405
*sessionNameSavepb.width: 205
*sessionNameSavepb.height: 30
*sessionNameSavepb.labelString: "SAVE"
*sessionNameSavepb.bottomAttachment: "attach_form"
*sessionNameSavepb.bottomOffset: 15
*sessionNameSavepb.leftOffset: 20
*sessionNameSavepb.rightAttachment: "attach_position"
*sessionNameSavepb.rightOffset: 0
*sessionNameSavepb.leftAttachment: "attach_form"
*sessionNameSavepb.topAttachment: "attach_form"
*sessionNameSavepb.topOffset: 15
*sessionNameSavepb.activateCallback: {\
   char *entry;\
   char commento[MAX_TITLE_LUN];\
  \
   fprintf (stderr,"save session name\n");\
   entry = XmTextGetString (UxGetWidget(sessionTitleEntrytext));\
   strncpy (commento, entry, MAX_TITLE_LUN);\
   commento[MAX_TITLE_LUN-1] = '\0';\
   XtFree (entry);\
   printf ("commento = :%s:\n",commento);\
   strcpy (cbdata, commento);\
   risposta = 1; /* sblocca il loop */\
  \
\
}
*sessionNameSavepb.activateCallbackClientData: (XtPointer) cbdata
*sessionNameSavepb.rightPosition: 30

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: sessionName
*label2.x: 0
*label2.y: 0
*label2.width: 460
*label2.height: 40
*label2.rightAttachment: "attach_form"
*label2.leftAttachment: "attach_form"
*label2.alignment: "alignment_center"
*label2.labelString: NEW_SESSION_NAME

*form8.class: form
*form8.static: true
*form8.name: form8
*form8.parent: sessionName
*form8.resizePolicy: "resize_none"
*form8.x: 20
*form8.y: 45
*form8.width: 540
*form8.height: 80
*form8.leftOffset: 0
*form8.rightAttachment: "attach_form"
*form8.leftAttachment: "attach_form"
*form8.topAttachment: "attach_widget"
*form8.topOffset: 0
*form8.topWidget: "label2"

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: form8
*label3.x: 0
*label3.y: 20
*label3.width: 110
*label3.height: 37
*label3.labelString: "Title:"
*label3.rightAttachment: "attach_position"
*label3.rightPosition: 20
*label3.leftAttachment: "attach_form"

*sessionTitleEntrytext.class: textField
*sessionTitleEntrytext.static: true
*sessionTitleEntrytext.name: sessionTitleEntrytext
*sessionTitleEntrytext.parent: form8
*sessionTitleEntrytext.x: 90
*sessionTitleEntrytext.y: 25
*sessionTitleEntrytext.width: 445
*sessionTitleEntrytext.height: 35
*sessionTitleEntrytext.rightAttachment: "attach_form"
*sessionTitleEntrytext.leftAttachment: "attach_widget"
*sessionTitleEntrytext.leftWidget: "label3"
*sessionTitleEntrytext.rightOffset: 20
*sessionTitleEntrytext.text: tit ? tit : " "

