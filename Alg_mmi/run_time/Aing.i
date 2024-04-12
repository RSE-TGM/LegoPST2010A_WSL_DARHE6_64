! UIMX ascii 2.5 key: 2114                                                      

*Aing.class: topLevelShell
*Aing.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo Aing.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)Aing.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include <string.h>\
#include <stdlib.h>\
#include <math.h>\
#include <Ol/OlDatabasePunti.h>\
#include <Xm/Protocols.h>\
#include "aing_def.h"\
\
#ifndef DESIGN_TIME\
#include "other.h"\
#endif\
\
#ifdef SCO_UNIX\
#include <Xm/MwmUtil.h>\
#else\
#include <Xm/MwmUtil.h>\
#endif\
\
#include "sim_param.h"\
#include "sim_ipc.h"\
#include "page_aing_icon.bmp"\
\
\
extern OlDatabasePuntiObject database_simulatore;\
int msg_pert;\
\
static void CreaIndicatore( );\
void DestroyAing( );\
static void refresh_aing( );\
void ConfigureAing( );\
void activateCB_QuitAing();\
int AingStartEnable(Widget, int);
*Aing.ispecdecl: Widget topLevel_selezionataAing;\
XtIntervalId timer_refresh_aing;\
XmFontList FontLabelAing;\
int key_refresh_aing;\
WidgetList lista_wid_aing;\
int num_wid_aing;\
Widget OptionPert[NUM_MENU_AING];\
int PertSelezionata;\
int TempoSelezionato;\
char tagSelect[20];\
char unimisSelect[20];\
float aSelect;\
float bSelect;\
int indSelect;\
XrmDatabase RisDb;
*Aing.ispeclist: topLevel_selezionataAing, timer_refresh_aing, FontLabelAing, key_refresh_aing, lista_wid_aing, num_wid_aing, OptionPert, PertSelezionata, TempoSelezionato, tagSelect, unimisSelect, aSelect, bSelect, indSelect, RisDb
*Aing.ispeclist.topLevel_selezionataAing: "Widget", "%topLevel_selezionataAing%"
*Aing.ispeclist.timer_refresh_aing: "XtIntervalId", "%timer_refresh_aing%"
*Aing.ispeclist.FontLabelAing: "XmFontList", "%FontLabelAing%"
*Aing.ispeclist.key_refresh_aing: "int", "%key_refresh_aing%"
*Aing.ispeclist.lista_wid_aing: "WidgetList", "%lista_wid_aing%"
*Aing.ispeclist.num_wid_aing: "int", "%num_wid_aing%"
*Aing.ispeclist.OptionPert: "Widget", "%OptionPert%[10]"
*Aing.ispeclist.PertSelezionata: "int", "%PertSelezionata%"
*Aing.ispeclist.TempoSelezionato: "int", "%TempoSelezionato%"
*Aing.ispeclist.tagSelect: "unsigned char", "%tagSelect%[20]"
*Aing.ispeclist.unimisSelect: "unsigned char", "%unimisSelect%[20]"
*Aing.ispeclist.aSelect: "float", "%aSelect%"
*Aing.ispeclist.bSelect: "float", "%bSelect%"
*Aing.ispeclist.indSelect: "int", "%indSelect%"
*Aing.ispeclist.RisDb: "XrmDatabase", "%RisDb%"
*Aing.funcdecl: swidget create_Aing(rigaAing,PadreAing)\
char *rigaAing;\
Widget PadreAing;\

*Aing.funcname: create_Aing
*Aing.funcdef: "swidget", "<create_Aing>(%)"
*Aing.argdecl: unsigned char *rigaAing;\
Widget PadreAing;
*Aing.arglist: rigaAing, PadreAing
*Aing.arglist.rigaAing: "unsigned char", "*%rigaAing%"
*Aing.arglist.PadreAing: "Widget", "%PadreAing%"
*Aing.icode: char c1[20],c2[20],c3[20],c4[20],c5[20],c6[20],c7[20];\
Pixmap pix;\
Atom WM_DELETE_WINDOW; /* per close con MWM*/\
\
if(!CanOpenPage(PadreAing))\
	return(NULL);\
