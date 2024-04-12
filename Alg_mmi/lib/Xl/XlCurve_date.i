! UIMX ascii 2.5 key: 5076                                                      

*setDate.class: dialogShell
*setDate.gbldecl: #include <stdio.h>\
#include <stdlib.h>\
\
#define MULT_STEP 10\
#define HOUR_LIMIT 99\
#define MINUTE_LIMIT 59\
\
/*\
extern Boolean seldata_OK;\
\
extern int hour_sel,minute_sel;\
*/\

*setDate.ispecdecl:
*setDate.funcdecl: swidget create_setDate(swidget UxParent,Boolean *sel_OK,int *hour,int *minute)
*setDate.funcname: create_setDate
*setDate.funcdef: "swidget", "<create_setDate>(%)"
*setDate.argdecl: swidget UxParent;\
Boolean *sel_OK;\
int *hour;\
int *minute;
*setDate.arglist: UxParent, sel_OK, hour, minute
*setDate.arglist.UxParent: "swidget", "%UxParent%"
*setDate.arglist.sel_OK: "Boolean", "*%sel_OK%"
*setDate.arglist.hour: "int", "*%hour%"
*setDate.arglist.minute: "int", "*%minute%"
*setDate.icode: int giorno,mese,anno;\
XmString compound;\
char app[5];
*setDate.fcode: data(&giorno,&mese,&anno);\
\
sprintf(app,"%2d",giorno);\
compound=XmStringCreateSimple(app);\
XtVaSetValues(labelval,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
sprintf(app,"%2d",mese);\
compound=XmStringCreateSimple(app);\
XtVaSetValues(labelval1,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
sprintf(app,"%2d",anno);\
compound=XmStringCreateSimple(app);\
XtVaSetValues(labelval2,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
sprintf(app,"%2d",*hour);\
compound=XmStringCreateSimple(app);\
XtVaSetValues(labelval3,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
sprintf(app,"%2d",*minute);\
compound=XmStringCreateSimple(app);\
XtVaSetValues(labelval4,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
UxPopupInterface(rtrn,no_grab);\
\
return(rtrn);\

*setDate.auxdecl:
*setDate.static: true
*setDate.name: setDate
*setDate.parent: NO_PARENT
*setDate.parentExpression: UxParent
*setDate.width: 270
*setDate.height: 210
*setDate.isCompound: "true"
*setDate.compoundIcon: "dialogS.xpm"
*setDate.compoundName: "dialog_Shell"
*setDate.x: 480
*setDate.y: 760

*formdate.class: form
*formdate.static: true
*formdate.name: formdate
*formdate.parent: setDate
*formdate.width: 270
*formdate.height: 220
*formdate.resizePolicy: "resize_none"
*formdate.isCompound: "true"
*formdate.compoundIcon: "form.xpm"
*formdate.compoundName: "form_"
*formdate.x: 70
*formdate.y: 110
*formdate.unitType: "pixels"
*formdate.background: "WhiteSmoke"
*formdate.initialFocus: "pushButOK"
*formdate.noResize: "true"
*formdate.dialogStyle: "dialog_full_application_modal"

*formlab.class: form
*formlab.static: true
*formlab.name: formlab
*formlab.parent: formdate
*formlab.width: 210
*formlab.height: 30
*formlab.resizePolicy: "resize_none"
*formlab.isCompound: "true"
*formlab.compoundIcon: "form.xpm"
*formlab.compoundName: "form_"
*formlab.x: 30
*formlab.y: 20
*formlab.background: "WhiteSmoke"
*formlab.leftOffset: 30
*formlab.topOffset: 20

*labeldd.class: label
*labeldd.static: true
*labeldd.name: labeldd
*labeldd.parent: formlab
*labeldd.isCompound: "true"
*labeldd.compoundIcon: "label.xpm"
*labeldd.compoundName: "label_"
*labeldd.x: 5
*labeldd.y: 5
*labeldd.labelString: "DD"
*labeldd.height: 20
*labeldd.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labeldd.marginBottom: 4
*labeldd.topOffset: 0
*labeldd.leftOffset: 0
*labeldd.bottomAttachment: "attach_form"
*labeldd.bottomOffset: 5
*labeldd.background: "WhiteSmoke"
*labeldd.width: 30

*labelmm.class: label
*labelmm.static: true
*labelmm.name: labelmm
*labelmm.parent: formlab
*labelmm.isCompound: "true"
*labelmm.compoundIcon: "label.xpm"
*labelmm.compoundName: "label_"
*labelmm.x: 40
*labelmm.y: 10
*labelmm.labelString: "MM"
*labelmm.height: 20
*labelmm.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelmm.marginBottom: 4
*labelmm.background: "WhiteSmoke"
*labelmm.bottomAttachment: "attach_form"
*labelmm.bottomOffset: 5
*labelmm.width: 30
*labelmm.leftOffset: 10
*labelmm.leftAttachment: "attach_widget"
*labelmm.leftWidget: "labeldd"

*labelyy.class: label
*labelyy.static: true
*labelyy.name: labelyy
*labelyy.parent: formlab
*labelyy.isCompound: "true"
*labelyy.compoundIcon: "label.xpm"
*labelyy.compoundName: "label_"
*labelyy.x: 80
*labelyy.y: 10
*labelyy.labelString: "YY"
*labelyy.height: 20
*labelyy.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelyy.marginBottom: 4
*labelyy.background: "WhiteSmoke"
*labelyy.bottomAttachment: "attach_form"
*labelyy.bottomOffset: 5
*labelyy.width: 30
*labelyy.leftOffset: 10
*labelyy.leftAttachment: "attach_widget"
*labelyy.leftWidget: "labelmm"

*labelhr.class: label
*labelhr.static: true
*labelhr.name: labelhr
*labelhr.parent: formlab
*labelhr.isCompound: "true"
*labelhr.compoundIcon: "label.xpm"
*labelhr.compoundName: "label_"
*labelhr.x: 130
*labelhr.y: 10
*labelhr.labelString: "Hr"
*labelhr.height: 20
*labelhr.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelhr.marginBottom: 4
*labelhr.background: "WhiteSmoke"
*labelhr.width: 30
*labelhr.bottomAttachment: "attach_form"
*labelhr.bottomOffset: 5
*labelhr.leftAttachment: "attach_widget"
*labelhr.leftOffset: 20
*labelhr.leftWidget: "labelyy"

*labelmn.class: label
*labelmn.static: true
*labelmn.name: labelmn
*labelmn.parent: formlab
*labelmn.isCompound: "true"
*labelmn.compoundIcon: "label.xpm"
*labelmn.compoundName: "label_"
*labelmn.x: 170
*labelmn.y: 0
*labelmn.labelString: "Mn"
*labelmn.height: 20
*labelmn.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelmn.marginBottom: 4
*labelmn.background: "WhiteSmoke"
*labelmn.width: 30
*labelmn.bottomAttachment: "attach_form"
*labelmn.bottomOffset: 5
*labelmn.leftOffset: 10
*labelmn.leftAttachment: "attach_widget"
*labelmn.leftWidget: "labelhr"

*formarrow.class: form
*formarrow.static: true
*formarrow.name: formarrow
*formarrow.parent: formdate
*formarrow.width: 210
*formarrow.height: 120
*formarrow.resizePolicy: "resize_none"
*formarrow.isCompound: "true"
*formarrow.compoundIcon: "form.xpm"
*formarrow.compoundName: "form_"
*formarrow.x: 30
*formarrow.y: 50
*formarrow.background: "WhiteSmoke"

*formarrow1.class: form
*formarrow1.static: true
*formarrow1.name: formarrow1
*formarrow1.parent: formarrow
*formarrow1.width: 30
*formarrow1.height: 110
*formarrow1.resizePolicy: "resize_none"
*formarrow1.isCompound: "true"
*formarrow1.compoundIcon: "form.xpm"
*formarrow1.compoundName: "form_"
*formarrow1.x: 5
*formarrow1.y: 5
*formarrow1.topOffset: 5
*formarrow1.bottomAttachment: "attach_form"
*formarrow1.bottomOffset: 5
*formarrow1.background: "WhiteSmoke"

*arrowButUp1.class: arrowButton
*arrowButUp1.static: true
*arrowButUp1.name: arrowButUp1
*arrowButUp1.parent: formarrow1
*arrowButUp1.isCompound: "true"
*arrowButUp1.compoundIcon: "arrow.xpm"
*arrowButUp1.compoundName: "arrow_Button"
*arrowButUp1.x: 0
*arrowButUp1.y: 0
*arrowButUp1.height: 20
*arrowButUp1.width: 30
*arrowButUp1.sensitive: "false"

*arrowButUp2.class: arrowButton
*arrowButUp2.static: true
*arrowButUp2.name: arrowButUp2
*arrowButUp2.parent: formarrow1
*arrowButUp2.isCompound: "true"
*arrowButUp2.compoundIcon: "arrow.xpm"
*arrowButUp2.compoundName: "arrow_Button"
*arrowButUp2.x: 0
*arrowButUp2.y: 20
*arrowButUp2.height: 20
*arrowButUp2.width: 30
*arrowButUp2.activateCallback: {\
String str_dd;\
XmString compound;\
char str_new[5];\
int dd;\
\
XtVaGetValues(labelval,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_dd);\
XmStringFree(compound);\
printf("callback_date: string_dd=%s\n",str_dd);\
dd=atoi(str_dd);\
if(dd<31)\
   dd++;\
else\
   dd=1;\
if(dd<10)\
   sprintf(str_new,"0%d",dd);\
else\
   sprintf(str_new,"%d",dd);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
\
}
*arrowButUp2.sensitive: "false"

*labelval.class: label
*labelval.static: true
*labelval.name: labelval
*labelval.parent: formarrow1
*labelval.isCompound: "true"
*labelval.compoundIcon: "label.xpm"
*labelval.compoundName: "label_"
*labelval.x: 2
*labelval.y: 39
*labelval.height: 27
*labelval.width: 26
*labelval.labelString: "00"
*labelval.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelval.borderWidth: 0
*labelval.borderColor: "#a05050"
*labelval.bottomShadowColor: "SaddleBrown"
*labelval.shadowThickness: 0
*labelval.topShadowColor: "#8b4513"
*labelval.topOffset: 38
*labelval.sensitive: "true"

*arrowButDown1.class: arrowButton
*arrowButDown1.static: true
*arrowButDown1.name: arrowButDown1
*arrowButDown1.parent: formarrow1
*arrowButDown1.isCompound: "true"
*arrowButDown1.compoundIcon: "arrow.xpm"
*arrowButDown1.compoundName: "arrow_Button"
*arrowButDown1.x: 0
*arrowButDown1.y: 65
*arrowButDown1.height: 20
*arrowButDown1.width: 30
*arrowButDown1.arrowDirection: "arrow_down"
*arrowButDown1.sensitive: "false"

*arrowButDown2.class: arrowButton
*arrowButDown2.static: true
*arrowButDown2.name: arrowButDown2
*arrowButDown2.parent: formarrow1
*arrowButDown2.isCompound: "true"
*arrowButDown2.compoundIcon: "arrow.xpm"
*arrowButDown2.compoundName: "arrow_Button"
*arrowButDown2.x: 0
*arrowButDown2.y: 85
*arrowButDown2.height: 20
*arrowButDown2.width: 30
*arrowButDown2.arrowDirection: "arrow_down"
*arrowButDown2.sensitive: "false"

*formarrow2.class: form
*formarrow2.static: true
*formarrow2.name: formarrow2
*formarrow2.parent: formarrow
*formarrow2.width: 30
*formarrow2.height: 110
*formarrow2.resizePolicy: "resize_none"
*formarrow2.isCompound: "true"
*formarrow2.compoundIcon: "form.xpm"
*formarrow2.compoundName: "form_"
*formarrow2.x: 44
*formarrow2.y: 5
*formarrow2.background: "WhiteSmoke"

*arrowButUp3.class: arrowButton
*arrowButUp3.static: true
*arrowButUp3.name: arrowButUp3
*arrowButUp3.parent: formarrow2
*arrowButUp3.isCompound: "true"
*arrowButUp3.compoundIcon: "arrow.xpm"
*arrowButUp3.compoundName: "arrow_Button"
*arrowButUp3.x: 0
*arrowButUp3.y: 0
*arrowButUp3.height: 20
*arrowButUp3.width: 30
*arrowButUp3.sensitive: "false"

*arrowButUp4.class: arrowButton
*arrowButUp4.static: true
*arrowButUp4.name: arrowButUp4
*arrowButUp4.parent: formarrow2
*arrowButUp4.isCompound: "true"
*arrowButUp4.compoundIcon: "arrow.xpm"
*arrowButUp4.compoundName: "arrow_Button"
*arrowButUp4.x: 0
*arrowButUp4.y: 20
*arrowButUp4.height: 20
*arrowButUp4.width: 30
*arrowButUp4.sensitive: "false"

*labelval1.class: label
*labelval1.static: true
*labelval1.name: labelval1
*labelval1.parent: formarrow2
*labelval1.isCompound: "true"
*labelval1.compoundIcon: "label.xpm"
*labelval1.compoundName: "label_"
*labelval1.x: 2
*labelval1.y: 39
*labelval1.height: 27
*labelval1.width: 26
*labelval1.labelString: "00"
*labelval1.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelval1.borderWidth: 0
*labelval1.borderColor: "#a05050"

*arrowButDown3.class: arrowButton
*arrowButDown3.static: true
*arrowButDown3.name: arrowButDown3
*arrowButDown3.parent: formarrow2
*arrowButDown3.isCompound: "true"
*arrowButDown3.compoundIcon: "arrow.xpm"
*arrowButDown3.compoundName: "arrow_Button"
*arrowButDown3.x: 0
*arrowButDown3.y: 65
*arrowButDown3.height: 20
*arrowButDown3.width: 30
*arrowButDown3.arrowDirection: "arrow_down"
*arrowButDown3.sensitive: "false"

*arrowButDown4.class: arrowButton
*arrowButDown4.static: true
*arrowButDown4.name: arrowButDown4
*arrowButDown4.parent: formarrow2
*arrowButDown4.isCompound: "true"
*arrowButDown4.compoundIcon: "arrow.xpm"
*arrowButDown4.compoundName: "arrow_Button"
*arrowButDown4.x: 0
*arrowButDown4.y: 85
*arrowButDown4.height: 20
*arrowButDown4.width: 30
*arrowButDown4.arrowDirection: "arrow_down"
*arrowButDown4.sensitive: "false"

*formarrow3.class: form
*formarrow3.static: true
*formarrow3.name: formarrow3
*formarrow3.parent: formarrow
*formarrow3.width: 30
*formarrow3.height: 110
*formarrow3.resizePolicy: "resize_none"
*formarrow3.isCompound: "true"
*formarrow3.compoundIcon: "form.xpm"
*formarrow3.compoundName: "form_"
*formarrow3.x: 83
*formarrow3.y: 5
*formarrow3.background: "WhiteSmoke"

*arrowButUp5.class: arrowButton
*arrowButUp5.static: true
*arrowButUp5.name: arrowButUp5
*arrowButUp5.parent: formarrow3
*arrowButUp5.isCompound: "true"
*arrowButUp5.compoundIcon: "arrow.xpm"
*arrowButUp5.compoundName: "arrow_Button"
*arrowButUp5.x: 0
*arrowButUp5.y: 0
*arrowButUp5.height: 20
*arrowButUp5.width: 30
*arrowButUp5.sensitive: "false"

*arrowButUp6.class: arrowButton
*arrowButUp6.static: true
*arrowButUp6.name: arrowButUp6
*arrowButUp6.parent: formarrow3
*arrowButUp6.isCompound: "true"
*arrowButUp6.compoundIcon: "arrow.xpm"
*arrowButUp6.compoundName: "arrow_Button"
*arrowButUp6.x: 0
*arrowButUp6.y: 20
*arrowButUp6.height: 20
*arrowButUp6.width: 30
*arrowButUp6.sensitive: "false"

*labelval2.class: label
*labelval2.static: true
*labelval2.name: labelval2
*labelval2.parent: formarrow3
*labelval2.isCompound: "true"
*labelval2.compoundIcon: "label.xpm"
*labelval2.compoundName: "label_"
*labelval2.x: 2
*labelval2.y: 39
*labelval2.height: 27
*labelval2.width: 26
*labelval2.labelString: "00"
*labelval2.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelval2.borderWidth: 0
*labelval2.borderColor: "#a05050"

*arrowButDown5.class: arrowButton
*arrowButDown5.static: true
*arrowButDown5.name: arrowButDown5
*arrowButDown5.parent: formarrow3
*arrowButDown5.isCompound: "true"
*arrowButDown5.compoundIcon: "arrow.xpm"
*arrowButDown5.compoundName: "arrow_Button"
*arrowButDown5.x: 0
*arrowButDown5.y: 65
*arrowButDown5.height: 20
*arrowButDown5.width: 30
*arrowButDown5.arrowDirection: "arrow_down"
*arrowButDown5.sensitive: "false"

*arrowButDown6.class: arrowButton
*arrowButDown6.static: true
*arrowButDown6.name: arrowButDown6
*arrowButDown6.parent: formarrow3
*arrowButDown6.isCompound: "true"
*arrowButDown6.compoundIcon: "arrow.xpm"
*arrowButDown6.compoundName: "arrow_Button"
*arrowButDown6.x: 0
*arrowButDown6.y: 85
*arrowButDown6.height: 20
*arrowButDown6.width: 30
*arrowButDown6.arrowDirection: "arrow_down"
*arrowButDown6.sensitive: "false"

*formarrow4.class: form
*formarrow4.static: true
*formarrow4.name: formarrow4
*formarrow4.parent: formarrow
*formarrow4.width: 30
*formarrow4.height: 110
*formarrow4.resizePolicy: "resize_none"
*formarrow4.isCompound: "true"
*formarrow4.compoundIcon: "form.xpm"
*formarrow4.compoundName: "form_"
*formarrow4.x: 132
*formarrow4.y: 5
*formarrow4.background: "WhiteSmoke"

*arrowButUp7.class: arrowButton
*arrowButUp7.static: true
*arrowButUp7.name: arrowButUp7
*arrowButUp7.parent: formarrow4
*arrowButUp7.isCompound: "true"
*arrowButUp7.compoundIcon: "arrow.xpm"
*arrowButUp7.compoundName: "arrow_Button"
*arrowButUp7.x: 0
*arrowButUp7.y: 0
*arrowButUp7.height: 20
*arrowButUp7.width: 30
*arrowButUp7.activateCallback: {\
String str_hr;\
XmString compound;\
char str_new[5];\
int hr;\
\
XtVaGetValues(labelval3,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_hr);\
XmStringFree(compound);\
printf("callback_date: string_hr=%s\n",str_hr);\
hr=atoi(str_hr);\
if(hr<(100-MULT_STEP))\
   hr=hr+MULT_STEP;\
else\
   hr=hr-(100-MULT_STEP);\
if(hr<10)\
   sprintf(str_new,"0%d",hr);\
else\
   sprintf(str_new,"%d",hr);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval3,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
   \
}

*arrowButUp8.class: arrowButton
*arrowButUp8.static: true
*arrowButUp8.name: arrowButUp8
*arrowButUp8.parent: formarrow4
*arrowButUp8.isCompound: "true"
*arrowButUp8.compoundIcon: "arrow.xpm"
*arrowButUp8.compoundName: "arrow_Button"
*arrowButUp8.x: 0
*arrowButUp8.y: 20
*arrowButUp8.height: 20
*arrowButUp8.width: 30
*arrowButUp8.activateCallback: {\
String str_hr;\
XmString compound;\
char str_new[5];\
int hr;\
\
XtVaGetValues(labelval3,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_hr);\
XmStringFree(compound);\
printf("callback_date: string_hr=%s\n",str_hr);\
hr=atoi(str_hr);\
if(hr<HOUR_LIMIT)\
   hr++;\
else\
   hr=0;\
if(hr<10)\
   sprintf(str_new,"0%d",hr);\
else\
   sprintf(str_new,"%d",hr);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval3,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
\
}

*labelval3.class: label
*labelval3.static: true
*labelval3.name: labelval3
*labelval3.parent: formarrow4
*labelval3.isCompound: "true"
*labelval3.compoundIcon: "label.xpm"
*labelval3.compoundName: "label_"
*labelval3.x: 2
*labelval3.y: 39
*labelval3.height: 27
*labelval3.width: 26
*labelval3.labelString: "00"
*labelval3.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelval3.borderWidth: 0
*labelval3.borderColor: "#a05050"

*arrowButDown7.class: arrowButton
*arrowButDown7.static: true
*arrowButDown7.name: arrowButDown7
*arrowButDown7.parent: formarrow4
*arrowButDown7.isCompound: "true"
*arrowButDown7.compoundIcon: "arrow.xpm"
*arrowButDown7.compoundName: "arrow_Button"
*arrowButDown7.x: 0
*arrowButDown7.y: 65
*arrowButDown7.height: 20
*arrowButDown7.width: 30
*arrowButDown7.arrowDirection: "arrow_down"
*arrowButDown7.activateCallback: {\
String str_hr;\
XmString compound;\
char str_new[5];\
int hr;\
\
XtVaGetValues(labelval3,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_hr);\
XmStringFree(compound);\
printf("callback_date: string_dd=%s\n",str_hr);\
hr=atoi(str_hr);\
if(hr!=0)\
   hr--;\
else\
   hr=HOUR_LIMIT;\
if(hr<10)\
   sprintf(str_new,"0%d",hr);\
else\
   sprintf(str_new,"%d",hr);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval3,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*arrowButDown8.class: arrowButton
*arrowButDown8.static: true
*arrowButDown8.name: arrowButDown8
*arrowButDown8.parent: formarrow4
*arrowButDown8.isCompound: "true"
*arrowButDown8.compoundIcon: "arrow.xpm"
*arrowButDown8.compoundName: "arrow_Button"
*arrowButDown8.x: 0
*arrowButDown8.y: 85
*arrowButDown8.height: 20
*arrowButDown8.width: 30
*arrowButDown8.arrowDirection: "arrow_down"
*arrowButDown8.activateCallback: {\
String str_hr;\
XmString compound;\
char str_new[5];\
int hr;\
\
XtVaGetValues(labelval3,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_hr);\
XmStringFree(compound);\
printf("callback_date: string_hr=%s\n",str_hr);\
hr=atoi(str_hr);\
if(hr>=10)\
   hr=hr-MULT_STEP;\
else\
   hr=100+(hr-MULT_STEP);\
if(hr<10)\
   sprintf(str_new,"0%d",hr);\
else\
   sprintf(str_new,"%d",hr);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval3,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*formarrow5.class: form
*formarrow5.static: true
*formarrow5.name: formarrow5
*formarrow5.parent: formarrow
*formarrow5.width: 30
*formarrow5.height: 110
*formarrow5.resizePolicy: "resize_none"
*formarrow5.isCompound: "true"
*formarrow5.compoundIcon: "form.xpm"
*formarrow5.compoundName: "form_"
*formarrow5.x: 171
*formarrow5.y: 5
*formarrow5.background: "WhiteSmoke"

*arrowButUp9.class: arrowButton
*arrowButUp9.static: true
*arrowButUp9.name: arrowButUp9
*arrowButUp9.parent: formarrow5
*arrowButUp9.isCompound: "true"
*arrowButUp9.compoundIcon: "arrow.xpm"
*arrowButUp9.compoundName: "arrow_Button"
*arrowButUp9.x: 0
*arrowButUp9.y: 0
*arrowButUp9.height: 20
*arrowButUp9.width: 30
*arrowButUp9.activateCallback: {\
String str_min;\
XmString compound;\
char str_new[5];\
int min;\
\
XtVaGetValues(labelval4,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_min);\
XmStringFree(compound);\
printf("callback_date: string_min=%s\n",str_min);\
min=atoi(str_min);\
if(min<=(MINUTE_LIMIT-MULT_STEP))\
   min=min+MULT_STEP;\
else\
   min=min-(60-MULT_STEP);\
if(min<10)\
   sprintf(str_new,"0%d",min);\
else\
   sprintf(str_new,"%d",min);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval4,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*arrowButUp10.class: arrowButton
*arrowButUp10.static: true
*arrowButUp10.name: arrowButUp10
*arrowButUp10.parent: formarrow5
*arrowButUp10.isCompound: "true"
*arrowButUp10.compoundIcon: "arrow.xpm"
*arrowButUp10.compoundName: "arrow_Button"
*arrowButUp10.x: 0
*arrowButUp10.y: 20
*arrowButUp10.height: 20
*arrowButUp10.width: 30
*arrowButUp10.activateCallback: {\
String str_min;\
XmString compound;\
char str_new[5];\
int min;\
\
XtVaGetValues(labelval4,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_min);\
XmStringFree(compound);\
printf("callback_date: string_dd=%s\n",str_min);\
min=atoi(str_min);\
printf("callback_date: minuti=%d\n",min);\
if(min<MINUTE_LIMIT)\
   min++;\
else\
   min=0;\
printf("callback_date: minuti_after=%d\n",min);\
if(min<10)\
   sprintf(str_new,"0%d",min);\
else\
   sprintf(str_new,"%d",min);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval4,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*labelval4.class: label
*labelval4.static: true
*labelval4.name: labelval4
*labelval4.parent: formarrow5
*labelval4.isCompound: "true"
*labelval4.compoundIcon: "label.xpm"
*labelval4.compoundName: "label_"
*labelval4.x: 2
*labelval4.y: 39
*labelval4.height: 27
*labelval4.width: 26
*labelval4.labelString: "00"
*labelval4.fontList: "-adobe-courier-bold-r-normal--20-140-100-100-m-110-iso8859-1"
*labelval4.borderWidth: 0
*labelval4.borderColor: "#a05050"

*arrowButDown9.class: arrowButton
*arrowButDown9.static: true
*arrowButDown9.name: arrowButDown9
*arrowButDown9.parent: formarrow5
*arrowButDown9.isCompound: "true"
*arrowButDown9.compoundIcon: "arrow.xpm"
*arrowButDown9.compoundName: "arrow_Button"
*arrowButDown9.x: 0
*arrowButDown9.y: 65
*arrowButDown9.height: 20
*arrowButDown9.width: 30
*arrowButDown9.arrowDirection: "arrow_down"
*arrowButDown9.activateCallback: {\
String str_min;\
XmString compound;\
char str_new[5];\
int min;\
\
XtVaGetValues(labelval4,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_min);\
XmStringFree(compound);\
printf("callback_date: string_dd=%s\n",str_min);\
min=atoi(str_min);\
if(min!=0)\
   min--;\
else\
   min=MINUTE_LIMIT;\
if(min<10)\
   sprintf(str_new,"0%d",min);\
else\
   sprintf(str_new,"%d",min);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval4,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*arrowButDown10.class: arrowButton
*arrowButDown10.static: true
*arrowButDown10.name: arrowButDown10
*arrowButDown10.parent: formarrow5
*arrowButDown10.isCompound: "true"
*arrowButDown10.compoundIcon: "arrow.xpm"
*arrowButDown10.compoundName: "arrow_Button"
*arrowButDown10.x: 0
*arrowButDown10.y: 85
*arrowButDown10.height: 20
*arrowButDown10.width: 30
*arrowButDown10.arrowDirection: "arrow_down"
*arrowButDown10.activateCallback: {\
String str_min;\
XmString compound;\
char str_new[5];\
int min;\
\
XtVaGetValues(labelval4,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str_min);\
XmStringFree(compound);\
printf("callback_date: string_min=%s\n",str_min);\
min=atoi(str_min);\
if(min>=MULT_STEP)\
   min=min-MULT_STEP;\
else\
   min=60+(min-MULT_STEP);\
if(min<10)\
   sprintf(str_new,"0%d",min);\
else\
   sprintf(str_new,"%d",min);\
compound=XmStringCreateSimple(str_new);\
XtVaSetValues(labelval4,XmNlabelString,compound,NULL);\
XmStringFree(compound);\
}

*pushButOK.class: pushButton
*pushButOK.static: true
*pushButOK.name: pushButOK
*pushButOK.parent: formdate
*pushButOK.isCompound: "true"
*pushButOK.compoundIcon: "push.xpm"
*pushButOK.compoundName: "push_Button"
*pushButOK.x: 35
*pushButOK.y: 175
*pushButOK.labelString: "OK"
*pushButOK.recomputeSize: "true"
*pushButOK.width: 60
*pushButOK.height: 30
*pushButOK.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButOK.marginHeight: 0
*pushButOK.marginBottom: 2
*pushButOK.marginTop: 2
*pushButOK.activateCallback: {\
String str;\
XmString compound;\
\
XtVaGetValues(labelval3,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str);\
XmStringFree(compound);\
*hour=atoi(str);\
\
XtVaGetValues(labelval4,XmNlabelString,&compound,NULL);\
XmStringGetLtoR(compound,XmSTRING_DEFAULT_CHARSET,&str);\
XmStringFree(compound);\
*minute=atoi(str);\
\
printf("datasel: hour_sel=%d\tminute_sel=%d\n",*hour,*minute);\
\
*sel_OK=True;\
\
UxDestroyInterface(UxThisWidget);\
\
\
}

*pushButCanc.class: pushButton
*pushButCanc.static: true
*pushButCanc.name: pushButCanc
*pushButCanc.parent: formdate
*pushButCanc.isCompound: "true"
*pushButCanc.compoundIcon: "push.xpm"
*pushButCanc.compoundName: "push_Button"
*pushButCanc.x: 140
*pushButCanc.y: 175
*pushButCanc.labelString: "Cancel"
*pushButCanc.recomputeSize: "true"
*pushButCanc.width: 110
*pushButCanc.height: 30
*pushButCanc.fontList: "-adobe-courier-bold-r-normal--18-180-75-75-m-110-iso8859-1"
*pushButCanc.marginHeight: 0
*pushButCanc.marginBottom: 2
*pushButCanc.marginTop: 2
*pushButCanc.leftAttachment: "attach_widget"
*pushButCanc.leftOffset: 40
*pushButCanc.leftWidget: "pushButOK"
*pushButCanc.topOffset: 175
*pushButCanc.activateCallback: {\
UxDestroyInterface(UxThisWidget);\
}

