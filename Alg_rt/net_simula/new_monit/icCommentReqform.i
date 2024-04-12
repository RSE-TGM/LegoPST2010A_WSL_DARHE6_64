! UIMX ascii 2.8 key: 5469                                                      

*icCommentReqform.class: formDialog
*icCommentReqform.gbldecl: #include <stdio.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "bistrutt.h"\
#include "messaggi.h"\
extern SNTAB *snap_header;\
extern swidget initialCondition;\

*icCommentReqform.ispecdecl:
*icCommentReqform.funcdecl: swidget create_icCommentReqform(ic_select, prevComment)\
int ic_select;\
char *prevComment;   /* commento originale */
*icCommentReqform.funcname: create_icCommentReqform
*icCommentReqform.funcdef: "swidget", "<create_icCommentReqform>(%)"
*icCommentReqform.argdecl: int ic_select;\
char *prevComment;
*icCommentReqform.arglist: ic_select, prevComment
*icCommentReqform.arglist.ic_select: "int", "%ic_select%"
*icCommentReqform.arglist.prevComment: "char", "*%prevComment%"
*icCommentReqform.icode:
*icCommentReqform.fcode: fprintf (stderr,"prevComm [%s]\n",prevComment);\
write_txt (icCommentText, prevComment);\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*icCommentReqform.auxdecl:
*icCommentReqform.name.source: public
*icCommentReqform.static: false
*icCommentReqform.name: icCommentReqform
*icCommentReqform.parent: NO_PARENT
*icCommentReqform.parentExpression: initialCondition
*icCommentReqform.defaultShell: topLevelShell
*icCommentReqform.unitType: "pixels"
*icCommentReqform.x: 685
*icCommentReqform.y: 65
*icCommentReqform.width: 470
*icCommentReqform.height: 205
*icCommentReqform.dialogStyle: "dialog_primary_application_modal"
*icCommentReqform.defaultButton: "icCommentOkpb"

*frame4.class: frame
*frame4.static: true
*frame4.name: frame4
*frame4.parent: icCommentReqform
*frame4.x: 0
*frame4.y: 5
*frame4.width: 470
*frame4.height: 60
*frame4.bottomAttachment: "attach_form"
*frame4.rightAttachment: "attach_form"
*frame4.leftAttachment: "attach_form"

*form9.class: form
*form9.static: true
*form9.name: form9
*form9.parent: frame4
*form9.resizePolicy: "resize_none"
*form9.x: 15
*form9.y: 20
*form9.width: 650
*form9.height: 60

*icCommantQuitpb.class: pushButton
*icCommantQuitpb.static: true
*icCommantQuitpb.name: icCommantQuitpb
*icCommantQuitpb.parent: form9
*icCommantQuitpb.x: 350
*icCommantQuitpb.y: 10
*icCommantQuitpb.width: 100
*icCommantQuitpb.height: 40
*icCommantQuitpb.labelString: "QUIT"
*icCommantQuitpb.bottomAttachment: "attach_form"
*icCommantQuitpb.leftAttachment: "attach_position"
*icCommantQuitpb.rightAttachment: "attach_form"
*icCommantQuitpb.rightOffset: 20
*icCommantQuitpb.topAttachment: "attach_form"
*icCommantQuitpb.topOffset: 10
*icCommantQuitpb.bottomOffset: 10
*icCommantQuitpb.activateCallback: {\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*icCommantQuitpb.leftPosition: 70
*icCommantQuitpb.activateCallbackClientData: UxGetWidget(icCommentReqform)

*icCommentOkpb.class: pushButton
*icCommentOkpb.static: true
*icCommentOkpb.name: icCommentOkpb
*icCommentOkpb.parent: form9
*icCommentOkpb.x: 20
*icCommentOkpb.y: 15
*icCommentOkpb.width: 100
*icCommentOkpb.height: 52
*icCommentOkpb.labelString: "SAVE"
*icCommentOkpb.bottomAttachment: "attach_form"
*icCommentOkpb.bottomOffset: 10
*icCommentOkpb.rightAttachment: "attach_position"
*icCommentOkpb.rightPosition: 30
*icCommentOkpb.rightOffset: 0
*icCommentOkpb.leftAttachment: "attach_form"
*icCommentOkpb.leftOffset: 20
*icCommentOkpb.topAttachment: "attach_form"
*icCommentOkpb.topOffset: 10
*icCommentOkpb.sensitive: "true"
*icCommentOkpb.activateCallback: {\
#ifndef DESIGN_TIME\
   char *entry;\
   char commento[100];\
\
   entry = XmTextGetString (UxGetWidget(icCommentText));\
   strncpy (commento, entry, MAX_LUN_COMMENTO);\
   commento[MAX_LUN_COMMENTO] = '\0';\
   XtFree (entry);\
   printf ("commento = :%s:\n",commento);\
  \
   esegui_snap(ic_select,commento); \
  \
   UxDestroyInterface(icCommentReqform);\
#endif\
}

*icCommentText.class: textField
*icCommentText.static: true
*icCommentText.name: icCommentText
*icCommentText.parent: icCommentReqform
*icCommentText.x: 20
*icCommentText.y: 50
*icCommentText.width: 460
*icCommentText.height: 40
*icCommentText.rightAttachment: "attach_form"
*icCommentText.rightOffset: 20
*icCommentText.leftAttachment: "attach_form"
*icCommentText.leftOffset: 20
*icCommentText.maxLength: MAX_LUN_COMMENTO

*icCommentTitle.class: label
*icCommentTitle.static: true
*icCommentTitle.name: icCommentTitle
*icCommentTitle.parent: icCommentReqform
*icCommentTitle.x: 0
*icCommentTitle.y: 0
*icCommentTitle.width: 473
*icCommentTitle.height: 30
*icCommentTitle.rightAttachment: "attach_form"
*icCommentTitle.leftAttachment: "attach_form"
*icCommentTitle.labelString: IC_COMMENT_REQ