\
\
sscanf(rigaAing,"%s %s %s %s %s %s %s",tagSelect,c2,c3,c4,c5,c6,unimisSelect);\
aSelect=atof(c5);\
bSelect=atof(c6);\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabelAing,XtDisplay(PadreAing)))\
	exit(0);\
#endif\
PertSelezionata = 0;\
TempoSelezionato = 0;\
\

*Aing.fcode: set_something(tag,XmNfontList,FontLabelAing);\
set_something(unimis,XmNfontList,FontLabelAing);\
set_something(Start,XmNfontList,FontLabelAing);\
set_something(Stop,XmNfontList,FontLabelAing);\
set_something(tag,XmNlabelString,\
                 XmStringCreateLtoR(tagSelect,XmSTRING_DEFAULT_CHARSET));\
set_something(unimis,XmNlabelString,\
                 XmStringCreateLtoR(unimisSelect,XmSTRING_DEFAULT_CHARSET));\
#ifndef DESIGN_TIME\
LoadBitmap(testata,&pix,page_aing_icon_bits,page_aing_icon_width,\
		page_aing_icon_height);\
#endif\
set_something(rtrn,XmNiconPixmap,pix);\
CreaIndicatore(drawingAing);\
#ifndef DESIGN_TIME\
if((key_refresh_aing=\
	InsElencoPagine("__AING__",lista_wid_aing,num_wid_aing,\
			REFRESH_AING/1000)) == -1)\
	return(NULL);\
#endif\
\
UxPopupInterface(rtrn, no_grab);\
ConfigureAing(rtrn,0);\
#ifndef DESIGN_TIME\
timer_refresh_aing = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (PadreAing),\
            (unsigned long) REFRESH_AING ,refresh_aing, UxContext);\
#endif\
WM_DELETE_WINDOW=XmInternAtom(XtDisplay(Aing),"WM_DELETE_WINDOW",False);\
XmAddWMProtocolCallback(Aing,WM_DELETE_WINDOW,activateCB_QuitAing,NULL);\
\
return(rtrn);
*Aing.auxdecl: void DestroyAing(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCAing *Context;\
\
        Context =(_UxCAing *) UxGetContext(w);	\
	DelElencoPagine(Context->Uxkey_refresh_aing, \
		Context->UxdrawingAing);\
	XSync(XtDisplay(w),False);\
	XtRemoveTimeOut(Context->Uxtimer_refresh_aing);\
	XtDestroyWidget(Context->UxAing);\
	XrmDestroyDatabase(Context->UxRisDb);\
#endif\
}\
\
\
#ifndef DESIGN_TIME\
static void refresh_aing(_UxCAing *Context)\
#else\
static void refresh_aing()\
#endif\
{\
#ifndef DESIGN_TIME\
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_aing))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_aing))\
     XlRefreshWidget(Context->Uxlista_wid_aing,Context->Uxnum_wid_aing);\
\
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_aing))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
/*\
        carica il timer per il refresh\
*/\
Context->Uxtimer_refresh_aing = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (Context->UxAing),\
            (unsigned long) REFRESH_AING ,refresh_aing, Context);\
