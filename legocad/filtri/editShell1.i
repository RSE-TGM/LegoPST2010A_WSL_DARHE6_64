! UIMX ascii 2.0 key: 8029                                                      

*editShell1.class: dialogShell
*editShell1.parent: NO_PARENT
*editShell1.static: false
*editShell1.gbldecl: /*\
   modulo editShell1.i\
   tipo \
   release 2.6\
   data 3/20/95\
   reserved @(#)editShell1.i	2.6\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/MwmUtil.h>\
#include <Xm/Text.h>\
#ifndef FILTRI_H\
#include "filtri.h"\
#endif\
\
\
extern void delete_all_items();\
extern void add_items_list();\
\
extern char filedf[];                 /* filename file di editing */\
extern FILE *fpedf;                   /* file di edting */\
extern FILTRI *filtri[];              /* vettore filtri */\
extern short num_filtri;              /* numero di filtri definiti */\
\
extern swidget scrolledList1;\
extern swidget scrolledList2;
*editShell1.ispecdecl: int apro;
*editShell1.ispeclist: apro
*editShell1.ispeclist.apro: "int", "%apro%"
*editShell1.funcdecl: swidget create_editShell1()\

*editShell1.funcname: create_editShell1
*editShell1.funcdef: "swidget", "<create_editShell1>(%)"
*editShell1.icode:
*editShell1.fcode: return(rtrn);\

*editShell1.auxdecl: /*===================================================================\
|\
|  clear_field:  ripulisce la finestra di input dati\
|\
====================================================================*/\
\
int clear_field()\
{\
   char appo[MAXCHNAME+1];\
\
   strcpy(appo,"");\
   UxPutText(textField1,appo);\
   UxPutText(textField2,appo);\
   UxPutText(textField3,appo);\
   UxPutText(textField4,appo);\
   UxPutText(textField5,appo); \
   UxPutText(textField6,appo);\
   UxPutText(textField7,appo); \
   UxPutText(textField8,appo);\
   UxPutText(textField9,appo);\
   UxPutText(textField10,appo);\
   UxPutText(textField11,appo);\
\
}\
\
/*===============================================================\
|\
|   aggiorna_edit_shell: visualizza nella shell i dati di un filtro\
|\
|===============================================================*/\
\
int aggiorna_edit_shell(FILTRI *filtro)\
{\
   printf("\naggiorna edti shell con filtro ->%s\n",filtro->nome_filtro);\
\
   clear_field();\
   UxPutText(textField1,filtro->nome_filtro);\
   UxPutText(textField2,filtro->var[0]);\
   UxPutText(textField3,filtro->var[1]);\
   UxPutText(textField4,filtro->var[2]);\
   UxPutText(textField5,filtro->var[3]);\
   UxPutText(textField6,filtro->var[4]);\
   UxPutText(textField7,filtro->var[5]);\
   UxPutText(textField8,filtro->var[6]);\
   UxPutText(textField9,filtro->var[7]);\
   UxPutText(textField10,filtro->var[8]);\
   UxPutText(textField11,filtro->var[9]);\
}\
\
/*===============================================================\
|\
|   aggiorna_filtro: modifica i dati di un filtro\
|\
|===============================================================*/\
\
int aggiorna_filtro(FILTRI *filtro)\
{\
   char appo[100];\
   int i;\
\
 \
   printf("\naggiorna filtro %s \n",filtro->nome_filtro);\
   strcpy(appo,UxGetText(textField1));\
   if(strlen(appo))\
   {\
      strcpy(filtro->nome_filtro,appo);\
      filtro->num_var=0;\
    \
      strcpy(appo,UxGetText(textField2));\
      if(strlen(appo))\
      {\
         strcpy(filtro->var[0],appo);\
         filtro->num_var++;         \
      \
         strcpy(appo,UxGetText(textField3));\
         if(strlen(appo))\
         { \
            strcpy(filtro->var[1],appo);\
            filtro->num_var++;         \
      \
            strcpy(appo,UxGetText(textField4));\
            if(strlen(appo))\
            {      \
               strcpy(filtro->var[2],appo);\
               filtro->num_var++;         \
      \
               strcpy(appo,UxGetText(textField5));\
               if(strlen(appo))\
               {\
                  strcpy(filtro->var[3],appo);\
                  filtro->num_var++;         \
         \
                  strcpy(appo,UxGetText(textField6));\
                  if(strlen(appo))\
                  {\
                     strcpy(filtro->var[4],appo);\
                     filtro->num_var++;         \
      \
                     strcpy(appo,UxGetText(textField7));\
                     if(strlen(appo))\
                     {\
                        strcpy(filtro->var[5],appo);\
                        filtro->num_var++;         \
      \
                        strcpy(appo,UxGetText(textField8));\
                        if(strlen(appo))\
                        {\
                           strcpy(filtro->var[6],appo);\
                           filtro->num_var++;         \
\
                           strcpy(appo,UxGetText(textField9));\
                           if(strlen(appo))\
                           {\
                              strcpy(filtro->var[7],appo);\
                              filtro->num_var++;         \
      \
\
                              strcpy(appo,UxGetText(textField10));\
                              if(strlen(appo))\
                              {\
                                 strcpy(filtro->var[8],appo);\
                                 filtro->num_var++;         \
      \
\
                                 strcpy(appo,UxGetText(textField11));\
                                 if(strlen(appo))\
                                 {\
                                    strcpy(filtro->var[9],appo);\
                                    filtro->num_var++;         \
                                 }\
                              }\
                           }\
                        }\
                     }\
                  }\
               }\
            }\
         }\
      }\
\
      printf("ho %d filtri\n",filtro->num_var);\
   }\
\
   delete_all_items(scrolledList1);\
   delete_all_items(scrolledList2);\
   refresh_lista_nomi();\
}\
\
/*===============================================================\
|\
|   aggiungi_filtri: inserisce un nuovo  filtro nella tabella dei filtri\
|\
|===============================================================*/\
\
int aggiungi_filtro()\
{\
\
   char appo[100];\
   char *nomi[MAXFILTRI];\
   short i;\
   extern FILTRI *filtro_init();\
\
   printf("\naggiungi  filtro \n");\
\
   \
   filtri[num_filtri] = filtro_init();\
   num_filtri++;\
   aggiorna_filtro(filtri[num_filtri - 1]);\
\
\
   printf("\naggiungi  filtro \n");\
   printf("\n          filtro n.1  %s\n",filtri[num_filtri - 1]->var[0]);\
   printf("\n          filtro n.2  %s\n",filtri[num_filtri - 1]->var[1]);\
   printf("\n          filtro n.3  %s\n",filtri[num_filtri - 1]->var[2]);\
   printf("\n          filtro n.4  %s\n",filtri[num_filtri - 1]->var[3]);\
   printf("\n          filtro n.5  %s\n",filtri[num_filtri - 1]->var[4]);\
   printf("\n          filtro n.6  %s\n",filtri[num_filtri - 1]->var[5]);\
   printf("\n          filtro n.7  %s\n",filtri[num_filtri - 1]->var[6]);\
   printf("\n          filtro n.8  %s\n",filtri[num_filtri - 1]->var[7]);\
   printf("\n          filtro n.9  %s\n",filtri[num_filtri - 1]->var[8]);\
   printf("\n          filtro n.10 %s\n",filtri[num_filtri - 1]->var[9]);\
\
   for(i=0;i<num_filtri;i++)\
   {\
      nomi[i] = (char *)(malloc(sizeof(char) * MAXCHNAME));\
      strcpy(nomi[i],filtri[i]->nome_filtro);\
   }\
\
   delete_all_items(scrolledList1);\
   delete_all_items(scrolledList2);\
   add_items_list(scrolledList1,nomi,num_filtri);\
\
   \
   for(i=0;i<num_filtri;i++)\
      free(nomi[i]);\
\
   clear_field();\
\
}
*editShell1.name: editShell1
*editShell1.x: 454
*editShell1.y: 266
*editShell1.width: 360
*editShell1.height: 410
*editShell1.mwmDecorations: MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU
*editShell1.mwmFunctions: MWM_FUNC_MOVE | MWM_FUNC_CLOSE
*editShell1.allowShellResize: "true"

