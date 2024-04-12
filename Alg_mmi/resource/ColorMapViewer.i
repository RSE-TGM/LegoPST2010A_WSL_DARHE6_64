! UIMX ascii 2.5 key: 9300                                                      

*ColorMapViewer.class: topLevelShell
*ColorMapViewer.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ColorMapViewer.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)ColorMapViewer.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <X11/Xlib.h>\
#include <X11/Xutil.h>\
#include <X11/Xatom.h>\
#include <Xm/Label.h>\
#include "res_edit.h"\
\
extern Display *UxDisplay;
*ColorMapViewer.ispecdecl:
*ColorMapViewer.funcdecl: swidget create_ColorMapViewer(Widget Padre) \

*ColorMapViewer.funcname: create_ColorMapViewer
*ColorMapViewer.funcdef: "swidget", "<create_ColorMapViewer>(%)"
*ColorMapViewer.argdecl: Widget Padre;
*ColorMapViewer.arglist: Padre
*ColorMapViewer.arglist.Padre: "Widget", "%Padre%"
*ColorMapViewer.icode: XVisualInfo visual_info;\
Widget Wid;\
int default_depth,i;\
XmString Str;\
int NumeroMAX,j;\
Visual *default_visual;\
\
static char *visual_class[] = {\
	"StaticGray",\
	"GrayScale",\
	"StaticColor",\
	"PseudoColor",\
	"TrueColor",\
	"DirectColor"  };\
\
i = 5;
*ColorMapViewer.fcode: default_depth = DefaultDepth (UxDisplay, DefaultScreen (UxDisplay) );\
\
while (!XMatchVisualInfo (UxDisplay,DefaultScreen (UxDisplay),default_depth,\
		i--, &visual_info) )\
	;\
Str = XmStringCreateSimple (" ");\
\
NumeroMAX = visual_info.red_mask+visual_info.green_mask+visual_info.blue_mask;\
for (j=0;j<64;j++)\
	{\
	Wid = XtVaCreateManagedWidget ("label",\
		xmLabelWidgetClass, rowColumn1,\
		XmNwidth, 20,\
		XmNheight, 20,\
		XmNsensitive, True,\
		XmNbackground, j,\
		XmNrecomputeSize, False,\
		XmNlabelString, Str,\
		NULL);\
	}\
\
/* Setta la posizione dell'interfaccia rispetto al Parent  */\
InterfaceSetPos (ColorMapViewer,Padre);\
\
return(rtrn);
*ColorMapViewer.auxdecl:
*ColorMapViewer.static: true
*ColorMapViewer.name: ColorMapViewer
*ColorMapViewer.parent: NO_PARENT
*ColorMapViewer.parentExpression: Padre
*ColorMapViewer.x: 580
*ColorMapViewer.y: 110
*ColorMapViewer.width: 210
*ColorMapViewer.height: 250
*ColorMapViewer.iconName: "Color Map Viewer"
*ColorMapViewer.title: "System Color Map"
*ColorMapViewer.allowShellResize: "true"

*mainWindow6.class: mainWindow
*mainWindow6.static: true
*mainWindow6.name: mainWindow6
*mainWindow6.parent: ColorMapViewer
*mainWindow6.unitType: "pixels"
*mainWindow6.x: 40
*mainWindow6.y: 10
*mainWindow6.width: 210
*mainWindow6.height: 250

*form7.class: form
*form7.static: true
*form7.name: form7
*form7.parent: mainWindow6
*form7.noResize: "false"
*form7.width: 210
*form7.height: 250

*frame1.class: frame
*frame1.static: true
*frame1.name: frame1
*frame1.parent: form7
*frame1.x: 10
*frame1.y: 10
*frame1.width: 190
*frame1.height: 190
*frame1.borderWidth: 0
*frame1.shadowType: "shadow_etched_out"
*frame1.bottomAttachment: "attach_form"
*frame1.bottomOffset: 50
*frame1.leftAttachment: "attach_form"
*frame1.leftOffset: 10
*frame1.rightAttachment: "attach_form"
*frame1.rightOffset: 10
*frame1.topAttachment: "attach_form"
*frame1.topOffset: 10

*rowColumn1.class: rowColumn
*rowColumn1.static: true
*rowColumn1.name: rowColumn1
*rowColumn1.parent: frame1
*rowColumn1.x: 10
*rowColumn1.y: 10
*rowColumn1.width: 190
*rowColumn1.height: 190
*rowColumn1.background: "#50a0a0"
*rowColumn1.entryClass: ""
*rowColumn1.numColumns: 8
*rowColumn1.packing: "pack_column"
*rowColumn1.orientation: "vertical"
*rowColumn1.isAligned: "false"
*rowColumn1.resizeHeight: "true"
*rowColumn1.resizeWidth: "true"

*pushButton12.class: pushButton
*pushButton12.static: true
*pushButton12.name: pushButton12
*pushButton12.parent: form7
*pushButton12.x: 260
*pushButton12.y: 230
*pushButton12.width: 110
*pushButton12.height: 30
*pushButton12.labelString: "OK"
*pushButton12.bottomAttachment: "attach_form"
*pushButton12.bottomOffset: 10
*pushButton12.leftAttachment: "attach_position"
*pushButton12.leftPosition: 40
*pushButton12.rightAttachment: "attach_position"
*pushButton12.rightPosition: 60
*pushButton12.activateCallback: {\
XtDestroyWidget (ColorMapViewer);\
}