#endif	\
}\
\
\
\
static void CreaIndicatore(Widget Drawing)\
{\
#ifndef DESIGN_TIME\
_UxCAing *Context;\
XrmDatabase SaveDb;\
Display *display;\
\
	WriteDbAing();	\
        Context =(_UxCAing *) UxGetContext(Drawing);\
	RisDb=XrmGetFileDatabase("TemplateIndicAing.rtf");\
	display=XtDisplay(Drawing);\
	SaveDb=display->db;\
	display->db=RisDb;\
	CreaPagina(Context->UxdrawingAing,&(Context->Uxlista_wid_aing),\
		 &(Context->Uxnum_wid_aing));\
	Context->UxindSelect = SettaIndicAing(Context->Uxlista_wid_aing[0],Context->UxtagSelect,\
		Context->UxaSelect,Context->UxbSelect);\
	display->db=SaveDb;\
	\
#endif\
\
}\
\
\
\
void ConfigureAing(Widget w, int sel)\
{\
#ifndef DESIGN_TIME\
 _UxCAing                *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxAingContext;\
        UxAingContext = UxContext =\
                        (_UxCAing *) UxGetContext( w );\
#endif\
PertSelezionata=sel;\
printf("Perturbazione selezionata = %d\n",PertSelezionata);\
XtUnmanageChild(campo_1);\
XtUnmanageChild(text_1);\
XtUnmanageChild(campo_2);\
XtUnmanageChild(text_2);\
XtUnmanageChild(campo_3);\
XtUnmanageChild(text_3);\
XtUnmanageChild(campo_4);\
XtUnmanageChild(text_4);\
XtUnmanageChild(campo_5);\
XtUnmanageChild(text_5);\
XtUnmanageChild(campo_6);\
XtUnmanageChild(text_6);\
XtUnmanageChild(campo_7);\
XtUnmanageChild(text_7);\
#ifndef DESIGN_TIME\
if(menu_aing[sel]._campo_1)\
	{\
	set_something(campo_1,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_1,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_1);\
	XtManageChild(text_1);\
	}\
if(menu_aing[sel]._campo_2)\
	{\
	set_something(campo_2,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_2,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_2);\
	XtManageChild(text_2);\
	}\
if(menu_aing[sel]._campo_3)\
	{\
	set_something(campo_3,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_3,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_3);\
	XtManageChild(text_3);\
	}\
if(menu_aing[sel]._campo_4)\
	{\
	set_something(campo_4,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_4,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_4);\
	XtManageChild(text_4);\
	}\
if(menu_aing[sel]._campo_5)\
	{\
	set_something(campo_5,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_5,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_5);\
	XtManageChild(text_5);\
	}\
if(menu_aing[sel]._campo_6)\
	{\
	set_something(campo_6,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_6,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_6);\
	XtManageChild(text_6);\
	}\
if(menu_aing[sel]._campo_7)\
	{\
	set_something(campo_7,XmNlabelString,\
                 XmStringCreateLtoR(menu_aing[sel].descr_7,XmSTRING_DEFAULT_CHARSET));\
	XtManageChild(campo_7);\
	XtManageChild(text_7);\
	}\
if(menu_aing[sel]._Start)\
	set_something(Start,XmNsensitive,True);\
else\
	set_something(Start,XmNsensitive,False);\
if(menu_aing[sel]._Stop)\
	set_something(Stop,XmNsensitive,True);\
else\
	set_something(Stop,XmNsensitive,False);\
\
UxAingContext = UxSaveCtx;\
#endif\
}\
\
\
AingStartEnable(w,enable)\
Widget w;\
int enable;\
{\
\
 _UxCAing                *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxAingContext;\
        UxAingContext = UxContext =\
                        (_UxCAing *) UxGetContext( w );\
\
Aing_start_enable(w,&UxEnv,enable);\
\
UxAingContext = UxSaveCtx;\
\
}
*Aing_start_enable.class: method
*Aing_start_enable.name: start_enable
*Aing_start_enable.parent: Aing
*Aing_start_enable.methodType: int
*Aing_start_enable.methodArgs: int sensitive;\

*Aing_start_enable.methodBody: if(!sensitive)\
   {\
   XtVaSetValues(tipo_pert,XmNsensitive,False,NULL);\
   XtVaSetValues(timeAing,XmNsensitive,False,NULL);\
   XtVaSetValues(Start,XmNsensitive,False,NULL);\
   }\
else\
   XtVaSetValues(Start,XmNsensitive,True,NULL);
*Aing_start_enable.arguments: sensitive
*Aing_start_enable.sensitive.def: "int", "%sensitive%"

*Aing.static: true
*Aing.name: Aing
*Aing.parent: NO_PARENT
*Aing.x: 240
*Aing.y: 190
*Aing.width: 400
*Aing.height: 240
*Aing.mwmDecorations: MWM_DECOR_BORDER | MWM_DECOR_MINIMIZE
*Aing.iconName: tagSelect
*Aing.title: tagSelect
*Aing.deleteResponse: "do_nothing"

*sfondo.class: form
*sfondo.static: true
*sfondo.name: sfondo
*sfondo.parent: Aing
*sfondo.resizePolicy: "resize_none"
*sfondo.unitType: "pixels"
*sfondo.x: 20
*sfondo.y: 10
*sfondo.width: 520
*sfondo.height: 300

