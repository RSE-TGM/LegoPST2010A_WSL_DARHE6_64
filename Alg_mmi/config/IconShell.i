! UIMX ascii 2.5 key: 6180                                                      

*IconShell.class: topLevelShell
*IconShell.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo IconShell.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)IconShell.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "config.h"\
\
WidgetClass istanzia_wid_class;\
Widget *lista_widlib;
*IconShell.ispecdecl: XrmValue Value;\
char *Tipo;\
int Num_widget;\
\
ICONLIB *Plib;
*IconShell.ispeclist: Value, Tipo, Num_widget, Plib
*IconShell.ispeclist.Value: "XrmValue", "%Value%"
*IconShell.ispeclist.Tipo: "unsigned char", "*%Tipo%"
*IconShell.ispeclist.Num_widget: "int", "%Num_widget%"
*IconShell.ispeclist.Plib: "ICONLIB", "*%Plib%"
*IconShell.funcdecl: swidget create_IconShell( char *Libname )\

*IconShell.funcname: create_IconShell
*IconShell.funcdef: "swidget", "<create_IconShell>(%)"
*IconShell.argdecl: unsigned char *Libname;
*IconShell.arglist: Libname
*IconShell.arglist.Libname: "unsigned char", "*%Libname%"
*IconShell.icode: AN_OBJ *lista_icone = NULL;\
\
iconlib_init(Libname,&Plib);\
iconlib_getres(Plib,&lista_icone);
*IconShell.fcode: Plib->topwidget = (Widget )rtrn;\
Plib->drawing = (Widget )IconDrawingArea;\
\
/*\
 *  setta le dimensioni della drawing area\
 */\
set_something(IconDrawingArea,XmNwidth,Plib->draw_width);\
set_something(IconDrawingArea,XmNheight,Plib->draw_height);\
\
iconlib_create_widget(Plib,lista_icone);\
iconlib_def_translation(Plib);\
if(lista_icone != NULL)\
   libera_memoria(lista_icone);\
\
return(rtrn);\

*IconShell.auxdecl:
*IconShell.static: true
*IconShell.name: IconShell
*IconShell.parent: NO_PARENT
*IconShell.x: 1040
*IconShell.y: 0
*IconShell.width: 240
*IconShell.height: 1020
*IconShell.title: "Icon Library"

*IconMainWindow1.class: mainWindow
*IconMainWindow1.static: true
*IconMainWindow1.name: IconMainWindow1
*IconMainWindow1.parent: IconShell
*IconMainWindow1.unitType: "pixels"
*IconMainWindow1.x: 40
*IconMainWindow1.y: 250
*IconMainWindow1.width: 110
*IconMainWindow1.height: 310

*menuIcon.class: rowColumn
*menuIcon.static: true
*menuIcon.name: menuIcon
*menuIcon.parent: IconMainWindow1
*menuIcon.rowColumnType: "menu_bar"
*menuIcon.menuAccelerator: "<KeyUp>F10"

*menuIconFile.class: rowColumn
*menuIconFile.static: true
*menuIconFile.name: menuIconFile
*menuIconFile.parent: menuIcon
*menuIconFile.rowColumnType: "menu_pulldown"

*Close.class: pushButton
*Close.static: true
*Close.name: Close
*Close.parent: menuIconFile
*Close.labelString: "Close"
*Close.activateCallback: UxPopdownInterface(IconShell);\


*File.class: cascadeButton
*File.static: true
*File.name: File
*File.parent: menuIcon
*File.labelString: "File"
*File.subMenuId: "menuIconFile"

*form1.class: form
*form1.static: true
*form1.name: form1
*form1.parent: IconMainWindow1

*IconScrolledWindow.class: scrolledWindow
*IconScrolledWindow.static: true
*IconScrolledWindow.name: IconScrolledWindow
*IconScrolledWindow.parent: form1
*IconScrolledWindow.scrollingPolicy: "automatic"
*IconScrolledWindow.x: 0
*IconScrolledWindow.y: 0
*IconScrolledWindow.width: 240
*IconScrolledWindow.height: 940
*IconScrolledWindow.bottomAttachment: "attach_form"
*IconScrolledWindow.leftAttachment: "attach_form"
*IconScrolledWindow.rightAttachment: "attach_form"
*IconScrolledWindow.topAttachment: "attach_form"

*IconDrawingArea.class: drawingArea
*IconDrawingArea.static: true
*IconDrawingArea.name: IconDrawingArea
*IconDrawingArea.parent: IconScrolledWindow
*IconDrawingArea.resizePolicy: "resize_none"
*IconDrawingArea.x: -30
*IconDrawingArea.y: 4
*IconDrawingArea.width: 798
*IconDrawingArea.height: 990
*IconDrawingArea.marginHeight: 0
*IconDrawingArea.marginWidth: 0
*IconDrawingArea.navigationType: "none"
*IconDrawingArea.traversalOn: "false"