*form2.class: form
*form2.parent: editShell1
*form2.static: true
*form2.name: form2
*form2.resizePolicy: "resize_none"
*form2.unitType: "pixels"
*form2.x: 0
*form2.y: 10
*form2.width: 360
*form2.height: 410
*form2.dialogTitle: "Filter Edit"
*form2.dialogStyle: "dialog_primary_application_modal"
*form2.traversalOn: "true"

*textField1.class: textField
*textField1.parent: form2
*textField1.static: false
*textField1.name: textField1
*textField1.x: 130
*textField1.y: 60
*textField1.width: 140
*textField1.height: 40
*textField1.maxLength: 10

*textField2.class: textField
*textField2.parent: form2
*textField2.static: true
*textField2.name: textField2
*textField2.x: 80
*textField2.y: 150
*textField2.width: 70
*textField2.height: 40
*textField2.columns: 4
*textField2.maxLength: 4

*label1.class: label
*label1.parent: form2
*label1.static: true
*label1.name: label1
*label1.x: 20
*label1.y: 70
*label1.width: 110
*label1.height: 20
*label1.labelString: "Filter Name"

*label2.class: label
*label2.parent: form2
*label2.static: true
*label2.name: label2
*label2.x: 110
*label2.y: 120
*label2.width: 140
*label2.height: 20
*label2.labelString: "Filter"