*testata.class: form
*testata.static: true
*testata.name: testata
*testata.parent: sfondo
*testata.resizePolicy: "resize_none"
*testata.x: 0
*testata.y: 0
*testata.width: 560
*testata.height: 60
*testata.rightAttachment: "attach_form"
*testata.topOffset: 0
*testata.leftAttachment: "attach_form"
*testata.background: "#50a050"

*tag.class: label
*tag.static: true
*tag.name: tag
*tag.parent: testata
*tag.x: 10
*tag.y: 10
*tag.width: 100
*tag.height: 40
*tag.topOffset: 8
*tag.leftOffset: 20
*tag.background: "#50a050"
*tag.bottomAttachment: "attach_form"
*tag.bottomOffset: 10
*tag.topAttachment: "attach_form"
*tag.recomputeSize: "false"

*unimis.class: label
*unimis.static: true
*unimis.name: unimis
*unimis.parent: testata
*unimis.x: 350
*unimis.y: 10
*unimis.width: 100
*unimis.height: 40
*unimis.background: "#50a050"
*unimis.leftAttachment: "attach_none"
*unimis.leftOffset: 0
*unimis.rightAttachment: "attach_form"
*unimis.rightOffset: 10
*unimis.bottomAttachment: "attach_form"
*unimis.bottomOffset: 10
*unimis.topAttachment: "attach_form"
*unimis.topOffset: 8
*unimis.recomputeSize: "false"

*separator1.class: separator
*separator1.static: true
*separator1.name: separator1
*separator1.parent: testata
*separator1.x: 0
*separator1.y: 50
*separator1.width: 560
*separator1.height: 10
*separator1.background: "#50a050"
*separator1.bottomAttachment: "attach_form"
*separator1.rightAttachment: "attach_form"
*separator1.leftAttachment: "attach_form"

*drawingAing.class: drawingArea
*drawingAing.static: true
*drawingAing.name: drawingAing
*drawingAing.parent: testata
*drawingAing.resizePolicy: "resize_none"
*drawingAing.x: 120
*drawingAing.y: 10
*drawingAing.width: 190
*drawingAing.height: 40
*drawingAing.bottomAttachment: "attach_form"
*drawingAing.bottomOffset: 10
*drawingAing.rightAttachment: "attach_widget"
*drawingAing.rightWidget: "unimis"
*drawingAing.topAttachment: "attach_form"
*drawingAing.topOffset: 2
*drawingAing.leftAttachment: "attach_widget"
*drawingAing.leftOffset: 10
*drawingAing.leftWidget: "tag"
*drawingAing.rightOffset: 10
*drawingAing.background: "#50a050"

*tasti_label.class: form
*tasti_label.static: true
*tasti_label.name: tasti_label
*tasti_label.parent: sfondo
*tasti_label.resizePolicy: "resize_none"
*tasti_label.x: 160
*tasti_label.y: 70
*tasti_label.width: 380
*tasti_label.height: 230
*tasti_label.bottomAttachment: "attach_form"
*tasti_label.rightAttachment: "attach_form"
*tasti_label.topAttachment: "attach_widget"
*tasti_label.topWidget: "testata"
*tasti_label.background: "#50a050"
*tasti_label.leftAttachment: "attach_form"
*tasti_label.borderWidth: 0
*tasti_label.borderColor: "#507050"

