! UIMX ascii 2.5 key: 2515                                                      

*Message.class: messageBoxDialog
*Message.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo Message.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)Message.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
#include <Xl/Xl.h>\
#include "res_edit.h"\
\
extern void EseguiLoadBitmap();\
extern void EseguiCaricaIcona();\
extern int EseguiLoadResource( );
*Message.ispecdecl: int Ingresso;\
Widget Oggetto;\
Widget OggettoParametro;
*Message.ispeclist: Ingresso, Oggetto, OggettoParametro
*Message.ispeclist.Ingresso: "int", "%Ingresso%"
*Message.ispeclist.Oggetto: "Widget", "%Oggetto%"
*Message.ispeclist.OggettoParametro: "Widget", "%OggettoParametro%"
*Message.funcdecl: swidget create_Message(int TipoMsg,Widget Chiamante,Widget Par)\

*Message.funcname: create_Message
*Message.funcdef: "swidget", "<create_Message>(%)"
*Message.argdecl: int TipoMsg;\
Widget Chiamante;\
Widget Par;
*Message.arglist: TipoMsg, Chiamante, Par
*Message.arglist.TipoMsg: "int", "%TipoMsg%"
*Message.arglist.Chiamante: "Widget", "%Chiamante%"
*Message.arglist.Par: "Widget", "%Par%"
*Message.icode: Position Px,Py;\
Dimension WidC,WidM,HeiC,HeiM;\
\
Ingresso = TipoMsg;\
Oggetto = Chiamante;\
OggettoParametro = Par;
*Message.fcode: get_something (Chiamante, XmNx, (char*)&Px);\
get_something (Chiamante, XmNy, (char*)&Py);\
get_something (Chiamante, XmNwidth, (char*)&WidC);\
get_something (Chiamante, XmNheight, (char*)&HeiC);\
get_something (Message, XmNwidth, (char*)&WidM);\
get_something (Message, XmNheight, (char*)&HeiM);\
\
Px += (Position )(WidC-WidM)/2;\
Py += (Position )(HeiC-HeiM)/2;\
\
set_something (rtrn, XmNx, Px);\
set_something (rtrn, XmNy, Py);\
\
return(rtrn);\

*Message.auxdecl:
*Message.name.source: public
*Message.static: false
*Message.name: Message
*Message.parent: NO_PARENT
*Message.parentExpression: Chiamante
*Message.defaultShell: dialogShell
*Message.unitType: "pixels"
*Message.width: 320
*Message.height: 145
*Message.cancelCallback: {\
XtDestroyWidget (Message);\
}
*Message.okCallback: {\
Arg arg[3];\
switch (Ingresso)\
	{\
	case LOAD:\
		EseguiLoadResources();\
	break;\
	case BITMAP:\
		EseguiLoadBitmap(Chiamante);\
	break;\
	case ICONA:\
		EseguiCaricaIcona(Chiamante,"#000000000000",OggettoParametro);\
	break;\
	case CLOSE:\
	if (OggettoParametro)\
		{\
		XtSetArg (arg[0], XlNinEdit, False);\
		XtSetArg (arg[1], XlNwEdit, NULL);\
		XtSetValues (OggettoParametro, arg, 2);\
		}\
	XtDestroyWidget (Chiamante);\
	break;\
	}\
XtDestroyWidget (Message);\
}
*Message.x: 654
*Message.y: 249