*pushButton1.class: pushButton
*pushButton1.parent: form2
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 30
*pushButton1.y: 370
*pushButton1.width: 70
*pushButton1.height: 30
*pushButton1.labelString: "Ok"
*pushButton1.activateCallback: {\
extern int operaz;\
extern short num_filtro_selez;\
\
switch(operaz)\
{\
   case NEW_FILTRO:\
     printf("\nswitch entry NEW_FILTRO\n");\
     aggiungi_filtro();\
   break;\
   case OPEN_FILTRO:\
     printf("\nswitch entry OPEN_FILTRO\n");\
     aggiorna_filtro(filtri[num_filtro_selez]);\
   break;\
}\
\
\
}

*pushButton2.class: pushButton
*pushButton2.parent: form2
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 110
*pushButton2.y: 370
*pushButton2.width: 80
*pushButton2.height: 30
*pushButton2.labelString: "Cancel"

*textField3.class: textField
*textField3.parent: form2
*textField3.static: true
*textField3.name: textField3
*textField3.x: 250
*textField3.y: 150
*textField3.width: 70
*textField3.height: 40
*textField3.columns: 4
*textField3.maxLength: 4

*textField4.class: textField
*textField4.parent: form2
*textField4.static: true
*textField4.name: textField4
*textField4.x: 80
*textField4.y: 190
*textField4.width: 70
*textField4.height: 40
*textField4.columns: 4
*textField4.maxLength: 4

*textField5.class: textField
*textField5.parent: form2
*textField5.static: true
*textField5.name: textField5
*textField5.x: 250
*textField5.y: 190
*textField5.width: 70
*textField5.height: 40
*textField5.columns: 4
*textField5.maxLength: 4

*textField6.class: textField
*textField6.parent: form2
*textField6.static: true
*textField6.name: textField6
*textField6.x: 80
*textField6.y: 230
*textField6.width: 70
*textField6.height: 40
*textField6.columns: 5
*textField6.maxLength: 4

*textField7.class: textField
*textField7.parent: form2
*textField7.static: true
*textField7.name: textField7
*textField7.x: 250
*textField7.y: 230
*textField7.width: 70
*textField7.height: 40
*textField7.maxLength: 4

*textField8.class: textField
*textField8.parent: form2
*textField8.static: true
*textField8.name: textField8
*textField8.x: 80
*textField8.y: 270
*textField8.width: 70
*textField8.height: 40
*textField8.maxLength: 4

*textField9.class: textField
*textField9.parent: form2
*textField9.static: true
*textField9.name: textField9
*textField9.x: 250
*textField9.y: 270
*textField9.width: 70
*textField9.height: 40
*textField9.maxLength: 4

*textField10.class: textField
*textField10.parent: form2
*textField10.static: true
*textField10.name: textField10
*textField10.x: 80
*textField10.y: 310
*textField10.width: 70
*textField10.height: 40
*textField10.maxLength: 4

*textField11.class: textField
*textField11.parent: form2
*textField11.static: true
*textField11.name: textField11
*textField11.x: 250
*textField11.y: 310
*textField11.width: 70
*textField11.height: 40
*textField11.maxLength: 4

*label3.class: label
*label3.parent: form2
*label3.static: true
*label3.name: label3
*label3.x: 20
*label3.y: 160
*label3.width: 50
*label3.height: 20
*label3.labelString: "n.1"

*label4.class: label
*label4.parent: form2
*label4.static: true
*label4.name: label4
*label4.x: 190
*label4.y: 240
*label4.width: 50
*label4.height: 20
*label4.labelString: "n.6"

*label5.class: label
*label5.parent: form2
*label5.static: true
*label5.name: label5
*label5.x: 190
*label5.y: 320
*label5.width: 50
*label5.height: 20
*label5.labelString: "n.10"

*label6.class: label
*label6.parent: form2
*label6.static: true
*label6.name: label6
*label6.x: 20
*label6.y: 240
*label6.width: 50
*label6.height: 20
*label6.labelString: "n.5"

*label7.class: label
*label7.parent: form2
*label7.static: true
*label7.name: label7
*label7.x: 20
*label7.y: 280
*label7.width: 50
*label7.height: 20
*label7.labelString: "n.7"

*label8.class: label
*label8.parent: form2
*label8.static: true
*label8.name: label8
*label8.x: 20
*label8.y: 320
*label8.width: 50
*label8.height: 20
*label8.labelString: "n.9"

*label9.class: label
*label9.parent: form2
*label9.static: true
*label9.name: label9
*label9.x: 20
*label9.y: 200
*label9.width: 50
*label9.height: 20
*label9.labelString: "n.3"

*label10.class: label
*label10.parent: form2
*label10.static: true
*label10.name: label10
*label10.x: 190
*label10.y: 160
*label10.width: 50
*label10.height: 20
*label10.labelString: "n.2"

*label11.class: label
*label11.parent: form2
*label11.static: true
*label11.name: label11
*label11.x: 190
*label11.y: 200
*label11.width: 50
*label11.height: 20
*label11.labelString: "n.4"

*label12.class: label
*label12.parent: form2
*label12.static: true
*label12.name: label12
*label12.x: 190
*label12.y: 280
*label12.width: 50
*label12.height: 20
*label12.labelString: "n.8"