*Stop.class: pushButton
*Stop.static: true
*Stop.name: Stop
*Stop.parent: tasti_label
*Stop.x: 220
*Stop.y: 150
*Stop.width: 80
*Stop.height: 40
*Stop.background: "#ff0000"
*Stop.bottomAttachment: "attach_form"
*Stop.rightAttachment: "attach_form"
*Stop.rightOffset: 5
*Stop.bottomOffset: 10
*Stop.recomputeSize: "false"
*Stop.activateCallback: {\
float t;\
int shr_usr_key;\
\
if(msg_pert==0)\
	{\
	shr_usr_key=atoi(XlGetenv("SHR_USR_KEY"));\
/*\
Inserisco controllo sul tipo di database in maniera da inviare perturbazioni sulla\
giusta coda di messaggi.\
*/	if((OlDatabasePuntiType(database_simulatore))==DB_XLSIMUL)\
		msg_pert=msg_create(shr_usr_key+ID_MSG_PERT,0);\
	else\
		msg_pert=msg_create(shr_usr_key+ID_MSG_PERT_MMI,0);\
	}\
\
\
\
t=atof(XmTextFieldGetString(TextFieldTempo));\
if(TempoSelezionato == 0)\
 t = -t;\
\
if(PertSelezionata == 2)\
	pert_impulso_stop(msg_pert,indSelect,t);	\
\
if(PertSelezionata == 3)\
	pert_rampa_stop(msg_pert,indSelect,t);	\
	\
if((PertSelezionata == 4) || (PertSelezionata == 5))\
	pert_to_stop(msg_pert,indSelect,t);\
\
if((PertSelezionata == 6) || (PertSelezionata == 7))\
	pert_period_stop(msg_pert,indSelect,t);\
\
if(PertSelezionata == 8)\
	pert_whitenoise_stop(msg_pert,indSelect,t);\
\
if(PertSelezionata == 9)\
        pert_malfunction_stop(msg_pert,indSelect,t);	\
\
}

*Start.class: pushButton
*Start.static: true
*Start.name: Start
*Start.parent: tasti_label
*Start.x: 120
*Start.y: 150
*Start.width: 80
*Start.height: 40
*Start.background: "#00ff00"
*Start.bottomAttachment: "attach_form"
*Start.bottomOffset: 10
*Start.leftAttachment: "attach_none"
*Start.leftOffset: 30
*Start.rightAttachment: "attach_widget"
*Start.rightOffset: 5
*Start.rightWidget: "Stop"
*Start.recomputeSize: "false"
*Start.activateCallback: {\
float v1,v2,v3,v4,v5,v6,v7,t;\
int shr_usr_key;\
\
if(msg_pert==0)\
	{\
	shr_usr_key=atoi(XlGetenv("SHR_USR_KEY"));\
/*\
Inserisco controllo sul tipo di database in maniera da inviare perturbazioni sulla\
giusta coda di messaggi.\
*/	if((OlDatabasePuntiType(database_simulatore))==DB_XLSIMUL)\
		msg_pert=msg_create(shr_usr_key+ID_MSG_PERT,0);\
	else\
		msg_pert=msg_create(shr_usr_key+ID_MSG_PERT_MMI,0);\
	}\
\
\
\
v1=atof(XmTextFieldGetString(text_1));\
v2=atof(XmTextFieldGetString(text_2));\
v3=atof(XmTextFieldGetString(text_3));\
v4=atof(XmTextFieldGetString(text_4));\
v5=atof(XmTextFieldGetString(text_5));\
v6=atof(XmTextFieldGetString(text_6));\
v7=atof(XmTextFieldGetString(text_7));\
t=atof(XmTextFieldGetString(TextFieldTempo));\
if(TempoSelezionato == 0)\
	t = -t;\
\
\
if(PertSelezionata == 0)\
	pert_nega(msg_pert,indSelect,t);\
\
if(PertSelezionata == 1)\
	{\
	v1=(v1-bSelect)/aSelect;\
	pert_scalino(msg_pert,indSelect,v1,t);	\
	}\
if(PertSelezionata == 2)\
	{\
	v1=(v1-bSelect)/aSelect;\
	pert_impulso(msg_pert,indSelect,v1,v2,t);	\
	}\
if(PertSelezionata == 3)\
	{\
	v1=(v1-bSelect)/aSelect;\
	v2=(v2/60.-bSelect)/aSelect;\
	pert_rampa(msg_pert,indSelect,v1,v2,t);	\
	}\
\
if(PertSelezionata == 4)\
	{\
	v1=(v1-bSelect)/aSelect;\
	v2= -v2;\
	pert_to(msg_pert,indSelect,v1,v2,t);	\
	}\
\
if(PertSelezionata == 5)\
	{\
	v1=(v1-bSelect)/aSelect;\
	pert_to(msg_pert,indSelect,v1,v2,t);	\
	}\
\
if(PertSelezionata == 6)\
	{\
	v2=(v2-bSelect)/aSelect;\
	v3=(v3-bSelect)/aSelect;\
	pert_period(msg_pert,indSelect,-1.,-1.,v1,v4,v2,v3,0.,t);\
	}\
\
if(PertSelezionata == 7)\
	{\
	v2=(v2-bSelect)/aSelect;\
	v3=(v3-bSelect)/aSelect;\
	pert_period(msg_pert,indSelect,v5,v6,v1,v4,v2,v3,v7,t);\
	}\
if(PertSelezionata == 8)\
	{\
	v1=(v1-bSelect)/aSelect;\
	pert_whitenoise(msg_pert,indSelect,v1,v2,t);	\
	}\
if(PertSelezionata == 9)\
        {\
        v1=(v1-bSelect)/aSelect;\
        pert_malfunction(msg_pert,indSelect,v1,v2,t);\
        }\
}

