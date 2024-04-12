! UIMX ascii 2.0 key: 2082                                                      

*questionDB.class: questionDialog
*questionDB.parent: NO_PARENT
*questionDB.defaultShell: topLevelShell
*questionDB.static: false
*questionDB.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo questionDB.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)questionDB.i	2.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
#include <stdio.h>\
#include "question_type.h"\
\
\
QUESTION question;\
extern int graphics_on;
*questionDB.ispecdecl:
*questionDB.funcdecl: swidget create_questionDB()\

*questionDB.funcname: create_questionDB
*questionDB.funcdef: "swidget", "<create_questionDB>(%)"
*questionDB.icode: Widget wid;
*questionDB.fcode: wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );\
XtUnmanageChild( wid );\
\
return(rtrn);\
\

*questionDB.auxdecl: questionDB_activate ( messaggio )\
char *messaggio;\
{\
\
   extern swidget questionDB;\
   extern swidget lg1MainWindow;\
\
   \
   switch ( question ) {\
\
     case QST_USCITA:\
     case QST_DEL_BL: \
                      break;\
                    \
     case QST_SALVA_MOD:\
                      UxPutOkLabelString( questionDB, "Yes" );\
                      UxPutCancelLabelString( questionDB, "No" );\
                      break;\
   }\
\
   UxPutMessageString(questionDB,messaggio);\
   UxPopupInterface(questionDB,no_grab);\
/*\
   set_win_cursors( "busy" );\
*/\
}
*questionDB.name: questionDB
*questionDB.dialogType: "dialog_question"
*questionDB.unitType: "pixels"
*questionDB.x: 965
*questionDB.y: 570
*questionDB.width: 275
*questionDB.height: 190
*questionDB.okCallback: {\
extern swidget lg1MainWindow;\
extern int     changes_in_F01;\
extern int     write_f01();\
                  \
printf("Ok Callback questionDB\n");\
\
switch ( question ) {\
\
   case QST_USCITA: \
                    printf(" USCITA\n");            \
                    exit(0);\
\
   case QST_DEL_BL:\
                    printf(" QST_DEL_BL\n");            \
                    bl_del_qst_cb();\
                    break;\
                    \
   case QST_DEL_CONN:\
                    printf(" QST_DEL_MOD\n");            \
                    del_conn_qst_cb();\
                    break;\
\
   case QST_SALVA_MOD:      \
                    printf(" QST_SALVA_MOD\n");            \
                    printf(" Su conferma scrivo il nuovo F01.dat \n");\
                    write_f01();\
                    if(graphics_on == True)\
                       Isalva_grafica();\
                    break;\
}\
\
\
\
}
*questionDB.dialogStyle: "dialog_full_application_modal"
*questionDB.minimizeButtons: "false"
*questionDB.noResize: "true"
*questionDB.cancelCallback: {\
extern swidget lg1MainWindow;\
extern int     changes_in_F01;\
\
\
switch ( question ) {\
\
   case QST_USCITA: \
   case QST_SALVA_MOD:\
   case QST_DEL_BL:\
                    break;\
}\
\
\
\
}
*questionDB.unmapCallback: {\
extern char nome_modello[];\
extern char path_legocad[];\
extern int write_f01();\
\
/**\
reset_win_cursors ();\
**/\
                    \
printf("Unmap Callback questionDB\n");\
\
switch ( question ) {\
\
   case QST_USCITA:\
   case QST_DEL_BL: \
                    printf("QST_USCITA oppure QST_DEL_BL\n");\
                    break;\
                    \
   case QST_SALVA_MOD: \
                    printf("QST_SALVA_MOD\n");\
\
                    write_f01();\
                    printf("Inizializzo Il Modello %s\n",nome_modello);\
\
                    init_modello(nome_modello, path_legocad);\
                    printf("Set Bl_list\n");\
                    set_bl_list();\
\
                    set_model_name();\
\
                    printf("QST_SALVA_MOD ended /n");\
                    \
/*\
                    UxPutOkLabelString( UxThisWidget, "Ok" );\
                    UxPutCancelLabelString( UxThisWidget, "Cancel" );\
*/\
                    break;\
}\
\
\
}

