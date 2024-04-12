! UIMX ascii 2.5 key: 7578                                                      

*PerturbEditor.class: topLevelShell
*PerturbEditor.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo PerturbEditor.i\
   tipo \
   release 5.2\
   data 2/6/96\
   reserved @(#)PerturbEditor.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <string.h>\
#include "res_edit.h"\
#include "ImpPert.h"
*PerturbEditor.ispecdecl: Widget VettoreLabel[3],VettoreText[3];\
char *Perturbazione;\
Widget TextPerturbazione;\
int IndicePerturba;
*PerturbEditor.ispeclist: VettoreLabel, VettoreText, Perturbazione, TextPerturbazione, IndicePerturba
*PerturbEditor.ispeclist.VettoreLabel: "Widget", "%VettoreLabel%[3]"
*PerturbEditor.ispeclist.VettoreText: "Widget", "%VettoreText%[3]"
*PerturbEditor.ispeclist.Perturbazione: "unsigned char", "*%Perturbazione%"
*PerturbEditor.ispeclist.TextPerturbazione: "Widget", "%TextPerturbazione%"
*PerturbEditor.ispeclist.IndicePerturba: "int", "%IndicePerturba%"
*PerturbEditor.funcdecl: swidget create_PerturbEditor(Widget Parent3,  /* shell chiamante */\
			     char *Pert,      /* perturbazione gia' definita */\
			     Widget TextPert) /* text field del variable editor\
                                                 che definisce le perturbazione */\

*PerturbEditor.funcname: create_PerturbEditor
*PerturbEditor.funcdef: "swidget", "<create_PerturbEditor>(%)"
*PerturbEditor.argdecl: Widget Parent3;\
unsigned char *Pert;\
Widget TextPert;
*PerturbEditor.arglist: Parent3, Pert, TextPert
*PerturbEditor.arglist.Parent3: "Widget", "%Parent3%"
*PerturbEditor.arglist.Pert: "unsigned char", "*%Pert%"
*PerturbEditor.arglist.TextPert: "Widget", "%TextPert%"
*PerturbEditor.icode: int Pos;\
\
Perturbazione = Pert; \
TextPerturbazione = TextPert;
*PerturbEditor.fcode: VettoreLabel[0] = (Widget )labPar1;\
VettoreLabel[1] = (Widget )labPar2;\
\
VettoreText[0] = (Widget )textPar1;\
VettoreText[1] = (Widget )textPar2;\
\
IndicePerturba = InizializzaParameter (VettoreLabel,VettoreText,(char *)Perturbazione);\
ImpostaOptionMenu (OptionM,IndicePerturba);\
\
/*  Setta la posizione dell'interfaccia secondo il Parent  */\
InterfaceSetPos (PerturbEditor,Parent3);\
\
return(rtrn);\

*PerturbEditor.auxdecl: void RiazzeraParameter (Widget *Lab,Widget *TextFi)\
{\
XmString XmAppo;\
int i;\
\
XmAppo = XmStringCreateSimple (" ");\
for (i=0;i<2;i++)\
	{\
	set_something (TextFi[i], XmNsensitive, False);\
	XmTextFieldSetString (TextFi[i], "");\
	set_something (Lab[i], XmNlabelString, XmAppo);\
	}\
XmStringFree (XmAppo);\
}\
\
void LeggiPerturb (char *Defi,int *Posiz,char **A,char **B)\
{\
int ritorno,Indice,uguali;\
char *Appo,*Conf;\
\
Conf = XtNewString (Defi);\
\
Appo = XtCalloc (20,sizeof(char));\
sscanf (Conf,"%s",Appo);\
Conf += strlen (Appo)+1;\
\
Indice = 0;\
*Posiz = Indice;\
\
uguali = strcmp (Appo,PerturbDefinitions[Indice]);\
while ( (uguali != 0) && (Indice <= NumPert) )\
        {\
        Indice++;\
        uguali = strcmp (Appo,PerturbDefinitions[Indice]);\
        }\
XtFree (Appo);\
\
if (uguali==0)\
  {\
  *Posiz = Indice;\
  Appo = XtCalloc (20,sizeof(char));\
  if ( (sscanf(Conf,"%s",Appo)) <= 0 )\
    {\
    *A = XtNewString ("");\
    *B = XtNewString ("");\
    }\
  else\
    {\
    Conf += strlen (Appo)+1;\
    *A = XtNewString (Appo);\
    XtFree (Appo);\
    Appo = XtCalloc (20,sizeof(char));\
    if ( (sscanf (Conf,"%s",Appo)) <= 0)\
      *B = XtNewString ("");\
    else *B = XtNewString (Appo);\
    XtFree (Appo);\
    }\
  }\
else\
  {\
  *A = XtNewString ("");\
  *B = XtNewString ("");\
  }\
XtFree (Conf);\
}\
\
int InizializzaParameter (Widget *Lab,Widget *TextF,char *Definiz)\
{\
int j,i,RigheLette;\
int Posizione;\
char *Par1,*Par2;\
XmString XmLab;\
\
if (Definiz[0] != '\0')\
	LeggiPerturb (Definiz,&Posizione,&Par1,&Par2);\
else\
	{\
	Posizione = 0;\
	Par1 = XtNewString ("");\
	Par2 = XtNewString ("");\
	}\
\
RigheLette = 0;\
i=0;\
while (RigheLette != Posizione )\
	{\
	if (strcmp (EditorDefinitions[i],"NULL") == 0)\
		RigheLette++;\
	i++;\
	}\
\
j = 0;\
while (strcmp (EditorDefinitions[i],"NULL"))\
	{\
	XmLab = XmStringCreateSimple (EditorDefinitions[i]);\
	set_something (Lab[j], XmNlabelString, XmLab);\
	set_something (TextF[j], XmNsensitive, True);\
	XmStringFree (XmLab);\
	i++;\
	j++;\
	}\
\
XmTextFieldSetString (TextF[0], Par1);\
XmTextFieldSetString (TextF[1], Par2);\
\
XtFree (Par1);\
XtFree (Par2);\
return (Posizione);\
}\
\
void ImpostaParameter (Widget *Lab,Widget *TextF,int Posizione)\
{\
int j,i,RigheLette,RigheLetteDef;\
XmString XmLab;\
\
RigheLette = 0;\
i=0;\
while (RigheLette != Posizione )\
	{\
	if (strcmp(EditorDefinitions[i],"NULL") == 0)\
		RigheLette++;\
	i++;\
	}\
\
j = 0;\
while (strcmp (EditorDefinitions[i],"NULL"))\
	{\
	XmLab = XmStringCreateSimple (EditorDefinitions[i]);\
	set_something (Lab[j], XmNlabelString, XmLab);\
	set_something (TextF[j], XmNsensitive, True);\
	XmStringFree (XmLab);\
	i++;\
	j++;\
	}\
\
i=0;\
RigheLetteDef = 0;\
while (RigheLetteDef != Posizione)\
	{\
	if (strcmp (PerturbDefaults[i],"NULL")==0)\
		RigheLetteDef++;\
	i++;\
	}\
\
XmTextFieldSetString (TextF[0],PerturbDefaults[i]);\
XmTextFieldSetString (TextF[1],PerturbDefaults[i+1]);\
}\
\
int OptPertCB (Widget wid, int ind_res, XmAnyCallbackStruct *call_data)\
{\
\
#ifndef DESIGN_TIME\
        _UxCPerturbEditor *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxPerturbEditorContext;\
        UxPerturbEditorContext = UxContext =\
                        (_UxCPerturbEditor *)UxGetContext(wid);\
#endif\
\
RiazzeraParameter (VettoreLabel,VettoreText);\
ImpostaParameter (VettoreLabel,VettoreText,ind_res);\
\
IndicePerturba = ind_res;\
\
#ifndef DESIGN_TIME\
        UxPerturbEditorContext = UxSaveCtx;\
#endif\
return (OK);\
}\
\
/*****************************************************************\
        Creazione dell'option menu delle perturbazioni\
*****************************************************************/\
\
int ImpostaOptionMenu (Widget ogg,int Posizione)\
{\
        Widget  *ListaItem;\
        int i,narg;\
        XmString StrLab;\
	Arg args[10];\
\
        XtDestroyWidget (Fittizio);\
        ListaItem = (Widget *)XtCalloc (NumPert, sizeof(Widget));\
        if (ListaItem == NULL) return (NON_ALLOCATA);\
        for ( i = 0 ; i < NumPert ; i++ )\
        {\
                StrLab = XmStringCreateSimple (EditorOption[i]);\
	\
		narg = 0;\
		XtSetArg (args[narg], XmNlabelString, StrLab); narg++;\
\
                ListaItem[i] = (Widget )XmCreatePushButton (ogg,"optbt",\
							args,narg);\
		XtManageChild (ListaItem[i]);\
\
#ifndef DESIGN_TIME\
		UxPutContext (ListaItem[i], (char *) UxPerturbEditorContext);\
#endif\
                XmStringFree(StrLab);\
                XtAddCallback (ListaItem[i],XmNactivateCallback, OptPertCB,i);\
        }\
        set_something (menu2, XmNmenuHistory, ListaItem[Posizione]);\
        return (OK);\
}
*PerturbEditor.static: true
*PerturbEditor.name: PerturbEditor
*PerturbEditor.parent: NO_PARENT
*PerturbEditor.x: 260
*PerturbEditor.y: 79
*PerturbEditor.width: 400
*PerturbEditor.height: 170
*PerturbEditor.iconName: "Perturb"
*PerturbEditor.title: "Perturb. Editor"

*form5.class: form
*form5.static: true
*form5.name: form5
*form5.parent: PerturbEditor
*form5.resizePolicy: "resize_none"
*form5.unitType: "pixels"
*form5.x: 0
*form5.y: 0
*form5.width: 400
*form5.height: 170

*pushButton15.class: pushButton
*pushButton15.static: true
*pushButton15.name: pushButton15
*pushButton15.parent: form5
*pushButton15.x: 9
*pushButton15.y: 124
*pushButton15.width: 80
*pushButton15.height: 30
*pushButton15.labelString: "OK"
*pushButton15.activateCallback: {\
Boolean Valore;\
Boolean GiustoA,GiustoB;\
char *DefPerturba,*ParA,*ParB;\
char Messag[50];\
int Lunghezza;\
\
Lunghezza = 0;\
ParA = XmTextFieldGetString (textPar1);\
GiustoA = NumFloVerifica (ParA);\
\
ParB = XmTextFieldGetString (textPar2);\
GiustoB = NumFloVerifica (ParB);\
\
if ( GiustoA && GiustoB )\
	{\
	Lunghezza = strlen (PerturbDefinitions[IndicePerturba])+1;\
	Lunghezza += strlen (ParA) + 1;\
	Lunghezza += strlen (ParB) + 1;\
	DefPerturba = XtCalloc (Lunghezza,sizeof(char));\
	strcpy (DefPerturba,PerturbDefinitions[IndicePerturba]);\
	if (ParA[0] != '\0')\
		{\
		strcat (DefPerturba," ");\
		strcat (DefPerturba,ParA);\
		}\
	if (ParB[0] != '\0')\
		{\
		strcat (DefPerturba," ");\
		strcat (DefPerturba,ParB);\
		}\
	XmTextFieldSetString (TextPerturbazione,DefPerturba);\
	XtFree (DefPerturba);\
	XtFree (ParA);\
	XtFree (ParB);\
	XtDestroyWidget (PerturbEditor);\
	}\
else\
	{\
	strcpy (Messag,"An error detected in input!");\
	VisualizzaMessageBox (GENERICA,PerturbEditor,Messag,PerturbEditor);\
	}\
XtFree (ParA);\
XtFree (ParB);\
}
*pushButton15.bottomAttachment: "attach_position"
*pushButton15.bottomPosition: 95
*pushButton15.leftAttachment: "attach_position"
*pushButton15.leftOffset: 0
*pushButton15.rightAttachment: "attach_position"
*pushButton15.topAttachment: "attach_position"
*pushButton15.topOffset: 0
*pushButton15.topPosition: 70
*pushButton15.leftPosition: 5
*pushButton15.rightPosition: 30

*pushButton14.class: pushButton
*pushButton14.static: true
*pushButton14.name: pushButton14
*pushButton14.parent: form5
*pushButton14.x: 99
*pushButton14.y: 124
*pushButton14.width: 80
*pushButton14.height: 30
*pushButton14.labelString: "CANCEL"
*pushButton14.activateCallback: {\
XtDestroyWidget (PerturbEditor);\
}
*pushButton14.bottomAttachment: "attach_position"
*pushButton14.bottomPosition: 95
*pushButton14.leftAttachment: "attach_position"
*pushButton14.leftOffset: 0
*pushButton14.rightAttachment: "attach_position"
*pushButton14.topAttachment: "attach_position"
*pushButton14.topOffset: 0
*pushButton14.topPosition: 70
*pushButton14.leftPosition: 32
*pushButton14.rightPosition: 57

*separator7.class: separator
*separator7.static: true
*separator7.name: separator7
*separator7.parent: form5
*separator7.x: 0
*separator7.y: 104
*separator7.width: 550
*separator7.height: 10
*separator7.bottomAttachment: "attach_position"
*separator7.bottomPosition: 66
*separator7.leftAttachment: "attach_position"
*separator7.leftPosition: 1
*separator7.rightAttachment: "attach_position"
*separator7.rightPosition: 99
*separator7.topAttachment: "attach_position"
*separator7.topOffset: 0
*separator7.topPosition: 62

*menu2.class: rowColumn
*menu2.static: true
*menu2.name: menu2
*menu2.parent: form5
*menu2.rowColumnType: "menu_option"
*menu2.subMenuId: "OptionM"
*menu2.x: 30
*menu2.y: 60
*menu2.entryAlignment: "alignment_center"
*menu2.labelString: ""
*menu2.bottomAttachment: "attach_position"
*menu2.bottomPosition: 55
*menu2.topAttachment: "attach_position"
*menu2.topOffset: 0
*menu2.topPosition: 35
*menu2.leftAttachment: "attach_position"
*menu2.leftOffset: 0
*menu2.leftPosition: 10
*menu2.rightAttachment: "attach_position"
*menu2.rightPosition: 38

*OptionM.class: rowColumn
*OptionM.static: true
*OptionM.name: OptionM
*OptionM.parent: menu2
*OptionM.rowColumnType: "menu_pulldown"
*OptionM.marginHeight: 0
*OptionM.entryAlignment: "alignment_center"
*OptionM.adjustMargin: "false"

*Fittizio.class: pushButton
*Fittizio.static: true
*Fittizio.name: Fittizio
*Fittizio.parent: OptionM
*Fittizio.labelString: "Fittizio"

*label7.class: label
*label7.static: true
*label7.name: label7
*label7.parent: form5
*label7.x: 30
*label7.y: 20
*label7.width: 100
*label7.height: 30
*label7.labelString: "Perturb. Type"
*label7.bottomAttachment: "attach_position"
*label7.bottomPosition: 30
*label7.topAttachment: "attach_position"
*label7.topOffset: 0
*label7.topPosition: 10
*label7.leftAttachment: "attach_position"
*label7.leftOffset: 0
*label7.leftPosition: 10
*label7.rightAttachment: "attach_position"
*label7.rightPosition: 38

*textPar1.class: textField
*textPar1.static: true
*textPar1.name: textPar1
*textPar1.parent: form5
*textPar1.x: 170
*textPar1.y: 60
*textPar1.width: 80
*textPar1.height: 30
*textPar1.maxLength: 10
*textPar1.ancestorSensitive: "true"
*textPar1.sensitive: "false"
*textPar1.marginHeight: 1
*textPar1.bottomAttachment: "attach_position"
*textPar1.bottomPosition: 55
*textPar1.topAttachment: "attach_position"
*textPar1.topOffset: 0
*textPar1.topPosition: 35
*textPar1.leftAttachment: "attach_position"
*textPar1.leftOffset: 0
*textPar1.leftPosition: 40
*textPar1.rightAttachment: "attach_position"
*textPar1.rightPosition: 65

*labPar1.class: label
*labPar1.static: true
*labPar1.name: labPar1
*labPar1.parent: form5
*labPar1.x: 160
*labPar1.y: 20
*labPar1.width: 100
*labPar1.height: 30
*labPar1.labelString: ""
*labPar1.recomputeSize: "false"
*labPar1.bottomAttachment: "attach_position"
*labPar1.bottomPosition: 30
*labPar1.topAttachment: "attach_position"
*labPar1.topOffset: 0
*labPar1.topPosition: 10
*labPar1.leftAttachment: "attach_position"
*labPar1.leftOffset: 0
*labPar1.leftPosition: 40
*labPar1.rightAttachment: "attach_position"
*labPar1.rightPosition: 65

*textPar2.class: textField
*textPar2.static: true
*textPar2.name: textPar2
*textPar2.parent: form5
*textPar2.x: 290
*textPar2.y: 60
*textPar2.width: 80
*textPar2.height: 30
*textPar2.maxLength: 10
*textPar2.ancestorSensitive: "true"
*textPar2.sensitive: "false"
*textPar2.marginHeight: 1
*textPar2.bottomAttachment: "attach_position"
*textPar2.bottomPosition: 55
*textPar2.topAttachment: "attach_position"
*textPar2.topOffset: 0
*textPar2.topPosition: 35
*textPar2.leftAttachment: "attach_position"
*textPar2.leftOffset: 0
*textPar2.leftPosition: 68
*textPar2.rightAttachment: "attach_position"
*textPar2.rightPosition: 93

*labPar2.class: label
*labPar2.static: true
*labPar2.name: labPar2
*labPar2.parent: form5
*labPar2.x: 280
*labPar2.y: 20
*labPar2.width: 100
*labPar2.height: 30
*labPar2.labelString: ""
*labPar2.recomputeSize: "false"
*labPar2.bottomAttachment: "attach_position"
*labPar2.bottomPosition: 30
*labPar2.topAttachment: "attach_position"
*labPar2.topOffset: 0
*labPar2.topPosition: 10
*labPar2.leftAttachment: "attach_position"
*labPar2.leftOffset: 0
*labPar2.leftPosition: 68
*labPar2.rightAttachment: "attach_position"
*labPar2.rightPosition: 93