*tipo_pert.class: rowColumn
*tipo_pert.static: true
*tipo_pert.name: tipo_pert
*tipo_pert.parent: tasti_label
*tipo_pert.rowColumnType: "menu_option"
*tipo_pert.subMenuId: "SceltaPert"
*tipo_pert.x: 0
*tipo_pert.y: 190
*tipo_pert.bottomAttachment: "attach_form"
*tipo_pert.bottomOffset: 10
*tipo_pert.leftOffset: 0
*tipo_pert.marginHeight: 5
*tipo_pert.marginWidth: 5
*tipo_pert.background: "#50a050"

*SceltaPert.class: rowColumn
*SceltaPert.static: true
*SceltaPert.name: SceltaPert
*SceltaPert.parent: tipo_pert
*SceltaPert.rowColumnType: "menu_pulldown"

*pert_1.class: pushButton
*pert_1.static: true
*pert_1.name: pert_1
*pert_1.parent: SceltaPert
*pert_1.labelString: menu_aing[0].descrizione
*pert_1.background: "#50a050"
*pert_1.activateCallback: ConfigureAing(pert_1,0);

*pert_2.class: pushButton
*pert_2.static: true
*pert_2.name: pert_2
*pert_2.parent: SceltaPert
*pert_2.labelString: menu_aing[1].descrizione
*pert_2.background: "#50a050"
*pert_2.activateCallback: ConfigureAing(pert_2,1);

*pert_3.class: pushButton
*pert_3.static: true
*pert_3.name: pert_3
*pert_3.parent: SceltaPert
*pert_3.labelString: menu_aing[2].descrizione
*pert_3.background: "#50a050"
*pert_3.activateCallback: ConfigureAing(pert_3,2);

*pert_4.class: pushButton
*pert_4.static: true
*pert_4.name: pert_4
*pert_4.parent: SceltaPert
*pert_4.labelString: menu_aing[3].descrizione
*pert_4.background: "#50a050"
*pert_4.activateCallback: ConfigureAing(pert_4,3);

*pert_5.class: pushButton
*pert_5.static: true
*pert_5.name: pert_5
*pert_5.parent: SceltaPert
*pert_5.labelString: menu_aing[4].descrizione
*pert_5.background: "#50a050"
*pert_5.activateCallback: ConfigureAing(pert_5,4);

*pert_6.class: pushButton
*pert_6.static: true
*pert_6.name: pert_6
*pert_6.parent: SceltaPert
*pert_6.labelString: menu_aing[5].descrizione
*pert_6.background: "#50a050"
*pert_6.activateCallback: ConfigureAing(pert_6,5);

*SceltaPert_b10.class: separator
*SceltaPert_b10.static: true
*SceltaPert_b10.name: SceltaPert_b10
*SceltaPert_b10.parent: SceltaPert
*SceltaPert_b10.background: "#50a050"

*pert_7.class: pushButton
*pert_7.static: true
*pert_7.name: pert_7
*pert_7.parent: SceltaPert
*pert_7.labelString: menu_aing[6].descrizione
*pert_7.activateCallback: ConfigureAing(pert_7,6);
*pert_7.background: "#50a050"

*pert_8.class: pushButton
*pert_8.static: true
*pert_8.name: pert_8
*pert_8.parent: SceltaPert
*pert_8.labelString: menu_aing[7].descrizione
*pert_8.activateCallback: ConfigureAing(pert_8,7);
*pert_8.background: "#50a050"

*SceltaPert_b11.class: separator
*SceltaPert_b11.static: true
*SceltaPert_b11.name: SceltaPert_b11
*SceltaPert_b11.parent: SceltaPert
*SceltaPert_b11.background: "#50a050"

*pert_9.class: pushButton
*pert_9.static: true
*pert_9.name: pert_9
*pert_9.parent: SceltaPert
*pert_9.labelString: menu_aing[8].descrizione
*pert_9.activateCallback: ConfigureAing(pert_9,8);
*pert_9.background: "#50a050"

*pert_10.class: pushButton
*pert_10.static: true
*pert_10.name: pert_10
*pert_10.parent: SceltaPert
*pert_10.labelString: menu_aing[9].descrizione
*pert_10.activateCallback: ConfigureAing(pert_10,9);
*pert_10.background: "#50a050"

*Configure.class: rowColumn
*Configure.static: true
*Configure.name: Configure
*Configure.parent: tasti_label
*Configure.rowColumnType: "menu_popup"
*Configure.menuAccelerator: "<KeyUp>F4"

*QuitAing.class: pushButton
*QuitAing.static: true
*QuitAing.name: QuitAing
*QuitAing.parent: Configure
*QuitAing.labelString: "Quit"
*QuitAing.background: "#50a050"
*QuitAing.activateCallback: {\
DestroyAing(Aing);\
}

*campo_1.class: label
*campo_1.static: true
*campo_1.name: campo_1
*campo_1.parent: tasti_label
*campo_1.x: 0
*campo_1.y: 0
*campo_1.width: 90
*campo_1.height: 30
*campo_1.background: "#50a050"
*campo_1.alignment: "alignment_end"
*campo_1.recomputeSize: "false"

*text_1.class: textField
*text_1.static: true
*text_1.name: text_1
*text_1.parent: tasti_label
*text_1.x: 90
*text_1.y: 0
*text_1.width: 80
*text_1.height: 30
*text_1.leftAttachment: "attach_form"
*text_1.leftOffset: 100
*text_1.leftWidget: "campo_1"
*text_1.background: "#ffffff"
*text_1.marginHeight: 5
*text_1.marginWidth: 5

*campo_2.class: label
*campo_2.static: true
*campo_2.name: campo_2
*campo_2.parent: tasti_label
*campo_2.x: 0
*campo_2.y: 30
*campo_2.width: 90
*campo_2.height: 30
*campo_2.background: "#50a050"
*campo_2.alignment: "alignment_end"
*campo_2.recomputeSize: "false"

*campo_3.class: label
*campo_3.static: true
*campo_3.name: campo_3
*campo_3.parent: tasti_label
*campo_3.x: 0
*campo_3.y: 60
*campo_3.width: 90
*campo_3.height: 30
*campo_3.background: "#50a050"
*campo_3.alignment: "alignment_end"
*campo_3.recomputeSize: "false"

*campo_4.class: label
*campo_4.static: true
*campo_4.name: campo_4
*campo_4.parent: tasti_label
*campo_4.x: 0
*campo_4.y: 90
*campo_4.width: 90
*campo_4.height: 30
*campo_4.background: "#50a050"
*campo_4.ancestorSensitive: "true"
*campo_4.alignment: "alignment_end"
*campo_4.recomputeSize: "false"

*campo_5.class: label
*campo_5.static: true
*campo_5.name: campo_5
*campo_5.parent: tasti_label
*campo_5.x: 200
*campo_5.y: 30
*campo_5.width: 90
*campo_5.height: 30
*campo_5.background: "#50a050"
*campo_5.alignment: "alignment_end"
*campo_5.recomputeSize: "false"

*campo_6.class: label
*campo_6.static: true
*campo_6.name: campo_6
*campo_6.parent: tasti_label
*campo_6.x: 200
*campo_6.y: 0
*campo_6.width: 90
*campo_6.height: 30
*campo_6.background: "#50a050"
*campo_6.alignment: "alignment_end"
*campo_6.recomputeSize: "false"

*campo_7.class: label
*campo_7.static: true
*campo_7.name: campo_7
*campo_7.parent: tasti_label
*campo_7.x: 200
*campo_7.y: 60
*campo_7.width: 90
*campo_7.height: 30
*campo_7.background: "#50a050"
*campo_7.alignment: "alignment_end"
*campo_7.recomputeSize: "false"

*text_3.class: textField
*text_3.static: true
*text_3.name: text_3
*text_3.parent: tasti_label
*text_3.x: 100
*text_3.y: 60
*text_3.width: 80
*text_3.height: 30
*text_3.backcround: "#ffffff"
*text_3.marginHeight: 5
*text_3.marginWidth: 5

*text_4.class: textField
*text_4.static: true
*text_4.name: text_4
*text_4.parent: tasti_label
*text_4.x: 100
*text_4.y: 90
*text_4.width: 80
*text_4.height: 30
*text_4.background: "#ffffff"
*text_4.marginHeight: 5
*text_4.marginWidth: 5

*text_5.class: textField
*text_5.static: true
*text_5.name: text_5
*text_5.parent: tasti_label
*text_5.x: 300
*text_5.y: 0
*text_5.width: 80
*text_5.height: 30
*text_5.background: "#ffffff"
*text_5.marginHeight: 5
*text_5.marginWidth: 5

*text_6.class: textField
*text_6.static: true
*text_6.name: text_6
*text_6.parent: tasti_label
*text_6.x: 300
*text_6.y: 30
*text_6.width: 80
*text_6.height: 30
*text_6.background: "#ffffff"
*text_6.marginHeight: 5
*text_6.marginWidth: 5

*text_7.class: textField
*text_7.static: true
*text_7.name: text_7
*text_7.parent: tasti_label
*text_7.x: 300
*text_7.y: 60
*text_7.width: 80
*text_7.height: 30
*text_7.background: "#ffffff"
*text_7.marginHeight: 5
*text_7.marginWidth: 5

*text_2.class: textField
*text_2.static: true
*text_2.name: text_2
*text_2.parent: tasti_label
*text_2.x: 100
*text_2.y: 30
*text_2.width: 80
*text_2.height: 30
*text_2.background: "#ffffff"
*text_2.marginHeight: 5
*text_2.marginWidth: 5

*timeAing.class: rowColumn
*timeAing.static: true
*timeAing.name: timeAing
*timeAing.parent: tasti_label
*timeAing.rowColumnType: "menu_option"
*timeAing.subMenuId: "menu3_p1"
*timeAing.y: 90
*timeAing.background: "#50a050"
*timeAing.bottomAttachment: "attach_none"
*timeAing.bottomOffset: 10
*timeAing.leftAttachment: "attach_form"
*timeAing.leftOffset: 200
*timeAing.leftWidget: "tipo_pert"

*menu3_p1.class: rowColumn
*menu3_p1.static: true
*menu3_p1.name: menu3_p1
*menu3_p1.parent: timeAing
*menu3_p1.rowColumnType: "menu_pulldown"
*menu3_p1.background: "#50a050"

*delayAing.class: pushButton
*delayAing.static: true
*delayAing.name: delayAing
*delayAing.parent: menu3_p1
*delayAing.labelString: "Delay"
*delayAing.background: "#50a050"
*delayAing.activateCallback: {\
TempoSelezionato = 0;\
}

*startAtAing.class: pushButton
*startAtAing.static: true
*startAtAing.name: startAtAing
*startAtAing.parent: menu3_p1
*startAtAing.labelString: "Start at"
*startAtAing.background: "#50a050"
*startAtAing.activateCallback: {\
TempoSelezionato = 1;\
}

*TextFieldTempo.class: textField
*TextFieldTempo.static: true
*TextFieldTempo.name: TextFieldTempo
*TextFieldTempo.parent: tasti_label
*TextFieldTempo.x: 300
*TextFieldTempo.y: 90
*TextFieldTempo.width: 80
*TextFieldTempo.height: 30
*TextFieldTempo.background: "#ffffff"
*TextFieldTempo.marginHeight: 5
*TextFieldTempo.marginWidth: 5

